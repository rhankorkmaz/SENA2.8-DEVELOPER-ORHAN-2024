// random standard header

// Copyright (c) Microsoft Corporation.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#pragma once
#ifndef _RANDOM_
#define _RANDOM_
#include <yvals_core.h>

#if _STL_COMPILER_PREPROCESSOR
#include <algorithm>
#include <cmath>
#include <cstdint>
#include <ios>
#include <vector>
#include <xbit_ops.h>
#include <xstring>

#pragma pack(push, _CRT_PACKING)
#pragma warning(push, _STL_WARNING_LEVEL)
#pragma warning(disable : _STL_DISABLED_WARNINGS)
_STL_DISABLE_CLANG_WARNINGS
#pragma push_macro("new")
#undef new

#pragma warning(disable : 4127) // conditional expression is constant

_STD_BEGIN
#define _RNG_PROHIBIT_CHAR(_CheckedType)               \
    static_assert(!_Is_character<_CheckedType>::value, \
        "note: char, signed char, unsigned char, char8_t, int8_t, and uint8_t are not allowed")

#define _RNG_REQUIRE_REALTYPE(_RandType, _CheckedType)                                                     \
    static_assert(_Is_any_of_v<_CheckedType, float, double, long double>,                                  \
        "invalid template argument for " #_RandType ": N4659 29.6.1.1 [rand.req.genl]/1d requires one of " \
        "float, double, or long double")

#define _RNG_REQUIRE_INTTYPE(_RandType, _CheckedType)                                                                  \
    static_assert(_Is_any_of_v<_CheckedType, short, int, long, long long, unsigned short, unsigned int, unsigned long, \
                      unsigned long long>,                                                                             \
        "invalid template argument for " #_RandType ": N4659 29.6.1.1 [rand.req.genl]/1e requires one of "             \
        "short, int, long, long long, unsigned short, unsigned int, unsigned long, or unsigned long long");            \
    _RNG_PROHIBIT_CHAR(_CheckedType)

#define _RNG_REQUIRE_UINTTYPE(_RandType, _CheckedType)                                                         \
    static_assert(_Is_any_of_v<_CheckedType, unsigned short, unsigned int, unsigned long, unsigned long long>, \
        "invalid template argument for " #_RandType ": N4659 29.6.1.1 [rand.req.genl]/1f requires one of "     \
        "unsigned short, unsigned int, unsigned long, or unsigned long long");                                 \
    _RNG_PROHIBIT_CHAR(_CheckedType)

template <class _Seed_seq, class _Self, class _Engine = _Self>
using _Enable_if_seed_seq_t = enable_if_t<
    !is_convertible_v<remove_cv_t<_Seed_seq>,
    typename _Self::
    result_type> && !is_same_v<remove_cv_t<_Seed_seq>, _Self> && !is_same_v<remove_cv_t<_Seed_seq>, _Engine>,
    int>;

_INLINE_VAR constexpr long double _Pi = 3.14159265358979323846264338327950288L;
_INLINE_VAR constexpr long double _Exp1 = 2.71828182845904523536028747135266250L;
_INLINE_VAR constexpr long double _Two32 = 4294967296.0L;
_INLINE_VAR constexpr long double _Two31 = 2147483648.0L;

_CRTIMP2_PURE float __CLRCALL_PURE_OR_CDECL _XLgamma(float);
_CRTIMP2_PURE double __CLRCALL_PURE_OR_CDECL _XLgamma(double);
_CRTIMP2_PURE long double __CLRCALL_PURE_OR_CDECL _XLgamma(long double);

_INLINE_VAR constexpr int _Nwords = 4;

template <class _Elem, class _Traits>
basic_ostream<_Elem, _Traits>& _Write(
    basic_ostream<_Elem, _Traits>& _Os, long double _Dx) { // write long double to stream
    int _Ex;
    long double _Frac = _CSTD frexpl(_Dx, &_Ex);
    for (int _Nw = 0; _Nw < _Nwords; ++_Nw) { // break into 31-bit words
        _Frac *= _Two31;
        long _Digits = static_cast<long>(_Frac);
        _Frac -= _Digits;
        _Os << ' ' << _Digits;
    }
    _Os << ' ' << _Ex;
    return _Os;
}

template <class _Elem, class _Traits>
basic_istream<_Elem, _Traits>& _Read(
    basic_istream<_Elem, _Traits>& _Is, long double& _Dx) { // read long double from stream
    long double _Frac = 0.0;
    long _Digits;
    for (int _Nw = 0; _Nw < _Nwords; ++_Nw) { // accumulate 31-bit words
        _Is >> _Digits;
        long double _Temp = _Digits / _Two31;
        for (int _Idx = 0; _Idx < _Nw; ++_Idx) {
            _Temp /= _Two31;
        }

        _Frac += _Temp;
    }
    _Is >> _Digits;
    _Dx = _CSTD ldexpl(_Frac, _Digits);
    return _Is;
}

template <class _Elem, class _Traits, class _Ty>
basic_istream<_Elem, _Traits>& _In(basic_istream<_Elem, _Traits>& _Is, _Ty& _Dx) { // read from stream
    long double _Vx;
    _Ty _Max = (numeric_limits<_Ty>::max) ();
    _Read(_Is, _Vx);
    if (_CSTD fabsl(_Vx) <= _Max) {
        _Dx = static_cast<_Ty>(_Vx);
    }
    else if (_Vx < 0) {
        _Dx = -_Max;
    }
    else {
        _Dx = _Max;
    }

    return _Is;
}

template <class _Elem, class _Traits, class _Ty>
basic_ostream<_Elem, _Traits>& _Out(basic_ostream<_Elem, _Traits>& _Os, _Ty _Dx) { // write to stream
    return _Write(_Os, _Dx);
}

template <class _Elem, class _Traits, class _Ty>
class _Wrap_istream { // wrap input stream as function object
public:
    _Wrap_istream(basic_istream<_Elem, _Traits>& _Is) : _Str(_Is) {}

    _Ty operator()() { // read next value
        _Ty _Data;
        _Str >> _Data;
        if (!_Str) {
            _Xinvalid_argument("input stream corrupted");
        }

        return _Data;
    }

    _Wrap_istream& operator=(const _Wrap_istream&) = delete;

private:
    basic_istream<_Elem, _Traits>& _Str;
};

class seed_seq { // standard sequence of seed values
public:
    using result_type = unsigned int;

    seed_seq() noexcept {}

    template <class _Ty, enable_if_t<is_integral_v<_Ty>, int> = 0>
    seed_seq(initializer_list<_Ty> _Ilist) {
        _Construct(_Ilist.begin(), _Ilist.end());
    }

    template <class _InIt>
    seed_seq(_InIt _First, _InIt _Last) {
        _Construct(_First, _Last);
    }

    template <class _RanIt>
    void generate(_RanIt _First, _RanIt _Last) const { // generate randomized interval from seeds
        _Adl_verify_range(_First, _Last);
        auto _UFirst = _Get_unwrapped(_First);
        const auto _Nx = static_cast<size_t>(_Get_unwrapped(_Last) - _UFirst);

        if (0 < _Nx) { // finite interval, fill it
            const size_t _Sx = _Myvec.size();
            const size_t _Tx = 623 <= _Nx ? 11 : 68 <= _Nx ? 7 : 39 <= _Nx ? 5 : 7 <= _Nx ? 3 : (_Nx - 1) / 2;
            const size_t _Px = (_Nx - _Tx) / 2;
            const size_t _Qx = _Px + _Tx;
            const size_t _Mx = _Nx <= _Sx ? _Sx + 1 : _Nx;
            size_t _Kx;

            _Iter_value_t<_RanIt> _Mask = _Iter_value_t<_RanIt>(1) << 31;
            _Mask <<= 1; // build 32-bit mask safely
            _Mask -= 1;

            for (_Kx = 0; _Kx < _Nx; ++_Kx) {
                _UFirst[_Kx] = 0x8b8b8b8b;
            }

            for (_Kx = 0; _Kx < _Mx; ++_Kx) { // scramble and add any vector contributions
                result_type _Rx1 =
                    1664525 * _Xor27(_UFirst[_Kx % _Nx] ^ _UFirst[(_Kx + _Px) % _Nx] ^ _UFirst[(_Kx - 1) % _Nx]);

                size_t _Off;
                if (_Kx == 0) {
                    _Off = _Sx;
                }
                else if (_Kx <= _Sx) {
                    _Off = _Kx % _Nx + _Myvec[_Kx - 1];
                }
                else {
                    _Off = _Kx % _Nx;
                }
                result_type _Rx2 = static_cast<result_type>((_Rx1 + _Off) & _Mask);

                _UFirst[(_Kx + _Px) % _Nx] = (_UFirst[(_Kx + _Px) % _Nx] + _Rx1) & _Mask;
                _UFirst[(_Kx + _Qx) % _Nx] = (_UFirst[(_Kx + _Qx) % _Nx] + _Rx2) & _Mask;
                _UFirst[_Kx % _Nx] = _Rx2;
            }
            for (; _Kx < _Mx + _Nx; ++_Kx) { // rescramble
                result_type _Rx3 =
                    1566083941 * _Xor27(_UFirst[_Kx % _Nx] + _UFirst[(_Kx + _Px) % _Nx] + _UFirst[(_Kx - 1) % _Nx]);
                result_type _Rx4 = static_cast<result_type>((_Rx3 - _Kx % _Nx) & _Mask);

                _UFirst[(_Kx + _Px) % _Nx] = (_UFirst[(_Kx + _Px) % _Nx] ^ _Rx3) & _Mask;
                _UFirst[(_Kx + _Qx) % _Nx] = (_UFirst[(_Kx + _Qx) % _Nx] ^ _Rx4) & _Mask;
                _UFirst[_Kx % _Nx] = _Rx4;
            }
        }
    }

    template <class _OutIt>
    void param(_OutIt _Dest) const { // copy seeds
        _STD copy(_Myvec.begin(), _Myvec.end(), _Dest);
    }

    _NODISCARD size_t size() const noexcept { // get size of seed
        return _Myvec.size();
    }

    seed_seq(const seed_seq&) = delete;
    void operator=(const seed_seq&) = delete;

private:
    template <class _InIt>
    void _Construct(_InIt _First, _InIt _Last) {
        for (; _First != _Last; ++_First) {
            _Myvec.push_back(static_cast<unsigned int>(*_First));
        }
    }

    result_type _Xor27(result_type _Val) const { // shift and merge
        return _Val ^ (_Val >> 27);
    }

    vector<result_type> _Myvec;
};

template <class _Real, size_t _Bits, class _Gen>
_NODISCARD _Real generate_canonical(_Gen& _Gx) { // build a floating-point value from random sequence
    _RNG_REQUIRE_REALTYPE(generate_canonical, _Real);

    const size_t _Digits = static_cast<size_t>(numeric_limits<_Real>::digits);
    const size_t _Minbits = _Digits < _Bits ? _Digits : _Bits;

    const _Real _Gxmin = static_cast<_Real>((_Gx.min) ());
    const _Real _Gxmax = static_cast<_Real>((_Gx.max) ());
    const _Real _Rx = (_Gxmax - _Gxmin) + _Real{ 1 };

    const int _Ceil = static_cast<int>(_STD ceil(static_cast<_Real>(_Minbits) / _STD log2(_Rx)));
    const int _Kx = _Ceil < 1 ? 1 : _Ceil;

    _Real _Ans{ 0 };
    _Real _Factor{ 1 };

    for (int _Idx = 0; _Idx < _Kx; ++_Idx) { // add in another set of bits
        _Ans += (static_cast<_Real>(_Gx()) - _Gxmin) * _Factor;
        _Factor *= _Rx;
    }

    return _Ans / _Factor;
}

#define _NRAND(eng, resty) (_STD generate_canonical<resty, static_cast<size_t>(-1)>(eng))

_INLINE_VAR constexpr int _MP_len = 5;
using _MP_arr = uint64_t[_MP_len];

_NODISCARD _CRTIMP2_PURE uint64_t __CLRCALL_PURE_OR_CDECL _MP_Get(_MP_arr) noexcept;
_CRTIMP2_PURE void __CLRCALL_PURE_OR_CDECL _MP_Add(_MP_arr, uint64_t) noexcept;
_CRTIMP2_PURE void __CLRCALL_PURE_OR_CDECL _MP_Mul(_MP_arr, uint64_t, uint64_t) noexcept;
_CRTIMP2_PURE void __CLRCALL_PURE_OR_CDECL _MP_Rem(_MP_arr, uint64_t) noexcept;

template <class _Uint, _Uint _Ax, _Uint _Cx, _Uint _Mx>
_NODISCARD _Uint _Next_linear_congruential_value(_Uint _Prev) noexcept {
    // Choose intermediate type:
    // To use type T for the intermediate calculation, we must show
    //  _Ax * (_Mx - 1) + _Cx <= numeric_limits<T>::max()
    // Split _Cx:
    //   _Cx <= numeric_limits<T>::max()
    //   && _Ax * (_Mx - 1) <= numeric_limits<T>::max() - _Cx
    // Divide by _Ax:
    //   _Cx <= numeric_limits<T>::max()
    //   && (_Mx - 1) <= (numeric_limits<T>::max() - _Cx) / _Ax
    if constexpr (_Ax == 0) { // degenerate case; avoid divide by 0
        return static_cast<_Uint>(_Cx); // relies on _Mx == 0 || _Cx <= _Mx, N4741 [rand.eng.lcong]/3
    }
    else if constexpr (_Mx == 0) {
        // N4762 [rand.eng.lcong]/2: "If the template parameter m is 0, the modulus m
        // used throughout this subclause [rand.eng.lcong] is
        // numeric_limits<result_type>::max() plus 1." That is: Just do the multiply
        // and let normal unsigned modulo take care of it
        return static_cast<_Uint>(static_cast<_Uint>(_Ax * _Prev) + _Cx);
    }
    else if constexpr (_Cx <= UINT_MAX && static_cast<_Uint>(_Mx - 1) <= (UINT_MAX - _Cx) / _Ax) {
        // unsigned int is sufficient to store intermediate calculation
        const auto _Mul =
            static_cast<unsigned int>(_Prev) * static_cast<unsigned int>(_Ax) + static_cast<unsigned int>(_Cx);
        return static_cast<_Uint>(_Mul % _Mx);
    }
    else if constexpr (_Cx <= ULLONG_MAX && static_cast<_Uint>(_Mx - 1) <= (ULLONG_MAX - _Cx) / _Ax) {
        // unsigned long long is sufficient to store intermediate calculation
        const auto _Mul = static_cast<unsigned long long>(_Prev) * _Ax + _Cx;
        return static_cast<_Uint>(_Mul % _Mx);
    }
    else { // no intermediate integral type fits; fall back to multiprecision
        _MP_arr _Wx;
        _MP_Mul(_Wx, _Prev, _Ax);
        _MP_Add(_Wx, _Cx);
        _MP_Rem(_Wx, _Mx);
        return static_cast<_Uint>(_MP_Get(_Wx));
    }
}

template <class _Seed_seq>
_NODISCARD constexpr unsigned int _Seed_seq_to_uint(_Seed_seq& _Seq) {
    unsigned int _Arr[4]{};
    _Seq.generate(_Arr, _Arr + 4);
    return _Arr[3];
}

template <class _Seed_seq>
_NODISCARD constexpr unsigned long long _Seed_seq_to_ull(_Seed_seq& _Seq) {
    unsigned int _Arr[5]{};
    _Seq.generate(_Arr, _Arr + 5);
    unsigned long long _Result = _Arr[4];
    _Result <<= 32;
    _Result |= _Arr[3];
    return _Result;
}

template <class _Uint, _Uint _Cx, _Uint _Mx>
_NODISCARD constexpr _Uint _Get_linear_congruential_seed(_Uint _Sx) noexcept { // N4741 [rand.eng.lcong]/5
    if constexpr (_Mx != 0) {
        _Sx %= _Mx;
    }

    if constexpr (_Cx == 0) {
        if (_Sx == 0) {
            _Sx = _Uint{ 1 };
        }
    }

    return _Sx;
}

template <class _Uint, _Uint _Cx, _Uint _Mx, class _Seed_seq>
_NODISCARD _Uint _Get_linear_congruential_seed_from_seq(_Seed_seq& _Seq) { // N4741 [rand.eng.lcong]/6
    _Uint _Sx;
    if constexpr (_Mx == 0) {
        if constexpr (sizeof(_Uint) <= sizeof(unsigned int)) {
            _Sx = static_cast<_Uint>(_Seed_seq_to_uint(_Seq));
        }
        else {
            _Sx = static_cast<_Uint>(_Seed_seq_to_ull(_Seq));
        }
    }
    else if constexpr (_Mx <= UINT_MAX) {
        _Sx = static_cast<_Uint>(_Seed_seq_to_uint(_Seq) % _Mx);
    }
    else {
        _Sx = static_cast<_Uint>(_Seed_seq_to_ull(_Seq) % _Mx);
    }

    return _Get_linear_congruential_seed<_Uint, _Cx, _Mx>(_Sx);
}

template <class _Uint, _Uint _Ax, _Uint _Cx, _Uint _Mx>
class linear_congruential_engine { // a linear congruential generator random engine
public:
    _RNG_REQUIRE_UINTTYPE(linear_congruential_engine, _Uint);

    static_assert(0 == _Mx || (_Ax < _Mx&& _Cx < _Mx), "invalid template argument for linear_congruential_engine");

    using result_type = _Uint;
    static constexpr result_type multiplier = _Ax;
    static constexpr result_type increment = _Cx;
    static constexpr result_type modulus = _Mx;

    _NODISCARD static constexpr result_type(min)() noexcept /* strengthened */ {
        // return minimum possible generated value
        return _Cx == 0;
    }

#pragma warning(push)
#pragma warning(disable : 4309) // truncation of constant value
    _NODISCARD static constexpr result_type(max)() noexcept /* strengthened */ {
        // return maximum possible generated value
        return static_cast<result_type>(_Mx - 1u); // note 0 wraps around to max
    }
#pragma warning(pop)

    static constexpr result_type default_seed = 1u;

    linear_congruential_engine() noexcept // strengthened
        : _Prev(_Get_linear_congruential_seed<result_type, _Cx, _Mx>(default_seed)) {}

    explicit linear_congruential_engine(result_type _Sx) noexcept // strengthened
        : _Prev(_Get_linear_congruential_seed<result_type, _Cx, _Mx>(_Sx)) {}

    template <class _Seed_seq, _Enable_if_seed_seq_t<_Seed_seq, linear_congruential_engine> = 0>
    explicit linear_congruential_engine(_Seed_seq& _Seq)
        : _Prev(_Get_linear_congruential_seed_from_seq<result_type, _Cx, _Mx>(_Seq)) {}

    void seed(result_type _Sx = default_seed) noexcept /* strengthened */ {
        // reset sequence from numeric value
        _Prev = _Get_linear_congruential_seed<result_type, _Cx, _Mx>(_Sx);
    }

    template <class _Seed_seq, _Enable_if_seed_seq_t<_Seed_seq, linear_congruential_engine> = 0>
    void seed(_Seed_seq& _Seq) { // reset sequence from seed sequence
        _Prev = _Get_linear_congruential_seed_from_seq<result_type, _Cx, _Mx>(_Seq);
    }

    _NODISCARD _Uint operator()() noexcept {
        _Prev = _Next_linear_congruential_value<result_type, _Ax, _Cx, _Mx>(_Prev);
        return _Prev;
    }

    void discard(unsigned long long _Nskip) noexcept /* strengthened */ {
        // discard _Nskip elements
        auto _Temp = _Prev;
        for (; 0 < _Nskip; --_Nskip) {
            _Temp = _Next_linear_congruential_value<_Uint, _Ax, _Cx, _Mx>(_Temp);
        }

        _Prev = _Temp;
    }

#ifndef __CUDACC__ // TRANSITION, VSO-568006
    _NODISCARD
#endif // TRANSITION, VSO-568006
        friend bool operator==(const linear_congruential_engine& _Lhs, const linear_congruential_engine& _Rhs) noexcept
        /* strengthened */ {
        return _Lhs._Prev == _Rhs._Prev;
    }

#ifndef __CUDACC__ // TRANSITION, VSO-568006
    _NODISCARD
#endif // TRANSITION, VSO-568006
        friend bool operator!=(const linear_congruential_engine& _Lhs, const linear_congruential_engine& _Rhs) noexcept
        /* strengthened */ {
        return _Lhs._Prev != _Rhs._Prev;
    }

    template <class _Elem, class _Traits>
    friend basic_istream<_Elem, _Traits>& operator>>(
        basic_istream<_Elem, _Traits>& _Istr, linear_congruential_engine& _Eng) {
        return _Istr >> _Eng._Prev;
    }

    template <class _Elem, class _Traits>
    friend basic_ostream<_Elem, _Traits>& operator<<(
        basic_ostream<_Elem, _Traits>& _Ostr, const linear_congruential_engine& _Eng) {
        return _Ostr << _Eng._Prev;
    }

private:
    result_type _Prev;
};

template <class _Uint, _Uint _Ax, _Uint _Cx, _Uint _Mx>
class linear_congruential { // linear congruential random engine
public:
    _RNG_REQUIRE_UINTTYPE(linear_congruential, _Uint);

    static_assert(0 == _Mx || (_Ax < _Mx&& _Cx < _Mx), "invalid template argument for linear_congruential");

    using result_type = _Uint;

    static constexpr _Uint multiplier = _Ax;
    static constexpr _Uint increment = _Cx;
    static constexpr _Uint modulus = _Mx;

    linear_congruential() noexcept // strengthened
        : _Prev(_Get_linear_congruential_seed<_Uint, _Cx, _Mx>(1u)) {}

    explicit linear_congruential(_Uint _Xx0) noexcept // strengthened
        : _Prev(_Get_linear_congruential_seed<_Uint, _Cx, _Mx>(_Xx0)) {}

    template <class _Gen, _Enable_if_seed_seq_t<_Gen, linear_congruential> = 0>
    linear_congruential(_Gen& _Seq) : _Prev(_Get_linear_congruential_seed<_Uint, _Cx, _Mx>(_Seq())) {}

    void seed(_Uint _Xx0 = 1u) noexcept /* strengthened */ {
        // reset sequence from numeric value
        _Prev = _Get_linear_congruential_seed<_Uint, _Cx, _Mx>(_Xx0);
    }

    template <class _Gen, _Enable_if_seed_seq_t<_Gen, linear_congruential> = 0>
    void seed(_Gen& _Seq) { // reset sequence from generator
        _Prev = _Get_linear_congruential_seed<_Uint, _Cx, _Mx>(_Seq());
    }

    _NODISCARD _Uint(min)() const noexcept /* strengthened */ {
        // return minimum possible generated value
        return _Cx == 0;
    }

#pragma warning(push)
#pragma warning(disable : 4309) // truncation of constant value
    _NODISCARD _Uint(max)() const noexcept /* strengthened */ {
        // return maximum possible generated value
        return static_cast<_Uint>(_Mx - 1u); // note 0 wraps around to max
    }
#pragma warning(pop)

    _NODISCARD _Uint operator()() noexcept /* strengthened */ {
        // return next value
        _Prev = _Next_linear_congruential_value<_Uint, _Ax, _Cx, _Mx>(_Prev);
        return _Prev;
    }

    void discard(unsigned long long _Nskip) noexcept /* strengthened */ {
        // discard _Nskip elements
        auto _Temp = _Prev;
        for (; 0 < _Nskip; --_Nskip) {
            _Temp = _Next_linear_congruential_value<_Uint, _Ax, _Cx, _Mx>(_Temp);
        }

        _Prev = _Temp;
    }

#ifndef __CUDACC__ // TRANSITION, VSO-568006
    _NODISCARD
#endif // TRANSITION, VSO-568006
        friend bool operator==(const linear_congruential& _Lhs, const linear_congruential& _Rhs) noexcept
        /* strengthened */ {
        return _Lhs._Prev == _Rhs._Prev;
    }

#ifndef __CUDACC__ // TRANSITION, VSO-568006
    _NODISCARD
#endif // TRANSITION, VSO-568006
        friend bool operator!=(const linear_congruential& _Lhs, const linear_congruential& _Rhs) noexcept
        /* strengthened */ {
        return _Lhs._Prev != _Rhs._Prev;
    }

    template <class _Elem, class _Traits>
    friend basic_istream<_Elem, _Traits>& operator>>(basic_istream<_Elem, _Traits>& _Istr, linear_congruential& _Eng) {
        return _Istr >> _Eng._Prev;
    }

