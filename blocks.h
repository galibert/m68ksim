#ifndef BLOCKS_H
#define BLOCKS_H

#include "state.h"

void reset_input(cstate &s);
void eclk(cstate &s);
void eu_timing(cstate &s);
void ma(cstate &s);

#endif
