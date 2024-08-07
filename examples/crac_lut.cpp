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
/*
 * The example prints out internal 32-LUT (2*16 elements) lookup table used
 * for fast CRC calculation.
 */

#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include "crac.h"

using CRC = crac::CRC32;

//
// Need to create CRC_lut class inheriting from CRC to get access to its
// lookup table, which is part of its protected, low level interface.
//
struct CRC_lut: CRC
{
    constexpr static CRC::type get(uint8_t b) {
        return CRC::lut[b];
    }
};

//
// Print out table of arbitrary integers to stdout.
// NOTE: table passed by a reference to avoid decaying to T*
//
template<typename T, size_t N>
static void print_tab(const T (&tab)[N])
{
    static const char *HEX = "0123456789abcdef";

    using namespace crac;

    size_t i = 0;
    while (i < N)
    {
        for(int n = (int)(2 * sizeof(T) - 1); n >= 0; n--) {
            fputc(HEX[(tab[i] >> (n << 2)) & 0xf], stdout);
        }
        if (++i % 8) {
            fputc(' ', stdout);
        } else {
            fputc('\n', stdout);
        }
    }
    if (i % 8) {
        fputc('\n', stdout);
    }
}

int main(int argc, const char *argv[])
{
    CRC::type tab_l[16];
    CRC::type tab_h[16];

    // Get L/H tables.
    // NOTE: it's not important here what type of LUT is used internally.
    for (uint8_t i = 0; i < 16; i++) {
        tab_l[i] = CRC_lut::get(i);
        tab_h[i] = CRC_lut::get(i << 4);
    }

    // check correctness of the above tables
    for (int i = 0; i < 256; i++) {
        assert(CRC_lut::get(i) == (tab_l[i & 0xf] ^ tab_h[i >> 4]));
    }

    printf("tab_l\n"); print_tab(tab_l);
    printf("tab_h\n"); print_tab(tab_h);

    return 0;
}
