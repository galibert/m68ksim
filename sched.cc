#include "sched.h"
#include "blocks.h"
#include "rom.h"
#include "eu.h"

#define T(c) r.c != s.c

void compute_sched(const cstate &r, const cstate &s, std::list<void (*)(cstate &)> &f, bool first)
{
  if(first || T(clk) || T(iclk) || T(p_halt) || T(p_reset) || T(reseti) || T(bus_delay))
    f.push_back(reset_input);
  if(first || T(clk) || T(iclk) || T(n1361) || T(berro) || T(dtackc) || T(n1035) || T(address_drive))
    f.push_back(eclk);     
  if(first || T(n148) || T(bus_error_1) || T(n1569) || T(internal_halt) || T(internal_reset) || T(n1361) || T(clk) || T(berro) || T(n2735) || T(iclk))
    f.push_back(eu_timing);
  if(first || T(romarray_precharge) || T(marom) || T(romarray_clear) || T(eu_w))
    f.push_back(rom);
  if(first || T(address_drive) || T(iclk) || T(clk) || T(interrupt_bus_cycle) || T(berro) || T(aob_active) || T(internal_reset) || T(eu_w) || T(eu_p) || T(eu_r) || T(excp_1) || T(trace) || T(priviledge_violation) || T(illegal_instruction) || T(linea) || T(linef) || T(excp_2) || T(excp_3) || T(address_error) || T(ma1) || T(ma2) || T(ma3) || T(l_micro) || T(romarray_precharge) || T(romarray_clear) || T(cc2) || T(cc3))
    f.push_back(ma);

  if(first || T(eu_p) || T(eu_r) || T(eu_w) || T(l_nano1) || T(l_nano2) || T(l_nano3) || T(eu_ld_sense_amp_keep))
    f.push_back(eu);
}