    template <class _Elem, class _Traits>
    friend basic_ostream<_Elem, _Traits>& operator<<(
        basic_ostream<_Elem, _Traits>& _Ostr, const linear_congruential& _Eng) {
        return _Ostr << _Eng._Prev;
    }

private:
    _Uint _Prev;
};

template <class _Ty, size_t _Nw>
struct _Circ_buf { // holds historical values for generators
    _Ty _At(size_t _Ix) const {
        return _Ax[_Base(_Ix)];
    }

    bool _Equals(const _Circ_buf& _Right) const {
        const _Ty* _Last1 = _Ax + _Idx;
        const _Ty* _Last2 = _Right._Ax + _Right._Idx;
        const _Ty* _First;
        const _Ty* _Last;
        const _Ty* _Other;
        bool _Use2 = _Base() < _Right._Base();

        if (_Use2) { // _Right's range is higher up in the array
                     // than ours, so scan it first
            _First = _Right._Ax + _Right._Base();
            _Last = _Last2;
            _Other = _Ax + _Base();
        }
        else { // our range is higher up in the array
              // than _Right's, so scan ours first
            _First = _Ax + _Base();
            _Last = _Last1;
            _Other = _Right._Ax + _Right._Base();
        }

        ptrdiff_t _Nx0 = _Nw;
        while (0 < _Nx0) { // scan
                           // note: may need up to three passes; each scan starts at the
                           // current highest array position and ends at the end of the
                           // array or the _Idx value, whichever comes first; the
                           // equality test succeeds only by reaching the _Idx value.
            const _Ty* _Limit = _First < _Last ? _Last : _Use2 ? _Right._Ax + 2 * _Nw : _Ax + 2 * _Nw;
            _Nx0 -= _Limit - _First;
            while (_First != _Limit) {
                if (*_First++ != *_Other++) {
                    return false;
                }
            }

            _First = _Other;
            _Last = _Use2 ? _Last1 : _Last2;
            _Other = _Use2 ? _Right._Ax : _Ax;
            _Use2 = !_Use2;
        }
        return true;
    }

    size_t _Base(size_t _Ix = 0) const {
        return (_Ix += _Idx) < _Nw ? (_Ix + _Nw) : (_Ix - _Nw);
    }

    unsigned int _Idx;
    _Ty _Ax[2 * _Nw];
};

template <class _Ty, size_t _Sx, size_t _Rx, class _Swc_Traits>
class _Swc_base : public _Circ_buf<_Ty, _Rx> { // common bits of subtract_with_carry/_01
public:
    using result_type = _Ty;
    using _Traits = _Swc_Traits;
    using _Mybase = _Circ_buf<_Ty, _Rx>;
    using _Seed_t = typename _Swc_Traits::_Seed_t;

    static constexpr size_t short_lag = _Sx;
    static constexpr size_t long_lag = _Rx;
    static constexpr _Seed_t default_seed = static_cast<_Seed_t>(19780503U);

    _Swc_base() {
        seed();
    }

    _Swc_base(_Seed_t _Xx0) {
        seed(_Xx0);
    }

    template <class _Gen, _Enable_if_seed_seq_t<_Gen, _Swc_base> = 0>
    _Swc_base(_Gen& _Gx) {
        seed(_Gx);
    }

    void seed(_Seed_t _Value = default_seed) { // set initial values from specified seed value
        _Seed(_Value, false, true_type{});
    }

    template <class _Gen>
    void seed(_Gen& _Gx, bool _Readcy = false) { // set initial values from range
        _Seed(_Gx, _Readcy, is_arithmetic<_Gen>{});
    }

    _NODISCARD result_type(min)() const {
        return 0;
    }

    _NODISCARD result_type(max)() const {
        return _Swc_Traits::_Max;
    }

    _NODISCARD result_type operator()() {
        const auto _Ix = 2 * _Rx <= this->_Idx ? 0 : this->_Idx;
        if (_Ix < _Sx) {
            _Setx(_Ix, this->_Ax[_Ix + 2 * _Rx - _Sx], this->_Ax[_Ix + _Rx]);
        }
        else if (_Ix < _Rx) {
            _Setx(_Ix, this->_Ax[_Ix - _Sx], this->_Ax[_Ix + _Rx]);
        }
        else {
            _Setx(_Ix, this->_Ax[_Ix - _Sx], this->_Ax[_Ix - _Rx]);
        }

        this->_Idx = _Ix + 1;
        return this->_Ax[_Ix];
    }

    void discard(unsigned long long _Nskip) { // discard _Nskip elements
        for (; 0 < _Nskip; --_Nskip) {
            (void)(*this)();
        }
    }

    bool _Equals(const _Swc_base& _Right) const {
        return _Mybase::_Equals(_Right) && _Carry == _Right._Carry;
    }

    template <class _Elem, class _Traits>
    basic_ostream<_Elem, _Traits>& _Write(basic_ostream<_Elem, _Traits>& _Ostr) const { // write state to _Ostr
        _Swc_Traits::_Write(_Ostr, *this, _Carry);
        return _Ostr;
    }

    template <class _Elem, class _Traits>
    basic_ostream<_Elem, _Traits>& _Write_full(basic_ostream<_Elem, _Traits>& _Ostr) const { // write state to _Ostr
        _Swc_Traits::_Write_full(_Ostr, *this, _Carry);
        return _Ostr;
    }

protected:
    template <class _Gen>
    void _Seed(_Gen& _Gx, bool _Readcy, true_type) { // reset sequence from numeric value
        linear_congruential<_Seed_t, 40014U, 0U, 2147483563U> _Lc(_Gx == 0U ? default_seed : _Gx);
        _Reset(_Lc, _Readcy);
    }

    template <class _Gen>
    void _Seed(_Gen& _Gx, bool _Readcy, false_type) { // reset sequence from generator
        _Reset(_Gx, _Readcy);
    }

    template <class _Gen>
    void _Reset(_Gen& _Gx, bool _Readcy) { // reset sequence
        _Carry = _Swc_Traits::_Reset(_Gx, this->_Ax, _Readcy);
        this->_Idx = _Rx;
    }

    void _Setx(size_t _Ix, _Ty _Xis, _Ty _Xir) { // update _Ax[_Ix] and _Carry
        bool _Underflowed = false;
        _Ty _Newx = _Xis;
        if (_Newx < _Xir) {
            _Underflowed = true;
        }

        _Newx -= _Xir;
        if (_Newx < static_cast<typename _Swc_Traits::_UCy_t>(_Carry)) {
            _Underflowed = true;
        }

        _Newx -= _Carry;
        if (_Underflowed) { // underflowed, so add _Mod
            _Newx += _Swc_Traits::_Mod;
            _Carry = _Swc_Traits::_Cy;
        }
        else {
            _Carry = 0;
        }

        this->_Ax[_Ix] = _Newx;
    }

    typename _Swc_Traits::_Cy_t _Carry;
};

template <class _Ty, size_t _Sx, size_t _Rx, class _Swc_Traits>
_NODISCARD bool operator==(
    const _Swc_base<_Ty, _Sx, _Rx, _Swc_Traits>& _Left, const _Swc_base<_Ty, _Sx, _Rx, _Swc_Traits>& _Right) {
    return _Left._Equals(_Right);
}

template <class _Ty, size_t _Sx, size_t _Rx, class _Swc_Traits>
_NODISCARD bool operator!=(
    const _Swc_base<_Ty, _Sx, _Rx, _Swc_Traits>& _Left, const _Swc_base<_Ty, _Sx, _Rx, _Swc_Traits>& _Right) {
    return !_Left._Equals(_Right);
}

template <class _Elem, class _Traits, class _Ty, size_t _Sx, size_t _Rx, class _Swc_Traits>
basic_istream<_Elem, _Traits>& operator>>(
    basic_istream<_Elem, _Traits>& _Istr, _Swc_base<_Ty, _Sx, _Rx, _Swc_Traits>& _Eng) { // read state from _Istr
    _Wrap_istream<_Elem, _Traits, typename _Swc_Traits::_Seed_t> _Gen(_Istr);
    _Eng.seed(_Gen, true);
    return _Istr;
}

template <class _Elem, class _Traits, class _Ty, size_t _Sx, size_t _Rx, class _Swc_Traits>
basic_ostream<_Elem, _Traits>& operator<<(
    basic_ostream<_Elem, _Traits>& _Ostr, const _Swc_base<_Ty, _Sx, _Rx, _Swc_Traits>& _Eng) { // write state to _Ostr
    return _Eng._Write(_Ostr);
}

template <class _Ty, size_t _Sx, size_t _Rx, class _Swc_Traits>
const size_t _Swc_base<_Ty, _Sx, _Rx, _Swc_Traits>::short_lag;

template <class _Ty, size_t _Sx, size_t _Rx, class _Swc_Traits>
const size_t _Swc_base<_Ty, _Sx, _Rx, _Swc_Traits>::long_lag;

template <class _Ty, _Ty _Mx, size_t _Nw>
struct _Swc_traits { // traits for subtract_with_carry generator
    using _Cy_t = int;
    using _UCy_t = unsigned int;
    using _Mod_t = _Ty;
    using _Seed_t = _Ty;

    static constexpr _Cy_t _Cy = 1;
    static constexpr _Mod_t _Mod = _Mx;
    static constexpr _Ty _Max = _Mx - 1;

    static int _Get_wc() { // compute number of 32-bit words per element
        int _Kx;

        if constexpr (_Mx == 0) {
            _Kx = (8 * sizeof(_Ty) + 31) / 32;
        }
        else { // compute number of 32-bit words required
            unsigned long long _Val = 1ULL << 32;
            for (_Kx = 1; 0 < _Val && _Val < _Mx; ++_Kx) {
                _Val = _Val << 32;
            }
        }

        return _Kx;
    }

    template <class _Gen>
    static _Cy_t _Reset(_Gen& _Gx, _Ty* _Ax, bool _Readcy) { // set initial values of _Ax from generator _Gx
                                                             // return value of _Cy from range if _Readcy is true,
                                                             // otherwise compute from last value
        int _Kx = _Get_wc();

        for (size_t _Ix = 0; _Ix < _Nw; ++_Ix) { // pack _Kx words
            _Ax[_Ix] = _Gx();
            for (int _Jx = 1; _Jx < _Kx; ++_Jx) {
                _Ax[_Ix] |= static_cast<_Ty>(_Gx()) << (32 * _Jx);
            }
        }

        _Cy_t _Ans = _Reduce(_Ax);
        if (!_Readcy) {
            return _Ans;
        }
        else {
            return static_cast<_Cy_t>(_Gx()); // TRANSITION, investigate this conversion
        }
    }

#pragma warning(push)
#pragma warning(disable : 4724) // potential mod by 0
    static _Cy_t _Reduce(_Ty* _Ax) { // reduce values to allowed range
        if constexpr (_Mx != 0) {
            for (size_t _Ix = 0; _Ix < _Nw; ++_Ix) {
                _Ax[_Ix] = _Ax[_Ix] % _Mx;
            }
        }

        return _Ax[_Nw - 1] == 0;
    }
#pragma warning(pop)

    template <class _Elem, class _Traits>
    static void _Write(
        basic_ostream<_Elem, _Traits>& _Ostr, const _Circ_buf<_Ty, _Nw>& _Buf, _Cy_t _Cy) { // write state to _Ostr
        int _Kx = _Get_wc();

        for (size_t _Ix = 0; _Ix < _Nw; ++_Ix) {
            for (int _Jx = 0; _Jx < _Kx; ++_Jx) { // unpack into _Kx words
                const unsigned int _Word = static_cast<unsigned int>(_Buf._At(_Ix) >> (_Jx * 32));
                _Ostr << _Word << ' ';
            }
        }

        _Ostr << _Cy;
    }

    template <class _Elem, class _Traits>
    static void _Write_full(
        basic_ostream<_Elem, _Traits>& _Ostr, const _Circ_buf<_Ty, _Nw>& _Buf, _Cy_t _Cy) { // write state to _Ostr
        for (size_t _Ix = 0; _Ix < _Nw; ++_Ix) {
            _Ostr << _Buf._At(_Ix) << ' ';
        }

        _Ostr << _Cy;
    }
};

template <class _Ty, _Ty _Mx, size_t _Sx, size_t _Rx>
class subtract_with_carry
    : public _Swc_base<_Ty, _Sx, _Rx, _Swc_traits<_Ty, _Mx, _Rx>> { // subtract_with_carry generator
public:
    using _Mybase = _Swc_base<_Ty, _Sx, _Rx, _Swc_traits<_Ty, _Mx, _Rx>>;

    static constexpr _Ty modulus = _Mx;

    using _Mybase::default_seed;

    subtract_with_carry() : _Mybase(default_seed) {}

    explicit subtract_with_carry(_Ty _Xx0) : _Mybase(_Xx0) {}

    template <class _Gen, _Enable_if_seed_seq_t<_Gen, subtract_with_carry> = 0>
    subtract_with_carry(_Gen& _Gx) : _Mybase(_Gx) {}
};

template <class _Ty, size_t _Wx, size_t _Sx, size_t _Rx>
class subtract_with_carry_engine : public subtract_with_carry < _Ty, (_Ty{ 1 } << (_Wx - 1)) << 1, _Sx, _Rx > {
    // subtract_with_carry generator
public:
    _RNG_REQUIRE_UINTTYPE(subtract_with_carry_engine, _Ty);

    static_assert(0U < _Sx && _Sx < _Rx && 0 < _Wx && _Wx <= numeric_limits<_Ty>::digits,
        "invalid template argument for subtract_with_carry_engine");

    static constexpr _Ty _Mx = (_Ty{ 1 } << (_Wx - 1)) << 1;
    static constexpr size_t word_size = _Wx;
    static constexpr size_t short_lag = _Sx;
    static constexpr size_t long_lag = _Rx;

    using _Mybase = subtract_with_carry<_Ty, _Mx, _Sx, _Rx>;
    using _Traits = typename _Mybase::_Traits;
    using result_type = _Ty;

    using _Mybase::default_seed;

    subtract_with_carry_engine() : _Mybase(default_seed) {}

    explicit subtract_with_carry_engine(_Ty _Xx0) : _Mybase(_Xx0) {}

    template <class _Seed_seq, _Enable_if_seed_seq_t<_Seed_seq, subtract_with_carry_engine> = 0>
    explicit subtract_with_carry_engine(_Seed_seq& _Seq) : _Mybase() {
        seed(_Seq);
    }

    void seed(_Ty _Value = default_seed) { // set initial values from specified seed value
        this->_Seed(_Value, false, true_type{});
    }

    static constexpr int _Kx = (8 * sizeof(_Ty) + 31) / 32;

    template <class _Seed_seq, _Enable_if_seed_seq_t<_Seed_seq, subtract_with_carry_engine> = 0>
    void seed(_Seed_seq& _Seq) { // reset sequence from seed sequence
        unsigned long _Arr[_Kx * _Rx];
        _Seq.generate(&_Arr[0], &_Arr[_Kx * _Rx]);

        size_t _Idx0 = 0;
        for (size_t _Ix = 0; _Ix < _Rx; ++_Ix, _Idx0 += _Kx) { // pack _Kx words
            this->_Ax[_Ix] = _Arr[_Idx0];
            for (int _Jx = 1; _Jx < _Kx; ++_Jx) {
                this->_Ax[_Ix] |= static_cast<_Ty>(_Arr[_Idx0 + _Jx]) << (32 * _Jx);
            }

            constexpr bool _Mod_non_zero = _Traits::_Mod != 0;
            if constexpr (_Mod_non_zero) {
                this->_Ax[_Ix] %= _Traits::_Mod;
            }
        }

        this->_Carry = _Traits::_Reduce(this->_Ax);
        this->_Idx = _Rx;
    }

    _NODISCARD static constexpr _Ty(min)() {
        return 0;
    }

    _NODISCARD static constexpr _Ty(max)() {
        return _Mx - 1;
    }

    template <class _Elem, class _Traits>
    friend basic_ostream<_Elem, _Traits>& operator<<(
        basic_ostream<_Elem, _Traits>& _Ostr, const subtract_with_carry_engine& _Eng) {
        const auto _Save_flags = _Ostr.flags(ios_base::dec | ios_base::left);
        const auto _Save_fill = _Ostr.fill(' ');
        _Eng._Write_full(_Ostr);
        _Ostr.flags(_Save_flags);
        _Ostr.fill(_Save_fill);
        return _Ostr;
    }

    template <class _Elem, class _Traits>
    friend basic_istream<_Elem, _Traits>& operator>>(
        basic_istream<_Elem, _Traits>& _Istr, subtract_with_carry_engine& _Eng) {
        constexpr auto _Nx = long_lag;
        result_type _Buffer[_Nx];
        typename _Mybase::_Traits::_Cy_t _Carry_buf;
        const auto _Save_flags = _Istr.flags(ios_base::dec | ios_base::skipws);
        for (size_t _Ix = 0; _Ix < _Nx; ++_Ix) {
            _Istr >> _Buffer[_Ix];
        }

        _Istr >> _Carry_buf;
        if (_Istr) {
            for (size_t _Ix = 0; _Ix < _Nx; ++_Ix) {
                _Eng._Ax[_Ix] = _Buffer[_Ix];
            }

            _Eng._Carry = _Carry_buf;
            _Eng._Idx = _Nx;
        }
        else {
            _Istr.setstate(ios_base::failbit);
        }

        _Istr.flags(_Save_flags);
        return _Istr;
    }
};

#if _HAS_TR1_NAMESPACE
template <class _Ty, size_t _Wx, size_t _Rx>
struct _Swc_01_traits { // traits for subtract_with_carry_01 generator
    using _Cy_t = _Ty;
    using _UCy_t = _Ty;
    using _Mod_t = _Ty;
    using _Seed_t = unsigned int;

    static const _Cy_t _Cy;
    static const _Mod_t _Mod;
    static const _Ty _Max;
    static constexpr int _Nwords = (_Wx + 31) / 32;

    template <class _Gen>
    static _Cy_t _Reset(_Gen& _Gx, _Ty* _Ax, bool _Readcy) { // set initial values of _Ax from generator _Gx
                                                             // return value of _Cy from range if _Readcy is true,
                                                             // otherwise from last value
        for (size_t _Ix = 0; _Ix < _Rx; ++_Ix) { // read values
            _Ty _Factor = 1;
            _Ty _Val = 0;
            for (int _Jx = 0; _Jx < _Nwords - 1; ++_Jx) { // read components of value
                _Factor /= static_cast<_Ty>(_Two32);
                _Val += _Gx() * _Factor;
            }
            _Ty _Temp = (static_cast<unsigned long>(_Gx()) & _Mask) / _Scale1;
            _Val += (_Temp - static_cast<unsigned long>(_Temp)) * _Factor;
            _Ax[_Ix] = _Val;
        }
        if (!_Readcy) {
            return _Ax[_Rx - 1] != 0 ? 0 : _Cy;
        }
        else {
            return _Gx() == 0 ? 0 : _Cy;
        }
    }

    template <class _Elem, class _Traits>
    static void _Write(
        basic_ostream<_Elem, _Traits>& _Ostr, const _Circ_buf<_Ty, _Rx>& _Buf, _Cy_t _Cy) { // write state to _Ostr
        for (size_t _Ix = 0; _Ix < _Rx; ++_Ix) { // write values
            _Ty _Val = _Buf._At(_Ix);
            unsigned long _Temp;
            for (int _Jx = 0; _Jx < _Nwords - 1; ++_Jx) { // write components of value
                _Val *= static_cast<_Ty>(_Two32);
                _Temp = static_cast<unsigned long>(_Val);
                _Val -= _Temp;
                _Ostr << _Temp << ' ';
            }
            _Temp = static_cast<unsigned long>(_Val * _Scale1);
            _Ostr << _Temp << ' ';
        }
        _Ostr << (_Cy ? 1 : 0);
    }

private:
    static const _Ty _Scale1;
    static constexpr unsigned long _Mask = ~((~0UL) << (_Wx % 32));
};

template <class _Ty, size_t _Wx, size_t _Rx>
const typename _Swc_01_traits<_Ty, _Wx, _Rx>::_Cy_t
_Swc_01_traits<_Ty, _Wx, _Rx>::_Cy = static_cast<typename _Swc_01_traits<_Ty, _Wx, _Rx>::_Cy_t>(
    _CSTD ldexp(1.0, static_cast<int>(-static_cast<ptrdiff_t>(_Wx))));

template <class _Ty, size_t _Wx, size_t _Rx>
const typename _Swc_01_traits<_Ty, _Wx, _Rx>::_Mod_t _Swc_01_traits<_Ty, _Wx, _Rx>::_Mod = 1;

template <class _Ty, size_t _Wx, size_t _Rx>
const _Ty _Swc_01_traits<_Ty, _Wx, _Rx>::_Max = 1;

template <class _Ty, size_t _Wx, size_t _Rx>
const _Ty _Swc_01_traits<_Ty, _Wx, _Rx>::_Scale1 = static_cast<_Ty>(_CSTD ldexp(1.0, _Wx % 32));

template <class _Ty, size_t _Wx, size_t _Sx, size_t _Rx>
class _DEPRECATE_TR1_NAMESPACE subtract_with_carry_01
    : public _Swc_base<_Ty, _Sx, _Rx, _Swc_01_traits<_Ty, _Wx, _Rx>> { // subtract_with_carry_01 generator
public:
    static constexpr size_t word_size = _Wx;

    using _Mybase = _Swc_base<_Ty, _Sx, _Rx, _Swc_01_traits<_Ty, _Wx, _Rx>>;

    subtract_with_carry_01() : _Mybase() {}

    explicit subtract_with_carry_01(typename _Mybase::_Seed_t _Value) : _Mybase(_Value) {}

    template <class _Gen, _Enable_if_seed_seq_t<_Gen, subtract_with_carry_01> = 0>
    subtract_with_carry_01(_Gen& _Gx) : _Mybase(_Gx) {}
};

_STL_DISABLE_DEPRECATED_WARNING
template <class _Ty, size_t _Wx, size_t _Sx, size_t _Rx>
const size_t subtract_with_carry_01<_Ty, _Wx, _Sx, _Rx>::word_size;
_STL_RESTORE_DEPRECATED_WARNING

#endif // _HAS_TR1_NAMESPACE

template <class _Ty, int _Wx, int _Nx, int _Mx, int _Rx, _Ty _Px, int _Ux, int _Sx, _Ty _Bx, int _Tx, _Ty _Cx, int _Lx>
class mersenne_twister : public _Circ_buf<_Ty, _Nx> { // mersenne twister generator
public:
    using result_type = _Ty;

    static constexpr int word_size = _Wx;
    static constexpr int state_size = _Nx;
    static constexpr int shift_size = _Mx;
    static constexpr int mask_bits = _Rx;
    static constexpr _Ty parameter_a = _Px;
    static constexpr int output_u = _Ux;
    static constexpr int output_s = _Sx;
    static constexpr _Ty output_b = _Bx;
    static constexpr int output_t = _Tx;
    static constexpr _Ty output_c = _Cx;
    static constexpr int output_l = _Lx;

    static constexpr _Ty default_seed = 5489U;

    mersenne_twister() : _Dxval(_WMSK) {
        seed(default_seed, static_cast<_Ty>(1812433253));
    }

    explicit mersenne_twister(_Ty _Xx0, _Ty _Dxarg = _WMSK, _Ty _Fxarg = static_cast<_Ty>(1812433253))
        : _Dxval(_Dxarg) {
        seed(_Xx0, _Fxarg);
    }

    template <class _Gen, _Enable_if_seed_seq_t<_Gen, mersenne_twister> = 0>
    explicit mersenne_twister(_Gen& _Gx) : _Dxval(_WMSK) {
        seed(_Gx);
    }

    void seed(_Ty _Xx0 = default_seed, _Ty _Fx = static_cast<_Ty>(1812433253)) {
        // set initial values from specified value
        _Ty _Prev = this->_Ax[0] = _Xx0 & _WMSK;
        for (size_t _Ix = 1; _Ix < _Nx; ++_Ix) {
            _Prev = this->_Ax[_Ix] = (_Ix + _Fx * (_Prev ^ (_Prev >> (_Wx - 2)))) & _WMSK;
        }

        this->_Idx = _Nx;
    }

