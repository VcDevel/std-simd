// Simd NEON specific implementations -*- C++ -*-

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

#ifndef _GLIBCXX_EXPERIMENTAL_SIMD_NEON_H_
#define _GLIBCXX_EXPERIMENTAL_SIMD_NEON_H_

#if __cplusplus >= 201703L

#if !_GLIBCXX_SIMD_HAVE_NEON
#error "simd_neon.h may only be included when NEON on ARM is available"
#endif

_GLIBCXX_SIMD_BEGIN_NAMESPACE

// _CommonImplNeon {{{
struct _CommonImplNeon : _CommonImplBuiltin
{
  // __store {{{
  using _CommonImplBuiltin::__store;

  // }}}
};

// }}}
// _SimdImplNeon {{{
template <typename _Abi>
struct _SimdImplNeon : _SimdImplBuiltin<_Abi>
{
  using _Base = _SimdImplBuiltin<_Abi>;
  template <typename _Tp>
  static constexpr size_t _S_max_store_size = 16;

  // __masked_load {{{
  template <typename _Tp, size_t _Np, typename _Up, typename _Fp>
  static inline _SimdWrapper<_Tp, _Np>
    __masked_load(_SimdWrapper<_Tp, _Np> __merge,
		  _SimdWrapper<_Tp, _Np> __k,
		  const _Up*            __mem,
		  _Fp) noexcept
  {
    __execute_n_times<_Np>([&](auto __i) {
      if (__k[__i] != 0)
	__merge.__set(__i, static_cast<_Tp>(__mem[__i]));
    });
    return __merge;
  }

  // }}}
  // __masked_store_nocvt {{{
  template <typename _Tp, std::size_t _Np, typename _Fp>
  _GLIBCXX_SIMD_INTRINSIC static void __masked_store_nocvt(
    _SimdWrapper<_Tp, _Np> __v, _Tp* __mem, _Fp, _SimdWrapper<_Tp, _Np> __k)
  {
    __execute_n_times<_Np>([&](auto __i) {
      if (__k[__i] != 0)
	__mem[__i] = __v[__i];
    });
  }

  // }}}
  // __reduce {{{
  template <typename _Tp, typename _BinaryOperation>
  _GLIBCXX_SIMD_INTRINSIC static _Tp
    __reduce(simd<_Tp, _Abi> __x, _BinaryOperation&& __binary_op)
  {
    constexpr size_t _Np = __x.size();
    if constexpr (sizeof(__x) == 16 && _Np >= 4 && !_Abi::_S_is_partial)
      {
	const auto __halves = split<simd<_Tp, simd_abi::_Neon<8>>>(__x);
	const auto __y      = __binary_op(__halves[0], __halves[1]);
	return _SimdImplNeon<simd_abi::_Neon<8>>::__reduce(
	  __y, static_cast<_BinaryOperation&&>(__binary_op));
      }
    else if constexpr (_Np == 8)
      {
	__x = __binary_op(
	  __x, _Base::template __make_simd<_Tp, _Np>(
		 __vector_permute<1, 0, 3, 2, 5, 4, 7, 6>(__x._M_data)));
	__x = __binary_op(
	  __x, _Base::template __make_simd<_Tp, _Np>(
		 __vector_permute<3, 2, 1, 0, 7, 6, 5, 4>(__x._M_data)));
	__x = __binary_op(
	  __x, _Base::template __make_simd<_Tp, _Np>(
		 __vector_permute<7, 6, 5, 4, 3, 2, 1, 0>(__x._M_data)));
	return __x[0];
      }
    else if constexpr (_Np == 4)
      {
	__x = __binary_op(__x, _Base::template __make_simd<_Tp, _Np>(
				 __vector_permute<1, 0, 3, 2>(__x._M_data)));
	__x = __binary_op(__x, _Base::template __make_simd<_Tp, _Np>(
				 __vector_permute<3, 2, 1, 0>(__x._M_data)));
	return __x[0];
      }
    else if constexpr (_Np == 2)
      {
	__x = __binary_op(__x, _Base::template __make_simd<_Tp, _Np>(
				 __vector_permute<1, 0>(__x._M_data)));
	return __x[0];
      }
    else
      return _Base::__reduce(__x, static_cast<_BinaryOperation&&>(__binary_op));
  }

