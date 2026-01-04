#include <cstdint>
#include <cstddef>

#include "bs_protocol.h"

namespace s2t {
namespace protocol {

struct ProtocolTestStats {
    uint32_t frames_extracted = 0;
    uint32_t packets_valid    = 0;
    uint32_t packets_invalid  = 0;
    uint32_t sync_losses      = 0;
};

struct ToolContext {
    ProtocolTestStats* stats = nullptr;
};

static void tool_frame_handler(const uint8_t* frame_buf,
                               std::size_t frame_len,
                               void* ctx)
{
    ToolContext* tc = static_cast<ToolContext*>(ctx);
    if (!tc || !tc->stats) {
        return;
    }

    tc->stats->frames_extracted++;

    const PacketStatus st = validate_packet(frame_buf, frame_len);
    if (st == PacketStatus::OK) {
        tc->stats->packets_valid++;
    } else {
        tc->stats->packets_invalid++;
    }
}

ProtocolTestStats run_protocol_harness(const uint8_t* input_data,
                                       std::size_t input_len)
{
    ProtocolTestStats stats;
    ToolContext ctx{&stats};

    ByteStreamFramer framer;
    bs_framer_init(&framer);

    if (input_data && input_len > 0) {
        bs_framer_push(&framer, input_data, input_len,
                       tool_frame_handler, &ctx);
    }

    stats.sync_losses = framer.sync_loss_count;
    return stats;
}

} // namespace protocol
} // namespace s2t