    template <class _Gen, _Enable_if_seed_seq_t<_Gen, mersenne_twister> = 0>
    void seed(_Gen& _Gx, bool = false) { // set initial values from range
        for (size_t _Ix = 0; _Ix < _Nx; ++_Ix) {
            this->_Ax[_Ix] = _Gx() & _WMSK;
        }

        this->_Idx = _Nx;
    }

    template <class _Elem, class _S_Traits>
    basic_ostream<_Elem, _S_Traits>& _Write(basic_ostream<_Elem, _S_Traits>& _Ostr) const { // write state to _Ostr
        _Ostr << this->_At(0);

        for (size_t _Ix = 1; _Ix < _Nx; ++_Ix) {
            _Ostr << ' ' << this->_At(_Ix);
        }

        return _Ostr;
    }

    _NODISCARD result_type(min)() const {
        return 0;
    }

    _NODISCARD result_type(max)() const {
        return _WMSK;
    }

    _NODISCARD result_type operator()() {
        if (this->_Idx == _Nx) {
            _Refill_upper();
        }
        else if (2 * _Nx <= this->_Idx) {
            _Refill_lower();
        }

        _Ty _Res = this->_Ax[this->_Idx++] & _WMSK;
        _Res ^= (_Res >> _Ux) & _Dxval;
        _Res ^= (_Res << _Sx) & _Bx;
        _Res ^= (_Res << _Tx) & _Cx;
        _Res ^= (_Res & _WMSK) >> _Lx;
        return _Res;
    }

    void discard(unsigned long long _Nskip) { // discard _Nskip elements
        for (; 0 < _Nskip; --_Nskip) {
            (void)(*this)();
        }
    }

protected:
    _Post_satisfies_(this->_Idx == 0)

        void _Refill_lower() { // compute values for the lower half of the history array
        constexpr size_t _Wrap_bound_one = _Nx - _One_mod_n;
        constexpr size_t _Wrap_bound_m = _Nx - _M_mod_n;

        if constexpr (_M_mod_n == 0) {
            for (size_t _Ix = 0; _Ix < _Wrap_bound_one; ++_Ix) { // fill in values
                const _Ty _Tmp = (this->_Ax[_Ix + _Nx] & _HMSK) | (this->_Ax[_Ix + _Nx + _One_mod_n] & _LMSK);
                this->_Ax[_Ix] = (_Tmp >> 1) ^ (_Tmp & 1 ? _Px : 0) ^ this->_Ax[_Ix + _Nx + _M_mod_n];
            }

            if constexpr (_One_mod_n == 1) { // fill in _Ax[_Nx - 1]
                constexpr size_t _Ix = _Wrap_bound_one;

                const _Ty _Tmp = (this->_Ax[_Ix + _Nx] & _HMSK) | (this->_Ax[_Ix - _Nx + _One_mod_n] & _LMSK);
                this->_Ax[_Ix] = (_Tmp >> 1) ^ (_Tmp & 1 ? _Px : 0) ^ this->_Ax[_Ix + _Nx + _M_mod_n];
            }
        }
        else {
            for (size_t _Ix = 0; _Ix < _Wrap_bound_m; ++_Ix) { // fill in lower region
                const _Ty _Tmp = (this->_Ax[_Ix + _Nx] & _HMSK) | (this->_Ax[_Ix + _Nx + _One_mod_n] & _LMSK);
                this->_Ax[_Ix] = (_Tmp >> 1) ^ (_Tmp & 1 ? _Px : 0) ^ this->_Ax[_Ix + _Nx + _M_mod_n];
            }

            for (size_t _Ix = _Wrap_bound_m; _Ix < _Wrap_bound_one; ++_Ix) {
                // fill in upper region (avoids modulus operation)
                const _Ty _Tmp = (this->_Ax[_Ix + _Nx] & _HMSK) | (this->_Ax[_Ix + _Nx + _One_mod_n] & _LMSK);
                this->_Ax[_Ix] = (_Tmp >> 1) ^ (_Tmp & 1 ? _Px : 0) ^ this->_Ax[_Ix - _Nx + _M_mod_n];
            }

            if constexpr (_One_mod_n == 1) { // fill in _Ax[_Nx - 1]
                constexpr size_t _Ix = _Wrap_bound_one;

                const _Ty _Tmp = (this->_Ax[_Ix + _Nx] & _HMSK) | (this->_Ax[_Ix - _Nx + _One_mod_n] & _LMSK);
                this->_Ax[_Ix] = (_Tmp >> 1) ^ (_Tmp & 1 ? _Px : 0) ^ this->_Ax[_Ix - _Nx + _M_mod_n];
            }
        }

        this->_Idx = 0;
    }

    void _Refill_upper() { // compute values for the upper half of the history array
        for (size_t _Ix = _Nx; _Ix < 2 * _Nx; ++_Ix) { // fill in values
            const _Ty _Tmp = (this->_Ax[_Ix - _Nx] & _HMSK) | (this->_Ax[_Ix - _Nx + _One_mod_n] & _LMSK);
            this->_Ax[_Ix] = (_Tmp >> 1) ^ (_Tmp & 1 ? _Px : 0) ^ this->_Ax[_Ix - _Nx + _M_mod_n];
        }
    }

    _Ty _Dxval;

    static constexpr _Ty _WMSK = ~((~_Ty{ 0 } << (_Wx - 1)) << 1);
    static constexpr _Ty _HMSK = (_WMSK << _Rx) & _WMSK;
    static constexpr _Ty _LMSK = ~_HMSK & _WMSK;

    static constexpr int _One_mod_n = 1 % _Nx; // either 0 or 1
    static constexpr int _M_mod_n = _Mx % _Nx;
};

template <class _Ty, int _Wx, int _Nx, int _Mx, int _Rx, _Ty _Px, int _Ux, int _Sx, _Ty _Bx, int _Tx, _Ty _Cx, int _Lx>
_NODISCARD bool operator==(const mersenne_twister<_Ty, _Wx, _Nx, _Mx, _Rx, _Px, _Ux, _Sx, _Bx, _Tx, _Cx, _Lx>& _Left,
    const mersenne_twister<_Ty, _Wx, _Nx, _Mx, _Rx, _Px, _Ux, _Sx, _Bx, _Tx, _Cx, _Lx>& _Right) {
    return _Left._Equals(_Right);
}

template <class _Ty, int _Wx, int _Nx, int _Mx, int _Rx, _Ty _Px, int _Ux, int _Sx, _Ty _Bx, int _Tx, _Ty _Cx, int _Lx>
_NODISCARD bool operator!=(const mersenne_twister<_Ty, _Wx, _Nx, _Mx, _Rx, _Px, _Ux, _Sx, _Bx, _Tx, _Cx, _Lx>& _Left,
    const mersenne_twister<_Ty, _Wx, _Nx, _Mx, _Rx, _Px, _Ux, _Sx, _Bx, _Tx, _Cx, _Lx>& _Right) {
    return !_Left._Equals(_Right);
}

template <class _Elem, class _S_Traits, class _Ty, int _Wx, int _Nx, int _Mx, int _Rx, _Ty _Px, int _Ux, int _Sx,
    _Ty _Bx, int _Tx, _Ty _Cx, int _Lx>
    basic_istream<_Elem, _S_Traits>& operator>>(basic_istream<_Elem, _S_Traits>& _Istr,
        mersenne_twister<_Ty, _Wx, _Nx, _Mx, _Rx, _Px, _Ux, _Sx, _Bx, _Tx, _Cx, _Lx>& _Eng) { // read state from _Istr
    _Wrap_istream<_Elem, _S_Traits, _Ty> _Gen(_Istr);
    _Eng.seed(_Gen);
    return _Istr;
}

template <class _Elem, class _S_Traits, class _Ty, int _Wx, int _Nx, int _Mx, int _Rx, _Ty _Px, int _Ux, int _Sx,
    _Ty _Bx, int _Tx, _Ty _Cx, int _Lx>
    basic_ostream<_Elem, _S_Traits>& operator<<(basic_ostream<_Elem, _S_Traits>& _Ostr,
        const mersenne_twister<_Ty, _Wx, _Nx, _Mx, _Rx, _Px, _Ux, _Sx, _Bx, _Tx, _Cx, _Lx>& _Eng) { // write state to _Ostr
    return _Eng._Write(_Ostr);
}

template <class _Ty, size_t _Wx, size_t _Nx, size_t _Mx, size_t _Rx, _Ty _Px, size_t _Ux, _Ty _Dx, size_t _Sx, _Ty _Bx,
    size_t _Tx, _Ty _Cx, size_t _Lx, _Ty _Fx>
    class mersenne_twister_engine : public mersenne_twister<_Ty, _Wx, _Nx, _Mx, _Rx, _Px, _Ux, _Sx, _Bx, _Tx, _Cx, _Lx> {
    public:
        static constexpr unsigned long long _Max = (((1ULL << (_Wx - 1)) - 1) << 1) + 1;

        _RNG_REQUIRE_UINTTYPE(mersenne_twister_engine, _Ty);

        static_assert(0 < _Mx && _Mx <= _Nx && 2U < _Wx && _Rx <= _Wx && _Ux <= _Wx && _Sx <= _Wx && _Tx <= _Wx
            && _Lx <= _Wx && _Wx <= numeric_limits<_Ty>::digits && _Px <= _Max && _Bx <= _Max && _Cx <= _Max
            && _Dx <= _Max && _Fx <= _Max,
            "invalid template argument for mersenne_twister_engine");

        using _Mybase = mersenne_twister<_Ty, _Wx, _Nx, _Mx, _Rx, _Px, _Ux, _Sx, _Bx, _Tx, _Cx, _Lx>;
        using result_type = _Ty;

        static constexpr size_t word_size = _Wx;
        static constexpr size_t state_size = _Nx;
        static constexpr size_t shift_size = _Mx;
        static constexpr size_t mask_bits = _Rx;
        static constexpr _Ty xor_mask = _Px;
        static constexpr size_t tempering_u = _Ux;
        static constexpr _Ty tempering_d = _Dx;
        static constexpr size_t tempering_s = _Sx;
        static constexpr _Ty tempering_b = _Bx;
        static constexpr size_t tempering_t = _Tx;
        static constexpr _Ty tempering_c = _Cx;
        static constexpr size_t tempering_l = _Lx;
        static constexpr _Ty initialization_multiplier = _Fx;

        static constexpr result_type default_seed = 5489U;

        mersenne_twister_engine() : _Mybase(default_seed, _Dx, _Fx) {}

        explicit mersenne_twister_engine(result_type _Xx0) : _Mybase(_Xx0, _Dx, _Fx) {}

        template <class _Seed_seq, _Enable_if_seed_seq_t<_Seed_seq, mersenne_twister_engine> = 0>
        explicit mersenne_twister_engine(_Seed_seq& _Seq) : _Mybase(default_seed, _Dx, _Fx) {
            seed(_Seq);
        }

        void seed(result_type _Xx0 = default_seed) { // set initial values from specified value
            _Mybase::seed(_Xx0, _Fx);
        }

        template <class _Seed_seq, _Enable_if_seed_seq_t<_Seed_seq, mersenne_twister_engine> = 0>
        void seed(_Seed_seq& _Seq) { // reset sequence from seed sequence
            constexpr int _Kx = (_Wx + 31) / 32;
            unsigned long _Arr[_Kx * _Nx];
            _Seq.generate(&_Arr[0], &_Arr[_Kx * _Nx]);

            int _Idx0 = 0;
            _Ty _Sum = 0;
            for (size_t _Ix = 0; _Ix < _Nx; ++_Ix, _Idx0 += _Kx) { // pack _Kx words
                this->_Ax[_Ix] = static_cast<_Ty>(_Arr[_Idx0]);
                for (int _Jx = 1; _Jx < _Kx; ++_Jx) {
                    this->_Ax[_Ix] |= static_cast<_Ty>(_Arr[_Idx0 + _Jx]) << (32 * _Jx);
                }

                this->_Ax[_Ix] &= this->_WMSK;

                if (_Ix == 0) {
                    _Sum = this->_Ax[_Ix] >> _Rx;
                }
                else {
                    _Sum |= this->_Ax[_Ix];
                }
            }

            if (_Sum == 0) {
                this->_Ax[0] = _Ty{ 1 } << (_Wx - 1);
            }

            this->_Idx = _Nx;
        }

        _NODISCARD static constexpr result_type(min)() {
            return 0;
        }

        _NODISCARD static constexpr result_type(max)() {
            return _Mybase::_WMSK;
        }
};

template <class _Engine, int _Px, int _Rx>
class discard_block { // discard_block compound engine
public:
    using base_type = _Engine;
    using result_type = typename _Engine::result_type;

    static constexpr int block_size = _Px;
    static constexpr int used_block = _Rx;

    discard_block() : _Eng(), _Nx(0) {}

    explicit discard_block(const _Engine& _Ex) : _Eng(_Ex), _Nx(0) {}

    explicit discard_block(result_type _Seed) : _Eng(_Seed), _Nx(0) {}

    template <class _Seed_seq, _Enable_if_seed_seq_t<_Seed_seq, discard_block, _Engine> = 0>
    explicit discard_block(_Seed_seq& _Seq) : _Eng(_Seq), _Nx(0) {}

    void seed() { // seed engine from default value
        _Eng.seed();
        _Nx = 0;
    }

    void seed(result_type _Xx0) { // seed engine from specified value
        _Eng.seed(_Xx0);
        _Nx = 0;
    }

    template <class _Seed_seq, _Enable_if_seed_seq_t<_Seed_seq, discard_block> = 0>
    void seed(_Seed_seq& _Seq) { // seed engine from seed sequence
        _Eng.seed(_Seq);
        _Nx = 0;
    }

    _NODISCARD const base_type& base() const noexcept {
        return _Eng;
    }

    _NODISCARD result_type(min)() const {
        return (_Eng.min) ();
    }

    _NODISCARD result_type(max)() const {
        return (_Eng.max) ();
    }

    _NODISCARD result_type operator()() {
        if (_Rx <= _Nx) { // discard values
            while (_Nx++ < _Px) {
                (void)_Eng();
            }

            _Nx = 0;
        }
        ++_Nx;
        return _Eng();
    }

    void discard(unsigned long long _Nskip) { // discard _Nskip elements
        for (; 0 < _Nskip; --_Nskip) {
            (void)(*this)();
        }
    }

    bool _Equals(const discard_block& _Right) const {
        return _Eng == _Right._Eng && _Nx == _Right._Nx;
    }

    template <class _Elem, class _Traits>
    basic_istream<_Elem, _Traits>& _Read(basic_istream<_Elem, _Traits>& _Istr) { // read state from _Istr
        return _Istr >> _Eng >> _Nx;
    }

    template <class _Elem, class _Traits>
    basic_ostream<_Elem, _Traits>& _Write(basic_ostream<_Elem, _Traits>& _Ostr) const { // write state to _Ostr
        return _Ostr << _Eng << ' ' << _Nx;
    }

private:
    base_type _Eng;
    int _Nx;
};

template <class _Engine, int _Px, int _Rx>
const int discard_block<_Engine, _Px, _Rx>::block_size;

template <class _Engine, int _Px, int _Rx>
const int discard_block<_Engine, _Px, _Rx>::used_block;

template <class _Engine, int _Px, int _Rx>
_NODISCARD bool operator==(
    const discard_block<_Engine, _Px, _Rx>& _Left, const discard_block<_Engine, _Px, _Rx>& _Right) {
    return _Left._Equals(_Right);
}

template <class _Engine, int _Px, int _Rx>
_NODISCARD bool operator!=(
    const discard_block<_Engine, _Px, _Rx>& _Left, const discard_block<_Engine, _Px, _Rx>& _Right) {
    return !(_Left == _Right);
}

template <class _Elem, class _Traits, class _Engine, int _Px, int _Rx>
basic_istream<_Elem, _Traits>& operator>>(
    basic_istream<_Elem, _Traits>& _Istr, discard_block<_Engine, _Px, _Rx>& _Eng) { // read state from _Istr
    return _Eng._Read(_Istr);
}

template <class _Elem, class _Traits, class _Engine, int _Px, int _Rx>
basic_ostream<_Elem, _Traits>& operator<<(
    basic_ostream<_Elem, _Traits>& _Ostr, const discard_block<_Engine, _Px, _Rx>& _Eng) { // write state to _Ostr
    return _Eng._Write(_Ostr);
}

template <class _Engine, size_t _Px, size_t _Rx>
class discard_block_engine : public discard_block<_Engine, _Px, _Rx> { // discard_block_engine compound engine
public:
    static_assert(0 < _Rx && _Rx <= _Px, "invalid template argument for discard_block_engine");

    using _Mybase = discard_block<_Engine, _Px, _Rx>;
    using result_type = typename _Engine::result_type;

    discard_block_engine() : _Mybase() {}

    explicit discard_block_engine(const _Engine& _Ex) : _Mybase(_Ex) {}

    explicit discard_block_engine(_Engine&& _Ex) : _Mybase(_STD move(_Ex)) {}

    explicit discard_block_engine(result_type _Xx0) : _Mybase(_Xx0) {}

    template <class _Seed_seq, _Enable_if_seed_seq_t<_Seed_seq, discard_block_engine, _Engine> = 0>
    explicit discard_block_engine(_Seed_seq& _Seq) : _Mybase(_Seq) {}

    _NODISCARD static constexpr typename _Engine::result_type(min)() {
        return (_Engine::min)();
    }

    _NODISCARD static constexpr typename _Engine::result_type(max)() {
        return (_Engine::max)();
    }
};

template <class _Engine, size_t _Wx, class _UIntType>
class independent_bits_engine { // independent_bits_engine compound engine
public:
    _RNG_REQUIRE_UINTTYPE(independent_bits_engine, _UIntType);

    static_assert(
        0 < _Wx && _Wx <= numeric_limits<_UIntType>::digits, "invalid template argument for independent_bits_engine");

    using base_type = _Engine;
    using result_type = _UIntType;
    using _Eres = typename _Engine::result_type;

    independent_bits_engine() {
        _Init();
    }

    explicit independent_bits_engine(const _Engine& _Ex) : _Eng(_Ex) {
        _Init();
    }

    explicit independent_bits_engine(_Engine&& _Ex) : _Eng(_STD move(_Ex)) {
        _Init();
    }

    explicit independent_bits_engine(result_type _Xx0) : _Eng(static_cast<_Eres>(_Xx0)) {
        _Init();
    }

    template <class _Seed_seq, _Enable_if_seed_seq_t<_Seed_seq, independent_bits_engine, _Engine> = 0>
    explicit independent_bits_engine(_Seed_seq& _Seq) : _Eng(_Seq) {
        _Init();
    }

    void seed() { // seed engine from default value
        _Eng.seed();
    }

    void seed(result_type _Xx0) { // seed engine from specified value
        _Eng.seed(static_cast<_Eres>(_Xx0));
    }

    template <class _Seed_seq, _Enable_if_seed_seq_t<_Seed_seq, independent_bits_engine> = 0>
    void seed(_Seed_seq& _Seq) { // seed engine from seed sequence
        _Eng.seed(_Seq);
    }

    _NODISCARD const _Engine& base() const noexcept {
        return _Eng;
    }

    _NODISCARD static constexpr result_type(min)() {
        return 0;
    }

    _NODISCARD static constexpr result_type(max)() {
        return ((result_type{ 1 } << (_Wx - 1)) << 1) - 1;
    }

    _NODISCARD result_type operator()() {
        size_t _Idx = 0;
        result_type _Res = 0;
        result_type _Mask = ((result_type{ 1 } << (_Wx0 - 1)) << 1) - 1;
        _Eres _Val;

        for (; _Idx < _Nx0; ++_Idx) { // pack _Wx0-bit values
            for (;;) { // get a small enough value
                _Val = _Eng() - (_Engine::min)();
                if (_Val <= _Yx0) {
                    break;
                }
            }
            _Res = _Res << _Wx0 | (static_cast<result_type>(_Val) & _Mask);
        }

        _Mask = _Mask << 1 | 1;
        for (; _Idx < _Nx; ++_Idx) { // pack _Wx0+1-bit values
            for (;;) { // get a small enough value
                _Val = _Eng() - (_Engine::min)();
                if (_Val <= _Yx1) {
                    break;
                }
            }
            _Res = _Res << (_Wx0 + 1) | (static_cast<result_type>(_Val) & _Mask);
        }
        return _Res;
    }

    void discard(unsigned long long _Nskip) { // discard _Nskip elements
        for (; 0 < _Nskip; --_Nskip) {
            (void)(*this)();
        }
    }

    template <class _Elem, class _Traits>
    basic_istream<_Elem, _Traits>& _Read(basic_istream<_Elem, _Traits>& _Istr) { // read state from _Istr
        return _Istr >> _Eng;
    }

    template <class _Elem, class _Traits>
    basic_ostream<_Elem, _Traits>& _Write(basic_ostream<_Elem, _Traits>& _Ostr) const { // write state to _Ostr
        return _Ostr << _Eng;
    }

private:
    void _Init() { // compute values for operator()
        size_t _Mx = 0;
        _Eres _Rx = (_Engine::max)() - (_Engine::min)() + 1;

        _Eres _Tmp = _Rx;
        if (_Tmp == 0) { // all bits used, make _Rx finite
            _Mx = 1;
            --_Tmp;
        }
        for (; 1 < _Tmp; _Tmp >>= 1) {
            ++_Mx; // compute _Mx = floor(log2(_Rx))
        }

        for (size_t _Nfix = 0;; ++_Nfix) { // compute consistent set of parameters
            _Nx = (_Wx + _Mx - 1) / _Mx + _Nfix; // trial _Nx
            _Wx0 = _Wx / _Nx;
            _Nx0 = _Nx - _Wx % _Nx;
            _Yx0 = (_Rx >> _Wx0) << _Wx0;
            _Yx1 = (((_Rx >> _Wx0) >> 1) << _Wx0) << 1;
            if (_Nfix == 1 || _Rx - _Yx0 <= _Yx0 / _Nx) {
                break; // also works if _Rx == 0 (_Mx == all bits)
            }
        }
        --_Yx0;
        --_Yx1;
    }

    _Engine _Eng; // the stored engine
    size_t _Nx0; // number of smaller packing words
    size_t _Nx; // total number of packing words
    size_t _Wx0; // bits per smaller packing word
    _Eres _Yx0; // max value for smaller packing word
    _Eres _Yx1; // max value for larger packing word
};

template <class _Engine, size_t _Wx, class _UIntType>
_NODISCARD bool operator==(const independent_bits_engine<_Engine, _Wx, _UIntType>& _Left,
    const independent_bits_engine<_Engine, _Wx, _UIntType>& _Right) {
    return _Left.base() == _Right.base();
}

template <class _Engine, size_t _Wx, class _UIntType>
_NODISCARD bool operator!=(const independent_bits_engine<_Engine, _Wx, _UIntType>& _Left,
    const independent_bits_engine<_Engine, _Wx, _UIntType>& _Right) {
    return !(_Left == _Right);
}

template <class _Elem, class _Traits, class _Engine, size_t _Wx, class _UIntType>
basic_istream<_Elem, _Traits>& operator>>(basic_istream<_Elem, _Traits>& _Istr,
    independent_bits_engine<_Engine, _Wx, _UIntType>& _Eng) { // read state from _Istr
    return _Eng._Read(_Istr);
}

template <class _Elem, class _Traits, class _Engine, size_t _Wx, class _UIntType>
basic_ostream<_Elem, _Traits>& operator<<(basic_ostream<_Elem, _Traits>& _Ostr,
    const independent_bits_engine<_Engine, _Wx, _UIntType>& _Eng) { // write state to _Ostr
    return _Eng._Write(_Ostr);
}

template <class _Engine, size_t _Kx>
class shuffle_order_engine { // shuffle_order_engine compound engine
public:
    static_assert(0 < _Kx, "invalid template argument for shuffle_order_engine");

    using base_type = _Engine;
    using result_type = typename _Engine::result_type;

    static constexpr size_t table_size = _Kx;

    shuffle_order_engine() {
        _Init();
    }

    explicit shuffle_order_engine(const _Engine& _Ex) : _Eng(_Ex) {
        _Init();
    }

    explicit shuffle_order_engine(_Engine&& _Ex) : _Eng(_STD move(_Ex)) {
        _Init();
    }

    explicit shuffle_order_engine(result_type _Xx0) : _Eng(_Xx0) {
        _Init();
    }

    template <class _Seed_seq, _Enable_if_seed_seq_t<_Seed_seq, shuffle_order_engine, _Engine> = 0>
    explicit shuffle_order_engine(_Seed_seq& _Seq) : _Eng(_Seq) {
        _Init();
    }

