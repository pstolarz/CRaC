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

#include <cassert>

// define to use 256-elements lookup table
//#define CRAC_TAB256
#include "crac.h"

int main(int argc, const char *argv[])
{
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

    return 0;
}
