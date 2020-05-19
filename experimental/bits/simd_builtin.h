// Simd Abi specific implementations -*- C++ -*-

// Copyright © 2015-2020 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH
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
static inline _GLIBCXX_SIMD_USE_CONSTEXPR _V _S_allbits
  = reinterpret_cast<_V>(~__vector_type_t<char, sizeof(_V) / sizeof(char)>());

// }}}
// _S_signmask, _S_absmask{{{
template <typename _V, typename = _VectorTraits<_V>>
static inline _GLIBCXX_SIMD_USE_CONSTEXPR _V _S_signmask = __xor(_V() + 1, _V() - 1);
//__andnot(_S_signmask<_V>, _S_allbits<_V>) does not work in Clang for unknown reason
template <typename _V, typename = _VectorTraits<_V>>
static inline _GLIBCXX_SIMD_USE_CONSTEXPR _V _S_absmask
  = __andnot(_S_signmask<_V>, reinterpret_cast<_V>(~__vector_type_t<char, sizeof(_V) / sizeof(char)>()));

//}}}
// __vector_permute<Indices...>{{{
// Index == -1 requests zeroing of the output element
template <int... _Indices, typename _Tp, typename _TVT = _VectorTraits<_Tp>>
_Tp
__vector_permute(_Tp __x)
{
  static_assert(sizeof...(_Indices) == _TVT::_S_width);
  return __make_vector<typename _TVT::value_type>(
    (_Indices == -1 ? 0 : __x[_Indices == -1 ? 0 : _Indices])...);
}

// }}}
// __vector_shuffle<Indices...>{{{
// Index == -1 requests zeroing of the output element
template <int... _Indices, typename _Tp, typename _TVT = _VectorTraits<_Tp>>
_Tp
__vector_shuffle(_Tp __x, _Tp __y)
{
  return _Tp{(_Indices == -1 ? 0
			     : _Indices < _TVT::_S_width
				 ? __x[_Indices]
				 : __y[_Indices - _TVT::_S_width])...};
}

// }}}
// __make_wrapper{{{
template <typename _Tp, typename... _Args>
_GLIBCXX_SIMD_INTRINSIC constexpr _SimdWrapper<_Tp, sizeof...(_Args)>
__make_wrapper(const _Args&... __args)
{
  return __make_vector<_Tp>(__args...);
}

// }}}
// __wrapper_bitcast{{{
template <typename _Tp, size_t _ToN = 0, typename _Up, size_t _M,
	  size_t _Np = _ToN != 0 ? _ToN : sizeof(_Up) * _M / sizeof(_Tp)>
_GLIBCXX_SIMD_INTRINSIC constexpr _SimdWrapper<_Tp, _Np>
__wrapper_bitcast(_SimdWrapper<_Up, _M> __x)
{
  static_assert(_Np > 1);
  return __intrin_bitcast<__vector_type_t<_Tp, _Np>>(__x._M_data);
}

// }}}
// __shift_elements_right{{{
// if (__shift % 2ⁿ == 0) => the low n Bytes are correct
template <unsigned __shift, typename _Tp, typename _TVT = _VectorTraits<_Tp>>
_GLIBCXX_SIMD_INTRINSIC _Tp
__shift_elements_right(_Tp __v)
{
  [[maybe_unused]] const auto __iv = __to_intrin(__v);
  static_assert(__shift <= sizeof(_Tp));
  if constexpr (__shift == 0)
    return __v;
  else if constexpr (__shift == sizeof(_Tp))
    return _Tp();
#if _GLIBCXX_SIMD_X86INTRIN // {{{
  else if constexpr (__have_sse && __shift == 8
		     && _TVT::template __is<float, 4>)
    return _mm_movehl_ps(__iv, __iv);
  else if constexpr (__have_sse2 && __shift == 8
		     && _TVT::template __is<double, 2>)
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
      return reinterpret_cast<typename _TVT::type>(
	_mm256_alignr_epi8(_mm256_permute2x128_si256(__vll, __vll, 0x81), __vll,
			   __shift));
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
      if constexpr (__shift >= 48)
	return __zero_extend(
	  __shift_elements_right<__shift - 48>(__extract<3, 4>(__v)));
      else if constexpr (__shift >= 32)
	return __zero_extend(
	  __shift_elements_right<__shift - 32>(__hi256(__v)));
      else if constexpr (__shift % 8 == 0)
	return reinterpret_cast<typename _TVT::type>(
	  _mm512_alignr_epi64(__m512i(), __intrin_bitcast<__m512i>(__v),
			      __shift / 8));
      else if constexpr (__shift % 4 == 0)
	return reinterpret_cast<typename _TVT::type>(
	  _mm512_alignr_epi32(__m512i(), __intrin_bitcast<__m512i>(__v),
			      __shift / 4));
      else if constexpr (__have_avx512bw && __shift < 16)
	{
	  const auto __vll = __vector_bitcast<_LLong>(__v);
	  return reinterpret_cast<typename _TVT::type>(
	    _mm512_alignr_epi8(_mm512_shuffle_i32x4(__vll, __vll, 0xf9), __vll,
			       __shift));
	}
      else if constexpr (__have_avx512bw && __shift < 32)
	{
	  const auto __vll = __vector_bitcast<_LLong>(__v);
	  return reinterpret_cast<typename _TVT::type>(
	    _mm512_alignr_epi8(_mm512_shuffle_i32x4(__vll, __m512i(), 0xee),
			       _mm512_shuffle_i32x4(__vll, __vll, 0xf9),
			       __shift - 16));
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
      constexpr int __chunksize
	= __shift % 8 == 0 ? 8
			   : __shift % 4 == 0 ? 4 : __shift % 2 == 0 ? 2 : 1;
      auto __w = __vector_bitcast<__int_with_sizeof_t<__chunksize>>(__v);
      using _Up = decltype(__w);
      return __intrin_bitcast<_Tp>(
	__call_with_n_evaluations<(sizeof(_Tp) - __shift) / __chunksize>(
	  [](auto... __chunks) { return _Up{__chunks...}; },
	  [&](auto __i) { return __w[__shift / __chunksize + __i]; }));
    }
}

// }}}
// __extract_part(_SimdWrapper<_Tp, _Np>) {{{
template <int _Index, int _Total, int _Combine, typename _Tp, size_t _Np>
_GLIBCXX_SIMD_INTRINSIC
  _GLIBCXX_SIMD_CONST _SimdWrapper<_Tp, _Np / _Total * _Combine>
  __extract_part(const _SimdWrapper<_Tp, _Np> __x)
{
  if constexpr (_Index % 2 == 0 && _Total % 2 == 0 && _Combine % 2 == 0)
    return __extract_part<_Index / 2, _Total / 2, _Combine / 2>(__x);
  else
    {
      constexpr size_t __values_per_part = _Np / _Total;
      constexpr size_t __values_to_skip = _Index * __values_per_part;
      constexpr size_t __return_size = __values_per_part * _Combine;
      using _R = __vector_type_t<_Tp, __return_size>;
      static_assert((_Index + _Combine) * __values_per_part * sizeof(_Tp)
		      <= sizeof(__x),
		    "out of bounds __extract_part");
      // the following assertion would ensure no "padding" to be read
      // static_assert(_Total >= _Index + _Combine, "_Total must be greater than
      // _Index");

      // static_assert(__return_size * _Total == _Np, "_Np must be divisible by
      // _Total");
      if (__x._M_is_constprop())
	return __generate_from_n_evaluations<__return_size, _R>(
	  [&](auto __i) { return __x[__values_to_skip + __i]; });
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
	    return __vector_bitcast<_Tp, __return_size>(
	      _mm_alignr_epi8(__hi128(__vector_bitcast<_LLong>(__x)),
			      __lo128(__vector_bitcast<_LLong>(__x)),
			      __bytes_to_skip));
	}
#endif // _GLIBCXX_SIMD_X86INTRIN }}}
      else if constexpr (_Index > 0
			 && (__values_to_skip % __return_size != 0
			     || sizeof(_R) >= 8)
			 && (__values_to_skip + __return_size) * sizeof(_Tp)
			      <= 64
			 && sizeof(__x) >= 16)
	return __intrin_bitcast<_R>(
	  __shift_elements_right<__values_to_skip * sizeof(_Tp)>(
	    __as_vector(__x)));
      else
	{
	  _R __r = {};
	  __builtin_memcpy(&__r,
			   reinterpret_cast<const char*>(&__x)
			     + sizeof(_Tp) * __values_to_skip,
			   __return_size * sizeof(_Tp));
	  return __r;
	}
    }
}

// }}}
// __extract_part(_SimdWrapper<bool, _Np>) {{{
template <int _Index, int _Total, int _Combine = 1, size_t _Np>
_GLIBCXX_SIMD_INTRINSIC constexpr _SimdWrapper<bool, _Np / _Total * _Combine>
__extract_part(const _SimdWrapper<bool, _Np> __x)
{
  static_assert(_Combine == 1, "_Combine != 1 not implemented");
  static_assert(__have_avx512f && _Np == _Np);
  static_assert(_Total >= 2 && _Index + _Combine <= _Total && _Index >= 0);
  return __x._M_data >> (_Index * _Np / _Total);
}

// }}}

// __vector_convert {{{
// implementation requires an index sequence
template <typename _To, typename _From, size_t... _I>
_GLIBCXX_SIMD_INTRINSIC constexpr _To
__vector_convert(_From __a, index_sequence<_I...>)
{
  using _Tp = typename _VectorTraits<_To>::value_type;
  return _To{static_cast<_Tp>(__a[_I])...};
}

template <typename _To, typename _From, size_t... _I>
_GLIBCXX_SIMD_INTRINSIC constexpr _To
__vector_convert(_From __a, _From __b, index_sequence<_I...>)
{
  using _Tp = typename _VectorTraits<_To>::value_type;
  return _To{static_cast<_Tp>(__a[_I])..., static_cast<_Tp>(__b[_I])...};
}

template <typename _To, typename _From, size_t... _I>
_GLIBCXX_SIMD_INTRINSIC constexpr _To
__vector_convert(_From __a, _From __b, _From __c, index_sequence<_I...>)
{
  using _Tp = typename _VectorTraits<_To>::value_type;
  return _To{static_cast<_Tp>(__a[_I])..., static_cast<_Tp>(__b[_I])...,
	     static_cast<_Tp>(__c[_I])...};
}

template <typename _To, typename _From, size_t... _I>
_GLIBCXX_SIMD_INTRINSIC constexpr _To
__vector_convert(_From __a, _From __b, _From __c, _From __d,
		 index_sequence<_I...>)
{
  using _Tp = typename _VectorTraits<_To>::value_type;
  return _To{static_cast<_Tp>(__a[_I])..., static_cast<_Tp>(__b[_I])...,
	     static_cast<_Tp>(__c[_I])..., static_cast<_Tp>(__d[_I])...};
}

template <typename _To, typename _From, size_t... _I>
_GLIBCXX_SIMD_INTRINSIC constexpr _To
__vector_convert(_From __a, _From __b, _From __c, _From __d, _From __e,
		 index_sequence<_I...>)
{
  using _Tp = typename _VectorTraits<_To>::value_type;
  return _To{static_cast<_Tp>(__a[_I])..., static_cast<_Tp>(__b[_I])...,
	     static_cast<_Tp>(__c[_I])..., static_cast<_Tp>(__d[_I])...,
	     static_cast<_Tp>(__e[_I])...};
}

template <typename _To, typename _From, size_t... _I>
_GLIBCXX_SIMD_INTRINSIC constexpr _To
__vector_convert(_From __a, _From __b, _From __c, _From __d, _From __e,
		 _From __f, index_sequence<_I...>)
{
  using _Tp = typename _VectorTraits<_To>::value_type;
  return _To{static_cast<_Tp>(__a[_I])..., static_cast<_Tp>(__b[_I])...,
	     static_cast<_Tp>(__c[_I])..., static_cast<_Tp>(__d[_I])...,
	     static_cast<_Tp>(__e[_I])..., static_cast<_Tp>(__f[_I])...};
}

template <typename _To, typename _From, size_t... _I>
_GLIBCXX_SIMD_INTRINSIC constexpr _To
__vector_convert(_From __a, _From __b, _From __c, _From __d, _From __e,
		 _From __f, _From __g, index_sequence<_I...>)
{
  using _Tp = typename _VectorTraits<_To>::value_type;
  return _To{static_cast<_Tp>(__a[_I])..., static_cast<_Tp>(__b[_I])...,
	     static_cast<_Tp>(__c[_I])..., static_cast<_Tp>(__d[_I])...,
	     static_cast<_Tp>(__e[_I])..., static_cast<_Tp>(__f[_I])...,
	     static_cast<_Tp>(__g[_I])...};
}

template <typename _To, typename _From, size_t... _I>
_GLIBCXX_SIMD_INTRINSIC constexpr _To
__vector_convert(_From __a, _From __b, _From __c, _From __d, _From __e,
		 _From __f, _From __g, _From __h, index_sequence<_I...>)
{
  using _Tp = typename _VectorTraits<_To>::value_type;
  return _To{static_cast<_Tp>(__a[_I])..., static_cast<_Tp>(__b[_I])...,
	     static_cast<_Tp>(__c[_I])..., static_cast<_Tp>(__d[_I])...,
	     static_cast<_Tp>(__e[_I])..., static_cast<_Tp>(__f[_I])...,
	     static_cast<_Tp>(__g[_I])..., static_cast<_Tp>(__h[_I])...};
}

template <typename _To, typename _From, size_t... _I>
_GLIBCXX_SIMD_INTRINSIC constexpr _To
__vector_convert(_From __a, _From __b, _From __c, _From __d, _From __e,
		 _From __f, _From __g, _From __h, _From __i,
		 index_sequence<_I...>)
{
  using _Tp = typename _VectorTraits<_To>::value_type;
  return _To{static_cast<_Tp>(__a[_I])..., static_cast<_Tp>(__b[_I])...,
	     static_cast<_Tp>(__c[_I])..., static_cast<_Tp>(__d[_I])...,
	     static_cast<_Tp>(__e[_I])..., static_cast<_Tp>(__f[_I])...,
	     static_cast<_Tp>(__g[_I])..., static_cast<_Tp>(__h[_I])...,
	     static_cast<_Tp>(__i[_I])...};
}

template <typename _To, typename _From, size_t... _I>
_GLIBCXX_SIMD_INTRINSIC constexpr _To
__vector_convert(_From __a, _From __b, _From __c, _From __d, _From __e,
		 _From __f, _From __g, _From __h, _From __i, _From __j,
		 index_sequence<_I...>)
{
  using _Tp = typename _VectorTraits<_To>::value_type;
  return _To{static_cast<_Tp>(__a[_I])..., static_cast<_Tp>(__b[_I])...,
	     static_cast<_Tp>(__c[_I])..., static_cast<_Tp>(__d[_I])...,
	     static_cast<_Tp>(__e[_I])..., static_cast<_Tp>(__f[_I])...,
	     static_cast<_Tp>(__g[_I])..., static_cast<_Tp>(__h[_I])...,
	     static_cast<_Tp>(__i[_I])..., static_cast<_Tp>(__j[_I])...};
}