    void seed() { // seed engine from default value
        _Eng.seed();
        _Init();
    }

    void seed(result_type _Xx0) { // seed engine from specified value
        _Eng.seed(_Xx0);
        _Init();
    }

    template <class _Seed_seq, _Enable_if_seed_seq_t<_Seed_seq, shuffle_order_engine> = 0>
    void seed(_Seed_seq& _Seq) { // seed engine from seed sequence
        _Eng.seed(_Seq);
        _Init();
    }

    _NODISCARD const _Engine& base() const noexcept {
        return _Eng;
    }

    _NODISCARD static constexpr result_type(min)() {
        return (_Engine::min)();
    }

    _NODISCARD static constexpr result_type(max)() {
        return (_Engine::max)();
    }

    _NODISCARD result_type operator()() {
        size_t _Idx = static_cast<size_t>(static_cast<double>(_Yx - (_Eng.min) ()) * _Scale);

        _Yx = _Arr[_Idx];
        _Arr[_Idx] = _Eng();
        return _Yx;
    }

    void discard(unsigned long long _Nskip) { // discard _Nskip elements
        for (; 0 < _Nskip; --_Nskip) {
            (void)(*this)();
        }
    }

    template <class _Elem, class _Traits>
    basic_istream<_Elem, _Traits>& _Read(basic_istream<_Elem, _Traits>& _Istr) { // read state from _Istr
        _Istr >> _Eng;
        for (size_t _Idx = 0; _Idx < _Kx; ++_Idx) {
            _Istr >> _Arr[_Idx];
        }

        return _Istr >> _Yx;
    }

    template <class _Elem, class _Traits>
    basic_ostream<_Elem, _Traits>& _Write(basic_ostream<_Elem, _Traits>& _Ostr) const { // write state to _Ostr
        _Ostr << _Eng;
        for (size_t _Idx = 0; _Idx < _Kx; ++_Idx) {
            _Ostr << ' ' << _Arr[_Idx];
        }

        return _Ostr << ' ' << _Yx;
    }

private:
    void _Init() { // compute values for operator()
        for (size_t _Idx = 0; _Idx < _Kx; ++_Idx) {
            _Arr[_Idx] = _Eng();
        }

        _Yx = _Eng();
        _Scale =
            static_cast<double>(_Kx) / (static_cast<double>((_Eng.max) ()) - static_cast<double>((_Eng.min) ()) + 1.0);
    }

    _Engine _Eng; // the stored engine
    result_type _Arr[_Kx];
    result_type _Yx;
    double _Scale;
};

template <class _Engine, size_t _Kx>
_NODISCARD bool operator==(
    const shuffle_order_engine<_Engine, _Kx>& _Left, const shuffle_order_engine<_Engine, _Kx>& _Right) {
    return _Left.base() == _Right.base();
}

template <class _Engine, size_t _Kx>
_NODISCARD bool operator!=(
    const shuffle_order_engine<_Engine, _Kx>& _Left, const shuffle_order_engine<_Engine, _Kx>& _Right) {
    return !(_Left == _Right);
}

template <class _Elem, class _Traits, class _Engine, size_t _Kx>
basic_istream<_Elem, _Traits>& operator>>(
    basic_istream<_Elem, _Traits>& _Istr, shuffle_order_engine<_Engine, _Kx>& _Eng) { // read state from _Istr
    return _Eng._Read(_Istr);
}

template <class _Elem, class _Traits, class _Engine, size_t _Kx>
basic_ostream<_Elem, _Traits>& operator<<(
    basic_ostream<_Elem, _Traits>& _Ostr, const shuffle_order_engine<_Engine, _Kx>& _Eng) { // write state to _Ostr
    return _Eng._Write(_Ostr);
}

template <class _Ty = int>
class uniform_int { // uniform integer distribution
public:
    using result_type = _Ty;

    struct param_type { // parameter package
        using distribution_type = uniform_int;

        param_type() {
            _Init(0, 9);
        }

        explicit param_type(result_type _Min0, result_type _Max0 = 9) {
            _Init(_Min0, _Max0);
        }

        _NODISCARD bool operator==(const param_type& _Right) const {
            return _Min == _Right._Min && _Max == _Right._Max;
        }

        _NODISCARD bool operator!=(const param_type& _Right) const {
            return !(*this == _Right);
        }

        _NODISCARD result_type a() const {
            return _Min;
        }

        _NODISCARD result_type b() const {
            return _Max;
        }

        void _Init(_Ty _Min0, _Ty _Max0) { // set internal state
            _STL_ASSERT(_Min0 <= _Max0, "invalid min and max arguments for uniform_int");
            _Min = _Min0;
            _Max = _Max0;
        }

        result_type _Min;
        result_type _Max;
    };

    uniform_int() : _Par(0, 9) {}

    explicit uniform_int(_Ty _Min0, _Ty _Max0 = 9) : _Par(_Min0, _Max0) {}

    explicit uniform_int(const param_type& _Par0) : _Par(_Par0) {}

    _NODISCARD result_type a() const {
        return _Par.a();
    }

    _NODISCARD result_type b() const {
        return _Par.b();
    }

    _NODISCARD param_type param() const {
        return _Par;
    }

    void param(const param_type& _Par0) { // set parameter package
        _Par = _Par0;
    }

    _NODISCARD result_type(min)() const {
        return _Par._Min;
    }

    _NODISCARD result_type(max)() const {
        return _Par._Max;
    }

    void reset() {} // clear internal state

    template <class _Engine>
    _NODISCARD result_type operator()(_Engine& _Eng) const {
        return _Eval(_Eng, _Par._Min, _Par._Max);
    }

    template <class _Engine>
    _NODISCARD result_type operator()(_Engine& _Eng, const param_type& _Par0) const {
        return _Eval(_Eng, _Par0._Min, _Par0._Max);
    }

    template <class _Engine>
    _NODISCARD result_type operator()(_Engine& _Eng, result_type _Nx) const {
        return _Eval(_Eng, 0, _Nx - 1);
    }

    template <class _Elem, class _Traits>
    basic_istream<_Elem, _Traits>& _Read(basic_istream<_Elem, _Traits>& _Istr) { // read state from _Istr
        _Ty _Min0;
        _Ty _Max0;
        _Istr >> _Min0 >> _Max0;
        _Par._Init(_Min0, _Max0);
        return _Istr;
    }

    template <class _Elem, class _Traits>
    basic_ostream<_Elem, _Traits>& _Write(basic_ostream<_Elem, _Traits>& _Ostr) const { // write state to _Ostr
        return _Ostr << _Par._Min << ' ' << _Par._Max;
    }

private:
    using _Uty = make_unsigned_t<_Ty>;

    template <class _Engine>
    result_type _Eval(_Engine& _Eng, _Ty _Min, _Ty _Max) const { // compute next value in range [_Min, _Max]
        _Rng_from_urng<_Uty, _Engine> _Generator(_Eng);

        const _Uty _Umin = _Adjust(static_cast<_Uty>(_Min));
        const _Uty _Umax = _Adjust(static_cast<_Uty>(_Max));

        _Uty _Uret;

        if (_Umax - _Umin == static_cast<_Uty>(-1)) {
            _Uret = static_cast<_Uty>(_Generator._Get_all_bits());
        }
        else {
            _Uret = static_cast<_Uty>(_Generator(static_cast<_Uty>(_Umax - _Umin + 1)));
        }

        return static_cast<_Ty>(_Adjust(static_cast<_Uty>(_Uret + _Umin)));
    }

    static _Uty _Adjust(_Uty _Uval) { // convert signed ranges to unsigned ranges and vice versa
        if constexpr (is_signed_v<_Ty>) {
            const _Uty _Adjuster = (static_cast<_Uty>(-1) >> 1) + 1; // 2^(N-1)

            if (_Uval < _Adjuster) {
                return static_cast<_Uty>(_Uval + _Adjuster);
            }
            else {
                return static_cast<_Uty>(_Uval - _Adjuster);
            }
        }
        else { // _Ty is already unsigned, do nothing
            return _Uval;
        }
    }

    param_type _Par;
};

template <class _Elem, class _Traits, class _Ty>
basic_istream<_Elem, _Traits>& operator>>(basic_istream<_Elem, _Traits>& _Istr,
    uniform_int<_Ty>& _Dist) { // read state from _Istr
    return _Dist._Read(_Istr);
}

template <class _Elem, class _Traits, class _Ty>
basic_ostream<_Elem, _Traits>& operator<<(basic_ostream<_Elem, _Traits>& _Ostr,
    const uniform_int<_Ty>& _Dist) { // write state to _Ostr
    return _Dist._Write(_Ostr);
}

template <class _Ty = int>
class uniform_int_distribution : public uniform_int<_Ty> { // uniform integer distribution
public:
    _RNG_REQUIRE_INTTYPE(uniform_int_distribution, _Ty);

    using _Mybase = uniform_int<_Ty>;
    using _Mypbase = typename _Mybase::param_type;
    using result_type = typename _Mybase::result_type;

    struct param_type : _Mypbase { // parameter package
        using distribution_type = uniform_int_distribution;

        param_type() : _Mypbase(0, (numeric_limits<_Ty>::max) ()) {}

        explicit param_type(result_type _Min0, result_type _Max0 = (numeric_limits<_Ty>::max) ())
            : _Mypbase(_Min0, _Max0) {}

        param_type(const _Mypbase& _Right) : _Mypbase(_Right) {}
    };

    uniform_int_distribution() : _Mybase(0, (numeric_limits<_Ty>::max) ()) {}

    explicit uniform_int_distribution(_Ty _Min0, _Ty _Max0 = (numeric_limits<_Ty>::max) ()) : _Mybase(_Min0, _Max0) {}

    explicit uniform_int_distribution(const param_type& _Par0) : _Mybase(_Par0) {}
};

template <class _Ty>
_NODISCARD bool operator==(const uniform_int_distribution<_Ty>& _Left, const uniform_int_distribution<_Ty>& _Right) {
    return _Left.param() == _Right.param();
}

template <class _Ty>
_NODISCARD bool operator!=(const uniform_int_distribution<_Ty>& _Left, const uniform_int_distribution<_Ty>& _Right) {
    return !(_Left == _Right);
}

class bernoulli_distribution { // class for bernoulli distribution
public:
    using result_type = bool;

    struct param_type { // parameter package
        using distribution_type = bernoulli_distribution;

        param_type() {
            _Init(0.5);
        }

        explicit param_type(double _Px0) {
            _Init(_Px0);
        }

        _NODISCARD bool operator==(const param_type& _Right) const {
            return _Px == _Right._Px;
        }

        _NODISCARD bool operator!=(const param_type& _Right) const {
            return !(*this == _Right);
        }

        _NODISCARD double p() const {
            return _Px;
        }

        void _Init(double _Px0) { // set internal state
            _STL_ASSERT(0.0 <= _Px0 && _Px0 <= 1.0, "invalid probability argument for bernoulli_distribution");

            _Px = _Px0;
        }

        double _Px;
    };

    bernoulli_distribution() : _Par(0.5) {}

    explicit bernoulli_distribution(double _Px0) : _Par(_Px0) {}

    explicit bernoulli_distribution(const param_type& _Par0) : _Par(_Par0) {}

    _NODISCARD double p() const {
        return _Par.p();
    }

    _NODISCARD param_type param() const {
        return _Par;
    }

    void param(const param_type& _Par0) { // set parameter package
        _Par = _Par0;
    }

    _NODISCARD result_type(min)() const { // get smallest possible result
        return false;
    }

    _NODISCARD result_type(max)() const { // get largest possible result
        return true;
    }

    void reset() {} // clear internal state

    template <class _Engine>
    _NODISCARD result_type operator()(_Engine& _Eng) const {
        return _Eval(_Eng, _Par);
    }

    template <class _Engine>
    _NODISCARD result_type operator()(_Engine& _Eng, const param_type& _Par0) const {
        return _Eval(_Eng, _Par0);
    }

    template <class _Elem, class _Traits>
    basic_istream<_Elem, _Traits>& _Read(basic_istream<_Elem, _Traits>& _Istr) { // read state from _Istr
        double _Px0;
        _In(_Istr, _Px0);
        _Par._Init(_Px0);
        return _Istr;
    }

    template <class _Elem, class _Traits>
    basic_ostream<_Elem, _Traits>& _Write(basic_ostream<_Elem, _Traits>& _Ostr) const { // write state to _Ostr
        _Out(_Ostr, _Par._Px);
        return _Ostr;
    }

private:
    template <class _Engine>
    result_type _Eval(_Engine& _Eng, const param_type& _Par0) const {
        return _NRAND(_Eng, double) < _Par0._Px;
    }

    param_type _Par;
};

_NODISCARD inline bool operator==(const bernoulli_distribution& _Left, const bernoulli_distribution& _Right) {
    return _Left.param() == _Right.param();
}

_NODISCARD inline bool operator!=(const bernoulli_distribution& _Left, const bernoulli_distribution& _Right) {
    return !(_Left == _Right);
}

template <class _Elem, class _Traits>
basic_istream<_Elem, _Traits>& operator>>(basic_istream<_Elem, _Traits>& _Istr,
    bernoulli_distribution& _Dist) { // read state from _Istr
    return _Dist._Read(_Istr);
}

template <class _Elem, class _Traits>
basic_ostream<_Elem, _Traits>& operator<<(basic_ostream<_Elem, _Traits>& _Ostr,
    const bernoulli_distribution& _Dist) { // write state to _Ostr
    return _Dist._Write(_Ostr);
}


// Returns smallest _Flt such that static_cast<_Ty>(_Result) > _Val.
// First truncate to largest _Flt <= _Val, then add ceil(ulp).

template <class _Flt, class _Ty>
_NODISCARD _Flt _Float_upper_bound(_Ty _Val) {
    static_assert(is_unsigned_v<_Ty> && is_integral_v<_Ty> && is_floating_point_v<_Flt>,
        "invalid template argument for _Float_upper_bound");
    constexpr auto _Ty_digits = numeric_limits<_Ty>::digits;
    constexpr auto _Flt_digits = numeric_limits<_Flt>::digits;
    using _Ty_32or64 = conditional_t<_Ty_digits <= 32, uint32_t, uint64_t>;

    if constexpr (_Ty_digits <= _Flt_digits) {
        return static_cast<_Flt>(_Val) + _Flt{ 1 };
    }
    else {
#pragma warning(push)
#pragma warning(disable : 4146 4293) // unary minus of unsigned, negative shift
        constexpr auto _Mask = static_cast<_Ty>(-1) << (_Ty_digits - _Flt_digits);
#ifdef _M_CEE_PURE
        constexpr auto _Ty_32or64_digits = numeric_limits<_Ty_32or64>::digits;
        const auto _Log_plus1 = _Ty_32or64_digits - _Countl_zero_fallback(static_cast<_Ty_32or64>(_Val | _Ty{ 1 }));
#else // _M_CEE_PURE
        const auto _Log_plus1 = _Bit_scan_reverse(static_cast<_Ty_32or64>(_Val | _Ty{ 1 }));
#endif // _M_CEE_PURE
        const auto _Shifted_mask = _Mask >> (_Ty_digits - _Log_plus1);
        const auto _Ceil_ulp = _Shifted_mask & -_Shifted_mask;
        _Val &= _Shifted_mask;
        if (_Val == _Mask) {
            // integer add would overflow
            constexpr auto _Big_ulp = static_cast<_Flt>(_Mask & -_Mask);
            return static_cast<_Flt>(_Val) + _Big_ulp;
        }
        else {
            return static_cast<_Flt>(_Val + _Ceil_ulp);
        }
#pragma warning(pop)
    }
}

template <class _Ty = int>
class geometric_distribution { // geometric distribution
public:
    using _Ty1 = double;

    using result_type = _Ty;

    _RNG_REQUIRE_INTTYPE(geometric_distribution, _Ty);

    struct param_type { // parameter package
        using distribution_type = geometric_distribution;

        param_type() {
            _Init(_Ty1(0.5));
        }

        explicit param_type(_Ty1 _Px0) {
            _Init(_Px0);
        }

        _NODISCARD bool operator==(const param_type& _Right) const {
            return _Px == _Right._Px;
        }

        _NODISCARD bool operator!=(const param_type& _Right) const {
            return !(*this == _Right);
        }

        _NODISCARD _Ty1 p() const {
            return _Px;
        }

        void _Init(_Ty1 _Px0) { // initialize
            _STL_ASSERT(0.0 < _Px0 && _Px0 < 1.0, "invalid probability argument for geometric_distribution");
            _Px = _Px0;
            _Log_1_p = _CSTD log(1 - _Px);
        }

        _Ty1 _Px;
        _Ty1 _Log_1_p;
    };

    geometric_distribution() : _Par(_Ty1(0.5)) {}

    explicit geometric_distribution(_Ty1 _Px0) : _Par(_Px0) {}

    explicit geometric_distribution(const param_type& _Par0) : _Par(_Par0) {}

    _NODISCARD _Ty1 p() const {
        return _Par.p();
    }

    _NODISCARD param_type param() const {
        return _Par;
    }

    void param(const param_type& _Par0) { // set parameter package
        _Par = _Par0;
    }

    _NODISCARD result_type(min)() const { // get smallest possible result
        return 0;
    }

    _NODISCARD result_type(max)() const { // get largest possible result
        return (numeric_limits<result_type>::max) ();
    }

    void reset() {} // clear internal state

    template <class _Engine>
    _NODISCARD result_type operator()(_Engine& _Eng) const {
        return _Eval(_Eng, _Par);
    }

    template <class _Engine>
    _NODISCARD result_type operator()(_Engine& _Eng, const param_type& _Par0) const {
        return _Eval(_Eng, _Par0);
    }

    template <class _Elem, class _Traits>
    basic_istream<_Elem, _Traits>& _Read(basic_istream<_Elem, _Traits>& _Istr) { // read state from _Istr
        _Ty1 _Px0;
        _In(_Istr, _Px0);
        _Par._Init(_Px0);
        return _Istr;
    }

    template <class _Elem, class _Traits>
    basic_ostream<_Elem, _Traits>& _Write(basic_ostream<_Elem, _Traits>& _Ostr) const { // write state to _Ostr
        _Out(_Ostr, _Par._Px);
        return _Ostr;
    }

private:
    template <class _Engine>
    result_type _Eval(_Engine& _Eng, const param_type& _Par0) const {
        using _Uty = make_unsigned_t<_Ty>;
        constexpr auto _Ty_max{ (numeric_limits<_Ty>::max) () };
        const auto _Ty1_max{ _Float_upper_bound<_Ty1>(static_cast<_Uty>(_Ty_max)) };

        _Ty1 _Val;
        do {
            _Val = _CSTD log(_NRAND(_Eng, _Ty1)) / _Par0._Log_1_p;
        } while (_Val >= _Ty1_max);
        return static_cast<_Ty>(_Val);
    }

    param_type _Par;
};

template <class _Ty>
_NODISCARD bool operator==(const geometric_distribution<_Ty>& _Left, const geometric_distribution<_Ty>& _Right) {
    return _Left.param() == _Right.param();
}

template <class _Ty>
_NODISCARD bool operator!=(const geometric_distribution<_Ty>& _Left, const geometric_distribution<_Ty>& _Right) {
    return !(_Left == _Right);
}

template <class _Elem, class _Traits, class _Ty>
basic_istream<_Elem, _Traits>& operator>>(basic_istream<_Elem, _Traits>& _Istr,
    geometric_distribution<_Ty>& _Dist) { // read state from _Istr
    return _Dist._Read(_Istr);
}

template <class _Elem, class _Traits, class _Ty>
basic_ostream<_Elem, _Traits>& operator<<(basic_ostream<_Elem, _Traits>& _Ostr,
    const geometric_distribution<_Ty>& _Dist) { // write state to _Ostr
    return _Dist._Write(_Ostr);
}

template <class _Ty = int>
class _Small_poisson_distribution { // poisson distribution with small mean
public:
    using _Ty1 = double;

    template <class _Engine>
    _NODISCARD _Ty operator()(_Engine& _Eng) const {
        _Ty _Res;
        _Ty1 _Val;
        for (_Res = 0, _Val = 1.0;; ++_Res) { // count repetitions
            _Val *= _NRAND(_Eng, _Ty1);
            if (_Val <= _Gx0) {
                break;
            }
        }
        return _Res;
    }

    void _Init(const _Ty1& _Mean0) { // set internal state
        _Gx0 = _CSTD exp(-_Mean0);
    }

private:
    _Ty1 _Gx0;
};

template <class _Ty = int>
class poisson_distribution { // poisson distribution
public:
    using _Ty1 = double;

    using result_type = _Ty;

    _RNG_REQUIRE_INTTYPE(poisson_distribution, _Ty);

    struct param_type { // parameter package
        using distribution_type = poisson_distribution;

        param_type() {
            _Init(_Ty1(1));
        }

        explicit param_type(_Ty1 _Mean0) {
            _Init(_Mean0);
        }

        _NODISCARD bool operator==(const param_type& _Right) const {
            return _Mean == _Right._Mean;
        }

        _NODISCARD bool operator!=(const param_type& _Right) const {
            return !(*this == _Right);
        }

        _NODISCARD _Ty1 mean() const {
            return _Mean;
        }

        void _Init(_Ty1 _Mean0) { // set internal state
            _STL_ASSERT(0.0 < _Mean0, "invalid mean argument for poisson_distribution");
            _Mean = _Mean0;
            _Sqrt = _CSTD sqrt(2.0 * _Mean0);
            _Logm = _CSTD log(_Mean0);
            _Gx1 = _Mean0 * _Logm - _XLgamma(_Mean0 + 1.0);
            _Small._Init(_Mean0);
        }

        _Ty1 _Mean;
        _Ty1 _Sqrt;
        _Ty1 _Logm;
        _Ty1 _Gx1;

        _Small_poisson_distribution<_Ty> _Small;
    };

    poisson_distribution() : _Par(_Ty1(1)) {}

    explicit poisson_distribution(_Ty1 _Mean0) : _Par(_Mean0) {}

    explicit poisson_distribution(const param_type& _Par0) : _Par(_Par0) {}

    _NODISCARD _Ty1 mean() const {
        return _Par.mean();
    }

    _NODISCARD param_type param() const {
        return _Par;
    }

    void param(const param_type& _Par0) { // set parameter package
        _Par = _Par0;
    }

    _NODISCARD result_type(min)() const { // get smallest possible result
        return 0;
    }

    _NODISCARD result_type(max)() const { // get largest possible result
        return (numeric_limits<result_type>::max) ();
    }

    void reset() {} // clear internal state

    template <class _Engine>
    _NODISCARD result_type operator()(_Engine& _Eng) const {
        return _Eval(_Eng, _Par);
    }

    template <class _Engine>
    _NODISCARD result_type operator()(_Engine& _Eng, const param_type& _Par0) const {
        return _Eval(_Eng, _Par0);
    }

    template <class _Elem, class _Traits>
    basic_istream<_Elem, _Traits>& _Read(basic_istream<_Elem, _Traits>& _Istr) { // read state from _Istr
        _Ty1 _Mean0;
        _In(_Istr, _Mean0);
        _Par._Init(_Mean0);
        return _Istr;
    }

    template <class _Elem, class _Traits>
    basic_ostream<_Elem, _Traits>& _Write(basic_ostream<_Elem, _Traits>& _Ostr) const { // write state to _Ostr
        _Out(_Ostr, _Par._Mean);
        return _Ostr;
    }

private:
    template <class _Engine>
    result_type _Eval(_Engine& _Eng, const param_type& _Par0) const {
        if (_Par0._Mean < 12.0) {
            return _Par0._Small(_Eng);
        }

        for (;;) { // generate and reject
            using _Uty = make_unsigned_t<_Ty>;
            constexpr auto _Ty_max{ (numeric_limits<_Ty>::max) () };
            const auto _Ty1_max{ _Float_upper_bound<_Ty1>(static_cast<_Uty>(_Ty_max)) };

            _Ty _Res;
            _Ty1 _Yx;
            for (;;) { // generate a tentative value
                _Yx = static_cast<_Ty1>(_CSTD tan(_Pi * _NRAND(_Eng, _Ty1)));
                const _Ty1 _Mx{ _Par0._Sqrt * _Yx + _Par0._Mean };
                if (0.0 <= _Mx && _Mx < _Ty1_max) {
                    _Res = static_cast<_Ty>(_Mx);
                    break;
                }
            }

            if (_NRAND(_Eng, _Ty1)
                <= 0.9 * (1.0 + _Yx * _Yx) * _CSTD exp(_Res * _Par0._Logm - _XLgamma(_Res + 1.0) - _Par0._Gx1)) {
                return _Res;
            }
        }
    }

