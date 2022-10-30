# CRaC: C++17 CRC template library

CRaC is C++ single-header template library aiming for fast calculation and
limited runtime footprint needs (especially embedded systems case). The library
extensively exploits compile-time oriented features of the C++ language
requiring at least C++17 compliant compiler.

## Features

The following features distinct the library among dozens of other CRC libraries.

**Runtime fast, compile-time optimized**

Lookup tables generation and all conditional branches are defined and checked
at the compile time by a compiler, emitting the runtime output in reduced
form, optimized for a particular CRC algorithm. Moreover, if an input for
a calculated CRC checksum is known at the compile time, the library may
calculate it purely at the compilation stage with no footprint emitted to the
runtime output. As an example - the library unit tests are performed entirely
at the compile-time level by [`crac_test.h`](inc/crac_test.h) header, and may
be activated by defining `CRAC_TEST`.

**Limited runtime footprint**

The library exploits special type of reduced size lookup table to decrease
runtime footprint size. Most CRC libraries out there, which use lookup tables
to increase CRC computation speed, base on a single 256-elements table to
calculate single-byte CRC checksum. Such approach may by a blocker for tiny
embedded platforms, where 1kB CRC-32 lookup table is simply too large. CRaC
incorporates two 16-elements lookup tables, drastically reducing the footprint,
without significant performance penalty (see below for details).

NOTE: Single 256-elements lookup table is still possible to use by defining
`CRAC_TAB256`.

**100+ predefined CRCs**

Beside allowing to define arbitrary CRCs, the library provides large set of
predefined CRCs ready to use out of the box. Note, the definitions are provided
directly at the compile-time level, therefore don't occupy runtime outcome
unless reference exists in the source code - if you don't use it, you don't pay
for it.

## Performance

CRaC, as most modern C++ libraries, heavily depends on compiler optimization
techniques to produce fast and efficient code. The following table presents
CRC-32 computation timings for 1 million iterations over 256-bytes table with
256-elements lookup table used (values in ms):

|            | clang -O | clang    | gcc -O   | gcc      |
|------------|----------|----------|----------|----------|
| CRaC       |**0.452** | 1.440    | 0.524    | 1.48     |
| CRC++      | 0.525    | 1.170    | 0.522    | 1.08     |
| libcrc     | 0.514    | 0.516    | 0.516    | 0.518    |

As may be seen, decent C++ compiler (clang) with basic optimization turned on
(`-O`) produces code even more efficient than pure C library (`libcrc`).

**256 vs 32-elements lookups**

By default CRaC works with 32-elements lookup tables, which produce lower
footprint size with some performance loss as presented in the following table
(the same test conditions as previously; values in ms):

|            | clang -O | clang    | gcc -O   | gcc      |
|------------|----------|----------|----------|----------|
| 256-lookup | 0.452    | 1.440    | 0.524    | 1.48     |
| 32-lookup  | 0.676    | 1.685    | 0.687    | 1.67     |

As a conclusion, unoptimized compilation introduces performance loss an order
of magnitude larger than 32-elements lookup tables usage.

**Runtime footprint**

CRaC is characterized by reduced runtime footprint size, which is especially
important factor in the embedded systems area. The following table presents
various CRC types usage, compiled for AVR 8-bit platform (gcc-avr toolchain)
with size optimization turned on (`-Os`).

|                     | FLASH [B]          | RAM [B]  |
|---------------------|--------------------|----------|
| CRC-8 [32-lookup]   | 74(code)+32(LU)    | 32(LU)   |
| CRC-8 [256-lookup]  | 50(code)+256(LU)   | 256(LU)  |
| CRC-16 [32-lookup]  | 86(code)+64(LU)    | 64(LU)   |
| CRC-16 [256-lookup] | 60(code)+512(LU)   | 512(LU)  |
| CRC-32 [32-lookup]  | 144(code)+128(LU)  | 128(LU)  |
| CRC-32 [256-lookup] | 92(code)+1024(LU)  | 1024(LU) |
| CRC-64 [32-lookup]  | 198(code)+256(LU)  | 256(LU)  |
| CRC-64 [256-lookup] | 108(code)+2048(LU) | 2048(LU) |


