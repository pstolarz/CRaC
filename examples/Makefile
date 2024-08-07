.PHONY: all clean

CXXFLAGS+=--std=c++17 -Wall -I../inc -O
crac_simple: CXXFLAGS+=-DCRAC_LUT32 -DCRAC_TEST -DCRAC_EXTINT
crac_perf: CXXFLAGS+=-DCRAC_LUT256

EXES:=\
	crac_calcbits \
	crac_simple \
	crac_perf \
	crac_lut

all: ${EXES}

clean:
	${RM} ${EXES} *.disasm

%.disasm: %
	objdump --disassemble --disassembler-options=intel --source --line-numbers --demangle $< >$@
