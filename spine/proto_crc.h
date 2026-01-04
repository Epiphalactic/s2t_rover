#ifndef PROTO_CRC_H
#define PROTO_CRC_H

#include <cstddef>
#include <cstdint>

namespace proto {

/*
 * CRC-16/CCITT-FALSE (header_crc16)
 * width=16 poly=0x1021 init=0xFFFF refin=false refout=false xorout=0x0000
 *
 * NOTE: data may be nullptr only if len==0.
 */
uint16_t proto_crc16_ccitt_false(const uint8_t* data, std::size_t len);

/*
 * CRC-32/ISO-HDLC (payload_crc32)
 * width=32 poly=0x04C11DB7 init=0xFFFFFFFF refin=true refout=true xorout=0xFFFFFFFF
 *
 * Contract rule: if len==0, return 0.
 * NOTE: data may be nullptr only if len==0.
 */
uint32_t proto_crc32_iso_hdlc(const uint8_t* data, std::size_t len);

} // namespace proto

#endif // PROTO_CRC_H