    param_type _Par;
};

template <class _Ty>
_NODISCARD bool operator==(const poisson_distribution<_Ty>& _Left, const poisson_distribution<_Ty>& _Right) {
    return _Left.param() == _Right.param();
}

template <class _Ty>
_NODISCARD bool operator!=(const poisson_distribution<_Ty>& _Left, const poisson_distribution<_Ty>& _Right) {
    return !(_Left == _Right);
}

template <class _Elem, class _Traits, class _Ty>
basic_istream<_Elem, _Traits>& operator>>(basic_istream<_Elem, _Traits>& _Istr,
    poisson_distribution<_Ty>& _Dist) { // read state from _Istr
    return _Dist._Read(_Istr);
}

template <class _Elem, class _Traits, class _Ty>
basic_ostream<_Elem, _Traits>& operator<<(basic_ostream<_Elem, _Traits>& _Ostr,
    const poisson_distribution<_Ty>& _Dist) { // write state to _Ostr
    return _Dist._Write(_Ostr);
}

template <class _Ty = int>
class binomial_distribution { // binomial distribution
public:
    using _Ty1 = double;

    using result_type = _Ty;

    _RNG_REQUIRE_INTTYPE(binomial_distribution, _Ty);

    struct param_type { // parameter package
        using distribution_type = binomial_distribution;

        param_type() {
            _Init(1, _Ty1(0.5));
        }

        explicit param_type(_Ty _Tx0, _Ty1 _Px0 = _Ty1(0.5)) {
            _Init(_Tx0, _Px0);
        }

        _NODISCARD bool operator==(const param_type& _Right) const {
            return _Tx == _Right._Tx && _Px == _Right._Px;
        }

        _NODISCARD bool operator!=(const param_type& _Right) const {
            return !(*this == _Right);
        }

        _NODISCARD _Ty t() const {
            return _Tx;
        }

        _NODISCARD _Ty1 p() const {
            return _Px;
        }

        void _Init(_Ty _Tx0, _Ty1 _Px0) { // initialize
            _STL_ASSERT(0.0 <= _Tx0, "invalid max argument for binomial_distribution");
            _STL_ASSERT(0.0 <= _Px0 && _Px0 <= 1.0, "invalid probability argument for binomial_distribution");
            _Tx = _Tx0;
            _Px = _Px0;
            _Pp = _Px < 0.5 ? _Px : (1.0 - _Px);
            _Mean = _Tx * _Pp;
            _Gx1 = _XLgamma(_Tx + 1.0);
            _Sqrt = _CSTD sqrt(2 * _Mean * (1 - _Pp));
            _Logp = _CSTD log(_Pp);
            _Logp1 = _CSTD log(1.0 - _Pp);
            _Small._Init(_Mean);
        }

        _Ty _Tx;
        _Ty1 _Px;
        _Ty1 _Pp;
        _Ty1 _Mean;
        _Ty1 _Gx1;
        _Ty1 _Sqrt;
        _Ty1 _Logp;
        _Ty1 _Logp1;

        _Small_poisson_distribution<_Ty> _Small; // TRANSITION, ABI: unused
    };

    binomial_distribution() : _Par(1, _Ty1(0.5)) {}

    explicit binomial_distribution(_Ty _Tx0, _Ty1 _Px0 = _Ty1(0.5)) : _Par(_Tx0, _Px0) {}

    explicit binomial_distribution(const param_type& _Par0) : _Par(_Par0) {}

    _NODISCARD _Ty t() const {
        return _Par.t();
    }

    _NODISCARD _Ty1 p() const {
        return _Par.p();
    }

    _NODISCARD param_type param() const {
        return _Par;
    }

    void param(const param_type& _Par0) { // set parameter package
        _Par = _Par0;
    }

    _NODISCARD result_type(min)() const { // get smallest possible result
        return 0;
    }

    _NODISCARD result_type(max)() const { // get largest possible result
        return _Par.t();
    }

    void reset() {} // clear internal state

    template <class _Engine>
    _NODISCARD result_type operator()(_Engine& _Eng) const {
        return _Eval(_Eng, _Par);
    }

    template <class _Engine>
    _NODISCARD result_type operator()(_Engine& _Eng, const param_type& _Par0) const {
        return _Eval(_Eng, _Par0);
    }

    template <class _Elem, class _Traits>
    basic_istream<_Elem, _Traits>& _Read(basic_istream<_Elem, _Traits>& _Istr) { // read state from _Istr
        _Ty _Tx0;
        _Ty1 _Px0;
        _In(_Istr, _Px0);
        _In(_Istr, _Tx0);
        _Par._Init(_Tx0, _Px0);
        return _Istr;
    }

    template <class _Elem, class _Traits>
    basic_ostream<_Elem, _Traits>& _Write(basic_ostream<_Elem, _Traits>& _Ostr) const { // write state to _Ostr
        _Out(_Ostr, _Par._Px);
        _Out(_Ostr, _Par._Tx);
        return _Ostr;
    }

private:
    template <class _Engine>
    result_type _Eval(
        _Engine& _Eng, const param_type& _Par0) const { // Press et al., Numerical Recipes in C, 2nd ed., pp 295-296.
        _Ty _Res;
        if (_Par0._Tx < 25) { // generate directly
            _Res = 0;
            for (_Ty _Ix = 0; _Ix < _Par0._Tx; ++_Ix) {
                if (_NRAND(_Eng, _Ty1) < _Par0._Px) {
                    ++_Res;
                }
            }

            return _Res;
        }
        else if (_Par0._Mean < 1.0) {
            // Events are rare, use waiting time method (Luc Devroye, Non-Uniform Random Variate Generation, p. 525).
            const _Ty1 _Rand = _NRAND(_Eng, _Ty1);

            // The exit condition is log(1 - _Rand)/t < log(1-p), which is equivalent to _Rand > 1 - (1-p)^t. If
            // we have a cheap upper bound for 1-(1-p)^t, we can exit early without having to call log. We use two
            // such bounds, one that is tight for mean ~0 and another for mean ~1. In the first case, Bernoulli's
            // inequality gives -1+p*t >= -(1-p)^t, so 1 - (1-p)^t <= p*t = mean. For the other bound, 1-(1-p)^t =
            // 1-(1-p)(1-mean/t)^(t-1) <= 1-(1-p)(1-1/t)^(t-1) <= 1-(1-p)/e.
            const _Ty1 _Ub =
                (_STD min) (_Par0._Mean, _Ty1{ 3.678794411714423216e-1 } *_Par0._Pp + _Ty1{ 6.32120558828557678e-1 });
            if (_Rand > _Ub) {
                _Res = _Ty{ 0 };
            }
            else {
                _Ty _Denom = _Par0._Tx;
                _Ty1 _Sum = _CSTD log(_Ty1{ 1.0 } - _Rand) / _Denom;
                while (_Sum >= _Par0._Logp1 && --_Denom != 0) {
                    _Sum += _CSTD log(_Ty1{ 1.0 } - _NRAND(_Eng, _Ty1)) / _Denom;
                }
                _Res = static_cast<_Ty>(_Par0._Tx - _Denom);
            }
        }
        else { // no shortcuts
            using _Uty = make_unsigned_t<_Ty>;
            const auto _Ty1_Tx{ _Float_upper_bound<_Ty1>(static_cast<_Uty>(_Par0._Tx)) };

            for (;;) { // generate and reject
                _Ty1 _Yx;
                for (;;) { // generate a tentative value
                    _Yx = static_cast<_Ty1>(_CSTD tan(_Pi * _NRAND(_Eng, _Ty1)));
                    const _Ty1 _Mx{ _Par0._Sqrt * _Yx + _Par0._Mean };
                    if (0.0 <= _Mx && _Mx < _Ty1_Tx) {
                        _Res = static_cast<_Ty>(_Mx);
                        break;
                    }
                }
                if (_NRAND(_Eng, _Ty1)
                    <= 1.2 * _Par0._Sqrt * (1.0 + _Yx * _Yx)
                    * _CSTD exp(_Par0._Gx1 - _XLgamma(_Res + 1.0) - _XLgamma(_Par0._Tx - _Res + 1.0)
                        + _Res * _Par0._Logp + (_Par0._Tx - _Res) * _Par0._Logp1)) {
                    break;
                }
            }
        }
        return _Par0._Px == _Par0._Pp ? _Res : static_cast<_Ty>(_Par0._Tx - _Res);
    }

    param_type _Par;
};

template <class _Ty>
_NODISCARD bool operator==(const binomial_distribution<_Ty>& _Left, const binomial_distribution<_Ty>& _Right) {
    return _Left.param() == _Right.param();
}

template <class _Ty>
_NODISCARD bool operator!=(const binomial_distribution<_Ty>& _Left, const binomial_distribution<_Ty>& _Right) {
    return !(_Left == _Right);
}

template <class _Elem, class _Traits, class _Ty>
basic_istream<_Elem, _Traits>& operator>>(basic_istream<_Elem, _Traits>& _Istr,
    binomial_distribution<_Ty>& _Dist) { // read state from _Istr
    return _Dist._Read(_Istr);
}

template <class _Elem, class _Traits, class _Ty>
basic_ostream<_Elem, _Traits>& operator<<(basic_ostream<_Elem, _Traits>& _Ostr,
    const binomial_distribution<_Ty>& _Dist) { // write state to _Ostr
    return _Dist._Write(_Ostr);
}

template <class _Ty = double>
class uniform_real { // uniform real distribution
public:
    using result_type = _Ty;

    struct param_type { // parameter package
        using distribution_type = uniform_real;

        param_type() {
            _Init(_Ty{ 0 }, _Ty{ 1 });
        }

        explicit param_type(_Ty _Min0, _Ty _Max0 = _Ty{ 1 }) {
            _Init(_Min0, _Max0);
        }

        _NODISCARD bool operator==(const param_type& _Right) const {
            return _Min == _Right._Min && _Max == _Right._Max;
        }

        _NODISCARD bool operator!=(const param_type& _Right) const {
            return !(*this == _Right);
        }

        _NODISCARD result_type a() const {
            return _Min;
        }

        _NODISCARD result_type b() const {
            return _Max;
        }

        void _Init(_Ty _Min0, _Ty _Max0) { // set internal state
            _STL_ASSERT(_Min0 <= _Max0 && (0 <= _Min0 || _Max0 <= _Min0 + (numeric_limits<_Ty>::max) ()),
                "invalid min and max arguments for uniform_real");
            _Min = _Min0;
            _Max = _Max0;
        }

        result_type _Min;
        result_type _Max;
    };

    uniform_real() : _Par(_Ty{ 0 }, _Ty{ 1 }) {}

    explicit uniform_real(_Ty _Min0, _Ty _Max0 = _Ty{ 1 }) : _Par(_Min0, _Max0) {}

    explicit uniform_real(const param_type& _Par0) : _Par(_Par0) {}

    _NODISCARD result_type a() const {
        return _Par.a();
    }

    _NODISCARD result_type b() const {
        return _Par.b();
    }

    _NODISCARD param_type param() const {
        return _Par;
    }

    void param(const param_type& _Par0) { // set parameter package
        _Par = _Par0;
    }

    _NODISCARD result_type(min)() const {
        return _Par._Min;
    }

    _NODISCARD result_type(max)() const {
        return _Par._Max;
    }

    void reset() {} // clear internal state

    template <class _Engine>
    _NODISCARD result_type operator()(_Engine& _Eng) const {
        return _Eval(_Eng, _Par);
    }

    template <class _Engine>
    _NODISCARD result_type operator()(_Engine& _Eng, const param_type& _Par0) const {
        return _Eval(_Eng, _Par0);
    }

    template <class _Elem, class _Traits>
    basic_istream<_Elem, _Traits>& _Read(basic_istream<_Elem, _Traits>& _Istr) { // read state from _Istr
        _Ty _Min0;
        _Ty _Max0;
        _In(_Istr, _Min0);
        _In(_Istr, _Max0);
        _Par._Init(_Min0, _Max0);
        return _Istr;
    }

    template <class _Elem, class _Traits>
    basic_ostream<_Elem, _Traits>& _Write(basic_ostream<_Elem, _Traits>& _Ostr) const { // write state to _Ostr
        _Out(_Ostr, _Par._Min);
        _Out(_Ostr, _Par._Max);
        return _Ostr;
    }

private:
    template <class _Engine>
    result_type _Eval(_Engine& _Eng, const param_type& _Par0) const {
        return _NRAND(_Eng, _Ty) * (_Par0._Max - _Par0._Min) + _Par0._Min;
    }

    param_type _Par;
};

template <class _Elem, class _Traits, class _Ty>
basic_istream<_Elem, _Traits>& operator>>(basic_istream<_Elem, _Traits>& _Istr,
    uniform_real<_Ty>& _Dist) { // read state from _Istr
    return _Dist._Read(_Istr);
}

template <class _Elem, class _Traits, class _Ty>
basic_ostream<_Elem, _Traits>& operator<<(basic_ostream<_Elem, _Traits>& _Ostr,
    const uniform_real<_Ty>& _Dist) { // write state to _Ostr
    return _Dist._Write(_Ostr);
}

template <class _Ty = double>
class uniform_real_distribution : public uniform_real<_Ty> { // uniform real distribution
public:
    _RNG_REQUIRE_REALTYPE(uniform_real_distribution, _Ty);

    using _Mybase = uniform_real<_Ty>;
    using _Mypbase = typename _Mybase::param_type;
    using result_type = typename _Mybase::result_type;

    struct param_type : _Mypbase { // parameter package
        using distribution_type = uniform_real_distribution;

        param_type() : _Mypbase(_Ty{ 0 }, _Ty{ 1 }) {}

        explicit param_type(_Ty _Min0, _Ty _Max0 = _Ty{ 1 }) : _Mypbase(_Min0, _Max0) {}

        param_type(const _Mypbase& _Right) : _Mypbase(_Right) {}
    };

    uniform_real_distribution() : _Mybase(_Ty{ 0 }, _Ty{ 1 }) {}

    explicit uniform_real_distribution(_Ty _Min0, _Ty _Max0 = _Ty{ 1 }) : _Mybase(_Min0, _Max0) {}

    explicit uniform_real_distribution(const param_type& _Par0) : _Mybase(_Par0) {}
};

template <class _Ty>
_NODISCARD bool operator==(const uniform_real_distribution<_Ty>& _Left, const uniform_real_distribution<_Ty>& _Right) {
    return _Left.param() == _Right.param();
}

template <class _Ty>
_NODISCARD bool operator!=(const uniform_real_distribution<_Ty>& _Left, const uniform_real_distribution<_Ty>& _Right) {
    return !(_Left == _Right);
}

template <class _Ty = double>
class exponential_distribution { // exponential distribution
public:
    _RNG_REQUIRE_REALTYPE(exponential_distribution, _Ty);

    using result_type = _Ty;

    struct param_type { // parameter package
        using distribution_type = exponential_distribution;

        param_type() {
            _Init(_Ty{ 1 });
        }

        explicit param_type(_Ty _Lambda0) {
            _Init(_Lambda0);
        }

        _NODISCARD bool operator==(const param_type& _Right) const {
            return _Lambda == _Right._Lambda;
        }

        _NODISCARD bool operator!=(const param_type& _Right) const {
            return !(*this == _Right);
        }

        _NODISCARD _Ty lambda() const {
            return _Lambda;
        }

        void _Init(_Ty _Lambda0) { // set internal state
            _STL_ASSERT(0.0 < _Lambda0, "invalid lambda argument for exponential_distribution");
            _Lambda = _Lambda0;
        }

        _Ty _Lambda;
    };

    exponential_distribution() : _Par(_Ty{ 1 }) {}

    explicit exponential_distribution(_Ty _Lambda0) : _Par(_Lambda0) {}

    explicit exponential_distribution(const param_type& _Par0) : _Par(_Par0) {}

    _NODISCARD _Ty lambda() const {
        return _Par.lambda();
    }

    _NODISCARD param_type param() const {
        return _Par;
    }

    void param(const param_type& _Par0) { // set parameter package
        _Par = _Par0;
    }

    _NODISCARD result_type(min)() const { // get smallest possible result
        return 0;
    }

    _NODISCARD result_type(max)() const { // get largest possible result
        return numeric_limits<result_type>::infinity();
    }

    void reset() {} // clear internal state

    template <class _Engine>
    _NODISCARD result_type operator()(_Engine& _Eng) const {
        return _Eval(_Eng, _Par);
    }

    template <class _Engine>
    _NODISCARD result_type operator()(_Engine& _Eng, const param_type& _Par0) const {
        return _Eval(_Eng, _Par0);
    }

    template <class _Elem, class _Traits>
    basic_istream<_Elem, _Traits>& _Read(basic_istream<_Elem, _Traits>& _Istr) { // read state from _Istr
        _Ty _Lambda0;
        _In(_Istr, _Lambda0);
        _Par._Init(_Lambda0);
        return _Istr;
    }

    template <class _Elem, class _Traits>
    basic_ostream<_Elem, _Traits>& _Write(basic_ostream<_Elem, _Traits>& _Ostr) const { // write state to _Ostr
        _Out(_Ostr, _Par._Lambda);
        return _Ostr;
    }

private:
    template <class _Engine>
    result_type _Eval(_Engine& _Eng, const param_type& _Par0) const {
        return -_CSTD log(_Ty{ 1 } - _NRAND(_Eng, _Ty)) / _Par0._Lambda;
    }

    param_type _Par;
};

template <class _Ty>
_NODISCARD bool operator==(const exponential_distribution<_Ty>& _Left, const exponential_distribution<_Ty>& _Right) {
    return _Left.param() == _Right.param();
}

template <class _Ty>
_NODISCARD bool operator!=(const exponential_distribution<_Ty>& _Left, const exponential_distribution<_Ty>& _Right) {
    return !(_Left == _Right);
}

template <class _Elem, class _Traits, class _Ty>
basic_istream<_Elem, _Traits>& operator>>(basic_istream<_Elem, _Traits>& _Istr,
    exponential_distribution<_Ty>& _Dist) { // read state from _Istr
    return _Dist._Read(_Istr);
}

template <class _Elem, class _Traits, class _Ty>
basic_ostream<_Elem, _Traits>& operator<<(basic_ostream<_Elem, _Traits>& _Ostr,
    const exponential_distribution<_Ty>& _Dist) { // write state to _Ostr
    return _Dist._Write(_Ostr);
}

template <class _Ty = double>
class normal_distribution { // normal distribution
public:
    _RNG_REQUIRE_REALTYPE(normal_distribution, _Ty);

    using result_type = _Ty;

    struct param_type { // parameter package
        using distribution_type = normal_distribution;

        param_type() {
            _Init(0.0, 1.0);
        }

        explicit param_type(_Ty _Mean0, _Ty _Sigma0 = 1.0) {
            _Init(_Mean0, _Sigma0);
        }

        _NODISCARD bool operator==(const param_type& _Right) const {
            return _Mean == _Right._Mean && _Sigma == _Right._Sigma;
        }

        _NODISCARD bool operator!=(const param_type& _Right) const {
            return !(*this == _Right);
        }

        _NODISCARD _Ty mean() const {
            return _Mean;
        }

        _NODISCARD _Ty sigma() const {
            return _Sigma;
        }

        _NODISCARD _Ty stddev() const {
            return _Sigma;
        }

        void _Init(_Ty _Mean0, _Ty _Sigma0) { // set internal state
            _STL_ASSERT(0.0 < _Sigma0, "invalid sigma argument for normal_distribution");
            _Mean = _Mean0;
            _Sigma = _Sigma0;
        }

        _Ty _Mean;
        _Ty _Sigma;
    };

    normal_distribution() : _Par(0.0, 1.0), _Valid(false), _Xx2(0) {}

    explicit normal_distribution(_Ty _Mean0, _Ty _Sigma0 = 1.0) : _Par(_Mean0, _Sigma0), _Valid(false), _Xx2(0) {}

    explicit normal_distribution(const param_type& _Par0) : _Par(_Par0), _Valid(false), _Xx2(0) {}

    _NODISCARD _Ty mean() const {
        return _Par.mean();
    }

    _NODISCARD _Ty sigma() const {
        return _Par.sigma();
    }

    _NODISCARD _Ty stddev() const {
        return _Par.sigma();
    }

    _NODISCARD param_type param() const {
        return _Par;
    }

    void param(const param_type& _Par0) { // set parameter package
        _Par = _Par0;
        reset();
    }

    _NODISCARD result_type(min)() const { // get smallest possible result
        return -numeric_limits<result_type>::infinity();
    }

    _NODISCARD result_type(max)() const { // get largest possible result
        return numeric_limits<result_type>::infinity();
    }

    void reset() { // clear internal state
        _Valid = false;
    }

    template <class _Engine>
    _NODISCARD result_type operator()(_Engine& _Eng) {
        return _Eval(_Eng, _Par);
    }

    template <class _Engine>
    _NODISCARD result_type operator()(_Engine& _Eng, const param_type& _Par0) {
        reset();
        return _Eval(_Eng, _Par0, false);
    }

    template <class _Elem, class _Traits>
    basic_istream<_Elem, _Traits>& _Read(basic_istream<_Elem, _Traits>& _Istr) { // read state from _Istr
        _Ty _Mean0;
        _Ty _Sigma0;
        _In(_Istr, _Mean0);
        _In(_Istr, _Sigma0);
        _Par._Init(_Mean0, _Sigma0);

        _Istr >> _Valid;
        _In(_Istr, _Xx2);
        return _Istr;
    }

    template <class _Elem, class _Traits>
    basic_ostream<_Elem, _Traits>& _Write(basic_ostream<_Elem, _Traits>& _Ostr) const { // write state to _Ostr
        _Out(_Ostr, _Par._Mean);
        _Out(_Ostr, _Par._Sigma);

        _Ostr << ' ' << _Valid;
        _Out(_Ostr, _Xx2);
        return _Ostr;
    }

private:
    template <class _Engine>
    result_type _Eval(_Engine& _Eng, const param_type& _Par0,
        bool _Keep = true) { // compute next value
                             // Knuth, vol. 2, p. 122, alg. P
        _Ty _Res;
        if (_Keep && _Valid) {
            _Res = _Xx2;
            _Valid = false;
        }
        else { // generate two values, store one, return one
            _Ty _Vx1;
            _Ty _Vx2;
            _Ty _Sx;
            for (;;) { // reject bad values to avoid generating NaN/Inf on the next calculations
                _Vx1 = 2 * _NRAND(_Eng, _Ty) - 1;
                _Vx2 = 2 * _NRAND(_Eng, _Ty) - 1;
                _Sx = _Vx1 * _Vx1 + _Vx2 * _Vx2;
                if (_Sx < _Ty{ 1 } && _Vx1 != _Ty{ 0 } && _Vx2 != _Ty{ 0 }) {
                    // good values!
                    break;
                }
            }

            _Ty _LogSx;
            if (_Sx > _Ty{ 1e-4 }) {
                _LogSx = _STD log(_Sx);
            }
            else {
                // Bad _Sx value! Very small values will overflow log(_Sx) / _Sx.
                // Generate a new value based on scaling method.
                const _Ty _Ln2{ _Ty{0.69314718055994530941723212145818} };
                const _Ty _Maxabs{ (_STD max) (_STD abs(_Vx1), _STD abs(_Vx2)) };
                const int _ExpMax{ _STD ilogb(_Maxabs) };
                _Vx1 = _STD scalbn(_Vx1, -_ExpMax);
                _Vx2 = _STD scalbn(_Vx2, -_ExpMax);
                _Sx = _Vx1 * _Vx1 + _Vx2 * _Vx2;
                _LogSx = _STD log(_Sx) + static_cast<_Ty>(_ExpMax) * (_Ln2 * 2);
            }

            const _Ty _Fx{ _STD sqrt(_Ty{-2} *_LogSx / _Sx) };
            if (_Keep) { // save second value for next call
                _Xx2 = _Fx * _Vx2;
                _Valid = true;
            }
            _Res = _Fx * _Vx1;
        }
        return _Res * _Par0._Sigma + _Par0._Mean;
    }

    param_type _Par;
    bool _Valid;
    _Ty _Xx2;
};

