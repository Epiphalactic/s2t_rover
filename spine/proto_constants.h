#ifndef PROTO_CONSTANTS_H
#define PROTO_CONSTANTS_H

#include <cstddef>
#include <cstdint>

/*
 * Wire-format constants and layout definitions for Brain <-> Spine
 * Message Contract v0.1.
 *
 * This file defines immutable packet layout only:
 * - constants
 * - sizes
 * - byte offsets
 *
 * It intentionally defines NO behavior:
 * - no CRC algorithms
 * - no parsing or framing logic
 * - no state machine semantics
 *
 * Endianness: little-endian for all multi-byte fields.
 */

namespace proto {

//
// 1) PROTOCOL IDENTIFIERS
//

// Protocol magic (u16). Mnemonic: "S2"
static constexpr uint16_t PROTO_MAGIC = 0x5332u;

// Protocol version (u8/u8) as carried in every packet header.
static constexpr uint8_t PROTO_VERSION_MAJOR = 0u;
static constexpr uint8_t PROTO_VERSION_MINOR = 1u;

//
// 2) PACKET SIZES (BYTES)
//
// Header layout (Section 5.3):
//  magic(u16) + proto_major(u8) + proto_minor(u8) + msg_type(u8) + flags(u8)
//  + src(u8) + dst(u8) + seq(u16) + payload_len(u16) + header_crc16(u16)
//  = 14 bytes
//
static constexpr std::size_t HEADER_SIZE_BYTES = 14u;

// Trailer layout (Section 5.4):
//  payload_crc32(u32) = 4 bytes
//
static constexpr std::size_t TRAILER_SIZE_BYTES = 4u;

static constexpr std::size_t MIN_PACKET_SIZE_BYTES =
    HEADER_SIZE_BYTES + TRAILER_SIZE_BYTES;

/*
 * Maximum payload size (implementation safety cap).
 *
 * NOTE: The contract defines payload_len as u16, but does not specify a maximum
 * payload size for a given MCU implementation. This cap exists to prevent
 * buffer exhaustion on the Spine and MUST be treated as an implementation
 * limit, not a protocol guarantee.
 */
static constexpr std::size_t MAX_PAYLOAD_SIZE_BYTES = 256u;

//
// 3) HEADER BYTE OFFSETS (0-indexed)
//

static constexpr std::size_t OFFSET_MAGIC         = 0u;  // u16
static constexpr std::size_t OFFSET_PROTO_MAJOR   = 2u;  // u8
static constexpr std::size_t OFFSET_PROTO_MINOR   = 3u;  // u8
static constexpr std::size_t OFFSET_MSG_TYPE      = 4u;  // u8
static constexpr std::size_t OFFSET_FLAGS         = 5u;  // u8
static constexpr std::size_t OFFSET_SRC           = 6u;  // u8
static constexpr std::size_t OFFSET_DST           = 7u;  // u8
static constexpr std::size_t OFFSET_SEQ           = 8u;  // u16
static constexpr std::size_t OFFSET_PAYLOAD_LEN   = 10u; // u16
static constexpr std::size_t OFFSET_HEADER_CRC16  = 12u; // u16

//
// 4) TRAILER BYTE OFFSETS (relative to start of trailer)
//

static constexpr std::size_t OFFSET_PAYLOAD_CRC32_IN_TRAILER = 0u; // u32

//
// 5) Layout sanity checks (compile-time)
//

static_assert(HEADER_SIZE_BYTES == 14u, "header size must match contract v0.1");
static_assert(TRAILER_SIZE_BYTES == 4u, "trailer size must match contract v0.1");
static_assert(OFFSET_HEADER_CRC16 + 2u == HEADER_SIZE_BYTES,
              "header_crc16 must be the final header field (u16)");

} // namespace proto

#endif // PROTO_CONSTANTS_H
