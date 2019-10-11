// Simd x86 specific implementations -*- C++ -*-

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

#ifndef _GLIBCXX_EXPERIMENTAL_SIMD_X86_H_
#define _GLIBCXX_EXPERIMENTAL_SIMD_X86_H_

#if __cplusplus >= 201703L

#if !_GLIBCXX_SIMD_X86INTRIN
#error "simd_x86.h may only be included when MMX or SSE on x86(_64) are available"
#endif

_GLIBCXX_SIMD_BEGIN_NAMESPACE

// __xzyw{{{
// shuffles the complete vector, swapping the inner two quarters. Often useful
// for AVX for fixing up a shuffle result.
template <typename _Tp, typename _TVT = _VectorTraits<_Tp>>
_GLIBCXX_SIMD_INTRINSIC _Tp __xzyw(_Tp __a)
{
  if constexpr (sizeof(_Tp) == 16)
    {
      const auto __x = __vector_bitcast<conditional_t<
	is_floating_point_v<typename _TVT::value_type>, float, int>>(__a);
      return reinterpret_cast<_Tp>(
	decltype(__x){__x[0], __x[2], __x[1], __x[3]});
    }
  else if constexpr (sizeof(_Tp) == 32)
    {
      const auto __x = __vector_bitcast<conditional_t<
	is_floating_point_v<typename _TVT::value_type>, double, _LLong>>(__a);
      return reinterpret_cast<_Tp>(
	decltype(__x){__x[0], __x[2], __x[1], __x[3]});
    }
  else if constexpr (sizeof(_Tp) == 64)
    {
      const auto __x = __vector_bitcast<conditional_t<
	is_floating_point_v<typename _TVT::value_type>, double, _LLong>>(__a);
      return reinterpret_cast<_Tp>(decltype(__x){
	__x[0], __x[1], __x[4], __x[5], __x[2], __x[3], __x[6], __x[7]});
    }
  else
    __assert_unreachable<_Tp>();
}

// }}}

#ifdef _GLIBCXX_SIMD_WORKAROUND_PR85048
#include "simd_x86_conversions.h"
#endif

// ISA & type detection {{{
template <typename _Tp, size_t _N>
constexpr bool __is_sse_ps()
{
  return __have_sse && std::is_same_v<_Tp, float> &&
	 sizeof(__intrinsic_type_t<_Tp, _N>) == 16;
}
template <typename _Tp, size_t _N>
constexpr bool __is_sse_pd()
{
  return __have_sse2 && std::is_same_v<_Tp, double> &&
	 sizeof(__intrinsic_type_t<_Tp, _N>) == 16;
}
template <typename _Tp, size_t _N>
constexpr bool __is_avx_ps()
{
  return __have_avx && std::is_same_v<_Tp, float> &&
	 sizeof(__intrinsic_type_t<_Tp, _N>) == 32;
}
template <typename _Tp, size_t _N>
constexpr bool __is_avx_pd()
{
  return __have_avx && std::is_same_v<_Tp, double> &&
	 sizeof(__intrinsic_type_t<_Tp, _N>) == 32;
}
template <typename _Tp, size_t _N>
constexpr bool __is_avx512_ps()
{
  return __have_avx512f && std::is_same_v<_Tp, float> &&
	 sizeof(__intrinsic_type_t<_Tp, _N>) == 64;
}
template <typename _Tp, size_t _N>
constexpr bool __is_avx512_pd()
{
  return __have_avx512f && std::is_same_v<_Tp, double> &&
	 sizeof(__intrinsic_type_t<_Tp, _N>) == 64;
}

// }}}
// _SimdImplX86Mixin {{{
struct _SimdImplX86Mixin
{
#ifdef _GLIBCXX_SIMD_WORKAROUND_PR85048
  template <typename _From, typename _To, size_t _ToSize>
  static constexpr bool __converts_via_decomposition()
  {
    if constexpr (is_integral_v<_From> && is_integral_v<_To> &&
		  sizeof(_From) == 8 && _ToSize == 16)
      return (sizeof(_To) == 2 && !__have_ssse3) ||
	     (sizeof(_To) == 1 && !__have_avx512f);
    else if constexpr (is_floating_point_v<_From> && is_integral_v<_To>)
      return ((sizeof(_From) == 4 || sizeof(_From) == 8) && sizeof(_To) == 8 &&
	      !__have_avx512dq) ||
	     (sizeof(_From) == 8 && sizeof(_To) == 4 && !__have_sse4_1 &&
	      _ToSize == 16);
    else if constexpr (is_integral_v<_From> && is_floating_point_v<_To> &&
		       sizeof(_From) == 8 && !__have_avx512dq)
      return (sizeof(_To) == 4 && _ToSize == 16) ||
	     (sizeof(_To) == 8 && _ToSize < 64);
    else
      return false;
  }

  template <typename _From, typename _To, size_t _ToSize>
  static inline constexpr bool __converts_via_decomposition_v =
    __converts_via_decomposition<_From, _To, _ToSize>();
#else
  template <typename _From, typename _To, size_t _ToSize>
  static inline constexpr bool __converts_via_decomposition_v =
    _SimdImplBuiltinMixin::__converts_via_decomposition_v<_From, _To, _ToSize>;
#endif
};

// }}}
// _SimdImplX86 {{{1
template <typename _Abi>
struct _SimdImplX86 : _SimdImplX86Mixin, _SimdImplBuiltin<_Abi>
{
  using _SimdImplX86Mixin::__converts_via_decomposition_v;

  using _Base = _SimdImplBuiltin<_Abi>;
  template <typename _Tp>
  using _MaskMember = typename _Base::template _MaskMember<_Tp>;
  template <typename _Tp>
  static constexpr size_t _S_full_size = _Abi::template _S_full_size<_Tp>;
  template <typename _Tp>
  static constexpr size_t size = _Abi::template size<_Tp>;
  template <typename _Tp>
  static constexpr size_t _S_max_store_size =
    (sizeof(_Tp) >= 4 && __have_avx512f) || __have_avx512bw
      ? 64
      : (std::is_floating_point_v<_Tp>&& __have_avx) || __have_avx2 ? 32 : 16;
  using _MaskImpl = typename _Abi::_MaskImpl;

  // __masked_load {{{2
  template <class _Tp, size_t _N, class _U, class _F>
  static inline _SimdWrapper<_Tp, _N>
    __masked_load(_SimdWrapper<_Tp, _N> __merge,
		  _MaskMember<_Tp>      __k,
		  const _U*             __mem,
		  _F) noexcept
  {
    static_assert(_N == size<_Tp>);
    if constexpr (std::is_same_v<_Tp, _U> || // no conversion
		  (sizeof(_Tp) == sizeof(_U) &&
		   std::is_integral_v<_Tp> ==
		     std::is_integral_v<_U>) // conversion via bit
					     // reinterpretation
    )
      {
	[[maybe_unused]] const auto __intrin = __to_intrin(__merge);
	if constexpr ((__is_avx512_abi<_Abi>() || __have_avx512bw_vl) &&
		      sizeof(_Tp) == 1)
	  {
	    const auto __kk = _MaskImpl::__to_bits(__k);
	    if constexpr (sizeof(__intrin) == 16)
	      __merge = __vector_bitcast<_Tp, _N>(
		_mm_mask_loadu_epi8(__intrin, __kk, __mem));
	    else if constexpr (sizeof(__merge) == 32)
	      __merge = __vector_bitcast<_Tp, _N>(
		_mm256_mask_loadu_epi8(__intrin, __kk, __mem));
	    else if constexpr (sizeof(__merge) == 64)
	      __merge = __vector_bitcast<_Tp, _N>(
		_mm512_mask_loadu_epi8(__intrin, __kk, __mem));
	    else
	      __assert_unreachable<_Tp>();
	  }
	else if constexpr ((__is_avx512_abi<_Abi>() || __have_avx512bw_vl) &&
			   sizeof(_Tp) == 2)
	  {
	    const auto __kk = _MaskImpl::__to_bits(__k);
	    if constexpr (sizeof(__intrin) == 16)
	      __merge = __vector_bitcast<_Tp, _N>(
		_mm_mask_loadu_epi16(__intrin, __kk, __mem));
	    else if constexpr (sizeof(__intrin) == 32)
	      __merge = __vector_bitcast<_Tp, _N>(
		_mm256_mask_loadu_epi16(__intrin, __kk, __mem));
	    else if constexpr (sizeof(__intrin) == 64)
	      __merge = __vector_bitcast<_Tp, _N>(
		_mm512_mask_loadu_epi16(__intrin, __kk, __mem));
	    else
	      __assert_unreachable<_Tp>();
	  }
	else if constexpr ((__is_avx512_abi<_Abi>() || __have_avx512vl) &&
			   sizeof(_Tp) == 4 && std::is_integral_v<_U>)
	  {
	    const auto __kk = _MaskImpl::__to_bits(__k);
	    if constexpr (sizeof(__intrin) == 16)
	      __merge = __vector_bitcast<_Tp, _N>(
		_mm_mask_loadu_epi32(__intrin, __kk, __mem));
	    else if constexpr (sizeof(__intrin) == 32)
	      __merge = __vector_bitcast<_Tp, _N>(
		_mm256_mask_loadu_epi32(__intrin, __kk, __mem));
	    else if constexpr (sizeof(__intrin) == 64)
	      __merge = __vector_bitcast<_Tp, _N>(
		_mm512_mask_loadu_epi32(__intrin, __kk, __mem));
	    else
	      __assert_unreachable<_Tp>();
	  }
	else if constexpr ((__is_avx512_abi<_Abi>() || __have_avx512vl) &&
			   sizeof(_Tp) == 4 && std::is_floating_point_v<_U>)
	  {
	    const auto __kk = _MaskImpl::__to_bits(__k);
	    if constexpr (sizeof(__intrin) == 16)
	      __merge = __vector_bitcast<_Tp, _N>(
		_mm_mask_loadu_ps(__intrin, __kk, __mem));
	    else if constexpr (sizeof(__intrin) == 32)
	      __merge = __vector_bitcast<_Tp, _N>(
		_mm256_mask_loadu_ps(__intrin, __kk, __mem));
	    else if constexpr (sizeof(__intrin) == 64)
	      __merge = __vector_bitcast<_Tp, _N>(
		_mm512_mask_loadu_ps(__intrin, __kk, __mem));
	    else
	      __assert_unreachable<_Tp>();
	  }
	else if constexpr (__have_avx2 && sizeof(_Tp) == 4 &&
			   std::is_integral_v<_U>)
	  {
	    if constexpr (sizeof(__intrin) == 16)
	      __merge =
		__or(__andnot(__k._M_data, __merge._M_data),
		     __vector_bitcast<_Tp, _N>(_mm_maskload_epi32(
		       reinterpret_cast<const int*>(__mem), __to_intrin(__k))));
	    else if constexpr (sizeof(__intrin) == 32)
	      __merge =
		(~__k._M_data & __merge._M_data) |
		__vector_bitcast<_Tp, _N>(_mm256_maskload_epi32(
		  reinterpret_cast<const int*>(__mem), __to_intrin(__k)));
	    else
	      __assert_unreachable<_Tp>();
	  }
	else if constexpr (__have_avx && sizeof(_Tp) == 4)
	  {
	    if constexpr (sizeof(__intrin) == 16)
	      __merge = __or(__andnot(__k._M_data, __merge._M_data),
			     __vector_bitcast<_Tp, _N>(_mm_maskload_ps(
			       reinterpret_cast<const float*>(__mem),
			       __intrin_bitcast<__m128i>(__as_vector(__k)))));
	    else if constexpr (sizeof(__intrin) == 32)
	      __merge =
		__or(__andnot(__k._M_data, __merge._M_data),
		     _mm256_maskload_ps(reinterpret_cast<const float*>(__mem),
					__vector_bitcast<_LLong>(__k)));
	    else
	      __assert_unreachable<_Tp>();
	  }
	else if constexpr ((__is_avx512_abi<_Abi>() || __have_avx512vl) &&
			   sizeof(_Tp) == 8 && std::is_integral_v<_U>)
	  {
	    const auto __kk = _MaskImpl::__to_bits(__k);
	    if constexpr (sizeof(__intrin) == 16)
	      __merge = __vector_bitcast<_Tp, _N>(
		_mm_mask_loadu_epi64(__intrin, __kk, __mem));
	    else if constexpr (sizeof(__intrin) == 32)
	      __merge = __vector_bitcast<_Tp, _N>(
		_mm256_mask_loadu_epi64(__intrin, __kk, __mem));
	    else if constexpr (sizeof(__intrin) == 64)
	      __merge = __vector_bitcast<_Tp, _N>(
		_mm512_mask_loadu_epi64(__intrin, __kk, __mem));
	    else
	      __assert_unreachable<_Tp>();
	  }
	else if constexpr ((__is_avx512_abi<_Abi>() || __have_avx512vl) &&
			   sizeof(_Tp) == 8 && std::is_floating_point_v<_U>)
	  {
	    const auto __kk = _MaskImpl::__to_bits(__k);
	    if constexpr (sizeof(__intrin) == 16)
	      __merge = __vector_bitcast<_Tp, _N>(
		_mm_mask_loadu_pd(__intrin, __kk, __mem));
	    else if constexpr (sizeof(__intrin) == 32)
	      __merge = __vector_bitcast<_Tp, _N>(
		_mm256_mask_loadu_pd(__intrin, __kk, __mem));
	    else if constexpr (sizeof(__intrin) == 64)
	      __merge = __vector_bitcast<_Tp, _N>(
		_mm512_mask_loadu_pd(__intrin, __kk, __mem));
	    else
	      __assert_unreachable<_Tp>();
	  }
	else if constexpr (__have_avx2 && sizeof(_Tp) == 8 &&
			   std::is_integral_v<_U>)
	  {
	    if constexpr (sizeof(__intrin) == 16)
	      __merge = __or(
		__andnot(__k._M_data, __merge._M_data),
		__vector_bitcast<_Tp, _N>(_mm_maskload_epi64(
		  reinterpret_cast<const _LLong*>(__mem), __to_intrin(__k))));
	    else if constexpr (sizeof(__intrin) == 32)
	      __merge =
		(~__k._M_data & __merge._M_data) |
		__vector_bitcast<_Tp>(_mm256_maskload_epi64(
		  reinterpret_cast<const _LLong*>(__mem), __to_intrin(__k)));
	    else
	      __assert_unreachable<_Tp>();
	  }
	else if constexpr (__have_avx && sizeof(_Tp) == 8)
	  {
	    if constexpr (sizeof(__intrin) == 16)
	      __merge = __or(__andnot(__k._M_data, __merge._M_data),
			     __vector_bitcast<_Tp, _N>(_mm_maskload_pd(
			       reinterpret_cast<const double*>(__mem),
			       __vector_bitcast<_LLong>(__k))));
	    else if constexpr (sizeof(__intrin) == 32)
	      __merge =
		__or(__andnot(__k._M_data, __merge._M_data),
		     _mm256_maskload_pd(reinterpret_cast<const double*>(__mem),
					__vector_bitcast<_LLong>(__k)));
	    else
	      __assert_unreachable<_Tp>();
	  }
	else
	  _BitOps::__bit_iteration(
	    _MaskImpl::__to_bits(__k), [&](auto __i) {
	      __merge.__set(__i, static_cast<_Tp>(__mem[__i]));
	    });
      }
    /* Very uncertain, that the following improves anything. Needs benchmarking
     * before it's activated.
    else if constexpr (sizeof(_U) <= 8 && // no long double
		       !__converts_via_decomposition_v<
			 _U, _Tp,
			 sizeof(__merge)> // conversion via decomposition
					  // is better handled via the
					  // bit_iteration fallback below
    )
      {
	// TODO: copy pattern from __masked_store, which doesn't resort to
	// fixed_size
	using _A       = simd_abi::deduce_t<_U, _N>;
	using _ATraits = _SimdTraits<_U, _A>;
	using _AImpl   = typename _ATraits::_SimdImpl;
	typename _ATraits::_SimdMember __uncvted{};
	typename _ATraits::_MaskMember __kk = _A::_MaskImpl::template __convert<_U>(__k);
	__uncvted = _AImpl::__masked_load(__uncvted, __kk, __mem, _F());
	_SimdConverter<_U, _A, _Tp, _Abi> __converter;
	_Base::__masked_assign(__k, __merge, __converter(__uncvted));
      }
      */
    else
      __merge = _Base::__masked_load(__merge, __k, __mem, _F());
    return __merge;
    return __merge;
  }

  // __masked_store_nocvt {{{2
  template <typename _Tp, std::size_t _N, class _F>
  _GLIBCXX_SIMD_INTRINSIC static void __masked_store_nocvt(
    _SimdWrapper<_Tp, _N> __v, _Tp* __mem, _F, _SimdWrapper<bool, _N> __k)
  {
    [[maybe_unused]] const auto __vi = __to_intrin(__v);
    if constexpr (sizeof(__vi) == 64)
      {
	static_assert(sizeof(__v) == 64 && __have_avx512f);
	if constexpr (__have_avx512bw && sizeof(_Tp) == 1)
	  _mm512_mask_storeu_epi8(__mem, __k, __vi);
	else if constexpr (__have_avx512bw && sizeof(_Tp) == 2)
	  _mm512_mask_storeu_epi16(__mem, __k, __vi);
	else if constexpr (__have_avx512f && sizeof(_Tp) == 4)
	  {
	    if constexpr (__is_aligned_v<_F, 64> && std::is_integral_v<_Tp>)
	      _mm512_mask_store_epi32(__mem, __k, __vi);
	    else if constexpr (__is_aligned_v<_F, 64> &&
			       std::is_floating_point_v<_Tp>)
	      _mm512_mask_store_ps(__mem, __k, __vi);
	    else if constexpr (std::is_integral_v<_Tp>)
	      _mm512_mask_storeu_epi32(__mem, __k, __vi);
	    else
	      _mm512_mask_storeu_ps(__mem, __k, __vi);
	  }
	else if constexpr (__have_avx512f && sizeof(_Tp) == 8)
	  {
	    if constexpr (__is_aligned_v<_F, 64> && std::is_integral_v<_Tp>)
	      _mm512_mask_store_epi64(__mem, __k, __vi);
	    else if constexpr (__is_aligned_v<_F, 64> &&
			       std::is_floating_point_v<_Tp>)
	      _mm512_mask_store_pd(__mem, __k, __vi);
	    else if constexpr (std::is_integral_v<_Tp>)
	      _mm512_mask_storeu_epi64(__mem, __k, __vi);
	    else
	      _mm512_mask_storeu_pd(__mem, __k, __vi);
	  }
#if 0   // with KNL either sizeof(_Tp) >= 4 or sizeof(_vi) <= 32
        // with Skylake-AVX512, __have_avx512bw is true
	else if constexpr (__have_sse2)
	  {
	    using _M   = __vector_type_t<_Tp, _N>;
	    using _MVT = _VectorTraits<_M>;
	    _mm_maskmoveu_si128(__auto_bitcast(__extract<0, 4>(__v._M_data)),
				__auto_bitcast(_MaskImpl::template __convert<_Tp, _N>(__k._M_data)),
				reinterpret_cast<char*>(__mem));
	    _mm_maskmoveu_si128(__auto_bitcast(__extract<1, 4>(__v._M_data)),
				__auto_bitcast(_MaskImpl::template __convert<_Tp, _N>(
				  __k._M_data >> 1 * _MVT::_S_width)),
				reinterpret_cast<char*>(__mem) + 1 * 16);
	    _mm_maskmoveu_si128(__auto_bitcast(__extract<2, 4>(__v._M_data)),
				__auto_bitcast(_MaskImpl::template __convert<_Tp, _N>(
				  __k._M_data >> 2 * _MVT::_S_width)),
				reinterpret_cast<char*>(__mem) + 2 * 16);
	    if constexpr (_N > 48 / sizeof(_Tp))
	      _mm_maskmoveu_si128(
		__auto_bitcast(__extract<3, 4>(__v._M_data)),
		__auto_bitcast(_MaskImpl::template __convert<_Tp, _N>(
		  __k._M_data >> 3 * _MVT::_S_width)),
		reinterpret_cast<char*>(__mem) + 3 * 16);
	  }
#endif
	else
	  __assert_unreachable<_Tp>();
      }
    else if constexpr (sizeof(__vi) == 32)
      {
	if constexpr (__have_avx512bw_vl && sizeof(_Tp) == 1)
	  _mm256_mask_storeu_epi8(__mem, __k, __vi);
	else if constexpr (__have_avx512bw_vl && sizeof(_Tp) == 2)
	  _mm256_mask_storeu_epi16(__mem, __k, __vi);
	else if constexpr (__have_avx512vl && sizeof(_Tp) == 4)
	  {
	    if constexpr (__is_aligned_v<_F, 32> && std::is_integral_v<_Tp>)
	      _mm256_mask_store_epi32(__mem, __k, __vi);
	    else if constexpr (__is_aligned_v<_F, 32> &&
			       std::is_floating_point_v<_Tp>)
	      _mm256_mask_store_ps(__mem, __k, __vi);
	    else if constexpr (std::is_integral_v<_Tp>)
	      _mm256_mask_storeu_epi32(__mem, __k, __vi);
	    else
	      _mm256_mask_storeu_ps(__mem, __k, __vi);
	  }
	else if constexpr (__have_avx512vl && sizeof(_Tp) == 8)
	  {
	    if constexpr (__is_aligned_v<_F, 32> && std::is_integral_v<_Tp>)
	      _mm256_mask_store_epi64(__mem, __k, __vi);
	    else if constexpr (__is_aligned_v<_F, 32> &&
			       std::is_floating_point_v<_Tp>)
	      _mm256_mask_store_pd(__mem, __k, __vi);
	    else if constexpr (std::is_integral_v<_Tp>)
	      _mm256_mask_storeu_epi64(__mem, __k, __vi);
	    else
	      _mm256_mask_storeu_pd(__mem, __k, __vi);
	  }
	else if constexpr (__have_avx512f &&
			   (sizeof(_Tp) >= 4 || __have_avx512bw))
	  {
	    // use a 512-bit maskstore, using zero-extension of the bitmask
	    __masked_store_nocvt(
	      _SimdWrapper64<_Tp>(
		__intrin_bitcast<__vector_type64_t<_Tp>>(__v._M_data)),
	      __mem,
	      // careful, vector_aligned has a stricter meaning in the
	      // 512-bit maskstore:
	      std::conditional_t<std::is_same_v<_F, vector_aligned_tag>,
				 overaligned_tag<32>, _F>(),
	      _SimdWrapper<bool, 64 / sizeof(_Tp)>(__k._M_data));
	  }
	else
	  __masked_store_nocvt(
	    __v, __mem, _F(),
	    _MaskImpl::template __to_maskvector<_Tp, 32 / sizeof(_Tp)>(__k));
      }
    else if constexpr (sizeof(__vi) == 16)
      {
	// the store is aligned if _F is overaligned_tag<16> (or higher) or _F
	// is vector_aligned_tag while __v is actually a 16-Byte vector (could
	// be 2/4/8 as well)
	[[maybe_unused]] constexpr bool __aligned =
	  __is_aligned_v<_F, 16> &&
	  (sizeof(__v) == 16 || !std::is_same_v<_F, vector_aligned_tag>);
	if constexpr (__have_avx512bw_vl && sizeof(_Tp) == 1)
	  _mm_mask_storeu_epi8(__mem, __k, __vi);
	else if constexpr (__have_avx512bw_vl && sizeof(_Tp) == 2)
	  _mm_mask_storeu_epi16(__mem, __k, __vi);
	else if constexpr (__have_avx512vl && sizeof(_Tp) == 4)
	  {
	    if constexpr (__aligned && std::is_integral_v<_Tp>)
	      _mm_mask_store_epi32(__mem, __k, __vi);
	    else if constexpr (__aligned && std::is_floating_point_v<_Tp>)
	      _mm_mask_store_ps(__mem, __k, __vi);
	    else if constexpr (std::is_integral_v<_Tp>)
	      _mm_mask_storeu_epi32(__mem, __k, __vi);
	    else
	      _mm_mask_storeu_ps(__mem, __k, __vi);
	  }
	else if constexpr (__have_avx512vl && sizeof(_Tp) == 8)
	  {
	    if constexpr (__aligned && std::is_integral_v<_Tp>)
	      _mm_mask_store_epi64(__mem, __k, __vi);
	    else if constexpr (__aligned && std::is_floating_point_v<_Tp>)
	      _mm_mask_store_pd(__mem, __k, __vi);
	    else if constexpr (std::is_integral_v<_Tp>)
	      _mm_mask_storeu_epi64(__mem, __k, __vi);
	    else
	      _mm_mask_storeu_pd(__mem, __k, __vi);
	  }
	else if constexpr (__have_avx512f &&
			   (sizeof(_Tp) >= 4 || __have_avx512bw))
	  {
	    // use a 512-bit maskstore, using zero-extension of the bitmask
	    __masked_store_nocvt(
	      _SimdWrapper64<_Tp>(
		__intrin_bitcast<__intrinsic_type64_t<_Tp>>(__v._M_data)),
	      __mem,
	      // careful, vector_aligned has a stricter meaning in the 512-bit
	      // maskstore:
	      std::conditional_t<std::is_same_v<_F, vector_aligned_tag>,
				 overaligned_tag<sizeof(__v)>, _F>(),
	      _SimdWrapper<bool, 64 / sizeof(_Tp)>(__k._M_data));
	  }
	else
	  __masked_store_nocvt(
	    __v, __mem, _F(),
	    _MaskImpl::template __to_maskvector<_Tp, 16 / sizeof(_Tp)>(__k));
      }
    else
      __assert_unreachable<_Tp>();
  }