  // }}}
  // math {{{
  // __sqrt {{{
  template <typename _Tp, typename _TVT = _VectorTraits<_Tp>>
  _GLIBCXX_SIMD_INTRINSIC static _Tp __sqrt(_Tp __x)
  {
    if constexpr (__have_neon_a64)
      {
	const auto __intrin = __to_intrin(__x);
	if constexpr (_TVT::template __is<float, 2>)
	  return vsqrt_f32(__intrin);
	else if constexpr (_TVT::template __is<float, 4>)
	  return vsqrtq_f32(__intrin);
	else if constexpr (_TVT::template __is<double, 1>)
	  return vsqrt_f64(__intrin);
	else if constexpr (_TVT::template __is<double, 2>)
	  return vsqrtq_f64(__intrin);
	else
	  __assert_unreachable<_Tp>();
      }
    else
      return _Base::__sqrt(__x);
  } // }}}
  // __trunc {{{
  template <typename _Tp, typename _TVT = _VectorTraits<_Tp>>
  _GLIBCXX_SIMD_INTRINSIC static _Tp __trunc(_Tp __x)
  {
    if constexpr (__have_neon_a32)
      {
	const auto __intrin = __to_intrin(__x);
	if constexpr (_TVT::template __is<float, 2>)
	  return vrnd_f32(__intrin);
	else if constexpr (_TVT::template __is<float, 4>)
	  return vrndq_f32(__intrin);
	else if constexpr (_TVT::template __is<double, 1>)
	  return vrnd_f64(__intrin);
	else if constexpr (_TVT::template __is<double, 2>)
	  return vrndq_f64(__intrin);
	else
	  __assert_unreachable<_Tp>();
      }
    else
      return _Base::__trunc(__x);
  } // }}}
  // __floor {{{
  template <typename _Tp, typename _TVT = _VectorTraits<_Tp>>
  _GLIBCXX_SIMD_INTRINSIC static _Tp __floor(_Tp __x)
  {
    if constexpr (__have_neon_a32)
      {
	const auto __intrin = __to_intrin(__x);
	if constexpr (_TVT::template __is<float, 2>)
	  return vrndm_f32(__intrin);
	else if constexpr (_TVT::template __is<float, 4>)
	  return vrndmq_f32(__intrin);
	else if constexpr (_TVT::template __is<double, 1>)
	  return vrndm_f64(__intrin);
	else if constexpr (_TVT::template __is<double, 2>)
	  return vrndmq_f64(__intrin);
	else
	  __assert_unreachable<_Tp>();
      }
    else
      return _Base::__floor(__x);
  } // }}}
  // __ceil {{{
  template <typename _Tp, typename _TVT = _VectorTraits<_Tp>>
  _GLIBCXX_SIMD_INTRINSIC static _Tp __ceil(_Tp __x)
  {
    if constexpr (__have_neon_a32)
      {
	const auto __intrin = __to_intrin(__x);
	if constexpr (_TVT::template __is<float, 2>)
	  return vrndp_f32(__intrin);
	else if constexpr (_TVT::template __is<float, 4>)
	  return vrndpq_f32(__intrin);
	else if constexpr (_TVT::template __is<double, 1>)
	  return vrndp_f64(__intrin);
	else if constexpr (_TVT::template __is<double, 2>)
	  return vrndpq_f64(__intrin);
	else
	  __assert_unreachable<_Tp>();
      }
    else
      return _Base::__ceil(__x);
  } //}}}
  //}}}
}; // }}}
// _MaskImplNeonMixin {{{
struct _MaskImplNeonMixin {
  using _Base = _MaskImplBuiltinMixin;

