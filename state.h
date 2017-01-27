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
  bool bus_error_1;

  bool n148, n1569, n2703, n2735, n2772, n2781, n1932, n2079, n2172, n2350, n1852, n2493;

  
};

#endif
