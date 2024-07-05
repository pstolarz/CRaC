/*
 * Copyright (c) 2024 Piotr Stolarz
 * CRaC: C++17 Cyclic Redundancy Check (CRC) template library.
 *
 * Distributed under the 2-clause BSD License (the License)
 * see accompanying file LICENSE for details.
 *
 * This software is distributed WITHOUT ANY WARRANTY; without even the
 * implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the License for more information.
 */

#include <assert.h>
#include "crac.h"

int main(int argc, const char *argv[])
{
    using namespace crac;

    using CRC = crc_algo<
        CRC32::bits,
        CRC32::poly,
        false,          // direct mode
        false,          // result CRC is not reverted
        0, 0>;

    using CRC_refl = crc_algo<
        CRC::bits,
        CRC::poly,
        true,           // reflected mode
        false,          // result CRC is reverted
        0, 0>;

    // input bits
    const uint64_t in = 0x0123456789abcdef;

    // `n_bits' denotes number of bits to read (starting from LSB)
    for (unsigned n_bits = 0; n_bits <= (8 * sizeof(in)); n_bits++)
    {
        auto crc = CRC::calc_bits(in, n_bits);

        // need to revert input bits to treat MSB as LSB for `CRC_refl' engine
        auto crc_refl = CRC_refl::calc_bits(bits_rev(in, n_bits), n_bits);

        // both CRCs must match
        assert(crc == crc_refl);
    }

    return 0;
}
