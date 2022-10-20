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

#ifndef __CRAC_H__
#define __CRAC_H__

#include <cstdint>
#include <cstddef>      // size_t
#include <type_traits>  // make_unsigned, is_same (tests only)

// rid off C++17 compile-time-if statement errors for C++14 compiler
#if __cplusplus >= 201703L
# define __CONSTEXPR constexpr
#else
# define __CONSTEXPR
#endif

namespace crac {

/// Types of CRC lookup tables
enum class crc_tab_e {
    TAB16LH = 0,
    TAB256
};

namespace {

#ifdef CRAC_TAB256
constexpr static crc_tab_e def_tab_type = crc_tab_e::TAB256;
#else
constexpr static crc_tab_e def_tab_type = crc_tab_e::TAB16LH;
#endif

// CRC lookup table
template<typename Algo,
    bool ReflIn = Algo::refl_in, crc_tab_e TabType = Algo::tab_type>
struct crc_tab;

// reflected-input, 256 elements table
template<typename Algo>
struct crc_tab<Algo, true, crc_tab_e::TAB256>
{
    constexpr crc_tab()
    {
        uint8_t i = 0;
        do {
            _tab[i] = Algo::_calc(&i, 1, 0);
        } while (++i);
    }

    constexpr inline typename Algo::type tab(uint8_t in) const {
        return _tab[in];
    }

private:
    typename Algo::type _tab[256] = {};
};

// direct-input, 256 elements table
template<typename Algo>
struct crc_tab<Algo, false, crc_tab_e::TAB256>
{
    constexpr crc_tab()
    {
        uint8_t i = 0;
        do {
            _tab[i] = Algo::_calc(&i, 1, 0);
            if __CONSTEXPR (Algo::bits < 8) {
                _tab[i] <<= (8 - Algo::bits);
            }
        } while (++i);
    }

    constexpr inline typename Algo::type tab(uint8_t in) const {
        return _tab[in];
    }

private:
    typename Algo::type _tab[256] = {};
};

// reflected-input, 2*16 elements table
template<typename Algo>
struct crc_tab<Algo, true, crc_tab_e::TAB16LH>
{
    constexpr crc_tab()
    {
        for (uint8_t i = 0; i < 16; i++) {
            _tab_l[i] = Algo::_calc(&i, 1, 0);

            uint8_t ih = i << 4;
            _tab_h[i] = Algo::_calc(&ih, 1, 0);
        }
    }

    constexpr inline typename Algo::type tab(uint8_t in) const {
        return _tab_l[in & 0xf] ^ _tab_h[in >> 4];
    }

private:
    typename Algo::type _tab_l[16] = {};
    typename Algo::type _tab_h[16] = {};
};

// direct-input, 2*16 elements table
template<typename Algo>
struct crc_tab<Algo, false, crc_tab_e::TAB16LH>
{
    constexpr crc_tab()
    {
        for (uint8_t i = 0; i < 16; i++) {
            _tab_l[i] = Algo::_calc(&i, 1, 0);
            if __CONSTEXPR (Algo::bits < 8) {
                _tab_l[i] <<= (8 - Algo::bits);
            }

            uint8_t ih = i << 4;
            _tab_h[i] = Algo::_calc(&ih, 1, 0);
            if __CONSTEXPR (Algo::bits < 8) {
                _tab_h[i] <<= (8 - Algo::bits);
            }
        }
    }