  template <typename _Tp, size_t _Np>
  _GLIBCXX_SIMD_INTRINSIC static constexpr _SanitizedBitMask<_Np>
    __to_bits(_SimdWrapper<_Tp, _Np> __x)
  {
    if (__builtin_is_constant_evaluated())
      return _Base::__to_bits(__x);

    using _I = __int_for_sizeof_t<_Tp>;
    if constexpr (sizeof(__x) == 16)
      {
	auto                            __asint = __vector_bitcast<_I>(__x);
#ifdef __aarch64__
	[[maybe_unused]] constexpr auto __zero  = decltype(__asint)();
#else
	[[maybe_unused]] constexpr auto __zero = decltype(__lo64(__asint))();
#endif
	if constexpr (sizeof(_Tp) == 1)
	  {
	    constexpr auto __bitsel =
	      __generate_from_n_evaluations<16, __vector_type_t<_I, 16>>(
		[&](auto __i) {
		  return static_cast<_I>(
		    __i < _Np ? (__i < 8 ? 1 << __i : 1 << (__i - 8)) : 0);
		});
	    __asint &= __bitsel;
#ifdef __aarch64__
	    return __vector_bitcast<_UShort>(vpaddq_s8(
	      vpaddq_s8(vpaddq_s8(__asint, __zero), __zero), __zero))[0];
#else
	    return __vector_bitcast<_UShort>(vpadd_s8(
	      vpadd_s8(vpadd_s8(__lo64(__asint), __hi64(__asint)), __zero),
	      __zero))[0];
#endif
	  }
	else if constexpr (sizeof(_Tp) == 2)
	  {
	    constexpr auto __bitsel =
	      __generate_from_n_evaluations<8, __vector_type_t<_I, 8>>(
		[&](auto __i) {
		  return static_cast<_I>(__i < _Np ? 1 << __i : 0);
		});
	    __asint &= __bitsel;
#ifdef __aarch64__
	    return vpaddq_s16(vpaddq_s16(vpaddq_s16(__asint, __zero), __zero),
			      __zero)[0];
#else
	    return vpadd_s16(
	      vpadd_s16(vpadd_s16(__lo64(__asint), __hi64(__asint)), __zero),
	      __zero)[0];
#endif
	  }
	else if constexpr (sizeof(_Tp) == 4)
	  {
	    constexpr auto __bitsel =
	      __generate_from_n_evaluations<4, __vector_type_t<_I, 4>>(
		[&](auto __i) {
		  return static_cast<_I>(__i < _Np ? 1 << __i : 0);
		});
	    __asint &= __bitsel;
#ifdef __aarch64__
	    return vpaddq_s32(vpaddq_s32(__asint, __zero), __zero)[0];
#else
	    return vpadd_s32(vpadd_s32(__lo64(__asint), __hi64(__asint)),
			     __zero)[0];
#endif
	  }
	else if constexpr (sizeof(_Tp) == 8)
	  {
	    return (__asint[0] & 1) | (__asint[1] & 2);
	  }
	else
	  __assert_unreachable<_Tp>();
      }
    else if constexpr (sizeof(__x) == 8)
      {
	auto                            __asint = __vector_bitcast<_I>(__x);
	[[maybe_unused]] constexpr auto __zero  = decltype(__asint)();
	if constexpr (sizeof(_Tp) == 1)
	  {
	    constexpr auto __bitsel =
	      __generate_from_n_evaluations<8, __vector_type_t<_I, 8>>(
		[&](auto __i) {
		  return static_cast<_I>(__i < _Np ? 1 << __i : 0);
		});
	    __asint &= __bitsel;
	    return vpadd_s8(vpadd_s8(vpadd_s8(__asint, __zero), __zero),
			    __zero)[0];
	  }
	else if constexpr (sizeof(_Tp) == 2)
	  {
	    constexpr auto __bitsel =
	      __generate_from_n_evaluations<4, __vector_type_t<_I, 4>>(
		[&](auto __i) {
		  return static_cast<_I>(__i < _Np ? 1 << __i : 0);
		});
	    __asint &= __bitsel;
	    return vpadd_s16(vpadd_s16(__asint, __zero), __zero)[0];
	  }
	else if constexpr (sizeof(_Tp) == 4)
	  {
	    __asint &= __make_vector<_I>(0x1, 0x2);
	    return vpadd_s32(__asint, __zero)[0];
	  }
	else
	  __assert_unreachable<_Tp>();
      }
    else
      return _Base::__to_bits(__x);
  }
};

// }}}
// _MaskImplNeon {{{
template <typename _Abi>
struct _MaskImplNeon : _MaskImplNeonMixin, _MaskImplBuiltin<_Abi>
{
  using _MaskImplNeonMixin::__to_bits;
  using _Base = _MaskImplBuiltin<_Abi>;

  // __all_of {{{
  template <typename _Tp>
  _GLIBCXX_SIMD_INTRINSIC static bool __all_of(simd_mask<_Tp, _Abi> __k)
  {
    const auto __kk =
      __vector_bitcast<char>(__k._M_data) |
      ~__vector_bitcast<char>(_Abi::template __implicit_mask<_Tp>());
    if constexpr (sizeof(__k) == 16)
      {
	const auto __x = __vector_bitcast<long long>(__kk);
	return __x[0] + __x[1] == -2;
      }
    else if constexpr (sizeof(__k) <= 8)
      return __bit_cast<__int_for_sizeof_t<decltype(__kk)>>(__kk) == -1;
    else
      __assert_unreachable<_Tp>();
  }