## Usage

The library can calculate CRC checksum purely at the compile time (if an input
data is known at the source code level, aka `constexpr`) or classically during
the runtime phase. In the latter case the computation may be performed in two
types of modes - single step mode and the block mode.

```c++
// define to use 256-elements lookup table
//#define CRAC_TAB256
#include "crac.h"

// ...

using namespace crac;

// crc_check_str is defined by CRaC library as compile-time
// constant "123456789" string w/o trailing null-terminator

constexpr const size_t len = sizeof(crc_check_str);

// compile-time CRC calculation
static_assert(CRC32::calc(crc_check_str, len) == CRC32::check_val);

// runtime calculation: single step mode
auto crc = CRC32::calc(crc_check_str, len);

// runtime calculation: block mode
auto block_eng = CRC32::get_block_eng();
block_eng.update(crc_check_str, 3);
block_eng.update(crc_check_str + 3, 3);
block_eng.update(crc_check_str + 6, len - 6);
assert(crc == block_eng.final());

// Custom CRC-5 definition:
//   polynomial: 0x15,
//   direct-input,
//   direct-output,
//   initial value: 0,
//   output XOR value: 0.
using CRC5_CUSTOM = crc_algo<5, 0x15, false, false, 0, 0>;
static_assert(CRC5_CUSTOM::calc(crc_check_str, len) == CRC5_CUSTOM::check_val);
```

## Predefined CRCs

The library provides the following set of predefined CRCs:

