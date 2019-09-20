// Simd Abi specific implementations -*- C++ -*-

// Copyright © 2015-2019 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH
//                       Matthias Kretz <m.kretz@gsi.de>
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//     * Redistributions of source code must retain the above copyright
//       notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above copyright
//       notice, this list of conditions and the following disclaimer in the
//       documentation and/or other materials provided with the distribution.
//     * Neither the names of contributing organizations nor the
//       names of its contributors may be used to endorse or promote products
//       derived from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER BE LIABLE FOR ANY
// DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
// ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#ifndef _GLIBCXX_EXPERIMENTAL_SIMD_ABIS_H_
#define _GLIBCXX_EXPERIMENTAL_SIMD_ABIS_H_

#if __cplusplus >= 201703L

#include <array>
#include <cmath>
#include <cstdlib>

_GLIBCXX_SIMD_BEGIN_NAMESPACE
// _S_allbits{{{
template <typename _V>
static inline constexpr _V _S_allbits = reinterpret_cast<_V>(
  ~std::conditional_t<
    (sizeof(_V) < sizeof(__intrinsic_type_t<_LLong, 2>)),
    __vector_type_t<int, sizeof(_V) / sizeof(int)>,
    __intrinsic_type_t<_LLong, sizeof(_V) / sizeof(_LLong)>>());

// }}}
// _S_signmask, _S_absmask{{{
template <typename _V, typename = _VectorTraits<_V>>
static inline constexpr _V _S_signmask = __xor(_V() + 1, _V() - 1);
template <typename _V, typename = _VectorTraits<_V>>
static inline constexpr _V _S_absmask = __andnot(_S_signmask<_V>, _S_allbits<_V>);

//}}}
// __xzyw{{{
// shuffles the complete vector, swapping the inner two quarters. Often useful for AVX for
// fixing up a shuffle result.
template <class _Tp, class _TVT = _VectorTraits<_Tp>>
_GLIBCXX_SIMD_INTRINSIC _Tp __xzyw(_Tp __a)
{
    if constexpr (sizeof(_Tp) == 16) {
        static_assert(sizeof(float) == 4 && sizeof(int) == 4);
        const auto __x = __vector_bitcast<
            conditional_t<is_floating_point_v<typename _TVT::value_type>, float, int>>(
            __a);
        return reinterpret_cast<_Tp>(decltype(__x){__x[0], __x[2], __x[1], __x[3]});
    } else if constexpr (sizeof(_Tp) == 32) {
        static_assert(sizeof(double) == 8 && sizeof(_LLong) == 8);
        const auto __x =
            __vector_bitcast<conditional_t<is_floating_point_v<typename _TVT::value_type>,
                                           double, _LLong>>(__a);
        return reinterpret_cast<_Tp>(decltype(__x){__x[0], __x[2], __x[1], __x[3]});
    } else if constexpr (sizeof(_Tp) == 64) {
        static_assert(sizeof(double) == 8 && sizeof(_LLong) == 8);
        const auto __x =
            __vector_bitcast<conditional_t<is_floating_point_v<typename _TVT::value_type>,
                                           double, _LLong>>(__a);
        return reinterpret_cast<_Tp>(decltype(__x){__x[0], __x[1], __x[4], __x[5], __x[2],
                                                  __x[3], __x[6], __x[7]});
    } else {
        __assert_unreachable<_Tp>();
    }
}

// }}}
// __shift_elements_right{{{
// if (__shift % 2ⁿ == 0) => the low n Bytes are correct
template <unsigned __shift, class _Tp, class _TVT = _VectorTraits<_Tp>>
_GLIBCXX_SIMD_INTRINSIC _Tp __shift_elements_right(_Tp __v)
{
  [[maybe_unused]] const auto __iv = __to_intrin(__v);
  static_assert(__shift <= sizeof(_Tp));
  if constexpr (__shift == 0)
    return __v;
  else if constexpr (__shift == sizeof(_Tp))
    return _Tp();
#if _GLIBCXX_SIMD_X86INTRIN // {{{
  else if constexpr (__have_sse && __shift == 8 &&
		     _TVT::template __is<float, 4>)
    return _mm_movehl_ps(__iv, __iv);
  else if constexpr (__have_sse2 && __shift == 8 &&
		     _TVT::template __is<double, 2>)
    return _mm_unpackhi_pd(__iv, __iv);
  else if constexpr (__have_sse2 && sizeof(_Tp) == 16)
    return reinterpret_cast<typename _TVT::type>(
      _mm_srli_si128(reinterpret_cast<__m128i>(__iv), __shift));
  else if constexpr (__shift == 16 && sizeof(_Tp) == 32)
    {
      /*if constexpr (__have_avx && _TVT::template __is<double, 4>)
	return _mm256_permute2f128_pd(__iv, __iv, 0x81);
      else if constexpr (__have_avx && _TVT::template __is<float, 8>)
	return _mm256_permute2f128_ps(__iv, __iv, 0x81);
      else if constexpr (__have_avx)
	return reinterpret_cast<typename _TVT::type>(
	  _mm256_permute2f128_si256(__iv, __iv, 0x81));
      else*/
	return __zero_extend(__hi128(__v));
    }
  else if constexpr (__have_avx2 && sizeof(_Tp) == 32 && __shift < 16)
    {
      const auto __vll = __vector_bitcast<_LLong>(__v);
      return reinterpret_cast<typename _TVT::type>(_mm256_alignr_epi8(
	_mm256_permute2x128_si256(__vll, __vll, 0x81), __vll, __shift));
    }
  else if constexpr (__have_avx && sizeof(_Tp) == 32 && __shift < 16)
    {
      const auto __vll = __vector_bitcast<_LLong>(__v);
      return reinterpret_cast<typename _TVT::type>(
	__concat(_mm_alignr_epi8(__hi128(__vll), __lo128(__vll), __shift),
		 _mm_srli_si128(__hi128(__vll), __shift)));
    }
  else if constexpr (sizeof(_Tp) == 32 && __shift > 16)
    return __zero_extend(__shift_elements_right<__shift - 16>(__hi128(__v)));
  else if constexpr (sizeof(_Tp) == 64 && __shift == 32)
    return __zero_extend(__hi256(__v));
  else if constexpr (__have_avx512f && sizeof(_Tp) == 64)
    {
      if constexpr(__shift >= 48)
	return __zero_extend( __shift_elements_right<__shift - 48>(__extract<3, 4>(__v)));
      else if constexpr(__shift >= 32)
	return __zero_extend(__shift_elements_right<__shift - 32>(__hi256(__v)));
      else if constexpr (__shift % 8 == 0)
	return reinterpret_cast<typename _TVT::type>(_mm512_alignr_epi64(
	  __m512i(), __intrin_bitcast<__m512i>(__v), __shift / 8));
      else if constexpr (__shift % 4 == 0)
	return reinterpret_cast<typename _TVT::type>(_mm512_alignr_epi32(
	  __m512i(), __intrin_bitcast<__m512i>(__v), __shift / 4));
      else if constexpr(__have_avx512bw && __shift < 16)
	{
	  const auto __vll = __vector_bitcast<_LLong>(__v);
	  return reinterpret_cast<typename _TVT::type>(_mm512_alignr_epi8(
	    _mm512_shuffle_i32x4(__vll, __vll, 0xf9), __vll, __shift));
	}
      else if constexpr(__have_avx512bw && __shift < 32)
	{
	  const auto __vll = __vector_bitcast<_LLong>(__v);
	  return reinterpret_cast<typename _TVT::type>(_mm512_alignr_epi8(
	    _mm512_shuffle_i32x4(__vll, __m512i(), 0xee),
	    _mm512_shuffle_i32x4(__vll, __vll, 0xf9), __shift - 16));
	}
      else
	__assert_unreachable<_Tp>();
    }
/*
    } else if constexpr (__shift % 16 == 0 && sizeof(_Tp) == 64)
        return __auto_bitcast(__extract<__shift / 16, 4>(__v));
*/
#endif // _GLIBCXX_SIMD_X86INTRIN }}}
  else
    {
      constexpr int __chunksize =
	__shift % 8 == 0 ? 8 : __shift % 4 == 0 ? 4 : __shift % 2 == 0 ? 2 : 1;
      auto __w = __vector_bitcast<__int_with_sizeof_t<__chunksize>>(__v);
      using _U = decltype(__w);
      return __intrin_bitcast<_Tp>(
	__call_with_n_evaluations<(sizeof(_Tp) - __shift) / __chunksize>(
	  [](auto... __chunks) { return _U{__chunks...}; },
	  [&](auto __i) { return __w[__shift / __chunksize + __i]; }));
    }
}

// }}}
// __extract_part(_Tp) {{{
template <int _Index, int _Total, int _Combine, typename _Tp, size_t _N>
_GLIBCXX_SIMD_INTRINSIC
  _GLIBCXX_SIMD_CONST _SimdWrapper<_Tp, _N / _Total * _Combine>
		      __extract_part(const _SimdWrapper<_Tp, _N> __x)
{
  if constexpr (_Index % 2 == 0 && _Total % 2 == 0 && _Combine % 2 == 0)
    return __extract_part<_Index / 2, _Total / 2, _Combine / 2>(__x);
  else
    {
      constexpr size_t __values_per_part = _N / _Total;
      constexpr size_t __values_to_skip  = _Index * __values_per_part;
      constexpr size_t __return_size     = __values_per_part * _Combine;
      using _R = __vector_type_t<_Tp, __return_size>;
      static_assert((_Index + _Combine) * __values_per_part * sizeof(_Tp) <=
		      sizeof(__x),
		    "out of bounds __extract_part");
      // the following assertion would ensure no "padding" to be read
      //static_assert(_Total >= _Index + _Combine, "_Total must be greater than _Index");

      // static_assert(__return_size * _Total == _N, "_N must be divisible by
      // _Total");
      if constexpr (_Index == 0 && _Total == 1)
	return __x;
      else if constexpr (_Index == 0)
	return __intrin_bitcast<_R>(__as_vector(__x));
#if _GLIBCXX_SIMD_X86INTRIN // {{{
      else if constexpr (sizeof(__x) == 32 && __return_size * sizeof(_Tp) <= 16)
	{
	  constexpr size_t __bytes_to_skip = __values_to_skip * sizeof(_Tp);
	  if constexpr (__bytes_to_skip == 16)
	    return __vector_bitcast<_Tp, __return_size>(
	      __hi128(__as_vector(__x)));
	  else
	    return __vector_bitcast<_Tp, __return_size>(_mm_alignr_epi8(
	      __hi128(__vector_bitcast<_LLong>(__x)),
	      __lo128(__vector_bitcast<_LLong>(__x)), __bytes_to_skip));
	}
#endif // _GLIBCXX_SIMD_X86INTRIN }}}
      else if constexpr (_Index > 0 &&
			 (__values_to_skip % __return_size != 0 ||
			  sizeof(_R) >= 8) &&
			 (__values_to_skip + __return_size) * sizeof(_Tp) <=
			   64 &&
			 sizeof(__x) >= 16)
	return __intrin_bitcast<_R>(
	  __shift_elements_right<__values_to_skip * sizeof(_Tp)>(
	    __as_vector(__x)));
      else
	{
	  _R __r = {};
	  __builtin_memcpy(&__r,
			   reinterpret_cast<const char*>(&__x) +
			     sizeof(_Tp) * __values_to_skip,
			   __return_size * sizeof(_Tp));
	  return __r;
	}
    }
}

// }}}
// __extract_part(_SimdWrapper<bool, _N>) {{{
template <int _Index, int _Total, int _Combine = 1, size_t _N>
_GLIBCXX_SIMD_INTRINSIC constexpr __bool_storage_member_type_t<_N / _Total>
  __extract_part(_SimdWrapper<bool, _N> __x)
{
  static_assert(_Combine == 1, "_Combine != 1 not implemented");
  static_assert(__have_avx512f && _N == _N);
  static_assert(_Total >= 2 && _Index + _Combine <= _Total && _Index >= 0);
  return __x._M_data >> (_Index * _N / _Total);
}

// }}}
// _ToWrapper specializations for bitset and __mmask<_N> {{{
#if _GLIBCXX_SIMD_HAVE_AVX512_ABI && _GLIBCXX_SIMD_X86INTRIN
template <size_t _N> class _ToWrapper<std::bitset<_N>>
{
    std::bitset<_N> _M_data;

public:
    // can convert to larger storage for _Abi::_S_is_partial == true
    template <class _U, size_t _M> constexpr operator _SimdWrapper<_U, _M>() const
    {
        static_assert(_M >= _N);
        return __convert_mask<_SimdWrapper<_U, _M>>(_M_data);
    }
};

#define _GLIBCXX_SIMD_TO_STORAGE(_Type)                                                  \
    template <> class _ToWrapper<_Type>                                                \
    {                                                                                    \
        _Type _M_data;                                                                         \
                                                                                         \
    public:                                                                              \
        template <class _U, size_t _N> constexpr operator _SimdWrapper<_U, _N>() const      \
        {                                                                                \
            static_assert(_N >= sizeof(_Type) * CHAR_BIT);                               \
            return reinterpret_cast<__vector_type_t<_U, _N>>(                            \
                __convert_mask<_SimdWrapper<_U, _N>>(_M_data));                                   \
        }                                                                                \
                                                                                         \
        template <size_t _N> constexpr operator _SimdWrapper<bool, _N>() const              \
        {                                                                                \
            static_assert(                                                               \
                std::is_same_v<_Type, typename __bool_storage_member_type<_N>::type>);   \
            return _M_data;                                                                    \
        }                                                                                \
    }
_GLIBCXX_SIMD_TO_STORAGE(__mmask8);
_GLIBCXX_SIMD_TO_STORAGE(__mmask16);
_GLIBCXX_SIMD_TO_STORAGE(__mmask32);
_GLIBCXX_SIMD_TO_STORAGE(__mmask64);
#undef _GLIBCXX_SIMD_TO_STORAGE
#endif  // _GLIBCXX_SIMD_HAVE_AVX512_ABI

// }}}

// __convert function{{{
template <class _To, class _From, class... _More>
_GLIBCXX_SIMD_INTRINSIC auto __convert(_From __v0, _More... __vs)
{
  if constexpr (__is_vectorizable_v<_From>)
    {
      static_assert((true && ... && is_same_v<_From, _More>));
      using _V = typename _VectorTraits<_To>::type;
      using _Tp = typename _VectorTraits<_To>::value_type;
      return _V{static_cast<_Tp>(__v0), static_cast<_Tp>(__vs)...};
    }
  else if constexpr (!__is_vector_type_v<_From>)
    return __convert<_To>(__as_vector(__v0), __as_vector(__vs)...);
  else
    {
      static_assert((true && ... && is_same_v<_From, _More>));
      if constexpr (__is_vectorizable_v<_To>)
	return __convert<__vector_type_t<_To, (_VectorTraits<_From>::_S_width *
					       (1 + sizeof...(_More)))>>(
	  __v0, __vs...);
      else if constexpr (!__is_vector_type_v<_To>)
	return _To(__convert<typename _To::_BuiltinType>(__v0, __vs...));
      else
	{
	  static_assert(
	    sizeof...(_More) == 0 ||
	      _VectorTraits<_To>::_S_width >=
		(1 + sizeof...(_More)) * _VectorTraits<_From>::_S_width,
	    "__convert(...) requires the input to fit into the output");
	  return __vector_convert<_To>(__v0, __vs...);
	}
    }
}

// }}}
// __convert_all{{{
// Converts __v into std::array<_To, N>, where N is _NParts if non-zero or
// otherwise deduced from _To such that N * #elements(_To) <= #elements(__v).
// Note: this function may return less than all converted elements
template <typename _To,
	  size_t _NParts = 0, // allows to convert fewer or more (only last _To,
			      // to be partially filled) than all
	  size_t _Offset = 0, // where to start, # of elements (not Bytes or
			      // Parts)
	  typename _From,
	  typename _FromVT = _VectorTraits<_From>>
