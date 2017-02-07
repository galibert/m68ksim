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

void ma(cstate &s)
{
  if(s.address_drive && s.iclk)
    s.bus_error_1 = s.interrupt_bus_cycle && s.berro;

  if(s.eu_p)
    s.n1926 = s.aob_active;

  if(s.clk)
    s.n1997 = s.n1926 && !s.internal_reset;

  if(s.iclk)
    s.excp_2 = !s.n1997;

  bool n2300 = !(s.address_error || s.bus_error_1);
  bool n2368 = !n2300;

  if(s.eu_p) {
    s.n6447 = s.n5500;
    bool n6265 = (s.l_micro & 0x12) == 0x10;
    s.n6448 = (s.l_micro & 1) && !n6265;
    s.n6449 = n6265;
  }

  bool n6518 = s.n6447 || s.n6448 ? s.eu_w : false;
  bool n6656 = s.n6449 ? s.eu_w : false;

  if(n6518)
    s.excpla = (s.excpla & 0x01f)
      | (s.excp_1               ? 0x400 : 0)
      | (s.trace                ? 0x200 : 0)
      | (s.priviledge_violation ? 0x100 : 0)
      | (s.illegal_instruction  ? 0x080 : 0)
      | (s.linea                ? 0x040 : 0)
      | (s.linef                ? 0x020 : 0);

  if(n6656)
    s.excpla = (s.excpla & 0x7e0)
      | (s.excp_2               ? 0x010 : 0)
      | (s.bus_error_1          ? 0x008 : 0)
      | (s.excp_3               ? 0x004 : 0)
      | (s.bus_error_2          ? 0x002 : 0)
      | (s.address_error        ? 0x001 : 0);

  u16 excv = 0;
  if((s.excpla & 0x010) == 0x010) excv |= 0x400;
  if((s.excpla & 0x21b) == 0x000) excv |= 0x200;
  if((s.excpla & 0x21f) == 0x002) excv |= 0x100;
  if((s.excpla & 0x65f) == 0x446) excv |= 0x080;
  if((s.excpla & 0x67f) == 0x426) excv |= 0x040;
  if((s.excpla & 0x6ff) == 0x406) excv |= 0x020;
  if((s.excpla & 0x7ff) == 0x586) excv |= 0x010;
  if((s.excpla & 0x61f) == 0x006) excv |= 0x008;
  if((s.excpla & 0x219) == 0x200) excv |= 0x004;
  if((s.excpla & 0x011) == 0x001) excv |= 0x002;
  if((s.excpla & 0x019) == 0x008) excv |= 0x001;

  s.ma0 = 0x1c0 | (s.excpla & 0x0fc ? 0 : 0x23b) | (s.excpla & 0x0f4 ? 0 : 0x004);

  bool ma01_select = s.excpla & 0x0fc;
  s.excfc =
    (s.excpla & 0x0f0 ? 0x1 : 0) |
    (s.excpla & 0x37c ? 0x2 : 0) |
    (s.excpla & 0x599 ? 0x4 : 0) |
    (s.excpla & 0x6aa ? 0x8 : 0);

  s.n9266 = s.eu_p ? true : n6518 ? false : s.n9266;
  s.n9255 = n6518 ? true : s.eu_p ? false : s.n9255;

  if(!s.eu_p) {
    s.n9202 = s.n9266;
    s.n9179 = s.n9255 && !s.n9202;
  }

  if(s.n9202)
    s.n8162 = false;
  else if(s.n9179)
    s.n8162 = s.eu_p;

  if(s.n8162)
    s.ma1l = s.ma1;

  bool n2333 = !(s.excpla & 0x019);
  bool n2314 = !(n2300 || n2333);

  if(s.romarray_clear) {
    s.n2553 = s.excp_2;
    s.n2648 = n2368 && !s.n2553;
    s.n2780 = n2314 && !s.n2553;
  } else if(s.eu_w)
    s.n2553 = s.n2648 = s.n2780 = false;

  bool n3024 = !(s.n2553 || s.n2648 || s.n2780);
  bool n3175 = !n3024;

  s.ma3_enable     = (s.l_micro & 0xe) == 0xc;
  bool ma01_enable = (s.l_micro & 0xe) == 0x4;
  s.ma2_enable     = (s.l_micro & 0xe) == 0x8;
  bool n5540       = (s.l_micro & 0xe) == 0x0;
  s.flow_control_enable = s.l_micro & 0x2;

  s.madr_alu_commit = ma01_enable || s.ma2_enable || s.ma3_enable;

  s.madr_rom_commit = n5540 || s.flow_control_enable;
  s.ma0_enable = ma01_select && ma01_enable;
  s.ma1_enable = (!ma01_select) && ma01_enable;

  // 9876543210
  // 0123456789

  // 0 200 *
  // 1 100 *
  // 2 080 *
  // 3 040 *
  // 4 020 *
  // 5 010 *
  // 6 008 *
  // 7 004 *
  // 8 002 *
  // 9 001 *

  if(s.ma0_enable)
    s.ma123 = s.ma0;

  if(s.ma1_enable)
    s.ma123 = s.ma1l;

  if(s.ma2_enable)
    s.ma123 = s.ma2;

  if(s.ma3_enable)
    s.ma123 = s.ma3;

  if(s.madr_alu_commit)
    s.madr = s.ma123 ^ 0x3ff;

  if(s.madr_rom_commit)
    s.madr = (s.madr & 0x0c0)
      | (s.l_micro & 0x04000 ? 0x200 : 0)
      | (s.l_micro & 0x02000 ? 0x100 : 0)
      | (s.l_micro & 0x01000 ? 0x002 : 0)
      | (s.l_micro & 0x00800 ? 0x001 : 0)
      | (s.l_micro & 0x00400 ? 0x020 : 0)
      | (s.l_micro & 0x00200 ? 0x010 : 0)
      | (s.l_micro & 0x00100 ? 0x008 : 0)
      | (s.l_micro & 0x00080 ? 0x004 : 0);

  if(s.flow_control_enable)
    s.madr = (s.madr & 0x33f)
      | (s.cc2 ? 0 : 0x080)
      | (s.cc3 ? 0 : 0x040);

  if(n5540)
    s.madr = (s.madr & 0x33f)
      | (s.l_micro & 0x00040 ? 0 : 0x080)
      | (s.l_micro & 0x00020 ? 0 : 0x040);

  if(s.eu_r)
    s.marom = (s.marom & 0x0c0)
      | (n3175 ? 0 : ~s.madr & 0x33c)
      | (s.n2553 ? 0 : n3024 ? ~s.madr & 0x001 : 0x001)
      | (s.n2780 ? 0 : n3024 ? ~s.madr & 0x002 : 0x002);

  if(s.romarray_precharge)
    s.marom = (s.marom & 0x33f)
      | (n3175 ? 0 : ~s.madr & 0x0c0);
}