template <class _Ty>
_NODISCARD bool operator==(const normal_distribution<_Ty>& _Left, const normal_distribution<_Ty>& _Right) {
    return _Left.param() == _Right.param();
}

template <class _Ty>
_NODISCARD bool operator!=(const normal_distribution<_Ty>& _Left, const normal_distribution<_Ty>& _Right) {
    return !(_Left == _Right);
}

template <class _Elem, class _Traits, class _Ty>
basic_istream<_Elem, _Traits>& operator>>(basic_istream<_Elem, _Traits>& _Istr,
    normal_distribution<_Ty>& _Dist) { // read state from _Istr
    return _Dist._Read(_Istr);
}

template <class _Elem, class _Traits, class _Ty>
basic_ostream<_Elem, _Traits>& operator<<(basic_ostream<_Elem, _Traits>& _Ostr,
    const normal_distribution<_Ty>& _Dist) { // write state to _Ostr
    return _Dist._Write(_Ostr);
}

template <class _Ty = double>
class gamma_distribution { // gamma distribution
public:
    _RNG_REQUIRE_REALTYPE(gamma_distribution, _Ty);

    using result_type = _Ty;

    struct param_type { // parameter package
        using distribution_type = gamma_distribution;

        param_type() {
            _Init(_Ty{ 1 }, _Ty{ 1 });
        }

        explicit param_type(_Ty _Alpha0, _Ty _Beta0 = _Ty{ 1 }) {
            _Init(_Alpha0, _Beta0);
        }

        _NODISCARD bool operator==(const param_type& _Right) const {
            return _Alpha == _Right._Alpha && _Beta == _Right._Beta;
        }

        _NODISCARD bool operator!=(const param_type& _Right) const {
            return !(*this == _Right);
        }

        _NODISCARD _Ty alpha() const {
            return _Alpha;
        }

        _NODISCARD _Ty beta() const {
            return _Beta;
        }

        void _Init(_Ty _Alpha0, _Ty _Beta0) { // initialize
            _STL_ASSERT(0.0 < _Alpha0, "invalid alpha argument for gamma_distribution");
            _STL_ASSERT(0.0 < _Beta0, "invalid beta argument for gamma_distribution");
            _Alpha = _Alpha0;
            _Beta = _Beta0;
            _Px = static_cast<_Ty>(_Exp1 / (_Alpha + _Exp1));
            _Sqrt = _CSTD sqrt(2 * _Alpha - 1);
        }

        _Ty _Alpha;
        _Ty _Beta;
        _Ty _Px;
        _Ty _Sqrt;
        exponential_distribution<_Ty> _Exp;
    };

    gamma_distribution() : _Par(_Ty{ 1 }, _Ty{ 1 }) {}

    explicit gamma_distribution(_Ty _Alpha0, _Ty _Beta0 = _Ty{ 1 }) : _Par(_Alpha0, _Beta0) {}

    explicit gamma_distribution(const param_type& _Par0) : _Par(_Par0) {}

    _NODISCARD _Ty alpha() const {
        return _Par.alpha();
    }

    _NODISCARD _Ty beta() const {
        return _Par.beta();
    }

    _NODISCARD param_type param() const {
        return _Par;
    }

    void param(const param_type& _Par0) { // set parameter package
        _Par = _Par0;
    }

    _NODISCARD result_type(min)() const { // get smallest possible result
        return result_type{ 0.0 };
    }

    _NODISCARD result_type(max)() const { // get largest possible result
        return numeric_limits<result_type>::infinity();
    }

    void reset() {} // clear internal state

    template <class _Engine>
    _NODISCARD result_type operator()(_Engine& _Eng) const {
        return _Eval(_Eng, _Par);
    }

    template <class _Engine>
    _NODISCARD result_type operator()(_Engine& _Eng, const param_type& _Par0) const {
        return _Eval(_Eng, _Par0);
    }

    template <class _Elem, class _Traits>
    basic_istream<_Elem, _Traits>& _Read(basic_istream<_Elem, _Traits>& _Istr) { // read state from _Istr
        _Ty _Alpha0;
        _Ty _Beta0;
        _In(_Istr, _Alpha0);
        _In(_Istr, _Beta0);
        _Par._Init(_Alpha0, _Beta0);
        return _Istr;
    }

    template <class _Elem, class _Traits>
    basic_ostream<_Elem, _Traits>& _Write(basic_ostream<_Elem, _Traits>& _Ostr) const { // write state to _Ostr
        _Out(_Ostr, _Par._Alpha);
        _Out(_Ostr, _Par._Beta);
        return _Ostr;
    }

private:
    template <class _Engine>
    result_type _Eval(_Engine& _Eng, param_type _Par0) const {
        _Ty _Ux;
        _Ty _Vx;
        _Ty _Xx;
        _Ty _Yx;
        _Ty _Qx;
        int _Count;
        if (_Par0._Alpha < 1) { // small values of alpha
                                // from Knuth
            for (;;) { // generate and reject
                _Ux = _NRAND(_Eng, _Ty);
                do {
                    _Vx = _NRAND(_Eng, _Ty);
                } while (_Vx == 0);

                if (_Ux < _Par0._Px) { // small _Ux
                    _Xx = _CSTD pow(_Vx, _Ty{ 1 } / _Par0._Alpha);
                    _Qx = _CSTD exp(-_Xx);
                }
                else { // large _Ux
                    _Xx = 1 - _CSTD log(_Vx);
                    _Qx = _CSTD pow(_Xx, _Par0._Alpha - 1);
                }

                if (_NRAND(_Eng, _Ty) < _Qx) {
                    return _Par0._Beta * _Xx;
                }
            }
        }

        if (_Par0._Alpha == 1) {
            return _Par0._Beta * _Par0._Exp(_Eng);
        }

        if (_Par0._Alpha < 20.0 && (_Count = static_cast<int>(_Par0._Alpha)) == _Par0._Alpha) {
            // _Alpha is small integer, compute directly
            _Yx = _NRAND(_Eng, _Ty);
            while (--_Count) { // adjust result
                do {
                    _Ux = _NRAND(_Eng, _Ty);
                } while (_Ux == 0);

                _Yx *= _Ux;
            }
            return _Par0._Beta * -_CSTD log(_Yx);
        }

        // no shortcuts
        for (;;) { // generate and reject
            _Yx = static_cast<_Ty>(_CSTD tan(_Pi * _NRAND(_Eng, _Ty)));
            _Xx = _Par0._Sqrt * _Yx + _Par0._Alpha - 1;
            if (0 < _Xx
                && _NRAND(_Eng, _Ty) <= (1 + _Yx * _Yx)
                * _CSTD exp((_Par0._Alpha - 1) * _CSTD log(_Xx / (_Par0._Alpha - 1))
                    - _Par0._Sqrt * _Yx)) {
                return _Par0._Beta * _Xx;
            }
        }
    }

    param_type _Par;
};

template <class _Ty>
_NODISCARD bool operator==(const gamma_distribution<_Ty>& _Left, const gamma_distribution<_Ty>& _Right) {
    return _Left.param() == _Right.param();
}

template <class _Ty>
_NODISCARD bool operator!=(const gamma_distribution<_Ty>& _Left, const gamma_distribution<_Ty>& _Right) {
    return !(_Left == _Right);
}

template <class _Elem, class _Traits, class _Ty>
basic_istream<_Elem, _Traits>& operator>>(basic_istream<_Elem, _Traits>& _Istr,
    gamma_distribution<_Ty>& _Dist) { // read state from _Istr
    return _Dist._Read(_Istr);
}

template <class _Elem, class _Traits, class _Ty>
basic_ostream<_Elem, _Traits>& operator<<(basic_ostream<_Elem, _Traits>& _Ostr,
    const gamma_distribution<_Ty>& _Dist) { // write state to _Ostr
    return _Dist._Write(_Ostr);
}

template <class _Ty = double>
class weibull_distribution { // weibull distribution
public:
    _RNG_REQUIRE_REALTYPE(weibull_distribution, _Ty);

    using result_type = _Ty;

    struct param_type { // parameter package
        using distribution_type = weibull_distribution;

        param_type() {
            _Init(_Ty{ 1 }, _Ty{ 1 });
        }

        explicit param_type(_Ty _Ax0, _Ty _Bx0 = _Ty{ 1 }) {
            _Init(_Ax0, _Bx0);
        }

        _NODISCARD bool operator==(const param_type& _Right) const {
            return _Ax == _Right._Ax && _Bx == _Right._Bx;
        }

        _NODISCARD bool operator!=(const param_type& _Right) const {
            return !(*this == _Right);
        }

        _NODISCARD _Ty a() const {
            return _Ax;
        }

        _NODISCARD _Ty b() const {
            return _Bx;
        }

        void _Init(_Ty _Ax0, _Ty _Bx0) { // initialize
            _STL_ASSERT(0.0 < _Ax0, "invalid a argument for weibull_distribution");
            _STL_ASSERT(0.0 < _Bx0, "invalid b argument for weibull_distribution");
            _Ax = _Ax0;
            _Bx = _Bx0;
        }

        _Ty _Ax;
        _Ty _Bx;
    };

    weibull_distribution() : _Par(_Ty{ 1 }, _Ty{ 1 }) {}

    explicit weibull_distribution(_Ty _Ax0, _Ty _Bx0 = _Ty{ 1 }) : _Par(_Ax0, _Bx0) {}

    explicit weibull_distribution(const param_type& _Par0) : _Par(_Par0) {}

    _NODISCARD _Ty a() const {
        return _Par.a();
    }

    _NODISCARD _Ty b() const {
        return _Par.b();
    }

    _NODISCARD param_type param() const {
        return _Par;
    }

    void param(const param_type& _Par0) { // set parameter package
        _Par = _Par0;
    }

    _NODISCARD result_type(min)() const { // get smallest possible result
        return 0;
    }

    _NODISCARD result_type(max)() const { // get largest possible result
        return numeric_limits<result_type>::infinity();
    }

    void reset() {} // clear internal state

    template <class _Engine>
    _NODISCARD result_type operator()(_Engine& _Eng) const {
        return _Eval(_Eng, _Par);
    }

    template <class _Engine>
    _NODISCARD result_type operator()(_Engine& _Eng, const param_type& _Par0) const {
        return _Eval(_Eng, _Par0);
    }

    template <class _Elem, class _Traits>
    basic_istream<_Elem, _Traits>& _Read(basic_istream<_Elem, _Traits>& _Istr) { // read state from _Istr
        _Ty _Ax0;
        _Ty _Bx0;
        _In(_Istr, _Ax0);
        _In(_Istr, _Bx0);
        _Par._Init(_Ax0, _Bx0);
        return _Istr;
    }

    template <class _Elem, class _Traits>
    basic_ostream<_Elem, _Traits>& _Write(basic_ostream<_Elem, _Traits>& _Ostr) const { // write state to _Ostr
        _Out(_Ostr, _Par._Ax);
        _Out(_Ostr, _Par._Bx);
        return _Ostr;
    }

private:
    template <class _Engine>
    result_type _Eval(_Engine& _Eng, const param_type& _Par0) const { // generate pseudo-random value
        _Ty _Px = (_Ty{ 1 } - _NRAND(_Eng, _Ty));
        return _Par0._Bx * _CSTD pow(-_CSTD log(_Px), _Ty{ 1 } / _Par0._Ax);
    }

    param_type _Par;
};

template <class _Ty>
_NODISCARD bool operator==(const weibull_distribution<_Ty>& _Left, const weibull_distribution<_Ty>& _Right) {
    return _Left.param() == _Right.param();
}

template <class _Ty>
_NODISCARD bool operator!=(const weibull_distribution<_Ty>& _Left, const weibull_distribution<_Ty>& _Right) {
    return !(_Left == _Right);
}

template <class _Elem, class _Traits, class _Ty>
basic_istream<_Elem, _Traits>& operator>>(basic_istream<_Elem, _Traits>& _Istr,
    weibull_distribution<_Ty>& _Dist) { // read state from _Istr
    return _Dist._Read(_Istr);
}

template <class _Elem, class _Traits, class _Ty>
basic_ostream<_Elem, _Traits>& operator<<(basic_ostream<_Elem, _Traits>& _Ostr,
    const weibull_distribution<_Ty>& _Dist) { // write state to _Ostr
    return _Dist._Write(_Ostr);
}

template <class _Ty = double>
class extreme_value_distribution { // extreme value distribution
public:
    _RNG_REQUIRE_REALTYPE(extreme_value_distribution, _Ty);

    using result_type = _Ty;

    struct param_type { // parameter package
        using distribution_type = extreme_value_distribution;

        param_type() {
            _Init(_Ty{ 0 }, _Ty{ 1 });
        }

        explicit param_type(_Ty _Ax0, _Ty _Bx0 = _Ty{ 1 }) {
            _Init(_Ax0, _Bx0);
        }

        _NODISCARD bool operator==(const param_type& _Right) const {
            return _Ax == _Right._Ax && _Bx == _Right._Bx;
        }

        _NODISCARD bool operator!=(const param_type& _Right) const {
            return !(*this == _Right);
        }

        _NODISCARD _Ty a() const {
            return _Ax;
        }

        _NODISCARD _Ty b() const {
            return _Bx;
        }

        void _Init(_Ty _Ax0, _Ty _Bx0) { // initialize
            _STL_ASSERT(0.0 < _Bx0, "invalid b argument for extreme_value_distribution");
            _Ax = _Ax0;
            _Bx = _Bx0;
        }

        _Ty _Ax;
        _Ty _Bx;
    };

    extreme_value_distribution() : _Par(_Ty{ 0 }, _Ty{ 1 }) {}

    explicit extreme_value_distribution(_Ty _Ax0, _Ty _Bx0 = _Ty{ 1 }) : _Par(_Ax0, _Bx0) {}

    explicit extreme_value_distribution(const param_type& _Par0) : _Par(_Par0) {}

    _NODISCARD _Ty a() const {
        return _Par.a();
    }

    _NODISCARD _Ty b() const {
        return _Par.b();
    }

    _NODISCARD param_type param() const {
        return _Par;
    }

    void param(const param_type& _Par0) { // set parameter package
        _Par = _Par0;
    }

    _NODISCARD result_type(min)() const { // get smallest possible result
        return -numeric_limits<result_type>::infinity();
    }

    _NODISCARD result_type(max)() const { // get largest possible result
        return numeric_limits<result_type>::infinity();
    }

    void reset() {} // clear internal state

    template <class _Engine>
    _NODISCARD result_type operator()(_Engine& _Eng) const {
        return _Eval(_Eng, _Par);
    }

    template <class _Engine>
    _NODISCARD result_type operator()(_Engine& _Eng, const param_type& _Par0) const {
        return _Eval(_Eng, _Par0);
    }

    template <class _Elem, class _Traits>
    basic_istream<_Elem, _Traits>& _Read(basic_istream<_Elem, _Traits>& _Istr) { // read state from _Istr
        _Ty _Ax0;
        _Ty _Bx0;
        _In(_Istr, _Ax0);
        _In(_Istr, _Bx0);
        _Par._Init(_Ax0, _Bx0);
        return _Istr;
    }

    template <class _Elem, class _Traits>
    basic_ostream<_Elem, _Traits>& _Write(basic_ostream<_Elem, _Traits>& _Ostr) const { // write state to _Ostr
        _Out(_Ostr, _Par._Ax);
        _Out(_Ostr, _Par._Bx);
        return _Ostr;
    }

private:
    template <class _Engine>
    result_type _Eval(_Engine& _Eng, const param_type& _Par0) const { // generate pseudo-random value
        _Ty _Px = _NRAND(_Eng, _Ty);
        return _Par0._Ax - _Par0._Bx * _CSTD log(-_CSTD log(_Px));
    }

    param_type _Par;
};

template <class _Ty>
_NODISCARD bool operator==(
    const extreme_value_distribution<_Ty>& _Left, const extreme_value_distribution<_Ty>& _Right) {
    return _Left.param() == _Right.param();
}

template <class _Ty>
_NODISCARD bool operator!=(
    const extreme_value_distribution<_Ty>& _Left, const extreme_value_distribution<_Ty>& _Right) {
    return !(_Left == _Right);
}

template <class _Elem, class _Traits, class _Ty>
basic_istream<_Elem, _Traits>& operator>>(basic_istream<_Elem, _Traits>& _Istr,
    extreme_value_distribution<_Ty>& _Dist) { // read state from _Istr
    return _Dist._Read(_Istr);
}

template <class _Elem, class _Traits, class _Ty>
basic_ostream<_Elem, _Traits>& operator<<(basic_ostream<_Elem, _Traits>& _Ostr,
    const extreme_value_distribution<_Ty>& _Dist) { // write state to _Ostr
    return _Dist._Write(_Ostr);
}

template <class _Ty = double>
class lognormal_distribution { // lognormal_distribution
public:
    _RNG_REQUIRE_REALTYPE(lognormal_distribution, _Ty);

    using result_type = _Ty;

    struct param_type { // parameter package
        using distribution_type = lognormal_distribution;

        param_type() {
            _Init(_Ty{ 0 }, _Ty{ 1 });
        }

        explicit param_type(_Ty _Mx0, _Ty _Sx0 = _Ty{ 1 }) {
            _Init(_Mx0, _Sx0);
        }

        _NODISCARD bool operator==(const param_type& _Right) const {
            return _Mx == _Right._Mx && _Sx == _Right._Sx;
        }

        _NODISCARD bool operator!=(const param_type& _Right) const {
            return !(*this == _Right);
        }

        _NODISCARD _Ty m() const {
            return _Mx;
        }

        _NODISCARD _Ty s() const {
            return _Sx;
        }

        void _Init(_Ty _Mx0, _Ty _Sx0) { // initialize
            _STL_ASSERT(0.0 < _Sx0, "invalid s argument for lognormal_distribution");
            _Mx = _Mx0;
            _Sx = _Sx0;
        }

        _Ty _Mx;
        _Ty _Sx;
    };

    lognormal_distribution() : _Par(_Ty{ 0 }, _Ty{ 1 }) {}

    explicit lognormal_distribution(_Ty _Mx0, _Ty _Sx0 = _Ty{ 1 }) : _Par(_Mx0, _Sx0) {}

    explicit lognormal_distribution(const param_type& _Par0) : _Par(_Par0) {}

    _NODISCARD _Ty m() const {
        return _Par.m();
    }

    _NODISCARD _Ty s() const {
        return _Par.s();
    }

    _NODISCARD param_type param() const {
        return _Par;
    }

    void param(const param_type& _Par0) { // set parameter package
        _Par = _Par0;
    }

    _NODISCARD result_type(min)() const { // get smallest possible result
        return result_type{ 0.0 };
    }

    _NODISCARD result_type(max)() const { // get largest possible result
        return numeric_limits<result_type>::infinity();
    }

    void reset() {} // clear internal state

    template <class _Engine>
    _NODISCARD result_type operator()(_Engine& _Eng) const {
        return _Eval(_Eng, _Par);
    }

    template <class _Engine>
    _NODISCARD result_type operator()(_Engine& _Eng, const param_type& _Par0) const {
        return _Eval(_Eng, _Par0);
    }

    template <class _Elem, class _Traits>
    basic_istream<_Elem, _Traits>& _Read(basic_istream<_Elem, _Traits>& _Istr) { // read state from _Istr
        _Ty _Mx0;
        _Ty _Sx0;
        _In(_Istr, _Mx0);
        _In(_Istr, _Sx0);
        _Par._Init(_Mx0, _Sx0);
        return _Istr;
    }

    template <class _Elem, class _Traits>
    basic_ostream<_Elem, _Traits>& _Write(basic_ostream<_Elem, _Traits>& _Ostr) const { // write state to _Ostr
        _Out(_Ostr, _Par._Mx);
        _Out(_Ostr, _Par._Sx);
        return _Ostr;
    }

private:
    template <class _Engine>
    result_type _Eval(_Engine& _Eng, param_type _Par0) const { // generate pseudo-random value
        normal_distribution<_Ty> _Dist(_Par0._Mx, _Par0._Sx);
        return _CSTD exp(_Dist(_Eng));
    }

    param_type _Par;
};

template <class _Ty>
_NODISCARD bool operator==(const lognormal_distribution<_Ty>& _Left, const lognormal_distribution<_Ty>& _Right) {
    return _Left.param() == _Right.param();
}

template <class _Ty>
_NODISCARD bool operator!=(const lognormal_distribution<_Ty>& _Left, const lognormal_distribution<_Ty>& _Right) {
    return !(_Left == _Right);
}

template <class _Elem, class _Traits, class _Ty>
basic_istream<_Elem, _Traits>& operator>>(basic_istream<_Elem, _Traits>& _Istr,
    lognormal_distribution<_Ty>& _Dist) { // read state from _Istr
    return _Dist._Read(_Istr);
}

template <class _Elem, class _Traits, class _Ty>
basic_ostream<_Elem, _Traits>& operator<<(basic_ostream<_Elem, _Traits>& _Ostr,
    const lognormal_distribution<_Ty>& _Dist) { // write state to _Ostr
    return _Dist._Write(_Ostr);
}

template <class _Ty = double>
class chi_squared_distribution { // chi squared distribution
public:
    _RNG_REQUIRE_REALTYPE(chi_squared_distribution, _Ty);

    using result_type = _Ty;

    struct param_type { // parameter package
        using distribution_type = chi_squared_distribution;

        param_type() {
            _Init(_Ty{ 1 });
        }

        explicit param_type(_Ty _Nx0) {
            _Init(_Nx0);
        }

        _NODISCARD bool operator==(const param_type& _Right) const {
            return _Nx == _Right._Nx;
        }

        _NODISCARD bool operator!=(const param_type& _Right) const {
            return !(*this == _Right);
        }

        _NODISCARD _Ty n() const {
            return _Nx;
        }

        void _Init(_Ty _Nx0) { // initialize
            _STL_ASSERT(0 < _Nx0, "invalid n argument for chi_squared_distribution");
            _Nx = _Nx0;
        }

        _Ty _Nx;
    };

    chi_squared_distribution() : _Par(_Ty{ 1 }) {}

    explicit chi_squared_distribution(_Ty _Nx0) : _Par(_Nx0) {}

    explicit chi_squared_distribution(const param_type& _Par0) : _Par(_Par0) {}

    _NODISCARD _Ty n() const {
        return _Par.n();
    }

    _NODISCARD param_type param() const {
        return _Par;
    }

    void param(const param_type& _Par0) { // set parameter package
        _Par = _Par0;
    }

    _NODISCARD result_type(min)() const { // get smallest possible result
        return result_type{ 0.0 };
    }

    _NODISCARD result_type(max)() const { // get largest possible result
        return numeric_limits<result_type>::infinity();
    }

    void reset() {} // clear internal state

    template <class _Engine>
    _NODISCARD result_type operator()(_Engine& _Eng) const {
        return _Eval(_Eng, _Par);
    }

    template <class _Engine>
    _NODISCARD result_type operator()(_Engine& _Eng, const param_type& _Par0) const {
        return _Eval(_Eng, _Par0);
    }

    template <class _Elem, class _Traits>
    basic_istream<_Elem, _Traits>& _Read(basic_istream<_Elem, _Traits>& _Istr) { // read state from _Istr
        _Ty _Nx0;
        _Istr >> _Nx0;
        _Par._Init(_Nx0);
        return _Istr;
    }

    template <class _Elem, class _Traits>
    basic_ostream<_Elem, _Traits>& _Write(basic_ostream<_Elem, _Traits>& _Ostr) const { // write state to _Ostr
        return _Ostr << ' ' << _Par._Nx;
    }

private:
    template <class _Engine>
    result_type _Eval(_Engine& _Eng, const param_type& _Par0) const {
        gamma_distribution<_Ty> _Dist(static_cast<_Ty>(_Par0._Nx) * static_cast<_Ty>(0.5), _Ty{ 2 });
        return _Dist(_Eng);
    }

    param_type _Par;
};

template <class _Ty>
_NODISCARD bool operator==(const chi_squared_distribution<_Ty>& _Left, const chi_squared_distribution<_Ty>& _Right) {
    return _Left.param() == _Right.param();
}

template <class _Ty>
_NODISCARD bool operator!=(const chi_squared_distribution<_Ty>& _Left, const chi_squared_distribution<_Ty>& _Right) {
    return !(_Left == _Right);
}

template <class _Elem, class _Traits, class _Ty>
basic_istream<_Elem, _Traits>& operator>>(basic_istream<_Elem, _Traits>& _Istr,
    chi_squared_distribution<_Ty>& _Dist) { // read state from _Istr
    return _Dist._Read(_Istr);
}

