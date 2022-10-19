.PHONY: all clean

CXXFLAGS+=--std=c++17 -Wall -D_TEST_ -I../inc
crac_perf: CXXFLAGS+=-O3

EXES:=\
    crac_example \
    crac_perf

all: ${EXES}

clean:
	${RM} ${EXES}