  template <typename _TW,
	    typename _Tp = typename _VectorTraits<_TW>::value_type,
	    typename _F>
  _GLIBCXX_SIMD_INTRINSIC static void
    __masked_store_nocvt(_TW __v, _Tp* __mem, _F, _TW __k)
  {
    if constexpr (sizeof(_TW) <= 16)
      {
	[[maybe_unused]] const auto __vi =
	  __intrin_bitcast<__m128i>(__as_vector(__v));
	[[maybe_unused]] const auto __ki =
	  __intrin_bitcast<__m128i>(__as_vector(__k));
	if constexpr (__have_avx512bw_vl && sizeof(_Tp) == 1)
	  _mm_mask_storeu_epi8(__mem, _mm_movepi8_mask(__ki), __vi);
	else if constexpr (__have_avx512bw_vl && sizeof(_Tp) == 2)
	  _mm_mask_storeu_epi16(__mem, _mm_movepi16_mask(__ki), __vi);
	else if constexpr (__have_avx2 && sizeof(_Tp) == 4 &&
			   std::is_integral_v<_Tp>)
	  _mm_maskstore_epi32(reinterpret_cast<int*>(__mem), __ki, __vi);
	else if constexpr (__have_avx && sizeof(_Tp) == 4)
	  _mm_maskstore_ps(reinterpret_cast<float*>(__mem), __ki,
			   __vector_bitcast<float>(__vi));
	else if constexpr (__have_avx2 && sizeof(_Tp) == 8 &&
			   std::is_integral_v<_Tp>)
	  _mm_maskstore_epi64(reinterpret_cast<_LLong*>(__mem), __ki, __vi);
	else if constexpr (__have_avx && sizeof(_Tp) == 8)
	  _mm_maskstore_pd(reinterpret_cast<double*>(__mem), __ki,
			   __vector_bitcast<double>(__vi));
	else if constexpr (__have_sse2)
	  _mm_maskmoveu_si128(__vi, __ki, reinterpret_cast<char*>(__mem));
      }
    else if constexpr (sizeof(_TW) == 32)
      {
	[[maybe_unused]] const auto __vi =
	  __intrin_bitcast<__m256i>(__as_vector(__v));
	[[maybe_unused]] const auto __ki =
	  __intrin_bitcast<__m256i>(__as_vector(__k));
	if constexpr (__have_avx512bw_vl && sizeof(_Tp) == 1)
	  _mm256_mask_storeu_epi8(__mem, _mm256_movepi8_mask(__ki), __vi);
	else if constexpr (__have_avx512bw_vl && sizeof(_Tp) == 2)
	  _mm256_mask_storeu_epi16(__mem, _mm256_movepi16_mask(__ki), __vi);
	else if constexpr (__have_avx2 && sizeof(_Tp) == 4 &&
			   std::is_integral_v<_Tp>)
	  _mm256_maskstore_epi32(reinterpret_cast<int*>(__mem), __ki, __vi);
	else if constexpr (sizeof(_Tp) == 4)
	  _mm256_maskstore_ps(reinterpret_cast<float*>(__mem), __ki,
			      __vector_bitcast<float>(__v));
	else if constexpr (__have_avx2 && sizeof(_Tp) == 8 &&
			   std::is_integral_v<_Tp>)
	  _mm256_maskstore_epi64(reinterpret_cast<_LLong*>(__mem), __ki, __vi);
	else if constexpr (__have_avx && sizeof(_Tp) == 8)
	  _mm256_maskstore_pd(reinterpret_cast<double*>(__mem), __ki,
			      __vector_bitcast<double>(__v));
	else if constexpr (__have_sse2)
	  {
	    _mm_maskmoveu_si128(__lo128(__vi), __lo128(__ki),
				reinterpret_cast<char*>(__mem));
	    _mm_maskmoveu_si128(__hi128(__vi), __hi128(__ki),
				reinterpret_cast<char*>(__mem) + 16);
	  }
      }
    else
      __assert_unreachable<_Tp>();
  }

  // __masked_store {{{2
  template <class _Tp, size_t _N, class _U, class _F>
  _GLIBCXX_SIMD_INTRINSIC static void
    __masked_store(const _SimdWrapper<_Tp, _N> __v,
		   _U*                         __mem,
		   _F,
		   const _MaskMember<_Tp> __k) noexcept
  {
    if constexpr (std::is_integral_v<_Tp> && std::is_integral_v<_U> &&
		  sizeof(_Tp) > sizeof(_U) && __have_avx512f &&
		  (sizeof(_Tp) >= 4 || __have_avx512bw) &&
		  (sizeof(__v) == 64 || __have_avx512vl))
      { // truncating store
	const auto __vi = __to_intrin(__v);
	const auto __kk = _MaskImpl::__to_bits(__k);
	if constexpr (sizeof(_Tp) == 8 && sizeof(_U) == 4 && sizeof(__vi) == 64)
	  _mm512_mask_cvtepi64_storeu_epi32(__mem, __kk, __vi);
	else if constexpr (sizeof(_Tp) == 8 && sizeof(_U) == 4 &&
			   sizeof(__vi) == 32)
	  _mm256_mask_cvtepi64_storeu_epi32(__mem, __kk, __vi);
	else if constexpr (sizeof(_Tp) == 8 && sizeof(_U) == 4 &&
			   sizeof(__vi) == 16)
	  _mm_mask_cvtepi64_storeu_epi32(__mem, __kk, __vi);
	else if constexpr (sizeof(_Tp) == 8 && sizeof(_U) == 2 &&
			   sizeof(__vi) == 64)
	  _mm512_mask_cvtepi64_storeu_epi16(__mem, __kk, __vi);
	else if constexpr (sizeof(_Tp) == 8 && sizeof(_U) == 2 &&
			   sizeof(__vi) == 32)
	  _mm256_mask_cvtepi64_storeu_epi16(__mem, __kk, __vi);
	else if constexpr (sizeof(_Tp) == 8 && sizeof(_U) == 2 &&
			   sizeof(__vi) == 16)
	  _mm_mask_cvtepi64_storeu_epi16(__mem, __kk, __vi);
	else if constexpr (sizeof(_Tp) == 8 && sizeof(_U) == 1 &&
			   sizeof(__vi) == 64)
	  _mm512_mask_cvtepi64_storeu_epi8(__mem, __kk, __vi);
	else if constexpr (sizeof(_Tp) == 8 && sizeof(_U) == 1 &&
			   sizeof(__vi) == 32)
	  _mm256_mask_cvtepi64_storeu_epi8(__mem, __kk, __vi);
	else if constexpr (sizeof(_Tp) == 8 && sizeof(_U) == 1 &&
			   sizeof(__vi) == 16)
	  _mm_mask_cvtepi64_storeu_epi8(__mem, __kk, __vi);
	else if constexpr (sizeof(_Tp) == 4 && sizeof(_U) == 2 &&
			   sizeof(__vi) == 64)
	  _mm512_mask_cvtepi32_storeu_epi16(__mem, __kk, __vi);
	else if constexpr (sizeof(_Tp) == 4 && sizeof(_U) == 2 &&
			   sizeof(__vi) == 32)
	  _mm256_mask_cvtepi32_storeu_epi16(__mem, __kk, __vi);
	else if constexpr (sizeof(_Tp) == 4 && sizeof(_U) == 2 &&
			   sizeof(__vi) == 16)
	  _mm_mask_cvtepi32_storeu_epi16(__mem, __kk, __vi);
	else if constexpr (sizeof(_Tp) == 4 && sizeof(_U) == 1 &&
			   sizeof(__vi) == 64)
	  _mm512_mask_cvtepi32_storeu_epi8(__mem, __kk, __vi);
	else if constexpr (sizeof(_Tp) == 4 && sizeof(_U) == 1 &&
			   sizeof(__vi) == 32)
	  _mm256_mask_cvtepi32_storeu_epi8(__mem, __kk, __vi);
	else if constexpr (sizeof(_Tp) == 4 && sizeof(_U) == 1 &&
			   sizeof(__vi) == 16)
	  _mm_mask_cvtepi32_storeu_epi8(__mem, __kk, __vi);
	else if constexpr (sizeof(_Tp) == 2 && sizeof(_U) == 1 &&
			   sizeof(__vi) == 64)
	  _mm512_mask_cvtepi16_storeu_epi8(__mem, __kk, __vi);
	else if constexpr (sizeof(_Tp) == 2 && sizeof(_U) == 1 &&
			   sizeof(__vi) == 32)
	  _mm256_mask_cvtepi16_storeu_epi8(__mem, __kk, __vi);
	else if constexpr (sizeof(_Tp) == 2 && sizeof(_U) == 1 &&
			   sizeof(__vi) == 16)
	  _mm_mask_cvtepi16_storeu_epi8(__mem, __kk, __vi);
	else
	  __assert_unreachable<_Tp>();
      }
    else
      _Base::__masked_store(__v, __mem, _F(), __k);
  }

    // __multiplies {{{2
    template <typename _V, typename _VVT = _VectorTraits<_V>>
    _GLIBCXX_SIMD_INTRINSIC static constexpr _V
      __multiplies(_V __x, _V __y)
    {
      using _Tp = typename _VVT::value_type;
      if (__builtin_is_constant_evaluated())
	return __as_vector(__x) * __as_vector(__y);
      else if constexpr (sizeof(_Tp) == 1 && sizeof(_V) == 2)
	{
	  const auto __xs = reinterpret_cast<short>(__x._M_data);
	  const auto __ys = reinterpret_cast<short>(__y._M_data);
	  return reinterpret_cast<__vector_type_t<_Tp, 2>>(
	    short(((__xs * __ys) & 0xff) | ((__xs >> 8) * (__ys & 0xff00))));
	}
      else if constexpr (sizeof(_Tp) == 1 && sizeof(_V) == 4 &&
			 _VVT::_S_partial_width == 3)
	{
	  const auto __xi = reinterpret_cast<int>(__x._M_data);
	  const auto __yi = reinterpret_cast<int>(__y._M_data);
	  return reinterpret_cast<__vector_type_t<_Tp, 3>>(
	    ((__xi * __yi) & 0xff) |
	    (((__xi >> 8) * (__yi & 0xff00)) & 0xff00) |
	    ((__xi >> 16) * (__yi & 0xff0000)));
	}
      else if constexpr (sizeof(_Tp) == 1 && sizeof(_V) == 4)
	{
	  const auto __xi = reinterpret_cast<int>(__x._M_data);
	  const auto __yi = reinterpret_cast<int>(__y._M_data);
	  return reinterpret_cast<__vector_type_t<_Tp, 4>>(
	    ((__xi * __yi) & 0xff) |
	    (((__xi >> 8) * (__yi & 0xff00)) & 0xff00) |
	    (((__xi >> 16) * (__yi & 0xff0000)) & 0xff0000) |
	    ((__xi >> 24) * (__yi & 0xff000000u)));
	}
      else if constexpr (sizeof(_Tp) == 1 && sizeof(_V) == 8 && __have_avx2 &&
			 std::is_signed_v<_Tp>)
	return __convert<typename _VVT::type>(
	  __vector_bitcast<short>(_mm_cvtepi8_epi16(__to_intrin(__x))) *
	  __vector_bitcast<short>(_mm_cvtepi8_epi16(__to_intrin(__y))));
      else if constexpr (sizeof(_Tp) == 1 && sizeof(_V) == 8 && __have_avx2 &&
			 std::is_unsigned_v<_Tp>)
	return __convert<typename _VVT::type>(
	  __vector_bitcast<short>(_mm_cvtepu8_epi16(__to_intrin(__x))) *
	  __vector_bitcast<short>(_mm_cvtepu8_epi16(__to_intrin(__y))));
      else if constexpr (sizeof(_Tp) == 1)
	{
	  // codegen of `x*y` is suboptimal (as of GCC 9.0.1)
	  constexpr int _N = sizeof(_V) >= 16 ? _VVT::_S_width / 2 : 8;
	  using _Vs        = __vector_type_t<short, _N>;
	  const _Vs __even =
	    __vector_bitcast<short, _N>(__x) * __vector_bitcast<short, _N>(__y);
	  const _Vs __high_byte = _Vs() - 256;
	  const _Vs __odd       = (__vector_bitcast<short, _N>(__x) >> 8) *
			    (__vector_bitcast<short, _N>(__y) & __high_byte);
	  if constexpr (__have_avx512bw && sizeof(_V) > 2)
	    return __blend(0xaaaa'aaaa'aaaa'aaaaLL,
			   __vector_bitcast<_Tp>(__even),
			   __vector_bitcast<_Tp>(__odd));
	  else if constexpr (__have_sse4_1 && sizeof(_V) > 2)
	    return __intrin_bitcast<typename _VVT::type>(__blend(__high_byte, __even, __odd));
	  else
	    return __intrin_bitcast<typename _VVT::type>(_Vs(__andnot(__high_byte, __even) | __odd));
	}
      else
	return _Base::__multiplies(__x, __y);
    }

    // __divides {{{2
#ifdef _GLIBCXX_SIMD_WORKAROUND_PR90993
    template <typename _Tp, size_t _N>
    _GLIBCXX_SIMD_INTRINSIC static constexpr _SimdWrapper<_Tp, _N>
      __divides(_SimdWrapper<_Tp, _N> __x, _SimdWrapper<_Tp, _N> __y)
    {
      if (!__builtin_is_constant_evaluated())
	if constexpr (is_integral_v<_Tp> && sizeof(_Tp) <= 4)
	  { // use divps - codegen of `x/y` is suboptimal (as of GCC 9.0.1)
	    using _Float = conditional_t<sizeof(_Tp) == 4, double, float>;
	    constexpr size_t __n_intermediate =
	      std::min(_N, (__have_avx512f ? 64 : __have_avx ? 32 : 16) /
			     sizeof(_Float));
	    using _FloatV = __vector_type_t<_Float, __n_intermediate>;
	    constexpr size_t __n_floatv = __div_roundup(_N, __n_intermediate);
	    using _R                    = __vector_type_t<_Tp, _N>;
	    const auto __xf = __convert_all<_FloatV, __n_floatv>(__x);
	    const auto __yf             = __convert_all<_FloatV, __n_floatv>(
              _Abi::__make_padding_nonzero(__as_vector(__y)));
	    return __call_with_n_evaluations<__n_floatv>(
	      [](auto... __quotients) {
		return __vector_convert<_R>(__quotients...);
	      },
	      [&__xf, &__yf](auto __i) { return __xf[__i] / __yf[__i]; });
	  }
	/* 64-bit int division is potentially optimizable via double division if
	 * the value in __x is small enough and the conversion between
	 * int<->double is efficient enough:
	else if constexpr (is_integral_v<_Tp> && is_unsigned_v<_Tp> &&
			   sizeof(_Tp) == 8)
	  {
	    if constexpr (__have_sse4_1 && sizeof(__x) == 16)
	      {
		if (_mm_test_all_zeros(__x, __m128i{0xffe0'0000'0000'0000ull,
						    0xffe0'0000'0000'0000ull}))
		  {
		    __x._M_data | 0x __vector_convert<__m128d>(__x._M_data)
		  }
	      }
	  }
	  */
      return _Base::__divides(__x, __y);
    }
#endif // _GLIBCXX_SIMD_WORKAROUND_PR90993

    // __bit_shift_left {{{2
    // Notes on UB. C++2a [expr.shift] says:
    // -1- [...] The operands shall be of integral or unscoped enumeration type
    //     and integral promotions are performed. The type of the result is that
    //     of the promoted left operand. The behavior is undefined if the right
    //     operand is negative, or greater than or equal to the width of the
    //     promoted left operand.
    // -2- The value of E1 << E2 is the unique value congruent to E1×2^E2 modulo
    //     2^N, where N is the width of the type of the result.
    //
    // C++17 [expr.shift] says:
    // -2- The value of E1 << E2 is E1 left-shifted E2 bit positions; vacated
    //     bits are zero-filled. If E1 has an unsigned type, the value of the
    //     result is E1 × 2^E2 , reduced modulo one more than the maximum value
    //     representable in the result type. Otherwise, if E1 has a signed type
    //     and non-negative value, and E1 × 2^E2 is representable in the
    //     corresponding unsigned type of the result type, then that value,
    //     converted to the result type, is the resulting value; otherwise, the
    //     behavior is undefined.
    //
    // Consequences:
    // With C++2a signed and unsigned types have the same UB
    // characteristics:
    // - left shift is not UB for 0 <= RHS < max(32, #bits(T))
    //
    // With C++17 there's little room for optimizations because the standard
    // requires all shifts to happen on promoted integrals (i.e. int). Thus,
    // short and char shifts must assume shifts affect bits of neighboring
    // values.
#ifndef _GLIBCXX_SIMD_NO_SHIFT_OPT
    template <typename _Tp, typename _TVT = _VectorTraits<_Tp>>
    inline _GLIBCXX_SIMD_CONST static typename _TVT::type
      __bit_shift_left(_Tp __xx, int __y)
    {
      using _V = typename _TVT::type;
      using _U = typename _TVT::value_type;
      _V __x   = __xx;
      [[maybe_unused]] const auto __ix = __to_intrin(__x);
      if (__builtin_is_constant_evaluated())
	return __x << __y;
#if __cplusplus > 201703
      // after C++17, signed shifts have no UB, and behave just like unsigned
      // shifts
      else if constexpr (sizeof(_U) == 1 && is_signed_v<_U>)
	return __vector_bitcast<_U>(
	  __bit_shift_left(__vector_bitcast<make_unsigned_t<_U>>(__x), __y));
#endif
      else if constexpr (sizeof(_U) == 1)
	{
	  // (cf. https://gcc.gnu.org/bugzilla/show_bug.cgi?id=83894)
	  if (__builtin_constant_p(__y))
	    {
	      if (__y == 0)
		return __x;
	      else if (__y == 1)
		return __x + __x;
	      else if (__y == 2)
		{
		  __x = __x + __x;
		  return __x + __x;
		}
	      else if (__y > 2 && __y < 8)
		{
		  if constexpr (sizeof(__x) > sizeof(unsigned))
		    {
		      const _UChar __mask = 0xff << __y; // precomputed vector
		      return __vector_bitcast<_U>(
			__vector_bitcast<_UChar>(__vector_bitcast<unsigned>(__x)
						 << __y) &
			__mask);
		    }
		  else
		    {
		      const unsigned __mask =
			(0xff & (0xff << __y)) * 0x01010101u;
		      return reinterpret_cast<_V>(
			static_cast<__int_for_sizeof_t<_V>>(
			  unsigned(reinterpret_cast<__int_for_sizeof_t<_V>>(__x)
				   << __y) &
			  __mask));
		    }
		}
	      else if (__y >= 8 && __y < 32)
		return _V();
	      else
		__builtin_unreachable();
	    }
	  // general strategy in the following: use an sllv instead of sll
	  // instruction, because it's 2 to 4 times faster:
	  else if constexpr (__have_avx512bw_vl && sizeof(__x) == 16)
	    return __vector_bitcast<_U>(_mm256_cvtepi16_epi8(_mm256_sllv_epi16(
	      _mm256_cvtepi8_epi16(__ix), _mm256_set1_epi16(__y))));
	  else if constexpr (__have_avx512bw && sizeof(__x) == 32)
	    return __vector_bitcast<_U>(_mm512_cvtepi16_epi8(_mm512_sllv_epi16(
	      _mm512_cvtepi8_epi16(__ix), _mm512_set1_epi16(__y))));
	  else if constexpr (__have_avx512bw && sizeof(__x) == 64)
	    {
	      const auto __shift = _mm512_set1_epi16(__y);
	      return __vector_bitcast<_U>(
		__concat(_mm512_cvtepi16_epi8(_mm512_sllv_epi16(
			   _mm512_cvtepi8_epi16(__lo256(__ix)), __shift)),
			 _mm512_cvtepi16_epi8(_mm512_sllv_epi16(
			   _mm512_cvtepi8_epi16(__hi256(__ix)), __shift))));
	    }
	  else if constexpr (__have_avx2 && sizeof(__x) == 32)
	    {
#if 1
	      const auto __shift = _mm_cvtsi32_si128(__y);
	      auto __k = _mm256_sll_epi16(_mm256_slli_epi16(~__m256i(), 8), __shift);
	      __k |= _mm256_srli_epi16(__k, 8);
	      return __vector_bitcast<_U>(_mm256_sll_epi32(__ix, __shift) &
					  __k);
#else
	      const _U __k = 0xff << __y;
	      return __vector_bitcast<_U>(__vector_bitcast<int>(__x) << __y) &
		     __k;
#endif
	    }
	  else
	    {
	      const auto __shift = _mm_cvtsi32_si128(__y);
	      auto __k = _mm_sll_epi16(_mm_slli_epi16(~__m128i(), 8), __shift);
	      __k |= _mm_srli_epi16(__k, 8);
	      return __intrin_bitcast<_V>(_mm_sll_epi16(__ix, __shift) & __k);
	    }
	}
      return __x << __y;
    }

