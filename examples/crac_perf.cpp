/*
 * Copyright (c) 2022,2024 Piotr Stolarz
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
 * Performance tests.
 * ITERS_NUM iteration of CRC calculation over table of TAB_SIZE bytes.
 */

#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include "crac.h"

using namespace crac;
using CRC = CRC32;

static constexpr unsigned ITERS_NUM = 1'000'000;
static constexpr unsigned TAB_SIZE  = 256;

static inline time_t get_ts()
{
    timeval tv;
    gettimeofday(&tv, NULL);
    return (uint64_t)tv.tv_sec * 1000 + tv.tv_usec / 1000;
}

template<typename Crc>
static void cal_perf(const uint8_t in[TAB_SIZE])
{
    typename Crc::type crc;

    time_t start = get_ts();
    for (unsigned i = 0; i < ITERS_NUM; i++) {
        crc = Crc::calc(in, TAB_SIZE);
    }
    time_t stop = get_ts();

    printf("CRC[%d]: 0x%08x, time: %f ms\n",
        (Crc::tab_type == crc_tab_e::TAB256 ? 256 :
             (Crc::tab_type == crc_tab_e::TAB32 ? 32 : 16)),
        crc, (stop - start) / 1000.0);
}

int main(int argc, const char *argv[])
{
    using CRC_TAB256 = crc_algo<CRC::bits, CRC::poly,
          CRC::refl_in, CRC::refl_out,
          CRC::init_val, CRC::xor_out,
          no_check_val, crc_tab_e::TAB256>;

    using CRC_TAB32 = crc_algo<CRC::bits, CRC::poly,
          CRC::refl_in, CRC::refl_out,
          CRC::init_val, CRC::xor_out,
          no_check_val, crc_tab_e::TAB32>;

    using CRC_TAB16 = crc_algo<CRC::bits, CRC::poly,
          CRC::refl_in, CRC::refl_out,
          CRC::init_val, CRC::xor_out,
          no_check_val, crc_tab_e::TAB16>;

    // input table
    uint8_t in[TAB_SIZE];
    for (size_t i = 0; i < sizeof(in); i++) {
        in[i] = i;
    }

    cal_perf<CRC_TAB256>(in);
    cal_perf<CRC_TAB32>(in);
    cal_perf<CRC_TAB16>(in);

    return 0;
}
