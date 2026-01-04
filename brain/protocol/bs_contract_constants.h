#ifndef BS_CONTRACT_CONSTANTS_H
#define BS_CONTRACT_CONSTANTS_H

#include <cstdint>
#include <cstddef>

/**
 * @file bs_contract_constants.h
 * @brief Authoritative Brain-side constants for Brain <-> Spine Contract v0.2.
 *
 * This file mirrors ONLY the frozen, normative wire-format constants
 * defined in BRAIN_SPINE_MESSAGE_CONTRACT.md v0.2.
 *
 * It intentionally contains no behavioral, timing, motion, or fault semantics.
 */

namespace s2t {
namespace protocol {

    // ==========================================================================
    // 1. PROTOCOL IDENTIFIERS & VERSIONING
    // ==========================================================================

    /**
     * Protocol Magic Number ("S2")
     * Canon: Contract v0.2
     */
    static constexpr uint16_t PROTO_MAGIC = 0x5332;

    /**
     * Protocol Version
     */
    static constexpr uint8_t PROTO_VERSION_MAJOR = 0;
    static constexpr uint8_t PROTO_VERSION_MINOR = 2;

    /**
     * Node Identifiers
     */
    static constexpr uint8_t NODE_ID_BRAIN = 0x00;
    static constexpr uint8_t NODE_ID_SPINE = 0x01;

    // ==========================================================================
    // 2. PACKET LAYOUT & SIZES
    // ==========================================================================

    /**
     * Fixed header size (bytes)
     */
    static constexpr std::size_t HEADER_SIZE_BYTES = 14;

    /**
     * Fixed trailer size (bytes)
     */
    static constexpr std::size_t TRAILER_SIZE_BYTES = 4;

    /**
     * Minimum packet size (header + trailer, zero payload)
     */
    static constexpr std::size_t MIN_PACKET_SIZE_BYTES =
        HEADER_SIZE_BYTES + TRAILER_SIZE_BYTES;

    /**
     * Maximum payload size (implementation safety cap)
     * NOTE: This is a transport-safety limit, not a semantic constraint.
     */
    static constexpr std::size_t MAX_PAYLOAD_SIZE_BYTES = 256;

    // ==========================================================================
    // 3. HEADER FIELD OFFSETS (0-indexed)
    // ==========================================================================

    static constexpr std::size_t OFFSET_MAGIC        = 0;   // u16
    static constexpr std::size_t OFFSET_PROTO_MAJOR  = 2;   // u8
    static constexpr std::size_t OFFSET_PROTO_MINOR  = 3;   // u8
    static constexpr std::size_t OFFSET_MSG_TYPE     = 4;   // u8
    static constexpr std::size_t OFFSET_FLAGS        = 5;   // u8
    static constexpr std::size_t OFFSET_SRC          = 6;   // u8
    static constexpr std::size_t OFFSET_DST          = 7;   // u8
    static constexpr std::size_t OFFSET_SEQ          = 8;   // u16
    static constexpr std::size_t OFFSET_PAYLOAD_LEN  = 10;  // u16
    static constexpr std::size_t OFFSET_HEADER_CRC16 = 12;  // u16

    // ==========================================================================
    // 4. TRAILER FIELD OFFSETS
    // ==========================================================================

    static constexpr std::size_t TRAILER_OFFSET_CRC32 = 0; // u32

    // ==========================================================================
    // 5. MESSAGE TYPE IDS (Normative)
    // ==========================================================================

    // Brain -> Spine (0x10 – 0x2F)
    static constexpr uint8_t MSG_ID_B2S_HELLO           = 0x10;
    static constexpr uint8_t MSG_ID_B2S_HEARTBEAT       = 0x11;
    static constexpr uint8_t MSG_ID_B2S_MOTION_ENABLE   = 0x12;
    static constexpr uint8_t MSG_ID_B2S_MOTION_SETPOINT = 0x13;

    // Spine -> Brain (0x80 – 0x9F)
    static constexpr uint8_t MSG_ID_S2B_IDENTITY     = 0x80;
    static constexpr uint8_t MSG_ID_S2B_HEARTBEAT    = 0x81;
    static constexpr uint8_t MSG_ID_S2B_STATE_REPORT = 0x82;
    static constexpr uint8_t MSG_ID_S2B_ACK          = 0x83;
    static constexpr uint8_t MSG_ID_S2B_FAULT        = 0x84;

    // ==========================================================================
    // 6. SPINE STATE ENUM VALUES (Normative)
    // ==========================================================================

    static constexpr uint8_t SPINE_STATE_INIT    = 0x00;
    static constexpr uint8_t SPINE_STATE_SAFE    = 0x01;
    static constexpr uint8_t SPINE_STATE_ENABLED = 0x02;
    static constexpr uint8_t SPINE_STATE_FAULT   = 0x03;

    // ==========================================================================
    // 7. STATIC CONTRACT CHECKS
    // ==========================================================================

    static_assert(HEADER_SIZE_BYTES == 14,
                  "Contract violation: header size mismatch");
    static_assert(TRAILER_SIZE_BYTES == 4,
                  "Contract violation: trailer size mismatch");

} // namespace protocol
} // namespace s2t

#endif // BS_CONTRACT_CONSTANTS_H