    constexpr inline typename Algo::type tab(uint8_t in) const {
        return _tab_l[in & 0xf] ^ _tab_h[in >> 4];
    }

private:
    typename Algo::type _tab_l[16] = {};
    typename Algo::type _tab_h[16] = {};
};

constexpr static unsigned pwr2_ceil(unsigned v)
{
    for (unsigned p2 = 8; p2; p2 <<= 1) {
        if (v <= p2) return p2;
    }
    // will fail subsequently
    return 0;
}

// CRC type detector template
template<unsigned U> struct pwr2;
template<> struct pwr2<8> { using type = uint8_t; };
template<> struct pwr2<16> { using type = uint16_t; };
template<> struct pwr2<32> { using type = uint32_t; };
template<> struct pwr2<64> { using type = uint64_t; };
template<unsigned U> using pwr2_t = typename pwr2<U>::type;

constexpr static uint8_t rev16_tab[] = {
    0x0, 0x8, 0x4, 0xc, 0x2, 0xa, 0x6, 0xe,
    0x1, 0x9, 0x5, 0xd, 0x3, 0xb, 0x7, 0xf
};

} // unnamed namespace

/// Bits reversal (helper routine).
template<typename T>
constexpr inline T bits_rev(T in, unsigned bits = 8 * sizeof(T))
{
    typename std::make_unsigned_t<T> out = 0;

    for (; bits > 4; bits -= 4) {
        out |= rev16_tab[in & 0xf];
        in >>= 4; out <<= 4;
    }
    return (out | rev16_tab[in & 0xf]) >> (4 - bits);
}

/**
 * CRC algorithm.
 *
 * The following template parameters constitute compile-time CRC algorithm
 * definition:
 *
 * @param Bits CRC size in bits.
 * @param Poly CRC polynomial in direct (non-reflected) form.
 * @param ReflIn If @c true the CRC works in reflected-input mode (least
 *     significant bits of input bytes corresponds to most significant poly
 *     coefficients), if @false in direct-input mode.
 * @param TabType Type of CRC lookup table.
 *
 * @note The parameters uniquely define CRC algorithm lookup table, calculated
 *     at the compile time and assigned to the algorithm on the class-level
 *     (static) context.
 */
template<unsigned Bits, uint64_t Poly, bool ReflIn,
    crc_tab_e TabType = def_tab_type>
struct crc_algo;

/**
 * @c crc_algo template in reflected-input (LSB) mode specialization.
 */
template<unsigned Bits, uint64_t Poly, crc_tab_e TabType>
struct crc_algo<Bits, Poly, true, TabType>
{
    static_assert(Bits >= 1 && Bits <= 64, "Invalid CRC size");

    /// CRC algorithm bits size specification
    constexpr static unsigned bits = Bits;
    /// CRC result type
    using type = pwr2_t<pwr2_ceil(bits)>;
    /// CRC value mask
    constexpr static type mask =
        (type)(bits < 64 ? ((uint64_t)1 << bits) - 1 : -1);
    /// Polynomial associated with the CRC algorithm
    constexpr static type poly = Poly;
    /// Polynomial associated with the CRC algorithm (reverse order)
    constexpr static type poly_rev = bits_rev(Poly, bits);
    /// The template specialization defines reflected-input algorithms
    constexpr static bool refl_in = true;
    /// Type of CRC lookup table used
    constexpr static crc_tab_e tab_type = TabType;

    /**
     * Calculate CRC for given input bytes - slow version (direct calculation
     * basing on mathematical definition).
     *
     * @note Don't use this version unless for *very specific* use cases.
     *    The routine is used at the compile time to generate internal lookup
     *    table.
     */
    constexpr static type _calc(const uint8_t *in, size_t len, type crc_in)
    {
        type crc = crc_in;

        while (len--) {
            crc ^= *in++;
            for (int i = 8; i; i--) {
                crc = (crc & 1 ? poly_rev : 0) ^ (crc >> 1);
            }
        }
        return crc;
    }

    // generate lookup table at the compile time
    constexpr static crc_tab<crc_algo> lookup{};

    /**
     * Calculate CRC for given input bytes - fast version (basing on the
     * CRC lookup table).
     *
     * @note This is "plumbing" routine devoted for specific use-cases.
     *     See @ref crc_engine::calc() for more usable variant.
     */
    constexpr inline static type _calc_tab(
        const uint8_t *in, size_t len, type crc_in)
    {
        type crc = crc_in;

        while (len--) {
            crc = crc ^ *in++;
            if __CONSTEXPR (bits <= 8) {
                crc = lookup.tab(crc);
            } else {
                crc = (crc >> 8) ^ lookup.tab(crc);
            }
        }
        return crc;
    }

    /**
     * Calculate final CRC value for given @c crc.
     *
     * @note This is "plumbing" routine devoted for specific use-cases.
     *     See @ref crc_engine::final() for more usable variant.
     */
    constexpr inline type _final(type crc) const
    {
        if (!refl_out) {
            crc = bits_rev(crc, bits);
        }
        return crc ^ xor_out;
    }

