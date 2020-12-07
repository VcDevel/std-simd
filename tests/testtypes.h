/*  This file is part of the Vc library. {{{
Copyright © 2016-2017 Matthias Kretz <kretz@kde.org>

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

#ifndef TESTS_TESTTYPES_H_
#define TESTS_TESTTYPES_H_

#include <vir/typelist.h>
#include <experimental/simd>

using schar = signed char;
using uchar = unsigned char;
using ushort = unsigned short;
using uint = unsigned int;
using ulong = unsigned long;
using llong = long long;
using ullong = unsigned long long;
using ldouble = long double;
using wchar = wchar_t;
using char16 = char16_t;
using char32 = char32_t;
// type with sizeof(char) but different signedness
using xchar = std::conditional_t<std::is_unsigned_v<char>, schar, uchar>;

namespace stdx = std::experimental;
namespace simd_abi = std::experimental::simd_abi;

// all_native_abis {{{1
#ifdef TRAVIS
using all_native_abis
  = vir::Typelist<simd_abi::scalar,
		  simd_abi::_VecBuiltin<16>,
		  simd_abi::_VecBltnBtmsk<64>
		 >;
#else // TRAVIS
using all_native_abis
  = vir::Typelist<simd_abi::scalar, simd_abi::_VecBuiltin<8>,
		  simd_abi::_VecBuiltin<16>, simd_abi::_VecBuiltin<24>,
		  simd_abi::_VecBuiltin<32>, simd_abi::_VecBuiltin<48>,
		  simd_abi::_VecBuiltin<64>
#ifdef _GLIBCXX_SIMD_X86INTRIN
		  ,
		  simd_abi::_Avx512<8>, simd_abi::_Avx512<16>,
		  simd_abi::_Avx512<32>, simd_abi::_Avx512<64>
#endif
		  >;
#endif // TRAVIS

// (all_)arithmetic_types {{{1
using all_arithmetic_types
  = vir::Typelist<long double, double, float, long long, unsigned long, int,
		  unsigned short, signed char, unsigned long long, long,
		  unsigned int, short, unsigned char, char32_t, char16_t, char,
		  wchar_t>;
#ifdef ONE_RANDOM_ARITHMETIC_TYPE
using arithmetic_types = VIR_CHOOSE_ONE_RANDOMLY(all_arithmetic_types);
#else
using arithmetic_types = all_arithmetic_types;
#endif

// testtypes... {{{1
#ifdef TESTTYPES
using testtypes = vir::Typelist<TESTTYPES>;
#else
using testtypes = all_arithmetic_types;
#endif
using testtypes_wo_ldouble =
  typename vir::filter_list<long double, testtypes>::type;
using testtypes_64_32 = typename vir::filter_list<
  vir::Typelist<ushort, short, uchar, schar, char, wchar_t, char16_t>,
  testtypes_wo_ldouble>::type;
using testtypes_fp = typename vir::filter_list<
  vir::Typelist<ullong, llong, ulong, long, uint, int, char32_t>,
  testtypes_64_32>::type;
using testtypes_float = typename vir::filter_list<double, testtypes_fp>::type;
static_assert(vir::list_size<testtypes_fp>::value <= 2,
	      "filtering the list failed");
static_assert(vir::list_size<testtypes_float>::value <= 1,
	      "filtering the list failed");

// vT {{{1
using vschar = stdx::native_simd<schar>;
using vuchar = stdx::native_simd<uchar>;
using vshort = stdx::native_simd<short>;
using vushort = stdx::native_simd<ushort>;
using vint = stdx::native_simd<int>;
using vuint = stdx::native_simd<uint>;
using vlong = stdx::native_simd<long>;
using vulong = stdx::native_simd<ulong>;
using vllong = stdx::native_simd<llong>;
using vullong = stdx::native_simd<ullong>;
using vfloat = stdx::native_simd<float>;
using vdouble = stdx::native_simd<double>;
using vldouble = stdx::native_simd<long double>;

using vchar = stdx::native_simd<char>;
using vxchar = stdx::native_simd<xchar>;
using vwchar = stdx::native_simd<wchar_t>;
using vchar16 = stdx::native_simd<char16_t>;
using vchar32 = stdx::native_simd<char32_t>;

// viN/vfN {{{1
template <typename T> using vi8 = stdx::fixed_size_simd<T, vschar::size()>;
template <typename T> using vi16 = stdx::fixed_size_simd<T, vshort::size()>;
template <typename T> using vf32 = stdx::fixed_size_simd<T, vfloat::size()>;
template <typename T> using vi32 = stdx::fixed_size_simd<T, vint::size()>;
template <typename T> using vf64 = stdx::fixed_size_simd<T, vdouble::size()>;
template <typename T> using vi64 = stdx::fixed_size_simd<T, vllong::size()>;
template <typename T>
using vl = typename std::conditional<sizeof(long) == sizeof(llong), vi64<T>,
				     vi32<T>>::type;

// current_native_test_types {{{1
using current_native_test_types
  = vir::expand_one<vir::Template1<stdx::native_simd>, testtypes>;
using current_native_mask_test_types
  = vir::expand_one<vir::Template1<stdx::native_simd_mask>, testtypes>;

// native_test_types {{{1
template <class T> struct is_unusable : std::negation<std::is_destructible<T>>
{
};
using native_test_types =
#if !defined(ABITYPES) || ABITYPES == 0
  // Creates a list of
  //   base_template<testtypes..., all_native_abis...>
  // using an outer product of testtypes and all_native_abis. Subseqently, all
  // types that are unusable (not destructible) are filtered out.
  vir::filter_list<
    vir::filter_predicate<is_unusable>,
    vir::expand_one<vir::Template<base_template>,
		    vir::outer_product<testtypes, all_native_abis>>>::type;
#else  // !defined(ABITYPES) || ABITYPES == 0
  vir::Typelist<>;
#endif // !defined(ABITYPES) || ABITYPES == 0

// native_real_test_types {{{1
template <class T> struct first_tparam_is_not_fp : std::true_type
{
};
template <template <typename...> class Class, typename T0, typename... Ts>
struct first_tparam_is_not_fp<Class<T0, Ts...>>
  : std::negation<std::is_floating_point<T0>>
{
};
using native_real_test_types =
  typename vir::filter_list<vir::filter_predicate<first_tparam_is_not_fp>,
			    native_test_types>::type;

// fixed_size_abi_list {{{1
using fixed_size_abi_list = vir::concat<
#ifndef ABITYPES
  VIR_CHOOSE_ONE_RANDOMLY(
    vir::Typelist<vir::Template<base_template, simd_abi::fixed_size<3>>,
		  vir::Template<base_template, simd_abi::fixed_size<6>>,
		  vir::Template<base_template, simd_abi::fixed_size<8>>,
		  vir::Template<base_template, simd_abi::fixed_size<12>>>),
  VIR_CHOOSE_ONE_RANDOMLY(
    vir::Typelist<vir::Template<base_template, simd_abi::fixed_size<1>>,
		  vir::Template<base_template, simd_abi::fixed_size<2>>,
		  vir::Template<base_template, simd_abi::fixed_size<4>>,
		  vir::Template<base_template, simd_abi::fixed_size<5>>,
		  vir::Template<base_template, simd_abi::fixed_size<7>>,
		  vir::Template<base_template, simd_abi::fixed_size<9>>,
		  vir::Template<base_template, simd_abi::fixed_size<10>>,
		  vir::Template<base_template, simd_abi::fixed_size<11>>,
		  vir::Template<base_template, simd_abi::fixed_size<13>>,
		  vir::Template<base_template, simd_abi::fixed_size<14>>,
		  vir::Template<base_template, simd_abi::fixed_size<15>>>),
  VIR_CHOOSE_ONE_RANDOMLY(
    vir::Typelist<vir::Template<base_template, simd_abi::fixed_size<16>>,
		  vir::Template<base_template, simd_abi::fixed_size<31>>,
		  vir::Template<base_template, simd_abi::fixed_size<32>>>)
#elif ABITYPES >= 1 && ABITYPES <= 8
  vir::Template<base_template, simd_abi::fixed_size<ABITYPES>>,
  vir::Template<base_template, simd_abi::fixed_size<8 + ABITYPES>>,
  vir::Template<base_template, simd_abi::fixed_size<16 + ABITYPES>>,
  vir::Template<base_template, simd_abi::fixed_size<24 + ABITYPES>>
#else
    vir::Typelist<>
#endif
  >;

// all_test_types {{{1
using all_test_types
  = vir::concat<native_test_types,
		vir::expand_list<fixed_size_abi_list, testtypes>>;

// real_test_types {{{1
using real_test_types
  = vir::concat<native_real_test_types,
		vir::expand_list<fixed_size_abi_list, testtypes_fp>>;

// many_fixed_size_types {{{1
using many_fixed_size_types = vir::expand_one<
  vir::Template<base_template>,
  vir::outer_product<
    testtypes_float,
    vir::Typelist<simd_abi::fixed_size<3>, simd_abi::fixed_size<4>,
		  simd_abi::fixed_size<5>, simd_abi::fixed_size<6>,
		  simd_abi::fixed_size<7>, simd_abi::fixed_size<8>,
		  simd_abi::fixed_size<9>, simd_abi::fixed_size<10>,
		  simd_abi::fixed_size<11>, simd_abi::fixed_size<12>,
		  simd_abi::fixed_size<13>, simd_abi::fixed_size<14>,
		  simd_abi::fixed_size<15>, simd_abi::fixed_size<17>>>>;

// reduced_test_types {{{1
#if _GLIBCXX_SIMD_HAVE_AVX512F
// reduce compile times when AVX512 is available
using reduced_test_types = native_test_types;
#else  // _GLIBCXX_SIMD_HAVE_AVX512F
typedef vir::concat<
  native_test_types,
  vir::expand_list<
    vir::Typelist<vir::Template<base_template, simd_abi::scalar>>, testtypes>>
  reduced_test_types;
#endif // _GLIBCXX_SIMD_HAVE_AVX512F

//}}}1
#endif // TESTS_TESTTYPES_H_

// vim: foldmethod=marker
