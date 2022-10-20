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

#include <cassert>

// use 256 lookup table
//#define CRAC_TAB256
#include "crac.h"

int main(int argc, const char *argv[])
{
    using namespace crac;

    constexpr const uint8_t check_str[] = "123456789";
    constexpr const size_t len = sizeof(check_str) - 1;

    // compile-time CRC calculation
    static_assert(
        CRC32::get_engine().calc(check_str, len) ==
        CRC32::check_val, "Invalid CRC32 check-val");

    // runtime calculation: single step mode
    auto crc32 = CRC32::get_engine();
    auto res = crc32.calc(check_str, len);

    // runtime calculation: block mode
    crc32.update(check_str, 3);
    crc32.update(check_str + 3, 3);
    crc32.update(check_str + 6, len - 6);
    assert(res == crc32.final());

    return 0;
}
