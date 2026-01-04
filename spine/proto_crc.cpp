#include "proto_crc.h"

namespace proto {

uint16_t proto_crc16_ccitt_false(const uint8_t* data, std::size_t len) {
    if (len == 0) {
        return 0xFFFFu;
    }
    if (data == nullptr) {
        return 0;
    }

    uint16_t crc = 0xFFFFu;

    for (std::size_t i = 0; i < len; ++i) {
        crc ^= (static_cast<uint16_t>(data[i]) << 8);

        for (int bit = 0; bit < 8; ++bit) {
            if ((crc & 0x8000u) != 0u) {
                crc = static_cast<uint16_t>((crc << 1) ^ 0x1021u);
            } else {
                crc = static_cast<uint16_t>(crc << 1);
            }
        }
    }

    return crc;
}

uint32_t proto_crc32_iso_hdlc(const uint8_t* data, std::size_t len) {
    if (len == 0) {
        return 0;
    }
    if (data == nullptr) {
        return 0;
    }

    uint32_t crc = 0xFFFFFFFFu;
    constexpr uint32_t REVERSED_POLY = 0xEDB88320u;

    for (std::size_t i = 0; i < len; ++i) {
        crc ^= static_cast<uint32_t>(data[i]);

        for (int bit = 0; bit < 8; ++bit) {
            if ((crc & 1u) != 0u) {
                crc = (crc >> 1) ^ REVERSED_POLY;
            } else {
                crc >>= 1;
            }
        }
    }

    return crc ^ 0xFFFFFFFFu;
}

} // namespace proto
