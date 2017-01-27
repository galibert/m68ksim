#include "blocks.h"
#include <stdio.h>

void reset_input(cstate &s)
{
  if(s.clk) {
    s.s_reset[0] = !s.p_reset;
    s.s_reset[2] = s.s_reset[1];
    s.s_halt[0] = !s.p_halt;
    s.s_halt[2] = s.s_halt[1];
    s.s_reseti[1] = !s.s_reseti[0];
    s.s_reseti[3] = !s.s_reseti[2];
    s.s_reseti[5] = !s.s_reseti[4];
  }

  if(s.iclk) {
    s.s_reset[1] = s.s_reset[0];
    s.s_halt[1] = s.s_halt[0];
    s.s_reseti[0] = !s.reseti;
    s.s_reseti[2] = !s.s_reseti[1];
    s.s_reseti[4] = !s.s_reseti[3];

    s.internal_reset = s.s_reset[2] && (s.s_halt[2] || (s.s_reseti[5] && s.reseti));
  }

  s.internal_halt = !(s.s_halt[2] && s.bus_delay);
}

void eclk(cstate &s)
{
  if(s.clk) {
    s.s_e[0] = !(!s.s_e[5] || s.s_e[7]) || !(s.s_e[5] || !s.s_e[7]);
    s.s_e[2] = !s.s_e[1];
    s.s_e[4] = !s.s_e[3];
    s.s_e[6] = !s.s_e[5];
    s.s_er   =
      !(!s.s_e[1] || s.s_e[3] || s.s_e[5] || !s.s_e[7]) ||
      !(!s.s_e[1] || !s.s_e[3] || !s.s_e[5] || !s.s_e[7]);

    if(!(!s.s_e[1] || !s.s_e[3] || !s.s_e[5] || s.s_e[7]))
      s.s_ec = true;
    if(!(!s.s_e[1] || s.s_e[3] || s.s_e[5] || !s.s_e[7]))
      s.s_ec = false;
  }
  if(s.iclk) {
    if(s.s_er)
      s.s_e[1] = s.s_e[3] = s.s_e[5] = s.s_e[7] = false;
    else {
      s.s_e[1] = !s.s_e[0];
      s.s_e[3] = !s.s_e[2];
      s.s_e[5] = !s.s_e[4];
      s.s_e[7] = !s.s_e[6];
    }
    s.p_e = !s.s_ec;
  }
}

void eu_timing(cstate &s)
{
  bool n1760 = s.n148 && s.bus_error_1 && s.n1569 && s.internal_halt;
  bool n1704 = !(s.internal_reset || s.n1361 || n1760);
  if(s.iclk)
    s.n2703 = n1704;
  bool changed;
  do {
    changed = false;

    bool n2388 = !(s.clk || s.berro || s.n1361 || s.n2735 || s.n2772 || s.n2781);

    if(0)
    printf("%d = %d %d %d %d %d %d n1704=%d (%d %d %d)\n", n2388,
	   s.clk, s.berro, s.n1361, s.n2735, s.n2772, s.n2781,
	   n1704, s.internal_reset, s.n1361, n1760);

    if(s.clk)
      s.n1852 = s.romarray_precharge_gate;
    if(s.iclk)
      s.n1932 = s.n1852 = s.n1852 && !s.internal_reset;
    if(s.clk)
      s.n1932 = s.n1932 && !s.internal_reset;
    if(!s.n1932) {
      if(s.eu_w_gate) {
	s.eu_w_gate = false;
	changed = true;
      }
    } else if(!s.internal_reset) {
      if(!s.eu_w_gate) {
	s.eu_w_gate = true;
	changed = true;
      }
    }


    if(s.iclk)
      s.n2079 = s.eu_r_gate;
    if(s.clk)
      s.n2172 = s.n2079 = s.n2079 && !s.internal_reset;
    if(s.iclk)
      s.n2172 = s.n2172 && !s.internal_reset;
    if(!s.n2172) {
      if(s.romarray_precharge_gate) {
	s.romarray_precharge_gate = false;
	changed = true;
      }
      if(!s.eu_p_gate) {
	s.eu_p_gate = true;
	changed = true;
      }
    } else if(!s.internal_reset) {
      if(!s.romarray_precharge_gate) {
	s.romarray_precharge_gate = true;
	changed = true;
      }
      if(s.eu_p_gate) {
	s.eu_p_gate = false;
	changed = true;
      }
    }

    if(s.clk)
      s.n2350 = false;
    if(s.iclk)
      s.n2493 = s.n2350 = (s.n2350 || n2388) && !s.internal_reset;
    if(s.clk)
      s.n2493 = s.n2493 && !s.internal_reset;
    if(!(s.n2493 || n2388)) {
      if(s.eu_r_gate) {
	s.eu_r_gate = false;
	changed = true;
      }
    } else if(!s.internal_reset) {
      if(!s.eu_r_gate) {
	s.eu_r_gate = true;
	changed = true;
      }
    }

    bool rcg = !(s.eu_w_gate || s.eu_r_gate || s.n2703);
    if(rcg != s.romarray_clear_gate) {
      s.romarray_clear_gate = rcg;
      changed = true;
    }

    if(s.clk) {
      s.n2781 = s.eu_r_gate;
      s.n2772 = s.romarray_clear_gate;
    }
  } while(changed);

  
}
