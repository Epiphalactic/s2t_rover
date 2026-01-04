/**
 * @file bs_header.cpp
 * @brief Brain-side header parsing and validation for Brain <-> Spine protocol v0.2
 *
 * Implements deterministic parsing/validation of the fixed header.
 * No framing, no payload CRC32, no I/O, no timing.
 */

#include <cstdint>
#include <cstddef>

#include "bs_contract_constants.h"

namespace s2t {
namespace protocol {

// Forward declaration (implemented in bs_crc.cpp)
uint16_t compute_header_crc16(const uint8_t* data, std::size_t len);

/**
 * Parsed header fields (host-side representation).
 * NOTE: This is NOT a wire struct; fields are explicitly decoded from bytes.
 */
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

// Explicit little-endian reads (wire format).
static inline uint16_t read_u16_le(const uint8_t* p)
{
    return static_cast<uint16_t>(static_cast<uint16_t>(p[0]) |
                                 (static_cast<uint16_t>(p[1]) << 8));
}

/**
 * Parse and validate the fixed packet header.
 *
 * Validation steps:
 * 1) Args / length
 * 2) Decode fields (explicit LE for u16 fields)
 * 3) Magic check
 * 4) Version check (exact match)
 * 5) Payload length safety cap
 * 6) Header CRC16 check (CRC field treated as zero during computation)
 */
HeaderStatus parse_and_validate_header(const uint8_t* buf,
                                      std::size_t len,
                                      PacketHeader* out)
{
    if (!out) {
        return HeaderStatus::ERR_INVALID_ARGS;
    }
    if (!buf) {
        return HeaderStatus::ERR_INVALID_ARGS;
    }
    if (len < HEADER_SIZE_BYTES) {
        return HeaderStatus::ERR_BUFFER_TOO_SMALL;
    }

    out->magic        = read_u16_le(&buf[OFFSET_MAGIC]);
    out->proto_major  = buf[OFFSET_PROTO_MAJOR];
    out->proto_minor  = buf[OFFSET_PROTO_MINOR];
    out->msg_type     = buf[OFFSET_MSG_TYPE];
    out->flags        = buf[OFFSET_FLAGS];
    out->src          = buf[OFFSET_SRC];
    out->dst          = buf[OFFSET_DST];
    out->seq          = read_u16_le(&buf[OFFSET_SEQ]);
    out->payload_len  = read_u16_le(&buf[OFFSET_PAYLOAD_LEN]);
    out->header_crc16 = read_u16_le(&buf[OFFSET_HEADER_CRC16]);

    if (out->magic != PROTO_MAGIC) {
        return HeaderStatus::ERR_MAGIC_MISMATCH;
    }

    // Version handling: exact match unless canon explicitly allows ranges.
    if (out->proto_major != PROTO_VERSION_MAJOR ||
        out->proto_minor != PROTO_VERSION_MINOR) {
        return HeaderStatus::ERR_VERSION_MISMATCH;
    }

    if (out->payload_len > MAX_PAYLOAD_SIZE_BYTES) {
        return HeaderStatus::ERR_PAYLOAD_TOO_LARGE;
    }

    uint8_t scratch[HEADER_SIZE_BYTES];
    for (std::size_t i = 0; i < HEADER_SIZE_BYTES; ++i) {
        scratch[i] = buf[i];
    }
    scratch[OFFSET_HEADER_CRC16]     = 0;
    scratch[OFFSET_HEADER_CRC16 + 1] = 0;

    const uint16_t computed = compute_header_crc16(scratch, HEADER_SIZE_BYTES);
    if (computed != out->header_crc16) {
        return HeaderStatus::ERR_CRC_MISMATCH;
    }

    return HeaderStatus::OK;
}

} // namespace protocol
} // namespace s2t
