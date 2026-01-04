/**
 * @file bs_packet.cpp
 * @brief Brain-side full packet validation for Brain <-> Spine protocol v0.2
 *
 * Validates a contiguous packet buffer:
 * 1) Header parse/validate (magic/version/payload cap/header CRC16)
 * 2) Total length consistency (header + payload + trailer)
 * 3) Payload CRC32 vs trailer
 *
 * No framing, no buffering, no I/O, no timing.
 */

#include <cstdint>
#include <cstddef>
#include <limits>

#include "bs_contract_constants.h"

namespace s2t {
namespace protocol {

// Forward declarations from earlier chunks.
// NOTE: We intentionally avoid duplicating wire/type definitions here.
struct PacketHeader;
enum class HeaderStatus;
HeaderStatus parse_and_validate_header(const uint8_t* buf, std::size_t len, PacketHeader* out);

uint32_t compute_payload_crc32(const uint8_t* data, std::size_t len);

enum class PacketStatus {
    OK = 0,
    ERR_INVALID_ARGS,
    ERR_HEADER_INVALID,
    ERR_LENGTH_MISMATCH,
    ERR_PAYLOAD_CRC_MISMATCH
};

static inline uint32_t read_u32_le(const uint8_t* p)
{
    return static_cast<uint32_t>(static_cast<uint32_t>(p[0]) |
                                 (static_cast<uint32_t>(p[1]) << 8) |
                                 (static_cast<uint32_t>(p[2]) << 16) |
                                 (static_cast<uint32_t>(p[3]) << 24));
}

PacketStatus validate_packet(const uint8_t* buf, std::size_t len)
{
    if (!buf) {
        return PacketStatus::ERR_INVALID_ARGS;
    }
    if (len < MIN_PACKET_SIZE_BYTES) {
        return PacketStatus::ERR_HEADER_INVALID;
    }

    PacketHeader header;
    const HeaderStatus hs = parse_and_validate_header(buf, len, &header);
    if (hs != HeaderStatus::OK) {
        return PacketStatus::ERR_HEADER_INVALID;
    }

    // expected_total = HEADER_SIZE_BYTES + payload_len + TRAILER_SIZE_BYTES
    // Guard against overflow in size_t arithmetic.
    const std::size_t payload_len = static_cast<std::size_t>(header.payload_len);

    if (payload_len > (std::numeric_limits<std::size_t>::max() - HEADER_SIZE_BYTES - TRAILER_SIZE_BYTES)) {
        return PacketStatus::ERR_LENGTH_MISMATCH;
    }

    const std::size_t expected_total_len =
        HEADER_SIZE_BYTES + payload_len + TRAILER_SIZE_BYTES;

    if (len != expected_total_len) {
        return PacketStatus::ERR_LENGTH_MISMATCH;
    }

    const uint8_t* payload_ptr = buf + HEADER_SIZE_BYTES;
    const uint8_t* trailer_ptr = payload_ptr + payload_len;

    const uint32_t trailer_crc = read_u32_le(&trailer_ptr[TRAILER_OFFSET_CRC32]);
    const uint32_t computed_crc = compute_payload_crc32(payload_ptr, payload_len);

    if (computed_crc != trailer_crc) {
        return PacketStatus::ERR_PAYLOAD_CRC_MISMATCH;
    }

    return PacketStatus::OK;
}

} // namespace protocol
} // namespace s2t
