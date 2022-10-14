/*
 * Copyright (c) 2022 Piotr Stolarz
 * CRaC: C++ Cyclic Redundancy Check (CRC) template library.
 *
 * Distributed under the 2-clause BSD License (the License)
 * see accompanying file LICENSE for details.
 *
 * This software is distributed WITHOUT ANY WARRANTY; without even the
 * implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the License for more information.
 */

/*
 * Compile time tester. To be included from the library header only.
 */

//
// CRC output types test
//
static_assert(std::is_same<CRC1::algo_type::type, uint8_t>::value, "");
static_assert(std::is_same<CRC3_GSM::algo_type::type, uint8_t>::value, "");
static_assert(std::is_same<CRC4_ITU::algo_type::type, uint8_t>::value, "");
static_assert(std::is_same<CRC5_USB::algo_type::type, uint8_t>::value, "");
static_assert(std::is_same<CRC6_ITU::algo_type::type, uint8_t>::value, "");
static_assert(std::is_same<CRC7::algo_type::type, uint8_t>::value, "");
static_assert(std::is_same<CRC8::algo_type::type, uint8_t>::value, "");
static_assert(std::is_same<CRC10_GSM::algo_type::type, uint16_t>::value, "");
static_assert(std::is_same<CRC11_UMTS::algo_type::type, uint16_t>::value, "");
static_assert(std::is_same<CRC12_DECT::algo_type::type, uint16_t>::value, "");
static_assert(std::is_same<CRC13_BBC::algo_type::type, uint16_t>::value, "");
static_assert(std::is_same<CRC14_GSM::algo_type::type, uint16_t>::value, "");
static_assert(std::is_same<CRC15_CAN::algo_type::type, uint16_t>::value, "");
static_assert(std::is_same<CRC16_DECT_R::algo_type::type, uint16_t>::value, "");
static_assert(std::is_same<CRC17_CAN::algo_type::type, uint32_t>::value, "");
static_assert(std::is_same<CRC21_CAN::algo_type::type, uint32_t>::value, "");
static_assert(std::is_same<CRC24_BLE::algo_type::type, uint32_t>::value, "");
static_assert(std::is_same<CRC30_CDMA::algo_type::type, uint32_t>::value, "");
static_assert(std::is_same<CRC31_PHILIPS::algo_type::type, uint32_t>::value, "");
static_assert(std::is_same<CRC32_XFER::algo_type::type, uint32_t>::value, "");
static_assert(std::is_same<CRC40_GSM::algo_type::type, uint64_t>::value, "");
static_assert(std::is_same<CRC64_ISO::algo_type::type, uint64_t>::value, "");

