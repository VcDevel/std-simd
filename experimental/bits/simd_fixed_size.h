// Simd fixed_size ABI specific implementations -*- C++ -*-

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

/*
 * The fixed_size ABI gives the following guarantees:
 *  - simd objects are passed via the stack
 *  - memory layout of `simd<_Tp, _N>` is equivalent to `std::array<_Tp, _N>`
 *  - alignment of `simd<_Tp, _N>` is `_N * sizeof(_Tp)` if _N is __a power-of-2 value,
 *    otherwise `__next_power_of_2(_N * sizeof(_Tp))` (Note: if the alignment were to
 *    exceed the system/compiler maximum, it is bounded to that maximum)
 *  - simd_mask objects are passed like std::bitset<_N>
 *  - memory layout of `simd_mask<_Tp, _N>` is equivalent to `std::bitset<_N>`
 *  - alignment of `simd_mask<_Tp, _N>` is equal to the alignment of `std::bitset<_N>`
 */

#ifndef _GLIBCXX_EXPERIMENTAL_SIMD_FIXED_SIZE_H_
#define _GLIBCXX_EXPERIMENTAL_SIMD_FIXED_SIZE_H_

#if __cplusplus >= 201703L

#include <array>

_GLIBCXX_SIMD_BEGIN_NAMESPACE

// __simd_tuple_element {{{
template <size_t _I, typename _Tp> struct __simd_tuple_element;
template <typename _Tp, typename _A0, typename... _As>
struct __simd_tuple_element<0, _SimdTuple<_Tp, _A0, _As...>> {
    using type = std::experimental::simd<_Tp, _A0>;
};
template <size_t _I, typename _Tp, typename _A0, typename... _As>
struct __simd_tuple_element<_I, _SimdTuple<_Tp, _A0, _As...>> {
    using type = typename __simd_tuple_element<_I - 1, _SimdTuple<_Tp, _As...>>::type;
};
template <size_t _I, typename _Tp>
using __simd_tuple_element_t = typename __simd_tuple_element<_I, _Tp>::type;

// }}}
// __simd_tuple_concat {{{
template <typename _Tp, typename... _A0s, typename... _A1s>
_GLIBCXX_SIMD_INTRINSIC constexpr _SimdTuple<_Tp, _A0s..., _A1s...>
  __simd_tuple_concat(const _SimdTuple<_Tp, _A0s...>& __left,
		      const _SimdTuple<_Tp, _A1s...>& __right)
{
  if constexpr (sizeof...(_A0s) == 0)
    return __right;
  else if constexpr (sizeof...(_A1s) == 0)
    return __left;
  else
    return {__left.first, __simd_tuple_concat(__left.second, __right)};
}

template <typename _Tp, typename _A10, typename... _A1s>
_GLIBCXX_SIMD_INTRINSIC constexpr _SimdTuple<_Tp,
					       simd_abi::scalar,
					       _A10,
					       _A1s...>
  __simd_tuple_concat(const _Tp&                              __left,
		      const _SimdTuple<_Tp, _A10, _A1s...>& __right)
{
  return {__left, __right};
}

// }}}
// __simd_tuple_pop_front {{{
template <size_t _N, typename _Tp>
_GLIBCXX_SIMD_INTRINSIC constexpr decltype(auto)
  __simd_tuple_pop_front(_Tp&& __x)
{
  if constexpr (_N == 0)
    return std::forward<_Tp>(__x);
  else
    return __simd_tuple_pop_front<_N - 1>(__x.second);
}

// }}}
// __get_simd_at<_N> {{{1
struct __as_simd {};
struct __as_simd_tuple {};
template <typename _Tp, typename _A0, typename... _Abis>
_GLIBCXX_SIMD_INTRINSIC constexpr simd<_Tp, _A0> __simd_tuple_get_impl(
    __as_simd, const _SimdTuple<_Tp, _A0, _Abis...> &__t, _SizeConstant<0>)
{
    return {__private_init, __t.first};
}
template <typename _Tp, typename _A0, typename... _Abis>
_GLIBCXX_SIMD_INTRINSIC constexpr const auto &__simd_tuple_get_impl(
    __as_simd_tuple, const _SimdTuple<_Tp, _A0, _Abis...> &__t, _SizeConstant<0>)
{
    return __t.first;
}
template <typename _Tp, typename _A0, typename... _Abis>
_GLIBCXX_SIMD_INTRINSIC constexpr auto &__simd_tuple_get_impl(
    __as_simd_tuple, _SimdTuple<_Tp, _A0, _Abis...> &__t, _SizeConstant<0>)
{
    return __t.first;
}

template <typename _R, size_t _N, typename _Tp, typename... _Abis>
_GLIBCXX_SIMD_INTRINSIC constexpr auto __simd_tuple_get_impl(
    _R, const _SimdTuple<_Tp, _Abis...> &__t, _SizeConstant<_N>)
{
    return __simd_tuple_get_impl(_R(), __t.second, _SizeConstant<_N - 1>());
}
template <size_t _N, typename _Tp, typename... _Abis>
_GLIBCXX_SIMD_INTRINSIC constexpr auto &__simd_tuple_get_impl(
    __as_simd_tuple, _SimdTuple<_Tp, _Abis...> &__t, _SizeConstant<_N>)
{
    return __simd_tuple_get_impl(__as_simd_tuple(), __t.second, _SizeConstant<_N - 1>());
}

template <size_t _N, typename _Tp, typename... _Abis>
_GLIBCXX_SIMD_INTRINSIC constexpr auto __get_simd_at(const _SimdTuple<_Tp, _Abis...> &__t)
{
    return __simd_tuple_get_impl(__as_simd(), __t, _SizeConstant<_N>());
}

// }}}
// __get_tuple_at<_N> {{{
template <size_t _N, typename _Tp, typename... _Abis>
_GLIBCXX_SIMD_INTRINSIC constexpr auto __get_tuple_at(const _SimdTuple<_Tp, _Abis...> &__t)
{
    return __simd_tuple_get_impl(__as_simd_tuple(), __t, _SizeConstant<_N>());
}

template <size_t _N, typename _Tp, typename... _Abis>
_GLIBCXX_SIMD_INTRINSIC constexpr auto &__get_tuple_at(_SimdTuple<_Tp, _Abis...> &__t)
{
    return __simd_tuple_get_impl(__as_simd_tuple(), __t, _SizeConstant<_N>());
}

// __tuple_element_meta {{{1
template <typename _Tp, typename _Abi, size_t _Offset>
struct __tuple_element_meta : public _Abi::_SimdImpl {
  static_assert(is_same_v<typename _Abi::_SimdImpl::abi_type,
			  _Abi>); // this fails e.g. when _SimdImpl is an alias
				  // for _SimdImplBuiltin<_DifferentAbi>
  using value_type                    = _Tp;
  using abi_type                      = _Abi;
  using _Traits                       = _SimdTraits<_Tp, _Abi>;
  using _MaskImpl                     = typename _Abi::_MaskImpl;
  using _MaskMember                   = typename _Traits::_MaskMember;
  using simd_type                     = std::experimental::simd<_Tp, _Abi>;
  static constexpr size_t    _S_offset = _Offset;
  static constexpr size_t    size() { return simd_size<_Tp, _Abi>::value; }
  static constexpr _MaskImpl _S_mask_impl = {};

  template <size_t _N>
  _GLIBCXX_SIMD_INTRINSIC static _MaskMember __make_mask(std::bitset<_N> __bits)
  {
    constexpr _Tp* __type_tag = nullptr;
    return _MaskImpl::__from_bitset(
      std::bitset<size()>((__bits >> _Offset).to_ullong()), __type_tag);
  }

  _GLIBCXX_SIMD_INTRINSIC static _ULLong __mask_to_shifted_ullong(_MaskMember __k)
  {
    return _ULLong(_MaskImpl::__to_bits(__k)) << _Offset;
  }
};

template <size_t _Offset, typename _Tp, typename _Abi, typename... _As>
__tuple_element_meta<_Tp, _Abi, _Offset> __make_meta(const _SimdTuple<_Tp, _Abi, _As...> &)
{
    return {};
}

// }}}1
// _WithOffset wrapper class {{{
template <size_t _Offset, typename _Base>
struct _WithOffset : public _Base
{
  static inline constexpr size_t _S_offset = _Offset;

  _GLIBCXX_SIMD_INTRINSIC char* __as_charptr()
  {
    return reinterpret_cast<char*>(this) +
	   _S_offset * sizeof(typename _Base::value_type);
  }
  _GLIBCXX_SIMD_INTRINSIC const char* __as_charptr() const
  {
    return reinterpret_cast<const char*>(this) +
	   _S_offset * sizeof(typename _Base::value_type);
  }
};

// make _WithOffset<_WithOffset> ill-formed to use:
template <size_t _O0, size_t _O1, typename _Base>
struct _WithOffset<_O0, _WithOffset<_O1, _Base>> {};

template <size_t _Offset, typename _Tp>
decltype(auto) __add_offset(_Tp& __base)
{
  return static_cast<_WithOffset<_Offset, __remove_cvref_t<_Tp>>&>(__base);
}
template <size_t _Offset, typename _Tp>
decltype(auto) __add_offset(const _Tp& __base)
{
  return static_cast<const _WithOffset<_Offset, __remove_cvref_t<_Tp>>&>(
    __base);
}
template <size_t _Offset, size_t _ExistingOffset, typename _Tp>
decltype(auto) __add_offset(_WithOffset<_ExistingOffset, _Tp>& __base)
{
  return static_cast<_WithOffset<_Offset + _ExistingOffset, _Tp>&>(
    static_cast<_Tp&>(__base));
}
template <size_t _Offset, size_t _ExistingOffset, typename _Tp>
decltype(auto) __add_offset(const _WithOffset<_ExistingOffset, _Tp>& __base)
{
  return static_cast<const _WithOffset<_Offset + _ExistingOffset, _Tp>&>(
    static_cast<const _Tp&>(__base));
}

template <typename _Tp>
constexpr inline size_t __offset = 0;
template <size_t _Offset, typename _Tp>
constexpr inline size_t __offset<_WithOffset<_Offset, _Tp>> =
  _WithOffset<_Offset, _Tp>::_S_offset;
template <typename _Tp>
constexpr inline size_t __offset<const _Tp> = __offset<_Tp>;
template <typename _Tp>
constexpr inline size_t __offset<_Tp&> = __offset<_Tp>;
template <typename _Tp>
constexpr inline size_t __offset<_Tp&&> = __offset<_Tp>;

// }}}
// _SimdTuple specializations {{{1
// empty {{{2
template <typename _Tp> struct _SimdTuple<_Tp> {
    using value_type = _Tp;
    static constexpr size_t _S_tuple_size = 0;
    static constexpr size_t size() { return 0; }
};

// _SimdTupleData {{{2
template <typename _FirstType, typename _SecondType>
struct _SimdTupleData
{
  _FirstType  first;
  _SecondType second;
};