_GLIBCXX_SIMD_INTRINSIC auto __convert_all(_From __v)
{
  if constexpr (std::is_arithmetic_v<_To> && _NParts != 1)
    {
      static_assert(_Offset < _FromVT::_S_width);
      constexpr auto _N = _NParts == 0 ? _FromVT::_S_partial_width - _Offset : _NParts;
      return __generate_from_n_evaluations<_N, std::array<_To, _N>>(
	[&](auto __i) { return static_cast<_To>(__v[__i + _Offset]); });
    }
  else
    {
      static_assert(__is_vector_type_v<_To>);
      using _ToVT = _VectorTraits<_To>;
      if constexpr (__is_vector_type_v<_From>)
	return __convert_all<_To, _NParts>(__as_wrapper(__v));
      else if constexpr (_NParts == 1)
	{
	  static_assert(_Offset % _ToVT::_S_width == 0);
	  return std::array<_To, 1>{__vector_convert<_To>(
	    __extract_part<_Offset / _ToVT::_S_width,
			   __div_roundup(_FromVT::_S_partial_width,
					 _ToVT::_S_width)>(__v))};
	}
#if _GLIBCXX_SIMD_X86INTRIN // {{{
      else if constexpr (!__have_sse4_1 && _Offset == 0 &&
			 is_integral_v<typename _FromVT::value_type> &&
			 sizeof(typename _FromVT::value_type) <
			   sizeof(typename _ToVT::value_type) &&
			 !(sizeof(typename _FromVT::value_type) == 4 &&
			   is_same_v<typename _ToVT::value_type, double>))
	{
	  using _ToT   = typename _ToVT::value_type;
	  using _FromT = typename _FromVT::value_type;
	  constexpr size_t _N =
	    _NParts != 0 ? _NParts
			 : (_FromVT::_S_partial_width / _ToVT::_S_width);
	  using _R = std::array<_To, _N>;
	  // __adjust modifies its input to have _N (use _SizeConstant) entries
	  // so that no unnecessary intermediate conversions are requested and,
	  // more importantly, no intermediate conversions are missing
	  [[maybe_unused]] auto __adjust =
	    [](auto __n,
	       auto __vv) -> _SimdWrapper<_FromT, decltype(__n)::value> {
	    return __vector_bitcast<_FromT, decltype(__n)::value>(__vv);
	  };
	  [[maybe_unused]] const auto __vi = __to_intrin(__v);
	  auto&& __make_array         = [](std::initializer_list<auto> __xs) {
	    return __call_with_subscripts(
	      __xs.begin(), std::make_index_sequence<_N>(),
	      [](auto... __ys) { return _R{__vector_bitcast<_ToT>(__ys)...}; });
	  };

	  if constexpr (_N == 0)
	    return _R{};
	  else if constexpr (sizeof(_FromT) == 1 && sizeof(_ToT) == 2)
	    {
	      static_assert(std::is_integral_v<_FromT>);
	      static_assert(std::is_integral_v<_ToT>);
	      if constexpr (is_unsigned_v<_FromT>)
		return __make_array({_mm_unpacklo_epi8(__vi, __m128i()),
				     _mm_unpackhi_epi8(__vi, __m128i())});
	      else
		return __make_array(
		  {_mm_srai_epi16(_mm_unpacklo_epi8(__vi, __vi), 8),
		   _mm_srai_epi16(_mm_unpackhi_epi8(__vi, __vi), 8)});
	    }
	  else if constexpr (sizeof(_FromT) == 2 && sizeof(_ToT) == 4)
	    {
	      static_assert(std::is_integral_v<_FromT>);
	      if constexpr (is_floating_point_v<_ToT>)
		{
		  const auto __ints = __convert_all<__vector_type16_t<int>, _N>(
		    __adjust(_SizeConstant<_N * 4>(), __v));
		  return __generate_from_n_evaluations<_N, _R>([&](auto __i) {
		    return __vector_convert<_To>(__ints[__i]);
		  });
		}
	      else if constexpr (is_unsigned_v<_FromT>)
		return __make_array({_mm_unpacklo_epi16(__vi, __m128i()),
				     _mm_unpackhi_epi16(__vi, __m128i())});
	      else
		return __make_array(
		  {_mm_srai_epi32(_mm_unpacklo_epi16(__vi, __vi), 16),
		   _mm_srai_epi32(_mm_unpackhi_epi16(__vi, __vi), 16)});
	    }
	  else if constexpr (sizeof(_FromT) == 4 && sizeof(_ToT) == 8 &&
			     is_integral_v<_FromT> && is_integral_v<_ToT>)
	    {
	      if constexpr (is_unsigned_v<_FromT>)
		return __make_array({_mm_unpacklo_epi32(__vi, __m128i()),
				     _mm_unpackhi_epi32(__vi, __m128i())});
	      else
		return __make_array(
		  {_mm_unpacklo_epi32(__vi, _mm_srai_epi32(__vi, 31)),
		   _mm_unpackhi_epi32(__vi, _mm_srai_epi32(__vi, 31))});
	    }
	  else if constexpr (sizeof(_FromT) == 4 && sizeof(_ToT) == 8 &&
			     is_integral_v<_FromT> && is_integral_v<_ToT>)
	    {
	      if constexpr (is_unsigned_v<_FromT>)
		return __make_array({_mm_unpacklo_epi32(__vi, __m128i()),
				     _mm_unpackhi_epi32(__vi, __m128i())});
	      else
		return __make_array(
		  {_mm_unpacklo_epi32(__vi, _mm_srai_epi32(__vi, 31)),
		   _mm_unpackhi_epi32(__vi, _mm_srai_epi32(__vi, 31))});
	    }
	  else if constexpr (sizeof(_FromT) == 1 && sizeof(_ToT) >= 4 &&
			     is_signed_v<_FromT>)
	    {
	      const __m128i __vv[2] = {_mm_unpacklo_epi8(__vi, __vi),
				       _mm_unpackhi_epi8(__vi, __vi)};
	      const __vector_type16_t<int> __vvvv[4] = {
		__vector_bitcast<int>(_mm_unpacklo_epi16(__vv[0], __vv[0])),
		__vector_bitcast<int>(_mm_unpackhi_epi16(__vv[0], __vv[0])),
		__vector_bitcast<int>(_mm_unpacklo_epi16(__vv[1], __vv[1])),
		__vector_bitcast<int>(_mm_unpackhi_epi16(__vv[1], __vv[1]))};
	      if constexpr (sizeof(_ToT) == 4)
		return __generate_from_n_evaluations<_N, _R>([&](auto __i) {
		  return __vector_convert<_To>(__vvvv[__i] >> 24);
		});
	      else if constexpr (is_integral_v<_ToT>)
		return __generate_from_n_evaluations<_N, _R>([&](auto __i) {
		  const auto __signbits = __to_intrin(__vvvv[__i / 2] >> 31);
		  const auto __sx32     = __to_intrin(__vvvv[__i / 2] >> 24);
		  return __vector_bitcast<_ToT>(
		    __i % 2 == 0 ? _mm_unpacklo_epi32(__sx32, __signbits)
				 : _mm_unpackhi_epi32(__sx32, __signbits));
		});
	      else
		return __generate_from_n_evaluations<_N, _R>([&](auto __i) {
		  const auto __int4 = __vvvv[__i / 2] >> 24;
		  return __vector_convert<_To>(
		    __i % 2 == 0
		      ? __int4
		      : __vector_bitcast<int>(_mm_unpackhi_epi64(
			  __to_intrin(__int4), __to_intrin(__int4))));
		});
	    }
	  else if constexpr (sizeof(_FromT) == 1 && sizeof(_ToT) == 4)
	    {
	      const auto __shorts = __convert_all<__vector_type16_t<
		conditional_t<is_signed_v<_FromT>, short, unsigned short>>>(
		__adjust(_SizeConstant<(_N + 1) / 2 * 8>(), __v));
	      return __generate_from_n_evaluations<_N, _R>([&](auto __i) {
		return __convert_all<_To>(__shorts[__i / 2])[__i % 2];
	      });
	    }
	  else if constexpr (sizeof(_FromT) == 2 && sizeof(_ToT) == 8 &&
			     is_signed_v<_FromT> && is_integral_v<_ToT>)
	    {
	      const __m128i __vv[2] = {_mm_unpacklo_epi16(__vi, __vi),
				       _mm_unpackhi_epi16(__vi, __vi)};
	      const __vector_type16_t<int> __vvvv[4] = {
		__vector_bitcast<int>(_mm_unpacklo_epi32(
		  _mm_srai_epi32(__vv[0], 16), _mm_srai_epi32(__vv[0], 31))),
		__vector_bitcast<int>(_mm_unpackhi_epi32(
		  _mm_srai_epi32(__vv[0], 16), _mm_srai_epi32(__vv[0], 31))),
		__vector_bitcast<int>(_mm_unpacklo_epi32(
		  _mm_srai_epi32(__vv[1], 16), _mm_srai_epi32(__vv[1], 31))),
		__vector_bitcast<int>(_mm_unpackhi_epi32(
		  _mm_srai_epi32(__vv[1], 16), _mm_srai_epi32(__vv[1], 31)))};
	      return __generate_from_n_evaluations<_N, _R>(
		[&](auto __i) { return __vector_bitcast<_ToT>(__vvvv[__i]); });
	    }
	  else if constexpr (sizeof(_FromT) <= 2 && sizeof(_ToT) == 8)
	    {
	      const auto __ints = __convert_all<__vector_type16_t<
		conditional_t<is_signed_v<_FromT> || is_floating_point_v<_ToT>,
			      int, unsigned int>>>(
		__adjust(_SizeConstant<(_N + 1) / 2 * 4>(), __v));
	      return __generate_from_n_evaluations<_N, _R>([&](auto __i) {
		return __convert_all<_To>(__ints[__i / 2])[__i % 2];
	      });
	    }
	  else
	    __assert_unreachable<_To>();
	}
#endif // _GLIBCXX_SIMD_X86INTRIN }}}
      else if constexpr ((_FromVT::_S_partial_width - _Offset) >
			 _ToVT::_S_width)
	{
	  /*
	  static_assert(
	    (_FromVT::_S_partial_width & (_FromVT::_S_partial_width - 1)) == 0,
	    "__convert_all only supports power-of-2 number of elements.
	  Otherwise " "the return type cannot be std::array<_To, N>.");
	    */
	  constexpr size_t _NTotal =
	    (_FromVT::_S_partial_width - _Offset) / _ToVT::_S_width;
	  constexpr size_t _N = _NParts == 0 ? _NTotal : _NParts;
	  static_assert(
	    _N <= _NTotal ||
	    (_N == _NTotal + 1 &&
	     (_FromVT::_S_partial_width - _Offset) % _ToVT::_S_width > 0));
	  using _R = std::array<_To, _N>;
	  if constexpr (_N == 1)
	    return _R{__vector_convert<_To>(
	      __as_vector(__extract_part<_Offset, _FromVT::_S_partial_width,
					 _ToVT::_S_width>(__v)))};
	  else
	    return __generate_from_n_evaluations<_N, _R>([&](
	      auto __i) constexpr {
	      auto __part =
		__extract_part<__i * _ToVT::_S_width + _Offset,
			       _FromVT::_S_partial_width, _ToVT::_S_width>(__v);
	      return __vector_convert<_To>(__part);
	    });
	}
      else if constexpr (_Offset == 0)
	return std::array<_To, 1>{__vector_convert<_To>(__as_vector(__v))};
      else
	return std::array<_To, 1>{__vector_convert<_To>(__as_vector(
	  __extract_part<_Offset, _FromVT::_S_partial_width,
			 _FromVT::_S_partial_width - _Offset>(__v)))};
    }
}

// }}}
// __converts_via_decomposition{{{
// This lists all cases where a __vector_convert needs to fall back to conversion of
// individual scalars (i.e. decompose the input vector into scalars, convert, compose
// output vector). In those cases, __masked_load & __masked_store prefer to use the
// __bit_iteration implementation.
template <class _From, class _To, size_t _ToSize> struct __converts_via_decomposition {
private:
    static constexpr bool _S_i_to_i = is_integral_v<_From> && is_integral_v<_To>;
    static constexpr bool _S_f_to_i = is_floating_point_v<_From> && is_integral_v<_To>;
    static constexpr bool _S_f_to_f = is_floating_point_v<_From> && is_floating_point_v<_To>;
    static constexpr bool _S_i_to_f = is_integral_v<_From> && is_floating_point_v<_To>;

    template <size_t _A, size_t _B>
    static constexpr bool _S_sizes = sizeof(_From) == _A && sizeof(_To) == _B;

public:
    static constexpr bool value =
        (_S_i_to_i && _S_sizes<8, 2> && !__have_ssse3 && _ToSize == 16) ||
        (_S_i_to_i && _S_sizes<8, 1> && !__have_avx512f && _ToSize == 16) ||
        (_S_f_to_i && _S_sizes<4, 8> && !__have_avx512dq) ||
        (_S_f_to_i && _S_sizes<8, 8> && !__have_avx512dq) ||
        (_S_f_to_i && _S_sizes<8, 4> && !__have_sse4_1 && _ToSize == 16) ||
        (_S_i_to_f && _S_sizes<8, 4> && !__have_avx512dq && _ToSize == 16) ||
        (_S_i_to_f && _S_sizes<8, 8> && !__have_avx512dq && _ToSize < 64);
};

template <class _From, class _To, size_t _ToSize>
inline constexpr bool __converts_via_decomposition_v =
    __converts_via_decomposition<_From, _To, _ToSize>::value;

// }}}
// __is_bitset {{{
template <class _Tp> struct __is_bitset : false_type {};
template <size_t _N> struct __is_bitset<std::bitset<_N>> : true_type {};
template <class _Tp> inline constexpr bool __is_bitset_v = __is_bitset<_Tp>::value;