| CRC                    | Poly               | ReflIn | ReflOut | InitVal  | XorOut   | CheckVal           |
|------------------------|--------------------|--------|---------|----------|----------|--------------------|
| CRC1                   | 0x1                | Y      | Y       | 0        | 0        | 0x1                |
| CRC3_GSM               | 0x3                | N      | N       | 0        | ~0       | 0x4                |
| CRC3_ROHC              | 0x3                | Y      | Y       | ~0       | 0        | 0x6                |
| CRC4_ITU               | 0x3                | Y      | Y       | 0        | 0        | 0x7                |
| CRC4_INTERLAKEN        | 0x3                | N      | N       | ~0       | ~0       | 0xb                |
| CRC5_USB               | 0x05               | Y      | Y       | ~0       | ~0       | 0x19               |
| CRC5_EPC               | 0x09               | N      | N       | 0x09     | 0        | 0                  |
| CRC5_ITU               | 0x15               | Y      | Y       | 0        | 0        | 0x07               |
| CRC6_ITU               | 0x03               | Y      | Y       | 0        | 0        | 0x06               |
| CRC6_CDMA2000_B        | 0x07               | N      | N       | ~0       | 0        | 0x3b               |
| CRC6_DARC              | 0x19               | Y      | Y       | 0        | 0        | 0x26               |
| CRC6_NR                | 0x21               | N      | N       | 0        | 0        | 0x15               |
| CRC6_CDMA2000_A        | 0x27               | N      | N       | ~0       | 0        | 0x0d               |
| CRC6_GSM               | 0x2f               | N      | N       | 0        | ~0       | 0x13               |
| CRC7                   | 0x09               | N      | N       | 0        | 0        | 0x75               |
| CRC7_UMTS              | 0x45               | N      | N       | 0        | 0        | 0x61               |
| CRC7_ROHC              | 0x4f               | Y      | Y       | ~0       | 0        | 0x53               |
| CRC8                   | 0x07               | N      | N       | 0        | 0        | 0xf4               |
| CRC8_HDLC              | 0x07               | Y      | Y       | ~0       | ~0       | 0x2f               |
| CRC8_ITU               | 0x07               | N      | N       | 0        | 0x55     | 0xa1               |
| CRC8_ROHC              | 0x07               | Y      | Y       | ~0       | 0        | 0xd0               |
| CRC8_EBU               | 0x1d               | Y      | Y       | ~0       | 0        | 0x97               |
| CRC8_GSM_A             | 0x1d               | N      | N       | 0        | 0        | 0x37               |
| CRC8_HITAG             | 0x1d               | N      | N       | ~0       | 0        | 0xb4               |
| CRC8_ICODE             | 0x1d               | N      | N       | 0xfd     | 0        | 0x7e               |
| CRC8_MIFRAME_MAD       | 0x1d               | N      | N       | 0xc7     | 0        | 0x99               |
| CRC8_SAE_J1850         | 0x1d               | N      | N       | ~0       | ~0       | 0x4b               |
| CRC8_AUTOSAR           | 0x2f               | N      | N       | ~0       | ~0       | 0xdf               |
| CRC8_OPENSAFETY        | 0x2f               | N      | N       | 0        | 0        | 0x3e               |
| CRC8_MAXIM             | 0x31               | Y      | Y       | 0        | 0        | 0xa1               |
| CRC8_NRSC5             | 0x31               | N      | N       | ~0       | 0        | 0xf7               |
| CRC8_DARC              | 0x39               | Y      | Y       | 0        | 0        | 0x15               |
| CRC8_GSM_B             | 0x49               | N      | N       | 0        | ~0       | 0x94               |
| CRC8_CDMA2000          | 0x9b               | N      | N       | ~0       | 0        | 0xda               |
| CRC8_LTE               | 0x9b               | N      | N       | 0        | 0        | 0xea               |
| CRC8_WCDMA             | 0x9b               | Y      | Y       | 0        | 0        | 0x25               |
| CRC8_DVB_S2            | 0xd5               | N      | N       | 0        | 0        | 0xbc               |
| CRC8_BLUETOOTH         | 0xa7               | Y      | Y       | 0        | 0        | 0x26               |
| CRC10_GSM              | 0x175              | N      | N       | 0        | ~0       | 0x12a              |
| CRC10                  | 0x233              | N      | N       | 0        | 0        | 0x199              |
| CRC10_CDMA2000         | 0x3d9              | N      | N       | ~0       | 0        | 0x233              |
| CRC11_UMTS             | 0x307              | N      | N       | 0        | 0        | 0x061              |
| CRC11                  | 0x385              | N      | N       | 0x01a    | 0        | 0x5a3              |
| CRC11_NR               | 0x621              | N      | N       | 0        | 0        | 0x5ca              |
| CRC12_DECT             | 0x80f              | N      | N       | 0        | 0        | 0xf5b              |
| CRC12_UMTS             | 0x80f              | N      | Y       | 0        | 0        | 0xdaf              |
| CRC12_GSM              | 0xd31              | N      | N       | 0        | ~0       | 0xb34              |
| CRC12_CDMA2000         | 0xf13              | N      | N       | ~0       | 0        | 0xd4d              |
| CRC13_BBC              | 0x1cf5             | N      | N       | 0        | 0        | 0x04fa             |
| CRC14_GSM              | 0x202d             | N      | N       | 0        | ~0       | 0x30ae             |
| CRC14_DARC             | 0x0805             | Y      | Y       | 0        | 0        | 0x082d             |
| CRC15                  | 0x4599             | N      | N       | 0        | 0        | 0x059e             |
| CRC15_MPT1327          | 0x6815             | N      | N       | 0        | 0x0001   | 0x2566             |
| CRC16_DECT_R           | 0x0589             | N      | N       | 0        | 0x0001   | 0x007e             |
| CRC16_DECT_X           | 0x0589             | N      | N       | 0        | 0        | 0x007f             |
| CRC16_NRSC5            | 0x080b             | Y      | Y       | ~0       | 0        | 0xa066             |
| CRC16_AUG_CCITT        | 0x1021             | N      | N       | 0x1d0f   | 0        | 0xe5cc             |
| CRC16_CCITT_FALSE      | 0x1021             | N      | N       | ~0       | 0        | 0x29b1             |
| CRC16_GENIBUS          | 0x1021             | N      | N       | ~0       | ~0       | 0xd64e             |
| CRC16_GSM              | 0x1021             | N      | N       | 0        | ~0       | 0xce3c             |
| CRC16_ISO_IEC14443_3_A | 0x1021             | Y      | Y       | 0xc6c6   | 0        | 0xbf05             |
| CRC16_KERMIT           | 0x1021             | Y      | Y       | 0        | 0        | 0x2189             |
| CRC16_MCRF4XX          | 0x1021             | Y      | Y       | ~0       | 0        | 0x6f91             |
| CRC16_RIELLO           | 0x1021             | Y      | Y       | 0xb2aa   | 0        | 0x63d0             |
| CRC16_TMS37157         | 0x1021             | Y      | Y       | 0x89ec   | 0        | 0x26b1             |
| CRC16_X25              | 0x1021             | Y      | Y       | ~0       | ~0       | 0x906e             |
| CRC16_XMODEM           | 0x1021             | N      | N       | 0        | 0        | 0x31c3             |
| CRC16_PROFIBUS         | 0x1dcf             | N      | N       | ~0       | ~0       | 0xa819             |
| CRC16_DNP              | 0x3d65             | Y      | Y       | 0        | ~0       | 0xea82             |
| CRC16_EN13757          | 0x3d65             | N      | N       | 0        | ~0       | 0xc2b7             |
| CRC16_M17              | 0x5935             | N      | N       | ~0       | 0        | 0x772b             |
| CRC16_OPENSAFETY_A     | 0x5935             | N      | N       | 0        | 0        | 0x5d38             |
| CRC16_LJ1200           | 0x6f63             | N      | N       | 0        | 0        | 0xbdf4             |
| CRC16_OPENSAFETY_B     | 0x755b             | N      | N       | 0        | 0        | 0x20fe             |
| CRC16_ARC              | 0x8005             | Y      | Y       | 0        | 0        | 0xbb3d             |
| CRC16_BUYPASS          | 0x8005             | N      | N       | 0        | 0        | 0xfee8             |
| CRC16_CMS              | 0x8005             | N      | N       | ~0       | 0        | 0xaee7             |
| CRC16_DDS110           | 0x8005             | N      | N       | 0x800d   | 0        | 0x9ecf             |
| CRC16_MAXIM            | 0x8005             | Y      | Y       | 0        | ~0       | 0x44c2             |
| CRC16_MODBUS           | 0x8005             | Y      | Y       | ~0       | 0        | 0x4b37             |
| CRC16_USB              | 0x8005             | Y      | Y       | ~0       | ~0       | 0xb4c8             |
| CRC16_T10_DIF          | 0x8bb7             | N      | N       | 0        | 0        | 0xd0db             |
| CRC16_CDMA2000         | 0xc867             | N      | N       | ~0       | 0        | 0x4c06             |
| CRC16_TELEDISK         | 0xa097             | N      | N       | 0        | 0        | 0x0fb3             |
| CRC17_CAN_FD           | 0x1685b            | N      | N       | 0        | 0        | 0x04f03            |
| CRC21_CAN_FD           | 0x102899           | N      | N       | 0        | 0        | 0x0ed841           |
| CRC24_BLE              | 0x00065b           | Y      | Y       | 0x555555 | 0        | 0xc25a56           |
| CRC24_INTERLAKEN       | 0x328b63           | N      | N       | ~0       | ~0       | 0xb4f3e6           |
| CRC24_FLEXRAY_A        | 0x5d6dcb           | N      | N       | 0xfedcba | 0        | 0x7979bd           |
| CRC24_FLEXRAY_B        | 0x5d6dcb           | N      | N       | 0xabcdef | 0        | 0x1f23b8           |
| CRC24_LTE_B            | 0x800063           | N      | N       | 0        | 0        | 0x23ef52           |
| CRC24_OS9              | 0x800063           | N      | N       | ~0       | ~0       | 0x200fa5           |
| CRC24                  | 0x864cfb           | N      | N       | 0xb704ce | 0        | 0x21cf02           |
| CRC24_LTE_A            | 0x864cfb           | N      | N       | 0        | 0        | 0xcde703           |
| CRC24_NR_C             | 0xb2b117           | N      | N       | 0        | 0        | 0xf48279           |
| CRC30_CDMA             | 0x2030b9c7         | N      | N       | ~0       | ~0       | 0x04c34abf         |
| CRC31_PHILIPS          | 0x04c11db7         | N      | N       | ~0       | ~0       | 0x0ce9e46c         |
| CRC32_XFER             | 0x000000af         | N      | N       | 0        | 0        | 0xbd0be338         |
| CRC32                  | 0x04c11db7         | Y      | Y       | ~0       | ~0       | 0xcbf43926         |
| CRC32_BZIP2            | 0x04c11db7         | N      | N       | ~0       | ~0       | 0xfc891918         |
| CRC32_JAMCRC           | 0x04c11db7         | Y      | Y       | ~0       | 0        | 0x340bc6d9         |
| CRC32_MPEG2            | 0x04c11db7         | N      | N       | ~0       | 0        | 0x0376e6e7         |
| CRC32_POSIX            | 0x04c11db7         | N      | N       | 0        | ~0       | 0x765e7680         |
| CRC32_C                | 0x1edc6f41         | Y      | Y       | ~0       | ~0       | 0xe3069283         |
| CRC32_MEF              | 0x741b8cd7         | Y      | Y       | ~0       | 0        | 0xd2c22f51         |
| CRC32_CDROM_EDC        | 0x8001801b         | Y      | Y       | 0        | 0        | 0x6ec2edc4         |
| CRC32_Q                | 0x814141ab         | N      | N       | 0        | 0        | 0x3010bf7f         |
| CRC32_D                | 0xa833982b         | Y      | Y       | ~0       | ~0       | 0x87315576         |
| CRC32_AUTOSAR          | 0xf4acfb13         | Y      | Y       | ~0       | ~0       | 0x1697d06a         |
| CRC40_GSM              | 0x0004820009       | N      | N       | 0        | ~0       | 0xd4164fc646       |
| CRC64_GO_ISO           | 0x000000000000001b | Y      | Y       | ~0       | ~0       | 0xb90956c775a41001 |
| CRC64_MS               | 0x259c84cba6426349 | Y      | Y       | ~0       | 0        | 0x75d4b74f024eceea |
| CRC64                  | 0x42f0e1eba9ea3693 | N      | N       | 0        | 0        | 0x6c40df5f0b497347 |
| CRC64_WE               | 0x42f0e1eba9ea3693 | N      | N       | ~0       | ~0       | 0x62ec59e3f1a4f00a |
| CRC64_XZ               | 0x42f0e1eba9ea3693 | Y      | Y       | ~0       | ~0       | 0x995dc9bbdf1939fa |
| CRC64_REDIS            | 0xad93d23594c935a9 | Y      | Y       | 0        | 0        | 0xe9c6d914c4b8d9ca |

Some of the above algorithms have one or more aliases (e.g. `CRC16_KERMIT`,
`CRC16_BLUETOOTH`, `CRC16_CCITT`, `CRC16_CCITT_TRUE`, `CRC16_V41_LSB` refer
to the same CRC). See [`crac.h`](inc/crac.h) for more details.

### References

1. [Catalogue of parametrised CRC algorithms](https://reveng.sourceforge.io/crc-catalogue/all.htm); CRC RevEng
2. [Cyclic redundancy code (CRC)](https://infineon.github.io/mtb-pdl-cat2/pdl_api_reference_manual/html/group__group__crypto__lld__crc__functions.html); CAT2 Peripheral Driver Library
3. [Cyclic redundancy code (CRC)](https://en.wikipedia.org/wiki/Cyclic_redundancy_check); Wikipedia
## License

2 clause BSD license. See [`LICENSE`](LICENSE) file for details.
