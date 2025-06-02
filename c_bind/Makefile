.PHONY: all c_bind clean

CXXFLAGS+=--std=c++17 -Wall -I../include -O

all: crac_c_example
c_bind: crac_c.o

crac_c_example: CRC_LIST=CRC8 CRC16 CRC32
crac_c_example: crac_c.o

ifdef $(CRAC_IN_T)
GEN_CONFIG+="CRAC_IN_T=$(CRAC_IN_T)"
endif
ifdef $(CUSTOM_CRCS)
GEN_CONFIG+="CUSTOM_CRCS=$(CUSTOM_CRCS)"
endif

crac_c.cpp:
	@if [ "$(CRC_LIST)x" = "x" ]; then \
	 echo "ERROR: CRC_LIST not defined" >/dev/stderr; \
	 exit 1; \
	fi
	$(GEN_CONFIG) ./gen_c_bind.pl $(CRC_LIST)

clean:
	$(RM) crac_c.h crac_c.cpp crac_c.o crac_c_example
