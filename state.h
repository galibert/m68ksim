#ifndef STATE_H
#define STATE_H

#include <cstdint>
#include <stdio.h>

using u8 = std::uint8_t;
using u16 = std::uint16_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;

struct cstate {
  bool first;

  u64 ctime;
  int svtime;

  bool clk, iclk;

  bool p_reset, p_halt, p_e;

  bool reseti, reseto, halto;

  bool s_reset[3];
  bool s_halt[3];
  bool s_reseti[6];
  bool s_e[8];

  bool s_er, s_ec;
  bool n1361, berro, dtackc, n1035, address_drive, bus_delay;
  bool internal_reset, internal_halt;

  bool eu_r_gate, eu_w_gate, eu_p_gate, romarray_precharge_gate, romarray_clear_gate;
  bool eu_r, eu_w, eu_p, romarray_precharge, romarray_clear;
  bool bus_error_1, linea, linef, bus_error_2, address_error;
  bool aob_active, priviledge_violation, illegal_instruction, interrupt_bus_cycle, trace;
  bool excp_1, excp_2, excp_3;

  bool n148, n1569, n2703, n2735, n2772, n2781, n1932, n2079, n2172, n2350, n1852, n2493;
  bool n8162, n2553, n2648, n2780, n9266, n9255, n9202, n6448, n6449, n6447;
  bool n1926, n1997, n5500, n9179;

  bool ma0_enable, ma1_enable, ma2_enable, ma3_enable;
  bool madr_alu_commit, madr_rom_commit, flow_control_enable;
  bool cc2, cc3;
  u32 r_micro, r_nano1, r_nano2, r_nano3;
  u32 l_micro, l_nano1, l_nano2, l_nano3;
  u16 marom, madr, ma0, ma1, ma1l, ma2, ma3, ma123;
  u16 excpla;
  u8 excfc;
  bool euc_hd_sense_amp_keep, euc_ha_sense_amp_keep;
  bool eu_ld_sense_amp_keep, eu_hd_sense_amp_keep, eu_ha_sense_amp_keep;

  bool eu_hl_a_connect, eu_hl_d_connect, eu_ld_a_connect, eu_ld_d_connect;

  bool eu_r0h_abc, eu_r1h_abc, eu_r2h_abc, eu_r3h_abc, eu_r4h_abc, eu_r5h_abc, eu_r6h_abc, eu_r7h_abc, eu_r8h_abc, eu_r9h_abc;
  bool eu_r10h_abc, eu_r11h_abc, eu_r12h_abc, eu_r13h_abc, eu_r14h_abc, eu_r15h_abc, eu_r16h_abc, eu_r17h_abc, eu_r18h_abc, eu_pch_abc;
  bool eu_r0h_dbc, eu_r1h_dbc, eu_r2h_dbc, eu_r3h_dbc, eu_r4h_dbc, eu_r5h_dbc, eu_r6h_dbc, eu_r7h_dbc, eu_r8h_dbc, eu_r9h_dbc;
  bool eu_r10h_dbc, eu_r11h_dbc, eu_r12h_dbc, eu_r13h_dbc, eu_r14h_dbc, eu_r15h_dbc, eu_r16h_dbc, eu_r17h_dbc, eu_r18h_dbc, eu_pch_dbc;

  bool eu_aluh_ab_in, eu_aluh_cst_val, eu_auh_aluh_w, eu_auh_a_w, eu_auh_d_w;
  bool eu_pch_auh_w, eu_pch_d_w, eu_pch_a_w, eu_aobh_auh_w, eu_aobh_a_w, eu_aobh_d_w, eu_aobh_r;

  bool eu_r0l_abc, eu_r1l_abc, eu_r2l_abc, eu_r3l_abc, eu_r4l_abc, eu_r5l_abc, eu_r6l_abc, eu_r7l_abc, eu_r8l_abc, eu_r9l_abc, eu_pcl_abc;
  bool eu_r0l_dbc, eu_r1l_dbc, eu_r2l_dbc, eu_r3l_dbc, eu_r4l_dbc, eu_r5l_dbc, eu_r6l_dbc, eu_r7l_dbc, eu_r8l_dbc, eu_r9l_dbc, eu_pcl_dbc;


  bool eu_r0d_abc, eu_r1d_abc, eu_r2d_abc, eu_r3d_abc, eu_r4d_abc, eu_r5d_abc, eu_r6d_abc, eu_r7d_abc, eu_r8d_abc;
  bool eu_r0d_dbc, eu_r1d_dbc, eu_r2d_dbc, eu_r3d_dbc, eu_r4d_dbc, eu_r5d_dbc, eu_r6d_dbc, eu_r7d_dbc, eu_r8d_dbc;

  bool eu_alul_ab_in, eu_alul_bit_0, eu_alul_bit_1, eu_alul_bit_2p, eu_alul_add1;
  bool eu_mvm_step;

  bool n3225, n5283;

  bool euc_auh_aluh_w;
  bool euc_ibuf_rw, euc_ibuf_d, euc_ibuf_a, euc_ibuf_to_ib, euc_ib_to_ibuf;

  u16 eu_ah, eu_dh;
  u16 eu_r0h, eu_r1h, eu_r2h, eu_r3h, eu_r4h, eu_r5h, eu_r6h, eu_r7h, eu_r8h, eu_r9h;
  u16 eu_r10h, eu_r11h, eu_r12h, eu_r13h, eu_r14h, eu_r15h, eu_r16h, eu_r17h, eu_r18h;
  u16 eu_auh, eu_pch, eu_aluh, eu_aobh;

  u16 eu_al, eu_dl;
  u16 eu_r0l, eu_r1l, eu_r2l, eu_r3l, eu_r4l, eu_r5l, eu_r6l, eu_r7l, eu_r8l, eu_r9l;
  u16 eu_aul, eu_pcl, eu_alul, eu_aobl;

  u16 eu_ad, eu_dd;
  u16 eu_r0d, eu_r1d, eu_r2d, eu_r3d, eu_r4d, eu_r5d, eu_r6d, eu_r7d, eu_r8d;

  u16 ird, ir, ib, ibuf;

  u8 disp;
  bool disp2, trace_srt_w, trace_clear_w, ipl_sr_w, srt_clear_w, eu_ib_sr_r, disp13, disp14, disp15, disp16, ib_ib1_w, ib1_status_w;
};

static inline int ln(const cstate &s, int bit)
{
  int res;
  if(bit >= 64)
    res = (s.l_nano1 >> (bit - 64)) & 1;
  else if(bit >= 32)
    res = (s.l_nano2 >> (bit - 32)) & 1;
  else
    res = (s.l_nano3 >> bit) & 1;
  return res;
}

template<typename... bitlist> static inline int ln(const cstate &s, int bit, bitlist... bits)
{
  return (ln(s, bit) << sizeof...(bits)) | ln(s, bits...);
}


#endif
