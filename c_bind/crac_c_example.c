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
 * The example presents usage of CRaC library from C-language code.
 */

#include <stdio.h>
#include "crac_c.h"

int main(void)
{
    uint8_t in[0x100];
    for (size_t i = 0; i < sizeof(in); i++)
        in[i] = i;

    // single step mode
    uint8_t crc8 = crac_calc_CRC8(in, sizeof(in));
    printf("CRC-8: 0x%02x\n", crc8);

    // block mode
    uint16_t crc16 = crac_init_val_CRC16();
    crc16 = crac_update_CRC16(in, sizeof(in) / 2, crc16);
    crc16 = crac_update_CRC16(in + sizeof(in) / 2, sizeof(in) / 2, crc16);
    printf("CRC-16: 0x%04x\n", crac_final_CRC16(crc16));

    // block bit mode
    uint32_t crc32 = crac_init_val_CRC32();
    for (size_t i = 0; i < sizeof(in); i++) {
        crc32 = crac_update_bits_CRC32(in[i], 8, crc32);
    }
    printf("CRC-32: 0x%08x\n", crac_final_CRC32(crc32));

    return 0;
}
