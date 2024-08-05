/*
 * Copyright (c) 2022-2024 Piotr Stolarz
 * CRaC: C++17 Cyclic Redundancy Check (CRC) template library.
 *
 * Distributed under the 2-clause BSD License (the License)
 * see accompanying file LICENSE for details.
 *
 * This software is distributed WITHOUT ANY WARRANTY; without even the
 * implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the License for more information.
 */

/*
 * Compile-time tester. To be included from the library header only.
 */

namespace {

// std::is_same counterpart
template<typename T1, typename T2> struct _is_same { constexpr static bool value = false; };
template<typename T> struct _is_same<T, T> { constexpr static bool value = true; };
template<typename T1, typename T2> constexpr static bool _is_same_v = _is_same<T1, T2>::value;

//
// CRC output types test
//
static_assert(_is_same_v<CRC1::type, uint8_t>);
static_assert(_is_same_v<CRC3_GSM::type, uint8_t>);
static_assert(_is_same_v<CRC4_ITU::type, uint8_t>);
static_assert(_is_same_v<CRC5_USB::type, uint8_t>);
static_assert(_is_same_v<CRC6_ITU::type, uint8_t>);
static_assert(_is_same_v<CRC7::type, uint8_t>);
static_assert(_is_same_v<CRC8::type, uint8_t>);
static_assert(_is_same_v<CRC10_GSM::type, uint16_t>);
static_assert(_is_same_v<CRC11_UMTS::type, uint16_t>);
static_assert(_is_same_v<CRC12_DECT::type, uint16_t>);
static_assert(_is_same_v<CRC13_BBC::type, uint16_t>);
static_assert(_is_same_v<CRC14_GSM::type, uint16_t>);
static_assert(_is_same_v<CRC15::type, uint16_t>);
static_assert(_is_same_v<CRC16_DECT_R::type, uint16_t>);
static_assert(_is_same_v<CRC17_CAN_FD::type, uint32_t>);
static_assert(_is_same_v<CRC21_CAN_FD::type, uint32_t>);
static_assert(_is_same_v<CRC24_BLE::type, uint32_t>);
static_assert(_is_same_v<CRC30_CDMA::type, uint32_t>);
static_assert(_is_same_v<CRC31_PHILIPS::type, uint32_t>);
static_assert(_is_same_v<CRC32_XFER::type, uint32_t>);
static_assert(_is_same_v<CRC40_GSM::type, uint64_t>);
static_assert(_is_same_v<CRC64_GO_ISO::type, uint64_t>);
#ifdef __USE_EXTINT
static_assert(_is_same_v<CRC82_DARC::type, __uint128_t>);
#endif

//
// Reverse polynomials test
//
static_assert(CRC1::poly_rev == 0x1);
static_assert(CRC3_GSM::poly_rev == 0x6);
static_assert(CRC4_ITU::poly_rev == 0xc);
static_assert(CRC5_USB::poly_rev == 0x14);
static_assert(CRC5_EPC::poly_rev == 0x12);
static_assert(CRC5_ITU::poly_rev == 0x15);
static_assert(CRC6_ITU::poly_rev == 0x30);
static_assert(CRC6_CDMA2000_B::poly_rev == 0x38);
static_assert(CRC6_DARC::poly_rev == 0x26);
static_assert(CRC6_NR::poly_rev == 0x21);
static_assert(CRC6_CDMA2000_A::poly_rev == 0x39);
static_assert(CRC6_GSM::poly_rev == 0x3d);
static_assert(CRC7::poly_rev == 0x48);
static_assert(CRC7_UMTS::poly_rev == 0x51);
static_assert(CRC7_ROHC::poly_rev == 0x79);
// static_assert(CRC7_MVB::poly_rev == 0x53);
static_assert(CRC8::poly_rev == 0xe0);
static_assert(CRC8_EBU::poly_rev == 0xb8);
static_assert(CRC8_AUTOSAR::poly_rev == 0xf4);
static_assert(CRC8_MAXIM::poly_rev == 0x8c);
static_assert(CRC8_DARC::poly_rev == 0x9c);
static_assert(CRC8_GSM_B::poly_rev == 0x92);
static_assert(CRC8_CDMA2000::poly_rev == 0xd9);
static_assert(CRC8_DVB_S2::poly_rev == 0xab);
static_assert(CRC8_BLUETOOTH::poly_rev == 0xe5);
static_assert(CRC10_GSM::poly_rev == 0x2ba);
static_assert(CRC10::poly_rev == 0x331);
static_assert(CRC10_CDMA2000::poly_rev == 0x26f);
static_assert(CRC11_UMTS::poly_rev == 0x0706);
static_assert(CRC11::poly_rev == 0x50e);
static_assert(CRC11_NR::poly_rev == 0x423);
static_assert(CRC12_DECT::poly_rev == 0xf01);
static_assert(CRC12_GSM::poly_rev == 0x8cb);
static_assert(CRC12_CDMA2000::poly_rev == 0xc8f);
static_assert(CRC13_BBC::poly_rev == 0x15e7);
static_assert(CRC14_GSM::poly_rev == 0x2d01);
static_assert(CRC14_DARC::poly_rev == 0x2804);
static_assert(CRC15::poly_rev == 0x4cd1);
static_assert(CRC15_MPT1327::poly_rev == 0x540b);
static_assert(CRC16_DECT_R::poly_rev == 0x91a0);
static_assert(CRC16_NRSC5::poly_rev == 0xd010);
static_assert(CRC16_AUG_CCITT::poly_rev == 0x8408);
static_assert(CRC16_PROFIBUS::poly_rev == 0xf3b8);
// static_assert(CRC16_CHAKRAVARTY::poly_rev == 0xa8f4);
static_assert(CRC16_DNP::poly_rev == 0xa6bc);
static_assert(CRC16_M17::poly_rev == 0xac9a);
static_assert(CRC16_LJ1200::poly_rev == 0xc6f6);
static_assert(CRC16_OPENSAFETY_B::poly_rev == 0xdaae);
static_assert(CRC16_ARC::poly_rev == 0xa001);
static_assert(CRC16_T10_DIF::poly_rev == 0xedd1);
static_assert(CRC16_CDMA2000::poly_rev == 0xe613);
// static_assert(CRC16_ARINC::poly_rev == 0xd405);
static_assert(CRC16_TELEDISK::poly_rev == 0xe905);
static_assert(CRC17_CAN_FD::poly_rev == 0x1b42d);
static_assert(CRC21_CAN_FD::poly_rev == 0x132281);
static_assert(CRC24_BLE::poly_rev == 0xda6000);
static_assert(CRC24_INTERLAKEN::poly_rev == 0xc6d14c);
static_assert(CRC24_FLEXRAY_A::poly_rev == 0xd3b6ba);
static_assert(CRC24_LTE_B::poly_rev == 0xc60001);
static_assert(CRC24::poly_rev == 0xdf3261);
static_assert(CRC24_NR_C::poly_rev == 0xe88d4d);
static_assert(CRC30_CDMA::poly_rev == 0x38e74301);
static_assert(CRC31_PHILIPS::poly_rev == 0x76dc4190);
static_assert(CRC32_XFER::poly_rev == 0xf5000000);
static_assert(CRC32::poly_rev == 0xedb88320);
static_assert(CRC32_C::poly_rev == 0x82f63b78);
static_assert(CRC32_MEF::poly_rev == 0xeb31d82e);
// static_assert(CRC32_K2::poly_rev == 0x992c1a4c);
static_assert(CRC32_CDROM_EDC::poly_rev == 0xd8018001);
static_assert(CRC32_Q::poly_rev == 0xd5828281);
static_assert(CRC32_D::poly_rev == 0xd419cc15);
static_assert(CRC32_AUTOSAR::poly_rev == 0xc8df352f);
static_assert(CRC40_GSM::poly_rev == 0x9000412000);
static_assert(CRC64_GO_ISO::poly_rev == 0xd800000000000000);
static_assert(CRC64_MS::poly_rev == 0x92c64265d32139a4);
static_assert(CRC64::poly_rev == 0xc96c5795d7870f42);
static_assert(CRC64_REDIS::poly_rev == 0x95ac9329ac4bc9b5);
#ifdef __USE_EXTINT
static_assert(CRC82_DARC::poly_rev == 0x220808a00a2022200c430_u128);
#endif

// runtime objects size tester
template<typename Crc>
struct test_rt_sizes: Crc
{
    constexpr static bool do_test()
    {
        if (sizeof(typename Crc::block_eng) != sizeof(typename Crc::type))
            return false;

        if constexpr (Crc::tab_type == crc_tab_e::TAB256) {
            return (sizeof(Crc::lookup) == 256 * sizeof(typename Crc::type));
        } else if constexpr (Crc::tab_type == crc_tab_e::TAB16) {
            return (sizeof(Crc::lookup) == 16 * sizeof(typename Crc::type));
        } else {
            return (sizeof(Crc::lookup) == 32 * sizeof(typename Crc::type));
        }
    }

