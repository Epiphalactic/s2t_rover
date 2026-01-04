#ifndef BS_PROTOCOL_H
#define BS_PROTOCOL_H

#include <cstdint>
#include <cstddef>

#include "bs_contract_constants.h"

namespace s2t {
namespace protocol {

// ==========================================================================
// SHARED CONSTANTS & TYPES
// ==========================================================================

static constexpr std::size_t MAX_FRAME_BUFFER_SIZE =
    HEADER_SIZE_BYTES + MAX_PAYLOAD_SIZE_BYTES + TRAILER_SIZE_BYTES;

struct PacketHeader {
    uint16_t magic;
    uint8_t  proto_major;
    uint8_t  proto_minor;
    uint8_t  msg_type;
    uint8_t  flags;
    uint8_t  src;
    uint8_t  dst;
    uint16_t seq;
    uint16_t payload_len;
    uint16_t header_crc16;
};

enum class HeaderStatus {
    OK = 0,
    ERR_INVALID_ARGS,
    ERR_BUFFER_TOO_SMALL,
    ERR_MAGIC_MISMATCH,
    ERR_VERSION_MISMATCH,
    ERR_PAYLOAD_TOO_LARGE,
    ERR_CRC_MISMATCH
};

enum class PacketStatus {
    OK = 0,
    ERR_INVALID_ARGS,
    ERR_HEADER_INVALID,
    ERR_LENGTH_MISMATCH,
    ERR_PAYLOAD_CRC_MISMATCH
};

struct ByteStreamFramer {
    uint8_t  buffer[MAX_FRAME_BUFFER_SIZE];
    std::size_t write_idx;
    uint32_t sync_loss_count;
    uint32_t frames_found_count;
};

typedef void (*FrameCallback)(const uint8_t* frame_buf,
                              std::size_t frame_len,
                              void* ctx);

// ==========================================================================
// PUBLIC INTERFACE
// ==========================================================================

HeaderStatus parse_and_validate_header(const uint8_t* buf,
                                      std::size_t len,
                                      PacketHeader* out);

PacketStatus validate_packet(const uint8_t* buf, std::size_t len);

void bs_framer_init(ByteStreamFramer* framer);

void bs_framer_push(ByteStreamFramer* framer,
                    const uint8_t* data,
                    std::size_t len,
                    FrameCallback callback,
                    void* callback_ctx);

} // namespace protocol
} // namespace s2t

#endif // BS_PROTOCOL_H
