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
  printf("%8ld: clk=%d iclk=%d i_reset=%d eu_prw=%c%c%c rpcg=%c%c rmicro=%05x lmicro=%05x rnano=%x.%08x.%08x lnano=%x.%08x.%08x ma0=%03x ma1=%03x ma2=%03x ma3=%03x madr=%03x marom=%03x 2553=%d 2780=%d\n",
	 s.ctime, s.clk, s.iclk,
	 s.internal_reset,
	 s.eu_p ? 'p' : '-', s.eu_r ? 'r' : '-', s.eu_w ? 'w' : '-',
	 s.romarray_precharge ? 'p' : '-', s.romarray_clear ? 'c' : '-',
	 s.r_micro^0x1ffff, s.l_micro,
	 s.r_nano1^0xf, ~s.r_nano2, ~s.r_nano3,
	 s.l_nano1, s.l_nano2, s.l_nano3,
	 s.ma0, s.ma1, s.ma2, s.ma3, s.madr^0x3ff, s.marom,
	 s.n2553, s.n2780
	 );
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

  if(verbose)
    show_state(s);

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

  if(verbose)
    show_state(s);

  s.ctime++;
}

int main()
{
  cstate s;
  init(s);

  s.p_reset = false;
  s.p_halt = false;

  for(int i=0; i<5; i++)
    step(s, true);

  s.p_reset = true;
  s.p_halt = true;

  for(int i=0; i<20; i++)
    step(s, true);

  return 0;
}
