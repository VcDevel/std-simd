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

template <int _N, typename _Abi>
struct _SimdImplCombine
{
  // member types {{{
  using abi_type = simd_abi::_Combine<_N, _Abi>;
  template <typename _Tp> using _TypeTag = _Tp *;
  using _PartImpl = typename _Abi::_SimdImpl;
  template <typename _Tp>
  using _SimdMember =
    std::array<typename _Abi::template __traits<_Tp>::_SimdMember, _N>;

  // }}}
  // broadcast {{{
  template <typename _Tp>
  _GLIBCXX_SIMD_INTRINSIC static constexpr _SimdMember<_Tp>
    __broadcast(_Tp __x) noexcept
  {
    return __generate_from_n_evaluations<_N, _SimdMember<_Tp>>(
      [&](int) constexpr { return _PartImpl::__broadcast(__x); });
  }

  // }}}
  // load {{{
//X   template <typename _Tp, typename _Up, typename _F>
//X   _GLIBCXX_SIMD_INTRINSIC static constexpr _Tp
//X     __load(const _U* __mem, _F, _TypeTag<_Tp> __x) noexcept
//X   {
//X     return __generate_from_n_evaluations<_N, _Tp>(
//X       [&](auto __i) constexpr { return _PartImpl::__load(__mem + __i * __part_size<_Tp>, _F{}, __x); });
//X   }
//X 
  // }}}
};
template <int _N, typename _Abi>
struct _MaskImplCombine
{
};

_GLIBCXX_SIMD_END_NAMESPACE
#endif  // __cplusplus >= 201703L
#endif  // _GLIBCXX_EXPERIMENTAL_SIMD_COMBINE_H_
// vim: foldmethod=marker sw=2 noet ts=8 sts=2 tw=80
