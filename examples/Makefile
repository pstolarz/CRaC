.PHONY: all test clean

CXXFLAGS+=--std=c++17 -Wall -I../include -O
crac_perf: CXXFLAGS+=-DCRAC_LUT256

EXES:=\
	crac_calcbits \
	crac_simple \
	crac_perf \
	crac_lut

TESTS:=\
	test256.o \
	test32.o \
	test16.o

test256.o: CXXFLAGS+=-DCRAC_LUT256 -DCRAC_TEST -DCRAC_EXTINT
test32.o: CXXFLAGS+=-DCRAC_LUT32 -DCRAC_TEST -DCRAC_EXTINT
test16.o: CXXFLAGS+=-DCRAC_LUT16 -DCRAC_TEST -DCRAC_EXTINT

all: $(EXES)

test: $(TESTS)

$(TESTS):
	$(CXX) $(CXXFLAGS) -c -o $@ crac_simple.cpp

clean:
	$(RM) test*.o $(EXES) *.disasm

%.disasm: %
	objdump --disassemble --disassembler-options=intel --source --line-numbers --demangle $< >$@
