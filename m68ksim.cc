#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <list>

#include "blocks.h"
#include "sched.h"

cstate ref;

void init(cstate &s)
{
  memset(&s, 0, sizeof(s));
  ref = s;
  s.first = true;
  s.svtime = -6;
  s.bus_delay = true;
}

void update(cstate &s)
{
  for(;;) {
    std::list<void (*)(cstate &)> f;
    compute_sched(ref, s, f, s.first);
    s.first = false;
    ref = s;
    if(f.empty())
      break;
    for(std::list<void (*)(cstate &)>::const_iterator i = f.begin(); i != f.end(); i++)
      (*i)(s);
  }
}

void show_state(const cstate &s)
{
  printf("%8ld: %4d clk=%d iclk=%d i_reset=%d eu_prw=%c%c%c nano=%x.%08x.%08x ma0=%03x ma1=%03x ma2=%03x ma3=%03x madr=%03x marom=%03x\n",
	 s.ctime, s.svtime, s.clk, s.iclk,
	 s.internal_reset,
	 s.eu_p ? 'p' : '-', s.eu_r ? 'r' : '-', s.eu_w ? 'w' : '-',
	 s.l_nano1^0xf, ~s.l_nano2 ^ 0x82feffc2, ~s.l_nano3 ^ 0x1ffd7d7e,
	 s.ma0, s.ma1, s.ma2, s.ma3, s.madr^0x3ff, s.marom
	 );
  printf("          eu=(%04x %04x %04x %04x %04x %04x) alu=%04x%04x au=%04x%04x pc=%04x%04x aob=%04x%04x\n",
	 s.eu_ah, s.eu_dh, s.eu_al, s.eu_dl, s.eu_ad, s.eu_dd,
	 s.eu_aluh, s.eu_alul, s.eu_auh, s.eu_aul, s.eu_pch, s.eu_pcl, s.eu_aobh, s.eu_aobl);
}

void show_euconfig(const cstate &s)
{
  printf("          -");
  if(!s.euc_hd_sense_amp_keep)
    printf(" dh=sgn(dl)");
  if(!s.euc_ha_sense_amp_keep)
    printf(" ah=sgn(al)");
  if(s.eu_aluh_ab_in)
    printf(" alu=a+d");
  else if(s.eu_alul_bit_2p) {
    int delta = (s.eu_alul_bit_2p ? 0 : -4)+(s.eu_alul_bit_1 ? 0 : 2)+(s.eu_alul_bit_0 ? 0 : 1)+(s.eu_alul_add1 ? 0 : 1);
    if(!delta)
      printf(" alu=d");
    else if(delta > 0)
      printf(" alu=d+%d", delta);
    else
      printf(" alu=d-%d", delta);
  }

  if(s.eu_auh_aluh_w)
    printf(" au=alu");
  if(s.eu_auh_a_w)
    printf(" a=au");
  if(s.eu_auh_d_w)
    printf(" d=au");

  if(s.eu_aobh_auh_w)
    printf(" aob=au");
  if(s.eu_aobh_a_w)
    printf(" aob=a");
  if(s.eu_aobh_d_w)
    printf(" aob=d");

  if(s.eu_pch_auh_w)
    printf(" pch=auh");
  if(s.eu_pch_d_w)
    printf(" pch=dh");
  if(s.eu_pch_a_w)
    printf(" pch=ah");

  if(s.eu_hl_a_connect)
    printf(" ah=al");
  if(s.eu_hl_d_connect)
    printf(" dh=al");
  if(s.eu_ld_a_connect)
    printf(" al=ad");
  if(s.eu_ld_d_connect)
    printf(" dl=dd");

  if(s.trace_srt_w)
    printf(" tr=sr.t");
  if(s.trace_clear_w)
    printf(" tr=0");
  if(s.euc_ibuf_rw && s.euc_ibuf_d)
    printf(" ibuf=d");
  if(s.euc_ibuf_rw && s.euc_ibuf_a)
    printf(" ibuf=a");
  if(!s.euc_ibuf_rw && s.euc_ibuf_d)
    printf(" d=ibuf");
  if(!s.euc_ibuf_rw && s.euc_ibuf_a)
    printf(" a=ibuf");
  if(s.euc_ibuf_to_ib)
    printf(" ib=ibuf");
  if(s.euc_ib_to_ibuf)
    printf(" ibuf=ib");
  if(s.ipl_sr_w)
    printf(" sr.i=iplb");
  if(s.srt_clear_w)
    printf(" sr.t=0");
  if(s.eu_ib_sr_r)
    printf(" ib=sr");
  if(s.ib_ib1_w)
    printf(" ib=ib1");
  if(s.ib1_status_w)
    printf(" ib1=status");
  printf(" || disp=%x", s.disp);

  printf("\n");
  //  printf("  . tri=%d ab_in=%d 2p=%d 1=%d 0=%d +1=%d\n\n",
  //	 ln(s, 51, 50, 49), s.eu_alul_ab_in, s.eu_alul_bit_2p, s.eu_alul_bit_1, s.eu_alul_bit_0, s.eu_alul_add1);
  printf("\n");
}

void step(cstate &s, bool verbose)
{
  s.clk = false;
  s.iclk = false;
  s.eu_r = false;
  s.eu_w = false;
  s.romarray_clear = false;
  update(s);

  s.clk = true;
  s.iclk = false;
  update(s);

  if(s.eu_p_gate)
    s.eu_p = true;
  if(s.romarray_precharge_gate)
    s.romarray_precharge = true;
  update(s);

  if(s.eu_p && s.eu_ld_sense_amp_keep) {
    s.eu_ld_sense_amp_keep = false;
    update(s);
  }

  if(verbose)
    show_state(s);
  if(verbose)
    show_euconfig(s);

  if(s.eu_p)
    s.svtime++;

  s.svtime ++;

  s.clk = false;
  s.iclk = false;
  s.eu_p = false;
  s.romarray_precharge = false;
  update(s);

  s.clk = false;
  s.iclk = true;
  update(s);

  if(s.eu_r_gate)
    s.eu_r = true;
  if(s.eu_w_gate)
    s.eu_w = true;
  if(s.romarray_clear_gate)
    s.romarray_clear = true;
  update(s);

  if(s.eu_r && !s.eu_ld_sense_amp_keep) {
    s.eu_ld_sense_amp_keep = true;
    update(s);
  }

  if(verbose)
    show_state(s);
  if(verbose)
    show_euconfig(s);

  if(s.eu_r)
    s.svtime++;

  s.svtime++;
  s.ctime++;
}

int main()
{
  cstate s;
  init(s);

  s.p_reset = false;
  s.p_halt = false;

  for(int i=0; i<6; i++)
    step(s, false);

  s.p_reset = true;
  s.p_halt = true;

  for(int i=0; i<6; i++)
    step(s, false);

  for(int i=0; i<24; i++)
    step(s, true);

  return 0;
}