template <typename _FirstType, typename _Tp>
struct _SimdTupleData<_FirstType, _SimdTuple<_Tp>>
{
  _FirstType  first;
  static constexpr _SimdTuple<_Tp> second = {};
};

// 1 or more {{{2
template <class _Tp, class _Abi0, class... _Abis>
struct _SimdTuple<_Tp, _Abi0, _Abis...>
: _SimdTupleData<typename _SimdTraits<_Tp, _Abi0>::_SimdMember,
		 _SimdTuple<_Tp, _Abis...>>
{
  using value_type  = _Tp;
  using _FirstType  = typename _SimdTraits<_Tp, _Abi0>::_SimdMember;
  using _FirstAbi   = _Abi0;
  using _SecondType = _SimdTuple<_Tp, _Abis...>;
  static constexpr size_t _S_tuple_size = sizeof...(_Abis) + 1;
  static constexpr size_t size()
  {
    return simd_size_v<_Tp, _Abi0> + _SecondType::size();
  }
  static constexpr size_t _S_first_size = simd_size_v<_Tp, _Abi0>;

  using _Base = _SimdTupleData<typename _SimdTraits<_Tp, _Abi0>::_SimdMember,
			       _SimdTuple<_Tp, _Abis...>>;
  using _Base::first;
  using _Base::second;

  _GLIBCXX_SIMD_INTRINSIC constexpr _SimdTuple() = default;
  _GLIBCXX_SIMD_INTRINSIC constexpr _SimdTuple(const _SimdTuple&) = default;
  _GLIBCXX_SIMD_INTRINSIC constexpr _SimdTuple& operator=(const _SimdTuple&) = default;

  template <typename _Up>
  _GLIBCXX_SIMD_INTRINSIC constexpr _SimdTuple(_Up&& __x)
  : _Base{forward<_Up>(__x)}
  {
  }
  template <typename _Up, typename _Up2>
  _GLIBCXX_SIMD_INTRINSIC constexpr _SimdTuple(_Up&& __x, _Up2&& __y)
  : _Base{forward<_Up>(__x), forward<_Up2>(__y)}
  {
  }
  template <typename _Up>
  _GLIBCXX_SIMD_INTRINSIC constexpr _SimdTuple(_Up&& __x, _SimdTuple<_Tp>)
  : _Base{forward<_Up>(__x)}
  {
  }

  _GLIBCXX_SIMD_INTRINSIC char* __as_charptr()
  {
    return reinterpret_cast<char*>(this);
  }
  _GLIBCXX_SIMD_INTRINSIC const char* __as_charptr() const
  {
    return reinterpret_cast<const char*>(this);
  }

  template <size_t _N>
  auto& __at()
  {
    if constexpr (_N == 0)
      return first;
    else
      return second.template __at<_N - 1>();
  }
  template <size_t _N>
  const auto& __at() const
  {
    if constexpr (_N == 0)
      return first;
    else
      return second.template __at<_N - 1>();
  }

  template <size_t _N>
  auto __simd_at() const
  {
    if constexpr (_N == 0)
      return simd<_Tp, _Abi0>(__private_init, first);
    else
      return second.template __simd_at<_N - 1>();
  }

  template <size_t _Offset = 0, class _F>
  _GLIBCXX_SIMD_INTRINSIC static constexpr _SimdTuple
    __generate(_F&& __gen, _SizeConstant<_Offset> = {})
  {
    auto &&__first = __gen(__tuple_element_meta<_Tp, _Abi0, _Offset>());
    if constexpr (_S_tuple_size == 1)
      return {__first};
    else
      return {__first, _SecondType::__generate(
			 std::forward<_F>(__gen),
			 _SizeConstant<_Offset + simd_size_v<_Tp, _Abi0>>())};
  }

  template <size_t _Offset = 0, class _F, class... _More>
  _GLIBCXX_SIMD_INTRINSIC _SimdTuple
			  __apply_wrapped(_F&& __fun, const _More&... __more) const
  {
    auto&& __first= __fun(__make_meta<_Offset>(*this), first, __more.first...);
    if constexpr (_S_tuple_size == 1)
      return { __first };
    else
      return {
	__first,
	second.template __apply_wrapped<_Offset + simd_size_v<_Tp, _Abi0>>(
	  std::forward<_F>(__fun), __more.second...)};
  }

  template <size_t _Size,
	    size_t _Offset = 0,
	    typename _R    = __fixed_size_storage_t<_Tp, _Size>>
  _GLIBCXX_SIMD_INTRINSIC constexpr _R __extract_tuple_with_size() const
  {
    if constexpr (_Size == _S_first_size && _Offset == 0)
      return {first};
    else if constexpr (_Size > _S_first_size && _Offset == 0 && _S_tuple_size > 1)
      return {
	first,
	second.template __extract_tuple_with_size<_Size - _S_first_size>()};
    else if constexpr (_Size == 1)
      return {operator[](_SizeConstant<_Offset>())};
    else if constexpr (_R::_S_tuple_size == 1)
      {
	static_assert(_Offset % _Size == 0);
	static_assert(_S_first_size % _Size == 0);
	return {typename _R::_FirstType(
	  __private_init,
	  __extract_part<_Offset / _Size, _S_first_size / _Size>(first))};
      }
    else
      __assert_unreachable<_SizeConstant<_Size>>();
  }

  template <typename _Tup>
  _GLIBCXX_SIMD_INTRINSIC constexpr decltype(auto)
    __extract_argument(_Tup&& __tup) const
  {
    using _TupT = typename __remove_cvref_t<_Tup>::value_type;
    if constexpr (is_same_v<_SimdTuple, __remove_cvref_t<_Tup>>)
      return __tup.first;
    else if (__builtin_is_constant_evaluated())
      return __fixed_size_storage_t<_TupT, _S_first_size>::__generate([&](
	auto __meta) constexpr {
	return __meta.__generator(
	  [&](auto __i) constexpr { return __tup[__i]; },
	  static_cast<_TupT*>(nullptr));
      });
    else
      return [&]() {
	__fixed_size_storage_t<_TupT, _S_first_size> __r;
	__builtin_memcpy(__r.__as_charptr(), __tup.__as_charptr(), sizeof(__r));
	return __r;
      }();
  }

  template <typename _Tup>
  _GLIBCXX_SIMD_INTRINSIC constexpr auto& __skip_argument(_Tup&& __tup) const
  {
    static_assert(_S_tuple_size > 1);
    using _U               = __remove_cvref_t<_Tup>;
    constexpr size_t __off = __offset<_U>;
    if constexpr (_S_first_size == _U::_S_first_size && __off == 0)
      return __tup.second;
    else if constexpr (_S_first_size > _U::_S_first_size &&
		       _S_first_size % _U::_S_first_size == 0 && __off == 0)
      return __simd_tuple_pop_front<_S_first_size / _U::_S_first_size>(__tup);
    else if constexpr (_S_first_size + __off < _U::_S_first_size)
      return __add_offset<_S_first_size>(__tup);
    else if constexpr (_S_first_size + __off == _U::_S_first_size)
      return __tup.second;
    else
      __assert_unreachable<_Tup>();
  }

  template <size_t _Offset, typename... _More>
  _GLIBCXX_SIMD_INTRINSIC constexpr void
    __assign_front(const _SimdTuple<_Tp, _Abi0, _More...>& __x) &
  {
    static_assert(_Offset == 0);
    first = __x.first;
    if constexpr (sizeof...(_More) > 0)
      {
	static_assert(sizeof...(_Abis) >= sizeof...(_More));
	second.template __assign_front<0>(__x.second);
      }
  }

  template <size_t _Offset>
  _GLIBCXX_SIMD_INTRINSIC constexpr void
    __assign_front(const _FirstType& __x) &
  {
    static_assert(_Offset == 0);
    first = __x;
  }

  template <size_t _Offset, typename... _As>
  _GLIBCXX_SIMD_INTRINSIC constexpr void
    __assign_front(const _SimdTuple<_Tp, _As...>& __x) &
  {
    __builtin_memcpy(__as_charptr() + _Offset * sizeof(value_type),
		     __x.__as_charptr(),
		     sizeof(_Tp) * _SimdTuple<_Tp, _As...>::size());
  }

  /*
   * Iterate over the first objects in this _SimdTuple and call __fun for each
   * of them. If additional arguments are passed via __more, chunk them into
   * _SimdTuple or __vector_type_t objects of the same number of values.
   */
  template <class _F, class... _More>
  _GLIBCXX_SIMD_INTRINSIC constexpr _SimdTuple
    __apply_per_chunk(_F&& __fun, _More&&... __more) const
  {
    if constexpr ((... || conjunction_v<
			    is_lvalue_reference<_More>,
			    negation<is_const<remove_reference_t<_More>>>>))
      {
	// need to write back at least one of __more after calling __fun
	auto&& __first = [&](auto... __args) constexpr {
	  auto __r =
	    __fun(__tuple_element_meta<_Tp, _Abi0, 0>(), first, __args...);
	  [[maybe_unused]] auto&& __ignore_me = {(
	    [](auto&& __dst, const auto& __src) {
	      if constexpr (is_assignable_v<decltype(__dst), decltype(__dst)>)
		{
		  __dst.template __assign_front<__offset<decltype(__dst)>>(
		    __src);
		}
	    }(std::forward<_More>(__more), __args),
	    0)...};
	  return __r;
	}(__extract_argument(__more)...);
	if constexpr (_S_tuple_size == 1)
	  return { __first };
	else
	  return {__first,
		  second.__apply_per_chunk(std::forward<_F>(__fun),
					   __skip_argument(__more)...)};
      }
    else
      {
	auto&& __first = __fun(__tuple_element_meta<_Tp, _Abi0, 0>(), first,
			       __extract_argument(__more)...);
	if constexpr (_S_tuple_size == 1)
	  return { __first };
	else
	  return {__first,
		  second.__apply_per_chunk(std::forward<_F>(__fun),
					   __skip_argument(__more)...)};
      }
  }

  template <typename _R = _Tp, typename _F, typename... _More>
  _GLIBCXX_SIMD_INTRINSIC auto
    __apply_r(_F&& __fun, const _More&... __more) const
  {
    auto&& __first =
      __fun(__tuple_element_meta<_Tp, _Abi0, 0>(), first, __more.first...);
    if constexpr (_S_tuple_size == 1)
      return __first;
    else
      return __simd_tuple_concat<_R>(
	__first, second.template __apply_r<_R>(std::forward<_F>(__fun),
					       __more.second...));
  }

  template <typename _F, typename... _More>
  _GLIBCXX_SIMD_INTRINSIC friend std::bitset<size()>
    __test(_F&& __fun, const _SimdTuple& __x, const _More&... __more)
  {
    const bitset<size()> __first = _Abi0::_MaskImpl::__to_bits(
      __fun(__tuple_element_meta<_Tp, _Abi0, 0>(), __x.first, __more.first...));
    if constexpr (_S_tuple_size == 1)
      return __first;
    else
      return __first.to_ullong() |
	     (__test(__fun, __x.second, __more.second...).to_ullong()
	      << simd_size_v<_Tp, _Abi0>);
  }

  template <typename _U, _U _I>
  _GLIBCXX_SIMD_INTRINSIC constexpr _Tp
    operator[](std::integral_constant<_U, _I>) const noexcept
  {
    if constexpr (_I < simd_size_v<_Tp, _Abi0>)
      return __subscript_read(_I);
    else
      return second[std::integral_constant<_U, _I - simd_size_v<_Tp, _Abi0>>()];
  }

  _Tp operator[](size_t __i) const noexcept
  {
    if constexpr (_S_tuple_size == 1)
      return __subscript_read(__i);
    else
      {
#ifdef _GLIBCXX_SIMD_USE_ALIASING_LOADS
	return reinterpret_cast<const __may_alias<_Tp>*>(this)[__i];
#else
	if constexpr (__is_scalar_abi<_Abi0>())
	  {
	    const _Tp* ptr = &first;
	    return ptr[__i];
	  }
	else
	  return __i < simd_size_v<_Tp, _Abi0>
		   ? __subscript_read(__i)
		   : second[__i - simd_size_v<_Tp, _Abi0>];
#endif
      }
  }

  void __set(size_t __i, _Tp __val) noexcept
  {
    if constexpr (_S_tuple_size == 1)
      return __subscript_write(__i, __val);
    else
      {
#ifdef _GLIBCXX_SIMD_USE_ALIASING_LOADS
	reinterpret_cast<__may_alias<_Tp>*>(this)[__i] = __val;
#else
	if (__i < simd_size_v<_Tp, _Abi0>)
	  __subscript_write(__i, __val);
	else
	  second.__set(__i - simd_size_v<_Tp, _Abi0>, __val);
#endif
      }
  }

private:
  // __subscript_read/_write {{{
  _Tp __subscript_read([[maybe_unused]] size_t __i) const noexcept
  {
    if constexpr (__is_vectorizable_v<_FirstType>)
      return first;
    else
      return first[__i];
  }

  void __subscript_write([[maybe_unused]] size_t __i, _Tp __y) noexcept
  {
    if constexpr (__is_vectorizable_v<_FirstType>)
      first = __y;
    else
      first.__set(__i, __y);
  }

  // }}}
};