    template <typename _Tp, typename _TVT = _VectorTraits<_Tp>>
    inline _GLIBCXX_SIMD_CONST static typename _TVT::type
      __bit_shift_left(_Tp __xx, typename _TVT::type __y)
    {
      using _V                         = typename _TVT::type;
      using _U                         = typename _TVT::value_type;
      _V                          __x  = __xx;
      [[maybe_unused]] const auto __ix = __to_intrin(__x);
      [[maybe_unused]] const auto __iy = __to_intrin(__y);
      if (__builtin_is_constant_evaluated())
	return __x << __y;
#if __cplusplus > 201703
      // after C++17, signed shifts have no UB, and behave just like unsigned
      // shifts
      else if constexpr (is_signed_v<_U>)
	return __vector_bitcast<_U>(
	  __bit_shift_left(__vector_bitcast<make_unsigned_t<_U>>(__x),
			   __vector_bitcast<make_unsigned_t<_U>>(__y)));
#endif
      else if constexpr (sizeof(_U) == 1)
	{
	  if constexpr (sizeof __ix == 64 && __have_avx512bw)
	    return __vector_bitcast<_U>(__concat(
	      _mm512_cvtepi16_epi8(
		_mm512_sllv_epi16(_mm512_cvtepu8_epi16(__lo256(__ix)),
				  _mm512_cvtepu8_epi16(__lo256(__iy)))),
	      _mm512_cvtepi16_epi8(
		_mm512_sllv_epi16(_mm512_cvtepu8_epi16(__hi256(__ix)),
				  _mm512_cvtepu8_epi16(__hi256(__iy))))));
	  else if constexpr (sizeof __ix == 32 && __have_avx512bw)
	    return __vector_bitcast<_U>(_mm512_cvtepi16_epi8(_mm512_sllv_epi16(
	      _mm512_cvtepu8_epi16(__ix), _mm512_cvtepu8_epi16(__iy))));
	  else if constexpr (sizeof __x <= 8 && __have_avx512bw_vl)
	    return __intrin_bitcast<_V>(_mm_cvtepi16_epi8(_mm_sllv_epi16(
	      _mm_cvtepu8_epi16(__ix), _mm_cvtepu8_epi16(__iy))));
	  else if constexpr (sizeof __ix == 16 && __have_avx512bw_vl)
	    return __intrin_bitcast<_V>(_mm256_cvtepi16_epi8(_mm256_sllv_epi16(
	      _mm256_cvtepu8_epi16(__ix), _mm256_cvtepu8_epi16(__iy))));
	  else if constexpr (sizeof __ix == 16 && __have_avx512bw)
	    return __intrin_bitcast<_V>(
	      __lo128(_mm512_cvtepi16_epi8(_mm512_sllv_epi16(
		_mm512_cvtepu8_epi16(_mm256_castsi128_si256(__ix)),
		_mm512_cvtepu8_epi16(_mm256_castsi128_si256(__iy))))));
	  else if constexpr (__have_sse4_1 && sizeof(__x) == 16)
	    {
              auto __mask = __vector_bitcast<_U>(__vector_bitcast<short>(__y) << 5);
	      auto __x4   = __vector_bitcast<_U>(__vector_bitcast<short>(__x) << 4);
	      __x4 &= char(0xf0);
              __x = __blend(__mask, __x, __x4);
              __mask += __mask;
	      auto __x2   = __vector_bitcast<_U>(__vector_bitcast<short>(__x) << 2);
	      __x2 &= char(0xfc);
              __x = __blend(__mask, __x, __x2);
              __mask += __mask;
	      auto __x1   = __x + __x;
              __x = __blend(__mask, __x, __x1);
	      return __x & ((__y & char(0xf8)) == 0); // y > 7 nulls the result
	    }
          else if constexpr (sizeof(__x) == 16)
	    {
              auto __mask = __vector_bitcast<_UChar>(__vector_bitcast<short>(__y) << 5);
	      auto __x4   = __vector_bitcast<_U>(__vector_bitcast<short>(__x) << 4);
	      __x4 &= char(0xf0);
              __x = __blend(__vector_bitcast<_SChar>(__mask) < 0, __x, __x4);
              __mask += __mask;
	      auto __x2   = __vector_bitcast<_U>(__vector_bitcast<short>(__x) << 2);
	      __x2 &= char(0xfc);
              __x = __blend(__vector_bitcast<_SChar>(__mask) < 0, __x, __x2);
              __mask += __mask;
	      auto __x1   = __x + __x;
              __x = __blend(__vector_bitcast<_SChar>(__mask) < 0, __x, __x1);
	      return __x & ((__y & char(0xf8)) == 0); // y > 7 nulls the result
	    }
	  else
	    return __x << __y;
	}
      else if constexpr (sizeof(_U) == 2)
	{
	  if constexpr (sizeof __ix == 64 && __have_avx512bw)
	    return __vector_bitcast<_U>(_mm512_sllv_epi16(__ix, __iy));
	  else if constexpr (sizeof __ix == 32 && __have_avx512bw_vl)
	    return __vector_bitcast<_U>(_mm256_sllv_epi16(__ix, __iy));
	  else if constexpr (sizeof __ix == 32 && __have_avx512bw)
	    return __vector_bitcast<_U>(__lo256(_mm512_sllv_epi16(
	      _mm512_castsi256_si512(__ix), _mm512_castsi256_si512(__iy))));
	  else if constexpr (sizeof __ix == 32 && __have_avx2)
	    {
	      const auto __ux = __vector_bitcast<unsigned>(__x);
	      const auto __uy = __vector_bitcast<unsigned>(__y);
	      return __vector_bitcast<_U>(_mm256_blend_epi16(
		__auto_bitcast(__ux << (__uy & 0x0000ffffu)),
		__auto_bitcast((__ux & 0xffff0000u) << (__uy >> 16)), 0xaa));
	    }
	  else if constexpr (sizeof __ix == 16 && __have_avx512bw_vl)
	    return __intrin_bitcast<_V>(_mm_sllv_epi16(__ix, __iy));
	  else if constexpr (sizeof __ix == 16 && __have_avx512bw)
	    return __intrin_bitcast<_V>(__lo128(_mm512_sllv_epi16(
	      _mm512_castsi128_si512(__ix), _mm512_castsi128_si512(__iy))));
	  else if constexpr (sizeof __ix == 16 && __have_avx2)
	    {
	      const auto __ux = __vector_bitcast<unsigned>(__ix);
	      const auto __uy = __vector_bitcast<unsigned>(__iy);
	      return __intrin_bitcast<_V>(_mm_blend_epi16(
		__auto_bitcast(__ux << (__uy & 0x0000ffffu)),
		__auto_bitcast((__ux & 0xffff0000u) << (__uy >> 16)), 0xaa));
	    }
	  else if constexpr (sizeof __ix == 16)
	    {
	      __y += 0x3f8 >> 3;
	      return __x *
		     __intrin_bitcast<_V>(
		       __vector_convert<__vector_type16_t<int>>(
			 __vector_bitcast<float>(
			   __vector_bitcast<unsigned>(__to_intrin(__y))
			   << 23)) |
		       (__vector_convert<__vector_type16_t<int>>(
			  __vector_bitcast<float>(
			    (__vector_bitcast<unsigned>(__to_intrin(__y)) >> 16)
			    << 23))
			<< 16));
	    }
	  else
	    __assert_unreachable<_Tp>();
	}
      else if constexpr (sizeof(_U) == 4 && sizeof __ix == 16 && !__have_avx2)
        // latency is suboptimal, but throughput is at full speedup
	return __intrin_bitcast<_V>(
	  __vector_bitcast<unsigned>(__ix) *
	  __vector_convert<__vector_type16_t<int>>(__vector_bitcast<float>(
	    (__vector_bitcast<unsigned, 4>(__y) << 23) + 0x3f80'0000)));
      else if constexpr (sizeof(_U) == 8 && sizeof __ix == 16 && !__have_avx2)
	{
	  const auto __lo = _mm_sll_epi64(__ix, __iy);
	  const auto __hi = _mm_sll_epi64(__ix, _mm_unpackhi_epi64(__iy, __iy));
	  if constexpr (__have_sse4_1)
	    return __vector_bitcast<_U>(_mm_blend_epi16(__lo, __hi, 0xf0));
	  else
	    return __vector_bitcast<_U>(_mm_move_sd(
	      __vector_bitcast<double>(__hi), __vector_bitcast<double>(__lo)));
	}
      else
	return __x << __y;
    }
#endif // _GLIBCXX_SIMD_NO_SHIFT_OPT

    // __bit_shift_right {{{2
#ifndef _GLIBCXX_SIMD_NO_SHIFT_OPT
    template <typename _Tp, typename _TVT = _VectorTraits<_Tp>>
    inline _GLIBCXX_SIMD_CONST static typename _TVT::type
      __bit_shift_right(_Tp __xx, int __y)
    {
      using _V = typename _TVT::type;
      using _U = typename _TVT::value_type;
      _V __x   = __xx;
      [[maybe_unused]] const auto __ix = __to_intrin(__x);
      if (__builtin_is_constant_evaluated())
	return __x >> __y;
      else if (__builtin_constant_p(__y) && std::is_unsigned_v<_U> &&
	       __y >= int(sizeof(_U) * CHAR_BIT))
	return _V();
      else if constexpr (sizeof(_U) == 1 && is_unsigned_v<_U>) //{{{
	return __intrin_bitcast<_V>(__vector_bitcast<_UShort>(__ix) >> __y) &
	       _U(0xff >> __y);
      //}}}
      else if constexpr (sizeof(_U) == 1 && is_signed_v<_U>) //{{{
	return __intrin_bitcast<_V>(
	  (__vector_bitcast<_UShort>(__vector_bitcast<short>(__ix) >> (__y + 8))
	   << 8) |
	  (__vector_bitcast<_UShort>(
	     __vector_bitcast<short>(__vector_bitcast<_UShort>(__ix) << 8) >>
	     __y) >>
	   8));
      //}}}
      // GCC optimizes sizeof == 2, 4, and unsigned 8 as expected
      else if constexpr (sizeof(_U) == 8 && is_signed_v<_U>) //{{{
      {
	if (__y > 32)
	  return (__intrin_bitcast<_V>(__vector_bitcast<int>(__ix) >> 32) &
		  _U(0xffff'ffff'0000'0000ull)) |
		 __vector_bitcast<_U>(__vector_bitcast<int>(
					__vector_bitcast<_ULLong>(__ix) >> 32) >>
				      (__y - 32));
	else
	  return __intrin_bitcast<_V>(__vector_bitcast<_ULLong>(__ix) >> __y) |
		 __vector_bitcast<_U>(
		   __vector_bitcast<int>(__ix & -0x8000'0000'0000'0000ll) >>
		   __y);
      }
      //}}}
      else
	return __x >> __y;
    }

    template <typename _Tp, typename _TVT = _VectorTraits<_Tp>>
    inline _GLIBCXX_SIMD_CONST static typename _TVT::type
      __bit_shift_right(_Tp __xx, typename _TVT::type __y)
    {
      using _V                         = typename _TVT::type;
      using _U                         = typename _TVT::value_type;
      _V                          __x  = __xx;
      [[maybe_unused]] const auto __ix = __to_intrin(__x);
      [[maybe_unused]] const auto __iy = __to_intrin(__y);
      if (__builtin_is_constant_evaluated())
	return __x >> __y;
      else if constexpr (sizeof(_U) == 1) //{{{
	{
	  if constexpr (sizeof(__x) <= 8 && __have_avx512bw_vl)
	    return __intrin_bitcast<_V>(_mm_cvtepi16_epi8(
	      is_signed_v<_U> ? _mm_srav_epi16(_mm_cvtepi8_epi16(__ix),
					       _mm_cvtepi8_epi16(__iy))
			      : _mm_srlv_epi16(_mm_cvtepu8_epi16(__ix),
					       _mm_cvtepu8_epi16(__iy))));
	  if constexpr (sizeof(__x) == 16 && __have_avx512bw_vl)
	    return __intrin_bitcast<_V>(_mm256_cvtepi16_epi8(
	      is_signed_v<_U> ? _mm256_srav_epi16(_mm256_cvtepi8_epi16(__ix),
						  _mm256_cvtepi8_epi16(__iy))
			      : _mm256_srlv_epi16(_mm256_cvtepu8_epi16(__ix),
						  _mm256_cvtepu8_epi16(__iy))));
	  else if constexpr (sizeof(__x) == 32 && __have_avx512bw)
	    return __vector_bitcast<_U>(_mm512_cvtepi16_epi8(
	      is_signed_v<_U> ? _mm512_srav_epi16(_mm512_cvtepi8_epi16(__ix),
						  _mm512_cvtepi8_epi16(__iy))
			      : _mm512_srlv_epi16(_mm512_cvtepu8_epi16(__ix),
						  _mm512_cvtepu8_epi16(__iy))));
	  else if constexpr (sizeof(__x) == 64 && is_signed_v<_U>)
	    return __vector_bitcast<_U>(_mm512_mask_mov_epi8(
	      _mm512_srav_epi16(__ix, _mm512_srli_epi16(__iy, 8)),
	      0x5555'5555'5555'5555ull,
	      _mm512_srav_epi16(_mm512_slli_epi16(__ix, 8),
				_mm512_maskz_add_epi8(0x5555'5555'5555'5555ull,
						      __iy,
						      _mm512_set1_epi16(8)))));
	  else if constexpr (sizeof(__x) == 64 && is_unsigned_v<_U>)
	    return __vector_bitcast<_U>(_mm512_mask_mov_epi8(
	      _mm512_srlv_epi16(__ix, _mm512_srli_epi16(__iy, 8)),
	      0x5555'5555'5555'5555ull,
	      _mm512_srlv_epi16(
		_mm512_maskz_mov_epi8(0x5555'5555'5555'5555ull, __ix),
		_mm512_maskz_mov_epi8(0x5555'5555'5555'5555ull, __iy))));
	  /* This has better throughput but higher latency than the impl below
	  else if constexpr (__have_avx2 && sizeof(__x) == 16 &&
			     is_unsigned_v<_U>)
	    {
	      const auto __shorts = __to_intrin(__bit_shift_right(
		__vector_bitcast<_UShort>(_mm256_cvtepu8_epi16(__ix)),
		__vector_bitcast<_UShort>(_mm256_cvtepu8_epi16(__iy))));
	      return __vector_bitcast<_U>(
		_mm_packus_epi16(__lo128(__shorts), __hi128(__shorts)));
	    }
	    */
	  else if constexpr (__have_avx2 && sizeof(__x) > 8)
	    // the following uses vpsr[al]vd, which requires AVX2
	    if constexpr (is_signed_v<_U>)
	      {
		const auto r3 = __vector_bitcast<_UInt>(
				  (__vector_bitcast<int>(__x) >>
				   (__vector_bitcast<_UInt>(__y) >> 24))) &
				0xff000000u;
		const auto r2 =
		  __vector_bitcast<_UInt>(
		    ((__vector_bitcast<int>(__x) << 8) >>
		     ((__vector_bitcast<_UInt>(__y) << 8) >> 24))) &
		  0xff000000u;
		const auto r1 =
		  __vector_bitcast<_UInt>(
		    ((__vector_bitcast<int>(__x) << 16) >>
		     ((__vector_bitcast<_UInt>(__y) << 16) >> 24))) &
		  0xff000000u;
		const auto r0 = __vector_bitcast<_UInt>(
		  (__vector_bitcast<int>(__x) << 24) >>
		  ((__vector_bitcast<_UInt>(__y) << 24) >> 24));
		return __vector_bitcast<_U>(r3 | (r2 >> 8) | (r1 >> 16) |
					    (r0 >> 24));
	      }
	    else
	      {
		const auto r3 = (__vector_bitcast<_UInt>(__x) >>
				 (__vector_bitcast<_UInt>(__y) >> 24)) &
				0xff000000u;
		const auto r2 = ((__vector_bitcast<_UInt>(__x) << 8) >>
				 ((__vector_bitcast<_UInt>(__y) << 8) >> 24)) &
				0xff000000u;
		const auto r1 = ((__vector_bitcast<_UInt>(__x) << 16) >>
				 ((__vector_bitcast<_UInt>(__y) << 16) >> 24)) &
				0xff000000u;
		const auto r0 = (__vector_bitcast<_UInt>(__x) << 24) >>
				((__vector_bitcast<_UInt>(__y) << 24) >> 24);
		return __vector_bitcast<_U>(r3 | (r2 >> 8) | (r1 >> 16) |
					    (r0 >> 24));
	      }
	  else if constexpr (__have_sse4_1 && is_unsigned_v<_U> && sizeof(__x) > 2)
	    {
	      auto __x128 = __vector_bitcast<_U>(__ix);
	      auto __mask =
		__vector_bitcast<_U>(__vector_bitcast<_UShort>(__iy) << 5);
	      auto __x4 = __vector_bitcast<_U>(
		(__vector_bitcast<_UShort>(__x128) >> 4) & _UShort(0xff0f));
	      __x128 = __blend(__mask, __x128, __x4);
	      __mask += __mask;
	      auto __x2 = __vector_bitcast<_U>(
		(__vector_bitcast<_UShort>(__x128) >> 2) & _UShort(0xff3f));
	      __x128 = __blend(__mask, __x128, __x2);
	      __mask += __mask;
	      auto __x1 = __vector_bitcast<_U>(
		(__vector_bitcast<_UShort>(__x128) >> 1) & _UShort(0xff7f));
	      __x128 = __blend(__mask, __x128, __x1);
	      return __intrin_bitcast<_V>(
		__x128 & ((__vector_bitcast<_U>(__iy) & char(0xf8)) ==
			  0)); // y > 7 nulls the result
	    }
	  else if constexpr (__have_sse4_1 && is_signed_v<_U> && sizeof(__x) > 2)
	    {
	      auto __mask =
		__vector_bitcast<_UChar>(__vector_bitcast<_UShort>(__iy) << 5);
	      auto __maskl = [&]() {
		return __vector_bitcast<_UShort>(__mask) << 8;
	      };
	      auto __xh  = __vector_bitcast<short>(__ix);
	      auto __xl  = __vector_bitcast<short>(__ix) << 8;
	      auto __xh4 = __xh >> 4;
	      auto __xl4 = __xl >> 4;
	      __xh       = __blend(__mask, __xh, __xh4);
	      __xl       = __blend(__maskl(), __xl, __xl4);
	      __mask += __mask;
	      auto __xh2 = __xh >> 2;
	      auto __xl2 = __xl >> 2;
	      __xh       = __blend(__mask, __xh, __xh2);
	      __xl       = __blend(__maskl(), __xl, __xl2);
	      __mask += __mask;
	      auto __xh1 = __xh >> 1;
	      auto __xl1 = __xl >> 1;
	      __xh       = __blend(__mask, __xh, __xh1);
	      __xl       = __blend(__maskl(), __xl, __xl1);
	      return __intrin_bitcast<_V>(
		(__vector_bitcast<_U>((__xh & short(0xff00))) |
		 __vector_bitcast<_U>(__vector_bitcast<_UShort>(__xl) >> 8)) &
		((__vector_bitcast<_U>(__iy) & char(0xf8)) ==
		 0)); // y > 7 nulls the result
	    }
	  else if constexpr (is_unsigned_v<_U> && sizeof(__x) > 2) // SSE2
	    {
	      auto __mask =
		__vector_bitcast<_U>(__vector_bitcast<_UShort>(__y) << 5);
	      auto __x4 = __vector_bitcast<_U>(
		(__vector_bitcast<_UShort>(__x) >> 4) & _UShort(0xff0f));
	      __x = __blend(__mask > 0x7f, __x, __x4);
	      __mask += __mask;
	      auto __x2 = __vector_bitcast<_U>(
		(__vector_bitcast<_UShort>(__x) >> 2) & _UShort(0xff3f));
	      __x = __blend(__mask > 0x7f, __x, __x2);
	      __mask += __mask;
	      auto __x1 = __vector_bitcast<_U>(
		(__vector_bitcast<_UShort>(__x) >> 1) & _UShort(0xff7f));
	      __x = __blend(__mask > 0x7f, __x, __x1);
	      return __x & ((__y & char(0xf8)) == 0); // y > 7 nulls the result
	    }
	  else if constexpr (sizeof(__x) > 2) // signed SSE2
	    {
	      static_assert(is_signed_v<_U>);
	      auto __maskh = __vector_bitcast<_UShort>(__y) << 5;
	      auto __maskl = __vector_bitcast<_UShort>(__y) << (5 + 8);
	      auto __xh  = __vector_bitcast<short>(__x);
	      auto __xl  = __vector_bitcast<short>(__x) << 8;
	      auto __xh4 = __xh >> 4;
	      auto __xl4 = __xl >> 4;
	      __xh       = __blend(__maskh > 0x7fff, __xh, __xh4);
	      __xl       = __blend(__maskl > 0x7fff, __xl, __xl4);
	      __maskh += __maskh;
	      __maskl += __maskl;
	      auto __xh2 = __xh >> 2;
	      auto __xl2 = __xl >> 2;
	      __xh       = __blend(__maskh > 0x7fff, __xh, __xh2);
	      __xl       = __blend(__maskl > 0x7fff, __xl, __xl2);
	      __maskh += __maskh;
	      __maskl += __maskl;
	      auto __xh1 = __xh >> 1;
	      auto __xl1 = __xl >> 1;
	      __xh       = __blend(__maskh > 0x7fff, __xh, __xh1);
	      __xl       = __blend(__maskl > 0x7fff, __xl, __xl1);
	      __x        = __vector_bitcast<_U>((__xh & short(0xff00))) |
		    __vector_bitcast<_U>(__vector_bitcast<_UShort>(__xl) >> 8);
	      return __x & ((__y & char(0xf8)) == 0); // y > 7 nulls the result
	    }
	  else
	    return __x >> __y;
	} //}}}
      else if constexpr (sizeof(_U) == 2 && sizeof(__x) >= 4) //{{{
	{
	  [[maybe_unused]] auto __blend_0xaa =
	    [](auto __a, auto __b) {
	      if constexpr (sizeof(__a) == 16)
		return _mm_blend_epi16(__to_intrin(__a), __to_intrin(__b),
				       0xaa);
	      else if constexpr (sizeof(__a) == 32)
		return _mm256_blend_epi16(__to_intrin(__a), __to_intrin(__b),
					  0xaa);
	      else if constexpr (sizeof(__a) == 64)
		return _mm512_mask_blend_epi16(0xaaaa'aaaaU, __to_intrin(__a),
					       __to_intrin(__b));
	      else
		__assert_unreachable<decltype(__a)>();
	    };
	  if constexpr (__have_avx512bw_vl && sizeof(_Tp) <= 16)
	    return __intrin_bitcast<_V>(is_signed_v<_U>
					  ? _mm_srav_epi16(__ix, __iy)
					  : _mm_srlv_epi16(__ix, __iy));
	  else if constexpr (__have_avx512bw_vl && sizeof(_Tp) == 32)
	    return __vector_bitcast<_U>(is_signed_v<_U>
					  ? _mm256_srav_epi16(__ix, __iy)
					  : _mm256_srlv_epi16(__ix, __iy));
	  else if constexpr (__have_avx512bw && sizeof(_Tp) == 64)
	    return __vector_bitcast<_U>(is_signed_v<_U>
					  ? _mm512_srav_epi16(__ix, __iy)
					  : _mm512_srlv_epi16(__ix, __iy));
	  else if constexpr (__have_avx2 && is_signed_v<_U>)
	    return __intrin_bitcast<_V>(
	      __blend_0xaa(((__vector_bitcast<int>(__ix) << 16) >>
			     (__vector_bitcast<int>(__iy) & 0xffffu)) >> 16,
			   __vector_bitcast<int>(__ix) >>
			     (__vector_bitcast<int>(__iy) >> 16)));
	  else if constexpr (__have_avx2 && is_unsigned_v<_U>)
	    return __intrin_bitcast<_V>(
	      __blend_0xaa((__vector_bitcast<_UInt>(__ix) & 0xffffu) >>
			     (__vector_bitcast<_UInt>(__iy) & 0xffffu),
			   __vector_bitcast<_UInt>(__ix) >>
			     (__vector_bitcast<_UInt>(__iy) >> 16)));
	  else if constexpr (__have_sse4_1)
	    {
	      auto __mask = __vector_bitcast<_UShort>(__iy);
	      auto __x128 = __vector_bitcast<_U>(__ix);
	      //__mask *= 0x0808;
	      __mask = (__mask << 3) | (__mask << 11);
	      // do __x128 = 0 where __y[4] is set
	      __x128 = __blend(__mask, __x128, decltype(__x128)());
	      // do __x128 =>> 8 where __y[3] is set
	      __x128 = __blend(__mask += __mask, __x128, __x128 >> 8);
	      // do __x128 =>> 4 where __y[2] is set
	      __x128 = __blend(__mask += __mask, __x128, __x128 >> 4);
	      // do __x128 =>> 2 where __y[1] is set
	      __x128 = __blend(__mask += __mask, __x128, __x128 >> 2);
	      // do __x128 =>> 1 where __y[0] is set
	      return __intrin_bitcast<_V>(__blend(__mask + __mask, __x128, __x128 >> 1));
	    }
	  else
	    {
	      auto __k = __vector_bitcast<_UShort>(__iy) << 11;
	      auto __x128 = __vector_bitcast<_U>(__ix);
	      auto __mask = [](__vector_type16_t<_UShort> __kk) {
		return __vector_bitcast<short>(__kk) < 0;
	      };
	      // do __x128 = 0 where __y[4] is set
	      __x128 = __blend(__mask(__k), __x128, decltype(__x128)());
	      // do __x128 =>> 8 where __y[3] is set
	      __x128 = __blend(__mask(__k += __k), __x128, __x128 >> 8);
	      // do __x128 =>> 4 where __y[2] is set
	      __x128 = __blend(__mask(__k += __k), __x128, __x128 >> 4);
	      // do __x128 =>> 2 where __y[1] is set
	      __x128 = __blend(__mask(__k += __k), __x128, __x128 >> 2);
	      // do __x128 =>> 1 where __y[0] is set
	      return __intrin_bitcast<_V>(__blend(__mask(__k + __k), __x128, __x128 >> 1));
	    }
	} //}}}
      else if constexpr (sizeof(_U) == 4 && !__have_avx2) //{{{
	{
	  if constexpr (is_unsigned_v<_U>)
	    {
	      // x >> y == x * 2^-y == (x * 2^(31-y)) >> 31
	      const __m128 __factor_f = reinterpret_cast<__m128>(
		0x4f00'0000u - (__vector_bitcast<unsigned, 4>(__y) << 23));
	      const __m128i __factor = __builtin_constant_p(__factor_f)
					 ? __to_intrin(__make_vector<int>(
					     __factor_f[0], __factor_f[1],
					     __factor_f[2], __factor_f[3]))
					 : _mm_cvttps_epi32(__factor_f);
	      const auto __r02 = _mm_srli_epi64(_mm_mul_epu32(__ix, __factor), 31);
	      const auto __r13 = _mm_mul_epu32(_mm_srli_si128(__ix, 4),
					       _mm_srli_si128(__factor, 4));
	      if constexpr (__have_sse4_1)
		return __intrin_bitcast<_V>(
		  _mm_blend_epi16(_mm_slli_epi64(__r13, 1), __r02, 0x33));
	      else
		return __intrin_bitcast<_V>(
		  __r02 | _mm_slli_si128(_mm_srli_epi64(__r13, 31), 4));
	    }
	  else
	    {
	      auto __shift = [](auto __a, auto __b) {
		if constexpr (is_signed_v<_U>)
		  return _mm_sra_epi32(__a, __b);
		else
		  return _mm_srl_epi32(__a, __b);
	      };
	      const auto __r0 =
		__shift(__ix, _mm_unpacklo_epi32(__iy, __m128i()));
	      const auto __r1 = __shift(__ix, _mm_srli_epi64(__iy, 32));
	      const auto __r2 =
		__shift(__ix, _mm_unpackhi_epi32(__iy, __m128i()));
	      const auto __r3 = __shift(__ix, _mm_srli_si128(__iy, 12));
	      if constexpr (__have_sse4_1)
		return __intrin_bitcast<_V>(
		  _mm_blend_epi16(_mm_blend_epi16(__r1, __r0, 0x3),
				  _mm_blend_epi16(__r3, __r2, 0x30), 0xf0));
	      else
		return __intrin_bitcast<_V>(_mm_unpacklo_epi64(
		  _mm_unpacklo_epi32(__r0, _mm_srli_si128(__r1, 4)),
		  _mm_unpackhi_epi32(__r2, _mm_srli_si128(__r3, 4))));
	    }
	} //}}}
      else
	return __x >> __y;
    }
#endif // _GLIBCXX_SIMD_NO_SHIFT_OPT

    // compares {{{2
    // __equal_to {{{3
    template <class _Tp, size_t _N>
    _GLIBCXX_SIMD_INTRINSIC static constexpr _MaskMember<_Tp> __equal_to(
        _SimdWrapper<_Tp, _N> __x, _SimdWrapper<_Tp, _N> __y)
    {
      if constexpr (__is_avx512_abi<_Abi>())
	{
	  constexpr auto __k1 = _Abi::template __implicit_mask<_Tp>();
	  [[maybe_unused]] const auto __xi = __to_intrin(__x);
	  [[maybe_unused]] const auto __yi = __to_intrin(__y);
	  if constexpr (std::is_floating_point_v<_Tp>)
	    {
	      if constexpr (sizeof(__xi) == 64 && sizeof(_Tp) == 8)
		return _mm512_mask_cmp_pd_mask(__k1, __xi, __yi, _CMP_EQ_OQ);
	      else if constexpr (sizeof(__xi) == 64 && sizeof(_Tp) == 4)
		return _mm512_mask_cmp_ps_mask(__k1, __xi, __yi, _CMP_EQ_OQ);
	      else if constexpr (sizeof(__xi) == 32 && sizeof(_Tp) == 8)
		return _mm256_mask_cmp_pd_mask(__k1, __xi, __yi, _CMP_EQ_OQ);
	      else if constexpr (sizeof(__xi) == 32 && sizeof(_Tp) == 4)
		return _mm256_mask_cmp_ps_mask(__k1, __xi, __yi, _CMP_EQ_OQ);
	      else if constexpr (sizeof(__xi) == 16 && sizeof(_Tp) == 8)
		return _mm_mask_cmp_pd_mask(__k1, __xi, __yi, _CMP_EQ_OQ);
	      else if constexpr (sizeof(__xi) == 16 && sizeof(_Tp) == 4)
		return _mm_mask_cmp_ps_mask(__k1, __xi, __yi, _CMP_EQ_OQ);
	      else
		__assert_unreachable<_Tp>();
	    }
	  else if constexpr (sizeof(__xi) == 64 && sizeof(_Tp) == 8)
	    return _mm512_mask_cmpeq_epi64_mask(__k1, __xi, __yi);
	  else if constexpr (sizeof(__xi) == 64 && sizeof(_Tp) == 4)
	    return _mm512_mask_cmpeq_epi32_mask(__k1, __xi, __yi);
	  else if constexpr (sizeof(__xi) == 64 && sizeof(_Tp) == 2)
	    return _mm512_mask_cmpeq_epi16_mask(__k1, __xi, __yi);
	  else if constexpr (sizeof(__xi) == 64 && sizeof(_Tp) == 1)
	    return _mm512_mask_cmpeq_epi8_mask(__k1, __xi, __yi);
	  else if constexpr (sizeof(__xi) == 32 && sizeof(_Tp) == 8)
	    return _mm256_mask_cmpeq_epi64_mask(__k1, __xi, __yi);
	  else if constexpr (sizeof(__xi) == 32 && sizeof(_Tp) == 4)
	    return _mm256_mask_cmpeq_epi32_mask(__k1, __xi, __yi);
	  else if constexpr (sizeof(__xi) == 32 && sizeof(_Tp) == 2)
	    return _mm256_mask_cmpeq_epi16_mask(__k1, __xi, __yi);
	  else if constexpr (sizeof(__xi) == 32 && sizeof(_Tp) == 1)
	    return _mm256_mask_cmpeq_epi8_mask(__k1, __xi, __yi);
	  else if constexpr (sizeof(__xi) == 16 && sizeof(_Tp) == 8)
	    return _mm_mask_cmpeq_epi64_mask(__k1, __xi, __yi);
	  else if constexpr (sizeof(__xi) == 16 && sizeof(_Tp) == 4)
	    return _mm_mask_cmpeq_epi32_mask(__k1, __xi, __yi);
	  else if constexpr (sizeof(__xi) == 16 && sizeof(_Tp) == 2)
	    return _mm_mask_cmpeq_epi16_mask(__k1, __xi, __yi);
	  else if constexpr (sizeof(__xi) == 16 && sizeof(_Tp) == 1)
	    return _mm_mask_cmpeq_epi8_mask(__k1, __xi, __yi);
	  else
	    __assert_unreachable<_Tp>();
	}
      else
	return _Base::__equal_to(__x,__y);
    }

    // __not_equal_to {{{3
    template <class _Tp, size_t _N>
    _GLIBCXX_SIMD_INTRINSIC static constexpr _MaskMember<_Tp>
      __not_equal_to(_SimdWrapper<_Tp, _N> __x, _SimdWrapper<_Tp, _N> __y)
    {
      if constexpr (__is_avx512_abi<_Abi>())
	{
	  constexpr auto __k1 = _Abi::template __implicit_mask<_Tp>();
	  [[maybe_unused]] const auto __xi = __to_intrin(__x);
	  [[maybe_unused]] const auto __yi = __to_intrin(__y);
	  if constexpr (std::is_floating_point_v<_Tp>)
	    {
	      if constexpr (sizeof(__xi) == 64 && sizeof(_Tp) == 8)
		return _mm512_mask_cmp_pd_mask(__k1, __xi, __yi, _CMP_NEQ_UQ);
	      else if constexpr (sizeof(__xi) == 64 && sizeof(_Tp) == 4)
		return _mm512_mask_cmp_ps_mask(__k1, __xi, __yi, _CMP_NEQ_UQ);
	      else if constexpr (sizeof(__xi) == 32 && sizeof(_Tp) == 8)
		return _mm256_mask_cmp_pd_mask(__k1, __xi, __yi, _CMP_NEQ_UQ);
	      else if constexpr (sizeof(__xi) == 32 && sizeof(_Tp) == 4)
		return _mm256_mask_cmp_ps_mask(__k1, __xi, __yi, _CMP_NEQ_UQ);
	      else if constexpr (sizeof(__xi) == 16 && sizeof(_Tp) == 8)
		return _mm_mask_cmp_pd_mask(__k1, __xi, __yi, _CMP_NEQ_UQ);
	      else if constexpr (sizeof(__xi) == 16 && sizeof(_Tp) == 4)
		return _mm_mask_cmp_ps_mask(__k1, __xi, __yi, _CMP_NEQ_UQ);
	      else
		__assert_unreachable<_Tp>();
	    }
	  else if constexpr (sizeof(__xi) == 64 && sizeof(_Tp) == 8)
	    return ~_mm512_mask_cmpeq_epi64_mask(__k1, __xi, __yi);
	  else if constexpr (sizeof(__xi) == 64 && sizeof(_Tp) == 4)
	    return ~_mm512_mask_cmpeq_epi32_mask(__k1, __xi, __yi);
	  else if constexpr (sizeof(__xi) == 64 && sizeof(_Tp) == 2)
	    return ~_mm512_mask_cmpeq_epi16_mask(__k1, __xi, __yi);
	  else if constexpr (sizeof(__xi) == 64 && sizeof(_Tp) == 1)
	    return ~_mm512_mask_cmpeq_epi8_mask(__k1, __xi, __yi);
	  else if constexpr (sizeof(__xi) == 32 && sizeof(_Tp) == 8)
	    return ~_mm256_mask_cmpeq_epi64_mask(__k1, __xi, __yi);
	  else if constexpr (sizeof(__xi) == 32 && sizeof(_Tp) == 4)
	    return ~_mm256_mask_cmpeq_epi32_mask(__k1, __xi, __yi);
	  else if constexpr (sizeof(__xi) == 32 && sizeof(_Tp) == 2)
	    return ~_mm256_mask_cmpeq_epi16_mask(__k1, __xi, __yi);
	  else if constexpr (sizeof(__xi) == 32 && sizeof(_Tp) == 1)
	    return ~_mm256_mask_cmpeq_epi8_mask(__k1, __xi, __yi);
	  else if constexpr (sizeof(__xi) == 16 && sizeof(_Tp) == 8)
	    return ~_mm_mask_cmpeq_epi64_mask(__k1, __xi, __yi);
	  else if constexpr (sizeof(__xi) == 16 && sizeof(_Tp) == 4)
	    return ~_mm_mask_cmpeq_epi32_mask(__k1, __xi, __yi);
	  else if constexpr (sizeof(__xi) == 16 && sizeof(_Tp) == 2)
	    return ~_mm_mask_cmpeq_epi16_mask(__k1, __xi, __yi);
	  else if constexpr (sizeof(__xi) == 16 && sizeof(_Tp) == 1)
	    return ~_mm_mask_cmpeq_epi8_mask(__k1, __xi, __yi);
	  else
	    __assert_unreachable<_Tp>();
	}
      else
	return _Base::__not_equal_to(__x, __y);
    }

    // __less {{{3
    template <class _Tp, size_t _N>
    _GLIBCXX_SIMD_INTRINSIC static constexpr _MaskMember<_Tp>
      __less(_SimdWrapper<_Tp, _N> __x, _SimdWrapper<_Tp, _N> __y)
    {
      if constexpr (__is_avx512_abi<_Abi>())
	{
	  constexpr auto __k1 = _Abi::template __implicit_mask<_Tp>();
	  [[maybe_unused]] const auto __xi = __to_intrin(__x);
	  [[maybe_unused]] const auto __yi = __to_intrin(__y);
	  if constexpr (sizeof(__xi) == 64)
	    {
	      if constexpr (std::is_same_v<_Tp, float>)
		return _mm512_mask_cmp_ps_mask(__k1, __xi, __yi, _CMP_LT_OS);
	      else if constexpr (std::is_same_v<_Tp, double>)
		return _mm512_mask_cmp_pd_mask(__k1, __xi, __yi, _CMP_LT_OS);
	      else if constexpr (std::is_signed_v<_Tp> && sizeof(_Tp) == 1)
		return _mm512_mask_cmplt_epi8_mask(__k1, __xi, __yi);
	      else if constexpr (std::is_signed_v<_Tp> && sizeof(_Tp) == 2)
		return _mm512_mask_cmplt_epi16_mask(__k1, __xi, __yi);
	      else if constexpr (std::is_signed_v<_Tp> && sizeof(_Tp) == 4)
		return _mm512_mask_cmplt_epi32_mask(__k1, __xi, __yi);
	      else if constexpr (std::is_signed_v<_Tp> && sizeof(_Tp) == 8)
		return _mm512_mask_cmplt_epi64_mask(__k1, __xi, __yi);
	      else if constexpr (std::is_unsigned_v<_Tp> && sizeof(_Tp) == 1)
		return _mm512_mask_cmplt_epu8_mask(__k1, __xi, __yi);
	      else if constexpr (std::is_unsigned_v<_Tp> && sizeof(_Tp) == 2)
		return _mm512_mask_cmplt_epu16_mask(__k1, __xi, __yi);
	      else if constexpr (std::is_unsigned_v<_Tp> && sizeof(_Tp) == 4)
		return _mm512_mask_cmplt_epu32_mask(__k1, __xi, __yi);
	      else if constexpr (std::is_unsigned_v<_Tp> && sizeof(_Tp) == 8)
		return _mm512_mask_cmplt_epu64_mask(__k1, __xi, __yi);
	      else
		__assert_unreachable<_Tp>();
	    }
	  else if constexpr (sizeof(__xi) == 32)
	    {
	      if constexpr (std::is_same_v<_Tp, float>)
		return _mm256_mask_cmp_ps_mask(__k1, __xi, __yi, _CMP_LT_OS);
	      else if constexpr (std::is_same_v<_Tp, double>)
		return _mm256_mask_cmp_pd_mask(__k1, __xi, __yi, _CMP_LT_OS);
	      else if constexpr (std::is_signed_v<_Tp> && sizeof(_Tp) == 1)
		return _mm256_mask_cmplt_epi8_mask(__k1, __xi, __yi);
	      else if constexpr (std::is_signed_v<_Tp> && sizeof(_Tp) == 2)
		return _mm256_mask_cmplt_epi16_mask(__k1, __xi, __yi);
	      else if constexpr (std::is_signed_v<_Tp> && sizeof(_Tp) == 4)
		return _mm256_mask_cmplt_epi32_mask(__k1, __xi, __yi);
	      else if constexpr (std::is_signed_v<_Tp> && sizeof(_Tp) == 8)
		return _mm256_mask_cmplt_epi64_mask(__k1, __xi, __yi);
	      else if constexpr (std::is_unsigned_v<_Tp> && sizeof(_Tp) == 1)
		return _mm256_mask_cmplt_epu8_mask(__k1, __xi, __yi);
	      else if constexpr (std::is_unsigned_v<_Tp> && sizeof(_Tp) == 2)
		return _mm256_mask_cmplt_epu16_mask(__k1, __xi, __yi);
	      else if constexpr (std::is_unsigned_v<_Tp> && sizeof(_Tp) == 4)
		return _mm256_mask_cmplt_epu32_mask(__k1, __xi, __yi);
	      else if constexpr (std::is_unsigned_v<_Tp> && sizeof(_Tp) == 8)
		return _mm256_mask_cmplt_epu64_mask(__k1, __xi, __yi);
	      else
		__assert_unreachable<_Tp>();
	    }
	  else if constexpr (sizeof(__xi) == 16)
	    {
	      if constexpr (std::is_same_v<_Tp, float>)
		return _mm_mask_cmp_ps_mask(__k1, __xi, __yi, _CMP_LT_OS);
	      else if constexpr (std::is_same_v<_Tp, double>)
		return _mm_mask_cmp_pd_mask(__k1, __xi, __yi, _CMP_LT_OS);
	      else if constexpr (std::is_signed_v<_Tp> && sizeof(_Tp) == 1)
		return _mm_mask_cmplt_epi8_mask(__k1, __xi, __yi);
	      else if constexpr (std::is_signed_v<_Tp> && sizeof(_Tp) == 2)
		return _mm_mask_cmplt_epi16_mask(__k1, __xi, __yi);
	      else if constexpr (std::is_signed_v<_Tp> && sizeof(_Tp) == 4)
		return _mm_mask_cmplt_epi32_mask(__k1, __xi, __yi);
	      else if constexpr (std::is_signed_v<_Tp> && sizeof(_Tp) == 8)
		return _mm_mask_cmplt_epi64_mask(__k1, __xi, __yi);
	      else if constexpr (std::is_unsigned_v<_Tp> && sizeof(_Tp) == 1)
		return _mm_mask_cmplt_epu8_mask(__k1, __xi, __yi);
	      else if constexpr (std::is_unsigned_v<_Tp> && sizeof(_Tp) == 2)
		return _mm_mask_cmplt_epu16_mask(__k1, __xi, __yi);
	      else if constexpr (std::is_unsigned_v<_Tp> && sizeof(_Tp) == 4)
		return _mm_mask_cmplt_epu32_mask(__k1, __xi, __yi);
	      else if constexpr (std::is_unsigned_v<_Tp> && sizeof(_Tp) == 8)
		return _mm_mask_cmplt_epu64_mask(__k1, __xi, __yi);
	      else
		__assert_unreachable<_Tp>();
	    }
	  else
	    __assert_unreachable<_Tp>();
	}
      else
	return _Base::__less(__x, __y);
    }

    // __less_equal {{{3
    template <class _Tp, size_t _N>
    _GLIBCXX_SIMD_INTRINSIC static constexpr _MaskMember<_Tp>
      __less_equal(_SimdWrapper<_Tp, _N> __x, _SimdWrapper<_Tp, _N> __y)
    {
      if constexpr (__is_avx512_abi<_Abi>())
	{
	  constexpr auto __k1 = _Abi::template __implicit_mask<_Tp>();
	  [[maybe_unused]] const auto __xi = __to_intrin(__x);
	  [[maybe_unused]] const auto __yi = __to_intrin(__y);
	  if constexpr (sizeof(__xi) == 64)
	    {
	      if constexpr (std::is_same_v<_Tp, float>)
		return _mm512_mask_cmp_ps_mask(__k1, __xi, __yi, _CMP_LE_OS);
	      else if constexpr (std::is_same_v<_Tp, double>)
		return _mm512_mask_cmp_pd_mask(__k1, __xi, __yi, _CMP_LE_OS);
	      else if constexpr (std::is_signed_v<_Tp> && sizeof(_Tp) == 1)
		return _mm512_mask_cmple_epi8_mask(__k1, __xi, __yi);
	      else if constexpr (std::is_signed_v<_Tp> && sizeof(_Tp) == 2)
		return _mm512_mask_cmple_epi16_mask(__k1, __xi, __yi);
	      else if constexpr (std::is_signed_v<_Tp> && sizeof(_Tp) == 4)
		return _mm512_mask_cmple_epi32_mask(__k1, __xi, __yi);
	      else if constexpr (std::is_signed_v<_Tp> && sizeof(_Tp) == 8)
		return _mm512_mask_cmple_epi64_mask(__k1, __xi, __yi);
	      else if constexpr (std::is_unsigned_v<_Tp> && sizeof(_Tp) == 1)
		return _mm512_mask_cmple_epu8_mask(__k1, __xi, __yi);
	      else if constexpr (std::is_unsigned_v<_Tp> && sizeof(_Tp) == 2)
		return _mm512_mask_cmple_epu16_mask(__k1, __xi, __yi);
	      else if constexpr (std::is_unsigned_v<_Tp> && sizeof(_Tp) == 4)
		return _mm512_mask_cmple_epu32_mask(__k1, __xi, __yi);
	      else if constexpr (std::is_unsigned_v<_Tp> && sizeof(_Tp) == 8)
		return _mm512_mask_cmple_epu64_mask(__k1, __xi, __yi);
	      else
		__assert_unreachable<_Tp>();
	    }
	  else if constexpr (sizeof(__xi) == 32)
	    {
	      if constexpr (std::is_same_v<_Tp, float>)
		return _mm256_mask_cmp_ps_mask(__k1, __xi, __yi, _CMP_LE_OS);
	      else if constexpr (std::is_same_v<_Tp, double>)
		return _mm256_mask_cmp_pd_mask(__k1, __xi, __yi, _CMP_LE_OS);
	      else if constexpr (std::is_signed_v<_Tp> && sizeof(_Tp) == 1)
		return _mm256_mask_cmple_epi8_mask(__k1, __xi, __yi);
	      else if constexpr (std::is_signed_v<_Tp> && sizeof(_Tp) == 2)
		return _mm256_mask_cmple_epi16_mask(__k1, __xi, __yi);
	      else if constexpr (std::is_signed_v<_Tp> && sizeof(_Tp) == 4)
		return _mm256_mask_cmple_epi32_mask(__k1, __xi, __yi);
	      else if constexpr (std::is_signed_v<_Tp> && sizeof(_Tp) == 8)
		return _mm256_mask_cmple_epi64_mask(__k1, __xi, __yi);
	      else if constexpr (std::is_unsigned_v<_Tp> && sizeof(_Tp) == 1)
		return _mm256_mask_cmple_epu8_mask(__k1, __xi, __yi);
	      else if constexpr (std::is_unsigned_v<_Tp> && sizeof(_Tp) == 2)
		return _mm256_mask_cmple_epu16_mask(__k1, __xi, __yi);
	      else if constexpr (std::is_unsigned_v<_Tp> && sizeof(_Tp) == 4)
		return _mm256_mask_cmple_epu32_mask(__k1, __xi, __yi);
	      else if constexpr (std::is_unsigned_v<_Tp> && sizeof(_Tp) == 8)
		return _mm256_mask_cmple_epu64_mask(__k1, __xi, __yi);
	      else
		__assert_unreachable<_Tp>();
	    }
	  else if constexpr (sizeof(__xi) == 16)
	    {
	      if constexpr (std::is_same_v<_Tp, float>)
		return _mm_mask_cmp_ps_mask(__k1, __xi, __yi, _CMP_LE_OS);
	      else if constexpr (std::is_same_v<_Tp, double>)
		return _mm_mask_cmp_pd_mask(__k1, __xi, __yi, _CMP_LE_OS);
	      else if constexpr (std::is_signed_v<_Tp> && sizeof(_Tp) == 1)
		return _mm_mask_cmple_epi8_mask(__k1, __xi, __yi);
	      else if constexpr (std::is_signed_v<_Tp> && sizeof(_Tp) == 2)
		return _mm_mask_cmple_epi16_mask(__k1, __xi, __yi);
	      else if constexpr (std::is_signed_v<_Tp> && sizeof(_Tp) == 4)
		return _mm_mask_cmple_epi32_mask(__k1, __xi, __yi);
	      else if constexpr (std::is_signed_v<_Tp> && sizeof(_Tp) == 8)
		return _mm_mask_cmple_epi64_mask(__k1, __xi, __yi);
	      else if constexpr (std::is_unsigned_v<_Tp> && sizeof(_Tp) == 1)
		return _mm_mask_cmple_epu8_mask(__k1, __xi, __yi);
	      else if constexpr (std::is_unsigned_v<_Tp> && sizeof(_Tp) == 2)
		return _mm_mask_cmple_epu16_mask(__k1, __xi, __yi);
	      else if constexpr (std::is_unsigned_v<_Tp> && sizeof(_Tp) == 4)
		return _mm_mask_cmple_epu32_mask(__k1, __xi, __yi);
	      else if constexpr (std::is_unsigned_v<_Tp> && sizeof(_Tp) == 8)
		return _mm_mask_cmple_epu64_mask(__k1, __xi, __yi);
	      else
		__assert_unreachable<_Tp>();
	    }
	  else
	    __assert_unreachable<_Tp>();
	}
      else
	return _Base::__less_equal(__x, __y);
    }

    // negation {{{2
    template <class _Tp, size_t _N>
    _GLIBCXX_SIMD_INTRINSIC static constexpr _MaskMember<_Tp> __negate(_SimdWrapper<_Tp, _N> __x) noexcept
    {
      if constexpr (__is_avx512_abi<_Abi>()) {
	  return __equal_to(__x, _SimdWrapper<_Tp, _N>());
      } else {
	return _Base::__negate(__x);
      }
    }

    // math {{{2
    using _Base::__abs;
    // __sqrt {{{3
    template <class _Tp, size_t _N> _GLIBCXX_SIMD_INTRINSIC static _SimdWrapper<_Tp, _N> __sqrt(_SimdWrapper<_Tp, _N> __x)
    {
               if constexpr (__is_sse_ps   <_Tp, _N>()) { return __auto_bitcast(_mm_sqrt_ps(__to_intrin(__x)));
        } else if constexpr (__is_sse_pd   <_Tp, _N>()) { return _mm_sqrt_pd(__x);
        } else if constexpr (__is_avx_ps   <_Tp, _N>()) { return _mm256_sqrt_ps(__x);
        } else if constexpr (__is_avx_pd   <_Tp, _N>()) { return _mm256_sqrt_pd(__x);
        } else if constexpr (__is_avx512_ps<_Tp, _N>()) { return _mm512_sqrt_ps(__x);
        } else if constexpr (__is_avx512_pd<_Tp, _N>()) { return _mm512_sqrt_pd(__x);
        } else { __assert_unreachable<_Tp>(); }
    }

    // __trunc {{{3
    template <class _Tp, size_t _N>
    _GLIBCXX_SIMD_INTRINSIC static _SimdWrapper<_Tp, _N> __trunc(_SimdWrapper<_Tp, _N> __x)
    {
        if constexpr (__is_avx512_ps<_Tp, _N>()) {
            return _mm512_roundscale_ps(__x, 0x0b);
        } else if constexpr (__is_avx512_pd<_Tp, _N>()) {
            return _mm512_roundscale_pd(__x, 0x0b);
        } else if constexpr (__is_avx_ps<_Tp, _N>()) {
            return _mm256_round_ps(__x, 0x3);
        } else if constexpr (__is_avx_pd<_Tp, _N>()) {
            return _mm256_round_pd(__x, 0x3);
        } else if constexpr (__have_sse4_1 && __is_sse_ps<_Tp, _N>()) {
            return __auto_bitcast(_mm_round_ps(__to_intrin(__x), 0x3));
        } else if constexpr (__have_sse4_1 && __is_sse_pd<_Tp, _N>()) {
            return _mm_round_pd(__x, 0x3);
        } else if constexpr (__is_sse_ps<_Tp, _N>()) {
	    auto __truncated =
	      _mm_cvtepi32_ps(_mm_cvttps_epi32(__to_intrin(__x)));
	    const auto __no_fractional_values =
	      __to_intrin(__vector_bitcast<float>(
		__vector_bitcast<int>(__vector_bitcast<_UInt>(__x._M_data) &
				      0x7f800000u) <
		0x4b000000)); // the exponent is so large that no mantissa bits
			      // signify fractional values (0x3f8 + 23*8 =
			      // 0x4b0)
	    return __auto_bitcast(
	      __blend(__no_fractional_values, __to_intrin(__x), __truncated));
	} else {
            return _Base::__trunc(__x);
        }
    }

    // __round {{{3
    template <class _Tp, size_t _N>
    _GLIBCXX_SIMD_INTRINSIC static _SimdWrapper<_Tp, _N>
      __round(_SimdWrapper<_Tp, _N> __x)
    {
      using _V = __vector_type_t<_Tp, _N>;
      _V __truncated;
      if constexpr (__is_avx512_ps<_Tp, _N>())
	__truncated = _mm512_roundscale_ps(__x._M_data, 0x0b);
      else if constexpr (__is_avx512_pd<_Tp, _N>())
	__truncated = _mm512_roundscale_pd(__x._M_data, 0x0b);
      else if constexpr (__is_avx_ps<_Tp, _N>())
	__truncated = _mm256_round_ps(__x._M_data,
			       _MM_FROUND_TO_ZERO | _MM_FROUND_NO_EXC);
      else if constexpr (__is_avx_pd<_Tp, _N>())
	__truncated = _mm256_round_pd(__x._M_data,
			       _MM_FROUND_TO_ZERO | _MM_FROUND_NO_EXC);
      else if constexpr (__have_sse4_1 && __is_sse_ps<_Tp, _N>())
	__truncated = __auto_bitcast(_mm_round_ps(
	  __to_intrin(__x), _MM_FROUND_TO_ZERO | _MM_FROUND_NO_EXC));
      else if constexpr (__have_sse4_1 && __is_sse_pd<_Tp, _N>())
	__truncated = _mm_round_pd(__x._M_data,
			    _MM_FROUND_TO_ZERO | _MM_FROUND_NO_EXC);
      else if constexpr (__is_sse_ps<_Tp, _N>())
	__truncated =
	  __auto_bitcast(_mm_cvtepi32_ps(_mm_cvttps_epi32(__to_intrin(__x))));
      else
	return _Base::__round(__x);

      // x < 0 => truncated <= 0 && truncated >= x => x - truncated <= 0
      // x > 0 => truncated >= 0 && truncated <= x => x - truncated >= 0

      const _V __rounded =
	__truncated +
	(__and(_S_absmask<_V>, __x._M_data - __truncated) >= _Tp(.5)
	   ? __or(__and(_S_signmask<_V>, __x._M_data), _V() + 1)
	   : _V());
      if constexpr(__have_sse4_1)
	return __rounded;
      else
	return __and(_S_absmask<_V>, __x._M_data) < 0x1p23f ? __rounded : __x._M_data;
    }

    // __nearbyint {{{3
    template <typename _Tp, typename _TVT = _VectorTraits<_Tp>>
    _GLIBCXX_SIMD_INTRINSIC static _Tp __nearbyint(_Tp __x) noexcept
    {
      if constexpr (_TVT::template __is<float, 16>)
	return _mm512_roundscale_ps(__x, 0x0c);
      else if constexpr (_TVT::template __is<double, 8>)
	return _mm512_roundscale_pd(__x, 0x0c);
      else if constexpr (_TVT::template __is<float, 8>)
	return _mm256_round_ps(__x,
			       _MM_FROUND_CUR_DIRECTION | _MM_FROUND_NO_EXC);
      else if constexpr (_TVT::template __is<double, 4>)
	return _mm256_round_pd(__x,
			       _MM_FROUND_CUR_DIRECTION | _MM_FROUND_NO_EXC);
      else if constexpr (__have_sse4_1 && _TVT::template __is<float, 4>)
	return _mm_round_ps(__x, _MM_FROUND_CUR_DIRECTION | _MM_FROUND_NO_EXC);
      else if constexpr (__have_sse4_1 && _TVT::template __is<double, 2>)
	return _mm_round_pd(__x, _MM_FROUND_CUR_DIRECTION | _MM_FROUND_NO_EXC);
      else
	return _Base::__nearbyint(__x);
    }

    // __rint {{{3
    template <typename _Tp, typename _TVT = _VectorTraits<_Tp>>
    _GLIBCXX_SIMD_INTRINSIC static _Tp __rint(_Tp __x) noexcept
    {
      if constexpr (_TVT::template __is<float, 16>)
	return _mm512_roundscale_ps(__x, 0x04);
      else if constexpr (_TVT::template __is<double, 8>)
	return _mm512_roundscale_pd(__x, 0x04);
      else if constexpr (_TVT::template __is<float, 8>)
	return _mm256_round_ps(__x, _MM_FROUND_CUR_DIRECTION);
      else if constexpr (_TVT::template __is<double, 4>)
	return _mm256_round_pd(__x, _MM_FROUND_CUR_DIRECTION);
      else if constexpr (__have_sse4_1 && _TVT::template __is<float, 4>)
	return _mm_round_ps(__x, _MM_FROUND_CUR_DIRECTION);
      else if constexpr (__have_sse4_1 && _TVT::template __is<double, 2>)
	return _mm_round_pd(__x, _MM_FROUND_CUR_DIRECTION);
      else
	return _Base::__rint(__x);
    }

    // __floor {{{3
    template <class _Tp, size_t _N>
    _GLIBCXX_SIMD_INTRINSIC static _SimdWrapper<_Tp, _N> __floor(_SimdWrapper<_Tp, _N> __x)
    {
        if constexpr (__is_avx512_ps<_Tp, _N>()) {
            return _mm512_roundscale_ps(__x, 0x09);
        } else if constexpr (__is_avx512_pd<_Tp, _N>()) {
            return _mm512_roundscale_pd(__x, 0x09);
        } else if constexpr (__is_avx_ps<_Tp, _N>()) {
            return _mm256_round_ps(__x, 0x1);
        } else if constexpr (__is_avx_pd<_Tp, _N>()) {
            return _mm256_round_pd(__x, 0x1);
        } else if constexpr (__have_sse4_1 && __is_sse_ps<_Tp, _N>()) {
	    return __auto_bitcast(_mm_floor_ps(__to_intrin(__x)));
	} else if constexpr (__have_sse4_1 && __is_sse_pd<_Tp, _N>()) {
            return _mm_floor_pd(__x);
        } else {
	  return _Base::__floor(__x);
        }
    }

    // __ceil {{{3
    template <class _Tp, size_t _N> _GLIBCXX_SIMD_INTRINSIC static _SimdWrapper<_Tp, _N> __ceil(_SimdWrapper<_Tp, _N> __x)
    {
        if constexpr (__is_avx512_ps<_Tp, _N>()) {
            return _mm512_roundscale_ps(__x, 0x0a);
        } else if constexpr (__is_avx512_pd<_Tp, _N>()) {
            return _mm512_roundscale_pd(__x, 0x0a);
        } else if constexpr (__is_avx_ps<_Tp, _N>()) {
            return _mm256_round_ps(__x, 0x2);
        } else if constexpr (__is_avx_pd<_Tp, _N>()) {
            return _mm256_round_pd(__x, 0x2);
        } else if constexpr (__have_sse4_1 && __is_sse_ps<_Tp, _N>()) {
            return __auto_bitcast(_mm_ceil_ps(__to_intrin(__x)));
        } else if constexpr (__have_sse4_1 && __is_sse_pd<_Tp, _N>()) {
            return _mm_ceil_pd(__x);
        } else {
	  return _Base::__ceil(__x);
        }
    }

    // __signbit {{{3
    template <class _Tp, size_t _N>
    _GLIBCXX_SIMD_INTRINSIC static _MaskMember<_Tp> __signbit(_SimdWrapper<_Tp, _N> __x)
    {
      if constexpr (__is_avx512_abi<_Abi>() && __have_avx512dq)
	{
	  if constexpr (sizeof(__x) == 64 && sizeof(_Tp) == 4)
	    return _mm512_movepi32_mask(__intrin_bitcast<__m512i>(__x._M_data));
	  else if constexpr (sizeof(__x) == 64 && sizeof(_Tp) == 8)
	    return _mm512_movepi64_mask(__intrin_bitcast<__m512i>(__x._M_data));
	  else if constexpr (sizeof(__x) == 32 && sizeof(_Tp) == 4)
	    return _mm256_movepi32_mask(__intrin_bitcast<__m256i>(__x._M_data));
	  else if constexpr (sizeof(__x) == 32 && sizeof(_Tp) == 8)
	    return _mm256_movepi64_mask(__intrin_bitcast<__m256i>(__x._M_data));
	  else if constexpr (sizeof(__x) <= 16 && sizeof(_Tp) == 4)
	    return _mm_movepi32_mask(__intrin_bitcast<__m128i>(__x._M_data));
	  else if constexpr (sizeof(__x) <= 16 && sizeof(_Tp) == 8)
	    return _mm_movepi64_mask(__intrin_bitcast<__m128i>(__x._M_data));
	}
      else if constexpr (__is_avx512_abi<_Abi>())
	{
	  const auto                      __xi = __to_intrin(__x);
	  [[maybe_unused]] constexpr auto __k1 =
	    _Abi::template __implicit_mask<_Tp>();
	  if constexpr (sizeof(__xi) == 16 && sizeof(_Tp) == 4)
	    return _mm_movemask_ps(__xi);
	  else if constexpr (sizeof(__xi) == 16 && sizeof(_Tp) == 8)
	    return _mm_movemask_pd(__xi);
	  else if constexpr (sizeof(__xi) == 32 && sizeof(_Tp) == 4)
	    return _mm256_movemask_ps(__xi);
	  else if constexpr (sizeof(__xi) == 32 && sizeof(_Tp) == 8)
	    return _mm256_movemask_pd(__xi);
	  else if constexpr (sizeof(__xi) == 64 && sizeof(_Tp) == 4)
	    return _mm512_mask_cmplt_epi32_mask(
	      __k1, __intrin_bitcast<__m512i>(__xi), __m512i());
	  else if constexpr (sizeof(__xi) == 64 && sizeof(_Tp) == 8)
	    return _mm512_mask_cmplt_epi64_mask(
	      __k1, __intrin_bitcast<__m512i>(__xi), __m512i());
	  else
	    __assert_unreachable<_Tp>();
	}
      else
	return _Base::__signbit(__x);
	/*{
	  using _I = __int_for_sizeof_t<_Tp>;
	  if constexpr (sizeof(__x) == 64)
	    return __less(__vector_bitcast<_I>(__x), _I());
	  else
	    {
	      const auto __xx = __vector_bitcast<_I>(__x._M_data);
	      [[maybe_unused]] constexpr _I __signmask =
		std::numeric_limits<_I>::min();
	      if constexpr ((sizeof(_Tp) == 4 &&
			     (__have_avx2 || sizeof(__x) == 16)) ||
			    __have_avx512vl)
		{
		  return __vector_bitcast<_Tp>(__xx >>
					       std::numeric_limits<_I>::digits);
		}
	      else if constexpr ((__have_avx2 ||
				  (__have_ssse3 && sizeof(__x) == 16)))
		{
		  return __vector_bitcast<_Tp>((__xx & __signmask) ==
					       __signmask);
		}
	      else
		{ // SSE2/3 or AVX (w/o AVX2)
		  constexpr auto __one = __vector_broadcast<_N, _Tp>(1);
		  return __vector_bitcast<_Tp>(
		    __vector_bitcast<_Tp>(
		      (__xx & __signmask) |
		      __vector_bitcast<_I>(__one)) // -1 or 1
		    != __one);
		}
	    }
	}*/
    }

    // __isnonzerovalue_mask (isnormal | is subnormal == !isinf & !isnan & !is zero) {{{3
    template <class _Tp>
    _GLIBCXX_SIMD_INTRINSIC static auto __isnonzerovalue_mask(_Tp __x)
    {
      using _Traits = _VectorTraits<_Tp>;
      if constexpr (__have_avx512dq_vl)
	{
	  if constexpr (_Traits::template __is<float, 2> ||
			_Traits::template __is<float, 4>)
	    return _knot_mask8(_mm_fpclass_ps_mask(__to_intrin(__x), 0x9f));
	  else if constexpr (_Traits::template __is<float, 8>)
	    return _knot_mask8(_mm256_fpclass_ps_mask(__x, 0x9f));
	  else if constexpr (_Traits::template __is<float, 16>)
	    return _knot_mask16(_mm512_fpclass_ps_mask(__x, 0x9f));
	  else if constexpr (_Traits::template __is<double, 2>)
	    return _knot_mask8(_mm_fpclass_pd_mask(__x, 0x9f));
	  else if constexpr (_Traits::template __is<double, 4>)
	    return _knot_mask8(_mm256_fpclass_pd_mask(__x, 0x9f));
	  else if constexpr (_Traits::template __is<double, 8>)
	    return _knot_mask8(_mm512_fpclass_pd_mask(__x, 0x9f));
	  else
	    __assert_unreachable<_Tp>();
	}
      else
	{
	  using _U            = typename _Traits::value_type;
	  constexpr size_t _N = _Traits::_S_width;
	  const auto       __a =
	    __x * std::numeric_limits<_U>::infinity(); // NaN if __x == 0
	  const auto __b = __x * _U();                 // NaN if __x == inf
	  if constexpr (__have_avx512vl && __is_sse_ps<_U, _N>())
	    {
	      return _mm_cmp_ps_mask(__to_intrin(__a), __to_intrin(__b),
				     _CMP_ORD_Q);
	    }
	  else if constexpr (__have_avx512f && __is_sse_ps<_U, _N>())
	    {
	      return __mmask8(0xf & _mm512_cmp_ps_mask(__auto_bitcast(__a),
						       __auto_bitcast(__b),
						       _CMP_ORD_Q));
	    }
	  else if constexpr (__have_avx512vl && __is_sse_pd<_U, _N>())
	    {
	      return _mm_cmp_pd_mask(__a, __b, _CMP_ORD_Q);
	    }
	  else if constexpr (__have_avx512f && __is_sse_pd<_U, _N>())
	    {
	      return __mmask8(0x3 & _mm512_cmp_pd_mask(__auto_bitcast(__a),
						       __auto_bitcast(__b),
						       _CMP_ORD_Q));
	    }
	  else if constexpr (__have_avx512vl && __is_avx_ps<_U, _N>())
	    {
	      return _mm256_cmp_ps_mask(__a, __b, _CMP_ORD_Q);
	    }
	  else if constexpr (__have_avx512f && __is_avx_ps<_U, _N>())
	    {
	      return __mmask8(_mm512_cmp_ps_mask(
		__auto_bitcast(__a), __auto_bitcast(__b), _CMP_ORD_Q));
	    }
	  else if constexpr (__have_avx512vl && __is_avx_pd<_U, _N>())
	    {
	      return _mm256_cmp_pd_mask(__a, __b, _CMP_ORD_Q);
	    }
	  else if constexpr (__have_avx512f && __is_avx_pd<_U, _N>())
	    {
	      return __mmask8(0xf & _mm512_cmp_pd_mask(__auto_bitcast(__a),
						       __auto_bitcast(__b),
						       _CMP_ORD_Q));
	    }
	  else if constexpr (__is_avx512_ps<_U, _N>())
	    {
	      return _mm512_cmp_ps_mask(__a, __b, _CMP_ORD_Q);
	    }
	  else if constexpr (__is_avx512_pd<_U, _N>())
	    {
	      return _mm512_cmp_pd_mask(__a, __b, _CMP_ORD_Q);
	    }
	  else
	    {
	      __assert_unreachable<_Tp>();
	    }
	}
    }

    // __isfinite {{{3
    template <typename _Tp, size_t _N>
    _GLIBCXX_SIMD_INTRINSIC static _MaskMember<_Tp>
      __isfinite(_SimdWrapper<_Tp, _N> __x)
    {
      static_assert(is_floating_point_v<_Tp>);
#if __FINITE_MATH_ONLY__
      [](auto&&){}(__x);
      return __equal_to(_SimdWrapper<_Tp, _N>(), _SimdWrapper<_Tp, _N>());
#else
      if constexpr (__is_avx512_abi<_Abi>() && __have_avx512dq)
	{
	  const auto __xi = __to_intrin(__x);
	  constexpr auto __k1 = _Abi::template __implicit_mask<_Tp>();
	  if constexpr (sizeof(__xi) == 64 && sizeof(_Tp) == 4)
	    return __k1 ^ _mm512_mask_fpclass_ps_mask(__k1, __xi, 0x99);
	  else if constexpr (sizeof(__xi) == 64 && sizeof(_Tp) == 8)
	    return __k1 ^ _mm512_mask_fpclass_pd_mask(__k1, __xi, 0x99);
	  else if constexpr (sizeof(__xi) == 32 && sizeof(_Tp) == 4)
	    return __k1 ^ _mm256_mask_fpclass_ps_mask(__k1, __xi, 0x99);
	  else if constexpr (sizeof(__xi) == 32 && sizeof(_Tp) == 8)
	    return __k1 ^ _mm256_mask_fpclass_pd_mask(__k1, __xi, 0x99);
	  else if constexpr (sizeof(__xi) == 16 && sizeof(_Tp) == 4)
	    return __k1 ^ _mm_mask_fpclass_ps_mask(__k1, __xi, 0x99);
	  else if constexpr (sizeof(__xi) == 16 && sizeof(_Tp) == 8)
	    return __k1 ^ _mm_mask_fpclass_pd_mask(__k1, __xi, 0x99);
	}
      else if constexpr (__is_avx512_abi<_Abi>())
	{
	  // if all exponent bits are set, __x is either inf or NaN
	  using _I         = __int_for_sizeof_t<_Tp>;
	  const auto __inf = __vector_bitcast<_I>(
	    __vector_broadcast<_N>(std::numeric_limits<_Tp>::infinity()));
	  return __less<_I, _N>(__vector_bitcast<_I>(__x) & __inf, __inf);
	}
      else
	return _Base::__isfinite(__x);
#endif
    }

    // __isinf {{{3
    template <class _Tp, size_t _N>
    _GLIBCXX_SIMD_INTRINSIC static _MaskMember<_Tp> __isinf(_SimdWrapper<_Tp, _N> __x)
    {
#if __FINITE_MATH_ONLY__
      [](auto&&){}(__x);
      return {}; // false
#else
      if constexpr (__is_avx512_abi<_Abi>() && __have_avx512dq)
	{
	  const auto __xi = __to_intrin(__x);
	  if constexpr (sizeof(__xi) == 64 && sizeof(_Tp) == 4)
	    return _mm512_fpclass_ps_mask(__xi, 0x18);
	  else if constexpr (sizeof(__xi) == 64 && sizeof(_Tp) == 8)
	    return _mm512_fpclass_pd_mask(__xi, 0x18);
	  else if constexpr (sizeof(__xi) == 32 && sizeof(_Tp) == 4)
	    return _mm256_fpclass_ps_mask(__xi, 0x18);
	  else if constexpr (sizeof(__xi) == 32 && sizeof(_Tp) == 8)
	    return _mm256_fpclass_pd_mask(__xi, 0x18);
	  else if constexpr (sizeof(__xi) == 16 && sizeof(_Tp) == 4)
	    return _mm_fpclass_ps_mask(__xi, 0x18);
	  else if constexpr (sizeof(__xi) == 16 && sizeof(_Tp) == 8)
	    return _mm_fpclass_pd_mask(__xi, 0x18);
	  else
	    __assert_unreachable<_Tp>();
	}
      else if constexpr (__have_avx512dq_vl)
	{
	  if constexpr (__is_sse_pd<_Tp, _N>())
	    return __vector_bitcast<double>(
	      _mm_movm_epi64(_mm_fpclass_pd_mask(__x, 0x18)));
	  else if constexpr (__is_avx_pd<_Tp, _N>())
	    return __vector_bitcast<double>(
	      _mm256_movm_epi64(_mm256_fpclass_pd_mask(__x, 0x18)));
	  else if constexpr (__is_sse_ps<_Tp, _N>())
	    return __auto_bitcast(
	      _mm_movm_epi32(_mm_fpclass_ps_mask(__to_intrin(__x), 0x18)));
	  else if constexpr (__is_avx_ps<_Tp, _N>())
	    return __vector_bitcast<float>(
	      _mm256_movm_epi32(_mm256_fpclass_ps_mask(__x, 0x18)));
	  else
	    __assert_unreachable<_Tp>();
	}
      else
	return _Base::__isinf(__x);
#endif
    }

    // __isnormal {{{3
    template <class _Tp, size_t _N>
    _GLIBCXX_SIMD_INTRINSIC static _MaskMember<_Tp>
      __isnormal(_SimdWrapper<_Tp, _N> __x)
    {
#if __FINITE_MATH_ONLY__
      [[maybe_unused]] constexpr int __mode = 0x26;
#else
      [[maybe_unused]] constexpr int __mode = 0xbf;
#endif
      if constexpr (__is_avx512_abi<_Abi>() && __have_avx512dq)
	{
	  const auto __xi = __to_intrin(__x);
	  const auto __k1 = _Abi::template __implicit_mask<_Tp>();
	  if constexpr (sizeof(__xi) == 64 && sizeof(_Tp) == 4)
	    return __k1 ^ _mm512_mask_fpclass_ps_mask(__k1, __xi, __mode);
	  else if constexpr (sizeof(__xi) == 64 && sizeof(_Tp) == 8)
	    return __k1 ^ _mm512_mask_fpclass_pd_mask(__k1, __xi, __mode);
	  else if constexpr (sizeof(__xi) == 32 && sizeof(_Tp) == 4)
	    return __k1 ^ _mm256_mask_fpclass_ps_mask(__k1, __xi, __mode);
	  else if constexpr (sizeof(__xi) == 32 && sizeof(_Tp) == 8)
	    return __k1 ^ _mm256_mask_fpclass_pd_mask(__k1, __xi, __mode);
	  else if constexpr (sizeof(__xi) == 16 && sizeof(_Tp) == 4)
	    return __k1 ^ _mm_mask_fpclass_ps_mask(__k1, __xi, __mode);
	  else if constexpr (sizeof(__xi) == 16 && sizeof(_Tp) == 8)
	    return __k1 ^ _mm_mask_fpclass_pd_mask(__k1, __xi, __mode);
	  else
	    __assert_unreachable<_Tp>();
	}
      else if constexpr (__have_avx512dq)
	{
	  if constexpr (__have_avx512vl && __is_sse_ps<_Tp, _N>())
	    return __auto_bitcast(_mm_movm_epi32(
	      _knot_mask8(_mm_fpclass_ps_mask(__to_intrin(__x), __mode))));
	  else if constexpr (__have_avx512vl && __is_avx_ps<_Tp, _N>())
	    return __vector_bitcast<float>(_mm256_movm_epi32(
	      _knot_mask8(_mm256_fpclass_ps_mask(__x, __mode))));
	  else if constexpr (__is_avx512_ps<_Tp, _N>())
	    return _knot_mask16(_mm512_fpclass_ps_mask(__x, __mode));
	  else if constexpr (__have_avx512vl && __is_sse_pd<_Tp, _N>())
	    return __vector_bitcast<double>(
	      _mm_movm_epi64(_knot_mask8(_mm_fpclass_pd_mask(__x, __mode))));
	  else if constexpr (__have_avx512vl && __is_avx_pd<_Tp, _N>())
	    return __vector_bitcast<double>(_mm256_movm_epi64(
	      _knot_mask8(_mm256_fpclass_pd_mask(__x, __mode))));
	  else if constexpr (__is_avx512_pd<_Tp, _N>())
	    return _knot_mask8(_mm512_fpclass_pd_mask(__x, __mode));
	  else
	    __assert_unreachable<_Tp>();
	}
      else if constexpr (__is_avx512_abi<_Abi>())
	{
	  using _I        = __int_for_sizeof_t<_Tp>;
	  const auto absn = __vector_bitcast<_I>(__abs(__x));
	  const auto minn = __vector_bitcast<_I>(
	    __vector_broadcast<_N>(std::numeric_limits<_Tp>::min()));
#if __FINITE_MATH_ONLY__
	  return __less_equal<_I, _N>(minn, absn);
#else
	  const auto infn = __vector_bitcast<_I>(
	    __vector_broadcast<_N>(std::numeric_limits<_Tp>::infinity()));
	  return __and(__less_equal<_I, _N>(minn, absn),
		       __less<_I, _N>(absn, infn));
#endif
	}
      else
	return _Base::__isnormal(__x);
    }

    // __isnan {{{3
    using _Base::__isnan;

    // __isunordered {{{3
    template <class _Tp, size_t _N>
    _GLIBCXX_SIMD_INTRINSIC static _MaskMember<_Tp>
      __isunordered(_SimdWrapper<_Tp, _N> __x, _SimdWrapper<_Tp, _N> __y)
    {
      const auto __xi = __to_intrin(__x);
      const auto __yi = __to_intrin(__y);
      if constexpr (__is_avx512_abi<_Abi>())
	{
	  constexpr auto __k1 = _Abi::template __implicit_mask<_Tp>();
	  if constexpr (sizeof(__xi) == 64 && sizeof(_Tp) == 4)
	    return _mm512_mask_cmp_ps_mask(__k1, __xi, __yi, _CMP_UNORD_Q);
	  else if constexpr (sizeof(__xi) == 64 && sizeof(_Tp) == 8)
	    return _mm512_mask_cmp_pd_mask(__k1, __xi, __yi, _CMP_UNORD_Q);
	  else if constexpr (sizeof(__xi) == 32 && sizeof(_Tp) == 4)
	    return _mm256_mask_cmp_ps_mask(__k1, __xi, __yi, _CMP_UNORD_Q);
	  else if constexpr (sizeof(__xi) == 32 && sizeof(_Tp) == 8)
	    return _mm256_mask_cmp_pd_mask(__k1, __xi, __yi, _CMP_UNORD_Q);
	  else if constexpr (sizeof(__xi) == 16 && sizeof(_Tp) == 4)
	    return _mm_mask_cmp_ps_mask(__k1, __xi, __yi, _CMP_UNORD_Q);
	  else if constexpr (sizeof(__xi) == 16 && sizeof(_Tp) == 8)
	    return _mm_mask_cmp_pd_mask(__k1, __xi, __yi, _CMP_UNORD_Q);
	}
      else if constexpr (sizeof(__xi) == 32 && sizeof(_Tp) == 4)
	return _mm256_cmp_ps(__xi, __yi, _CMP_UNORD_Q);
      else if constexpr (sizeof(__xi) == 32 && sizeof(_Tp) == 8)
	return _mm256_cmp_pd(__xi, __yi, _CMP_UNORD_Q);
      else if constexpr (sizeof(__xi) == 16 && sizeof(_Tp) == 4)
	return __auto_bitcast(_mm_cmpunord_ps(__xi, __yi));
      else if constexpr (sizeof(__xi) == 16 && sizeof(_Tp) == 8)
	return __auto_bitcast(_mm_cmpunord_pd(__xi, __yi));
      else
	__assert_unreachable<_Tp>();
    }

    // __isgreater {{{3
    template <typename _Tp, size_t _N>
    static constexpr _MaskMember<_Tp>
      __isgreater(_SimdWrapper<_Tp, _N> __x, _SimdWrapper<_Tp, _N> __y)
    {
      const auto __xi = __to_intrin(__x);
      const auto __yi = __to_intrin(__y);
      if constexpr (__is_avx512_abi<_Abi>())
	{
	  const auto __k1 = _Abi::template __implicit_mask<_Tp>();
	  if constexpr (sizeof(__xi) == 64 && sizeof(_Tp) == 4)
	    return _mm512_mask_cmp_ps_mask(__k1, __xi, __yi, _CMP_GT_OQ);
	  else if constexpr (sizeof(__xi) == 64 && sizeof(_Tp) == 8)
	    return _mm512_mask_cmp_pd_mask(__k1, __xi, __yi, _CMP_GT_OQ);
	  else if constexpr (sizeof(__xi) == 32 && sizeof(_Tp) == 4)
	    return _mm256_mask_cmp_ps_mask(__k1, __xi, __yi, _CMP_GT_OQ);
	  else if constexpr (sizeof(__xi) == 32 && sizeof(_Tp) == 8)
	    return _mm256_mask_cmp_pd_mask(__k1, __xi, __yi, _CMP_GT_OQ);
	  else if constexpr (sizeof(__xi) == 16 && sizeof(_Tp) == 4)
	    return _mm_mask_cmp_ps_mask(__k1, __xi, __yi, _CMP_GT_OQ);
	  else if constexpr (sizeof(__xi) == 16 && sizeof(_Tp) == 8)
	    return _mm_mask_cmp_pd_mask(__k1, __xi, __yi, _CMP_GT_OQ);
	  else
	    __assert_unreachable<_Tp>();
	}
      else if constexpr(__have_avx)
        {
	  if constexpr (sizeof(__xi) == 32 && sizeof(_Tp) == 4)
	    return _mm256_cmp_ps(__xi, __yi, _CMP_GT_OQ);
	  else if constexpr (sizeof(__xi) == 32 && sizeof(_Tp) == 8)
	    return _mm256_cmp_pd(__xi, __yi, _CMP_GT_OQ);
	  else if constexpr (sizeof(__xi) == 16 && sizeof(_Tp) == 4)
	    return __auto_bitcast(_mm_cmp_ps(__xi, __yi, _CMP_GT_OQ));
	  else if constexpr (sizeof(__xi) == 16 && sizeof(_Tp) == 8)
	    return _mm_cmp_pd(__xi, __yi, _CMP_GT_OQ);
	  else
	    __assert_unreachable<_Tp>();
	}
      else if constexpr (__have_sse2 && sizeof(__xi) == 16 && sizeof(_Tp) == 4)
	{
	  const auto __xn = __vector_bitcast<int>(__xi);
	  const auto __yn = __vector_bitcast<int>(__yi);
	  const auto __xp = __xn < 0 ? -(__xn & 0x7fff'ffff) : __xn;
	  const auto __yp = __yn < 0 ? -(__yn & 0x7fff'ffff) : __yn;
	  return __auto_bitcast(__and(_mm_cmpord_ps(__xi, __yi),
				      reinterpret_cast<__m128>(__xp > __yp)));
	}
      else if constexpr (__have_sse2 && sizeof(__xi) == 16 && sizeof(_Tp) == 8)
	return __auto_bitcast(__vector_type_t<__int_with_sizeof_t<8>, 2>{
	  -_mm_ucomigt_sd(__xi, __yi),
	  -_mm_ucomigt_sd(_mm_unpackhi_pd(__xi, __xi),
			  _mm_unpackhi_pd(__yi, __yi))});
      else
	return _Base::__isgreater(__x, __y);
    }

    // __isgreaterequal {{{3
    template <typename _Tp, size_t _N>
    static constexpr _MaskMember<_Tp>
      __isgreaterequal(_SimdWrapper<_Tp, _N> __x, _SimdWrapper<_Tp, _N> __y)
    {
      const auto __xi = __to_intrin(__x);
      const auto __yi = __to_intrin(__y);
      if constexpr (__is_avx512_abi<_Abi>())
	{
	  const auto __k1 = _Abi::template __implicit_mask<_Tp>();
	  if constexpr (sizeof(__xi) == 64 && sizeof(_Tp) == 4)
	    return _mm512_mask_cmp_ps_mask(__k1, __xi, __yi, _CMP_GE_OQ);
	  else if constexpr (sizeof(__xi) == 64 && sizeof(_Tp) == 8)
	    return _mm512_mask_cmp_pd_mask(__k1, __xi, __yi, _CMP_GE_OQ);
	  else if constexpr (sizeof(__xi) == 32 && sizeof(_Tp) == 4)
	    return _mm256_mask_cmp_ps_mask(__k1, __xi, __yi, _CMP_GE_OQ);
	  else if constexpr (sizeof(__xi) == 32 && sizeof(_Tp) == 8)
	    return _mm256_mask_cmp_pd_mask(__k1, __xi, __yi, _CMP_GE_OQ);
	  else if constexpr (sizeof(__xi) == 16 && sizeof(_Tp) == 4)
	    return _mm_mask_cmp_ps_mask(__k1, __xi, __yi, _CMP_GE_OQ);
	  else if constexpr (sizeof(__xi) == 16 && sizeof(_Tp) == 8)
	    return _mm_mask_cmp_pd_mask(__k1, __xi, __yi, _CMP_GE_OQ);
	  else
	    __assert_unreachable<_Tp>();
	}
      else if constexpr(__have_avx)
        {
	  if constexpr (sizeof(__xi) == 32 && sizeof(_Tp) == 4)
	    return _mm256_cmp_ps(__xi, __yi, _CMP_GE_OQ);
	  else if constexpr (sizeof(__xi) == 32 && sizeof(_Tp) == 8)
	    return _mm256_cmp_pd(__xi, __yi, _CMP_GE_OQ);
	  else if constexpr (sizeof(__xi) == 16 && sizeof(_Tp) == 4)
	    return __auto_bitcast(_mm_cmp_ps(__xi, __yi, _CMP_GE_OQ));
	  else if constexpr (sizeof(__xi) == 16 && sizeof(_Tp) == 8)
	    return _mm_cmp_pd(__xi, __yi, _CMP_GE_OQ);
	  else
	    __assert_unreachable<_Tp>();
	}
      else if constexpr (__have_sse2 && sizeof(__xi) == 16 && sizeof(_Tp) == 4)
	{
	  const auto __xn = __vector_bitcast<int>(__xi);
	  const auto __yn = __vector_bitcast<int>(__yi);
	  const auto __xp = __xn < 0 ? -(__xn & 0x7fff'ffff) : __xn;
	  const auto __yp = __yn < 0 ? -(__yn & 0x7fff'ffff) : __yn;
	  return __auto_bitcast(__and(_mm_cmpord_ps(__xi, __yi),
				      reinterpret_cast<__m128>(__xp >= __yp)));
	}
      else if constexpr (__have_sse2 && sizeof(__xi) == 16 && sizeof(_Tp) == 8)
	return __auto_bitcast(__vector_type_t<__int_with_sizeof_t<8>, 2>{
	  -_mm_ucomige_sd(__xi, __yi),
	  -_mm_ucomige_sd(_mm_unpackhi_pd(__xi, __xi),
			  _mm_unpackhi_pd(__yi, __yi))});
      else
	return _Base::__isgreaterequal(__x, __y);
    }

    // __isless {{{3
    template <typename _Tp, size_t _N>
    static constexpr _MaskMember<_Tp>
      __isless(_SimdWrapper<_Tp, _N> __x, _SimdWrapper<_Tp, _N> __y)
    {
      const auto __xi = __to_intrin(__x);
      const auto __yi = __to_intrin(__y);
      if constexpr (__is_avx512_abi<_Abi>())
	{
	  const auto __k1 = _Abi::template __implicit_mask<_Tp>();
	  if constexpr (sizeof(__xi) == 64 && sizeof(_Tp) == 4)
	    return _mm512_mask_cmp_ps_mask(__k1, __xi, __yi, _CMP_LT_OQ);
	  else if constexpr (sizeof(__xi) == 64 && sizeof(_Tp) == 8)
	    return _mm512_mask_cmp_pd_mask(__k1, __xi, __yi, _CMP_LT_OQ);
	  else if constexpr (sizeof(__xi) == 32 && sizeof(_Tp) == 4)
	    return _mm256_mask_cmp_ps_mask(__k1, __xi, __yi, _CMP_LT_OQ);
	  else if constexpr (sizeof(__xi) == 32 && sizeof(_Tp) == 8)
	    return _mm256_mask_cmp_pd_mask(__k1, __xi, __yi, _CMP_LT_OQ);
	  else if constexpr (sizeof(__xi) == 16 && sizeof(_Tp) == 4)
	    return _mm_mask_cmp_ps_mask(__k1, __xi, __yi, _CMP_LT_OQ);
	  else if constexpr (sizeof(__xi) == 16 && sizeof(_Tp) == 8)
	    return _mm_mask_cmp_pd_mask(__k1, __xi, __yi, _CMP_LT_OQ);
	  else
	    __assert_unreachable<_Tp>();
	}
      else if constexpr(__have_avx)
        {
	  if constexpr (sizeof(__xi) == 32 && sizeof(_Tp) == 4)
	    return _mm256_cmp_ps(__xi, __yi, _CMP_LT_OQ);
	  else if constexpr (sizeof(__xi) == 32 && sizeof(_Tp) == 8)
	    return _mm256_cmp_pd(__xi, __yi, _CMP_LT_OQ);
	  else if constexpr (sizeof(__xi) == 16 && sizeof(_Tp) == 4)
	    return __auto_bitcast(_mm_cmp_ps(__xi, __yi, _CMP_LT_OQ));
	  else if constexpr (sizeof(__xi) == 16 && sizeof(_Tp) == 8)
	    return _mm_cmp_pd(__xi, __yi, _CMP_LT_OQ);
	  else
	    __assert_unreachable<_Tp>();
	}
      else if constexpr (__have_sse2 && sizeof(__xi) == 16 && sizeof(_Tp) == 4)
	{
	  const auto __xn = __vector_bitcast<int>(__xi);
	  const auto __yn = __vector_bitcast<int>(__yi);
	  const auto __xp = __xn < 0 ? -(__xn & 0x7fff'ffff) : __xn;
	  const auto __yp = __yn < 0 ? -(__yn & 0x7fff'ffff) : __yn;
	  return __auto_bitcast(__and(_mm_cmpord_ps(__xi, __yi),
				      reinterpret_cast<__m128>(__xp < __yp)));
	}
      else if constexpr (__have_sse2 && sizeof(__xi) == 16 && sizeof(_Tp) == 8)
	return __auto_bitcast(__vector_type_t<__int_with_sizeof_t<8>, 2>{
	  -_mm_ucomigt_sd(__yi, __xi),
	  -_mm_ucomigt_sd(_mm_unpackhi_pd(__yi, __yi),
			  _mm_unpackhi_pd(__xi, __xi))});
      else
	return _Base::__isless(__x, __y);
    }

    // __islessequal {{{3
    template <typename _Tp, size_t _N>
    static constexpr _MaskMember<_Tp>
      __islessequal(_SimdWrapper<_Tp, _N> __x, _SimdWrapper<_Tp, _N> __y)
    {
      const auto __xi = __to_intrin(__x);
      const auto __yi = __to_intrin(__y);
      if constexpr (__is_avx512_abi<_Abi>())
	{
	  const auto __k1 = _Abi::template __implicit_mask<_Tp>();
	  if constexpr (sizeof(__xi) == 64 && sizeof(_Tp) == 4)
	    return _mm512_mask_cmp_ps_mask(__k1, __xi, __yi, _CMP_LE_OQ);
	  else if constexpr (sizeof(__xi) == 64 && sizeof(_Tp) == 8)
	    return _mm512_mask_cmp_pd_mask(__k1, __xi, __yi, _CMP_LE_OQ);
	  else if constexpr (sizeof(__xi) == 32 && sizeof(_Tp) == 4)
	    return _mm256_mask_cmp_ps_mask(__k1, __xi, __yi, _CMP_LE_OQ);
	  else if constexpr (sizeof(__xi) == 32 && sizeof(_Tp) == 8)
	    return _mm256_mask_cmp_pd_mask(__k1, __xi, __yi, _CMP_LE_OQ);
	  else if constexpr (sizeof(__xi) == 16 && sizeof(_Tp) == 4)
	    return _mm_mask_cmp_ps_mask(__k1, __xi, __yi, _CMP_LE_OQ);
	  else if constexpr (sizeof(__xi) == 16 && sizeof(_Tp) == 8)
	    return _mm_mask_cmp_pd_mask(__k1, __xi, __yi, _CMP_LE_OQ);
	  else
	    __assert_unreachable<_Tp>();
	}
      else if constexpr(__have_avx)
        {
	  if constexpr (sizeof(__xi) == 32 && sizeof(_Tp) == 4)
	    return _mm256_cmp_ps(__xi, __yi, _CMP_LE_OQ);
	  else if constexpr (sizeof(__xi) == 32 && sizeof(_Tp) == 8)
	    return _mm256_cmp_pd(__xi, __yi, _CMP_LE_OQ);
	  else if constexpr (sizeof(__xi) == 16 && sizeof(_Tp) == 4)
	    return __auto_bitcast(_mm_cmp_ps(__xi, __yi, _CMP_LE_OQ));
	  else if constexpr (sizeof(__xi) == 16 && sizeof(_Tp) == 8)
	    return _mm_cmp_pd(__xi, __yi, _CMP_LE_OQ);
	  else
	    __assert_unreachable<_Tp>();
	}
      else if constexpr (__have_sse2 && sizeof(__xi) == 16 && sizeof(_Tp) == 4)
	{
	  const auto __xn = __vector_bitcast<int>(__xi);
	  const auto __yn = __vector_bitcast<int>(__yi);
	  const auto __xp = __xn < 0 ? -(__xn & 0x7fff'ffff) : __xn;
	  const auto __yp = __yn < 0 ? -(__yn & 0x7fff'ffff) : __yn;
	  return __auto_bitcast(__and(_mm_cmpord_ps(__xi, __yi),
				      reinterpret_cast<__m128>(__xp <= __yp)));
	}
      else if constexpr (__have_sse2 && sizeof(__xi) == 16 && sizeof(_Tp) == 8)
	return __auto_bitcast(__vector_type_t<__int_with_sizeof_t<8>, 2>{
	  -_mm_ucomige_sd(__yi, __xi),
	  -_mm_ucomige_sd(_mm_unpackhi_pd(__yi, __yi),
			  _mm_unpackhi_pd(__xi, __xi))});
      else
	return _Base::__islessequal(__x, __y);
    }

    // __islessgreater {{{3
    template <typename _Tp, size_t _N>
    static constexpr _MaskMember<_Tp>
      __islessgreater(_SimdWrapper<_Tp, _N> __x, _SimdWrapper<_Tp, _N> __y)
    {
      const auto __xi = __to_intrin(__x);
      const auto __yi = __to_intrin(__y);
      if constexpr (__is_avx512_abi<_Abi>())
	{
	  const auto __k1 = _Abi::template __implicit_mask<_Tp>();
	  if constexpr (sizeof(__xi) == 64 && sizeof(_Tp) == 4)
	    return _mm512_mask_cmp_ps_mask(__k1, __xi, __yi, _CMP_NEQ_OQ);
	  else if constexpr (sizeof(__xi) == 64 && sizeof(_Tp) == 8)
	    return _mm512_mask_cmp_pd_mask(__k1, __xi, __yi, _CMP_NEQ_OQ);
	  else if constexpr (sizeof(__xi) == 32 && sizeof(_Tp) == 4)
	    return _mm256_mask_cmp_ps_mask(__k1, __xi, __yi, _CMP_NEQ_OQ);
	  else if constexpr (sizeof(__xi) == 32 && sizeof(_Tp) == 8)
	    return _mm256_mask_cmp_pd_mask(__k1, __xi, __yi, _CMP_NEQ_OQ);
	  else if constexpr (sizeof(__xi) == 16 && sizeof(_Tp) == 4)
	    return _mm_mask_cmp_ps_mask(__k1, __xi, __yi, _CMP_NEQ_OQ);
	  else if constexpr (sizeof(__xi) == 16 && sizeof(_Tp) == 8)
	    return _mm_mask_cmp_pd_mask(__k1, __xi, __yi, _CMP_NEQ_OQ);
	  else
	    __assert_unreachable<_Tp>();
	}
      else if constexpr(__have_avx)
        {
	  if constexpr (sizeof(__xi) == 32 && sizeof(_Tp) == 4)
	    return _mm256_cmp_ps(__xi, __yi, _CMP_NEQ_OQ);
	  else if constexpr (sizeof(__xi) == 32 && sizeof(_Tp) == 8)
	    return _mm256_cmp_pd(__xi, __yi, _CMP_NEQ_OQ);
	  else if constexpr (sizeof(__xi) == 16 && sizeof(_Tp) == 4)
	    return __auto_bitcast(_mm_cmp_ps(__xi, __yi, _CMP_NEQ_OQ));
	  else if constexpr (sizeof(__xi) == 16 && sizeof(_Tp) == 8)
	    return _mm_cmp_pd(__xi, __yi, _CMP_NEQ_OQ);
	  else
	    __assert_unreachable<_Tp>();
	}
      else if constexpr (sizeof(__xi) == 16 && sizeof(_Tp) == 4)
	return __auto_bitcast(
	  __and(_mm_cmpord_ps(__xi, __yi), _mm_cmpneq_ps(__xi, __yi)));
      else if constexpr (sizeof(__xi) == 16 && sizeof(_Tp) == 8)
	return __and(_mm_cmpord_pd(__xi, __yi), _mm_cmpneq_pd(__xi, __yi));
      else
	__assert_unreachable<_Tp>();
    }

    //}}}2
};

// _MaskImplX86 {{{1
struct _MaskImplX86Mixin
{
  template <class _Tp>
  using _TypeTag = _Tp*;
  using _Base = _MaskImplBuiltinMixin;

  template <typename _Up, size_t _ToN = 1>
  _GLIBCXX_SIMD_INTRINSIC static constexpr _SimdWrapper<_Up, _ToN>
    __to_maskvector(bool __x)
  {
    using _I = __int_for_sizeof_t<_Up>;
    return __vector_bitcast<_Up>(__x ? __vector_type_t<_I, _ToN>{~_I()}
				     : __vector_type_t<_I, _ToN>{});
  }

  template <typename _Up,
	    size_t _UpN = 0,
	    size_t _N,
	    size_t _ToN = _UpN == 0 ? _N : _UpN>
  _GLIBCXX_SIMD_INTRINSIC static constexpr _SimdWrapper<_Up, _ToN>
    __to_maskvector(std::bitset<_N> __x)
  {
    using _UV               = __vector_type_t<_Up, _ToN>;
    using _UI               = __intrinsic_type_t<_Up, _ToN>;
    const auto     __k      = __x.to_ullong();
    if constexpr (sizeof(_Up) == 1)
      {
	if constexpr (sizeof(_UI) == 16)
	  {
	    if constexpr (__have_avx512bw_vl)
	      return __intrin_bitcast<_UV>(_mm_movm_epi8(__k));
	    else if constexpr (__have_avx512bw)
	      return __intrin_bitcast<_UV>(__lo128(_mm512_movm_epi8(__k)));
	    else if constexpr (__have_avx512f)
	      {
		auto __as32bits = _mm512_maskz_mov_epi32(__k, ~__m512i());
		auto __as16bits = __xzyw(
		  _mm256_packs_epi32(__lo256(__as32bits), __hi256(__as32bits)));
		return __intrin_bitcast<_UV>(
		  _mm_packs_epi16(__lo128(__as16bits), __hi128(__as16bits)));
	      }
	    else if constexpr (__have_ssse3)
	      {
		const auto __bitmask = __to_intrin(__make_vector<_UChar>(
		  1, 2, 4, 8, 16, 32, 64, 128, 1, 2, 4, 8, 16, 32, 64, 128));
		return __intrin_bitcast<_UV>(
		  __vector_bitcast<_Up>(
		    _mm_shuffle_epi8(
		      __to_intrin(__vector_type_t<_ULLong, 2>{__k}),
		      _mm_setr_epi8(0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1,
				    1)) &
		    __bitmask) != 0);
	      }
	    // else fall through
	  }
	else if constexpr (sizeof(_UI) == 32)
	  {
	    if constexpr (__have_avx512bw_vl)
	      return __vector_bitcast<_Up>(_mm256_movm_epi8(__k));
	    else if constexpr (__have_avx512bw)
	      return __vector_bitcast<_Up>(__lo256(_mm512_movm_epi8(__k)));
	    else if constexpr (__have_avx512f)
	      {
		auto __as16bits = // 0 16 1 17 ... 15 31
		  _mm512_srli_epi32(_mm512_maskz_mov_epi32(__k, ~__m512i()),
				    16) |
		  _mm512_slli_epi32(
		    _mm512_maskz_mov_epi32(__k >> 16, ~__m512i()), 16);
		auto __0_16_1_17 = __xzyw(_mm256_packs_epi16(
		  __lo256(__as16bits),
		  __hi256(__as16bits)) // 0 16 1 17 2 18 3 19 8 24 9 25 ...
		);
		// deinterleave:
		return __vector_bitcast<_Up>(__xzyw(_mm256_shuffle_epi8(
		  __0_16_1_17, // 0 16 1 17 2 ...
		  _mm256_setr_epi8(0, 2, 4, 6, 8, 10, 12, 14, 1, 3, 5, 7, 9, 11,
				   13, 15, 0, 2, 4, 6, 8, 10, 12, 14, 1, 3, 5,
				   7, 9, 11, 13,
				   15)))); // 0-7 16-23 8-15 24-31 -> xzyw
					   // 0-3  8-11 16-19 24-27
					   // 4-7 12-15 20-23 28-31
	      }
	    else if constexpr (__have_avx2)
	      {
		const auto __bitmask =
		  _mm256_broadcastsi128_si256(__to_intrin(__make_vector<_UChar>(
		    1, 2, 4, 8, 16, 32, 64, 128, 1, 2, 4, 8, 16, 32, 64, 128)));
		return __vector_bitcast<_Up>(
		  __vector_bitcast<_Up>(
		    _mm256_shuffle_epi8(
		      _mm256_broadcastsi128_si256(
			__to_intrin(__vector_type_t<_ULLong, 2>{__k})),
		      _mm256_setr_epi8(0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1,
				       1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3,
				       3, 3, 3, 3)) &
		    __bitmask) != 0);
	      }
	    // else fall through
	  }
	else if constexpr (sizeof(_UI) == 64)
	  return reinterpret_cast<__vector_type_t<_SChar, 64>>(
	    _mm512_movm_epi8(__k));
      }
    else if constexpr (sizeof(_Up) == 2)
      {
	if constexpr (sizeof(_UI) == 16)
	  {
	    if constexpr (__have_avx512bw_vl)
	      return __intrin_bitcast<_UV>(_mm_movm_epi16(__k));
	    else if constexpr (__have_avx512bw)
	      return __intrin_bitcast<_UV>(__lo128(_mm512_movm_epi16(__k)));
	    else if constexpr (__have_avx512f)
	      {
		__m256i __as32bits;
		if constexpr (__have_avx512vl)
		  __as32bits = _mm256_maskz_mov_epi32(__k, ~__m256i());
		else
		  __as32bits = __lo256(_mm512_maskz_mov_epi32(__k, ~__m512i()));
		return __intrin_bitcast<_UV>(
		  _mm_packs_epi32(__lo128(__as32bits), __hi128(__as32bits)));
	      }
	    // else fall through
	  }
	else if constexpr (sizeof(_UI) == 32)
	  {
	    if constexpr (__have_avx512bw_vl)
	      return __vector_bitcast<_Up>(_mm256_movm_epi16(__k));
	    else if constexpr (__have_avx512bw)
	      return __vector_bitcast<_Up>(__lo256(_mm512_movm_epi16(__k)));
	    else if constexpr (__have_avx512f)
	      {
		auto __as32bits = _mm512_maskz_mov_epi32(__k, ~__m512i());
		return __vector_bitcast<_Up>(__xzyw(_mm256_packs_epi32(
		  __lo256(__as32bits), __hi256(__as32bits))));
	      }
	    // else fall through
	  }
	else if constexpr (sizeof(_UI) == 64)
	  return __vector_bitcast<_Up>(_mm512_movm_epi16(__k));
      }
    else if constexpr (sizeof(_Up) == 4)
      {
	if constexpr (sizeof(_UI) == 16)
	  {
	    if constexpr (__have_avx512dq_vl)
	      return __intrin_bitcast<_UV>(_mm_movm_epi32(__k));
	    else if constexpr (__have_avx512dq)
	      return __intrin_bitcast<_UV>(__lo128(_mm512_movm_epi32(__k)));
	    else if constexpr (__have_avx512vl)
	      return __intrin_bitcast<_UV>(
		_mm_maskz_mov_epi32(__k, ~__m128i()));
	    else if constexpr (__have_avx512f)
	      return __intrin_bitcast<_UV>(
		__lo128(_mm512_maskz_mov_epi32(__k, ~__m512i())));
	    // else fall through
	  }
	else if constexpr (sizeof(_UI) == 32)
	  {
	    if constexpr (__have_avx512dq_vl)
	      return __vector_bitcast<_Up>(_mm256_movm_epi32(__k));
	    else if constexpr (__have_avx512dq)
	      return __vector_bitcast<_Up>(__lo256(_mm512_movm_epi32(__k)));
	    else if constexpr (__have_avx512vl)
	      return __vector_bitcast<_Up>(
		_mm256_maskz_mov_epi32(__k, ~__m256i()));
	    else if constexpr (__have_avx512f)
	      return __vector_bitcast<_Up>(
		__lo256(_mm512_maskz_mov_epi32(__k, ~__m512i())));
	    // else fall through
	  }
	else if constexpr (sizeof(_UI) == 64)
	  return __vector_bitcast<_Up>(
	    __have_avx512dq ? _mm512_movm_epi32(__k)
			    : _mm512_maskz_mov_epi32(__k, ~__m512i()));
      }
    else if constexpr (sizeof(_Up) == 8)
      {
	if constexpr (sizeof(_UI) == 16)
	  {
	    if constexpr (__have_avx512dq_vl)
	      return __vector_bitcast<_Up>(_mm_movm_epi64(__k));
	    else if constexpr (__have_avx512dq)
	      return __vector_bitcast<_Up>(__lo128(_mm512_movm_epi64(__k)));
	    else if constexpr (__have_avx512vl)
	      return __vector_bitcast<_Up>(
		_mm_maskz_mov_epi64(__k, ~__m128i()));
	    else if constexpr (__have_avx512f)
	      return __vector_bitcast<_Up>(
		__lo128(_mm512_maskz_mov_epi64(__k, ~__m512i())));
	    // else fall through
	  }
	else if constexpr (sizeof(_UI) == 32)
	  {
	    if constexpr (__have_avx512dq_vl)
	      return __vector_bitcast<_Up>(_mm256_movm_epi64(__k));
	    else if constexpr (__have_avx512dq)
	      return __vector_bitcast<_Up>(__lo256(_mm512_movm_epi64(__k)));
	    else if constexpr (__have_avx512vl)
	      return __vector_bitcast<_Up>(
		_mm256_maskz_mov_epi64(__k, ~__m256i()));
	    else if constexpr (__have_avx512f)
	      return __vector_bitcast<_Up>(
		__lo256(_mm512_maskz_mov_epi64(__k, ~__m512i())));
	    // else fall through
	  }
	else if constexpr (sizeof(_UI) == 64)
	  return __vector_bitcast<_Up>(
	    __have_avx512dq ? _mm512_movm_epi64(__k)
			    : _mm512_maskz_mov_epi64(__k, ~__m512i()));
      }

    using _UpUInt = std::make_unsigned_t<__int_for_sizeof_t<_Up>>;
    using _V      = __vector_type_t<_UpUInt, _ToN>;
    constexpr size_t __bits_per_element = sizeof(_Up) * CHAR_BIT;
    if constexpr (!__have_avx2 && __have_avx && sizeof(_V) == 32)
      {
	if constexpr (sizeof(_Up) == 4)
	  return __vector_bitcast<_Up>(_mm256_cmp_ps(
	    _mm256_and_ps(_mm256_castsi256_ps(_mm256_set1_epi32(__k)),
			  _mm256_castsi256_ps(_mm256_setr_epi32(
			    0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80))),
	    _mm256_setzero_ps(), _CMP_NEQ_UQ));
	else if constexpr (sizeof(_Up) == 8)
	  return __vector_bitcast<_Up>(_mm256_cmp_pd(
	    _mm256_and_pd(
	      _mm256_castsi256_pd(_mm256_set1_epi64x(__k)),
	      _mm256_castsi256_pd(_mm256_setr_epi64x(0x01, 0x02, 0x04, 0x08))),
	    _mm256_setzero_pd(), _CMP_NEQ_UQ));
	else
	  __assert_unreachable<_Up>();
      }
    else if constexpr (__bits_per_element >= _ToN)
      {
	constexpr auto __bitmask =
	  __generate_vector<__vector_type_t<_UpUInt, _ToN>>(
	    [](auto __i) constexpr->_UpUInt {
	      return __i < _ToN ? 1ull << __i : 0;
	    });
	return __vector_bitcast<_Up>(
	  (__vector_broadcast<_ToN, _UpUInt>(__k) & __bitmask) != 0);
      }
    else
      {
	const _V __tmp =
	  __generate_vector<_V>([&](auto __i) constexpr {
	    return static_cast<_UpUInt>(
	      __k >> (__bits_per_element * (__i / __bits_per_element)));
	  }) &
	  __generate_vector<_V>([](auto __i) constexpr {
	    return static_cast<_UpUInt>(1ull << (__i % __bits_per_element));
	  }); // mask bit index
	return __vector_bitcast<_Up>(__tmp != _V());
      }
  }

  template <typename _Up,
	    size_t _UpN = 0,
	    typename _Tp,
	    size_t _N,
	    size_t _ToN = _UpN == 0 ? _N : _UpN>
  _GLIBCXX_SIMD_INTRINSIC static constexpr _SimdWrapper<_Up, _ToN>
    __to_maskvector(_SimdWrapper<_Tp, _N> __x)
  {
    using _TW = _SimdWrapper<_Tp, _N>;
    using _UW = _SimdWrapper<_Up, _ToN>;
    using _UI = __intrinsic_type_t<_Up, _ToN>;
    if constexpr (sizeof(_Up) == sizeof(_Tp) && sizeof(_TW) == sizeof(_UW))
      if constexpr(_ToN <= _N)
        return __wrapper_bitcast<_Up>(__x);
      else
	return simd_abi::deduce_t<_Up, _ToN>::__masked(
	  __wrapper_bitcast<_Up, _ToN>(__x));
    else if constexpr (is_same_v<_Tp, bool>) // bits -> vector
      return __to_maskvector<_Up, _ToN>(std::bitset<_N>(__x._M_data));
    else
      { // vector -> vector {{{
	using _To = __vector_type_t<_Up, _ToN>;
	[[maybe_unused]] constexpr size_t _FromN     = _N;
	constexpr int                     _FromBytes = sizeof(_Tp);
	constexpr int                     _ToBytes   = sizeof(_Up);
	const auto                        __k        = __x._M_data;

	if constexpr (_FromBytes == _ToBytes)
	  return __intrin_bitcast<_To>(__k);
	else if constexpr (sizeof(_UI) == 16 && sizeof(__k) == 16)
	  { // SSE -> SSE {{{
	    if constexpr (_FromBytes == 4 && _ToBytes == 8)
	      return __intrin_bitcast<_To>(__interleave128_lo(__k, __k));
	    else if constexpr (_FromBytes == 2 && _ToBytes == 8)
	      {
		const auto __y =
		  __vector_bitcast<int>(__interleave128_lo(__k, __k));
		return __intrin_bitcast<_To>(__interleave128_lo(__y, __y));
	      }
	    else if constexpr (_FromBytes == 1 && _ToBytes == 8)
	      {
		auto __y =
		  __vector_bitcast<short>(__interleave128_lo(__k, __k));
		auto __z = __vector_bitcast<int>(__interleave128_lo(__y, __y));
		return __intrin_bitcast<_To>(__interleave128_lo(__z, __z));
	      }
	    else if constexpr (_FromBytes == 8 && _ToBytes == 4 && __have_sse2)
	      return __intrin_bitcast<_To>(
		_mm_packs_epi32(__vector_bitcast<_LLong>(__k), __m128i()));
	    else if constexpr (_FromBytes == 8 && _ToBytes == 4)
	      return __vector_shuffle<1, 3, 6, 7>(__vector_bitcast<_Up>(__k),
						  _UI());
	    else if constexpr (_FromBytes == 2 && _ToBytes == 4)
	      return __intrin_bitcast<_To>(__interleave128_lo(__k, __k));
	    else if constexpr (_FromBytes == 1 && _ToBytes == 4)
	      {
		const auto __y =
		  __vector_bitcast<short>(__interleave128_lo(__k, __k));
		return __intrin_bitcast<_To>(__interleave128_lo(__y, __y));
	      }
	    else if constexpr (_FromBytes == 8 && _ToBytes == 2)
	      {
		if constexpr (__have_sse2 && !__have_ssse3)
		  return __intrin_bitcast<_To>(_mm_packs_epi32(
		    _mm_packs_epi32(__vector_bitcast<_LLong>(__k), __m128i()),
		    __m128i()));
		else
		  return __intrin_bitcast<_To>(
		    __vector_permute<3, 7, -1, -1, -1, -1, -1, -1>(
		      __vector_bitcast<_Up>(__k)));
	      }
	    else if constexpr (_FromBytes == 4 && _ToBytes == 2)
	      return __intrin_bitcast<_To>(
		_mm_packs_epi32(__vector_bitcast<_LLong>(__k), __m128i()));
	    else if constexpr (_FromBytes == 1 && _ToBytes == 2)
	      return __intrin_bitcast<_To>(__interleave128_lo(__k, __k));
	    else if constexpr (_FromBytes == 8 && _ToBytes == 1 && __have_ssse3)
	      return __intrin_bitcast<_To>(_mm_shuffle_epi8(
		__vector_bitcast<_LLong>(__k),
		_mm_setr_epi8(7, 15, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
			      -1, -1, -1)));
	    else if constexpr (_FromBytes == 8 && _ToBytes == 1)
	      {
		auto __y =
		  _mm_packs_epi32(__vector_bitcast<_LLong>(__k), __m128i());
		__y = _mm_packs_epi32(__y, __m128i());
		return __intrin_bitcast<_To>(_mm_packs_epi16(__y, __m128i()));
	      }
	    else if constexpr (_FromBytes == 4 && _ToBytes == 1 && __have_ssse3)
	      return __intrin_bitcast<_To>(
		_mm_shuffle_epi8(__vector_bitcast<_LLong>(__k),
				 _mm_setr_epi8(3, 7, 11, 15, -1, -1, -1, -1, -1,
					       -1, -1, -1, -1, -1, -1, -1)));
	    else if constexpr (_FromBytes == 4 && _ToBytes == 1)
	      {
		const auto __y =
		  _mm_packs_epi32(__vector_bitcast<_LLong>(__k), __m128i());
		return __intrin_bitcast<_To>(_mm_packs_epi16(__y, __m128i()));
	      }
	    else if constexpr (_FromBytes == 2 && _ToBytes == 1)
	      return __intrin_bitcast<_To>(
		_mm_packs_epi16(__vector_bitcast<_LLong>(__k), __m128i()));
	    else
	      __assert_unreachable<_Tp>();
	  } // }}}
	else if constexpr (sizeof(_UI) == 32 && sizeof(__k) == 32)
	  { // AVX -> AVX {{{
	    if constexpr (_FromBytes == _ToBytes)
	      __assert_unreachable<_Tp>();
	    else if constexpr (_FromBytes == _ToBytes * 2)
	      {
		const auto __y = __vector_bitcast<_LLong>(__k);
		return __intrin_bitcast<_To>(_mm256_castsi128_si256(
		  _mm_packs_epi16(__lo128(__y), __hi128(__y))));
	      }
	    else if constexpr (_FromBytes == _ToBytes * 4)
	      {
		const auto __y = __vector_bitcast<_LLong>(__k);
		return __intrin_bitcast<_To>(
		  _mm256_castsi128_si256(_mm_packs_epi16(
		    _mm_packs_epi16(__lo128(__y), __hi128(__y)), __m128i())));
	      }
	    else if constexpr (_FromBytes == _ToBytes * 8)
	      {
		const auto __y = __vector_bitcast<_LLong>(__k);
		return __intrin_bitcast<_To>(
		  _mm256_castsi128_si256(_mm_shuffle_epi8(
		    _mm_packs_epi16(__lo128(__y), __hi128(__y)),
		    _mm_setr_epi8(3, 7, 11, 15, -1, -1, -1, -1, -1, -1, -1, -1,
				  -1, -1, -1, -1))));
	      }
	    else if constexpr (_FromBytes * 2 == _ToBytes)
	      {
		auto __y = __xzyw(__to_intrin(__k));
		if constexpr (std::is_floating_point_v<_Tp>)
		  {
		    return __intrin_bitcast<_To>(_mm256_unpacklo_ps(__y, __y));
		  }
		else
		  {
		    return __intrin_bitcast<_To>(
		      _mm256_unpacklo_epi8(__y, __y));
		  }
	      }
	    else if constexpr (_FromBytes * 4 == _ToBytes)
	      {
		auto __y = _mm_unpacklo_epi8(
		  __lo128(__vector_bitcast<_LLong>(__k)),
		  __lo128(__vector_bitcast<_LLong>(__k))); // drops 3/4 of input
		return __intrin_bitcast<_To>(__concat(
		  _mm_unpacklo_epi16(__y, __y), _mm_unpackhi_epi16(__y, __y)));
	      }
	    else if constexpr (_FromBytes == 1 && _ToBytes == 8)
	      {
		auto __y = _mm_unpacklo_epi8(
		  __lo128(__vector_bitcast<_LLong>(__k)),
		  __lo128(__vector_bitcast<_LLong>(__k))); // drops 3/4 of input
		__y = _mm_unpacklo_epi16(__y,
					 __y); // drops another 1/2 => 7/8 total
		return __intrin_bitcast<_To>(__concat(
		  _mm_unpacklo_epi32(__y, __y), _mm_unpackhi_epi32(__y, __y)));
	      }
	    else
	      __assert_unreachable<_Tp>();
	  } // }}}
	else if constexpr (sizeof(_UI) == 32 && sizeof(__k) == 16)
	  { // SSE -> AVX {{{
	    if constexpr (_FromBytes == _ToBytes)
	      return __intrin_bitcast<_To>(
		__intrinsic_type_t<_Tp, 32 / sizeof(_Tp)>(
		  __zero_extend(__to_intrin(__k))));
	    else if constexpr (_FromBytes * 2 == _ToBytes)
	      { // keep all
		return __intrin_bitcast<_To>(
		  __concat(_mm_unpacklo_epi8(__vector_bitcast<_LLong>(__k),
					     __vector_bitcast<_LLong>(__k)),
			   _mm_unpackhi_epi8(__vector_bitcast<_LLong>(__k),
					     __vector_bitcast<_LLong>(__k))));
	      }
	    else if constexpr (_FromBytes * 4 == _ToBytes)
	      {
		if constexpr (__have_avx2)
		  {
		    return __intrin_bitcast<_To>(_mm256_shuffle_epi8(
		      __concat(__vector_bitcast<_LLong>(__k),
			       __vector_bitcast<_LLong>(__k)),
		      _mm256_setr_epi8(0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3,
				       3, 3, 4, 4, 4, 4, 5, 5, 5, 5, 6, 6, 6, 6,
				       7, 7, 7, 7)));
		  }
		else
		  {
		    return __intrin_bitcast<_To>(__concat(
		      _mm_shuffle_epi8(__vector_bitcast<_LLong>(__k),
				       _mm_setr_epi8(0, 0, 0, 0, 1, 1, 1, 1, 2,
						     2, 2, 2, 3, 3, 3, 3)),
		      _mm_shuffle_epi8(__vector_bitcast<_LLong>(__k),
				       _mm_setr_epi8(4, 4, 4, 4, 5, 5, 5, 5, 6,
						     6, 6, 6, 7, 7, 7, 7))));
		  }
	      }
	    else if constexpr (_FromBytes * 8 == _ToBytes)
	      {
		if constexpr (__have_avx2)
		  {
		    return __intrin_bitcast<_To>(_mm256_shuffle_epi8(
		      __concat(__vector_bitcast<_LLong>(__k),
			       __vector_bitcast<_LLong>(__k)),
		      _mm256_setr_epi8(0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1,
				       1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3,
				       3, 3, 3, 3)));
		  }
		else
		  {
		    return __intrin_bitcast<_To>(__concat(
		      _mm_shuffle_epi8(__vector_bitcast<_LLong>(__k),
				       _mm_setr_epi8(0, 0, 0, 0, 0, 0, 0, 0, 1,
						     1, 1, 1, 1, 1, 1, 1)),
		      _mm_shuffle_epi8(__vector_bitcast<_LLong>(__k),
				       _mm_setr_epi8(2, 2, 2, 2, 2, 2, 2, 2, 3,
						     3, 3, 3, 3, 3, 3, 3))));
		  }
	      }
	    else if constexpr (_FromBytes == _ToBytes * 2)
	      {
		return __intrin_bitcast<_To>(__m256i(__zero_extend(
		  _mm_packs_epi16(__vector_bitcast<_LLong>(__k), __m128i()))));
	      }
	    else if constexpr (_FromBytes == 8 && _ToBytes == 2)
	      {
		return __intrin_bitcast<_To>(
		  __m256i(__zero_extend(_mm_shuffle_epi8(
		    __vector_bitcast<_LLong>(__k),
		    _mm_setr_epi8(6, 7, 14, 15, -1, -1, -1, -1, -1, -1, -1, -1,
				  -1, -1, -1, -1)))));
	      }
	    else if constexpr (_FromBytes == 4 && _ToBytes == 1)
	      {
		return __intrin_bitcast<_To>(
		  __m256i(__zero_extend(_mm_shuffle_epi8(
		    __vector_bitcast<_LLong>(__k),
		    _mm_setr_epi8(3, 7, 11, 15, -1, -1, -1, -1, -1, -1, -1, -1,
				  -1, -1, -1, -1)))));
	      }
	    else if constexpr (_FromBytes == 8 && _ToBytes == 1)
	      {
		return __intrin_bitcast<_To>(
		  __m256i(__zero_extend(_mm_shuffle_epi8(
		    __vector_bitcast<_LLong>(__k),
		    _mm_setr_epi8(7, 15, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
				  -1, -1, -1, -1)))));
	      }
	    else
	      {
		static_assert(!std::is_same_v<_Tp, _Tp>,
			      "should be unreachable");
	      }
	  } // }}}
	else if constexpr (sizeof(_UI) == 16 && sizeof(__k) == 32)
	  { // AVX -> SSE {{{
	    if constexpr (_FromBytes == _ToBytes)
	      { // keep low 1/2
		return __intrin_bitcast<_To>(__lo128(__k));
	      }
	    else if constexpr (_FromBytes == _ToBytes * 2)
	      { // keep all
		auto __y = __vector_bitcast<_LLong>(__k);
		return __intrin_bitcast<_To>(
		  _mm_packs_epi16(__lo128(__y), __hi128(__y)));
	      }
	    else if constexpr (_FromBytes == _ToBytes * 4)
	      { // add 1/2 undef
		auto __y = __vector_bitcast<_LLong>(__k);
		return __intrin_bitcast<_To>(_mm_packs_epi16(
		  _mm_packs_epi16(__lo128(__y), __hi128(__y)), __m128i()));
	      }
	    else if constexpr (_FromBytes == 8 && _ToBytes == 1)
	      { // add 3/4 undef
		auto __y = __vector_bitcast<_LLong>(__k);
		return __intrin_bitcast<_To>(_mm_shuffle_epi8(
		  _mm_packs_epi16(__lo128(__y), __hi128(__y)),
		  _mm_setr_epi8(3, 7, 11, 15, -1, -1, -1, -1, -1, -1, -1, -1,
				-1, -1, -1, -1)));
	      }
	    else if constexpr (_FromBytes * 2 == _ToBytes)
	      { // keep low 1/4
		auto __y = __lo128(__vector_bitcast<_LLong>(__k));
		return __intrin_bitcast<_To>(_mm_unpacklo_epi8(__y, __y));
	      }
	    else if constexpr (_FromBytes * 4 == _ToBytes)
	      { // keep low 1/8
		auto __y = __lo128(__vector_bitcast<_LLong>(__k));
		__y      = _mm_unpacklo_epi8(__y, __y);
		return __intrin_bitcast<_To>(_mm_unpacklo_epi8(__y, __y));
	      }
	    else if constexpr (_FromBytes * 8 == _ToBytes)
	      { // keep low 1/16
		auto __y = __lo128(__vector_bitcast<_LLong>(__k));
		__y      = _mm_unpacklo_epi8(__y, __y);
		__y      = _mm_unpacklo_epi8(__y, __y);
		return __intrin_bitcast<_To>(_mm_unpacklo_epi8(__y, __y));
	      }
	    else
	      {
		static_assert(!std::is_same_v<_Tp, _Tp>,
			      "should be unreachable");
	      }
	  } // }}}
	else
	  return _Base::template __to_maskvector<_Up, _ToN>(__x);
	/*
	if constexpr (_FromBytes > _ToBytes) {
	    const _To     __y      = __vector_bitcast<_Up>(__k);
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
	      return __intrin_bitcast<_To>(_From{__k[_Is / __dup]...});
	    }(std::make_index_sequence<_FromN>());
	}
	*/
      } // }}}
  }

  template <typename _Tp, size_t _N>
  _GLIBCXX_SIMD_INTRINSIC static constexpr auto
    __to_bits(_SimdWrapper<_Tp, _N> __x)
  {
    if constexpr (is_same_v<_Tp, bool>)
      return __x._M_data;
    else
      {
	const auto       __xi   = __to_intrin(__x);
	if constexpr (is_floating_point_v<_Tp>)
	  if constexpr (sizeof(_Tp) == 4) // float
	    if constexpr (sizeof(__xi) == 16)
	      return _UChar(_mm_movemask_ps(__xi));
	    else if constexpr (sizeof(__xi) == 32)
	      return _UChar(_mm256_movemask_ps(__xi));
	    else if constexpr (__have_avx512dq)
	      return _mm512_movepi32_mask(reinterpret_cast<__m512i>(__xi));
	    else
	      return _mm512_cmp_ps_mask(__xi, __xi, _CMP_UNORD_Q);
	  else // implies double
	    if constexpr (sizeof(__xi) == 16)
	      return _UChar(_mm_movemask_pd(__xi));
	    else if constexpr (sizeof(__xi) == 32)
	      return _UChar(_mm256_movemask_pd(__xi));
	    else if constexpr (__have_avx512dq)
	      return _mm512_movepi64_mask(reinterpret_cast<__m512i>(__xi));
	    else
	      return _mm512_cmp_pd_mask(__xi, __xi, _CMP_UNORD_Q);

	else if constexpr (sizeof(_Tp) == 1)
	  if constexpr (sizeof(__xi) == 16)
	    if constexpr (__have_avx512bw_vl)
	      return _mm_movepi8_mask(__xi);
	    else // implies SSE2
	      return _UShort(_mm_movemask_epi8(__xi));
	  else if constexpr (sizeof(__xi) == 32)
	    if constexpr (__have_avx512bw_vl)
	      return _mm256_movepi8_mask(__xi);
	    else // implies AVX2
	      return _UInt(_mm256_movemask_epi8(__xi));
	  else // implies AVX512BW
	    return _mm512_movepi8_mask(__xi);

	else if constexpr (sizeof(_Tp) == 2)
	  if constexpr (sizeof(__xi) == 16)
	    if constexpr (__have_avx512bw_vl)
	      return _mm_movepi16_mask(__xi);
	    else if constexpr (__have_avx512bw)
	      return __mmask8(_mm512_movepi16_mask(__zero_extend(__xi)));
	    else // implies SSE2
	      return _UChar(_mm_movemask_epi8(_mm_packs_epi16(__xi, __m128i())));
	  else if constexpr (sizeof(__xi) == 32)
	    if constexpr (__have_avx512bw_vl)
	      return _mm256_movepi16_mask(__xi);
	    else if constexpr (__have_avx512bw)
	      return __mmask16(_mm512_movepi16_mask(__zero_extend(__xi)));
	    else // implies SSE2
	      return _UShort(_mm_movemask_epi8(_mm_packs_epi16(__lo128(__xi), __hi128(__xi))));
	  else // implies AVX512BW
	    return _mm512_movepi16_mask(__xi);

	else if constexpr (sizeof(_Tp) == 4)
	  if constexpr (sizeof(__xi) == 16)
	    if constexpr (__have_avx512dq_vl)
	      return _mm_movepi32_mask(__xi);
	    else if constexpr (__have_avx512vl)
	      return _mm_cmplt_epi32_mask(__xi, __m128i());
	    else if constexpr (__have_avx512dq)
	      return __mmask8(_mm512_movepi32_mask(__zero_extend(__xi)));
	    else if constexpr (__have_avx512f)
	      return __mmask8(_mm512_cmplt_epi32_mask(__zero_extend(__xi), __m512i()));
	    else // implies SSE
	      return _mm_movemask_ps(reinterpret_cast<__m128>(__xi));
	  else if constexpr (sizeof(__xi) == 32)
	    if constexpr (__have_avx512dq_vl)
	      return _mm256_movepi32_mask(__xi);
	    else if constexpr (__have_avx512dq)
	      return __mmask8(_mm512_movepi32_mask( __zero_extend(__xi)));
	    else if constexpr (__have_avx512vl)
	      return _mm256_cmplt_epi32_mask(__xi, __m256i());
	    else if constexpr (__have_avx512f)
	      return __mmask8(_mm512_cmplt_epi32_mask(__zero_extend(__xi), __m512i()));
	    else // implies AVX
	      return _mm256_movemask_ps(reinterpret_cast<__m256>(__xi));
	  else // implies AVX512??
	    if constexpr (__have_avx512dq)
	      return _mm512_movepi32_mask(__xi);
	    else // implies AVX512F
	      return _mm512_cmplt_epi32_mask(__xi, __m512i());

	else if constexpr (sizeof(_Tp) == 8)
	  if constexpr (sizeof(__xi) == 16)
	    if constexpr (__have_avx512dq_vl)
	      return _mm_movepi64_mask(__xi);
	    else if constexpr (__have_avx512dq)
	      return _mm512_movepi64_mask(__zero_extend(__xi));
	    else if constexpr (__have_avx512vl)
	      return _mm_cmplt_epi64_mask(__xi, __m128i());
	    else if constexpr (__have_avx512f)
	      return _mm512_cmplt_epi64_mask(__zero_extend(__xi), __m512i());
	    else // implies SSE2
	      return _UChar(_mm_movemask_pd(reinterpret_cast<__m128d>(__xi)));
	  else if constexpr (sizeof(__xi) == 32)
	    if constexpr (__have_avx512dq_vl)
	      return _mm256_movepi64_mask(__xi);
	    else if constexpr (__have_avx512dq)
	      return _mm512_movepi64_mask(__zero_extend(__xi));
	    else if constexpr (__have_avx512vl)
	      return _mm256_cmplt_epi64_mask(__xi, __m256i());
	    else if constexpr (__have_avx512f)
	      return _mm512_cmplt_epi64_mask(__zero_extend(__xi), __m512i());
	    else // implies AVX
	      return _mm256_movemask_pd(reinterpret_cast<__m256d>(__xi));
	  else // implies AVX512??
	    if constexpr (__have_avx512dq)
	      return _mm512_movepi64_mask(__xi);
	    else // implies AVX512F
	      return _mm512_cmplt_epi64_mask(__xi, __m512i());

	else
	  __assert_unreachable<_Tp>();
      }
  }
};

template <typename _Abi>
struct _MaskImplX86 : _MaskImplX86Mixin, _MaskImplBuiltin<_Abi>
{
  using _MaskImplX86Mixin::__to_maskvector;
  using _MaskImplX86Mixin::__to_bits;

  // member types {{{
  template <class _Tp>
  using _SimdMember = typename _Abi::template __traits<_Tp>::_SimdMember;
  template <class _Tp>
  using _MaskMember = typename _Abi::template __traits<_Tp>::_MaskMember;
  template <typename _Tp>
  static constexpr size_t size = simd_size_v<_Tp, _Abi>;
  using _Base = _MaskImplBuiltin<_Abi>;

  // }}}
  // __convert {{{
  template <typename _Tp, size_t _N>
  _GLIBCXX_SIMD_INTRINSIC static constexpr auto __convert(_SimdWrapper<bool, _N> __x)
  {
    if constexpr (__is_avx512_abi<_Abi>())
      return _SimdWrapper<bool, simd_size_v<_Tp, _Abi>>(__x);
    else
      return __to_maskvector<_Tp, size<_Tp>>(__x);
  }

  template <typename _Tp, typename _Up, size_t _N>
  _GLIBCXX_SIMD_INTRINSIC static constexpr auto __convert(_SimdWrapper<_Up, _N> __x)
  {
    if constexpr (__is_avx512_abi<_Abi>())
      return _SimdWrapper<bool, simd_size_v<_Tp, _Abi>>(__to_bits(__x));
    else
      return __to_maskvector<_Tp, size<_Tp>>(__x);
  }

  template <typename _Tp, typename _Up, typename _UAbi>
  _GLIBCXX_SIMD_INTRINSIC static constexpr auto __convert(simd_mask<_Up, _UAbi> __x)
  {
    if constexpr (__is_avx512_abi<_Abi>())
      {
	using _R = _SimdWrapper<bool, simd_size_v<_Tp, _Abi>>;
	if constexpr (__is_avx512_abi<_UAbi>()) // bits -> bits
//X 	  if constexpr (simd_size_v<_Tp, _Abi> < __x.size())
//X 	    return _R(_Abi::__masked(__data(__x))._M_data);
//X 	  else if constexpr ((simd_size_v<_Tp, _Abi>) > __x.size())
//X 	    return _R(_UAbi::__masked(__data(__x))._M_data);
//X 	  else
	    return _R(__data(__x));
	else if constexpr (__is_scalar_abi<_UAbi>()) // bool -> bits
	  return _R(__data(__x));
	else if constexpr (__is_fixed_size_abi_v<_UAbi>) // bitset -> bits
//X 	  if constexpr (simd_size_v<_Tp, _Abi> < __x.size())
//X 	    return _Abi::__masked(_R(__data(__x).to_ullong()));
//X 	  else
	    return _R(__data(__x).to_ullong());
	else // vector -> bits
	  return _R(_UAbi::_MaskImpl::__to_bits(__data(__x)));
      }
    else
      return __to_maskvector<_Tp, size<_Tp>>(__data(__x));
  }

  // }}}
  // __from_bitset{{{
  template <size_t _N, class _Tp>
  _GLIBCXX_SIMD_INTRINSIC static _MaskMember<_Tp>
    __from_bitset(std::bitset<_N> __bits, _TypeTag<_Tp>)
  {
    if constexpr (__is_avx512_abi<_Abi>())
      return __bits.to_ullong();
    else
      return __to_maskvector<_Tp, size<_Tp>>(__bits);
  }

  // }}}
  // __masked_load {{{2
  template <class _Tp, size_t _N, class _F>
  static inline _SimdWrapper<_Tp, _N> __masked_load(_SimdWrapper<_Tp, _N> __merge,
						  _SimdWrapper<_Tp, _N> __mask,
						  const bool*           __mem,
						  _F) noexcept
  {
    if constexpr (__is_avx512_abi<_Abi>())
      {
	if constexpr (__have_avx512bw_vl)
	  {
	    if constexpr (_N == 8)
	      {
		const auto __a = _mm_mask_loadu_epi8(__m128i(), __mask, __mem);
		return (__merge & ~__mask) | _mm_test_epi8_mask(__a, __a);
	      }
	    else if constexpr (_N == 16)
	      {
		const auto __a = _mm_mask_loadu_epi8(__m128i(), __mask, __mem);
		return (__merge & ~__mask) | _mm_test_epi8_mask(__a, __a);
	      }
	    else if constexpr (_N == 32)
	      {
		const auto __a = _mm256_mask_loadu_epi8(__m256i(), __mask, __mem);
		return (__merge & ~__mask) | _mm256_test_epi8_mask(__a, __a);
	      }
	    else if constexpr (_N == 64)
	      {
		const auto __a = _mm512_mask_loadu_epi8(__m512i(), __mask, __mem);
		return (__merge & ~__mask) | _mm512_test_epi8_mask(__a, __a);
	      }
	    else
	      {
		__assert_unreachable<_Tp>();
	      }
	  }
	else
	  {
	    _BitOps::__bit_iteration(
	      __mask, [&](auto __i) { __merge.__set(__i, __mem[__i]); });
	    return __merge;
	  }
      }
    else if constexpr (__have_avx512bw_vl && _N == 32 && sizeof(_Tp) == 1)
      {
	const auto __k = __to_bits(__mask);
	__merge =
	  _mm256_mask_sub_epi8(__to_intrin(__merge), __k, __m256i(),
			       _mm256_mask_loadu_epi8(__m256i(), __k, __mem));
      }
    else if constexpr (__have_avx512bw_vl && _N == 16 && sizeof(_Tp) == 1)
      {
	const auto __k = __to_bits(__mask);
	__merge =
	  _mm_mask_sub_epi8(__vector_bitcast<_LLong>(__merge), __k, __m128i(),
			    _mm_mask_loadu_epi8(__m128i(), __k, __mem));
      }
    else if constexpr (__have_avx512bw_vl && _N == 16 && sizeof(_Tp) == 2)
      {
	const auto __k = __to_bits(__mask);
	__merge        = _mm256_mask_sub_epi16(
          __vector_bitcast<_LLong>(__merge), __k, __m256i(),
          _mm256_cvtepi8_epi16(_mm_mask_loadu_epi8(__m128i(), __k, __mem)));
      }
    else if constexpr (__have_avx512bw_vl && _N == 8 && sizeof(_Tp) == 2)
      {
	const auto __k = __to_bits(__mask);
	__merge        = _mm_mask_sub_epi16(
          __vector_bitcast<_LLong>(__merge), __k, __m128i(),
          _mm_cvtepi8_epi16(_mm_mask_loadu_epi8(__m128i(), __k, __mem)));
      }
    else if constexpr (__have_avx512bw_vl && _N == 8 && sizeof(_Tp) == 4)
      {
	const auto __k = __to_bits(__mask);
	__merge        = __vector_bitcast<_Tp>(_mm256_mask_sub_epi32(
          __vector_bitcast<_LLong>(__merge), __k, __m256i(),
          _mm256_cvtepi8_epi32(_mm_mask_loadu_epi8(__m128i(), __k, __mem))));
      }
    else if constexpr (__have_avx512bw_vl && _N == 4 && sizeof(_Tp) == 4)
      {
	const auto __k = __to_bits(__mask);
	__merge        = __vector_bitcast<_Tp>(_mm_mask_sub_epi32(
          __vector_bitcast<_LLong>(__merge), __k, __m128i(),
          _mm_cvtepi8_epi32(_mm_mask_loadu_epi8(__m128i(), __k, __mem))));
      }
    else if constexpr (__have_avx512bw_vl && _N == 4 && sizeof(_Tp) == 8)
      {
	const auto __k = __to_bits(__mask);
	__merge        = __vector_bitcast<_Tp>(_mm256_mask_sub_epi64(
          __vector_bitcast<_LLong>(__merge), __k, __m256i(),
          _mm256_cvtepi8_epi64(_mm_mask_loadu_epi8(__m128i(), __k, __mem))));
      }
    else if constexpr (__have_avx512bw_vl && _N == 2 && sizeof(_Tp) == 8)
      {
	const auto __k = __to_bits(__mask);
	__merge        = __vector_bitcast<_Tp>(_mm_mask_sub_epi64(
          __vector_bitcast<_LLong>(__merge), __k, __m128i(),
          _mm_cvtepi8_epi64(_mm_mask_loadu_epi8(__m128i(), __k, __mem))));
      }
    else
      {
	return _Base::__masked_load(__merge, __mask, __mem, _F{});
      }
    return __merge;
  }

  // __store {{{2
  template <class _Tp, size_t _N, class _F>
  _GLIBCXX_SIMD_INTRINSIC static void
    __store(_SimdWrapper<_Tp, _N> __v, bool* __mem, _F) noexcept
  {
    if constexpr (__is_sse_abi<_Abi>())
      {
	if constexpr (_N == 2 && __have_sse2)
	  {
	    const auto __k = __vector_bitcast<int>(__v);
	    __mem[0]       = -__k[1];
	    __mem[1]       = -__k[3];
	  }
	else if constexpr (_N == 4 && __have_sse2)
	  {
	    const unsigned __bool4 =
	      __vector_bitcast<_UInt>(_mm_packs_epi16(
		_mm_packs_epi32(__vector_bitcast<_LLong>(__v), __m128i()),
		__m128i()))[0] &
	      0x01010101u;
	    std::memcpy(__mem, &__bool4, 4);
	  }
	else if constexpr (std::is_same_v<_Tp, float> && __have_mmx)
	  {
	    const __m128 __k = __to_intrin(__v);
	    const __m64  __kk  = _mm_cvtps_pi8(__and(__k, _mm_set1_ps(1.f)));
	    __vector_store<4>(__kk, __mem, _F());
	    _mm_empty();
	  }
	else if constexpr (_N == 8 && __have_sse2)
	  {
	    __vector_store<8>(
	      _mm_packs_epi16(__to_intrin(__vector_bitcast<_UShort>(__v) >> 15),
			      __m128i()),
	      __mem, _F());
	  }
	else if constexpr (_N == 16 && __have_sse2)
	  {
	    __vector_store(__v._M_data & 1, __mem, _F());
	  }
	else
	  {
	    __assert_unreachable<_Tp>();
	  }
      }
    else if constexpr (__is_avx_abi<_Abi>())
      {
	if constexpr (_N == 4 && __have_avx)
	  {
	    auto __k = __vector_bitcast<_LLong>(__v);
	    int  __bool4;
	    if constexpr (__have_avx2)
	      {
		__bool4 = _mm256_movemask_epi8(__k);
	      }
	    else
	      {
		__bool4 = (_mm_movemask_epi8(__lo128(__k)) |
			 (_mm_movemask_epi8(__hi128(__k)) << 16));
	      }
	    __bool4 &= 0x01010101;
	    std::memcpy(__mem, &__bool4, 4);
	  }
	else if constexpr (_N == 8 && __have_avx)
	  {
	    const auto __k = __vector_bitcast<_LLong>(__v);
	    const auto __k2 =
	      _mm_srli_epi16(_mm_packs_epi16(__lo128(__k), __hi128(__k)), 15);
	    const auto __k3 = _mm_packs_epi16(__k2, __m128i());
	    __vector_store<8>(__k3, __mem, _F());
	  }
	else if constexpr (_N == 16 && __have_avx2)
	  {
	    const auto __x   = _mm256_srli_epi16(__to_intrin(__v), 15);
	    const auto __bools = _mm_packs_epi16(__lo128(__x), __hi128(__x));
	    __vector_store<16>(__bools, __mem, _F());
	  }
	else if constexpr (_N == 16 && __have_avx)
	  {
	    const auto __bools =
	      1 & __vector_bitcast<_UChar>(_mm_packs_epi16(
		    __lo128(__to_intrin(__v)), __hi128(__to_intrin(__v))));
	    __vector_store<16>(__bools, __mem, _F());
	  }
	else if constexpr (_N == 32 && __have_avx)
	  {
	    __vector_store<32>(1 & __v._M_data, __mem, _F());
	  }
	else
	  {
	    __assert_unreachable<_Tp>();
	  }
      }
    else if constexpr (__is_avx512_abi<_Abi>())
      {
	if constexpr (_N == 8)
	  {
	    __vector_store<8>(
#if _GLIBCXX_SIMD_HAVE_AVX512VL && _GLIBCXX_SIMD_HAVE_AVX512BW
	      _mm_maskz_set1_epi8(__v._M_data, 1),
#elif defined __x86_64__
	      __make_wrapper<_ULLong>(
		_pdep_u64(__v._M_data, 0x0101010101010101ULL), 0ull),
#else
	      __make_wrapper<_UInt>(_pdep_u32(__v._M_data, 0x01010101U),
				    _pdep_u32(__v._M_data >> 4, 0x01010101U)),
#endif
	      __mem, _F());
	  }
	else if constexpr (_N == 16 && __have_avx512bw_vl)
	  {
	    __vector_store(_mm_maskz_set1_epi8(__v._M_data, 1), __mem, _F());
	  }
	else if constexpr (_N == 16 && __have_avx512f)
	  {
	    _mm512_mask_cvtepi32_storeu_epi8(
	      __mem, ~__mmask16(), _mm512_maskz_set1_epi32(__v._M_data, 1));
	  }
	else if constexpr (_N == 32 && __have_avx512bw_vl)
	  {
	    __vector_store(_mm256_maskz_set1_epi8(__v._M_data, 1), __mem, _F());
	  }
	else if constexpr (_N == 32 && __have_avx512bw)
	  {
	    __vector_store(__lo256(_mm512_maskz_set1_epi8(__v._M_data, 1)),
			   __mem, _F());
	  }
	else if constexpr (_N == 64 && __have_avx512bw)
	  {
	    __vector_store(_mm512_maskz_set1_epi8(__v._M_data, 1), __mem, _F());
	  }
	else
	  {
	    __assert_unreachable<_Tp>();
	  }
      }
    else
      {
	__assert_unreachable<_Tp>();
      }
  }

  // __masked_store {{{2
  template <class _Tp, size_t _N, class _F>
  static inline void __masked_store(const _SimdWrapper<_Tp, _N> __v,
				  bool*                       __mem,
				  _F,
				  const _SimdWrapper<_Tp, _N> __k) noexcept
  {
    if constexpr (__is_avx512_abi<_Abi>())
      {
	if constexpr (_N == 8 && __have_avx512bw_vl)
	  {
	    _mm_mask_cvtepi16_storeu_epi8(__mem, __k,
					  _mm_maskz_set1_epi16(__v, 1));
	  }
	else if constexpr (_N == 8 && __have_avx512vl)
	  {
	    _mm256_mask_cvtepi32_storeu_epi8(__mem, __k,
					     _mm256_maskz_set1_epi32(__v, 1));
	  }
	else if constexpr (_N == 8)
	  {
	    // we rely on __k < 0x100:
	    _mm512_mask_cvtepi32_storeu_epi8(__mem, __k,
					     _mm512_maskz_set1_epi32(__v, 1));
	  }
	else if constexpr (_N == 16 && __have_avx512bw_vl)
	  {
	    _mm_mask_storeu_epi8(__mem, __k, _mm_maskz_set1_epi8(__v, 1));
	  }
	else if constexpr (_N == 16)
	  {
	    _mm512_mask_cvtepi32_storeu_epi8(__mem, __k,
					     _mm512_maskz_set1_epi32(__v, 1));
	  }
	else if constexpr (_N == 32 && __have_avx512bw_vl)
	  {
	    _mm256_mask_storeu_epi8(__mem, __k, _mm256_maskz_set1_epi8(__v, 1));
	  }
	else if constexpr (_N == 32 && __have_avx512bw)
	  {
	    _mm256_mask_storeu_epi8(__mem, __k,
				    __lo256(_mm512_maskz_set1_epi8(__v, 1)));
	  }
	else if constexpr (_N == 64 && __have_avx512bw)
	  {
	    _mm512_mask_storeu_epi8(__mem, __k, _mm512_maskz_set1_epi8(__v, 1));
	  }
	else
	  {
	    __assert_unreachable<_Tp>();
	  }
      }
    else
      {
	_Base::__masked_store(__v, __mem, _F(), __k);
      }
  }

  // logical and bitwise operators {{{2
  template <class _Tp, size_t _N>
  _GLIBCXX_SIMD_INTRINSIC static constexpr _SimdWrapper<_Tp, _N>
    __logical_and(const _SimdWrapper<_Tp, _N>& __x,
		const _SimdWrapper<_Tp, _N>& __y)
  {
    if constexpr (std::is_same_v<_Tp, bool>)
      {
	if constexpr (__have_avx512dq && _N <= 8)
	  return _kand_mask8(__x._M_data, __y._M_data);
	else if constexpr (_N <= 16)
	  return _kand_mask16(__x._M_data, __y._M_data);
	else if constexpr (__have_avx512bw && _N <= 32)
	  return _kand_mask32(__x._M_data, __y._M_data);
	else if constexpr (__have_avx512bw && _N <= 64)
	  return _kand_mask64(__x._M_data, __y._M_data);
	else
	  __assert_unreachable<_Tp>();
      }
    else
      return _Base::__logical_and(__x, __y);
  }

  template <class _Tp, size_t _N>
  _GLIBCXX_SIMD_INTRINSIC static constexpr _SimdWrapper<_Tp, _N>
    __logical_or(const _SimdWrapper<_Tp, _N>& __x,
	       const _SimdWrapper<_Tp, _N>& __y)
  {
    if constexpr (std::is_same_v<_Tp, bool>)
      {
	if constexpr (__have_avx512dq && _N <= 8)
	  return _kor_mask8(__x._M_data, __y._M_data);
	else if constexpr (_N <= 16)
	  return _kor_mask16(__x._M_data, __y._M_data);
	else if constexpr (__have_avx512bw && _N <= 32)
	  return _kor_mask32(__x._M_data, __y._M_data);
	else if constexpr (__have_avx512bw && _N <= 64)
	  return _kor_mask64(__x._M_data, __y._M_data);
	else
	  __assert_unreachable<_Tp>();
      }
    else
      return _Base::__logical_or(__x, __y);
  }

  template <typename _Tp, size_t _N>
  _GLIBCXX_SIMD_INTRINSIC static constexpr _SimdWrapper<_Tp, _N>
    __bit_not(const _SimdWrapper<_Tp, _N>& __x)
  {
    if constexpr (std::is_same_v<_Tp, bool>)
      {
	if constexpr (__have_avx512dq && _N <= 8)
	  return _kandn_mask8(__x._M_data,
			      _Abi::template __implicit_mask_n<_N>());
	else if constexpr (_N <= 16)
	  return _kandn_mask16(__x._M_data,
			      _Abi::template __implicit_mask_n<_N>());
	else if constexpr (__have_avx512bw && _N <= 32)
	  return _kandn_mask32(__x._M_data,
			      _Abi::template __implicit_mask_n<_N>());
	else if constexpr (__have_avx512bw && _N <= 64)
	  return _kandn_mask64(__x._M_data,
			      _Abi::template __implicit_mask_n<_N>());
	else
	  __assert_unreachable<_Tp>();
      }
    else
      return _Base::__bit_not(__x);
  }

  template <class _Tp, size_t _N>
  _GLIBCXX_SIMD_INTRINSIC static constexpr _SimdWrapper<_Tp, _N>
    __bit_and(const _SimdWrapper<_Tp, _N>& __x, const _SimdWrapper<_Tp, _N>& __y)
  {
    if constexpr (std::is_same_v<_Tp, bool>)
      {
	if constexpr (__have_avx512dq && _N <= 8)
	  return _kand_mask8(__x._M_data, __y._M_data);
	else if constexpr (_N <= 16)
	  return _kand_mask16(__x._M_data, __y._M_data);
	else if constexpr (__have_avx512bw && _N <= 32)
	  return _kand_mask32(__x._M_data, __y._M_data);
	else if constexpr (__have_avx512bw && _N <= 64)
	  return _kand_mask64(__x._M_data, __y._M_data);
	else
	  __assert_unreachable<_Tp>();
      }
    else
      return _Base::__bit_and(__x, __y);
  }

  template <class _Tp, size_t _N>
  _GLIBCXX_SIMD_INTRINSIC static constexpr _SimdWrapper<_Tp, _N>
    __bit_or(const _SimdWrapper<_Tp, _N>& __x, const _SimdWrapper<_Tp, _N>& __y)
  {
    if constexpr (std::is_same_v<_Tp, bool>)
      {
	if constexpr (__have_avx512dq && _N <= 8)
	  return _kor_mask8(__x._M_data, __y._M_data);
	else if constexpr (_N <= 16)
	  return _kor_mask16(__x._M_data, __y._M_data);
	else if constexpr (__have_avx512bw && _N <= 32)
	  return _kor_mask32(__x._M_data, __y._M_data);
	else if constexpr (__have_avx512bw && _N <= 64)
	  return _kor_mask64(__x._M_data, __y._M_data);
	else
	  __assert_unreachable<_Tp>();
      }
    else
      return _Base::__bit_or(__x, __y);
  }

  template <class _Tp, size_t _N>
  _GLIBCXX_SIMD_INTRINSIC static constexpr _SimdWrapper<_Tp, _N>
    __bit_xor(const _SimdWrapper<_Tp, _N>& __x, const _SimdWrapper<_Tp, _N>& __y)
  {
    if constexpr (std::is_same_v<_Tp, bool>)
      {
	if constexpr (__have_avx512dq && _N <= 8)
	  return _kxor_mask8(__x._M_data, __y._M_data);
	else if constexpr (_N <= 16)
	  return _kxor_mask16(__x._M_data, __y._M_data);
	else if constexpr (__have_avx512bw && _N <= 32)
	  return _kxor_mask32(__x._M_data, __y._M_data);
	else if constexpr (__have_avx512bw && _N <= 64)
	  return _kxor_mask64(__x._M_data, __y._M_data);
	else
	  __assert_unreachable<_Tp>();
      }
    else
      return _Base::__bit_xor(__x, __y);
  }

  //}}}2
};

//}}}1

_GLIBCXX_SIMD_END_NAMESPACE
#endif  // __cplusplus >= 201703L
#endif  // _GLIBCXX_EXPERIMENTAL_SIMD_X86_H_
// vim: foldmethod=marker sw=2 noet ts=8 sts=2 tw=80
