.PHONY: all clean

CXXFLAGS+=--std=c++17 -Wall -I../inc -O
crac_example: CXXFLAGS+=-DCRAC_TEST

EXES:=\
    crac_example \
    crac_perf

all: ${EXES}

clean:
	${RM} ${EXES}
