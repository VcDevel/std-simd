/*{{{
Copyright © 2017-2019 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH
                      Matthias Kretz <m.kretz@gsi.de>

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

//#define UNITTEST_ONLY_XTEST 1
#include <cstddef>
#include "unittest.h"
#include "metahelpers.h"

#define TESTTYPES                                                              \
  long double, double, float, unsigned long long, long long, unsigned long,    \
    long, unsigned int, int, unsigned short, short, unsigned char,             \
    signed char, char, wchar_t, char16_t, char32_t
template <class... Ts> using base_template = std::experimental::simd<Ts...>;
#include "testtypes.h"

using std::experimental::simd;
using std::experimental::simd_mask;
using vir::concat;
using vir::expand_list;
using vir::filter_list;
using vir::Template;
using vir::Template1;
using vir::Typelist;

using std::nullptr_t;

struct dummy
{
};
template <class A> using dummy_simd = simd<dummy, A>;
template <class A> using dummy_mask = simd_mask<dummy, A>;
template <class A> using bool_simd = simd<bool, A>;
template <class A> using bool_mask = simd_mask<bool, A>;

namespace assertions {
using std::experimental::__fixed_size_storage_t;
using std::experimental::_SimdTuple;
using std::experimental::simd_abi::__avx;
using std::experimental::simd_abi::__avx512;
using std::experimental::simd_abi::__sse;
using std::experimental::simd_abi::_Avx;
using std::experimental::simd_abi::_Avx512;
using std::experimental::simd_abi::_Neon;
using std::experimental::simd_abi::_Sse;
using std::experimental::simd_abi::scalar;

template <class A, class B>
constexpr int
assert_equal()
{
  static_assert(std::is_same_v<A, B>);
  return 0;
}

int tmp[] = {
  assert_equal<__fixed_size_storage_t<float, 1>, _SimdTuple<float, scalar>>(),
  assert_equal<__fixed_size_storage_t<int, 1>, _SimdTuple<int, scalar>>(),
  assert_equal<__fixed_size_storage_t<char16_t, 1>,
	       _SimdTuple<char16_t, scalar>>(),
#if _GLIBCXX_SIMD_HAVE_AVX512VL && _GLIBCXX_SIMD_X86INTRIN
  assert_equal<__fixed_size_storage_t<float, 2>,
	       _SimdTuple<float, _Avx512<8>>>(),
  assert_equal<__fixed_size_storage_t<float, 3>,
	       _SimdTuple<float, _Avx512<12>>>(),
  assert_equal<__fixed_size_storage_t<float, 4>,
	       _SimdTuple<float, _Avx512<16>>>(),
  assert_equal<__fixed_size_storage_t<float, 5>,
	       _SimdTuple<float, _Avx512<20>>>(),
  assert_equal<__fixed_size_storage_t<float, 5>,
	       _SimdTuple<float, _Avx512<20>>>(),
  assert_equal<__fixed_size_storage_t<float, 8>,
	       _SimdTuple<float, _Avx512<32>>>(),
  assert_equal<__fixed_size_storage_t<float, 12>,
	       _SimdTuple<float, _Avx512<48>>>(),
  assert_equal<__fixed_size_storage_t<float, 13>,
	       _SimdTuple<float, _Avx512<52>>>(),
  assert_equal<__fixed_size_storage_t<float, 16>,
	       _SimdTuple<float, __avx512>>(),
  assert_equal<__fixed_size_storage_t<float, 20>,
	       _SimdTuple<float, __avx512, _Avx512<16>>>(),
  assert_equal<__fixed_size_storage_t<float, 24>,
	       _SimdTuple<float, __avx512, _Avx512<32>>>(),
  assert_equal<__fixed_size_storage_t<float, 28>,
	       _SimdTuple<float, __avx512, _Avx512<48>>>(),
  assert_equal<__fixed_size_storage_t<float, 29>,
	       _SimdTuple<float, __avx512, _Avx512<52>>>(),
#else
#if _GLIBCXX_SIMD_HAVE_SSE_ABI
  assert_equal<__fixed_size_storage_t<float, 2>, _SimdTuple<float, _Sse<8>>>(),
  assert_equal<__fixed_size_storage_t<float, 3>, _SimdTuple<float, _Sse<12>>>(),
  assert_equal<__fixed_size_storage_t<float, 4>, _SimdTuple<float, __sse>>(),
#if !_GLIBCXX_SIMD_HAVE_AVX_ABI
  assert_equal<__fixed_size_storage_t<float, 5>,
	       _SimdTuple<float, __sse, scalar>>(),
#endif
#elif _GLIBCXX_SIMD_HAVE_NEON
  assert_equal<__fixed_size_storage_t<float, 2>, _SimdTuple<float, _Neon<8>>>(),
  assert_equal<__fixed_size_storage_t<float, 3>,
	       _SimdTuple<float, _Neon<12>>>(),
  assert_equal<__fixed_size_storage_t<float, 4>,
	       _SimdTuple<float, _Neon<16>>>(),
  assert_equal<__fixed_size_storage_t<float, 5>,
	       _SimdTuple<float, _Neon<16>, scalar>>(),
  assert_equal<__fixed_size_storage_t<float, 6>,
	       _SimdTuple<float, _Neon<16>, _Neon<8>>>(),
#endif // _GLIBCXX_SIMD_HAVE_SSE_ABI
#if _GLIBCXX_SIMD_HAVE_AVX_ABI
  assert_equal<__fixed_size_storage_t<float, 5>, _SimdTuple<float, _Avx<20>>>(),
  assert_equal<__fixed_size_storage_t<float, 8>, _SimdTuple<float, __avx>>(),
#if !_GLIBCXX_SIMD_HAVE_AVX512F
  assert_equal<__fixed_size_storage_t<float, 12>,
	       _SimdTuple<float, __avx, __sse>>(),
  assert_equal<__fixed_size_storage_t<float, 13>,
	       _SimdTuple<float, __avx, _Avx<20>>>(),
  assert_equal<__fixed_size_storage_t<float, 32>,
	       _SimdTuple<float, __avx, __avx, __avx, __avx>>(),
#endif
#endif
#if _GLIBCXX_SIMD_HAVE_AVX512F && !_GLIBCXX_SIMD_HAVE_AVX512VL                 \
  && _GLIBCXX_SIMD_X86INTRIN
  assert_equal<__fixed_size_storage_t<float, 16>,
	       _SimdTuple<float, __avx512>>(),
  assert_equal<__fixed_size_storage_t<float, 17>,
	       _SimdTuple<float, __avx512, scalar>>(),
  assert_equal<__fixed_size_storage_t<float, 20>,
	       _SimdTuple<float, __avx512, __sse>>(),
  assert_equal<__fixed_size_storage_t<float, 24>,
	       _SimdTuple<float, __avx512, __avx>>(),
  assert_equal<__fixed_size_storage_t<float, 28>,
	       _SimdTuple<float, __avx512, _Avx512<48>>>(),
  assert_equal<__fixed_size_storage_t<float, 29>,
	       _SimdTuple<float, __avx512, _Avx512<52>>>(),
#endif
#endif
};

} // namespace assertions

// type lists {{{1
using all_valid_scalars
  = vir::expand_one<Template<simd, std::experimental::simd_abi::scalar>,
		    testtypes>;

using all_valid_fixed_size = expand_list<fixed_size_abi_list, testtypes>;

using all_valid_simd = native_test_types;

#if ABITYPES == 0
using all_native_simd_types
  = expand_list<Typelist<Template<simd, std::experimental::simd_abi::__sse>,
			 Template<simd, std::experimental::simd_abi::__avx>,
			 Template<simd, std::experimental::simd_abi::__avx512>,
			 Template<simd, std::experimental::simd_abi::__neon>>,
		testtypes>;

TEST_TYPES(V, has_size, all_native_simd_types) //{{{1
{
  VERIFY((std::experimental::simd_size_v<typename V::value_type,
					 typename V::abi_type>)
	 > 0);
}

TEST_TYPES(
  Tup, has_no_size, //{{{1
  concat<
    outer_product<concat<testtypes, nullptr_t, dummy>, Typelist<int, dummy>>,
    outer_product<Typelist<nullptr_t, dummy>,
		  Typelist<std::experimental::simd_abi::scalar,
			   std::experimental::simd_abi::fixed_size<4>,
			   std::experimental::simd_abi::__sse,
			   std::experimental::simd_abi::__avx,
			   std::experimental::simd_abi::__avx512,
			   std::experimental::simd_abi::__neon>>>)
{
  VERIFY(!(sfinae_is_callable<typename Tup::template at<0>,
			      typename Tup::template at<1>>(
    [](auto a, auto b)
      -> decltype(
	std::experimental::simd_size<decltype(a), decltype(b)>::type) {
      return {};
    })));
}
#endif

template <class T> constexpr bool is_fixed_size_mask(T) { return false; }
template <class T, int N>
constexpr bool is_fixed_size_mask(std::experimental::fixed_size_simd_mask<T, N>)
{
  return true;
}

template <class T> constexpr bool is_fixed_size_simd(T) { return false; }
template <class T, int N>
constexpr bool is_fixed_size_simd(std::experimental::fixed_size_simd<T, N>)
{
  return true;
}

TEST_TYPES(V, is_usable, //{{{1
	   concat<all_valid_scalars, all_valid_simd, all_valid_fixed_size>)
{
  using M = typename V::mask_type;
#ifndef __SUPPORT_SNAN__
  VERIFY(std::is_trivially_default_constructible<V>::value);
  VERIFY(std::is_trivially_default_constructible<M>::value);
#endif
  // fixed_size must always pass via the stack, therefore not trivially
  // copyable. All others preferably should be trivially copyable, though
  // this is not required by the spec.
  COMPARE(std::is_trivially_copyable<V>::value, !is_fixed_size_simd(V()));
  // OTOH, fixed_size masks are stored as bitmasks and thus should pass via the
  // stack
  VERIFY(std::is_trivially_copyable<M>::value);

  VERIFY(std::is_destructible<V>::value);
  VERIFY(std::is_copy_constructible<V>::value);
  VERIFY(std::is_copy_assignable<V>::value);
  VERIFY(std::is_destructible<M>::value);
  VERIFY(std::is_copy_constructible<M>::value);
  VERIFY(std::is_copy_assignable<M>::value);
}

using unusable_abis = Typelist<
#if !(_GLIBCXX_SIMD_HAVE_SSE_ABI || _GLIBCXX_SIMD_HAVE_NEON)
  Template<simd, std::experimental::simd_abi::_VecBuiltin<16>>,
  Template<simd_mask, std::experimental::simd_abi::_VecBuiltin<16>>,
#endif
#if !_GLIBCXX_SIMD_HAVE_AVX_ABI
  Template<simd, std::experimental::simd_abi::_VecBuiltin<32>>,
  Template<simd_mask, std::experimental::simd_abi::_VecBuiltin<32>>,
#endif
#if !_GLIBCXX_SIMD_HAVE_AVX512_ABI
  Template<simd, std::experimental::simd_abi::_VecBuiltin<64>>,
  Template<simd_mask, std::experimental::simd_abi::_VecBuiltin<64>>,
  Template<simd, std::experimental::simd_abi::_Avx512<64>>,
  Template<simd_mask, std::experimental::simd_abi::_Avx512<64>>,
#endif
  Template<simd, int>, Template<simd_mask, int>>;

template <typename... T>
using first = typename vir::Typelist<T...>::template at<0>;

template <typename... T>
using maxplus1_fixed_simd
  = stdx::fixed_size_simd<first<T...>,
			  stdx::simd_abi::max_fixed_size<first<T...>> + 1>;
template <typename... T>
using maxplus1_fixed_simd_mask
  = stdx::fixed_size_simd_mask<first<T...>,
			       stdx::simd_abi::max_fixed_size<first<T...>> + 1>;

using unusable_fixed_size = expand_list<
  Typelist<Template<maxplus1_fixed_simd>, Template<maxplus1_fixed_simd_mask>>,
  testtypes>;

using unusable_simd_types = concat<
  expand_list<Typelist<Template<simd, std::experimental::simd_abi::__sse>,
		       Template<simd_mask, std::experimental::simd_abi::__sse>>,
#if _GLIBCXX_SIMD_HAVE_SSE_ABI && !_GLIBCXX_SIMD_HAVE_FULL_SSE_ABI
	      typename filter_list<float, testtypes>::type
#else
	      Typelist<long double>
#endif
	      >,
  expand_list<Typelist<Template<simd, std::experimental::simd_abi::__avx>,
		       Template<simd_mask, std::experimental::simd_abi::__avx>>,
#if _GLIBCXX_SIMD_HAVE_AVX_ABI && !_GLIBCXX_SIMD_HAVE_FULL_AVX_ABI
	      typename filter_list<Typelist<float, double>, testtypes>::type
#else
	      Typelist<long double>
#endif
	      >,
  expand_list<
    Typelist<Template<simd, std::experimental::simd_abi::__neon>,
	     Template<simd_mask, std::experimental::simd_abi::__neon>>,
    Typelist<long double>>,
  expand_list<
    Typelist<Template<simd, std::experimental::simd_abi::__avx512>,
	     Template<simd_mask, std::experimental::simd_abi::__avx512>>,
#if _GLIBCXX_SIMD_HAVE_AVX512_ABI && !_GLIBCXX_SIMD_HAVE_FULL_AVX512_ABI
    typename filter_list<
      Typelist<float, double, ullong, llong, ulong, long, uint, int,
#if WCHAR_MAX > 0xffff
	       wchar_t,
#endif
	       char32_t>,
      testtypes>::type
#else
    Typelist<long double>
#endif
    >>;

TEST_TYPES(
  V, is_unusable, //{{{1
  concat<expand_list<unusable_abis, testtypes_wo_ldouble>, unusable_simd_types,
	 unusable_fixed_size,
	 expand_list<Typelist<Template1<dummy_simd>, Template1<dummy_mask>,
			      Template1<bool_simd>, Template1<bool_mask>>,
		     all_native_abis>>)
{
  VERIFY(!std::is_constructible<V>::value);
  VERIFY(!std::is_destructible<V>::value);
  VERIFY(!std::is_copy_constructible<V>::value);
  VERIFY(!std::is_copy_assignable<V>::value);
}

// loadstore_pointer_types {{{1
struct call_memload
{
  template <class V, class T>
  auto operator()(V&& v, const T* mem)
    -> decltype(v.copy_from(mem, std::experimental::element_aligned));
};
struct call_masked_memload
{
  template <class M, class V, class T>
  auto operator()(const M& k, V&& v, const T* mem)
    -> decltype(std::experimental::where(k, v).copy_from(
      mem, std::experimental::element_aligned));
};
struct call_memstore
{
  template <class V, class T>
  auto operator()(V&& v, T* mem)
    -> decltype(v.copy_to(mem, std::experimental::element_aligned));
};
struct call_masked_memstore
{
  template <class M, class V, class T>
  auto operator()(const M& k, V&& v, T* mem)
    -> decltype(std::experimental::where(k, v).copy_to(
      mem, std::experimental::element_aligned));
};
TEST_TYPES(V, loadstore_pointer_types, all_test_types)
{
  using vir::test::sfinae_is_callable;
  using M = typename V::mask_type;
  struct Foo
  {
  };
  VERIFY((sfinae_is_callable<V&, const int*>(call_memload())));
  VERIFY((sfinae_is_callable<V&, const float*>(call_memload())));
  VERIFY(!(sfinae_is_callable<V&, const bool*>(call_memload())));
  VERIFY(!(sfinae_is_callable<V&, const Foo*>(call_memload())));
  VERIFY((sfinae_is_callable<const V&, int*>(call_memstore())));
  VERIFY((sfinae_is_callable<const V&, float*>(call_memstore())));
  VERIFY(!(sfinae_is_callable<const V&, bool*>(call_memstore())));
  VERIFY(!(sfinae_is_callable<const V&, Foo*>(call_memstore())));

  VERIFY((sfinae_is_callable<M, const V&, const int*>(call_masked_memload())));
  VERIFY(
    (sfinae_is_callable<M, const V&, const float*>(call_masked_memload())));
  VERIFY(!(sfinae_is_callable<M, const V&, const Foo*>(call_masked_memload())));
  VERIFY((sfinae_is_callable<M, const V&, int*>(call_masked_memstore())));
  VERIFY((sfinae_is_callable<M, const V&, float*>(call_masked_memstore())));
  VERIFY(!(sfinae_is_callable<M, const V&, Foo*>(call_masked_memstore())));

  VERIFY((sfinae_is_callable<M, V&, const int*>(call_masked_memload())));
  VERIFY((sfinae_is_callable<M, V&, const float*>(call_masked_memload())));
  VERIFY(!(sfinae_is_callable<M, V&, const Foo*>(call_masked_memload())));

  VERIFY((sfinae_is_callable<M&, const bool*>(call_memload())));
  VERIFY(!(sfinae_is_callable<M&, const int*>(call_memload())));
  VERIFY(!(sfinae_is_callable<M&, const Foo*>(call_memload())));
  VERIFY((sfinae_is_callable<M&, bool*>(call_memstore())));
  VERIFY(!(sfinae_is_callable<M&, int*>(call_memstore())));
  VERIFY(!(sfinae_is_callable<M&, Foo*>(call_memstore())));

  VERIFY((sfinae_is_callable<M, M&, const bool*>(call_masked_memload())));
  VERIFY(!(sfinae_is_callable<M, M&, const int*>(call_masked_memload())));
  VERIFY(!(sfinae_is_callable<M, M&, const Foo*>(call_masked_memload())));
  VERIFY((sfinae_is_callable<M, M&, bool*>(call_masked_memstore())));
  VERIFY(!(sfinae_is_callable<M, M&, int*>(call_masked_memstore())));
  VERIFY(!(sfinae_is_callable<M, M&, Foo*>(call_masked_memstore())));

  VERIFY((sfinae_is_callable<M, const M&, const bool*>(call_masked_memload())));
  VERIFY(!(sfinae_is_callable<M, const M&, const int*>(call_masked_memload())));
  VERIFY(!(sfinae_is_callable<M, const M&, const Foo*>(call_masked_memload())));
  VERIFY((sfinae_is_callable<M, const M&, bool*>(call_masked_memstore())));
  VERIFY(!(sfinae_is_callable<M, const M&, int*>(call_masked_memstore())));
  VERIFY(!(sfinae_is_callable<M, const M&, Foo*>(call_masked_memstore())));
}

TEST(masked_loadstore_builtin)
{
  VERIFY(
    (sfinae_is_callable<bool, const int&, const int*>(call_masked_memload())));
  VERIFY((
    sfinae_is_callable<bool, const int&, const float*>(call_masked_memload())));
  VERIFY((
    sfinae_is_callable<bool, const bool&, const bool*>(call_masked_memload())));
  VERIFY(!(
    sfinae_is_callable<bool, const bool&, const int*>(call_masked_memload())));
  VERIFY((sfinae_is_callable<bool, const int&, int*>(call_masked_memstore())));
  VERIFY(
    (sfinae_is_callable<bool, const int&, float*>(call_masked_memstore())));
  VERIFY(
    (sfinae_is_callable<bool, const bool&, bool*>(call_masked_memstore())));
  VERIFY(
    !(sfinae_is_callable<bool, const bool&, int*>(call_masked_memstore())));

  VERIFY((sfinae_is_callable<bool, int&, const int*>(call_masked_memload())));
  VERIFY((sfinae_is_callable<bool, int&, const float*>(call_masked_memload())));
  VERIFY((sfinae_is_callable<bool, bool&, const bool*>(call_masked_memload())));
  VERIFY(!(sfinae_is_callable<bool, bool&, const int*>(call_masked_memload())));
}

TEST(deduce_broken)
{
  VERIFY(!(sfinae_is_callable<bool>(
    [](auto a) -> std::experimental::simd_abi::deduce_t<decltype(a), 1> {
      return {};
    })));
  VERIFY(!(sfinae_is_callable<bool>(
    [](auto a) -> std::experimental::simd_abi::deduce_t<decltype(a), 2> {
      return {};
    })));
  VERIFY(!(sfinae_is_callable<bool>(
    [](auto a) -> std::experimental::simd_abi::deduce_t<decltype(a), 4> {
      return {};
    })));
  VERIFY(!(sfinae_is_callable<bool>(
    [](auto a) -> std::experimental::simd_abi::deduce_t<decltype(a), 8> {
      return {};
    })));
  enum Foo
  {
  };
  VERIFY(!(sfinae_is_callable<Foo>(
    [](auto a) -> std::experimental::simd_abi::deduce_t<decltype(a), 1> {
      return {};
    })));
  VERIFY(!(sfinae_is_callable<Foo>(
    [](auto a) -> std::experimental::simd_abi::deduce_t<decltype(a), 8> {
      return {};
    })));
}

TEST_TYPES(V, deduce_from_list, all_test_types)
{
  using T = typename V::value_type;
  using A = typename V::abi_type;
  VERIFY((sfinae_is_callable<T>(
    [](auto a) -> std::experimental::simd_abi::deduce_t<decltype(a), 1> {
      return {};
    })));
  VERIFY((sfinae_is_callable<T>(
    [](auto a) -> std::experimental::simd_abi::deduce_t<decltype(a), 2> {
      return {};
    })));
  VERIFY((sfinae_is_callable<T>(
    [](auto a) -> std::experimental::simd_abi::deduce_t<decltype(a), 4> {
      return {};
    })));
  VERIFY((sfinae_is_callable<T>(
    [](auto a) -> std::experimental::simd_abi::deduce_t<decltype(a), 8> {
      return {};
    })));
  using W
    = std::experimental::simd_abi::deduce_t<T, V::size(), typename V::abi_type>;
  VERIFY((sfinae_is_callable<W>(
    [](auto a) -> std::experimental::simd<T, W> { return {}; })));
  if constexpr (std::experimental::__is_fixed_size_abi_v<A>)
    {
      VERIFY((V::size() == std::experimental::simd_size_v<T, W>) )
	<< vir::typeToString<W>();
    }
  else
    {
#ifdef __AVX512VL__
      // with AVX512VL <float, 8> deduces to simd<float, _Avx512<32>>
      if (sizeof(V) > 32)
	{
	  COMPARE(typeid(A), typeid(W));
	}
      else if (V::size() == 1)
	{
	  COMPARE(typeid(A), typeid(std::experimental::simd_abi::scalar));
	}
      else
	{
	  COMPARE(V::size(), (std::experimental::simd_size_v<T, W>) )
	    << vir::typeToString<W>();
	  using ExpectedAbi = std::experimental::simd_abi::
#if _GLIBCXX_SIMD_X86INTRIN
	    _Avx512
#else
	    _VecBuiltin
#endif
	    <V::size() * sizeof(T)>;
	  COMPARE_TYPES(W, ExpectedAbi);
	}
#else
      COMPARE(typeid(A), typeid(W));
#endif
    }
}

// vim: foldmethod=marker