    /**
     * Create CRC algorithm instance by associating it with specific
     * runtime parameters. @c crc_algo instance serves as immutable object
     * uniquely defining the underlying algorithm.
     *
     * @param refl_out If @c true the CRC works in reflected-output mode,
     *     if @false in direct-output mode.
     * @param init_in Initial CRC input value. Note the value is inverted
     *     for reflected-input CRC algorithms. See @ref bits_rev().
     * @param xor_out Value used to XOR final CRC value.
     * @param check_val CRC check value (CRC computed on "123456789" UTF-8
     *     string w/o trailing null-terminator).
     */
    constexpr crc_algo(
        bool refl_out, type init_in, type xor_out, type check_val):
        refl_out(refl_out),
        init_in(bits_rev(init_in, bits)),
        xor_out(xor_out & mask),
        check_val(check_val)
    {}

    constexpr crc_algo(const crc_algo&) = default;

    // Runtime parameters directly accessible in read-only mode.
    // They may be reduced to compile-time constants by a compiler.
    const bool refl_out;
    const type init_in;
    const type xor_out;
    const type check_val;
};

/**
 * @c crc_algo in direct-input (MSB) mode specialization.
 */
template<unsigned Bits, uint64_t Poly, crc_tab_e TabType>
struct crc_algo<Bits, Poly, false, TabType>
{
    static_assert(Bits >= 1 && Bits <= 64, "Invalid CRC size");

    /// CRC algorithm bits size specification
    constexpr static unsigned bits = Bits;
    /// CRC result type
    using type = pwr2_t<pwr2_ceil(bits)>;
    /// CRC value mask
    constexpr static type mask =
        (type)(bits < 64 ? ((uint64_t)1 << bits) - 1 : -1);
    /// Polynomial associated with the CRC algorithm
    constexpr static type poly = Poly;
    /// Polynomial associated with the CRC algorithm (reverse order)
    constexpr static type poly_rev = bits_rev(Poly, bits);
    /// The template specialization defines direct-input algorithms
    constexpr static bool refl_in = false;
    /// Type of CRC lookup table used
    constexpr static crc_tab_e tab_type = TabType;

    /**
     * See @c _calc() for reflected-input mode specialization.
     *
     * @note Don't use this version unless for *very specific* use cases.
     *    The routine is used at the compile time to generate internal lookup
     *    table.
     */
    constexpr static type _calc(const uint8_t *in, size_t len, type crc_in)
    {
        type crc = crc_in;
        if __CONSTEXPR (bits < 8) {
            crc <<= (8 - bits);
        }

        while (len--) {
            if __CONSTEXPR (bits <= 8) {
                crc ^= *in++;
            } else {
                crc ^= (type)*in++ << (bits - 8);
            }
            for (int i = 8; i; i--) {
                if __CONSTEXPR (bits < 8) {
                    crc = (crc & 0x80 ? poly << (8 - bits) : 0) ^ (crc << 1);
                } else {
                    crc = (crc & ((type)1 << (bits - 1)) ?  poly : 0) ^ (crc << 1);
                }
            }
        }

        if __CONSTEXPR (bits < 8) {
            return crc >> (8 - bits);
        } else {
            return crc & mask;
        }
    }

    // generate lookup table at the compile time
    constexpr static crc_tab<crc_algo> lookup{};

    /// See @c _calc_tab() for reflected-input mode specialization.
    constexpr inline static type _calc_tab(
        const uint8_t *in, size_t len, type crc_in)
    {
        type crc = crc_in;
        if __CONSTEXPR (bits < 8) {
            crc <<= (8 - bits);
        }

        while (len--) {
            if __CONSTEXPR (bits <= 8) {
                crc = lookup.tab(crc ^ *in++);
            } else {
                crc = (crc << 8) ^
                    lookup.tab((crc >> (bits - 8)) ^ (type)*in++);
            }
        }

        if __CONSTEXPR (bits < 8) {
            return crc >> (8 - bits);
        } else {
            return crc & mask;
        }
    }

    /// See @c _final() for reflected-input mode specialization.
    constexpr inline type _final(type crc) const
    {
        if (refl_out) {
            crc = bits_rev(crc, bits);
        }
        return crc ^ xor_out;
    }

    /**
     * See @c calc_algo() constructor for reflected-input mode specialization.
     *
     * @note In direct-input mode @c init_in (initial CRC input value)
     *     is not inverted.
     */
    constexpr crc_algo(
        bool refl_out, type init_in, type xor_out, type check_val):
        refl_out(refl_out),
        init_in(init_in & mask),
        xor_out(xor_out & mask),
        check_val(check_val)
    {}

