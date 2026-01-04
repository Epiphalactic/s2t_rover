/**
 * @file bs_crc.cpp
 * @brief Brain-side CRC implementations for Brain <-> Spine protocol v0.2
 *
 * Implements CRC algorithms exactly matching Spine-side behavior as defined
 * in BRAIN_SPINE_MESSAGE_CONTRACT.md v0.2.
 *
 * This file contains no parsing, framing, I/O, or timing logic.
 */

#include <cstdint>
#include <cstddef>

#include "bs_contract_constants.h"

namespace s2t {
namespace protocol {

/**
 * Compute CRC-16/CCITT-FALSE over the packet header.
 *
 * Parameters (normative):
 * - Width:  16
 * - Poly:   0x1021
 * - Init:   0xFFFF
 * - RefIn:  false
 * - RefOut: false
 * - XorOut: 0x0000
 */
uint16_t compute_header_crc16(const uint8_t* data, std::size_t len)
{
    uint16_t crc = 0xFFFF;

    if (!data && len > 0) {
        return 0;
    }

    for (std::size_t i = 0; i < len; ++i) {
        crc ^= static_cast<uint16_t>(data[i]) << 8;

        for (int bit = 0; bit < 8; ++bit) {
            if (crc & 0x8000) {
                crc = (crc << 1) ^ 0x1021;
            } else {
                crc <<= 1;
            }
        }
    }

    return crc;
}

/**
 * Compute CRC-32/ISO-HDLC over the packet payload.
 *
 * Parameters (normative):
 * - Width:  32
 * - Poly:   0x04C11DB7
 * - Init:   0xFFFFFFFF
 * - RefIn:  true
 * - RefOut: true
 * - XorOut: 0xFFFFFFFF
 *
 * Contract rule:
 * - If payload length is zero, CRC value SHALL be 0.
 */
uint32_t compute_payload_crc32(const uint8_t* data, std::size_t len)
{
    if (len == 0) {
        return 0;
    }

    if (!data) {
        return 0;
    }

    uint32_t crc = 0xFFFFFFFF;
    constexpr uint32_t POLY_REVERSED = 0xEDB88320;

    for (std::size_t i = 0; i < len; ++i) {
        crc ^= static_cast<uint32_t>(data[i]);

        for (int bit = 0; bit < 8; ++bit) {
            if (crc & 1) {
                crc = (crc >> 1) ^ POLY_REVERSED;
            } else {
                crc >>= 1;
            }
        }
    }

    return crc ^ 0xFFFFFFFF;
}

} // namespace protocol
} // namespace s2t
