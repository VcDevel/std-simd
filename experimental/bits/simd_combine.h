// Simd _Combine ABI specific implementations -*- C++ -*-

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

#ifndef _GLIBCXX_EXPERIMENTAL_SIMD_COMBINE_H_
#define _GLIBCXX_EXPERIMENTAL_SIMD_COMBINE_H_

#if __cplusplus >= 201703L

_GLIBCXX_SIMD_BEGIN_NAMESPACE

// simd_abi::_Combine {{{
template <int _Np, typename _Abi>
struct simd_abi::_Combine
{
  template <typename _Tp>
  static constexpr size_t size = _Np* _Abi::template size<_Tp>;
  template <typename _Tp>
  static constexpr size_t _S_full_size = size<_Tp>;

  static constexpr int _S_factor = _Np;
  using _MemberAbi               = _Abi;

  // validity traits {{{
  // allow 2x, 3x, and 4x "unroll"
  struct _IsValidAbiTag : conjunction<__bool_constant<(_Np > 1 && _Np <= 4)>,
				      typename _Abi::_IsValidAbiTag>
  {
  };
  template <typename _Tp>
  struct _IsValidSizeFor : _Abi::template _IsValidSizeFor<_Tp>
  {
  };
  template <typename _Tp>
  struct _IsValid
  : conjunction<_IsValidAbiTag, typename _Abi::template _IsValid<_Tp>>
  {
  };
  template <typename _Tp>
  static constexpr bool _S_is_valid_v = _IsValid<_Tp>::value;

  // }}}
  // _SimdImpl/_MaskImpl {{{
  using _SimdImpl = _SimdImplCombine<_Np, _Abi>;
  using _MaskImpl = _MaskImplCombine<_Np, _Abi>;

  // }}}
  // __traits {{{
  template <typename _Tp, bool = _S_is_valid_v<_Tp>>
  struct __traits : _InvalidTraits
  {
  };

  template <typename _Tp>
  struct __traits<_Tp, true>
  {
    using _IsValid  = true_type;
    using _SimdImpl = _SimdImplCombine<_Np, _Abi>;
    using _MaskImpl = _MaskImplCombine<_Np, _Abi>;

    // simd and simd_mask member types {{{
    using _SimdMember =
      std::array<typename _Abi::template __traits<_Tp>::_SimdMember, _Np>;
    using _MaskMember =
      std::array<typename _Abi::template __traits<_Tp>::_MaskMember, _Np>;
    static constexpr size_t _S_simd_align =
      _Abi::template __traits<_Tp>::_S_simd_align;
    static constexpr size_t _S_mask_align =
      _Abi::template __traits<_Tp>::_S_mask_align;

    // }}}
    // _SimdBase / base class for simd, providing extra conversions {{{
    struct _SimdBase
    {
      explicit operator const _SimdMember&() const
      {
	return static_cast<const simd<_Tp, _Combine>*>(this)->_M_data;
      }
    };

    // }}}
    // _MaskBase {{{
    // empty. The std::bitset interface suffices
    struct _MaskBase
    {
      explicit operator const _MaskMember&() const
      {
	return static_cast<const simd_mask<_Tp, _Combine>*>(this)->_M_data;
      }
    };

    // }}}
    // _SimdCastType {{{
    struct _SimdCastType
    {
      _SimdCastType(const _SimdMember& dd)
      : _M_data(dd)
      {
      }
      explicit operator const _SimdMember&() const { return _M_data; }

    private:
      const _SimdMember& _M_data;
    };

    // }}}
    // _MaskCastType {{{
    struct _MaskCastType
    {
      _MaskCastType(const _MaskMember& dd)
      : _M_data(dd)
      {
      }
      explicit operator const _MaskMember&() const { return _M_data; }

    private:
      const _MaskMember& _M_data;
    };
    //}}}
  };
  //}}}
};

// }}}
template <int _Np, typename _Abi>
struct _SimdImplCombine
{
  // member types {{{
  using abi_type = simd_abi::_Combine<_Np, _Abi>;
  template <typename _Tp> using _TypeTag = _Tp *;
  using _PartImpl = typename _Abi::_SimdImpl;
  template <typename _Tp>
  using _SimdMember =
    std::array<typename _Abi::template __traits<_Tp>::_SimdMember, _Np>;

  // }}}
  // broadcast {{{
  template <typename _Tp>
  _GLIBCXX_SIMD_INTRINSIC static constexpr _SimdMember<_Tp>
    __broadcast(_Tp __x) noexcept
  {
    return __generate_from_n_evaluations<_Np, _SimdMember<_Tp>>(
      [&](int) constexpr { return _PartImpl::__broadcast(__x); });
  }