    constexpr static bool value = do_test();
};

template<typename Crc>
constexpr static bool test_rt_sizes_v = test_rt_sizes<Crc>::value;

//
// Runtime objects size test
//
static_assert(test_rt_sizes_v<CRC1>);
static_assert(test_rt_sizes_v<CRC3_GSM>);
static_assert(test_rt_sizes_v<CRC4_ITU>);
static_assert(test_rt_sizes_v<CRC5_USB>);
static_assert(test_rt_sizes_v<CRC6_ITU>);
static_assert(test_rt_sizes_v<CRC7>);
static_assert(test_rt_sizes_v<CRC8>);
static_assert(test_rt_sizes_v<CRC10_GSM>);
static_assert(test_rt_sizes_v<CRC11_UMTS>);
static_assert(test_rt_sizes_v<CRC12_DECT>);
static_assert(test_rt_sizes_v<CRC13_BBC>);
static_assert(test_rt_sizes_v<CRC14_GSM>);
static_assert(test_rt_sizes_v<CRC15>);
static_assert(test_rt_sizes_v<CRC16_DECT_R>);
static_assert(test_rt_sizes_v<CRC17_CAN_FD>);
static_assert(test_rt_sizes_v<CRC21_CAN_FD>);
static_assert(test_rt_sizes_v<CRC24_BLE>);
static_assert(test_rt_sizes_v<CRC30_CDMA>);
static_assert(test_rt_sizes_v<CRC31_PHILIPS>);
static_assert(test_rt_sizes_v<CRC32_XFER>);
static_assert(test_rt_sizes_v<CRC40_GSM>);
static_assert(test_rt_sizes_v<CRC64_GO_ISO>);
#ifdef __USE_EXTINT
static_assert(test_rt_sizes_v<CRC82_DARC>);
#endif

// CRC validation tester
template<typename Crc>
struct test_crc: Crc
{
    constexpr static bool do_test()
    {
        return (Crc::check_val == Crc::calc(crc_check_str, sizeof(crc_check_str)));
    }