// __make_simd_tuple {{{1
template <typename _Tp, typename _A0>
_GLIBCXX_SIMD_INTRINSIC _SimdTuple<_Tp, _A0> __make_simd_tuple(
    std::experimental::simd<_Tp, _A0> __x0)
{
    return {__data(__x0)};
}
template <typename _Tp, typename _A0, typename... _As>
_GLIBCXX_SIMD_INTRINSIC _SimdTuple<_Tp, _A0, _As...> __make_simd_tuple(
    const std::experimental::simd<_Tp, _A0> &__x0,
    const std::experimental::simd<_Tp, _As> &... __xs)
{
    return {__data(__x0), __make_simd_tuple(__xs...)};
}

template <typename _Tp, typename _A0>
_GLIBCXX_SIMD_INTRINSIC _SimdTuple<_Tp, _A0> __make_simd_tuple(
    const typename _SimdTraits<_Tp, _A0>::_SimdMember &__arg0)
{
    return {__arg0};
}

template <typename _Tp, typename _A0, typename _A1, typename... _Abis>
_GLIBCXX_SIMD_INTRINSIC _SimdTuple<_Tp, _A0, _A1, _Abis...> __make_simd_tuple(
    const typename _SimdTraits<_Tp, _A0>::_SimdMember &__arg0,
    const typename _SimdTraits<_Tp, _A1>::_SimdMember &__arg1,
    const typename _SimdTraits<_Tp, _Abis>::_SimdMember &... __args)
{
    return {__arg0, __make_simd_tuple<_Tp, _A1, _Abis...>(__arg1, __args...)};
}

// __to_simd_tuple {{{1
template <typename _Tp,
	  size_t _N,
	  typename _V,
	  size_t _NV,
	  typename... _VX>
_GLIBCXX_SIMD_INTRINSIC constexpr __fixed_size_storage_t<_Tp, _N>
  __to_simd_tuple(const std::array<_V, _NV>& __from, const _VX... __fromX);

template <typename _Tp,
	  size_t _N,
	  size_t _Offset = 0, // skip this many elements in __from0
	  typename _R    = __fixed_size_storage_t<_Tp, _N>,
	  typename _V0,
	  typename _V0VT = _VectorTraits<_V0>,
	  typename... _VX>
_GLIBCXX_SIMD_INTRINSIC
  _R constexpr __to_simd_tuple(const _V0 __from0, const _VX... __fromX)
{
  static_assert(std::is_same_v<typename _V0VT::value_type, _Tp>);
  static_assert(_Offset < _V0VT::_S_width);
  using _R0 = __vector_type_t<_Tp, _R::_S_first_size>;
  if constexpr (_R::_S_tuple_size == 1)
    {
      if constexpr (_N == 1)
	return _R{__from0[_Offset]};
      else if constexpr (_Offset == 0 && _V0VT::_S_width >= _N)
	return _R{__intrin_bitcast<_R0>(__from0)};
      else if constexpr (_Offset * 2 == _V0VT::_S_width &&
			 _V0VT::_S_width / 2 >= _N)
	return _R{__intrin_bitcast<_R0>(__extract_part<1, 2>(__from0))};
      else if constexpr (_Offset * 4 == _V0VT::_S_width &&
			 _V0VT::_S_width / 4 >= _N)
	return _R{__intrin_bitcast<_R0>(__extract_part<1, 4>(__from0))};
      else
	__assert_unreachable<_Tp>();
    }
  else
    {
      if constexpr (1 == _R::_S_first_size)
	{ // extract one scalar and recurse
	  if constexpr (_Offset + 1 < _V0VT::_S_width)
	    return _R{
	      __from0[_Offset],
	      __to_simd_tuple<_Tp, _N - 1, _Offset + 1>(__from0, __fromX...)};
	  else
	    return _R{__from0[_Offset],
		      __to_simd_tuple<_Tp, _N - 1, 0>(__fromX...)};
	}

      // place __from0 into _R::first and recurse for __fromX -> _R::second
      else if constexpr (_V0VT::_S_width == _R::_S_first_size && _Offset == 0)
	return _R{__from0,
		  __to_simd_tuple<_Tp, _N - _R::_S_first_size>(__fromX...)};

      // place lower part of __from0 into _R::first and recurse with _Offset
      else if constexpr (_V0VT::_S_width > _R::_S_first_size && _Offset == 0)
	return _R{
	  __intrin_bitcast<_R0>(__from0),
	  __to_simd_tuple<_Tp, _N - _R::_S_first_size, _R::_S_first_size>(
	    __from0, __fromX...)};

      // place lower part of second quarter of __from0 into _R::first and recurse
      // with _Offset
      else if constexpr (_Offset * 4 == _V0VT::_S_width &&
			 _V0VT::_S_width >= 4 * _R::_S_first_size)
	return _R{
	  __intrin_bitcast<_R0>(__extract_part<2, 4>(__from0)),
	  __to_simd_tuple<_Tp, _N - _R::_S_first_size,
			  _Offset + _R::_S_first_size>(__from0, __fromX...)};

      // place lower half of high half of __from0 into _R::first and recurse
      // with _Offset
      else if constexpr (_Offset * 2 == _V0VT::_S_width &&
			 _V0VT::_S_width >= 4 * _R::_S_first_size)
	return _R{__intrin_bitcast<_R0>(__extract_part<2, 4>(__from0)),
	  __to_simd_tuple<_Tp, _N - _R::_S_first_size,
			  _Offset + _R::_S_first_size>(__from0, __fromX...)};

      // place high half of __from0 into _R::first and recurse with __fromX
      else if constexpr (_Offset * 2 == _V0VT::_S_width &&
			 _V0VT::_S_width / 2 >= _R::_S_first_size)
	return _R{__intrin_bitcast<_R0>(__extract_part<1, 2>(__from0)),
		  __to_simd_tuple<_Tp, _N - _R::_S_first_size, 0>(__fromX...)};

      // ill-formed if some unforseen pattern is needed
      else
	__assert_unreachable<_Tp>();
    }
}

template <typename _Tp,
	  size_t _N,
	  typename _V,
	  size_t _NV,
	  typename... _VX>
_GLIBCXX_SIMD_INTRINSIC constexpr __fixed_size_storage_t<_Tp, _N>
  __to_simd_tuple(const std::array<_V, _NV>& __from, const _VX... __fromX)
{
  if constexpr (std::is_same_v<_Tp, _V>)
    {
      static_assert(
	sizeof...(_VX) == 0,
	"An array of scalars must be the last argument to __to_simd_tuple");
      return __call_with_subscripts(
	__from,
	std::make_index_sequence<_NV>(), [&](const auto... __args) constexpr {
	  return __simd_tuple_concat(
	    _SimdTuple<_Tp, simd_abi::scalar>{__args}..., _SimdTuple<_Tp>());
	});
    }
  else
  return __call_with_subscripts(
    __from,
    std::make_index_sequence<_NV>(), [&](const auto... __args) constexpr {
      return __to_simd_tuple<_Tp, _N>(__args..., __fromX...);
    });
}

template <size_t, typename _Tp> using __to_tuple_helper = _Tp;
template <typename _Tp,
	  typename _A0,
	  size_t _NOut,
	  size_t _N,
	  size_t... _Indexes>
_GLIBCXX_SIMD_INTRINSIC __fixed_size_storage_t<_Tp, _NOut> __to_simd_tuple_impl(
  std::index_sequence<_Indexes...>,
  const std::array<__vector_type_t<_Tp, simd_size_v<_Tp, _A0>>, _N>& __args)
{
  return __make_simd_tuple<_Tp, __to_tuple_helper<_Indexes, _A0>...>(__args[_Indexes]...);
}

template <typename _Tp,
	  typename _A0,
	  size_t _NOut,
	  size_t _N,
	  typename _R = __fixed_size_storage_t<_Tp, _NOut>>
_GLIBCXX_SIMD_INTRINSIC _R __to_simd_tuple_sized(
  const std::array<__vector_type_t<_Tp, simd_size_v<_Tp, _A0>>, _N>& __args)
{
  static_assert(_N * simd_size_v<_Tp, _A0> >= _NOut);
  return __to_simd_tuple_impl<_Tp, _A0, _NOut>(
    std::make_index_sequence<_R::_S_tuple_size>(), __args);
}

template <typename _Tp, typename _A0, size_t _N>
[[deprecated]] _GLIBCXX_SIMD_INTRINSIC auto __to_simd_tuple(
  const std::array<__vector_type_t<_Tp, simd_size_v<_Tp, _A0>>, _N>& __args)
{
  return __to_simd_tuple<_Tp, _N * simd_size_v<_Tp, _A0>>(__args);
}

