#ifndef PROTO_HEADER_H
#define PROTO_HEADER_H

#include <cstddef>
#include <cstdint>

namespace proto {

struct Header {
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
    OK,
    ERR_OUT_NULL,
    ERR_BUF_NULL,
    ERR_SHORT,
    ERR_MAGIC,
    ERR_VERSION,
    ERR_PAYLOAD_LEN,
    ERR_CRC16,
};

HeaderStatus proto_header_parse_and_validate(
    Header* out,
    const uint8_t* buf,
    std::size_t buf_len);

} // namespace proto

#endif // PROTO_HEADER_H