    constexpr static bool value = do_test();
};

template<typename Crc>
constexpr static bool test_crc_v = test_crc<Crc>::value;

//
// CRCs validation test
//
static_assert(test_crc_v<CRC1>);
static_assert(test_crc_v<CRC3_GSM>);
static_assert(test_crc_v<CRC3_ROHC>);
static_assert(test_crc_v<CRC4_ITU>);
static_assert(test_crc_v<CRC4_INTERLAKEN>);
static_assert(test_crc_v<CRC5_USB>);
static_assert(test_crc_v<CRC5_EPC>);
static_assert(test_crc_v<CRC5_ITU>);
static_assert(test_crc_v<CRC6_ITU>);
static_assert(test_crc_v<CRC6_CDMA2000_B>);
static_assert(test_crc_v<CRC6_DARC>);
static_assert(test_crc_v<CRC6_NR>);
static_assert(test_crc_v<CRC6_CDMA2000_A>);
static_assert(test_crc_v<CRC6_GSM>);
static_assert(test_crc_v<CRC7>);
static_assert(test_crc_v<CRC7_UMTS>);
static_assert(test_crc_v<CRC7_ROHC>);
// static_assert(test_crc_v<CRC7_MVB>);
static_assert(test_crc_v<CRC8>);
static_assert(test_crc_v<CRC8_HDLC>);
static_assert(test_crc_v<CRC8_ITU>);
static_assert(test_crc_v<CRC8_ROHC>);
static_assert(test_crc_v<CRC8_EBU>);
static_assert(test_crc_v<CRC8_GSM_A>);
static_assert(test_crc_v<CRC8_HITAG>);
static_assert(test_crc_v<CRC8_ICODE>);
static_assert(test_crc_v<CRC8_MIFRAME_MAD>);
static_assert(test_crc_v<CRC8_SAE_J1850>);
static_assert(test_crc_v<CRC8_AUTOSAR>);
static_assert(test_crc_v<CRC8_OPENSAFETY>);
static_assert(test_crc_v<CRC8_MAXIM>);
static_assert(test_crc_v<CRC8_NRSC5>);
static_assert(test_crc_v<CRC8_DARC>);
static_assert(test_crc_v<CRC8_GSM_B>);
static_assert(test_crc_v<CRC8_CDMA2000>);
static_assert(test_crc_v<CRC8_LTE>);
static_assert(test_crc_v<CRC8_WCDMA>);
static_assert(test_crc_v<CRC8_DVB_S2>);
static_assert(test_crc_v<CRC8_BLUETOOTH>);
static_assert(test_crc_v<CRC10_GSM>);
static_assert(test_crc_v<CRC10>);
static_assert(test_crc_v<CRC10_CDMA2000>);
static_assert(test_crc_v<CRC11_UMTS>);
static_assert(test_crc_v<CRC11>);
static_assert(test_crc_v<CRC11_NR>);
static_assert(test_crc_v<CRC12_DECT>);
static_assert(test_crc_v<CRC12_UMTS>);
static_assert(test_crc_v<CRC12_GSM>);
static_assert(test_crc_v<CRC12_CDMA2000>);
static_assert(test_crc_v<CRC13_BBC>);
static_assert(test_crc_v<CRC14_GSM>);
static_assert(test_crc_v<CRC14_DARC>);
static_assert(test_crc_v<CRC15>);
static_assert(test_crc_v<CRC15_MPT1327>);
static_assert(test_crc_v<CRC16_DECT_R>);
static_assert(test_crc_v<CRC16_DECT_X>);
static_assert(test_crc_v<CRC16_NRSC5>);
static_assert(test_crc_v<CRC16_AUG_CCITT>);
static_assert(test_crc_v<CRC16_CCITT_FALSE>);
static_assert(test_crc_v<CRC16_GENIBUS>);
static_assert(test_crc_v<CRC16_GSM>);
static_assert(test_crc_v<CRC16_ISO_IEC14443_3_A>);
static_assert(test_crc_v<CRC16_KERMIT>);
static_assert(test_crc_v<CRC16_MCRF4XX>);
static_assert(test_crc_v<CRC16_RIELLO>);
static_assert(test_crc_v<CRC16_TMS37157>);
static_assert(test_crc_v<CRC16_X25>);
static_assert(test_crc_v<CRC16_XMODEM>);
static_assert(test_crc_v<CRC16_PROFIBUS>);
// static_assert(test_crc_v<CRC16_CHAKRAVARTY>);
static_assert(test_crc_v<CRC16_DNP>);
static_assert(test_crc_v<CRC16_EN13757>);
static_assert(test_crc_v<CRC16_M17>);
static_assert(test_crc_v<CRC16_OPENSAFETY_A>);
static_assert(test_crc_v<CRC16_LJ1200>);
static_assert(test_crc_v<CRC16_OPENSAFETY_B>);
static_assert(test_crc_v<CRC16_ARC>);
static_assert(test_crc_v<CRC16_BUYPASS>);
static_assert(test_crc_v<CRC16_CMS>);
static_assert(test_crc_v<CRC16_DDS110>);
static_assert(test_crc_v<CRC16_MAXIM>);
static_assert(test_crc_v<CRC16_MODBUS>);
static_assert(test_crc_v<CRC16_USB>);
static_assert(test_crc_v<CRC16_T10_DIF>);
static_assert(test_crc_v<CRC16_CDMA2000>);
// static_assert(test_crc_v<CRC16_ARINC>);
static_assert(test_crc_v<CRC16_TELEDISK>);
static_assert(test_crc_v<CRC17_CAN_FD>);
static_assert(test_crc_v<CRC21_CAN_FD>);
static_assert(test_crc_v<CRC24_BLE>);
static_assert(test_crc_v<CRC24_INTERLAKEN>);
static_assert(test_crc_v<CRC24_FLEXRAY_A>);
static_assert(test_crc_v<CRC24_FLEXRAY_B>);
static_assert(test_crc_v<CRC24_LTE_B>);
static_assert(test_crc_v<CRC24_OS9>);
static_assert(test_crc_v<CRC24>);
static_assert(test_crc_v<CRC24_LTE_A>);
static_assert(test_crc_v<CRC24_NR_C>);
static_assert(test_crc_v<CRC30_CDMA>);
static_assert(test_crc_v<CRC31_PHILIPS>);
static_assert(test_crc_v<CRC32_XFER>);
static_assert(test_crc_v<CRC32>);
static_assert(test_crc_v<CRC32_BZIP2>);
static_assert(test_crc_v<CRC32_EDC>);
static_assert(test_crc_v<CRC32_JAMCRC>);
static_assert(test_crc_v<CRC32_MPEG2>);
static_assert(test_crc_v<CRC32_POSIX>);
static_assert(test_crc_v<CRC32_C>);
// static_assert(test_crc_v<CRC32_K2>);
static_assert(test_crc_v<CRC32_MEF>);
static_assert(test_crc_v<CRC32_CDROM_EDC>);
static_assert(test_crc_v<CRC32_Q>);
static_assert(test_crc_v<CRC32_D>);
static_assert(test_crc_v<CRC32_AUTOSAR>);
static_assert(test_crc_v<CRC40_GSM>);
static_assert(test_crc_v<CRC64_GO_ISO>);
static_assert(test_crc_v<CRC64_MS>);
static_assert(test_crc_v<CRC64>);
static_assert(test_crc_v<CRC64_WE>);
static_assert(test_crc_v<CRC64_XZ>);
static_assert(test_crc_v<CRC64_REDIS>);
#ifdef __USE_EXTINT
static_assert(test_crc_v<CRC82_DARC>);
#endif

// non-standard CRC w/o check-value provided
static_assert(test_crc_v<crc_algo<5, 0x15, false, false, 0, 0>>);

// CRC on bits validation tester
template<typename Crc, typename T, T In, unsigned InBits, typename Crc::type ExpVal>
struct test_crc_bits: Crc
{
    static_assert(!Crc::refl_in && Crc::init_val == 0);