template <typename _To, typename _From, size_t... _I>
_GLIBCXX_SIMD_INTRINSIC constexpr _To
__vector_convert(_From __a, _From __b, _From __c, _From __d, _From __e,
		 _From __f, _From __g, _From __h, _From __i, _From __j,
		 _From __k, index_sequence<_I...>)
{
  using _Tp = typename _VectorTraits<_To>::value_type;
  return _To{static_cast<_Tp>(__a[_I])..., static_cast<_Tp>(__b[_I])...,
	     static_cast<_Tp>(__c[_I])..., static_cast<_Tp>(__d[_I])...,
	     static_cast<_Tp>(__e[_I])..., static_cast<_Tp>(__f[_I])...,
	     static_cast<_Tp>(__g[_I])..., static_cast<_Tp>(__h[_I])...,
	     static_cast<_Tp>(__i[_I])..., static_cast<_Tp>(__j[_I])...,
	     static_cast<_Tp>(__k[_I])...};
}

template <typename _To, typename _From, size_t... _I>
_GLIBCXX_SIMD_INTRINSIC constexpr _To
__vector_convert(_From __a, _From __b, _From __c, _From __d, _From __e,
		 _From __f, _From __g, _From __h, _From __i, _From __j,
		 _From __k, _From __l, index_sequence<_I...>)
{
  using _Tp = typename _VectorTraits<_To>::value_type;
  return _To{static_cast<_Tp>(__a[_I])..., static_cast<_Tp>(__b[_I])...,
	     static_cast<_Tp>(__c[_I])..., static_cast<_Tp>(__d[_I])...,
	     static_cast<_Tp>(__e[_I])..., static_cast<_Tp>(__f[_I])...,
	     static_cast<_Tp>(__g[_I])..., static_cast<_Tp>(__h[_I])...,
	     static_cast<_Tp>(__i[_I])..., static_cast<_Tp>(__j[_I])...,
	     static_cast<_Tp>(__k[_I])..., static_cast<_Tp>(__l[_I])...};
}

template <typename _To, typename _From, size_t... _I>
_GLIBCXX_SIMD_INTRINSIC constexpr _To
__vector_convert(_From __a, _From __b, _From __c, _From __d, _From __e,
		 _From __f, _From __g, _From __h, _From __i, _From __j,
		 _From __k, _From __l, _From __m, index_sequence<_I...>)
{
  using _Tp = typename _VectorTraits<_To>::value_type;
  return _To{static_cast<_Tp>(__a[_I])..., static_cast<_Tp>(__b[_I])...,
	     static_cast<_Tp>(__c[_I])..., static_cast<_Tp>(__d[_I])...,
	     static_cast<_Tp>(__e[_I])..., static_cast<_Tp>(__f[_I])...,
	     static_cast<_Tp>(__g[_I])..., static_cast<_Tp>(__h[_I])...,
	     static_cast<_Tp>(__i[_I])..., static_cast<_Tp>(__j[_I])...,
	     static_cast<_Tp>(__k[_I])..., static_cast<_Tp>(__l[_I])...,
	     static_cast<_Tp>(__m[_I])...};
}

template <typename _To, typename _From, size_t... _I>
_GLIBCXX_SIMD_INTRINSIC constexpr _To
__vector_convert(_From __a, _From __b, _From __c, _From __d, _From __e,
		 _From __f, _From __g, _From __h, _From __i, _From __j,
		 _From __k, _From __l, _From __m, _From __n,
		 index_sequence<_I...>)
{
  using _Tp = typename _VectorTraits<_To>::value_type;
  return _To{static_cast<_Tp>(__a[_I])..., static_cast<_Tp>(__b[_I])...,
	     static_cast<_Tp>(__c[_I])..., static_cast<_Tp>(__d[_I])...,
	     static_cast<_Tp>(__e[_I])..., static_cast<_Tp>(__f[_I])...,
	     static_cast<_Tp>(__g[_I])..., static_cast<_Tp>(__h[_I])...,
	     static_cast<_Tp>(__i[_I])..., static_cast<_Tp>(__j[_I])...,
	     static_cast<_Tp>(__k[_I])..., static_cast<_Tp>(__l[_I])...,
	     static_cast<_Tp>(__m[_I])..., static_cast<_Tp>(__n[_I])...};
}

template <typename _To, typename _From, size_t... _I>
_GLIBCXX_SIMD_INTRINSIC constexpr _To
__vector_convert(_From __a, _From __b, _From __c, _From __d, _From __e,
		 _From __f, _From __g, _From __h, _From __i, _From __j,
		 _From __k, _From __l, _From __m, _From __n, _From __o,
		 index_sequence<_I...>)
{
  using _Tp = typename _VectorTraits<_To>::value_type;
  return _To{static_cast<_Tp>(__a[_I])..., static_cast<_Tp>(__b[_I])...,
	     static_cast<_Tp>(__c[_I])..., static_cast<_Tp>(__d[_I])...,
	     static_cast<_Tp>(__e[_I])..., static_cast<_Tp>(__f[_I])...,
	     static_cast<_Tp>(__g[_I])..., static_cast<_Tp>(__h[_I])...,
	     static_cast<_Tp>(__i[_I])..., static_cast<_Tp>(__j[_I])...,
	     static_cast<_Tp>(__k[_I])..., static_cast<_Tp>(__l[_I])...,
	     static_cast<_Tp>(__m[_I])..., static_cast<_Tp>(__n[_I])...,
	     static_cast<_Tp>(__o[_I])...};
}

template <typename _To, typename _From, size_t... _I>
_GLIBCXX_SIMD_INTRINSIC constexpr _To
__vector_convert(_From __a, _From __b, _From __c, _From __d, _From __e,
		 _From __f, _From __g, _From __h, _From __i, _From __j,
		 _From __k, _From __l, _From __m, _From __n, _From __o,
		 _From __p, index_sequence<_I...>)
{
  using _Tp = typename _VectorTraits<_To>::value_type;
  return _To{static_cast<_Tp>(__a[_I])..., static_cast<_Tp>(__b[_I])...,
	     static_cast<_Tp>(__c[_I])..., static_cast<_Tp>(__d[_I])...,
	     static_cast<_Tp>(__e[_I])..., static_cast<_Tp>(__f[_I])...,
	     static_cast<_Tp>(__g[_I])..., static_cast<_Tp>(__h[_I])...,
	     static_cast<_Tp>(__i[_I])..., static_cast<_Tp>(__j[_I])...,
	     static_cast<_Tp>(__k[_I])..., static_cast<_Tp>(__l[_I])...,
	     static_cast<_Tp>(__m[_I])..., static_cast<_Tp>(__n[_I])...,
	     static_cast<_Tp>(__o[_I])..., static_cast<_Tp>(__p[_I])...};
}

// Defer actual conversion to the overload that takes an index sequence. Note
// that this function adds zeros or drops values off the end if you don't ensure
// matching width.
template <typename _To, typename... _From, typename _ToT = _VectorTraits<_To>,
	  typename _FromT = _VectorTraits<__first_of_pack_t<_From...>>>
_GLIBCXX_SIMD_INTRINSIC constexpr _To
__vector_convert(_From... __xs)
{
#ifdef _GLIBCXX_SIMD_WORKAROUND_PR85048
  if (!(... && __builtin_constant_p(__xs)))
    {
      if constexpr ((sizeof...(_From) & (sizeof...(_From) - 1))
		    == 0) // power-of-two number of arguments
	return __convert_x86<_To>(__as_vector(__xs)...);
      else
	{
	  using _FF = __first_of_pack_t<_From...>;
	  return __vector_convert<_To>(__xs..., _FF{});
	}
    }
  else
#endif
    return __vector_convert<_To>(
      __xs...,
      make_index_sequence<std::min(_ToT::_S_width, _FromT::_S_width)>());
}

// This overload takes a vectorizable type _To and produces a return type that
// matches the width.
template <typename _To, typename... _From,
	  typename = enable_if_t<__is_vectorizable_v<_To>>,
	  typename _FromT = _VectorTraits<__first_of_pack_t<_From...>>,
	  typename = int>
_GLIBCXX_SIMD_INTRINSIC constexpr _To
__vector_convert(_From... __xs)
{
  return __vector_convert<__vector_type_t<_To, _FromT::_S_width>>(__xs...);
}

// }}}
// __convert function{{{
template <typename _To, typename _From, typename... _More>
_GLIBCXX_SIMD_INTRINSIC constexpr auto
__convert(_From __v0, _More... __vs)
{
  if constexpr (__is_vectorizable_v<_From>)
    {
      static_assert((true && ... && is_same_v<_From, _More>) );
      using _V = typename _VectorTraits<_To>::type;
      using _Tp = typename _VectorTraits<_To>::value_type;
      return _V{static_cast<_Tp>(__v0), static_cast<_Tp>(__vs)...};
    }
  else if constexpr (!__is_vector_type_v<_From>)
    return __convert<_To>(__as_vector(__v0), __as_vector(__vs)...);
  else
    {
      static_assert((true && ... && is_same_v<_From, _More>) );
      if constexpr (__is_vectorizable_v<_To>)
	return __convert<__vector_type_t<_To, (_VectorTraits<_From>::_S_width
					       * (1 + sizeof...(_More)))>>(
	  __v0, __vs...);
      else if constexpr (!__is_vector_type_v<_To>)
	return _To(__convert<typename _To::_BuiltinType>(__v0, __vs...));
      else
	{
	  static_assert(
	    sizeof...(_More) == 0
	      || _VectorTraits<_To>::_S_width
		   >= (1 + sizeof...(_More)) * _VectorTraits<_From>::_S_width,
	    "__convert(...) requires the input to fit into the output");
	  return __vector_convert<_To>(__v0, __vs...);
	}
    }
}

// }}}
// __convert_all{{{
template< std::size_t _Np, typename _ToT, typename _R >
struct __make_array_impl {
  template< typename T >
  auto operator() ( std::initializer_list<T> __xs ) {
    return __call_with_subscripts(
      __xs.begin(), std::make_index_sequence<_Np>(),
      [](auto... __ys) { return _R{__vector_bitcast<_ToT>(__ys)...}; });
  }
};

// Converts __v into std::array<_To, N>, where N is _NParts if non-zero or
// otherwise deduced from _To such that N * #elements(_To) <= #elements(__v).
// Note: this function may return less than all converted elements
template <typename _To,
	  size_t _NParts = 0, // allows to convert fewer or more (only last _To,
			      // to be partially filled) than all
	  size_t _Offset = 0, // where to start, # of elements (not Bytes or
			      // Parts)
	  typename _From, typename _FromVT = _VectorTraits<_From>>
