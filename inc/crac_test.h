/*
 * Copyright (c) 2022 Piotr Stolarz
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
 *
 * NOTE: Since the header has impact on the compilation time as well as
 * runtime size output, it is not recommended to use it for builds where
 * these factors are important.
 */

namespace {

// std::is_same counterpart
template<typename T1, typename T2> struct _is_same { constexpr static bool value = false; };
template<typename T> struct _is_same<T, T> { constexpr static bool value = true; };
template<typename T1, typename T2> constexpr static bool _is_same_v = _is_same<T1, T2>::value;

//
// CRC output types test
//
static_assert(_is_same_v<CRC1::type, uint8_t>, "");
static_assert(_is_same_v<CRC3_GSM::type, uint8_t>, "");
static_assert(_is_same_v<CRC4_ITU::type, uint8_t>, "");
static_assert(_is_same_v<CRC5_USB::type, uint8_t>, "");
static_assert(_is_same_v<CRC6_ITU::type, uint8_t>, "");
static_assert(_is_same_v<CRC7::type, uint8_t>, "");
static_assert(_is_same_v<CRC8::type, uint8_t>, "");
static_assert(_is_same_v<CRC10_GSM::type, uint16_t>, "");
static_assert(_is_same_v<CRC11_UMTS::type, uint16_t>, "");
static_assert(_is_same_v<CRC12_DECT::type, uint16_t>, "");
static_assert(_is_same_v<CRC13_BBC::type, uint16_t>, "");
static_assert(_is_same_v<CRC14_GSM::type, uint16_t>, "");
static_assert(_is_same_v<CRC15::type, uint16_t>, "");
static_assert(_is_same_v<CRC16_DECT_R::type, uint16_t>, "");
static_assert(_is_same_v<CRC17_CAN_FD::type, uint32_t>, "");
static_assert(_is_same_v<CRC21_CAN_FD::type, uint32_t>, "");
static_assert(_is_same_v<CRC24_BLE::type, uint32_t>, "");
static_assert(_is_same_v<CRC30_CDMA::type, uint32_t>, "");
static_assert(_is_same_v<CRC31_PHILIPS::type, uint32_t>, "");
static_assert(_is_same_v<CRC32_XFER::type, uint32_t>, "");
static_assert(_is_same_v<CRC40_GSM::type, uint64_t>, "");
static_assert(_is_same_v<CRC64_GO_ISO::type, uint64_t>, "");

//
// Reverse polynomials test
//
static_assert(CRC1::poly_rev == 0x1, "");
static_assert(CRC3_GSM::poly_rev == 0x6, "");
static_assert(CRC4_ITU::poly_rev == 0xc, "");
static_assert(CRC5_USB::poly_rev == 0x14, "");
static_assert(CRC5_EPC::poly_rev == 0x12, "");
static_assert(CRC5_ITU::poly_rev == 0x15, "");
static_assert(CRC6_ITU::poly_rev == 0x30, "");
static_assert(CRC6_CDMA2000_B::poly_rev == 0x38, "");
static_assert(CRC6_DARC::poly_rev == 0x26, "");
static_assert(CRC6_NR::poly_rev == 0x21, "");
static_assert(CRC6_CDMA2000_A::poly_rev == 0x39, "");
static_assert(CRC6_GSM::poly_rev == 0x3d, "");
static_assert(CRC7::poly_rev == 0x48, "");
static_assert(CRC7_UMTS::poly_rev == 0x51, "");
static_assert(CRC7_ROHC::poly_rev == 0x79, "");
// static_assert(CRC7_MVB::poly_rev == 0x53, "");
static_assert(CRC8::poly_rev == 0xe0, "");
static_assert(CRC8_EBU::poly_rev == 0xb8, "");
static_assert(CRC8_AUTOSAR::poly_rev == 0xf4, "");
static_assert(CRC8_MAXIM::poly_rev == 0x8c, "");
static_assert(CRC8_DARC::poly_rev == 0x9c, "");
static_assert(CRC8_GSM_B::poly_rev == 0x92, "");
static_assert(CRC8_CDMA2000::poly_rev == 0xd9, "");
static_assert(CRC8_DVB_S2::poly_rev == 0xab, "");
static_assert(CRC8_BLUETOOTH::poly_rev == 0xe5, "");
static_assert(CRC10_GSM::poly_rev == 0x2ba, "");
static_assert(CRC10::poly_rev == 0x331, "");
static_assert(CRC10_CDMA2000::poly_rev == 0x26f, "");
static_assert(CRC11_UMTS::poly_rev == 0x0706, "");
static_assert(CRC11::poly_rev == 0x50e, "");
static_assert(CRC11_NR::poly_rev == 0x423, "");
static_assert(CRC12_DECT::poly_rev == 0xf01, "");
static_assert(CRC12_GSM::poly_rev == 0x8cb, "");
static_assert(CRC12_CDMA2000::poly_rev == 0xc8f, "");
static_assert(CRC13_BBC::poly_rev == 0x15e7, "");
static_assert(CRC14_GSM::poly_rev == 0x2d01, "");
static_assert(CRC14_DARC::poly_rev == 0x2804, "");
static_assert(CRC15::poly_rev == 0x4cd1, "");
static_assert(CRC15_MPT1327::poly_rev == 0x540b, "");
static_assert(CRC16_DECT_R::poly_rev == 0x91a0, "");
static_assert(CRC16_NRSC5::poly_rev == 0xd010, "");
static_assert(CRC16_AUG_CCITT::poly_rev == 0x8408, "");
static_assert(CRC16_PROFIBUS::poly_rev == 0xf3b8, "");
// static_assert(CRC16_CHAKRAVARTY::poly_rev == 0xa8f4, "");
static_assert(CRC16_DNP::poly_rev == 0xa6bc, "");
static_assert(CRC16_M17::poly_rev == 0xac9a, "");
static_assert(CRC16_LJ1200::poly_rev == 0xc6f6, "");
static_assert(CRC16_OPENSAFETY_B::poly_rev == 0xdaae, "");
static_assert(CRC16_ARC::poly_rev == 0xa001, "");
static_assert(CRC16_T10_DIF::poly_rev == 0xedd1, "");
static_assert(CRC16_CDMA2000::poly_rev == 0xe613, "");
// static_assert(CRC16_ARINC::poly_rev == 0xd405, "");
static_assert(CRC16_TELEDISK::poly_rev == 0xe905, "");
static_assert(CRC17_CAN_FD::poly_rev == 0x1b42d, "");
static_assert(CRC21_CAN_FD::poly_rev == 0x132281, "");
static_assert(CRC24_BLE::poly_rev == 0xda6000, "");
static_assert(CRC24_INTERLAKEN::poly_rev == 0xc6d14c, "");
static_assert(CRC24_FLEXRAY_A::poly_rev == 0xd3b6ba, "");
static_assert(CRC24_LTE_B::poly_rev == 0xc60001, "");
static_assert(CRC24::poly_rev == 0xdf3261, "");
static_assert(CRC24_NR_C::poly_rev == 0xe88d4d, "");
static_assert(CRC30_CDMA::poly_rev == 0x38e74301, "");
static_assert(CRC31_PHILIPS::poly_rev == 0x76dc4190, "");
static_assert(CRC32_XFER::poly_rev == 0xf5000000, "");
static_assert(CRC32::poly_rev == 0xedb88320, "");
static_assert(CRC32_C::poly_rev == 0x82f63b78, "");
static_assert(CRC32_MEF::poly_rev == 0xeb31d82e, "");
// static_assert(CRC32_K2::poly_rev == 0x992c1a4c, "");
static_assert(CRC32_CDROM_EDC::poly_rev == 0xd8018001, "");
static_assert(CRC32_Q::poly_rev == 0xd5828281, "");
static_assert(CRC32_D::poly_rev == 0xd419cc15, "");
static_assert(CRC32_AUTOSAR::poly_rev == 0xc8df352f, "");
static_assert(CRC40_GSM::poly_rev == 0x9000412000, "");
static_assert(CRC64_GO_ISO::poly_rev == 0xd800000000000000, "");
static_assert(CRC64_MS::poly_rev == 0x92c64265d32139a4, "");
static_assert(CRC64::poly_rev == 0xc96c5795d7870f42, "");
static_assert(CRC64_REDIS::poly_rev == 0x95ac9329ac4bc9b5, "");

// compile-time CRC tester
template<typename Algo>
constexpr void test_crc()
{
    constexpr const uint8_t check_tab[] =
        {'1', '2', '3', '4', '5', '6', '7', '8', '9'};

    static_assert(
        Algo::_calc(check_tab, sizeof(check_tab), Algo::init_in) ==
        Algo::_calc_tab(check_tab, sizeof(check_tab), Algo::init_in),
        "Calculation coherency test failed");

    constexpr auto crc =
        Algo::_calc_tab(check_tab, sizeof(check_tab), Algo::init_in);
    static_assert(Algo::_final(crc) == Algo::check_val,
        "CRC check-value test failed");
}

//
// Function templates declaration forces compile-time CRC tests
//
// NOTE: The declarations forces a compiler to generate actual definitions
// of the declared functions, therefore have influence on the runtime output.
//
template void test_crc<CRC1>();
template void test_crc<CRC3_GSM>();
template void test_crc<CRC3_ROHC>();
template void test_crc<CRC4_ITU>();
template void test_crc<CRC4_INTERLAKEN>();
template void test_crc<CRC5_USB>();
template void test_crc<CRC5_EPC>();
template void test_crc<CRC5_ITU>();
template void test_crc<CRC6_ITU>();
template void test_crc<CRC6_CDMA2000_B>();
template void test_crc<CRC6_DARC>();
template void test_crc<CRC6_NR>();
template void test_crc<CRC6_CDMA2000_A>();
template void test_crc<CRC6_GSM>();
template void test_crc<CRC7>();
template void test_crc<CRC7_UMTS>();
template void test_crc<CRC7_ROHC>();
// template void test_crc<CRC7_MVB>();
template void test_crc<CRC8>();
template void test_crc<CRC8_HDLC>();
template void test_crc<CRC8_ITU>();
template void test_crc<CRC8_ROHC>();
template void test_crc<CRC8_EBU>();
template void test_crc<CRC8_GSM_A>();
template void test_crc<CRC8_HITAG>();
template void test_crc<CRC8_ICODE>();
template void test_crc<CRC8_MIFRAME_MAD>();
template void test_crc<CRC8_SAE_J1850>();
template void test_crc<CRC8_AUTOSAR>();
template void test_crc<CRC8_OPENSAFETY>();
template void test_crc<CRC8_MAXIM>();
template void test_crc<CRC8_NRSC5>();
template void test_crc<CRC8_DARC>();
template void test_crc<CRC8_GSM_B>();
template void test_crc<CRC8_CDMA2000>();
template void test_crc<CRC8_LTE>();
template void test_crc<CRC8_WCDMA>();
template void test_crc<CRC8_DVB_S2>();
template void test_crc<CRC8_BLUETOOTH>();
template void test_crc<CRC10_GSM>();
template void test_crc<CRC10>();
template void test_crc<CRC10_CDMA2000>();
template void test_crc<CRC11_UMTS>();
template void test_crc<CRC11>();
template void test_crc<CRC11_NR>();
template void test_crc<CRC12_DECT>();
template void test_crc<CRC12_UMTS>();
template void test_crc<CRC12_GSM>();
template void test_crc<CRC12_CDMA2000>();
template void test_crc<CRC13_BBC>();
template void test_crc<CRC14_GSM>();
template void test_crc<CRC14_DARC>();
template void test_crc<CRC15>();
template void test_crc<CRC15_MPT1327>();
template void test_crc<CRC16_DECT_R>();
template void test_crc<CRC16_DECT_X>();
template void test_crc<CRC16_NRSC5>();
template void test_crc<CRC16_AUG_CCITT>();
template void test_crc<CRC16_CCITT_FALSE>();
template void test_crc<CRC16_GENIBUS>();
template void test_crc<CRC16_GSM>();
template void test_crc<CRC16_ISO_IEC14443_3_A>();
template void test_crc<CRC16_KERMIT>();
template void test_crc<CRC16_MCRF4XX>();
template void test_crc<CRC16_RIELLO>();
template void test_crc<CRC16_TMS37157>();
template void test_crc<CRC16_X25>();
template void test_crc<CRC16_XMODEM>();
template void test_crc<CRC16_PROFIBUS>();
// template void test_crc<CRC16_CHAKRAVARTY>();
template void test_crc<CRC16_DNP>();
template void test_crc<CRC16_EN13757>();
template void test_crc<CRC16_M17>();
template void test_crc<CRC16_OPENSAFETY_A>();
template void test_crc<CRC16_LJ1200>();
template void test_crc<CRC16_OPENSAFETY_B>();
template void test_crc<CRC16_ARC>();
template void test_crc<CRC16_BUYPASS>();
template void test_crc<CRC16_CMS>();
template void test_crc<CRC16_DDS110>();
template void test_crc<CRC16_MAXIM>();
template void test_crc<CRC16_MODBUS>();
template void test_crc<CRC16_USB>();
template void test_crc<CRC16_T10_DIF>();
template void test_crc<CRC16_CDMA2000>();
// template void test_crc<CRC16_ARINC>();
template void test_crc<CRC16_TELEDISK>();
template void test_crc<CRC17_CAN_FD>();
template void test_crc<CRC21_CAN_FD>();
template void test_crc<CRC24_BLE>();
template void test_crc<CRC24_INTERLAKEN>();
template void test_crc<CRC24_FLEXRAY_A>();
template void test_crc<CRC24_FLEXRAY_B>();
template void test_crc<CRC24_LTE_B>();
template void test_crc<CRC24_OS9>();
template void test_crc<CRC24>();
template void test_crc<CRC24_LTE_A>();
template void test_crc<CRC24_NR_C>();
template void test_crc<CRC30_CDMA>();
template void test_crc<CRC31_PHILIPS>();
template void test_crc<CRC32_XFER>();
template void test_crc<CRC32>();
template void test_crc<CRC32_BZIP2>();
template void test_crc<CRC32_JAMCRC>();
template void test_crc<CRC32_MPEG2>();
template void test_crc<CRC32_POSIX>();
template void test_crc<CRC32_C>();
// template void test_crc<CRC32_K2>();
template void test_crc<CRC32_MEF>();
template void test_crc<CRC32_CDROM_EDC>();
template void test_crc<CRC32_Q>();
template void test_crc<CRC32_D>();
template void test_crc<CRC32_AUTOSAR>();
template void test_crc<CRC40_GSM>();
template void test_crc<CRC64_GO_ISO>();
template void test_crc<CRC64_MS>();
template void test_crc<CRC64>();
template void test_crc<CRC64_WE>();
template void test_crc<CRC64_XZ>();
template void test_crc<CRC64_REDIS>();

// compile-time CRC runtime objects size tester
template<typename Algo>
constexpr void test_rt_sizes()
{
    static_assert(sizeof(typename Algo::engine) == sizeof(typename Algo::type));

    if constexpr (Algo::tab_type == crc_tab_e::TAB256) {
        static_assert(sizeof(Algo::lookup) == 256 *sizeof(typename Algo::type));
    } else {
        static_assert(sizeof(Algo::lookup) == 32 * sizeof(typename Algo::type));
    }
}

//
// Force compile-time runtime objects size test
//
template void test_rt_sizes<CRC1>();
template void test_rt_sizes<CRC3_GSM>();
template void test_rt_sizes<CRC4_ITU>();
template void test_rt_sizes<CRC5_USB>();
template void test_rt_sizes<CRC6_ITU>();
template void test_rt_sizes<CRC7>();
template void test_rt_sizes<CRC8>();
template void test_rt_sizes<CRC10_GSM>();
template void test_rt_sizes<CRC11_UMTS>();
template void test_rt_sizes<CRC12_DECT>();
template void test_rt_sizes<CRC13_BBC>();
template void test_rt_sizes<CRC14_GSM>();
template void test_rt_sizes<CRC15>();
template void test_rt_sizes<CRC16_DECT_R>();
template void test_rt_sizes<CRC17_CAN_FD>();
template void test_rt_sizes<CRC21_CAN_FD>();
template void test_rt_sizes<CRC24_BLE>();
template void test_rt_sizes<CRC30_CDMA>();
template void test_rt_sizes<CRC31_PHILIPS>();
template void test_rt_sizes<CRC32_XFER>();
template void test_rt_sizes<CRC40_GSM>();
template void test_rt_sizes<CRC64_GO_ISO>();

} // unnamed namespace
