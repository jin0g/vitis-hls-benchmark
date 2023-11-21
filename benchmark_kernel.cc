#include <ap_int.h>
#include <hls_stream.h>
#include <ap_axi_sdata.h>

struct Instruction {
    ap_uint<1> loop_start;
    ap_uint<1> loop_end;
    ap_uint<16> count;
    ap_int<32> weight;
    ap_uint<1> output;
    ap_uint<1> last;
};

void kernel(
        hls::stream<Instruction> &instructions,
        hls::stream<ap_axis<32,0,0,0>> &out
) {
#pragma HLS pipeline II=1
#pragma HLS interface ap_ctrl_none port=return
#pragma HLS interface axis port=instructions
#pragma HLS interface axis port=out
#pragma HLS aggregate variable=instructions

    static Instruction inst_cache[8];
#pragma HLS aggregate variable=inst_cache
    static ap_uint<4> pc = 0;
    static ap_uint<4> pc_next_fetch = 0;
    static ap_uint<4> pc_checkpoint = -1;

    bool is_cache_miss = pc == pc_next_fetch;

    Instruction inst = inst_cache[pc % 8];

    bool is_pre_fetch = (pc_next_fetch % 8) != (pc_checkpoint % 8);
    if (is_pre_fetch) {
        Instruction inst_fetch;
        if (instructions.read_nb(inst_fetch)) {
            inst_cache[pc_next_fetch % 8] = inst_fetch;
            pc_next_fetch = (pc_next_fetch + 1) % (2 * 8);
        }
    }

    if (is_cache_miss) return;
    pc = (pc + 1) % (2 * 8);

    static ap_uint<16> loop_count = 0;
    if (loop_count == 0) {
        pc_checkpoint = pc;
    }
    if (inst.loop_start) {
        pc_checkpoint = pc;
        loop_count = inst.count;
        return;
    }
    if (inst.loop_end && loop_count != 0) {
        pc = pc_checkpoint;
        loop_count--;
    }

    static ap_int<32> acc = 0;

    int tmp = 1;
    for (int i=0; i<1000; i++) {
        tmp = tmp * inst.weight;
    }
    acc += tmp;

    ap_axis<32,0,0,0> t;
    t.data = acc;
    t.keep = -1;
    t.strb = -1;
    t.last = inst.last;
    if (inst.output) out.write(t);
}
