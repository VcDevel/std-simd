// Generic simd conversions -*- C++ -*-

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

#ifndef _GLIBCXX_EXPERIMENTAL_SIMD_CONVERTER_H_
#define _GLIBCXX_EXPERIMENTAL_SIMD_CONVERTER_H_

#if __cplusplus >= 201703L

_GLIBCXX_SIMD_BEGIN_NAMESPACE
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
#endif  // _GLIBCXX_EXPERIMENTAL_SIMD_CONVERTER_H_
// vim: foldmethod=marker sw=2 noet ts=8 sts=2 tw=80