// __optimize_simd_tuple {{{1
template <class _Tp> _GLIBCXX_SIMD_INTRINSIC _SimdTuple<_Tp> __optimize_simd_tuple(const _SimdTuple<_Tp>)
{
    return {};
}

template <class _Tp, class _A>
_GLIBCXX_SIMD_INTRINSIC const _SimdTuple<_Tp, _A> &__optimize_simd_tuple(const _SimdTuple<_Tp, _A> &__x)
{
    return __x;
}

template <class _Tp, class _A0, class _A1, class... _Abis,
          class _R = __fixed_size_storage_t<_Tp, _SimdTuple<_Tp, _A0, _A1, _Abis...>::size()>>
_GLIBCXX_SIMD_INTRINSIC _R __optimize_simd_tuple(const _SimdTuple<_Tp, _A0, _A1, _Abis...> &__x)
{
    using _Tup = _SimdTuple<_Tp, _A0, _A1, _Abis...>;
    if constexpr (std::is_same_v<_R, _Tup>)
      return __x;
    else if constexpr (is_same_v<typename _R::_FirstType,
				 typename _Tup::_FirstType>)
      return {__x.first, __optimize_simd_tuple(__x.second)};
    else if constexpr (__is_scalar_abi<_A0>()) // implies all entries are scalar
      return {
	__generate_from_n_evaluations<_R::_S_first_size,
				      typename _R::_FirstType>(
	  [&](auto __i) { return __x[__i]; }),
	__optimize_simd_tuple(__simd_tuple_pop_front<_R::_S_first_size>(__x))};
    else if constexpr (_R::_S_first_size ==
			 simd_size_v<_Tp, _A0> + simd_size_v<_Tp, _A1> &&
		       is_same_v<_A0, _A1>)
      return {__concat(__x.template __at<0>(), __x.template __at<1>()),
	      __optimize_simd_tuple(__x.second.second)};
    else if constexpr (sizeof...(_Abis) >= 2 &&
		       _R::_S_first_size == 4 * simd_size_v<_Tp, _A0> &&
		       simd_size_v<_Tp, _A0> ==
			 __simd_tuple_element_t<(sizeof...(_Abis) >= 2 ? 3 : 0),
						_Tup>::size())
      return {
	__concat(__concat(__x.template __at<0>(), __x.template __at<1>()),
		 __concat(__x.template __at<2>(), __x.template __at<3>())),
	__optimize_simd_tuple(__x.second.second.second.second)};
    else
      {
	_R __r;
	__builtin_memcpy(__r.__as_charptr(), __x.__as_charptr(),
			 sizeof(_Tp) * _R::size());
	return __r;
      }
}

// __for_each(const _SimdTuple &, Fun) {{{1
template <size_t _Offset = 0, class _Tp, class _A0, class _F>
_GLIBCXX_SIMD_INTRINSIC constexpr void
  __for_each(const _SimdTuple<_Tp, _A0>& __t, _F&& __fun)
{
  std::forward<_F>(__fun)(__make_meta<_Offset>(__t), __t.first);
}
template <size_t _Offset = 0,
	  class _Tp,
	  class _A0,
	  class _A1,
	  class... _As,
	  class _F>
_GLIBCXX_SIMD_INTRINSIC constexpr void
  __for_each(const _SimdTuple<_Tp, _A0, _A1, _As...>& __t, _F&& __fun)
{
  __fun(__make_meta<_Offset>(__t), __t.first);
  __for_each<_Offset + simd_size<_Tp, _A0>::value>(__t.second,
						   std::forward<_F>(__fun));
}

// __for_each(_SimdTuple &, Fun) {{{1
template <size_t _Offset = 0, class _Tp, class _A0, class _F>
_GLIBCXX_SIMD_INTRINSIC constexpr void
  __for_each(_SimdTuple<_Tp, _A0>& __t, _F&& __fun)
{
  std::forward<_F>(__fun)(__make_meta<_Offset>(__t), __t.first);
}
template <size_t _Offset = 0,
	  class _Tp,
	  class _A0,
	  class _A1,
	  class... _As,
	  class _F>
_GLIBCXX_SIMD_INTRINSIC constexpr void
  __for_each(_SimdTuple<_Tp, _A0, _A1, _As...>& __t, _F&& __fun)
{
  __fun(__make_meta<_Offset>(__t), __t.first);
  __for_each<_Offset + simd_size<_Tp, _A0>::value>(__t.second,
						   std::forward<_F>(__fun));
}

// __for_each(_SimdTuple &, const _SimdTuple &, Fun) {{{1
template <size_t _Offset = 0, class _Tp, class _A0, class _F>
_GLIBCXX_SIMD_INTRINSIC constexpr void
  __for_each(_SimdTuple<_Tp, _A0>&       __a,
	     const _SimdTuple<_Tp, _A0>& __b,
	     _F&&                          __fun)
{
  std::forward<_F>(__fun)(__make_meta<_Offset>(__a), __a.first, __b.first);
}
template <size_t _Offset = 0,
	  class _Tp,
	  class _A0,
	  class _A1,
	  class... _As,
	  class _F>
_GLIBCXX_SIMD_INTRINSIC constexpr void
  __for_each(_SimdTuple<_Tp, _A0, _A1, _As...>&       __a,
	     const _SimdTuple<_Tp, _A0, _A1, _As...>& __b,
	     _F&&                                      __fun)
{
  __fun(__make_meta<_Offset>(__a), __a.first, __b.first);
  __for_each<_Offset + simd_size<_Tp, _A0>::value>(__a.second, __b.second,
						   std::forward<_F>(__fun));
}

// __for_each(const _SimdTuple &, const _SimdTuple &, Fun) {{{1
template <size_t _Offset = 0, class _Tp, class _A0, class _F>
_GLIBCXX_SIMD_INTRINSIC constexpr void
  __for_each(const _SimdTuple<_Tp, _A0>& __a,
	     const _SimdTuple<_Tp, _A0>& __b,
	     _F&&                          __fun)
{
  std::forward<_F>(__fun)(__make_meta<_Offset>(__a), __a.first, __b.first);
}
template <size_t _Offset = 0,
	  class _Tp,
	  class _A0,
	  class _A1,
	  class... _As,
	  class _F>
_GLIBCXX_SIMD_INTRINSIC constexpr void
  __for_each(const _SimdTuple<_Tp, _A0, _A1, _As...>& __a,
	     const _SimdTuple<_Tp, _A0, _A1, _As...>& __b,
	     _F&&                                      __fun)
{
  __fun(__make_meta<_Offset>(__a), __a.first, __b.first);
  __for_each<_Offset + simd_size<_Tp, _A0>::value>(__a.second, __b.second,
						   std::forward<_F>(__fun));
}

// }}}1
// __extract_part(_SimdTuple) {{{
template <int _Index,
	  int _Total,
	  int _Combine,
	  typename _Tp,
	  typename _A0,
	  typename... _As>
_GLIBCXX_SIMD_INTRINSIC auto // __vector_type_t or _SimdTuple
  __extract_part(const _SimdTuple<_Tp, _A0, _As...>& __x)
{
  // worst cases:
  // (a) 4, 4, 4 => 3, 3, 3, 3 (_Total = 4)
  // (b) 2, 2, 2 => 3, 3       (_Total = 2)
  // (c) 4, 2 => 2, 2, 2       (_Total = 3)
  using _Tuple = _SimdTuple<_Tp, _A0, _As...>;
  static_assert(_Index + _Combine <= _Total && _Index >= 0 && _Total >= 1);
  constexpr size_t _N = _Tuple::size();
  static_assert(_N >= _Total && _N % _Total == 0);
  constexpr size_t __values_per_part = _N / _Total;
  [[maybe_unused]] constexpr size_t __values_to_skip = _Index * __values_per_part;
  constexpr size_t __return_size = __values_per_part * _Combine;
  using _RetAbi = simd_abi::deduce_t<_Tp, __return_size>;

  // handle (optimize) the simple cases
  if constexpr (_Index == 0 && _Tuple::_S_first_size == __return_size)
    return __x.first._M_data;
  else if constexpr (_Index == 0 && _Total == _Combine)
    return __x;
  else if constexpr (_Index == 0 && _Tuple::_S_first_size >= __return_size)
    return __intrin_bitcast<__vector_type_t<_Tp, __return_size>>(
      __as_vector(__x.first));

  // recurse to skip unused data members at the beginning of _SimdTuple
  else if constexpr (__values_to_skip >= _Tuple::_S_first_size)
    { // recurse
      if constexpr (_Tuple::_S_first_size % __values_per_part == 0)
	{
	  constexpr int __parts_in_first =
	    _Tuple::_S_first_size / __values_per_part;
	  return __extract_part<_Index - __parts_in_first,
				_Total - __parts_in_first, _Combine>(
	    __x.second);
	}
      else
	return __extract_part<__values_to_skip - _Tuple::_S_first_size,
			      _N - _Tuple::_S_first_size, __return_size>(
	  __x.second);
    }

  // extract from multiple _SimdTuple data members
  else if constexpr (__return_size > _Tuple::_S_first_size - __values_to_skip)
    {
#ifdef _GLIBCXX_SIMD_USE_ALIASING_LOADS
      const __may_alias<_Tp>* const element_ptr =
	reinterpret_cast<const __may_alias<_Tp>*>(&__x) + __values_to_skip;
      return __as_vector(simd<_Tp, _RetAbi>(element_ptr, element_aligned));
#else
      [[maybe_unused]] constexpr size_t __offset = __values_to_skip;
      return __as_vector(simd<_Tp, _RetAbi>([&](auto __i) constexpr {
	constexpr _SizeConstant<__i + __offset> __k;
	return __x[__k];
      }));
#endif
    }

  // all of the return values are in __x.first
  else if constexpr (_Tuple::_S_first_size % __values_per_part == 0)
    return __extract_part<_Index, _Tuple::_S_first_size / __values_per_part,
			  _Combine>(__x.first);
  else
    return __extract_part<__values_to_skip, _Tuple::_S_first_size,
			  _Combine * __values_per_part>(__x.first);
}

// }}}
// __fixed_size_storage_t<_Tp, _N>{{{
template <class _Tp, int _N, class _Tuple,
          class _Next = simd<_Tp, _AllNativeAbis::_BestAbi<_Tp, _N>>,
          int _Remain = _N - int(_Next::size())>
struct __fixed_size_storage_builder;

template <class _Tp, int _N>
struct __fixed_size_storage
    : public __fixed_size_storage_builder<_Tp, _N, _SimdTuple<_Tp>> {
};

template <class _Tp, int _N, class... _As, class _Next>
struct __fixed_size_storage_builder<_Tp, _N, _SimdTuple<_Tp, _As...>, _Next, 0> {
    using type = _SimdTuple<_Tp, _As..., typename _Next::abi_type>;
};

