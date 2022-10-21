.PHONY: all clean

CXXFLAGS+=--std=c++17 -Wall -I../inc
crac_example: CXXFLAGS+=-D_CRAC_TEST_
crac_perf: CXXFLAGS+=-O3

EXES:=\
    crac_example \
    crac_perf

all: ${EXES}

clean:
	${RM} ${EXES}
