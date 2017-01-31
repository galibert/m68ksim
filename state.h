#ifndef STATE_H
#define STATE_H

#include <cstdint>

using u8 = std::uint8_t;
using u16 = std::uint16_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;

struct cstate {
  bool first;

  u64 ctime;

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
  bool aob_active, priviledge_violation, illegal_instruction, interrupt_bus_cycle;

  bool n148, n1569, n2703, n2735, n2772, n2781, n1932, n2079, n2172, n2350, n1852, n2493;
  bool n8162, n2553, n2082, n2648, n2780, n9266, n9255, n9202, n6448, n6449, n6447;
  bool n1926, n1997, n5500, n461, n7809, n9179, n1627;

  bool ma0_enable, ma1_enable, ma2_enable, ma3_enable;
  bool madr_alu_commit, madr_rom_commit, flow_control_enable;
  bool cc2, cc3;
  u32 r_micro, r_nano1, r_nano2, r_nano3;
  u32 l_micro, l_nano1, l_nano2, l_nano3;
  u16 marom, madr, ma0, ma1, ma1l, ma2, ma3, ma123;
  u16 excpla;
  u8 excfc;
};

#endif