// }}}
// __convert_mask{{{
template <class _To, class _From>
inline _To __convert_mask(_From __k)
{
  if constexpr (std::is_same_v<_To, _From>)
    { // also covers bool -> bool
      return __k;
    } else if constexpr (std::is_unsigned_v<_From> && std::is_unsigned_v<_To>) {
        // bits -> bits
        return __k;  // zero-extends or truncates
    } else if constexpr (__is_bitset_v<_From>) {
        // from std::bitset {{{
        static_assert(__k.size() <= sizeof(_ULLong) * CHAR_BIT);
        using _Tp = std::conditional_t<
            (__k.size() <= sizeof(_UShort) * CHAR_BIT),
            std::conditional_t<(__k.size() <= CHAR_BIT), _UChar, _UShort>,
            std::conditional_t<(__k.size() <= sizeof(_UInt) * CHAR_BIT), _UInt, _ULLong>>;
        return __convert_mask<_To>(static_cast<_Tp>(__k.to_ullong()));
        // }}}
    } else if constexpr (__is_bitset_v<_To>) {
        // to std::bitset {{{
        static_assert(_To().size() <= sizeof(_ULLong) * CHAR_BIT);
        using _Tp = std::conditional_t<
            (_To().size() <= sizeof(_UShort) * CHAR_BIT),
            std::conditional_t<(_To().size() <= CHAR_BIT), _UChar, _UShort>,
            std::conditional_t<(_To().size() <= sizeof(_UInt) * CHAR_BIT), _UInt, _ULLong>>;
        return __convert_mask<_Tp>(__k);
        // }}}
    } else if constexpr (__is_simd_wrapper_v<_From>) {
        return __convert_mask<_To>(__k._M_data);
    } else if constexpr (__is_simd_wrapper_v<_To>) {
        return __convert_mask<typename _To::_BuiltinType>(__k);
    } else if constexpr (std::is_unsigned_v<_From> && __is_vector_type_v<_To>) {
        // bits -> vector {{{
        using _Trait = _VectorTraits<_To>;
        constexpr size_t _N_in = sizeof(_From) * CHAR_BIT;
        using _ToT = typename _Trait::value_type;
        constexpr size_t _N_out = _Trait::_S_width;
        constexpr size_t _N = std::min(_N_in, _N_out);
        constexpr size_t __bytes_per_output_element = sizeof(_ToT);
#if _GLIBCXX_SIMD_X86INTRIN // {{{
        if constexpr (__have_avx512f) {
            if constexpr (__bytes_per_output_element == 1 && sizeof(_To) <= 16) {
                if constexpr (__have_avx512bw_vl) {
                    return __intrin_bitcast<_To>(_mm_movm_epi8(__k));
                } else if constexpr (__have_avx512bw) {
                    return __intrin_bitcast<_To>(__lo128(_mm512_movm_epi8(__k)));
                } else {
                    auto __as32bits = _mm512_maskz_mov_epi32(__k, ~__m512i());
                    auto __as16bits = __xzyw(
                        _mm256_packs_epi32(__lo256(__as32bits), __hi256(__as32bits)));
                    return __intrin_bitcast<_To>(
                        _mm_packs_epi16(__lo128(__as16bits), __hi128(__as16bits)));
                }
            } else if constexpr (__bytes_per_output_element == 1 && sizeof(_To) == 32) {
                if constexpr (__have_avx512bw_vl) {
                    return __vector_bitcast<_ToT>(_mm256_movm_epi8(__k));
                } else if constexpr (__have_avx512bw) {
                    return __vector_bitcast<_ToT>(__lo256(_mm512_movm_epi8(__k)));
                } else {
                    auto __as16bits =  // 0 16 1 17 ... 15 31
                        _mm512_srli_epi32(_mm512_maskz_mov_epi32(__k, ~__m512i()), 16) |
                        _mm512_slli_epi32(_mm512_maskz_mov_epi32(__k >> 16, ~__m512i()),
                                          16);
                    auto __0_16_1_17 = __xzyw(_mm256_packs_epi16(
                        __lo256(__as16bits),
                        __hi256(__as16bits))  // 0 16 1 17 2 18 3 19 8 24 9 25 ...
                    );
                    // deinterleave:
                    return __vector_bitcast<_ToT>(__xzyw(_mm256_shuffle_epi8(
                        __0_16_1_17,  // 0 16 1 17 2 ...
                        _mm256_setr_epi8(0, 2, 4, 6, 8, 10, 12, 14, 1, 3, 5, 7, 9, 11, 13,
                                         15, 0, 2, 4, 6, 8, 10, 12, 14, 1, 3, 5, 7, 9, 11,
                                         13, 15))));  // 0-7 16-23 8-15 24-31 -> xzyw
                                                      // 0-3  8-11 16-19 24-27
                                                      // 4-7 12-15 20-23 28-31
                }
            } else if constexpr (__bytes_per_output_element == 1 && sizeof(_To) == 64) {
                return reinterpret_cast<__vector_type_t<_SChar, 64>>(_mm512_movm_epi8(__k));
            } else if constexpr (__bytes_per_output_element == 2 && sizeof(_To) <= 16) {
                if constexpr (__have_avx512bw_vl) {
                    return __intrin_bitcast<_To>(_mm_movm_epi16(__k));
                } else if constexpr (__have_avx512bw) {
                    return __intrin_bitcast<_To>(__lo128(_mm512_movm_epi16(__k)));
                } else {
                    __m256i __as32bits;
                    if constexpr (__have_avx512vl) {
                        __as32bits = _mm256_maskz_mov_epi32(__k, ~__m256i());
                    } else {
                        __as32bits = __lo256(_mm512_maskz_mov_epi32(__k, ~__m512i()));
                    }
                    return __intrin_bitcast<_To>(
                        _mm_packs_epi32(__lo128(__as32bits), __hi128(__as32bits)));
                }
            } else if constexpr (__bytes_per_output_element == 2 && sizeof(_To) == 32) {
                if constexpr (__have_avx512bw_vl) {
                    return __vector_bitcast<_ToT>(_mm256_movm_epi16(__k));
                } else if constexpr (__have_avx512bw) {
                    return __vector_bitcast<_ToT>(__lo256(_mm512_movm_epi16(__k)));
                } else {
                    auto __as32bits = _mm512_maskz_mov_epi32(__k, ~__m512i());
                    return __vector_bitcast<_ToT>(__xzyw(
                        _mm256_packs_epi32(__lo256(__as32bits), __hi256(__as32bits))));
                }
            } else if constexpr (__bytes_per_output_element == 2 && sizeof(_To) == 64) {
                return __vector_bitcast<_ToT>(_mm512_movm_epi16(__k));
            } else if constexpr (__bytes_per_output_element == 4 && sizeof(_To) <= 16) {
                return __intrin_bitcast<_To>(
                    __have_avx512dq_vl
                        ? _mm_movm_epi32(__k)
                        : __have_avx512dq
                              ? __lo128(_mm512_movm_epi32(__k))
                              : __have_avx512vl
                                    ? _mm_maskz_mov_epi32(__k, ~__m128i())
                                    : __lo128(_mm512_maskz_mov_epi32(__k, ~__m512i())));
            } else if constexpr (__bytes_per_output_element == 4 && sizeof(_To) == 32) {
                return __vector_bitcast<_ToT>(
                    __have_avx512dq_vl
                        ? _mm256_movm_epi32(__k)
                        : __have_avx512dq
                              ? __lo256(_mm512_movm_epi32(__k))
                              : __have_avx512vl
                                    ? _mm256_maskz_mov_epi32(__k, ~__m256i())
                                    : __lo256(_mm512_maskz_mov_epi32(__k, ~__m512i())));
            } else if constexpr (__bytes_per_output_element == 4 && sizeof(_To) == 64) {
                return __vector_bitcast<_ToT>(__have_avx512dq
                                             ? _mm512_movm_epi32(__k)
                                             : _mm512_maskz_mov_epi32(__k, ~__m512i()));
            } else if constexpr (__bytes_per_output_element == 8 && sizeof(_To) == 16) {
                return __vector_bitcast<_ToT>(
                    __have_avx512dq_vl
                        ? _mm_movm_epi64(__k)
                        : __have_avx512dq
                              ? __lo128(_mm512_movm_epi64(__k))
                              : __have_avx512vl
                                    ? _mm_maskz_mov_epi64(__k, ~__m128i())
                                    : __lo128(_mm512_maskz_mov_epi64(__k, ~__m512i())));
            } else if constexpr (__bytes_per_output_element == 8 && sizeof(_To) == 32) {
                return __vector_bitcast<_ToT>(
                    __have_avx512dq_vl
                        ? _mm256_movm_epi64(__k)
                        : __have_avx512dq
                              ? __lo256(_mm512_movm_epi64(__k))
                              : __have_avx512vl
                                    ? _mm256_maskz_mov_epi64(__k, ~__m256i())
                                    : __lo256(_mm512_maskz_mov_epi64(__k, ~__m512i())));
            } else if constexpr (__bytes_per_output_element == 8 && sizeof(_To) == 64) {
                return __vector_bitcast<_ToT>(__have_avx512dq
                                             ? _mm512_movm_epi64(__k)
                                             : _mm512_maskz_mov_epi64(__k, ~__m512i()));
            } else {
                __assert_unreachable<_To>();
            }
        } else if constexpr (__have_sse) {
            using _U = std::make_unsigned_t<__int_for_sizeof_t<_ToT>>;
            using _V = __vector_type_t<_U, _N>;  // simd<_U, _Abi>;
            static_assert(sizeof(_V) <= 32);  // can't be AVX512
            constexpr size_t __bits_per_element = sizeof(_U) * CHAR_BIT;
            if constexpr (!__have_avx2 && __have_avx && sizeof(_V) == 32) {
                if constexpr (_N == 8) {
                    return _mm256_cmp_ps(
                        _mm256_and_ps(
                            _mm256_castsi256_ps(_mm256_set1_epi32(__k)),
                            _mm256_castsi256_ps(_mm256_setr_epi32(
                                0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80))),
                        _mm256_setzero_ps(), _CMP_NEQ_UQ);
                } else if constexpr (_N == 4) {
                    return _mm256_cmp_pd(
                        _mm256_and_pd(
                            _mm256_castsi256_pd(_mm256_set1_epi64x(__k)),
                            _mm256_castsi256_pd(
                                _mm256_setr_epi64x(0x01, 0x02, 0x04, 0x08))),
                        _mm256_setzero_pd(), _CMP_NEQ_UQ);
                } else {
                    __assert_unreachable<_To>();
                }
            } else if constexpr (__bits_per_element >= _N)
	      {
		constexpr auto __bitmask =
		  __generate_vector<__vector_type_t<_U, _N_out>>(
		    [](auto __i) constexpr->_U {
		      return __i < _N ? 1ull << __i : 0;
		    });
		return __vector_bitcast<_ToT>(
		  (__vector_broadcast<_N_out, _U>(__k) & __bitmask) != 0);
	      }
	    else if constexpr (sizeof(_V) == 16 && sizeof(_ToT) == 1 && __have_ssse3) {
                const auto __bitmask = __to_intrin(__make_vector<_UChar>(
                    1, 2, 4, 8, 16, 32, 64, 128, 1, 2, 4, 8, 16, 32, 64, 128));
                return __vector_bitcast<_ToT>(
                    __vector_bitcast<_ToT>(
                        _mm_shuffle_epi8(
                            __to_intrin(__vector_type_t<_ULLong, 2>{__k}),
                            _mm_setr_epi8(0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1,
                                          1)) &
                        __bitmask) != 0);
            } else if constexpr (sizeof(_V) == 32 && sizeof(_ToT) == 1 && __have_avx2) {
                const auto __bitmask =
                    _mm256_broadcastsi128_si256(__to_intrin(__make_vector<_UChar>(
                        1, 2, 4, 8, 16, 32, 64, 128, 1, 2, 4, 8, 16, 32, 64, 128)));
                return __vector_bitcast<_ToT>(
                    __vector_bitcast<_ToT>(_mm256_shuffle_epi8(
                                        _mm256_broadcastsi128_si256(__to_intrin(
                                            __vector_type_t<_ULLong, 2>{__k})),
                                        _mm256_setr_epi8(0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1,
                                                         1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2,
                                                         2, 2, 3, 3, 3, 3, 3, 3, 3, 3)) &
                                    __bitmask) != 0);
                /* TODO:
                } else if constexpr (sizeof(_V) == 32 && sizeof(_ToT) == 2 && __have_avx2) {
                    constexpr auto __bitmask = _mm256_broadcastsi128_si256(
                        _mm_setr_epi8(0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80,
                0x100, 0x200, 0x400, 0x800, 0x1000, 0x2000, 0x4000, 0x8000)); return
                __vector_bitcast<_ToT>( _mm256_shuffle_epi8(
                                   _mm256_broadcastsi128_si256(__m128i{__k}),
                                   _mm_setr_epi8(0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1,
                1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3)) & __bitmask) != 0;
                */
            } else {
                const _V __tmp = __generate_vector<_V>([&](auto __i) constexpr {
                                  return static_cast<_U>(
                                      __k >> (__bits_per_element * (__i / __bits_per_element)));
                              }) &
                              __generate_vector<_V>([](auto __i) constexpr {
                                  return static_cast<_U>(1ull << (__i % __bits_per_element));
                              });  // mask bit index
                return __vector_bitcast<_ToT>(__tmp != _V());
            }
        } else
#endif // _GLIBCXX_SIMD_X86INTRIN }}}
	  {
	    using _I = __int_for_sizeof_t<_ToT>;
	    return reinterpret_cast<_To>(
	      __generate_vector<__vector_type_t<_I, _N_out>>([&](auto __i) constexpr {
		return ((__k >> __i) & 1) == 0 ? _I() : ~_I();
	      }));
	  }
	// }}}
    } else if constexpr (__is_vector_type_v<_From> && std::is_unsigned_v<_To>) {
        // vector -> bits {{{
#if _GLIBCXX_SIMD_X86INTRIN // {{{
        using _Trait = _VectorTraits<_From>;
        using _Tp = typename _Trait::value_type;
        constexpr size_t _FromN = sizeof(_From) < 16 ? 16 / sizeof(_Tp) : _Trait::_S_width;
        constexpr size_t cvt_id = _FromN * 10 + sizeof(_Tp);
        constexpr bool __have_avx512_int = __have_avx512f && std::is_integral_v<_Tp>;
        [[maybe_unused]]  // PR85827
        const auto __intrin = __to_intrin(__k);

             if constexpr (cvt_id == 16'1 && __have_avx512bw_vl) { return    _mm_movepi8_mask(__intrin); }
        else if constexpr (cvt_id == 16'1 && __have_avx512bw   ) { return _mm512_movepi8_mask(__zero_extend(__intrin)); }
        else if constexpr (cvt_id == 16'1                      ) { return    _mm_movemask_epi8(__intrin); }
        else if constexpr (cvt_id == 32'1 && __have_avx512bw_vl) { return _mm256_movepi8_mask(__intrin); }
        else if constexpr (cvt_id == 32'1 && __have_avx512bw   ) { return _mm512_movepi8_mask(__zero_extend(__intrin)); }
        else if constexpr (cvt_id == 32'1                      ) { return _mm256_movemask_epi8(__intrin); }
        else if constexpr (cvt_id == 64'1 && __have_avx512bw   ) { return _mm512_movepi8_mask(__intrin); }
        else if constexpr (cvt_id ==  8'2 && __have_avx512bw_vl) { return    _mm_movepi16_mask(__intrin); }
        else if constexpr (cvt_id ==  8'2 && __have_avx512bw   ) { return _mm512_movepi16_mask(__zero_extend(__intrin)); }
        else if constexpr (cvt_id ==  8'2                      ) { return movemask_epi16(__intrin); }
        else if constexpr (cvt_id == 16'2 && __have_avx512bw_vl) { return _mm256_movepi16_mask(__intrin); }
        else if constexpr (cvt_id == 16'2 && __have_avx512bw   ) { return _mm512_movepi16_mask(__zero_extend(__intrin)); }
        else if constexpr (cvt_id == 16'2                      ) { return movemask_epi16(__intrin); }
        else if constexpr (cvt_id == 32'2 && __have_avx512bw   ) { return _mm512_movepi16_mask(__intrin); }
        else if constexpr (cvt_id ==  4'4 && __have_avx512dq_vl) { return    _mm_movepi32_mask(__intrin_bitcast<__m128i>(__k)); }
        else if constexpr (cvt_id ==  4'4 && __have_avx512dq   ) { return _mm512_movepi32_mask(__zero_extend(__intrin_bitcast<__m128i>(__k))); }
        else if constexpr (cvt_id ==  4'4 && __have_avx512vl   ) { return    _mm_cmp_epi32_mask(__intrin_bitcast<__m128i>(__k), __m128i(), _MM_CMPINT_LT); }
        else if constexpr (cvt_id ==  4'4 && __have_avx512_int ) { return _mm512_cmp_epi32_mask(__zero_extend(__intrin), __m512i(), _MM_CMPINT_LT); }
        else if constexpr (cvt_id ==  4'4                      ) { return    _mm_movemask_ps(__intrin); }
        else if constexpr (cvt_id ==  8'4 && __have_avx512dq_vl) { return _mm256_movepi32_mask(__vector_bitcast<_LLong>(__k)); }
        else if constexpr (cvt_id ==  8'4 && __have_avx512dq   ) { return _mm512_movepi32_mask(__zero_extend(__vector_bitcast<_LLong>(__k))); }
        else if constexpr (cvt_id ==  8'4 && __have_avx512vl   ) { return _mm256_cmp_epi32_mask(__vector_bitcast<_LLong>(__k), __m256i(), _MM_CMPINT_LT); }
        else if constexpr (cvt_id ==  8'4 && __have_avx512_int ) { return _mm512_cmp_epi32_mask(__zero_extend(__intrin), __m512i(), _MM_CMPINT_LT); }
        else if constexpr (cvt_id ==  8'4                      ) { return _mm256_movemask_ps(__intrin); }
        else if constexpr (cvt_id == 16'4 && __have_avx512dq   ) { return _mm512_movepi32_mask(__vector_bitcast<_LLong>(__k)); }
        else if constexpr (cvt_id == 16'4                      ) { return _mm512_cmp_epi32_mask(__vector_bitcast<_LLong>(__k), __m512i(), _MM_CMPINT_LT); }
        else if constexpr (cvt_id ==  2'8 && __have_avx512dq_vl) { return    _mm_movepi64_mask(__intrin_bitcast<__m128i>(__k)); }
        else if constexpr (cvt_id ==  2'8 && __have_avx512dq   ) { return _mm512_movepi64_mask(__zero_extend(__intrin_bitcast<__m128i>(__k))); }
        else if constexpr (cvt_id ==  2'8 && __have_avx512vl   ) { return    _mm_cmp_epi64_mask(__intrin_bitcast<__m128i>(__k), __m128i(), _MM_CMPINT_LT); }
        else if constexpr (cvt_id ==  2'8 && __have_avx512_int ) { return _mm512_cmp_epi64_mask(__zero_extend(__intrin), __m512i(), _MM_CMPINT_LT); }
        else if constexpr (cvt_id ==  2'8                      ) { return    _mm_movemask_pd(__intrin); }
        else if constexpr (cvt_id ==  4'8 && __have_avx512dq_vl) { return _mm256_movepi64_mask(__vector_bitcast<_LLong>(__k)); }
        else if constexpr (cvt_id ==  4'8 && __have_avx512dq   ) { return _mm512_movepi64_mask(__zero_extend(__vector_bitcast<_LLong>(__k))); }
        else if constexpr (cvt_id ==  4'8 && __have_avx512vl   ) { return _mm256_cmp_epi64_mask(__vector_bitcast<_LLong>(__k), __m256i(), _MM_CMPINT_LT); }
        else if constexpr (cvt_id ==  4'8 && __have_avx512_int ) { return _mm512_cmp_epi64_mask(__zero_extend(__intrin), __m512i(), _MM_CMPINT_LT); }
        else if constexpr (cvt_id ==  4'8                      ) { return _mm256_movemask_pd(__intrin); }
        else if constexpr (cvt_id ==  8'8 && __have_avx512dq   ) { return _mm512_movepi64_mask(__vector_bitcast<_LLong>(__k)); }
        else if constexpr (cvt_id ==  8'8                      ) { return _mm512_cmp_epi64_mask(__vector_bitcast<_LLong>(__k), __m512i(), _MM_CMPINT_LT); }
        else
#endif // _GLIBCXX_SIMD_X86INTRIN }}}
        __assert_unreachable<_To>();
        // }}}
    } else if constexpr (__is_vector_type_v<_From> && __is_vector_type_v<_To>) {
        // vector -> vector {{{
        using _ToTrait = _VectorTraits<_To>;
        using _FromTrait = _VectorTraits<_From>;
        using _ToT = typename _ToTrait::value_type;
        using _Tp = typename _FromTrait::value_type;
        [[maybe_unused]] constexpr size_t _FromN = _FromTrait::_S_width;
        constexpr size_t _ToN = _ToTrait::_S_width;
        constexpr int _FromBytes = sizeof(_Tp);
        constexpr int _ToBytes = sizeof(_ToT);

	if constexpr (_FromBytes == _ToBytes)
	  return __intrin_bitcast<_To>(__k);
#if _GLIBCXX_SIMD_X86INTRIN // {{{
        else if constexpr (sizeof(_To) == 16 && sizeof(__k) == 16)
	{ // SSE -> SSE {{{
            if constexpr (_FromBytes == 4 && _ToBytes == 8) {
                if constexpr(std::is_integral_v<_Tp>) {
                    return __vector_bitcast<_ToT>(__interleave128_lo(__k, __k));
                } else {
                    return __vector_bitcast<_ToT>(__interleave128_lo(__k, __k));
                }
            } else if constexpr (_FromBytes == 2 && _ToBytes == 8) {
                const auto __y = __vector_bitcast<int>(__interleave128_lo(__k, __k));
                return __vector_bitcast<_ToT>(__interleave128_lo(__y, __y));
            } else if constexpr (_FromBytes == 1 && _ToBytes == 8) {
                auto __y = __vector_bitcast<short>(__interleave128_lo(__k, __k));
                auto __z = __vector_bitcast<int>(__interleave128_lo(__y, __y));
                return __vector_bitcast<_ToT>(__interleave128_lo(__z, __z));
            } else if constexpr (_FromBytes == 8 && _ToBytes == 4) {
		if constexpr (__have_sse2)
		  return __vector_bitcast<_ToT>(
		    _mm_packs_epi32(__vector_bitcast<_LLong>(__k), __m128i()));
		else
		  return __vector_shuffle<1, 3, 6, 7>(
		    __vector_bitcast<_ToT>(__k), _To());
	    } else if constexpr (_FromBytes == 2 && _ToBytes == 4) {
                return __vector_bitcast<_ToT>(__interleave128_lo(__k, __k));
            } else if constexpr (_FromBytes == 1 && _ToBytes == 4) {
                const auto __y = __vector_bitcast<short>(__interleave128_lo(__k, __k));
                return __vector_bitcast<_ToT>(__interleave128_lo(__y, __y));
            } else if constexpr (_FromBytes == 8 && _ToBytes == 2) {
		if constexpr (__have_sse2 && !__have_ssse3)
		  return __vector_bitcast<_ToT>(_mm_packs_epi32(
		    _mm_packs_epi32(__vector_bitcast<_LLong>(__k), __m128i()),
		    __m128i()));
		else
		  return __vector_permute<3, 7, -1, -1, -1, -1, -1, -1>(
		    __vector_bitcast<_ToT>(__k));
	    } else if constexpr (_FromBytes == 4 && _ToBytes == 2) {
                return __vector_bitcast<_ToT>(
                    _mm_packs_epi32(__vector_bitcast<_LLong>(__k), __m128i()));
            } else if constexpr (_FromBytes == 1 && _ToBytes == 2) {
                return __vector_bitcast<_ToT>(__interleave128_lo(__k, __k));
            } else if constexpr (_FromBytes == 8 && _ToBytes == 1) {
                if constexpr(__have_ssse3) {
                    return __vector_bitcast<_ToT>(
                        _mm_shuffle_epi8(__vector_bitcast<_LLong>(__k),
                                         _mm_setr_epi8(7, 15, -1, -1, -1, -1, -1, -1, -1,
                                                       -1, -1, -1, -1, -1, -1, -1)));
                } else {
                    auto __y = _mm_packs_epi32(__vector_bitcast<_LLong>(__k), __m128i());
                    __y = _mm_packs_epi32(__y, __m128i());
                    return __vector_bitcast<_ToT>(_mm_packs_epi16(__y, __m128i()));
                }
		return __vector_permute<7, 15, -1, -1, -1, -1, -1, -1, -1, -1,
					-1, -1, -1, -1, -1, -1>(
		  __vector_bitcast<_ToT>(__k));
	    } else if constexpr (_FromBytes == 4 && _ToBytes == 1) {
                if constexpr(__have_ssse3) {
                    return __vector_bitcast<_ToT>(
                        _mm_shuffle_epi8(__vector_bitcast<_LLong>(__k),
                                         _mm_setr_epi8(3, 7, 11, 15, -1, -1, -1, -1, -1,
                                                       -1, -1, -1, -1, -1, -1, -1)));
                } else {
                    const auto __y = _mm_packs_epi32(__vector_bitcast<_LLong>(__k), __m128i());
                    return __vector_bitcast<_ToT>(_mm_packs_epi16(__y, __m128i()));
                }
		return __vector_permute<3, 7, 11, 15, -1, -1, -1, -1, -1, -1,
					-1, -1, -1, -1, -1, -1>(
		  __vector_bitcast<_ToT>(__k));
	    } else if constexpr (_FromBytes == 2 && _ToBytes == 1) {
                return __vector_bitcast<_ToT>(_mm_packs_epi16(__vector_bitcast<_LLong>(__k), __m128i()));
	    } else {
                static_assert(!std::is_same_v<_Tp, _Tp>, "should be unreachable");
            }
	  } // }}}
	else if constexpr (sizeof(_To) == 32 && sizeof(__k) == 32)
	  { // AVX -> AVX {{{
            if constexpr (_FromBytes == _ToBytes) {  // keep low 1/2
                __assert_unreachable<_Tp>();
            } else if constexpr (_FromBytes == _ToBytes * 2) {
                const auto __y = __vector_bitcast<_LLong>(__k);
                return __vector_bitcast<_ToT>(
                    _mm256_castsi128_si256(_mm_packs_epi16(__lo128(__y), __hi128(__y))));
            } else if constexpr (_FromBytes == _ToBytes * 4) {
                const auto __y = __vector_bitcast<_LLong>(__k);
                return __vector_bitcast<_ToT>(_mm256_castsi128_si256(
                    _mm_packs_epi16(_mm_packs_epi16(__lo128(__y), __hi128(__y)), __m128i())));
            } else if constexpr (_FromBytes == _ToBytes * 8) {
                const auto __y = __vector_bitcast<_LLong>(__k);
                return __vector_bitcast<_ToT>(_mm256_castsi128_si256(
                    _mm_shuffle_epi8(_mm_packs_epi16(__lo128(__y), __hi128(__y)),
                                     _mm_setr_epi8(3, 7, 11, 15, -1, -1, -1, -1, -1, -1,
                                                   -1, -1, -1, -1, -1, -1))));
            } else if constexpr (_FromBytes * 2 == _ToBytes) {
                auto __y = __xzyw(__to_intrin(__k));
                if constexpr(std::is_floating_point_v<_Tp>) {
                    return __vector_bitcast<_ToT>(_mm256_unpacklo_ps(__y, __y));
                } else {
                    return __vector_bitcast<_ToT>(_mm256_unpacklo_epi8(__y, __y));
                }
            } else if constexpr (_FromBytes * 4 == _ToBytes) {
                auto __y = _mm_unpacklo_epi8(__lo128(__vector_bitcast<_LLong>(__k)),
                                           __lo128(__vector_bitcast<_LLong>(__k)));  // drops 3/4 of input
                return __vector_bitcast<_ToT>(
                    __concat(_mm_unpacklo_epi16(__y, __y), _mm_unpackhi_epi16(__y, __y)));
            } else if constexpr (_FromBytes == 1 && _ToBytes == 8) {
                auto __y = _mm_unpacklo_epi8(__lo128(__vector_bitcast<_LLong>(__k)),
                                           __lo128(__vector_bitcast<_LLong>(__k)));  // drops 3/4 of input
                __y = _mm_unpacklo_epi16(__y, __y);  // drops another 1/2 => 7/8 total
                return __vector_bitcast<_ToT>(
                    __concat(_mm_unpacklo_epi32(__y, __y), _mm_unpackhi_epi32(__y, __y)));
            } else {
                __assert_unreachable<_Tp>();
            }
	  } // }}}
	else if constexpr (sizeof(_To) == 32 && sizeof(__k) == 16)
	  { // SSE -> AVX {{{
            if constexpr (_FromBytes == _ToBytes) {
                return __vector_bitcast<_ToT>(
                    __intrinsic_type_t<_Tp, 32 / sizeof(_Tp)>(__zero_extend(__to_intrin(__k))));
            } else if constexpr (_FromBytes * 2 == _ToBytes) {  // keep all
                return __vector_bitcast<_ToT>(__concat(_mm_unpacklo_epi8(__vector_bitcast<_LLong>(__k), __vector_bitcast<_LLong>(__k)),
                                         _mm_unpackhi_epi8(__vector_bitcast<_LLong>(__k), __vector_bitcast<_LLong>(__k))));
            } else if constexpr (_FromBytes * 4 == _ToBytes) {
                if constexpr (__have_avx2) {
                    return __vector_bitcast<_ToT>(_mm256_shuffle_epi8(
                        __concat(__vector_bitcast<_LLong>(__k), __vector_bitcast<_LLong>(__k)),
                        _mm256_setr_epi8(0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3,
                                         4, 4, 4, 4, 5, 5, 5, 5, 6, 6, 6, 6, 7, 7, 7,
                                         7)));
                } else {
                    return __vector_bitcast<_ToT>(
                        __concat(_mm_shuffle_epi8(__vector_bitcast<_LLong>(__k),
                                                _mm_setr_epi8(0, 0, 0, 0, 1, 1, 1, 1, 2,
                                                              2, 2, 2, 3, 3, 3, 3)),
                               _mm_shuffle_epi8(__vector_bitcast<_LLong>(__k),
                                                _mm_setr_epi8(4, 4, 4, 4, 5, 5, 5, 5, 6,
                                                              6, 6, 6, 7, 7, 7, 7))));
                }
            } else if constexpr (_FromBytes * 8 == _ToBytes) {
                if constexpr (__have_avx2) {
                    return __vector_bitcast<_ToT>(_mm256_shuffle_epi8(
                        __concat(__vector_bitcast<_LLong>(__k), __vector_bitcast<_LLong>(__k)),
                        _mm256_setr_epi8(0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1,
                                         2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3,
                                         3)));
                } else {
                    return __vector_bitcast<_ToT>(
                        __concat(_mm_shuffle_epi8(__vector_bitcast<_LLong>(__k),
                                                _mm_setr_epi8(0, 0, 0, 0, 0, 0, 0, 0, 1,
                                                              1, 1, 1, 1, 1, 1, 1)),
                               _mm_shuffle_epi8(__vector_bitcast<_LLong>(__k),
                                                _mm_setr_epi8(2, 2, 2, 2, 2, 2, 2, 2, 3,
                                                              3, 3, 3, 3, 3, 3, 3))));
                }
            } else if constexpr (_FromBytes == _ToBytes * 2) {
                return __vector_bitcast<_ToT>(
                    __m256i(__zero_extend(_mm_packs_epi16(__vector_bitcast<_LLong>(__k), __m128i()))));
            } else if constexpr (_FromBytes == 8 && _ToBytes == 2) {
                return __vector_bitcast<_ToT>(__m256i(__zero_extend(
                    _mm_shuffle_epi8(__vector_bitcast<_LLong>(__k),
                                     _mm_setr_epi8(6, 7, 14, 15, -1, -1, -1, -1, -1, -1,
                                                   -1, -1, -1, -1, -1, -1)))));
            } else if constexpr (_FromBytes == 4 && _ToBytes == 1) {
                return __vector_bitcast<_ToT>(__m256i(__zero_extend(
                    _mm_shuffle_epi8(__vector_bitcast<_LLong>(__k),
                                     _mm_setr_epi8(3, 7, 11, 15, -1, -1, -1, -1, -1, -1,
                                                   -1, -1, -1, -1, -1, -1)))));
            } else if constexpr (_FromBytes == 8 && _ToBytes == 1) {
                return __vector_bitcast<_ToT>(__m256i(__zero_extend(
                    _mm_shuffle_epi8(__vector_bitcast<_LLong>(__k),
                                     _mm_setr_epi8(7, 15, -1, -1, -1, -1, -1, -1, -1, -1,
                                                   -1, -1, -1, -1, -1, -1)))));
            } else {
                static_assert(!std::is_same_v<_Tp, _Tp>, "should be unreachable");
            }
	  } // }}}
	else if constexpr (sizeof(_To) == 16 && sizeof(__k) == 32)
	  { // AVX -> SSE {{{
            if constexpr (_FromBytes == _ToBytes) {  // keep low 1/2
                return __vector_bitcast<_ToT>(__lo128(__k));
            } else if constexpr (_FromBytes == _ToBytes * 2) {  // keep all
                auto __y = __vector_bitcast<_LLong>(__k);
                return __vector_bitcast<_ToT>(_mm_packs_epi16(__lo128(__y), __hi128(__y)));
            } else if constexpr (_FromBytes == _ToBytes * 4) {  // add 1/2 undef
                auto __y = __vector_bitcast<_LLong>(__k);
                return __vector_bitcast<_ToT>(
                    _mm_packs_epi16(_mm_packs_epi16(__lo128(__y), __hi128(__y)), __m128i()));
            } else if constexpr (_FromBytes == 8 && _ToBytes == 1) {  // add 3/4 undef
                auto __y = __vector_bitcast<_LLong>(__k);
                return __vector_bitcast<_ToT>(
                    _mm_shuffle_epi8(_mm_packs_epi16(__lo128(__y), __hi128(__y)),
                                     _mm_setr_epi8(3, 7, 11, 15, -1, -1, -1, -1, -1, -1,
                                                   -1, -1, -1, -1, -1, -1)));
            } else if constexpr (_FromBytes * 2 == _ToBytes) {  // keep low 1/4
                auto __y = __lo128(__vector_bitcast<_LLong>(__k));
                return __vector_bitcast<_ToT>(_mm_unpacklo_epi8(__y, __y));
            } else if constexpr (_FromBytes * 4 == _ToBytes) {  // keep low 1/8
                auto __y = __lo128(__vector_bitcast<_LLong>(__k));
                __y = _mm_unpacklo_epi8(__y, __y);
                return __vector_bitcast<_ToT>(_mm_unpacklo_epi8(__y, __y));
            } else if constexpr (_FromBytes * 8 == _ToBytes) {  // keep low 1/16
                auto __y = __lo128(__vector_bitcast<_LLong>(__k));
                __y = _mm_unpacklo_epi8(__y, __y);
                __y = _mm_unpacklo_epi8(__y, __y);
                return __vector_bitcast<_ToT>(_mm_unpacklo_epi8(__y, __y));
            } else {
                static_assert(!std::is_same_v<_Tp, _Tp>, "should be unreachable");
            }
	  } // }}}
#endif // _GLIBCXX_SIMD_X86INTRIN }}}
	else
	  {
	    using _I = __int_for_sizeof_t<_ToT>;
	    return reinterpret_cast<_To>(
	      __generate_vector<__vector_type_t<_I, _ToN>>([&](
		auto __i) constexpr {
		if constexpr (__i >= _FromN)
		  return _I();
		else
		  return __k[int(__i)] == 0 ? _I() : ~_I();
	      }));
	  }
	/*
        } else if constexpr (_FromBytes > _ToBytes) {
	    const _To     __y      = __vector_bitcast<_ToT>(__k);
	    return [&] <std::size_t... _Is> (std::index_sequence<_Is...>) {
	      constexpr int _Stride = _FromBytes / _ToBytes;
	      return _To{__y[(_Is + 1) * _Stride - 1]...};
	    }(std::make_index_sequence<std::min(_ToN, _FromN)>());
	} else {
	    // {0, 0, 1, 1} (_Dups = 2, _Is<4>)
	    // {0, 0, 0, 0, 1, 1, 1, 1} (_Dups = 4, _Is<8>)
	    // {0, 0, 1, 1, 2, 2, 3, 3} (_Dups = 2, _Is<8>)
	    // ...
	    return [&] <std::size_t... _Is> (std::index_sequence<_Is...>) {
	      constexpr int __dup = _ToBytes / _FromBytes;
	      return __vector_bitcast<_ToT>(_From{__k[_Is / __dup]...});
	    }(std::make_index_sequence<_FromN>());
	}
	*/
        // }}}
    } else {
        __assert_unreachable<_To>();
    }
}

// }}}

// ISA & type detection {{{1
template <class _Tp, size_t _N>
constexpr bool __is_sse_ps()
{
  return __have_sse && std::is_same_v<_Tp, float> &&
	 sizeof(__intrinsic_type_t<_Tp, _N>) == 16;
}
template <class _Tp, size_t _N>
constexpr bool __is_sse_pd()
{
  return __have_sse2 && std::is_same_v<_Tp, double> &&
	 sizeof(__intrinsic_type_t<_Tp, _N>) == 16;
}
template <class _Tp, size_t _N>
constexpr bool __is_avx_ps()
{
  return __have_avx && std::is_same_v<_Tp, float> &&
	 sizeof(__intrinsic_type_t<_Tp, _N>) == 32;
}
template <class _Tp, size_t _N>
constexpr bool __is_avx_pd()
{
  return __have_avx && std::is_same_v<_Tp, double> &&
	 sizeof(__intrinsic_type_t<_Tp, _N>) == 32;
}
template <class _Tp, size_t _N>
constexpr bool __is_avx512_ps()
{
  return __have_avx512f && std::is_same_v<_Tp, float> &&
	 sizeof(__intrinsic_type_t<_Tp, _N>) == 64;
}
template <class _Tp, size_t _N>
constexpr bool __is_avx512_pd()
{
  return __have_avx512f && std::is_same_v<_Tp, double> &&
	 sizeof(__intrinsic_type_t<_Tp, _N>) == 64;
}

template <class _Tp, size_t _N> constexpr bool __is_neon_ps()
{
    constexpr auto _Bytes = sizeof(__vector_type_t<_Tp, _N>);
    return __have_neon && std::is_same_v<_Tp, float> && (_Bytes == 16 || _Bytes == 8);
}
template <class _Tp, size_t _N> constexpr bool __is_neon_pd()
{
    return __have_neon && std::is_same_v<_Tp, double> && sizeof(__vector_type_t<_Tp, _N>) == 16;
}

// _SimdImplBuiltin {{{1
template <typename _Abi>
struct _SimdImplBuiltin
{
  // member types {{{2
  template <typename _Tp>
  static constexpr size_t _S_max_store_size = 16;
    using abi_type = _Abi;
    template <class _Tp> using _TypeTag = _Tp *;
    template <class _Tp>
    using _SimdMember = typename _Abi::template __traits<_Tp>::_SimdMember;
    template <class _Tp>
    using _MaskMember = typename _Abi::template __traits<_Tp>::_MaskMember;
    template <class _Tp> static constexpr size_t _S_size = _Abi::template size<_Tp>;
    template <class _Tp> static constexpr size_t _S_full_size = _Abi::template _S_full_size<_Tp>;
    using _SuperImpl = typename _Abi::_SimdImpl;

    // __make_simd(_SimdWrapper/__intrinsic_type_t) {{{2
    template <class _Tp, size_t _N>
    _GLIBCXX_SIMD_INTRINSIC static simd<_Tp, _Abi> __make_simd(_SimdWrapper<_Tp, _N> __x)
    {
        return {__private_init, __x};
    }
    template <class _Tp, size_t _N>
    _GLIBCXX_SIMD_INTRINSIC static simd<_Tp, _Abi> __make_simd(__intrinsic_type_t<_Tp, _N> __x)
    {
        return {__private_init, __vector_bitcast<_Tp>(__x)};
    }

    // __broadcast {{{2
    template <class _Tp>
    _GLIBCXX_SIMD_INTRINSIC static constexpr _SimdMember<_Tp> __broadcast(_Tp __x) noexcept
    {
        return __vector_broadcast<_S_full_size<_Tp>>(__x);
    }

    // __generator {{{2
    template <class _F, class _Tp>
    inline static constexpr _SimdMember<_Tp>
      __generator(_F&& __gen, _TypeTag<_Tp>)
    {
      return __generate_vector<_Tp, _S_full_size<_Tp>>([&](
	auto __i) constexpr {
	if constexpr (__i < _S_size<_Tp>)
	  return __gen(__i);
	else
	  return 0;
      });
    }

    // __load {{{2
    template <class _Tp, class _U, class _F>
    _GLIBCXX_SIMD_INTRINSIC static _SimdMember<_Tp>
      __load(const _U* __mem, _F, _TypeTag<_Tp>) noexcept
    {
      constexpr size_t _N = _S_size<_Tp>;
      constexpr size_t __max_load_size =
	(sizeof(_U) >= 4 && __have_avx512f) || __have_avx512bw
	  ? 64
	  : (std::is_floating_point_v<_U> && __have_avx) || __have_avx2 ? 32
									: 16;
      constexpr size_t __bytes_to_load = sizeof(_U) * _N;
      if constexpr (sizeof(_U) > 8)
	return __generate_vector<_Tp, _SimdMember<_Tp>::_S_width>([&](
	  auto __i) constexpr {
	  return static_cast<_Tp>(__i < _N ? __mem[__i] : 0);
	});
      else if constexpr (std::is_same_v<_U, _Tp>)
	return __vector_load<_Tp, _S_full_size<_Tp>, _N * sizeof(_Tp)>(__mem,
								       _F());
      else if constexpr (__bytes_to_load <= __max_load_size)
	return __convert<_SimdMember<_Tp>>(__vector_load<_U, _N>(__mem, _F()));
      else if constexpr(__bytes_to_load % __max_load_size == 0)
	{
	  constexpr size_t __n_loads = __bytes_to_load / __max_load_size;
	  constexpr size_t __elements_per_load = _N / __n_loads;
	  return __call_with_n_evaluations<__n_loads>(
	    [](auto... __uncvted) {
	      return __convert<_SimdMember<_Tp>>(__uncvted...);
	    },
	    [&](auto __i) {
	      return __vector_load<_U, __elements_per_load>(
		__mem + __i * __elements_per_load, _F());
	    });
	}
      else if constexpr (__bytes_to_load % (__max_load_size / 2) == 0 &&
			 __max_load_size > 16)
	{ // e.g. int[] -> <char, 12> with AVX2
	  constexpr size_t __n_loads = __bytes_to_load / (__max_load_size / 2);
	  constexpr size_t __elements_per_load = _N / __n_loads;
	  return __call_with_n_evaluations<__n_loads>(
	    [](auto... __uncvted) {
	      return __convert<_SimdMember<_Tp>>(__uncvted...);
	    },
	    [&](auto __i) {
	      return __vector_load<_U, __elements_per_load>(
		__mem + __i * __elements_per_load, _F());
	    });
	}
      else // e.g. int[] -> <char, 9>
	return __call_with_subscripts(
	  __mem, make_index_sequence<_N>(), [](auto... __args) {
	    return __vector_type_t<_Tp, _S_full_size<_Tp>>{
	      static_cast<_Tp>(__args)...};
	  });
    }

    // __masked_load {{{2
    template <class _Tp, size_t _N, class _U, class _F>
    static inline _SimdWrapper<_Tp, _N> __masked_load(_SimdWrapper<_Tp, _N> __merge,
                                                _MaskMember<_Tp> __k,
                                                const _U *__mem,
                                                _F) noexcept
    {
      _BitOps::__bit_iteration(
	__vector_to_bitset(__k._M_data).to_ullong(),
	[&](auto __i) { __merge.__set(__i, static_cast<_Tp>(__mem[__i])); });
      return __merge;
    }

    // __store {{{2
    template <class _Tp, class _U, class _F>
    _GLIBCXX_SIMD_INTRINSIC static void
      __store(_SimdMember<_Tp> __v, _U* __mem, _F, _TypeTag<_Tp>) noexcept
    {
      // TODO: converting int -> "smaller int" can be optimized with AVX512
      constexpr size_t _N = _S_size<_Tp>;
      constexpr size_t __max_store_size =
	_SuperImpl::template _S_max_store_size<_U>;
      if constexpr (sizeof(_U) > 8)
	__execute_n_times<_N>([&](auto __i) constexpr {
	  __mem[__i] = __v[__i];
	});
      else if constexpr (std::is_same_v<_U, _Tp>)
	__vector_store<sizeof(_Tp) * _N, _N>(__v._M_data, __mem, _F());
      else if constexpr (sizeof(_U) * _N < 16)
	__vector_store<sizeof(_U) * _N>(__convert<_U>(__v),
					__mem, _F());
      else if constexpr (sizeof(_U) * _N <= __max_store_size)
	__vector_store<0, _N>(__convert<__vector_type_t<_U, _N>>(__v), __mem, _F());
      else
	{
	  constexpr size_t __vsize = __max_store_size / sizeof(_U);
	  // round up to convert the last partial vector as well:
	  constexpr size_t __stores = __div_roundup(_N, __vsize);
	  constexpr size_t __full_stores = _N / __vsize;
	  using _V = __vector_type_t<_U, __vsize>;
	  const std::array<_V, __stores> __converted =
	    __convert_all<_V, __stores>(__v);
	  __execute_n_times<__full_stores>([&](auto __i) constexpr {
	    __vector_store(__converted[__i], __mem + __i * __vsize, _F());
	  });
	  if constexpr (__full_stores < __stores)
	    __vector_store<(_N - __full_stores * __vsize) * sizeof(_U)>(
	      __converted[__full_stores], __mem + __full_stores * __vsize,
	      _F());
	}
    }

    // __masked_store_nocvt {{{2
    template <typename _Tp, std::size_t _N, typename _F>
    _GLIBCXX_SIMD_INTRINSIC static void __masked_store_nocvt(
      _SimdWrapper<_Tp, _N> __v, _Tp* __mem, _F, _SimdWrapper<_Tp, _N> __k)
    {
      if constexpr (_N <= sizeof(long) * CHAR_BIT)
	_BitOps::__bit_iteration(
	  __vector_to_bitset(__k).to_ulong(), [&](auto __i) constexpr {
	    __mem[__i] = __v[__i];
	  });
      else if constexpr (_N <= sizeof(long long) * CHAR_BIT)
	_BitOps::__bit_iteration(
	  __vector_to_bitset(__k._M_data).to_ullong(), [&](auto __i) constexpr {
	    __mem[__i] = __v[__i];
	  });
      else
	__assert_unreachable<_Tp>();
    }

    // __masked_store {{{2
    template <typename _TW,
	      typename _TVT = _VectorTraits<_TW>,
	      typename _Tp  = typename _TVT::value_type,
	      typename _U,
	      typename _F>
    static inline void __masked_store(const _TW __v,
				      _U*       __mem,
				      _F,
				      const _MaskMember<_Tp> __k) noexcept
    {
      constexpr size_t            _TV_size = _S_size<_Tp>;
      [[maybe_unused]] const auto __vi     = __to_intrin(__v);
      constexpr size_t            __max_store_size =
	_SuperImpl::template _S_max_store_size<_U>;
      if constexpr (std::is_same_v<_Tp, _U> ||
		    (std::is_integral_v<_Tp> && std::is_integral_v<_U> &&
		     sizeof(_Tp) == sizeof(_U)))
	{
	  // bitwise or no conversion, reinterpret:
	  const auto __kk = [&]() {
	    if constexpr (__is_bitmask_v<decltype(__k)>)
	      return _MaskMember<_U>(__k._M_data);
	    else
	      return __wrapper_bitcast<_U>(__k);
	  }();
	  _SuperImpl::__masked_store_nocvt(__wrapper_bitcast<_U>(__v), __mem,
					   _F(), __kk);
	}
      else if constexpr (sizeof(_U) <= 8 && // no long double
			 !__converts_via_decomposition_v<
			   _Tp, _U,
			   __max_store_size> // conversion via decomposition
					     // is better handled via the
					     // bit_iteration fallback below
      )
	{
	  using _UV = __vector_type_t<_U, std::min(_TV_size, __max_store_size /
							       sizeof(_U))>;
	  constexpr size_t _UV_size = _VectorTraits<_UV>::_S_width;
	  using _UW                 = _SimdWrapper<_U, _UV_size>;
	  constexpr bool __prefer_bitmask =
#if _GLIBCXX_SIMD_X86INTRIN // {{{
	    (__have_avx512f && sizeof(_U) >= 4) || __have_avx512bw ||
#endif // _GLIBCXX_SIMD_X86INTRIN }}}
	    false;
	  using _UM =
	    _SimdWrapper<std::conditional_t<__prefer_bitmask, bool, _U>,
			 _UV_size>;
	  if constexpr (_UV_size >= _TV_size)
	    {
	      _UW __converted(__convert<_UV>(__v));
	      // if _UV has more elements than the input (_TV_size),
	      // vector_aligned is incorrect:
	      std::conditional_t<(_UV_size > _TV_size),
				 overaligned_tag<sizeof(_U) * _TV_size>, _F>
		__flag;
	      _SuperImpl::__masked_store_nocvt(__converted, __mem, __flag,
					       __convert_mask<_UM>(__k));
	    }
	  else
	    {
	      constexpr size_t _NFullStores = _TV_size / _UV_size;
	      constexpr size_t _NAllStores  = __div_roundup(_TV_size, _UV_size);
	      constexpr size_t _NParts      = _S_full_size<_Tp> / _UV_size;
	      const std::array<_UV, _NAllStores> __converted =
		__convert_all<_UV, _NAllStores>(__v);
	      __execute_n_times<_NFullStores>([&](auto __i) {
		_SuperImpl::__masked_store_nocvt(
		  _UW(__converted[__i]), __mem + __i * _UV_size, _F(),
		  __convert_mask<_UM>(
		    __extract_part<__i, _NParts>(__k.__as_full_vector())));
	      });
	      if constexpr (_NAllStores >
			    _NFullStores) // one partial at the end
		_SuperImpl::__masked_store_nocvt(
		  _UW(__converted[_NFullStores]),
		  __mem + _NFullStores * _UV_size, _F(),
		  __convert_mask<_UM>(__extract_part<_NFullStores, _NParts>(
		    __k.__as_full_vector())));
	    }
	}
      else
	_BitOps::__bit_iteration(
	  __vector_to_bitset(__k._M_data).to_ullong(), [&](auto __i) constexpr {
	    __mem[__i] = static_cast<_U>(__v[__i]);
	  });
    }

    // __complement {{{2
    template <class _Tp, size_t _N>
    _GLIBCXX_SIMD_INTRINSIC static constexpr _SimdWrapper<_Tp, _N> __complement(_SimdWrapper<_Tp, _N> __x) noexcept
    {
        return ~__x._M_data;
    }

    // __unary_minus {{{2
    template <class _Tp, size_t _N>
    _GLIBCXX_SIMD_INTRINSIC static constexpr _SimdWrapper<_Tp, _N> __unary_minus(_SimdWrapper<_Tp, _N> __x) noexcept
    {
        // GCC doesn't use the psign instructions, but pxor & psub seem to be just as good
        // a choice as pcmpeqd & psign. So meh.
        return -__x._M_data;
    }

    // arithmetic operators {{{2
    template <class _Tp, size_t _N>
    _GLIBCXX_SIMD_INTRINSIC static constexpr _SimdWrapper<_Tp, _N> __plus(_SimdWrapper<_Tp, _N> __x,
                                                                    _SimdWrapper<_Tp, _N> __y)
    {
      return __x._M_data + __y._M_data;
    }
    template <class _Tp, size_t _N>
    _GLIBCXX_SIMD_INTRINSIC static constexpr _SimdWrapper<_Tp, _N> __minus(_SimdWrapper<_Tp, _N> __x,
                                                                     _SimdWrapper<_Tp, _N> __y)
    {
      return __x._M_data - __y._M_data;
    }
    template <class _Tp, size_t _N>
    _GLIBCXX_SIMD_INTRINSIC static constexpr _SimdWrapper<_Tp, _N> __multiplies(
        _SimdWrapper<_Tp, _N> __x, _SimdWrapper<_Tp, _N> __y)
    {
      return __x._M_data * __y._M_data;
    }
    template <class _Tp, size_t _N>
    _GLIBCXX_SIMD_INTRINSIC static constexpr _SimdWrapper<_Tp, _N> __divides(
        _SimdWrapper<_Tp, _N> __x, _SimdWrapper<_Tp, _N> __y)
    {
      // Note that division by 0 is always UB, so we must ensure we avoid the
      // case for partial registers
      if constexpr (!_Abi::_S_is_partial)
        return __x._M_data / __y._M_data;
      else
	return __as_vector(__x) /
	       _Abi::__make_padding_nonzero(__as_vector(__y));
    }
    template <class _Tp, size_t _N>
    _GLIBCXX_SIMD_INTRINSIC static constexpr _SimdWrapper<_Tp, _N> __modulus(_SimdWrapper<_Tp, _N> __x, _SimdWrapper<_Tp, _N> __y)
    {
      static_assert(std::is_integral<_Tp>::value,
		    "modulus is only supported for integral types");
      if constexpr (!_Abi::_S_is_partial)
	return __x._M_data % __y._M_data;
      else
	return __as_vector(__x) %
	       _Abi::__make_padding_nonzero(__as_vector(__y));
    }
    template <class _Tp, size_t _N>
    _GLIBCXX_SIMD_INTRINSIC static constexpr _SimdWrapper<_Tp, _N> __bit_and(_SimdWrapper<_Tp, _N> __x, _SimdWrapper<_Tp, _N> __y)
    {
        return __and(__x._M_data, __y._M_data);
    }
    template <class _Tp, size_t _N>
    _GLIBCXX_SIMD_INTRINSIC static constexpr _SimdWrapper<_Tp, _N> __bit_or(_SimdWrapper<_Tp, _N> __x, _SimdWrapper<_Tp, _N> __y)
    {
        return __or(__x._M_data, __y._M_data);
    }
    template <class _Tp, size_t _N>
    _GLIBCXX_SIMD_INTRINSIC static constexpr _SimdWrapper<_Tp, _N> __bit_xor(_SimdWrapper<_Tp, _N> __x, _SimdWrapper<_Tp, _N> __y)
    {
        return __xor(__x._M_data, __y._M_data);
    }
    template <class _Tp, size_t _N>
    _GLIBCXX_SIMD_INTRINSIC static _SimdWrapper<_Tp, _N> __bit_shift_left(_SimdWrapper<_Tp, _N> __x, _SimdWrapper<_Tp, _N> __y)
    {
        return __x._M_data << __y._M_data;
    }
    template <class _Tp, size_t _N>
    _GLIBCXX_SIMD_INTRINSIC static _SimdWrapper<_Tp, _N> __bit_shift_right(_SimdWrapper<_Tp, _N> __x, _SimdWrapper<_Tp, _N> __y)
    {
        return __x._M_data >> __y._M_data;
    }

    template <class _Tp, size_t _N>
    _GLIBCXX_SIMD_INTRINSIC static constexpr _SimdWrapper<_Tp, _N> __bit_shift_left(_SimdWrapper<_Tp, _N> __x, int __y)
    {
        return __x._M_data << __y;
    }
    template <class _Tp, size_t _N>
    _GLIBCXX_SIMD_INTRINSIC static constexpr _SimdWrapper<_Tp, _N> __bit_shift_right(_SimdWrapper<_Tp, _N> __x,
                                                                         int __y)
    {
      // work around PR91838
      if (__builtin_constant_p(__y) &&
	  __y >= static_cast<int>(sizeof(_Tp) * CHAR_BIT) && is_unsigned_v<_Tp>)
	return _SimdWrapper<_Tp, _N>{};
      else
	return __x._M_data >> __y;
    }

    // compares {{{2
    // __equal_to {{{3
    template <class _Tp, size_t _N>
    _GLIBCXX_SIMD_INTRINSIC static constexpr _MaskMember<_Tp> __equal_to(
        _SimdWrapper<_Tp, _N> __x, _SimdWrapper<_Tp, _N> __y)
    {
      return _ToWrapper(__x._M_data == __y._M_data);
    }

    // __not_equal_to {{{3
    template <class _Tp, size_t _N>
    _GLIBCXX_SIMD_INTRINSIC static constexpr _MaskMember<_Tp> __not_equal_to(
        _SimdWrapper<_Tp, _N> __x, _SimdWrapper<_Tp, _N> __y)
    {
      return _ToWrapper(__x._M_data != __y._M_data);
    }

    // __less {{{3
    template <class _Tp, size_t _N>
    _GLIBCXX_SIMD_INTRINSIC static constexpr _MaskMember<_Tp> __less(_SimdWrapper<_Tp, _N> __x,
                                                           _SimdWrapper<_Tp, _N> __y)
    {
      return _ToWrapper(__x._M_data < __y._M_data);
    }

    // __less_equal {{{3
    template <class _Tp, size_t _N>
    _GLIBCXX_SIMD_INTRINSIC static constexpr _MaskMember<_Tp> __less_equal(_SimdWrapper<_Tp, _N> __x,
                                                                 _SimdWrapper<_Tp, _N> __y)
    {
      return _ToWrapper(__x._M_data <= __y._M_data);
    }

    // negation {{{2
    template <class _Tp, size_t _N>
    _GLIBCXX_SIMD_INTRINSIC static constexpr _MaskMember<_Tp> __negate(_SimdWrapper<_Tp, _N> __x) noexcept
    {
      return _ToWrapper(!__x._M_data);
    }

    // __min, __max, __minmax {{{2
    template <class _Tp, size_t _N>
    _GLIBCXX_SIMD_NORMAL_MATH _GLIBCXX_SIMD_INTRINSIC static constexpr _SimdWrapper<_Tp, _N> __min(_SimdWrapper<_Tp, _N> __a,
                                                                   _SimdWrapper<_Tp, _N> __b)
    {
        return __a._M_data < __b._M_data ? __a._M_data : __b._M_data;
    }
    template <class _Tp, size_t _N>
    _GLIBCXX_SIMD_NORMAL_MATH _GLIBCXX_SIMD_INTRINSIC static constexpr _SimdWrapper<_Tp, _N> __max(_SimdWrapper<_Tp, _N> __a,
                                                                   _SimdWrapper<_Tp, _N> __b)
    {
        return __a._M_data > __b._M_data ? __a._M_data : __b._M_data;
    }

    template <class _Tp, size_t _N>
    _GLIBCXX_SIMD_NORMAL_MATH _GLIBCXX_SIMD_INTRINSIC static constexpr std::pair<_SimdWrapper<_Tp, _N>, _SimdWrapper<_Tp, _N>>
    __minmax(_SimdWrapper<_Tp, _N> __a, _SimdWrapper<_Tp, _N> __b)
    {
        return {__a._M_data < __b._M_data ? __a._M_data : __b._M_data, __a._M_data < __b._M_data ? __b._M_data : __a._M_data};
    }

    // reductions {{{2
    template <size_t _N,
	      size_t... _Is,
	      size_t... _Zeros,
	      class _Tp,
	      class _BinaryOperation>
    _GLIBCXX_SIMD_INTRINSIC static _Tp
      __reduce_partial(std::index_sequence<_Is...>,
		       std::index_sequence<_Zeros...>,
		       simd<_Tp, _Abi>    __x,
		       _BinaryOperation&& __binary_op)
    {
      using _V = __vector_type_t<_Tp, _N / 2>;
      static_assert(sizeof(_V) <= sizeof(__x));
      // _S_width is the size of the smallest native SIMD register that can
      // store _N/2 elements:
      using _FullSimd =
	__deduced_simd<_Tp, _VectorTraits<_V>::_S_width>;
      using _HalfSimd = __deduced_simd<_Tp, _N / 2>;
      const auto __xx = __as_vector(__x);
      return _HalfSimd::abi_type::_SimdImpl::__reduce(
	static_cast<_HalfSimd>(__as_vector(__binary_op(
	  static_cast<_FullSimd>(__intrin_bitcast<_V>(__xx)),
	  static_cast<_FullSimd>(__intrin_bitcast<_V>(
	    __vector_permute<(_N / 2 + _Is)..., (int(_Zeros * 0) - 1)...>(
	      __xx)))))),
	__binary_op);
    }

    template <class _Tp, class _BinaryOperation>
    _GLIBCXX_SIMD_INTRINSIC static _Tp
      __reduce(simd<_Tp, _Abi> __x, _BinaryOperation&& __binary_op)
    {
      constexpr size_t _N = simd_size_v<_Tp, _Abi>;
      if constexpr (_Abi::_S_is_partial) //{{{
	{
	  [[maybe_unused]] constexpr auto __full_size =
	    _Abi::template _S_full_size<_Tp>;
	  if constexpr (_N == 1)
	    return __x[0];
	  else if constexpr (_N == 2)
	    return __binary_op(simd<_Tp, simd_abi::scalar>(__x[0]),
			       simd<_Tp, simd_abi::scalar>(__x[1]))[0];
	  else if constexpr (_N == 3)
	    return __binary_op(__binary_op(simd<_Tp, simd_abi::scalar>(__x[0]),
					   simd<_Tp, simd_abi::scalar>(__x[1])),
			       simd<_Tp, simd_abi::scalar>(__x[2]))[0];
	  else if constexpr (std::is_same_v<__remove_cvref_t<_BinaryOperation>,
					    std::plus<>>)
	    {
	      using _A = simd_abi::deduce_t<_Tp, __full_size>;
	      return _A::_SimdImpl::__reduce(
		simd<_Tp, _A>(__private_init, _Abi::__masked(__as_vector(__x))),
		__binary_op);
	    }
	  else if constexpr (std::is_same_v<__remove_cvref_t<_BinaryOperation>,
					    std::multiplies<>>)
	    {
	      using _A = simd_abi::deduce_t<_Tp, __full_size>;
	      return _A::_SimdImpl::__reduce(
		simd<_Tp, _A>(__private_init,
			      __blend(_Abi::template __implicit_mask<_Tp>(),
				      __vector_broadcast<__full_size>(_Tp(1)),
				      __as_vector(__x))),
		__binary_op);
	    }
	  else if constexpr (_N & 1)
	    {
	      using _A = simd_abi::deduce_t<_Tp, _N-1>;
	      return __binary_op(
		simd<_Tp, simd_abi::scalar>(_A::_SimdImpl::__reduce(
		  simd<_Tp, _A>(__intrin_bitcast<__vector_type_t<_Tp, _N - 1>>(
		    __as_vector(__x))),
		  __binary_op)),
		simd<_Tp, simd_abi::scalar>(__x[_N - 1]))[0];
	    }
	  else
	    return __reduce_partial<_N>(
	      std::make_index_sequence<_N / 2>(),
	      std::make_index_sequence<__full_size - _N / 2>(), __x,
	      __binary_op);
	} //}}}
#if _GLIBCXX_SIMD_HAVE_NEON // {{{
      else if constexpr (sizeof(__x) == 8 || sizeof(__x) == 16)
	{
	  static_assert(_N <= 8); // either 64-bit vectors or 128-bit double
	  if constexpr (_N == 8)
	    {
	      __x = __binary_op(
		__x, __make_simd<_Tp, _N>(
		       __vector_permute<1, 0, 3, 2, 5, 4, 7, 6>(__x._M_data)));
	      __x = __binary_op(
		__x, __make_simd<_Tp, _N>(
		       __vector_permute<3, 2, 1, 0, 7, 6, 5, 4>(__x._M_data)));
	      __x = __binary_op(
		__x, __make_simd<_Tp, _N>(
		       __vector_permute<7, 6, 5, 4, 3, 2, 1, 0>(__x._M_data)));
              return __x[0];
	    }
	  else if constexpr (_N == 4)
	    {
	      __x = __binary_op(
		__x, __make_simd<_Tp, _N>(
		       __vector_permute<1, 0, 3, 2>(__x._M_data)));
	      __x = __binary_op(
		__x, __make_simd<_Tp, _N>(
		       __vector_permute<3, 2, 1, 0>(__x._M_data)));
              return __x[0];
	    }
	  else
	    {
	      static_assert(_N == 2);
	      __x = __binary_op(
		__x, __make_simd<_Tp, _N>(__vector_permute<1, 0>(__x._M_data)));
	      return __x[0];
	    }
	}
#endif // _GLIBCXX_SIMD_HAVE_NEON }}}
      else if constexpr (sizeof(__x) == 16) //{{{
	{
	  if constexpr (_N == 16)
	    {
	      const auto __y = __x._M_data;
	      __x            = __binary_op(
                __make_simd<_Tp, _N>(__vector_permute<0, 0, 1, 1, 2, 2, 3, 3, 4,
                                                    4, 5, 5, 6, 6, 7, 7>(__y)),
                __make_simd<_Tp, _N>(
                  __vector_permute<8, 8, 9, 9, 10, 10, 11, 11, 12, 12, 13, 13,
                                   14, 14, 15, 15>(__y)));
	    }
	  if constexpr (_N >= 8)
	    {
	      const auto __y = __vector_bitcast<short>(__x._M_data);
	      __x =
		__binary_op(__make_simd<_Tp, _N>(__vector_bitcast<_Tp>(
			      __vector_permute<0, 0, 1, 1, 2, 2, 3, 3>(__y))),
			    __make_simd<_Tp, _N>(__vector_bitcast<_Tp>(
			      __vector_permute<4, 4, 5, 5, 6, 6, 7, 7>(__y))));
	    }
	  if constexpr (_N >= 4)
	    {
	      using _U =
		std::conditional_t<std::is_floating_point_v<_Tp>, float, int>;
	      const auto __y = __vector_bitcast<_U>(__x._M_data);
	      __x = __binary_op(__x, __make_simd<_Tp, _N>(__vector_bitcast<_Tp>(
				       __vector_permute<3, 2, 1, 0>(__y))));
	    }
	  using _U =
	    std::conditional_t<std::is_floating_point_v<_Tp>, double, _LLong>;
	  const auto __y = __vector_bitcast<_U>(__x._M_data);
	  __x = __binary_op(__x, __make_simd<_Tp, _N>(__vector_bitcast<_Tp>(
				   __vector_permute<1, 1>(__y))));
	  return __x[0];
	} //}}}
      else if constexpr(_N == 2)
	return __binary_op(__x, simd<_Tp, _Abi>(__x[1]))[0];
      else
	{
	  static_assert(sizeof(__x) > __min_vector_size<_Tp>);
	  static_assert((_N & (_N - 1)) == 0); // _N must be a power of 2
	  using _A = simd_abi::deduce_t<_Tp, _N / 2>;
	  using _V = std::experimental::simd<_Tp, _A>;
	  return _A::_SimdImpl::__reduce(
	    __binary_op(
	      _V(__private_init, __extract<0, 2>(__data(__x)._M_data)),
	      _V(__private_init, __extract<1, 2>(__data(__x)._M_data))),
	    std::forward<_BinaryOperation>(__binary_op));
	}
    }

    // math {{{2
    // frexp, modf and copysign implemented in simd_math.h
#define _GLIBCXX_SIMD_MATH_FALLBACK(__name)                                    \
  template <typename _Tp, typename... _More>                                   \
  static _Tp __##__name(const _Tp& __x, const _More&... __more)                \
  {                                                                            \
    return __generate_vector<_Tp>(                                             \
      [&](auto __i) { return std::__name(__x[__i], __more[__i]...); });        \
  }

#define _GLIBCXX_SIMD_MATH_FALLBACK_MASKRET(__name)                            \
  template <typename _Tp, typename... _More>                                   \
  static                                                                       \
    typename _Tp::mask_type __##__name(const _Tp& __x, const _More&... __more) \
  {                                                                            \
    return __generate_vector<_Tp>(                                             \
      [&](auto __i) { return std::__name(__x[__i], __more[__i]...); });        \
  }

#define _GLIBCXX_SIMD_MATH_FALLBACK_FIXEDRET(_RetTp, __name)                   \
  template <typename _Tp, typename... _More>                                   \
  static auto __##__name(const _Tp& __x, const _More&... __more)               \
  {                                                                            \
    return __fixed_size_storage_t<_RetTp,                                      \
				  _VectorTraits<_Tp>::_S_partial_width>::      \
      __generate([&](auto __meta) constexpr {                                  \
	return __meta.__generator(                                             \
	  [&](auto __i) {                                                      \
	    return std::__name(__x[__meta._S_offset + __i],                    \
			       __more[__meta._S_offset + __i]...);             \
	  },                                                                   \
	  static_cast<_RetTp*>(nullptr));                                      \
      });                                                                      \
  }

  _GLIBCXX_SIMD_MATH_FALLBACK(acos)
  _GLIBCXX_SIMD_MATH_FALLBACK(asin)
  _GLIBCXX_SIMD_MATH_FALLBACK(atan)
  _GLIBCXX_SIMD_MATH_FALLBACK(atan2)
  _GLIBCXX_SIMD_MATH_FALLBACK(cos)
  _GLIBCXX_SIMD_MATH_FALLBACK(sin)
  _GLIBCXX_SIMD_MATH_FALLBACK(tan)
  _GLIBCXX_SIMD_MATH_FALLBACK(acosh)
  _GLIBCXX_SIMD_MATH_FALLBACK(asinh)
  _GLIBCXX_SIMD_MATH_FALLBACK(atanh)
  _GLIBCXX_SIMD_MATH_FALLBACK(cosh)
  _GLIBCXX_SIMD_MATH_FALLBACK(sinh)
  _GLIBCXX_SIMD_MATH_FALLBACK(tanh)
  _GLIBCXX_SIMD_MATH_FALLBACK(exp)
  _GLIBCXX_SIMD_MATH_FALLBACK(exp2)
  _GLIBCXX_SIMD_MATH_FALLBACK(expm1)
  _GLIBCXX_SIMD_MATH_FALLBACK(ldexp)
  _GLIBCXX_SIMD_MATH_FALLBACK_FIXEDRET(int, ilogb)
  _GLIBCXX_SIMD_MATH_FALLBACK(log)
  _GLIBCXX_SIMD_MATH_FALLBACK(log10)
  _GLIBCXX_SIMD_MATH_FALLBACK(log1p)
  _GLIBCXX_SIMD_MATH_FALLBACK(log2)
  _GLIBCXX_SIMD_MATH_FALLBACK(logb)

  //modf implemented in simd_math.h
  _GLIBCXX_SIMD_MATH_FALLBACK(scalbn)
  _GLIBCXX_SIMD_MATH_FALLBACK(scalbln)
  _GLIBCXX_SIMD_MATH_FALLBACK(cbrt)
  _GLIBCXX_SIMD_MATH_FALLBACK(abs)
  _GLIBCXX_SIMD_MATH_FALLBACK(fabs)
  _GLIBCXX_SIMD_MATH_FALLBACK(pow)
  _GLIBCXX_SIMD_MATH_FALLBACK(sqrt)
  _GLIBCXX_SIMD_MATH_FALLBACK(erf)
  _GLIBCXX_SIMD_MATH_FALLBACK(erfc)
  _GLIBCXX_SIMD_MATH_FALLBACK(lgamma)
  _GLIBCXX_SIMD_MATH_FALLBACK(tgamma)
  _GLIBCXX_SIMD_MATH_FALLBACK(ceil)
  _GLIBCXX_SIMD_MATH_FALLBACK(floor)
  _GLIBCXX_SIMD_MATH_FALLBACK(nearbyint)

  _GLIBCXX_SIMD_MATH_FALLBACK(rint)
  _GLIBCXX_SIMD_MATH_FALLBACK_FIXEDRET(long, lrint)
  _GLIBCXX_SIMD_MATH_FALLBACK_FIXEDRET(long long, llrint)

  _GLIBCXX_SIMD_MATH_FALLBACK(round)
  _GLIBCXX_SIMD_MATH_FALLBACK_FIXEDRET(long, lround)
  _GLIBCXX_SIMD_MATH_FALLBACK_FIXEDRET(long long, llround)

  _GLIBCXX_SIMD_MATH_FALLBACK(trunc)
  _GLIBCXX_SIMD_MATH_FALLBACK(fmod)
  _GLIBCXX_SIMD_MATH_FALLBACK(remainder)

  template <typename _Tp, typename _TVT = _VectorTraits<_Tp>>
  static _Tp __remquo(const _Tp                                   __x,
		      const _Tp                                   __y,
		      __fixed_size_storage_t<int, _TVT::_S_partial_width>* __z)
  {
    return __generate_vector<_Tp>([&](auto __i) {
      int  __tmp;
      auto __r    = std::remquo(__x[__i], __y[__i], &__tmp);
      __z->__set(__i, __tmp);
      return __r;
    });
  }

  // copysign in simd_math.h
  _GLIBCXX_SIMD_MATH_FALLBACK(nextafter)
  _GLIBCXX_SIMD_MATH_FALLBACK(fdim)
  _GLIBCXX_SIMD_MATH_FALLBACK(fmax)
  _GLIBCXX_SIMD_MATH_FALLBACK(fmin)
  _GLIBCXX_SIMD_MATH_FALLBACK(fma)

  template <typename _Tp>
  static constexpr auto __isgreater(_Tp __x, _Tp __y)
  {
      return [=](auto __i) constexpr
      {
	return std::isgreater(__x[__i], __y[__i]);
      };
  }
  template <typename _Tp>
  static constexpr auto __isgreaterequal(_Tp __x, _Tp __y)
  {
      return [=](auto __i) constexpr
      {
	return std::isgreaterequal(__x[__i], __y[__i]);
      };
  }
  template <typename _Tp>
  static constexpr auto __isless(_Tp __x, _Tp __y)
  {
      return [=](auto __i) constexpr
      {
	return std::isless(__x[__i], __y[__i]);
      };
  }
  template <typename _Tp>
  static constexpr auto __islessequal(_Tp __x, _Tp __y)
  {
      return [=](auto __i) constexpr
      {
	return std::islessequal(__x[__i], __y[__i]);
      };
  }
  template <typename _Tp>
  static constexpr auto __islessgreater(_Tp __x, _Tp __y)
  {
      return [=](auto __i) constexpr
      {
	return std::islessgreater(__x[__i], __y[__i]);
      };
  }

#undef _GLIBCXX_SIMD_MATH_FALLBACK
#undef _GLIBCXX_SIMD_MATH_FALLBACK_MASKRET
#undef _GLIBCXX_SIMD_MATH_FALLBACK_FIXEDRET
    // __abs {{{3
    template <class _Tp, size_t _N>
    _GLIBCXX_SIMD_INTRINSIC static _SimdWrapper<_Tp, _N>
      __abs(_SimdWrapper<_Tp, _N> __x) noexcept
    {
      // if (__builtin_is_constant_evaluated())
      //  {
      //    return __x._M_data < 0 ? -__x._M_data : __x._M_data;
      //  }
      if constexpr (std::is_floating_point_v<_Tp>)
	// `v < 0 ? -v : v` cannot compile to the efficient implementation of
	// masking the signbit off because it must consider v == -0

	// ~(-0.) & v would be easy, but breaks with fno-signed-zeros
	return __and(_S_absmask<__vector_type_t<_Tp, _N>>, __x._M_data);
      else
#ifdef _GLIBCXX_SIMD_WORKAROUND_PR91533
	if constexpr (sizeof(__x) < 16 && std::is_signed_v<_Tp>)
	{
	  if constexpr (sizeof(_Tp) == 4)
	    return __auto_bitcast(_mm_abs_epi32(__to_intrin(__x)));
	  else if constexpr (sizeof(_Tp) == 2)
	    return __auto_bitcast(_mm_abs_epi16(__to_intrin(__x)));
	  else
	    return __auto_bitcast(_mm_abs_epi8(__to_intrin(__x)));
	}
      else
#endif //_GLIBCXX_SIMD_WORKAROUND_PR91533
	return __x._M_data < 0 ? -__x._M_data : __x._M_data;
    }

    // __nearbyint {{{3
    template <typename _Tp, typename _TVT = _VectorTraits<_Tp>>
    _GLIBCXX_SIMD_INTRINSIC static _Tp __nearbyint(_Tp __x_) noexcept
    {
      using value_type = typename _TVT::value_type;
      using _V        = typename _TVT::type;
      const _V __x    = __x_;
      const _V __absx = __and(__x, _S_absmask<_V>);
      static_assert(CHAR_BIT * sizeof(1ull) >=
		    std::numeric_limits<value_type>::digits);
      constexpr _V __shifter_abs =
	_V() + (1ull << (std::numeric_limits<value_type>::digits - 1));
      const _V __shifter = __or(__and(_S_signmask<_V>, __x), __shifter_abs);
      _V __shifted = __x + __shifter;
      // how can we stop -fassociative-math to break this pattern?
      //asm("" : "+X"(__shifted));
      __shifted -= __shifter;
      return __absx < __shifter_abs ? __shifted : __x;
    }

    // __rint {{{3
    template <typename _Tp, typename _TVT = _VectorTraits<_Tp>>
    _GLIBCXX_SIMD_INTRINSIC static _Tp __rint(_Tp __x) noexcept
    {
      return _SuperImpl::__nearbyint(__x);
    }

    // __trunc {{{3
    template <class _Tp, size_t _N>
    _GLIBCXX_SIMD_INTRINSIC static _SimdWrapper<_Tp, _N>
      __trunc(_SimdWrapper<_Tp, _N> __x)
    {
      using _V        = __vector_type_t<_Tp, _N>;
      const _V __absx = __and(__x._M_data, _S_absmask<_V>);
      static_assert(CHAR_BIT * sizeof(1ull) >=
		    std::numeric_limits<_Tp>::digits);
      constexpr _Tp __shifter = 1ull << (std::numeric_limits<_Tp>::digits - 1);
      _V            __truncated = (__absx + __shifter) - __shifter;
      __truncated -= __truncated > __absx ? _V() + 1 : _V();
      return __absx < __shifter ? __or(__xor(__absx, __x._M_data), __truncated)
				: __x._M_data;
    }

    // __round {{{3
    template <class _Tp, size_t _N>
    _GLIBCXX_SIMD_INTRINSIC static _SimdWrapper<_Tp, _N>
      __round(_SimdWrapper<_Tp, _N> __x)
    {
      using _V        = __vector_type_t<_Tp, _N>;
      const _V __absx = __and(__x._M_data, _S_absmask<_V>);
      static_assert(CHAR_BIT * sizeof(1ull) >=
		    std::numeric_limits<_Tp>::digits);
      constexpr _Tp __shifter = 1ull << (std::numeric_limits<_Tp>::digits - 1);
      _V            __truncated = (__absx + __shifter) - __shifter;
      __truncated -= __truncated > __absx ? _V() + 1 : _V();
      const _V __rounded =
	__or(__xor(__absx, __x._M_data),
	     __truncated + (__absx - __truncated >= _Tp(.5) ? _V() + 1 : _V()));
      return __absx < __shifter ? __rounded : __x._M_data;
    }

    // __floor {{{3
    template <class _Tp, size_t _N>
    _GLIBCXX_SIMD_INTRINSIC static _SimdWrapper<_Tp, _N> __floor(_SimdWrapper<_Tp, _N> __x)
    {
      const auto __y = _SuperImpl::__trunc(__x)._M_data;
      const auto __negative_input = __vector_bitcast<_Tp>(__x._M_data < __vector_broadcast<_N, _Tp>(0));
      const auto __mask = __andnot(__vector_bitcast<_Tp>(__y == __x._M_data), __negative_input);
      return __or(__andnot(__mask, __y), __and(__mask, __y - __vector_broadcast<_N, _Tp>(1)));
    }

    // __ceil {{{3
    template <class _Tp, size_t _N> _GLIBCXX_SIMD_INTRINSIC static _SimdWrapper<_Tp, _N> __ceil(_SimdWrapper<_Tp, _N> __x)
    {
      const auto __y = _SuperImpl::__trunc(__x)._M_data;
      const auto __negative_input = __vector_bitcast<_Tp>(__x._M_data < __vector_broadcast<_N, _Tp>(0));
      const auto __inv_mask = __or(__vector_bitcast<_Tp>(__y == __x._M_data), __negative_input);
      return __or(__and(__inv_mask, __y),
		  __andnot(__inv_mask, __y + __vector_broadcast<_N, _Tp>(1)));
    }

    // __isnan {{{3
    template <class _Tp, size_t _N>
    _GLIBCXX_SIMD_INTRINSIC static _MaskMember<_Tp> __isnan(_SimdWrapper<_Tp, _N> __x)
    {
#if __FINITE_MATH_ONLY__
      [](auto&&){}(__x);
      return {}; // false
#else
      return _SuperImpl::__isunordered(__x, __x);
#endif
    }

    // __isfinite {{{3
    template <class _Tp, size_t _N>
    _GLIBCXX_SIMD_INTRINSIC static _MaskMember<_Tp> __isfinite(_SimdWrapper<_Tp, _N> __x)
    {
#if __FINITE_MATH_ONLY__
      [](auto&&){}(__x);
      return __vector_bitcast<_N>(_Tp()) == __vector_bitcast<_N>(_Tp());
#else
      // if all exponent bits are set, __x is either inf or NaN
      using _I = __int_for_sizeof_t<_Tp>;
      constexpr auto __inf = __vector_bitcast<_I>(
	__vector_broadcast<_N>(std::numeric_limits<_Tp>::infinity()));
      return __vector_bitcast<_Tp>(__inf >
				   (__vector_bitcast<_I>(__x) & __inf));
#endif
    }

    // __isunordered {{{3
    template <class _Tp, size_t _N>
    _GLIBCXX_SIMD_INTRINSIC static _MaskMember<_Tp>
      __isunordered(_SimdWrapper<_Tp, _N> __x, _SimdWrapper<_Tp, _N> __y)
    {
      return _SuperImpl::__isless(__x, __y) ==
	     _SuperImpl::__isgreaterequal(__x, __y);
    }

    // __signbit {{{3
    template <class _Tp, size_t _N>
    _GLIBCXX_SIMD_INTRINSIC static _MaskMember<_Tp> __signbit(_SimdWrapper<_Tp, _N> __x)
    {
      using _I = __int_for_sizeof_t<_Tp>;
      return __vector_bitcast<_Tp>(__vector_bitcast<_I>(__x) < 0);
      // Arithmetic right shift (SRA) would also work (instead of compare), but
      // 64-bit SRA isn't available on x86 before AVX512. And in general,
      // compares are more likely to be efficient than SRA.
    }

    // __isinf {{{3
    template <class _Tp, size_t _N>
    _GLIBCXX_SIMD_INTRINSIC static _MaskMember<_Tp> __isinf(_SimdWrapper<_Tp, _N> __x)
    {
#if __FINITE_MATH_ONLY__
      [](auto&&){}(__x);
      return {}; // false
#else
      return _SuperImpl::template __equal_to<_Tp, _N>(
	_SuperImpl::__abs(__x),
	__vector_broadcast<_N>(std::numeric_limits<_Tp>::infinity()));
      // alternative:
      // compare to inf using the corresponding integer type
      /*
	 return
	 __vector_bitcast<_Tp>(__vector_bitcast<__int_for_sizeof_t<_Tp>>(__abs(__x)._M_data)
	 ==
	 __vector_bitcast<__int_for_sizeof_t<_Tp>>(__vector_broadcast<_N>(
	 std::numeric_limits<_Tp>::infinity())));
	 */
#endif
    }

    // __isnormal {{{3
    template <class _Tp, size_t _N>
    _GLIBCXX_SIMD_INTRINSIC static _MaskMember<_Tp>
      __isnormal(_SimdWrapper<_Tp, _N> __x)
    {
      using _I        = __int_for_sizeof_t<_Tp>;
      const auto absn = __vector_bitcast<_I>(_SuperImpl::__abs(__x));
      const auto minn = __vector_bitcast<_I>(
	__vector_broadcast<_N>(std::numeric_limits<_Tp>::min()));
#if __FINITE_MATH_ONLY__
      return __auto_bitcast(absn >= minn);
#else
      const auto infn = __vector_bitcast<_I>(
	__vector_broadcast<_N>(std::numeric_limits<_Tp>::infinity()));
      return __auto_bitcast(absn >= minn && absn < infn);
#endif
    }

    // __fpclassify {{{3
    template <class _Tp, size_t _N>
    _GLIBCXX_SIMD_INTRINSIC static __fixed_size_storage_t<int, _N>
      __fpclassify(_SimdWrapper<_Tp, _N> __x)
    {
      using _I              = __int_for_sizeof_t<_Tp>;
      const auto       __xi = __to_intrin(__abs(__x));
      const auto       __xn = __vector_bitcast<_I>(__xi);
      constexpr size_t _NI  = sizeof(__xn) / sizeof(_I);

      constexpr auto __fp_normal    = __vector_broadcast<_NI, _I>(FP_NORMAL);
      constexpr auto __fp_nan       = __vector_broadcast<_NI, _I>(FP_NAN);
      constexpr auto __fp_infinite  = __vector_broadcast<_NI, _I>(FP_INFINITE);
      constexpr auto __fp_subnormal = __vector_broadcast<_NI, _I>(FP_SUBNORMAL);
      constexpr auto __fp_zero      = __vector_broadcast<_NI, _I>(FP_ZERO);

      __vector_type_t<_I, _NI> __tmp;
      if constexpr (sizeof(_Tp) == 4)
	__tmp = __xn < 0x0080'0000
		  ? (__xn == 0 ? __fp_zero : __fp_subnormal)
		  : (__xn < 0x7f80'0000
		       ? __fp_normal
		       : (__xn == 0x7f80'0000 ? __fp_infinite : __fp_nan));
      else if constexpr (sizeof(_Tp) == 8)
	__tmp = __xn < 0x0010'0000'0000'0000LL
		  ? (__xn == 0 ? __fp_zero : __fp_subnormal)
		  : (__xn < 0x7ff0'0000'0000'0000LL
		       ? __fp_normal
		       : (__xn == 0x7ff0'0000'0000'0000LL ? __fp_infinite
							  : __fp_nan));
      else
	__assert_unreachable<_Tp>();

      if constexpr (sizeof(_I) == sizeof(int))
	{
	  using _FixedInt = __fixed_size_storage_t<int, _N>;
	  const auto __as_int = __vector_bitcast<int, _N>(__tmp);
	  if constexpr (_FixedInt::_S_tuple_size == 1)
	    return {__as_int};
	  else if constexpr (_FixedInt::_S_tuple_size == 2 &&
			     std::is_same_v<
			       typename _FixedInt::_SecondType::_FirstAbi,
			       simd_abi::scalar>)
	    return {__extract<0, 2>(__as_int), __as_int[_N - 1]};
	  else if constexpr (_FixedInt::_S_tuple_size == 2)
	    return {__extract<0, 2>(__as_int), __auto_bitcast(__extract<1, 2>(__as_int))};
	  else
	    __assert_unreachable<_Tp>();
	}
      else if constexpr (_N == 2 && sizeof(_I) == 8 &&
			 __fixed_size_storage_t<int, _N>::_S_tuple_size == 2)
	{
	  const auto __aslong = __vector_bitcast<_LLong>(__tmp);
	  return {int(__aslong[0]), {int(__aslong[1])}};
	}
#if _GLIBCXX_SIMD_X86INTRIN
      else if constexpr (sizeof(_Tp) == 8 && sizeof(__tmp) == 32 &&
			 __fixed_size_storage_t<int, _N>::_S_tuple_size == 1)
	  return {_mm_packs_epi32(__to_intrin(__lo128(__tmp)),
				  __to_intrin(__hi128(__tmp)))};
      else if constexpr (sizeof(_Tp) == 8 && sizeof(__tmp) == 64 &&
			 __fixed_size_storage_t<int, _N>::_S_tuple_size == 1)
	  return {_mm512_cvtepi64_epi32(__to_intrin(__tmp))};
#endif // _GLIBCXX_SIMD_X86INTRIN
      else if constexpr(__fixed_size_storage_t<int, _N>::_S_tuple_size == 1)
	return {__call_with_subscripts<_N>(
	  __vector_bitcast<_LLong>(__tmp),
	  [](auto... __l) { return __make_wrapper<int>(__l...); })};
      else
	__assert_unreachable<_Tp>();
    }

    // __increment & __decrement{{{2
    template <class _Tp, size_t _N> _GLIBCXX_SIMD_INTRINSIC static void __increment(_SimdWrapper<_Tp, _N> &__x)
    {
        __x = __x._M_data + 1;
    }
    template <class _Tp, size_t _N> _GLIBCXX_SIMD_INTRINSIC static void __decrement(_SimdWrapper<_Tp, _N> &__x)
    {
        __x = __x._M_data - 1;
    }

    // smart_reference access {{{2
    template <class _Tp, size_t _N, class _U>
    _GLIBCXX_SIMD_INTRINSIC static void __set(_SimdWrapper<_Tp, _N> &__v, int __i, _U &&__x) noexcept
    {
        __v.__set(__i, std::forward<_U>(__x));
    }

    // __masked_assign{{{2
    template <class _Tp, class _K, size_t _N>
    _GLIBCXX_SIMD_INTRINSIC static void __masked_assign(_SimdWrapper<_K, _N> __k,
                                                      _SimdWrapper<_Tp, _N> &__lhs,
                                                      __id<_SimdWrapper<_Tp, _N>> __rhs)
    {
        __lhs = __blend(__k._M_data, __lhs._M_data, __rhs._M_data);
    }

    template <class _Tp, class _K, size_t _N>
    _GLIBCXX_SIMD_INTRINSIC static void __masked_assign(_SimdWrapper<_K, _N> __k, _SimdWrapper<_Tp, _N> &__lhs,
                                           __id<_Tp> __rhs)
    {
        if (__builtin_constant_p(__rhs) && __rhs == 0 && std::is_same<_K, _Tp>::value) {
            if constexpr (!__is_bitmask(__k)) {
                // the __andnot optimization only makes sense if __k._M_data is a vector register
                __lhs._M_data = __andnot(__k._M_data, __lhs._M_data);
                return;
            } else {
                // for AVX512/__mmask, a _mm512_maskz_mov is best
                __lhs._M_data = __auto_bitcast(__blend(__k, __lhs, __vector_type_t<_Tp, _N>()));
                return;
            }
        }
        __lhs._M_data = __blend(__k._M_data, __lhs._M_data, __vector_broadcast<_N>(__rhs));
    }

    // __masked_cassign {{{2
    template <typename _Op, class _Tp, class _K, size_t _N>
    _GLIBCXX_SIMD_INTRINSIC static void
      __masked_cassign(const _SimdWrapper<_K, _N>        __k,
		       _SimdWrapper<_Tp, _N>&            __lhs,
		       const __id<_SimdWrapper<_Tp, _N>> __rhs,
		       _Op                               __op)
    {
      __lhs._M_data =
	__blend(__k._M_data, __lhs._M_data, __op(_SuperImpl{}, __lhs, __rhs));
    }

    template <typename _Op, class _Tp, class _K, size_t _N>
    _GLIBCXX_SIMD_INTRINSIC static void
      __masked_cassign(const _SimdWrapper<_K, _N> __k,
		       _SimdWrapper<_Tp, _N>&     __lhs,
		       const __id<_Tp>            __rhs,
		       _Op                        __op)
    {
      __lhs._M_data =
	__blend(__k._M_data, __lhs._M_data,
		__op(_SuperImpl{}, __lhs,
		     _SimdWrapper<_Tp, _N>(__vector_broadcast<_N>(__rhs))));
    }

    // __masked_unary {{{2
    template <template <typename> class _Op, class _Tp, class _K, size_t _N>
    _GLIBCXX_SIMD_INTRINSIC static _SimdWrapper<_Tp, _N> __masked_unary(const _SimdWrapper<_K, _N> __k,
                                                            const _SimdWrapper<_Tp, _N> __v)
    {
        auto __vv = __make_simd(__v);
        _Op<decltype(__vv)> __op;
        return __blend(__k, __v, __data(__op(__vv)));
    }

    //}}}2
};

// _MaskImplBuiltin {{{1
template <class _Abi> struct _MaskImplBuiltin {
    // member types {{{2
    template <class _Tp> using _TypeTag = _Tp *;
    template <class _Tp>
    using _SimdMember = typename _Abi::template __traits<_Tp>::_SimdMember;
    template <class _Tp>
    using _MaskMember = typename _Abi::template __traits<_Tp>::_MaskMember;

    // __masked_load {{{2
    template <class _Tp, size_t _N, class _F>
    static inline _SimdWrapper<_Tp, _N> __masked_load(_SimdWrapper<_Tp, _N> __merge,
						    _SimdWrapper<_Tp, _N> __mask,
						    const bool*           __mem,
						    _F) noexcept
    {
      // AVX(2) has 32/64 bit maskload, but nothing at 8 bit granularity
      auto __tmp = __wrapper_bitcast<__int_for_sizeof_t<_Tp>>(__merge);
      _BitOps::__bit_iteration(
	__vector_to_bitset(__mask._M_data).to_ullong(),
	[&](auto __i) { __tmp.__set(__i, -__mem[__i]); });
      __merge = __wrapper_bitcast<_Tp>(__tmp);
      return __merge;
    }

    // __store {{{2
    template <class _Tp, size_t _N, class _F>
    _GLIBCXX_SIMD_INTRINSIC static void __store(_SimdWrapper<_Tp, _N> __v, bool *__mem, _F) noexcept
    {
      __execute_n_times<_N>([&](auto __i) constexpr { __mem[__i] = __v[__i]; });
    }

    // __masked_store {{{2
    template <class _Tp, size_t _N, class _F>
    static inline void __masked_store(const _SimdWrapper<_Tp, _N> __v, bool *__mem, _F,
                                    const _SimdWrapper<_Tp, _N> __k) noexcept
    {
      _BitOps::__bit_iteration(
	__vector_to_bitset(__k._M_data).to_ullong(), [&](auto __i) constexpr {
	  __mem[__i] = __v[__i];
	});
    }

    // __from_bitset{{{2
    template <size_t _N, class _Tp>
    _GLIBCXX_SIMD_INTRINSIC static _MaskMember<_Tp> __from_bitset(std::bitset<_N> __bits, _TypeTag<_Tp>)
    {
        return __convert_mask<typename _MaskMember<_Tp>::_BuiltinType>(__bits);
    }

    // logical and bitwise operators {{{2
    template <class _Tp, size_t _N>
    _GLIBCXX_SIMD_INTRINSIC static constexpr _SimdWrapper<_Tp, _N>
      __logical_and(const _SimdWrapper<_Tp, _N>& __x,
		  const _SimdWrapper<_Tp, _N>& __y)
    {
      return __and(__x._M_data, __y._M_data);
    }

    template <class _Tp, size_t _N>
    _GLIBCXX_SIMD_INTRINSIC static constexpr _SimdWrapper<_Tp, _N>
      __logical_or(const _SimdWrapper<_Tp, _N>& __x,
		 const _SimdWrapper<_Tp, _N>& __y)
    {
      return __or(__x._M_data, __y._M_data);
    }

    template <class _Tp, size_t _N>
    _GLIBCXX_SIMD_INTRINSIC static constexpr _SimdWrapper<_Tp, _N>
      __bit_and(const _SimdWrapper<_Tp, _N>& __x,
	      const _SimdWrapper<_Tp, _N>& __y)
    {
      return __and(__x._M_data, __y._M_data);
    }

    template <class _Tp, size_t _N>
    _GLIBCXX_SIMD_INTRINSIC static constexpr _SimdWrapper<_Tp, _N>
      __bit_or(const _SimdWrapper<_Tp, _N>& __x, const _SimdWrapper<_Tp, _N>& __y)
    {
      return __or(__x._M_data, __y._M_data);
    }

    template <class _Tp, size_t _N>
    _GLIBCXX_SIMD_INTRINSIC static constexpr _SimdWrapper<_Tp, _N>
      __bit_xor(const _SimdWrapper<_Tp, _N>& __x,
	      const _SimdWrapper<_Tp, _N>& __y)
    {
      return __xor(__x._M_data, __y._M_data);
    }

    // smart_reference access {{{2
    template <class _Tp, size_t _N>
    static void __set(_SimdWrapper<_Tp, _N>& __k, int __i, bool __x) noexcept
    {
      if constexpr (std::is_same_v<_Tp, bool>)
	__k.__set(__i, __x);
      else
	__k._M_data[__i] = __bit_cast<_Tp>(__int_for_sizeof_t<_Tp>(-__x));
    }

    // __masked_assign{{{2
    template <class _Tp, size_t _N>
    _GLIBCXX_SIMD_INTRINSIC static void __masked_assign(_SimdWrapper<_Tp, _N> __k, _SimdWrapper<_Tp, _N> &__lhs,
                                           __id<_SimdWrapper<_Tp, _N>> __rhs)
    {
        __lhs = __blend(__k._M_data, __lhs._M_data, __rhs._M_data);
    }

    template <class _Tp, size_t _N>
    _GLIBCXX_SIMD_INTRINSIC static void __masked_assign(_SimdWrapper<_Tp, _N> __k, _SimdWrapper<_Tp, _N> &__lhs, bool __rhs)
    {
        if (__builtin_constant_p(__rhs)) {
            if (__rhs == false) {
                __lhs = __andnot(__k._M_data, __lhs._M_data);
            } else {
                __lhs = __or(__k._M_data, __lhs._M_data);
            }
            return;
        }
        __lhs = __blend(__k, __lhs, __data(simd_mask<_Tp, _Abi>(__rhs)));
    }

    //}}}2
};

//}}}1

// _SimdConverter scalar -> scalar {{{
template <typename _From, typename _To>
struct _SimdConverter<_From,
		      simd_abi::scalar,
		      _To,
		      simd_abi::scalar,
		      std::enable_if_t<!std::is_same_v<_From, _To>>>
{
  _GLIBCXX_SIMD_INTRINSIC _To operator()(_From __a)
  {
    return static_cast<_To>(__a);
  }
};

// }}}
// _SimdConverter "native" -> scalar {{{
template <typename _From, typename _To, typename _Abi>
struct _SimdConverter<_From,
		      _Abi,
		      _To,
		      simd_abi::scalar,
		      std::enable_if_t<!std::is_same_v<_Abi, simd_abi::scalar>>>
{
  using _Arg = typename _Abi::template __traits<_From>::_SimdMember;
  static constexpr size_t _S_n = _Arg::_S_width;

  _GLIBCXX_SIMD_INTRINSIC std::array<_To, _S_n> __all(_Arg __a)
  {
    return __call_with_subscripts(
      __a, make_index_sequence<_S_n>(),
      [&](auto... __values) constexpr -> std::array<_To, _S_n> {
	return {static_cast<_To>(__values)...};
      });
  }
};

// }}}
// _SimdConverter scalar -> "native" {{{
template <typename _From, typename _To, typename _Abi>
struct _SimdConverter<_From,
		      simd_abi::scalar,
		      _To,
		      _Abi,
		      std::enable_if_t<!std::is_same_v<_Abi, simd_abi::scalar>>>
{
  using _Ret = typename _Abi::template __traits<_To>::_SimdMember;

  template <typename... _More>
  _GLIBCXX_SIMD_INTRINSIC constexpr _Ret operator()(_From __a, _More... __more)
  {
    static_assert(sizeof...(_More) + 1 == _Abi::template size<_To>);
    static_assert(std::conjunction_v<std::is_same<_From, _More>...>);
    return __make_vector<_To>(__a, __more...);
  }
};

// }}}
// _SimdConverter "native 1" -> "native 2" {{{
template <typename _From, typename _To, typename _AFrom, typename _ATo>
struct _SimdConverter<
  _From,
  _AFrom,
  _To,
  _ATo,
  std::enable_if_t<!std::disjunction_v<
    __is_fixed_size_abi<_AFrom>,
    __is_fixed_size_abi<_ATo>,
    std::is_same<_AFrom, simd_abi::scalar>,
    std::is_same<_ATo, simd_abi::scalar>,
    std::conjunction<std::is_same<_From, _To>, std::is_same<_AFrom, _ATo>>>>>
{
  using _Arg = typename _AFrom::template __traits<_From>::_SimdMember;
  using _Ret = typename _ATo::template __traits<_To>::_SimdMember;
  using _V   = __vector_type_t<_To, simd_size_v<_To, _ATo>>;

  _GLIBCXX_SIMD_INTRINSIC auto __all(_Arg __a)
  {
    return __convert_all<_V>(__a);
  }

  template <typename... _More>
  _GLIBCXX_SIMD_INTRINSIC _Ret operator()(_Arg __a, _More... __more)
  {
    return __convert<_V>(__a, __more...);
  }
};

// }}}
// _SimdConverter scalar -> fixed_size<1> {{{1
template <typename _From, typename _To>
struct _SimdConverter<_From,
		      simd_abi::scalar,
		      _To,
		      simd_abi::fixed_size<1>,
		      void>
{
  _SimdTuple<_To, simd_abi::scalar> operator()(_From __x)
  {
    return {static_cast<_To>(__x)};
  }
};

// _SimdConverter fixed_size<1> -> scalar {{{1
template <typename _From, typename _To>
struct _SimdConverter<_From,
		      simd_abi::fixed_size<1>,
		      _To,
		      simd_abi::scalar,
		      void>
{
  _GLIBCXX_SIMD_INTRINSIC _To
			  operator()(_SimdTuple<_From, simd_abi::scalar> __x)
  {
    return {static_cast<_To>(__x.first)};
  }
};

// _SimdConverter fixed_size<_N> -> fixed_size<_N> {{{1
template <typename _From, typename _To, int _N>
struct _SimdConverter<_From,
		      simd_abi::fixed_size<_N>,
		      _To,
		      simd_abi::fixed_size<_N>,
		      std::enable_if_t<!std::is_same_v<_From, _To>>>
{
  using _Ret = __fixed_size_storage_t<_To, _N>;
  using _Arg = __fixed_size_storage_t<_From, _N>;

  _GLIBCXX_SIMD_INTRINSIC _Ret operator()(const _Arg& __x)
  {
    if constexpr (std::is_same_v<_From, _To>)
      return __x;

    // special case (optimize) int signedness casts
    else if constexpr (sizeof(_From) == sizeof(_To) &&
		       std::is_integral_v<_From> && std::is_integral_v<_To>)
      return __bit_cast<_Ret>(__x);

    // special case if all ABI tags in _Ret are scalar
    else if constexpr (__is_scalar_abi<typename _Ret::_FirstAbi>())
      {
	return __call_with_subscripts(
	  __x, make_index_sequence<_N>(), [](auto... __values) constexpr->_Ret {
	    return __make_simd_tuple<_To, decltype((void)__values,
						   simd_abi::scalar())...>(
	      static_cast<_To>(__values)...);
	  });
      }

    // from one vector to one vector
    else if constexpr (_Arg::_S_first_size == _Ret::_S_first_size)
      {
	_SimdConverter<_From, typename _Arg::_FirstAbi, _To,
		       typename _Ret::_FirstAbi>
	  __native_cvt;
	if constexpr (_Arg::_S_tuple_size == 1)
	  return {__native_cvt(__x.first)};
	else
	  {
	    constexpr size_t _NRemain = _N - _Arg::_S_first_size;
	    _SimdConverter<_From, simd_abi::fixed_size<_NRemain>, _To,
			   simd_abi::fixed_size<_NRemain>>
	      __remainder_cvt;
	    return {__native_cvt(__x.first), __remainder_cvt(__x.second)};
	  }
      }

    // from one vector to multiple vectors
    else if constexpr (_Arg::_S_first_size > _Ret::_S_first_size)
      {
	const auto __multiple_return_chunks =
	  __convert_all<__vector_type_t<_To, _Ret::_S_first_size>>(__x.first);
	constexpr auto __converted = __multiple_return_chunks.size() *
				     _Ret::_FirstAbi::template size<_To>;
	constexpr auto __remaining = _N - __converted;
	if constexpr (_Arg::_S_tuple_size == 1 && __remaining == 0)
	  return __to_simd_tuple<_To, _N>(__multiple_return_chunks);
	else if constexpr (_Arg::_S_tuple_size == 1)
	  { // e.g. <int, 3> -> <double, 2, 1> or <short, 7> -> <double, 4, 2,
	    // 1>
	    using _RetRem = __remove_cvref_t<decltype(
	      __simd_tuple_pop_front<__multiple_return_chunks.size()>(_Ret()))>;
	    const auto __return_chunks2 =
	      __convert_all<__vector_type_t<_To, _RetRem::_S_first_size>, 0,
			    __converted>(__x.first);
	    constexpr auto __converted2 =
	      __converted + __return_chunks2.size() * _RetRem::_S_first_size;
	    if constexpr (__converted2 == _N)
	      return __to_simd_tuple<_To, _N>(__multiple_return_chunks,
					      __return_chunks2);
	    else
	      {
		using _RetRem2 = __remove_cvref_t<decltype(
		  __simd_tuple_pop_front<__return_chunks2.size()>(_RetRem()))>;
		const auto __return_chunks3 =
		  __convert_all<__vector_type_t<_To, _RetRem2::_S_first_size>,
				0, __converted2>(__x.first);
		constexpr auto __converted3 =
		  __converted2 +
		  __return_chunks3.size() * _RetRem2::_S_first_size;
		if constexpr (__converted3 == _N)
		  return __to_simd_tuple<_To, _N>(__multiple_return_chunks,
						  __return_chunks2, __return_chunks3);
		else
		  {
		    using _RetRem3              = __remove_cvref_t<decltype(
                      __simd_tuple_pop_front<__return_chunks3.size()>(
                        _RetRem2()))>;
		    const auto __return_chunks4 = __convert_all<
		      __vector_type_t<_To, _RetRem3::_S_first_size>, 0,
		      __converted3>(__x.first);
		    constexpr auto __converted4 =
		      __converted3 +
		      __return_chunks4.size() * _RetRem3::_S_first_size;
		    if constexpr (__converted4 == _N)
		      return __to_simd_tuple<_To, _N>(
			__multiple_return_chunks, __return_chunks2,
			__return_chunks3, __return_chunks4);
		    else
		      __assert_unreachable<_To>();
		  }
	      }
	  }
	else
	  {
	    constexpr size_t _NRemain = _N - _Arg::_S_first_size;
	    _SimdConverter<_From, simd_abi::fixed_size<_NRemain>, _To,
			   simd_abi::fixed_size<_NRemain>>
	      __remainder_cvt;
	    return __simd_tuple_concat(
	      __to_simd_tuple<_To, _Arg::_S_first_size>(
		__multiple_return_chunks),
	      __remainder_cvt(__x.second));
	  }
      }

    // from multiple vectors to one vector
    // _Arg::_S_first_size < _Ret::_S_first_size
    // a) heterogeneous input at the end of the tuple (possible with partial
    //    native registers in _Ret)
    else if constexpr (_Ret::_S_tuple_size == 1 && _N % _Arg::_S_first_size != 0)
      {
	static_assert(_Ret::_FirstAbi::_S_is_partial);
	return _Ret{__generate_from_n_evaluations<
	  _N, typename _VectorTraits<typename _Ret::_FirstType>::type>(
	  [&](auto __i) { return static_cast<_To>(__x[__i]); })};
      }
    else
      {
	static_assert(_Arg::_S_tuple_size > 1);
	constexpr auto __n =
	  __div_roundup(_Ret::_S_first_size, _Arg::_S_first_size);
	return __call_with_n_evaluations<__n>(
	  [&__x](auto... __uncvted) {
	    // assuming _Arg Abi tags for all __i are _Arg::_FirstAbi
	    _SimdConverter<_From, typename _Arg::_FirstAbi, _To,
			   typename _Ret::_FirstAbi>
	      __native_cvt;
	    if constexpr (_Ret::_S_tuple_size == 1)
	      return _Ret{__native_cvt(__uncvted...)};
	    else
	      return _Ret{
		__native_cvt(__uncvted...),
		_SimdConverter<
		  _From, simd_abi::fixed_size<_N - _Ret::_S_first_size>, _To,
		  simd_abi::fixed_size<_N - _Ret::_S_first_size>>()(
		  __simd_tuple_pop_front<sizeof...(__uncvted)>(__x))};
	  },
	  [&__x](auto __i) { return __get_tuple_at<__i>(__x); });
      }
  }
};

// _SimdConverter "native" -> fixed_size<_N> {{{1
// i.e. 1 register to ? registers
template <typename _From, typename _A, typename _To, int _N>
struct _SimdConverter<_From,
		      _A,
		      _To,
		      simd_abi::fixed_size<_N>,
		      std::enable_if_t<!__is_fixed_size_abi_v<_A>>>
{
  static_assert(
    _N == simd_size_v<_From, _A>,
    "_SimdConverter to fixed_size only works for equal element counts");

  _GLIBCXX_SIMD_INTRINSIC __fixed_size_storage_t<_To, _N>
			  operator()(typename _SimdTraits<_From, _A>::_SimdMember __x)
  {
    _SimdConverter<_From, simd_abi::fixed_size<_N>, _To,
		   simd_abi::fixed_size<_N>>
      __fixed_cvt;
    return __fixed_cvt(__fixed_size_storage_t<_From, _N>{__x});
  }
};

// _SimdConverter fixed_size<_N> -> "native" {{{1
// i.e. ? register to 1 registers
template <typename _From, int _N, typename _To, typename _A>
struct _SimdConverter<_From,
		      simd_abi::fixed_size<_N>,
		      _To,
		      _A,
		      std::enable_if_t<!__is_fixed_size_abi_v<_A>>>
{
  static_assert(
    _N == simd_size_v<_To, _A>,
    "_SimdConverter to fixed_size only works for equal element counts");

  _GLIBCXX_SIMD_INTRINSIC typename _SimdTraits<_To, _A>::_SimdMember
    operator()(__fixed_size_storage_t<_From, _N> __x)
  {
    _SimdConverter<_From, simd_abi::fixed_size<_N>, _To,
		   simd_abi::fixed_size<_N>>
      __fixed_cvt;
    return __fixed_cvt(__x).first;
  }
};

// }}}1
_GLIBCXX_SIMD_END_NAMESPACE
#endif  // __cplusplus >= 201703L
#endif  // _GLIBCXX_EXPERIMENTAL_SIMD_ABIS_H_
// vim: foldmethod=marker sw=2 noet ts=8 sts=2 tw=80
