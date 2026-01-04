#include "proto_packet.h"
#include "proto_constants.h"
#include "proto_header.h"
#include "proto_crc.h"

namespace proto {

PacketStatus proto_packet_validate(const uint8_t* buf, std::size_t buf_len) {
    if (buf == nullptr) {
        return PacketStatus::ERR_BUF_NULL;
    }

    if (buf_len < MIN_PACKET_SIZE_BYTES) {
        return PacketStatus::ERR_LENGTH;
    }

    Header header;
    const HeaderStatus header_res = proto_header_parse_and_validate(&header, buf, buf_len);
    if (header_res != HeaderStatus::OK) {
        return PacketStatus::ERR_HEADER;
    }

    const std::size_t expected_len =
        HEADER_SIZE_BYTES + static_cast<std::size_t>(header.payload_len) + TRAILER_SIZE_BYTES;

    if (buf_len != expected_len) {
        return PacketStatus::ERR_LENGTH;
    }

    const uint8_t* payload_ptr = buf + HEADER_SIZE_BYTES;
    const uint8_t* trailer_ptr = payload_ptr + header.payload_len;

    const uint32_t received_crc32 =
        static_cast<uint32_t>(trailer_ptr[0]) |
        (static_cast<uint32_t>(trailer_ptr[1]) << 8) |
        (static_cast<uint32_t>(trailer_ptr[2]) << 16) |
        (static_cast<uint32_t>(trailer_ptr[3]) << 24);

    const uint32_t computed_crc32 =
        (header.payload_len == 0) ? 0u : proto_crc32_iso_hdlc(payload_ptr, header.payload_len);

    if (computed_crc32 != received_crc32) {
        return PacketStatus::ERR_PAYLOAD_CRC;
    }

    return PacketStatus::OK;
}

} // namespace proto