//
// Reverse polynomials test
//
static_assert(CRC1::algo_type::poly_rev == 0x1, "");
static_assert(CRC3_GSM::algo_type::poly_rev == 0x6, "");
static_assert(CRC4_ITU::algo_type::poly_rev == 0xc, "");
static_assert(CRC5_USB::algo_type::poly_rev == 0x14, "");
static_assert(CRC5_EPC::algo_type::poly_rev == 0x12, "");
static_assert(CRC5_ITU::algo_type::poly_rev == 0x15, "");
static_assert(CRC6_ITU::algo_type::poly_rev == 0x30, "");
static_assert(CRC6_CDMA2000_B::algo_type::poly_rev == 0x38, "");
static_assert(CRC6_DARC::algo_type::poly_rev == 0x26, "");
static_assert(CRC6_NR::algo_type::poly_rev == 0x21, "");
static_assert(CRC6_CDMA2000_A::algo_type::poly_rev == 0x39, "");
static_assert(CRC6_GSM::algo_type::poly_rev == 0x3d, "");
static_assert(CRC7::algo_type::poly_rev == 0x48, "");
static_assert(CRC7_UMTS::algo_type::poly_rev == 0x51, "");
static_assert(CRC7_ROHC::algo_type::poly_rev == 0x79, "");
// static_assert(CRC7_MVB::algo_type::poly_rev == 0x53, "");
static_assert(CRC8::algo_type::poly_rev == 0xe0, "");
static_assert(CRC8_EBU::algo_type::poly_rev == 0xb8, "");
static_assert(CRC8_AUTOSAR::algo_type::poly_rev == 0xf4, "");
static_assert(CRC8_MAXIM::algo_type::poly_rev == 0x8c, "");
static_assert(CRC8_DARC::algo_type::poly_rev == 0x9c, "");
static_assert(CRC8_GSM_B::algo_type::poly_rev == 0x92, "");
static_assert(CRC8_CDMA2000::algo_type::poly_rev == 0xd9, "");
static_assert(CRC8_DVB_S2::algo_type::poly_rev == 0xab, "");
static_assert(CRC8_BLUETOOTH::algo_type::poly_rev == 0xe5, "");
static_assert(CRC10_GSM::algo_type::poly_rev == 0x2ba, "");
static_assert(CRC10::algo_type::poly_rev == 0x331, "");
static_assert(CRC10_CDMA2000::algo_type::poly_rev == 0x26f, "");
static_assert(CRC11_UMTS::algo_type::poly_rev == 0x0706, "");
static_assert(CRC11::algo_type::poly_rev == 0x50e, "");
static_assert(CRC11_NR::algo_type::poly_rev == 0x423, "");
static_assert(CRC12_DECT::algo_type::poly_rev == 0xf01, "");
static_assert(CRC12_GSM::algo_type::poly_rev == 0x8cb, "");
static_assert(CRC12_CDMA2000::algo_type::poly_rev == 0xc8f, "");
static_assert(CRC13_BBC::algo_type::poly_rev == 0x15e7, "");
static_assert(CRC14_GSM::algo_type::poly_rev == 0x2d01, "");
static_assert(CRC14_DARC::algo_type::poly_rev == 0x2804, "");
static_assert(CRC15_CAN::algo_type::poly_rev == 0x4cd1, "");
static_assert(CRC15_MPT1327::algo_type::poly_rev == 0x540b, "");
static_assert(CRC16_DECT_R::algo_type::poly_rev == 0x91a0, "");
static_assert(CRC16_NRSC5::algo_type::poly_rev == 0xd010, "");
static_assert(CRC16_A::algo_type::poly_rev == 0x8408, "");
static_assert(CRC16_PROFIBUS::algo_type::poly_rev == 0xf3b8, "");
// static_assert(CRC16_CHAKRAVARTY::algo_type::poly_rev == 0xa8f4, "");
static_assert(CRC16_DNP::algo_type::poly_rev == 0xa6bc, "");
static_assert(CRC16_M17::algo_type::poly_rev == 0xac9a, "");
static_assert(CRC16_LJ1200::algo_type::poly_rev == 0xc6f6, "");
static_assert(CRC16_OPENSAFETY_B::algo_type::poly_rev == 0xdaae, "");
static_assert(CRC16_ARC::algo_type::poly_rev == 0xa001, "");
static_assert(CRC16_T10_DIF::algo_type::poly_rev == 0xedd1, "");
static_assert(CRC16_CDMA2000::algo_type::poly_rev == 0xe613, "");
// static_assert(CRC16_ARINC::algo_type::poly_rev == 0xd405, "");
static_assert(CRC16_TELEDISK::algo_type::poly_rev == 0xe905, "");
static_assert(CRC17_CAN::algo_type::poly_rev == 0x1b42d, "");
static_assert(CRC21_CAN::algo_type::poly_rev == 0x132281, "");
static_assert(CRC24_BLE::algo_type::poly_rev == 0xda6000, "");
static_assert(CRC24_INTERLAKEN::algo_type::poly_rev == 0xc6d14c, "");
static_assert(CRC24_FLEXRAY_A::algo_type::poly_rev == 0xd3b6ba, "");
static_assert(CRC24_LTE_B::algo_type::poly_rev == 0xc60001, "");
static_assert(CRC24::algo_type::poly_rev == 0xdf3261, "");
static_assert(CRC24_NR_C::algo_type::poly_rev == 0xe88d4d, "");
static_assert(CRC30_CDMA::algo_type::poly_rev == 0x38e74301, "");
static_assert(CRC31_PHILIPS::algo_type::poly_rev == 0x76dc4190, "");
static_assert(CRC32_XFER::algo_type::poly_rev == 0xf5000000, "");
static_assert(CRC32::algo_type::poly_rev == 0xedb88320, "");
static_assert(CRC32_C::algo_type::poly_rev == 0x82f63b78, "");
static_assert(CRC32_K::algo_type::poly_rev == 0xeb31d82e, "");
// static_assert(CRC32_K2::algo_type::poly_rev == 0x992c1a4c, "");
static_assert(CRC32_CDROM_EDC::algo_type::poly_rev == 0xd8018001, "");
static_assert(CRC32_Q::algo_type::poly_rev == 0xd5828281, "");
static_assert(CRC32_D::algo_type::poly_rev == 0xd419cc15, "");
static_assert(CRC32_AUTOSAR::algo_type::poly_rev == 0xc8df352f, "");
static_assert(CRC40_GSM::algo_type::poly_rev == 0x9000412000, "");
static_assert(CRC64_ISO::algo_type::poly_rev == 0xd800000000000000, "");
static_assert(CRC64_MS::algo_type::poly_rev == 0x92c64265d32139a4, "");
static_assert(CRC64_ECMA::algo_type::poly_rev == 0xc96c5795d7870f42, "");
static_assert(CRC64_REDIS::algo_type::poly_rev == 0x95ac9329ac4bc9b5, "");

