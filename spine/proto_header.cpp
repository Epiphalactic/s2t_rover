#include "proto_header.h"
#include "proto_constants.h"
#include "proto_crc.h"

namespace proto {

HeaderStatus proto_header_parse_and_validate(
    Header* out,
    const uint8_t* buf,
    std::size_t buf_len)
{
    if (out == nullptr) {
        return HeaderStatus::ERR_OUT_NULL;
    }

    // buf may be nullptr only if buf_len == 0.
    if (buf == nullptr) {
        return (buf_len == 0) ? HeaderStatus::ERR_SHORT : HeaderStatus::ERR_BUF_NULL;
    }

    if (buf_len < HEADER_SIZE_BYTES) {
        return HeaderStatus::ERR_SHORT;
    }

    out->magic = static_cast<uint16_t>(
        static_cast<uint16_t>(buf[OFFSET_MAGIC]) |
        (static_cast<uint16_t>(buf[OFFSET_MAGIC + 1]) << 8));

    out->proto_major = buf[OFFSET_PROTO_MAJOR];
    out->proto_minor = buf[OFFSET_PROTO_MINOR];

    out->msg_type = buf[OFFSET_MSG_TYPE];
    out->flags    = buf[OFFSET_FLAGS];

    out->src = buf[OFFSET_SRC];
    out->dst = buf[OFFSET_DST];

    out->seq = static_cast<uint16_t>(
        static_cast<uint16_t>(buf[OFFSET_SEQ]) |
        (static_cast<uint16_t>(buf[OFFSET_SEQ + 1]) << 8));

    out->payload_len = static_cast<uint16_t>(
        static_cast<uint16_t>(buf[OFFSET_PAYLOAD_LEN]) |
        (static_cast<uint16_t>(buf[OFFSET_PAYLOAD_LEN + 1]) << 8));

    out->header_crc16 = static_cast<uint16_t>(
        static_cast<uint16_t>(buf[OFFSET_HEADER_CRC16]) |
        (static_cast<uint16_t>(buf[OFFSET_HEADER_CRC16 + 1]) << 8));

    if (out->magic != PROTO_MAGIC) {
        return HeaderStatus::ERR_MAGIC;
    }

    if (out->proto_major != PROTO_VERSION_MAJOR) {
        return HeaderStatus::ERR_VERSION;
    }
    if (out->proto_minor > PROTO_VERSION_MINOR) {
        return HeaderStatus::ERR_VERSION;
    }

    if (out->payload_len > MAX_PAYLOAD_SIZE_BYTES) {
        return HeaderStatus::ERR_PAYLOAD_LEN;
    }

    uint8_t scratch[HEADER_SIZE_BYTES];
    for (std::size_t i = 0; i < HEADER_SIZE_BYTES; ++i) {
        scratch[i] = buf[i];
    }

    scratch[OFFSET_HEADER_CRC16]     = 0;
    scratch[OFFSET_HEADER_CRC16 + 1] = 0;

    const uint16_t computed_crc = proto_crc16_ccitt_false(scratch, HEADER_SIZE_BYTES);
    if (computed_crc != out->header_crc16) {
        return HeaderStatus::ERR_CRC16;
    }

    return HeaderStatus::OK;
}

} // namespace proto