template <class _Elem, class _Traits, class _Ty>
basic_ostream<_Elem, _Traits>& operator<<(basic_ostream<_Elem, _Traits>& _Ostr,
    const chi_squared_distribution<_Ty>& _Dist) { // write state to _Ostr
    return _Dist._Write(_Ostr);
}

template <class _Ty = double>
class cauchy_distribution { // Cauchy distribution
public:
    _RNG_REQUIRE_REALTYPE(cauchy_distribution, _Ty);

    using result_type = _Ty;

    struct param_type { // parameter package
        using distribution_type = cauchy_distribution;

        param_type() {
            _Init(_Ty{ 0 }, _Ty{ 1 });
        }

        explicit param_type(_Ty _Ax0, _Ty _Bx0 = _Ty{ 1 }) {
            _Init(_Ax0, _Bx0);
        }

        _NODISCARD bool operator==(const param_type& _Right) const {
            return _Ax == _Right._Ax && _Bx == _Right._Bx;
        }

        _NODISCARD bool operator!=(const param_type& _Right) const {
            return !(*this == _Right);
        }

        _NODISCARD _Ty a() const {
            return _Ax;
        }

        _NODISCARD _Ty b() const {
            return _Bx;
        }

        void _Init(_Ty _Ax0, _Ty _Bx0) { // initialize
            _STL_ASSERT(0.0 < _Bx0, "invalid b argument for cauchy_distribution");
            _Ax = _Ax0;
            _Bx = _Bx0;
        }

        _Ty _Ax;
        _Ty _Bx;
    };

    cauchy_distribution() : _Par(_Ty{ 0 }, _Ty{ 1 }) {}

    explicit cauchy_distribution(_Ty _Ax0, _Ty _Bx0 = _Ty{ 1 }) : _Par(_Ax0, _Bx0) {}

    explicit cauchy_distribution(const param_type& _Par0) : _Par(_Par0) {}

    _NODISCARD _Ty a() const {
        return _Par.a();
    }

    _NODISCARD _Ty b() const {
        return _Par.b();
    }

    _NODISCARD param_type param() const {
        return _Par;
    }

    void param(const param_type& _Par0) { // set parameter package
        _Par = _Par0;
    }

    _NODISCARD result_type(min)() const { // get smallest possible result
        return -numeric_limits<result_type>::infinity();
    }

    _NODISCARD result_type(max)() const { // get largest possible result
        return numeric_limits<result_type>::infinity();
    }

    void reset() {} // clear internal state

    template <class _Engine>
    _NODISCARD result_type operator()(_Engine& _Eng) const {
        return _Eval(_Eng, _Par);
    }

    template <class _Engine>
    _NODISCARD result_type operator()(_Engine& _Eng, const param_type& _Par0) const {
        return _Eval(_Eng, _Par0);
    }

    template <class _Elem, class _Traits>
    basic_istream<_Elem, _Traits>& _Read(basic_istream<_Elem, _Traits>& _Istr) { // read state from _Istr
        _Ty _Ax0;
        _Ty _Bx0;
        _In(_Istr, _Ax0);
        _In(_Istr, _Bx0);
        _Par._Init(_Ax0, _Bx0);
        return _Istr;
    }

    template <class _Elem, class _Traits>
    basic_ostream<_Elem, _Traits>& _Write(basic_ostream<_Elem, _Traits>& _Ostr) const { // write state to _Ostr
        _Out(_Ostr, _Par._Ax);
        _Out(_Ostr, _Par._Bx);
        return _Ostr;
    }

private:
    template <class _Engine>
    result_type _Eval(_Engine& _Eng, const param_type& _Par0) const { // generate pseudo-random value
        _Ty Px = _NRAND(_Eng, _Ty);
        return static_cast<_Ty>(_Par0._Ax + _Par0._Bx * _CSTD tan(_Pi * (Px - static_cast<_Ty>(0.5))));
    }

    param_type _Par;
};

template <class _Ty>
_NODISCARD bool operator==(const cauchy_distribution<_Ty>& _Left, const cauchy_distribution<_Ty>& _Right) {
    return _Left.param() == _Right.param();
}

template <class _Ty>
_NODISCARD bool operator!=(const cauchy_distribution<_Ty>& _Left, const cauchy_distribution<_Ty>& _Right) {
    return !(_Left == _Right);
}

template <class _Elem, class _Traits, class _Ty>
basic_istream<_Elem, _Traits>& operator>>(basic_istream<_Elem, _Traits>& _Istr,
    cauchy_distribution<_Ty>& _Dist) { // read state from _Istr
    return _Dist._Read(_Istr);
}

template <class _Elem, class _Traits, class _Ty>
basic_ostream<_Elem, _Traits>& operator<<(basic_ostream<_Elem, _Traits>& _Ostr,
    const cauchy_distribution<_Ty>& _Dist) { // write state to _Ostr
    return _Dist._Write(_Ostr);
}

template <class _Ty = double>
class _Beta_distribution { // beta distribution
public:
    using result_type = _Ty;

    explicit _Beta_distribution(const _Ty& _Ax0 = _Ty{ 1 }, const _Ty& _Bx0 = _Ty{ 1 }) {
        _Init(_Ax0, _Bx0);
    }

    template <class _Engine>
    _NODISCARD result_type operator()(_Engine& _Eng) const {
        if (_Ax < _Ty{ 1 } && _Bx < _Ty{ 1 }) { // look for a good value
            _Ty _Wx;
            _Ty _Px1;
            _Ty _Px2;
            for (;;) { // reject large values
                _Px1 = _NRAND(_Eng, _Ty);
                _Px2 = _NRAND(_Eng, _Ty);
                _Px1 = _CSTD pow(_Px1, _Ty{ 1 } / _Ax);
                _Px2 = _CSTD pow(_Px2, _Ty{ 1 } / _Bx);
                _Wx = _Px1 + _Px2;
                if (_Wx <= _Ty{ 1 } && _Wx != _Ty{ 0 }) {
                    break;
                }
            }
            return _Px1 / _Wx;
        }
        else { // use gamma distributions instead
            _Ty _Px1;
            _Ty _Px2;
            _Ty _PSum;
            gamma_distribution<_Ty> _Dist1(_Ax, 1);
            gamma_distribution<_Ty> _Dist2(_Bx, 1);

            for (;;) { // reject pairs whose sum is zero
                _Px1 = _Dist1(_Eng);
                _Px2 = _Dist2(_Eng);
                _PSum = _Px1 + _Px2;

                if (_PSum != _Ty{ 0 }) {
                    break;
                }
            }

            return _Px1 / _PSum;
        }
    }

private:
    void _Init(_Ty _Ax0, _Ty _Bx0) { // initialize
        _STL_ASSERT(0.0 < _Ax0, "invalid a argument for _Beta_distribution");
        _STL_ASSERT(0.0 < _Bx0, "invalid b argument for _Beta_distribution");
        _Ax = _Ax0;
        _Bx = _Bx0;
    }

    _Ty _Ax;
    _Ty _Bx;
};

template <class _Ty = double>
class fisher_f_distribution { // fisher_f distribution
public:
    _RNG_REQUIRE_REALTYPE(fisher_f_distribution, _Ty);

    using result_type = _Ty;

    struct param_type { // parameter package
        using distribution_type = fisher_f_distribution;

        param_type() {
            _Init(_Ty{ 1 }, _Ty{ 1 });
        }

        explicit param_type(_Ty _Mx0, _Ty _Nx0 = _Ty{ 1 }) {
            _Init(_Mx0, _Nx0);
        }

        _NODISCARD bool operator==(const param_type& _Right) const {
            return _Mx == _Right._Mx && _Nx == _Right._Nx;
        }

        _NODISCARD bool operator!=(const param_type& _Right) const {
            return !(*this == _Right);
        }

        _NODISCARD _Ty m() const {
            return _Mx;
        }

        _NODISCARD _Ty n() const {
            return _Nx;
        }

        void _Init(_Ty _Mx0, _Ty _Nx0) { // initialize
            _STL_ASSERT(0 < _Mx0, "invalid m argument for fisher_f_distribution");
            _STL_ASSERT(0 < _Nx0, "invalid n argument for fisher_f_distribution");
            _Mx = _Mx0;
            _Nx = _Nx0;
        }

        _Ty _Mx;
        _Ty _Nx;
    };

    fisher_f_distribution() : _Par(_Ty{ 1 }, _Ty{ 1 }) {}

    explicit fisher_f_distribution(_Ty _Mx0, _Ty _Nx0 = _Ty{ 1 }) : _Par(_Mx0, _Nx0) {}

    explicit fisher_f_distribution(const param_type& _Par0) : _Par(_Par0) {}

    _NODISCARD _Ty m() const {
        return _Par.m();
    }

    _NODISCARD _Ty n() const {
        return _Par.n();
    }

    _NODISCARD param_type param() const {
        return _Par;
    }

    void param(const param_type& _Par0) { // set parameter package
        _Par = _Par0;
    }

    _NODISCARD result_type(min)() const { // get smallest possible result
        return result_type(0);
    }

    _NODISCARD result_type(max)() const { // get largest possible result
        return numeric_limits<result_type>::infinity();
    }

    void reset() {} // clear internal state

    template <class _Engine>
    _NODISCARD result_type operator()(_Engine& _Eng) const {
        return _Eval(_Eng, _Par);
    }

    template <class _Engine>
    _NODISCARD result_type operator()(_Engine& _Eng, const param_type& _Par0) const {
        return _Eval(_Eng, _Par0);
    }

    template <class _Elem, class _Traits>
    basic_istream<_Elem, _Traits>& _Read(basic_istream<_Elem, _Traits>& _Istr) { // read state from _Istr
        _Ty _Mx0;
        _Ty _Nx0;
        _Istr >> _Mx0 >> _Nx0;
        _Par._Init(_Mx0, _Nx0);
        return _Istr;
    }

    template <class _Elem, class _Traits>
    basic_ostream<_Elem, _Traits>& _Write(basic_ostream<_Elem, _Traits>& _Ostr) const { // write state to _Ostr
        _Ostr << ' ' << _Par._Mx << ' ' << _Par._Nx;
        return _Ostr;
    }

private:
    template <class _Engine>
    result_type _Eval(_Engine& _Eng, const param_type& _Par0) const {
        _Ty _Px;
        _Ty _Vx1;
        _Ty _Vx2;
        const _Ty _Vx3{ 1 };
        _Vx1 = static_cast<_Ty>(_Par0._Mx) * static_cast<_Ty>(0.5);
        _Vx2 = static_cast<_Ty>(_Par0._Nx) * static_cast<_Ty>(0.5);
        _Beta_distribution<_Ty> _Dist(_Vx1, _Vx2);
        for (;;) { // reject bad values
            _Px = _Dist(_Eng);
            if (_Px != _Vx3) {
                break;
            }
        }

        return (_Vx2 / _Vx1) * (_Px / (_Vx3 - _Px));
    }

    param_type _Par;
};

template <class _Ty>
_NODISCARD bool operator==(const fisher_f_distribution<_Ty>& _Left, const fisher_f_distribution<_Ty>& _Right) {
    return _Left.param() == _Right.param();
}

template <class _Ty>
_NODISCARD bool operator!=(const fisher_f_distribution<_Ty>& _Left, const fisher_f_distribution<_Ty>& _Right) {
    return !(_Left == _Right);
}

template <class _Elem, class _Traits, class _Ty>
basic_istream<_Elem, _Traits>& operator>>(basic_istream<_Elem, _Traits>& _Istr,
    fisher_f_distribution<_Ty>& _Dist) { // read state from _Istr
    return _Dist._Read(_Istr);
}

template <class _Elem, class _Traits, class _Ty>
basic_ostream<_Elem, _Traits>& operator<<(basic_ostream<_Elem, _Traits>& _Ostr,
    const fisher_f_distribution<_Ty>& _Dist) { // write state to _Ostr
    return _Dist._Write(_Ostr);
}

template <class _Ty = double>
class student_t_distribution { // student_t distribution
public:
    _RNG_REQUIRE_REALTYPE(student_t_distribution, _Ty);

    using result_type = _Ty;

    struct param_type { // parameter package
        using distribution_type = student_t_distribution;

        param_type() {
            _Init(_Ty{ 1 });
        }

        explicit param_type(_Ty _Nx0) {
            _Init(_Nx0);
        }

        _NODISCARD bool operator==(const param_type& _Right) const {
            return _Nx == _Right._Nx;
        }

        _NODISCARD bool operator!=(const param_type& _Right) const {
            return !(*this == _Right);
        }

        _NODISCARD _Ty n() const {
            return _Nx;
        }

        void _Init(_Ty _Nx0) { // initialize
            _STL_ASSERT(0 < _Nx0, "invalid n argument for student_t_distribution");
            _Nx = _Nx0;
        }

        _Ty _Nx;
    };

    student_t_distribution() : _Par(_Ty{ 1 }) {}

    explicit student_t_distribution(_Ty _Nx0) : _Par(_Nx0) {}

    explicit student_t_distribution(const param_type& _Par0) : _Par(_Par0) {}

    _NODISCARD _Ty n() const {
        return _Par.n();
    }

    _NODISCARD param_type param() const {
        return _Par;
    }

    void param(const param_type& _Par0) { // set parameter package
        _Par = _Par0;
    }

    _NODISCARD result_type(min)() const { // get smallest possible result
        return -numeric_limits<result_type>::infinity();
    }

    _NODISCARD result_type(max)() const { // get largest possible result
        return numeric_limits<result_type>::infinity();
    }

    void reset() {} // clear internal state

    template <class _Engine>
    _NODISCARD result_type operator()(_Engine& _Eng) const {
        return _Eval(_Eng, _Par);
    }

    template <class _Engine>
    _NODISCARD result_type operator()(_Engine& _Eng, const param_type& _Par0) const {
        return _Eval(_Eng, _Par0);
    }

    template <class _Elem, class _Traits>
    basic_istream<_Elem, _Traits>& _Read(basic_istream<_Elem, _Traits>& _Istr) { // read state from _Istr
        _Ty _Nx0;
        _Istr >> _Nx0;
        _Par._Init(_Nx0);
        return _Istr;
    }

    template <class _Elem, class _Traits>
    basic_ostream<_Elem, _Traits>& _Write(basic_ostream<_Elem, _Traits>& _Ostr) const { // write state to _Ostr
        return _Ostr << ' ' << _Par._Nx;
    }

private:
    template <class _Engine>
    result_type _Eval(_Engine& _Eng, const param_type& _Par0) const {
        _Ty _Vx1;
        _Ty _Vx2;
        _Ty _Rx0;
        _Ty _Rs;
        uniform_real<_Ty> _Dist(-1, 1);
        for (;;) { // get a point inside unit circle
            _Vx1 = _Dist(_Eng);
            _Vx2 = _Dist(_Eng);
            _Rs = _Vx1 * _Vx1 + _Vx2 * _Vx2;

            // very small _Rs will overflow on pow(_Rx0, -_Ty{4} / _Par0._Nx)
            if (_Rs < _Ty{ 1 } && _Rs > _Ty{ 1e-12 }) {
                break;
            }
        }
        _Rx0 = _STD sqrt(_Rs);
        return _Vx1 * _STD sqrt(_Par0._Nx * (_STD pow(_Rx0, -_Ty{ 4 } / _Par0._Nx) - _Ty{ 1 }) / _Rs);
    }

    param_type _Par;
};

template <class _Ty>
_NODISCARD bool operator==(const student_t_distribution<_Ty>& _Left, const student_t_distribution<_Ty>& _Right) {
    return _Left.param() == _Right.param();
}

template <class _Ty>
_NODISCARD bool operator!=(const student_t_distribution<_Ty>& _Left, const student_t_distribution<_Ty>& _Right) {
    return !(_Left == _Right);
}

template <class _Elem, class _Traits, class _Ty>
basic_istream<_Elem, _Traits>& operator>>(basic_istream<_Elem, _Traits>& _Istr,
    student_t_distribution<_Ty>& _Dist) { // read state from _Istr
    return _Dist._Read(_Istr);
}

template <class _Elem, class _Traits, class _Ty>
basic_ostream<_Elem, _Traits>& operator<<(basic_ostream<_Elem, _Traits>& _Ostr,
    const student_t_distribution<_Ty>& _Dist) { // write state to _Ostr
    return _Dist._Write(_Ostr);
}

template <class _Ty = int>
class negative_binomial_distribution { // negative binomial distribution
public:
    _RNG_REQUIRE_INTTYPE(negative_binomial_distribution, _Ty);

    using result_type = _Ty;

    struct param_type { // parameter package
        using distribution_type = negative_binomial_distribution;

        param_type() {
            _Init(1, 0.5);
        }

        explicit param_type(_Ty _Kx0, double _Px0 = 0.5) {
            _Init(_Kx0, _Px0);
        }

        _NODISCARD bool operator==(const param_type& _Right) const {
            return _Kx == _Right._Kx && _Px == _Right._Px;
        }

        _NODISCARD bool operator!=(const param_type& _Right) const {
            return !(*this == _Right);
        }

        _NODISCARD _Ty k() const {
            return _Kx;
        }

        _NODISCARD double p() const {
            return _Px;
        }

        void _Init(_Ty _Kx0, double _Px0) { // initialize
            _STL_ASSERT(0.0 < _Kx0, "invalid max argument for "
                "negative_binomial_distribution");
            _STL_ASSERT(0.0 < _Px0 && _Px0 <= 1.0, "invalid probability argument for "
                "negative_binomial_distribution");
            _Kx = _Kx0;
            _Px = _Px0;
        }

        _Ty _Kx;
        double _Px;
    };

    negative_binomial_distribution() : _Par(1, 0.5) {}

    explicit negative_binomial_distribution(_Ty _Kx0, double _Px0 = 0.5) : _Par(_Kx0, _Px0) {}

    explicit negative_binomial_distribution(const param_type& _Par0) : _Par(_Par0) {}

    _NODISCARD _Ty k() const {
        return _Par.k();
    }

    _NODISCARD double p() const {
        return _Par.p();
    }

    _NODISCARD param_type param() const {
        return _Par;
    }

    void param(const param_type& _Par0) { // set parameter package
        _Par = _Par0;
    }

    _NODISCARD result_type(min)() const { // get smallest possible result
        return 0;
    }

    _NODISCARD result_type(max)() const { // get largest possible result
        return (numeric_limits<result_type>::max) ();
    }

    void reset() {} // clear internal state

    template <class _Engine>
    _NODISCARD result_type operator()(_Engine& _Eng) const {
        return _Eval(_Eng, _Par);
    }

    template <class _Engine>
    _NODISCARD result_type operator()(_Engine& _Eng, const param_type& _Par0) const {
        return _Eval(_Eng, _Par0);
    }

    template <class _Elem, class _Traits>
    basic_istream<_Elem, _Traits>& _Read(basic_istream<_Elem, _Traits>& _Istr) { // read state from _Istr
        _Ty _Kx0;
        double _Px0;
        _In(_Istr, _Px0);
        _In(_Istr, _Kx0);
        _Par._Init(_Kx0, _Px0);
        return _Istr;
    }

    template <class _Elem, class _Traits>
    basic_ostream<_Elem, _Traits>& _Write(basic_ostream<_Elem, _Traits>& _Ostr) const { // write state to _Ostr
        _Out(_Ostr, _Par._Px);
        _Out(_Ostr, _Par._Kx);
        return _Ostr;
    }

private:
    template <class _Engine>
    result_type _Eval(_Engine& _Eng, const param_type& _Par0) const {
        double _Vx1;
        gamma_distribution<double> _Dist1(
            static_cast<double>(_Par0._Kx), static_cast<double>((_Ty{ 1 } - _Par0._Px) / _Par0._Px));
        _Vx1 = _Dist1(_Eng);
        poisson_distribution<_Ty> _Dist2(_Vx1);

        return _Dist2(_Eng);
    }

    param_type _Par;
};

template <class _Ty>
_NODISCARD bool operator==(
    const negative_binomial_distribution<_Ty>& _Left, const negative_binomial_distribution<_Ty>& _Right) {
    return _Left.param() == _Right.param();
}

template <class _Ty>
_NODISCARD bool operator!=(
    const negative_binomial_distribution<_Ty>& _Left, const negative_binomial_distribution<_Ty>& _Right) {
    return !(_Left == _Right);
}

template <class _Elem, class _Traits, class _Ty>
basic_istream<_Elem, _Traits>& operator>>(basic_istream<_Elem, _Traits>& _Istr,
    negative_binomial_distribution<_Ty>& _Dist) { // read state from _Istr
    return _Dist._Read(_Istr);
}

template <class _Elem, class _Traits, class _Ty>
basic_ostream<_Elem, _Traits>& operator<<(basic_ostream<_Elem, _Traits>& _Ostr,
    const negative_binomial_distribution<_Ty>& _Dist) { // write state to _Ostr
    return _Dist._Write(_Ostr);
}

template <class _Ty = int>
class discrete_distribution { // discrete integer distribution
public:
    _RNG_REQUIRE_INTTYPE(discrete_distribution, _Ty);

    using _Myvec = vector<double>;
    using result_type = _Ty;

    struct param_type { // parameter package
        using distribution_type = discrete_distribution;

        param_type(_Uninitialized) {} // do-nothing constructor for derived classes

        param_type() {
            _Init();
        }

        template <class _InIt>
        param_type(_InIt _First, _InIt _Last) : _Pvec(_First, _Last) {
            _Init();
        }

        param_type(initializer_list<double> _Ilist) : _Pvec(_Ilist) {
            _Init();
        }

        template <class _Fn>
        param_type(size_t _Count, double _Low, double _High, _Fn _Func) {
            double _Range = _High - _Low;
            _STL_ASSERT(0.0 < _Range, "invalid range for discrete_distribution");
            if (_Count <= 0) {
                _Count = 1;
            }

            _Range /= static_cast<double>(_Count);
            _Low += 0.5 * _Range; // evaluate in center of each interval
            for (size_t _Idx = 0; _Idx < _Count; ++_Idx) {
                _Pvec.push_back(_Func(_Low + _Idx * _Range));
            }

            _Init();
        }

        _NODISCARD bool operator==(const param_type& _Right) const {
            return _Pvec == _Right._Pvec;
        }

        _NODISCARD bool operator!=(const param_type& _Right) const {
            return !(*this == _Right);
        }

        _NODISCARD _Myvec probabilities() const {
            return _Pvec;
        }

        void _Init(bool _Renorm = true) { // initialize
            size_t _Size = _Pvec.size();
            size_t _Idx;

            if (_Renorm) {
                if (_Pvec.empty()) {
                    _Pvec.push_back(1.0); // make empty vector degenerate
                }
                else { // normalize probabilities
                    double _Sum = 0;

                    for (_Idx = 0; _Idx < _Size; ++_Idx) { // sum all probabilities
                        _STL_ASSERT(0.0 <= _Pvec[_Idx], "invalid probability for discrete_distribution");
                        _Sum += _Pvec[_Idx];
                    }

                    _STL_ASSERT(0.0 < _Sum, "invalid probability vector for discrete_distribution");
                    if (_Sum != 1.0) {
                        for (_Idx = 0; _Idx < _Size; ++_Idx) {
                            _Pvec[_Idx] /= _Sum;
                        }
                    }
                }
            }

            _Pcdf.assign(1, _Pvec[0]);
            for (_Idx = 1; _Idx < _Size; ++_Idx) {
                _Pcdf.push_back(_Pvec[_Idx] + _Pcdf[_Idx - 1]);
            }
        }

        _Myvec _Pvec;
        _Myvec _Pcdf;
    };

    discrete_distribution() {}

    template <class _InIt>
    discrete_distribution(_InIt _First, _InIt _Last) : _Par(_First, _Last) {}

    discrete_distribution(initializer_list<double> _Ilist) : _Par(_Ilist) {}

    template <class _Fn>
    discrete_distribution(size_t _Count, double _Low, double _High, _Fn _Func) : _Par(_Count, _Low, _High, _Func) {}

    explicit discrete_distribution(const param_type& _Par0) : _Par(_Par0) {}

    _NODISCARD _Myvec probabilities() const {
        return _Par.probabilities();
    }

    _NODISCARD param_type param() const {
        return _Par;
    }

    void param(const param_type& _Par0) { // set parameter package
        _Par = _Par0;
    }

    _NODISCARD result_type(min)() const {
        return 0;
    }