    constexpr crc_algo(const crc_algo&) = default;

    // Runtime parameters directly accessible in read-only mode.
    // They may be reduced to compile-time constants by a compiler.
    const bool refl_out;
    const type init_in;
    const type xor_out;
    const type check_val;
};

/**
 * CRC calculation engine.
 */
template<unsigned Bits, uint64_t Poly, bool ReflIn,
    crc_tab_e TabType = def_tab_type>
struct crc_engine: crc_algo<Bits, Poly, ReflIn, TabType>
{
    /// CRC algorithm type
    using algo_type = crc_algo<Bits, Poly, ReflIn, TabType>;
    /// CRC result type
    using type = typename algo_type::type;

    /// Create engine for specific CRC algorithm @c algo.
    constexpr crc_engine(algo_type algo):
        algo_type(algo), crc(this->init_in)
    {}

    /**
     * Calculate CRC for given input bytes - block mode.
     *
     * Calculation engine collects passed input blocks for processing CRC
     * until @ref final() method call.
     */
    inline void update(const uint8_t *in, size_t len) {
        crc = this->_calc_tab(in, len, crc);
    }

    /**
     * Return final CRC value - block mode.
     *
     * Onece the value is returned the method resets the engine for subsequent
     * block calculations.
     */
    inline type final() {
        type res = this->_final(crc);
        crc = this->init_in;
        return res;
    }

    /**
     * Calculate CRC for given input bytes - single step mode.
     *
     * @note The method doesn't interfere with @c update() and @c final()
     *     used in the block mode.
     */
    constexpr inline type calc(const uint8_t *in, size_t len) const {
        return this->_final(this->_calc_tab(in, len, this->init_in));
    }

private:
    type crc;
};

/**
 * CRC algorithm parameters.
 *
 * The template embraces all CRC algorithm parameters stored in compile-time
 * (type oriented) form. See @ref calc_algo and @ref calc_algo::calc_algo()
 * for more details.
 *
 * @note The library provides large set of predefined instantiations
 *     of this template for various types of CRC algorithms.
 */
template<
    unsigned Bits, uint64_t Poly, bool ReflIn, bool ReflOut,
    uint64_t InitVal, uint64_t XorOut, uint64_t CheckVal,
    crc_tab_e TabType = def_tab_type>
struct crc_algo_desc
{
    /// CRC algorithm type
    using algo_type = crc_algo<Bits, Poly, ReflIn, TabType>;
    /// CRC engine type
    using engine_type = crc_engine<Bits, Poly, ReflIn, TabType>;
    /// CRC result type
    using type = typename algo_type::type;

    /// Get the algorithm instance
    constexpr inline static algo_type get_algo() {
        return algo_type(ReflOut, (type)InitVal, (type)XorOut, CheckVal);
    }