template <class _Tp, int _N, class... _As, class _Next, int _Remain>
struct __fixed_size_storage_builder<_Tp, _N, _SimdTuple<_Tp, _As...>, _Next, _Remain> {
    using type = typename __fixed_size_storage_builder<
        _Tp, _Remain, _SimdTuple<_Tp, _As..., typename _Next::abi_type>>::type;
};

// }}}
// _AbisInSimdTuple {{{
template <class _Tp> struct _SeqOp;
template <size_t _I0, size_t... _Is> struct _SeqOp<std::index_sequence<_I0, _Is...>> {
    using _FirstPlusOne = std::index_sequence<_I0 + 1, _Is...>;
    using _NotFirstPlusOne = std::index_sequence<_I0, (_Is + 1)...>;
    template <size_t _First, size_t _Add>
    using _Prepend = std::index_sequence<_First, _I0 + _Add, (_Is + _Add)...>;
};

template <class _Tp> struct _AbisInSimdTuple;
template <class _Tp> struct _AbisInSimdTuple<_SimdTuple<_Tp>> {
    using _Counts = std::index_sequence<0>;
    using _Begins = std::index_sequence<0>;
};
template <class _Tp, class _A> struct _AbisInSimdTuple<_SimdTuple<_Tp, _A>> {
    using _Counts = std::index_sequence<1>;
    using _Begins = std::index_sequence<0>;
};
template <class _Tp, class _A0, class... _As>
struct _AbisInSimdTuple<_SimdTuple<_Tp, _A0, _A0, _As...>> {
    using _Counts = typename _SeqOp<typename _AbisInSimdTuple<
        _SimdTuple<_Tp, _A0, _As...>>::_Counts>::_FirstPlusOne;
    using _Begins = typename _SeqOp<typename _AbisInSimdTuple<
        _SimdTuple<_Tp, _A0, _As...>>::_Begins>::_NotFirstPlusOne;
};
template <class _Tp, class _A0, class _A1, class... _As>
struct _AbisInSimdTuple<_SimdTuple<_Tp, _A0, _A1, _As...>> {
    using _Counts = typename _SeqOp<typename _AbisInSimdTuple<
        _SimdTuple<_Tp, _A1, _As...>>::_Counts>::template _Prepend<1, 0>;
    using _Begins = typename _SeqOp<typename _AbisInSimdTuple<
        _SimdTuple<_Tp, _A1, _As...>>::_Begins>::template _Prepend<0, 1>;
};

// }}}
// __binary_tree_reduce {{{
template <size_t _Count,
	  size_t _Begin,
	  class _Tp,
	  class... _As,
	  class _BinaryOperation>
auto __binary_tree_reduce(const _SimdTuple<_Tp, _As...>& __tup,
			  const _BinaryOperation&        __binary_op) noexcept
{
  static_assert(_Count > 0);
  if constexpr (_Count == 1)
    return __get_simd_at<_Begin>(__tup);
  else if constexpr (_Count == 2)
    return __binary_op(__get_simd_at<_Begin>(__tup),
		       __get_simd_at<_Begin + 1>(__tup));
  else
    {
      constexpr size_t __left  = __next_power_of_2(_Count) / 2;
      constexpr size_t __right = _Count - __left;
      return __binary_op(
	__binary_tree_reduce<__left, _Begin>(__tup, __binary_op),
	__binary_tree_reduce<__right, _Begin + __left>(__tup, __binary_op));
    }
}

// }}}
// __vec_to_scalar_reduction {{{
// This helper function implements the second step in a generic fixed_size reduction.
// -  Input: a tuple of native simd (or scalar) objects of decreasing size.
// - Output: a scalar (the reduction).
// - Approach:
//   1. reduce the first two tuple elements
//      a) If the number of elements differs by a factor of 2, split the first object into
//         two objects of the second type and reduce all three to one object of second
//         type.
//      b) If the number of elements differs by a factor of 4, split the first object into
//         two equally sized objects, reduce, and split to two objects of the second type.
//         Finally, reduce all three remaining objects to one object of second type.
//      c) Otherwise use std::experimental::reduce to reduce both inputs to a scalar, and binary_op to
//         reduce to a single scalar.
//
//      (This optimizes all native cases on x86, e.g. <AVX512, SSE, Scalar>.)
//
//   2. Concate the result of (1) with the remaining tuple elements to recurse into
//      __vec_to_scalar_reduction.
//
//   3. If __vec_to_scalar_reduction is called with a one-element tuple, call std::experimental::reduce to
//      reduce to a scalar and return.
template <class _Tp, class _A0, class _BinaryOperation>
_GLIBCXX_SIMD_INTRINSIC _Tp __vec_to_scalar_reduction(
  const _SimdTuple<_Tp, _A0>& __tup, const _BinaryOperation& __binary_op)
{
    return std::experimental::reduce(simd<_Tp, _A0>(__private_init, __tup.first), __binary_op);
}

template <class _Tp, class _A0, class _A1, class... _As, class _BinaryOperation>
_GLIBCXX_SIMD_INTRINSIC _Tp
			__vec_to_scalar_reduction(const _SimdTuple<_Tp, _A0, _A1, _As...>& __tup,
						  const _BinaryOperation& __binary_op)
{
  using _Simd0 = simd<_Tp, _A0>;
  using _Simd1 = simd<_Tp, _A1>;
  static_assert(_Simd0::size() != _Simd1::size());

  const _Simd0 __left(__private_init, __tup.first);
  [[maybe_unused]] const _Simd1 __right(__private_init, __tup.second.first);
  if constexpr (sizeof(_Simd0) == sizeof(_Simd1) && _A1::_S_is_partial &&
		std::is_same_v<_BinaryOperation, std::plus<>>)
    return reduce(
      __binary_op(__left, _Simd0(__private_init,
				 _A1::__masked(__tup.second.first._M_data))),
      __binary_op);
  else if constexpr (sizeof(_Simd0) == sizeof(_Simd1) && _A1::_S_is_partial &&
		std::is_same_v<_BinaryOperation, std::multiplies<>>)
    return reduce(
      __binary_op(
	__left,
	_Simd0(
	  __private_init,
	  __blend(_A1::template __implicit_mask<_Tp>(),
		  __vector_broadcast<_A1::template _S_full_size<_Tp>>(_Tp(1)),
		  __tup.second.first._M_data))),
      __binary_op);
  else if constexpr (_Simd0::size() == 2 * _Simd1::size() && !_A1::_S_is_partial)
    {
      const auto [__l0, __l1] = split<_Simd1>(__left);
      const _Simd1 __reduced  = __binary_op(__binary_op(__l0, __right), __l1);
      return __vec_to_scalar_reduction(
	__simd_tuple_concat(__make_simd_tuple(__reduced), __tup.second.second),
	__binary_op);
    }
  else if constexpr (_Simd0::size() == 4 * _Simd1::size() && !_A1::_S_is_partial)
    {
      using _SimdIntermed = __deduced_simd<_Tp, _Simd0::size() / 2>;
      const auto [__l0, __l1] = split<_SimdIntermed>(__left);
      const auto [__m0, __m1] = split<_Simd1>(__binary_op(__l0, __l1));
      const _Simd1 __reduced  = __binary_op(__binary_op(__m0, __right), __m1);
      return __vec_to_scalar_reduction(
	__simd_tuple_concat(__make_simd_tuple(__reduced), __tup.second.second),
	__binary_op);
    }
  else // use reduction via scalar
    return __binary_op(
      simd<_Tp, simd_abi::scalar>(reduce(__left, __binary_op)),
      simd<_Tp, simd_abi::scalar>(reduce(__right, __binary_op)))[0];
}

// }}}
// __autocvt_to_simd {{{
template <class _Tp, bool = std::is_arithmetic_v<__remove_cvref_t<_Tp>>>
struct __autocvt_to_simd {
    _Tp _M_data;
    using _TT = __remove_cvref_t<_Tp>;
    operator _TT() { return _M_data; }
    operator _TT &()
    {
        static_assert(std::is_lvalue_reference<_Tp>::value, "");
        static_assert(!std::is_const<_Tp>::value, "");
        return _M_data;
    }
    operator _TT *()
    {
        static_assert(std::is_lvalue_reference<_Tp>::value, "");
        static_assert(!std::is_const<_Tp>::value, "");
        return &_M_data;
    }

    constexpr inline __autocvt_to_simd(_Tp dd) : _M_data(dd) {}

    template <class _Abi> operator simd<typename _TT::value_type, _Abi>()
    {
        return {__private_init, _M_data};
    }

    template <class _Abi> operator simd<typename _TT::value_type, _Abi> &()
    {
        return *reinterpret_cast<simd<typename _TT::value_type, _Abi> *>(&_M_data);
    }

    template <class _Abi> operator simd<typename _TT::value_type, _Abi> *()
    {
        return reinterpret_cast<simd<typename _TT::value_type, _Abi> *>(&_M_data);
    }
};
template <class _Tp> __autocvt_to_simd(_Tp &&)->__autocvt_to_simd<_Tp>;

template <class _Tp> struct __autocvt_to_simd<_Tp, true> {
    using _TT = __remove_cvref_t<_Tp>;
    _Tp _M_data;
    fixed_size_simd<_TT, 1> _M_fd;

    constexpr inline __autocvt_to_simd(_Tp dd) : _M_data(dd), _M_fd(_M_data) {}
    ~__autocvt_to_simd()
    {
        _M_data = __data(_M_fd).first;
    }

    operator fixed_size_simd<_TT, 1>()
    {
        return _M_fd;
    }
    operator fixed_size_simd<_TT, 1> &()
    {
        static_assert(std::is_lvalue_reference<_Tp>::value, "");
        static_assert(!std::is_const<_Tp>::value, "");
        return _M_fd;
    }
    operator fixed_size_simd<_TT, 1> *()
    {
        static_assert(std::is_lvalue_reference<_Tp>::value, "");
        static_assert(!std::is_const<_Tp>::value, "");
        return &_M_fd;
    }
};

// }}}

