.PHONY: all clean

CRC_LIST?=\
	CRC8 \
	CRC16 \
	CRC32

CXXFLAGS+=--std=c++17 -Wall -I../inc -O

all: crac_c_example

clean:
	$(RM) crac_c.h crac_c.cpp crac_c.o crac_c_example

crac_c.cpp:
	./gen_c_bind.pl $(CRC_LIST)

crac_c_example: crac_c.o