    /// Get the CRC engine instance
    constexpr inline static engine_type get_engine() {
        return engine_type(get_algo());
    }
};

/*
 * Predefined CRC algorithms
 */
using CRC1 = crc_algo_desc<1, 0x1, true, true, 0, 0, 0x1>;
using CRC3_GSM = crc_algo_desc<3, 0x3, false, false, 0, ~0U, 0x4>;
using CRC3_ROHC = crc_algo_desc<3, 0x3, true, true, ~0U, 0, 0x6>;
using CRC4_ITU = crc_algo_desc<4, 0x3, true, true, 0, 0, 0x7>;
using CRC4_G704 = CRC4_ITU;
using CRC4_INTERLAKEN = crc_algo_desc<4, 0x3, false, false, ~0U, ~0U, 0xb>;
using CRC5_USB = crc_algo_desc<5, 0x05, true, true, ~0U, ~0U, 0x19>;
using CRC5_EPC = crc_algo_desc<5, 0x09, false, false, 0x09, 0, 0>;
using CRC5_EPC_C1G2 = CRC5_EPC;
using CRC5_ITU = crc_algo_desc<5, 0x15, true, true, 0, 0, 0x07>;
using CRC5_G704 = CRC5_ITU;
using CRC6_ITU = crc_algo_desc<6, 0x03, true, true, 0, 0, 0x06>;
using CRC6_G704 = CRC6_ITU;
using CRC6_CDMA2000_B = crc_algo_desc<6, 0x07, false, false, ~0U, 0, 0x3b>;
using CRC6_DARC = crc_algo_desc<6, 0x19, true, true, 0, 0, 0x26>;
using CRC6_NR = crc_algo_desc<6, 0x21, false, false, 0, 0, 0x15>;
using CRC6_CDMA2000_A = crc_algo_desc<6, 0x27, false, false, ~0U, 0, 0x0d>;
using CRC6_GSM = crc_algo_desc<6, 0x2f, false, false, 0, ~0U, 0x13>;
using CRC7 = crc_algo_desc<7, 0x09, false, false, 0, 0, 0x75>;
using CRC7_MMC = CRC7;
using CRC7_UMTS = crc_algo_desc<7, 0x45, false, false, 0, 0, 0x61>;
using CRC7_ROHC = crc_algo_desc<7, 0x4f, true, true, ~0U, 0, 0x53>;
// using CRC7_MVB = crc_algo_desc<7, 0x65, false, false, 0, 0, 0x1f>;
using CRC8 = crc_algo_desc<8, 0x07, false, false, 0, 0, 0xf4>;
using CRC8_SMBUS = CRC8;
using CRC8_HDLC = crc_algo_desc<8, 0x07, true, true, ~0U, ~0U, 0x2f>;
using CRC8_ITU = crc_algo_desc<8, 0x07, false, false, 0, 0x55, 0xa1>;
using CRC8_I432_1 = CRC8_ITU;
using CRC8_ROHC = crc_algo_desc<8, 0x07, true, true, ~0U, 0, 0xd0>;
using CRC8_EBU = crc_algo_desc<8, 0x1d, true, true, ~0U, 0, 0x97>;
using CRC8_AES = CRC8_EBU;
using CRC8_TECH3250 = CRC8_EBU;
using CRC8_GSM_A = crc_algo_desc<8, 0x1d, false, false, 0, 0, 0x37>;
using CRC8_HITAG = crc_algo_desc<8, 0x1d, false, false, ~0U, 0, 0xb4>;
using CRC8_ICODE = crc_algo_desc<8, 0x1d, false, false, 0xfd, 0, 0x7e>;
using CRC8_MIFRAME_MAD = crc_algo_desc<8, 0x1d, false, false, 0xc7, 0, 0x99>;
using CRC8_SAE_J1850 = crc_algo_desc<8, 0x1d, false, false, ~0U, ~0U, 0x4b>;
using CRC8_AUTOSAR = crc_algo_desc<8, 0x2f, false, false, ~0U, ~0U, 0xdf>;
using CRC8_OPENSAFETY = crc_algo_desc<8, 0x2f, false, false, 0, 0, 0x3e>;
using CRC8_MAXIM = crc_algo_desc<8, 0x31, true, true, 0, 0, 0xa1>;
using CRC8_MAXIM_DOW = CRC8_MAXIM;
using CRC8_NRSC5 = crc_algo_desc<8, 0x31, false, false, ~0U, 0, 0xf7>;
using CRC8_DARC = crc_algo_desc<8, 0x39, true, true, 0, 0, 0x15>;
using CRC8_GSM_B = crc_algo_desc<8, 0x49, false, false, 0, ~0U, 0x94>;
using CRC8_CDMA2000 = crc_algo_desc<8, 0x9b, false, false, ~0U, 0, 0xda>;
using CRC8_LTE = crc_algo_desc<8, 0x9b, false, false, 0, 0, 0xea>;
using CRC8_WCDMA = crc_algo_desc<8, 0x9b, true, true, 0, 0, 0x25>;
using CRC8_DVB_S2 = crc_algo_desc<8, 0xd5, false, false, 0, 0, 0xbc>;
using CRC8_BLUETOOTH = crc_algo_desc<8, 0xa7, true, true, 0, 0, 0x26>;
using CRC10_GSM = crc_algo_desc<10, 0x175, false, false, 0, ~0U, 0x12a>;
using CRC10 = crc_algo_desc<10, 0x233, false, false, 0, 0, 0x199>;
using CRC10_ATM = CRC10;
using CRC10_I610 = CRC10;
using CRC10_CDMA2000 = crc_algo_desc<10, 0x3d9, false, false, ~0U, 0, 0x233>;
using CRC11_UMTS = crc_algo_desc<11, 0x307, false, false, 0, 0, 0x061>;
using CRC11 = crc_algo_desc<11, 0x385, false, false, 0x01a, 0, 0x5a3>;
using CRC11_FLEXRAY = CRC11;
using CRC11_NR = crc_algo_desc<11, 0x621, false, false, 0, 0, 0x5ca>;
using CRC12_DECT = crc_algo_desc<12, 0x80f, false, false, 0, 0, 0xf5b>;
using X_CRC12 = CRC12_DECT;
using CRC12_UMTS = crc_algo_desc<12, 0x80f, false, true, 0, 0, 0xdaf>;
using CRC12_3GPP = CRC12_UMTS;
using CRC12_GSM = crc_algo_desc<12, 0xd31, false, false, 0, ~0U, 0xb34>;
using CRC12_CDMA2000 = crc_algo_desc<12, 0xf13, false, false, ~0U, 0, 0xd4d>;
using CRC13_BBC = crc_algo_desc<13, 0x1cf5, false, false, 0, 0, 0x04fa>;
using CRC14_GSM = crc_algo_desc<14, 0x202d, false, false, 0, ~0U, 0x30ae>;
using CRC14_DARC = crc_algo_desc<14, 0x0805, true, true, 0, 0, 0x082d>;
using CRC15 = crc_algo_desc<15, 0x4599, false, false, 0, 0, 0x059e>;
using CRC15_CAN = CRC15;
using CRC15_MPT1327 = crc_algo_desc<15, 0x6815, false, false, 0, 0x0001, 0x2566>;
using CRC16_DECT_R = crc_algo_desc<16, 0x0589, false, false, 0, 0x0001, 0x007e>;
using R_CRC16 = CRC16_DECT_R;
using CRC16_DECT_X = crc_algo_desc<16, 0x0589, false, false, 0, 0, 0x007f>;
using X_CRC16 = CRC16_DECT_X;
using CRC16_NRSC5 = crc_algo_desc<16, 0x080b, true, true, ~0U, 0, 0xa066>;
using CRC16_AUG_CCITT = crc_algo_desc<16, 0x1021, false, false, 0x1d0f, 0, 0xe5cc>;
using CRC16_SPI_FUJITSU = CRC16_AUG_CCITT;
using CRC16_CCITT_FALSE = crc_algo_desc<16, 0x1021, false, false, ~0U, 0, 0x29b1>;
using CRC16_AUTOSAR = CRC16_CCITT_FALSE;
using CRC16_IBM3740 = CRC16_CCITT_FALSE;
using CRC16_GENIBUS = crc_algo_desc<16, 0x1021, false, false, ~0U, ~0U, 0xd64e>;
using CRC16_DARC = CRC16_GENIBUS;
using CRC16_EPC = CRC16_GENIBUS;
using CRC16_EPC_C1G2 = CRC16_GENIBUS;
using CRC16_ICODE = CRC16_GENIBUS;
using CRC16_GSM = crc_algo_desc<16, 0x1021, false, false, 0, ~0U, 0xce3c>;
using CRC16_ISO_IEC14443_3_A = crc_algo_desc<16, 0x1021, true, true, 0xc6c6, 0, 0xbf05>;
using CRC_A = CRC16_ISO_IEC14443_3_A;
using CRC16_KERMIT = crc_algo_desc<16, 0x1021, true, true, 0, 0, 0x2189>;
using CRC16_BLUETOOTH = CRC16_KERMIT;
using CRC16_CCITT = CRC16_KERMIT;
using CRC16_CCITT_TRUE = CRC16_KERMIT;
using CRC16_V41_LSB = CRC16_KERMIT;
using CRC16_MCRF4XX = crc_algo_desc<16, 0x1021, true, true, ~0U, 0, 0x6f91>;
using CRC16_RIELLO = crc_algo_desc<16, 0x1021, true, true, 0xb2aa, 0, 0x63d0>;
using CRC16_TMS37157 = crc_algo_desc<16, 0x1021, true, true, 0x89ec, 0, 0x26b1>;
using CRC16_X25 = crc_algo_desc<16, 0x1021, true, true, ~0U, ~0U, 0x906e>;
using CRC16_IBM_SDLC = CRC16_X25;
using CRC16_ISO_HDLC = CRC16_X25;
using CRC16_ISO_IEC14443_3_B = CRC16_X25;
using CRC_B = CRC16_X25;
using CRC16_XMODEM = crc_algo_desc<16, 0x1021, false, false, 0, 0, 0x31c3>;
using CRC16_ACORN = CRC16_XMODEM;
using CRC16_LTE = CRC16_XMODEM;
using CRC16_V41_MSB = CRC16_XMODEM;
using CRC16_PROFIBUS = crc_algo_desc<16, 0x1dcf, false, false, ~0U, ~0U, 0xa819>;
using CRC16_IEC61158_2 = CRC16_PROFIBUS;
// using CRC16_CHAKRAVARTY = crc_algo_desc<16, 0x2f15, false, false, 0, 0, 0xa2d1>;
using CRC16_DNP = crc_algo_desc<16, 0x3d65, true, true, 0, ~0U, 0xea82>;
using CRC16_EN13757 = crc_algo_desc<16, 0x3d65, false, false, 0, ~0U, 0xc2b7>;
using CRC16_M17 = crc_algo_desc<16, 0x5935, false, false, ~0U, 0, 0x772b>;
using CRC16_OPENSAFETY_A = crc_algo_desc<16, 0x5935, false, false, 0, 0, 0x5d38>;
using CRC16_LJ1200 = crc_algo_desc<16, 0x6f63, false, false, 0, 0, 0xbdf4>;
using CRC16_OPENSAFETY_B = crc_algo_desc<16, 0x755b, false, false, 0, 0, 0x20fe>;
using CRC16_ARC = crc_algo_desc<16, 0x8005, true, true, 0, 0, 0xbb3d>;
using CRC16 = CRC16_ARC;
using CRC16_LHA = CRC16_ARC;
using CRC16_BUYPASS = crc_algo_desc<16, 0x8005, false, false, 0, 0, 0xfee8>;
using CRC16_UMTS = CRC16_BUYPASS;
using CRC16_VERIFONE = CRC16_BUYPASS;
using CRC16_CMS = crc_algo_desc<16, 0x8005, false, false, ~0U, 0, 0xaee7>;
using CRC16_DDS110 = crc_algo_desc<16, 0x8005, false, false, 0x800d, 0, 0x9ecf>;
using CRC16_MAXIM = crc_algo_desc<16, 0x8005, true, true, 0, ~0U, 0x44c2>;
using CRC16_MAXIM_DOW = CRC16_MAXIM;
using CRC16_MODBUS = crc_algo_desc<16, 0x8005, true, true, ~0U, 0, 0x4b37>;
using CRC16_USB = crc_algo_desc<16, 0x8005, true, true, ~0U, ~0U, 0xb4c8>;
using CRC16_T10_DIF = crc_algo_desc<16, 0x8bb7, false, false, 0, 0, 0xd0db>;
using CRC16_CDMA2000 = crc_algo_desc<16, 0xc867, false, false, ~0U, 0, 0x4c06>;
// using CRC16_ARINC = crc_algo_desc<16, 0xa02b, false, false, 0, 0, 0xeba4>;
using CRC16_TELEDISK = crc_algo_desc<16, 0xa097, false, false, 0, 0, 0x0fb3>;
using CRC17_CAN_FD = crc_algo_desc<17, 0x1685b, false, false, 0, 0, 0x04f03>;
using CRC21_CAN_FD = crc_algo_desc<21, 0x102899, false, false, 0, 0, 0x0ed841>;
using CRC24_BLE = crc_algo_desc<24, 0x00065b, true, true, 0x555555, 0, 0xc25a56>;
using CRC24_INTERLAKEN = crc_algo_desc<24, 0x328b63, false, false, ~0U, ~0U, 0xb4f3e6>;
using CRC24_FLEXRAY_A = crc_algo_desc<24, 0x5d6dcb, false, false, 0xfedcba, 0, 0x7979bd>;
using CRC24_FLEXRAY_B = crc_algo_desc<24, 0x5d6dcb, false, false, 0xabcdef, 0, 0x1f23b8>;
using CRC24_LTE_B = crc_algo_desc<24, 0x800063, false, false, 0, 0, 0x23ef52>;
using CRC24_OS9 = crc_algo_desc<24, 0x800063, false, false, ~0U, ~0U, 0x200fa5>;
using CRC24 = crc_algo_desc<24, 0x864cfb, false, false, 0xb704ce, 0, 0x21cf02>;
using CRC24_OPENPGP = CRC24;
using CRC24_LTE_A = crc_algo_desc<24, 0x864cfb, false, false, 0, 0, 0xcde703>;
using CRC24_NR_C = crc_algo_desc<24, 0xb2b117, false, false, 0, 0, 0xf48279>;
using CRC30_CDMA = crc_algo_desc<30, 0x2030b9c7, false, false, ~0U, ~0U, 0x04c34abf>;
using CRC31_PHILIPS = crc_algo_desc<31, 0x04c11db7, false, false, ~0U, ~0U, 0x0ce9e46c>;
using CRC32_XFER = crc_algo_desc<32, 0x000000af, false, false, 0, 0, 0xbd0be338>;
using CRC32 = crc_algo_desc<32, 0x04c11db7, true, true, ~0U, ~0U, 0xcbf43926>;
using CRC32_ADCCP = CRC32;
using CRC32_ISO_HDLC = CRC32;
using CRC32_V42 = CRC32;
using CRC32_XZ = CRC32;
using CRC32_BZIP2 = crc_algo_desc<32, 0x04c11db7, false, false, ~0U, ~0U, 0xfc891918>;
using CRC32_AAL5 = CRC32_BZIP2;
using CRC32_DECT_B = CRC32_BZIP2;
using B_CRC32 = CRC32_BZIP2;
using CRC32_JAMCRC = crc_algo_desc<32, 0x04c11db7, true, true, ~0U, 0, 0x340bc6d9>;
using CRC32_MPEG2 = crc_algo_desc<32, 0x04c11db7, false, false, ~0U, 0, 0x0376e6e7>;
using CRC32_POSIX = crc_algo_desc<32, 0x04c11db7, false, false, 0, ~0U, 0x765e7680>;
using CRC32_CKSUM = CRC32_POSIX;
using CRC32_C = crc_algo_desc<32, 0x1edc6f41, true, true, ~0U, ~0U, 0xe3069283>;
using CRC32_BASE91_C = CRC32_C;
using CRC32_CASTAGNOLI = CRC32_C;
using CRC32_INTERLAKEN = CRC32_C;
using CRC32_ISCSI = CRC32_C;
// using CRC32_K2 = crc_algo_desc<32, 0x32583499, true, true, ~0U, 0, 0x1148ab33>;
using CRC32_MEF = crc_algo_desc<32, 0x741b8cd7, true, true, ~0U, 0, 0xd2c22f51>;
using CRC32_K = CRC32_MEF;
using CRC32_CDROM_EDC = crc_algo_desc<32, 0x8001801b, true, true, 0, 0, 0x6ec2edc4>;
using CRC32_Q = crc_algo_desc<32, 0x814141ab, false, false, 0, 0, 0x3010bf7f>;
using CRC32_AIXM = CRC32_Q;
using CRC32_D = crc_algo_desc<32, 0xa833982b, true, true, ~0U, ~0U, 0x87315576>;
using CRC32_BASE91_D = CRC32_D;
using CRC32_AUTOSAR = crc_algo_desc<32, 0xf4acfb13, true, true, ~0U, ~0U, 0x1697d06a>;
using CRC40_GSM = crc_algo_desc<40, 0x0004820009, false, false, 0, ~0ULL, 0xd4164fc646>;
using CRC64_GO_ISO = crc_algo_desc<64, 0x000000000000001b, true, true, ~0ULL, ~0ULL, 0xb90956c775a41001>;
using CRC64_MS = crc_algo_desc<64, 0x259c84cba6426349, true, true, ~0ULL, 0, 0x75d4b74f024eceea>;
using CRC64 = crc_algo_desc<64, 0x42f0e1eba9ea3693, false, false, 0, 0, 0x6c40df5f0b497347>;
using CRC64_ECMA182 = CRC64;
using CRC64_WE = crc_algo_desc<64, 0x42f0e1eba9ea3693, false, false, ~0ULL, ~0ULL, 0x62ec59e3f1a4f00a>;
using CRC64_XZ = crc_algo_desc<64, 0x42f0e1eba9ea3693, true, true, ~0ULL, ~0ULL, 0x995dc9bbdf1939fa>;
using CRC64_GO_ECMA = CRC64_XZ;
using CRC64_REDIS = crc_algo_desc<64, 0xad93d23594c935a9, true, true, 0, 0, 0xe9c6d914c4b8d9ca>;

#ifdef _CRAC_TEST_
# include "crac_test.h"
#endif

} // crac namespace

#undef __CONSTEXPR
#endif /* __CRAC_H__ */
