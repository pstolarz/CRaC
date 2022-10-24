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

#include <time.h>
#include <sys/time.h>
#include <cstdio>

#define CRAC_TAB256
#include "crac.h"

static inline time_t get_ts()
{
    timeval tv;
    gettimeofday(&tv, NULL);
    return (uint64_t)tv.tv_sec * 1000 + tv.tv_usec / 1000;
}

int main(int argc, const char *argv[])
{
    using namespace crac;

    // input tab
    uint8_t in[256];
    for (size_t i = 0; i < sizeof(in); i++) in[i] = i;

    CRC32::type crc;
    time_t start = get_ts();

    for (unsigned i = 0; i < 1'000'000; i++) {
        crc = CRC32::calc(in, sizeof(in));
    }
    time_t stop = get_ts();

    printf("CRC: 0x%08x, time: %f ms\n", crc, (stop - start) / 1000.0);

    return 0;
}