_GLIBCXX_SIMD_INTRINSIC auto
__convert_all(_From __v)
{
  if constexpr (std::is_arithmetic_v<_To> && _NParts != 1)
    {
      static_assert(_Offset < _FromVT::_S_width);
      constexpr auto _Np
	= _NParts == 0 ? _FromVT::_S_partial_width - _Offset : _NParts;
      return __generate_from_n_evaluations<_Np, std::array<_To, _Np>>(
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
      else if constexpr (
	!__have_sse4_1 && _Offset == 0
	&& is_integral_v<
	  typename _FromVT::
	    value_type> && sizeof(typename _FromVT::value_type) < sizeof(typename _ToVT::value_type)
	&& !(sizeof(typename _FromVT::value_type) == 4
	     && is_same_v<typename _ToVT::value_type, double>) )
	{
	  using _ToT = typename _ToVT::value_type;
	  using _FromT = typename _FromVT::value_type;
	  constexpr size_t _Np
	    = _NParts != 0 ? _NParts
			   : (_FromVT::_S_partial_width / _ToVT::_S_width);
	  using _R = std::array<_To, _Np>;
	  // __adjust modifies its input to have _Np (use _SizeConstant) entries
	  // so that no unnecessary intermediate conversions are requested and,
	  // more importantly, no intermediate conversions are missing
	  [[maybe_unused]] auto __adjust
	    = [](auto __n,
		 auto __vv) -> _SimdWrapper<_FromT, decltype(__n)::value> {
	    return __vector_bitcast<_FromT, decltype(__n)::value>(__vv);
	  };
	  [[maybe_unused]] const auto __vi = __to_intrin(__v);

      auto&& __make_array = __make_array_impl<_Np, _ToT, _R>{};

	  if constexpr (_Np == 0)
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
		  const auto __ints
		    = __convert_all<__vector_type16_t<int>, _Np>(
		      __adjust(_SizeConstant<_Np * 4>(), __v));
		  return __generate_from_n_evaluations<_Np, _R>([&](auto __i) {
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
	  else if constexpr (sizeof(_FromT) == 4 && sizeof(_ToT) == 8
			     && is_integral_v<_FromT> && is_integral_v<_ToT>)
	    {
	      if constexpr (is_unsigned_v<_FromT>)
		return __make_array({_mm_unpacklo_epi32(__vi, __m128i()),
				     _mm_unpackhi_epi32(__vi, __m128i())});
	      else
		return __make_array(
		  {_mm_unpacklo_epi32(__vi, _mm_srai_epi32(__vi, 31)),
		   _mm_unpackhi_epi32(__vi, _mm_srai_epi32(__vi, 31))});
	    }
	  else if constexpr (sizeof(_FromT) == 4 && sizeof(_ToT) == 8
			     && is_integral_v<_FromT> && is_integral_v<_ToT>)
	    {
	      if constexpr (is_unsigned_v<_FromT>)
		return __make_array({_mm_unpacklo_epi32(__vi, __m128i()),
				     _mm_unpackhi_epi32(__vi, __m128i())});
	      else
		return __make_array(
		  {_mm_unpacklo_epi32(__vi, _mm_srai_epi32(__vi, 31)),
		   _mm_unpackhi_epi32(__vi, _mm_srai_epi32(__vi, 31))});
	    }
	  else if constexpr (sizeof(_FromT) == 1 && sizeof(_ToT) >= 4
			     && is_signed_v<_FromT>)
	    {
	      const __m128i __vv[2] = {_mm_unpacklo_epi8(__vi, __vi),
				       _mm_unpackhi_epi8(__vi, __vi)};
	      const __vector_type16_t<int> __vvvv[4]
		= {__vector_bitcast<int>(_mm_unpacklo_epi16(__vv[0], __vv[0])),
		   __vector_bitcast<int>(_mm_unpackhi_epi16(__vv[0], __vv[0])),
		   __vector_bitcast<int>(_mm_unpacklo_epi16(__vv[1], __vv[1])),
		   __vector_bitcast<int>(_mm_unpackhi_epi16(__vv[1], __vv[1]))};
	      if constexpr (sizeof(_ToT) == 4)
		return __generate_from_n_evaluations<_Np, _R>([&](auto __i) {
		  return __vector_convert<_To>(__vvvv[__i] >> 24);
		});
	      else if constexpr (is_integral_v<_ToT>)
		return __generate_from_n_evaluations<_Np, _R>([&](auto __i) {
		  const auto __signbits = __to_intrin(__vvvv[__i / 2] >> 31);
		  const auto __sx32 = __to_intrin(__vvvv[__i / 2] >> 24);
		  return __vector_bitcast<_ToT>(
		    __i % 2 == 0 ? _mm_unpacklo_epi32(__sx32, __signbits)
				 : _mm_unpackhi_epi32(__sx32, __signbits));
		});
	      else
		return __generate_from_n_evaluations<_Np, _R>([&](auto __i) {
		  const auto __int4 = __vvvv[__i / 2] >> 24;
		  return __vector_convert<_To>(
		    __i % 2 == 0 ? __int4
				 : __vector_bitcast<int>(
				   _mm_unpackhi_epi64(__to_intrin(__int4),
						      __to_intrin(__int4))));
		});
	    }
	  else if constexpr (sizeof(_FromT) == 1 && sizeof(_ToT) == 4)
	    {
	      const auto __shorts = __convert_all<__vector_type16_t<
		conditional_t<is_signed_v<_FromT>, short, unsigned short>>>(
		__adjust(_SizeConstant<(_Np + 1) / 2 * 8>(), __v));
	      return __generate_from_n_evaluations<_Np, _R>([&](auto __i) {
		return __convert_all<_To>(__shorts[__i / 2])[__i % 2];
	      });
	    }
	  else if constexpr (sizeof(_FromT) == 2 && sizeof(_ToT) == 8
			     && is_signed_v<_FromT> && is_integral_v<_ToT>)
	    {
	      const __m128i __vv[2] = {_mm_unpacklo_epi16(__vi, __vi),
				       _mm_unpackhi_epi16(__vi, __vi)};
	      const __vector_type16_t<int> __vvvv[4]
		= {__vector_bitcast<int>(
		     _mm_unpacklo_epi32(_mm_srai_epi32(__vv[0], 16),
					_mm_srai_epi32(__vv[0], 31))),
		   __vector_bitcast<int>(
		     _mm_unpackhi_epi32(_mm_srai_epi32(__vv[0], 16),
					_mm_srai_epi32(__vv[0], 31))),
		   __vector_bitcast<int>(
		     _mm_unpacklo_epi32(_mm_srai_epi32(__vv[1], 16),
					_mm_srai_epi32(__vv[1], 31))),
		   __vector_bitcast<int>(
		     _mm_unpackhi_epi32(_mm_srai_epi32(__vv[1], 16),
					_mm_srai_epi32(__vv[1], 31)))};
	      return __generate_from_n_evaluations<_Np, _R>(
		[&](auto __i) { return __vector_bitcast<_ToT>(__vvvv[__i]); });
	    }
	  else if constexpr (sizeof(_FromT) <= 2 && sizeof(_ToT) == 8)
	    {
	      const auto __ints = __convert_all<__vector_type16_t<
		conditional_t<is_signed_v<_FromT> || is_floating_point_v<_ToT>,
			      int, unsigned int>>>(
		__adjust(_SizeConstant<(_Np + 1) / 2 * 4>(), __v));
	      return __generate_from_n_evaluations<_Np, _R>([&](auto __i) {
		return __convert_all<_To>(__ints[__i / 2])[__i % 2];
	      });
	    }
	  else
	    __assert_unreachable<_To>();
	}
#endif // _GLIBCXX_SIMD_X86INTRIN }}}
      else if constexpr ((_FromVT::_S_partial_width - _Offset)
			 > _ToVT::_S_width)
	{
	  /*
	  static_assert(
	    (_FromVT::_S_partial_width & (_FromVT::_S_partial_width - 1)) == 0,
	    "__convert_all only supports power-of-2 number of elements.
	  Otherwise " "the return type cannot be std::array<_To, N>.");
	    */
	  constexpr size_t _NTotal
	    = (_FromVT::_S_partial_width - _Offset) / _ToVT::_S_width;
	  constexpr size_t _Np = _NParts == 0 ? _NTotal : _NParts;
	  static_assert(
	    _Np <= _NTotal
	    || (_Np == _NTotal + 1
		&& (_FromVT::_S_partial_width - _Offset) % _ToVT::_S_width
		     > 0));
	  using _R = std::array<_To, _Np>;
	  if constexpr (_Np == 1)
	    return _R{__vector_convert<_To>(
	      __as_vector(__extract_part<_Offset, _FromVT::_S_partial_width,
					 _ToVT::_S_width>(__v)))};
	  else
	    return __generate_from_n_evaluations<_Np, _R>([&](
	      auto __i) constexpr {
	      auto __part
		= __extract_part<__i * _ToVT::_S_width + _Offset,
				 _FromVT::_S_partial_width, _ToVT::_S_width>(
		  __v);
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

// __can_vectorize {{{
template <typename _Tp>
struct __can_vectorize
  : conjunction<
      __is_vectorizable<_Tp>,
      __bool_constant<(
	__have_sse2 || (__have_sse && is_same_v<_Tp, float>) || __have_neon_a64
	|| (__have_neon_a32 && !is_same_v<_Tp, double>)
	|| (__have_neon && sizeof(_Tp) < 8))>>
{
};
template <> struct __can_vectorize<long double> : false_type
{
};

template <typename _Tp>
inline constexpr bool __can_vectorize_v = __can_vectorize<_Tp>::value;

// }}}
// __avx512_is_vectorizable {{{1
template <typename _Tp>
struct __avx512_is_vectorizable
#if _GLIBCXX_SIMD_X86INTRIN // {{{
  : std::conditional_t<__have_avx512bw || (sizeof(_Tp) >= 4 && __have_avx512f),
		       __is_vectorizable<_Tp>, std::false_type>
#else
  : std::false_type
#endif // _GLIBCXX_SIMD_X86INTRIN }}}
{
};
template <> struct __avx512_is_vectorizable<long double> : false_type
{
};

// }}}
// _GnuTraits {{{
template <typename _Tp, typename _Mp, typename _Abi, size_t _Np>
struct _GnuTraits
{
  using _IsValid = true_type;
  using _SimdImpl = typename _Abi::_SimdImpl;
  using _MaskImpl = typename _Abi::_MaskImpl;

  // simd and simd_mask member types {{{
  using _SimdMember = _SimdWrapper<_Tp, _Np>;
  using _MaskMember = _SimdWrapper<_Mp, _Np>;
  static constexpr size_t _S_simd_align = alignof(_SimdMember);
  static constexpr size_t _S_mask_align = alignof(_MaskMember);

  // }}}
  // _SimdBase / base class for simd, providing extra conversions {{{
  struct _SimdBase2
  {
    explicit operator __intrinsic_type_t<_Tp, _Np>() const
    {
      return __to_intrin(static_cast<const simd<_Tp, _Abi>*>(this)->_M_data);
    }
    explicit operator __vector_type_t<_Tp, _Np>() const
    {
      return static_cast<const simd<_Tp, _Abi>*>(this)->_M_data.__builtin();
    }
  };
  struct _SimdBase1
  {
    explicit operator __intrinsic_type_t<_Tp, _Np>() const
    {
      return __data(*static_cast<const simd<_Tp, _Abi>*>(this));
    }
  };
  using _SimdBase
    = std::conditional_t<std::is_same<__intrinsic_type_t<_Tp, _Np>,
				      __vector_type_t<_Tp, _Np>>::value,
			 _SimdBase1, _SimdBase2>;

  // }}}
  // _MaskBase {{{
  struct _MaskBase2
  {
    explicit operator __intrinsic_type_t<_Tp, _Np>() const
    {
      return static_cast<const simd_mask<_Tp, _Abi>*>(this)->_M_data.__intrin();
    }
    explicit operator __vector_type_t<_Tp, _Np>() const
    {
      return static_cast<const simd_mask<_Tp, _Abi>*>(this)->_M_data._M_data;
    }
  };
  struct _MaskBase1
  {
    explicit operator __intrinsic_type_t<_Tp, _Np>() const
    {
      return __data(*static_cast<const simd_mask<_Tp, _Abi>*>(this));
    }
  };
  using _MaskBase
    = std::conditional_t<std::is_same<__intrinsic_type_t<_Tp, _Np>,
				      __vector_type_t<_Tp, _Np>>::value,
			 _MaskBase1, _MaskBase2>;

  // }}}
  // _MaskCastType {{{
  // parameter type of one explicit simd_mask constructor
  class _MaskCastType
  {
    using _Up = __intrinsic_type_t<_Tp, _Np>;
    _Up _M_data;

  public:
    _MaskCastType(_Up __x) : _M_data(__x) {}
    operator _MaskMember() const { return _M_data; }
  };

  // }}}
  // _SimdCastType {{{
  // parameter type of one explicit simd constructor
  class _SimdCastType1
  {
    using _Ap = __intrinsic_type_t<_Tp, _Np>;
    _SimdMember _M_data;

  public:
    _SimdCastType1(_Ap __a) : _M_data(__vector_bitcast<_Tp>(__a)) {}
    operator _SimdMember() const { return _M_data; }
  };

  class _SimdCastType2
  {
    using _Ap = __intrinsic_type_t<_Tp, _Np>;
    using _B = __vector_type_t<_Tp, _Np>;
    _SimdMember _M_data;

  public:
    _SimdCastType2(_Ap __a) : _M_data(__vector_bitcast<_Tp>(__a)) {}
    _SimdCastType2(_B __b) : _M_data(__b) {}
    operator _SimdMember() const { return _M_data; }
  };

  using _SimdCastType
    = std::conditional_t<std::is_same<__intrinsic_type_t<_Tp, _Np>,
				      __vector_type_t<_Tp, _Np>>::value,
			 _SimdCastType1, _SimdCastType2>;
  //}}}
};

// }}}
struct _CommonImplX86;
struct _CommonImplNeon;
struct _CommonImplBuiltin;
template <typename _Abi> struct _SimdImplBuiltin;
template <typename _Abi> struct _MaskImplBuiltin;
template <typename _Abi> struct _SimdImplX86;
template <typename _Abi> struct _MaskImplX86;
template <typename _Abi> struct _SimdImplNeon;
template <typename _Abi> struct _MaskImplNeon;
// simd_abi::_VecBuiltin {{{
template <int _UsedBytes> struct simd_abi::_VecBuiltin
{
  template <typename _Tp>
  static constexpr size_t size = _UsedBytes / sizeof(_Tp);
  template <typename _Tp>
  static constexpr size_t _S_full_size
    = sizeof(__vector_type_t<_Tp, size<_Tp>>) / sizeof(_Tp);
  static constexpr bool _S_is_partial = (_UsedBytes & (_UsedBytes - 1)) != 0;

  // validity traits {{{
  struct _IsValidAbiTag : __bool_constant<(_UsedBytes > 1)>
  {
  };

  template <typename _Tp>
  struct _IsValidSizeFor
    : std::conjunction<
	__bool_constant<(_UsedBytes / sizeof(_Tp) > 1
			 && _UsedBytes % sizeof(_Tp) == 0)>,
	__can_vectorize<_Tp>,
	__bool_constant<(
	  _UsedBytes
	  <= (__have_avx512bw || (__have_avx512f && sizeof(_Tp) >= 4)
		? 64
		: __have_avx2 || (__have_avx && std::is_floating_point_v<_Tp>)
		    ? 32
		    : __have_sse || __have_neon ? 16 : 0))>>
  {
  };
  template <typename _Tp>
  struct _IsValid : std::conjunction<_IsValidAbiTag, __is_vectorizable<_Tp>,
				     _IsValidSizeFor<_Tp>>
  {
  };
  template <typename _Tp>
  static constexpr bool _S_is_valid_v = _IsValid<_Tp>::value;

  // }}}
  // _SimdImpl/_MaskImpl {{{
#if _GLIBCXX_SIMD_X86INTRIN
  using _CommonImpl = _CommonImplX86;
  using _SimdImpl = _SimdImplX86<_VecBuiltin<_UsedBytes>>;
  using _MaskImpl = _MaskImplX86<_VecBuiltin<_UsedBytes>>;
#elif _GLIBCXX_SIMD_HAVE_NEON
  using _CommonImpl = _CommonImplNeon;
  using _SimdImpl = _SimdImplNeon<_VecBuiltin<_UsedBytes>>;
  using _MaskImpl = _MaskImplNeon<_VecBuiltin<_UsedBytes>>;
#else
  using _CommonImpl = _CommonImplBuiltin;
  using _SimdImpl = _SimdImplBuiltin<_VecBuiltin<_UsedBytes>>;
  using _MaskImpl = _MaskImplBuiltin<_VecBuiltin<_UsedBytes>>;
#endif

  // }}}
  // __traits {{{
  template <typename _Tp>
  using __traits = std::conditional_t<
    _S_is_valid_v<_Tp>,
    _GnuTraits<_Tp, _Tp, _VecBuiltin<_UsedBytes>, size<_Tp>>, _InvalidTraits>;
  //}}}
  // implicit masks {{{
  template <typename _Tp>
  static constexpr _SimdWrapper<_Tp, size<_Tp>> __implicit_mask()
  {
    constexpr auto __size = _S_full_size<_Tp>;
    using _ImplicitMask = __vector_type_t<__int_for_sizeof_t<_Tp>, __size>;
    return reinterpret_cast<__vector_type_t<_Tp, __size>>(
      !_S_is_partial ? ~_ImplicitMask()
		     : __generate_vector<_ImplicitMask>([](auto __i) constexpr {
			 return __i < _UsedBytes / sizeof(_Tp) ? -1 : 0;
		       }));
  }

  template <typename _Tp, typename _TVT = _VectorTraits<_Tp>>
  static constexpr _Tp __masked(_Tp __x)
  {
    using _Up = typename _TVT::value_type;
    if constexpr (_S_is_partial)
      return __and(__as_vector(__x), __implicit_mask<_Up>()._M_data);
    else
      return __x;
  }

  template <typename _Tp, typename _TVT = _VectorTraits<_Tp>>
  static constexpr auto __make_padding_nonzero(_Tp __x)
  {
    if constexpr (!_S_is_partial)
      return __x;
    else
      {
	using _Up = typename _TVT::value_type;
	if constexpr (std::is_integral_v<_Up>)
	  return __or(__x, ~__implicit_mask<_Up>()._M_data);
	else
	  {
	    constexpr auto __one
	      = __andnot(__implicit_mask<_Up>()._M_data,
			 __vector_broadcast<_S_full_size<_Up>>(_Up(1)));
	    return __or(__x, __one);
	  }
      }
  }
  // }}}
};

// }}}
// simd_abi::_VecBltnBtmsk {{{
template <int _UsedBytes> struct simd_abi::_VecBltnBtmsk
{
  template <typename _Tp>
  static constexpr size_t size = _UsedBytes / sizeof(_Tp);
  template <typename _Tp>
  static constexpr size_t _S_full_size
    = sizeof(__vector_type_t<_Tp, size<_Tp>>) / sizeof(_Tp);
  static constexpr bool _S_is_partial = (_UsedBytes & (_UsedBytes - 1)) != 0;

  // validity traits {{{
  struct _IsValidAbiTag : __bool_constant<(_UsedBytes > 1)>
  {
  };
  template <typename _Tp>
  struct _IsValidSizeFor
    : __bool_constant<(_UsedBytes / sizeof(_Tp) > 1
		       && _UsedBytes % sizeof(_Tp) == 0 && _UsedBytes <= 64
		       && (_UsedBytes > 32 || __have_avx512vl))>
  {
  };
  template <typename _Tp>
  struct _IsValid : conjunction<_IsValidAbiTag, __avx512_is_vectorizable<_Tp>,
				_IsValidSizeFor<_Tp>>
  {
  };
  template <typename _Tp>
  static constexpr bool _S_is_valid_v = _IsValid<_Tp>::value;

  // }}}
  // implicit mask {{{
private:
  template <typename _Tp> using _ImplicitMask = _SimdWrapper<bool, size<_Tp>>;

public:
  template <size_t _Np>
  _GLIBCXX_SIMD_INTRINSIC static constexpr __bool_storage_member_type_t<_Np>
  __implicit_mask_n()
  {
    using _Tp = __bool_storage_member_type_t<_Np>;
    return _Np < sizeof(_Tp) * CHAR_BIT ? _Tp((1ULL << _Np) - 1) : ~_Tp();
  }

  template <typename _Tp>
  _GLIBCXX_SIMD_INTRINSIC static constexpr _ImplicitMask<_Tp> __implicit_mask()
  {
    return __implicit_mask_n<size<_Tp>>();
  }

  template <typename _Tp, size_t _Np>
  _GLIBCXX_SIMD_INTRINSIC static constexpr _SimdWrapper<_Tp, _Np>
  __masked(_SimdWrapper<_Tp, _Np> __x)
  {
    if constexpr (is_same_v<_Tp, bool>)
      if constexpr (_S_is_partial || _Np < 8)
	return _MaskImpl::__bit_and(__x, _SimdWrapper<_Tp, _Np>(
					   __bool_storage_member_type_t<_Np>(
					     (1ULL << _Np) - 1)));
      else
	return __x;
    else
      return __masked(__x._M_data);
  }

  template <typename _TV>
  _GLIBCXX_SIMD_INTRINSIC static constexpr _TV __masked(_TV __x)
  {
    static_assert(
      !__is_bitmask_v<_TV>,
      "_VecBltnBtmsk::__masked cannot work on bitmasks, since it doesn't "
      "know the number of elements. Use _SimdWrapper<bool, N> instead.");
    if constexpr (_S_is_partial)
      {
	using _Tp = typename _VectorTraits<_TV>::value_type;
	constexpr size_t _Np = size<_Tp>;
	return __make_dependent_t<_TV, _CommonImpl>::_S_blend(
	  __implicit_mask<_Tp>(), _SimdWrapper<_Tp, _Np>(),
	  _SimdWrapper<_Tp, _Np>(__x));
      }
    else
      return __x;
  }

  template <typename _TV, typename _TVT = _VectorTraits<_TV>>
  static constexpr auto __make_padding_nonzero(_TV __x)
  {
    if constexpr (!_S_is_partial)
      return __x;
    else
      {
	using _Tp = typename _TVT::value_type;
	constexpr size_t _Np = size<_Tp>;
	if constexpr (is_integral_v<typename _TVT::value_type>)
	  return __x
		 | __generate_vector<_Tp, _S_full_size<_Tp>>(
		   [](auto __i) -> _Tp {
		     if (__i < _Np)
		       return 0;
		     else
		       return 1;
		   });
	else
	  return __make_dependent_t<_TV, _CommonImpl>::_S_blend(
		   __implicit_mask<_Tp>(),
		   _SimdWrapper<_Tp, _Np>(
		     __vector_broadcast<_S_full_size<_Tp>>(_Tp(1))),
		   _SimdWrapper<_Tp, _Np>(__x))
	    ._M_data;
      }
  }

  // }}}
  // simd/_MaskImpl {{{
#if _GLIBCXX_SIMD_X86INTRIN
  using _CommonImpl = _CommonImplX86;
  using _SimdImpl = _SimdImplX86<_VecBltnBtmsk<_UsedBytes>>;
  using _MaskImpl = _MaskImplX86<_VecBltnBtmsk<_UsedBytes>>;
#else
  template <int> struct _MissingImpl;
  using _CommonImpl = _MissingImpl<_UsedBytes>;
  using _SimdImpl = _MissingImpl<_UsedBytes>;
  using _MaskImpl = _MissingImpl<_UsedBytes>;
#endif

  // }}}
  // __traits {{{
  template <typename _Tp>
  using __traits = std::conditional_t<
    _S_is_valid_v<_Tp>,
    _GnuTraits<_Tp, bool, _VecBltnBtmsk<_UsedBytes>, size<_Tp>>,
    _InvalidTraits>;
  //}}}
};

//}}}
// _CommonImplBuiltin {{{
struct _CommonImplBuiltin
{
  // __converts_via_decomposition{{{
  // This lists all cases where a __vector_convert needs to fall back to
  // conversion of individual scalars (i.e. decompose the input vector into
  // scalars, convert, compose output vector). In those cases, __masked_load &
  // __masked_store prefer to use the __bit_iteration implementation.
  template <typename _From, typename _To, size_t _ToSize>
  static inline constexpr bool __converts_via_decomposition_v
    = sizeof(_From) != sizeof(_To);

  // }}}
  // _S_load{{{
  template <typename _Tp, size_t _Np, size_t _M = _Np * sizeof(_Tp),
	    typename _Fp>
  _GLIBCXX_SIMD_INTRINSIC static __vector_type_t<_Tp, _Np>
  _S_load(const void* __p, _Fp)
  {
    static_assert(_Np > 1);
    static_assert(_M % sizeof(_Tp) == 0);
#ifdef _GLIBCXX_SIMD_WORKAROUND_PR90424
    using _Up = conditional_t<
      is_integral_v<_Tp>,
      conditional_t<_M % 4 == 0, conditional_t<_M % 8 == 0, long long, int>,
		    conditional_t<_M % 2 == 0, short, signed char>>,
      conditional_t<(_M < 8 || _Np % 2 == 1 || _Np == 2), _Tp, double>>;
    using _V = __vector_type_t<_Up, _Np * sizeof(_Tp) / sizeof(_Up)>;
#else  // _GLIBCXX_SIMD_WORKAROUND_PR90424
    using _V = __vector_type_t<_Tp, _Np>;
#endif // _GLIBCXX_SIMD_WORKAROUND_PR90424
    _V __r{};
    static_assert(_M <= sizeof(_V));
    if constexpr (std::is_same_v<_Fp, vector_aligned_tag>)
      __p = __builtin_assume_aligned(__p, alignof(__vector_type_t<_Tp, _Np>));
    else if constexpr (!std::is_same_v<_Fp, element_aligned_tag>)
      __p = __builtin_assume_aligned(__p, _Fp::_S_alignment);

    __builtin_memcpy(&__r, __p, _M);
    return reinterpret_cast<__vector_type_t<_Tp, _Np>>(__r);
  }

  // }}}
  // __store {{{
  template <size_t _ReqBytes = 0, typename _Flags, typename _TV>
  _GLIBCXX_SIMD_INTRINSIC static void __store(_TV __x, void* __addr, _Flags)
  {
    constexpr size_t _Bytes = _ReqBytes == 0 ? sizeof(__x) : _ReqBytes;
    static_assert(sizeof(__x) >= _Bytes);

    if constexpr (std::is_same_v<_Flags, vector_aligned_tag>)
      __addr = __builtin_assume_aligned(__addr, alignof(_TV));
    else if constexpr (!std::is_same_v<_Flags, element_aligned_tag>)
      __addr = __builtin_assume_aligned(__addr, _Flags::_S_alignment);

    if constexpr (__is_vector_type_v<_TV>)
      {
	using _Tp = typename _VectorTraits<_TV>::value_type;
	constexpr size_t _Np = _Bytes / sizeof(_Tp);
	static_assert(_Np * sizeof(_Tp) == _Bytes);

#ifdef _GLIBCXX_SIMD_WORKAROUND_PR90424
	using _Up = std::conditional_t<
	  (std::is_integral_v<_Tp> || _Bytes < 4),
	  std::conditional_t<(sizeof(__x) > sizeof(long long)), long long, _Tp>,
	  float>;
	const auto __v = __vector_bitcast<_Up>(__x);
#else  // _GLIBCXX_SIMD_WORKAROUND_PR90424
	const __vector_type_t<_Tp, _Np> __v = __x;
#endif // _GLIBCXX_SIMD_WORKAROUND_PR90424

	if constexpr ((_Bytes & (_Bytes - 1)) != 0)
	  {
	    constexpr size_t _MoreBytes = __next_power_of_2(_Bytes);
	    alignas(decltype(__v)) char __tmp[_MoreBytes];
	    __builtin_memcpy(__tmp, &__v, _MoreBytes);
	    __builtin_memcpy(__addr, __tmp, _Bytes);
	  }
	else
	  __builtin_memcpy(__addr, &__v, _Bytes);
      }
    else
      __builtin_memcpy(__addr, &__x, _Bytes);
  }

  template <typename _Flags, typename _Tp, size_t _Np>
  _GLIBCXX_SIMD_INTRINSIC static void __store(_SimdWrapper<_Tp, _Np> __x,
					      void* __addr, _Flags)
  {
    __store<_Np * sizeof(_Tp)>(__x._M_data, __addr, _Flags());
  }

  // }}}
  // __store_bool_array(_BitMask) {{{
  template <size_t _Np, typename _Flags, bool _Sanitized>
  _GLIBCXX_SIMD_INTRINSIC static constexpr void
  __store_bool_array(_BitMask<_Np, _Sanitized> __x, bool* __mem, _Flags)
  {
    if constexpr (_Np == 1)
      __mem[0] = __x[0];
    else if constexpr (_Np == 2)
      {
	short __bool2 = (__x._M_to_bits() * 0x81) & 0x0101;
	__store<_Np>(__bool2, __mem, _Flags());
      }
    else if constexpr (_Np == 3)
      {
	int __bool3 = (__x._M_to_bits() * 0x4081) & 0x010101;
	__store<_Np>(__bool3, __mem, _Flags());
      }
    else
      {
	__execute_n_times<__div_roundup(_Np, 4)>([&](auto __i) {
	  constexpr int __offset = __i * 4;
	  constexpr int __remaining = _Np - __offset;
	  if constexpr (__remaining > 4 && __remaining <= 7)
	    {
	      const _ULLong __bool7
		= (__x.template _M_extract<__offset>()._M_to_bits()
		   * 0x40810204081ULL)
		  & 0x0101010101010101ULL;
	      __store<__remaining>(__bool7, __mem + __offset, _Flags());
	    }
	  else if constexpr (__remaining >= 4)
	    {
	      int __bits = __x.template _M_extract<__offset>()._M_to_bits();
	      if constexpr (__remaining > 7)
		__bits &= 0xf;
	      const int __bool4 = (__bits * 0x204081) & 0x01010101;
	      __store<4>(__bool4, __mem + __offset, _Flags());
	    }
	});
      }
  }

  // }}}
  // _S_blend{{{
  template <typename _Tp, size_t _Np>
  _GLIBCXX_SIMD_INTRINSIC static constexpr auto
  _S_blend(_SimdWrapper<_Tp, _Np> __k, _SimdWrapper<_Tp, _Np> __at0,
	   _SimdWrapper<_Tp, _Np> __at1)
  {
    return __vector_bitcast<__int_for_sizeof_t<_Tp>>(__k) ? __at1._M_data
							  : __at0._M_data;
  }

  // }}}
};

// }}}
// _SimdImplBuiltin {{{1
template <typename _Abi> struct _SimdImplBuiltin
{
  // member types {{{2
  template <typename _Tp> static constexpr size_t _S_max_store_size = 16;
  using abi_type = _Abi;
  template <typename _Tp> using _TypeTag = _Tp*;
  template <typename _Tp>
  using _SimdMember = typename _Abi::template __traits<_Tp>::_SimdMember;
  template <typename _Tp>
  using _MaskMember = typename _Abi::template __traits<_Tp>::_MaskMember;
  template <typename _Tp>
  static constexpr size_t _S_size = _Abi::template size<_Tp>;
  template <typename _Tp>
  static constexpr size_t _S_full_size = _Abi::template _S_full_size<_Tp>;
  using _CommonImpl = typename _Abi::_CommonImpl;
  using _SuperImpl = typename _Abi::_SimdImpl;
  using _MaskImpl = typename _Abi::_MaskImpl;

  // __make_simd(_SimdWrapper/__intrinsic_type_t) {{{2
  template <typename _Tp, size_t _Np>
  _GLIBCXX_SIMD_INTRINSIC static simd<_Tp, _Abi>
  __make_simd(_SimdWrapper<_Tp, _Np> __x)
  {
    return {__private_init, __x};
  }
  template <typename _Tp, size_t _Np>
  _GLIBCXX_SIMD_INTRINSIC static simd<_Tp, _Abi>
  __make_simd(__intrinsic_type_t<_Tp, _Np> __x)
  {
    return {__private_init, __vector_bitcast<_Tp>(__x)};
  }

  // __broadcast {{{2
  template <typename _Tp>
  _GLIBCXX_SIMD_INTRINSIC static constexpr _SimdMember<_Tp>
  __broadcast(_Tp __x) noexcept
  {
    return __vector_broadcast<_S_full_size<_Tp>>(__x);
  }

  // __generator {{{2
  template <typename _Fp, typename _Tp>
  inline static constexpr _SimdMember<_Tp> __generator(_Fp&& __gen,
						       _TypeTag<_Tp>)
  {
    return __generate_vector<_Tp, _S_full_size<_Tp>>([&](auto __i) constexpr {
      if constexpr (__i < _S_size<_Tp>)
	return __gen(__i);
      else
	return 0;
    });
  }

  // __load {{{2
  template <typename _Tp, typename _Up, typename _Fp>
  _GLIBCXX_SIMD_INTRINSIC static _SimdMember<_Tp> __load(const _Up* __mem, _Fp,
							 _TypeTag<_Tp>) noexcept
  {
    constexpr size_t _Np = _S_size<_Tp>;
    constexpr size_t __max_load_size
      = (sizeof(_Up) >= 4 && __have_avx512f) || __have_avx512bw
	  ? 64
	  : (std::is_floating_point_v<_Up> && __have_avx) || __have_avx2 ? 32
									 : 16;
    constexpr size_t __bytes_to_load = sizeof(_Up) * _Np;
    if constexpr (sizeof(_Up) > 8)
      return __generate_vector<_Tp, _SimdMember<_Tp>::_S_width>([&](
	auto __i) constexpr {
	return static_cast<_Tp>(__i < _Np ? __mem[__i] : 0);
      });
    else if constexpr (std::is_same_v<_Up, _Tp>)
      return _CommonImpl::template _S_load<_Tp, _S_full_size<_Tp>,
					   _Np * sizeof(_Tp)>(__mem, _Fp());
    else if constexpr (__bytes_to_load <= __max_load_size)
      return __convert<_SimdMember<_Tp>>(
	_CommonImpl::template _S_load<_Up, _Np>(__mem, _Fp()));
    else if constexpr (__bytes_to_load % __max_load_size == 0)
      {
	constexpr size_t __n_loads = __bytes_to_load / __max_load_size;
	constexpr size_t __elements_per_load = _Np / __n_loads;
	return __call_with_n_evaluations<__n_loads>(
	  [](auto... __uncvted) {
	    return __convert<_SimdMember<_Tp>>(__uncvted...);
	  },
	  [&](auto __i) {
	    return _CommonImpl::template _S_load<_Up, __elements_per_load>(
	      __mem + __i * __elements_per_load, _Fp());
	  });
      }
    else if constexpr (__bytes_to_load % (__max_load_size / 2) == 0
		       && __max_load_size > 16)
      { // e.g. int[] -> <char, 12> with AVX2
	constexpr size_t __n_loads = __bytes_to_load / (__max_load_size / 2);
	constexpr size_t __elements_per_load = _Np / __n_loads;
	return __call_with_n_evaluations<__n_loads>(
	  [](auto... __uncvted) {
	    return __convert<_SimdMember<_Tp>>(__uncvted...);
	  },
	  [&](auto __i) {
	    return _CommonImpl::template _S_load<_Up, __elements_per_load>(
	      __mem + __i * __elements_per_load, _Fp());
	  });
      }
    else // e.g. int[] -> <char, 9>
      return __call_with_subscripts(
	__mem, make_index_sequence<_Np>(), [](auto... __args) {
	  return __vector_type_t<_Tp, _S_full_size<_Tp>>{
	    static_cast<_Tp>(__args)...};
	});
  }

  // __masked_load {{{2
  template <typename _Tp, size_t _Np, typename _Up, typename _Fp>
  static inline _SimdWrapper<_Tp, _Np>
  __masked_load(_SimdWrapper<_Tp, _Np> __merge, _MaskMember<_Tp> __k,
		const _Up* __mem, _Fp) noexcept
  {
    _BitOps::__bit_iteration(_MaskImpl::__to_bits(__k), [&](auto __i) {
      __merge.__set(__i, static_cast<_Tp>(__mem[__i]));
    });
    return __merge;
  }

  // __store {{{2
  template <typename _Tp, typename _Up, typename _Fp>
  _GLIBCXX_SIMD_INTRINSIC static void __store(_SimdMember<_Tp> __v, _Up* __mem,
					      _Fp, _TypeTag<_Tp>) noexcept
  {
    // TODO: converting int -> "smaller int" can be optimized with AVX512
    constexpr size_t _Np = _S_size<_Tp>;
    constexpr size_t __max_store_size
      = _SuperImpl::template _S_max_store_size<_Up>;
    if constexpr (sizeof(_Up) > 8)
      __execute_n_times<_Np>([&](auto __i) constexpr {
	__mem[__i] = __v[__i];
      });
    else if constexpr (std::is_same_v<_Up, _Tp>)
      _CommonImpl::__store(__v, __mem, _Fp());
    else if constexpr (sizeof(_Up) * _Np <= __max_store_size)
      _CommonImpl::__store(_SimdWrapper<_Up, _Np>(__convert<_Up>(__v)), __mem,
			   _Fp());
    else
      {
	constexpr size_t __vsize = __max_store_size / sizeof(_Up);
	// round up to convert the last partial vector as well:
	constexpr size_t __stores = __div_roundup(_Np, __vsize);
	constexpr size_t __full_stores = _Np / __vsize;
	using _V = __vector_type_t<_Up, __vsize>;
	const std::array<_V, __stores> __converted
	  = __convert_all<_V, __stores>(__v);
	__execute_n_times<__full_stores>([&](auto __i) constexpr {
	  _CommonImpl::__store(__converted[__i], __mem + __i * __vsize, _Fp());
	});
	if constexpr (__full_stores < __stores)
	  _CommonImpl::template __store<(_Np - __full_stores * __vsize)
					* sizeof(_Up)>(
	    __converted[__full_stores], __mem + __full_stores * __vsize, _Fp());
      }
  }

  // __masked_store_nocvt {{{2
  template <typename _Tp, std::size_t _Np, typename _Fp>
  _GLIBCXX_SIMD_INTRINSIC static void
  __masked_store_nocvt(_SimdWrapper<_Tp, _Np> __v, _Tp* __mem, _Fp,
		       _SimdWrapper<_Tp, _Np> __k)
  {
    _BitOps::__bit_iteration(
      _MaskImpl::__to_bits(__k), [&](auto __i) constexpr {
	__mem[__i] = __v[__i];
      });
  }

  // __masked_store {{{2
  template <typename _TW, typename _TVT = _VectorTraits<_TW>,
	    typename _Tp = typename _TVT::value_type, typename _Up,
	    typename _Fp>
  static inline void __masked_store(const _TW __v, _Up* __mem, _Fp,
				    const _MaskMember<_Tp> __k) noexcept
  {
    constexpr size_t _TV_size = _S_size<_Tp>;
    [[maybe_unused]] const auto __vi = __to_intrin(__v);
    constexpr size_t __max_store_size
      = _SuperImpl::template _S_max_store_size<_Up>;
    if constexpr (
      std::is_same_v<
	_Tp,
	_Up> || (std::is_integral_v<_Tp> && std::is_integral_v<_Up> && sizeof(_Tp) == sizeof(_Up)))
      {
	// bitwise or no conversion, reinterpret:
	const auto __kk = [&]() {
	  if constexpr (__is_bitmask_v<decltype(__k)>)
	    return _MaskMember<_Up>(__k._M_data);
	  else
	    return __wrapper_bitcast<_Up>(__k);
	}();
	_SuperImpl::__masked_store_nocvt(__wrapper_bitcast<_Up>(__v), __mem,
					 _Fp(), __kk);
      }
    else if constexpr (
      __can_vectorize_v<
	_Up> && !_CommonImpl::template __converts_via_decomposition_v<_Tp, _Up, __max_store_size>)
      { // conversion via decomposition is better handled via the bit_iteration
	// fallback below
	constexpr size_t _UW_size
	  = std::min(_TV_size, __max_store_size / sizeof(_Up));
	static_assert(_UW_size <= _TV_size);
	using _UW = _SimdWrapper<_Up, _UW_size>;
	using _UV = __vector_type_t<_Up, _UW_size>;
	using _UAbi = simd_abi::deduce_t<_Up, _UW_size>;
	if constexpr (_UW_size == _TV_size) // one convert+store
	  {
	    const _UW __converted = __convert<_UW>(__v);
	    _SuperImpl::__masked_store_nocvt(
	      __converted, __mem, _Fp(),
	      _UAbi::_MaskImpl::template __convert<_Up>(__k));
	  }
	else
	  {
	    static_assert(_UW_size * sizeof(_Up) == __max_store_size);
	    constexpr size_t _NFullStores = _TV_size / _UW_size;
	    constexpr size_t _NAllStores = __div_roundup(_TV_size, _UW_size);
	    constexpr size_t _NParts = _S_full_size<_Tp> / _UW_size;
	    const std::array<_UV, _NAllStores> __converted
	      = __convert_all<_UV, _NAllStores>(__v);
	    __execute_n_times<_NFullStores>([&](auto __i) {
	      _SuperImpl::__masked_store_nocvt(
		_UW(__converted[__i]), __mem + __i * _UW_size, _Fp(),
		_UAbi::_MaskImpl::template __convert<_Up>(
		  __extract_part<__i, _NParts>(__k.__as_full_vector())));
	    });
	    if constexpr (_NAllStores > _NFullStores) // one partial at the end
	      _SuperImpl::__masked_store_nocvt(
		_UW(__converted[_NFullStores]), __mem + _NFullStores * _UW_size,
		_Fp(),
		_UAbi::_MaskImpl::template __convert<_Up>(
		  __extract_part<_NFullStores, _NParts>(
		    __k.__as_full_vector())));
	  }
      }
    else
      _BitOps::__bit_iteration(
	_MaskImpl::__to_bits(__k), [&](auto __i) constexpr {
	  __mem[__i] = static_cast<_Up>(__v[__i]);
	});
  }

  // __complement {{{2
  template <typename _Tp, size_t _Np>
  _GLIBCXX_SIMD_INTRINSIC static constexpr _SimdWrapper<_Tp, _Np>
  __complement(_SimdWrapper<_Tp, _Np> __x) noexcept
  {
    return ~__x._M_data;
  }

  // __unary_minus {{{2
  template <typename _Tp, size_t _Np>
  _GLIBCXX_SIMD_INTRINSIC static constexpr _SimdWrapper<_Tp, _Np>
  __unary_minus(_SimdWrapper<_Tp, _Np> __x) noexcept
  {
    // GCC doesn't use the psign instructions, but pxor & psub seem to be just
    // as good a choice as pcmpeqd & psign. So meh.
    return -__x._M_data;
  }

  // arithmetic operators {{{2
  template <typename _Tp, size_t _Np>
  _GLIBCXX_SIMD_INTRINSIC static constexpr _SimdWrapper<_Tp, _Np>
  __plus(_SimdWrapper<_Tp, _Np> __x, _SimdWrapper<_Tp, _Np> __y)
  {
    return __x._M_data + __y._M_data;
  }
  template <typename _Tp, size_t _Np>
  _GLIBCXX_SIMD_INTRINSIC static constexpr _SimdWrapper<_Tp, _Np>
  __minus(_SimdWrapper<_Tp, _Np> __x, _SimdWrapper<_Tp, _Np> __y)
  {
    return __x._M_data - __y._M_data;
  }
  template <typename _Tp, size_t _Np>
  _GLIBCXX_SIMD_INTRINSIC static constexpr _SimdWrapper<_Tp, _Np>
  __multiplies(_SimdWrapper<_Tp, _Np> __x, _SimdWrapper<_Tp, _Np> __y)
  {
    return __x._M_data * __y._M_data;
  }
  template <typename _Tp, size_t _Np>
  _GLIBCXX_SIMD_INTRINSIC static constexpr _SimdWrapper<_Tp, _Np>
  __divides(_SimdWrapper<_Tp, _Np> __x, _SimdWrapper<_Tp, _Np> __y)
  {
    // Note that division by 0 is always UB, so we must ensure we avoid the
    // case for partial registers
    if constexpr (!_Abi::_S_is_partial)
      return __x._M_data / __y._M_data;
    else
      return __as_vector(__x) / _Abi::__make_padding_nonzero(__as_vector(__y));
  }
  template <typename _Tp, size_t _Np>
  _GLIBCXX_SIMD_INTRINSIC static constexpr _SimdWrapper<_Tp, _Np>
  __modulus(_SimdWrapper<_Tp, _Np> __x, _SimdWrapper<_Tp, _Np> __y)
  {
    if constexpr (!_Abi::_S_is_partial)
      return __x._M_data % __y._M_data;
    else
      return __as_vector(__x) % _Abi::__make_padding_nonzero(__as_vector(__y));
  }
  template <typename _Tp, size_t _Np>
  _GLIBCXX_SIMD_INTRINSIC static constexpr _SimdWrapper<_Tp, _Np>
  __bit_and(_SimdWrapper<_Tp, _Np> __x, _SimdWrapper<_Tp, _Np> __y)
  {
    return __and(__x, __y);
  }
  template <typename _Tp, size_t _Np>
  _GLIBCXX_SIMD_INTRINSIC static constexpr _SimdWrapper<_Tp, _Np>
  __bit_or(_SimdWrapper<_Tp, _Np> __x, _SimdWrapper<_Tp, _Np> __y)
  {
    return __or(__x, __y);
  }
  template <typename _Tp, size_t _Np>
  _GLIBCXX_SIMD_INTRINSIC static constexpr _SimdWrapper<_Tp, _Np>
  __bit_xor(_SimdWrapper<_Tp, _Np> __x, _SimdWrapper<_Tp, _Np> __y)
  {
    return __xor(__x, __y);
  }
  template <typename _Tp, size_t _Np>
  _GLIBCXX_SIMD_INTRINSIC static _SimdWrapper<_Tp, _Np>
  __bit_shift_left(_SimdWrapper<_Tp, _Np> __x, _SimdWrapper<_Tp, _Np> __y)
  {
    return __x._M_data << __y._M_data;
  }
  template <typename _Tp, size_t _Np>
  _GLIBCXX_SIMD_INTRINSIC static _SimdWrapper<_Tp, _Np>
  __bit_shift_right(_SimdWrapper<_Tp, _Np> __x, _SimdWrapper<_Tp, _Np> __y)
  {
#ifdef _GLIBCXX_SIMD_WORKAROUND_XXX_5
    if constexpr (sizeof(_Tp) == 8)
      return __generate_vector<__vector_type_t<_Tp, _Np>>([&](auto __i) {
	return __x._M_data[__i.value] >> __y._M_data[__i.value];
      });
    else
#endif
      return __x._M_data >> __y._M_data;
  }

  template <typename _Tp, size_t _Np>
  _GLIBCXX_SIMD_INTRINSIC static constexpr _SimdWrapper<_Tp, _Np>
  __bit_shift_left(_SimdWrapper<_Tp, _Np> __x, int __y)
  {
    return __x._M_data << __y;
  }
  template <typename _Tp, size_t _Np>
  _GLIBCXX_SIMD_INTRINSIC static constexpr _SimdWrapper<_Tp, _Np>
  __bit_shift_right(_SimdWrapper<_Tp, _Np> __x, int __y)
  {
    // work around PR91838
    if (__builtin_constant_p(__y)
	&& __y >= static_cast<int>(sizeof(_Tp) * CHAR_BIT)
	&& is_unsigned_v<_Tp>)
      return _SimdWrapper<_Tp, _Np>{};
    else
      return __x._M_data >> __y;
  }

  // compares {{{2
  // __equal_to {{{3
  template <typename _Tp, size_t _Np>
  _GLIBCXX_SIMD_INTRINSIC static constexpr _MaskMember<_Tp>
  __equal_to(_SimdWrapper<_Tp, _Np> __x, _SimdWrapper<_Tp, _Np> __y)
  {
    return __vector_bitcast<_Tp>(__x._M_data == __y._M_data);
  }

  // __not_equal_to {{{3
  template <typename _Tp, size_t _Np>
  _GLIBCXX_SIMD_INTRINSIC static constexpr _MaskMember<_Tp>
  __not_equal_to(_SimdWrapper<_Tp, _Np> __x, _SimdWrapper<_Tp, _Np> __y)
  {
    return __vector_bitcast<_Tp>(__x._M_data != __y._M_data);
  }

  // __less {{{3
  template <typename _Tp, size_t _Np>
  _GLIBCXX_SIMD_INTRINSIC static constexpr _MaskMember<_Tp>
  __less(_SimdWrapper<_Tp, _Np> __x, _SimdWrapper<_Tp, _Np> __y)
  {
    return __vector_bitcast<_Tp>(__x._M_data < __y._M_data);
  }

  // __less_equal {{{3
  template <typename _Tp, size_t _Np>
  _GLIBCXX_SIMD_INTRINSIC static constexpr _MaskMember<_Tp>
  __less_equal(_SimdWrapper<_Tp, _Np> __x, _SimdWrapper<_Tp, _Np> __y)
  {
    return __vector_bitcast<_Tp>(__x._M_data <= __y._M_data);
  }

  // negation {{{2
  template <typename _Tp, size_t _Np>
  _GLIBCXX_SIMD_INTRINSIC static constexpr _MaskMember<_Tp>
  __negate(_SimdWrapper<_Tp, _Np> __x) noexcept
  {
#if !defined __clang__
    return __vector_bitcast<_Tp>(!__x._M_data);
#else
    return __vector_bitcast<_Tp>(__x._M_data == decltype(__x._M_data){});
#endif
  }

  // __min, __max, __minmax {{{2
  template <typename _Tp, size_t _Np>
  _GLIBCXX_SIMD_NORMAL_MATH
    _GLIBCXX_SIMD_INTRINSIC static constexpr _SimdWrapper<_Tp, _Np>
    __min(_SimdWrapper<_Tp, _Np> __a, _SimdWrapper<_Tp, _Np> __b)
  {
    return __a._M_data < __b._M_data ? __a._M_data : __b._M_data;
  }
  template <typename _Tp, size_t _Np>
  _GLIBCXX_SIMD_NORMAL_MATH
    _GLIBCXX_SIMD_INTRINSIC static constexpr _SimdWrapper<_Tp, _Np>
    __max(_SimdWrapper<_Tp, _Np> __a, _SimdWrapper<_Tp, _Np> __b)
  {
    return __a._M_data > __b._M_data ? __a._M_data : __b._M_data;
  }

  template <typename _Tp, size_t _Np>
  _GLIBCXX_SIMD_NORMAL_MATH
    _GLIBCXX_SIMD_INTRINSIC static constexpr std::pair<_SimdWrapper<_Tp, _Np>,
						       _SimdWrapper<_Tp, _Np>>
    __minmax(_SimdWrapper<_Tp, _Np> __a, _SimdWrapper<_Tp, _Np> __b)
  {
    return {__a._M_data < __b._M_data ? __a._M_data : __b._M_data,
	    __a._M_data < __b._M_data ? __b._M_data : __a._M_data};
  }

  // reductions {{{2
  template <size_t _Np, size_t... _Is, size_t... _Zeros, typename _Tp,
	    typename _BinaryOperation>
  _GLIBCXX_SIMD_INTRINSIC static _Tp
  __reduce_partial(std::index_sequence<_Is...>, std::index_sequence<_Zeros...>,
		   simd<_Tp, _Abi> __x, _BinaryOperation&& __binary_op)
  {
    using _V = __vector_type_t<_Tp, _Np / 2>;
    static_assert(sizeof(_V) <= sizeof(__x));
    // _S_width is the size of the smallest native SIMD register that can
    // store _Np/2 elements:
    using _FullSimd = __deduced_simd<_Tp, _VectorTraits<_V>::_S_width>;
    using _HalfSimd = __deduced_simd<_Tp, _Np / 2>;
    const auto __xx = __as_vector(__x);
    return _HalfSimd::abi_type::_SimdImpl::__reduce(
      static_cast<_HalfSimd>(__as_vector(__binary_op(
	static_cast<_FullSimd>(__intrin_bitcast<_V>(__xx)),
	static_cast<_FullSimd>(__intrin_bitcast<_V>(
	  __vector_permute<(_Np / 2 + _Is)..., (int(_Zeros * 0) - 1)...>(
	    __xx)))))),
      __binary_op);
  }

  template <typename _Tp, typename _BinaryOperation>
  _GLIBCXX_SIMD_INTRINSIC static constexpr _Tp
  __reduce(simd<_Tp, _Abi> __x, _BinaryOperation&& __binary_op)
  {
    constexpr size_t _Np = simd_size_v<_Tp, _Abi>;
    if constexpr (_Np == 1)
      return __x[0];
    else if constexpr (_Np == 2)
      return __binary_op(simd<_Tp, simd_abi::scalar>(__x[0]),
			 simd<_Tp, simd_abi::scalar>(__x[1]))[0];
    else if constexpr (_Abi::_S_is_partial) //{{{
      {
	[[maybe_unused]] constexpr auto __full_size
	  = _Abi::template _S_full_size<_Tp>;
	if constexpr (_Np == 3)
	  return __binary_op(__binary_op(simd<_Tp, simd_abi::scalar>(__x[0]),
					 simd<_Tp, simd_abi::scalar>(__x[1])),
			     simd<_Tp, simd_abi::scalar>(__x[2]))[0];
	else if constexpr (std::is_same_v<__remove_cvref_t<_BinaryOperation>,
					  std::plus<>>)
	  {
	    using _Ap = simd_abi::deduce_t<_Tp, __full_size>;
	    return _Ap::_SimdImpl::__reduce(
	      simd<_Tp, _Ap>(__private_init, _Abi::__masked(__as_vector(__x))),
	      __binary_op);
	  }
	else if constexpr (std::is_same_v<__remove_cvref_t<_BinaryOperation>,
					  std::multiplies<>>)
	  {
	    using _Ap = simd_abi::deduce_t<_Tp, __full_size>;
	    using _TW = _SimdWrapper<_Tp, __full_size>;
	    constexpr auto __implicit_mask_full
	      = _Abi::template __implicit_mask<_Tp>().__as_full_vector();
	    constexpr _TW __one = __vector_broadcast<__full_size>(_Tp(1));
	    const _TW __x_full = __data(__x).__as_full_vector();
	    const _TW __x_padded_with_ones
	      = _Ap::_CommonImpl::_S_blend(__implicit_mask_full, __one,
					   __x_full);
	    return _Ap::_SimdImpl::__reduce(
	      simd<_Tp, _Ap>(__private_init, __x_padded_with_ones),
	      __binary_op);
	  }
	else if constexpr (_Np & 1)
	  {
	    using _Ap = simd_abi::deduce_t<_Tp, _Np - 1>;
	    return __binary_op(
	      simd<_Tp, simd_abi::scalar>(_Ap::_SimdImpl::__reduce(
		simd<_Tp, _Ap>(__intrin_bitcast<__vector_type_t<_Tp, _Np - 1>>(
		  __as_vector(__x))),
		__binary_op)),
	      simd<_Tp, simd_abi::scalar>(__x[_Np - 1]))[0];
	  }
	else
	  return __reduce_partial<_Np>(
	    std::make_index_sequence<_Np / 2>(),
	    std::make_index_sequence<__full_size - _Np / 2>(), __x,
	    __binary_op);
      }                                   //}}}
    else if constexpr (sizeof(__x) == 16) //{{{
      {
	if constexpr (_Np == 16)
	  {
	    const auto __y = __data(__x);
	    __x = __binary_op(
	      __make_simd<_Tp, _Np>(__vector_permute<0, 0, 1, 1, 2, 2, 3, 3, 4,
						     4, 5, 5, 6, 6, 7, 7>(__y)),
	      __make_simd<_Tp, _Np>(
		__vector_permute<8, 8, 9, 9, 10, 10, 11, 11, 12, 12, 13, 13, 14,
				 14, 15, 15>(__y)));
	  }
	if constexpr (_Np >= 8)
	  {
	    const auto __y = __vector_bitcast<short>(__data(__x));
	    __x
	      = __binary_op(__make_simd<_Tp, _Np>(__vector_bitcast<_Tp>(
			      __vector_permute<0, 0, 1, 1, 2, 2, 3, 3>(__y))),
			    __make_simd<_Tp, _Np>(__vector_bitcast<_Tp>(
			      __vector_permute<4, 4, 5, 5, 6, 6, 7, 7>(__y))));
	  }
	if constexpr (_Np >= 4)
	  {
	    using _Up
	      = std::conditional_t<std::is_floating_point_v<_Tp>, float, int>;
	    const auto __y = __vector_bitcast<_Up>(__data(__x));
	    __x = __binary_op(__x, __make_simd<_Tp, _Np>(__vector_bitcast<_Tp>(
				     __vector_permute<3, 2, 1, 0>(__y))));
	  }
	using _Up
	  = std::conditional_t<std::is_floating_point_v<_Tp>, double, _LLong>;
	const auto __y = __vector_bitcast<_Up>(__data(__x));
	__x = __binary_op(__x, __make_simd<_Tp, _Np>(__vector_bitcast<_Tp>(
				 __vector_permute<1, 1>(__y))));
	return __x[0];
      } //}}}
    else
      {
	static_assert(sizeof(__x) > __min_vector_size<_Tp>);
	static_assert((_Np & (_Np - 1)) == 0); // _Np must be a power of 2
	using _Ap = simd_abi::deduce_t<_Tp, _Np / 2>;
	using _V = std::experimental::simd<_Tp, _Ap>;
	return _Ap::_SimdImpl::__reduce(
	  __binary_op(_V(__private_init, __extract<0, 2>(__as_vector(__x))),
		      _V(__private_init, __extract<1, 2>(__as_vector(__x)))),
	  static_cast<_BinaryOperation&&>(__binary_op));
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

  // modf implemented in simd_math.h
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
  static _Tp __remquo(const _Tp __x, const _Tp __y,
		      __fixed_size_storage_t<int, _TVT::_S_partial_width>* __z)
  {
    return __generate_vector<_Tp>([&](auto __i) {
      int __tmp;
      auto __r = std::remquo(__x[__i], __y[__i], &__tmp);
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

  template <typename _Tp, size_t _Np>
  static constexpr auto __isgreater(_SimdWrapper<_Tp, _Np> __x,
				    _SimdWrapper<_Tp, _Np> __y) noexcept
  {
    using _Ip = __int_for_sizeof_t<_Tp>;
    const auto __xn = __vector_bitcast<_Ip>(__x);
    const auto __yn = __vector_bitcast<_Ip>(__y);
    const auto __xp = __xn < 0 ? -(__xn & numeric_limits<_Ip>::max()) : __xn;
    const auto __yp = __yn < 0 ? -(__yn & numeric_limits<_Ip>::max()) : __yn;
    return __and(__not(_SuperImpl::__isunordered(__x, __y)),
		 __vector_bitcast<_Tp>(__xp > __yp));
  }
  template <typename _Tp, size_t _Np>
  static constexpr auto __isgreaterequal(_SimdWrapper<_Tp, _Np> __x,
					 _SimdWrapper<_Tp, _Np> __y) noexcept
  {
    using _Ip = __int_for_sizeof_t<_Tp>;
    const auto __xn = __vector_bitcast<_Ip>(__x);
    const auto __yn = __vector_bitcast<_Ip>(__y);
    const auto __xp = __xn < 0 ? -(__xn & numeric_limits<_Ip>::max()) : __xn;
    const auto __yp = __yn < 0 ? -(__yn & numeric_limits<_Ip>::max()) : __yn;
    return __and(__not(_SuperImpl::__isunordered(__x, __y)),
		 __vector_bitcast<_Tp>(__xp >= __yp));
  }
  template <typename _Tp, size_t _Np>
  static constexpr auto __isless(_SimdWrapper<_Tp, _Np> __x,
				 _SimdWrapper<_Tp, _Np> __y) noexcept
  {
    using _Ip = __int_for_sizeof_t<_Tp>;
    const auto __xn = __vector_bitcast<_Ip>(__x);
    const auto __yn = __vector_bitcast<_Ip>(__y);
    const auto __xp = __xn < 0 ? -(__xn & numeric_limits<_Ip>::max()) : __xn;
    const auto __yp = __yn < 0 ? -(__yn & numeric_limits<_Ip>::max()) : __yn;
    return __and(__not(_SuperImpl::__isunordered(__x, __y)),
		 __vector_bitcast<_Tp>(__xp < __yp));
  }
  template <typename _Tp, size_t _Np>
  static constexpr auto __islessequal(_SimdWrapper<_Tp, _Np> __x,
				      _SimdWrapper<_Tp, _Np> __y) noexcept
  {
    using _Ip = __int_for_sizeof_t<_Tp>;
    const auto __xn = __vector_bitcast<_Ip>(__x);
    const auto __yn = __vector_bitcast<_Ip>(__y);
    const auto __xp = __xn < 0 ? -(__xn & numeric_limits<_Ip>::max()) : __xn;
    const auto __yp = __yn < 0 ? -(__yn & numeric_limits<_Ip>::max()) : __yn;
    return __and(__not(_SuperImpl::__isunordered(__x, __y)),
		 __vector_bitcast<_Tp>(__xp <= __yp));
  }
  template <typename _Tp, size_t _Np>
  static constexpr auto __islessgreater(_SimdWrapper<_Tp, _Np> __x,
					_SimdWrapper<_Tp, _Np> __y) noexcept
  {
    return __and(__not(_SuperImpl::__isunordered(__x, __y)),
		 _SuperImpl::__not_equal_to(__x, __y));
  }

#undef _GLIBCXX_SIMD_MATH_FALLBACK
#undef _GLIBCXX_SIMD_MATH_FALLBACK_MASKRET
#undef _GLIBCXX_SIMD_MATH_FALLBACK_FIXEDRET
  // __abs {{{3
  template <typename _Tp, size_t _Np>
  _GLIBCXX_SIMD_INTRINSIC static _SimdWrapper<_Tp, _Np>
  __abs(_SimdWrapper<_Tp, _Np> __x) noexcept
  {
    // if (__builtin_is_constant_evaluated())
    //  {
    //    return __x._M_data < 0 ? -__x._M_data : __x._M_data;
    //  }
    if constexpr (std::is_floating_point_v<_Tp>)
      // `v < 0 ? -v : v` cannot compile to the efficient implementation of
      // masking the signbit off because it must consider v == -0

      // ~(-0.) & v would be easy, but breaks with fno-signed-zeros
      return __and(_S_absmask<__vector_type_t<_Tp, _Np>>, __x._M_data);
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
    using _V = typename _TVT::type;
    const _V __x = __x_;
    const _V __absx = __and(__x, _S_absmask<_V>);
    static_assert(CHAR_BIT * sizeof(1ull)
		  >= std::numeric_limits<value_type>::digits);
    _GLIBCXX_SIMD_USE_CONSTEXPR _V __shifter_abs
      = _V() + (1ull << (std::numeric_limits<value_type>::digits - 1));
    const _V __shifter = __or(__and(_S_signmask<_V>, __x), __shifter_abs);
    _V __shifted = __x + __shifter;
    // how can we stop -fassociative-math to break this pattern?
    // asm("" : "+X"(__shifted));
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
  template <typename _Tp, size_t _Np>
  _GLIBCXX_SIMD_INTRINSIC static _SimdWrapper<_Tp, _Np>
  __trunc(_SimdWrapper<_Tp, _Np> __x)
  {
    using _V = __vector_type_t<_Tp, _Np>;
    const _V __absx = __and(__x._M_data, _S_absmask<_V>);
    static_assert(CHAR_BIT * sizeof(1ull) >= std::numeric_limits<_Tp>::digits);
    constexpr _Tp __shifter = 1ull << (std::numeric_limits<_Tp>::digits - 1);
    _V __truncated = (__absx + __shifter) - __shifter;
    __truncated -= __truncated > __absx ? _V() + 1 : _V();
    return __absx < __shifter ? __or(__xor(__absx, __x._M_data), __truncated)
			      : __x._M_data;
  }

  // __round {{{3
  template <typename _Tp, size_t _Np>
  _GLIBCXX_SIMD_INTRINSIC static _SimdWrapper<_Tp, _Np>
  __round(_SimdWrapper<_Tp, _Np> __x)
  {
    using _V = __vector_type_t<_Tp, _Np>;
    const _V __absx = __and(__x._M_data, _S_absmask<_V>);
    static_assert(CHAR_BIT * sizeof(1ull) >= std::numeric_limits<_Tp>::digits);
    constexpr _Tp __shifter = 1ull << (std::numeric_limits<_Tp>::digits - 1);
    _V __truncated = (__absx + __shifter) - __shifter;
    __truncated -= __truncated > __absx ? _V() + 1 : _V();
    const _V __rounded
      = __or(__xor(__absx, __x._M_data),
	     __truncated + (__absx - __truncated >= _Tp(.5) ? _V() + 1 : _V()));
    return __absx < __shifter ? __rounded : __x._M_data;
  }

  // __floor {{{3
  template <typename _Tp, size_t _Np>
  _GLIBCXX_SIMD_INTRINSIC static _SimdWrapper<_Tp, _Np>
  __floor(_SimdWrapper<_Tp, _Np> __x)
  {
    const auto __y = _SuperImpl::__trunc(__x)._M_data;
    const auto __negative_input
      = __vector_bitcast<_Tp>(__x._M_data < __vector_broadcast<_Np, _Tp>(0));
    const auto __mask
      = __andnot(__vector_bitcast<_Tp>(__y == __x._M_data), __negative_input);
    return __or(__andnot(__mask, __y),
		__and(__mask, __y - __vector_broadcast<_Np, _Tp>(1)));
  }

  // __ceil {{{3
  template <typename _Tp, size_t _Np>
  _GLIBCXX_SIMD_INTRINSIC static _SimdWrapper<_Tp, _Np>
  __ceil(_SimdWrapper<_Tp, _Np> __x)
  {
    const auto __y = _SuperImpl::__trunc(__x)._M_data;
    const auto __negative_input
      = __vector_bitcast<_Tp>(__x._M_data < __vector_broadcast<_Np, _Tp>(0));
    const auto __inv_mask
      = __or(__vector_bitcast<_Tp>(__y == __x._M_data), __negative_input);
    return __or(__and(__inv_mask, __y),
		__andnot(__inv_mask, __y + __vector_broadcast<_Np, _Tp>(1)));
  }

  // __isnan {{{3
  template <typename _Tp, size_t _Np>
  _GLIBCXX_SIMD_INTRINSIC static _MaskMember<_Tp>
  __isnan(_SimdWrapper<_Tp, _Np> __x)
  {
#if __FINITE_MATH_ONLY__
    [](auto&&) {}(__x);
    return {}; // false
#elif !defined __SUPPORT_SNAN__
    return __vector_bitcast<_Tp>(~(__x._M_data == __x._M_data));
#elif defined __STDC_IEC_559__
    using _Up = make_unsigned_t<__int_for_sizeof_t<_Tp>>;
    constexpr auto __max = __vector_bitcast<_Up>(
      __vector_broadcast<_Np>(numeric_limits<_Tp>::infinity()));
    auto __bits = __vector_bitcast<_Up>(__x);
    __bits &= __vector_bitcast<_Up>(_S_absmask<__vector_type_t<_Tp, _Np>>);
    return __vector_bitcast<_Tp>(__bits > __max);
#else
#error "Not implemented: how to support SNaN but non-IEC559 floating-point?"
#endif
  }

  // __isfinite {{{3
  template <typename _Tp, size_t _Np>
  _GLIBCXX_SIMD_INTRINSIC static _MaskMember<_Tp>
  __isfinite(_SimdWrapper<_Tp, _Np> __x)
  {
#if __FINITE_MATH_ONLY__
    [](auto&&) {}(__x);
    return __vector_bitcast<_Np>(_Tp()) == __vector_bitcast<_Np>(_Tp());
#else
    // if all exponent bits are set, __x is either inf or NaN
    using _I = __int_for_sizeof_t<_Tp>;
    constexpr auto __inf = __vector_bitcast<_I>(
      __vector_broadcast<_Np>(std::numeric_limits<_Tp>::infinity()));
    return __vector_bitcast<_Tp>(__inf > (__vector_bitcast<_I>(__x) & __inf));
#endif
  }

  // __isunordered {{{3
  template <typename _Tp, size_t _Np>
  _GLIBCXX_SIMD_INTRINSIC static _MaskMember<_Tp>
  __isunordered(_SimdWrapper<_Tp, _Np> __x, _SimdWrapper<_Tp, _Np> __y)
  {
    return __or(__isnan(__x), __isnan(__y));
  }

  // __signbit {{{3
  template <typename _Tp, size_t _Np>
  _GLIBCXX_SIMD_INTRINSIC static _MaskMember<_Tp>
  __signbit(_SimdWrapper<_Tp, _Np> __x)
  {
    using _I = __int_for_sizeof_t<_Tp>;
    return __vector_bitcast<_Tp>(__vector_bitcast<_I>(__x) < 0);
    // Arithmetic right shift (SRA) would also work (instead of compare), but
    // 64-bit SRA isn't available on x86 before AVX512. And in general,
    // compares are more likely to be efficient than SRA.
  }

  // __isinf {{{3
  template <typename _Tp, size_t _Np>
  _GLIBCXX_SIMD_INTRINSIC static _MaskMember<_Tp>
  __isinf(_SimdWrapper<_Tp, _Np> __x)
  {
#if __FINITE_MATH_ONLY__
    [](auto&&) {}(__x);
    return {}; // false
#else
    return _SuperImpl::template __equal_to<_Tp, _Np>(
      _SuperImpl::__abs(__x),
      __vector_broadcast<_Np>(std::numeric_limits<_Tp>::infinity()));
    // alternative:
    // compare to inf using the corresponding integer type
    /*
       return
       __vector_bitcast<_Tp>(__vector_bitcast<__int_for_sizeof_t<_Tp>>(__abs(__x)._M_data)
       ==
       __vector_bitcast<__int_for_sizeof_t<_Tp>>(__vector_broadcast<_Np>(
       std::numeric_limits<_Tp>::infinity())));
       */
#endif
  }

  // __isnormal {{{3
  template <typename _Tp, size_t _Np>
  _GLIBCXX_SIMD_INTRINSIC static _MaskMember<_Tp>
  __isnormal(_SimdWrapper<_Tp, _Np> __x)
  {
    using _I = __int_for_sizeof_t<_Tp>;
    const auto absn = __vector_bitcast<_I>(_SuperImpl::__abs(__x));
    const auto minn = __vector_bitcast<_I>(
      __vector_broadcast<_Np>(std::numeric_limits<_Tp>::min()));
#if __FINITE_MATH_ONLY__
    return __auto_bitcast(absn >= minn);
#else
    const auto infn = __vector_bitcast<_I>(
      __vector_broadcast<_Np>(std::numeric_limits<_Tp>::infinity()));
    return __auto_bitcast(absn >= minn && absn < infn);
#endif
  }

  // __fpclassify {{{3
  template <typename _Tp, size_t _Np>
  _GLIBCXX_SIMD_INTRINSIC static __fixed_size_storage_t<int, _Np>
  __fpclassify(_SimdWrapper<_Tp, _Np> __x)
  {
    using _I = __int_for_sizeof_t<_Tp>;
    const auto __xi = __to_intrin(__abs(__x));
    const auto __xn = __vector_bitcast<_I>(__xi);
    constexpr size_t _NI = sizeof(__xn) / sizeof(_I);

    constexpr auto __fp_normal = __vector_broadcast<_NI, _I>(FP_NORMAL);
    constexpr auto __fp_nan = __vector_broadcast<_NI, _I>(FP_NAN);
    constexpr auto __fp_infinite = __vector_broadcast<_NI, _I>(FP_INFINITE);
    constexpr auto __fp_subnormal = __vector_broadcast<_NI, _I>(FP_SUBNORMAL);
    constexpr auto __fp_zero = __vector_broadcast<_NI, _I>(FP_ZERO);

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
	using _FixedInt = __fixed_size_storage_t<int, _Np>;
	const auto __as_int = __vector_bitcast<int, _Np>(__tmp);
	if constexpr (_FixedInt::_S_tuple_size == 1)
	  return {__as_int};
	else if constexpr (_FixedInt::_S_tuple_size == 2
			   && std::is_same_v<
			     typename _FixedInt::_SecondType::_FirstAbi,
			     simd_abi::scalar>)
	  return {__extract<0, 2>(__as_int), __as_int[_Np - 1]};
	else if constexpr (_FixedInt::_S_tuple_size == 2)
	  return {__extract<0, 2>(__as_int),
		  __auto_bitcast(__extract<1, 2>(__as_int))};
	else
	  __assert_unreachable<_Tp>();
      }
    else if constexpr (_Np == 2 && sizeof(_I) == 8
		       && __fixed_size_storage_t<int, _Np>::_S_tuple_size == 2)
      {
	const auto __aslong = __vector_bitcast<_LLong>(__tmp);
	return {int(__aslong[0]), {int(__aslong[1])}};
      }
#if _GLIBCXX_SIMD_X86INTRIN
    else if constexpr (sizeof(_Tp) == 8 && sizeof(__tmp) == 32
		       && __fixed_size_storage_t<int, _Np>::_S_tuple_size == 1)
      return {_mm_packs_epi32(__to_intrin(__lo128(__tmp)),
			      __to_intrin(__hi128(__tmp)))};
    else if constexpr (sizeof(_Tp) == 8 && sizeof(__tmp) == 64
		       && __fixed_size_storage_t<int, _Np>::_S_tuple_size == 1)
      return {_mm512_cvtepi64_epi32(__to_intrin(__tmp))};
#endif // _GLIBCXX_SIMD_X86INTRIN
    else if constexpr (__fixed_size_storage_t<int, _Np>::_S_tuple_size == 1)
      return {__call_with_subscripts<_Np>(__vector_bitcast<_LLong>(__tmp),
					  [](auto... __l) {
					    return __make_wrapper<int>(__l...);
					  })};
    else
      __assert_unreachable<_Tp>();
  }

  // __increment & __decrement{{{2
  template <typename _Tp, size_t _Np>
  _GLIBCXX_SIMD_INTRINSIC static void __increment(_SimdWrapper<_Tp, _Np>& __x)
  {
    __x = __x._M_data + 1;
  }
  template <typename _Tp, size_t _Np>
  _GLIBCXX_SIMD_INTRINSIC static void __decrement(_SimdWrapper<_Tp, _Np>& __x)
  {
    __x = __x._M_data - 1;
  }

  // smart_reference access {{{2
  template <typename _Tp, size_t _Np, typename _Up>
  _GLIBCXX_SIMD_INTRINSIC constexpr static void
  __set(_SimdWrapper<_Tp, _Np>& __v, int __i, _Up&& __x) noexcept
  {
    __v.__set(__i, static_cast<_Up&&>(__x));
  }

  // __masked_assign{{{2
  template <typename _Tp, typename _K, size_t _Np>
  _GLIBCXX_SIMD_INTRINSIC static void
  __masked_assign(_SimdWrapper<_K, _Np> __k, _SimdWrapper<_Tp, _Np>& __lhs,
		  __id<_SimdWrapper<_Tp, _Np>> __rhs)
  {
    __lhs = _CommonImpl::_S_blend(__k, __lhs, __rhs);
  }

  template <typename _Tp, typename _K, size_t _Np>
  _GLIBCXX_SIMD_INTRINSIC static void
  __masked_assign(_SimdWrapper<_K, _Np> __k, _SimdWrapper<_Tp, _Np>& __lhs,
		  __id<_Tp> __rhs)
  {
    if (__builtin_constant_p(__rhs) && __rhs == 0 && std::is_same_v<_K, _Tp>)
      {
	if constexpr (!is_same_v<bool, _K>)
	  // the __andnot optimization only makes sense if __k._M_data is a
	  // vector register
	  __lhs._M_data = __andnot(__k._M_data, __lhs._M_data);
	else
	  // for AVX512/__mmask, a _mm512_maskz_mov is best
	  __lhs = _CommonImpl::_S_blend(__k, __lhs, _SimdWrapper<_Tp, _Np>());
      }
    else
      __lhs = _CommonImpl::_S_blend(__k, __lhs,
				    _SimdWrapper<_Tp, _Np>(
				      __vector_broadcast<_Np>(__rhs)));
  }

  // __masked_cassign {{{2
  template <typename _Op, typename _Tp, typename _K, size_t _Np>
  _GLIBCXX_SIMD_INTRINSIC static void
  __masked_cassign(const _SimdWrapper<_K, _Np> __k,
		   _SimdWrapper<_Tp, _Np>& __lhs,
		   const __id<_SimdWrapper<_Tp, _Np>> __rhs, _Op __op)
  {
    __lhs = _CommonImpl::_S_blend(__k, __lhs, __op(_SuperImpl{}, __lhs, __rhs));
  }

  template <typename _Op, typename _Tp, typename _K, size_t _Np>
  _GLIBCXX_SIMD_INTRINSIC static void
  __masked_cassign(const _SimdWrapper<_K, _Np> __k,
		   _SimdWrapper<_Tp, _Np>& __lhs, const __id<_Tp> __rhs,
		   _Op __op)
  {
    __lhs = _CommonImpl::_S_blend(__k, __lhs,
				  __op(_SuperImpl{}, __lhs,
				       _SimdWrapper<_Tp, _Np>(
					 __vector_broadcast<_Np>(__rhs))));
  }

  // __masked_unary {{{2
  template <template <typename> class _Op, typename _Tp, typename _K,
	    size_t _Np>
  _GLIBCXX_SIMD_INTRINSIC static _SimdWrapper<_Tp, _Np>
  __masked_unary(const _SimdWrapper<_K, _Np> __k,
		 const _SimdWrapper<_Tp, _Np> __v)
  {
    auto __vv = __make_simd(__v);
    _Op<decltype(__vv)> __op;
    return _CommonImpl::_S_blend(__k, __v, __data(__op(__vv)));
  }

  //}}}2
};

// _MaskImplBuiltinMixin {{{1
struct _MaskImplBuiltinMixin
{
  template <typename _Tp> using _TypeTag = _Tp*;

  // __to_maskvector {{{
  template <typename _Up, size_t _ToN = 1>
  _GLIBCXX_SIMD_INTRINSIC static constexpr _SimdWrapper<_Up, _ToN>
  __to_maskvector(bool __x)
  {
    using _I = __int_for_sizeof_t<_Up>;
    return __vector_bitcast<_Up>(__x ? __vector_type_t<_I, _ToN>{~_I()}
				     : __vector_type_t<_I, _ToN>{});
  }

  template <typename _Up, size_t _UpN = 0, size_t _Np, bool _Sanitized,
	    size_t _ToN = _UpN == 0 ? _Np : _UpN>
  _GLIBCXX_SIMD_INTRINSIC static constexpr _SimdWrapper<_Up, _ToN>
  __to_maskvector(_BitMask<_Np, _Sanitized> __x)
  {
    using _I = __int_for_sizeof_t<_Up>;
    return __vector_bitcast<_Up>(
      __generate_vector<__vector_type_t<_I, _ToN>>([&](auto __i) constexpr {
	if constexpr (__i < _Np)
	  return __x[__i] ? ~_I() : _I();
	else
	  return _I();
      }));
  }

  template <typename _Up, size_t _UpN = 0, typename _Tp, size_t _Np,
	    size_t _ToN = _UpN == 0 ? _Np : _UpN>
  _GLIBCXX_SIMD_INTRINSIC static constexpr _SimdWrapper<_Up, _ToN>
  __to_maskvector(_SimdWrapper<_Tp, _Np> __x)
  {
    using _TW = _SimdWrapper<_Tp, _Np>;
    using _UW = _SimdWrapper<_Up, _ToN>;
    if constexpr (sizeof(_Up) == sizeof(_Tp) && sizeof(_TW) == sizeof(_UW))
      return __wrapper_bitcast<_Up, _ToN>(__x);
    else if constexpr (is_same_v<_Tp, bool>) // bits -> vector
      return __to_maskvector<_Up, _ToN>(std::bitset<_Np>(__x._M_data));
    else
      { // vector -> vector
	/*
	[[maybe_unused]] const auto __y = __vector_bitcast<_Up>(__x._M_data);
	if constexpr (sizeof(_Tp) == 8 && sizeof(_Up) == 4 && sizeof(__y) == 16)
	  return __vector_permute<1, 3, -1, -1>(__y);
	else if constexpr (sizeof(_Tp) == 4 && sizeof(_Up) == 2
			   && sizeof(__y) == 16)
	  return __vector_permute<1, 3, 5, 7, -1, -1, -1, -1>(__y);
	else if constexpr (sizeof(_Tp) == 8 && sizeof(_Up) == 2
			   && sizeof(__y) == 16)
	  return __vector_permute<3, 7, -1, -1, -1, -1, -1, -1>(__y);
	else if constexpr (sizeof(_Tp) == 2 && sizeof(_Up) == 1
			   && sizeof(__y) == 16)
	  return __vector_permute<1, 3, 5, 7, 9, 11, 13, 15, -1, -1, -1, -1, -1,
				  -1, -1, -1>(__y);
	else if constexpr (sizeof(_Tp) == 4 && sizeof(_Up) == 1
			   && sizeof(__y) == 16)
	  return __vector_permute<3, 7, 11, 15, -1, -1, -1, -1, -1, -1, -1, -1,
				  -1, -1, -1, -1>(__y);
	else if constexpr (sizeof(_Tp) == 8 && sizeof(_Up) == 1
			   && sizeof(__y) == 16)
	  return __vector_permute<7, 15, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
				  -1, -1, -1, -1>(__y);
	else
	*/
	{
	  using _I = __int_for_sizeof_t<_Up>;
	  const auto __y
	    = __vector_bitcast<__int_for_sizeof_t<_Tp>>(__x._M_data);
	  return __vector_bitcast<_Up>(
	    __generate_vector<__vector_type_t<_I, _ToN>>([&](
	      auto __i) constexpr {
	      if constexpr (__i < _Np)
		return _I(__y[__i.value]);
	      else
		return _I();
	    }));
	}
      }
  }

  // }}}
  // __to_bits {{{
  template <typename _Tp, size_t _Np>
  _GLIBCXX_SIMD_INTRINSIC static constexpr _SanitizedBitMask<_Np>
  __to_bits(_SimdWrapper<_Tp, _Np> __x)
  {
    static_assert(!is_same_v<_Tp, bool>);
    static_assert(_Np <= CHAR_BIT * sizeof(_ULLong));
    using _Up = make_unsigned_t<__int_for_sizeof_t<_Tp>>;
    const auto __bools
      = __vector_bitcast<_Up>(__x) >> (sizeof(_Up) * CHAR_BIT - 1);
    _ULLong __r = 0;
    __execute_n_times<_Np>(
      [&](auto __i) { __r |= _ULLong(__bools[__i.value]) << __i; });
    return __r;
  }

  // }}}
};

// _MaskImplBuiltin {{{1
template <typename _Abi> struct _MaskImplBuiltin : _MaskImplBuiltinMixin
{
  using _MaskImplBuiltinMixin::__to_bits;
  using _MaskImplBuiltinMixin::__to_maskvector;

  // member types {{{
  template <typename _Tp>
  using _SimdMember = typename _Abi::template __traits<_Tp>::_SimdMember;
  template <typename _Tp>
  using _MaskMember = typename _Abi::template __traits<_Tp>::_MaskMember;
  using _SuperImpl = typename _Abi::_MaskImpl;
  using _CommonImpl = typename _Abi::_CommonImpl;
  template <typename _Tp> static constexpr size_t size = simd_size_v<_Tp, _Abi>;

  // }}}
  // __broadcast {{{
  template <typename _Tp>
  _GLIBCXX_SIMD_INTRINSIC static constexpr _MaskMember<_Tp>
  __broadcast(bool __x)
  {
    return __x ? _Abi::template __implicit_mask<_Tp>() : _MaskMember<_Tp>();
  }

  // }}}
  // __load {{{
  template <typename _Tp, typename _Flags>
  _GLIBCXX_SIMD_INTRINSIC static constexpr _MaskMember<_Tp>
  __load(const bool* __mem)
  {
    using _I = __int_for_sizeof_t<_Tp>;
    if constexpr (sizeof(_Tp) == sizeof(bool))
      {
	const auto __bools
	  = _CommonImpl::template _S_load<_I, size<_Tp>>(__mem, _Flags());
	// bool is {0, 1}, everything else is UB
	return __vector_bitcast<_Tp>(__bools > 0);
      }
    else
      return __vector_bitcast<_Tp>(__generate_vector<_I, size<_Tp>>([&](
	auto __i) constexpr { return __mem[__i] ? ~_I() : _I(); }));
  }

  // }}}
  // __convert {{{
  template <typename _Tp, size_t _Np, bool _Sanitized>
  _GLIBCXX_SIMD_INTRINSIC static constexpr auto
  __convert(_BitMask<_Np, _Sanitized> __x)
  {
    if constexpr (__is_builtin_bitmask_abi<_Abi>())
      return _SimdWrapper<bool, simd_size_v<_Tp, _Abi>>(__x._M_to_bits());
    else
      return _SuperImpl::template __to_maskvector<_Tp, size<_Tp>>(
	__x._M_sanitized());
  }

  template <typename _Tp, size_t _Np>
  _GLIBCXX_SIMD_INTRINSIC static constexpr auto
  __convert(_SimdWrapper<bool, _Np> __x)
  {
    if constexpr (__is_builtin_bitmask_abi<_Abi>())
      return _SimdWrapper<bool, simd_size_v<_Tp, _Abi>>(__x._M_data);
    else
      return _SuperImpl::template __to_maskvector<_Tp, size<_Tp>>(
	_BitMask<_Np>(__x._M_data)._M_sanitized());
  }

  template <typename _Tp, typename _Up, size_t _Np>
  _GLIBCXX_SIMD_INTRINSIC static constexpr auto
  __convert(_SimdWrapper<_Up, _Np> __x)
  {
    if constexpr (__is_builtin_bitmask_abi<_Abi>())
      return _SimdWrapper<bool, simd_size_v<_Tp, _Abi>>(
	_SuperImpl::__to_bits(__x));
    else
      return _SuperImpl::template __to_maskvector<_Tp, size<_Tp>>(__x);
  }

  template <typename _Tp, typename _Up, typename _UAbi>
  _GLIBCXX_SIMD_INTRINSIC static constexpr auto
  __convert(simd_mask<_Up, _UAbi> __x)
  {
    if constexpr (__is_builtin_bitmask_abi<_Abi>())
      {
	using _R = _SimdWrapper<bool, simd_size_v<_Tp, _Abi>>;
	if constexpr (__is_builtin_bitmask_abi<_UAbi>()) // bits -> bits
	  return _R(__data(__x));
	else if constexpr (__is_scalar_abi<_UAbi>()) // bool -> bits
	  return _R(__data(__x));
	else if constexpr (__is_fixed_size_abi_v<_UAbi>) // bitset -> bits
	  return _R(__data(__x)._M_to_bits());
	else // vector -> bits
	  return _R(_UAbi::_MaskImpl::__to_bits(__data(__x))._M_to_bits());
      }
    else
      return _SuperImpl::template __to_maskvector<_Tp, size<_Tp>>(__data(__x));
  }

  // }}}
  // __masked_load {{{2
  template <typename _Tp, size_t _Np, typename _Fp>
  static inline _SimdWrapper<_Tp, _Np>
  __masked_load(_SimdWrapper<_Tp, _Np> __merge, _SimdWrapper<_Tp, _Np> __mask,
		const bool* __mem, _Fp) noexcept
  {
    // AVX(2) has 32/64 bit maskload, but nothing at 8 bit granularity
    auto __tmp = __wrapper_bitcast<__int_for_sizeof_t<_Tp>>(__merge);
    _BitOps::__bit_iteration(_SuperImpl::__to_bits(__mask),
			     [&](auto __i) { __tmp.__set(__i, -__mem[__i]); });
    __merge = __wrapper_bitcast<_Tp>(__tmp);
    return __merge;
  }

  // __store {{{2
  template <typename _Tp, size_t _Np, typename _Fp>
  _GLIBCXX_SIMD_INTRINSIC static void __store(_SimdWrapper<_Tp, _Np> __v,
					      bool* __mem, _Fp) noexcept
  {
    __execute_n_times<_Np>([&](auto __i) constexpr { __mem[__i] = __v[__i]; });
  }

  // __masked_store {{{2
  template <typename _Tp, size_t _Np, typename _Fp>
  static inline void __masked_store(const _SimdWrapper<_Tp, _Np> __v,
				    bool* __mem, _Fp,
				    const _SimdWrapper<_Tp, _Np> __k) noexcept
  {
    _BitOps::__bit_iteration(
      _SuperImpl::__to_bits(__k), [&](auto __i) constexpr {
	__mem[__i] = __v[__i];
      });
  }

  // __from_bitmask{{{2
  template <size_t _Np, typename _Tp>
  _GLIBCXX_SIMD_INTRINSIC static _MaskMember<_Tp>
  __from_bitmask(_SanitizedBitMask<_Np> __bits, _TypeTag<_Tp>)
  {
    return _SuperImpl::template __to_maskvector<_Tp, size<_Tp>>(__bits);
  }

  // logical and bitwise operators {{{2
  template <typename _Tp, size_t _Np>
  _GLIBCXX_SIMD_INTRINSIC static constexpr _SimdWrapper<_Tp, _Np>
  __logical_and(const _SimdWrapper<_Tp, _Np>& __x,
		const _SimdWrapper<_Tp, _Np>& __y)
  {
    return __and(__x._M_data, __y._M_data);
  }

  template <typename _Tp, size_t _Np>
  _GLIBCXX_SIMD_INTRINSIC static constexpr _SimdWrapper<_Tp, _Np>
  __logical_or(const _SimdWrapper<_Tp, _Np>& __x,
	       const _SimdWrapper<_Tp, _Np>& __y)
  {
    return __or(__x._M_data, __y._M_data);
  }

  template <typename _Tp, size_t _Np>
  _GLIBCXX_SIMD_INTRINSIC static constexpr _SimdWrapper<_Tp, _Np>
  __bit_not(const _SimdWrapper<_Tp, _Np>& __x)
  {
    if constexpr(_Abi::_S_is_partial)
      return __andnot(__x, _Abi::template __implicit_mask<_Tp>());
    else
      return __not(__x._M_data);
  }

  template <typename _Tp, size_t _Np>
  _GLIBCXX_SIMD_INTRINSIC static constexpr _SimdWrapper<_Tp, _Np>
  __bit_and(const _SimdWrapper<_Tp, _Np>& __x,
	    const _SimdWrapper<_Tp, _Np>& __y)
  {
    return __and(__x._M_data, __y._M_data);
  }

  template <typename _Tp, size_t _Np>
  _GLIBCXX_SIMD_INTRINSIC static constexpr _SimdWrapper<_Tp, _Np>
  __bit_or(const _SimdWrapper<_Tp, _Np>& __x, const _SimdWrapper<_Tp, _Np>& __y)
  {
    return __or(__x._M_data, __y._M_data);
  }

  template <typename _Tp, size_t _Np>
  _GLIBCXX_SIMD_INTRINSIC static constexpr _SimdWrapper<_Tp, _Np>
  __bit_xor(const _SimdWrapper<_Tp, _Np>& __x,
	    const _SimdWrapper<_Tp, _Np>& __y)
  {
    return __xor(__x._M_data, __y._M_data);
  }

  // smart_reference access {{{2
  template <typename _Tp, size_t _Np>
  static constexpr void __set(_SimdWrapper<_Tp, _Np>& __k, int __i,
			      bool __x) noexcept
  {
    if constexpr (std::is_same_v<_Tp, bool>)
      __k.__set(__i, __x);
    else
      {
	using _Ip = __int_for_sizeof_t<_Tp>;
	auto __ki = __vector_bitcast<_Ip>(__k._M_data);
	if (__builtin_is_constant_evaluated())
	  {
	    __k = __vector_bitcast<_Tp>(
	      __generate_from_n_evaluations<_Np, decltype(__ki)>([&](auto __j) {
		if (__i == __j)
		  return _Ip(-__x);
		else
		  return __ki[+__j];
	      }));
	  }
	else
	  {
	    __ki[__i] = _Ip(-__x);
	    __k = __vector_bitcast<_Tp>(__ki);
	  }
      }
  }

  // __masked_assign{{{2
  template <typename _Tp, size_t _Np>
  _GLIBCXX_SIMD_INTRINSIC static void
  __masked_assign(_SimdWrapper<_Tp, _Np> __k, _SimdWrapper<_Tp, _Np>& __lhs,
		  __id<_SimdWrapper<_Tp, _Np>> __rhs)
  {
    __lhs = _CommonImpl::_S_blend(__k, __lhs, __rhs);
  }

  template <typename _Tp, size_t _Np>
  _GLIBCXX_SIMD_INTRINSIC static void
  __masked_assign(_SimdWrapper<_Tp, _Np> __k, _SimdWrapper<_Tp, _Np>& __lhs,
		  bool __rhs)
  {
    if (__builtin_constant_p(__rhs))
      {
	if (__rhs == false)
	    __lhs = __andnot(__k, __lhs);
	else
	    __lhs = __or(__k, __lhs);
	return;
      }
    __lhs
      = _CommonImpl::_S_blend(__k, __lhs, __data(simd_mask<_Tp, _Abi>(__rhs)));
  }

  //}}}2
  // __all_of {{{
  template <typename _Tp>
  _GLIBCXX_SIMD_INTRINSIC static bool __all_of(simd_mask<_Tp, _Abi> __k)
  {
    return __call_with_subscripts(
      __vector_bitcast<__int_for_sizeof_t<_Tp>>(__data(__k)),
      make_index_sequence<size<_Tp>>(),
      [](const auto... __ent) constexpr { return (... && !(__ent == 0)); });
  }

  // }}}
  // __any_of {{{
  template <typename _Tp>
  _GLIBCXX_SIMD_INTRINSIC static bool __any_of(simd_mask<_Tp, _Abi> __k)
  {
    return __call_with_subscripts(
      __vector_bitcast<__int_for_sizeof_t<_Tp>>(__data(__k)),
      make_index_sequence<size<_Tp>>(),
      [](const auto... __ent) constexpr { return (... || !(__ent == 0)); });
  }

  // }}}
  // __none_of {{{
  template <typename _Tp>
  _GLIBCXX_SIMD_INTRINSIC static bool __none_of(simd_mask<_Tp, _Abi> __k)
  {
    return __call_with_subscripts(
      __vector_bitcast<__int_for_sizeof_t<_Tp>>(__data(__k)),
      make_index_sequence<size<_Tp>>(),
      [](const auto... __ent) constexpr { return (... && (__ent == 0)); });
  }

  // }}}
  // __some_of {{{
  template <typename _Tp>
  _GLIBCXX_SIMD_INTRINSIC static bool __some_of(simd_mask<_Tp, _Abi> __k)
  {
    const int __n_true = __popcount(__k);
    return __n_true > 0 && __n_true < int(size<_Tp>);
  }

  // }}}
  // __popcount {{{
  template <typename _Tp>
  _GLIBCXX_SIMD_INTRINSIC static int __popcount(simd_mask<_Tp, _Abi> __k)
  {
    using _I = __int_for_sizeof_t<_Tp>;
    if constexpr (std::is_default_constructible_v<simd<_I, _Abi>>)
      return -reduce(
	simd<_I, _Abi>(__private_init, __wrapper_bitcast<_I>(__data(__k))));
    else
      return -reduce(__bit_cast<rebind_simd_t<_I, simd<_Tp, _Abi>>>(
	simd<_Tp, _Abi>(__private_init, __data(__k))));
  }

  // }}}
  // __find_first_set {{{
  template <typename _Tp>
  _GLIBCXX_SIMD_INTRINSIC static int __find_first_set(simd_mask<_Tp, _Abi> __k)
  {
    return _BitOps::__firstbit(_SuperImpl::__to_bits(__data(__k))._M_to_bits());
  }

  // }}}
  // __find_last_set {{{
  template <typename _Tp>
  _GLIBCXX_SIMD_INTRINSIC static int __find_last_set(simd_mask<_Tp, _Abi> __k)
  {
    return _BitOps::__lastbit(_SuperImpl::__to_bits(__data(__k))._M_to_bits());
  }

  // }}}
};

//}}}1
_GLIBCXX_SIMD_END_NAMESPACE
#endif // __cplusplus >= 201703L
#endif // _GLIBCXX_EXPERIMENTAL_SIMD_ABIS_H_

// vim: foldmethod=marker sw=2 noet ts=8 sts=2 tw=80