// compile time CRC tester
template<typename AlgoDesc>
constexpr void test_crc()
{
    constexpr const uint8_t check_tab[] =
        {'1', '2', '3', '4', '5', '6', '7', '8', '9'};

    using algo_type = typename AlgoDesc::algo_type;
    constexpr auto algo = AlgoDesc::get_algo();

    static_assert(
        algo_type::_calc(check_tab, sizeof(check_tab), algo.init_in) ==
        algo_type::_calc_tab(check_tab, sizeof(check_tab), algo.init_in),
        "Calculation coherency test failed");

    constexpr auto crc = algo._calc(check_tab, sizeof(check_tab), algo.init_in);
    static_assert(algo._final(crc) == algo.check_val,
        "CRC check-value test failed");
}

//
// Function templates declaration forces compile time CRC tests
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
template void test_crc<CRC8_MIFRAME>();
template void test_crc<CRC8_SAE_J1850>();
template void test_crc<CRC8_AUTOSAR>();
template void test_crc<CRC8_OPENSAFETY>();
template void test_crc<CRC8_MAXIM>();
template void test_crc<CRC8_NRSC_5>();
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
template void test_crc<CRC15_CAN>();
template void test_crc<CRC15_MPT1327>();
template void test_crc<CRC16_DECT_R>();
template void test_crc<CRC16_DECT_X>();
template void test_crc<CRC16_NRSC5>();
template void test_crc<CRC16_A>();
template void test_crc<CRC16_AUG_CCITT>();
template void test_crc<CRC16_GENIBUS>();
template void test_crc<CRC16_GSM>();
template void test_crc<CRC16_IBM_3740>();
template void test_crc<CRC16_IBM_SDLC>();
template void test_crc<CRC16_KERMIT>();
template void test_crc<CRC16_MCRF4XX>();
template void test_crc<CRC16_RIELLO>();
template void test_crc<CRC16_TMS37157>();
template void test_crc<CRC16_XMODEM>();
template void test_crc<CRC16_PROFIBUS>();
// template void test_crc<CRC16_CHAKRAVARTY>();
template void test_crc<CRC16_DNP>();
template void test_crc<CRC16_EN_13757>();
template void test_crc<CRC16_M17>();
template void test_crc<CRC16_OPENSAFETY_A>();
template void test_crc<CRC16_LJ1200>();
template void test_crc<CRC16_OPENSAFETY_B>();
template void test_crc<CRC16_ARC>();
template void test_crc<CRC16_BUYPASS>();
template void test_crc<CRC16_CMS>();
template void test_crc<CRC16_DDS_110>();
template void test_crc<CRC16_MAXIM>();
template void test_crc<CRC16_MODBUS>();
template void test_crc<CRC16_USB>();
template void test_crc<CRC16_T10_DIF>();
template void test_crc<CRC16_CDMA2000>();
// template void test_crc<CRC16_ARINC>();
template void test_crc<CRC16_TELEDISK>();
template void test_crc<CRC17_CAN>();
template void test_crc<CRC21_CAN>();
template void test_crc<CRC24_BLE>();
template void test_crc<CRC24_INTERLAKEN>();
template void test_crc<CRC24_FLEXRAY_A>();
template void test_crc<CRC24_FLEXRAY_B>();
template void test_crc<CRC24_LTE_B>();
template void test_crc<CRC24_OS_9>();
template void test_crc<CRC24>();
template void test_crc<CRC24_LTE_A>();
template void test_crc<CRC24_NR_C>();
template void test_crc<CRC30_CDMA>();
template void test_crc<CRC31_PHILIPS>();
template void test_crc<CRC32_XFER>();
template void test_crc<CRC32>();
template void test_crc<CRC32_BZIP2>();
template void test_crc<CRC32_JAMCRC>();
template void test_crc<CRC32_MPEG_2>();
template void test_crc<CRC32_POSIX>();
template void test_crc<CRC32_C>();
template void test_crc<CRC32_K>();
// template void test_crc<CRC32_K2>();
template void test_crc<CRC32_CDROM_EDC>();
template void test_crc<CRC32_Q>();
template void test_crc<CRC32_D>();
template void test_crc<CRC32_AUTOSAR>();
template void test_crc<CRC40_GSM>();
template void test_crc<CRC64_ISO>();
template void test_crc<CRC64_MS>();
template void test_crc<CRC64_ECMA>();
template void test_crc<CRC64_WE>();
template void test_crc<CRC64_XZ>();
template void test_crc<CRC64_REDIS>();
