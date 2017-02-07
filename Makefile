ALLINC = 
ALLLIB =
DEPLIB = 

PROG = m68ksim
OBJS = blocks.o rom.o m68ksim.o eu.o sched.o
SRCS = blocks.cc rom.cc m68ksim.cc eu.cc sched.cc
JUNK =

OPT=-O9

CC=gcc
CXX=g++
CFLAGS=-g -Wall ${OPT}

all: ${PROG}

.SUFFIXES: .cc .hh .o .a .ui .m.cc .m.o .y
.PRECIOUS: ${JUNK}

${PROG}: ${OBJS} ${DEPLIB}
	${CXX} ${CFLAGS} ${OBJS} ${ALLLIB} ${ALLINC} -o ${PROG}

.cc.o:
	${CXX} -c ${CFLAGS} ${DEFS} ${ALLINC} $<

.c.o:
	${CC} -c ${CFLAGS} ${DEFS} ${ALLINC} $<

.y.c:
	bison -d -o $@ $<

.y.h:
	bison -d -o $@ $<

clean:
	rm -f ${PROG} ${OBJS} ${JUNK}

distclean:
	rm -f ${PROG} ${OBJS} ${JUNK}

###
blocks.o: blocks.h state.h
rom.o: blocks.h state.h
m68ksim.o: blocks.h state.h sched.h
eu.o: eu.h state.h
sched.o: sched.h state.h blocks.h rom.h eu.h
