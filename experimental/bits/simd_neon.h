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

#include "simd_abis.h"

#if !_GLIBCXX_SIMD_HAVE_NEON
#error "simd_neon.h may only be included when NEON on ARM is available"
#endif

_GLIBCXX_SIMD_BEGIN_NAMESPACE

// _SimdImplNeon {{{
template <int _Bytes>
struct _SimdImplNeon : _SimdImplBuiltin<simd_abi::_VecBuiltinAbi<_Bytes>>
{
  using _Base = _SimdImplBuiltin<simd_abi::_VecBuiltinAbi<_Bytes>>;
  // math {{{
  // __sqrt {{{
  template <typename _Tp, typename _TVT = _VectorTraits<_Tp>>
  _GLIBCXX_SIMD_INTRINSIC static _Tp __sqrt(_Tp __x)
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
      return _Base::__sqrt(__x);
  } // }}}
  // __trunc {{{
  template <typename _Tp, typename _TVT = _VectorTraits<_Tp>>
  _GLIBCXX_SIMD_INTRINSIC static _Tp __trunc(_Tp __x)
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
      return _Base::__trunc(__x);
  } // }}}
  // __floor {{{
  template <typename _Tp, typename _TVT = _VectorTraits<_Tp>>
  _GLIBCXX_SIMD_INTRINSIC static _Tp __floor(_Tp __x)
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
      return _Base::__floor(__x);
  } // }}}
  // __ceil {{{
  template <typename _Tp, typename _TVT = _VectorTraits<_Tp>>
  _GLIBCXX_SIMD_INTRINSIC static _Tp __ceil(_Tp __x)
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
      return _Base::__ceil(__x);
  } //}}}
  //}}}
}; // }}}
// _MaskImplNeon {{{
template <int _Bytes>
struct _MaskImplNeon : _MaskImplBuiltin<simd_abi::_VecBuiltinAbi<_Bytes>>
{
}; // }}}

_GLIBCXX_SIMD_END_NAMESPACE
#endif  // __cplusplus >= 201703L
#endif  // _GLIBCXX_EXPERIMENTAL_SIMD_NEON_H_
// vim: foldmethod=marker sw=2 noet ts=8 sts=2 tw=80
