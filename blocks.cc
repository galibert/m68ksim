#include "blocks.h"

void reset_input(cstate &s)
{
  if(s.clk) {
    s.s_reset[0] = s.p_reset;
    s.s_reset[2] = s.s_reset[1];
    s.s_halt[0] = s.p_halt;
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