  // }}}
  // __any_of {{{
  template <typename _Tp>
  _GLIBCXX_SIMD_INTRINSIC static bool __any_of(simd_mask<_Tp, _Abi> __k)
  {
    const auto __kk =
      __vector_bitcast<char>(__k._M_data) |
      ~__vector_bitcast<char>(_Abi::template __implicit_mask<_Tp>());
    if constexpr (sizeof(__k) == 16)
      {
	const auto __x = __vector_bitcast<long long>(__kk);
	return (__x[0] | __x[1]) != 0;
      }
    else if constexpr (sizeof(__k) <= 8)
      return __bit_cast<__int_for_sizeof_t<decltype(__kk)>>(__kk) != 0;
    else
      __assert_unreachable<_Tp>();
  }

  // }}}
  // __none_of {{{
  template <typename _Tp>
  _GLIBCXX_SIMD_INTRINSIC static bool __none_of(simd_mask<_Tp, _Abi> __k)
  {
    const auto __kk =
      __vector_bitcast<char>(__k._M_data) |
      ~__vector_bitcast<char>(_Abi::template __implicit_mask<_Tp>());
    if constexpr (sizeof(__k) == 16)
      {
	const auto __x = __vector_bitcast<long long>(__kk);
	return (__x[0] | __x[1]) == 0;
      }
    else if constexpr (sizeof(__k) <= 8)
      return __bit_cast<__int_for_sizeof_t<decltype(__kk)>>(__kk) == 0;
    else
      __assert_unreachable<_Tp>();
  }

  // }}}
  // __some_of {{{
  template <typename _Tp>
  _GLIBCXX_SIMD_INTRINSIC static bool __some_of(simd_mask<_Tp, _Abi> __k)
  {
    if constexpr (sizeof(__k) <= 8)
      {
	const auto __kk =
	  __vector_bitcast<char>(__k._M_data) |
	  ~__vector_bitcast<char>(_Abi::template __implicit_mask<_Tp>());
	using _Up = std::make_unsigned_t<__int_for_sizeof_t<decltype(__kk)>>;
	return __bit_cast<_Up>(__kk) + 1 > 1;
      }
    else
      return _Base::__some_of(__k);
  }

  // }}}
  // __popcount {{{
  template <typename _Tp>
  _GLIBCXX_SIMD_INTRINSIC static int __popcount(simd_mask<_Tp, _Abi> __k)
  {
    if constexpr (sizeof(_Tp) == 1)
      {
	const auto __s8  = __vector_bitcast<_SChar>(__k._M_data);
	int8x8_t   __tmp = __lo64(__s8) + __hi64z(__s8);
	return -vpadd_s8(vpadd_s8(vpadd_s8(__tmp, int8x8_t()), int8x8_t()),
			 int8x8_t())[0];
      }
    else if constexpr (sizeof(_Tp) == 2)
      {
	const auto __s16 = __vector_bitcast<short>(__k._M_data);
	int16x4_t  __tmp = __lo64(__s16) + __hi64z(__s16);
	return -vpadd_s16(vpadd_s16(__tmp, int16x4_t()), int16x4_t())[0];
      }
    else if constexpr (sizeof(_Tp) == 4)
      {
	const auto __s32 = __vector_bitcast<int>(__k._M_data);
	int32x2_t  __tmp = __lo64(__s32) + __hi64z(__s32);
	return -vpadd_s32(__tmp, int32x2_t())[0];
      }
    else if constexpr (sizeof(_Tp) == 8)
      {
	static_assert(sizeof(__k) == 16);
	const auto __s64 = __vector_bitcast<long>(__k._M_data);
	return -(__s64[0] + __s64[1]);
      }
  }

  // }}}
  // __find_first_set {{{
  template <typename _Tp>
  _GLIBCXX_SIMD_INTRINSIC static int __find_first_set(simd_mask<_Tp, _Abi> __k)
  {
    // TODO: the _Base implementation is not optimal for NEON
    return _Base::__find_first_set(__k);
  }

  // }}}
  // __find_last_set {{{
  template <typename _Tp>
  _GLIBCXX_SIMD_INTRINSIC static int __find_last_set(simd_mask<_Tp, _Abi> __k)
  {
    // TODO: the _Base implementation is not optimal for NEON
    return _Base::__find_last_set(__k);
  }

  // }}}
}; // }}}

_GLIBCXX_SIMD_END_NAMESPACE
#endif  // __cplusplus >= 201703L
#endif  // _GLIBCXX_EXPERIMENTAL_SIMD_NEON_H_
// vim: foldmethod=marker sw=2 noet ts=8 sts=2 tw=80
