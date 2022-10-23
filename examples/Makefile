.PHONY: all clean

CXXFLAGS+=--std=c++17 -Wall -I../inc
crac_example: CXXFLAGS+=-DCRAC_TEST
crac_perf: CXXFLAGS+=-O

EXES:=\
    crac_example \
    crac_perf

all: ${EXES}

clean:
	${RM} ${EXES}
