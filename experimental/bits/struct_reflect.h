/*{{{
Copyright © 2018-2020 Matthias Kretz <kretz@kde.org>

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the names of contributing organizations nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

}}}*/

#ifndef _GLIBCXX_STRUCT_SIZE_H_
#define _GLIBCXX_STRUCT_SIZE_H_
#if defined __cpp_structured_bindings && defined __cpp_concepts && __cpp_concepts >= 201907
#define _GLIBCXX_HAVE_STRUCT_REFLECT 1
#include <utility>
#include <tuple>
#include <climits>

namespace __vir
{
namespace __detail  //{{{1
{
using std::remove_cvref_t;
using std::size_t;

// __struct_size implementation {{{2
template <class _Struct> struct __anything_but_base_of {
  template <class _Tp>
  requires(!std::is_base_of_v<_Tp, _Struct>)
  operator _Tp&();
};

template <class _Struct> struct __any_empty_base_of {
  template <class _Tp>
  requires(std::is_base_of_v<_Tp, _Struct> && std::is_empty_v<_Tp>)
  operator _Tp();
};

template <class _Tp, size_t... _Indexes>
concept __brace_constructible =
   requires { _Tp{((void)_Indexes, __anything_but_base_of<_Tp>())...}; }
|| requires { _Tp{__any_empty_base_of<_Tp>(), ((void)_Indexes, __anything_but_base_of<_Tp>())...}; }
|| requires { _Tp{__any_empty_base_of<_Tp>(), __any_empty_base_of<_Tp>(), ((void)_Indexes, __anything_but_base_of<_Tp>())...}; }
|| requires { _Tp{__any_empty_base_of<_Tp>(), __any_empty_base_of<_Tp>(), __any_empty_base_of<_Tp>(), ((void)_Indexes, __anything_but_base_of<_Tp>())...}; };

template <class _Tp, size_t... _Indexes>
constexpr bool __brace_constructible_helper(std::index_sequence<_Indexes...>)
{
  return __brace_constructible<_Tp, _Indexes...>;
}

template <class _Tp, size_t _Np>
concept __aggregate_with_n_members =
    __brace_constructible_helper<_Tp>(std::make_index_sequence<_Np>());

template <class _Tp, size_t _Lo = 0, size_t _Hi = sizeof(_Tp) * CHAR_BIT, size_t _Np = 8>
constexpr size_t __struct_size()
{
  constexpr size_t __left_index = _Lo + (_Np - _Lo) / 2;
  constexpr size_t __right_index = _Np + (_Hi - _Np + 1) / 2;
  if constexpr (__aggregate_with_n_members<_Tp, _Np>) {  // _Np is a valid size
    if constexpr (_Np == _Hi) {  // we found the best valid size inside [_Lo, _Hi]
      return _Np;
    } else {  // there may be a larger size in [_Np+1, _Hi]
      constexpr size_t __right = __struct_size<_Tp, _Np + 1, _Hi, __right_index>();
      if constexpr (__right == 0) {  // no, there isn't
        return _Np;
      } else {  // there is
        return __right;
      }
    }
  } else if constexpr (_Np == _Lo) {  // we can only look for a valid size in [_Np+1, _Hi]
    if constexpr (_Np == _Hi) {       // but [_Np+1, _Hi] is empty
      return 0;                    // no valid size found
    } else {                       // [_Np+1, _Hi] is non-empty
      return __struct_size<_Tp, _Np + 1, _Hi, __right_index>();
    }
  } else {  // the answer could be in [_Lo, _Np-1] or [_Np+1, _Hi]
    constexpr size_t __left = __struct_size<_Tp, _Lo, _Np - 1, __left_index>();
    if constexpr (__left > 0) {  // valid size in [_Lo, _Np-1] => there can't be a valid size
                               // in [_Np+1, _Hi] anymore
      return __left;
    } else if constexpr (_Np == _Hi) {  // [_Np+1, _Hi] is empty => [_Lo, _Hi] has no valid size
      return 0;
    } else {  // there can only be a valid size in [_Np+1, _Hi], if there is none the
              // recursion returns 0 anyway
      return __struct_size<_Tp, _Np + 1, _Hi, __right_index>();
    }
  }
}

// __struct_get implementation {{{2
template <size_t _Total> struct __struct_get;

template <typename _Tp> struct __remove_ref_in_tuple;
template <typename... _Ts> struct __remove_ref_in_tuple<std::tuple<_Ts...>> {
  using type = std::tuple<std::remove_reference_t<_Ts>...>;
};
template <typename _T1, typename _T2> struct __remove_ref_in_tuple<std::pair<_T1, _T2>> {
  using type = std::pair<std::remove_reference_t<_T1>, std::remove_reference_t<_T2>>;
};

template <> struct __struct_get<0> {
  template <class _Tp> std::tuple<> __to_tuple_ref(_Tp &&) { return {}; }
  template <class _Tp> std::tuple<> __to_tuple(const _Tp &) { return {}; }
};

template <> struct __struct_get<1> {
  template <class _Tp> auto __to_tuple_ref(_Tp &&__obj)
  {
    auto && [a] = __obj;
    return std::forward_as_tuple(a);
  }
  template <class _Tp>
  auto __to_tuple(const _Tp &__obj) ->
      typename __remove_ref_in_tuple<decltype(__to_tuple_ref(std::declval<_Tp>()))>::type
  {
    const auto &[a] = __obj;
    return {a};
  }
  template <size_t _Np, class _Tp> const auto &get(const _Tp &__obj)
  {
    static_assert(_Np == 0);
    auto && [a] = __obj;
    return a;
  }
  template <size_t _Np, class _Tp> auto &get(_Tp &__obj)
  {
    static_assert(_Np == 0);
    auto && [a] = __obj;
    return a;
  }
};

template <> struct __struct_get<2> {
  template <class _Tp> auto __to_tuple_ref(_Tp &&__obj)
  {
    auto &&[a, b] = __obj;
    return std::forward_as_tuple(a, b);
  }
  template <class _Tp>
  auto __to_tuple(const _Tp &__obj) ->
      typename __remove_ref_in_tuple<decltype(__to_tuple_ref(std::declval<_Tp>()))>::type
  {
    const auto &[a, b] = __obj;
    return {a, b};
  }
  template <class _Tp> auto __to_pair_ref(_Tp &&__obj)
  {
    auto &&[a, b] = __obj;
    return std::pair<decltype((a)), decltype((b))>(a, b);
  }
  template <class _Tp>
  auto __to_pair(const _Tp &__obj) ->
      typename __remove_ref_in_tuple<decltype(__to_pair_ref(std::declval<_Tp>()))>::type
  {
    const auto &[a, b] = __obj;
    return {a, b};
  }
  template <size_t _Np, class _Tp> auto &get(_Tp &&__obj)
  {
    static_assert(_Np < 2);
    auto &&[a, b] = __obj;
    return std::get<_Np>(std::forward_as_tuple(a, b));
  }
};

#define _GLIBCXX_STRUCT_GET_(size_, ...)                                       \
  template <> struct __struct_get<size_>                                       \
  {                                                                            \
    template <class _Tp> auto __to_tuple_ref(_Tp&& __obj)                      \
    {                                                                          \
      auto&& [__VA_ARGS__] = __obj;                                            \
      return std::forward_as_tuple(__VA_ARGS__);                               \
    }                                                                          \
    template <class _Tp>                                                       \
    auto __to_tuple(const _Tp& __obj) -> typename __remove_ref_in_tuple<       \
      decltype(__to_tuple_ref(std::declval<_Tp>()))>::type                     \
    {                                                                          \
      const auto& [__VA_ARGS__] = __obj;                                       \
      return {__VA_ARGS__};                                                    \
    }                                                                          \
    template <size_t _Np, class _Tp> auto& get(_Tp&& __obj)                    \
    {                                                                          \
      static_assert(_Np < size_);                                              \
      auto&& [__VA_ARGS__] = __obj;                                            \
      return std::get<_Np>(std::forward_as_tuple(__VA_ARGS__));                \
    }                                                                          \
  }
_GLIBCXX_STRUCT_GET_(3, __x0, __x1, __x2);
_GLIBCXX_STRUCT_GET_(4, __x0, __x1, __x2, __x3);
_GLIBCXX_STRUCT_GET_(5, __x0, __x1, __x2, __x3, __x4);
_GLIBCXX_STRUCT_GET_(6, __x0, __x1, __x2, __x3, __x4, __x5);
_GLIBCXX_STRUCT_GET_(7, __x0, __x1, __x2, __x3, __x4, __x5, __x6);
_GLIBCXX_STRUCT_GET_(8, __x0, __x1, __x2, __x3, __x4, __x5, __x6, __x7);
_GLIBCXX_STRUCT_GET_(9, __x0, __x1, __x2, __x3, __x4, __x5, __x6, __x7, __x8);
_GLIBCXX_STRUCT_GET_(10, __x0, __x1, __x2, __x3, __x4, __x5, __x6, __x7, __x8,
		     __x9);
_GLIBCXX_STRUCT_GET_(11, __x0, __x1, __x2, __x3, __x4, __x5, __x6, __x7, __x8,
		     __x9, __x10);
_GLIBCXX_STRUCT_GET_(12, __x0, __x1, __x2, __x3, __x4, __x5, __x6, __x7, __x8,
		     __x9, __x10, __x11);
_GLIBCXX_STRUCT_GET_(13, __x0, __x1, __x2, __x3, __x4, __x5, __x6, __x7, __x8,
		     __x9, __x10, __x11, __x12);
_GLIBCXX_STRUCT_GET_(14, __x0, __x1, __x2, __x3, __x4, __x5, __x6, __x7, __x8,
		     __x9, __x10, __x11, __x12, __x13);
_GLIBCXX_STRUCT_GET_(15, __x0, __x1, __x2, __x3, __x4, __x5, __x6, __x7, __x8,
		     __x9, __x10, __x11, __x12, __x13, __x14);
_GLIBCXX_STRUCT_GET_(16, __x0, __x1, __x2, __x3, __x4, __x5, __x6, __x7, __x8,
		     __x9, __x10, __x11, __x12, __x13, __x14, __x15);
_GLIBCXX_STRUCT_GET_(17, __x0, __x1, __x2, __x3, __x4, __x5, __x6, __x7, __x8,
		     __x9, __x10, __x11, __x12, __x13, __x14, __x15, __x16);
_GLIBCXX_STRUCT_GET_(18, __x0, __x1, __x2, __x3, __x4, __x5, __x6, __x7, __x8,
		     __x9, __x10, __x11, __x12, __x13, __x14, __x15, __x16,
		     __x17);
_GLIBCXX_STRUCT_GET_(19, __x0, __x1, __x2, __x3, __x4, __x5, __x6, __x7, __x8,
		     __x9, __x10, __x11, __x12, __x13, __x14, __x15, __x16,
		     __x17, __x18);
_GLIBCXX_STRUCT_GET_(20, __x0, __x1, __x2, __x3, __x4, __x5, __x6, __x7, __x8,
		     __x9, __x10, __x11, __x12, __x13, __x14, __x15, __x16,
		     __x17, __x18, __x19);
_GLIBCXX_STRUCT_GET_(21, __x0, __x1, __x2, __x3, __x4, __x5, __x6, __x7, __x8,
		     __x9, __x10, __x11, __x12, __x13, __x14, __x15, __x16,
		     __x17, __x18, __x19, __x20);
_GLIBCXX_STRUCT_GET_(22, __x0, __x1, __x2, __x3, __x4, __x5, __x6, __x7, __x8,
		     __x9, __x10, __x11, __x12, __x13, __x14, __x15, __x16,
		     __x17, __x18, __x19, __x20, __x21);
_GLIBCXX_STRUCT_GET_(23, __x0, __x1, __x2, __x3, __x4, __x5, __x6, __x7, __x8,
		     __x9, __x10, __x11, __x12, __x13, __x14, __x15, __x16,
		     __x17, __x18, __x19, __x20, __x21, __x22);
_GLIBCXX_STRUCT_GET_(24, __x0, __x1, __x2, __x3, __x4, __x5, __x6, __x7, __x8,
		     __x9, __x10, __x11, __x12, __x13, __x14, __x15, __x16,
		     __x17, __x18, __x19, __x20, __x21, __x22, __x23);
_GLIBCXX_STRUCT_GET_(25, __x0, __x1, __x2, __x3, __x4, __x5, __x6, __x7, __x8,
		     __x9, __x10, __x11, __x12, __x13, __x14, __x15, __x16,
		     __x17, __x18, __x19, __x20, __x21, __x22, __x23, __x24);
_GLIBCXX_STRUCT_GET_(26, __x0, __x1, __x2, __x3, __x4, __x5, __x6, __x7, __x8,
		     __x9, __x10, __x11, __x12, __x13, __x14, __x15, __x16,
		     __x17, __x18, __x19, __x20, __x21, __x22, __x23, __x24,
		     __x25);
_GLIBCXX_STRUCT_GET_(27, __x0, __x1, __x2, __x3, __x4, __x5, __x6, __x7, __x8,
		     __x9, __x10, __x11, __x12, __x13, __x14, __x15, __x16,
		     __x17, __x18, __x19, __x20, __x21, __x22, __x23, __x24,
		     __x25, __x26);
_GLIBCXX_STRUCT_GET_(28, __x0, __x1, __x2, __x3, __x4, __x5, __x6, __x7, __x8,
		     __x9, __x10, __x11, __x12, __x13, __x14, __x15, __x16,
		     __x17, __x18, __x19, __x20, __x21, __x22, __x23, __x24,
		     __x25, __x26, __x27);
_GLIBCXX_STRUCT_GET_(29, __x0, __x1, __x2, __x3, __x4, __x5, __x6, __x7, __x8,
		     __x9, __x10, __x11, __x12, __x13, __x14, __x15, __x16,
		     __x17, __x18, __x19, __x20, __x21, __x22, __x23, __x24,
		     __x25, __x26, __x27, __x28);
_GLIBCXX_STRUCT_GET_(30, __x0, __x1, __x2, __x3, __x4, __x5, __x6, __x7, __x8,
		     __x9, __x10, __x11, __x12, __x13, __x14, __x15, __x16,
		     __x17, __x18, __x19, __x20, __x21, __x22, __x23, __x24,
		     __x25, __x26, __x27, __x28, __x29);
_GLIBCXX_STRUCT_GET_(31, __x0, __x1, __x2, __x3, __x4, __x5, __x6, __x7, __x8,
		     __x9, __x10, __x11, __x12, __x13, __x14, __x15, __x16,
		     __x17, __x18, __x19, __x20, __x21, __x22, __x23, __x24,
		     __x25, __x26, __x27, __x28, __x29, __x30);
_GLIBCXX_STRUCT_GET_(32, __x0, __x1, __x2, __x3, __x4, __x5, __x6, __x7, __x8,
		     __x9, __x10, __x11, __x12, __x13, __x14, __x15, __x16,
		     __x17, __x18, __x19, __x20, __x21, __x22, __x23, __x24,
		     __x25, __x26, __x27, __x28, __x29, __x30, __x31);
_GLIBCXX_STRUCT_GET_(33, __x0, __x1, __x2, __x3, __x4, __x5, __x6, __x7, __x8,
		     __x9, __x10, __x11, __x12, __x13, __x14, __x15, __x16,
		     __x17, __x18, __x19, __x20, __x21, __x22, __x23, __x24,
		     __x25, __x26, __x27, __x28, __x29, __x30, __x31, __x32);
_GLIBCXX_STRUCT_GET_(34, __x0, __x1, __x2, __x3, __x4, __x5, __x6, __x7, __x8,
		     __x9, __x10, __x11, __x12, __x13, __x14, __x15, __x16,
		     __x17, __x18, __x19, __x20, __x21, __x22, __x23, __x24,
		     __x25, __x26, __x27, __x28, __x29, __x30, __x31, __x32,
		     __x33);
_GLIBCXX_STRUCT_GET_(35, __x0, __x1, __x2, __x3, __x4, __x5, __x6, __x7, __x8,
		     __x9, __x10, __x11, __x12, __x13, __x14, __x15, __x16,
		     __x17, __x18, __x19, __x20, __x21, __x22, __x23, __x24,
		     __x25, __x26, __x27, __x28, __x29, __x30, __x31, __x32,
		     __x33, __x34);
_GLIBCXX_STRUCT_GET_(36, __x0, __x1, __x2, __x3, __x4, __x5, __x6, __x7, __x8,
		     __x9, __x10, __x11, __x12, __x13, __x14, __x15, __x16,
		     __x17, __x18, __x19, __x20, __x21, __x22, __x23, __x24,
		     __x25, __x26, __x27, __x28, __x29, __x30, __x31, __x32,
		     __x33, __x34, __x35);
_GLIBCXX_STRUCT_GET_(37, __x0, __x1, __x2, __x3, __x4, __x5, __x6, __x7, __x8,
		     __x9, __x10, __x11, __x12, __x13, __x14, __x15, __x16,
		     __x17, __x18, __x19, __x20, __x21, __x22, __x23, __x24,
		     __x25, __x26, __x27, __x28, __x29, __x30, __x31, __x32,
		     __x33, __x34, __x35, __x36);
_GLIBCXX_STRUCT_GET_(38, __x0, __x1, __x2, __x3, __x4, __x5, __x6, __x7, __x8,
		     __x9, __x10, __x11, __x12, __x13, __x14, __x15, __x16,
		     __x17, __x18, __x19, __x20, __x21, __x22, __x23, __x24,
		     __x25, __x26, __x27, __x28, __x29, __x30, __x31, __x32,
		     __x33, __x34, __x35, __x36, __x37);
_GLIBCXX_STRUCT_GET_(39, __x0, __x1, __x2, __x3, __x4, __x5, __x6, __x7, __x8,
		     __x9, __x10, __x11, __x12, __x13, __x14, __x15, __x16,
		     __x17, __x18, __x19, __x20, __x21, __x22, __x23, __x24,
		     __x25, __x26, __x27, __x28, __x29, __x30, __x31, __x32,
		     __x33, __x34, __x35, __x36, __x37, __x38);
_GLIBCXX_STRUCT_GET_(40, __x0, __x1, __x2, __x3, __x4, __x5, __x6, __x7, __x8,
		     __x9, __x10, __x11, __x12, __x13, __x14, __x15, __x16,
		     __x17, __x18, __x19, __x20, __x21, __x22, __x23, __x24,
		     __x25, __x26, __x27, __x28, __x29, __x30, __x31, __x32,
		     __x33, __x34, __x35, __x36, __x37, __x38, __x39);
_GLIBCXX_STRUCT_GET_(41, __x0, __x1, __x2, __x3, __x4, __x5, __x6, __x7, __x8,
		     __x9, __x10, __x11, __x12, __x13, __x14, __x15, __x16,
		     __x17, __x18, __x19, __x20, __x21, __x22, __x23, __x24,
		     __x25, __x26, __x27, __x28, __x29, __x30, __x31, __x32,
		     __x33, __x34, __x35, __x36, __x37, __x38, __x39, __x40);
_GLIBCXX_STRUCT_GET_(42, __x0, __x1, __x2, __x3, __x4, __x5, __x6, __x7, __x8,
		     __x9, __x10, __x11, __x12, __x13, __x14, __x15, __x16,
		     __x17, __x18, __x19, __x20, __x21, __x22, __x23, __x24,
		     __x25, __x26, __x27, __x28, __x29, __x30, __x31, __x32,
		     __x33, __x34, __x35, __x36, __x37, __x38, __x39, __x40,
		     __x41);
_GLIBCXX_STRUCT_GET_(43, __x0, __x1, __x2, __x3, __x4, __x5, __x6, __x7, __x8,
		     __x9, __x10, __x11, __x12, __x13, __x14, __x15, __x16,
		     __x17, __x18, __x19, __x20, __x21, __x22, __x23, __x24,
		     __x25, __x26, __x27, __x28, __x29, __x30, __x31, __x32,
		     __x33, __x34, __x35, __x36, __x37, __x38, __x39, __x40,
		     __x41, __x42);
_GLIBCXX_STRUCT_GET_(44, __x0, __x1, __x2, __x3, __x4, __x5, __x6, __x7, __x8,
		     __x9, __x10, __x11, __x12, __x13, __x14, __x15, __x16,
		     __x17, __x18, __x19, __x20, __x21, __x22, __x23, __x24,
		     __x25, __x26, __x27, __x28, __x29, __x30, __x31, __x32,
		     __x33, __x34, __x35, __x36, __x37, __x38, __x39, __x40,
		     __x41, __x42, __x43);
_GLIBCXX_STRUCT_GET_(45, __x0, __x1, __x2, __x3, __x4, __x5, __x6, __x7, __x8,
		     __x9, __x10, __x11, __x12, __x13, __x14, __x15, __x16,
		     __x17, __x18, __x19, __x20, __x21, __x22, __x23, __x24,
		     __x25, __x26, __x27, __x28, __x29, __x30, __x31, __x32,
		     __x33, __x34, __x35, __x36, __x37, __x38, __x39, __x40,
		     __x41, __x42, __x43, __x44);
_GLIBCXX_STRUCT_GET_(46, __x0, __x1, __x2, __x3, __x4, __x5, __x6, __x7, __x8,
		     __x9, __x10, __x11, __x12, __x13, __x14, __x15, __x16,
		     __x17, __x18, __x19, __x20, __x21, __x22, __x23, __x24,
		     __x25, __x26, __x27, __x28, __x29, __x30, __x31, __x32,
		     __x33, __x34, __x35, __x36, __x37, __x38, __x39, __x40,
		     __x41, __x42, __x43, __x44, __x45);
_GLIBCXX_STRUCT_GET_(47, __x0, __x1, __x2, __x3, __x4, __x5, __x6, __x7, __x8,
		     __x9, __x10, __x11, __x12, __x13, __x14, __x15, __x16,
		     __x17, __x18, __x19, __x20, __x21, __x22, __x23, __x24,
		     __x25, __x26, __x27, __x28, __x29, __x30, __x31, __x32,
		     __x33, __x34, __x35, __x36, __x37, __x38, __x39, __x40,
		     __x41, __x42, __x43, __x44, __x45, __x46);
_GLIBCXX_STRUCT_GET_(48, __x0, __x1, __x2, __x3, __x4, __x5, __x6, __x7, __x8,
		     __x9, __x10, __x11, __x12, __x13, __x14, __x15, __x16,
		     __x17, __x18, __x19, __x20, __x21, __x22, __x23, __x24,
		     __x25, __x26, __x27, __x28, __x29, __x30, __x31, __x32,
		     __x33, __x34, __x35, __x36, __x37, __x38, __x39, __x40,
		     __x41, __x42, __x43, __x44, __x45, __x46, __x47);
_GLIBCXX_STRUCT_GET_(49, __x0, __x1, __x2, __x3, __x4, __x5, __x6, __x7, __x8,
		     __x9, __x10, __x11, __x12, __x13, __x14, __x15, __x16,
		     __x17, __x18, __x19, __x20, __x21, __x22, __x23, __x24,
		     __x25, __x26, __x27, __x28, __x29, __x30, __x31, __x32,
		     __x33, __x34, __x35, __x36, __x37, __x38, __x39, __x40,
		     __x41, __x42, __x43, __x44, __x45, __x46, __x47, __x48);
_GLIBCXX_STRUCT_GET_(50, __x0, __x1, __x2, __x3, __x4, __x5, __x6, __x7, __x8,
		     __x9, __x10, __x11, __x12, __x13, __x14, __x15, __x16,
		     __x17, __x18, __x19, __x20, __x21, __x22, __x23, __x24,
		     __x25, __x26, __x27, __x28, __x29, __x30, __x31, __x32,
		     __x33, __x34, __x35, __x36, __x37, __x38, __x39, __x40,
		     __x41, __x42, __x43, __x44, __x45, __x46, __x47, __x48,
		     __x49);
#undef _GLIBCXX_STRUCT_GET_

// concept definitions {{{2
template <typename _Tp> concept __has_tuple_size = requires(_Tp __x, std::tuple_size<_Tp> __ts)
{
  {static_cast<int>(__ts)} -> std::same_as<int>;
  __struct_get<std::tuple_size_v<_Tp>>().__to_tuple(__x);
};
template <typename _Tp>
concept __aggregate_without_tuple_size =
    std::is_aggregate_v<_Tp> && !__has_tuple_size<_Tp> && requires (const _Tp& __x) {
  __detail::__struct_size<_Tp>();
  __detail::__struct_get<__detail::__struct_size<_Tp>()>().__to_tuple_ref(__x);
};

// traits {{{2
template <typename _From, typename _To> struct __copy_cvref {
  using _From2 = std::remove_reference_t<_From>;
  using __with_const = std::conditional_t<std::is_const_v<_From2>, const _To, _To>;
  using __with_volatile =
      std::conditional_t<std::is_volatile_v<_From2>, volatile __with_const, __with_const>;
  using type = std::conditional_t<std::is_lvalue_reference_v<_From>, __with_volatile &,
                                  std::conditional_t<std::is_rvalue_reference_v<_From>,
                                                     __with_volatile &&, __with_volatile>>;
};
}  // namespace __detail }}}1

/**
 * The value of __struct_size is the number of non-static data members of the type \p _Tp.
 * More precisely, __struct_size is the number of elements in the identifier-list of a
 * structured binding declaration.
 *
 * \tparam _Tp An aggregate type or a type specializing `std::tuple_size` that can be
 *           destructured via a structured binding. This implies that either \p _Tp has only
 *           empty bases (only up to 3 are supported) or \p _Tp has no non-static data
 *           members and a single base class with non-static data members. Using
 *           aggregate types that do not support destructuring is ill-formed. Using
 *           non-aggregate types that do not support destructuring results in a
 *           substitution failure.
 */
template <typename _Tp>
requires __detail::__aggregate_without_tuple_size<_Tp> || __detail::__has_tuple_size<_Tp>
constexpr inline std::size_t __struct_size;

template <__detail::__aggregate_without_tuple_size _Tp>
constexpr inline std::size_t __struct_size<_Tp> = __detail::__struct_size<_Tp>();

template <__detail::__has_tuple_size _Tp>
constexpr inline std::size_t __struct_size<_Tp> = std::tuple_size_v<_Tp>;

/**
 * Returns a cv-qualified reference to the \p _Np -th non-static data member in \p __obj.
 */
template <std::size_t _Np, class _Tp,
          std::size_t _Total = __struct_size<std::remove_cvref_t<_Tp>>,
          class = std::enable_if_t<(_Np < _Total)>>
decltype(auto) __struct_get(_Tp &&__obj)
{
  return __detail::__struct_get<_Total>().template get<_Np>(std::forward<_Tp>(__obj));
}

/**
 * `__struct_element_t` is an alias for the type of the \p _Np -th non-static data member of
 * \p _Tp.
 */
template <std::size_t _Np, class _Tp>
using __struct_element_t =
    std::remove_reference_t<decltype(__struct_get<_Np>(std::declval<_Tp &>()))>;

/**
 * Returns a std::tuple with a copy of all the non-static data members of \p __obj.
 */
template <class _Tp>
requires requires { __struct_size<std::remove_cvref_t<_Tp>>; }
auto __to_tuple(_Tp &&__obj)
{
  return __detail::__struct_get<__struct_size<std::remove_cvref_t<_Tp>>>().__to_tuple(
      std::forward<_Tp>(__obj));
}

/**
 * Returns a std::tuple of lvalue references to all the non-static data members of \p __obj.
 */
template <class _Tp>
requires requires { __struct_size<std::remove_cvref_t<_Tp>>; }
auto __to_tuple_ref(_Tp &&__obj)
{
  return __detail::__struct_get<__struct_size<std::remove_cvref_t<_Tp>>>().__to_tuple_ref(
      std::forward<_Tp>(__obj));
}

/**
 * Defines the member type \p type to a std::tuple specialization matching the non-static
 * data members of \p _Tp.
 */
template <class _Tp>
requires requires { __struct_size<std::remove_cvref_t<_Tp>>; }
struct __as_tuple
    : __detail::__copy_cvref<
          _Tp, decltype(__detail::__struct_get<__struct_size<std::remove_cvref_t<_Tp>>>().__to_tuple(
                 std::declval<_Tp>()))> {
};

/**
 * Alias for a std::tuple specialization matching the non-static data members of \p _Tp.
 */
template <class _Tp> using __as_tuple_t = typename __as_tuple<_Tp>::type;

/**
 * Returns a std::pair with a copy of all the non-static data members of \p __obj.
 */
template <class _Tp>
requires(__struct_size<std::remove_cvref_t<_Tp>> == 2)
auto __to_pair(_Tp &&__obj)
{
  return __detail::__struct_get<2>().__to_pair(std::forward<_Tp>(__obj));
}

/**
 * Returns a std::pair of lvalue references to all the non-static data members of \p __obj.
 */
template <class _Tp>
requires(__struct_size<std::remove_cvref_t<_Tp>> == 2)
auto __to_pair_ref(_Tp &&__obj)
{
  return __detail::__struct_get<2>().__to_pair_ref(std::forward<_Tp>(__obj));
}

/**
 * Defines the member type \p type to a std::pair specialization matching the non-static
 * data members of \p _Tp.
 */
template <class _Tp>
requires (__struct_size<std::remove_cvref_t<_Tp>> == 2)
struct __as_pair
    : __detail::__copy_cvref<
          _Tp, decltype(__detail::__struct_get<2>().__to_pair(
                 std::declval<_Tp>()))> {
};

/**
 * Alias for a std::pair specialization matching the non-static data members of \p _Tp.
 */
template <class _Tp> using __as_pair_t = typename __as_pair<_Tp>::type;

}  // namespace __vir

#endif // structured bindings & concepts
#endif  // _GLIBCXX_STRUCT_SIZE_H_

// vim: foldmethod=marker