    _NODISCARD result_type(max)() const {
        return static_cast<result_type>(_Par._Pvec.size() - 1);
    }

    void reset() {} // clear internal state

    template <class _Engine>
    _NODISCARD result_type operator()(_Engine& _Eng) const {
        return _Eval(_Eng, _Par);
    }

    template <class _Engine>
    _NODISCARD result_type operator()(_Engine& _Eng, const param_type& _Par0) const {
        return _Eval(_Eng, _Par0);
    }

    template <class _Elem, class _Traits>
    basic_istream<_Elem, _Traits>& _Read(basic_istream<_Elem, _Traits>& _Istr,
        param_type& _Par0) { // read state from _Istr
        size_t _Nvals;
        _Istr >> _Nvals;
        _Par0._Pvec.clear();
        for (; 0 < _Nvals; --_Nvals) { // get a value and add to vector
            double _Val;
            _In(_Istr, _Val);
            _Par0._Pvec.push_back(_Val);
        }
        _Par0._Init(false); // don't renormalize, just compute CDF
        return _Istr;
    }

    template <class _Elem, class _Traits>
    basic_ostream<_Elem, _Traits>& _Write(basic_ostream<_Elem, _Traits>& _Ostr,
        const param_type& _Par0) const { // write state to _Ostr
        size_t _Nvals = _Par0._Pvec.size();
        _Ostr << ' ' << _Nvals;

        for (size_t _Idx = 0; _Idx < _Par0._Pvec.size(); ++_Idx) {
            _Out(_Ostr, _Par0._Pvec[_Idx]);
        }

        return _Ostr;
    }

private:
    template <class _Engine>
    result_type _Eval(_Engine& _Eng, const param_type& _Par0) const {
        double _Px = _NRAND(_Eng, double);
        const auto _First = _Par0._Pcdf.begin();
        const auto _Position = _STD lower_bound(_First, _Prev_iter(_Par0._Pcdf.end()), _Px);
        return static_cast<result_type>(_Position - _First);
    }

public:
    param_type _Par;
};

template <class _Ty>
_NODISCARD bool operator==(const discrete_distribution<_Ty>& _Left, const discrete_distribution<_Ty>& _Right) {
    return _Left.param() == _Right.param();
}

template <class _Ty>
_NODISCARD bool operator!=(const discrete_distribution<_Ty>& _Left, const discrete_distribution<_Ty>& _Right) {
    return !(_Left == _Right);
}

template <class _Elem, class _Traits, class _Ty>
basic_istream<_Elem, _Traits>& operator>>(basic_istream<_Elem, _Traits>& _Istr,
    discrete_distribution<_Ty>& _Dist) { // read state from _Istr
    return _Dist._Read(_Istr, _Dist._Par);
}

template <class _Elem, class _Traits, class _Ty>
basic_ostream<_Elem, _Traits>& operator<<(basic_ostream<_Elem, _Traits>& _Ostr,
    const discrete_distribution<_Ty>& _Dist) { // write state to _Ostr
    return _Dist._Write(_Ostr, _Dist._Par);
}

template <class _Ty = double>
class piecewise_constant_distribution
    : public discrete_distribution<size_t> { // piecewise constant floating-point distribution
public:
    _RNG_REQUIRE_REALTYPE(piecewise_constant_distribution, _Ty);

    using _Mybase = discrete_distribution<size_t>;
    using _Mypbase = typename _Mybase::param_type;
    using result_type = _Ty;

    struct param_type : _Mypbase { // parameter package
        using distribution_type = piecewise_constant_distribution;

        param_type() : _Bvec{ 0, 1 } {}

        template <class _InIt1, class _InIt2>
        param_type(_InIt1 _First1, _InIt1 _Last1, _InIt2 _First2) : _Mypbase(_Noinit), _Bvec(_First1, _Last1) {
            if (2 <= _Bvec.size()) {
                for (size_t _Idx = 0; _Idx < _Bvec.size() - 1; ++_Idx) {
                    this->_Pvec.push_back(static_cast<double>(*_First2++));
                }
            }
            else { // default construct
                _Bvec = { 0, 1 };
            }

            _Init();
        }

        template <class _Fn>
        param_type(initializer_list<_Ty> _Ilist, _Fn _Func) : _Mypbase(_Noinit) {
            if (2 <= _Ilist.size()) {
                _Bvec.assign(_Ilist);

                for (size_t _Idx = 0; _Idx < _Bvec.size() - 1; ++_Idx) {
                    this->_Pvec.push_back(_Func(_Ty{ 0.5 } *(_Bvec[_Idx] + _Bvec[_Idx + 1])));
                }
            }
            else { // default construct
                _Bvec = { 0, 1 };
            }

            _Init();
        }

        template <class _Fn>
        param_type(size_t _Count, _Ty _Low, _Ty _High, _Fn _Func) : _Mypbase(_Count, _Low, _High, _Func) {
            _Ty _Range = _High - _Low;
            if (_Count <= 0) {
                _Count = 1;
            }

            _Range /= static_cast<_Ty>(_Count);
            for (size_t _Idx = 0; _Idx <= _Count; ++_Idx) {
                _Bvec.push_back(_Low + _Idx * _Range);
            }
        }

        _NODISCARD bool operator==(const param_type& _Right) const {
            return static_cast<const _Mypbase&>(*this) == static_cast<const _Mypbase&>(_Right) && _Bvec == _Right._Bvec;
        }

        _NODISCARD bool operator!=(const param_type& _Right) const {
            return !(*this == _Right);
        }

        _NODISCARD vector<_Ty> intervals() const {
            return _Bvec;
        }

        _NODISCARD vector<_Ty> densities() const {
            vector<_Ty> _Ans(this->_Pvec.begin(), this->_Pvec.end());

            for (size_t _Idx = 0; _Idx < _Ans.size(); ++_Idx) {
                _Ans[_Idx] /= _Bvec[_Idx + 1] - _Bvec[_Idx];
            }

            return _Ans;
        }

        void _Init() { // initialize
            _Mypbase::_Init();
        }

        vector<_Ty> _Bvec;
    };

    piecewise_constant_distribution() {}

    template <class _InIt1, class _InIt2>
    piecewise_constant_distribution(_InIt1 _First1, _InIt1 _Last1, _InIt2 _First2) : _Par(_First1, _Last1, _First2) {}

    template <class _Fn>
    piecewise_constant_distribution(initializer_list<_Ty> _Ilist, _Fn _Func) : _Par(_Ilist, _Func) {}

    template <class _Fn>
    piecewise_constant_distribution(size_t _Count, _Ty _Low, _Ty _High, _Fn _Func) : _Par(_Count, _Low, _High, _Func) {}

    explicit piecewise_constant_distribution(const param_type& _Par0) : _Par(_Par0) {}

    _NODISCARD vector<_Ty> intervals() const {
        return _Par.intervals();
    }

    _NODISCARD vector<_Ty> densities() const {
        return _Par.densities();
    }

    _NODISCARD param_type param() const {
        return _Par;
    }

    void param(const param_type& _Par0) { // set parameter package
        _Par = _Par0;
    }

    _NODISCARD result_type(min)() const {
        return _Par._Bvec.front();
    }

    _NODISCARD result_type(max)() const {
        return _Par._Bvec.back();
    }

    void reset() {} // clear internal state

    template <class _Engine>
    _NODISCARD result_type operator()(_Engine& _Eng) const {
        return _Eval(_Eng, _Par);
    }

    template <class _Engine>
    _NODISCARD result_type operator()(_Engine& _Eng, const param_type& _Par0) const {
        return _Eval(_Eng, _Par0);
    }

    template <class _Elem, class _Traits>
    basic_istream<_Elem, _Traits>& _Read(basic_istream<_Elem, _Traits>& _Istr) { // read state from _Istr
        _Mybase::_Read(_Istr, _Par);

        _Par._Bvec.clear();
        for (size_t _Idx = _Par._Pvec.size() + 1; 0 < _Idx; --_Idx) { // get a value and add to intervals vector
            double _Val;
            _In(_Istr, _Val);
            _Par._Bvec.push_back(_Val);
        }
        return _Istr;
    }

    template <class _Elem, class _Traits>
    basic_ostream<_Elem, _Traits>& _Write(basic_ostream<_Elem, _Traits>& _Ostr) const { // write state to _Ostr
        _Mybase::_Write(_Ostr, _Par);

        for (size_t _Idx = 0; _Idx < _Par._Bvec.size(); ++_Idx) {
            _Out(_Ostr, _Par._Bvec[_Idx]);
        }

        return _Ostr;
    }

    template <class _Engine>
    result_type _Eval(_Engine& _Eng, const param_type& _Par0) const {
        size_t _Px = _Mybase::operator()(_Eng, _Par0);
        uniform_real<_Ty> _Dist(_Par0._Bvec[_Px], _Par0._Bvec[_Px + 1]);
        return _Dist(_Eng);
    }

    param_type _Par;
};

template <class _Ty>
_NODISCARD bool operator==(
    const piecewise_constant_distribution<_Ty>& _Left, const piecewise_constant_distribution<_Ty>& _Right) {
    return _Left.param() == _Right.param();
}

template <class _Ty>
_NODISCARD bool operator!=(
    const piecewise_constant_distribution<_Ty>& _Left, const piecewise_constant_distribution<_Ty>& _Right) {
    return !(_Left == _Right);
}

template <class _Elem, class _Traits, class _Ty>
basic_istream<_Elem, _Traits>& operator>>(basic_istream<_Elem, _Traits>& _Istr,
    piecewise_constant_distribution<_Ty>& _Dist) { // read state from _Istr
    return _Dist._Read(_Istr);
}

template <class _Elem, class _Traits, class _Ty>
basic_ostream<_Elem, _Traits>& operator<<(basic_ostream<_Elem, _Traits>& _Ostr,
    const piecewise_constant_distribution<_Ty>& _Dist) { // write state to _Ostr
    return _Dist._Write(_Ostr);
}

template <class _Ty = double>
class piecewise_linear_distribution
    : public discrete_distribution<size_t> { // piecewise linear floating-point distribution
public:
    _RNG_REQUIRE_REALTYPE(piecewise_linear_distribution, _Ty);

    using _Mybase = discrete_distribution<size_t>;
    using _Mypbase = typename _Mybase::param_type;
    using result_type = _Ty;

    struct param_type : _Mypbase { // parameter package
        // TRANSITION, ABI: stores probability densities (N + 1 elements) in _Mybase::_Pvec
        // this breaks invariants of discrete_distribution<size_t>::param_type
        using distribution_type = piecewise_linear_distribution;

        param_type() : _Bvec{ 0, 1 } {
            this->_Pvec.push_back(1.0);
        }

        template <class _InIt1, class _InIt2>
        param_type(_InIt1 _First1, _InIt1 _Last1, _InIt2 _First2) : _Mypbase(_Noinit), _Bvec(_First1, _Last1) {
            if (2 <= _Bvec.size()) {
                for (size_t _Idx = 0; _Idx < _Bvec.size(); ++_Idx) {
                    this->_Pvec.push_back(static_cast<double>(*_First2++));
                }
            }
            else { // default construct
                _Bvec = { 0, 1 };
            }

            _Init();
        }

        template <class _Fn>
        param_type(initializer_list<_Ty> _Ilist, _Fn _Func) : _Mypbase(_Noinit) {
            if (2 <= _Ilist.size()) {
                _Bvec.assign(_Ilist);

                for (const auto& _Bval : _Bvec) {
                    this->_Pvec.push_back(_Func(_Bval));
                }
            }
            else { // default construct
                _Bvec = { 0, 1 };
            }

            _Init();
        }

        template <class _Fn>
        param_type(size_t _Count, _Ty _Low, _Ty _High, _Fn _Func) : _Mypbase(_Noinit) {
            _Ty _Range = _High - _Low;
            _STL_ASSERT(_Ty{ 0 } < _Range, "invalid range for piecewise_linear_distribution");
            if (_Count < 1) {
                _Count = 1;
            }

            _Range /= static_cast<double>(_Count);
            for (size_t _Idx = 0; _Idx <= _Count; ++_Idx) { // compute _Bvec and _Pvec
                _Ty _Bval = _Low + _Idx * _Range;
                _Bvec.push_back(_Bval);
                this->_Pvec.push_back(_Func(_Bval));
            }
            _Init();
        }

        _NODISCARD bool operator==(const param_type& _Right) const {
            return static_cast<const _Mypbase&>(*this) == static_cast<const _Mypbase&>(_Right) && _Bvec == _Right._Bvec;
        }

        _NODISCARD bool operator!=(const param_type& _Right) const {
            return !(*this == _Right);
        }

        _NODISCARD vector<_Ty> intervals() const {
            return _Bvec;
        }

        _NODISCARD vector<_Ty> densities() const {
            vector<_Ty> _Ans(this->_Pvec.begin(), this->_Pvec.end());
            return _Ans;
        }

        _NODISCARD double _Piece_probability(const size_t _Idx) const {
            return 0.5 * (this->_Pvec[_Idx] + this->_Pvec[_Idx + 1])
                * static_cast<double>(_Bvec[_Idx + 1] - _Bvec[_Idx]);
        }

        void _Init(bool _Renorm = true) { // initialize
            size_t _Size = this->_Pvec.size();
            size_t _Idx;

            if (_Renorm) {
                if (this->_Pvec.empty()) { // make empty vector degenerate
                    this->_Pvec = { 1.0, 1.0 };
                }
                else { // normalize probabilities
                    double _Sum = 0;

                    _STL_ASSERT(0.0 <= this->_Pvec[0], "invalid probability for "
                        "piecewise_linear_distribution");
                    for (_Idx = 1; _Idx < _Size; ++_Idx) { // sum all probabilities
                        _STL_ASSERT(0.0 <= this->_Pvec[_Idx], "invalid probability for "
                            "piecewise_linear_distribution");
                        _Sum += _Piece_probability(_Idx - 1);
                    }

                    _STL_ASSERT(0.0 < _Sum, "invalid probability vector for "
                        "piecewise_linear_distribution");
                    if (_Sum != 1.0) {
                        for (_Idx = 0; _Idx < _Size; ++_Idx) {
                            this->_Pvec[_Idx] /= _Sum;
                        }
                    }
                }
            }

            this->_Pcdf.assign(1, _Piece_probability(0));
            for (_Idx = 2; _Idx < _Size; ++_Idx) {
                this->_Pcdf.push_back(_Piece_probability(_Idx - 1) + this->_Pcdf[_Idx - 2]);
            }
        }

        vector<_Ty> _Bvec;
    };

    piecewise_linear_distribution() {}

    template <class _InIt1, class _InIt2>
    piecewise_linear_distribution(_InIt1 _First1, _InIt1 _Last1, _InIt2 _First2) : _Par(_First1, _Last1, _First2) {}

    template <class _Fn>
    piecewise_linear_distribution(initializer_list<_Ty> _Ilist, _Fn _Func) : _Par(_Ilist, _Func) {}

    template <class _Fn>
    piecewise_linear_distribution(size_t _Count, _Ty _Low, _Ty _High, _Fn _Func) : _Par(_Count, _Low, _High, _Func) {}

    explicit piecewise_linear_distribution(const param_type& _Par0) : _Par(_Par0) {}

    _NODISCARD vector<_Ty> intervals() const {
        return _Par.intervals();
    }

    _NODISCARD vector<_Ty> densities() const {
        return _Par.densities();
    }

    _NODISCARD param_type param() const {
        return _Par;
    }

    void param(const param_type& _Par0) { // set parameter package
        _Par = _Par0;
    }

    _NODISCARD result_type(min)() const {
        return _Par._Bvec.front();
    }

    _NODISCARD result_type(max)() const {
        return _Par._Bvec.back();
    }

    void reset() {} // clear internal state

    template <class _Engine>
    _NODISCARD result_type operator()(_Engine& _Eng) const {
        return _Eval(_Eng, _Par);
    }

    template <class _Engine>
    _NODISCARD result_type operator()(_Engine& _Eng, const param_type& _Par0) const {
        return _Eval(_Eng, _Par0);
    }

    template <class _Elem, class _Traits>
    basic_istream<_Elem, _Traits>& _Read(basic_istream<_Elem, _Traits>& _Istr,
        param_type& _Par0) { // read state from _Istr
        size_t _Nvals;
        _Istr >> _Nvals;
        _Par0._Pvec.clear();
        for (; 0 < _Nvals; --_Nvals) { // get a value and add to vector
            double _Val;
            _In(_Istr, _Val);
            _Par0._Pvec.push_back(_Val);
        }

        _Par0._Bvec.clear();
        for (size_t _Idx = _Par0._Pvec.size(); 0 < _Idx; --_Idx) { // get a value and add to intervals vector
            double _Val;
            _In(_Istr, _Val);
            _Par0._Bvec.push_back(_Val);
        }
        _Par0._Init(false); // don't renormalize, just compute CDF
        return _Istr;
    }

    template <class _Elem, class _Traits>
    basic_ostream<_Elem, _Traits>& _Write(basic_ostream<_Elem, _Traits>& _Ostr) const { // write state to _Ostr
        _Mybase::_Write(_Ostr, _Par);

        for (size_t _Idx = 0; _Idx < _Par._Bvec.size(); ++_Idx) {
            _Out(_Ostr, _Par._Bvec[_Idx]);
        }

        return _Ostr;
    }

    template <class _Engine>
    result_type _Eval(_Engine& _Eng, const param_type& _Par0) const {
        size_t _Px = _Mybase::operator()(_Eng, _Par0);
        double _Px0 = _Par0._Pvec[_Px];
        double _Px1 = _Par0._Pvec[_Px + 1];
        uniform_real<_Ty> _Dist;
        result_type _Xx0 = _Dist(_Eng);

        if (_Px0 != _Px1) {
            _Xx0 = static_cast<result_type>(
                (_STD sqrt(_Px0 * _Px0 * (1.0 - _Xx0) + _Px1 * _Px1 * _Xx0) - _Px0) / (_Px1 - _Px0));
        }

        return _Par0._Bvec[_Px] + _Xx0 * (_Par0._Bvec[_Px + 1] - _Par0._Bvec[_Px]);
    }

    param_type _Par;
};

template <class _Ty>
_NODISCARD bool operator==(
    const piecewise_linear_distribution<_Ty>& _Left, const piecewise_linear_distribution<_Ty>& _Right) {
    return _Left.param() == _Right.param();
}

template <class _Ty>
_NODISCARD bool operator!=(
    const piecewise_linear_distribution<_Ty>& _Left, const piecewise_linear_distribution<_Ty>& _Right) {
    return !(_Left == _Right);
}

template <class _Elem, class _Traits, class _Ty>
basic_istream<_Elem, _Traits>& operator>>(basic_istream<_Elem, _Traits>& _Istr,
    piecewise_linear_distribution<_Ty>& _Dist) { // read state from _Istr
    return _Dist._Read(_Istr, _Dist._Par);
}

template <class _Elem, class _Traits, class _Ty>
basic_ostream<_Elem, _Traits>& operator<<(basic_ostream<_Elem, _Traits>& _Ostr,
    const piecewise_linear_distribution<_Ty>& _Dist) { // write state to _Ostr
    return _Dist._Write(_Ostr);
}

using minstd_rand0 = linear_congruential_engine<unsigned int, 16807, 0, 2147483647>;
using minstd_rand = linear_congruential_engine<unsigned int, 48271, 0, 2147483647>;

using mt19937 = mersenne_twister_engine<unsigned int, 32, 624, 397, 31, 0x9908b0df, 11, 0xffffffff, 7, 0x9d2c5680, 15,
    0xefc60000, 18, 1812433253>;

#if _HAS_TR1_NAMESPACE
_STL_DISABLE_DEPRECATED_WARNING
using _Ranbase = subtract_with_carry<unsigned int, 1 << 24, 10, 24>;
_DEPRECATE_TR1_NAMESPACE typedef discard_block<_Ranbase, 223, 24> ranlux3;
_DEPRECATE_TR1_NAMESPACE typedef discard_block<_Ranbase, 389, 24> ranlux4;

_DEPRECATE_TR1_NAMESPACE typedef subtract_with_carry_01<float, 24, 10, 24> ranlux_base_01;
_DEPRECATE_TR1_NAMESPACE typedef subtract_with_carry_01<double, 48, 5, 12> ranlux64_base_01;
_DEPRECATE_TR1_NAMESPACE typedef discard_block<ranlux_base_01, 223, 24> ranlux3_01;
_DEPRECATE_TR1_NAMESPACE typedef discard_block<ranlux_base_01, 389, 24> ranlux4_01;
_STL_RESTORE_DEPRECATED_WARNING
#endif // _HAS_TR1_NAMESPACE

using mt19937_64 = mersenne_twister_engine<unsigned long long, 64, 312, 156, 31, 0xb5026f5aa96619e9ULL, 29,
    0x5555555555555555ULL, 17, 0x71d67fffeda60000ULL, 37, 0xfff7eee000000000ULL, 43, 6364136223846793005ULL>;

using ranlux24_base = subtract_with_carry_engine<unsigned int, 24, 10, 24>;
using ranlux48_base = subtract_with_carry_engine<unsigned long long, 48, 5, 12>;
using ranlux24 = discard_block_engine<ranlux24_base, 223, 23>;
using ranlux48 = discard_block_engine<ranlux48_base, 389, 11>;
using knuth_b = shuffle_order_engine<minstd_rand0, 256>;

using default_random_engine = mt19937;


_CRTIMP2_PURE unsigned int __CLRCALL_PURE_OR_CDECL _Random_device();

class random_device { // class to generate random numbers (from hardware where available)
public:
    using result_type = unsigned int;

    random_device() {}

    explicit random_device(const string&) {}

    _NODISCARD static constexpr result_type(min)() {
        return 0;
    }

    _NODISCARD static constexpr result_type(max)() {
        return static_cast<result_type>(-1);
    }

    _NODISCARD double entropy() const noexcept {
        return 32.0;
    }

    _NODISCARD result_type operator()() {
        return _Random_device();
    }

    random_device(const random_device&) = delete;
    random_device& operator=(const random_device&) = delete;
};

#if _HAS_TR1_NAMESPACE
_STL_DISABLE_DEPRECATED_WARNING
namespace _DEPRECATE_TR1_NAMESPACE tr1 {
    using _STD bernoulli_distribution;
    using _STD binomial_distribution;
    using _STD discard_block;
    using _STD exponential_distribution;
    using _STD gamma_distribution;
    using _STD geometric_distribution;
    using _STD linear_congruential;
    using _STD mersenne_twister;
    using _STD minstd_rand;
    using _STD minstd_rand0;
    using _STD mt19937;
    using _STD normal_distribution;
    using _STD poisson_distribution;
    using _STD random_device;
    using _STD ranlux3;
    using _STD ranlux3_01;
    using _STD ranlux4;
    using _STD ranlux4_01;
    using _STD ranlux64_base_01;
    using _STD ranlux_base_01;
    using _STD subtract_with_carry;
    using _STD subtract_with_carry_01;
    using _STD uniform_int;
    using _STD uniform_real;
    using _STD cauchy_distribution;
    using _STD chi_squared_distribution;
    using _STD default_random_engine;
    using _STD discard_block_engine;
    using _STD discrete_distribution;
    using _STD extreme_value_distribution;
    using _STD fisher_f_distribution;
    using _STD generate_canonical;
    using _STD independent_bits_engine;
    using _STD knuth_b;
    using _STD linear_congruential_engine;
    using _STD lognormal_distribution;
    using _STD mersenne_twister_engine;
    using _STD mt19937_64;
    using _STD negative_binomial_distribution;
    using _STD piecewise_constant_distribution;
    using _STD piecewise_linear_distribution;
    using _STD ranlux24;
    using _STD ranlux24_base;
    using _STD ranlux48;
    using _STD ranlux48_base;
    using _STD seed_seq;
    using _STD shuffle_order_engine;
    using _STD student_t_distribution;
    using _STD subtract_with_carry_engine;
    using _STD uniform_int_distribution;
    using _STD uniform_real_distribution;
    using _STD weibull_distribution;
} // namespace tr1
_STL_RESTORE_DEPRECATED_WARNING
#endif // _HAS_TR1_NAMESPACE
_STD_END

#undef _NRAND

#pragma pop_macro("new")
_STL_RESTORE_CLANG_WARNINGS
#pragma warning(pop)
#pragma pack(pop)
#endif // _STL_COMPILER_PREPROCESSOR
#endif // _RANDOM_