// _SimdImplFixedSize {{{1
// fixed_size should not inherit from _SimdMathFallback in order for
// specializations in the used _SimdTuple Abis to get used
template <int _N> struct _SimdImplFixedSize {
    // member types {{{2
    using _MaskMember = std::bitset<_N>;
    template <class _Tp> using _SimdMember = __fixed_size_storage_t<_Tp, _N>;
    template <class _Tp>
    static constexpr std::size_t _S_tuple_size = _SimdMember<_Tp>::_S_tuple_size;
    template <class _Tp> using _Simd = std::experimental::simd<_Tp, simd_abi::fixed_size<_N>>;
    template <class _Tp> using _TypeTag = _Tp *;

    // broadcast {{{2
    template <class _Tp> static constexpr inline _SimdMember<_Tp> __broadcast(_Tp __x) noexcept
    {
        return _SimdMember<_Tp>::__generate(
            [&](auto __meta) constexpr { return __meta.__broadcast(__x); });
    }

    // __generator {{{2
    template <class _F, class _Tp>
    static constexpr inline _SimdMember<_Tp>
      __generator(_F&& __gen, _TypeTag<_Tp>)
    {
      return _SimdMember<_Tp>::__generate([&__gen](auto __meta) constexpr {
	return __meta.__generator(
	  [&](auto __i) constexpr {
	    return __i < _N ? __gen(_SizeConstant<__meta._S_offset + __i>()) : 0;
	  },
	  _TypeTag<_Tp>());
      });
    }

    // __load {{{2
    template <class _Tp, class _U, class _F>
    static inline _SimdMember<_Tp>
      __load(const _U* __mem, _F __f, _TypeTag<_Tp>) noexcept
    {
        return _SimdMember<_Tp>::__generate(
            [&](auto __meta) { return __meta.__load(&__mem[__meta._S_offset], __f, _TypeTag<_Tp>()); });
    }

    // __masked_load {{{2
    template <class _Tp, class... _As, class _U, class _F>
    static inline _SimdTuple<_Tp, _As...>
      __masked_load(const _SimdTuple<_Tp, _As...>& __old,
		    const _MaskMember              __bits,
		    const _U*                      __mem,
		    _F                             __f) noexcept
    {
      auto __merge = __old;
      __for_each(__merge, [&](auto __meta, auto& __native) {
	__native = __meta.__masked_load(__native, __meta.__make_mask(__bits),
				  &__mem[__meta._S_offset], __f);
      });
      return __merge;
    }

    // __store {{{2
    template <class _Tp, class _U, class _F>
    static inline void __store(const _SimdMember<_Tp>& __v,
			       _U*                     __mem,
			       _F                      __f,
			       _TypeTag<_Tp>) noexcept
    {
      __for_each(__v, [&](auto __meta, auto __native) {
	__meta.__store(__native, &__mem[__meta._S_offset], __f, _TypeTag<_Tp>());
      });
    }

    // __masked_store {{{2
    template <class _Tp, class... _As, class _U, class _F>
    static inline void __masked_store(const _SimdTuple<_Tp, _As...>& __v,
				      _U*                            __mem,
				      _F                             __f,
				      const _MaskMember __bits) noexcept
    {
      __for_each(__v, [&](auto __meta, auto __native) {
	__meta.__masked_store(__native, &__mem[__meta._S_offset], __f,
			  __meta.__make_mask(__bits));
      });
    }

    // negation {{{2
    template <class _Tp, class... _As>
    static inline _MaskMember
      __negate(const _SimdTuple<_Tp, _As...>& __x) noexcept
    {
        _MaskMember __bits = 0;
        __for_each(__x, [&__bits](auto __meta, auto __native) constexpr {
            __bits |= __meta.__mask_to_shifted_ullong(__meta.__negate(__native));
        });
        return __bits;
    }

    // reductions {{{2
private:
    template <class _Tp, class... _As, class _BinaryOperation, size_t... _Counts,
              size_t... _Begins>
    static inline _Tp __reduce(const _SimdTuple<_Tp, _As...> &__tup,
                           const _BinaryOperation &__binary_op,
                           std::index_sequence<_Counts...>, std::index_sequence<_Begins...>)
    {
      // 1. reduce all tuple elements with equal ABI to a single element in the
      // output tuple
      const auto __reduced_vec = __make_simd_tuple(
	__binary_tree_reduce<_Counts, _Begins>(__tup, __binary_op)...);
      // 2. split and reduce until a scalar results
      return __vec_to_scalar_reduction(__reduced_vec, __binary_op);
    }

public:
    template <class _Tp, class _BinaryOperation>
    static inline _Tp __reduce(const _Simd<_Tp> &__x, const _BinaryOperation &__binary_op)
    {
        using _Ranges = _AbisInSimdTuple<_SimdMember<_Tp>>;
        return _SimdImplFixedSize::__reduce(__x._M_data, __binary_op,
                                              typename _Ranges::_Counts(),
                                              typename _Ranges::_Begins());
    }

    // __min, __max {{{2
    template <typename _Tp, typename... _As>
    static inline constexpr _SimdTuple<_Tp, _As...>
      __min(const _SimdTuple<_Tp, _As...>& __a,
	  const _SimdTuple<_Tp, _As...>& __b)
    {
      return __a.__apply_per_chunk(
	[](auto __impl, auto __aa, auto __bb) constexpr {
	  return __impl.__min(__aa, __bb);
	},
	__b);
    }

    template <typename _Tp, typename... _As>
    static inline constexpr _SimdTuple<_Tp, _As...>
      __max(const _SimdTuple<_Tp, _As...>& __a,
	  const _SimdTuple<_Tp, _As...>& __b)
    {
      return __a.__apply_per_chunk(
	[](auto __impl, auto __aa, auto __bb) constexpr {
	  return __impl.__max(__aa, __bb);
	},
	__b);
    }

    // __complement {{{2
    template <typename _Tp, typename... _As>
    static inline constexpr _SimdTuple<_Tp, _As...>
      __complement(const _SimdTuple<_Tp, _As...>& __x) noexcept
    {
      return __x.__apply_per_chunk([](auto __impl, auto __xx) constexpr {
	return __impl.__complement(__xx);
      });
    }

    // __unary_minus {{{2
    template <typename _Tp, typename... _As>
    static inline constexpr _SimdTuple<_Tp, _As...>
      __unary_minus(const _SimdTuple<_Tp, _As...>& __x) noexcept
    {
      return __x.__apply_per_chunk([](auto __impl, auto __xx) constexpr {
	return __impl.__unary_minus(__xx);
      });
    }

    // arithmetic operators {{{2

#define _GLIBCXX_SIMD_FIXED_OP(name_, op_)                                     \
  template <typename _Tp, typename... _As>                                     \
  static inline constexpr _SimdTuple<_Tp, _As...> name_(                       \
    const _SimdTuple<_Tp, _As...> __x, const _SimdTuple<_Tp, _As...> __y)      \
  {                                                                            \
    return __x.__apply_per_chunk(                                              \
      [](auto __impl, auto __xx, auto __yy) constexpr {                        \
	return __impl.name_(__xx, __yy);                                       \
      },                                                                       \
      __y);                                                                    \
  }

    _GLIBCXX_SIMD_FIXED_OP(__plus, +)
    _GLIBCXX_SIMD_FIXED_OP(__minus, -)
    _GLIBCXX_SIMD_FIXED_OP(__multiplies, *)
    _GLIBCXX_SIMD_FIXED_OP(__divides, /)
    _GLIBCXX_SIMD_FIXED_OP(__modulus, %)
    _GLIBCXX_SIMD_FIXED_OP(__bit_and, &)
    _GLIBCXX_SIMD_FIXED_OP(__bit_or, |)
    _GLIBCXX_SIMD_FIXED_OP(__bit_xor, ^)
    _GLIBCXX_SIMD_FIXED_OP(__bit_shift_left, <<)
    _GLIBCXX_SIMD_FIXED_OP(__bit_shift_right, >>)
#undef _GLIBCXX_SIMD_FIXED_OP

    template <typename _Tp, typename... _As>
    static inline constexpr _SimdTuple<_Tp, _As...>
      __bit_shift_left(const _SimdTuple<_Tp, _As...>& __x, int __y)
    {
      return __x.__apply_per_chunk([__y](auto __impl, auto __xx) constexpr {
	return __impl.__bit_shift_left(__xx, __y);
      });
    }

    template <typename _Tp, typename... _As>
    static inline constexpr _SimdTuple<_Tp, _As...>
      __bit_shift_right(const _SimdTuple<_Tp, _As...>& __x, int __y)
    {
      return __x.__apply_per_chunk([__y](auto __impl, auto __xx) constexpr {
	return __impl.__bit_shift_right(__xx, __y);
      });
    }

    // math {{{2
#define _GLIBCXX_SIMD_APPLY_ON_TUPLE(_RetTp, __name)                           \
  template <typename _Tp, typename... _As, typename... _More>                  \
  static inline __fixed_size_storage_t<_RetTp,                                 \
				       _SimdTuple<_Tp, _As...>::size()>        \
    __##__name(const _SimdTuple<_Tp, _As...>& __x, const _More&... __more)     \
  {                                                                            \
    if constexpr (sizeof...(_More) == 0)                                       \
      {                                                                        \
	if constexpr (is_same_v<_Tp, _RetTp>)                                  \
	  return __x.__apply_per_chunk([](auto __impl, auto __xx) constexpr {  \
	    using _V = typename decltype(__impl)::simd_type;                   \
	    return __data(__name(_V(__private_init, __xx)));                   \
	  });                                                                  \
	else                                                                   \
	  return __optimize_simd_tuple(__x.template __apply_r<_RetTp>(         \
	    [](auto __impl, auto __xx) { return __impl.__##__name(__xx); }));  \
      }                                                                        \
    else if constexpr (is_same_v<_Tp, _RetTp> &&                               \
		       (... &&                                                 \
			std::is_same_v<_SimdTuple<_Tp, _As...>, _More>))       \
      return __x.__apply_per_chunk(                                            \
	[](auto __impl, auto __xx, auto... __pack) constexpr {                 \
	  using _V = typename decltype(__impl)::simd_type;                     \
	  return __data(                                                       \
	    __name(_V(__private_init, __xx), _V(__private_init, __pack)...));  \
	},                                                                     \
	__more...);                                                            \
    else if constexpr (is_same_v<_Tp, _RetTp>)                                 \
      return __x.__apply_per_chunk(                                            \
	[](auto __impl, auto __xx, auto... __pack) constexpr {                 \
	  using _V = typename decltype(__impl)::simd_type;                     \
	  return __data(                                                       \
	    __name(_V(__private_init, __xx), __autocvt_to_simd(__pack)...));   \
	},                                                                     \
	__more...);                                                            \
    else                                                                       \
      __assert_unreachable<_Tp>();                                             \
  }
    _GLIBCXX_SIMD_APPLY_ON_TUPLE(_Tp, acos)
    _GLIBCXX_SIMD_APPLY_ON_TUPLE(_Tp, asin)
    _GLIBCXX_SIMD_APPLY_ON_TUPLE(_Tp, atan)
    _GLIBCXX_SIMD_APPLY_ON_TUPLE(_Tp, atan2)
    _GLIBCXX_SIMD_APPLY_ON_TUPLE(_Tp, cos)
    _GLIBCXX_SIMD_APPLY_ON_TUPLE(_Tp, sin)
    _GLIBCXX_SIMD_APPLY_ON_TUPLE(_Tp, tan)
    _GLIBCXX_SIMD_APPLY_ON_TUPLE(_Tp, acosh)
    _GLIBCXX_SIMD_APPLY_ON_TUPLE(_Tp, asinh)
    _GLIBCXX_SIMD_APPLY_ON_TUPLE(_Tp, atanh)
    _GLIBCXX_SIMD_APPLY_ON_TUPLE(_Tp, cosh)
    _GLIBCXX_SIMD_APPLY_ON_TUPLE(_Tp, sinh)
    _GLIBCXX_SIMD_APPLY_ON_TUPLE(_Tp, tanh)
    _GLIBCXX_SIMD_APPLY_ON_TUPLE(_Tp, exp)
    _GLIBCXX_SIMD_APPLY_ON_TUPLE(_Tp, exp2)
    _GLIBCXX_SIMD_APPLY_ON_TUPLE(_Tp, expm1)
    _GLIBCXX_SIMD_APPLY_ON_TUPLE(int, ilogb)
    _GLIBCXX_SIMD_APPLY_ON_TUPLE(_Tp, log)
    _GLIBCXX_SIMD_APPLY_ON_TUPLE(_Tp, log10)
    _GLIBCXX_SIMD_APPLY_ON_TUPLE(_Tp, log1p)
    _GLIBCXX_SIMD_APPLY_ON_TUPLE(_Tp, log2)
    _GLIBCXX_SIMD_APPLY_ON_TUPLE(_Tp, logb)
    //modf implemented in simd_math.h
    _GLIBCXX_SIMD_APPLY_ON_TUPLE(_Tp, scalbn) //double scalbn(double x, int exp);
    _GLIBCXX_SIMD_APPLY_ON_TUPLE(_Tp, scalbln)
    _GLIBCXX_SIMD_APPLY_ON_TUPLE(_Tp, cbrt)
    _GLIBCXX_SIMD_APPLY_ON_TUPLE(_Tp, abs)
    _GLIBCXX_SIMD_APPLY_ON_TUPLE(_Tp, fabs)
    _GLIBCXX_SIMD_APPLY_ON_TUPLE(_Tp, pow)
    _GLIBCXX_SIMD_APPLY_ON_TUPLE(_Tp, sqrt)
    _GLIBCXX_SIMD_APPLY_ON_TUPLE(_Tp, erf)
    _GLIBCXX_SIMD_APPLY_ON_TUPLE(_Tp, erfc)
    _GLIBCXX_SIMD_APPLY_ON_TUPLE(_Tp, lgamma)
    _GLIBCXX_SIMD_APPLY_ON_TUPLE(_Tp, tgamma)
    _GLIBCXX_SIMD_APPLY_ON_TUPLE(_Tp, trunc)
    _GLIBCXX_SIMD_APPLY_ON_TUPLE(_Tp, ceil)
    _GLIBCXX_SIMD_APPLY_ON_TUPLE(_Tp, floor)
    _GLIBCXX_SIMD_APPLY_ON_TUPLE(_Tp, nearbyint)

    _GLIBCXX_SIMD_APPLY_ON_TUPLE(_Tp, rint)
    _GLIBCXX_SIMD_APPLY_ON_TUPLE(long, lrint)
    _GLIBCXX_SIMD_APPLY_ON_TUPLE(long long, llrint)

    _GLIBCXX_SIMD_APPLY_ON_TUPLE(_Tp, round)
    _GLIBCXX_SIMD_APPLY_ON_TUPLE(long, lround)
    _GLIBCXX_SIMD_APPLY_ON_TUPLE(long long, llround)

    _GLIBCXX_SIMD_APPLY_ON_TUPLE(_Tp, ldexp)
    _GLIBCXX_SIMD_APPLY_ON_TUPLE(_Tp, fmod)
    _GLIBCXX_SIMD_APPLY_ON_TUPLE(_Tp, remainder)
    // copysign in simd_math.h
    _GLIBCXX_SIMD_APPLY_ON_TUPLE(_Tp, nextafter)
    _GLIBCXX_SIMD_APPLY_ON_TUPLE(_Tp, fdim)
    _GLIBCXX_SIMD_APPLY_ON_TUPLE(_Tp, fmax)
    _GLIBCXX_SIMD_APPLY_ON_TUPLE(_Tp, fmin)
    _GLIBCXX_SIMD_APPLY_ON_TUPLE(_Tp, fma)
    _GLIBCXX_SIMD_APPLY_ON_TUPLE(int, fpclassify)
#undef _GLIBCXX_SIMD_APPLY_ON_TUPLE

    template <typename _Tp, typename... _Abis>
    static _SimdTuple<_Tp, _Abis...> __remquo(
      const _SimdTuple<_Tp, _Abis...>&                                __x,
      const _SimdTuple<_Tp, _Abis...>&                                __y,
      __fixed_size_storage_t<int, _SimdTuple<_Tp, _Abis...>::size()>* __z)
    {
      return __x.__apply_per_chunk(
	[](auto __impl, const auto __xx, const auto __yy, auto& __zz) {
	  return __impl.__remquo(__xx, __yy, &__zz);
	},
	__y, *__z);
    }

    template <typename _Tp, typename... _As>
    static inline _SimdTuple<_Tp, _As...>
      __frexp(const _SimdTuple<_Tp, _As...>&   __x,
	      __fixed_size_storage_t<int, _N>& __exp) noexcept
    {
      return __x.__apply_per_chunk(
	[](auto __impl, const auto& __a, auto& __b) {
	  return __data(
	    frexp(typename decltype(__impl)::simd_type(__private_init, __a),
		  __autocvt_to_simd(__b)));
	},
	__exp);
    }

    template <typename _Tp, typename... _As>
    static inline __fixed_size_storage_t<int, _N>
      __fpclassify(const _SimdTuple<_Tp, _As...>& __x) noexcept
    {
      return __optimize_simd_tuple(__x.template __apply_r<int>(
	[](auto __impl, auto __xx) { return __impl.__fpclassify(__xx); }));
    }

#define _GLIBCXX_SIMD_TEST_ON_TUPLE_(name_)                                    \
  template <typename _Tp, typename... _As>                                     \
  static inline _MaskMember __##name_(                                   \
    const _SimdTuple<_Tp, _As...>& __x) noexcept                             \
  {                                                                            \
    return __test([](auto __impl, auto __xx) { return __impl.__##name_(__xx); }, \
		__x);                                                          \
  }
    _GLIBCXX_SIMD_TEST_ON_TUPLE_(isinf)
    _GLIBCXX_SIMD_TEST_ON_TUPLE_(isfinite)
    _GLIBCXX_SIMD_TEST_ON_TUPLE_(isnan)
    _GLIBCXX_SIMD_TEST_ON_TUPLE_(isnormal)
    _GLIBCXX_SIMD_TEST_ON_TUPLE_(signbit)
#undef _GLIBCXX_SIMD_TEST_ON_TUPLE_

    // __increment & __decrement{{{2
    template <typename... _Ts>
    _GLIBCXX_SIMD_INTRINSIC static constexpr void
      __increment(_SimdTuple<_Ts...>& __x)
    {
      __for_each(
	__x, [](auto __meta, auto& native) constexpr {
	  __meta.__increment(native);
	});
    }

    template <typename... _Ts>
    _GLIBCXX_SIMD_INTRINSIC static constexpr void
      __decrement(_SimdTuple<_Ts...>& __x)
    {
      __for_each(
	__x, [](auto __meta, auto& native) constexpr {
	  __meta.__decrement(native);
	});
    }

    // compares {{{2
#define _GLIBCXX_SIMD_CMP_OPERATIONS(__cmp)                                    \
  template <typename _Tp, typename... _As>                                     \
  _GLIBCXX_SIMD_INTRINSIC static _MaskMember __cmp(                            \
    const _SimdTuple<_Tp, _As...>& __x, const _SimdTuple<_Tp, _As...>& __y)    \
  {                                                                            \
    return __test([](auto __impl, auto __xx,                                   \
		     auto __yy) { return __impl.__cmp(__xx, __yy); },          \
		  __x, __y);                                                   \
  }
    _GLIBCXX_SIMD_CMP_OPERATIONS(__equal_to)
    _GLIBCXX_SIMD_CMP_OPERATIONS(__not_equal_to)
    _GLIBCXX_SIMD_CMP_OPERATIONS(__less)
    _GLIBCXX_SIMD_CMP_OPERATIONS(__less_equal)
    _GLIBCXX_SIMD_CMP_OPERATIONS(__isless)
    _GLIBCXX_SIMD_CMP_OPERATIONS(__islessequal)
    _GLIBCXX_SIMD_CMP_OPERATIONS(__isgreater)
    _GLIBCXX_SIMD_CMP_OPERATIONS(__isgreaterequal)
    _GLIBCXX_SIMD_CMP_OPERATIONS(__islessgreater)
    _GLIBCXX_SIMD_CMP_OPERATIONS(__isunordered)
#undef _GLIBCXX_SIMD_CMP_OPERATIONS

    // smart_reference access {{{2
    template <typename _Tp, typename... _As, typename _U>
    _GLIBCXX_SIMD_INTRINSIC static void __set(_SimdTuple<_Tp, _As...> &__v, int __i, _U &&__x) noexcept
    {
        __v.__set(__i, std::forward<_U>(__x));
    }

    // __masked_assign {{{2
    template <typename _Tp, typename... _As>
    _GLIBCXX_SIMD_INTRINSIC static void
      __masked_assign(const _MaskMember                __bits,
		    _SimdTuple<_Tp, _As...>&             __lhs,
		    const __id<_SimdTuple<_Tp, _As...>>& __rhs)
    {
      __for_each(__lhs, __rhs,
		 [&](auto __meta, auto& __native_lhs, auto __native_rhs) constexpr {
		   __meta.__masked_assign(__meta.__make_mask(__bits), __native_lhs,
					__native_rhs);
		 });
    }

    // Optimization for the case where the RHS is a scalar. No need to broadcast the
    // scalar to a simd first.
    template <typename _Tp, typename... _As>
    _GLIBCXX_SIMD_INTRINSIC static void
      __masked_assign(const _MaskMember    __bits,
		    _SimdTuple<_Tp, _As...>& __lhs,
		    const __id<_Tp>            __rhs)
    {
      __for_each(__lhs, [&](auto __meta, auto& __native_lhs) constexpr {
	__meta.__masked_assign(__meta.__make_mask(__bits), __native_lhs, __rhs);
      });
    }

    // __masked_cassign {{{2
    template <typename _Op, typename _Tp, typename... _As>
    static inline void __masked_cassign(const _MaskMember              __bits,
					_SimdTuple<_Tp, _As...>&       __lhs,
					const _SimdTuple<_Tp, _As...>& __rhs,
					_Op                            __op)
    {
      __for_each(
	__lhs, __rhs,
	[&](auto __meta, auto& __native_lhs, auto __native_rhs) constexpr {
	  __meta.template __masked_cassign(__meta.__make_mask(__bits),
					   __native_lhs, __native_rhs, __op);
	});
    }

    // Optimization for the case where the RHS is a scalar. No need to broadcast
    // the scalar to a simd first.
    template <typename _Op, typename _Tp, typename... _As>
    static inline void __masked_cassign(const _MaskMember        __bits,
					_SimdTuple<_Tp, _As...>& __lhs,
					const _Tp&               __rhs,
					_Op                      __op)
    {
      __for_each(
	__lhs, [&](auto __meta, auto& __native_lhs) constexpr {
	  __meta.template __masked_cassign(__meta.__make_mask(__bits),
					   __native_lhs, __rhs, __op);
	});
    }

    // __masked_unary {{{2
    template <template <typename> class _Op, typename _Tp, typename... _As>
    static inline _SimdTuple<_Tp, _As...>
      __masked_unary(const _MaskMember         __bits,
		   const _SimdTuple<_Tp, _As...> __v) // TODO: const-ref __v?
    {
      return __v.__apply_wrapped([&__bits](auto __meta, auto __native) constexpr {
	return __meta.template __masked_unary<_Op>(__meta.__make_mask(__bits),
						 __native);
      });
    }

    // }}}2
};

// _MaskImplFixedSize {{{1
template <int _N> struct _MaskImplFixedSize {
  static_assert(sizeof(_ULLong) * CHAR_BIT >= _N,
		"The fixed_size implementation relies on one "
		"_ULLong being able to store all boolean "
		"elements."); // required in load & store

  // member types {{{
  using _MaskMember = std::bitset<_N>;
  template <typename _Tp>
  using _TypeTag = _Tp*;

  // }}}
  // __to_bits {{{
  _GLIBCXX_SIMD_INTRINSIC static constexpr auto
    __to_bits(std::bitset<_N> __x)
  {
    if constexpr (_N <= sizeof(long) * CHAR_BIT)
      return __x.to_ulong();
    else
      return __x.to_ullong();
  }

  // }}}
  // __convert {{{
  template <typename _Tp, typename _Up, typename _UAbi>
  _GLIBCXX_SIMD_INTRINSIC static constexpr _MaskMember
    __convert(simd_mask<_Up, _UAbi> __x)
  {
    return _UAbi::_MaskImpl::__to_bits(__data(__x));
  }

  // }}}
    // __from_bitset {{{2
    template <typename _Tp>
    _GLIBCXX_SIMD_INTRINSIC static _MaskMember __from_bitset(const _MaskMember &__bs,
                                                     _TypeTag<_Tp>) noexcept
    {
        return __bs;
    }

    // __load {{{2
    template <typename _F> static inline _MaskMember __load(const bool *__mem, _F __f) noexcept
    {
        // TODO: _UChar is not necessarily the best type to use here. For smaller _N _UShort,
        // _UInt, _ULLong, float, and double can be more efficient.
        _ULLong __r = 0;
        using _Vs = __fixed_size_storage_t<_UChar, _N>;
        __for_each(_Vs{}, [&](auto __meta, auto) {
            __r |= __meta.__mask_to_shifted_ullong(
                __meta._S_mask_impl.__load(&__mem[__meta._S_offset], __f, _SizeConstant<__meta.size()>()));
        });
        return __r;
    }

    // __masked_load {{{2
    template <typename _F>
    static inline _MaskMember __masked_load(_MaskMember __merge,
                                               _MaskMember __mask, const bool *__mem,
                                               _F) noexcept
    {
      _BitOps::__bit_iteration(__mask.to_ullong(),
			       [&](auto __i) { __merge[__i] = __mem[__i]; });
      return __merge;
    }

    // __store {{{2
    template <typename _F>
    static inline void __store(_MaskMember __bs, bool *__mem, _F) noexcept
    {
#if _GLIBCXX_SIMD_X86INTRIN // {{{
      if constexpr (__have_avx512bw)
	{
	  const __m512i bool64 =
	    _mm512_movm_epi8(__bs.to_ullong()) & 0x0101010101010101ULL;
	  __vector_store<_N>(bool64, __mem, _F());
	}
      else if constexpr (__have_bmi2)
	{
#ifdef __x86_64__
	  __execute_n_times<_N / 8>([&](auto __i) {
	    constexpr size_t __offset = __i * 8;
	    const _ULLong    bool8 =
	      _pdep_u64(__bs.to_ullong() >> __offset, 0x0101010101010101ULL);
	    std::memcpy(&__mem[__offset], &bool8, 8);
	  });
	  if (_N % 8 > 0)
	    {
	      constexpr size_t __offset = (_N / 8) * 8;
	      const _ULLong    bool8 =
		_pdep_u64(__bs.to_ullong() >> __offset, 0x0101010101010101ULL);
	      std::memcpy(&__mem[__offset], &bool8, _N % 8);
	    }
#else  // __x86_64__
	  __execute_n_times<_N / 4>([&](auto __i) {
	    constexpr size_t __offset = __i * 4;
	    const _ULLong __bool4 =
	      _pdep_u32(__bs.to_ullong() >> __offset, 0x01010101U);
	    std::memcpy(&__mem[__offset], &__bool4, 4);
	  });
	  if (_N % 4 > 0)
	    {
	      constexpr size_t __offset = (_N / 4) * 4;
	      const _ULLong __bool4 =
		_pdep_u32(__bs.to_ullong() >> __offset, 0x01010101U);
	      std::memcpy(&__mem[__offset], &__bool4, _N % 4);
	    }
#endif // __x86_64__
	}
      else if constexpr (__have_sse2)
	{ // !AVX512BW && !BMI2
	  using _V       = simd<_UChar, simd_abi::__sse>;
	  _ULLong __bits = __bs.to_ullong();
	  __execute_n_times<(_N + 15) / 16>([&](auto __i) {
	    constexpr size_t __offset    = __i * 16;
	    constexpr size_t __remaining = _N - __offset;
	    if constexpr (__remaining == 1)
	      {
		__mem[__offset] = static_cast<bool>(__bits >> __offset);
	      }
	    else if constexpr (__remaining <= 4)
	      {
		const _UInt __bool4 =
		  ((__bits >> __offset) * 0x00204081U) & 0x01010101U;
		std::memcpy(&__mem[__offset], &__bool4, __remaining);
	      }
	    else if constexpr (__remaining <= 7)
	      {
		const _ULLong bool8 =
		  ((__bits >> __offset) * 0x40810204081ULL) &
		  0x0101010101010101ULL;
		std::memcpy(&__mem[__offset], &bool8, __remaining);
	      }
	    else if constexpr (__have_sse2)
	      {
		auto __tmp = _mm_cvtsi32_si128(__bits >> __offset);
		__tmp      = _mm_unpacklo_epi8(__tmp, __tmp);
		__tmp      = _mm_unpacklo_epi16(__tmp, __tmp);
		__tmp      = _mm_unpacklo_epi32(__tmp, __tmp);
		_V __tmp2(__tmp);
		__tmp2 &= _V([](auto __j) {
		  return static_cast<_UChar>(1 << (__j % CHAR_BIT));
		}); // mask bit index
		const __m128i __bool16 = __intrin_bitcast<__m128i>(
		  __vector_bitcast<_UChar>(__data(__tmp2 == 0)) +
		  1); // 0xff -> 0x00 | 0x00 -> 0x01
		if constexpr (__remaining >= 16)
		  {
		    __vector_store<16>(__bool16, &__mem[__offset], _F());
		  }
		else if constexpr (__remaining & 3)
		  {
		    constexpr int to_shift = 16 - int(__remaining);
		    _mm_maskmoveu_si128(
		      __bool16, _mm_srli_si128(~__m128i(), to_shift),
		      reinterpret_cast<char*>(&__mem[__offset]));
		  }
		else // at this point: 8 < __remaining < 16
		  if constexpr (__remaining >= 8)
		  {
		    __vector_store<8>(__bool16, &__mem[__offset], _F());
		    if constexpr (__remaining == 12)
		      {
			__vector_store<4>(
			  _mm_unpackhi_epi64(__bool16, __bool16),
			  &__mem[__offset + 8], _F());
		      }
		  }
	      }
	    else
	      __assert_unreachable<_F>();
	  });
	}
      else
#endif // _GLIBCXX_SIMD_X86INTRIN }}}
	{
	  // TODO: _UChar is not necessarily the best type to use here. For
	  // smaller _N _UShort, _UInt, _ULLong, float, and double can be more
	  // efficient.
	  using _Vs = __fixed_size_storage_t<_UChar, _N>;
	  __for_each(_Vs{}, [&](auto __meta, auto) {
	    __meta._S_mask_impl.__store(__meta.__make_mask(__bs),
					&__mem[__meta._S_offset], _F());
	  });
	  //__execute_n_times<_N>([&](auto __i) { __mem[__i] = __bs[__i]; });
	}
    }

    // __masked_store {{{2
    template <typename _F>
    static inline void __masked_store(const _MaskMember __v, bool *__mem, _F,
                                    const _MaskMember __k) noexcept
    {
      _BitOps::__bit_iteration(__k, [&](auto __i) { __mem[__i] = __v[__i]; });
    }

    // logical and bitwise operators {{{2
    _GLIBCXX_SIMD_INTRINSIC static _MaskMember __logical_and(const _MaskMember &__x,
                                                     const _MaskMember &__y) noexcept
    {
        return __x & __y;
    }

    _GLIBCXX_SIMD_INTRINSIC static _MaskMember __logical_or(const _MaskMember &__x,
                                                    const _MaskMember &__y) noexcept
    {
        return __x | __y;
    }

    _GLIBCXX_SIMD_INTRINSIC static constexpr _MaskMember
      __bit_not(const _MaskMember& __x) noexcept
    {
      return ~__x;
    }

    _GLIBCXX_SIMD_INTRINSIC static _MaskMember __bit_and(const _MaskMember &__x,
                                                 const _MaskMember &__y) noexcept
    {
        return __x & __y;
    }

    _GLIBCXX_SIMD_INTRINSIC static _MaskMember __bit_or(const _MaskMember &__x,
                                                const _MaskMember &__y) noexcept
    {
        return __x | __y;
    }

    _GLIBCXX_SIMD_INTRINSIC static _MaskMember __bit_xor(const _MaskMember &__x,
                                                 const _MaskMember &__y) noexcept
    {
        return __x ^ __y;
    }

    // smart_reference access {{{2
    _GLIBCXX_SIMD_INTRINSIC static void __set(_MaskMember &__k, int __i, bool __x) noexcept
    {
        __k.set(__i, __x);
    }

    // __masked_assign {{{2
    _GLIBCXX_SIMD_INTRINSIC static void __masked_assign(const _MaskMember __k,
                                           _MaskMember &__lhs,
                                           const _MaskMember __rhs)
    {
        __lhs = (__lhs & ~__k) | (__rhs & __k);
    }

    // Optimization for the case where the RHS is a scalar.
    _GLIBCXX_SIMD_INTRINSIC static void __masked_assign(const _MaskMember __k,
                                           _MaskMember &__lhs, const bool __rhs)
    {
        if (__rhs) {
            __lhs |= __k;
        } else {
            __lhs &= ~__k;
        }
    }

    // }}}2
};
// }}}1

_GLIBCXX_SIMD_END_NAMESPACE
#endif  // __cplusplus >= 201703L
#endif  // _GLIBCXX_EXPERIMENTAL_SIMD_FIXED_SIZE_H_
// vim: foldmethod=marker sw=2 noet ts=8 sts=2 tw=80