    // reflected CRC
    using Crc_r = crc_algo<
        Crc::bits,
        Crc::poly,
        true,
        true,
        0, 0>;

    constexpr static bool do_test()
    {
        constexpr auto crc = Crc::calc_bits(In, InBits);
        constexpr auto crc_r = Crc_r::calc_bits(
            // if possible add extra MSB bit to the reverted input (shall be ignored)
            ((InBits & 7) ? ((T)1 << InBits) : 0) | bits_rev(In, InBits),
            InBits);

        return (crc == ExpVal)  && (crc_r == bits_rev(ExpVal, Crc::bits));
    }

    constexpr static bool value = do_test();
};

template<typename Crc, typename T, T In, unsigned InBits, typename Crc::type ExpVal>
constexpr static bool test_crc_bits_v = test_crc_bits<Crc, T, In, InBits, ExpVal>::value;

//
// CRC on bits validation tests
//
// Test values computed directly from CRC definition using the following
// on-line calculator: https://rndtool.info/CRC-step-by-step-calculator
//

using TEST_CRC4 = crc_algo<
    4,
    0x3,
    false,
    false,
    0, 0>;

static_assert(test_crc_bits_v<TEST_CRC4, uint8_t, 0x01, 1, 0x3>);
static_assert(test_crc_bits_v<TEST_CRC4, uint8_t, 0x0f, 2, 0x5>);
static_assert(test_crc_bits_v<TEST_CRC4, uint8_t, 0x11, 5, 0x6>);
static_assert(test_crc_bits_v<TEST_CRC4, uint8_t, 0x14, 7, 0x9>);
static_assert(test_crc_bits_v<TEST_CRC4, uint8_t, 0x65, 8, 0x2>);
static_assert(test_crc_bits_v<TEST_CRC4, uint16_t, 0x29b, 10, 0x8>);
static_assert(test_crc_bits_v<TEST_CRC4, uint16_t, 0x874e, 14, 0xd>);
static_assert(test_crc_bits_v<TEST_CRC4, uint16_t, 0x8a6b, 16, 0xc>);
static_assert(test_crc_bits_v<TEST_CRC4, uint32_t, 0x497d7, 18, 0xf>);
static_assert(test_crc_bits_v<TEST_CRC4, uint32_t, 0x8802b, 20, 0x2>);
static_assert(test_crc_bits_v<TEST_CRC4, uint32_t, 0x0f0f0f, 24, 0xc>);
static_assert(test_crc_bits_v<TEST_CRC4, uint32_t, 0x3f3fbef, 26, 0xd>);
static_assert(test_crc_bits_v<TEST_CRC4, uint32_t, 0xe4057854, 30, 0x5>);
static_assert(test_crc_bits_v<TEST_CRC4, uint32_t, 0xffffffff, 32, 0x5>);

using TEST_CRC16 = crc_algo<
    16,
    0x1021,
    false,
    false,
    0, 0>;

static_assert(test_crc_bits_v<TEST_CRC16, uint8_t, 0xff, 1, 0x1021>);
static_assert(test_crc_bits_v<TEST_CRC16, uint8_t, 0x0f, 2, 0x3063>);
static_assert(test_crc_bits_v<TEST_CRC16, uint8_t, 0xf3, 5, 0x2252>);
static_assert(test_crc_bits_v<TEST_CRC16, uint8_t, 0x6f, 7, 0x9d49>);
static_assert(test_crc_bits_v<TEST_CRC16, uint8_t, 0xeb, 8, 0x4c45>);
static_assert(test_crc_bits_v<TEST_CRC16, uint16_t, 0xd375, 10, 0x7b61>);
static_assert(test_crc_bits_v<TEST_CRC16, uint16_t, 0xacca, 14, 0x3b8d>);
static_assert(test_crc_bits_v<TEST_CRC16, uint16_t, 0xa71f, 16, 0x6737>);
static_assert(test_crc_bits_v<TEST_CRC16, uint32_t, 0x1d493, 18, 0x5d09>);
static_assert(test_crc_bits_v<TEST_CRC16, uint32_t, 0xf3a927, 20, 0xaa33>);
static_assert(test_crc_bits_v<TEST_CRC16, uint32_t, 0xff0f0f0, 24, 0x1f8c>);
static_assert(test_crc_bits_v<TEST_CRC16, uint32_t, 0x43c3c3f, 26, 0x3780>);
static_assert(test_crc_bits_v<TEST_CRC16, uint32_t, 0xf4408203, 30, 0xb62c>);
static_assert(test_crc_bits_v<TEST_CRC16, uint32_t, 0xa4420810, 32, 0xc8d2>);

} // unnamed namespace
