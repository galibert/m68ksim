#include "sched.h"
#include "blocks.h"

#define T(c) r.c != s.c

void compute_sched(const cstate &r, const cstate &s, std::list<void (*)(cstate &)> &f, bool first)
{
  if(first || T(clk) || T(iclk) || T(p_halt) || T(p_reset) || T(reseti))
    f.push_back(reset_input);
  if(first || T(clk) || T(iclk) || T(n1361) || T(berro) || T(dtackc) || T(n1035) || T(address_drive))
    f.push_back(eclk);     
}