  // }}}
  // load {{{
//X   template <typename _Tp, typename _Up, typename _Fp>
//X   _GLIBCXX_SIMD_INTRINSIC static constexpr _Tp
//X     __load(const _U* __mem, _Fp, _TypeTag<_Tp> __x) noexcept
//X   {
//X     return __generate_from_n_evaluations<_Np, _Tp>(
//X       [&](auto __i) constexpr { return _PartImpl::__load(__mem + __i * __part_size<_Tp>, _Fp{}, __x); });
//X   }
//X 
  // }}}
};
template <int _Np, typename _MemberAbi>
struct _MaskImplCombine
{
  using _Abi            = simd_abi::_Combine<_Np, _MemberAbi>;
  using _MemberMaskImpl = typename _MemberAbi::_MaskImpl;
  template <typename _Tp>
  using _MemberSimdMask = simd_mask<_Tp, _MemberAbi>;

  // __all_of {{{
  template <typename _Tp>
  _GLIBCXX_SIMD_INTRINSIC static bool __all_of(simd_mask<_Tp, _Abi> __k)
  {
    bool __r =
      _MemberMaskImpl::__all_of(_MemberSimdMask<_Tp>(__private_init, __k[0]));
    __execute_n_times<_Np - 1>([&](auto __i) {
      __r = __r && _MemberMaskImpl::__all_of(
		     _MemberSimdMask<_Tp>(__private_init, __k[__i + 1]));
    });
    return __r;
  }

  // }}}
  // __any_of {{{
  template <typename _Tp>
  _GLIBCXX_SIMD_INTRINSIC static bool __any_of(simd_mask<_Tp, _Abi> __k)
  {
    bool __r =
      _MemberMaskImpl::__any_of(_MemberSimdMask<_Tp>(__private_init, __k[0]));
    __execute_n_times<_Np - 1>([&](auto __i) {
      __r = __r || _MemberMaskImpl::__any_of(
		     _MemberSimdMask<_Tp>(__private_init, __k[__i + 1]));
    });
    return __r;
  }

  // }}}
  // __none_of {{{
  template <typename _Tp>
  _GLIBCXX_SIMD_INTRINSIC static bool __none_of(simd_mask<_Tp, _Abi> __k)
  {
    bool __r =
      _MemberMaskImpl::__none_of(_MemberSimdMask<_Tp>(__private_init, __k[0]));
    __execute_n_times<_Np - 1>([&](auto __i) {
      __r = __r && _MemberMaskImpl::__none_of(
		     _MemberSimdMask<_Tp>(__private_init, __k[__i + 1]));
    });
    return __r;
  }

  // }}}
  // __some_of {{{
  template <typename _Tp>
  _GLIBCXX_SIMD_INTRINSIC static bool __some_of(simd_mask<_Tp, _Abi> __k)
  {
    return __any_of(__k) && !__all_of(__k);
  }

  // }}}
  // __popcount {{{
  template <typename _Tp>
  _GLIBCXX_SIMD_INTRINSIC static int __popcount(simd_mask<_Tp, _Abi> __k)
  {
    int __count =
      _MemberMaskImpl::__popcount(_MemberSimdMask<_Tp>(__private_init, __k[0]));
    __execute_n_times<_Np - 1>([&](auto __i) {
      __count += _MemberMaskImpl::__popcount(
	_MemberSimdMask<_Tp>(__private_init, __k[__i + 1]));
    });
    return __count;
  }

  // }}}
  // __find_first_set {{{
  template <typename _Tp>
  _GLIBCXX_SIMD_INTRINSIC static int __find_first_set(simd_mask<_Tp, _Abi> __k)
  {
    for (int __i = 0; __i < _Np - 1; ++__i)
      if (_MemberMaskImpl::__any_of(
	    _MemberSimdMask<_Tp>(__private_init, __k[__i])))
	return __i * simd_size_v<_Tp, _MemberAbi> +
	       _MemberMaskImpl::__find_first_set(
		 _MemberSimdMask<_Tp>(__private_init, __k[__i]));
    return (_Np - 1) * simd_size_v<_Tp, _MemberAbi> +
	   __find_first_set(__k[_Abi::_S_factor - 1]);
  }

  // }}}
  // __find_last_set {{{
  template <typename _Tp>
  _GLIBCXX_SIMD_INTRINSIC static int __find_last_set(simd_mask<_Tp, _Abi> __k)
  {
    // FIXME: I think the order of this one is reversed
    for (int __i = 0; __i < _Np - 1; ++__i)
      if (_MemberMaskImpl::__any_of(
	    _MemberSimdMask<_Tp>(__private_init, __k[__i])))
	return __i * simd_size_v<_Tp, _MemberAbi> +
	       _MemberMaskImpl::__find_last_set(
		 _MemberSimdMask<_Tp>(__private_init, __k[__i]));
    return (_Np - 1) * simd_size_v<_Tp, _MemberAbi> +
	   __find_last_set(__k[_Abi::_S_factor - 1]);
  }

  // }}}
};

_GLIBCXX_SIMD_END_NAMESPACE
#endif  // __cplusplus >= 201703L
#endif  // _GLIBCXX_EXPERIMENTAL_SIMD_COMBINE_H_
// vim: foldmethod=marker sw=2 noet ts=8 sts=2 tw=80
