/**
 * @file bs_framer.cpp
 * @brief Brain-side stream framer for Brain <-> Spine protocol v0.2
 *
 * Deterministically extracts complete packet frames from an arbitrary byte stream.
 * Resynchronization strategy: scan for magic at buffer[0]; on mismatch or invalid
 * header, discard 1 byte and retry.
 *
 * No I/O, no timing, no dynamic allocation.
 */

#include <cstdint>
#include <cstddef>
#include <cstring>

#include "bs_contract_constants.h"

namespace s2t {
namespace protocol {

// Forward declarations from Chunk C.
// We intentionally do NOT duplicate these types/values here.
struct PacketHeader;
enum class HeaderStatus;
HeaderStatus parse_and_validate_header(const uint8_t* buf, std::size_t len, PacketHeader* out);

static constexpr std::size_t MAX_FRAME_BUFFER_SIZE =
    HEADER_SIZE_BYTES + MAX_PAYLOAD_SIZE_BYTES + TRAILER_SIZE_BYTES;

typedef void (*FrameCallback)(const uint8_t* frame_buf, std::size_t frame_len, void* ctx);

struct ByteStreamFramer {
    uint8_t buffer[MAX_FRAME_BUFFER_SIZE];
    std::size_t write_idx = 0;

    // Observability counters (purely internal state; no I/O here)
    uint32_t sync_loss_count = 0;
    uint32_t frames_found_count = 0;
};

static inline void discard_one(ByteStreamFramer* framer)
{
    if (framer->write_idx == 0) {
        return;
    }
    std::memmove(framer->buffer, framer->buffer + 1, framer->write_idx - 1);
    framer->write_idx--;
    framer->sync_loss_count++;
}

void bs_framer_init(ByteStreamFramer* framer)
{
    if (!framer) {
        return;
    }
    framer->write_idx = 0;
    framer->sync_loss_count = 0;
    framer->frames_found_count = 0;
    std::memset(framer->buffer, 0, MAX_FRAME_BUFFER_SIZE);
}

void bs_framer_push(ByteStreamFramer* framer,
                    const uint8_t* data,
                    std::size_t len,
                    FrameCallback callback,
                    void* callback_ctx)
{
    if (!framer || !data || !callback) {
        return;
    }

    const uint8_t magic_lo = static_cast<uint8_t>(PROTO_MAGIC & 0xFF);
    const uint8_t magic_hi = static_cast<uint8_t>((PROTO_MAGIC >> 8) & 0xFF);

    std::size_t in_idx = 0;

    while (true) {
        // Fill internal buffer as much as possible.
        while (in_idx < len && framer->write_idx < MAX_FRAME_BUFFER_SIZE) {
            framer->buffer[framer->write_idx++] = data[in_idx++];
        }

        // If buffer is full and we still have more input, discard until space.
        // This is deterministic and preserves resync behavior under overload.
        while (in_idx < len && framer->write_idx == MAX_FRAME_BUFFER_SIZE) {
            discard_one(framer);
        }

        // We need at least 2 bytes to check magic.
        if (framer->write_idx < 2) {
            // No more internal work possible without more input.
            if (in_idx >= len) {
                return;
            }
            continue;
        }

        // Magic check at buffer[0..1].
        if (framer->buffer[0] != magic_lo || framer->buffer[1] != magic_hi) {
            discard_one(framer);
            continue;
        }

        // Need full header to validate and learn payload length safely.
        if (framer->write_idx < HEADER_SIZE_BYTES) {
            if (in_idx >= len) {
                return;
            }
            continue;
        }

        // Validate header (includes CRC16); pass at least HEADER_SIZE_BYTES.
        PacketHeader hdr;
        const HeaderStatus hs = parse_and_validate_header(framer->buffer, HEADER_SIZE_BYTES, &hdr);
        if (hs != HeaderStatus::OK) {
            discard_one(framer);
            continue;
        }

        const std::size_t payload_len = static_cast<std::size_t>(hdr.payload_len);
        const std::size_t frame_len = HEADER_SIZE_BYTES + payload_len + TRAILER_SIZE_BYTES;

        if (frame_len > MAX_FRAME_BUFFER_SIZE) {
            // Should be impossible if header validation enforces payload cap, but keep it hard.
            discard_one(framer);
            continue;
        }

        // Wait until full frame is buffered.
        if (framer->write_idx < frame_len) {
            if (in_idx >= len) {
                return;
            }
            continue;
        }

        // Emit the complete frame (validator decides if payload CRC32 passes).
        callback(framer->buffer, frame_len, callback_ctx);
        framer->frames_found_count++;

        // Consume emitted frame and keep any trailing bytes.
        const std::size_t remaining = framer->write_idx - frame_len;
        if (remaining > 0) {
            std::memmove(framer->buffer, framer->buffer + frame_len, remaining);
        }
        framer->write_idx = remaining;

        // Continue: may have another packet already buffered, or may need more input.
        if (framer->write_idx == 0 && in_idx >= len) {
            return;
        }
    }
}

} // namespace protocol
} // namespace s2t
