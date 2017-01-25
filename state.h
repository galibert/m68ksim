#ifndef STATE_H
#define STATE_H

struct cstate {
  bool first;

  unsigned long long ctime;

  bool clk, iclk;

  bool p_reset, p_halt, p_e;

  bool reseti, reseto, halto;

  bool s_reset[3];
  bool s_halt[3];
  bool s_reseti[6];
  bool s_e[8];

  bool s_er, s_ec;
  bool n1361, berro, dtackc, n1035, address_drive;
  bool internal_reset;

  bool eu_r_gate, eu_w_gate, eu_p_gate, romarray_precharge_gate, romarray_clear_gate;
  bool eu_r, eu_w, eu_p, romarray_precharge, romarray_clear;
};

#endif
