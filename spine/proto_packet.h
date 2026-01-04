#ifndef PROTO_PACKET_H
#define PROTO_PACKET_H

#include <cstddef>
#include <cstdint>

namespace proto {

/**
 * @brief Packet validation result codes.
 */
enum class PacketStatus {
    OK,
    ERR_BUF_NULL,       // Input buffer is null
    ERR_HEADER,         // Header validation failed
    ERR_LENGTH,         // Buffer length does not match header-defined packet size
    ERR_PAYLOAD_CRC     // Payload integrity check failed
};

/**
 * @brief Validate a complete, contiguous packet buffer.
 *
 * This function validates:
 *  - header (via proto_header_parse_and_validate)
 *  - total packet length
 *  - payload CRC32 against trailer
 *
 * No framing, transport I/O, or payload parsing is performed.
 *
 * @param buf     Pointer to the start of the packet buffer.
 * @param buf_len Total size of the buffer in bytes.
 * @return        PacketStatus::OK if the packet is valid.
 */
PacketStatus proto_packet_validate(const uint8_t* buf, std::size_t buf_len);

} // namespace proto

#endif // PROTO_PACKET_H
