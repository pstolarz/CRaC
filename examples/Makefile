.PHONY: all clean

CXXFLAGS+=--std=c++17 -Wall -I../inc -g -O
crac_example: CXXFLAGS+=-DCRAC_TEST

EXES:=\
    crac_calcbits \
    crac_example \
    crac_perf

all: ${EXES}

clean:
	${RM} ${EXES} *.disasm

%.disasm: %
	objdump --disassemble --disassembler-options=intel --source --line-numbers --demangle $< >$@
