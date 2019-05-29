#ifndef _GLIBCXX_EXPERIMENTAL_SIMD
#define _GLIBCXX_EXPERIMENTAL_SIMD 
#define __cpp_lib_experimental_parallel_simd 201803
#if defined __GNUC__ && __GNUC__ < 9
#define __gnu__ gnu
#endif
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpsabi"
#ifndef _GLIBCXX_EXPERIMENTAL_SIMD_DETAIL_H_
#define _GLIBCXX_EXPERIMENTAL_SIMD_DETAIL_H_ 
#if __cplusplus >= 201703L
#include <cstddef>
#include <cstdint>
#define Vir_SIMD_VERSION_STRING "1.0.0"
#define _GLIBCXX_SIMD_BEGIN_NAMESPACE \
namespace std _GLIBCXX_VISIBILITY(default) \
{ \
_GLIBCXX_BEGIN_NAMESPACE_VERSION namespace experimental \
{ \
inline namespace parallelism_v2 \
{
#define _GLIBCXX_SIMD_END_NAMESPACE \
} \
} \
_GLIBCXX_END_NAMESPACE_VERSION \
}
_GLIBCXX_SIMD_BEGIN_NAMESPACE
namespace simd_abi
{
struct _ScalarAbi;
template <int _N> struct _FixedAbi;
template <int _Bytes = 16> struct _SseAbi;
template <int _Bytes = 32> struct _AvxAbi;
template <int _Bytes = 64> struct _Avx512Abi;
template <int _Bytes = 16> struct _NeonAbi;
template <int _N, class _Abi> struct _CombineAbi;
template <int _NRegisters> using __sse_x = _CombineAbi<_NRegisters, _SseAbi<>>;
template <int _NRegisters> using __avx_x = _CombineAbi<_NRegisters, _AvxAbi<>>;
template <int _NRegisters> using __avx512_x = _CombineAbi<_NRegisters, _Avx512Abi<>>;
template <int _NRegisters> using __neon_x = _CombineAbi<_NRegisters, _NeonAbi<>>;
template <class _Tp, int _N> using __sse_n = _SseAbi<sizeof(_Tp) * _N>;
template <class _Tp, int _N> using __avx_n = _AvxAbi<sizeof(_Tp) * _N>;
template <class _Tp, int _N> using __avx512_n = _Avx512Abi<sizeof(_Tp) * _N>;
template <class _Tp, int _N> using __neon_n = _NeonAbi<sizeof(_Tp) * _N>;
using __sse = _SseAbi<>;
using __avx = _AvxAbi<>;
using __avx512 = _Avx512Abi<>;
using __neon = _NeonAbi<>;
using __neon128 = _NeonAbi<16>;
using __neon64 = _NeonAbi<8>;
template <class _Tp, size_t _N, class... > struct deduce;
template <int _N> using fixed_size = _FixedAbi<_N>;
using scalar = _ScalarAbi;
}
template <class _Tp> struct is_simd;
template <class _Tp> struct is_simd_mask;
template <class _Tp, class _Abi> class simd;
template <class _Tp, class _Abi> class simd_mask;
template <class _Tp, class _Abi> struct simd_size;
#ifdef WIN32
#define NOMINMAX 1
#if defined min
#undef min
#endif
#if defined max
#undef max
#endif
#endif
#ifdef __aarch64__
#define _GLIBCXX_SIMD_IS_AARCH64 1
#endif
#ifdef __ARM_NEON
#define _GLIBCXX_SIMD_HAVE_NEON 1
#define _GLIBCXX_SIMD_HAVE_NEON_ABI 1
#define _GLIBCXX_SIMD_HAVE_FULL_NEON_ABI 1
#else
#define _GLIBCXX_SIMD_HAVE_NEON 0
#define _GLIBCXX_SIMD_HAVE_NEON_ABI 0
#define _GLIBCXX_SIMD_HAVE_FULL_NEON_ABI 0
#endif
#ifdef __MMX__
#define _GLIBCXX_SIMD_HAVE_MMX 1
#else
#define _GLIBCXX_SIMD_HAVE_MMX 0
#endif
#if defined __SSE__ || defined __x86_64__
#define _GLIBCXX_SIMD_HAVE_SSE 1
#else
#define _GLIBCXX_SIMD_HAVE_SSE 0
#endif
#if defined __SSE2__ || defined __x86_64__
#define _GLIBCXX_SIMD_HAVE_SSE2 1
#else
#define _GLIBCXX_SIMD_HAVE_SSE2 0
#endif
#ifdef __SSE3__
#define _GLIBCXX_SIMD_HAVE_SSE3 1
#else
#define _GLIBCXX_SIMD_HAVE_SSE3 0
#endif
#ifdef __SSSE3__
#define _GLIBCXX_SIMD_HAVE_SSSE3 1
#else
#define _GLIBCXX_SIMD_HAVE_SSSE3 0
#endif
#ifdef __SSE4_1__
#define _GLIBCXX_SIMD_HAVE_SSE4_1 1
#else
#define _GLIBCXX_SIMD_HAVE_SSE4_1 0
#endif
#ifdef __SSE4_2__
#define _GLIBCXX_SIMD_HAVE_SSE4_2 1
#else
#define _GLIBCXX_SIMD_HAVE_SSE4_2 0
#endif
#ifdef __XOP__
#define _GLIBCXX_SIMD_HAVE_XOP 1
#else
#define _GLIBCXX_SIMD_HAVE_XOP 0
#endif
#ifdef __AVX__
#define _GLIBCXX_SIMD_HAVE_AVX 1
#else
#define _GLIBCXX_SIMD_HAVE_AVX 0
#endif
#ifdef __AVX2__
#define _GLIBCXX_SIMD_HAVE_AVX2 1
#else
#define _GLIBCXX_SIMD_HAVE_AVX2 0
#endif
#ifdef __BMI__
#define _GLIBCXX_SIMD_HAVE_BMI1 1
#else
#define _GLIBCXX_SIMD_HAVE_BMI1 0
#endif
#ifdef __BMI2__
#define _GLIBCXX_SIMD_HAVE_BMI2 1
#else
#define _GLIBCXX_SIMD_HAVE_BMI2 0
#endif
#ifdef __LZCNT__
#define _GLIBCXX_SIMD_HAVE_LZCNT 1
#else
#define _GLIBCXX_SIMD_HAVE_LZCNT 0
#endif
#ifdef __SSE4A__
#define _GLIBCXX_SIMD_HAVE_SSE4A 1
#else
#define _GLIBCXX_SIMD_HAVE_SSE4A 0
#endif
#ifdef __FMA__
#define _GLIBCXX_SIMD_HAVE_FMA 1
#else
#define _GLIBCXX_SIMD_HAVE_FMA 0
#endif
#ifdef __FMA4__
#define _GLIBCXX_SIMD_HAVE_FMA4 1
#else
#define _GLIBCXX_SIMD_HAVE_FMA4 0
#endif
#ifdef __F16C__
#define _GLIBCXX_SIMD_HAVE_F16C 1
#else
#define _GLIBCXX_SIMD_HAVE_F16C 0
#endif
#ifdef __POPCNT__
#define _GLIBCXX_SIMD_HAVE_POPCNT 1
#else
#define _GLIBCXX_SIMD_HAVE_POPCNT 0
#endif
#ifdef __AVX512F__
#define _GLIBCXX_SIMD_HAVE_AVX512F 1
#else
#define _GLIBCXX_SIMD_HAVE_AVX512F 0
#endif
#ifdef __AVX512DQ__
#define _GLIBCXX_SIMD_HAVE_AVX512DQ 1
#else
#define _GLIBCXX_SIMD_HAVE_AVX512DQ 0
#endif
#ifdef __AVX512VL__
#define _GLIBCXX_SIMD_HAVE_AVX512VL 1
#else
#define _GLIBCXX_SIMD_HAVE_AVX512VL 0
#endif
#ifdef __AVX512BW__
#define _GLIBCXX_SIMD_HAVE_AVX512BW 1
#else
#define _GLIBCXX_SIMD_HAVE_AVX512BW 0
#endif
#if _GLIBCXX_SIMD_HAVE_SSE
#define _GLIBCXX_SIMD_HAVE_SSE_ABI 1
#else
#define _GLIBCXX_SIMD_HAVE_SSE_ABI 0
#endif
#if _GLIBCXX_SIMD_HAVE_SSE2
#define _GLIBCXX_SIMD_HAVE_FULL_SSE_ABI 1
#else
#define _GLIBCXX_SIMD_HAVE_FULL_SSE_ABI 0
#endif
#if _GLIBCXX_SIMD_HAVE_AVX
#define _GLIBCXX_SIMD_HAVE_AVX_ABI 1
#else
#define _GLIBCXX_SIMD_HAVE_AVX_ABI 0
#endif
#if _GLIBCXX_SIMD_HAVE_AVX2
#define _GLIBCXX_SIMD_HAVE_FULL_AVX_ABI 1
#else
#define _GLIBCXX_SIMD_HAVE_FULL_AVX_ABI 0
#endif
#if _GLIBCXX_SIMD_HAVE_AVX512F
#define _GLIBCXX_SIMD_HAVE_AVX512_ABI 1
#else
#define _GLIBCXX_SIMD_HAVE_AVX512_ABI 0
#endif
#if _GLIBCXX_SIMD_HAVE_AVX512BW
#define _GLIBCXX_SIMD_HAVE_FULL_AVX512_ABI 1
#else
#define _GLIBCXX_SIMD_HAVE_FULL_AVX512_ABI 0
#endif
#if defined __x86_64__ && !_GLIBCXX_SIMD_HAVE_SSE2
#error "Use of SSE2 is required on AMD64"
#endif
#define _GLIBCXX_SIMD_NORMAL_MATH [[gnu::__optimize__("finite-math-only,no-signed-zeros")]]
#define _GLIBCXX_SIMD_NEVER_INLINE [[gnu::__noinline__]]
#define _GLIBCXX_SIMD_INTRINSIC [[gnu::__always_inline__, gnu::__artificial__]] inline
#define _GLIBCXX_SIMD_CONST __attribute__((__const__))
#define _GLIBCXX_SIMD_PURE __attribute__((__pure__))
#define _GLIBCXX_SIMD_ALWAYS_INLINE [[gnu::__always_inline__]] inline
#define _GLIBCXX_SIMD_IS_UNLIKELY(__x) __builtin_expect(__x, 0)
#define _GLIBCXX_SIMD_IS_LIKELY(__x) __builtin_expect(__x, 1)
#ifdef COMPILE_FOR_UNIT_TESTS
#define _GLIBCXX_SIMD_NOEXCEPT_OR_IN_TEST 
#else
#define _GLIBCXX_SIMD_NOEXCEPT_OR_IN_TEST noexcept
#endif
#define _GLIBCXX_SIMD_LIST_BINARY(macro) macro(|) macro(&) macro(^)
#define _GLIBCXX_SIMD_LIST_SHIFTS(macro) macro(<<) macro(>>)
#define _GLIBCXX_SIMD_LIST_ARITHMETICS(macro) macro(+) macro(-) macro(*) macro(/) macro(%)
#define _GLIBCXX_SIMD_ALL_BINARY(macro) _GLIBCXX_SIMD_LIST_BINARY(macro) static_assert(true)
#define _GLIBCXX_SIMD_ALL_SHIFTS(macro) _GLIBCXX_SIMD_LIST_SHIFTS(macro) static_assert(true)
#define _GLIBCXX_SIMD_ALL_ARITHMETICS(macro) _GLIBCXX_SIMD_LIST_ARITHMETICS(macro) static_assert(true)
#ifdef _GLIBCXX_SIMD_NO_ALWAYS_INLINE
#undef _GLIBCXX_SIMD_ALWAYS_INLINE
#define _GLIBCXX_SIMD_ALWAYS_INLINE inline
#undef _GLIBCXX_SIMD_INTRINSIC
#define _GLIBCXX_SIMD_INTRINSIC inline
#endif
#if _GLIBCXX_SIMD_HAVE_SSE || _GLIBCXX_SIMD_HAVE_MMX
#define _GLIBCXX_SIMD_X86INTRIN 1
#else
#define _GLIBCXX_SIMD_X86INTRIN 0
#endif
#define _GLIBCXX_SIMD_USE_ALIASING_LOADS 1
#if _GLIBCXX_SIMD_X86INTRIN
#define _GLIBCXX_SIMD_WORKAROUND_PR85048 1
#endif
#if __GNUC__ < 9
#define _GLIBCXX_SIMD_WORKAROUND_PR85480 1
#endif
#define _GLIBCXX_SIMD_WORKAROUND_PR85538 1
#if _GLIBCXX_SIMD_X86INTRIN
#define _GLIBCXX_SIMD_WORKAROUND_XXX_1 1
#endif
#define _GLIBCXX_SIMD_WORKAROUND_PR90424 1
#if _GLIBCXX_SIMD_X86INTRIN
#define _GLIBCXX_SIMD_WORKAROUND_XXX_3 1
#endif
#define _GLIBCXX_SIMD_WORKAROUND_XXX_4 1
#define _GLIBCXX_SIMD_FIX_P2TS_ISSUE65 1
#define _GLIBCXX_SIMD_FIX_P2TS_ISSUE66 1
_GLIBCXX_SIMD_END_NAMESPACE
#endif
#endif
#ifndef _GLIBCXX_EXPERIMENTAL_SIMD_H
#define _GLIBCXX_EXPERIMENTAL_SIMD_H 
#if __cplusplus >= 201703L
#include <bitset>
#include <climits>
#include <cstring>
#include <functional>
#include <iosfwd>
#include <limits>
#include <utility>
#if _GLIBCXX_SIMD_X86INTRIN
#include <x86intrin.h>
#elif _GLIBCXX_SIMD_HAVE_NEON
#include <arm_neon.h>
#endif
_GLIBCXX_SIMD_BEGIN_NAMESPACE
#if __GNUC__ < 9
template <typename T>
using __remove_cvref_t = std::remove_const_t<std::remove_reference_t<T>>;
constexpr bool __builtin_is_constant_evaluated() { return false; }
#endif
#if !_GLIBCXX_SIMD_X86INTRIN
using __m128 [[__gnu__::__vector_size__(16)]] = float;
using __m128d [[__gnu__::__vector_size__(16)]] = double;
using __m128i [[__gnu__::__vector_size__(16)]] = long long;
using __m256 [[__gnu__::__vector_size__(32)]] = float;
using __m256d [[__gnu__::__vector_size__(32)]] = double;
using __m256i [[__gnu__::__vector_size__(32)]] = long long;
using __m512 [[__gnu__::__vector_size__(64)]] = float;
using __m512d [[__gnu__::__vector_size__(64)]] = double;
using __m512i [[__gnu__::__vector_size__(64)]] = long long;
#endif
struct element_aligned_tag {};
struct vector_aligned_tag {};
template <size_t _N>
struct overaligned_tag
{
static constexpr size_t _S_alignment = _N;
};
inline constexpr element_aligned_tag element_aligned = {};
inline constexpr vector_aligned_tag vector_aligned = {};
template <size_t _N>
inline constexpr overaligned_tag<_N> overaligned = {};
using _UChar = unsigned char;
using _SChar = signed char;
using _UShort = unsigned short;
using _UInt = unsigned int;
using _ULong = unsigned long;
using _ULLong = unsigned long long;
using _LLong = long long;
template <typename _Tp, _Tp __a, _Tp __b>
struct __is_equal : public false_type
{
};
template <typename _Tp, _Tp __a>
struct __is_equal<_Tp, __a, __a> : public true_type
{
};
template <typename _Tp>
struct __identity
{
using type = _Tp;
};
template <typename _Tp>
using __id = typename __identity<_Tp>::type;
template <typename _T0, typename...>
struct __first_of_pack
{
using type = _T0;
};
template <typename... _Ts>
using __first_of_pack_t = typename __first_of_pack<_Ts...>::type;
template <typename _Tp>
typename _Tp::value_type __value_type_or_identity_impl(int);
template <typename _Tp>
_Tp __value_type_or_identity_impl(float);
template <typename _Tp>
using __value_type_or_identity_t =
decltype(__value_type_or_identity_impl<_Tp>(int()));
template <typename _Tp>
struct __is_vectorizable : public std::is_arithmetic<_Tp>
{
};
template <>
struct __is_vectorizable<bool> : public false_type
{
};
template <typename _Tp>
inline constexpr bool __is_vectorizable_v = __is_vectorizable<_Tp>::value;
template <typename _Tp, typename = enable_if_t<__is_vectorizable_v<_Tp>>>
using _Vectorizable = _Tp;
template <typename _Ptr, typename _ValueType>
struct __is_possible_loadstore_conversion
: conjunction<__is_vectorizable<_Ptr>, __is_vectorizable<_ValueType>> {
};
template <> struct __is_possible_loadstore_conversion<bool, bool> : true_type {
};
template <typename _Ptr, typename _ValueType,
typename = enable_if_t<__is_possible_loadstore_conversion<_Ptr, _ValueType>::value>>
using _LoadStorePtr = _Ptr;
template <size_t _X> using _SizeConstant = integral_constant<size_t, _X>;
template <typename _Tp, typename = std::void_t<>>
struct __is_bitmask : false_type
{
constexpr __is_bitmask(const _Tp&) noexcept {}
};
template <typename _Tp>
inline constexpr bool __is_bitmask_v = __is_bitmask<_Tp>::value;
template <typename _Tp>
struct __is_bitmask<
_Tp,
std::void_t<decltype(std::declval<unsigned&>() = std::declval<_Tp>() & 1u)>>
: true_type
{
constexpr __is_bitmask(const _Tp&) noexcept {}
};
template <size_t> struct __int_for_sizeof;
template <> struct __int_for_sizeof<1> { using type = signed char; };
template <> struct __int_for_sizeof<2> { using type = signed short; };
template <> struct __int_for_sizeof<4> { using type = signed int; };
template <> struct __int_for_sizeof<8> { using type = signed long long; };
#ifdef __SIZEOF_INT128__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpedantic"
template <> struct __int_for_sizeof<16> { using type = __int128; };
#pragma GCC diagnostic pop
#endif
template <typename _Tp>
using __int_for_sizeof_t = typename __int_for_sizeof<sizeof(_Tp)>::type;
template <size_t _N>
using __int_with_sizeof_t = typename __int_for_sizeof<_N>::type;
template <typename _Tp>
struct __is_fixed_size_abi : false_type
{
};
template <int _N>
struct __is_fixed_size_abi<simd_abi::fixed_size<_N>> : true_type
{
};
template <typename _Tp>
inline constexpr bool __is_fixed_size_abi_v = __is_fixed_size_abi<_Tp>::value;
constexpr inline bool __have_mmx = _GLIBCXX_SIMD_HAVE_MMX;
constexpr inline bool __have_sse = _GLIBCXX_SIMD_HAVE_SSE;
constexpr inline bool __have_sse2 = _GLIBCXX_SIMD_HAVE_SSE2;
constexpr inline bool __have_sse3 = _GLIBCXX_SIMD_HAVE_SSE3;
constexpr inline bool __have_ssse3 = _GLIBCXX_SIMD_HAVE_SSSE3;
constexpr inline bool __have_sse4_1 = _GLIBCXX_SIMD_HAVE_SSE4_1;
constexpr inline bool __have_sse4_2 = _GLIBCXX_SIMD_HAVE_SSE4_2;
constexpr inline bool __have_xop = _GLIBCXX_SIMD_HAVE_XOP;
constexpr inline bool __have_avx = _GLIBCXX_SIMD_HAVE_AVX;
constexpr inline bool __have_avx2 = _GLIBCXX_SIMD_HAVE_AVX2;
constexpr inline bool __have_bmi = _GLIBCXX_SIMD_HAVE_BMI1;
constexpr inline bool __have_bmi2 = _GLIBCXX_SIMD_HAVE_BMI2;
constexpr inline bool __have_lzcnt = _GLIBCXX_SIMD_HAVE_LZCNT;
constexpr inline bool __have_sse4a = _GLIBCXX_SIMD_HAVE_SSE4A;
constexpr inline bool __have_fma = _GLIBCXX_SIMD_HAVE_FMA;
constexpr inline bool __have_fma4 = _GLIBCXX_SIMD_HAVE_FMA4;
constexpr inline bool __have_f16c = _GLIBCXX_SIMD_HAVE_F16C;
constexpr inline bool __have_popcnt = _GLIBCXX_SIMD_HAVE_POPCNT;
constexpr inline bool __have_avx512f = _GLIBCXX_SIMD_HAVE_AVX512F;
constexpr inline bool __have_avx512dq = _GLIBCXX_SIMD_HAVE_AVX512DQ;
constexpr inline bool __have_avx512vl = _GLIBCXX_SIMD_HAVE_AVX512VL;
constexpr inline bool __have_avx512bw = _GLIBCXX_SIMD_HAVE_AVX512BW;
constexpr inline bool __have_avx512dq_vl = __have_avx512dq && __have_avx512vl;
constexpr inline bool __have_avx512bw_vl = __have_avx512bw && __have_avx512vl;
constexpr inline bool __have_neon = _GLIBCXX_SIMD_HAVE_NEON;
template <template <int> class _Abi, int _Bytes>
constexpr int __abi_bytes_impl(_Abi<_Bytes>*)
{
return _Bytes;
}
template <typename _Tp>
constexpr int __abi_bytes_impl(_Tp*)
{
return -1;
}
template <typename _Abi>
inline constexpr int
__abi_bytes_v = __abi_bytes_impl(static_cast<_Abi*>(nullptr));
template <typename _Abi0, typename _Abi1>
constexpr bool __is_abi()
{
return std::is_same_v<_Abi0, _Abi1>;
}
template <template <int> class _Abi0, typename _Abi1>
constexpr bool __is_abi()
{
return std::is_same_v<_Abi0<__abi_bytes_v<_Abi1>>, _Abi1>;
}
template <typename _Abi0, template <int> class _Abi1>
constexpr bool __is_abi()
{
return std::is_same_v<_Abi1<__abi_bytes_v<_Abi0>>, _Abi0>;
}
template <template <int> class _Abi0, template <int> class _Abi1>
constexpr bool __is_abi()
{
return std::is_same_v<_Abi0<0>, _Abi1<0>>;
}
template <template <int, typename> class _Combine, int _N, typename _Abi>
constexpr bool __is_combined_abi(_Combine<_N, _Abi>*)
{
return std::is_same_v<_Combine<_N, _Abi>, simd_abi::_CombineAbi<_N, _Abi>>;
}
template <typename _Abi>
constexpr bool __is_combined_abi(_Abi*)
{
return false;
}
template <typename _Abi>
constexpr bool __is_combined_abi()
{
return __is_combined_abi(static_cast<_Abi*>(nullptr));
}
template <typename _Tp>
static constexpr void __unused(_Tp&&)
{
}
template <typename _Tp>
struct __assert_unreachable
{
static_assert(!std::is_same_v<_Tp, _Tp>, "this should be unreachable");
};
template <typename _Tp, typename _A, size_t _N = simd_size<_Tp, _A>::value>
constexpr size_t __size_or_zero_dispatch(int)
{
return _N;
}
template <typename _Tp, typename _A>
constexpr size_t __size_or_zero_dispatch(float)
{
return 0;
}
template <typename _Tp, typename _A>
inline constexpr size_t __size_or_zero_v = __size_or_zero_dispatch<_Tp, _A>(0);
template <typename _To, typename _From>
_GLIBCXX_SIMD_INTRINSIC _To __bit_cast(const _From __x)
{
static_assert(sizeof(_To) == sizeof(_From));
_To __r;
std::memcpy(&__r, &__x, sizeof(_To));
return __r;
}
template <typename _Tp>
_GLIBCXX_SIMD_INTRINSIC constexpr const _Tp&
__promote_preserving_unsigned(const _Tp& __x)
{
return __x;
}
_GLIBCXX_SIMD_INTRINSIC constexpr unsigned int
__promote_preserving_unsigned(const unsigned char& __x)
{
return __x;
}
_GLIBCXX_SIMD_INTRINSIC constexpr unsigned int
__promote_preserving_unsigned(const unsigned short& __x)
{
return __x;
}
class _ExactBool
{
const bool _M_data;
public:
_GLIBCXX_SIMD_INTRINSIC constexpr _ExactBool(bool __b)
: _M_data(__b)
{
}
_ExactBool(int) = delete;
_GLIBCXX_SIMD_INTRINSIC constexpr operator bool() const { return _M_data; }
};
template <typename _F, size_t... _I>
_GLIBCXX_SIMD_INTRINSIC constexpr void
__execute_on_index_sequence(_F&& __f, std::index_sequence<_I...>)
{
auto&& __x = {(__f(_SizeConstant<_I>()), 0)...};
__unused(__x);
}
template <typename _F>
_GLIBCXX_SIMD_INTRINSIC constexpr void
__execute_on_index_sequence(_F&&, std::index_sequence<>)
{
}
template <typename _R, typename _F, size_t... _I>
_GLIBCXX_SIMD_INTRINSIC constexpr _R
__execute_on_index_sequence_with_return(_F&& __f, std::index_sequence<_I...>)
{
return _R{__f(_SizeConstant<_I>())...};
}
template <size_t _N, typename _F>
_GLIBCXX_SIMD_INTRINSIC constexpr void __execute_n_times(_F&& __f)
{
__execute_on_index_sequence(std::forward<_F>(__f),
std::make_index_sequence<_N>{});
}
template <size_t _N, typename _R, typename _F>
_GLIBCXX_SIMD_INTRINSIC constexpr _R __generate_from_n_evaluations(_F&& __f)
{
return __execute_on_index_sequence_with_return<_R>(
std::forward<_F>(__f), std::make_index_sequence<_N>{});
}
template <size_t... _It, typename _Tp, typename _F>
_GLIBCXX_SIMD_INTRINSIC auto
__call_with_subscripts(_Tp&& __x, index_sequence<_It...>, _F&& __fun)
{
return __fun(__x[_It]...);
}
template <typename _Tp> using __may_alias [[__gnu__::__may_alias__]] = _Tp;
struct _UnsupportedBase
{
_UnsupportedBase() = delete;
_UnsupportedBase(const _UnsupportedBase&) = delete;
_UnsupportedBase& operator=(const _UnsupportedBase&) = delete;
~_UnsupportedBase() = delete;
};
struct _InvalidTraits
{
using _IsValid = false_type;
using _SimdBase = _UnsupportedBase;
using _MaskBase = _UnsupportedBase;
static constexpr size_t _S_simd_align = 1;
struct _SimdImpl;
struct _SimdMember {};
struct _SimdCastType;
static constexpr size_t _S_mask_align = 1;
struct _MaskImpl;
struct _MaskMember {};
struct _MaskCastType;
};
template <typename _Tp, typename _Abi, typename = std::void_t<>>
struct _SimdTraits : _InvalidTraits
{
};
template <typename _Tp>
struct __get_impl;
template <typename _Tp>
using __get_impl_t = typename __get_impl<__remove_cvref_t<_Tp>>::_Impl;
template <typename _Tp>
using __get_traits_t = typename __get_impl<__remove_cvref_t<_Tp>>::_Traits;
constexpr std::size_t __next_power_of_2(std::size_t __x)
{
return (__x & (__x - 1)) == 0 ? __x
: __next_power_of_2((__x | (__x >> 1)) + 1);
}
inline constexpr struct _PrivateInit {} __private_init = {};
inline constexpr struct _BitsetInit {} __bitset_init = {};
template <typename _From,
typename _To,
bool = std::is_arithmetic<_From>::value,
bool = std::is_arithmetic<_To>::value>
struct __is_narrowing_conversion;
template <typename _From, typename _To>
struct __is_narrowing_conversion<_From, _To, true, true>
: public __bool_constant<(
std::numeric_limits<_From>::digits > std::numeric_limits<_To>::digits ||
std::numeric_limits<_From>::max() > std::numeric_limits<_To>::max() ||
std::numeric_limits<_From>::lowest() < std::numeric_limits<_To>::lowest() ||
(std::is_signed<_From>::value && std::is_unsigned<_To>::value))>
{
};
template <typename _Tp>
struct __is_narrowing_conversion<bool, _Tp, true, true> : public true_type
{
};
template <>
struct __is_narrowing_conversion<bool, bool, true, true> : public false_type
{
};
template <typename _Tp>
struct __is_narrowing_conversion<_Tp, _Tp, true, true> : public false_type
{
};
template <typename _From, typename _To>
struct __is_narrowing_conversion<_From, _To, false, true>
: public negation<std::is_convertible<_From, _To>>
{
};
template <typename _From, typename _To, bool = (sizeof(_From) < sizeof(_To))>
struct __converts_to_higher_integer_rank : public true_type
{
};
template <typename _From, typename _To>
struct __converts_to_higher_integer_rank<_From, _To, false>
: public std::is_same<decltype(std::declval<_From>() + std::declval<_To>()),
_To>
{
};
template <typename _Flag, size_t _Alignment>
struct __is_aligned;
template <size_t _Alignment>
struct __is_aligned<vector_aligned_tag, _Alignment> : public true_type
{
};
template <size_t _Alignment>
struct __is_aligned<element_aligned_tag, _Alignment> : public false_type
{
};
template <size_t _GivenAlignment, size_t _Alignment>
struct __is_aligned<overaligned_tag<_GivenAlignment>, _Alignment>
: public std::integral_constant<bool, (_GivenAlignment >= _Alignment)>
{
};
template <typename _Flag, size_t _Alignment>
inline constexpr bool __is_aligned_v = __is_aligned<_Flag, _Alignment>::value;
template <typename _Tp, typename _A>
_GLIBCXX_SIMD_INTRINSIC constexpr const auto& __data(const simd<_Tp, _A>& __x);
template <typename _Tp, typename _A>
_GLIBCXX_SIMD_INTRINSIC constexpr auto& __data(simd<_Tp, _A>& __x);
template <typename _Tp, typename _A>
_GLIBCXX_SIMD_INTRINSIC constexpr const auto&
__data(const simd_mask<_Tp, _A>& __x);
template <typename _Tp, typename _A>
_GLIBCXX_SIMD_INTRINSIC constexpr auto& __data(simd_mask<_Tp, _A>& __x);
template <typename _FromT, typename _FromA, typename _ToT, typename _ToA>
struct _SimdConverter;
template <typename _Tp, typename _A>
struct _SimdConverter<_Tp, _A, _Tp, _A>
{
template <typename _U>
_GLIBCXX_SIMD_INTRINSIC const _U& operator()(const _U& __x)
{
return __x;
}
};
template <typename _V>
_GLIBCXX_SIMD_INTRINSIC constexpr auto
__to_value_type_or_member_type(const _V& __x) -> decltype(__data(__x))
{
return __data(__x);
}
template <typename _V>
_GLIBCXX_SIMD_INTRINSIC constexpr const typename _V::value_type&
__to_value_type_or_member_type(const typename _V::value_type& __x)
{
return __x;
}
template <size_t _Size>
struct __bool_storage_member_type;
template <size_t _Size>
using __bool_storage_member_type_t =
typename __bool_storage_member_type<_Size>::type;
template <typename _Tp, typename... _Abis> struct _SimdTuple;
template <typename _Tp, int _N>
struct __fixed_size_storage;
template <typename _Tp, int _N>
using __fixed_size_storage_t = typename __fixed_size_storage<_Tp, _N>::type;
template <typename _Tp, size_t _Size, typename = std::void_t<>>
struct _SimdWrapper;
template <typename _Tp>
using _SimdWrapper8 = _SimdWrapper<_Tp, 8 / sizeof(_Tp)>;
template <typename _Tp>
using _SimdWrapper16 = _SimdWrapper<_Tp, 16 / sizeof(_Tp)>;
template <typename _Tp>
using _SimdWrapper32 = _SimdWrapper<_Tp, 32 / sizeof(_Tp)>;
template <typename _Tp>
using _SimdWrapper64 = _SimdWrapper<_Tp, 64 / sizeof(_Tp)>;
constexpr _UInt __popcount(_UInt __x) { return __builtin_popcount(__x); }
constexpr _ULong __popcount(_ULong __x) { return __builtin_popcountl(__x); }
constexpr _ULLong __popcount(_ULLong __x) { return __builtin_popcountll(__x); }
constexpr _UInt __ctz(_UInt __x) { return __builtin_ctz(__x); }
constexpr _ULong __ctz(_ULong __x) { return __builtin_ctzl(__x); }
constexpr _ULLong __ctz(_ULLong __x) { return __builtin_ctzll(__x); }
constexpr _UInt __clz(_UInt __x) { return __builtin_clz(__x); }
constexpr _ULong __clz(_ULong __x) { return __builtin_clzl(__x); }
constexpr _ULLong __clz(_ULLong __x) { return __builtin_clzll(__x); }
template <typename _Tp, typename _F>
void __bit_iteration(_Tp __mask, _F&& __f)
{
static_assert(sizeof(_ULLong) >= sizeof(_Tp));
std::conditional_t<sizeof(_Tp) <= sizeof(_UInt), _UInt, _ULLong> __k;
if constexpr (std::is_convertible_v<_Tp, decltype(__k)>) {
__k = __mask;
} else {
__k = __mask.to_ullong();
}
switch (__popcount(__k)) {
default:
do {
__f(__ctz(__k));
__k &= (__k - 1);
} while (__k);
break;
case 2:
__f(__ctz(__k));
[[fallthrough]];
case 1:
__f(__popcount(~decltype(__k)()) - 1 - __clz(__k));
[[fallthrough]];
case 0:
break;
}
}
template <typename _Tp>
_GLIBCXX_SIMD_INTRINSIC _GLIBCXX_SIMD_CONST auto __firstbit(_Tp __bits)
{
static_assert(std::is_integral_v<_Tp>,
"__firstbit requires an integral argument");
if constexpr (sizeof(_Tp) <= sizeof(int))
{
return __builtin_ctz(__bits);
}
else if constexpr (alignof(_ULLong) == 8)
{
return __builtin_ctzll(__bits);
}
else
{
_UInt __lo = __bits;
return __lo == 0 ? 32 + __builtin_ctz(__bits >> 32) : __builtin_ctz(__lo);
}
}
template <typename _Tp>
_GLIBCXX_SIMD_INTRINSIC _GLIBCXX_SIMD_CONST auto __lastbit(_Tp __bits)
{
static_assert(std::is_integral_v<_Tp>,
"__firstbit requires an integral argument");
if constexpr (sizeof(_Tp) <= sizeof(int))
{
return 31 - __builtin_clz(__bits);
}
else if constexpr (alignof(_ULLong) == 8)
{
return 63 - __builtin_clzll(__bits);
}
else
{
_UInt __lo = __bits;
_UInt __hi = __bits >> 32u;
return __hi == 0 ? 31 - __builtin_clz(__lo) : 63 - __builtin_clz(__hi);
}
}
template <typename _To, typename _From>
inline _To __convert_mask(_From __k);
template <typename _Tp = void>
struct __shift_left
{
constexpr _Tp operator()(const _Tp& __a, const _Tp& __b) const
{
return __a << __b;
}
};
template <>
struct __shift_left<void>
{
template <typename _L, typename _R>
constexpr auto operator()(_L&& __a, _R&& __b) const
{
return std::forward<_L>(__a) << std::forward<_R>(__b);
}
};
template <typename _Tp = void>
struct __shift_right
{
constexpr _Tp operator()(const _Tp& __a, const _Tp& __b) const
{
return __a >> __b;
}
};
template <>
struct __shift_right<void>
{
template <typename _L, typename _R>
constexpr auto operator()(_L&& __a, _R&& __b) const
{
return std::forward<_L>(__a) >> std::forward<_R>(__b);
}
};
template <typename _Tp = void>
struct __increment
{
constexpr _Tp operator()(_Tp __a) const { return ++__a; }
};
template <>
struct __increment<void>
{
template <typename _Tp>
constexpr _Tp operator()(_Tp __a) const
{
return ++__a;
}
};
template <typename _Tp = void>
struct __decrement
{
constexpr _Tp operator()(_Tp __a) const { return --__a; }
};
template <>
struct __decrement<void>
{
template <typename _Tp>
constexpr _Tp operator()(_Tp __a) const
{
return --__a;
}
};
template <typename _From,
typename _To,
typename = enable_if_t<negation<
__is_narrowing_conversion<__remove_cvref_t<_From>, _To>>::value>>
using _ValuePreserving = _From;
template <typename _From,
typename _To,
typename _DecayedFrom = __remove_cvref_t<_From>,
typename = enable_if_t<conjunction<
is_convertible<_From, _To>,
disjunction<
is_same<_DecayedFrom, _To>,
is_same<_DecayedFrom, int>,
conjunction<is_same<_DecayedFrom, _UInt>, is_unsigned<_To>>,
negation<__is_narrowing_conversion<_DecayedFrom, _To>>>>::value>>
using _ValuePreservingOrInt = _From;
template <typename _Tp, size_t _Bytes, typename = std::void_t<>> struct __intrinsic_type;
template <typename _Tp, size_t _Size>
using __intrinsic_type_t = typename __intrinsic_type<_Tp, _Size * sizeof(_Tp)>::type;
template <typename _Tp> using __intrinsic_type2_t = typename __intrinsic_type<_Tp, 2>::type;
template <typename _Tp> using __intrinsic_type4_t = typename __intrinsic_type<_Tp, 4>::type;
template <typename _Tp> using __intrinsic_type8_t = typename __intrinsic_type<_Tp, 8>::type;
template <typename _Tp> using __intrinsic_type16_t = typename __intrinsic_type<_Tp, 16>::type;
template <typename _Tp> using __intrinsic_type32_t = typename __intrinsic_type<_Tp, 32>::type;
template <typename _Tp> using __intrinsic_type64_t = typename __intrinsic_type<_Tp, 64>::type;
template <typename _Tp> using __intrinsic_type128_t = typename __intrinsic_type<_Tp, 128>::type;
static inline constexpr int __min_vector_size =
#if _GLIBCXX_SIMD_HAVE_NEON
8
#else
16
#endif
;
template <typename _Tp, size_t _N, typename = void> struct __vector_type_n {};
template <typename _Tp>
struct __vector_type_n<_Tp, 1, enable_if_t<__is_vectorizable_v<_Tp>>> {
using type = _Tp;
};
template <typename _Tp, size_t _N>
struct __vector_type_n<_Tp, _N, enable_if_t<__is_vectorizable_v<_Tp>>> {
static constexpr size_t _Bytes = __next_power_of_2(_N * sizeof(_Tp));
using type [[__gnu__::__vector_size__(_Bytes)]] = _Tp;
};
template <typename _Tp, size_t _Bytes>
struct __vector_type : __vector_type_n<_Tp, _Bytes / sizeof(_Tp)> {
static_assert(_Bytes % sizeof(_Tp) == 0);
};
template <typename _Tp, size_t _Size>
using __vector_type_t = typename __vector_type_n<_Tp, _Size>::type;
template <typename _Tp> using __vector_type2_t = typename __vector_type<_Tp, 2>::type;
template <typename _Tp> using __vector_type4_t = typename __vector_type<_Tp, 4>::type;
template <typename _Tp> using __vector_type8_t = typename __vector_type<_Tp, 8>::type;
template <typename _Tp> using __vector_type16_t = typename __vector_type<_Tp, 16>::type;
template <typename _Tp> using __vector_type32_t = typename __vector_type<_Tp, 32>::type;
template <typename _Tp> using __vector_type64_t = typename __vector_type<_Tp, 64>::type;
template <typename _Tp> using __vector_type128_t = typename __vector_type<_Tp, 128>::type;
template <typename _Tp, typename = std::void_t<>> struct __is_vector_type : false_type {};
template <typename _Tp>
struct __is_vector_type<
_Tp,
std::void_t<typename __vector_type<decltype(std::declval<_Tp>()[0]), sizeof(_Tp)>::type>>
: std::is_same<
_Tp, typename __vector_type<decltype(std::declval<_Tp>()[0]), sizeof(_Tp)>::type> {
};
template <typename _Tp>
inline constexpr bool __is_vector_type_v = __is_vector_type<_Tp>::value;
template <typename _Tp, typename = std::void_t<>>
struct _VectorTraits;
template <typename _Tp>
struct _VectorTraits<_Tp, std::void_t<enable_if_t<__is_vector_type_v<_Tp>>>>
{
using type = _Tp;
using value_type = decltype(std::declval<_Tp>()[0]);
static constexpr int _S_width = sizeof(_Tp) / sizeof(value_type);
template <typename _U, int _W = _S_width>
static constexpr bool __is = std::is_same_v<value_type, _U>&& _W == _S_width;
};
template <typename _Tp, size_t _N>
struct _VectorTraits<_SimdWrapper<_Tp, _N>,
std::void_t<__vector_type_t<_Tp, _N>>>
{
using type = __vector_type_t<_Tp, _N>;
using value_type = _Tp;
static constexpr int _S_width = _N;
template <typename _U, int _W = _S_width>
static constexpr bool __is = std::is_same_v<value_type, _U>&& _W == _S_width;
};
template <typename _To, typename _From, typename _FromVT = _VectorTraits<_From>>
_GLIBCXX_SIMD_INTRINSIC constexpr
typename __vector_type<_To, sizeof(_From)>::type
__vector_bitcast(_From __x)
{
return reinterpret_cast<typename __vector_type<_To, sizeof(_From)>::type>(
__x);
}
template <typename _To, typename _Tp, size_t _N>
_GLIBCXX_SIMD_INTRINSIC constexpr
typename __vector_type<_To, sizeof(_SimdWrapper<_Tp, _N>)>::type
__vector_bitcast(const _SimdWrapper<_Tp, _N>& __x)
{
return reinterpret_cast<
typename __vector_type<_To, sizeof(_SimdWrapper<_Tp, _N>)>::type>(
__x._M_data);
}
#ifdef _GLIBCXX_SIMD_WORKAROUND_PR85048
template <typename _To, typename _Tp, typename _TVT = _VectorTraits<_Tp>>
_To __convert_x86(_Tp);
template <typename _To, typename _Tp, typename _TVT = _VectorTraits<_Tp>>
_To __convert_x86(_Tp, _Tp);
template <typename _To, typename _Tp, typename _TVT = _VectorTraits<_Tp>>
_To __convert_x86(_Tp, _Tp, _Tp, _Tp);
template <typename _To, typename _Tp, typename _TVT = _VectorTraits<_Tp>>
_To __convert_x86(_Tp, _Tp, _Tp, _Tp, _Tp, _Tp, _Tp, _Tp);
#endif
template <typename _To, typename _From, size_t... _I>
_GLIBCXX_SIMD_INTRINSIC constexpr _To __vector_convert(_From __a, index_sequence<_I...>)
{
using _Tp = typename _VectorTraits<_To>::value_type;
return _To{static_cast<_Tp>(__a[_I])...};
}
template <typename _To, typename _From, size_t... _I>
_GLIBCXX_SIMD_INTRINSIC constexpr _To __vector_convert(_From __a, _From __b,
index_sequence<_I...>)
{
using _Tp = typename _VectorTraits<_To>::value_type;
return _To{static_cast<_Tp>(__a[_I])..., static_cast<_Tp>(__b[_I])...};
}
template <typename _To, typename _From, size_t... _I>
_GLIBCXX_SIMD_INTRINSIC constexpr _To __vector_convert(_From __a, _From __b, _From __c,
index_sequence<_I...>)
{
using _Tp = typename _VectorTraits<_To>::value_type;
return _To{static_cast<_Tp>(__a[_I])..., static_cast<_Tp>(__b[_I])...,
static_cast<_Tp>(__c[_I])...};
}
template <typename _To, typename _From, size_t... _I>
_GLIBCXX_SIMD_INTRINSIC constexpr _To __vector_convert(_From __a, _From __b, _From __c,
_From __d, index_sequence<_I...>)
{
using _Tp = typename _VectorTraits<_To>::value_type;
return _To{static_cast<_Tp>(__a[_I])..., static_cast<_Tp>(__b[_I])...,
static_cast<_Tp>(__c[_I])..., static_cast<_Tp>(__d[_I])...};
}
template <typename _To, typename _From, size_t... _I>
_GLIBCXX_SIMD_INTRINSIC constexpr _To __vector_convert(_From __a, _From __b, _From __c,
_From __d, _From __e, _From __f,
_From __g, _From __h,
index_sequence<_I...>)
{
using _Tp = typename _VectorTraits<_To>::value_type;
return _To{static_cast<_Tp>(__a[_I])..., static_cast<_Tp>(__b[_I])...,
static_cast<_Tp>(__c[_I])..., static_cast<_Tp>(__d[_I])...,
static_cast<_Tp>(__e[_I])..., static_cast<_Tp>(__f[_I])...,
static_cast<_Tp>(__g[_I])..., static_cast<_Tp>(__h[_I])...};
}
template <typename _To, typename... _From, typename _ToT = _VectorTraits<_To>,
typename _FromT = _VectorTraits<__first_of_pack_t<_From...>>>
_GLIBCXX_SIMD_INTRINSIC constexpr _To __vector_convert(_From... __xs)
{
#ifdef _GLIBCXX_SIMD_WORKAROUND_PR85048
return __convert_x86<_To>(__xs...);
#else
return __vector_convert<_To>(__xs...,
make_index_sequence<std::min(_ToT::_S_width, _FromT::_S_width)>());
#endif
}
template <typename _To, typename... _From, typename = enable_if_t<__is_vectorizable_v<_To>>,
typename _FromT = _VectorTraits<__first_of_pack_t<_From...>>, typename = int>
_GLIBCXX_SIMD_INTRINSIC constexpr _To __vector_convert(_From... __xs)
{
return __vector_convert<__vector_type_t<_To, _FromT::_S_width>>(__xs...);
}
template <typename _Tp, typename _TVT = _VectorTraits<_Tp>,
typename _R = __intrinsic_type_t<typename _TVT::value_type, _TVT::_S_width>>
_GLIBCXX_SIMD_INTRINSIC constexpr _R __to_intrin(_Tp __x)
{
return reinterpret_cast<_R>(__x);
}
template <typename _Tp, size_t _N, typename _R = __intrinsic_type_t<_Tp, _N>>
_GLIBCXX_SIMD_INTRINSIC constexpr _R __to_intrin(_SimdWrapper<_Tp, _N> __x)
{
return reinterpret_cast<_R>(__x._M_data);
}
template <typename _Tp, typename... _Args>
_GLIBCXX_SIMD_INTRINSIC constexpr __vector_type_t<_Tp, sizeof...(_Args)>
__make_vector(_Args&&... args)
{
return __vector_type_t<_Tp, sizeof...(_Args)>{static_cast<_Tp>(args)...};
}
template <size_t _N, typename _Tp>
_GLIBCXX_SIMD_INTRINSIC constexpr __vector_type_t<_Tp, _N> __vector_broadcast(_Tp __x)
{
if constexpr (_N == 2) {
return __vector_type_t<_Tp, 2>{__x, __x};
} else if constexpr (_N == 4) {
return __vector_type_t<_Tp, 4>{__x, __x, __x, __x};
} else if constexpr (_N == 8) {
return __vector_type_t<_Tp, 8>{__x, __x, __x, __x, __x, __x, __x, __x};
} else if constexpr (_N == 16) {
return __vector_type_t<_Tp, 16>{__x, __x, __x, __x, __x, __x, __x, __x,
__x, __x, __x, __x, __x, __x, __x, __x};
} else if constexpr (_N == 32) {
return __vector_type_t<_Tp, 32>{__x, __x, __x, __x, __x, __x, __x, __x,
__x, __x, __x, __x, __x, __x, __x, __x,
__x, __x, __x, __x, __x, __x, __x, __x,
__x, __x, __x, __x, __x, __x, __x, __x};
} else if constexpr (_N == 64) {
return __vector_type_t<_Tp, 64>{
__x, __x, __x, __x, __x, __x, __x, __x, __x, __x, __x, __x, __x,
__x, __x, __x, __x, __x, __x, __x, __x, __x, __x, __x, __x, __x,
__x, __x, __x, __x, __x, __x, __x, __x, __x, __x, __x, __x, __x,
__x, __x, __x, __x, __x, __x, __x, __x, __x, __x, __x, __x, __x,
__x, __x, __x, __x, __x, __x, __x, __x, __x, __x, __x, __x};
} else if constexpr (_N == 128) {
return __vector_type_t<_Tp, 128>{
__x, __x, __x, __x, __x, __x, __x, __x, __x, __x, __x, __x, __x, __x, __x,
__x, __x, __x, __x, __x, __x, __x, __x, __x, __x, __x, __x, __x, __x, __x,
__x, __x, __x, __x, __x, __x, __x, __x, __x, __x, __x, __x, __x, __x, __x,
__x, __x, __x, __x, __x, __x, __x, __x, __x, __x, __x, __x, __x, __x, __x,
__x, __x, __x, __x, __x, __x, __x, __x, __x, __x, __x, __x, __x, __x, __x,
__x, __x, __x, __x, __x, __x, __x, __x, __x, __x, __x, __x, __x, __x, __x,
__x, __x, __x, __x, __x, __x, __x, __x, __x, __x, __x, __x, __x, __x, __x,
__x, __x, __x, __x, __x, __x, __x, __x, __x, __x, __x, __x, __x, __x, __x,
__x, __x, __x, __x, __x, __x, __x, __x};
}
}
template <typename _Tp, size_t _N, typename _G, size_t... _I>
_GLIBCXX_SIMD_INTRINSIC constexpr __vector_type_t<_Tp, _N>
__generate_vector_impl(_G&& __gen, std::index_sequence<_I...>)
{
return __vector_type_t<_Tp, _N>{
static_cast<_Tp>(__gen(_SizeConstant<_I>()))...};
}
template <typename _V, typename _VVT = _VectorTraits<_V>, typename _G>
_GLIBCXX_SIMD_INTRINSIC constexpr _V __generate_vector(_G&& __gen)
{
return __generate_vector_impl<typename _VVT::value_type, _VVT::_S_width>(
std::forward<_G>(__gen), std::make_index_sequence<_VVT::_S_width>());
}
template <typename _Tp, size_t _N, typename _G>
_GLIBCXX_SIMD_INTRINSIC constexpr __vector_type_t<_Tp, _N>
__generate_vector(_G&& __gen)
{
return __generate_vector_impl<_Tp, _N>(std::forward<_G>(__gen),
std::make_index_sequence<_N>());
}
template <typename _Tp, size_t _N, size_t _M = _N * sizeof(_Tp), typename _F>
__vector_type_t<_Tp, _N> __vector_load(const void* __p, _F)
{
static_assert(_M % sizeof(_Tp) == 0);
#ifdef _GLIBCXX_SIMD_WORKAROUND_PR90424
using _U = conditional_t<
is_integral_v<_Tp>,
conditional_t<_M % 4 == 0, conditional_t<_M % 8 == 0, long long, int>,
conditional_t<_M % 2 == 0, short, signed char>>,
conditional_t<(_M < 8 || _N % 2 == 1), float, double>>;
using _V = __vector_type_t<_U, _N * sizeof(_Tp) / sizeof(_U)>;
#else
using _V = __vector_type_t<_Tp, _N>;
#endif
_V __r{};
static_assert(_M <= sizeof(_V));
if constexpr (std::is_same_v<_F, element_aligned_tag>) {}
else if constexpr (std::is_same_v<_F, vector_aligned_tag>)
__p = __builtin_assume_aligned(__p, alignof(__vector_type_t<_Tp, _N>));
else
__p = __builtin_assume_aligned(__p, _F::_S_alignment);
std::memcpy(&__r, __p, _M);
return reinterpret_cast<__vector_type_t<_Tp, _N>>(__r);
}
template <typename _Tp, size_t _M = 16, typename _F>
__vector_type16_t<_Tp> __vector_load16(const void* __p, _F __f)
{
return __vector_load<_Tp, 16 / sizeof(_Tp), _M>(__p, __f);
}
template <size_t _M = 0,
typename _B,
typename _BVT = _VectorTraits<_B>,
typename _F>
void __vector_store(const _B __v, void* __p, _F)
{
using _Tp = typename _BVT::value_type;
constexpr size_t _N = _BVT::_S_width;
constexpr size_t _Bytes = _M == 0 ? _N * sizeof(_Tp) : _M;
static_assert(_Bytes <= sizeof(__v));
#ifdef _GLIBCXX_SIMD_WORKAROUND_PR90424
using _U = std::conditional_t<
(std::is_integral_v<_Tp> || _Bytes < 4), long long,
std::conditional_t<(std::is_same_v<_Tp, double> || _Bytes < 8), float,
_Tp>>;
const auto __vv = __vector_bitcast<_U>(__v);
#else
const __vector_type_t<_Tp, _N> __vv = __v;
#endif
if constexpr (std::is_same_v<_F, vector_aligned_tag>)
__p = __builtin_assume_aligned(__p, alignof(__vector_type_t<_Tp, _N>));
else if constexpr (!std::is_same_v<_F, element_aligned_tag>)
__p = __builtin_assume_aligned(__p, _F::_S_alignment);
if constexpr ((_Bytes & (_Bytes - 1)) != 0)
{
constexpr size_t _MoreBytes = __next_power_of_2(_Bytes);
alignas(_MoreBytes) char __tmp[_MoreBytes];
std::memcpy(__tmp, &__vv, _MoreBytes);
std::memcpy(__p, __tmp, _Bytes);
}
else
std::memcpy(__p, &__vv, _Bytes);
}
template <typename _V>
inline constexpr _V __allbits = reinterpret_cast<_V>(
~__intrinsic_type_t<_LLong, sizeof(_V) / sizeof(_LLong)>());
template <typename _Tp, typename _TVT = _VectorTraits<_Tp>>
_GLIBCXX_SIMD_INTRINSIC constexpr _Tp
__xor(_Tp __a, typename _TVT::type __b) noexcept
{
#if _GLIBCXX_SIMD_X86INTRIN
if (!__builtin_is_constant_evaluated())
{
if constexpr (_TVT::template __is<float, 4> && __have_sse)
return _mm_xor_ps(__a, __b);
else if constexpr (_TVT::template __is<double, 2> && __have_sse2)
return _mm_xor_pd(__a, __b);
else if constexpr (_TVT::template __is<float, 8> && __have_avx)
return _mm256_xor_ps(__a, __b);
else if constexpr (_TVT::template __is<double, 4> && __have_avx)
return _mm256_xor_pd(__a, __b);
else if constexpr (_TVT::template __is<float, 16> && __have_avx512dq)
return _mm512_xor_ps(__a, __b);
else if constexpr (_TVT::template __is<double, 8> && __have_avx512dq)
return _mm512_xor_pd(__a, __b);
}
#endif
using _U = typename _TVT::value_type;
if constexpr (std::is_integral_v<_U>)
return __a ^ __b;
else
return __vector_bitcast<_U>(__vector_bitcast<__int_for_sizeof_t<_U>>(__a) ^
__vector_bitcast<__int_for_sizeof_t<_U>>(__b));
}
template <typename _Tp, typename _TVT = _VectorTraits<_Tp>, typename... _Dummy>
_GLIBCXX_SIMD_INTRINSIC constexpr _Tp
__or(_Tp __a, typename _TVT::type __b, _Dummy...) noexcept
{
#if _GLIBCXX_SIMD_X86INTRIN
if (!__builtin_is_constant_evaluated())
{
if constexpr (_TVT::template __is<float, 4> && __have_sse)
return _mm_or_ps(__a, __b);
else if constexpr (_TVT::template __is<double, 2> && __have_sse2)
return _mm_or_pd(__a, __b);
else if constexpr (_TVT::template __is<float, 8> && __have_avx)
return _mm256_or_ps(__a, __b);
else if constexpr (_TVT::template __is<double, 4> && __have_avx)
return _mm256_or_pd(__a, __b);
else if constexpr (_TVT::template __is<float, 16> && __have_avx512dq)
return _mm512_or_ps(__a, __b);
else if constexpr (_TVT::template __is<double, 8> && __have_avx512dq)
return _mm512_or_pd(__a, __b);
}
#endif
using _U = typename _TVT::value_type;
if constexpr (std::is_integral_v<_U>)
return __a | __b;
else
return __vector_bitcast<_U>(__vector_bitcast<__int_for_sizeof_t<_U>>(__a) |
__vector_bitcast<__int_for_sizeof_t<_U>>(__b));
}
template <typename _Tp, typename = decltype(_Tp() | _Tp())>
_GLIBCXX_SIMD_INTRINSIC constexpr _Tp __or(_Tp __a, _Tp __b) noexcept
{
return __a | __b;
}
template <typename _Tp, typename _TVT = _VectorTraits<_Tp>, typename... _Dummy>
_GLIBCXX_SIMD_INTRINSIC constexpr _Tp
__and(_Tp __a, typename _TVT::type __b, _Dummy...) noexcept
{
static_assert(sizeof...(_Dummy) == 0);
#if _GLIBCXX_SIMD_X86INTRIN
if (!__builtin_is_constant_evaluated())
{
if constexpr (_TVT::template __is<float, 4> && __have_sse)
return _mm_and_ps(__a, __b);
else if constexpr (_TVT::template __is<double, 2> && __have_sse2)
return _mm_and_pd(__a, __b);
else if constexpr (_TVT::template __is<float, 8> && __have_avx)
return _mm256_and_ps(__a, __b);
else if constexpr (_TVT::template __is<double, 4> && __have_avx)
return _mm256_and_pd(__a, __b);
else if constexpr (_TVT::template __is<float, 16> && __have_avx512dq)
return _mm512_and_ps(__a, __b);
else if constexpr (_TVT::template __is<double, 8> && __have_avx512dq)
return _mm512_and_pd(__a, __b);
}
#endif
using _U = typename _TVT::value_type;
if constexpr (std::is_integral_v<_U>)
return __a & __b;
else
return __vector_bitcast<_U>(__vector_bitcast<__int_for_sizeof_t<_U>>(__a) &
__vector_bitcast<__int_for_sizeof_t<_U>>(__b));
}
template <typename _Tp, typename = decltype(_Tp() & _Tp())>
_GLIBCXX_SIMD_INTRINSIC constexpr _Tp __and(_Tp __a, _Tp __b) noexcept
{
return __a & __b;
}
template <typename _Tp, typename _TVT = _VectorTraits<_Tp>>
_GLIBCXX_SIMD_INTRINSIC constexpr _Tp __andnot(_Tp __a, typename _TVT::type __b) noexcept
{
#if _GLIBCXX_SIMD_X86INTRIN
if (!__builtin_is_constant_evaluated())
{
if constexpr (_TVT::template __is<float, 4> && __have_sse)
return _mm_andnot_ps(__a, __b);
else if constexpr (_TVT::template __is<double, 2> && __have_sse2)
return _mm_andnot_pd(__a, __b);
else if constexpr (sizeof(__a) == 16 && __have_sse2)
return reinterpret_cast<_Tp>(
_mm_andnot_si128(__to_intrin(__a), __to_intrin(__b)));
else if constexpr (_TVT::template __is<float, 8> && __have_avx)
return _mm256_andnot_ps(__a, __b);
else if constexpr (_TVT::template __is<double, 4> && __have_avx)
return _mm256_andnot_pd(__a, __b);
else if constexpr (sizeof(__a) == 32 && __have_avx2)
return reinterpret_cast<_Tp>(
_mm256_andnot_si256(__to_intrin(__a), __to_intrin(__b)));
else if constexpr (_TVT::template __is<float, 16> && __have_avx512dq)
return _mm512_andnot_ps(__a, __b);
else if constexpr (_TVT::template __is<double, 8> && __have_avx512dq)
return _mm512_andnot_pd(__a, __b);
else if constexpr (sizeof(__a) == 64 && __have_avx512f)
return reinterpret_cast<_Tp>(_mm512_andnot_si512(
__vector_bitcast<_LLong>(__a), __vector_bitcast<_LLong>(__b)));
}
#endif
return reinterpret_cast<typename _TVT::type>(
~__vector_bitcast<unsigned>(__a) & __vector_bitcast<unsigned>(__b));
}
template <typename _Tp, typename _TVT = _VectorTraits<_Tp>>
_GLIBCXX_SIMD_INTRINSIC constexpr _Tp __not(_Tp __a) noexcept
{
return reinterpret_cast<_Tp>(~__vector_bitcast<unsigned>(__a));
}
template <typename _Tp, typename _TVT = _VectorTraits<_Tp>,
typename _R = __vector_type_t<typename _TVT::value_type, _TVT::_S_width * 2>>
constexpr _R __concat(_Tp a_, _Tp b_) {
#ifdef _GLIBCXX_SIMD_WORKAROUND_XXX_1
using _W = std::conditional_t<std::is_floating_point_v<typename _TVT::value_type>,
double, long long>;
constexpr int input_width = sizeof(_Tp) / sizeof(_W);
const auto __a = __vector_bitcast<_W>(a_);
const auto __b = __vector_bitcast<_W>(b_);
using _U = __vector_type_t<_W, sizeof(_R) / sizeof(_W)>;
#else
constexpr int input_width = _TVT::_S_width;
const _Tp &__a = a_;
const _Tp &__b = b_;
using _U = _R;
#endif
if constexpr(input_width == 2) {
return reinterpret_cast<_R>(_U{__a[0], __a[1], __b[0], __b[1]});
} else if constexpr (input_width == 4) {
return reinterpret_cast<_R>(_U{__a[0], __a[1], __a[2], __a[3], __b[0], __b[1], __b[2], __b[3]});
} else if constexpr (input_width == 8) {
return reinterpret_cast<_R>(_U{__a[0], __a[1], __a[2], __a[3], __a[4], __a[5], __a[6], __a[7], __b[0],
__b[1], __b[2], __b[3], __b[4], __b[5], __b[6], __b[7]});
} else if constexpr (input_width == 16) {
return reinterpret_cast<_R>(
_U{__a[0], __a[1], __a[2], __a[3], __a[4], __a[5], __a[6], __a[7], __a[8], __a[9], __a[10],
__a[11], __a[12], __a[13], __a[14], __a[15], __b[0], __b[1], __b[2], __b[3], __b[4], __b[5],
__b[6], __b[7], __b[8], __b[9], __b[10], __b[11], __b[12], __b[13], __b[14], __b[15]});
} else if constexpr (input_width == 32) {
return reinterpret_cast<_R>(
_U{__a[0], __a[1], __a[2], __a[3], __a[4], __a[5], __a[6], __a[7], __a[8], __a[9], __a[10],
__a[11], __a[12], __a[13], __a[14], __a[15], __a[16], __a[17], __a[18], __a[19], __a[20], __a[21],
__a[22], __a[23], __a[24], __a[25], __a[26], __a[27], __a[28], __a[29], __a[30], __a[31], __b[0],
__b[1], __b[2], __b[3], __b[4], __b[5], __b[6], __b[7], __b[8], __b[9], __b[10], __b[11],
__b[12], __b[13], __b[14], __b[15], __b[16], __b[17], __b[18], __b[19], __b[20], __b[21], __b[22],
__b[23], __b[24], __b[25], __b[26], __b[27], __b[28], __b[29], __b[30], __b[31]});
}
}
template <typename _Tp, typename _TVT = _VectorTraits<_Tp>>
_GLIBCXX_SIMD_INTRINSIC auto __zero_extend(_Tp __x)
{
using value_type = typename _TVT::value_type;
constexpr size_t _N = _TVT::_S_width;
struct {
_Tp __x;
operator __vector_type_t<value_type, _N * 2>()
{
#ifdef _GLIBCXX_SIMD_WORKAROUND_XXX_3
if constexpr (__have_avx && _TVT::template __is<float, 4>) {
return __vector_bitcast<value_type>(_mm256_insertf128_ps(__m256(), __x, 0));
} else if constexpr (__have_avx && _TVT::template __is<double, 2>) {
return __vector_bitcast<value_type>(_mm256_insertf128_pd(__m256d(), __x, 0));
} else if constexpr (__have_avx2 && sizeof(__x) == 16) {
return __vector_bitcast<value_type>(_mm256_insertf128_si256(__m256i(), __x, 0));
} else if constexpr (__have_avx512f && _TVT::template __is<float, 8>) {
if constexpr (__have_avx512dq) {
return __vector_bitcast<value_type>(_mm512_insertf32x8(__m512(), __x, 0));
} else {
return reinterpret_cast<__m512>(
_mm512_insertf64x4(__m512d(), reinterpret_cast<__m256d>(__x), 0));
}
} else if constexpr (__have_avx512f && _TVT::template __is<double, 4>) {
return __vector_bitcast<value_type>(_mm512_insertf64x4(__m512d(), __x, 0));
} else if constexpr (__have_avx512f && sizeof(__x) == 32) {
return __vector_bitcast<value_type>(_mm512_inserti64x4(__m512i(), __x, 0));
}
#endif
return __concat(__x, _Tp());
}
operator __vector_type_t<value_type, _N * 4>()
{
#ifdef _GLIBCXX_SIMD_WORKAROUND_XXX_3
if constexpr (__have_avx && _TVT::template __is<float, 4>) {
#ifdef _GLIBCXX_SIMD_WORKAROUND_PR85480
asm("vmovaps %0, %0" : "+__x"(__x));
return __vector_bitcast<value_type>(_mm512_castps128_ps512(__x));
#else
return __vector_bitcast<value_type>(_mm512_insertf32x4(__m512(), __x, 0));
#endif
} else if constexpr (__have_avx && _TVT::template __is<double, 2>) {
#ifdef _GLIBCXX_SIMD_WORKAROUND_PR85480
asm("vmovapd %0, %0" : "+__x"(__x));
return __vector_bitcast<value_type>(_mm512_castpd128_pd512(__x));
#else
return __vector_bitcast<value_type>(_mm512_insertf64x2(__m512d(), __x, 0));
#endif
} else if constexpr (__have_avx512f && sizeof(__x) == 16) {
#ifdef _GLIBCXX_SIMD_WORKAROUND_PR85480
asm("vmovadq %0, %0" : "+__x"(__x));
return __vector_bitcast<value_type>(_mm512_castsi128_si512(__x));
#else
return __vector_bitcast<value_type>(_mm512_inserti32x4(__m512i(), __x, 0));
#endif
}
#endif
return __concat(__concat(__x, _Tp()), __vector_type_t<value_type, _N * 2>());
}
operator __vector_type_t<value_type, _N * 8>()
{
return __concat(operator __vector_type_t<value_type, _N * 4>(),
__vector_type_t<value_type, _N * 4>());
}
operator __vector_type_t<value_type, _N * 16>()
{
return __concat(operator __vector_type_t<value_type, _N * 8>(),
__vector_type_t<value_type, _N * 8>());
}
} __r{__x};
return __r;
}
template <int _Offset,
int _SplitBy,
typename _Tp,
typename _TVT = _VectorTraits<_Tp>,
typename _R = __vector_type_t<typename _TVT::value_type,
_TVT::_S_width / _SplitBy>>
_GLIBCXX_SIMD_INTRINSIC constexpr _R __extract(_Tp __in)
{
#ifdef _GLIBCXX_SIMD_WORKAROUND_XXX_1
using _W =
std::conditional_t<std::is_floating_point_v<typename _TVT::value_type>,
double, long long>;
constexpr int return_width = sizeof(_R) / sizeof(_W);
using _U = __vector_type_t<_W, return_width>;
const auto __x = __vector_bitcast<_W>(__in);
#else
constexpr int return_width = _TVT::_S_width / _SplitBy;
using _U = _R;
const __vector_type_t<typename _TVT::value_type, _TVT::_S_width>& __x =
__in;
#endif
constexpr int _O = _Offset * return_width;
if constexpr (return_width == 2)
{
return reinterpret_cast<_R>(_U{__x[_O + 0], __x[_O + 1]});
}
else if constexpr (return_width == 4)
{
return reinterpret_cast<_R>(
_U{__x[_O + 0], __x[_O + 1], __x[_O + 2], __x[_O + 3]});
}
else if constexpr (return_width == 8)
{
return reinterpret_cast<_R>(_U{__x[_O + 0], __x[_O + 1], __x[_O + 2],
__x[_O + 3], __x[_O + 4], __x[_O + 5],
__x[_O + 6], __x[_O + 7]});
}
else if constexpr (return_width == 16)
{
return reinterpret_cast<_R>(
_U{__x[_O + 0], __x[_O + 1], __x[_O + 2], __x[_O + 3], __x[_O + 4],
__x[_O + 5], __x[_O + 6], __x[_O + 7], __x[_O + 8], __x[_O + 9],
__x[_O + 10], __x[_O + 11], __x[_O + 12], __x[_O + 13], __x[_O + 14],
__x[_O + 15]});
}
else if constexpr (return_width == 32)
{
return reinterpret_cast<_R>(
_U{__x[_O + 0], __x[_O + 1], __x[_O + 2], __x[_O + 3], __x[_O + 4],
__x[_O + 5], __x[_O + 6], __x[_O + 7], __x[_O + 8], __x[_O + 9],
__x[_O + 10], __x[_O + 11], __x[_O + 12], __x[_O + 13], __x[_O + 14],
__x[_O + 15], __x[_O + 16], __x[_O + 17], __x[_O + 18], __x[_O + 19],
__x[_O + 20], __x[_O + 21], __x[_O + 22], __x[_O + 23], __x[_O + 24],
__x[_O + 25], __x[_O + 26], __x[_O + 27], __x[_O + 28], __x[_O + 29],
__x[_O + 30], __x[_O + 31]});
}
else
{
__assert_unreachable<_Tp>();
}
}
template <
typename _Tp,
typename _R = __vector_type8_t<typename _VectorTraits<_Tp>::value_type>>
_GLIBCXX_SIMD_INTRINSIC constexpr _R __lo64(_Tp __x)
{
_R __r{};
__builtin_memcpy(&__r, &__x, 8);
return __r;
}
template <
typename _Tp,
typename _R = __vector_type8_t<typename _VectorTraits<_Tp>::value_type>>
_GLIBCXX_SIMD_INTRINSIC constexpr _R __hi64(_Tp __x)
{
static_assert(sizeof(_Tp) == 16);
_R __r{};
__builtin_memcpy(&__r, reinterpret_cast<const char*>(&__x) + 8, 8);
return __r;
}
template <
typename _Tp,
typename _R = __vector_type8_t<typename _VectorTraits<_Tp>::value_type>>
_GLIBCXX_SIMD_INTRINSIC constexpr _R __hi64z(_Tp __x)
{
_R __r{};
if constexpr (sizeof(_Tp) == 16)
__builtin_memcpy(&__r, reinterpret_cast<const char*>(&__x) + 8, 8);
return __r;
}
template <typename _Tp> _GLIBCXX_SIMD_INTRINSIC constexpr auto __lo128(_Tp __x)
{
return __extract<0, sizeof(_Tp) / 16>(__x);
}
template <typename _Tp> _GLIBCXX_SIMD_INTRINSIC constexpr auto __hi128(_Tp __x)
{
static_assert(sizeof(__x) == 32);
return __extract<1, 2>(__x);
}
template <typename _Tp> _GLIBCXX_SIMD_INTRINSIC constexpr auto __lo256(_Tp __x)
{
static_assert(sizeof(__x) == 64);
return __extract<0, 2>(__x);
}
template <typename _Tp> _GLIBCXX_SIMD_INTRINSIC constexpr auto __hi256(_Tp __x)
{
static_assert(sizeof(__x) == 64);
return __extract<1, 2>(__x);
}
template <typename _To, typename _From> _GLIBCXX_SIMD_INTRINSIC constexpr _To __intrin_bitcast(_From __v)
{
static_assert(__is_vector_type_v<_From> && __is_vector_type_v<_To>);
if constexpr (sizeof(_To) == sizeof(_From)) {
return reinterpret_cast<_To>(__v);
} else if constexpr (sizeof(_From) > sizeof(_To)) {
return reinterpret_cast<const _To &>(__v);
#if _GLIBCXX_SIMD_X86INTRIN
} else if constexpr (__have_avx && sizeof(_From) == 16 && sizeof(_To) == 32) {
return reinterpret_cast<_To>(_mm256_castps128_ps256(
reinterpret_cast<__intrinsic_type_t<float, sizeof(_From) / sizeof(float)>>(__v)));
} else if constexpr (__have_avx512f && sizeof(_From) == 16 && sizeof(_To) == 64) {
return reinterpret_cast<_To>(_mm512_castps128_ps512(
reinterpret_cast<__intrinsic_type_t<float, sizeof(_From) / sizeof(float)>>(__v)));
} else if constexpr (__have_avx512f && sizeof(_From) == 32 && sizeof(_To) == 64) {
return reinterpret_cast<_To>(_mm512_castps256_ps512(
reinterpret_cast<__intrinsic_type_t<float, sizeof(_From) / sizeof(float)>>(__v)));
#endif
} else {
__assert_unreachable<_To>();
}
}
template <typename _Tp> struct auto_cast_t {
static_assert(__is_vector_type_v<_Tp>);
const _Tp __x;
template <typename _U> _GLIBCXX_SIMD_INTRINSIC constexpr operator _U() const
{
return __intrin_bitcast<_U>(__x);
}
};
template <typename _Tp> _GLIBCXX_SIMD_INTRINSIC constexpr auto_cast_t<_Tp> __auto_bitcast(const _Tp &__x)
{
return {__x};
}
template <typename _Tp, size_t _N>
_GLIBCXX_SIMD_INTRINSIC constexpr auto_cast_t<typename _SimdWrapper<_Tp, _N>::_BuiltinType> __auto_bitcast(
const _SimdWrapper<_Tp, _N> &__x)
{
return {__x._M_data};
}
_GLIBCXX_SIMD_INTRINSIC constexpr std::bitset<1> __vector_to_bitset(bool __x) { return unsigned(__x); }
template <typename _Tp, typename = enable_if_t<__is_bitmask_v<_Tp> && __have_avx512f>>
_GLIBCXX_SIMD_INTRINSIC constexpr std::bitset<8 * sizeof(_Tp)> __vector_to_bitset(_Tp __x)
{
if constexpr (std::is_integral_v<_Tp>) {
return __x;
} else {
return __x._M_data;
}
}
template <typename _Tp, typename _TVT = _VectorTraits<_Tp>>
_GLIBCXX_SIMD_INTRINSIC std::bitset<_TVT::_S_width> __vector_to_bitset(_Tp __x)
{
constexpr int __w = sizeof(typename _TVT::value_type);
#if _GLIBCXX_SIMD_HAVE_NEON
using _I = __int_with_sizeof_t<__w>;
if constexpr (__have_neon && sizeof(_Tp) == 16)
{
auto __asint = __vector_bitcast<_I>(__x);
[[maybe_unused]] constexpr auto __zero = decltype(__asint)();
if constexpr (__w == 1)
{
__asint &=
__make_vector<_I>(0x1, 0x2, 0x4, 0x8, 0x10, 0x20, 0x40, 0x80, 0x1,
0x2, 0x4, 0x8, 0x10, 0x20, 0x40, 0x80);
return __vector_bitcast<_UShort>(vpaddq_s8(
vpaddq_s8(vpaddq_s8(__asint, __zero), __zero), __zero))[0];
}
else if constexpr (__w == 2)
{
__asint &=
__make_vector<_I>(0x1, 0x2, 0x4, 0x8, 0x10, 0x20, 0x40, 0x80);
#ifdef __aarch64__
return vpaddq_s16(vpaddq_s16(vpaddq_s16(__asint, __zero), __zero),
__zero)[0];
#else
return vpadd_s16(vpadd_s16(
vpadd_s16(__lo64(__asint), __hi64(__asint)), __zero) __zero)[0];
#endif
}
else if constexpr (__w == 4)
{
__asint &= __make_vector<_I>(0x1, 0x2, 0x4, 0x8);
return vpaddq_s32(vpaddq_s32(__asint, __zero), __zero)[0];
}
else if constexpr (__w == 8)
{
return (__asint[0] & 1) | (__asint[1] & 2);
}
}
else if constexpr (__have_neon && sizeof(_Tp) == 8)
{
auto __asint = __vector_bitcast<_I>(__x);
[[maybe_unused]] constexpr auto __zero = decltype(__asint)();
if constexpr (__w == 1)
{
__asint &=
__make_vector<_I>(0x1, 0x2, 0x4, 0x8, 0x10, 0x20, 0x40, 0x80);
return vpadd_s8(vpadd_s8(vpadd_s8(__asint, __zero), __zero),
__zero)[0];
}
else if constexpr (__w == 2)
{
__asint &=
__make_vector<_I>(0x1, 0x2, 0x4, 0x8);
return vpadd_s16(vpadd_s16(__asint, __zero), __zero)[0];
}
else if constexpr (__w == 4)
{
__asint &= __make_vector<_I>(0x1, 0x2);
return vpadd_s32(__asint, __zero)[0];
}
else if constexpr (__w == 8)
{
return !!__asint[0];
}
}
else
__assert_unreachable<_Tp>();
#endif
#if _GLIBCXX_SIMD_X86INTRIN
constexpr bool __is_sse = __have_sse && sizeof(_Tp) == 16;
constexpr bool __is_avx = __have_avx && sizeof(_Tp) == 32;
[[maybe_unused]] auto __intrin = __to_intrin(__x);
if constexpr (__is_sse && __w == 1)
{
return _mm_movemask_epi8(__intrin);
}
else if constexpr (__is_sse && __w == 2)
{
if constexpr (__have_avx512bw_vl)
{
return _mm_cmplt_epi16_mask(__intrin, __m128i());
}
else
{
return _mm_movemask_epi8(_mm_packs_epi16(__intrin, __m128i()));
}
}
else if constexpr (__is_sse && __w == 4)
{
if constexpr (__have_avx512vl && std::is_integral_v<_Tp>)
{
return _mm_cmplt_epi32_mask(__intrin, __m128i());
}
else
{
return _mm_movemask_ps(__vector_bitcast<float>(__x));
}
}
else if constexpr (__is_sse && __w == 8)
{
if constexpr (__have_avx512vl && std::is_integral_v<_Tp>)
{
return _mm_cmplt_epi64_mask(__intrin, __m128i());
}
else
{
return _mm_movemask_pd(__vector_bitcast<double>(__x));
}
}
else if constexpr (__is_avx && __w == 1)
{
return _mm256_movemask_epi8(__intrin);
}
else if constexpr (__is_avx && __w == 2)
{
if constexpr (__have_avx512bw_vl)
{
return _mm256_cmplt_epi16_mask(__intrin, __m256i());
}
else
{
return _mm_movemask_epi8(_mm_packs_epi16(__extract<0, 2>(__intrin),
__extract<1, 2>(__intrin)));
}
}
else if constexpr (__is_avx && __w == 4)
{
if constexpr (__have_avx512vl && std::is_integral_v<_Tp>)
{
return _mm256_cmplt_epi32_mask(__intrin, __m256i());
}
else
{
return _mm256_movemask_ps(__vector_bitcast<float>(__x));
}
}
else if constexpr (__is_avx && __w == 8)
{
if constexpr (__have_avx512vl && std::is_integral_v<_Tp>)
{
return _mm256_cmplt_epi64_mask(__intrin, __m256i());
}
else
{
return _mm256_movemask_pd(__vector_bitcast<double>(__x));
}
}
else
__assert_unreachable<_Tp>();
#endif
std::bitset<_TVT::_S_width> __r;
for (int __i = 0; __i < _TVT::_S_width; ++__i)
{
__r[__i] = !(__x[__i] == 0);
}
return __r;
}
template <typename _K, typename _V0, typename _V1>
_GLIBCXX_SIMD_INTRINSIC _GLIBCXX_SIMD_CONST auto
__blend(_K mask, _V0 at0, _V1 at1)
{
using _V = _V0;
if constexpr (!std::is_same_v<_V0, _V1>)
{
static_assert(sizeof(_V0) == sizeof(_V1));
if constexpr (__is_vector_type_v<_V0> && !__is_vector_type_v<_V1>)
{
return __blend(mask, at0, reinterpret_cast<_V0>(at1._M_data));
}
else if constexpr (!__is_vector_type_v<_V0> && __is_vector_type_v<_V1>)
{
return __blend(mask, reinterpret_cast<_V1>(at0._M_data), at1);
}
else
{
__assert_unreachable<_K>();
}
}
else if constexpr (__is_bitmask_v<_V> && __is_bitmask_v<_K>)
{
static_assert(sizeof(_K) == sizeof(_V0) && sizeof(_V0) == sizeof(_V1));
return (mask & at1) | (~mask & at0);
}
else if constexpr (!__is_vector_type_v<_V>)
{
return __blend(mask, at0._M_data, at1._M_data);
}
else if constexpr (__is_bitmask_v<_K>)
{
using _Tp = typename _VectorTraits<_V>::value_type;
if constexpr (sizeof(_V) == 16 && __have_avx512bw_vl && sizeof(_Tp) <= 2)
{
if constexpr (sizeof(_Tp) == 1)
{
return __intrin_bitcast<_V>(
_mm_mask_mov_epi8(__to_intrin(at0), mask, __to_intrin(at1)));
}
else if constexpr (sizeof(_Tp) == 2)
{
return __intrin_bitcast<_V>(
_mm_mask_mov_epi16(__to_intrin(at0), mask, __to_intrin(at1)));
}
}
else if constexpr (sizeof(_V) == 16 && __have_avx512vl && sizeof(_Tp) > 2)
{
if constexpr (std::is_integral_v<_Tp> && sizeof(_Tp) == 4)
{
return __intrin_bitcast<_V>(
_mm_mask_mov_epi32(__to_intrin(at0), mask, __to_intrin(at1)));
}
else if constexpr (std::is_integral_v<_Tp> && sizeof(_Tp) == 8)
{
return __intrin_bitcast<_V>(
_mm_mask_mov_epi64(__to_intrin(at0), mask, __to_intrin(at1)));
}
else if constexpr (std::is_floating_point_v<_Tp> && sizeof(_Tp) == 4)
{
return __intrin_bitcast<_V>(_mm_mask_mov_ps(at0, mask, at1));
}
else if constexpr (std::is_floating_point_v<_Tp> && sizeof(_Tp) == 8)
{
return __intrin_bitcast<_V>(_mm_mask_mov_pd(at0, mask, at1));
}
}
else if constexpr (sizeof(_V) == 16 && __have_avx512f && sizeof(_Tp) > 2)
{
if constexpr (std::is_integral_v<_Tp> && sizeof(_Tp) == 4)
{
return __intrin_bitcast<_V>(__lo128(_mm512_mask_mov_epi32(
__auto_bitcast(at0), mask, __auto_bitcast(at1))));
}
else if constexpr (std::is_integral_v<_Tp> && sizeof(_Tp) == 8)
{
return __intrin_bitcast<_V>(__lo128(_mm512_mask_mov_epi64(
__auto_bitcast(at0), mask, __auto_bitcast(at1))));
}
else if constexpr (std::is_floating_point_v<_Tp> && sizeof(_Tp) == 4)
{
return __intrin_bitcast<_V>(__lo128(_mm512_mask_mov_ps(
__auto_bitcast(at0), mask, __auto_bitcast(at1))));
}
else if constexpr (std::is_floating_point_v<_Tp> && sizeof(_Tp) == 8)
{
return __intrin_bitcast<_V>(__lo128(_mm512_mask_mov_pd(
__auto_bitcast(at0), mask, __auto_bitcast(at1))));
}
}
else if constexpr (sizeof(_V) == 32 && __have_avx512bw_vl &&
sizeof(_Tp) <= 2)
{
if constexpr (sizeof(_Tp) == 1)
{
return __intrin_bitcast<_V>(
_mm256_mask_mov_epi8(__to_intrin(at0), mask, __to_intrin(at1)));
}
else if constexpr (sizeof(_Tp) == 2)
{
return __intrin_bitcast<_V>(_mm256_mask_mov_epi16(
__to_intrin(at0), mask, __to_intrin(at1)));
}
}
else if constexpr (sizeof(_V) == 32 && __have_avx512vl && sizeof(_Tp) > 2)
{
if constexpr (std::is_integral_v<_Tp> && sizeof(_Tp) == 4)
{
return __intrin_bitcast<_V>(_mm256_mask_mov_epi32(
__to_intrin(at0), mask, __to_intrin(at1)));
}
else if constexpr (std::is_integral_v<_Tp> && sizeof(_Tp) == 8)
{
return __intrin_bitcast<_V>(_mm256_mask_mov_epi64(
__to_intrin(at0), mask, __to_intrin(at1)));
}
else if constexpr (std::is_floating_point_v<_Tp> && sizeof(_Tp) == 4)
{
return __intrin_bitcast<_V>(_mm256_mask_mov_ps(at0, mask, at1));
}
else if constexpr (std::is_floating_point_v<_Tp> && sizeof(_Tp) == 8)
{
return __intrin_bitcast<_V>(_mm256_mask_mov_pd(at0, mask, at1));
}
}
else if constexpr (sizeof(_V) == 32 && __have_avx512f && sizeof(_Tp) > 2)
{
if constexpr (std::is_integral_v<_Tp> && sizeof(_Tp) == 4)
{
return __intrin_bitcast<_V>(__lo256(_mm512_mask_mov_epi32(
__auto_bitcast(at0), mask, __auto_bitcast(at1))));
}
else if constexpr (std::is_integral_v<_Tp> && sizeof(_Tp) == 8)
{
return __intrin_bitcast<_V>(__lo256(_mm512_mask_mov_epi64(
__auto_bitcast(at0), mask, __auto_bitcast(at1))));
}
else if constexpr (std::is_floating_point_v<_Tp> && sizeof(_Tp) == 4)
{
return __intrin_bitcast<_V>(__lo256(_mm512_mask_mov_ps(
__auto_bitcast(at0), mask, __auto_bitcast(at1))));
}
else if constexpr (std::is_floating_point_v<_Tp> && sizeof(_Tp) == 8)
{
return __intrin_bitcast<_V>(__lo256(_mm512_mask_mov_pd(
__auto_bitcast(at0), mask, __auto_bitcast(at1))));
}
}
else if constexpr (sizeof(_V) == 64 && __have_avx512bw &&
sizeof(_Tp) <= 2)
{
if constexpr (sizeof(_Tp) == 1)
{
return __intrin_bitcast<_V>(
_mm512_mask_mov_epi8(__to_intrin(at0), mask, __to_intrin(at1)));
}
else if constexpr (sizeof(_Tp) == 2)
{
return __intrin_bitcast<_V>(_mm512_mask_mov_epi16(
__to_intrin(at0), mask, __to_intrin(at1)));
}
}
else if constexpr (sizeof(_V) == 64 && __have_avx512f && sizeof(_Tp) > 2)
{
if constexpr (std::is_integral_v<_Tp> && sizeof(_Tp) == 4)
{
return __intrin_bitcast<_V>(_mm512_mask_mov_epi32(
__to_intrin(at0), mask, __to_intrin(at1)));
}
else if constexpr (std::is_integral_v<_Tp> && sizeof(_Tp) == 8)
{
return __intrin_bitcast<_V>(_mm512_mask_mov_epi64(
__to_intrin(at0), mask, __to_intrin(at1)));
}
else if constexpr (std::is_floating_point_v<_Tp> && sizeof(_Tp) == 4)
{
return __intrin_bitcast<_V>(_mm512_mask_mov_ps(at0, mask, at1));
}
else if constexpr (std::is_floating_point_v<_Tp> && sizeof(_Tp) == 8)
{
return __intrin_bitcast<_V>(_mm512_mask_mov_pd(at0, mask, at1));
}
}
else
{
__assert_unreachable<_K>();
}
}
else if constexpr (((__have_avx512f && sizeof(_V) == 64) ||
__have_avx512vl) &&
(sizeof(typename _VectorTraits<_V>::value_type) >= 4 ||
__have_avx512bw))
{
return __blend(
__convert_mask<__bool_storage_member_type_t<_VectorTraits<_V>::_S_width>>(mask), at0,
at1);
}
else
{
const _V __k = __auto_bitcast(mask);
using _Tp = typename _VectorTraits<_V>::value_type;
if constexpr (sizeof(_V) == 16 && __have_sse4_1)
{
if constexpr (std::is_integral_v<_Tp>)
{
return __intrin_bitcast<_V>(_mm_blendv_epi8(
__to_intrin(at0), __to_intrin(at1), __to_intrin(__k)));
}
else if constexpr (sizeof(_Tp) == 4)
{
return __intrin_bitcast<_V>(_mm_blendv_ps(at0, at1, __k));
}
else if constexpr (sizeof(_Tp) == 8)
{
return __intrin_bitcast<_V>(_mm_blendv_pd(at0, at1, __k));
}
}
else if constexpr (sizeof(_V) == 32)
{
if constexpr (std::is_integral_v<_Tp>)
{
return __intrin_bitcast<_V>(_mm256_blendv_epi8(
__to_intrin(at0), __to_intrin(at1), __to_intrin(__k)));
}
else if constexpr (sizeof(_Tp) == 4)
{
return __intrin_bitcast<_V>(_mm256_blendv_ps(at0, at1, __k));
}
else if constexpr (sizeof(_Tp) == 8)
{
return __intrin_bitcast<_V>(_mm256_blendv_pd(at0, at1, __k));
}
}
else
{
return __or(__andnot(__k, at0), __and(__k, at1));
}
}
}
template <class _A,
class _B,
class _Tp = std::common_type_t<_A, _B>,
class _Trait = _VectorTraits<_Tp>>
_GLIBCXX_SIMD_INTRINSIC constexpr _Tp
__interleave_lo(const _A& _a, const _B& _b)
{
const _Tp __a(_a);
const _Tp __b(_b);
if constexpr (_Trait::_S_width == 2)
return _Tp{__a[0], __b[0]};
else if constexpr (_Trait::_S_width == 4)
return _Tp{__a[0], __b[0], __a[1], __b[1]};
else if constexpr (_Trait::_S_width == 8)
return _Tp{__a[0], __b[0], __a[1], __b[1], __a[2], __b[2], __a[3], __b[3]};
else if constexpr (_Trait::_S_width == 16)
return _Tp{__a[0], __b[0], __a[1], __b[1], __a[2], __b[2], __a[3], __b[3],
__a[4], __b[4], __a[5], __b[5], __a[6], __b[6], __a[7], __b[7]};
else if constexpr (_Trait::_S_width == 32)
return _Tp{__a[0], __b[0], __a[1], __b[1], __a[2], __b[2], __a[3],
__b[3], __a[4], __b[4], __a[5], __b[5], __a[6], __b[6],
__a[7], __b[7], __a[8], __b[8], __a[9], __b[9], __a[10],
__b[10], __a[11], __b[11], __a[12], __b[12], __a[13], __b[13],
__a[14], __b[14], __a[15], __b[15]};
else if constexpr (_Trait::_S_width == 64)
return _Tp{
__a[0], __b[0], __a[1], __b[1], __a[2], __b[2], __a[3], __b[3],
__a[4], __b[4], __a[5], __b[5], __a[6], __b[6], __a[7], __b[7],
__a[8], __b[8], __a[9], __b[9], __a[10], __b[10], __a[11], __b[11],
__a[12], __b[12], __a[13], __b[13], __a[14], __b[14], __a[15], __b[15],
__a[16], __b[16], __a[17], __b[17], __a[18], __b[18], __a[19], __b[19],
__a[20], __b[20], __a[21], __b[21], __a[22], __b[22], __a[23], __b[23],
__a[24], __b[24], __a[25], __b[25], __a[26], __b[26], __a[27], __b[27],
__a[28], __b[28], __a[29], __b[29], __a[30], __b[30], __a[31], __b[31]};
else
__assert_unreachable<_Tp>();
}
template <class _A,
class _B,
class _Tp = std::common_type_t<_A, _B>,
class _Trait = _VectorTraits<_Tp>>
_GLIBCXX_SIMD_INTRINSIC constexpr _Tp
__interleave_hi(const _A& _a, const _B& _b)
{
const _Tp __a(_a);
const _Tp __b(_b);
if constexpr (_Trait::_S_width == 2)
return _Tp{__a[1], __b[1]};
else if constexpr (_Trait::_S_width == 4)
return _Tp{__a[2], __b[2], __a[3], __b[3]};
else if constexpr (_Trait::_S_width == 8)
return _Tp{__a[4], __b[4], __a[5], __b[5], __a[6], __b[6], __a[7], __b[7]};
else if constexpr (_Trait::_S_width == 16)
return _Tp{__a[8], __b[8], __a[9], __b[9], __a[10], __b[10],
__a[11], __b[11], __a[12], __b[12], __a[13], __b[13],
__a[14], __b[14], __a[15], __b[15]};
else if constexpr (_Trait::_S_width == 32)
return _Tp{__a[16], __b[16], __a[17], __b[17], __a[18], __b[18], __a[19],
__b[19], __a[20], __b[20], __a[21], __b[21], __a[22], __b[22],
__a[23], __b[23], __a[24], __b[24], __a[25], __b[25], __a[26],
__b[26], __a[27], __b[27], __a[28], __b[28], __a[29], __b[29],
__a[30], __b[30], __a[31], __b[31]};
else if constexpr (_Trait::_S_width == 64)
return _Tp{
__a[32], __b[32], __a[33], __b[33], __a[34], __b[34], __a[35], __b[35],
__a[36], __b[36], __a[37], __b[37], __a[38], __b[38], __a[39], __b[39],
__a[40], __b[40], __a[41], __b[41], __a[42], __b[42], __a[43], __b[43],
__a[44], __b[44], __a[45], __b[45], __a[46], __b[46], __a[47], __b[47],
__a[48], __b[48], __a[49], __b[49], __a[50], __b[50], __a[51], __b[51],
__a[52], __b[52], __a[53], __b[53], __a[54], __b[54], __a[55], __b[55],
__a[56], __b[56], __a[57], __b[57], __a[58], __b[58], __a[59], __b[59],
__a[60], __b[60], __a[61], __b[61], __a[62], __b[62], __a[63], __b[63]};
else
__assert_unreachable<_Tp>();
}
template <class _A,
class _B,
class _Tp = std::common_type_t<_A, _B>,
class _Trait = _VectorTraits<_Tp>>
_GLIBCXX_SIMD_INTRINSIC constexpr _Tp
__interleave128_lo(const _A& _a, const _B& _b)
{
const _Tp __a(_a);
const _Tp __b(_b);
if constexpr (sizeof(_Tp) == 16)
return __interleave_lo(__a, __b);
else if constexpr (sizeof(_Tp) == 32 && _Trait::_S_width == 4)
return _Tp{__a[0], __b[0], __a[2], __b[2]};
else if constexpr (sizeof(_Tp) == 32 && _Trait::_S_width == 8)
return _Tp{__a[0], __b[0], __a[1], __b[1], __a[4], __b[4], __a[5], __b[5]};
else if constexpr (sizeof(_Tp) == 32 && _Trait::_S_width == 16)
return _Tp{__a[0], __b[0], __a[1], __b[1], __a[2], __b[2],
__a[3], __b[3], __a[8], __b[8], __a[9], __b[9],
__a[10], __b[10], __a[11], __b[11]};
else if constexpr (sizeof(_Tp) == 32 && _Trait::_S_width == 32)
return _Tp{__a[0], __b[0], __a[1], __b[1], __a[2], __b[2], __a[3],
__b[3], __a[4], __b[4], __a[5], __b[5], __a[6], __b[6],
__a[7], __b[7], __a[16], __b[16], __a[17], __b[17], __a[18],
__b[18], __a[19], __b[19], __a[20], __b[20], __a[21], __b[21],
__a[22], __b[22], __a[23], __b[23]};
else if constexpr (sizeof(_Tp) == 32 && _Trait::_S_width == 64)
return _Tp{
__a[0], __b[0], __a[1], __b[1], __a[2], __b[2], __a[3], __b[3],
__a[4], __b[4], __a[5], __b[5], __a[6], __b[6], __a[7], __b[7],
__a[8], __b[8], __a[9], __b[9], __a[10], __b[10], __a[11], __b[11],
__a[12], __b[12], __a[13], __b[13], __a[14], __b[14], __a[15], __b[15],
__a[32], __b[32], __a[33], __b[33], __a[34], __b[34], __a[35], __b[35],
__a[36], __b[36], __a[37], __b[37], __a[38], __b[38], __a[39], __b[39],
__a[40], __b[40], __a[41], __b[41], __a[42], __b[42], __a[43], __b[43],
__a[44], __b[44], __a[45], __b[45], __a[46], __b[46], __a[47], __b[47]};
else if constexpr (sizeof(_Tp) == 64 && _Trait::_S_width == 8)
return _Tp{__a[0], __b[0], __a[2], __b[2], __a[4], __b[4], __a[6], __b[6]};
else if constexpr (sizeof(_Tp) == 64 && _Trait::_S_width == 16)
return _Tp{__a[0], __b[0], __a[1], __b[1], __a[4], __b[4],
__a[5], __b[5], __a[8], __b[8], __a[9], __b[9],
__a[12], __b[12], __a[13], __b[13]};
else if constexpr (sizeof(_Tp) == 64 && _Trait::_S_width == 32)
return _Tp{__a[0], __b[0], __a[1], __b[1], __a[2], __b[2], __a[3],
__b[3], __a[8], __b[8], __a[9], __b[9], __a[10], __b[10],
__a[11], __b[11], __a[16], __b[16], __a[17], __b[17], __a[18],
__b[18], __a[19], __b[19], __a[24], __b[24], __a[25], __b[25],
__a[26], __b[26], __a[27], __b[27]};
else if constexpr (sizeof(_Tp) == 64 && _Trait::_S_width == 64)
return _Tp{
__a[0], __b[0], __a[1], __b[1], __a[2], __b[2], __a[3], __b[3],
__a[4], __b[4], __a[5], __b[5], __a[6], __b[6], __a[7], __b[7],
__a[16], __b[16], __a[17], __b[17], __a[18], __b[18], __a[19], __b[19],
__a[20], __b[20], __a[21], __b[21], __a[22], __b[22], __a[23], __b[23],
__a[32], __b[32], __a[33], __b[33], __a[34], __b[34], __a[35], __b[35],
__a[36], __b[36], __a[37], __b[37], __a[38], __b[38], __a[39], __b[39],
__a[48], __b[48], __a[49], __b[49], __a[50], __b[50], __a[51], __b[51],
__a[52], __b[52], __a[53], __b[53], __a[54], __b[54], __a[55], __b[55]};
else
__assert_unreachable<_Tp>();
}
template <class _A,
class _B,
class _Tp = std::common_type_t<_A, _B>,
class _Trait = _VectorTraits<_Tp>>
_GLIBCXX_SIMD_INTRINSIC constexpr _Tp
__interleave128_hi(const _A& _a, const _B& _b)
{
const _Tp __a(_a);
const _Tp __b(_b);
if constexpr (sizeof(_Tp) == 16)
return __interleave_hi(__a, __b);
else if constexpr (sizeof(_Tp) == 32 && _Trait::_S_width == 4)
return _Tp{__a[1], __b[1], __a[3], __b[3]};
else if constexpr (sizeof(_Tp) == 32 && _Trait::_S_width == 8)
return _Tp{__a[2], __b[2], __a[3], __b[3], __a[6], __b[6], __a[7], __b[7]};
else if constexpr (sizeof(_Tp) == 32 && _Trait::_S_width == 16)
return _Tp{__a[4], __b[4], __a[5], __b[5], __a[6], __b[6],
__a[7], __b[7], __a[12], __b[12], __a[13], __b[13],
__a[14], __b[14], __a[15], __b[15]};
else if constexpr (sizeof(_Tp) == 32 && _Trait::_S_width == 32)
return _Tp{__a[8], __b[8], __a[9], __b[9], __a[10], __b[10], __a[11],
__b[11], __a[12], __b[12], __a[13], __b[13], __a[14], __b[14],
__a[15], __b[15], __a[24], __b[24], __a[25], __b[25], __a[26],
__b[26], __a[27], __b[27], __a[28], __b[28], __a[29], __b[29],
__a[30], __b[30], __a[31], __b[31]};
else if constexpr (sizeof(_Tp) == 32 && _Trait::_S_width == 64)
return _Tp{
__a[16], __b[16], __a[17], __b[17], __a[18], __b[18], __a[19], __b[19],
__a[20], __b[20], __a[21], __b[21], __a[22], __b[22], __a[23], __b[23],
__a[24], __b[24], __a[25], __b[25], __a[26], __b[26], __a[27], __b[27],
__a[28], __b[28], __a[29], __b[29], __a[30], __b[30], __a[31], __b[31],
__a[48], __b[48], __a[49], __b[49], __a[50], __b[50], __a[51], __b[51],
__a[52], __b[52], __a[53], __b[53], __a[54], __b[54], __a[55], __b[55],
__a[56], __b[56], __a[57], __b[57], __a[58], __b[58], __a[59], __b[59],
__a[60], __b[60], __a[61], __b[61], __a[62], __b[62], __a[63], __b[63]};
else if constexpr (sizeof(_Tp) == 64 && _Trait::_S_width == 8)
return _Tp{__a[1], __b[1], __a[3], __b[3], __a[5], __b[5], __a[7], __b[7]};
else if constexpr (sizeof(_Tp) == 64 && _Trait::_S_width == 16)
return _Tp{__a[2], __b[2], __a[3], __b[3], __a[6], __b[6],
__a[7], __b[7], __a[10], __b[10], __a[11], __b[11],
__a[14], __b[14], __a[15], __b[15]};
else if constexpr (sizeof(_Tp) == 64 && _Trait::_S_width == 32)
return _Tp{__a[4], __b[4], __a[5], __b[5], __a[6], __b[6], __a[7],
__b[7], __a[12], __b[12], __a[13], __b[13], __a[14], __b[14],
__a[15], __b[15], __a[20], __b[20], __a[21], __b[21], __a[22],
__b[22], __a[23], __b[23], __a[28], __b[28], __a[29], __b[29],
__a[30], __b[30], __a[31], __b[31]};
else if constexpr (sizeof(_Tp) == 64 && _Trait::_S_width == 64)
return _Tp{
__a[8], __b[8], __a[9], __b[9], __a[10], __b[10], __a[11], __b[11],
__a[12], __b[12], __a[13], __b[13], __a[14], __b[14], __a[15], __b[15],
__a[24], __b[24], __a[25], __b[25], __a[26], __b[26], __a[27], __b[27],
__a[28], __b[28], __a[29], __b[29], __a[30], __b[30], __a[31], __b[31],
__a[40], __b[40], __a[41], __b[41], __a[42], __b[42], __a[43], __b[43],
__a[44], __b[44], __a[45], __b[45], __a[46], __b[46], __a[47], __b[47],
__a[56], __b[56], __a[57], __b[57], __a[58], __b[58], __a[59], __b[59],
__a[60], __b[60], __a[61], __b[61], __a[62], __b[62], __a[63], __b[63]};
else
__assert_unreachable<_Tp>();
}
template <int... _Indices, typename _Tp, typename _TVT = _VectorTraits<_Tp>>
_Tp __vector_permute(_Tp __x)
{
static_assert(sizeof...(_Indices) == _TVT::_S_width);
return __make_vector<typename _TVT::value_type>(
(_Indices == -1 ? 0 : __x[_Indices == -1 ? 0 : _Indices])...);
}
template <int... _Indices, typename _Tp, typename _TVT = _VectorTraits<_Tp>>
_Tp __vector_shuffle(_Tp __x, _Tp __y)
{
return _Tp{(_Indices == -1 ? 0
: _Indices < _TVT::_S_width
? __x[_Indices]
: __y[_Indices - _TVT::_S_width])...};
}
template <typename _Tp, typename _TVT = _VectorTraits<_Tp>>
_GLIBCXX_SIMD_INTRINSIC constexpr bool __is_zero(_Tp __a)
{
#if _GLIBCXX_SIMD_X86INTRIN
if (!__builtin_is_constant_evaluated())
{
if constexpr (__have_avx)
{
if constexpr (sizeof(_Tp) == 32 && _TVT::template __is<float>)
return _mm256_testz_ps(__a, __a);
else if constexpr (sizeof(_Tp) == 32 && _TVT::template __is<double>)
return _mm256_testz_pd(__a, __a);
else if constexpr (sizeof(_Tp) == 32)
return _mm256_testz_si256(__to_intrin(__a), __to_intrin(__a));
else if constexpr (_TVT::template __is<float, 4>)
return _mm_testz_ps(__a, __a);
else if constexpr (_TVT::template __is<double, 2>)
return _mm_testz_pd(__a, __a);
else
return _mm_testz_si128(__to_intrin(__a), __to_intrin(__a));
}
else if constexpr (__have_sse4_1)
return _mm_testz_si128(__vector_bitcast<_LLong>(__a),
__vector_bitcast<_LLong>(__a));
}
#endif
const auto __b = __vector_bitcast<_LLong>(__a);
static_assert(sizeof(_LLong) == 8);
if constexpr (sizeof(__b) == 8)
return __b[0] == 0;
else if constexpr (sizeof(__b) == 16)
return (__b[0] | __b[1]) == 0;
else if constexpr (sizeof(__b) == 32)
return __is_zero(__lo128(__b) | __hi128(__b));
else if constexpr (sizeof(__b) == 64)
return __is_zero(__lo256(__b) | __hi256(__b));
else
__assert_unreachable<_Tp>();
}
#if _GLIBCXX_SIMD_X86INTRIN
template <typename _Tp, typename _TVT = _VectorTraits<_Tp>>
_GLIBCXX_SIMD_INTRINSIC _GLIBCXX_SIMD_CONST int __movemask(_Tp __a)
{
if constexpr (__have_sse && _TVT::template __is<float, 4>) {
return _mm_movemask_ps(__a);
} else if constexpr (__have_avx && _TVT::template __is<float, 8>) {
return _mm256_movemask_ps(__a);
} else if constexpr (__have_sse2 && _TVT::template __is<double, 2>) {
return _mm_movemask_pd(__a);
} else if constexpr (__have_avx && _TVT::template __is<double, 4>) {
return _mm256_movemask_pd(__a);
} else if constexpr (__have_sse2 && sizeof(_Tp) == 16) {
return _mm_movemask_epi8(__a);
} else if constexpr (__have_avx2 && sizeof(_Tp) == 32) {
return _mm256_movemask_epi8(__a);
} else {
__assert_unreachable<_Tp>();
}
}
template <typename _Tp, typename _TVT = _VectorTraits<_Tp>>
_GLIBCXX_SIMD_INTRINSIC _GLIBCXX_SIMD_CONST int movemask_epi16(_Tp __a)
{
static_assert(std::is_integral_v<typename _TVT::value_type>);
if constexpr(__have_avx512bw_vl && sizeof(_Tp) == 16) {
return _mm_cmp_epi16_mask(__a, __m128i(), _MM_CMPINT_NE);
} else if constexpr(__have_avx512bw_vl && sizeof(_Tp) == 32) {
return _mm256_cmp_epi16_mask(__a, __m256i(), _MM_CMPINT_NE);
} else if constexpr(sizeof(_Tp) == 32) {
return _mm_movemask_epi8(_mm_packs_epi16(__lo128(__a), __hi128(__a)));
} else {
static_assert(sizeof(_Tp) == 16);
return _mm_movemask_epi8(_mm_packs_epi16(__a, __m128i()));
}
}
#endif
template <typename _Tp, typename _TVT = _VectorTraits<_Tp>>
_GLIBCXX_SIMD_INTRINSIC _GLIBCXX_SIMD_CONST constexpr int
__testz(_Tp __a, _Tp __b)
{
#if _GLIBCXX_SIMD_X86INTRIN
if (!__builtin_is_constant_evaluated())
{
if constexpr (__have_avx)
{
if constexpr (sizeof(_Tp) == 32 && _TVT::template __is<float>)
return _mm256_testz_ps(__a, __b);
else if constexpr (sizeof(_Tp) == 32 && _TVT::template __is<double>)
return _mm256_testz_pd(__a, __b);
else if constexpr (sizeof(_Tp) == 32)
return _mm256_testz_si256(__to_intrin(__a), __to_intrin(__b));
else if constexpr (_TVT::template __is<float, 4>)
return _mm_testz_ps(__a, __b);
else if constexpr (_TVT::template __is<double, 2>)
return _mm_testz_pd(__a, __b);
else
return _mm_testz_si128(__to_intrin(__a), __to_intrin(__b));
}
else if constexpr (__have_sse4_1)
return _mm_testz_si128(__vector_bitcast<_LLong>(__a),
__vector_bitcast<_LLong>(__b));
else
return __movemask(0 == __and(__a, __b)) != 0;
}
#endif
return __is_zero(__and(__a, __b));
}
template <typename _Tp, typename _TVT = _VectorTraits<_Tp>>
_GLIBCXX_SIMD_INTRINSIC _GLIBCXX_SIMD_CONST constexpr int
__testc(_Tp __a, _Tp __b)
{
#if _GLIBCXX_SIMD_X86INTRIN
if (!__builtin_is_constant_evaluated())
{
if constexpr (__have_avx)
{
if constexpr (sizeof(_Tp) == 32 && _TVT::template __is<float>)
return _mm256_testc_ps(__a, __b);
else if constexpr (sizeof(_Tp) == 32 && _TVT::template __is<double>)
return _mm256_testc_pd(__a, __b);
else if constexpr (sizeof(_Tp) == 32)
return _mm256_testc_si256(__to_intrin(__a), __to_intrin(__b));
else if constexpr (_TVT::template __is<float, 4>)
return _mm_testc_ps(__a, __b);
else if constexpr (_TVT::template __is<double, 2>)
return _mm_testc_pd(__a, __b);
else
return _mm_testc_si128(__to_intrin(__a), __to_intrin(__b));
}
else if constexpr (__have_sse4_1)
return _mm_testc_si128(__vector_bitcast<_LLong>(__a),
__vector_bitcast<_LLong>(__b));
else
return __movemask(0 == __andnot(__a, __b)) != 0;
}
#endif
return __is_zero(__andnot(__a, __b));
}
template <typename _Tp, typename _TVT = _VectorTraits<_Tp>>
_GLIBCXX_SIMD_INTRINSIC _GLIBCXX_SIMD_CONST constexpr int __testnzc(_Tp __a, _Tp __b)
{
#if _GLIBCXX_SIMD_X86INTRIN
if (!__builtin_is_constant_evaluated())
{
if constexpr (__have_avx)
{
if constexpr (sizeof(_Tp) == 32 && _TVT::template __is<float>)
return _mm256_testnzc_ps(__a, __b);
else if constexpr (sizeof(_Tp) == 32 && _TVT::template __is<double>)
return _mm256_testnzc_pd(__a, __b);
else if constexpr (sizeof(_Tp) == 32)
return _mm256_testnzc_si256(__to_intrin(__a), __to_intrin(__b));
else if constexpr (_TVT::template __is<float, 4>)
return _mm_testnzc_ps(__a, __b);
else if constexpr (_TVT::template __is<double, 2>)
return _mm_testnzc_pd(__a, __b);
else
return _mm_testnzc_si128(__to_intrin(__a), __to_intrin(__b));
}
else if constexpr (__have_sse4_1)
return _mm_testnzc_si128(__vector_bitcast<_LLong>(__a),
__vector_bitcast<_LLong>(__b));
else
return __movemask(0 == __and(__a, __b)) == 0 &&
__movemask(0 == __andnot(__a, __b)) == 0;
}
#endif
return !(__is_zero(__and(__a, __b)) || __is_zero(__andnot(__a, __b)));
}
#if _GLIBCXX_SIMD_HAVE_SSE_ABI
#if _GLIBCXX_SIMD_HAVE_AVX512F
template <size_t _Size>
struct __bool_storage_member_type
{
static_assert((_Size & (_Size - 1)) == 0,
"This trait may only be used for non-power-of-2 sizes. "
"Power-of-2 sizes must be specialized.");
using type =
typename __bool_storage_member_type<__next_power_of_2(_Size)>::type;
};
template <> struct __bool_storage_member_type< 2> { using type = __mmask8 ; };
template <> struct __bool_storage_member_type< 4> { using type = __mmask8 ; };
template <> struct __bool_storage_member_type< 8> { using type = __mmask8 ; };
template <> struct __bool_storage_member_type<16> { using type = __mmask16; };
template <> struct __bool_storage_member_type<32> { using type = __mmask32; };
template <> struct __bool_storage_member_type<64> { using type = __mmask64; };
#endif
#if _GLIBCXX_SIMD_HAVE_SSE
template <>
struct __intrinsic_type<double, 64, void>
{
using type [[__gnu__::__vector_size__(64)]] = double;
};
template <>
struct __intrinsic_type<float, 64, void>
{
using type [[__gnu__::__vector_size__(64)]] = float;
};
template <typename _Tp>
struct __intrinsic_type<_Tp, 64, enable_if_t<is_integral_v<_Tp>>>
{
using type [[__gnu__::__vector_size__(64)]] = long long int;
};
template <>
struct __intrinsic_type<double, 32, void>
{
using type [[__gnu__::__vector_size__(32)]] = double;
};
template <>
struct __intrinsic_type<float, 32, void>
{
using type [[__gnu__::__vector_size__(32)]] = float;
};
template <typename _Tp>
struct __intrinsic_type<_Tp, 32, enable_if_t<is_integral_v<_Tp>>>
{
using type [[__gnu__::__vector_size__(32)]] = long long int;
};
template <>
struct __intrinsic_type<float, 16, void>
{
using type [[__gnu__::__vector_size__(16)]] = float;
};
template <>
struct __intrinsic_type<float, 8, void>
{
using type [[__gnu__::__vector_size__(16)]] = float;
};
template <>
struct __intrinsic_type<float, 4, void>
{
using type [[__gnu__::__vector_size__(16)]] = float;
};
template <>
struct __intrinsic_type<double, 16, void>
{
using type [[__gnu__::__vector_size__(16)]] = double;
};
template <>
struct __intrinsic_type<double, 8, void>
{
using type [[__gnu__::__vector_size__(16)]] = double;
};
template <typename _Tp, size_t _Bytes>
struct __intrinsic_type<
_Tp,
_Bytes,
enable_if_t<(_Bytes <= 16 && _Bytes >= sizeof(_Tp) &&
((_Bytes - 1) & _Bytes) == 0 && is_integral_v<_Tp>)>>
{
using type [[__gnu__::__vector_size__(16)]] = long long int;
};
#endif
template <typename _Tp> using _SseSimdMember = _SimdWrapper16<_Tp>;
template <typename _Tp> using _SseMaskMember = _SimdWrapper16<_Tp>;
template <typename _Tp> using _AvxSimdMember = _SimdWrapper32<_Tp>;
template <typename _Tp> using _AvxMaskMember = _SimdWrapper32<_Tp>;
template <typename _Tp> using _Avx512SimdMember = _SimdWrapper64<_Tp>;
template <typename _Tp> using _Avx512MaskMember = _SimdWrapper<bool, 64 / sizeof(_Tp)>;
template <size_t _N> using _Avx512MaskMemberN = _SimdWrapper<bool, _N>;
#endif
#if _GLIBCXX_SIMD_HAVE_NEON
#define _GLIBCXX_SIMD_NEON_INTRIN(_Tp) \
template <> \
struct __intrinsic_type<__remove_cvref_t<decltype(_Tp()[0])>, sizeof(_Tp), \
void> \
{ \
using type = _Tp; \
}
_GLIBCXX_SIMD_NEON_INTRIN(int8x8_t);
_GLIBCXX_SIMD_NEON_INTRIN(int8x16_t);
_GLIBCXX_SIMD_NEON_INTRIN(int16x4_t);
_GLIBCXX_SIMD_NEON_INTRIN(int16x8_t);
_GLIBCXX_SIMD_NEON_INTRIN(int32x2_t);
_GLIBCXX_SIMD_NEON_INTRIN(int32x4_t);
_GLIBCXX_SIMD_NEON_INTRIN(int64x1_t);
_GLIBCXX_SIMD_NEON_INTRIN(int64x2_t);
_GLIBCXX_SIMD_NEON_INTRIN(uint8x8_t);
_GLIBCXX_SIMD_NEON_INTRIN(uint8x16_t);
_GLIBCXX_SIMD_NEON_INTRIN(uint16x4_t);
_GLIBCXX_SIMD_NEON_INTRIN(uint16x8_t);
_GLIBCXX_SIMD_NEON_INTRIN(uint32x2_t);
_GLIBCXX_SIMD_NEON_INTRIN(uint32x4_t);
_GLIBCXX_SIMD_NEON_INTRIN(uint64x1_t);
_GLIBCXX_SIMD_NEON_INTRIN(uint64x2_t);
_GLIBCXX_SIMD_NEON_INTRIN(float16x4_t);
_GLIBCXX_SIMD_NEON_INTRIN(float16x8_t);
_GLIBCXX_SIMD_NEON_INTRIN(float32x2_t);
_GLIBCXX_SIMD_NEON_INTRIN(float32x4_t);
_GLIBCXX_SIMD_NEON_INTRIN(float64x1_t);
_GLIBCXX_SIMD_NEON_INTRIN(float64x2_t);
#undef _GLIBCXX_SIMD_NEON_INTRIN
template <typename _Tp, size_t _Bytes>
struct __intrinsic_type<_Tp,
_Bytes,
enable_if_t<(_Bytes <= 16 && _Bytes >= sizeof(_Tp) &&
((_Bytes - 1) & _Bytes) == 0)>>
{
static constexpr int _VBytes = _Bytes <= 8 ? 8 : 16;
using _Tmp =
conditional_t<sizeof(_Tp) == 1, __remove_cvref_t<decltype(int8x16_t()[0])>,
conditional_t<sizeof(_Tp) == 2, short,
conditional_t<sizeof(_Tp) == 4, int,
conditional_t<sizeof(_Tp) == 8, __remove_cvref_t<decltype(int64x2_t()[0])>,
void>>>>;
using _U = conditional_t<is_floating_point_v<_Tp>, _Tp,
conditional_t<is_unsigned_v<_Tp>, make_unsigned_t<_Tmp>, _Tmp>>;
using type = typename __intrinsic_type<_U, _VBytes>::type;
};
#endif
template <size_t _Width>
struct _SimdWrapper<
bool,
_Width,
std::void_t<typename __bool_storage_member_type<_Width>::type>>
{
using _BuiltinType = typename __bool_storage_member_type<_Width>::type;
using value_type = bool;
static constexpr size_t _S_width = _Width;
_GLIBCXX_SIMD_INTRINSIC constexpr _SimdWrapper() = default;
_GLIBCXX_SIMD_INTRINSIC constexpr _SimdWrapper(_BuiltinType __k)
: _M_data(__k){};
_GLIBCXX_SIMD_INTRINSIC _GLIBCXX_SIMD_PURE
operator const _BuiltinType&() const
{
return _M_data;
}
_GLIBCXX_SIMD_INTRINSIC _GLIBCXX_SIMD_PURE operator _BuiltinType&()
{
return _M_data;
}
_GLIBCXX_SIMD_INTRINSIC _BuiltinType __intrin() const { return _M_data; }
_GLIBCXX_SIMD_INTRINSIC _GLIBCXX_SIMD_PURE value_type
operator[](size_t __i) const
{
return _M_data & (_BuiltinType(1) << __i);
}
_GLIBCXX_SIMD_INTRINSIC void __set(size_t __i, value_type __x)
{
if (__x)
_M_data |= (_BuiltinType(1) << __i);
else
_M_data &= ~(_BuiltinType(1) << __i);
}
_BuiltinType _M_data;
};
template <
typename _Tp,
size_t _Width,
typename _RegisterType = __vector_type_t<_Tp, _Width>,
bool = std::disjunction_v<
std::is_same<__vector_type_t<_Tp, _Width>, __intrinsic_type_t<_Tp, _Width>>,
std::is_same<_RegisterType, __intrinsic_type_t<_Tp, _Width>>>>
struct _SimdWrapperBase;
template <typename _Tp, size_t _Width, typename _RegisterType>
struct _SimdWrapperBase<_Tp, _Width, _RegisterType, true>
{
_RegisterType _M_data;
_GLIBCXX_SIMD_INTRINSIC constexpr _SimdWrapperBase() = default;
_GLIBCXX_SIMD_INTRINSIC constexpr _SimdWrapperBase(
__vector_type_t<_Tp, _Width> __x)
: _M_data(reinterpret_cast<_RegisterType>(__x))
{
}
};
template <typename _Tp, size_t _Width, typename _RegisterType>
struct _SimdWrapperBase<_Tp, _Width, _RegisterType, false>
{
using _IntrinType = __intrinsic_type_t<_Tp, _Width>;
_RegisterType _M_data;
_GLIBCXX_SIMD_INTRINSIC constexpr _SimdWrapperBase() = default;
_GLIBCXX_SIMD_INTRINSIC constexpr _SimdWrapperBase(
__vector_type_t<_Tp, _Width> __x)
: _M_data(reinterpret_cast<_RegisterType>(__x))
{
}
_GLIBCXX_SIMD_INTRINSIC constexpr _SimdWrapperBase(_IntrinType __x)
: _M_data(reinterpret_cast<_RegisterType>(__x))
{
}
};
template <typename _Tp, size_t _Width>
struct _SimdWrapper<
_Tp,
_Width,
std::void_t<__vector_type_t<_Tp, _Width>, __intrinsic_type_t<_Tp, _Width>>>
: _SimdWrapperBase<_Tp, _Width>
{
static_assert(__is_vectorizable_v<_Tp>);
static_assert(_Width >= 2);
using _BuiltinType = __vector_type_t<_Tp, _Width>;
using value_type = _Tp;
static constexpr size_t _S_width = _Width;
_GLIBCXX_SIMD_INTRINSIC constexpr _SimdWrapper() = default;
template <
typename _U,
typename = decltype(_SimdWrapperBase<_Tp, _Width>(std::declval<_U>()))>
_GLIBCXX_SIMD_INTRINSIC constexpr _SimdWrapper(_U&& __x)
: _SimdWrapperBase<_Tp, _Width>(std::forward<_U>(__x))
{
}
using _SimdWrapperBase<_Tp, _Width>::_M_data;
template <
typename... _As,
typename = enable_if_t<((std::is_same_v<simd_abi::scalar, _As> && ...) &&
sizeof...(_As) <= _Width)>>
_GLIBCXX_SIMD_INTRINSIC constexpr operator _SimdTuple<_Tp, _As...>() const
{
const auto& dd = _M_data;
return __generate_from_n_evaluations<sizeof...(_As),
_SimdTuple<_Tp, _As...>>(
[&](auto __i) constexpr { return dd[int(__i)]; });
}
_GLIBCXX_SIMD_INTRINSIC constexpr operator const _BuiltinType&() const
{
return _M_data;
}
_GLIBCXX_SIMD_INTRINSIC constexpr operator _BuiltinType&() { return _M_data; }
_GLIBCXX_SIMD_INTRINSIC constexpr _Tp operator[](size_t __i) const
{
return _M_data[__i];
}
_GLIBCXX_SIMD_INTRINSIC void __set(size_t __i, _Tp __x) { _M_data[__i] = __x; }
};
template <typename _Tp>
class _ToWrapper
{
_Tp _M_data;
public:
constexpr _ToWrapper(_Tp __x)
: _M_data(__x)
{
}
template <size_t _N>
constexpr operator _SimdWrapper<bool, _N>() const
{
static_assert(std::is_integral_v<_Tp>);
return static_cast<__bool_storage_member_type_t<_N>>(_M_data);
}
template <typename _U, size_t _N>
constexpr operator _SimdWrapper<_U, _N>() const
{
static_assert(__is_vector_type_v<_Tp>);
static_assert(sizeof(__vector_type_t<_U, _N>) == sizeof(_Tp));
return {reinterpret_cast<__vector_type_t<_U, _N>>(_M_data)};
}
};
template <typename _Tp,
typename _U,
size_t _M,
size_t _N = sizeof(_U) * _M / sizeof(_Tp)>
_GLIBCXX_SIMD_INTRINSIC constexpr _SimdWrapper<_Tp, _N>
__wrapper_bitcast(_SimdWrapper<_U, _M> __x)
{
static_assert(sizeof(__vector_type_t<_Tp, _N>) ==
sizeof(__vector_type_t<_U, _M>));
return reinterpret_cast<__vector_type_t<_Tp, _N>>(__x._M_data);
}
template <typename _Tp, typename... _Args>
_GLIBCXX_SIMD_INTRINSIC constexpr _SimdWrapper<_Tp, sizeof...(_Args)>
__make_wrapper(_Args&&... args)
{
return {typename _SimdWrapper<_Tp, sizeof...(_Args)>::_BuiltinType{
static_cast<_Tp>(args)...}};
}
template <typename _Tp, size_t _N, typename _G>
_GLIBCXX_SIMD_INTRINSIC constexpr _SimdWrapper<_Tp, _N>
__generate_wrapper(_G&& __gen)
{
return __generate_vector<_Tp, _N>(std::forward<_G>(__gen));
}
template <typename _Tp, typename _A0, typename _A1>
struct __fallback_abi_for_long_double
{
using type = _A0;
};
template <typename _A0, typename _A1>
struct __fallback_abi_for_long_double<long double, _A0, _A1>
{
using type = _A1;
};
template <typename _Tp, typename _A0, typename _A1>
using __fallback_abi_for_long_double_t =
typename __fallback_abi_for_long_double<_Tp, _A0, _A1>::type;
namespace simd_abi
{
template <typename _Tp>
inline constexpr int max_fixed_size = 32;
#if defined __x86_64__
template <typename _Tp>
using compatible = __fallback_abi_for_long_double_t<_Tp, __sse, scalar>;
#elif defined _GLIBCXX_SIMD_IS_AARCH64
template <typename _Tp>
using compatible = __fallback_abi_for_long_double_t<_Tp, __neon, scalar>;
#else
template <typename>
using compatible = scalar;
#endif
#if _GLIBCXX_SIMD_HAVE_FULL_AVX512_ABI
template <typename _Tp>
using native = __fallback_abi_for_long_double_t<_Tp, __avx512, scalar>;
#elif _GLIBCXX_SIMD_HAVE_AVX512_ABI
template <typename _Tp>
using native =
std::conditional_t<(sizeof(_Tp) >= 4),
__fallback_abi_for_long_double_t<_Tp, __avx512, scalar>,
__avx>;
#elif _GLIBCXX_SIMD_HAVE_FULL_AVX_ABI
template <typename _Tp>
using native = __fallback_abi_for_long_double_t<_Tp, __avx, scalar>;
#elif _GLIBCXX_SIMD_HAVE_AVX_ABI
template <typename _Tp>
using native =
std::conditional_t<std::is_floating_point<_Tp>::value,
__fallback_abi_for_long_double_t<_Tp, __avx, scalar>,
__sse>;
#elif _GLIBCXX_SIMD_HAVE_FULL_SSE_ABI
template <typename _Tp>
using native = __fallback_abi_for_long_double_t<_Tp, __sse, scalar>;
#elif _GLIBCXX_SIMD_HAVE_SSE_ABI
template <typename _Tp>
using native =
std::conditional_t<std::is_same<float, _Tp>::value, __sse, scalar>;
#elif defined _GLIBCXX_SIMD_HAVE_FULL_NEON_ABI
template <typename _Tp>
using native = __fallback_abi_for_long_double_t<_Tp, __neon, scalar>;
#else
template <typename>
using native = scalar;
#endif
#if defined _GLIBCXX_SIMD_DEFAULT_ABI
template <typename _Tp>
using __default_abi = _GLIBCXX_SIMD_DEFAULT_ABI<_Tp>;
#else
template <typename _Tp>
using __default_abi = compatible<_Tp>;
#endif
}
template <typename _Tp, typename = std::void_t<>>
struct is_abi_tag : false_type
{
};
template <typename _Tp>
struct is_abi_tag<_Tp, std::void_t<typename _Tp::_IsValidAbiTag>>
: public _Tp::_IsValidAbiTag
{
};
template <typename _Tp>
inline constexpr bool is_abi_tag_v = is_abi_tag<_Tp>::value;
template <typename _Tp>
struct is_simd : public false_type
{
};
template <typename _Tp>
inline constexpr bool is_simd_v = is_simd<_Tp>::value;
template <typename _Tp>
struct is_simd_mask : public false_type
{
};
template <typename _Tp>
inline constexpr bool is_simd_mask_v = is_simd_mask<_Tp>::value;
template <typename _Tp, typename _Abi, typename = void>
struct __simd_size_impl
{
};
template <typename _Tp, typename _Abi>
struct __simd_size_impl<
_Tp,
_Abi,
enable_if_t<std::conjunction_v<__is_vectorizable<_Tp>,
std::experimental::is_abi_tag<_Abi>>>>
: _SizeConstant<_Abi::template size<_Tp>>
{
};
template <typename _Tp, typename _Abi = simd_abi::__default_abi<_Tp>>
struct simd_size : __simd_size_impl<_Tp, _Abi>
{
};
template <typename _Tp, typename _Abi = simd_abi::__default_abi<_Tp>>
inline constexpr size_t simd_size_v = simd_size<_Tp, _Abi>::value;
template <typename _Tp, std::size_t _N, typename = void>
struct __deduce_impl;
namespace simd_abi
{
template <typename _Tp, std::size_t _N, typename...>
struct deduce : std::experimental::__deduce_impl<_Tp, _N>
{
};
template <typename _Tp, size_t _N, typename... _Abis>
using deduce_t = typename deduce<_Tp, _N, _Abis...>::type;
}
template <typename _Tp, typename _V>
struct rebind_simd;
template <typename _Tp, typename _U, typename _Abi>
struct rebind_simd<_Tp, simd<_U, _Abi>>
{
using type = simd<_Tp, simd_abi::deduce_t<_Tp, simd_size_v<_U, _Abi>, _Abi>>;
};
template <typename _Tp, typename _U, typename _Abi>
struct rebind_simd<_Tp, simd_mask<_U, _Abi>>
{
using type =
simd_mask<_Tp, simd_abi::deduce_t<_Tp, simd_size_v<_U, _Abi>, _Abi>>;
};
template <typename _Tp, typename _V>
using rebind_simd_t = typename rebind_simd<_Tp, _V>::type;
template <int _N, typename _V>
struct resize_simd;
template <int _N, typename _Tp, typename _Abi>
struct resize_simd<_N, simd<_Tp, _Abi>>
{
using type = simd<_Tp, simd_abi::deduce_t<_Tp, _N, _Abi>>;
};
template <int _N, typename _Tp, typename _Abi>
struct resize_simd<_N, simd_mask<_Tp, _Abi>>
{
using type = simd_mask<_Tp, simd_abi::deduce_t<_Tp, _N, _Abi>>;
};
template <int _N, typename _V>
using resize_simd_t = typename resize_simd<_N, _V>::type;
template <typename _Tp, typename _U = typename _Tp::value_type>
struct memory_alignment
: public _SizeConstant<__next_power_of_2(sizeof(_U) * _Tp::size())>
{
};
template <typename _Tp, typename _U = typename _Tp::value_type>
inline constexpr size_t memory_alignment_v = memory_alignment<_Tp, _U>::value;
template <typename _Tp, typename _Abi = simd_abi::__default_abi<_Tp>> class simd;
template <typename _Tp, typename _Abi> struct is_simd<simd<_Tp, _Abi>> : public true_type {};
template <typename _Tp> using native_simd = simd<_Tp, simd_abi::native<_Tp>>;
template <typename _Tp, int _N> using fixed_size_simd = simd<_Tp, simd_abi::fixed_size<_N>>;
template <typename _Tp, size_t _N> using __deduced_simd = simd<_Tp, simd_abi::deduce_t<_Tp, _N>>;
template <typename _Tp, typename _Abi = simd_abi::__default_abi<_Tp>> class simd_mask;
template <typename _Tp, typename _Abi> struct is_simd_mask<simd_mask<_Tp, _Abi>> : public true_type {};
template <typename _Tp> using native_simd_mask = simd_mask<_Tp, simd_abi::native<_Tp>>;
template <typename _Tp, int _N> using fixed_size_simd_mask = simd_mask<_Tp, simd_abi::fixed_size<_N>>;
template <typename _Tp, size_t _N>
using __deduced_simd_mask = simd_mask<_Tp, simd_abi::deduce_t<_Tp, _N>>;
template <typename _Tp, typename _Abi>
struct __get_impl<std::experimental::simd_mask<_Tp, _Abi>>
{
using _Traits = _SimdTraits<_Tp, _Abi>;
using _Impl = typename _Traits::_MaskImpl;
};
template <typename _Tp, typename _Abi>
struct __get_impl<std::experimental::simd<_Tp, _Abi>>
{
using _Traits = _SimdTraits<_Tp, _Abi>;
using _Impl = typename _Traits::_SimdImpl;
};
template <typename _Tp, typename _U, typename _A, bool = is_simd_v<_Tp>, typename = void>
struct __static_simd_cast_return_type;
template <typename _Tp, typename _A0, typename _U, typename _A>
struct __static_simd_cast_return_type<simd_mask<_Tp, _A0>, _U, _A, false, void>
: __static_simd_cast_return_type<simd<_Tp, _A0>, _U, _A> {
};
template <typename _Tp, typename _U, typename _A>
struct __static_simd_cast_return_type<_Tp, _U, _A, true,
enable_if_t<_Tp::size() == simd_size_v<_U, _A>>> {
using type = _Tp;
};
template <typename _Tp, typename _A>
struct __static_simd_cast_return_type<_Tp, _Tp, _A, false,
#ifdef _GLIBCXX_SIMD_FIX_P2TS_ISSUE66
enable_if_t<__is_vectorizable_v<_Tp>>
#else
void
#endif
> {
using type = simd<_Tp, _A>;
};
template <typename _Tp, typename = void> struct __safe_make_signed {
using type = _Tp;
};
template <typename _Tp> struct __safe_make_signed<_Tp, enable_if_t<std::is_integral_v<_Tp>>> {
using type = std::make_signed_t<std::make_unsigned_t<_Tp>>;
};
template <typename _Tp> using safe_make_signed_t = typename __safe_make_signed<_Tp>::type;
template <typename _Tp, typename _U, typename _A>
struct __static_simd_cast_return_type<_Tp, _U, _A, false,
#ifdef _GLIBCXX_SIMD_FIX_P2TS_ISSUE66
enable_if_t<__is_vectorizable_v<_Tp>>
#else
void
#endif
> {
using type =
std::conditional_t<(std::is_integral_v<_U> && std::is_integral_v<_Tp> &&
#ifndef _GLIBCXX_SIMD_FIX_P2TS_ISSUE65
std::is_signed_v<_U> != std::is_signed_v<_Tp> &&
#endif
std::is_same_v<safe_make_signed_t<_U>, safe_make_signed_t<_Tp>>),
simd<_Tp, _A>, fixed_size_simd<_Tp, simd_size_v<_U, _A>>>;
};
template <typename _To, typename, typename, typename _Native, typename _From>
_GLIBCXX_SIMD_INTRINSIC _To __mask_cast_impl(const _Native *, const _From &__x)
{
static_assert(std::is_same_v<_Native, typename __get_traits_t<_To>::_MaskMember>);
if constexpr (std::is_same_v<_Native, bool>) {
return {std::experimental::__private_init, bool(__x[0])};
} else if constexpr (std::is_same_v<_From, bool>) {
_To __r{};
__r[0] = __x;
return __r;
} else {
return {__private_init,
__convert_mask<typename __get_traits_t<_To>::_MaskMember>(__x)};
}
}
template <typename _To, typename, typename, typename _Native, size_t _N>
_GLIBCXX_SIMD_INTRINSIC _To __mask_cast_impl(const _Native *, const std::bitset<_N> &__x)
{
static_assert(_N <= sizeof(_ULLong) * CHAR_BIT ||
_To::size() <= sizeof(_ULLong) * CHAR_BIT,
"bug in std::experimental::(static|resizing)_simd_cast");
return {std::experimental::__bitset_init, __x.to_ullong()};
}
template <typename _To, typename, typename>
_GLIBCXX_SIMD_INTRINSIC _To __mask_cast_impl(const bool *, bool __x)
{
return _To(__x);
}
template <typename _To, typename, typename>
_GLIBCXX_SIMD_INTRINSIC _To __mask_cast_impl(const std::bitset<1> *, bool __x)
{
return _To(__x);
}
template <typename _To, typename _Tp, typename _Abi, size_t _N, typename _From>
_GLIBCXX_SIMD_INTRINSIC _To __mask_cast_impl(const std::bitset<_N> *, const _From &__x)
{
return {std::experimental::__private_init, __vector_to_bitset(__x)};
}
template <typename _To, typename, typename, size_t _N>
_GLIBCXX_SIMD_INTRINSIC _To __mask_cast_impl(const std::bitset<_N> *, const std::bitset<_N> &__x)
{
return {std::experimental::__private_init, __x};
}
template <typename _Tp, typename _U, typename _A,
typename _R = typename __static_simd_cast_return_type<_Tp, _U, _A>::type>
_GLIBCXX_SIMD_INTRINSIC _R static_simd_cast(const simd<_U, _A> &__x)
{
if constexpr(std::is_same<_R, simd<_U, _A>>::value) {
return __x;
} else {
_SimdConverter<_U, _A, typename _R::value_type, typename _R::abi_type> __c;
return _R(__private_init, __c(__data(__x)));
}
}
template <typename _Tp, typename _U, typename _A,
typename _R = typename __static_simd_cast_return_type<_Tp, _U, _A>::type>
_GLIBCXX_SIMD_INTRINSIC typename _R::mask_type static_simd_cast(const simd_mask<_U, _A> &__x)
{
using _RM = typename _R::mask_type;
if constexpr(std::is_same<_RM, simd_mask<_U, _A>>::value) {
return __x;
} else {
using __traits = _SimdTraits<typename _R::value_type, typename _R::abi_type>;
const typename __traits::_MaskMember *tag = nullptr;
return __mask_cast_impl<_RM, _U, _A>(tag, __data(__x));
}
}
template <typename _Tp, typename _U, typename _A, typename _To = __value_type_or_identity_t<_Tp>>
_GLIBCXX_SIMD_INTRINSIC auto simd_cast(const simd<_ValuePreserving<_U, _To>, _A> &__x)
->decltype(static_simd_cast<_Tp>(__x))
{
return static_simd_cast<_Tp>(__x);
}
template <typename _Tp, typename _U, typename _A, typename _To = __value_type_or_identity_t<_Tp>>
_GLIBCXX_SIMD_INTRINSIC auto simd_cast(const simd_mask<_ValuePreserving<_U, _To>, _A> &__x)
->decltype(static_simd_cast<_Tp>(__x))
{
return static_simd_cast<_Tp>(__x);
}
namespace __proposed
{
template <typename _Tp, typename _U, typename _A>
_GLIBCXX_SIMD_INTRINSIC _Tp resizing_simd_cast(const simd_mask<_U, _A> &__x)
{
static_assert(is_simd_mask_v<_Tp>);
if constexpr (std::is_same_v<_Tp, simd_mask<_U, _A>>) {
return __x;
} else {
using __traits = _SimdTraits<typename _Tp::simd_type::value_type, typename _Tp::abi_type>;
const typename __traits::_MaskMember *tag = nullptr;
return __mask_cast_impl<_Tp, _U, _A>(tag, __data(__x));
}
}
}
template <typename _Tp, int _N>
_GLIBCXX_SIMD_INTRINSIC fixed_size_simd<_Tp, _N> to_fixed_size(const fixed_size_simd<_Tp, _N> &__x)
{
return __x;
}
template <typename _Tp, int _N>
_GLIBCXX_SIMD_INTRINSIC fixed_size_simd_mask<_Tp, _N> to_fixed_size(const fixed_size_simd_mask<_Tp, _N> &__x)
{
return __x;
}
template <typename _Tp, typename _A> _GLIBCXX_SIMD_INTRINSIC auto to_fixed_size(const simd<_Tp, _A> &__x)
{
return simd<_Tp, simd_abi::fixed_size<simd_size_v<_Tp, _A>>>(
[&__x](auto __i) constexpr { return __x[__i]; });
}
template <typename _Tp, typename _A> _GLIBCXX_SIMD_INTRINSIC auto to_fixed_size(const simd_mask<_Tp, _A> &__x)
{
constexpr int _N = simd_mask<_Tp, _A>::size();
fixed_size_simd_mask<_Tp, _N> __r;
__execute_n_times<_N>([&](auto __i) constexpr { __r[__i] = __x[__i]; });
return __r;
}
template <typename _Tp, int _N>
_GLIBCXX_SIMD_INTRINSIC enable_if_t<(_N == native_simd<_Tp>::size()), native_simd<_Tp>>
to_native(const fixed_size_simd<_Tp, _N> &__x)
{
alignas(memory_alignment_v<native_simd<_Tp>>) _Tp __mem[_N];
__x.copy_to(__mem, vector_aligned);
return {__mem, vector_aligned};
}
template <typename _Tp, size_t _N>
_GLIBCXX_SIMD_INTRINSIC enable_if_t<(_N == native_simd_mask<_Tp>::size()), native_simd_mask<_Tp>> to_native(
const fixed_size_simd_mask<_Tp, _N> &__x)
{
return native_simd_mask<_Tp>([&](auto __i) constexpr { return __x[__i]; });
}
template <typename _Tp, size_t _N>
_GLIBCXX_SIMD_INTRINSIC enable_if_t<(_N == simd<_Tp>::size()), simd<_Tp>> to_compatible(
const simd<_Tp, simd_abi::fixed_size<_N>> &__x)
{
alignas(memory_alignment_v<simd<_Tp>>) _Tp __mem[_N];
__x.copy_to(__mem, vector_aligned);
return {__mem, vector_aligned};
}
template <typename _Tp, size_t _N>
_GLIBCXX_SIMD_INTRINSIC enable_if_t<(_N == simd_mask<_Tp>::size()), simd_mask<_Tp>> to_compatible(
const simd_mask<_Tp, simd_abi::fixed_size<_N>> &__x)
{
return simd_mask<_Tp>([&](auto __i) constexpr { return __x[__i]; });
}
template <typename _To, size_t _N> _GLIBCXX_SIMD_INTRINSIC _To __simd_reinterpret_cast_impl(std::bitset<_N> __x)
{
return {__bitset_init, __x};
}
template <typename _To, typename _Tp, size_t _N>
_GLIBCXX_SIMD_INTRINSIC _To __simd_reinterpret_cast_impl(_SimdWrapper<_Tp, _N> __x)
{
return {__private_init, __x};
}
namespace __proposed
{
template <typename _To,
typename _Tp,
typename _A,
typename = enable_if_t<sizeof(_To) == sizeof(simd<_Tp, _A>) &&
(is_simd_v<_To> || is_simd_mask_v<_To>)>>
_GLIBCXX_SIMD_INTRINSIC _To simd_reinterpret_cast(const simd<_Tp, _A>& __x)
{
_To __r;
std::memcpy(&__data(__r), &__data(__x), sizeof(_To));
return __r;
}
template <typename _To, typename _Tp, typename _A,
typename = enable_if_t<(is_simd_v<_To> || is_simd_mask_v<_To>)>>
_GLIBCXX_SIMD_INTRINSIC _To simd_reinterpret_cast(const simd_mask<_Tp, _A> &__x)
{
return std::experimental::__simd_reinterpret_cast_impl<_To>(__data(__x));
}
}
template <class _M, class _Tp> class const_where_expression
{
using _V = _Tp;
static_assert(std::is_same_v<_V, __remove_cvref_t<_Tp>>);
struct Wrapper {
using value_type = _V;
};
protected:
using value_type =
typename std::conditional_t<std::is_arithmetic<_V>::value, Wrapper, _V>::value_type;
_GLIBCXX_SIMD_INTRINSIC friend const _M &__get_mask(const const_where_expression &__x) { return __x.__k; }
_GLIBCXX_SIMD_INTRINSIC friend const _Tp &__get_lvalue(const const_where_expression &__x) { return __x._M_value; }
const _M &__k;
_Tp &_M_value;
public:
const_where_expression(const const_where_expression &) = delete;
const_where_expression &operator=(const const_where_expression &) = delete;
_GLIBCXX_SIMD_INTRINSIC const_where_expression(const _M &__kk, const _Tp &dd) : __k(__kk), _M_value(const_cast<_Tp &>(dd)) {}
_GLIBCXX_SIMD_INTRINSIC _V operator-() const &&
{
return {__private_init,
__get_impl_t<_V>::template __masked_unary<std::negate>(
__data(__k), __data(_M_value))};
}
template <class _U, class _Flags>
[[nodiscard]] _GLIBCXX_SIMD_INTRINSIC _V
copy_from(const _LoadStorePtr<_U, value_type> *__mem, _Flags __f) const &&
{
return {__private_init, __get_impl_t<_V>::__masked_load(
__data(_M_value), __data(__k), __mem, __f)};
}
template <class _U, class _Flags>
_GLIBCXX_SIMD_INTRINSIC void copy_to(_LoadStorePtr<_U, value_type> *__mem,
_Flags __f) const &&
{
__get_impl_t<_V>::__masked_store(__data(_M_value), __mem, __f, __data(__k));
}
};
template <class _Tp> class const_where_expression<bool, _Tp>
{
using _M = bool;
using _V = _Tp;
static_assert(std::is_same_v<_V, __remove_cvref_t<_Tp>>);
struct Wrapper {
using value_type = _V;
};
protected:
using value_type =
typename std::conditional_t<std::is_arithmetic<_V>::value, Wrapper, _V>::value_type;
_GLIBCXX_SIMD_INTRINSIC friend const _M &__get_mask(const const_where_expression &__x) { return __x.__k; }
_GLIBCXX_SIMD_INTRINSIC friend const _Tp &__get_lvalue(const const_where_expression &__x) { return __x._M_value; }
const bool __k;
_Tp &_M_value;
public:
const_where_expression(const const_where_expression &) = delete;
const_where_expression &operator=(const const_where_expression &) = delete;
_GLIBCXX_SIMD_INTRINSIC const_where_expression(const bool __kk, const _Tp &dd) : __k(__kk), _M_value(const_cast<_Tp &>(dd)) {}
_GLIBCXX_SIMD_INTRINSIC _V operator-() const && { return __k ? -_M_value : _M_value; }
template <class _U, class _Flags>
[[nodiscard]] _GLIBCXX_SIMD_INTRINSIC _V
copy_from(const _LoadStorePtr<_U, value_type> *__mem, _Flags) const &&
{
return __k ? static_cast<_V>(__mem[0]) : _M_value;
}
template <class _U, class _Flags>
_GLIBCXX_SIMD_INTRINSIC void copy_to(_LoadStorePtr<_U, value_type> *__mem,
_Flags) const &&
{
if (__k) {
__mem[0] = _M_value;
}
}
};
template <class _M, class _Tp>
class where_expression : public const_where_expression<_M, _Tp>
{
static_assert(!std::is_const<_Tp>::value, "where_expression may only be instantiated with __a non-const _Tp parameter");
using typename const_where_expression<_M, _Tp>::value_type;
using const_where_expression<_M, _Tp>::__k;
using const_where_expression<_M, _Tp>::_M_value;
static_assert(std::is_same<typename _M::abi_type, typename _Tp::abi_type>::value, "");
static_assert(_M::size() == _Tp::size(), "");
_GLIBCXX_SIMD_INTRINSIC friend _Tp &__get_lvalue(where_expression &__x) { return __x._M_value; }
public:
where_expression(const where_expression &) = delete;
where_expression &operator=(const where_expression &) = delete;
_GLIBCXX_SIMD_INTRINSIC where_expression(const _M &__kk, _Tp &dd)
: const_where_expression<_M, _Tp>(__kk, dd)
{
}
template <class _U> _GLIBCXX_SIMD_INTRINSIC void operator=(_U &&__x) &&
{
std::experimental::__get_impl_t<_Tp>::__masked_assign(
__data(__k), __data(_M_value),
__to_value_type_or_member_type<_Tp>(std::forward<_U>(__x)));
}
#define _GLIBCXX_SIMD_OP_(op_,name_) \
template <class _U> _GLIBCXX_SIMD_INTRINSIC void operator op_##=(_U&& __x)&& \
{ \
std::experimental::__get_impl_t<_Tp>::template __masked_cassign<name_>( \
__data(__k), __data(_M_value), \
__to_value_type_or_member_type<_Tp>(std::forward<_U>(__x))); \
} \
static_assert(true)
_GLIBCXX_SIMD_OP_(+, std::plus);
_GLIBCXX_SIMD_OP_(-, std::minus);
_GLIBCXX_SIMD_OP_(*, std::multiplies);
_GLIBCXX_SIMD_OP_(/, std::divides);
_GLIBCXX_SIMD_OP_(%, std::modulus);
_GLIBCXX_SIMD_OP_(&, std::bit_and);
_GLIBCXX_SIMD_OP_(|, std::bit_or);
_GLIBCXX_SIMD_OP_(^, std::bit_xor);
_GLIBCXX_SIMD_OP_(<<, __shift_left);
_GLIBCXX_SIMD_OP_(>>, __shift_right);
#undef _GLIBCXX_SIMD_OP_
_GLIBCXX_SIMD_INTRINSIC void operator++() &&
{
__data(_M_value) = __get_impl_t<_Tp>::template __masked_unary<__increment>(
__data(__k), __data(_M_value));
}
_GLIBCXX_SIMD_INTRINSIC void operator++(int) &&
{
__data(_M_value) = __get_impl_t<_Tp>::template __masked_unary<__increment>(
__data(__k), __data(_M_value));
}
_GLIBCXX_SIMD_INTRINSIC void operator--() &&
{
__data(_M_value) = __get_impl_t<_Tp>::template __masked_unary<__decrement>(
__data(__k), __data(_M_value));
}
_GLIBCXX_SIMD_INTRINSIC void operator--(int) &&
{
__data(_M_value) = __get_impl_t<_Tp>::template __masked_unary<__decrement>(
__data(__k), __data(_M_value));
}
template <class _U, class _Flags>
_GLIBCXX_SIMD_INTRINSIC void copy_from(const _LoadStorePtr<_U, value_type> *__mem,
_Flags __f) &&
{
__data(_M_value) =
__get_impl_t<_Tp>::__masked_load(__data(_M_value), __data(__k), __mem, __f);
}
};
template <class _Tp>
class where_expression<bool, _Tp> : public const_where_expression<bool, _Tp>
{
using _M = bool;
using typename const_where_expression<_M, _Tp>::value_type;
using const_where_expression<_M, _Tp>::__k;
using const_where_expression<_M, _Tp>::_M_value;
public:
where_expression(const where_expression &) = delete;
where_expression &operator=(const where_expression &) = delete;
_GLIBCXX_SIMD_INTRINSIC where_expression(const _M &__kk, _Tp &dd)
: const_where_expression<_M, _Tp>(__kk, dd)
{
}
#define _GLIBCXX_SIMD_OP_(op_) \
template <class _U> _GLIBCXX_SIMD_INTRINSIC void operator op_(_U&& __x)&& \
{ \
if (__k) { \
_M_value op_ std::forward<_U>(__x); \
} \
} \
static_assert(true)
_GLIBCXX_SIMD_OP_(=);
_GLIBCXX_SIMD_OP_(+=);
_GLIBCXX_SIMD_OP_(-=);
_GLIBCXX_SIMD_OP_(*=);
_GLIBCXX_SIMD_OP_(/=);
_GLIBCXX_SIMD_OP_(%=);
_GLIBCXX_SIMD_OP_(&=);
_GLIBCXX_SIMD_OP_(|=);
_GLIBCXX_SIMD_OP_(^=);
_GLIBCXX_SIMD_OP_(<<=);
_GLIBCXX_SIMD_OP_(>>=);
#undef _GLIBCXX_SIMD_OP_
_GLIBCXX_SIMD_INTRINSIC void operator++() && { if (__k) { ++_M_value; } }
_GLIBCXX_SIMD_INTRINSIC void operator++(int) && { if (__k) { ++_M_value; } }
_GLIBCXX_SIMD_INTRINSIC void operator--() && { if (__k) { --_M_value; } }
_GLIBCXX_SIMD_INTRINSIC void operator--(int) && { if (__k) { --_M_value; } }
template <class _U, class _Flags>
_GLIBCXX_SIMD_INTRINSIC void copy_from(const _LoadStorePtr<_U, value_type> *__mem,
_Flags) &&
{
if (__k) {
_M_value = __mem[0];
}
}
};
template <class _Tp, class _A>
_GLIBCXX_SIMD_INTRINSIC where_expression<simd_mask<_Tp, _A>, simd<_Tp, _A>> where(
const typename simd<_Tp, _A>::mask_type &__k, simd<_Tp, _A> &__value)
{
return {__k, __value};
}
template <class _Tp, class _A>
_GLIBCXX_SIMD_INTRINSIC const_where_expression<simd_mask<_Tp, _A>, simd<_Tp, _A>> where(
const typename simd<_Tp, _A>::mask_type &__k, const simd<_Tp, _A> &__value)
{
return {__k, __value};
}
template <class _Tp, class _A>
_GLIBCXX_SIMD_INTRINSIC where_expression<simd_mask<_Tp, _A>, simd_mask<_Tp, _A>> where(
const std::remove_const_t<simd_mask<_Tp, _A>> &__k, simd_mask<_Tp, _A> &__value)
{
return {__k, __value};
}
template <class _Tp, class _A>
_GLIBCXX_SIMD_INTRINSIC const_where_expression<simd_mask<_Tp, _A>, simd_mask<_Tp, _A>> where(
const std::remove_const_t<simd_mask<_Tp, _A>> &__k, const simd_mask<_Tp, _A> &__value)
{
return {__k, __value};
}
template <class _Tp>
_GLIBCXX_SIMD_INTRINSIC where_expression<bool, _Tp> where(_ExactBool __k, _Tp &__value)
{
return {__k, __value};
}
template <class _Tp>
_GLIBCXX_SIMD_INTRINSIC const_where_expression<bool, _Tp> where(_ExactBool __k, const _Tp &__value)
{
return {__k, __value};
}
template <class _Tp, class _A> void where(bool __k, simd<_Tp, _A> &__value) = delete;
template <class _Tp, class _A> void where(bool __k, const simd<_Tp, _A> &__value) = delete;
namespace __proposed
{
template <size_t _N> class where_range
{
const std::bitset<_N> __bits;
public:
where_range(std::bitset<_N> __b) : __bits(__b) {}
class iterator
{
size_t __mask;
size_t __bit;
_GLIBCXX_SIMD_INTRINSIC void __next_bit() { __bit = __builtin_ctzl(__mask); }
_GLIBCXX_SIMD_INTRINSIC void __reset_lsb()
{
__mask &= (__mask - 1);
}
public:
iterator(decltype(__mask) __m) : __mask(__m) { __next_bit(); }
iterator(const iterator &) = default;
iterator(iterator &&) = default;
_GLIBCXX_SIMD_ALWAYS_INLINE size_t operator->() const { return __bit; }
_GLIBCXX_SIMD_ALWAYS_INLINE size_t operator*() const { return __bit; }
_GLIBCXX_SIMD_ALWAYS_INLINE iterator &operator++()
{
__reset_lsb();
__next_bit();
return *this;
}
_GLIBCXX_SIMD_ALWAYS_INLINE iterator operator++(int)
{
iterator __tmp = *this;
__reset_lsb();
__next_bit();
return __tmp;
}
_GLIBCXX_SIMD_ALWAYS_INLINE bool operator==(const iterator &__rhs) const
{
return __mask == __rhs.__mask;
}
_GLIBCXX_SIMD_ALWAYS_INLINE bool operator!=(const iterator &__rhs) const
{
return __mask != __rhs.__mask;
}
};
iterator begin() const { return __bits.to_ullong(); }
iterator end() const { return 0; }
};
template <class _Tp, class _A>
where_range<simd_size_v<_Tp, _A>> where(const simd_mask<_Tp, _A> &__k)
{
return __k.__to_bitset();
}
}
template <class _Tp, class _Abi, class _BinaryOperation = std::plus<>>
_GLIBCXX_SIMD_INTRINSIC _Tp reduce(const simd<_Tp, _Abi>& __v,
_BinaryOperation __binary_op = _BinaryOperation())
{
using _V = simd<_Tp, _Abi>;
return __get_impl_t<_V>::__reduce(__v, __binary_op);
}
template <class _M, class _V, class _BinaryOperation = std::plus<>>
_GLIBCXX_SIMD_INTRINSIC typename _V::value_type reduce(
const const_where_expression<_M, _V>& __x, typename _V::value_type __identity_element,
_BinaryOperation __binary_op)
{
_V __tmp = __identity_element;
__get_impl_t<_V>::__masked_assign(__data(__get_mask(__x)), __data(__tmp),
__data(__get_lvalue(__x)));
return reduce(__tmp, __binary_op);
}
template <class _M, class _V>
_GLIBCXX_SIMD_INTRINSIC typename _V::value_type reduce(
const const_where_expression<_M, _V>& __x, std::plus<> __binary_op = {})
{
return reduce(__x, 0, __binary_op);
}
template <class _M, class _V>
_GLIBCXX_SIMD_INTRINSIC typename _V::value_type reduce(
const const_where_expression<_M, _V>& __x, std::multiplies<> __binary_op)
{
return reduce(__x, 1, __binary_op);
}
template <class _M, class _V>
_GLIBCXX_SIMD_INTRINSIC typename _V::value_type reduce(
const const_where_expression<_M, _V>& __x, std::bit_and<> __binary_op)
{
return reduce(__x, ~typename _V::value_type(), __binary_op);
}
template <class _M, class _V>
_GLIBCXX_SIMD_INTRINSIC typename _V::value_type reduce(
const const_where_expression<_M, _V>& __x, std::bit_or<> __binary_op)
{
return reduce(__x, 0, __binary_op);
}
template <class _M, class _V>
_GLIBCXX_SIMD_INTRINSIC typename _V::value_type reduce(
const const_where_expression<_M, _V>& __x, std::bit_xor<> __binary_op)
{
return reduce(__x, 0, __binary_op);
}
template <class _Tp, class _A>
_GLIBCXX_SIMD_INTRINSIC constexpr simd<_Tp, _A> min(const simd<_Tp, _A> &__a, const simd<_Tp, _A> &__b)
{
return {__private_init,
_A::_SimdImpl::__min(__data(__a), __data(__b))};
}
template <class _Tp, class _A>
_GLIBCXX_SIMD_INTRINSIC constexpr simd<_Tp, _A> max(const simd<_Tp, _A> &__a, const simd<_Tp, _A> &__b)
{
return {__private_init,
_A::_SimdImpl::__max(__data(__a), __data(__b))};
}
template <class _Tp, class _A>
_GLIBCXX_SIMD_INTRINSIC constexpr std::pair<simd<_Tp, _A>, simd<_Tp, _A>> minmax(const simd<_Tp, _A> &__a,
const simd<_Tp, _A> &__b)
{
const auto pair_of_members =
_A::_SimdImpl::__minmax(__data(__a), __data(__b));
return {simd<_Tp, _A>(__private_init, pair_of_members.first),
simd<_Tp, _A>(__private_init, pair_of_members.second)};
}
template <class _Tp, class _A>
_GLIBCXX_SIMD_INTRINSIC constexpr simd<_Tp, _A> clamp(const simd<_Tp, _A> &__v, const simd<_Tp, _A> &__lo,
const simd<_Tp, _A> &__hi)
{
using _Impl = typename _A::_SimdImpl;
return {__private_init,
_Impl::__min(__data(__hi), _Impl::__max(__data(__lo), __data(__v)))};
}
namespace __proposed
{
template <int _Stride, int _Offset = 0> struct strided {
static constexpr int _S_stride = _Stride;
static constexpr int _S_offset = _Offset;
template <class _Tp, class _A>
using __shuffle_return_type = simd<
_Tp, simd_abi::deduce_t<_Tp, (simd_size_v<_Tp, _A> - _Offset + _Stride - 1) / _Stride, _A>>;
template <class _Tp> static constexpr auto __src_index(_Tp __dst_index)
{
return _Offset + __dst_index * _Stride;
}
};
template <class _P, class _Tp, class _A,
class _R = typename _P::template __shuffle_return_type<_Tp, _A>,
class = decltype(_P::__src_index(std::experimental::_SizeConstant<0>()))>
_GLIBCXX_SIMD_INTRINSIC _R shuffle(const simd<_Tp, _A> &__x)
{
return _R([&__x](auto __i) constexpr { return __x[_P::__src_index(__i)]; });
}
}
template <size_t... _Sizes, class _Tp, class _A,
class = enable_if_t<((_Sizes + ...) == simd<_Tp, _A>::size())>>
inline std::tuple<simd<_Tp, simd_abi::deduce_t<_Tp, _Sizes>>...> split(const simd<_Tp, _A> &);
template <size_t _Index,
size_t _Total,
class _Tp,
typename _TVT = _VectorTraits<_Tp>>
_GLIBCXX_SIMD_INTRINSIC _GLIBCXX_SIMD_CONST
typename __vector_type<typename _TVT::value_type,
std::max(__min_vector_size,
int(sizeof(_Tp) / _Total))>::type
__extract_part(_Tp __x);
template <int Index, int Parts, typename _Tp, typename _A0, typename... _As>
auto __extract_part(const _SimdTuple<_Tp, _A0, _As...>& __x);
template <size_t _V0, size_t... _Values> struct _SizeList {
template <size_t _I> static constexpr size_t __at(_SizeConstant<_I> = {})
{
if constexpr (_I == 0) {
return _V0;
} else {
return _SizeList<_Values...>::template __at<_I - 1>();
}
}
template <size_t _I> static constexpr auto __before(_SizeConstant<_I> = {})
{
if constexpr (_I == 0) {
return _SizeConstant<0>();
} else {
return _SizeConstant<_V0 + _SizeList<_Values...>::template __before<_I - 1>()>();
}
}
template <size_t _N> static constexpr auto __pop_front(_SizeConstant<_N> = {})
{
if constexpr (_N == 0) {
return _SizeList();
} else {
return _SizeList<_Values...>::template __pop_front<_N-1>();
}
}
};
template <class _Tp, size_t _N>
_GLIBCXX_SIMD_INTRINSIC _SimdWrapper<_Tp, _N / 2> __extract_center(_SimdWrapper<_Tp, _N> __x)
{
if constexpr (__have_avx512f && sizeof(__x) == 64) {
const auto __intrin = __to_intrin(__x);
if constexpr (std::is_integral_v<_Tp>) {
return __vector_bitcast<_Tp>(_mm512_castsi512_si256(_mm512_shuffle_i32x4(
__intrin, __intrin, 1 + 2 * 0x4 + 2 * 0x10 + 3 * 0x40)));
} else if constexpr (sizeof(_Tp) == 4) {
return __vector_bitcast<_Tp>(_mm512_castps512_ps256(_mm512_shuffle_f32x4(
__intrin, __intrin, 1 + 2 * 0x4 + 2 * 0x10 + 3 * 0x40)));
} else if constexpr (sizeof(_Tp) == 8) {
return __vector_bitcast<_Tp>(_mm512_castpd512_pd256(_mm512_shuffle_f64x2(
__intrin, __intrin, 1 + 2 * 0x4 + 2 * 0x10 + 3 * 0x40)));
} else {
__assert_unreachable<_Tp>();
}
} else {
__assert_unreachable<_Tp>();
}
}
template <class _Tp, class _A>
inline _SimdWrapper<_Tp, simd_size_v<_Tp, _A>> __extract_center(
const _SimdTuple<_Tp, _A, _A>& __x)
{
return __concat(__extract<1, 2>(__x.first._M_data), __extract<0, 2>(__x.second.first._M_data));
}
template <class _Tp, class _A>
inline _SimdWrapper<_Tp, simd_size_v<_Tp, _A> / 2> __extract_center(
const _SimdTuple<_Tp, _A>& __x)
{
return __extract_center(__x.first);
}
template <size_t... _Sizes, class _Tp, class... _As>
auto __split_wrapper(_SizeList<_Sizes...>, const _SimdTuple<_Tp, _As...> &__x)
{
return std::experimental::split<_Sizes...>(
fixed_size_simd<_Tp, _SimdTuple<_Tp, _As...>::size()>(__private_init, __x));
}
template <class _V, class _A,
size_t Parts = simd_size_v<typename _V::value_type, _A> / _V::size()>
inline enable_if_t<(is_simd<_V>::value &&
simd_size_v<typename _V::value_type, _A> == Parts * _V::size()),
std::array<_V, Parts>>
split(const simd<typename _V::value_type, _A> &__x)
{
using _Tp = typename _V::value_type;
if constexpr (Parts == 1) {
return {simd_cast<_V>(__x)};
} else if constexpr (__is_fixed_size_abi_v<_A> &&
(std::is_same_v<typename _V::abi_type, simd_abi::scalar> ||
(__is_fixed_size_abi_v<typename _V::abi_type> &&
sizeof(_V) == sizeof(_Tp) * _V::size()
))) {
#ifdef _GLIBCXX_SIMD_USE_ALIASING_LOADS
const __may_alias<_Tp> *const __element_ptr =
reinterpret_cast<const __may_alias<_Tp> *>(&__data(__x));
return __generate_from_n_evaluations<Parts, std::array<_V, Parts>>(
[&](auto __i) constexpr { return _V(__element_ptr + __i * _V::size(), vector_aligned); });
#else
const auto &__xx = __data(__x);
return __generate_from_n_evaluations<Parts, std::array<_V, Parts>>(
[&](auto __i) constexpr {
[[maybe_unused]] constexpr size_t __offset = decltype(__i)::value * _V::size();
return _V([&](auto __j) constexpr {
constexpr _SizeConstant<__j + __offset> __k;
return __xx[__k];
});
});
#endif
} else if constexpr (std::is_same_v<typename _V::abi_type, simd_abi::scalar>) {
return __generate_from_n_evaluations<Parts, std::array<_V, Parts>>(
[&](auto __i) constexpr { return __x[__i]; });
} else {
return __generate_from_n_evaluations<Parts, std::array<_V, Parts>>([&](auto __i) constexpr {
if constexpr (__is_fixed_size_abi_v<typename _V::abi_type>) {
return _V([&](auto __j) constexpr { return __x[__i * _V::size() + __j]; });
} else {
return _V(__private_init,
__extract_part<__i, Parts>(__data(__x)));
}
});
}
}
template <typename _V,
typename _A,
size_t _Parts = simd_size_v<typename _V::simd_type::value_type, _A> /
_V::size()>
enable_if_t<(is_simd_mask_v<_V> &&
simd_size_v<typename _V::simd_type::value_type, _A> ==
_Parts * _V::size()),
std::array<_V, _Parts>>
split(const simd_mask<typename _V::simd_type::value_type, _A>& __x)
{
if constexpr (std::is_same_v<_A, typename _V::abi_type>)
{
return {__x};
}
else if constexpr (_Parts == 1)
{
return {static_simd_cast<_V>(__x)};
}
else if constexpr (_Parts == 2 &&
__is_abi<typename _V::abi_type, simd_abi::__sse>() &&
__is_abi<_A, simd_abi::__avx>())
{
return {_V(__private_init, __lo128(__data(__x))),
_V(__private_init, __hi128(__data(__x)))};
}
else if constexpr (_V::size() <= CHAR_BIT * sizeof(_ULLong))
{
const std::bitset __bits = __x.__to_bitset();
return __generate_from_n_evaluations<_Parts, std::array<_V, _Parts>>(
[&](auto __i) constexpr {
constexpr size_t __offset = __i * _V::size();
return _V(__bitset_init, (__bits >> __offset).to_ullong());
});
}
else
{
return __generate_from_n_evaluations<_Parts, std::array<_V, _Parts>>(
[&](auto __i) constexpr {
constexpr size_t __offset = __i * _V::size();
return _V(__private_init,
[&](auto __j) constexpr { return __x[__j + __offset]; });
});
}
}
template <size_t... _Sizes, class _Tp, class _A,
class = enable_if_t<((_Sizes + ...) == simd<_Tp, _A>::size())>>
_GLIBCXX_SIMD_ALWAYS_INLINE std::tuple<simd<_Tp, simd_abi::deduce_t<_Tp, _Sizes>>...> split(
const simd<_Tp, _A> &__x)
{
using _SL = _SizeList<_Sizes...>;
using _Tuple = std::tuple<__deduced_simd<_Tp, _Sizes>...>;
constexpr size_t _N = simd_size_v<_Tp, _A>;
constexpr size_t _N0 = _SL::template __at<0>();
using _V = __deduced_simd<_Tp, _N0>;
if constexpr (_N == _N0) {
static_assert(sizeof...(_Sizes) == 1);
return {simd_cast<_V>(__x)};
} else if constexpr (__is_fixed_size_abi_v<_A> &&
__fixed_size_storage_t<_Tp, _N>::_S_first_size == _N0) {
static_assert(!__is_fixed_size_abi_v<typename _V::abi_type>,
"How can <_Tp, _N> be __a single _SimdTuple entry but __a fixed_size_simd "
"when deduced?");
const __fixed_size_storage_t<_Tp, _N> &__xx = __data(__x);
return std::tuple_cat(
std::make_tuple(_V(__private_init, __xx.first)),
__split_wrapper(_SL::template __pop_front<1>(), __xx.second));
} else if constexpr ((!std::is_same_v<simd_abi::scalar,
simd_abi::deduce_t<_Tp, _Sizes>> &&
...) &&
(!__is_fixed_size_abi_v<simd_abi::deduce_t<_Tp, _Sizes>> &&
...)) {
if constexpr (((_Sizes * 2 == _N)&&...)) {
return {{__private_init, __extract_part<0, 2>(__data(__x))},
{__private_init, __extract_part<1, 2>(__data(__x))}};
} else if constexpr (std::is_same_v<_SizeList<_Sizes...>,
_SizeList<_N / 3, _N / 3, _N / 3>>) {
return {{__private_init, __extract_part<0, 3>(__data(__x))},
{__private_init, __extract_part<1, 3>(__data(__x))},
{__private_init, __extract_part<2, 3>(__data(__x))}};
} else if constexpr (std::is_same_v<_SizeList<_Sizes...>,
_SizeList<2 * _N / 3, _N / 3>>) {
return {{__private_init,
__concat(__extract_part<0, 3>(__data(__x)),
__extract_part<1, 3>(__data(__x)))},
{__private_init, __extract_part<2, 3>(__data(__x))}};
} else if constexpr (std::is_same_v<_SizeList<_Sizes...>,
_SizeList<_N / 3, 2 * _N / 3>>) {
return {{__private_init, __extract_part<0, 3>(__data(__x))},
{__private_init,
__concat(__extract_part<1, 3>(__data(__x)),
__extract_part<2, 3>(__data(__x)))}};
} else if constexpr (std::is_same_v<_SizeList<_Sizes...>,
_SizeList<_N / 2, _N / 4, _N / 4>>) {
return {{__private_init, __extract_part<0, 2>(__data(__x))},
{__private_init, __extract_part<2, 4>(__data(__x))},
{__private_init, __extract_part<3, 4>(__data(__x))}};
} else if constexpr (std::is_same_v<_SizeList<_Sizes...>,
_SizeList<_N / 4, _N / 4, _N / 2>>) {
return {{__private_init, __extract_part<0, 4>(__data(__x))},
{__private_init, __extract_part<1, 4>(__data(__x))},
{__private_init, __extract_part<1, 2>(__data(__x))}};
} else if constexpr (std::is_same_v<_SizeList<_Sizes...>,
_SizeList<_N / 4, _N / 2, _N / 4>>) {
return {
{__private_init, __extract_part<0, 4>(__data(__x))},
{__private_init, __extract_center(__data(__x))},
{__private_init, __extract_part<3, 4>(__data(__x))}};
} else if constexpr (((_Sizes * 4 == _N) && ...)) {
return {{__private_init, __extract_part<0, 4>(__data(__x))},
{__private_init, __extract_part<1, 4>(__data(__x))},
{__private_init, __extract_part<2, 4>(__data(__x))},
{__private_init, __extract_part<3, 4>(__data(__x))}};
} else {
__assert_unreachable<_Tp>();
}
} else {
#ifdef _GLIBCXX_SIMD_USE_ALIASING_LOADS
const __may_alias<_Tp> *const __element_ptr =
reinterpret_cast<const __may_alias<_Tp> *>(&__x);
return __generate_from_n_evaluations<sizeof...(_Sizes), _Tuple>([&](auto __i) constexpr {
using _Vi = __deduced_simd<_Tp, _SL::__at(__i)>;
constexpr size_t __offset = _SL::__before(__i);
constexpr size_t __base_align = alignof(simd<_Tp, _A>);
constexpr size_t __a = __base_align - ((__offset * sizeof(_Tp)) % __base_align);
constexpr size_t __b = ((__a - 1) & __a) ^ __a;
constexpr size_t __alignment = __b == 0 ? __a : __b;
return _Vi(__element_ptr + __offset, overaligned<__alignment>);
});
#else
return __generate_from_n_evaluations<sizeof...(_Sizes), _Tuple>([&](auto __i) constexpr {
using _Vi = __deduced_simd<_Tp, _SL::__at(__i)>;
const auto &__xx = __data(__x);
using _Offset = decltype(_SL::__before(__i));
return _Vi([&](auto __j) constexpr {
constexpr _SizeConstant<_Offset::value + __j> __k;
return __xx[__k];
});
});
#endif
}
}
template <size_t _I, class _Tp, class _A, class... _As>
_GLIBCXX_SIMD_INTRINSIC constexpr _Tp __subscript_in_pack(const simd<_Tp, _A> &__x, const simd<_Tp, _As> &... __xs)
{
if constexpr (_I < simd_size_v<_Tp, _A>) {
return __x[_I];
} else {
return __subscript_in_pack<_I - simd_size_v<_Tp, _A>>(__xs...);
}
}
template <class _Tp, class... _As>
simd<_Tp, simd_abi::deduce_t<_Tp, (simd_size_v<_Tp, _As> + ...)>> concat(
const simd<_Tp, _As> &... __xs)
{
return simd<_Tp, simd_abi::deduce_t<_Tp, (simd_size_v<_Tp, _As> + ...)>>(
[&](auto __i) constexpr { return __subscript_in_pack<__i>(__xs...); });
}
template <class _U, class _Accessor = _U, class _ValueType = typename _U::value_type>
class _Smart_reference
{
friend _Accessor;
int index;
_U &obj;
_GLIBCXX_SIMD_INTRINSIC constexpr _ValueType __read() const noexcept
{
if constexpr (std::is_arithmetic_v<_U>) {
_GLIBCXX_DEBUG_ASSERT(index == 0);
return obj;
} else {
return obj[index];
}
}
template <class _Tp> _GLIBCXX_SIMD_INTRINSIC constexpr void __write(_Tp &&__x) const
{
_Accessor::__set(obj, index, std::forward<_Tp>(__x));
}
public:
_GLIBCXX_SIMD_INTRINSIC constexpr _Smart_reference(_U& __o, int __i) noexcept
: index(__i), obj(__o)
{
}
using value_type = _ValueType;
_GLIBCXX_SIMD_INTRINSIC _Smart_reference(const _Smart_reference &) = delete;
_GLIBCXX_SIMD_INTRINSIC constexpr operator value_type() const noexcept { return __read(); }
template <class _Tp,
class = _ValuePreservingOrInt<__remove_cvref_t<_Tp>, value_type>>
_GLIBCXX_SIMD_INTRINSIC constexpr _Smart_reference operator=(_Tp &&__x) &&
{
__write(std::forward<_Tp>(__x));
return {obj, index};
}
#define _GLIBCXX_SIMD_OP_(op_) \
template <class _Tp, \
class _TT = \
decltype(std::declval<value_type>() op_ std::declval<_Tp>()), \
class = _ValuePreservingOrInt<__remove_cvref_t<_Tp>, _TT>, \
class = _ValuePreservingOrInt<_TT, value_type>> \
_GLIBCXX_SIMD_INTRINSIC constexpr _Smart_reference operator op_##=( \
_Tp&& __x)&& \
{ \
const value_type& __lhs = __read(); \
__write(__lhs op_ __x); \
return {obj, index}; \
}
_GLIBCXX_SIMD_ALL_ARITHMETICS(_GLIBCXX_SIMD_OP_);
_GLIBCXX_SIMD_ALL_SHIFTS(_GLIBCXX_SIMD_OP_);
_GLIBCXX_SIMD_ALL_BINARY(_GLIBCXX_SIMD_OP_);
#undef _GLIBCXX_SIMD_OP_
template <class _Tp = void,
class = decltype(
++std::declval<std::conditional_t<true, value_type, _Tp> &>())>
_GLIBCXX_SIMD_INTRINSIC constexpr _Smart_reference operator++() &&
{
value_type __x = __read();
__write(++__x);
return {obj, index};
}
template <class _Tp = void,
class = decltype(
std::declval<std::conditional_t<true, value_type, _Tp> &>()++)>
_GLIBCXX_SIMD_INTRINSIC constexpr value_type operator++(int) &&
{
const value_type __r = __read();
value_type __x = __r;
__write(++__x);
return __r;
}
template <class _Tp = void,
class = decltype(
--std::declval<std::conditional_t<true, value_type, _Tp> &>())>
_GLIBCXX_SIMD_INTRINSIC constexpr _Smart_reference operator--() &&
{
value_type __x = __read();
__write(--__x);
return {obj, index};
}
template <class _Tp = void,
class = decltype(
std::declval<std::conditional_t<true, value_type, _Tp> &>()--)>
_GLIBCXX_SIMD_INTRINSIC constexpr value_type operator--(int) &&
{
const value_type __r = __read();
value_type __x = __r;
__write(--__x);
return __r;
}
_GLIBCXX_SIMD_INTRINSIC friend void swap(_Smart_reference &&__a, _Smart_reference &&__b) noexcept(
conjunction<std::is_nothrow_constructible<value_type, _Smart_reference &&>,
std::is_nothrow_assignable<_Smart_reference &&, value_type &&>>::value)
{
value_type __tmp = static_cast<_Smart_reference &&>(__a);
static_cast<_Smart_reference &&>(__a) = static_cast<value_type>(__b);
static_cast<_Smart_reference &&>(__b) = std::move(__tmp);
}
_GLIBCXX_SIMD_INTRINSIC friend void swap(value_type &__a, _Smart_reference &&__b) noexcept(
conjunction<std::is_nothrow_constructible<value_type, value_type &&>,
std::is_nothrow_assignable<value_type &, value_type &&>,
std::is_nothrow_assignable<_Smart_reference &&, value_type &&>>::value)
{
value_type __tmp(std::move(__a));
__a = static_cast<value_type>(__b);
static_cast<_Smart_reference &&>(__b) = std::move(__tmp);
}
_GLIBCXX_SIMD_INTRINSIC friend void swap(_Smart_reference &&__a, value_type &__b) noexcept(
conjunction<std::is_nothrow_constructible<value_type, _Smart_reference &&>,
std::is_nothrow_assignable<value_type &, value_type &&>,
std::is_nothrow_assignable<_Smart_reference &&, value_type &&>>::value)
{
value_type __tmp(__a);
static_cast<_Smart_reference &&>(__a) = std::move(__b);
__b = std::move(__tmp);
}
};
template <int _Bytes> struct _SimdImplNeon;
template <int _Bytes> struct _MaskImplNeon;
struct _MaskImplSse;
struct _SimdImplSse;
struct _MaskImplAvx;
struct _SimdImplAvx;
struct _MaskImplAvx512;
struct _SimdImplAvx512;
struct _SimdImplScalar;
struct _MaskImplScalar;
template <int _N> struct _SimdImplFixedSize;
template <int _N> struct _MaskImplFixedSize;
template <int _N, class _Abi> struct _SimdImplCombine;
template <int _N, class _Abi> struct _MaskImplCombine;
template <class _Tp, class _MT, class _Abi, size_t _N> struct _GnuTraits {
using _IsValid = true_type;
using _SimdImpl = typename _Abi::_SimdImpl;
using _MaskImpl = typename _Abi::_MaskImpl;
using _SimdMember = _SimdWrapper<_Tp, _N>;
using _MaskMember = _SimdWrapper<_MT, _N>;
static constexpr size_t _S_simd_align = alignof(_SimdMember);
static constexpr size_t _S_mask_align = alignof(_MaskMember);
struct _SimdBase2 {
explicit operator __intrinsic_type_t<_Tp, _N>() const
{
return static_cast<const simd<_Tp, _Abi> *>(this)->_M_data.__v();
}
explicit operator __vector_type_t<_Tp, _N>() const
{
return static_cast<const simd<_Tp, _Abi> *>(this)->_M_data.__builtin();
}
};
struct _SimdBase1 {
explicit operator __intrinsic_type_t<_Tp, _N>() const
{
return __data(*static_cast<const simd<_Tp, _Abi> *>(this));
}
};
using _SimdBase = std::conditional_t<
std::is_same<__intrinsic_type_t<_Tp, _N>, __vector_type_t<_Tp, _N>>::value,
_SimdBase1, _SimdBase2>;
struct _MaskBase2 {
explicit operator __intrinsic_type_t<_Tp, _N>() const
{
return static_cast<const simd_mask<_Tp, _Abi> *>(this)->_M_data.__intrin();
}
explicit operator __vector_type_t<_Tp, _N>() const
{
return static_cast<const simd_mask<_Tp, _Abi> *>(this)->_M_data._M_data;
}
};
struct _MaskBase1 {
explicit operator __intrinsic_type_t<_Tp, _N>() const
{
return __data(*static_cast<const simd_mask<_Tp, _Abi> *>(this));
}
};
using _MaskBase = std::conditional_t<
std::is_same<__intrinsic_type_t<_Tp, _N>, __vector_type_t<_Tp, _N>>::value,
_MaskBase1, _MaskBase2>;
class _MaskCastType
{
using _U = __intrinsic_type_t<_Tp, _N>;
_U _M_data;
public:
_MaskCastType(_U __x) : _M_data(__x) {}
operator _MaskMember() const { return _M_data; }
};
class _SimdCastType1
{
using _A = __intrinsic_type_t<_Tp, _N>;
_SimdMember _M_data;
public:
_SimdCastType1(_A __a) : _M_data(__vector_bitcast<_Tp>(__a)) {}
operator _SimdMember() const { return _M_data; }
};
class _SimdCastType2
{
using _A = __intrinsic_type_t<_Tp, _N>;
using _B = __vector_type_t<_Tp, _N>;
_SimdMember _M_data;
public:
_SimdCastType2(_A __a) : _M_data(__vector_bitcast<_Tp>(__a)) {}
_SimdCastType2(_B __b) : _M_data(__b) {}
operator _SimdMember() const { return _M_data; }
};
using _SimdCastType = std::conditional_t<
std::is_same<__intrinsic_type_t<_Tp, _N>, __vector_type_t<_Tp, _N>>::value,
_SimdCastType1, _SimdCastType2>;
};
#if _GLIBCXX_SIMD_HAVE_NEON_ABI
template <class _Tp> struct __neon_is_vectorizable : __is_vectorizable<_Tp> {};
template <> struct __neon_is_vectorizable<long double> : false_type {};
#if !_GLIBCXX_SIMD_HAVE_FULL_NEON_ABI
template <> struct __neon_is_vectorizable<double> : false_type {};
#endif
#else
template <class _Tp> struct __neon_is_vectorizable : false_type {};
#endif
#if _GLIBCXX_SIMD_HAVE_FULL_SSE_ABI
template <class _Tp> struct __sse_is_vectorizable : __is_vectorizable<_Tp> {};
template <> struct __sse_is_vectorizable<long double> : false_type {};
#elif _GLIBCXX_SIMD_HAVE_SSE_ABI
template <class _Tp> struct __sse_is_vectorizable : is_same<_Tp, float> {};
#else
template <class _Tp> struct __sse_is_vectorizable : false_type {};
#endif
#if _GLIBCXX_SIMD_HAVE_FULL_AVX_ABI
template <class _Tp> struct __avx_is_vectorizable : __is_vectorizable<_Tp> {};
#elif _GLIBCXX_SIMD_HAVE_AVX_ABI
template <class _Tp> struct __avx_is_vectorizable : std::is_floating_point<_Tp> {};
#else
template <class _Tp> struct __avx_is_vectorizable : false_type {};
#endif
template <> struct __avx_is_vectorizable<long double> : false_type {};
#if _GLIBCXX_SIMD_HAVE_AVX512_ABI
template <class _Tp> struct __avx512_is_vectorizable : __is_vectorizable<_Tp> {};
template <> struct __avx512_is_vectorizable<long double> : false_type {};
#if !_GLIBCXX_SIMD_HAVE_FULL_AVX512_ABI
template <> struct __avx512_is_vectorizable< char> : false_type {};
template <> struct __avx512_is_vectorizable< _UChar> : false_type {};
template <> struct __avx512_is_vectorizable< _SChar> : false_type {};
template <> struct __avx512_is_vectorizable< short> : false_type {};
template <> struct __avx512_is_vectorizable<_UShort> : false_type {};
template <> struct __avx512_is_vectorizable<char16_t> : false_type {};
template <> struct __avx512_is_vectorizable<wchar_t> : __bool_constant<sizeof(wchar_t) >= 4> {};
#endif
#else
template <class _Tp> struct __avx512_is_vectorizable : false_type {};
#endif
template <int _Bytes, class _Abi> struct _MixinImplicitMasking {
template <class _Tp>
using _ImplicitMask =
__vector_type_t<__int_for_sizeof_t<_Tp>, simd_size_v<_Tp, _Abi>>;
template <class _Tp>
static constexpr auto _S_implicit_mask =
reinterpret_cast<__vector_type_t<_Tp, simd_size_v<_Tp, _Abi>>>(
_Abi::_S_is_partial ? __generate_vector<_ImplicitMask<_Tp>>([](auto __i) constexpr {
return __i < _Bytes / sizeof(_Tp) ? -1 : 0;
})
: ~_ImplicitMask<_Tp>());
template <class _Tp, class _TVT = _VectorTraits<_Tp>>
static constexpr auto __masked(_Tp __x)
{
using _U = typename _TVT::value_type;
if constexpr (_Abi::_S_is_partial) {
return __and(__x , _S_implicit_mask<_U>);
} else {
return __x;
}
}
};
namespace simd_abi
{
template <int _N, class _Abi> struct _CombineAbi {
template <class _Tp> static constexpr size_t size = _N *_Abi::template size<_Tp>;
template <class _Tp> static constexpr size_t _S_full_size = size<_Tp>;
static constexpr int _S_factor = _N;
using _MemberAbi = _Abi;
struct _IsValidAbiTag
: __bool_constant<(_N > 1 && _N <= 4) && _Abi::_IsValidAbiTag> {
};
template <class _Tp> struct _IsValidSizeFor : _Abi::template _IsValidSizeFor<_Tp> {
};
template <class _Tp>
struct _IsValid : conjunction<_IsValidAbiTag, typename _Abi::template _IsValid<_Tp>> {
};
template <class _Tp> static constexpr bool __is_valid_v = _IsValid<_Tp>::value;
using _SimdImpl = _SimdImplCombine<_N, _Abi>;
using _MaskImpl = _MaskImplCombine<_N, _Abi>;
template <class _Tp, bool = __is_valid_v<_Tp>> struct __traits : _InvalidTraits {
};
template <class _Tp> struct __traits<_Tp, true> {
using _IsValid = true_type;
using _SimdImpl = _SimdImplCombine<_N, _Abi>;
using _MaskImpl = _MaskImplCombine<_N, _Abi>;
using _SimdMember =
std::array<typename _Abi::template __traits<_Tp>::_SimdMember, _N>;
using _MaskMember =
std::array<typename _Abi::template __traits<_Tp>::_MaskMember, _N>;
static constexpr size_t _S_simd_align =
_Abi::template __traits<_Tp>::_S_simd_align;
static constexpr size_t _S_mask_align =
_Abi::template __traits<_Tp>::_S_mask_align;
struct _SimdBase {
explicit operator const _SimdMember &() const
{
return static_cast<const simd<_Tp, _CombineAbi> *>(this)->_M_data;
}
};
struct _MaskBase {
explicit operator const _MaskMember &() const
{
return static_cast<const simd_mask<_Tp, _CombineAbi> *>(this)->_M_data;
}
};
struct _SimdCastType {
_SimdCastType(const _SimdMember &dd) : _M_data(dd) {}
explicit operator const _SimdMember &() const { return _M_data; }
private:
const _SimdMember &_M_data;
};
struct _MaskCastType {
_MaskCastType(const _MaskMember &dd) : _M_data(dd) {}
explicit operator const _MaskMember &() const { return _M_data; }
private:
const _MaskMember &_M_data;
};
};
};
template <int _Bytes>
struct _NeonAbi : _MixinImplicitMasking<_Bytes, _NeonAbi<_Bytes>> {
template <class _Tp> static constexpr size_t size = _Bytes / sizeof(_Tp);
template <class _Tp>
static constexpr size_t _S_full_size = (_Bytes > 8 ? 16 : 8) / sizeof(_Tp);
static constexpr bool _S_is_partial =
_Bytes < 8 || (_Bytes > 8 && _Bytes < 16);
struct _IsValidAbiTag : __bool_constant<(_Bytes == 8 || _Bytes == 16)>
{
};
template <class _Tp>
struct _IsValidSizeFor
: __bool_constant<(_Bytes / sizeof(_Tp) > 1 && _Bytes % sizeof(_Tp) == 0)> {
};
template <class _Tp>
struct _IsValid : conjunction<_IsValidAbiTag, __neon_is_vectorizable<_Tp>,
_IsValidSizeFor<_Tp>> {
};
template <class _Tp> static constexpr bool __is_valid_v = _IsValid<_Tp>::value;
using _SimdImpl = _SimdImplNeon<_Bytes>;
using _MaskImpl = _MaskImplNeon<_Bytes>;
template <class _Tp>
using __traits = std::conditional_t<__is_valid_v<_Tp>,
_GnuTraits<_Tp, _Tp, _NeonAbi, _S_full_size<_Tp>>,
_InvalidTraits>;
};
template <int _Bytes>
struct _SseAbi : _MixinImplicitMasking<_Bytes, _SseAbi<_Bytes>> {
template <class _Tp> static constexpr size_t size = _Bytes / sizeof(_Tp);
template <class _Tp> static constexpr size_t _S_full_size = 16 / sizeof(_Tp);
static constexpr bool _S_is_partial = _Bytes < 16;
struct _IsValidAbiTag : __bool_constant<_Bytes == 16> {};
template <class _Tp>
struct _IsValidSizeFor
: __bool_constant<(_Bytes / sizeof(_Tp) > 1 && _Bytes % sizeof(_Tp) == 0)> {
};
template <class _Tp>
struct _IsValid
: conjunction<_IsValidAbiTag, __sse_is_vectorizable<_Tp>, _IsValidSizeFor<_Tp>> {
};
template <class _Tp> static constexpr bool __is_valid_v = _IsValid<_Tp>::value;
using _SimdImpl = _SimdImplSse;
using _MaskImpl = _MaskImplSse;
template <class _Tp>
using __traits = std::conditional_t<__is_valid_v<_Tp>,
_GnuTraits<_Tp, _Tp, _SseAbi, _S_full_size<_Tp>>,
_InvalidTraits>;
};
template <int _Bytes>
struct _AvxAbi : _MixinImplicitMasking<_Bytes, _AvxAbi<_Bytes>> {
template <class _Tp> static constexpr size_t size = _Bytes / sizeof(_Tp);
template <class _Tp> static constexpr size_t _S_full_size = 32 / sizeof(_Tp);
static constexpr bool _S_is_partial = _Bytes < 32;
struct _IsValidAbiTag : __bool_constant<_Bytes == 32> {};
template <class _Tp>
struct _IsValidSizeFor : __bool_constant<(_Bytes % sizeof(_Tp) == 0)> {
};
template <class _Tp>
struct _IsValid
: conjunction<_IsValidAbiTag, __avx_is_vectorizable<_Tp>, _IsValidSizeFor<_Tp>> {
};
template <class _Tp> static constexpr bool __is_valid_v = _IsValid<_Tp>::value;
using _SimdImpl = _SimdImplAvx;
using _MaskImpl = _MaskImplAvx;
template <class _Tp>
using __traits = std::conditional_t<__is_valid_v<_Tp>,
_GnuTraits<_Tp, _Tp, _AvxAbi, _S_full_size<_Tp>>,
_InvalidTraits>;
};
template <int _Bytes> struct _Avx512Abi {
template <class _Tp> static constexpr size_t size = _Bytes / sizeof(_Tp);
template <class _Tp> static constexpr size_t _S_full_size = 64 / sizeof(_Tp);
static constexpr bool _S_is_partial = _Bytes < 64;
struct _IsValidAbiTag : __bool_constant<_Bytes == 64> {};
template <class _Tp>
struct _IsValidSizeFor : __bool_constant<(_Bytes % sizeof(_Tp) == 0)> {
};
template <class _Tp>
struct _IsValid
: conjunction<_IsValidAbiTag, __avx512_is_vectorizable<_Tp>, _IsValidSizeFor<_Tp>> {
};
template <class _Tp> static constexpr bool __is_valid_v = _IsValid<_Tp>::value;
template <class _Tp>
using _ImplicitMask = __bool_storage_member_type_t<64 / sizeof(_Tp)>;
template <class _Tp>
static constexpr _ImplicitMask<_Tp> _S_implicit_mask =
_Bytes == 64 ? ~_ImplicitMask<_Tp>()
: (_ImplicitMask<_Tp>(1) << (_Bytes / sizeof(_Tp))) - 1;
template <class _Tp, class = enable_if_t<__is_bitmask_v<_Tp>>>
static constexpr _Tp __masked(_Tp __x)
{
if constexpr (_S_is_partial) {
constexpr size_t _N = sizeof(_Tp) * 8;
return __x &
((__bool_storage_member_type_t<_N>(1) << (_Bytes * _N / 64)) - 1);
} else {
return __x;
}
}
using _SimdImpl = _SimdImplAvx512;
using _MaskImpl = _MaskImplAvx512;
template <class _Tp>
using __traits =
std::conditional_t<__is_valid_v<_Tp>,
_GnuTraits<_Tp, bool, _Avx512Abi, _S_full_size<_Tp>>,
_InvalidTraits>;
};
struct _ScalarAbi {
template <class _Tp> static constexpr size_t size = 1;
template <class _Tp> static constexpr size_t _S_full_size = 1;
struct _IsValidAbiTag : true_type {};
template <class _Tp> struct _IsValidSizeFor : true_type {};
template <class _Tp> struct _IsValid : __is_vectorizable<_Tp> {};
template <class _Tp> static constexpr bool __is_valid_v = _IsValid<_Tp>::value;
using _SimdImpl = _SimdImplScalar;
using _MaskImpl = _MaskImplScalar;
template <class _Tp, bool = __is_valid_v<_Tp>> struct __traits : _InvalidTraits {
};
template <class _Tp> struct __traits<_Tp, true> {
using _IsValid = true_type;
using _SimdImpl = _SimdImplScalar;
using _MaskImpl = _MaskImplScalar;
using _SimdMember = _Tp;
using _MaskMember = bool;
static constexpr size_t _S_simd_align = alignof(_SimdMember);
static constexpr size_t _S_mask_align = alignof(_MaskMember);
struct _SimdCastType {
_SimdCastType() = delete;
};
struct _MaskCastType {
_MaskCastType() = delete;
};
struct _SimdBase {};
struct _MaskBase {};
};
};
template <int _N> struct _FixedAbi {
template <class _Tp> static constexpr size_t size = _N;
template <class _Tp> static constexpr size_t _S_full_size = _N;
struct _IsValidAbiTag
: public __bool_constant<(_N > 0)> {
};
template <class _Tp>
struct _IsValidSizeFor
: __bool_constant<((_N <= simd_abi::max_fixed_size<_Tp>) ||
(simd_abi::__neon::__is_valid_v<char> &&
_N == simd_size_v<char, simd_abi::__neon>) ||
(simd_abi::__sse::__is_valid_v<char> &&
_N == simd_size_v<char, simd_abi::__sse>) ||
(simd_abi::__avx::__is_valid_v<char> &&
_N == simd_size_v<char, simd_abi::__avx>) ||
(simd_abi::__avx512::__is_valid_v<char> &&
_N == simd_size_v<char, simd_abi::__avx512>))> {
};
template <class _Tp>
struct _IsValid
: conjunction<_IsValidAbiTag, __is_vectorizable<_Tp>, _IsValidSizeFor<_Tp>> {
};
template <class _Tp> static constexpr bool __is_valid_v = _IsValid<_Tp>::value;
using _SimdImpl = _SimdImplFixedSize<_N>;
using _MaskImpl = _MaskImplFixedSize<_N>;
template <class _Tp, bool = __is_valid_v<_Tp>> struct __traits : _InvalidTraits {
};
template <class _Tp> struct __traits<_Tp, true> {
using _IsValid = true_type;
using _SimdImpl = _SimdImplFixedSize<_N>;
using _MaskImpl = _MaskImplFixedSize<_N>;
using _SimdMember = __fixed_size_storage_t<_Tp, _N>;
using _MaskMember = std::bitset<_N>;
static constexpr size_t _S_simd_align =
__next_power_of_2(_N * sizeof(_Tp));
static constexpr size_t _S_mask_align = alignof(_MaskMember);
struct _SimdBase {
_SimdBase(const _SimdBase &) {}
_SimdBase() = default;
explicit operator const _SimdMember &() const
{
return static_cast<const simd<_Tp, _FixedAbi> *>(this)->_M_data;
}
explicit operator std::array<_Tp, _N>() const
{
std::array<_Tp, _N> __r;
static_assert(sizeof(__r) <= sizeof(_SimdMember), "");
std::memcpy(__r.data(), &static_cast<const _SimdMember &>(*this),
sizeof(__r));
return __r;
}
};
struct _MaskBase {};
struct _SimdCastType {
_SimdCastType(const std::array<_Tp, _N> &);
_SimdCastType(const _SimdMember &dd) : _M_data(dd) {}
explicit operator const _SimdMember &() const { return _M_data; }
private:
const _SimdMember &_M_data;
};
class _MaskCastType
{
_MaskCastType() = delete;
};
};
};
}
template <int _Bytes> struct __scalar_abi_wrapper : simd_abi::_ScalarAbi {
template <class _Tp>
static constexpr bool __is_valid_v = simd_abi::_ScalarAbi::_IsValid<_Tp>::value &&
sizeof(_Tp) == _Bytes;
};
template <class _Tp> struct __decay_abi {
using type = _Tp;
};
template <int _Bytes> struct __decay_abi<__scalar_abi_wrapper<_Bytes>> {
using type = simd_abi::scalar;
};
template <template <int> class, int _Bytes>
struct __full_abi;
template <int _Bytes>
struct __full_abi<simd_abi::_NeonAbi, _Bytes>
{
using type = simd_abi::_NeonAbi<(_Bytes >= 16 ? 16 : 8)>;
};
template <int _Bytes>
struct __full_abi<simd_abi::_SseAbi, _Bytes>
{
using type = simd_abi::__sse;
};
template <int _Bytes>
struct __full_abi<simd_abi::_AvxAbi, _Bytes>
{
using type = simd_abi::__avx;
};
template <int _Bytes>
struct __full_abi<simd_abi::_Avx512Abi, _Bytes>
{
using type = simd_abi::__avx512;
};
template <int _Bytes>
struct __full_abi<__scalar_abi_wrapper, _Bytes>
{
using type = simd_abi::scalar;
};
template <template <int> class...> struct _AbiList {
template <class, int> static constexpr bool _S_has_valid_abi = false;
template <class, int> using _FirstValidAbi = void;
template <class, int> using _BestAbi = void;
};
template <template <int> class _A0, template <int> class... _Rest>
struct _AbiList<_A0, _Rest...> {
template <class _Tp, int _N>
static constexpr bool _S_has_valid_abi = _A0<sizeof(_Tp) * _N>::template __is_valid_v<_Tp> ||
_AbiList<_Rest...>::template _S_has_valid_abi<_Tp, _N>;
template <class _Tp, int _N>
using _FirstValidAbi =
std::conditional_t<_A0<sizeof(_Tp) * _N>::template __is_valid_v<_Tp>,
typename __decay_abi<_A0<sizeof(_Tp) * _N>>::type,
typename _AbiList<_Rest...>::template _FirstValidAbi<_Tp, _N>>;
template <class _Tp,
int _N,
int _Bytes = sizeof(_Tp) * _N,
typename _B = typename __full_abi<_A0, _Bytes>::type>
using _BestAbi = std::conditional_t<
_A0<_Bytes>::template __is_valid_v<_Tp>,
typename __decay_abi<_A0<_Bytes>>::type,
std::conditional_t<
(_B::template __is_valid_v<_Tp> && _B::template size<_Tp> <= _N),
_B,
typename _AbiList<_Rest...>::template _BestAbi<_Tp, _N>>>;
};
using _AllNativeAbis =
_AbiList<simd_abi::_Avx512Abi, simd_abi::_AvxAbi, simd_abi::_SseAbi,
simd_abi::_NeonAbi, __scalar_abi_wrapper>;
template <class _Tp, class _Abi>
struct _SimdTraits<_Tp, _Abi, std::void_t<typename _Abi::template _IsValid<_Tp>>>
: _Abi::template __traits<_Tp> {
};
template <class _Tp, std::size_t _N>
struct __deduce_impl<_Tp, _N,
enable_if_t<_AllNativeAbis::template _S_has_valid_abi<_Tp, _N>>> {
using type = _AllNativeAbis::_FirstValidAbi<_Tp, _N>;
};
template <class _Tp, std::size_t _N, class = void> struct __deduce_fixed_size_fallback {};
template <class _Tp, std::size_t _N>
struct __deduce_fixed_size_fallback<
_Tp, _N, enable_if_t<simd_abi::fixed_size<_N>::template __is_valid_v<_Tp>>> {
using type = simd_abi::fixed_size<_N>;
};
template <class _Tp, std::size_t _N, class>
struct __deduce_impl : public __deduce_fixed_size_fallback<_Tp, _N> {
};
template <class _Tp, class _Abi> class simd_mask : public _SimdTraits<_Tp, _Abi>::_MaskBase
{
using __traits = _SimdTraits<_Tp, _Abi>;
using __impl = typename __traits::_MaskImpl;
using __member_type = typename __traits::_MaskMember;
static constexpr _Tp *_S_type_tag = nullptr;
friend typename __traits::_MaskBase;
friend class simd<_Tp, _Abi>;
friend __impl;
friend typename __traits::_SimdImpl;
static constexpr bool __is_scalar() { return __is_abi<_Abi, simd_abi::scalar>(); }
static constexpr bool __is_sse() { return __is_abi<_Abi, simd_abi::_SseAbi>(); }
static constexpr bool __is_avx() { return __is_abi<_Abi, simd_abi::_AvxAbi>(); }
static constexpr bool __is_avx512()
{
return __is_abi<_Abi, simd_abi::_Avx512Abi>();
}
static constexpr bool __is_neon()
{
return __is_abi<_Abi, simd_abi::_NeonAbi>();
}
static constexpr bool __is_fixed() { return __is_fixed_size_abi_v<_Abi>; }
static constexpr bool __is_combined() { return __is_combined_abi<_Abi>(); }
public:
using value_type = bool;
using reference = _Smart_reference<__member_type, __impl, value_type>;
using simd_type = simd<_Tp, _Abi>;
using abi_type = _Abi;
static constexpr size_t size() { return __size_or_zero_v<_Tp, _Abi>; }
simd_mask() = default;
simd_mask(const simd_mask &) = default;
simd_mask(simd_mask &&) = default;
simd_mask &operator=(const simd_mask &) = default;
simd_mask &operator=(simd_mask &&) = default;
_GLIBCXX_SIMD_ALWAYS_INLINE explicit simd_mask(
typename __traits::_MaskCastType __init)
: _M_data{__init}
{
}
_GLIBCXX_SIMD_ALWAYS_INLINE static simd_mask __from_bitset(std::bitset<size()> bs)
{
return {__bitset_init, bs};
}
_GLIBCXX_SIMD_ALWAYS_INLINE std::bitset<size()> __to_bitset() const {
if constexpr (__is_scalar()) {
return unsigned(_M_data);
} else if constexpr (__is_fixed()) {
return _M_data;
} else {
return __vector_to_bitset(__builtin());
}
}
_GLIBCXX_SIMD_ALWAYS_INLINE explicit constexpr simd_mask(value_type __x) : _M_data(__broadcast(__x)) {}
template <class _U, class = enable_if_t<
conjunction<is_same<abi_type, simd_abi::fixed_size<size()>>,
is_same<_U, _U>>::value>>
_GLIBCXX_SIMD_ALWAYS_INLINE simd_mask(
const simd_mask<_U, simd_abi::fixed_size<size()>> &__x)
: simd_mask{__bitset_init, __data(__x)}
{
}
private:
template <class _F>
_GLIBCXX_SIMD_INTRINSIC static __member_type __load_wrapper(const value_type* __mem,
[[maybe_unused]] _F __f)
{
if constexpr (__is_scalar())
{
return __mem[0];
}
else if constexpr (__is_fixed())
{
const fixed_size_simd<unsigned char, size()> __bools(
reinterpret_cast<const __may_alias<unsigned char>*>(__mem), __f);
return __data(__bools != 0);
}
#if _GLIBCXX_SIMD_X86INTRIN
else if constexpr (__is_sse())
{
if constexpr (size() == 2 && __have_sse2)
{
return _ToWrapper(_mm_set_epi32(-int(__mem[1]), -int(__mem[1]),
-int(__mem[0]), -int(__mem[0])));
} else if constexpr (size() == 4 && __have_sse2) {
__m128i __k = _mm_cvtsi32_si128(*reinterpret_cast<const int *>(__mem));
__k = _mm_cmpgt_epi16(_mm_unpacklo_epi8(__k, __k), _mm_setzero_si128());
return _ToWrapper(_mm_unpacklo_epi16(__k, __k));
} else if constexpr (size() == 4 && __have_mmx) {
__m128 __k =
_mm_cvtpi8_ps(_mm_cvtsi32_si64(*reinterpret_cast<const int *>(__mem)));
_mm_empty();
return _ToWrapper(_mm_cmpgt_ps(__k, __m128()));
} else if constexpr (size() == 8 && __have_sse2) {
const auto __k = __make_vector<long long>(
*reinterpret_cast<const __may_alias<long long> *>(__mem), 0);
if constexpr (__have_sse2) {
return _ToWrapper(
__vector_bitcast<short>(_mm_unpacklo_epi8(__k, __k)) != 0);
}
} else if constexpr (size() == 16 && __have_sse2) {
return __vector_bitcast<_Tp>(
_mm_cmpgt_epi8(__vector_load<long long, 2>(__mem, __f), __m128i()));
} else {
__assert_unreachable<_F>();
}
}
else if constexpr (__is_avx())
{
if constexpr (size() == 4 && __have_avx)
{
int __bool4;
if constexpr (__is_aligned_v<_F, 4>)
{
__bool4 = *reinterpret_cast<const __may_alias<int>*>(__mem);
} else {
std::memcpy(&__bool4, __mem, 4);
}
const auto __k = __to_intrin(
(__vector_broadcast<4>(__bool4) &
__make_vector<int>(0x1, 0x100, 0x10000, 0x1000000)) != 0);
return _ToWrapper(
__concat(_mm_unpacklo_epi32(__k, __k), _mm_unpackhi_epi32(__k, __k)));
} else if constexpr (size() == 8 && __have_avx) {
auto __k = __vector_load<long long, 2, 8>(__mem, __f);
__k = _mm_cmpgt_epi16(_mm_unpacklo_epi8(__k, __k), __m128i());
return _ToWrapper(
__concat(_mm_unpacklo_epi16(__k, __k), _mm_unpackhi_epi16(__k, __k)));
} else if constexpr (size() == 16 && __have_avx) {
const auto __k =
_mm_cmpgt_epi8(__vector_load<long long, 2>(__mem, __f), __m128i());
return __concat(_mm_unpacklo_epi8(__k, __k), _mm_unpackhi_epi8(__k, __k));
} else if constexpr (size() == 32 && __have_avx2) {
return __vector_bitcast<_Tp>(
_mm256_cmpgt_epi8(__vector_load<long long, 4>(__mem, __f), __m256i()));
} else {
__assert_unreachable<_F>();
}
}
else if constexpr (__is_avx512())
{
if constexpr (size() == 8)
{
const auto __a = __vector_load<long long, 2, 8>(__mem, __f);
if constexpr (__have_avx512bw_vl)
{
return _mm_test_epi8_mask(__a, __a);
} else {
const auto __b = _mm512_cvtepi8_epi64(__a);
return _mm512_test_epi64_mask(__b, __b);
}
} else if constexpr (size() == 16) {
const auto __a = __vector_load<long long, 2>(__mem, __f);
if constexpr (__have_avx512bw_vl) {
return _mm_test_epi8_mask(__a, __a);
} else {
const auto __b = _mm512_cvtepi8_epi32(__a);
return _mm512_test_epi32_mask(__b, __b);
}
} else if constexpr (size() == 32) {
if constexpr (__have_avx512bw_vl) {
const auto __a = __vector_load<long long, 4>(__mem, __f);
return _mm256_test_epi8_mask(__a, __a);
} else {
const auto __a =
_mm512_cvtepi8_epi32(__vector_load<long long, 2>(__mem, __f));
const auto __b =
_mm512_cvtepi8_epi32(__vector_load<long long, 2>(__mem + 16, __f));
return _mm512_test_epi32_mask(__a, __a) |
(_mm512_test_epi32_mask(__b, __b) << 16);
}
} else if constexpr (size() == 64) {
if constexpr (__have_avx512bw) {
const auto __a = __vector_load<long long, 8>(__mem, __f);
return _mm512_test_epi8_mask(__a, __a);
} else {
const auto __a =
_mm512_cvtepi8_epi32(__vector_load<long long, 2>(__mem, __f));
const auto __b = _mm512_cvtepi8_epi32(
__vector_load<long long, 2>(__mem + 16, __f));
const auto __c = _mm512_cvtepi8_epi32(
__vector_load<long long, 2>(__mem + 32, __f));
const auto __d = _mm512_cvtepi8_epi32(
__vector_load<long long, 2>(__mem + 48, __f));
return _mm512_test_epi32_mask(__a, __a) |
(_mm512_test_epi32_mask(__b, __b) << 16) |
(_mm512_test_epi32_mask(__c, __c) << 32) |
(_mm512_test_epi32_mask(__d, __d) << 48);
}
} else {
__assert_unreachable<_F>();
}
}
#endif
else if constexpr (sizeof(_Tp) == sizeof(value_type) &&
is_integral_v<_Tp>)
{
const auto __bools = __vector_load<_Tp, size()>(__mem, __f);
return __vector_bitcast<_Tp>(__bools > 0);
}
else
{
using _I = __int_for_sizeof_t<_Tp>;
return __vector_bitcast<_Tp>(__generate_vector<_I, size()>(
[&](auto __i) constexpr { return __mem[__i] ? ~_I() : _I(); }));
}
}
public :
template <class _Flags>
_GLIBCXX_SIMD_ALWAYS_INLINE simd_mask(const value_type* __mem, _Flags __f)
: _M_data(__load_wrapper(__mem, __f))
{
}
template <class _Flags>
_GLIBCXX_SIMD_ALWAYS_INLINE simd_mask(const value_type *__mem, simd_mask __k, _Flags __f) : _M_data{}
{
_M_data = __impl::__masked_load(_M_data, __k._M_data, __mem, __f);
}
template <class _Flags> _GLIBCXX_SIMD_ALWAYS_INLINE void copy_from(const value_type *__mem, _Flags __f)
{
_M_data = __load_wrapper(__mem, __f);
}
template <class _Flags> _GLIBCXX_SIMD_ALWAYS_INLINE void copy_to(value_type *__mem, _Flags __f) const
{
__impl::__store(_M_data, __mem, __f);
}
_GLIBCXX_SIMD_ALWAYS_INLINE reference operator[](size_t __i) { return {_M_data, int(__i)}; }
_GLIBCXX_SIMD_ALWAYS_INLINE value_type operator[](size_t __i) const {
if constexpr (__is_scalar()) {
_GLIBCXX_DEBUG_ASSERT(__i == 0);
__unused(__i);
return _M_data;
} else {
return _M_data[__i];
}
}
_GLIBCXX_SIMD_ALWAYS_INLINE simd_mask operator!() const
{
if constexpr (__is_scalar()) {
return {__private_init, !_M_data};
} else if constexpr (__is_fixed()) {
return {__private_init, ~__builtin()};
} else if constexpr (__have_avx512dq && __is_avx512() && size() <= 8) {
return {__private_init, _knot_mask8(__builtin())};
} else if constexpr (__is_avx512() && size() <= 16) {
return simd_mask(__private_init, _knot_mask16(__builtin()));
} else if constexpr (__have_avx512bw && __is_avx512() && size() <= 32) {
return {__private_init, _knot_mask32(__builtin())};
} else if constexpr (__have_avx512bw && __is_avx512() && size() <= 64) {
return {__private_init, _knot_mask64(__builtin())};
} else {
return {__private_init,
_ToWrapper(~__vector_bitcast<_UInt>(__builtin()))};
}
}
_GLIBCXX_SIMD_ALWAYS_INLINE friend simd_mask operator&&(const simd_mask &__x, const simd_mask &__y)
{
return {__private_init, __impl::__logical_and(__x._M_data, __y._M_data)};
}
_GLIBCXX_SIMD_ALWAYS_INLINE friend simd_mask operator||(const simd_mask &__x, const simd_mask &__y)
{
return {__private_init, __impl::__logical_or(__x._M_data, __y._M_data)};
}
_GLIBCXX_SIMD_ALWAYS_INLINE friend simd_mask operator&(const simd_mask &__x, const simd_mask &__y)
{
return {__private_init, __impl::__bit_and(__x._M_data, __y._M_data)};
}
_GLIBCXX_SIMD_ALWAYS_INLINE friend simd_mask operator|(const simd_mask &__x, const simd_mask &__y)
{
return {__private_init, __impl::__bit_or(__x._M_data, __y._M_data)};
}
_GLIBCXX_SIMD_ALWAYS_INLINE friend simd_mask operator^(const simd_mask &__x, const simd_mask &__y)
{
return {__private_init, __impl::__bit_xor(__x._M_data, __y._M_data)};
}
_GLIBCXX_SIMD_ALWAYS_INLINE friend simd_mask &operator&=(simd_mask &__x, const simd_mask &__y)
{
__x._M_data = __impl::__bit_and(__x._M_data, __y._M_data);
return __x;
}
_GLIBCXX_SIMD_ALWAYS_INLINE friend simd_mask &operator|=(simd_mask &__x, const simd_mask &__y)
{
__x._M_data = __impl::__bit_or(__x._M_data, __y._M_data);
return __x;
}
_GLIBCXX_SIMD_ALWAYS_INLINE friend simd_mask &operator^=(simd_mask &__x, const simd_mask &__y)
{
__x._M_data = __impl::__bit_xor(__x._M_data, __y._M_data);
return __x;
}
_GLIBCXX_SIMD_ALWAYS_INLINE friend simd_mask operator==(const simd_mask &__x, const simd_mask &__y)
{
return !operator!=(__x, __y);
}
_GLIBCXX_SIMD_ALWAYS_INLINE friend simd_mask operator!=(const simd_mask &__x, const simd_mask &__y)
{
return {__private_init, __impl::__bit_xor(__x._M_data, __y._M_data)};
}
_GLIBCXX_SIMD_INTRINSIC simd_mask(_PrivateInit, typename __traits::_MaskMember __init)
: _M_data(__init)
{
}
template <class _F, class = decltype(bool(std::declval<_F>()(size_t())))>
_GLIBCXX_SIMD_INTRINSIC simd_mask(_PrivateInit, _F &&__gen)
{
for (size_t __i = 0; __i < size(); ++__i) {
__impl::__set(_M_data, __i, __gen(__i));
}
}
_GLIBCXX_SIMD_INTRINSIC simd_mask(_BitsetInit, std::bitset<size()> __init)
: _M_data(__impl::__from_bitset(__init, _S_type_tag))
{
}
struct _CvtProxy
{
template <
typename _U,
typename _A2,
typename = enable_if_t<simd_size_v<_U, _A2> == simd_size_v<_Tp, _Abi>>>
operator simd_mask<_U, _A2>() &&
{
return static_simd_cast<simd_mask<_U, _A2>>(_M_data);
}
const simd_mask<_Tp, _Abi>& _M_data;
};
_GLIBCXX_SIMD_INTRINSIC _CvtProxy __cvt() const { return {*this}; }
private:
_GLIBCXX_SIMD_INTRINSIC static constexpr __member_type __broadcast(value_type __x)
{
if constexpr (__is_scalar()) {
return __x;
} else if constexpr (__is_fixed()) {
return __x ? ~__member_type() : __member_type();
} else if constexpr (__is_avx512()) {
using mmask_type = typename __bool_storage_member_type<size()>::type;
return __x ? _Abi::__masked(static_cast<mmask_type>(~mmask_type())) : mmask_type();
} else {
using _U = __vector_type_t<__int_for_sizeof_t<_Tp>, size()>;
return _ToWrapper(__x ? _Abi::__masked(~_U()) : _U());
}
}
auto &__builtin() {
if constexpr (__is_scalar() || __is_fixed()) {
return _M_data;
} else {
return _M_data._M_data;
}
}
const auto &__builtin() const
{
if constexpr (__is_scalar() || __is_fixed()) {
return _M_data;
} else {
return _M_data._M_data;
}
}
friend const auto &__data<_Tp, abi_type>(const simd_mask &);
friend auto &__data<_Tp, abi_type>(simd_mask &);
alignas(__traits::_S_mask_align) __member_type _M_data;
};
template <class _Tp, class _A>
_GLIBCXX_SIMD_INTRINSIC constexpr const auto &__data(const simd_mask<_Tp, _A> &__x)
{
return __x._M_data;
}
template <class _Tp, class _A> _GLIBCXX_SIMD_INTRINSIC constexpr auto &__data(simd_mask<_Tp, _A> &__x)
{
return __x._M_data;
}
template <class _Tp, class _Abi, class _Data> _GLIBCXX_SIMD_INTRINSIC bool __all_of(const _Data &__k)
{
if constexpr (__is_abi<_Abi, simd_abi::scalar>())
{
return __k;
}
else if constexpr (__is_abi<_Abi, simd_abi::fixed_size>())
{
return __k.all();
}
else if constexpr (__is_combined_abi<_Abi>())
{
for (int __i = 0; __i < _Abi::_S_factor; ++__i) {
if (!__all_of<_Tp, typename _Abi::_MemberAbi>(__k[__i])) {
return false;
}
}
return true;
}
#if _GLIBCXX_SIMD_X86INTRIN
else if constexpr (__is_abi<_Abi, simd_abi::_SseAbi>() ||
__is_abi<_Abi, simd_abi::_AvxAbi>())
{
constexpr size_t _N = simd_size_v<_Tp, _Abi>;
if constexpr (__have_sse4_1)
{
constexpr auto __b = reinterpret_cast<__intrinsic_type_t<_Tp, _N>>(
_Abi::template _S_implicit_mask<_Tp>);
if constexpr (std::is_same_v<_Tp, float> && _N > 4)
return 0 != _mm256_testc_ps(__to_intrin(__k), __b);
else if constexpr (std::is_same_v<_Tp, float> && __have_avx)
return 0 != _mm_testc_ps(__to_intrin(__k), __b);
else if constexpr (std::is_same_v<_Tp, float>)
return 0 != _mm_testc_si128(_mm_castps_si128(__to_intrin(__k)),
_mm_castps_si128(__b));
else if constexpr (std::is_same_v<_Tp, double> && _N > 2)
return 0 != _mm256_testc_pd(__to_intrin(__k), __b);
else if constexpr (std::is_same_v<_Tp, double> && __have_avx)
return 0 != _mm_testc_pd(__to_intrin(__k), __b);
else if constexpr (std::is_same_v<_Tp, double>)
return 0 != _mm_testc_si128(_mm_castpd_si128(__to_intrin(__k)),
_mm_castpd_si128(__b));
else if constexpr (sizeof(__b) == 32)
return _mm256_testc_si256(__to_intrin(__k), __b);
else
return _mm_testc_si128(__to_intrin(__k), __b);
}
else if constexpr (std::is_same_v<_Tp, float>)
{
return (_mm_movemask_ps(__to_intrin(__k)) & ((1 << _N) - 1)) ==
(1 << _N) - 1;
}
else if constexpr (std::is_same_v<_Tp, double>)
{
return (_mm_movemask_pd(__to_intrin(__k)) & ((1 << _N) - 1)) ==
(1 << _N) - 1;
}
else
{
return (_mm_movemask_epi8(__to_intrin(__k)) &
((1 << (_N * sizeof(_Tp))) - 1)) ==
(1 << (_N * sizeof(_Tp))) - 1;
}
}
else if constexpr (__is_abi<_Abi, simd_abi::_Avx512Abi>())
{
constexpr auto _Mask = _Abi::template _S_implicit_mask<_Tp>;
if constexpr (std::is_same_v<_Data, _SimdWrapper<bool, 8>>)
{
if constexpr (__have_avx512dq)
return _kortestc_mask8_u8(
__k._M_data, _Mask == 0xff ? __k._M_data : __mmask8(~_Mask));
else
return __k._M_data == _Mask;
}
else if constexpr (std::is_same_v<_Data, _SimdWrapper<bool, 16>>)
{
return _kortestc_mask16_u8(
__k._M_data, _Mask == 0xffff ? __k._M_data : __mmask16(~_Mask));
}
else if constexpr (std::is_same_v<_Data, _SimdWrapper<bool, 32>>)
{
if constexpr (__have_avx512bw)
{
#ifdef _GLIBCXX_SIMD_WORKAROUND_PR85538
return __k._M_data == _Mask;
#else
return _kortestc_mask32_u8(__k._M_data, _Mask == 0xffffffffU
? __k._M_data
: __mmask32(~_Mask));
#endif
}
}
else if constexpr (std::is_same_v<_Data, _SimdWrapper<bool, 64>>)
{
if constexpr (__have_avx512bw)
{
#ifdef _GLIBCXX_SIMD_WORKAROUND_PR85538
return __k._M_data == _Mask;
#else
return _kortestc_mask64_u8(__k._M_data,
_Mask == 0xffffffffffffffffULL
? __k._M_data
: __mmask64(~_Mask));
#endif
}
}
}
#endif
#if _GLIBCXX_SIMD_HAVE_NEON
else if constexpr (__is_abi<_Abi, simd_abi::_NeonAbi>())
{
constexpr size_t _N = simd_size_v<_Tp, _Abi>;
const auto __x = __vector_bitcast<long long>(__k);
if constexpr (sizeof(__k) == 16)
return __x[0] + __x[1] == -2;
else if constexpr (sizeof(__k) == 8)
return __x == -1;
else
__assert_unreachable<_Tp>();
}
#endif
else
{
constexpr size_t _N = simd_size_v<_Tp, _Abi>;
return __call_with_subscripts(
__vector_bitcast<__int_for_sizeof_t<_Tp>>(__k),
make_index_sequence<_N>(),
[](const auto... __ent) constexpr { return (... && !(__ent == 0)); });
}
}
template <class _Tp, class _Abi, class _Data> _GLIBCXX_SIMD_INTRINSIC bool __any_of(const _Data &__k)
{
if constexpr (__is_abi<_Abi, simd_abi::scalar>())
{
return __k;
}
else if constexpr (__is_abi<_Abi, simd_abi::fixed_size>())
{
return __k.any();
}
else if constexpr (__is_combined_abi<_Abi>())
{
for (int __i = 0; __i < _Abi::_S_factor; ++__i)
{
if (__any_of<_Tp, typename _Abi::_MemberAbi>(__k[__i]))
{
return true;
}
}
return false;
}
#if _GLIBCXX_SIMD_X86INTRIN
else if constexpr (__is_abi<_Abi, simd_abi::_SseAbi>() ||
__is_abi<_Abi, simd_abi::_AvxAbi>())
{
constexpr size_t _N = simd_size_v<_Tp, _Abi>;
if constexpr (__have_sse4_1)
{
return 0 == __testz(__k._M_data, _Abi::template _S_implicit_mask<_Tp>);
} else if constexpr (std::is_same_v<_Tp, float>) {
return (_mm_movemask_ps(__to_intrin(__k)) & ((1 << _N) - 1)) != 0;
} else if constexpr (std::is_same_v<_Tp, double>) {
return (_mm_movemask_pd(__to_intrin(__k)) & ((1 << _N) - 1)) != 0;
} else {
return (_mm_movemask_epi8(__to_intrin(__k)) & ((1 << (_N * sizeof(_Tp))) - 1)) != 0;
}
}
else if constexpr (__is_abi<_Abi, simd_abi::_Avx512Abi>())
{
return (__k & _Abi::template _S_implicit_mask<_Tp>) != 0;
}
#endif
else
{
constexpr size_t _N = simd_size_v<_Tp, _Abi>;
return __call_with_subscripts(
__vector_bitcast<__int_for_sizeof_t<_Tp>>(__k),
make_index_sequence<_N>(),
[](const auto... __ent) constexpr { return (... || !(__ent == 0)); });
}
}
template <class _Tp, class _Abi, class _Data> _GLIBCXX_SIMD_INTRINSIC bool __none_of(const _Data &__k)
{
if constexpr (__is_abi<_Abi, simd_abi::scalar>())
{
return !__k;
}
else if constexpr (__is_abi<_Abi, simd_abi::fixed_size>())
{
return __k.none();
}
else if constexpr (__is_combined_abi<_Abi>())
{
for (int __i = 0; __i < _Abi::_S_factor; ++__i)
{
if (__any_of<_Tp, typename _Abi::_MemberAbi>(__k[__i]))
{
return false;
}
}
return true;
}
#if _GLIBCXX_SIMD_X86INTRIN
else if constexpr (__is_abi<_Abi, simd_abi::_SseAbi>() ||
__is_abi<_Abi, simd_abi::_AvxAbi>())
{
constexpr size_t _N = simd_size_v<_Tp, _Abi>;
if constexpr (__have_sse4_1)
{
return 0 != __testz(__k._M_data, _Abi::template _S_implicit_mask<_Tp>);
} else if constexpr (std::is_same_v<_Tp, float>) {
return (_mm_movemask_ps(__to_intrin(__k)) & ((1 << _N) - 1)) == 0;
} else if constexpr (std::is_same_v<_Tp, double>) {
return (_mm_movemask_pd(__to_intrin(__k)) & ((1 << _N) - 1)) == 0;
} else {
return (_mm_movemask_epi8(__to_intrin(__k)) & ((1 << (_N * sizeof(_Tp))) - 1)) == 0;
}
}
else if constexpr (__is_abi<_Abi, simd_abi::_Avx512Abi>())
{
return (__k & _Abi::template _S_implicit_mask<_Tp>) == 0;
}
#endif
else
{
constexpr size_t _N = simd_size_v<_Tp, _Abi>;
return __call_with_subscripts(
__vector_bitcast<__int_for_sizeof_t<_Tp>>(__k),
make_index_sequence<_N>(),
[](const auto... __ent) constexpr { return (... && (__ent == 0)); });
}
}
template <class _Tp, class _Abi, class _Data> _GLIBCXX_SIMD_INTRINSIC bool __some_of(const _Data &__k)
{
constexpr size_t _N = simd_size_v<_Tp, _Abi>;
if constexpr (_N == 1)
{
return false;
}
else if constexpr (__is_abi<_Abi, simd_abi::fixed_size>())
{
return __k.any() && !__k.all();
}
else if constexpr (__is_combined_abi<_Abi>())
{
return __any_of<_Tp, _Abi>(__k) && !__all_of<_Tp, _Abi>(__k);
}
#if _GLIBCXX_SIMD_X86INTRIN
else if constexpr (__is_abi<_Abi, simd_abi::_SseAbi>() ||
__is_abi<_Abi, simd_abi::_AvxAbi>())
{
if constexpr (__have_sse4_1)
{
return 0 != __testnzc(__k._M_data, _Abi::template _S_implicit_mask<_Tp>);
}
else if constexpr (std::is_same_v<_Tp, float>)
{
constexpr int __allbits = (1 << _N) - 1;
const auto __tmp = _mm_movemask_ps(__to_intrin(__k)) & __allbits;
return __tmp > 0 && __tmp < __allbits;
}
else if constexpr (std::is_same_v<_Tp, double>)
{
constexpr int __allbits = (1 << _N) - 1;
const auto __tmp = _mm_movemask_pd(__to_intrin(__k)) & __allbits;
return __tmp > 0 && __tmp < __allbits;
}
else
{
constexpr int __allbits = (1 << (_N * sizeof(_Tp))) - 1;
const auto __tmp = _mm_movemask_epi8(__to_intrin(__k)) & __allbits;
return __tmp > 0 && __tmp < __allbits;
}
}
else if constexpr (__is_abi<_Abi, simd_abi::_Avx512Abi>())
{
return __any_of<_Tp, _Abi>(__k) && !__all_of<_Tp, _Abi>(__k);
}
#endif
else
{
int __n_false = __call_with_subscripts(
__vector_bitcast<__int_for_sizeof_t<_Tp>>(__k),
make_index_sequence<_N>(),
[](const auto... __ent) constexpr { return (... + (__ent == 0)); });
return __n_false > 0 && __n_false < _N;
}
}
template <class _Tp, class _Abi, class _Data>
_GLIBCXX_SIMD_INTRINSIC int __popcount(const _Data& __k)
{
if constexpr (__is_abi<_Abi, simd_abi::scalar>())
{
return __k;
}
else if constexpr (__is_abi<_Abi, simd_abi::fixed_size>())
{
return __k.count();
}
else if constexpr (__is_combined_abi<_Abi>())
{
int __count = __popcount<_Tp, typename _Abi::_MemberAbi>(__k[0]);
for (int __i = 1; __i < _Abi::_S_factor; ++__i)
{
__count += __popcount<_Tp, typename _Abi::_MemberAbi>(__k[__i]);
}
return __count;
}
#if _GLIBCXX_SIMD_X86INTRIN
else if constexpr (__is_abi<_Abi, simd_abi::_SseAbi>() ||
__is_abi<_Abi, simd_abi::_AvxAbi>())
{
constexpr size_t _N = simd_size_v<_Tp, _Abi>;
const auto __kk = _Abi::__masked(__k._M_data);
if constexpr (__have_popcnt)
{
int __bits = __movemask(__to_intrin(__vector_bitcast<_Tp>(__kk)));
const int __count = __builtin_popcount(__bits);
return std::is_integral_v<_Tp> ? __count / sizeof(_Tp) : __count;
}
else if constexpr (_N == 2)
{
const int mask = _mm_movemask_pd(__auto_bitcast(__kk));
return mask - (mask >> 1);
}
else if constexpr (_N == 4 && sizeof(__kk) == 16 && __have_sse2)
{
auto __x = __vector_bitcast<_LLong>(__kk);
__x =
_mm_add_epi32(__x, _mm_shuffle_epi32(__x, _MM_SHUFFLE(0, 1, 2, 3)));
__x = _mm_add_epi32(
__x, _mm_shufflelo_epi16(__x, _MM_SHUFFLE(1, 0, 3, 2)));
return -_mm_cvtsi128_si32(__x);
}
else if constexpr (_N == 4 && sizeof(__kk) == 16)
{
return __builtin_popcount(_mm_movemask_ps(__auto_bitcast(__kk)));
}
else if constexpr (_N == 8 && sizeof(__kk) == 16)
{
auto __x = __vector_bitcast<_LLong>(__kk);
__x =
_mm_add_epi16(__x, _mm_shuffle_epi32(__x, _MM_SHUFFLE(0, 1, 2, 3)));
__x = _mm_add_epi16(
__x, _mm_shufflelo_epi16(__x, _MM_SHUFFLE(0, 1, 2, 3)));
__x = _mm_add_epi16(
__x, _mm_shufflelo_epi16(__x, _MM_SHUFFLE(2, 3, 0, 1)));
return -short(_mm_extract_epi16(__x, 0));
}
else if constexpr (_N == 16 && sizeof(__kk) == 16)
{
auto __x = __vector_bitcast<_LLong>(__kk);
__x =
_mm_add_epi8(__x, _mm_shuffle_epi32(__x, _MM_SHUFFLE(0, 1, 2, 3)));
__x = _mm_add_epi8(__x,
_mm_shufflelo_epi16(__x, _MM_SHUFFLE(0, 1, 2, 3)));
__x = _mm_add_epi8(__x,
_mm_shufflelo_epi16(__x, _MM_SHUFFLE(2, 3, 0, 1)));
auto __y = -__vector_bitcast<_UChar>(__x);
if constexpr (__have_sse4_1)
{
return __y[0] + __y[1];
}
else
{
unsigned __z =
_mm_extract_epi16(__vector_bitcast<_LLong>(__y), 0);
return (__z & 0xff) + (__z >> 8);
}
}
else if constexpr (_N == 4 && sizeof(__kk) == 32)
{
auto __x = -(__lo128(__kk) + __hi128(__kk));
return __x[0] + __x[1];
}
else if constexpr (sizeof(__kk) == 32)
{
return __popcount<_Tp, simd_abi::__sse>(
-(__lo128(__kk) + __hi128(__kk)));
}
else
{
__assert_unreachable<_Tp>();
}
}
else if constexpr (__is_abi<_Abi, simd_abi::_Avx512Abi>())
{
constexpr size_t _N = simd_size_v<_Tp, _Abi>;
const auto __kk = _Abi::__masked(__k._M_data);
if constexpr (_N <= 4)
{
return __builtin_popcount(__kk);
}
else if constexpr (_N <= 8)
{
return __builtin_popcount(__kk);
}
else if constexpr (_N <= 16)
{
return __builtin_popcount(__kk);
}
else if constexpr (_N <= 32)
{
return __builtin_popcount(__kk);
}
else if constexpr (_N <= 64)
{
return __builtin_popcountll(__kk);
}
else
{
__assert_unreachable<_Tp>();
}
}
#endif
#if _GLIBCXX_SIMD_HAVE_NEON
else if constexpr (sizeof(_Tp) == 1)
{
const auto __s8 = __vector_bitcast<_SChar>(__k);
int8x8_t __tmp = __lo64(__s8) + __hi64z(__s8);
return -vpadd_s8(vpadd_s8(vpadd_s8(__tmp, int8x8_t()), int8x8_t()),
int8x8_t())[0];
}
else if constexpr (sizeof(_Tp) == 2)
{
const auto __s16 = __vector_bitcast<short>(__k);
int16x4_t __tmp = __lo64(__s16) + __hi64z(__s16);
return -vpadd_s16(vpadd_s16(__tmp, int16x4_t()), int16x4_t())[0];
}
else if constexpr (sizeof(_Tp) == 4)
{
const auto __s32 = __vector_bitcast<int>(__k);
int32x2_t __tmp = __lo64(__s32) + __hi64z(__s32);
return -vpadd_s32(__tmp, int32x2_t())[0];
}
else if constexpr (sizeof(_Tp) == 8)
{
static_assert(sizeof(__k) == 16);
const auto __s64 = __vector_bitcast<long>(__k);
return -(__s64[0] + __s64[1]);
}
#endif
else
{
__assert_unreachable<_Tp>();
}
}
template <class _Tp, class _Abi, class _Data> _GLIBCXX_SIMD_INTRINSIC int __find_first_set(const _Data &__k)
{
if constexpr (__is_abi<_Abi, simd_abi::scalar>())
return 0;
else if constexpr (__is_abi<_Abi, simd_abi::fixed_size>())
return __firstbit(__k.to_ullong());
else if constexpr (__is_combined_abi<_Abi>())
{
using _A2 = typename _Abi::_MemberAbi;
for (int __i = 0; __i < _Abi::_S_factor - 1; ++__i)
{
if (__any_of<_Tp, _A2>(__k[__i]))
{
return __i * simd_size_v<_Tp, _A2> + __find_first_set(__k[__i]);
}
}
return (_Abi::_S_factor - 1) * simd_size_v<_Tp, _A2> +
__find_first_set(__k[_Abi::_S_factor - 1]);
}
#if _GLIBCXX_SIMD_X86INTRIN
else if constexpr (__is_abi<_Abi, simd_abi::_Avx512Abi>())
{
if constexpr (simd_size_v<_Tp, _Abi> <= 32)
return _tzcnt_u32(__k._M_data);
else
return __firstbit(__k._M_data);
}
#endif
else
return __firstbit(__vector_to_bitset(__k._M_data).to_ullong());
}
template <class _Tp, class _Abi, class _Data> _GLIBCXX_SIMD_INTRINSIC int __find_last_set(const _Data &__k)
{
if constexpr (__is_abi<_Abi, simd_abi::scalar>())
return 0;
else if constexpr (__is_abi<_Abi, simd_abi::fixed_size>())
return __lastbit(__k.to_ullong());
else if constexpr (__is_combined_abi<_Abi>())
{
using _A2 = typename _Abi::_MemberAbi;
for (int __i = 0; __i < _Abi::_S_factor - 1; ++__i)
{
if (__any_of<_Tp, _A2>(__k[__i]))
{
return __i * simd_size_v<_Tp, _A2> + __find_last_set(__k[__i]);
}
}
return (_Abi::_S_factor - 1) * simd_size_v<_Tp, _A2> +
__find_last_set(__k[_Abi::_S_factor - 1]);
}
#if _GLIBCXX_SIMD_X86INTRIN
else if constexpr (__is_abi<_Abi, simd_abi::_Avx512Abi>())
{
if constexpr (simd_size_v<_Tp, _Abi> <= 32)
return 31 - _lzcnt_u32(__k._M_data);
else
return __lastbit(__k._M_data);
}
#endif
else
return __lastbit(__vector_to_bitset(__k._M_data).to_ullong());
}
template <class _Tp, class _Abi> _GLIBCXX_SIMD_ALWAYS_INLINE bool all_of(const simd_mask<_Tp, _Abi> &__k)
{
return __all_of<_Tp, _Abi>(__data(__k));
}
template <class _Tp, class _Abi> _GLIBCXX_SIMD_ALWAYS_INLINE bool any_of(const simd_mask<_Tp, _Abi> &__k)
{
return __any_of<_Tp, _Abi>(__data(__k));
}
template <class _Tp, class _Abi> _GLIBCXX_SIMD_ALWAYS_INLINE bool none_of(const simd_mask<_Tp, _Abi> &__k)
{
return __none_of<_Tp, _Abi>(__data(__k));
}
template <class _Tp, class _Abi> _GLIBCXX_SIMD_ALWAYS_INLINE bool some_of(const simd_mask<_Tp, _Abi> &__k)
{
return __some_of<_Tp, _Abi>(__data(__k));
}
template <class _Tp, class _Abi> _GLIBCXX_SIMD_ALWAYS_INLINE int popcount(const simd_mask<_Tp, _Abi> &__k)
{
return __popcount<_Tp, _Abi>(__data(__k));
}
template <class _Tp, class _Abi>
_GLIBCXX_SIMD_ALWAYS_INLINE int find_first_set(const simd_mask<_Tp, _Abi> &__k)
{
return __find_first_set<_Tp, _Abi>(__data(__k));
}
template <class _Tp, class _Abi>
_GLIBCXX_SIMD_ALWAYS_INLINE int find_last_set(const simd_mask<_Tp, _Abi> &__k)
{
return __find_last_set<_Tp, _Abi>(__data(__k));
}
constexpr bool all_of(_ExactBool __x) { return __x; }
constexpr bool any_of(_ExactBool __x) { return __x; }
constexpr bool none_of(_ExactBool __x) { return !__x; }
constexpr bool some_of(_ExactBool) { return false; }
constexpr int popcount(_ExactBool __x) { return __x; }
constexpr int find_first_set(_ExactBool) { return 0; }
constexpr int find_last_set(_ExactBool) { return 0; }
template <class _Abi> struct _SimdImplBuiltin;
template <class _V, bool> class _SimdIntOperators {};
template <class _V> class _SimdIntOperators<_V, true>
{
using _Impl = __get_impl_t<_V>;
_GLIBCXX_SIMD_INTRINSIC const _V &__derived() const { return *static_cast<const _V *>(this); }
template <class _Tp> _GLIBCXX_SIMD_INTRINSIC static _V __make_derived(_Tp &&__d)
{
return {__private_init, std::forward<_Tp>(__d)};
}
public:
constexpr friend _V &operator %=(_V &__lhs, const _V &__x) { return __lhs = __lhs % __x; }
constexpr friend _V &operator &=(_V &__lhs, const _V &__x) { return __lhs = __lhs & __x; }
constexpr friend _V &operator |=(_V &__lhs, const _V &__x) { return __lhs = __lhs | __x; }
constexpr friend _V &operator ^=(_V &__lhs, const _V &__x) { return __lhs = __lhs ^ __x; }
constexpr friend _V &operator<<=(_V &__lhs, const _V &__x) { return __lhs = __lhs << __x; }
constexpr friend _V &operator>>=(_V &__lhs, const _V &__x) { return __lhs = __lhs >> __x; }
constexpr friend _V &operator<<=(_V &__lhs, int __x) { return __lhs = __lhs << __x; }
constexpr friend _V &operator>>=(_V &__lhs, int __x) { return __lhs = __lhs >> __x; }
constexpr friend _V operator% (const _V &__x, const _V &__y) { return _SimdIntOperators::__make_derived(_Impl::__modulus (__data(__x), __data(__y))); }
constexpr friend _V operator& (const _V &__x, const _V &__y) { return _SimdIntOperators::__make_derived(_Impl::__bit_and (__data(__x), __data(__y))); }
constexpr friend _V operator| (const _V &__x, const _V &__y) { return _SimdIntOperators::__make_derived(_Impl::__bit_or (__data(__x), __data(__y))); }
constexpr friend _V operator^ (const _V &__x, const _V &__y) { return _SimdIntOperators::__make_derived(_Impl::__bit_xor (__data(__x), __data(__y))); }
constexpr friend _V operator<<(const _V &__x, const _V &__y) { return _SimdIntOperators::__make_derived(_Impl::__bit_shift_left (__data(__x), __data(__y))); }
constexpr friend _V operator>>(const _V &__x, const _V &__y) { return _SimdIntOperators::__make_derived(_Impl::__bit_shift_right(__data(__x), __data(__y))); }
constexpr friend _V operator<<(const _V &__x, int __y) { return _SimdIntOperators::__make_derived(_Impl::__bit_shift_left (__data(__x), __y)); }
constexpr friend _V operator>>(const _V &__x, int __y) { return _SimdIntOperators::__make_derived(_Impl::__bit_shift_right(__data(__x), __y)); }
constexpr _V operator~() const
{
return {__private_init, _Impl::__complement(__derived()._M_data)};
}
};
template <class _Tp, class _Abi>
class simd
: public _SimdIntOperators<
simd<_Tp, _Abi>, conjunction<std::is_integral<_Tp>,
typename _SimdTraits<_Tp, _Abi>::_IsValid>::value>,
public _SimdTraits<_Tp, _Abi>::_SimdBase
{
using __traits = _SimdTraits<_Tp, _Abi>;
using __impl = typename __traits::_SimdImpl;
using __member_type = typename __traits::_SimdMember;
using __cast_type = typename __traits::_SimdCastType;
static constexpr _Tp *_S_type_tag = nullptr;
friend typename __traits::_SimdBase;
friend __impl;
friend _SimdImplBuiltin<_Abi>;
friend _SimdIntOperators<simd, true>;
public:
using value_type = _Tp;
using reference = _Smart_reference<__member_type, __impl, value_type>;
using mask_type = simd_mask<_Tp, _Abi>;
using abi_type = _Abi;
static constexpr size_t size() { return __size_or_zero_v<_Tp, _Abi>; }
constexpr simd() = default;
constexpr simd(const simd &) = default;
constexpr simd(simd &&) = default;
constexpr simd &operator=(const simd &) = default;
constexpr simd &operator=(simd &&) = default;
template <class _U, class = _ValuePreservingOrInt<_U, value_type>>
_GLIBCXX_SIMD_ALWAYS_INLINE constexpr simd(_U &&__x)
: _M_data(__impl::__broadcast(static_cast<value_type>(std::forward<_U>(__x))))
{
}
template <class _U>
_GLIBCXX_SIMD_ALWAYS_INLINE simd(
const simd<_U, simd_abi::fixed_size<size()>> &__x,
enable_if_t<
conjunction<std::is_same<simd_abi::fixed_size<size()>, abi_type>,
std::negation<__is_narrowing_conversion<_U, value_type>>,
__converts_to_higher_integer_rank<_U, value_type>>::value,
void *> = nullptr)
: simd{static_cast<std::array<_U, size()>>(__x).data(), vector_aligned}
{
}
template <class _F>
_GLIBCXX_SIMD_ALWAYS_INLINE explicit constexpr simd(
_F &&__gen,
_ValuePreservingOrInt<
decltype(std::declval<_F>()(std::declval<_SizeConstant<0> &>())),
value_type> * = nullptr)
: _M_data(__impl::__generator(std::forward<_F>(__gen), _S_type_tag))
{
}
template <class _U, class _Flags>
_GLIBCXX_SIMD_ALWAYS_INLINE simd(const _U *__mem, _Flags __f)
: _M_data(__impl::__load(__mem, __f, _S_type_tag))
{
}
template <class _U, class _Flags>
_GLIBCXX_SIMD_ALWAYS_INLINE void copy_from(const _Vectorizable<_U> *__mem, _Flags __f)
{
_M_data = static_cast<decltype(_M_data)>(__impl::__load(__mem, __f, _S_type_tag));
}
template <class _U, class _Flags>
_GLIBCXX_SIMD_ALWAYS_INLINE void copy_to(_Vectorizable<_U> *__mem, _Flags __f) const
{
__impl::__store(_M_data, __mem, __f, _S_type_tag);
}
_GLIBCXX_SIMD_ALWAYS_INLINE constexpr reference operator[](size_t __i) { return {_M_data, int(__i)}; }
_GLIBCXX_SIMD_ALWAYS_INLINE constexpr value_type operator[](size_t __i) const
{
if constexpr (__is_scalar()) {
_GLIBCXX_DEBUG_ASSERT(__i == 0);
__unused(__i);
return _M_data;
} else {
return _M_data[__i];
}
}
_GLIBCXX_SIMD_ALWAYS_INLINE constexpr simd &operator++() { __impl::__increment(_M_data); return *this; }
_GLIBCXX_SIMD_ALWAYS_INLINE constexpr simd operator++(int) { simd __r = *this; __impl::__increment(_M_data); return __r; }
_GLIBCXX_SIMD_ALWAYS_INLINE constexpr simd &operator--() { __impl::__decrement(_M_data); return *this; }
_GLIBCXX_SIMD_ALWAYS_INLINE constexpr simd operator--(int) { simd __r = *this; __impl::__decrement(_M_data); return __r; }
_GLIBCXX_SIMD_ALWAYS_INLINE constexpr mask_type operator!() const
{
return {__private_init, __impl::__negate(_M_data)};
}
_GLIBCXX_SIMD_ALWAYS_INLINE constexpr simd operator+() const { return *this; }
_GLIBCXX_SIMD_ALWAYS_INLINE constexpr simd operator-() const
{
return {__private_init, __impl::__unary_minus(_M_data)};
}
_GLIBCXX_SIMD_ALWAYS_INLINE explicit simd(__cast_type __init) : _M_data(__init) {}
_GLIBCXX_SIMD_ALWAYS_INLINE constexpr friend simd &operator+=(simd &__lhs, const simd &__x) { return __lhs = __lhs + __x; }
_GLIBCXX_SIMD_ALWAYS_INLINE constexpr friend simd &operator-=(simd &__lhs, const simd &__x) { return __lhs = __lhs - __x; }
_GLIBCXX_SIMD_ALWAYS_INLINE constexpr friend simd &operator*=(simd &__lhs, const simd &__x) { return __lhs = __lhs * __x; }
_GLIBCXX_SIMD_ALWAYS_INLINE constexpr friend simd &operator/=(simd &__lhs, const simd &__x) { return __lhs = __lhs / __x; }
_GLIBCXX_SIMD_ALWAYS_INLINE constexpr friend simd operator+(const simd &__x, const simd &__y)
{
return {__private_init, __impl::__plus(__x._M_data, __y._M_data)};
}
_GLIBCXX_SIMD_ALWAYS_INLINE constexpr friend simd operator-(const simd &__x, const simd &__y)
{
return {__private_init, __impl::__minus(__x._M_data, __y._M_data)};
}
_GLIBCXX_SIMD_ALWAYS_INLINE constexpr friend simd operator*(const simd& __x, const simd& __y)
{
return {__private_init, __impl::__multiplies(__x._M_data, __y._M_data)};
}
_GLIBCXX_SIMD_ALWAYS_INLINE constexpr friend simd operator/(const simd &__x, const simd &__y)
{
return {__private_init, __impl::__divides(__x._M_data, __y._M_data)};
}
_GLIBCXX_SIMD_ALWAYS_INLINE friend mask_type operator==(const simd &__x, const simd &__y)
{
return simd::make_mask(__impl::__equal_to(__x._M_data, __y._M_data));
}
_GLIBCXX_SIMD_ALWAYS_INLINE friend mask_type operator!=(const simd &__x, const simd &__y)
{
return simd::make_mask(__impl::__not_equal_to(__x._M_data, __y._M_data));
}
_GLIBCXX_SIMD_ALWAYS_INLINE friend mask_type operator<(const simd &__x, const simd &__y)
{
return simd::make_mask(__impl::__less(__x._M_data, __y._M_data));
}
_GLIBCXX_SIMD_ALWAYS_INLINE friend mask_type operator<=(const simd &__x, const simd &__y)
{
return simd::make_mask(__impl::__less_equal(__x._M_data, __y._M_data));
}
_GLIBCXX_SIMD_ALWAYS_INLINE friend mask_type operator>(const simd &__x, const simd &__y)
{
return simd::make_mask(__impl::__less(__y._M_data, __x._M_data));
}
_GLIBCXX_SIMD_ALWAYS_INLINE friend mask_type operator>=(const simd &__x, const simd &__y)
{
return simd::make_mask(__impl::__less_equal(__y._M_data, __x._M_data));
}
_GLIBCXX_SIMD_INTRINSIC constexpr simd(_PrivateInit,
const __member_type& __init)
: _M_data(__init)
{
}
_GLIBCXX_SIMD_INTRINSIC simd(_BitsetInit, std::bitset<size()> __init) : _M_data() {
where(mask_type(__bitset_init, __init), *this) = ~*this;
}
private:
static constexpr bool __is_scalar() { return std::is_same_v<abi_type, simd_abi::scalar>; }
static constexpr bool __is_fixed() { return __is_fixed_size_abi_v<abi_type>; }
_GLIBCXX_SIMD_INTRINSIC static mask_type make_mask(typename mask_type::__member_type __k)
{
return {__private_init, __k};
}
friend const auto &__data<value_type, abi_type>(const simd &);
friend auto &__data<value_type, abi_type>(simd &);
alignas(__traits::_S_simd_align) __member_type _M_data;
};
template <class _Tp, class _A> _GLIBCXX_SIMD_INTRINSIC constexpr const auto &__data(const simd<_Tp, _A> &__x)
{
return __x._M_data;
}
template <class _Tp, class _A> _GLIBCXX_SIMD_INTRINSIC constexpr auto &__data(simd<_Tp, _A> &__x)
{
return __x._M_data;
}
namespace __proposed
{
namespace float_bitwise_operators
{
template <class _Tp, class _A>
_GLIBCXX_SIMD_INTRINSIC constexpr simd<_Tp, _A>
operator^(const simd<_Tp, _A>& __a, const simd<_Tp, _A>& __b)
{
return {__private_init,
__get_impl_t<simd<_Tp, _A>>::__bit_xor(__data(__a), __data(__b))};
}
template <class _Tp, class _A>
_GLIBCXX_SIMD_INTRINSIC constexpr simd<_Tp, _A> operator|(const simd<_Tp, _A> &__a, const simd<_Tp, _A> &__b)
{
return {__private_init, __get_impl_t<simd<_Tp, _A>>::__bit_or(__data(__a), __data(__b))};
}
template <class _Tp, class _A>
_GLIBCXX_SIMD_INTRINSIC constexpr simd<_Tp, _A> operator&(const simd<_Tp, _A> &__a, const simd<_Tp, _A> &__b)
{
return {__private_init, __get_impl_t<simd<_Tp, _A>>::__bit_and(__data(__a), __data(__b))};
}
}
}
_GLIBCXX_SIMD_END_NAMESPACE
#endif
#endif
#ifndef _GLIBCXX_EXPERIMENTAL_SIMD_ABIS_H_
#define _GLIBCXX_EXPERIMENTAL_SIMD_ABIS_H_ 
#if __cplusplus >= 201703L
#include <array>
#include <cmath>
#include <cstdlib>
_GLIBCXX_SIMD_BEGIN_NAMESPACE
template <typename _V, typename = _VectorTraits<_V>>
static inline constexpr _V _S_signmask = __xor(_V() + 1, _V() - 1);
template <typename _V, typename = _VectorTraits<_V>>
static inline constexpr _V _S_absmask = __andnot(_S_signmask<_V>, __allbits<_V>);
template <typename _Tp> _Tp __subscript_read(_Vectorizable<_Tp> __x, size_t) noexcept
{
return __x;
}
template <typename _Tp>
void __subscript_write(_Vectorizable<_Tp> &__x, size_t, __id<_Tp> __y) noexcept
{
__x = __y;
}
template <typename _Tp>
typename _Tp::value_type __subscript_read(const _Tp &__x, size_t __i) noexcept
{
return __x[__i];
}
template <typename _Tp>
void __subscript_write(_Tp &__x, size_t __i, typename _Tp::value_type __y) noexcept
{
return __x.__set(__i, __y);
}
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
__simd_tuple_concat(const _Tp& __left,
const _SimdTuple<_Tp, _A10, _A1s...>& __right)
{
return {__left, __right};
}
template <size_t _N, typename _Tp>
_GLIBCXX_SIMD_INTRINSIC constexpr decltype(auto)
__simd_tuple_pop_front(_Tp&& __x)
{
if constexpr (_N == 0)
return std::forward<_Tp>(__x);
else
return __simd_tuple_pop_front<_N - 1>(__x.second);
}
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
template <typename _Tp, typename _Abi, size_t _Offset>
struct __tuple_element_meta : public _Abi::_SimdImpl {
static_assert(is_same_v<typename _Abi::_SimdImpl::abi_type,
_Abi>);
using value_type = _Tp;
using abi_type = _Abi;
using _Traits = _SimdTraits<_Tp, _Abi>;
using _MaskImpl = typename _Traits::_MaskImpl;
using _MaskMember = typename _Traits::_MaskMember;
using simd_type = std::experimental::simd<_Tp, _Abi>;
static constexpr size_t _S_offset = _Offset;
static constexpr size_t size() { return simd_size<_Tp, _Abi>::value; }
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
return __vector_to_bitset(__k).to_ullong() << _Offset;
}
};
template <size_t _Offset, typename _Tp, typename _Abi, typename... _As>
__tuple_element_meta<_Tp, _Abi, _Offset> __make_meta(const _SimdTuple<_Tp, _Abi, _As...> &)
{
return {};
}
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
template <typename _Tp> struct _SimdTuple<_Tp> {
using value_type = _Tp;
static constexpr size_t _S_tuple_size = 0;
static constexpr size_t size() { return 0; }
};
template <typename _FirstType, typename _SecondType>
struct _SimdTupleData
{
_FirstType first;
_SecondType second;
};
template <typename _FirstType, typename _Tp>
struct _SimdTupleData<_FirstType, _SimdTuple<_Tp>>
{
_FirstType first;
static constexpr _SimdTuple<_Tp> second = {};
};
template <class _Tp, class _Abi0, class... _Abis>
struct _SimdTuple<_Tp, _Abi0, _Abis...>
: _SimdTupleData<typename _SimdTraits<_Tp, _Abi0>::_SimdMember,
_SimdTuple<_Tp, _Abis...>>
{
using value_type = _Tp;
using _First_type = typename _SimdTraits<_Tp, _Abi0>::_SimdMember;
using _First_abi = _Abi0;
using _Second_type = _SimdTuple<_Tp, _Abis...>;
static constexpr size_t _S_tuple_size = sizeof...(_Abis) + 1;
static constexpr size_t size()
{
return simd_size_v<_Tp, _Abi0> + _Second_type::size();
}
static constexpr size_t _S_first_size = simd_size_v<_Tp, _Abi0>;
using _Base = _SimdTupleData<typename _SimdTraits<_Tp, _Abi0>::_SimdMember,
_SimdTuple<_Tp, _Abis...>>;
using _Base::first;
using _Base::second;
_SimdTuple() = default;
_GLIBCXX_SIMD_INTRINSIC char* __as_charptr()
{
return reinterpret_cast<char*>(this);
}
_GLIBCXX_SIMD_INTRINSIC const char* __as_charptr() const
{
return reinterpret_cast<const char*>(this);
}
template <size_t _Offset = 0, class _F>
_GLIBCXX_SIMD_INTRINSIC static constexpr _SimdTuple
__generate(_F&& __gen, _SizeConstant<_Offset> = {})
{
auto &&__first = __gen(__tuple_element_meta<_Tp, _Abi0, _Offset>());
if constexpr (_S_tuple_size == 1)
return {__first};
else
return {__first, _Second_type::__generate(
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
typename _R = __fixed_size_storage_t<_Tp, _Size>>
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
return {typename _R::_First_type(
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
using _U = __remove_cvref_t<_Tup>;
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
__assign_front(const _First_type& __x) &
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
template <class _F, class... _More>
_GLIBCXX_SIMD_INTRINSIC constexpr _SimdTuple
__apply_per_chunk(_F&& __fun, _More&&... __more) const
{
static_assert(
(... && ((_S_first_size % __remove_cvref_t<_More>::_S_first_size == 0) ||
(__remove_cvref_t<_More>::_S_first_size % _S_first_size == 0))));
if constexpr ((... || conjunction_v<
is_lvalue_reference<_More>,
negation<is_const<remove_reference_t<_More>>>>))
{
auto&& __first = [&](auto... __args) constexpr {
auto __r =
__fun(__tuple_element_meta<_Tp, _Abi0, 0>(), first, __args...);
[[maybe_unused]] auto&& __unused = {(
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
auto&& __first = __vector_to_bitset(
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
return __subscript_read(first, _I);
else
return second[std::integral_constant<_U,
_I - simd_size_v<_Tp, _Abi0>>()];
}
_Tp operator[](size_t __i) const noexcept
{
if constexpr (_S_tuple_size == 1)
return __subscript_read(first, __i);
else
{
#ifdef _GLIBCXX_SIMD_USE_ALIASING_LOADS
return reinterpret_cast<const __may_alias<_Tp>*>(this)[__i];
#else
if constexpr (__is_abi<_Abi0, simd_abi::scalar>())
{
const _Tp* ptr = &first;
return ptr[__i];
}
else
return __i < simd_size_v<_Tp, _Abi0>
? __subscript_read(first, __i)
: second[__i - simd_size_v<_Tp, _Abi0>];
#endif
}
}
void __set(size_t __i, _Tp __val) noexcept
{
if constexpr (_S_tuple_size == 1)
return __subscript_write(first, __i, __val);
else
{
#ifdef _GLIBCXX_SIMD_USE_ALIASING_LOADS
reinterpret_cast<__may_alias<_Tp>*>(this)[__i] = __val;
#else
if (__i < simd_size_v<_Tp, _Abi0>)
__subscript_write(first, __i, __val);
else
second.__set(__i - simd_size_v<_Tp, _Abi0>, __val);
#endif
}
}
};
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
template <size_t, class _Tp> using __to_tuple_helper = _Tp;
template <class _Tp, class _A0, size_t... _Indexes>
_GLIBCXX_SIMD_INTRINSIC _SimdTuple<_Tp, __to_tuple_helper<_Indexes, _A0>...>
__to_simd_tuple_impl(std::index_sequence<_Indexes...>,
const std::array<__vector_type_t<_Tp, simd_size_v<_Tp, _A0>>,
sizeof...(_Indexes)> &__args)
{
return __make_simd_tuple<_Tp, __to_tuple_helper<_Indexes, _A0>...>(__args[_Indexes]...);
}
template <class _Tp, class _A0, size_t _N>
_GLIBCXX_SIMD_INTRINSIC auto __to_simd_tuple(
const std::array<__vector_type_t<_Tp, simd_size_v<_Tp, _A0>>, _N> &__args)
{
return __to_simd_tuple_impl<_Tp, _A0>(std::make_index_sequence<_N>(), __args);
}
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
{
return __x;
}
else if constexpr (_R::_S_first_size == simd_size_v<_Tp, _A0>)
{
return __simd_tuple_concat(_SimdTuple<_Tp, typename _R::_First_abi>{__x.first},
__optimize_simd_tuple(__x.second));
}
else if constexpr (_R::_S_first_size ==
simd_size_v<_Tp, _A0> + simd_size_v<_Tp, _A1>)
{
return __simd_tuple_concat(_SimdTuple<_Tp, typename _R::_First_abi>{__data(
std::experimental::concat(__get_simd_at<0>(__x), __get_simd_at<1>(__x)))},
__optimize_simd_tuple(__x.second.second));
}
else if constexpr (_R::_S_first_size ==
4 * __simd_tuple_element_t<0, _Tup>::size())
{
return __simd_tuple_concat(
_SimdTuple<_Tp, typename _R::_First_abi>{
__data(concat(__get_simd_at<0>(__x), __get_simd_at<1>(__x),
__get_simd_at<2>(__x), __get_simd_at<3>(__x)))},
__optimize_simd_tuple(__x.second.second.second.second));
}
else if constexpr (_R::_S_first_size ==
8 * __simd_tuple_element_t<0, _Tup>::size())
{
return __simd_tuple_concat(
_SimdTuple<_Tp, typename _R::_First_abi>{__data(concat(
__get_simd_at<0>(__x), __get_simd_at<1>(__x), __get_simd_at<2>(__x),
__get_simd_at<3>(__x), __get_simd_at<4>(__x), __get_simd_at<5>(__x),
__get_simd_at<6>(__x), __get_simd_at<7>(__x)))},
__optimize_simd_tuple(
__x.second.second.second.second.second.second.second.second));
}
else if constexpr (_R::_S_first_size ==
16 * __simd_tuple_element_t<0, _Tup>::size())
{
return __simd_tuple_concat(
_SimdTuple<_Tp, typename _R::_First_abi>{__data(concat(
__get_simd_at<0>(__x), __get_simd_at<1>(__x), __get_simd_at<2>(__x),
__get_simd_at<3>(__x), __get_simd_at<4>(__x), __get_simd_at<5>(__x),
__get_simd_at<6>(__x), __get_simd_at<7>(__x), __get_simd_at<8>(__x),
__get_simd_at<9>(__x), __get_simd_at<10>(__x),
__get_simd_at<11>(__x), __get_simd_at<12>(__x),
__get_simd_at<13>(__x), __get_simd_at<14>(__x),
__get_simd_at<15>(__x)))},
__optimize_simd_tuple(
__x.second.second.second.second.second.second.second.second.second
.second.second.second.second.second.second.second));
}
else
{
return __x;
}
}
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
template <size_t _Offset = 0, class _Tp, class _A0, class _F>
_GLIBCXX_SIMD_INTRINSIC constexpr void
__for_each(_SimdTuple<_Tp, _A0>& __a,
const _SimdTuple<_Tp, _A0>& __b,
_F&& __fun)
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
__for_each(_SimdTuple<_Tp, _A0, _A1, _As...>& __a,
const _SimdTuple<_Tp, _A0, _A1, _As...>& __b,
_F&& __fun)
{
__fun(__make_meta<_Offset>(__a), __a.first, __b.first);
__for_each<_Offset + simd_size<_Tp, _A0>::value>(__a.second, __b.second,
std::forward<_F>(__fun));
}
template <size_t _Offset = 0, class _Tp, class _A0, class _F>
_GLIBCXX_SIMD_INTRINSIC constexpr void
__for_each(const _SimdTuple<_Tp, _A0>& __a,
const _SimdTuple<_Tp, _A0>& __b,
_F&& __fun)
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
_F&& __fun)
{
__fun(__make_meta<_Offset>(__a), __a.first, __b.first);
__for_each<_Offset + simd_size<_Tp, _A0>::value>(__a.second, __b.second,
std::forward<_F>(__fun));
}
template <class _Tp, class _TVT = _VectorTraits<_Tp>>
_GLIBCXX_SIMD_INTRINSIC auto __cmpord(_Tp __x, _Tp __y)
{
static_assert(is_floating_point_v<typename _TVT::value_type>);
#if _GLIBCXX_SIMD_X86INTRIN
if constexpr (__have_sse && _TVT::template __is<float, 4>)
return __intrin_bitcast<_Tp>(_mm_cmpord_ps(__x, __y));
else if constexpr (__have_sse2 && _TVT::template __is<double, 2>)
return __intrin_bitcast<_Tp>(_mm_cmpord_pd(__x, __y));
else if constexpr (__have_avx && _TVT::template __is<float, 8>)
return __intrin_bitcast<_Tp>(_mm256_cmp_ps(__x, __y, _CMP_ORD_Q));
else if constexpr (__have_avx && _TVT::template __is<double, 4>)
return __intrin_bitcast<_Tp>(_mm256_cmp_pd(__x, __y, _CMP_ORD_Q));
else if constexpr (__have_avx512f && _TVT::template __is<float, 16>)
return _mm512_cmp_ps_mask(__x, __y, _CMP_ORD_Q);
else if constexpr (__have_avx512f && _TVT::template __is<double, 8>)
return _mm512_cmp_pd_mask(__x, __y, _CMP_ORD_Q);
else
#endif
{
return reinterpret_cast<_Tp>((__x < __y) != (__x >= __y));
}
}
template <class _Tp, class _TVT = _VectorTraits<_Tp>>
_GLIBCXX_SIMD_INTRINSIC auto __cmpunord(_Tp __x, _Tp __y)
{
static_assert(is_floating_point_v<typename _TVT::value_type>);
#if _GLIBCXX_SIMD_X86INTRIN
if constexpr (__have_sse && _TVT::template __is<float, 4>)
return __intrin_bitcast<_Tp>(_mm_cmpunord_ps(__x, __y));
else if constexpr (__have_sse2 && _TVT::template __is<double, 2>)
return __intrin_bitcast<_Tp>(_mm_cmpunord_pd(__x, __y));
else if constexpr (__have_avx && _TVT::template __is<float, 8>)
return __intrin_bitcast<_Tp>(_mm256_cmp_ps(__x, __y, _CMP_UNORD_Q));
else if constexpr (__have_avx && _TVT::template __is<double, 4>)
return __intrin_bitcast<_Tp>(_mm256_cmp_pd(__x, __y, _CMP_UNORD_Q));
else if constexpr (__have_avx512f && _TVT::template __is<float, 16>)
return _mm512_cmp_ps_mask(__x, __y, _CMP_UNORD_Q);
else if constexpr (__have_avx512f && _TVT::template __is<double, 8>)
return _mm512_cmp_pd_mask(__x, __y, _CMP_UNORD_Q);
else
#endif
{
return reinterpret_cast<_Tp>((__x < __y) == (__x >= __y));
}
}
#if _GLIBCXX_SIMD_X86INTRIN
template <class _Tp, class _F>
_GLIBCXX_SIMD_INTRINSIC void __maskstore(_SimdWrapper64<_Tp> __v, _Tp* __mem, _F,
_SimdWrapper<bool, _SimdWrapper64<_Tp>::_S_width> __k)
{
[[maybe_unused]] const auto __vi = __to_intrin(__v);
static_assert(sizeof(__v) == 64 && __have_avx512f);
if constexpr (__have_avx512bw && sizeof(_Tp) == 1) {
_mm512_mask_storeu_epi8(__mem, __k, __vi);
} else if constexpr (__have_avx512bw && sizeof(_Tp) == 2) {
_mm512_mask_storeu_epi16(__mem, __k, __vi);
} else if constexpr (__have_avx512f && sizeof(_Tp) == 4) {
if constexpr (__is_aligned_v<_F, 64> && std::is_integral_v<_Tp>) {
_mm512_mask_store_epi32(__mem, __k, __vi);
} else if constexpr (__is_aligned_v<_F, 64> && std::is_floating_point_v<_Tp>) {
_mm512_mask_store_ps(__mem, __k, __vi);
} else if constexpr (std::is_integral_v<_Tp>) {
_mm512_mask_storeu_epi32(__mem, __k, __vi);
} else {
_mm512_mask_storeu_ps(__mem, __k, __vi);
}
} else if constexpr (__have_avx512f && sizeof(_Tp) == 8) {
if constexpr (__is_aligned_v<_F, 64> && std::is_integral_v<_Tp>) {
_mm512_mask_store_epi64(__mem, __k, __vi);
} else if constexpr (__is_aligned_v<_F, 64> && std::is_floating_point_v<_Tp>) {
_mm512_mask_store_pd(__mem, __k, __vi);
} else if constexpr (std::is_integral_v<_Tp>) {
_mm512_mask_storeu_epi64(__mem, __k, __vi);
} else {
_mm512_mask_storeu_pd(__mem, __k, __vi);
}
} else if constexpr (__have_sse2) {
constexpr int _N = 16 / sizeof(_Tp);
using _M = __vector_type_t<_Tp, _N>;
_mm_maskmoveu_si128(__auto_bitcast(__extract<0, 4>(__v._M_data)),
__auto_bitcast(__convert_mask<_M>(__k._M_data)),
reinterpret_cast<char*>(__mem));
_mm_maskmoveu_si128(__auto_bitcast(__extract<1, 4>(__v._M_data)),
__auto_bitcast(__convert_mask<_M>(__k._M_data >> 1 * _N)),
reinterpret_cast<char*>(__mem) + 1 * 16);
_mm_maskmoveu_si128(__auto_bitcast(__extract<2, 4>(__v._M_data)),
__auto_bitcast(__convert_mask<_M>(__k._M_data >> 2 * _N)),
reinterpret_cast<char*>(__mem) + 2 * 16);
_mm_maskmoveu_si128(__auto_bitcast(__extract<3, 4>(__v._M_data)),
__auto_bitcast(__convert_mask<_M>(__k._M_data >> 3 * _N)),
reinterpret_cast<char*>(__mem) + 3 * 16);
} else {
__assert_unreachable<_Tp>();
}
}
template <class _Tp, class _F>
_GLIBCXX_SIMD_INTRINSIC void __maskstore(_SimdWrapper32<_Tp> __v, _Tp* __mem, _F,
_SimdWrapper32<_Tp> __k)
{
[[maybe_unused]] const auto __vi = __vector_bitcast<_LLong>(__v);
[[maybe_unused]] const auto __ki = __vector_bitcast<_LLong>(__k);
if constexpr (__have_avx512bw_vl && sizeof(_Tp) == 1) {
_mm256_mask_storeu_epi8(__mem, _mm256_movepi8_mask(__ki), __vi);
} else if constexpr (__have_avx512bw_vl && sizeof(_Tp) == 2) {
_mm256_mask_storeu_epi16(__mem, _mm256_movepi16_mask(__ki), __vi);
} else if constexpr (__have_avx2 && sizeof(_Tp) == 4 && std::is_integral_v<_Tp>) {
_mm256_maskstore_epi32(reinterpret_cast<int*>(__mem), __ki, __vi);
} else if constexpr (sizeof(_Tp) == 4) {
_mm256_maskstore_ps(reinterpret_cast<float*>(__mem), __ki,
__vector_bitcast<float>(__v));
} else if constexpr (__have_avx2 && sizeof(_Tp) == 8 && std::is_integral_v<_Tp>) {
_mm256_maskstore_epi64(reinterpret_cast<_LLong*>(__mem), __ki, __vi);
} else if constexpr (__have_avx && sizeof(_Tp) == 8) {
_mm256_maskstore_pd(reinterpret_cast<double*>(__mem), __ki,
__vector_bitcast<double>(__v));
} else if constexpr (__have_sse2) {
_mm_maskmoveu_si128(__lo128(__vi), __lo128(__ki), reinterpret_cast<char*>(__mem));
_mm_maskmoveu_si128(__hi128(__vi), __hi128(__ki),
reinterpret_cast<char*>(__mem) + 16);
} else {
__assert_unreachable<_Tp>();
}
}
template <class _Tp, class _F>
_GLIBCXX_SIMD_INTRINSIC void __maskstore(_SimdWrapper32<_Tp> __v, _Tp* __mem, _F,
_SimdWrapper<bool, _SimdWrapper32<_Tp>::_S_width> __k)
{
[[maybe_unused]] const auto __vi = __to_intrin(__v);
if constexpr (__have_avx512bw_vl && sizeof(_Tp) == 1) {
_mm256_mask_storeu_epi8(__mem, __k, __vi);
} else if constexpr (__have_avx512bw_vl && sizeof(_Tp) == 2) {
_mm256_mask_storeu_epi16(__mem, __k, __vi);
} else if constexpr (__have_avx512vl && sizeof(_Tp) == 4) {
if constexpr (__is_aligned_v<_F, 32> && std::is_integral_v<_Tp>) {
_mm256_mask_store_epi32(__mem, __k, __vi);
} else if constexpr (__is_aligned_v<_F, 32> && std::is_floating_point_v<_Tp>) {
_mm256_mask_store_ps(__mem, __k, __vi);
} else if constexpr (std::is_integral_v<_Tp>) {
_mm256_mask_storeu_epi32(__mem, __k, __vi);
} else {
_mm256_mask_storeu_ps(__mem, __k, __vi);
}
} else if constexpr (__have_avx512vl && sizeof(_Tp) == 8) {
if constexpr (__is_aligned_v<_F, 32> && std::is_integral_v<_Tp>) {
_mm256_mask_store_epi64(__mem, __k, __vi);
} else if constexpr (__is_aligned_v<_F, 32> && std::is_floating_point_v<_Tp>) {
_mm256_mask_store_pd(__mem, __k, __vi);
} else if constexpr (std::is_integral_v<_Tp>) {
_mm256_mask_storeu_epi64(__mem, __k, __vi);
} else {
_mm256_mask_storeu_pd(__mem, __k, __vi);
}
} else if constexpr (__have_avx512f && (sizeof(_Tp) >= 4 || __have_avx512bw)) {
__maskstore(
_SimdWrapper64<_Tp>(__intrin_bitcast<__vector_type64_t<_Tp>>(__v._M_data)),
__mem,
std::conditional_t<std::is_same_v<_F, vector_aligned_tag>,
overaligned_tag<32>, _F>(),
_SimdWrapper<bool, 64 / sizeof(_Tp)>(__k._M_data));
} else {
__maskstore(
__v, __mem, _F(),
_SimdWrapper32<_Tp>(__convert_mask<__vector_type_t<_Tp, 32 / sizeof(_Tp)>>(__k)));
}
}
#endif
template <class _Tp, class _F>
_GLIBCXX_SIMD_INTRINSIC void __maskstore(_SimdWrapper16<_Tp> __v, _Tp* __mem, _F,
_SimdWrapper16<_Tp> __k)
{
[[maybe_unused]] const auto __vi = __vector_bitcast<_LLong>(__v);
[[maybe_unused]] const auto __ki = __vector_bitcast<_LLong>(__k);
if constexpr (__have_avx512bw_vl && sizeof(_Tp) == 1) {
_mm_mask_storeu_epi8(__mem, _mm_movepi8_mask(__ki), __vi);
} else if constexpr (__have_avx512bw_vl && sizeof(_Tp) == 2) {
_mm_mask_storeu_epi16(__mem, _mm_movepi16_mask(__ki), __vi);
} else if constexpr (__have_avx2 && sizeof(_Tp) == 4 && std::is_integral_v<_Tp>) {
_mm_maskstore_epi32(reinterpret_cast<int*>(__mem), __ki, __vi);
} else if constexpr (__have_avx && sizeof(_Tp) == 4) {
_mm_maskstore_ps(reinterpret_cast<float*>(__mem), __ki,
__vector_bitcast<float>(__v));
} else if constexpr (__have_avx2 && sizeof(_Tp) == 8 && std::is_integral_v<_Tp>) {
_mm_maskstore_epi64(reinterpret_cast<_LLong*>(__mem), __ki, __vi);
} else if constexpr (__have_avx && sizeof(_Tp) == 8) {
_mm_maskstore_pd(reinterpret_cast<double*>(__mem), __ki,
__vector_bitcast<double>(__v));
} else if constexpr (__have_sse2) {
_mm_maskmoveu_si128(__vi, __ki, reinterpret_cast<char*>(__mem));
} else {
__bit_iteration(__vector_to_bitset(__k._M_data).to_ullong(),
[&](auto __i) constexpr { __mem[__i] = __v[__i]; });
}
}
template <class _Tp, class _F>
_GLIBCXX_SIMD_INTRINSIC void __maskstore(_SimdWrapper16<_Tp> __v, _Tp* __mem, _F,
_SimdWrapper<bool, _SimdWrapper16<_Tp>::_S_width> __k)
{
[[maybe_unused]] const auto __vi = __to_intrin(__v);
if constexpr (__have_avx512bw_vl && sizeof(_Tp) == 1) {
_mm_mask_storeu_epi8(__mem, __k, __vi);
} else if constexpr (__have_avx512bw_vl && sizeof(_Tp) == 2) {
_mm_mask_storeu_epi16(__mem, __k, __vi);
} else if constexpr (__have_avx512vl && sizeof(_Tp) == 4) {
if constexpr (__is_aligned_v<_F, 16> && std::is_integral_v<_Tp>) {
_mm_mask_store_epi32(__mem, __k, __vi);
} else if constexpr (__is_aligned_v<_F, 16> && std::is_floating_point_v<_Tp>) {
_mm_mask_store_ps(__mem, __k, __vi);
} else if constexpr (std::is_integral_v<_Tp>) {
_mm_mask_storeu_epi32(__mem, __k, __vi);
} else {
_mm_mask_storeu_ps(__mem, __k, __vi);
}
} else if constexpr (__have_avx512vl && sizeof(_Tp) == 8) {
if constexpr (__is_aligned_v<_F, 16> && std::is_integral_v<_Tp>) {
_mm_mask_store_epi64(__mem, __k, __vi);
} else if constexpr (__is_aligned_v<_F, 16> && std::is_floating_point_v<_Tp>) {
_mm_mask_store_pd(__mem, __k, __vi);
} else if constexpr (std::is_integral_v<_Tp>) {
_mm_mask_storeu_epi64(__mem, __k, __vi);
} else {
_mm_mask_storeu_pd(__mem, __k, __vi);
}
} else if constexpr (__have_avx512f && (sizeof(_Tp) >= 4 || __have_avx512bw)) {
__maskstore(
_SimdWrapper64<_Tp>(__intrin_bitcast<__intrinsic_type64_t<_Tp>>(__v._M_data)), __mem,
std::conditional_t<std::is_same_v<_F, vector_aligned_tag>,
overaligned_tag<16>, _F>(),
_SimdWrapper<bool, 64 / sizeof(_Tp)>(__k._M_data));
} else {
__maskstore(
__v, __mem, _F(),
_SimdWrapper16<_Tp>(__convert_mask<__vector_type_t<_Tp, 16 / sizeof(_Tp)>>(__k)));
}
}
template <typename _Tp, typename _F, typename _TVT = _VectorTraits<_Tp>>
_GLIBCXX_SIMD_INTRINSIC enable_if_t<sizeof(_Tp) == 8, void>
__maskstore(_Tp __v, typename _TVT::value_type* __mem, _F, _Tp __k)
{
__bit_iteration(__vector_to_bitset(__k).to_ulong(),
[&](auto __i) constexpr { __mem[__i] = __v[__i]; });
}
template <class _Tp, class _TVT = _VectorTraits<_Tp>>
_GLIBCXX_SIMD_INTRINSIC _Tp __xzyw(_Tp __a)
{
if constexpr (sizeof(_Tp) == 16) {
static_assert(sizeof(float) == 4 && sizeof(int) == 4);
const auto __x = __vector_bitcast<
conditional_t<is_floating_point_v<typename _TVT::value_type>, float, int>>(
__a);
return reinterpret_cast<_Tp>(decltype(__x){__x[0], __x[2], __x[1], __x[3]});
} else if constexpr (sizeof(_Tp) == 32) {
static_assert(sizeof(double) == 8 && sizeof(_LLong) == 8);
const auto __x =
__vector_bitcast<conditional_t<is_floating_point_v<typename _TVT::value_type>,
double, _LLong>>(__a);
return reinterpret_cast<_Tp>(decltype(__x){__x[0], __x[2], __x[1], __x[3]});
} else if constexpr (sizeof(_Tp) == 64) {
static_assert(sizeof(double) == 8 && sizeof(_LLong) == 8);
const auto __x =
__vector_bitcast<conditional_t<is_floating_point_v<typename _TVT::value_type>,
double, _LLong>>(__a);
return reinterpret_cast<_Tp>(decltype(__x){__x[0], __x[1], __x[4], __x[5], __x[2],
__x[3], __x[6], __x[7]});
} else {
__assert_unreachable<_Tp>();
}
}
template <unsigned __shift, class _Tp, class _TVT = _VectorTraits<_Tp>>
_GLIBCXX_SIMD_INTRINSIC _Tp __shift_elements_right(_Tp __v)
{
static_assert(__shift <= sizeof(_Tp));
if constexpr (__shift == 0) {
return __v;
} else if constexpr(__shift == sizeof(_Tp)) {
return _Tp();
#if _GLIBCXX_SIMD_X86INTRIN
} else if constexpr (__have_sse && __shift == 8 && _TVT::template __is<float, 4>) {
return _mm_movehl_ps(__v, __v);
} else if constexpr (__have_sse2 && __shift == 8 && _TVT::template __is<double, 2>) {
return _mm_unpackhi_pd(__v, __v);
} else if constexpr (__have_sse2 && sizeof(_Tp) == 16) {
return __intrin_bitcast<_Tp>(
_mm_srli_si128(__intrin_bitcast<__m128i>(__v), __shift));
#endif
}
else
{
constexpr int __chunksize =
__shift % 8 == 0 ? 8 : __shift % 4 == 0 ? 4 : __shift % 2 == 0 ? 2 : 1;
auto __w = __vector_bitcast<__int_with_sizeof_t<__chunksize>>(__v);
return __intrin_bitcast<_Tp>(decltype(__w){__w[__shift / __chunksize]});
}
}
template <size_t _Index, size_t _Total, class _Tp, typename _TVT>
_GLIBCXX_SIMD_INTRINSIC _GLIBCXX_SIMD_CONST
typename __vector_type<typename _TVT::value_type,
std::max(__min_vector_size,
int(sizeof(_Tp) / _Total))>::type
__extract_part(_Tp __x)
{
constexpr size_t _N = _TVT::_S_width;
constexpr size_t _NewN = _N / _Total;
static_assert(_Total > _Index, "_Total must be greater than _Index");
static_assert(_NewN * _Total == _N, "_N must be divisible by _Total");
if constexpr (_Index == 0 && _Total == 1)
return __x;
else if constexpr (sizeof(typename _TVT::value_type) * _NewN >=
__min_vector_size)
return __extract<_Index, _Total>(__x);
else
{
constexpr int __split = sizeof(__x) / __min_vector_size;
constexpr int __shift =
(sizeof(__x) / _Total * _Index) % __min_vector_size;
return __shift_elements_right<__shift>(
__extract_part<_Index * __split / _Total, __split>(__x));
}
}
template <size_t _Index, size_t _Total, size_t _N>
_GLIBCXX_SIMD_INTRINSIC constexpr __bool_storage_member_type_t<_N / _Total>
__extract_part(_SimdWrapper<bool, _N> __x)
{
static_assert(__have_avx512f && _N == _N);
static_assert(_Total >= 2 && _Index < _Total && _Index >= 0);
return __x._M_data >> (_Index * _N / _Total);
}
template <int _Index, int _Parts, class _Tp, class _A0, class... _As>
_GLIBCXX_SIMD_INTRINSIC auto
__extract_part(const _SimdTuple<_Tp, _A0, _As...> &__x)
{
using _Tuple = _SimdTuple<_Tp, _A0, _As...>;
static_assert(_Index < _Parts && _Index >= 0 && _Parts >= 1);
constexpr size_t _N = _Tuple::size();
static_assert(_N >= _Parts && _N % _Parts == 0);
constexpr size_t __values_per_part = _N / _Parts;
if constexpr (_Parts == 1) {
if constexpr (_Tuple::_S_tuple_size == 1) {
return __x.first._M_data;
} else {
return __x;
}
} else if constexpr (simd_size_v<_Tp, _A0> % __values_per_part != 0) {
#ifdef _GLIBCXX_SIMD_USE_ALIASING_LOADS
const __may_alias<_Tp> *const element_ptr =
reinterpret_cast<const __may_alias<_Tp> *>(&__x) + _Index * __values_per_part;
return __data(simd<_Tp, simd_abi::deduce_t<_Tp, __values_per_part>>(
[&](auto __i) constexpr { return element_ptr[__i]; }))
._M_data;
#else
[[maybe_unused]] constexpr size_t __offset = _Index * __values_per_part;
return __data(simd<_Tp, simd_abi::deduce_t<_Tp, __values_per_part>>([&](auto __i) constexpr {
constexpr _SizeConstant<__i + __offset> __k;
return __x[__k];
}))
._M_data;
#endif
} else if constexpr (__values_per_part * _Index >= simd_size_v<_Tp, _A0>) {
constexpr int __parts_in_first = simd_size_v<_Tp, _A0> / __values_per_part;
return __extract_part<_Index - __parts_in_first, _Parts - __parts_in_first>(__x.second);
} else {
static_assert(__values_per_part * (1 + _Index) <= simd_size_v<_Tp, _A0>);
if constexpr (simd_size_v<_Tp, _A0> == __values_per_part) {
return __x.first._M_data;
} else {
return __extract_part<_Index, simd_size_v<_Tp, _A0> / __values_per_part>(
__x.first);
}
}
}
#if _GLIBCXX_SIMD_HAVE_AVX512_ABI
template <size_t _N> class _ToWrapper<std::bitset<_N>>
{
std::bitset<_N> _M_data;
public:
template <class _U, size_t _M> constexpr operator _SimdWrapper<_U, _M>() const
{
static_assert(_M >= _N);
return __convert_mask<_SimdWrapper<_U, _M>>(_M_data);
}
};
#define _GLIBCXX_SIMD_TO_STORAGE(_Type) \
template <> class _ToWrapper<_Type> \
{ \
_Type _M_data; \
\
public: \
template <class _U, size_t _N> constexpr operator _SimdWrapper<_U, _N>() const \
{ \
static_assert(_N >= sizeof(_Type) * CHAR_BIT); \
return reinterpret_cast<__vector_type_t<_U, _N>>( \
__convert_mask<_SimdWrapper<_U, _N>>(_M_data)); \
} \
\
template <size_t _N> constexpr operator _SimdWrapper<bool, _N>() const \
{ \
static_assert( \
std::is_same_v<_Type, typename __bool_storage_member_type<_N>::type>); \
return _M_data; \
} \
}
_GLIBCXX_SIMD_TO_STORAGE(__mmask8);
_GLIBCXX_SIMD_TO_STORAGE(__mmask16);
_GLIBCXX_SIMD_TO_STORAGE(__mmask32);
_GLIBCXX_SIMD_TO_STORAGE(__mmask64);
#undef _GLIBCXX_SIMD_TO_STORAGE
#endif
#if _GLIBCXX_SIMD_HAVE_SSE && defined _GLIBCXX_SIMD_WORKAROUND_PR85048
#ifndef _GLIBCXX_EXPERIMENTAL_SIMD_X86_CONVERSIONS_H
#define _GLIBCXX_EXPERIMENTAL_SIMD_X86_CONVERSIONS_H 
#if __cplusplus >= 201703L
template <class _To, class _V, class _Traits> _GLIBCXX_SIMD_INTRINSIC _To __convert_x86(_V __v)
{
static_assert(__is_vector_type_v<_V>);
using _Tp = typename _Traits::value_type;
constexpr size_t _N = _Traits::_S_width;
[[maybe_unused]] const auto __intrin = __to_intrin(__v);
using _U = typename _VectorTraits<_To>::value_type;
constexpr size_t _M = _VectorTraits<_To>::_S_width;
[[maybe_unused]] constexpr bool __x_to_x = sizeof(__v) == 16 && sizeof(_To) == 16;
[[maybe_unused]] constexpr bool __x_to_y = sizeof(__v) == 16 && sizeof(_To) == 32;
[[maybe_unused]] constexpr bool __x_to_z = sizeof(__v) == 16 && sizeof(_To) == 64;
[[maybe_unused]] constexpr bool __y_to_x = sizeof(__v) == 32 && sizeof(_To) == 16;
[[maybe_unused]] constexpr bool __y_to_y = sizeof(__v) == 32 && sizeof(_To) == 32;
[[maybe_unused]] constexpr bool __y_to_z = sizeof(__v) == 32 && sizeof(_To) == 64;
[[maybe_unused]] constexpr bool __z_to_x = sizeof(__v) == 64 && sizeof(_To) == 16;
[[maybe_unused]] constexpr bool __z_to_y = sizeof(__v) == 64 && sizeof(_To) == 32;
[[maybe_unused]] constexpr bool __z_to_z = sizeof(__v) == 64 && sizeof(_To) == 64;
[[maybe_unused]] constexpr bool __i_to_i = is_integral_v<_U> && is_integral_v<_Tp>;
[[maybe_unused]] constexpr bool __i8_to_i16 = __i_to_i && sizeof(_Tp) == 1 && sizeof(_U) == 2;
[[maybe_unused]] constexpr bool __i8_to_i32 = __i_to_i && sizeof(_Tp) == 1 && sizeof(_U) == 4;
[[maybe_unused]] constexpr bool __i8_to_i64 = __i_to_i && sizeof(_Tp) == 1 && sizeof(_U) == 8;
[[maybe_unused]] constexpr bool __i16_to_i8 = __i_to_i && sizeof(_Tp) == 2 && sizeof(_U) == 1;
[[maybe_unused]] constexpr bool __i16_to_i32 = __i_to_i && sizeof(_Tp) == 2 && sizeof(_U) == 4;
[[maybe_unused]] constexpr bool __i16_to_i64 = __i_to_i && sizeof(_Tp) == 2 && sizeof(_U) == 8;
[[maybe_unused]] constexpr bool __i32_to_i8 = __i_to_i && sizeof(_Tp) == 4 && sizeof(_U) == 1;
[[maybe_unused]] constexpr bool __i32_to_i16 = __i_to_i && sizeof(_Tp) == 4 && sizeof(_U) == 2;
[[maybe_unused]] constexpr bool __i32_to_i64 = __i_to_i && sizeof(_Tp) == 4 && sizeof(_U) == 8;
[[maybe_unused]] constexpr bool __i64_to_i8 = __i_to_i && sizeof(_Tp) == 8 && sizeof(_U) == 1;
[[maybe_unused]] constexpr bool __i64_to_i16 = __i_to_i && sizeof(_Tp) == 8 && sizeof(_U) == 2;
[[maybe_unused]] constexpr bool __i64_to_i32 = __i_to_i && sizeof(_Tp) == 8 && sizeof(_U) == 4;
[[maybe_unused]] constexpr bool __s64_to_f32 = is_integral_v<_Tp> && is_signed_v<_Tp> && sizeof(_Tp) == 8 && is_floating_point_v<_U> && sizeof(_U) == 4;
[[maybe_unused]] constexpr bool __s32_to_f32 = is_integral_v<_Tp> && is_signed_v<_Tp> && sizeof(_Tp) == 4 && is_floating_point_v<_U> && sizeof(_U) == 4;
[[maybe_unused]] constexpr bool __s16_to_f32 = is_integral_v<_Tp> && is_signed_v<_Tp> && sizeof(_Tp) == 2 && is_floating_point_v<_U> && sizeof(_U) == 4;
[[maybe_unused]] constexpr bool __s8_to_f32 = is_integral_v<_Tp> && is_signed_v<_Tp> && sizeof(_Tp) == 1 && is_floating_point_v<_U> && sizeof(_U) == 4;
[[maybe_unused]] constexpr bool __u64_to_f32 = is_integral_v<_Tp> && is_unsigned_v<_Tp> && sizeof(_Tp) == 8 && is_floating_point_v<_U> && sizeof(_U) == 4;
[[maybe_unused]] constexpr bool __u32_to_f32 = is_integral_v<_Tp> && is_unsigned_v<_Tp> && sizeof(_Tp) == 4 && is_floating_point_v<_U> && sizeof(_U) == 4;
[[maybe_unused]] constexpr bool __u16_to_f32 = is_integral_v<_Tp> && is_unsigned_v<_Tp> && sizeof(_Tp) == 2 && is_floating_point_v<_U> && sizeof(_U) == 4;
[[maybe_unused]] constexpr bool __u8_to_f32 = is_integral_v<_Tp> && is_unsigned_v<_Tp> && sizeof(_Tp) == 1 && is_floating_point_v<_U> && sizeof(_U) == 4;
[[maybe_unused]] constexpr bool __s64_to_f64 = is_integral_v<_Tp> && is_signed_v<_Tp> && sizeof(_Tp) == 8 && is_floating_point_v<_U> && sizeof(_U) == 8;
[[maybe_unused]] constexpr bool __s32_to_f64 = is_integral_v<_Tp> && is_signed_v<_Tp> && sizeof(_Tp) == 4 && is_floating_point_v<_U> && sizeof(_U) == 8;
[[maybe_unused]] constexpr bool __u64_to_f64 = is_integral_v<_Tp> && is_unsigned_v<_Tp> && sizeof(_Tp) == 8 && is_floating_point_v<_U> && sizeof(_U) == 8;
[[maybe_unused]] constexpr bool __u32_to_f64 = is_integral_v<_Tp> && is_unsigned_v<_Tp> && sizeof(_Tp) == 4 && is_floating_point_v<_U> && sizeof(_U) == 8;
[[maybe_unused]] constexpr bool __f32_to_s64 = is_integral_v<_U> && is_signed_v<_U> && sizeof(_U) == 8 && is_floating_point_v<_Tp> && sizeof(_Tp) == 4;
[[maybe_unused]] constexpr bool __f32_to_s32 = is_integral_v<_U> && is_signed_v<_U> && sizeof(_U) == 4 && is_floating_point_v<_Tp> && sizeof(_Tp) == 4;
[[maybe_unused]] constexpr bool __f32_to_u64 = is_integral_v<_U> && is_unsigned_v<_U> && sizeof(_U) == 8 && is_floating_point_v<_Tp> && sizeof(_Tp) == 4;
[[maybe_unused]] constexpr bool __f32_to_u32 = is_integral_v<_U> && is_unsigned_v<_U> && sizeof(_U) == 4 && is_floating_point_v<_Tp> && sizeof(_Tp) == 4;
[[maybe_unused]] constexpr bool __f64_to_s64 = is_integral_v<_U> && is_signed_v<_U> && sizeof(_U) == 8 && is_floating_point_v<_Tp> && sizeof(_Tp) == 8;
[[maybe_unused]] constexpr bool __f64_to_s32 = is_integral_v<_U> && is_signed_v<_U> && sizeof(_U) == 4 && is_floating_point_v<_Tp> && sizeof(_Tp) == 8;
[[maybe_unused]] constexpr bool __f64_to_u64 = is_integral_v<_U> && is_unsigned_v<_U> && sizeof(_U) == 8 && is_floating_point_v<_Tp> && sizeof(_Tp) == 8;
[[maybe_unused]] constexpr bool __f64_to_u32 = is_integral_v<_U> && is_unsigned_v<_U> && sizeof(_U) == 4 && is_floating_point_v<_Tp> && sizeof(_Tp) == 8;
[[maybe_unused]] constexpr bool __ibw_to_f32 = is_integral_v<_Tp> && sizeof(_Tp) <= 2 && is_floating_point_v<_U> && sizeof(_U) == 4;
[[maybe_unused]] constexpr bool __ibw_to_f64 = is_integral_v<_Tp> && sizeof(_Tp) <= 2 && is_floating_point_v<_U> && sizeof(_U) == 8;
[[maybe_unused]] constexpr bool __f32_to_ibw = is_integral_v<_U> && sizeof(_U) <= 2 && is_floating_point_v<_Tp> && sizeof(_Tp) == 4;
[[maybe_unused]] constexpr bool __f64_to_ibw = is_integral_v<_U> && sizeof(_U) <= 2 && is_floating_point_v<_Tp> && sizeof(_Tp) == 8;
[[maybe_unused]] constexpr bool __f32_to_f64 = is_floating_point_v<_Tp> && sizeof(_Tp) == 4 && is_floating_point_v<_U> && sizeof(_U) == 8;
[[maybe_unused]] constexpr bool __f64_to_f32 = is_floating_point_v<_Tp> && sizeof(_Tp) == 8 && is_floating_point_v<_U> && sizeof(_U) == 4;
if constexpr (__i_to_i && __y_to_x && !__have_avx2) {
return __convert_x86<_To>(__lo128(__v), __hi128(__v));
} else if constexpr (__i_to_i && __x_to_y && !__have_avx2) {
return __concat(__convert_x86<__vector_type_t<_U, _M / 2>>(__v),
__convert_x86<__vector_type_t<_U, _M / 2>>(
__extract_part<1, _N / _M * 2>(__v)));
} else if constexpr (__i_to_i) {
static_assert(__x_to_x || __have_avx2,
"integral conversions with ymm registers require AVX2");
static_assert(__have_avx512bw || ((sizeof(_Tp) >= 4 || sizeof(__v) < 64) &&
(sizeof(_U) >= 4 || sizeof(_To) < 64)),
"8/16-bit integers in zmm registers require AVX512BW");
static_assert((sizeof(__v) < 64 && sizeof(_To) < 64) || __have_avx512f,
"integral conversions with ymm registers require AVX2");
}
if constexpr (is_floating_point_v<_Tp> == is_floating_point_v<_U> &&
sizeof(_Tp) == sizeof(_U)) {
if constexpr (_N >= _M) {
return __intrin_bitcast<_To>(__v);
} else {
return __zero_extend(__vector_bitcast<_U>(__v));
}
} else if constexpr (_N < _M && sizeof(_To) > 16) {
return __zero_extend(
__convert_x86<
__vector_type_t<_U, (16 / sizeof(_U) > _N) ? 16 / sizeof(_U) : _N>>(__v));
} else if constexpr (_N > _M && sizeof(__v) > 16) {
return __convert_x86<_To>(__extract_part<0, _N / _M>(__v));
} else if constexpr (__i64_to_i32) {
if constexpr (__x_to_x && __have_avx512vl) {
return __intrin_bitcast<_To>(_mm_cvtepi64_epi32(__intrin));
} else if constexpr (__x_to_x) {
return __auto_bitcast(_mm_shuffle_ps(__vector_bitcast<float>(__v), __m128(), 8));
} else if constexpr (__y_to_x && __have_avx512vl) {
return __intrin_bitcast<_To>(_mm256_cvtepi64_epi32(__intrin));
} else if constexpr (__y_to_x && __have_avx512f) {
return __intrin_bitcast<_To>(__lo128(_mm512_cvtepi64_epi32(__auto_bitcast(__v))));
} else if constexpr (__y_to_x) {
return __intrin_bitcast<_To>(__lo128(_mm256_permute4x64_epi64(_mm256_shuffle_epi32(__intrin, 8), 0 + 4 * 2)));
} else if constexpr (__z_to_y) {
return __intrin_bitcast<_To>(_mm512_cvtepi64_epi32(__intrin));
}
} else if constexpr (__i64_to_i16) {
if constexpr (__x_to_x && __have_avx512vl) {
return __intrin_bitcast<_To>(_mm_cvtepi64_epi16(__intrin));
} else if constexpr (__x_to_x && __have_avx512f) {
return __intrin_bitcast<_To>(__lo128(_mm512_cvtepi64_epi16(__auto_bitcast(__v))));
} else if constexpr (__x_to_x && __have_ssse3) {
return __intrin_bitcast<_To>(_mm_shuffle_epi8(
__intrin, _mm_setr_epi8(0, 1, 8, 9, -0x80, -0x80, -0x80, -0x80, -0x80, -0x80,
-0x80, -0x80, -0x80, -0x80, -0x80, -0x80)));
} else if constexpr (__y_to_x && __have_avx512vl) {
return __intrin_bitcast<_To>(_mm256_cvtepi64_epi16(__intrin));
} else if constexpr (__y_to_x && __have_avx512f) {
return __intrin_bitcast<_To>(__lo128(_mm512_cvtepi64_epi16(__auto_bitcast(__v))));
} else if constexpr (__y_to_x) {
const auto __a = _mm256_shuffle_epi8(
__intrin, _mm256_setr_epi8(0, 1, 8, 9, -0x80, -0x80, -0x80, -0x80, -0x80, -0x80,
-0x80, -0x80, -0x80, -0x80, -0x80, -0x80, -0x80,
-0x80, -0x80, -0x80, 0, 1, 8, 9, -0x80, -0x80, -0x80,
-0x80, -0x80, -0x80, -0x80, -0x80));
return __intrin_bitcast<_To>(__lo128(__a) | __hi128(__a));
} else if constexpr (__z_to_x) {
return __intrin_bitcast<_To>(_mm512_cvtepi64_epi16(__intrin));
}
} else if constexpr (__i64_to_i8) {
if constexpr (__x_to_x && __have_avx512vl) {
return __intrin_bitcast<_To>(_mm_cvtepi64_epi8(__intrin));
} else if constexpr (__x_to_x && __have_avx512f) {
return __intrin_bitcast<_To>(__lo128(_mm512_cvtepi64_epi8(__zero_extend(__intrin))));
} else if constexpr (__y_to_x && __have_avx512vl) {
return __intrin_bitcast<_To>(_mm256_cvtepi64_epi8(__intrin));
} else if constexpr (__y_to_x && __have_avx512f) {
return __intrin_bitcast<_To>(_mm512_cvtepi64_epi8(__zero_extend(__intrin)));
} else if constexpr (__z_to_x) {
return __intrin_bitcast<_To>(_mm512_cvtepi64_epi8(__intrin));
}
} else if constexpr (__i32_to_i64) {
if constexpr (__have_sse4_1 && __x_to_x) {
return __intrin_bitcast<_To>(is_signed_v<_Tp> ? _mm_cvtepi32_epi64(__intrin) : _mm_cvtepu32_epi64(__intrin));
} else if constexpr (__x_to_x) {
return __intrin_bitcast<_To>(_mm_unpacklo_epi32(
__intrin, is_signed_v<_Tp> ? _mm_srai_epi32(__intrin, 31) : __m128i()));
} else if constexpr (__x_to_y) {
return __intrin_bitcast<_To>(is_signed_v<_Tp> ? _mm256_cvtepi32_epi64(__intrin) : _mm256_cvtepu32_epi64(__intrin));
} else if constexpr (__y_to_z) {
return __intrin_bitcast<_To>(is_signed_v<_Tp> ? _mm512_cvtepi32_epi64(__intrin) : _mm512_cvtepu32_epi64(__intrin));
}
} else if constexpr (__i32_to_i16) {
if constexpr (__x_to_x && __have_avx512vl) {
return __intrin_bitcast<_To>(_mm_cvtepi32_epi16(__intrin));
} else if constexpr (__x_to_x && __have_avx512f) {
return __intrin_bitcast<_To>(__lo128(_mm512_cvtepi32_epi16(__auto_bitcast(__v))));
} else if constexpr (__x_to_x && __have_ssse3) {
return __intrin_bitcast<_To>(_mm_shuffle_epi8(
__intrin, _mm_setr_epi8(0, 1, 4, 5, 8, 9, 12, 13, -0x80, -0x80, -0x80, -0x80,
-0x80, -0x80, -0x80, -0x80)));
} else if constexpr (__x_to_x) {
auto __a = _mm_unpacklo_epi16(__intrin, __m128i());
auto __b = _mm_unpackhi_epi16(__intrin, __m128i());
auto __c = _mm_unpacklo_epi16(__a, __b);
auto __d = _mm_unpackhi_epi16(__a, __b);
return __intrin_bitcast<_To>(_mm_unpacklo_epi16(__c, __d));
} else if constexpr (__y_to_x && __have_avx512vl) {
return __intrin_bitcast<_To>(_mm256_cvtepi32_epi16(__intrin));
} else if constexpr (__y_to_x && __have_avx512f) {
return __intrin_bitcast<_To>(__lo128(_mm512_cvtepi32_epi16(__auto_bitcast(__v))));
} else if constexpr (__y_to_x) {
auto __a = _mm256_shuffle_epi8(
__intrin,
_mm256_setr_epi8(0, 1, 4, 5, 8, 9, 12, 13, -0x80, -0x80, -0x80, -0x80,
-0x80, -0x80, -0x80, -0x80, 0, 1, 4, 5, 8, 9, 12, 13,
-0x80, -0x80, -0x80, -0x80, -0x80, -0x80, -0x80, -0x80));
return __intrin_bitcast<_To>(
__lo128(_mm256_permute4x64_epi64(__a, 0xf8)));
} else if constexpr (__z_to_y) {
return __intrin_bitcast<_To>(_mm512_cvtepi32_epi16(__intrin));
}
} else if constexpr (__i32_to_i8) {
if constexpr (__x_to_x && __have_avx512vl) {
return __intrin_bitcast<_To>(_mm_cvtepi32_epi8(__intrin));
} else if constexpr (__x_to_x && __have_avx512f) {
return __intrin_bitcast<_To>(__lo128(_mm512_cvtepi32_epi8(__zero_extend(__intrin))));
} else if constexpr (__x_to_x && __have_ssse3) {
return __intrin_bitcast<_To>(_mm_shuffle_epi8(
__intrin, _mm_setr_epi8(0, 4, 8, 12, -0x80, -0x80, -0x80, -0x80, -0x80, -0x80,
-0x80, -0x80, -0x80, -0x80, -0x80, -0x80)));
} else if constexpr (__x_to_x) {
const auto __a = _mm_unpacklo_epi8(__intrin, __intrin);
const auto __b = _mm_unpackhi_epi8(__intrin, __intrin);
const auto __c = _mm_unpacklo_epi8(__a, __b);
const auto __d = _mm_unpackhi_epi8(__a, __b);
const auto __e = _mm_unpacklo_epi8(__c, __d);
return __intrin_bitcast<_To>(__e & _mm_cvtsi32_si128(-1));
} else if constexpr (__y_to_x && __have_avx512vl) {
return __intrin_bitcast<_To>(_mm256_cvtepi32_epi8(__intrin));
} else if constexpr (__y_to_x && __have_avx512f) {
return __intrin_bitcast<_To>(_mm512_cvtepi32_epi8(__zero_extend(__intrin)));
} else if constexpr (__z_to_x) {
return __intrin_bitcast<_To>(_mm512_cvtepi32_epi8(__intrin));
}
} else if constexpr (__i16_to_i64) {
if constexpr (__x_to_x && __have_sse4_1) {
return __intrin_bitcast<_To>(is_signed_v<_Tp> ? _mm_cvtepi16_epi64(__intrin) : _mm_cvtepu16_epi64(__intrin));
} else if constexpr (__x_to_x && is_signed_v<_Tp>) {
auto __x = _mm_srai_epi16(__intrin, 15);
auto __y = _mm_unpacklo_epi16(__intrin, __x);
__x = _mm_unpacklo_epi16(__x, __x);
return __intrin_bitcast<_To>(_mm_unpacklo_epi32(__y, __x));
} else if constexpr (__x_to_x) {
return __intrin_bitcast<_To>(_mm_unpacklo_epi32(_mm_unpacklo_epi16(__intrin, __m128i()), __m128i()));
} else if constexpr (__x_to_y) {
return __intrin_bitcast<_To>(is_signed_v<_Tp> ? _mm256_cvtepi16_epi64(__intrin) : _mm256_cvtepu16_epi64(__intrin));
} else if constexpr (__x_to_z) {
return __intrin_bitcast<_To>(is_signed_v<_Tp> ? _mm512_cvtepi16_epi64(__intrin) : _mm512_cvtepu16_epi64(__intrin));
}
} else if constexpr (__i16_to_i32) {
if constexpr (__x_to_x && __have_sse4_1) {
return __intrin_bitcast<_To>(is_signed_v<_Tp> ? _mm_cvtepi16_epi32(__intrin) : _mm_cvtepu16_epi32(__intrin));
} else if constexpr (__x_to_x && is_signed_v<_Tp>) {
return __intrin_bitcast<_To>(_mm_srai_epi32(_mm_unpacklo_epi16(__intrin, __intrin), 16));
} else if constexpr (__x_to_x && is_unsigned_v<_Tp>) {
return __intrin_bitcast<_To>(_mm_unpacklo_epi16(__intrin, __m128i()));
} else if constexpr (__x_to_y) {
return __intrin_bitcast<_To>(is_signed_v<_Tp> ? _mm256_cvtepi16_epi32(__intrin) : _mm256_cvtepu16_epi32(__intrin));
} else if constexpr (__y_to_z) {
return __intrin_bitcast<_To>(is_signed_v<_Tp> ? _mm512_cvtepi16_epi32(__intrin) : _mm512_cvtepu16_epi32(__intrin));
}
} else if constexpr (__i16_to_i8) {
if constexpr (__x_to_x && __have_avx512bw_vl) {
return __intrin_bitcast<_To>(_mm_cvtepi16_epi8(__intrin));
} else if constexpr (__x_to_x && __have_avx512bw) {
return __intrin_bitcast<_To>(__lo128(_mm512_cvtepi16_epi8(__zero_extend(__intrin))));
} else if constexpr (__x_to_x && __have_ssse3) {
return __intrin_bitcast<_To>(_mm_shuffle_epi8(
__intrin, _mm_setr_epi8(0, 2, 4, 6, 8, 10, 12, 14, -0x80, -0x80, -0x80, -0x80,
-0x80, -0x80, -0x80, -0x80)));
} else if constexpr (__x_to_x) {
auto __a = _mm_unpacklo_epi8(__intrin, __intrin);
auto __b = _mm_unpackhi_epi8(__intrin, __intrin);
auto __c = _mm_unpacklo_epi8(__a, __b);
auto __d = _mm_unpackhi_epi8(__a, __b);
auto __e = _mm_unpacklo_epi8(__c, __d);
auto __f = _mm_unpackhi_epi8(__c, __d);
return __intrin_bitcast<_To>(_mm_unpacklo_epi8(__e, __f));
} else if constexpr (__y_to_x && __have_avx512bw_vl) {
return __intrin_bitcast<_To>(_mm256_cvtepi16_epi8(__intrin));
} else if constexpr (__y_to_x && __have_avx512bw) {
return __intrin_bitcast<_To>(__lo256(_mm512_cvtepi16_epi8(__zero_extend(__intrin))));
} else if constexpr (__y_to_x) {
auto __a = _mm256_shuffle_epi8(
__intrin,
_mm256_setr_epi8(0, 2, 4, 6, 8, 10, 12, 14, -0x80, -0x80, -0x80, -0x80,
-0x80, -0x80, -0x80, -0x80, -0x80, -0x80, -0x80, -0x80,
-0x80, -0x80, -0x80, -0x80, 0, 2, 4, 6, 8, 10, 12, 14));
return __intrin_bitcast<_To>(__lo128(__a) | __hi128(__a));
} else if constexpr (__z_to_y && __have_avx512bw) {
return __intrin_bitcast<_To>(_mm512_cvtepi16_epi8(__intrin));
} else if constexpr (__z_to_y) {
__assert_unreachable<_Tp>();
}
} else if constexpr (__i8_to_i64) {
if constexpr (__x_to_x && __have_sse4_1) {
return __intrin_bitcast<_To>(is_signed_v<_Tp> ? _mm_cvtepi8_epi64(__intrin) : _mm_cvtepu8_epi64(__intrin));
} else if constexpr (__x_to_x && is_signed_v<_Tp>) {
if constexpr (__have_ssse3) {
auto __dup = _mm_unpacklo_epi8(__intrin, __intrin);
auto __epi16 = _mm_srai_epi16(__dup, 8);
_mm_shuffle_epi8(
__epi16, _mm_setr_epi8(0, 1, 1, 1, 1, 1, 1, 1, 2, 3, 3, 3, 3, 3, 3, 3));
} else {
auto __x = _mm_unpacklo_epi8(__intrin, __intrin);
__x = _mm_unpacklo_epi16(__x, __x);
return __intrin_bitcast<_To>(
_mm_unpacklo_epi32(_mm_srai_epi32(__x, 24), _mm_srai_epi32(__x, 31)));
}
} else if constexpr (__x_to_x) {
return __intrin_bitcast<_To>(_mm_unpacklo_epi32(
_mm_unpacklo_epi16(_mm_unpacklo_epi8(__intrin, __m128i()), __m128i()),
__m128i()));
} else if constexpr (__x_to_y) {
return __intrin_bitcast<_To>(is_signed_v<_Tp> ? _mm256_cvtepi8_epi64(__intrin) : _mm256_cvtepu8_epi64(__intrin));
} else if constexpr (__x_to_z) {
return __intrin_bitcast<_To>(is_signed_v<_Tp> ? _mm512_cvtepi8_epi64(__intrin) : _mm512_cvtepu8_epi64(__intrin));
}
} else if constexpr (__i8_to_i32) {
if constexpr (__x_to_x && __have_sse4_1) {
return __intrin_bitcast<_To>(is_signed_v<_Tp> ? _mm_cvtepi8_epi32(__intrin) : _mm_cvtepu8_epi32(__intrin));
} else if constexpr (__x_to_x && is_signed_v<_Tp>) {
const auto __x = _mm_unpacklo_epi8(__intrin, __intrin);
return __intrin_bitcast<_To>(_mm_srai_epi32(_mm_unpacklo_epi16(__x, __x), 24));
} else if constexpr (__x_to_x && is_unsigned_v<_Tp>) {
return __intrin_bitcast<_To>(_mm_unpacklo_epi16(_mm_unpacklo_epi8(__intrin, __m128i()), __m128i()));
} else if constexpr (__x_to_y) {
return __intrin_bitcast<_To>(is_signed_v<_Tp> ? _mm256_cvtepi8_epi32(__intrin) : _mm256_cvtepu8_epi32(__intrin));
} else if constexpr (__x_to_z) {
return __intrin_bitcast<_To>(is_signed_v<_Tp> ? _mm512_cvtepi8_epi32(__intrin) : _mm512_cvtepu8_epi32(__intrin));
}
} else if constexpr (__i8_to_i16) {
if constexpr (__x_to_x && __have_sse4_1) {
return __intrin_bitcast<_To>(is_signed_v<_Tp> ? _mm_cvtepi8_epi16(__intrin) : _mm_cvtepu8_epi16(__intrin));
} else if constexpr (__x_to_x && is_signed_v<_Tp>) {
return __intrin_bitcast<_To>(_mm_srai_epi16(_mm_unpacklo_epi8(__intrin, __intrin), 8));
} else if constexpr (__x_to_x && is_unsigned_v<_Tp>) {
return __intrin_bitcast<_To>(_mm_unpacklo_epi8(__intrin, __m128i()));
} else if constexpr (__x_to_y) {
return __intrin_bitcast<_To>(is_signed_v<_Tp> ? _mm256_cvtepi8_epi16(__intrin) : _mm256_cvtepu8_epi16(__intrin));
} else if constexpr (__y_to_z && __have_avx512bw) {
return __intrin_bitcast<_To>(is_signed_v<_Tp> ? _mm512_cvtepi8_epi16(__intrin) : _mm512_cvtepu8_epi16(__intrin));
} else if constexpr (__y_to_z) {
__assert_unreachable<_Tp>();
}
} else if constexpr (__f32_to_s64) {
if constexpr (__have_avx512dq_vl && __x_to_x) {
return __intrin_bitcast<_To>(_mm_cvttps_epi64(__intrin));
} else if constexpr (__have_avx512dq_vl && __x_to_y) {
return __intrin_bitcast<_To>(_mm256_cvttps_epi64(__intrin));
} else if constexpr (__have_avx512dq && __y_to_z) {
return __intrin_bitcast<_To>(_mm512_cvttps_epi64(__intrin));
}
} else if constexpr (__f32_to_u64) {
if constexpr (__have_avx512dq_vl && __x_to_x) {
return __intrin_bitcast<_To>(_mm_cvttps_epu64(__intrin));
} else if constexpr (__have_avx512dq_vl && __x_to_y) {
return __intrin_bitcast<_To>(_mm256_cvttps_epu64(__intrin));
} else if constexpr (__have_avx512dq && __y_to_z) {
return __intrin_bitcast<_To>(_mm512_cvttps_epu64(__intrin));
}
} else if constexpr (__f32_to_s32) {
if constexpr (__x_to_x || __y_to_y || __z_to_z) {
} else {
__assert_unreachable<_Tp>();
}
} else if constexpr (__f32_to_u32) {
if constexpr (__have_avx512vl && __x_to_x) {
const __vector_type_t<float, 4> __x = __v;
return __builtin_constant_p(__x) ? __make_vector<_U>(__x[0], __x[1], __x[2], __x[3])
: __vector_bitcast<_U>(_mm_cvttps_epu32(__intrin));
} else if constexpr (__have_avx512f && __x_to_x) {
const __vector_type_t<float, 4> __x = __v;
return __builtin_constant_p(__x)
? __make_vector<_U>(__x[0], __x[1], __x[2], __x[3])
: __vector_bitcast<_U>(__lo128(_mm512_cvttps_epu32(__auto_bitcast(__v))));
} else if constexpr (__have_avx512vl && __y_to_y) {
const __vector_type_t<float, 8> __x = __v;
return __builtin_constant_p(__x) ? __make_vector<_U>(__x[0], __x[1], __x[2], __x[3],
__x[4], __x[5], __x[6], __x[7])
: __vector_bitcast<_U>(_mm256_cvttps_epu32(__intrin));
} else if constexpr (__have_avx512f && __y_to_y) {
const __vector_type_t<float, 8> __x = __v;
return __builtin_constant_p(__x)
? __make_vector<_U>(__x[0], __x[1], __x[2], __x[3], __x[4], __x[5], __x[6],
__x[7])
: __vector_bitcast<_U>(__lo256(_mm512_cvttps_epu32(__auto_bitcast(__v))));
} else if constexpr (__x_to_x || __y_to_y || __z_to_z) {
} else {
__assert_unreachable<_Tp>();
}
} else if constexpr (__f32_to_ibw) {
return __convert_x86<_To>(__convert_x86<__vector_type_t<int, _N>>(__v));
} else if constexpr (__f64_to_s64) {
if constexpr (__have_avx512dq_vl && __x_to_x) {
return __intrin_bitcast<_To>(_mm_cvttpd_epi64(__intrin));
} else if constexpr (__have_avx512dq_vl && __y_to_y) {
return __intrin_bitcast<_To>(_mm256_cvttpd_epi64(__intrin));
} else if constexpr (__have_avx512dq && __z_to_z) {
return __intrin_bitcast<_To>(_mm512_cvttpd_epi64(__intrin));
}
} else if constexpr (__f64_to_u64) {
if constexpr (__have_avx512dq_vl && __x_to_x) {
return __intrin_bitcast<_To>(_mm_cvttpd_epu64(__intrin));
} else if constexpr (__have_avx512dq_vl && __y_to_y) {
return __intrin_bitcast<_To>(_mm256_cvttpd_epu64(__intrin));
} else if constexpr (__have_avx512dq && __z_to_z) {
return __intrin_bitcast<_To>(_mm512_cvttpd_epu64(__intrin));
}
} else if constexpr (__f64_to_s32) {
if constexpr (__x_to_x) {
return __intrin_bitcast<_To>(_mm_cvttpd_epi32(__intrin));
} else if constexpr (__y_to_x) {
return __intrin_bitcast<_To>(_mm256_cvttpd_epi32(__intrin));
} else if constexpr (__z_to_y) {
return __intrin_bitcast<_To>(_mm512_cvttpd_epi32(__intrin));
}
} else if constexpr (__f64_to_u32) {
if constexpr (__have_avx512vl && __x_to_x) {
return __intrin_bitcast<_To>(_mm_cvttpd_epu32(__intrin));
} else if constexpr (__have_sse4_1 && __x_to_x) {
return __vector_bitcast<_U>(_mm_cvttpd_epi32(_mm_floor_pd(__intrin) - 0x8000'0000u)) ^
0x8000'0000u;
} else if constexpr (__x_to_x) {
} else if constexpr (__have_avx512vl && __y_to_x) {
return __intrin_bitcast<_To>(_mm256_cvttpd_epu32(__intrin));
} else if constexpr (__y_to_x) {
return __intrin_bitcast<_To>(__vector_bitcast<_U>(_mm256_cvttpd_epi32(
_mm256_floor_pd(__intrin) - 0x8000'0000u)) ^
0x8000'0000u);
} else if constexpr (__z_to_y) {
return __intrin_bitcast<_To>(_mm512_cvttpd_epu32(__intrin));
}
} else if constexpr (__f64_to_ibw) {
return __convert_x86<_To>(__convert_x86<__vector_type_t<int, (_N < 4 ? 4 : _N)>>(__v));
} else if constexpr (__s64_to_f32) {
if constexpr (__x_to_x && __have_avx512dq_vl) {
return __intrin_bitcast<_To>(_mm_cvtepi64_ps(__intrin));
} else if constexpr (__y_to_x && __have_avx512dq_vl) {
return __intrin_bitcast<_To>(_mm256_cvtepi64_ps(__intrin));
} else if constexpr (__z_to_y && __have_avx512dq) {
return __intrin_bitcast<_To>(_mm512_cvtepi64_ps(__intrin));
} else if constexpr (__z_to_y) {
return __intrin_bitcast<_To>(_mm512_cvtpd_ps(__convert_x86<__vector_type_t<double, 8>>(__v)));
}
} else if constexpr (__u64_to_f32) {
if constexpr (__x_to_x && __have_avx512dq_vl) {
return __intrin_bitcast<_To>(_mm_cvtepu64_ps(__intrin));
} else if constexpr (__y_to_x && __have_avx512dq_vl) {
return __intrin_bitcast<_To>(_mm256_cvtepu64_ps(__intrin));
} else if constexpr (__z_to_y && __have_avx512dq) {
return __intrin_bitcast<_To>(_mm512_cvtepu64_ps(__intrin));
} else if constexpr (__z_to_y) {
return __intrin_bitcast<_To>(
__lo256(_mm512_cvtepu32_ps(
__auto_bitcast(_mm512_cvtepi64_epi32(_mm512_srai_epi64(__intrin, 32))))) *
0x100000000LL +
__lo256(_mm512_cvtepu32_ps(__auto_bitcast(_mm512_cvtepi64_epi32(__intrin)))));
}
} else if constexpr (__s32_to_f32) {
} else if constexpr (__u32_to_f32) {
if constexpr(__x_to_x && __have_avx512vl) {
} else if constexpr(__x_to_x && __have_avx512f) {
return __intrin_bitcast<_To>(__lo128(_mm512_cvtepu32_ps(__auto_bitcast(__v))));
} else if constexpr(__x_to_x && (__have_fma || __have_fma4)) {
return 0x10000 * _mm_cvtepi32_ps(__to_intrin(__v >> 16)) +
_mm_cvtepi32_ps(__to_intrin(__v & 0xffff));
} else if constexpr(__y_to_y && __have_avx512vl) {
} else if constexpr(__y_to_y && __have_avx512f) {
return __intrin_bitcast<_To>(__lo256(_mm512_cvtepu32_ps(__auto_bitcast(__v))));
} else if constexpr(__y_to_y) {
return 0x10000 * _mm256_cvtepi32_ps(__to_intrin(__v >> 16)) +
_mm256_cvtepi32_ps(__to_intrin(__v & 0xffff));
}
} else if constexpr (__ibw_to_f32) {
if constexpr (_M == 4 || __have_avx2) {
return __convert_x86<_To>(__convert_x86<__vector_type_t<int, _M>>(__v));
} else {
static_assert(__x_to_y);
__m128i __a, __b;
if constexpr (__have_sse4_1) {
__a = sizeof(_Tp) == 2
? (is_signed_v<_Tp> ? _mm_cvtepi16_epi32(__intrin) : _mm_cvtepu16_epi32(__intrin))
: (is_signed_v<_Tp> ? _mm_cvtepi8_epi32(__intrin) : _mm_cvtepu8_epi32(__intrin));
const auto __w = _mm_shuffle_epi32(__intrin, sizeof(_Tp) == 2 ? 0xee : 0xe9);
__b = sizeof(_Tp) == 2
? (is_signed_v<_Tp> ? _mm_cvtepi16_epi32(__w) : _mm_cvtepu16_epi32(__w))
: (is_signed_v<_Tp> ? _mm_cvtepi8_epi32(__w) : _mm_cvtepu8_epi32(__w));
} else {
__m128i __tmp;
if constexpr (sizeof(_Tp) == 1) {
__tmp = is_signed_v<_Tp> ? _mm_srai_epi16(_mm_unpacklo_epi8(__intrin, __intrin), 8):
_mm_unpacklo_epi8(__intrin, __m128i());
} else {
static_assert(sizeof(_Tp) == 2);
__tmp = __intrin;
}
__a = is_signed_v<_Tp> ? _mm_srai_epi32(_mm_unpacklo_epi16(__tmp, __tmp), 16)
: _mm_unpacklo_epi16(__tmp, __m128i());
__b = is_signed_v<_Tp> ? _mm_srai_epi32(_mm_unpackhi_epi16(__tmp, __tmp), 16)
: _mm_unpackhi_epi16(__tmp, __m128i());
}
return __convert_x86<_To>(__vector_bitcast<int>(__a), __vector_bitcast<int>(__b));
}
} else if constexpr (__s64_to_f64) {
if constexpr (__x_to_x && __have_avx512dq_vl) {
return __intrin_bitcast<_To>(_mm_cvtepi64_pd(__intrin));
} else if constexpr (__y_to_y && __have_avx512dq_vl) {
return __intrin_bitcast<_To>(_mm256_cvtepi64_pd(__intrin));
} else if constexpr (__z_to_z && __have_avx512dq) {
return __intrin_bitcast<_To>(_mm512_cvtepi64_pd(__intrin));
} else if constexpr (__z_to_z) {
return __intrin_bitcast<_To>(
_mm512_cvtepi32_pd(_mm512_cvtepi64_epi32(__to_intrin(__v >> 32))) *
0x100000000LL +
_mm512_cvtepu32_pd(_mm512_cvtepi64_epi32(__intrin)));
}
} else if constexpr (__u64_to_f64) {
if constexpr (__x_to_x && __have_avx512dq_vl) {
return __intrin_bitcast<_To>(_mm_cvtepu64_pd(__intrin));
} else if constexpr (__y_to_y && __have_avx512dq_vl) {
return __intrin_bitcast<_To>(_mm256_cvtepu64_pd(__intrin));
} else if constexpr (__z_to_z && __have_avx512dq) {
return __intrin_bitcast<_To>(_mm512_cvtepu64_pd(__intrin));
} else if constexpr (__z_to_z) {
return __intrin_bitcast<_To>(
_mm512_cvtepu32_pd(_mm512_cvtepi64_epi32(__to_intrin(__v >> 32))) *
0x100000000LL +
_mm512_cvtepu32_pd(_mm512_cvtepi64_epi32(__intrin)));
}
} else if constexpr (__s32_to_f64) {
if constexpr (__x_to_x) {
return __intrin_bitcast<_To>(_mm_cvtepi32_pd(__intrin));
} else if constexpr (__x_to_y) {
return __intrin_bitcast<_To>(_mm256_cvtepi32_pd(__intrin));
} else if constexpr (__y_to_z) {
return __intrin_bitcast<_To>(_mm512_cvtepi32_pd(__intrin));
}
} else if constexpr (__u32_to_f64) {
if constexpr (__x_to_x && __have_avx512vl) {
return __intrin_bitcast<_To>(_mm_cvtepu32_pd(__intrin));
} else if constexpr (__x_to_x && __have_avx512f) {
return __intrin_bitcast<_To>(__lo128(_mm512_cvtepu32_pd(__auto_bitcast(__v))));
} else if constexpr (__x_to_x) {
return __intrin_bitcast<_To>(_mm_cvtepi32_pd(__to_intrin(__v ^ 0x8000'0000u)) + 0x8000'0000u);
} else if constexpr (__x_to_y && __have_avx512vl) {
return __intrin_bitcast<_To>(_mm256_cvtepu32_pd(__intrin));
} else if constexpr (__x_to_y && __have_avx512f) {
return __intrin_bitcast<_To>(__lo256(_mm512_cvtepu32_pd(__auto_bitcast(__v))));
} else if constexpr (__x_to_y) {
return __intrin_bitcast<_To>(_mm256_cvtepi32_pd(__to_intrin(__v ^ 0x8000'0000u)) + 0x8000'0000u);
} else if constexpr (__y_to_z) {
return __intrin_bitcast<_To>(_mm512_cvtepu32_pd(__intrin));
}
} else if constexpr (__ibw_to_f64) {
return __convert_x86<_To>(__convert_x86<__vector_type_t<int, std::max(size_t(4), _M)>>(__v));
} else if constexpr (__f32_to_f64) {
if constexpr (__x_to_x) {
return __intrin_bitcast<_To>(_mm_cvtps_pd(__intrin));
} else if constexpr (__x_to_y) {
return __intrin_bitcast<_To>(_mm256_cvtps_pd(__intrin));
} else if constexpr (__y_to_z) {
return __intrin_bitcast<_To>(_mm512_cvtps_pd(__intrin));
}
} else if constexpr (__f64_to_f32) {
if constexpr (__x_to_x) {
return __intrin_bitcast<_To>(_mm_cvtpd_ps(__intrin));
} else if constexpr (__y_to_x) {
return __intrin_bitcast<_To>(_mm256_cvtpd_ps(__intrin));
} else if constexpr (__z_to_y) {
return __intrin_bitcast<_To>(_mm512_cvtpd_ps(__intrin));
}
} else {
__assert_unreachable<_Tp>();
}
return __vector_convert<_To>(__v, make_index_sequence<std::min(_M, _N)>());
}
template <class _To, class _V, class _Traits> _GLIBCXX_SIMD_INTRINSIC _To __convert_x86(_V __v0, _V __v1)
{
static_assert(__is_vector_type_v<_V>);
using _Tp = typename _Traits::value_type;
constexpr size_t _N = _Traits::_S_width;
[[maybe_unused]] const auto __i0 = __to_intrin(__v0);
[[maybe_unused]] const auto __i1 = __to_intrin(__v1);
using _U = typename _VectorTraits<_To>::value_type;
constexpr size_t _M = _VectorTraits<_To>::_S_width;
static_assert(
2 * _N <= _M,
"__v1 would be discarded; use the one-argument __convert_x86 overload instead");
[[maybe_unused]] constexpr bool __x_to_x = sizeof(__v0) == 16 && sizeof(_To) == 16;
[[maybe_unused]] constexpr bool __x_to_y = sizeof(__v0) == 16 && sizeof(_To) == 32;
[[maybe_unused]] constexpr bool __x_to_z = sizeof(__v0) == 16 && sizeof(_To) == 64;
[[maybe_unused]] constexpr bool __y_to_x = sizeof(__v0) == 32 && sizeof(_To) == 16;
[[maybe_unused]] constexpr bool __y_to_y = sizeof(__v0) == 32 && sizeof(_To) == 32;
[[maybe_unused]] constexpr bool __y_to_z = sizeof(__v0) == 32 && sizeof(_To) == 64;
[[maybe_unused]] constexpr bool __z_to_x = sizeof(__v0) == 64 && sizeof(_To) == 16;
[[maybe_unused]] constexpr bool __z_to_y = sizeof(__v0) == 64 && sizeof(_To) == 32;
[[maybe_unused]] constexpr bool __z_to_z = sizeof(__v0) == 64 && sizeof(_To) == 64;
[[maybe_unused]] constexpr bool __i_to_i = std::is_integral_v<_U> && std::is_integral_v<_Tp>;
[[maybe_unused]] constexpr bool __i8_to_i16 = __i_to_i && sizeof(_Tp) == 1 && sizeof(_U) == 2;
[[maybe_unused]] constexpr bool __i8_to_i32 = __i_to_i && sizeof(_Tp) == 1 && sizeof(_U) == 4;
[[maybe_unused]] constexpr bool __i8_to_i64 = __i_to_i && sizeof(_Tp) == 1 && sizeof(_U) == 8;
[[maybe_unused]] constexpr bool __i16_to_i8 = __i_to_i && sizeof(_Tp) == 2 && sizeof(_U) == 1;
[[maybe_unused]] constexpr bool __i16_to_i32 = __i_to_i && sizeof(_Tp) == 2 && sizeof(_U) == 4;
[[maybe_unused]] constexpr bool __i16_to_i64 = __i_to_i && sizeof(_Tp) == 2 && sizeof(_U) == 8;
[[maybe_unused]] constexpr bool __i32_to_i8 = __i_to_i && sizeof(_Tp) == 4 && sizeof(_U) == 1;
[[maybe_unused]] constexpr bool __i32_to_i16 = __i_to_i && sizeof(_Tp) == 4 && sizeof(_U) == 2;
[[maybe_unused]] constexpr bool __i32_to_i64 = __i_to_i && sizeof(_Tp) == 4 && sizeof(_U) == 8;
[[maybe_unused]] constexpr bool __i64_to_i8 = __i_to_i && sizeof(_Tp) == 8 && sizeof(_U) == 1;
[[maybe_unused]] constexpr bool __i64_to_i16 = __i_to_i && sizeof(_Tp) == 8 && sizeof(_U) == 2;
[[maybe_unused]] constexpr bool __i64_to_i32 = __i_to_i && sizeof(_Tp) == 8 && sizeof(_U) == 4;
[[maybe_unused]] constexpr bool __i64_to_f32 = is_integral_v<_Tp> && sizeof(_Tp) == 8 && is_floating_point_v<_U> && sizeof(_U) == 4;
[[maybe_unused]] constexpr bool __s32_to_f32 = is_integral_v<_Tp> && is_signed_v<_Tp> && sizeof(_Tp) == 4 && is_floating_point_v<_U> && sizeof(_U) == 4;
[[maybe_unused]] constexpr bool __s16_to_f32 = is_integral_v<_Tp> && is_signed_v<_Tp> && sizeof(_Tp) == 2 && is_floating_point_v<_U> && sizeof(_U) == 4;
[[maybe_unused]] constexpr bool __s8_to_f32 = is_integral_v<_Tp> && is_signed_v<_Tp> && sizeof(_Tp) == 1 && is_floating_point_v<_U> && sizeof(_U) == 4;
[[maybe_unused]] constexpr bool __u32_to_f32 = is_integral_v<_Tp> && is_unsigned_v<_Tp> && sizeof(_Tp) == 4 && is_floating_point_v<_U> && sizeof(_U) == 4;
[[maybe_unused]] constexpr bool __u16_to_f32 = is_integral_v<_Tp> && is_unsigned_v<_Tp> && sizeof(_Tp) == 2 && is_floating_point_v<_U> && sizeof(_U) == 4;
[[maybe_unused]] constexpr bool __u8_to_f32 = is_integral_v<_Tp> && is_unsigned_v<_Tp> && sizeof(_Tp) == 1 && is_floating_point_v<_U> && sizeof(_U) == 4;
[[maybe_unused]] constexpr bool __s64_to_f64 = is_integral_v<_Tp> && is_signed_v<_Tp> && sizeof(_Tp) == 8 && is_floating_point_v<_U> && sizeof(_U) == 8;
[[maybe_unused]] constexpr bool __s32_to_f64 = is_integral_v<_Tp> && is_signed_v<_Tp> && sizeof(_Tp) == 4 && is_floating_point_v<_U> && sizeof(_U) == 8;
[[maybe_unused]] constexpr bool __s16_to_f64 = is_integral_v<_Tp> && is_signed_v<_Tp> && sizeof(_Tp) == 2 && is_floating_point_v<_U> && sizeof(_U) == 8;
[[maybe_unused]] constexpr bool __s8_to_f64 = is_integral_v<_Tp> && is_signed_v<_Tp> && sizeof(_Tp) == 1 && is_floating_point_v<_U> && sizeof(_U) == 8;
[[maybe_unused]] constexpr bool __u64_to_f64 = is_integral_v<_Tp> && is_unsigned_v<_Tp> && sizeof(_Tp) == 8 && is_floating_point_v<_U> && sizeof(_U) == 8;
[[maybe_unused]] constexpr bool __u32_to_f64 = is_integral_v<_Tp> && is_unsigned_v<_Tp> && sizeof(_Tp) == 4 && is_floating_point_v<_U> && sizeof(_U) == 8;
[[maybe_unused]] constexpr bool __u16_to_f64 = is_integral_v<_Tp> && is_unsigned_v<_Tp> && sizeof(_Tp) == 2 && is_floating_point_v<_U> && sizeof(_U) == 8;
[[maybe_unused]] constexpr bool __u8_to_f64 = is_integral_v<_Tp> && is_unsigned_v<_Tp> && sizeof(_Tp) == 1 && is_floating_point_v<_U> && sizeof(_U) == 8;
[[maybe_unused]] constexpr bool __f32_to_s64 = is_integral_v<_U> && is_signed_v<_U> && sizeof(_U) == 8 && is_floating_point_v<_Tp> && sizeof(_Tp) == 4;
[[maybe_unused]] constexpr bool __f32_to_s32 = is_integral_v<_U> && is_signed_v<_U> && sizeof(_U) == 4 && is_floating_point_v<_Tp> && sizeof(_Tp) == 4;
[[maybe_unused]] constexpr bool __f32_to_u64 = is_integral_v<_U> && is_unsigned_v<_U> && sizeof(_U) == 8 && is_floating_point_v<_Tp> && sizeof(_Tp) == 4;
[[maybe_unused]] constexpr bool __f32_to_u32 = is_integral_v<_U> && is_unsigned_v<_U> && sizeof(_U) == 4 && is_floating_point_v<_Tp> && sizeof(_Tp) == 4;
[[maybe_unused]] constexpr bool __f64_to_s64 = is_integral_v<_U> && is_signed_v<_U> && sizeof(_U) == 8 && is_floating_point_v<_Tp> && sizeof(_Tp) == 8;
[[maybe_unused]] constexpr bool __f64_to_s32 = is_integral_v<_U> && is_signed_v<_U> && sizeof(_U) == 4 && is_floating_point_v<_Tp> && sizeof(_Tp) == 8;
[[maybe_unused]] constexpr bool __f64_to_u64 = is_integral_v<_U> && is_unsigned_v<_U> && sizeof(_U) == 8 && is_floating_point_v<_Tp> && sizeof(_Tp) == 8;
[[maybe_unused]] constexpr bool __f64_to_u32 = is_integral_v<_U> && is_unsigned_v<_U> && sizeof(_U) == 4 && is_floating_point_v<_Tp> && sizeof(_Tp) == 8;
[[maybe_unused]] constexpr bool __f32_to_ibw = is_integral_v<_U> && sizeof(_U) <= 2 && is_floating_point_v<_Tp> && sizeof(_Tp) == 4;
[[maybe_unused]] constexpr bool __f64_to_ibw = is_integral_v<_U> && sizeof(_U) <= 2 && is_floating_point_v<_Tp> && sizeof(_Tp) == 8;
[[maybe_unused]] constexpr bool __f32_to_f64 = is_floating_point_v<_Tp> && sizeof(_Tp) == 4 && is_floating_point_v<_U> && sizeof(_U) == 8;
[[maybe_unused]] constexpr bool __f64_to_f32 = is_floating_point_v<_Tp> && sizeof(_Tp) == 8 && is_floating_point_v<_U> && sizeof(_U) == 4;
if constexpr (__i_to_i && __y_to_x && !__have_avx2) {
return __convert_x86<_To>(__lo128(__v0), __hi128(__v0), __lo128(__v1), __hi128(__v1));
} else if constexpr (__i_to_i) {
static_assert(__x_to_x || __have_avx2,
"integral conversions with ymm registers require AVX2");
static_assert(__have_avx512bw || ((sizeof(_Tp) >= 4 || sizeof(__v0) < 64) &&
(sizeof(_U) >= 4 || sizeof(_To) < 64)),
"8/16-bit integers in zmm registers require AVX512BW");
static_assert((sizeof(__v0) < 64 && sizeof(_To) < 64) || __have_avx512f,
"integral conversions with ymm registers require AVX2");
}
if constexpr ((sizeof(__v0) == 16 && __have_avx2) ||
(sizeof(__v0) == 16 && __have_avx && std::is_floating_point_v<_Tp>) ||
(sizeof(__v0) == 32 && __have_avx512f && (sizeof(_Tp) >= 4 || __have_avx512bw))) {
return __convert_x86<_To>(__concat(__v0, __v1));
} else {
static_assert(!(std::is_floating_point_v<_Tp> == std::is_floating_point_v<_U> &&
sizeof(_Tp) == sizeof(_U)));
if constexpr (2 * _N < _M && sizeof(_To) > 16) {
constexpr size_t Min = 16 / sizeof(_U);
return __zero_extend(
__convert_x86<__vector_type_t<_U, (Min > 2 * _N) ? Min : 2 * _N>>(__v0, __v1));
} else if constexpr (__i64_to_i32) {
if constexpr (__x_to_x) {
return __auto_bitcast(_mm_shuffle_ps(__auto_bitcast(__v0), __auto_bitcast(__v1), 0x88));
} else if constexpr (__y_to_y) {
return __auto_bitcast(__xzyw(
_mm256_shuffle_ps(__auto_bitcast(__v0), __auto_bitcast(__v1), 0x88)));
} else if constexpr (__z_to_z) {
return __intrin_bitcast<_To>(
__concat(_mm512_cvtepi64_epi32(__i0), _mm512_cvtepi64_epi32(__i1)));
}
} else if constexpr (__i64_to_i16) {
if constexpr (__x_to_x) {
if constexpr (__have_sse4_1) {
return __intrin_bitcast<_To>(_mm_shuffle_epi8(
_mm_blend_epi16(__i0, _mm_slli_si128(__i1, 4), 0x44),
_mm_setr_epi8(0, 1, 8, 9, 4, 5, 12, 13, -0x80, -0x80, -0x80,
-0x80, -0x80, -0x80, -0x80, -0x80)));
} else {
return __vector_type_t<_U, _M>{_U(__v0[0]), _U(__v0[1]), _U(__v1[0]), _U(__v1[1])};
}
} else if constexpr (__y_to_x) {
auto __a = _mm256_unpacklo_epi16(__i0, __i1);
auto __b = _mm256_unpackhi_epi16(__i0, __i1);
auto __c = _mm256_unpacklo_epi16(__a, __b);
return __intrin_bitcast<_To>(
_mm_unpacklo_epi32(__lo128(__c), __hi128(__c)));
} else if constexpr (__z_to_y) {
return __intrin_bitcast<_To>(
__concat(_mm512_cvtepi64_epi16(__i0), _mm512_cvtepi64_epi16(__i1)));
}
} else if constexpr (__i64_to_i8) {
if constexpr (__x_to_x && __have_sse4_1) {
return __intrin_bitcast<_To>(_mm_shuffle_epi8(
_mm_blend_epi16(__i0, _mm_slli_si128(__i1, 4), 0x44),
_mm_setr_epi8(0, 8, 4, 12, -0x80, -0x80, -0x80, -0x80, -0x80, -0x80,
-0x80, -0x80, -0x80, -0x80, -0x80, -0x80)));
} else if constexpr (__x_to_x && __have_ssse3) {
return __intrin_bitcast<_To>(_mm_unpacklo_epi16(
_mm_shuffle_epi8(
__i0, _mm_setr_epi8(0, 8, -0x80, -0x80, -0x80, -0x80, -0x80, -0x80,
-0x80, -0x80, -0x80, -0x80, -0x80, -0x80, -0x80,
-0x80)),
_mm_shuffle_epi8(
__i1, _mm_setr_epi8(0, 8, -0x80, -0x80, -0x80, -0x80, -0x80, -0x80,
-0x80, -0x80, -0x80, -0x80, -0x80, -0x80, -0x80,
-0x80))));
} else if constexpr (__x_to_x) {
return __vector_type_t<_U, _M>{_U(__v0[0]), _U(__v0[1]), _U(__v1[0]), _U(__v1[1])};
} else if constexpr (__y_to_x) {
const auto __a = _mm256_shuffle_epi8(
_mm256_blend_epi32(__i0, _mm256_slli_epi64(__i1, 32), 0xAA),
_mm256_setr_epi8(0, 8, -0x80, -0x80, 4, 12, -0x80, -0x80, -0x80,
-0x80, -0x80, -0x80, -0x80, -0x80, -0x80, -0x80,
-0x80, -0x80, 0, 8, -0x80, -0x80, 4, 12, -0x80,
-0x80, -0x80, -0x80, -0x80, -0x80, -0x80, -0x80));
return __intrin_bitcast<_To>(__lo128(__a) | __hi128(__a));
}
} else if constexpr (__i32_to_i16) {
if constexpr (__x_to_x) {
if constexpr (__have_sse4_1) {
return __intrin_bitcast<_To>(
_mm_shuffle_epi8(_mm_blend_epi16(__i0, _mm_slli_si128(__i1, 2), 0xaa),
_mm_setr_epi8(0, 1, 4, 5, 8, 9, 12, 13, 2, 3, 6,
7, 10, 11, 14, 15)));
} else if constexpr (__have_ssse3) {
return __intrin_bitcast<_To>(
_mm_hadd_epi16(__to_intrin(__v0 << 16), __to_intrin(__v1 << 16)));
} else {
auto __a = _mm_unpacklo_epi16(__i0, __i1);
auto __b = _mm_unpackhi_epi16(__i0, __i1);
auto __c = _mm_unpacklo_epi16(__a, __b);
auto __d = _mm_unpackhi_epi16(__a, __b);
return __intrin_bitcast<_To>(_mm_unpacklo_epi16(__c, __d));
}
} else if constexpr (__y_to_y) {
const auto __shuf = _mm256_setr_epi8(
0, 1, 4, 5, 8, 9, 12, 13, -0x80, -0x80, -0x80, -0x80, -0x80, -0x80,
-0x80, -0x80, 0, 1, 4, 5, 8, 9, 12, 13, -0x80, -0x80, -0x80, -0x80,
-0x80, -0x80, -0x80, -0x80);
auto __a = _mm256_shuffle_epi8(__i0, __shuf);
auto __b = _mm256_shuffle_epi8(__i1, __shuf);
return __intrin_bitcast<_To>(__xzyw(_mm256_unpacklo_epi64(__a, __b)));
}
} else if constexpr (__i32_to_i8) {
if constexpr (__x_to_x && __have_ssse3) {
const auto shufmask =
_mm_setr_epi8(0, 4, 8, 12, -0x80, -0x80, -0x80, -0x80, -0x80, -0x80,
-0x80, -0x80, -0x80, -0x80, -0x80, -0x80);
return __intrin_bitcast<_To>(_mm_unpacklo_epi32(
_mm_shuffle_epi8(__i0, shufmask), _mm_shuffle_epi8(__i1, shufmask)));
} else if constexpr (__x_to_x) {
auto __a = _mm_unpacklo_epi8(__i0, __i1);
auto __b = _mm_unpackhi_epi8(__i0, __i1);
auto __c = _mm_unpacklo_epi8(__a, __b);
auto __d = _mm_unpackhi_epi8(__a, __b);
auto __e = _mm_unpacklo_epi8(__c, __d);
return __intrin_bitcast<_To>(__e & __m128i{-1, 0});
} else if constexpr (__y_to_x) {
const auto __a = _mm256_shuffle_epi8(
_mm256_blend_epi16(__i0, _mm256_slli_epi32(__i1, 16), 0xAA),
_mm256_setr_epi8(0, 4, 8, 12, -0x80, -0x80, -0x80, -0x80, 2, 6, 10,
14, -0x80, -0x80, -0x80, -0x80, -0x80, -0x80, -0x80,
-0x80, 0, 4, 8, 12, -0x80, -0x80, -0x80, -0x80, 2, 6,
10, 14));
return __intrin_bitcast<_To>(__lo128(__a) | __hi128(__a));
}
} else if constexpr (__i16_to_i8) {
if constexpr (__x_to_x && __have_ssse3) {
const auto __shuf = reinterpret_cast<__m128i>(
__vector_type_t<_UChar, 16>{0, 2, 4, 6, 8, 10, 12, 14, 0x80, 0x80, 0x80,
0x80, 0x80, 0x80, 0x80, 0x80});
return __intrin_bitcast<_To>(_mm_unpacklo_epi64(_mm_shuffle_epi8(__i0, __shuf),
_mm_shuffle_epi8(__i1, __shuf)));
} else if constexpr (__x_to_x) {
auto __a = _mm_unpacklo_epi8(__i0, __i1);
auto __b = _mm_unpackhi_epi8(__i0, __i1);
auto __c = _mm_unpacklo_epi8(__a, __b);
auto __d = _mm_unpackhi_epi8(__a, __b);
auto __e = _mm_unpacklo_epi8(__c, __d);
auto __f = _mm_unpackhi_epi8(__c, __d);
return __intrin_bitcast<_To>(_mm_unpacklo_epi8(__e, __f));
} else if constexpr (__y_to_y) {
return __intrin_bitcast<_To>(__xzyw(_mm256_shuffle_epi8(
(__to_intrin(__v0) & _mm256_set1_epi32(0x00ff00ff)) |
_mm256_slli_epi16(__i1, 8),
_mm256_setr_epi8(0, 2, 4, 6, 8, 10, 12, 14, 1, 3, 5, 7, 9, 11, 13, 15,
0, 2, 4, 6, 8, 10, 12, 14, 1, 3, 5, 7, 9, 11, 13,
15))));
}
} else if constexpr (__i64_to_f32) {
if constexpr (__x_to_x) {
return __make_wrapper<float>(__v0[0], __v0[1], __v1[0], __v1[1]);
} else if constexpr (__y_to_y) {
static_assert(__y_to_y && __have_avx2);
const auto __a = _mm256_unpacklo_epi32(__i0, __i1);
const auto __b = _mm256_unpackhi_epi32(__i0, __i1);
const auto __lo32 = _mm256_unpacklo_epi32(__a, __b);
const auto __hi32 =
__vector_bitcast<conditional_t<is_signed_v<_Tp>, int, _UInt>>(
_mm256_unpackhi_epi32(__a, __b));
const auto __hi = 0x100000000LL * __convert_x86<__vector_type_t<float, 8>>(__hi32);
const auto __mid =
0x10000 * _mm256_cvtepi32_ps(_mm256_srli_epi32(__lo32, 16));
const auto __lo = _mm256_cvtepi32_ps(_mm256_set1_epi32(0x0000ffffu) & __lo32);
return __xzyw((__hi + __mid) + __lo);
} else if constexpr (__z_to_z && __have_avx512dq) {
return std::is_signed_v<_Tp> ? __concat(_mm512_cvtepi64_ps(__i0),
_mm512_cvtepi64_ps(__i1))
: __concat(_mm512_cvtepu64_ps(__i0),
_mm512_cvtepu64_ps(__i1));
} else if constexpr (__z_to_z && std::is_signed_v<_Tp>) {
const __m512 __hi32 = _mm512_cvtepi32_ps(
__concat(_mm512_cvtepi64_epi32(__to_intrin(__v0 >> 32)),
_mm512_cvtepi64_epi32(__to_intrin(__v1 >> 32))));
const __m512i __lo32 =
__concat(_mm512_cvtepi64_epi32(__i0), _mm512_cvtepi64_epi32(__i1));
const __m512 __hi16 =
_mm512_cvtepu32_ps(_mm512_set1_epi32(0xffff0000u) & __lo32);
const __m512 __lo16 =
_mm512_cvtepi32_ps(_mm512_set1_epi32(0x0000ffffu) & __lo32);
return (__hi32 * 0x100000000LL + __hi16) + __lo16;
} else if constexpr (__z_to_z && std::is_unsigned_v<_Tp>) {
return __intrin_bitcast<_To>(
_mm512_cvtepu32_ps(
__concat(_mm512_cvtepi64_epi32(_mm512_srai_epi64(__i0, 32)),
_mm512_cvtepi64_epi32(_mm512_srai_epi64(__i1, 32)))) *
0x100000000LL +
_mm512_cvtepu32_ps(
__concat(_mm512_cvtepi64_epi32(__i0), _mm512_cvtepi64_epi32(__i1))));
}
} else if constexpr (__f64_to_s32) {
} else if constexpr (__f64_to_u32) {
if constexpr (__x_to_x && __have_sse4_1) {
return __vector_bitcast<_U>(_mm_unpacklo_epi64(
_mm_cvttpd_epi32(_mm_floor_pd(__i0) - 0x8000'0000u),
_mm_cvttpd_epi32(_mm_floor_pd(__i1) - 0x8000'0000u))) ^
0x8000'0000u;
} else if constexpr (__y_to_y) {
return __vector_bitcast<_U>(__concat(
_mm256_cvttpd_epi32(_mm256_floor_pd(__i0) - 0x8000'0000u),
_mm256_cvttpd_epi32(_mm256_floor_pd(__i1) - 0x8000'0000u))) ^
0x8000'0000u;
}
} else if constexpr (__f64_to_ibw) {
return __convert_x86<_To>(__convert_x86<__vector_type_t<int, _N * 2>>(__v0, __v1));
} else if constexpr (__f32_to_ibw) {
return __convert_x86<_To>(__convert_x86<__vector_type_t<int, _N>>(__v0),
__convert_x86<__vector_type_t<int, _N>>(__v1));
}
if constexpr (sizeof(_To) >= 32) {
return __concat(__convert_x86<__vector_type_t<_U, _M / 2>>(__v0),
__convert_x86<__vector_type_t<_U, _M / 2>>(__v1));
} else if constexpr (sizeof(_To) == 16) {
const auto __lo = __to_intrin(__convert_x86<_To>(__v0));
const auto __hi = __to_intrin(__convert_x86<_To>(__v1));
if constexpr (sizeof(_U) * _N == 8) {
if constexpr (is_floating_point_v<_U>) {
return __auto_bitcast(_mm_unpacklo_pd(__vector_bitcast<double>(__lo),
__vector_bitcast<double>(__hi)));
} else {
return __intrin_bitcast<_To>(_mm_unpacklo_epi64(__lo, __hi));
}
} else if constexpr (sizeof(_U) * _N == 4) {
if constexpr (is_floating_point_v<_U>) {
return __auto_bitcast(_mm_unpacklo_ps(__vector_bitcast<float>(__lo),
__vector_bitcast<float>(__hi)));
} else {
return __intrin_bitcast<_To>(_mm_unpacklo_epi32(__lo, __hi));
}
} else if constexpr (sizeof(_U) * _N == 2) {
return __intrin_bitcast<_To>(_mm_unpacklo_epi16(__lo, __hi));
} else {
__assert_unreachable<_Tp>();
}
} else {
return __vector_convert<_To>(__v0, __v1, make_index_sequence<_N>());
}
}
}
template <class _To, class _V, class _Traits> _GLIBCXX_SIMD_INTRINSIC _To __convert_x86(_V __v0, _V __v1,_V __v2,_V __v3)
{
static_assert(__is_vector_type_v<_V>);
using _Tp = typename _Traits::value_type;
constexpr size_t _N = _Traits::_S_width;
[[maybe_unused]] const auto __i0 = __to_intrin(__v0);
[[maybe_unused]] const auto __i1 = __to_intrin(__v1);
[[maybe_unused]] const auto __i2 = __to_intrin(__v2);
[[maybe_unused]] const auto __i3 = __to_intrin(__v3);
using _U = typename _VectorTraits<_To>::value_type;
constexpr size_t _M = _VectorTraits<_To>::_S_width;
static_assert(
4 * _N <= _M,
"__v2/__v3 would be discarded; use the two/one-argument __convert_x86 overload instead");
[[maybe_unused]] constexpr bool __x_to_x = sizeof(__v0) == 16 && sizeof(_To) == 16;
[[maybe_unused]] constexpr bool __x_to_y = sizeof(__v0) == 16 && sizeof(_To) == 32;
[[maybe_unused]] constexpr bool __x_to_z = sizeof(__v0) == 16 && sizeof(_To) == 64;
[[maybe_unused]] constexpr bool __y_to_x = sizeof(__v0) == 32 && sizeof(_To) == 16;
[[maybe_unused]] constexpr bool __y_to_y = sizeof(__v0) == 32 && sizeof(_To) == 32;
[[maybe_unused]] constexpr bool __y_to_z = sizeof(__v0) == 32 && sizeof(_To) == 64;
[[maybe_unused]] constexpr bool __z_to_x = sizeof(__v0) == 64 && sizeof(_To) == 16;
[[maybe_unused]] constexpr bool __z_to_y = sizeof(__v0) == 64 && sizeof(_To) == 32;
[[maybe_unused]] constexpr bool __z_to_z = sizeof(__v0) == 64 && sizeof(_To) == 64;
[[maybe_unused]] constexpr bool __i_to_i = std::is_integral_v<_U> && std::is_integral_v<_Tp>;
[[maybe_unused]] constexpr bool __i8_to_i16 = __i_to_i && sizeof(_Tp) == 1 && sizeof(_U) == 2;
[[maybe_unused]] constexpr bool __i8_to_i32 = __i_to_i && sizeof(_Tp) == 1 && sizeof(_U) == 4;
[[maybe_unused]] constexpr bool __i8_to_i64 = __i_to_i && sizeof(_Tp) == 1 && sizeof(_U) == 8;
[[maybe_unused]] constexpr bool __i16_to_i8 = __i_to_i && sizeof(_Tp) == 2 && sizeof(_U) == 1;
[[maybe_unused]] constexpr bool __i16_to_i32 = __i_to_i && sizeof(_Tp) == 2 && sizeof(_U) == 4;
[[maybe_unused]] constexpr bool __i16_to_i64 = __i_to_i && sizeof(_Tp) == 2 && sizeof(_U) == 8;
[[maybe_unused]] constexpr bool __i32_to_i8 = __i_to_i && sizeof(_Tp) == 4 && sizeof(_U) == 1;
[[maybe_unused]] constexpr bool __i32_to_i16 = __i_to_i && sizeof(_Tp) == 4 && sizeof(_U) == 2;
[[maybe_unused]] constexpr bool __i32_to_i64 = __i_to_i && sizeof(_Tp) == 4 && sizeof(_U) == 8;
[[maybe_unused]] constexpr bool __i64_to_i8 = __i_to_i && sizeof(_Tp) == 8 && sizeof(_U) == 1;
[[maybe_unused]] constexpr bool __i64_to_i16 = __i_to_i && sizeof(_Tp) == 8 && sizeof(_U) == 2;
[[maybe_unused]] constexpr bool __i64_to_i32 = __i_to_i && sizeof(_Tp) == 8 && sizeof(_U) == 4;
[[maybe_unused]] constexpr bool __i64_to_f32 = is_integral_v<_Tp> && sizeof(_Tp) == 8 && is_floating_point_v<_U> && sizeof(_U) == 4;
[[maybe_unused]] constexpr bool __s32_to_f32 = is_integral_v<_Tp> && is_signed_v<_Tp> && sizeof(_Tp) == 4 && is_floating_point_v<_U> && sizeof(_U) == 4;
[[maybe_unused]] constexpr bool __s16_to_f32 = is_integral_v<_Tp> && is_signed_v<_Tp> && sizeof(_Tp) == 2 && is_floating_point_v<_U> && sizeof(_U) == 4;
[[maybe_unused]] constexpr bool __s8_to_f32 = is_integral_v<_Tp> && is_signed_v<_Tp> && sizeof(_Tp) == 1 && is_floating_point_v<_U> && sizeof(_U) == 4;
[[maybe_unused]] constexpr bool __u32_to_f32 = is_integral_v<_Tp> && is_unsigned_v<_Tp> && sizeof(_Tp) == 4 && is_floating_point_v<_U> && sizeof(_U) == 4;
[[maybe_unused]] constexpr bool __u16_to_f32 = is_integral_v<_Tp> && is_unsigned_v<_Tp> && sizeof(_Tp) == 2 && is_floating_point_v<_U> && sizeof(_U) == 4;
[[maybe_unused]] constexpr bool __u8_to_f32 = is_integral_v<_Tp> && is_unsigned_v<_Tp> && sizeof(_Tp) == 1 && is_floating_point_v<_U> && sizeof(_U) == 4;
[[maybe_unused]] constexpr bool __s64_to_f64 = is_integral_v<_Tp> && is_signed_v<_Tp> && sizeof(_Tp) == 8 && is_floating_point_v<_U> && sizeof(_U) == 8;
[[maybe_unused]] constexpr bool __s32_to_f64 = is_integral_v<_Tp> && is_signed_v<_Tp> && sizeof(_Tp) == 4 && is_floating_point_v<_U> && sizeof(_U) == 8;
[[maybe_unused]] constexpr bool __s16_to_f64 = is_integral_v<_Tp> && is_signed_v<_Tp> && sizeof(_Tp) == 2 && is_floating_point_v<_U> && sizeof(_U) == 8;
[[maybe_unused]] constexpr bool __s8_to_f64 = is_integral_v<_Tp> && is_signed_v<_Tp> && sizeof(_Tp) == 1 && is_floating_point_v<_U> && sizeof(_U) == 8;
[[maybe_unused]] constexpr bool __u64_to_f64 = is_integral_v<_Tp> && is_unsigned_v<_Tp> && sizeof(_Tp) == 8 && is_floating_point_v<_U> && sizeof(_U) == 8;
[[maybe_unused]] constexpr bool __u32_to_f64 = is_integral_v<_Tp> && is_unsigned_v<_Tp> && sizeof(_Tp) == 4 && is_floating_point_v<_U> && sizeof(_U) == 8;
[[maybe_unused]] constexpr bool __u16_to_f64 = is_integral_v<_Tp> && is_unsigned_v<_Tp> && sizeof(_Tp) == 2 && is_floating_point_v<_U> && sizeof(_U) == 8;
[[maybe_unused]] constexpr bool __u8_to_f64 = is_integral_v<_Tp> && is_unsigned_v<_Tp> && sizeof(_Tp) == 1 && is_floating_point_v<_U> && sizeof(_U) == 8;
[[maybe_unused]] constexpr bool __f32_to_s64 = is_integral_v<_U> && is_signed_v<_U> && sizeof(_U) == 8 && is_floating_point_v<_Tp> && sizeof(_Tp) == 4;
[[maybe_unused]] constexpr bool __f32_to_s32 = is_integral_v<_U> && is_signed_v<_U> && sizeof(_U) == 4 && is_floating_point_v<_Tp> && sizeof(_Tp) == 4;
[[maybe_unused]] constexpr bool __f32_to_u64 = is_integral_v<_U> && is_unsigned_v<_U> && sizeof(_U) == 8 && is_floating_point_v<_Tp> && sizeof(_Tp) == 4;
[[maybe_unused]] constexpr bool __f32_to_u32 = is_integral_v<_U> && is_unsigned_v<_U> && sizeof(_U) == 4 && is_floating_point_v<_Tp> && sizeof(_Tp) == 4;
[[maybe_unused]] constexpr bool __f64_to_s64 = is_integral_v<_U> && is_signed_v<_U> && sizeof(_U) == 8 && is_floating_point_v<_Tp> && sizeof(_Tp) == 8;
[[maybe_unused]] constexpr bool __f64_to_s32 = is_integral_v<_U> && is_signed_v<_U> && sizeof(_U) == 4 && is_floating_point_v<_Tp> && sizeof(_Tp) == 8;
[[maybe_unused]] constexpr bool __f64_to_u64 = is_integral_v<_U> && is_unsigned_v<_U> && sizeof(_U) == 8 && is_floating_point_v<_Tp> && sizeof(_Tp) == 8;
[[maybe_unused]] constexpr bool __f64_to_u32 = is_integral_v<_U> && is_unsigned_v<_U> && sizeof(_U) == 4 && is_floating_point_v<_Tp> && sizeof(_Tp) == 8;
[[maybe_unused]] constexpr bool __f32_to_ibw = is_integral_v<_U> && sizeof(_U) <= 2 && is_floating_point_v<_Tp> && sizeof(_Tp) == 4;
[[maybe_unused]] constexpr bool __f64_to_ibw = is_integral_v<_U> && sizeof(_U) <= 2 && is_floating_point_v<_Tp> && sizeof(_Tp) == 8;
[[maybe_unused]] constexpr bool __f32_to_f64 = is_floating_point_v<_Tp> && sizeof(_Tp) == 4 && is_floating_point_v<_U> && sizeof(_U) == 8;
[[maybe_unused]] constexpr bool __f64_to_f32 = is_floating_point_v<_Tp> && sizeof(_Tp) == 8 && is_floating_point_v<_U> && sizeof(_U) == 4;
if constexpr (__i_to_i && __y_to_x && !__have_avx2) {
return __convert_x86<_To>(__lo128(__v0), __hi128(__v0), __lo128(__v1), __hi128(__v1),
__lo128(__v2), __hi128(__v2), __lo128(__v3), __hi128(__v3));
} else if constexpr (__i_to_i) {
static_assert(__x_to_x || __have_avx2,
"integral conversions with ymm registers require AVX2");
static_assert(__have_avx512bw || ((sizeof(_Tp) >= 4 || sizeof(__v0) < 64) &&
(sizeof(_U) >= 4 || sizeof(_To) < 64)),
"8/16-bit integers in zmm registers require AVX512BW");
static_assert((sizeof(__v0) < 64 && sizeof(_To) < 64) || __have_avx512f,
"integral conversions with ymm registers require AVX2");
}
if constexpr ((sizeof(__v0) == 16 && __have_avx2) ||
(sizeof(__v0) == 16 && __have_avx && std::is_floating_point_v<_Tp>) ||
(sizeof(__v0) == 32 && __have_avx512f)) {
return __convert_x86<_To>(__concat(__v0, __v1), __concat(__v2, __v3));
} else {
static_assert(!(std::is_floating_point_v<_Tp> == std::is_floating_point_v<_U> &&
sizeof(_Tp) == sizeof(_U)));
if constexpr (4 * _N < _M && sizeof(_To) > 16) {
constexpr size_t Min = 16 / sizeof(_U);
return __zero_extend(
__convert_x86<__vector_type_t<_U, (Min > 4 * _N) ? Min : 4 * _N>>(__v0, __v1,
__v2, __v3));
} else if constexpr (__i64_to_i16) {
if constexpr (__x_to_x && __have_sse4_1) {
return __intrin_bitcast<_To>(_mm_shuffle_epi8(
_mm_blend_epi16(_mm_blend_epi16(__i0, _mm_slli_si128(__i1, 2), 0x22),
_mm_blend_epi16(_mm_slli_si128(__i2, 4),
_mm_slli_si128(__i3, 6), 0x88),
0xcc),
_mm_setr_epi8(0, 1, 8, 9, 2, 3, 10, 11, 4, 5, 12, 13, 6, 7, 14, 15)));
} else if constexpr (__y_to_y && __have_avx2) {
return __intrin_bitcast<_To>(_mm256_shuffle_epi8(
__xzyw(_mm256_blend_epi16(
__auto_bitcast(_mm256_shuffle_ps(__vector_bitcast<float>(__v0),
__vector_bitcast<float>(__v2),
0x88)),
__to_intrin(
__vector_bitcast<int>(_mm256_shuffle_ps(
__vector_bitcast<float>(__v1), __vector_bitcast<float>(__v3), 0x88))
<< 16),
0xaa)
),
_mm256_setr_epi8(0, 1, 4, 5, 8, 9, 12, 13, 2, 3, 6, 7, 10, 11, 14, 15,
0, 1, 4, 5, 8, 9, 12, 13, 2, 3, 6, 7, 10, 11, 14,
15)));
}
} else if constexpr (__i64_to_i8) {
if constexpr (__x_to_x) {
} else if constexpr (__y_to_x) {
auto __a =
_mm256_srli_epi32(_mm256_slli_epi32(__i0, 24), 24) |
_mm256_srli_epi32(_mm256_slli_epi32(__i1, 24), 16) |
_mm256_srli_epi32(_mm256_slli_epi32(__i2, 24), 8) |
_mm256_slli_epi32(__i3, 24);
auto __b = _mm256_unpackhi_epi64(__a, __a);
auto __c = _mm256_unpacklo_epi8(__a, __b);
return __intrin_bitcast<_To>(_mm_unpacklo_epi16(__lo128(__c), __hi128(__c)));
}
} else if constexpr (__i32_to_i8) {
if constexpr (__x_to_x) {
if constexpr (__have_ssse3) {
const auto __x0 = __vector_bitcast<_UInt>(__v0) & 0xff;
const auto __x1 = (__vector_bitcast<_UInt>(__v1) & 0xff) << 8;
const auto __x2 = (__vector_bitcast<_UInt>(__v2) & 0xff) << 16;
const auto __x3 = __vector_bitcast<_UInt>(__v3) << 24;
return __intrin_bitcast<_To>(
_mm_shuffle_epi8(__to_intrin(__x0 | __x1 | __x2 | __x3),
_mm_setr_epi8(0, 4, 8, 12, 1, 5, 9, 13, 2, 6, 10,
14, 3, 7, 11, 15)));
} else {
auto __a = _mm_unpacklo_epi8(__i0, __i2);
auto __b = _mm_unpackhi_epi8(__i0, __i2);
auto __c = _mm_unpacklo_epi8(__i1, __i3);
auto __d = _mm_unpackhi_epi8(__i1, __i3);
auto __e = _mm_unpacklo_epi8(__a, __c);
auto __f = _mm_unpackhi_epi8(__a, __c);
auto __g = _mm_unpacklo_epi8(__b, __d);
auto __h = _mm_unpackhi_epi8(__b, __d);
return __intrin_bitcast<_To>(_mm_unpacklo_epi8(
_mm_unpacklo_epi8(__e, __g),
_mm_unpacklo_epi8(__f, __h)
));
}
} else if constexpr (__y_to_y) {
const auto __a = _mm256_shuffle_epi8(
__to_intrin((__vector_bitcast<ushort>(_mm256_blend_epi16(
__i0, _mm256_slli_epi32(__i1, 16), 0xAA)) &
0xff) |
(__vector_bitcast<ushort>(_mm256_blend_epi16(
__i2, _mm256_slli_epi32(__i3, 16), 0xAA))
<< 8)),
_mm256_setr_epi8(0, 4, 8, 12, 2, 6, 10, 14, 1, 5, 9, 13, 3, 7, 11, 15,
0, 4, 8, 12, 2, 6, 10, 14, 1, 5, 9, 13, 3, 7, 11, 15));
return __intrin_bitcast<_To>(_mm256_permutevar8x32_epi32(
__a, _mm256_setr_epi32(0, 4, 1, 5, 2, 6, 3, 7)));
}
} else if constexpr (__i64_to_f32) {
if constexpr (__x_to_y) {
return __make_wrapper<float>(__v0[0], __v0[1], __v1[0], __v1[1], __v2[0], __v2[1], __v3[0], __v3[1]);
const auto __a = _mm_unpacklo_epi32(__i0, __i1);
const auto __b = _mm_unpackhi_epi32(__i0, __i1);
const auto __c = _mm_unpacklo_epi32(__i2, __i3);
const auto __d = _mm_unpackhi_epi32(__i2, __i3);
const auto __lo32a = _mm_unpacklo_epi32(__a, __b);
const auto __lo32b = _mm_unpacklo_epi32(__c, __d);
const auto __hi32 =
__vector_bitcast<conditional_t<is_signed_v<_Tp>, int, _UInt>>(
__concat(_mm_unpackhi_epi32(__a, __b),
_mm_unpackhi_epi32(__c, __d)));
const auto __hi =
0x100000000LL * __convert_x86<__vector_type_t<float, 8>>(__hi32);
const auto __mid =
0x10000 * _mm256_cvtepi32_ps(__concat(_mm_srli_epi32(__lo32a, 16),
_mm_srli_epi32(__lo32b, 16)));
const auto __lo =
_mm256_cvtepi32_ps(__concat(_mm_set1_epi32(0x0000ffffu) & __lo32a,
_mm_set1_epi32(0x0000ffffu) & __lo32b));
return (__hi + __mid) + __lo;
}
} else if constexpr (__f64_to_ibw) {
return __convert_x86<_To>(__convert_x86<__vector_type_t<int, _N * 2>>(__v0, __v1),
__convert_x86<__vector_type_t<int, _N * 2>>(__v2, __v3));
} else if constexpr (__f32_to_ibw) {
return __convert_x86<_To>(__convert_x86<__vector_type_t<int, _N>>(__v0),
__convert_x86<__vector_type_t<int, _N>>(__v1),
__convert_x86<__vector_type_t<int, _N>>(__v2),
__convert_x86<__vector_type_t<int, _N>>(__v3));
}
if constexpr (sizeof(_To) >= 32) {
return __concat(__convert_x86<__vector_type_t<_U, _M / 2>>(__v0, __v1),
__convert_x86<__vector_type_t<_U, _M / 2>>(__v2, __v3));
} else if constexpr (sizeof(_To) == 16) {
const auto __lo = __to_intrin(__convert_x86<_To>(__v0, __v1));
const auto __hi = __to_intrin(__convert_x86<_To>(__v2, __v3));
if constexpr (sizeof(_U) * _N * 2 == 8) {
if constexpr (is_floating_point_v<_U>) {
return __auto_bitcast(_mm_unpacklo_pd(__lo, __hi));
} else {
return __intrin_bitcast<_To>(_mm_unpacklo_epi64(__lo, __hi));
}
} else if constexpr (sizeof(_U) * _N * 2 == 4) {
if constexpr (is_floating_point_v<_U>) {
return __auto_bitcast(_mm_unpacklo_ps(__lo, __hi));
} else {
return __intrin_bitcast<_To>(_mm_unpacklo_epi32(__lo, __hi));
}
} else {
__assert_unreachable<_Tp>();
}
} else {
return __vector_convert<_To>(__v0, __v1, __v2, __v3,
make_index_sequence<_N>());
}
}
}
template <class _To, class _V, class _Traits> _GLIBCXX_SIMD_INTRINSIC _To __convert_x86(_V __v0, _V __v1,_V __v2,_V __v3,_V __v4,_V __v5, _V __v6, _V __v7)
{
static_assert(__is_vector_type_v<_V>);
using _Tp = typename _Traits::value_type;
constexpr size_t _N = _Traits::_S_width;
[[maybe_unused]] const auto __i0 = __to_intrin(__v0);
[[maybe_unused]] const auto __i1 = __to_intrin(__v1);
[[maybe_unused]] const auto __i2 = __to_intrin(__v2);
[[maybe_unused]] const auto __i3 = __to_intrin(__v3);
[[maybe_unused]] const auto __i4 = __to_intrin(__v4);
[[maybe_unused]] const auto __i5 = __to_intrin(__v5);
[[maybe_unused]] const auto __i6 = __to_intrin(__v6);
[[maybe_unused]] const auto __i7 = __to_intrin(__v7);
using _U = typename _VectorTraits<_To>::value_type;
constexpr size_t _M = _VectorTraits<_To>::_S_width;
static_assert(8 * _N <= _M, "__v4-__v7 would be discarded; use the four/two/one-argument "
"__convert_x86 overload instead");
[[maybe_unused]] constexpr bool __x_to_x = sizeof(__v0) == 16 && sizeof(_To) == 16;
[[maybe_unused]] constexpr bool __x_to_y = sizeof(__v0) == 16 && sizeof(_To) == 32;
[[maybe_unused]] constexpr bool __x_to_z = sizeof(__v0) == 16 && sizeof(_To) == 64;
[[maybe_unused]] constexpr bool __y_to_x = sizeof(__v0) == 32 && sizeof(_To) == 16;
[[maybe_unused]] constexpr bool __y_to_y = sizeof(__v0) == 32 && sizeof(_To) == 32;
[[maybe_unused]] constexpr bool __y_to_z = sizeof(__v0) == 32 && sizeof(_To) == 64;
[[maybe_unused]] constexpr bool __z_to_x = sizeof(__v0) == 64 && sizeof(_To) == 16;
[[maybe_unused]] constexpr bool __z_to_y = sizeof(__v0) == 64 && sizeof(_To) == 32;
[[maybe_unused]] constexpr bool __z_to_z = sizeof(__v0) == 64 && sizeof(_To) == 64;
[[maybe_unused]] constexpr bool __i_to_i = std::is_integral_v<_U> && std::is_integral_v<_Tp>;
[[maybe_unused]] constexpr bool __i64_to_i8 = __i_to_i && sizeof(_Tp) == 8 && sizeof(_U) == 1;
[[maybe_unused]] constexpr bool __f64_to_i8 = is_integral_v<_U> && sizeof(_U) == 1 && is_floating_point_v<_Tp> && sizeof(_Tp) == 8;
if constexpr (__i_to_i) {
static_assert(__x_to_x || __have_avx2,
"integral conversions with ymm registers require AVX2");
static_assert(__have_avx512bw || ((sizeof(_Tp) >= 4 || sizeof(__v0) < 64) &&
(sizeof(_U) >= 4 || sizeof(_To) < 64)),
"8/16-bit integers in zmm registers require AVX512BW");
static_assert((sizeof(__v0) < 64 && sizeof(_To) < 64) || __have_avx512f,
"integral conversions with ymm registers require AVX2");
}
if constexpr ((sizeof(__v0) == 16 && __have_avx2) ||
(sizeof(__v0) == 16 && __have_avx && std::is_floating_point_v<_Tp>) ||
(sizeof(__v0) == 32 && __have_avx512f)) {
return __convert_x86<_To>(__concat(__v0, __v1), __concat(__v2, __v3), __concat(__v4, __v5),
__concat(__v6, __v7));
} else {
static_assert(!(std::is_floating_point_v<_Tp> == std::is_floating_point_v<_U> &&
sizeof(_Tp) == sizeof(_U)));
static_assert(!(8 * _N < _M && sizeof(_To) > 16),
"zero extension should be impossible");
if constexpr (__i64_to_i8) {
if constexpr (__x_to_x && __have_ssse3) {
return __intrin_bitcast<_To>(_mm_shuffle_epi8(
__to_intrin((((__v0 & 0xff) | ((__v1 & 0xff) << 8)) |
(((__v2 & 0xff) << 16) | ((__v3 & 0xff) << 24))) |
((((__v4 & 0xff) << 32) | ((__v5 & 0xff) << 40)) |
(((__v6 & 0xff) << 48) | (__v7 << 56)))),
_mm_setr_epi8(0, 8, 1, 9, 2, 10, 3, 11, 4, 12, 5, 13, 6, 14, 7, 15)));
} else if constexpr (__x_to_x) {
const auto __a = _mm_unpacklo_epi8(__i0, __i1);
const auto __b = _mm_unpackhi_epi8(__i0, __i1);
const auto __c = _mm_unpacklo_epi8(__i2, __i3);
const auto __d = _mm_unpackhi_epi8(__i2, __i3);
const auto __e = _mm_unpacklo_epi8(__i4, __i5);
const auto __f = _mm_unpackhi_epi8(__i4, __i5);
const auto __g = _mm_unpacklo_epi8(__i6, __i7);
const auto __h = _mm_unpackhi_epi8(__i6, __i7);
return __intrin_bitcast<_To>(_mm_unpacklo_epi64(
_mm_unpacklo_epi32(_mm_unpacklo_epi8(__a, __b),
_mm_unpacklo_epi8(__c, __d)),
_mm_unpacklo_epi32(_mm_unpacklo_epi8(__e, __f),
_mm_unpacklo_epi8(__g, __h))
));
} else if constexpr (__y_to_y) {
auto __a =
__to_intrin((((__v0 & 0xff) | ((__v1 & 0xff) << 8)) |
(((__v2 & 0xff) << 16) | ((__v3 & 0xff) << 24))) |
((((__v4 & 0xff) << 32) | ((__v5 & 0xff) << 40)) |
(((__v6 & 0xff) << 48) | ((__v7 << 56)))));
auto __b = _mm256_shuffle_epi8(
__a, _mm256_setr_epi8(0, 8, 1, 9, 2, 10, 3, 11, 4, 12, 5, 13, 6, 14, 7, 15,
0, 8, 1, 9, 2, 10, 3, 11, 4, 12, 5, 13, 6, 14, 7, 15));
auto __c = __xzyw(__b);
return __intrin_bitcast<_To>(_mm256_shuffle_epi8(
__c, _mm256_setr_epi8(0, 1, 8, 9, 2, 3, 10, 11, 4, 5, 12, 13, 6, 7, 14,
15, 0, 1, 8, 9, 2, 3, 10, 11, 4, 5, 12, 13, 6, 7,
14, 15)));
} else if constexpr(__z_to_z) {
return __concat(
__convert_x86<__vector_type_t<_U, _M / 2>>(__v0, __v1, __v2, __v3),
__convert_x86<__vector_type_t<_U, _M / 2>>(__v4, __v5, __v6, __v7));
}
} else if constexpr (__f64_to_i8) {
return __convert_x86<_To>(__convert_x86<__vector_type_t<int, _N * 2>>(__v0, __v1),
__convert_x86<__vector_type_t<int, _N * 2>>(__v2, __v3),
__convert_x86<__vector_type_t<int, _N * 2>>(__v4, __v5),
__convert_x86<__vector_type_t<int, _N * 2>>(__v6, __v7));
} else {
__assert_unreachable<_Tp>();
}
if constexpr (sizeof(_To) >= 32) {
return __concat(__convert_x86<__vector_type_t<_U, _M / 2>>(__v0, __v1, __v2, __v3),
__convert_x86<__vector_type_t<_U, _M / 2>>(__v4, __v5, __v6, __v7));
} else if constexpr (sizeof(_To) == 16) {
const auto __lo = __to_intrin(__convert_x86<_To>(__v0, __v1, __v2, __v3));
const auto __hi = __to_intrin(__convert_x86<_To>(__v4, __v5, __v6, __v7));
static_assert(sizeof(_U) == 1 && _N == 2);
return __intrin_bitcast<_To>(_mm_unpacklo_epi64(__lo, __hi));
} else {
__assert_unreachable<_Tp>();
}
}
}
#endif
#endif
#endif
template <class _To, class _From, class... _More>
_GLIBCXX_SIMD_INTRINSIC auto __convert(_From __v0, _More... __vs)
{
static_assert((true && ... && is_same_v<_From, _More>));
if constexpr (__is_vectorizable_v<_From>)
{
using _V = typename _VectorTraits<_To>::type;
using _Tp = typename _VectorTraits<_To>::value_type;
return _V{static_cast<_Tp>(__v0), static_cast<_Tp>(__vs)...};
}
else if constexpr (!__is_vector_type_v<_From>)
return __convert<_To>(__v0._M_data, __vs._M_data...);
else if constexpr (__is_vectorizable_v<_To>)
return __convert<__vector_type_t<_To, (_VectorTraits<_From>::_S_width *
(1 + sizeof...(_More)))>>(__v0,
__vs...);
else if constexpr (!__is_vector_type_v<_To>)
return _To(__convert<typename _To::_BuiltinType>(__v0, __vs...));
else
{
static_assert(sizeof...(_More) == 0 ||
_VectorTraits<_To>::_S_width >=
(1 + sizeof...(_More)) * _VectorTraits<_From>::_S_width,
"__convert(...) requires the input to fit into the output");
return __vector_convert<_To>(__v0, __vs...);
}
}
template <typename _To,
size_t _NParts = 0,
typename _From,
typename _FromVT = _VectorTraits<_From>>
_GLIBCXX_SIMD_INTRINSIC auto __convert_all(_From __v)
{
static_assert(__is_vector_type_v<_To>);
using _ToVT = _VectorTraits<_To>;
if constexpr (!__is_vector_type_v<_From>)
return __convert_all<_To, _NParts>(__v._M_data);
else if constexpr(_NParts == 1)
{
constexpr size_t _NTotal = _FromVT::_S_width / _ToVT::_S_width;
return __vector_convert<_To>(__extract_part<0, _NTotal>(__v));
}
#if _GLIBCXX_SIMD_X86INTRIN
else if constexpr (!__have_sse4_1 &&
!(sizeof(typename _FromVT::value_type) == 4 &&
is_same_v<typename _ToVT::value_type, double>))
{
using _ToT = typename _ToVT::value_type;
using _FromT = typename _FromVT::value_type;
constexpr size_t _N =
_NParts == 0 ? (_FromVT::_S_width / _ToVT::_S_width) : _NParts;
using _R = std::array<_To, _N>;
if constexpr (sizeof(_FromT) == 1 && sizeof(_ToT) == 2)
{
static_assert(std::is_integral_v<_FromT>);
static_assert(std::is_integral_v<_ToT>);
if constexpr (is_unsigned_v<_FromT>)
{
return _R{reinterpret_cast<_To>(
_mm_unpacklo_epi8(__to_intrin(__v), __m128i())),
reinterpret_cast<_To>(
_mm_unpackhi_epi8(__to_intrin(__v), __m128i()))};
}
else
{
return _R{
reinterpret_cast<_To>(_mm_srai_epi16(
_mm_unpacklo_epi8(__to_intrin(__v), __to_intrin(__v)), 8)),
reinterpret_cast<_To>(_mm_srai_epi16(
_mm_unpackhi_epi8(__to_intrin(__v), __to_intrin(__v)), 8))};
}
}
else if constexpr (sizeof(_FromT) == 2 && sizeof(_ToT) == 4)
{
static_assert(std::is_integral_v<_FromT>);
if constexpr (is_floating_point_v<_ToT>)
{
const auto __ints =
__convert_all<__vector_type16_t<int>, _N>(__v);
return __generate_from_n_evaluations<_N, _R>(
[&](auto __i) { return __vector_convert<_To>(__ints[__i]); });
}
else if constexpr (is_unsigned_v<_FromT>)
return _R{__vector_bitcast<_ToT>(
_mm_unpacklo_epi16(__to_intrin(__v), __m128i())),
__vector_bitcast<_ToT>(
_mm_unpackhi_epi16(__to_intrin(__v), __m128i()))};
else
return _R{
__vector_bitcast<_ToT>(_mm_srai_epi32(
_mm_unpacklo_epi16(__to_intrin(__v), __to_intrin(__v)), 16)),
__vector_bitcast<_ToT>(_mm_srai_epi32(
_mm_unpackhi_epi16(__to_intrin(__v), __to_intrin(__v)), 16))};
}
else if constexpr (sizeof(_FromT) == 4 && sizeof(_ToT) == 8 &&
is_integral_v<_FromT> && is_integral_v<_ToT>)
{
if constexpr (is_unsigned_v<_FromT>)
return _R{__vector_bitcast<_ToT>(
_mm_unpacklo_epi32(__to_intrin(__v), __m128i())),
__vector_bitcast<_ToT>(
_mm_unpackhi_epi32(__to_intrin(__v), __m128i()))};
else
return _R{
__vector_bitcast<_ToT>(_mm_unpacklo_epi32(
__to_intrin(__v), _mm_srai_epi32(__to_intrin(__v), 31))),
__vector_bitcast<_ToT>(_mm_unpackhi_epi32(
__to_intrin(__v), _mm_srai_epi32(__to_intrin(__v), 31)))};
}
else if constexpr (sizeof(_FromT) == 4 && sizeof(_ToT) == 8 &&
is_integral_v<_FromT> && is_integral_v<_ToT>)
{
if constexpr (is_unsigned_v<_FromT>)
return _R{__vector_bitcast<_ToT>(
_mm_unpacklo_epi32(__to_intrin(__v), __m128i())),
__vector_bitcast<_ToT>(
_mm_unpackhi_epi32(__to_intrin(__v), __m128i()))};
else
return _R{
__vector_bitcast<_ToT>(_mm_unpacklo_epi32(
__to_intrin(__v), _mm_srai_epi32(__to_intrin(__v), 31))),
__vector_bitcast<_ToT>(_mm_unpackhi_epi32(
__to_intrin(__v), _mm_srai_epi32(__to_intrin(__v), 31)))};
}
else if constexpr (sizeof(_FromT) == 1 && sizeof(_ToT) >= 4 && is_signed_v<_FromT>)
{
const __m128i __vv[2] = {
_mm_unpacklo_epi8(__to_intrin(__v), __to_intrin(__v)),
_mm_unpackhi_epi8(__to_intrin(__v), __to_intrin(__v))
};
const __vector_type16_t<int> __vvvv[4] = {
__vector_bitcast<int>(_mm_unpacklo_epi16(__vv[0], __vv[0])),
__vector_bitcast<int>(_mm_unpackhi_epi16(__vv[0], __vv[0])),
__vector_bitcast<int>(_mm_unpacklo_epi16(__vv[1], __vv[1])),
__vector_bitcast<int>(_mm_unpackhi_epi16(__vv[1], __vv[1]))
};
if constexpr (sizeof(_ToT) == 4)
return __generate_from_n_evaluations<_N, _R>([&](auto __i) {
return __vector_convert<_To>(__vvvv[__i] >> 24);
});
else if constexpr(is_integral_v<_ToT>)
return __generate_from_n_evaluations<_N, _R>(
[&](auto __i) {
const auto __signbits = __to_intrin(__vvvv[__i / 2] >> 31);
const auto __sx32 = __to_intrin(__vvvv[__i / 2] >> 24);
return __vector_bitcast<_ToT>(
__i % 2 == 0 ? _mm_unpacklo_epi32(__sx32, __signbits)
: _mm_unpackhi_epi32(__sx32, __signbits));
});
else
return __generate_from_n_evaluations<_N, _R>(
[&](auto __i) {
const auto __int4 = __vvvv[__i / 2] >> 24;
return __vector_convert<_To>(
__i % 2 == 0 ? __int4
: __vector_bitcast<int>(_mm_unpackhi_epi64(
__to_intrin(__int4), __to_intrin(__int4))));
});
}
else if constexpr (sizeof(_FromT) == 1 && sizeof(_ToT) == 4)
{
const auto __shorts =
__convert_all<__vector_type16_t<conditional_t<
is_signed_v<_FromT>, short, unsigned short>>,
(_N + 1) / 2>(__v);
return __generate_from_n_evaluations<_N, _R>([&](auto __i) {
return __convert_all<_To>(__shorts[__i / 2])[__i % 2];
});
}
else if constexpr (sizeof(_FromT) == 2 && sizeof(_ToT) == 8 &&
is_signed_v<_FromT> && is_integral_v<_ToT>)
{
const __m128i __vv[2] = {
_mm_unpacklo_epi16(__to_intrin(__v), __to_intrin(__v)),
_mm_unpackhi_epi16(__to_intrin(__v), __to_intrin(__v))};
const __vector_type16_t<int> __vvvv[4] = {
__vector_bitcast<int>(_mm_unpacklo_epi32(
_mm_srai_epi32(__vv[0], 24), _mm_srai_epi32(__vv[0], 31))),
__vector_bitcast<int>(_mm_unpackhi_epi32(
_mm_srai_epi32(__vv[0], 24), _mm_srai_epi32(__vv[0], 31))),
__vector_bitcast<int>(_mm_unpacklo_epi32(
_mm_srai_epi32(__vv[1], 24), _mm_srai_epi32(__vv[1], 31))),
__vector_bitcast<int>(_mm_unpackhi_epi32(
_mm_srai_epi32(__vv[1], 24), _mm_srai_epi32(__vv[1], 31)))};
return __generate_from_n_evaluations<_N, _R>([&](auto __i) {
return __vector_bitcast<_ToT>(__vvvv[__i]);
});
}
else if constexpr (sizeof(_FromT) <= 2 && sizeof(_ToT) == 8)
{
const auto __ints =
__convert_all<__vector_type16_t<conditional_t<
is_signed_v<_FromT> || is_floating_point_v<_ToT>,
int, unsigned int>>,
(_N + 1) / 2>(__v);
return __generate_from_n_evaluations<_N, _R>([&](auto __i) {
return __convert_all<_To>(__ints[__i / 2])[__i % 2];
});
}
else
__assert_unreachable<_To>();
}
#endif
else if constexpr (_FromVT::_S_width > _ToVT::_S_width)
{
constexpr size_t _NTotal = _FromVT::_S_width / _ToVT::_S_width;
constexpr size_t _N = _NParts == 0 ? _NTotal : _NParts;
static_assert(_N <= _NTotal);
return __generate_from_n_evaluations<_N, std::array<_To, _N>>([&](
auto __i) constexpr {
auto __part = __extract_part<decltype(__i)::value, _NTotal>(__v);
return __vector_convert<_To>(__part);
});
}
else
return __vector_convert<_To>(__v);
}
template <class _From, class _To, size_t _ToSize> struct __converts_via_decomposition {
private:
static constexpr bool _S_i_to_i = is_integral_v<_From> && is_integral_v<_To>;
static constexpr bool _S_f_to_i = is_floating_point_v<_From> && is_integral_v<_To>;
static constexpr bool _S_f_to_f = is_floating_point_v<_From> && is_floating_point_v<_To>;
static constexpr bool _S_i_to_f = is_integral_v<_From> && is_floating_point_v<_To>;
template <size_t _A, size_t _B>
static constexpr bool _S_sizes = sizeof(_From) == _A && sizeof(_To) == _B;
public:
static constexpr bool value =
(_S_i_to_i && _S_sizes<8, 2> && !__have_ssse3 && _ToSize == 16) ||
(_S_i_to_i && _S_sizes<8, 1> && !__have_avx512f && _ToSize == 16) ||
(_S_f_to_i && _S_sizes<4, 8> && !__have_avx512dq) ||
(_S_f_to_i && _S_sizes<8, 8> && !__have_avx512dq) ||
(_S_f_to_i && _S_sizes<8, 4> && !__have_sse4_1 && _ToSize == 16) ||
(_S_i_to_f && _S_sizes<8, 4> && !__have_avx512dq && _ToSize == 16) ||
(_S_i_to_f && _S_sizes<8, 8> && !__have_avx512dq && _ToSize < 64);
};
template <class _From, class _To, size_t _ToSize>
inline constexpr bool __converts_via_decomposition_v =
__converts_via_decomposition<_From, _To, _ToSize>::value;
template <class _Tp> struct __is_bitset : false_type {};
template <size_t _N> struct __is_bitset<std::bitset<_N>> : true_type {};
template <class _Tp> inline constexpr bool __is_bitset_v = __is_bitset<_Tp>::value;
template <class _Tp> struct __is_storage : false_type {};
template <class _Tp, size_t _N> struct __is_storage<_SimdWrapper<_Tp, _N>> : true_type {};
template <class _Tp> inline constexpr bool __is_storage_v = __is_storage<_Tp>::value;
template <class _To, class _From>
inline _To __convert_mask(_From __k)
{
if constexpr (std::is_same_v<_To, _From>)
{
return __k;
} else if constexpr (std::is_unsigned_v<_From> && std::is_unsigned_v<_To>) {
return __k;
} else if constexpr (__is_bitset_v<_From>) {
static_assert(__k.size() <= sizeof(_ULLong) * CHAR_BIT);
using _Tp = std::conditional_t<
(__k.size() <= sizeof(ushort) * CHAR_BIT),
std::conditional_t<(__k.size() <= CHAR_BIT), _UChar, ushort>,
std::conditional_t<(__k.size() <= sizeof(_UInt) * CHAR_BIT), _UInt, _ULLong>>;
return __convert_mask<_To>(static_cast<_Tp>(__k.to_ullong()));
} else if constexpr (__is_bitset_v<_To>) {
static_assert(_To().size() <= sizeof(_ULLong) * CHAR_BIT);
using _Tp = std::conditional_t<
(_To().size() <= sizeof(ushort) * CHAR_BIT),
std::conditional_t<(_To().size() <= CHAR_BIT), _UChar, ushort>,
std::conditional_t<(_To().size() <= sizeof(_UInt) * CHAR_BIT), _UInt, _ULLong>>;
return __convert_mask<_Tp>(__k);
} else if constexpr (__is_storage_v<_From>) {
return __convert_mask<_To>(__k._M_data);
} else if constexpr (__is_storage_v<_To>) {
return __convert_mask<typename _To::_BuiltinType>(__k);
} else if constexpr (std::is_unsigned_v<_From> && __is_vector_type_v<_To>) {
using _Trait = _VectorTraits<_To>;
constexpr size_t _N_in = sizeof(_From) * CHAR_BIT;
using _ToT = typename _Trait::value_type;
constexpr size_t _N_out = _Trait::_S_width;
constexpr size_t _N = std::min(_N_in, _N_out);
constexpr size_t __bytes_per_output_element = sizeof(_ToT);
#if _GLIBCXX_SIMD_X86INTRIN
if constexpr (__have_avx512f) {
if constexpr (__bytes_per_output_element == 1 && sizeof(_To) == 16) {
if constexpr (__have_avx512bw_vl) {
return __vector_bitcast<_ToT>(_mm_movm_epi8(__k));
} else if constexpr (__have_avx512bw) {
return __vector_bitcast<_ToT>(__lo128(_mm512_movm_epi8(__k)));
} else {
auto __as32bits = _mm512_maskz_mov_epi32(__k, ~__m512i());
auto __as16bits = __xzyw(
_mm256_packs_epi32(__lo256(__as32bits), __hi256(__as32bits)));
return __vector_bitcast<_ToT>(
_mm_packs_epi16(__lo128(__as16bits), __hi128(__as16bits)));
}
} else if constexpr (__bytes_per_output_element == 1 && sizeof(_To) == 32) {
if constexpr (__have_avx512bw_vl) {
return __vector_bitcast<_ToT>(_mm256_movm_epi8(__k));
} else if constexpr (__have_avx512bw) {
return __vector_bitcast<_ToT>(__lo256(_mm512_movm_epi8(__k)));
} else {
auto __as16bits =
_mm512_srli_epi32(_mm512_maskz_mov_epi32(__k, ~__m512i()), 16) |
_mm512_slli_epi32(_mm512_maskz_mov_epi32(__k >> 16, ~__m512i()),
16);
auto __0_16_1_17 = __xzyw(_mm256_packs_epi16(
__lo256(__as16bits),
__hi256(__as16bits))
);
return __vector_bitcast<_ToT>(__xzyw(_mm256_shuffle_epi8(
__0_16_1_17,
_mm256_setr_epi8(0, 2, 4, 6, 8, 10, 12, 14, 1, 3, 5, 7, 9, 11, 13,
15, 0, 2, 4, 6, 8, 10, 12, 14, 1, 3, 5, 7, 9, 11,
13, 15))));
}
} else if constexpr (__bytes_per_output_element == 1 && sizeof(_To) == 64) {
return reinterpret_cast<__vector_type_t<_SChar, 64>>(_mm512_movm_epi8(__k));
} else if constexpr (__bytes_per_output_element == 2 && sizeof(_To) == 16) {
if constexpr (__have_avx512bw_vl) {
return __vector_bitcast<_ToT>(_mm_movm_epi16(__k));
} else if constexpr (__have_avx512bw) {
return __vector_bitcast<_ToT>(__lo128(_mm512_movm_epi16(__k)));
} else {
__m256i __as32bits;
if constexpr (__have_avx512vl) {
__as32bits = _mm256_maskz_mov_epi32(__k, ~__m256i());
} else {
__as32bits = __lo256(_mm512_maskz_mov_epi32(__k, ~__m512i()));
}
return __vector_bitcast<_ToT>(
_mm_packs_epi32(__lo128(__as32bits), __hi128(__as32bits)));
}
} else if constexpr (__bytes_per_output_element == 2 && sizeof(_To) == 32) {
if constexpr (__have_avx512bw_vl) {
return __vector_bitcast<_ToT>(_mm256_movm_epi16(__k));
} else if constexpr (__have_avx512bw) {
return __vector_bitcast<_ToT>(__lo256(_mm512_movm_epi16(__k)));
} else {
auto __as32bits = _mm512_maskz_mov_epi32(__k, ~__m512i());
return __vector_bitcast<_ToT>(__xzyw(
_mm256_packs_epi32(__lo256(__as32bits), __hi256(__as32bits))));
}
} else if constexpr (__bytes_per_output_element == 2 && sizeof(_To) == 64) {
return __vector_bitcast<_ToT>(_mm512_movm_epi16(__k));
} else if constexpr (__bytes_per_output_element == 4 && sizeof(_To) == 16) {
return __vector_bitcast<_ToT>(
__have_avx512dq_vl
? _mm_movm_epi32(__k)
: __have_avx512dq
? __lo128(_mm512_movm_epi32(__k))
: __have_avx512vl
? _mm_maskz_mov_epi32(__k, ~__m128i())
: __lo128(_mm512_maskz_mov_epi32(__k, ~__m512i())));
} else if constexpr (__bytes_per_output_element == 4 && sizeof(_To) == 32) {
return __vector_bitcast<_ToT>(
__have_avx512dq_vl
? _mm256_movm_epi32(__k)
: __have_avx512dq
? __lo256(_mm512_movm_epi32(__k))
: __have_avx512vl
? _mm256_maskz_mov_epi32(__k, ~__m256i())
: __lo256(_mm512_maskz_mov_epi32(__k, ~__m512i())));
} else if constexpr (__bytes_per_output_element == 4 && sizeof(_To) == 64) {
return __vector_bitcast<_ToT>(__have_avx512dq
? _mm512_movm_epi32(__k)
: _mm512_maskz_mov_epi32(__k, ~__m512i()));
} else if constexpr (__bytes_per_output_element == 8 && sizeof(_To) == 16) {
return __vector_bitcast<_ToT>(
__have_avx512dq_vl
? _mm_movm_epi64(__k)
: __have_avx512dq
? __lo128(_mm512_movm_epi64(__k))
: __have_avx512vl
? _mm_maskz_mov_epi64(__k, ~__m128i())
: __lo128(_mm512_maskz_mov_epi64(__k, ~__m512i())));
} else if constexpr (__bytes_per_output_element == 8 && sizeof(_To) == 32) {
return __vector_bitcast<_ToT>(
__have_avx512dq_vl
? _mm256_movm_epi64(__k)
: __have_avx512dq
? __lo256(_mm512_movm_epi64(__k))
: __have_avx512vl
? _mm256_maskz_mov_epi64(__k, ~__m256i())
: __lo256(_mm512_maskz_mov_epi64(__k, ~__m512i())));
} else if constexpr (__bytes_per_output_element == 8 && sizeof(_To) == 64) {
return __vector_bitcast<_ToT>(__have_avx512dq
? _mm512_movm_epi64(__k)
: _mm512_maskz_mov_epi64(__k, ~__m512i()));
} else {
__assert_unreachable<_To>();
}
} else if constexpr (__have_sse) {
using _U = std::make_unsigned_t<__int_for_sizeof_t<_ToT>>;
using _V = __vector_type_t<_U, _N>;
static_assert(sizeof(_V) <= 32);
constexpr size_t __bits_per_element = sizeof(_U) * CHAR_BIT;
if constexpr (!__have_avx2 && __have_avx && sizeof(_V) == 32) {
if constexpr (_N == 8) {
return _mm256_cmp_ps(
_mm256_and_ps(
_mm256_castsi256_ps(_mm256_set1_epi32(__k)),
_mm256_castsi256_ps(_mm256_setr_epi32(
0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80))),
_mm256_setzero_ps(), _CMP_NEQ_UQ);
} else if constexpr (_N == 4) {
return _mm256_cmp_pd(
_mm256_and_pd(
_mm256_castsi256_pd(_mm256_set1_epi64x(__k)),
_mm256_castsi256_pd(
_mm256_setr_epi64x(0x01, 0x02, 0x04, 0x08))),
_mm256_setzero_pd(), _CMP_NEQ_UQ);
} else {
__assert_unreachable<_To>();
}
} else if constexpr (__bits_per_element >= _N) {
constexpr auto __bitmask = __generate_vector<__vector_type_t<_U, _N>>(
[](auto __i) constexpr -> _U { return 1ull << __i; });
return __vector_bitcast<_ToT>(
(__vector_broadcast<_N, _U>(__k) & __bitmask) != 0);
} else if constexpr (sizeof(_V) == 16 && sizeof(_ToT) == 1 && __have_ssse3) {
const auto __bitmask = __to_intrin(__make_vector<_UChar>(
1, 2, 4, 8, 16, 32, 64, 128, 1, 2, 4, 8, 16, 32, 64, 128));
return __vector_bitcast<_ToT>(
__vector_bitcast<_ToT>(
_mm_shuffle_epi8(
__to_intrin(__vector_type_t<_ULLong, 2>{__k}),
_mm_setr_epi8(0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1,
1)) &
__bitmask) != 0);
} else if constexpr (sizeof(_V) == 32 && sizeof(_ToT) == 1 && __have_avx2) {
const auto __bitmask =
_mm256_broadcastsi128_si256(__to_intrin(__make_vector<_UChar>(
1, 2, 4, 8, 16, 32, 64, 128, 1, 2, 4, 8, 16, 32, 64, 128)));
return __vector_bitcast<_ToT>(
__vector_bitcast<_ToT>(_mm256_shuffle_epi8(
_mm256_broadcastsi128_si256(__to_intrin(
__vector_type_t<_ULLong, 2>{__k})),
_mm256_setr_epi8(0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1,
1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2,
2, 2, 3, 3, 3, 3, 3, 3, 3, 3)) &
__bitmask) != 0);
} else {
const _V __tmp = __generate_vector<_V>([&](auto __i) constexpr {
return static_cast<_U>(
__k >> (__bits_per_element * (__i / __bits_per_element)));
}) &
__generate_vector<_V>([](auto __i) constexpr {
return static_cast<_U>(1ull << (__i % __bits_per_element));
});
return __vector_bitcast<_ToT>(__tmp != _V());
}
} else
#endif
{
using _I = __int_for_sizeof_t<_ToT>;
return reinterpret_cast<_To>(
__generate_vector<__vector_type_t<_I, _N_out>>([&](auto __i) constexpr {
return ((__k >> __i) & 1) == 0 ? _I() : ~_I();
}));
}
} else if constexpr (__is_vector_type_v<_From> && std::is_unsigned_v<_To>) {
using _Trait = _VectorTraits<_From>;
using _Tp = typename _Trait::value_type;
constexpr size_t _FromN = _Trait::_S_width;
constexpr size_t cvt_id = _FromN * 10 + sizeof(_Tp);
constexpr bool __have_avx512_int = __have_avx512f && std::is_integral_v<_Tp>;
[[maybe_unused]]
const auto __intrin = __to_intrin(__k);
#if _GLIBCXX_SIMD_X86INTRIN
if constexpr (cvt_id == 16'1 && __have_avx512bw_vl) { return    _mm_movepi8_mask(__intrin); }
else if constexpr (cvt_id == 16'1 && __have_avx512bw   ) { return _mm512_movepi8_mask(__zero_extend(__intrin)); }
else if constexpr (cvt_id == 16'1                      ) { return    _mm_movemask_epi8(__intrin); }
else if constexpr (cvt_id == 32'1 && __have_avx512bw_vl) { return _mm256_movepi8_mask(__intrin); }
else if constexpr (cvt_id == 32'1 && __have_avx512bw   ) { return _mm512_movepi8_mask(__zero_extend(__intrin)); }
else if constexpr (cvt_id == 32'1                      ) { return _mm256_movemask_epi8(__intrin); }
else if constexpr (cvt_id == 64'1 && __have_avx512bw   ) { return _mm512_movepi8_mask(__intrin); }
else if constexpr (cvt_id == 8'2 && __have_avx512bw_vl) { return    _mm_movepi16_mask(__intrin); }
else if constexpr (cvt_id == 8'2 && __have_avx512bw   ) { return _mm512_movepi16_mask(__zero_extend(__intrin)); }
else if constexpr (cvt_id == 8'2                      ) { return movemask_epi16(__intrin); }
else if constexpr (cvt_id == 16'2 && __have_avx512bw_vl) { return _mm256_movepi16_mask(__intrin); }
else if constexpr (cvt_id == 16'2 && __have_avx512bw   ) { return _mm512_movepi16_mask(__zero_extend(__intrin)); }
else if constexpr (cvt_id == 16'2                      ) { return movemask_epi16(__intrin); }
else if constexpr (cvt_id == 32'2 && __have_avx512bw   ) { return _mm512_movepi16_mask(__intrin); }
else if constexpr (cvt_id == 4'4 && __have_avx512dq_vl) { return    _mm_movepi32_mask(__vector_bitcast<_LLong>(__k)); }
else if constexpr (cvt_id == 4'4 && __have_avx512dq   ) { return _mm512_movepi32_mask(__zero_extend(__vector_bitcast<_LLong>(__k))); }
else if constexpr (cvt_id == 4'4 && __have_avx512vl   ) { return    _mm_cmp_epi32_mask(__vector_bitcast<_LLong>(__k), __m128i(), _MM_CMPINT_LT); }
else if constexpr (cvt_id == 4'4 && __have_avx512_int ) { return _mm512_cmp_epi32_mask(__zero_extend(__intrin), __m512i(), _MM_CMPINT_LT); }
else if constexpr (cvt_id == 4'4                      ) { return    _mm_movemask_ps(__k); }
else if constexpr (cvt_id == 8'4 && __have_avx512dq_vl) { return _mm256_movepi32_mask(__vector_bitcast<_LLong>(__k)); }
else if constexpr (cvt_id == 8'4 && __have_avx512dq   ) { return _mm512_movepi32_mask(__zero_extend(__vector_bitcast<_LLong>(__k))); }
else if constexpr (cvt_id == 8'4 && __have_avx512vl   ) { return _mm256_cmp_epi32_mask(__vector_bitcast<_LLong>(__k), __m256i(), _MM_CMPINT_LT); }
else if constexpr (cvt_id == 8'4 && __have_avx512_int ) { return _mm512_cmp_epi32_mask(__zero_extend(__intrin), __m512i(), _MM_CMPINT_LT); }
else if constexpr (cvt_id == 8'4                      ) { return _mm256_movemask_ps(__k); }
else if constexpr (cvt_id == 16'4 && __have_avx512dq   ) { return _mm512_movepi32_mask(__vector_bitcast<_LLong>(__k)); }
else if constexpr (cvt_id == 16'4                      ) { return _mm512_cmp_epi32_mask(__vector_bitcast<_LLong>(__k), __m512i(), _MM_CMPINT_LT); }
else if constexpr (cvt_id == 2'8 && __have_avx512dq_vl) { return    _mm_movepi64_mask(__vector_bitcast<_LLong>(__k)); }
else if constexpr (cvt_id == 2'8 && __have_avx512dq   ) { return _mm512_movepi64_mask(__zero_extend(__vector_bitcast<_LLong>(__k))); }
else if constexpr (cvt_id == 2'8 && __have_avx512vl   ) { return    _mm_cmp_epi64_mask(__vector_bitcast<_LLong>(__k), __m128i(), _MM_CMPINT_LT); }
else if constexpr (cvt_id == 2'8 && __have_avx512_int ) { return _mm512_cmp_epi64_mask(__zero_extend(__intrin), __m512i(), _MM_CMPINT_LT); }
else if constexpr (cvt_id == 2'8                      ) { return    _mm_movemask_pd(__k); }
else if constexpr (cvt_id == 4'8 && __have_avx512dq_vl) { return _mm256_movepi64_mask(__vector_bitcast<_LLong>(__k)); }
else if constexpr (cvt_id == 4'8 && __have_avx512dq   ) { return _mm512_movepi64_mask(__zero_extend(__vector_bitcast<_LLong>(__k))); }
else if constexpr (cvt_id == 4'8 && __have_avx512vl   ) { return _mm256_cmp_epi64_mask(__vector_bitcast<_LLong>(__k), __m256i(), _MM_CMPINT_LT); }
else if constexpr (cvt_id == 4'8 && __have_avx512_int ) { return _mm512_cmp_epi64_mask(__zero_extend(__intrin), __m512i(), _MM_CMPINT_LT); }
else if constexpr (cvt_id == 4'8                      ) { return _mm256_movemask_pd(__k); }
else if constexpr (cvt_id == 8'8 && __have_avx512dq   ) { return _mm512_movepi64_mask(__vector_bitcast<_LLong>(__k)); }
else if constexpr (cvt_id == 8'8                      ) { return _mm512_cmp_epi64_mask(__vector_bitcast<_LLong>(__k), __m512i(), _MM_CMPINT_LT); }
else
#endif
__assert_unreachable<_To>();
} else if constexpr (__is_vector_type_v<_From> && __is_vector_type_v<_To>) {
using _ToTrait = _VectorTraits<_To>;
using _FromTrait = _VectorTraits<_From>;
using _ToT = typename _ToTrait::value_type;
using _Tp = typename _FromTrait::value_type;
constexpr size_t _FromN = _FromTrait::_S_width;
constexpr size_t _ToN = _ToTrait::_S_width;
constexpr int _FromBytes = sizeof(_Tp);
constexpr int _ToBytes = sizeof(_ToT);
if constexpr (_FromN == _ToN && sizeof(_From) == sizeof(_To))
{
return reinterpret_cast<_To>(__k);
}
#if _GLIBCXX_SIMD_X86INTRIN
else if constexpr (sizeof(_To) == 16 && sizeof(__k) == 16)
{
if constexpr (_FromBytes == 4 && _ToBytes == 8) {
if constexpr(std::is_integral_v<_Tp>) {
return __vector_bitcast<_ToT>(__interleave128_lo(__k, __k));
} else {
return __vector_bitcast<_ToT>(__interleave128_lo(__k, __k));
}
} else if constexpr (_FromBytes == 2 && _ToBytes == 8) {
const auto __y = __vector_bitcast<int>(__interleave128_lo(__k, __k));
return __vector_bitcast<_ToT>(__interleave128_lo(__y, __y));
} else if constexpr (_FromBytes == 1 && _ToBytes == 8) {
auto __y = __vector_bitcast<short>(__interleave128_lo(__k, __k));
auto __z = __vector_bitcast<int>(__interleave128_lo(__y, __y));
return __vector_bitcast<_ToT>(__interleave128_lo(__z, __z));
} else if constexpr (_FromBytes == 8 && _ToBytes == 4) {
if constexpr (__have_sse2)
return __vector_bitcast<_ToT>(
_mm_packs_epi32(__vector_bitcast<_LLong>(__k), __m128i()));
else
return __vector_shuffle<1, 3, 6, 7>(
__vector_bitcast<_ToT>(__k), _To());
} else if constexpr (_FromBytes == 2 && _ToBytes == 4) {
return __vector_bitcast<_ToT>(__interleave128_lo(__k, __k));
} else if constexpr (_FromBytes == 1 && _ToBytes == 4) {
const auto __y = __vector_bitcast<short>(__interleave128_lo(__k, __k));
return __vector_bitcast<_ToT>(__interleave128_lo(__y, __y));
} else if constexpr (_FromBytes == 8 && _ToBytes == 2) {
if constexpr (__have_sse2 && !__have_ssse3)
return __vector_bitcast<_ToT>(_mm_packs_epi32(
_mm_packs_epi32(__vector_bitcast<_LLong>(__k), __m128i()),
__m128i()));
else
return __vector_permute<3, 7, -1, -1, -1, -1, -1, -1>(
__vector_bitcast<_ToT>(__k));
} else if constexpr (_FromBytes == 4 && _ToBytes == 2) {
return __vector_bitcast<_ToT>(
_mm_packs_epi32(__vector_bitcast<_LLong>(__k), __m128i()));
} else if constexpr (_FromBytes == 1 && _ToBytes == 2) {
return __vector_bitcast<_ToT>(__interleave128_lo(__k, __k));
} else if constexpr (_FromBytes == 8 && _ToBytes == 1) {
if constexpr(__have_ssse3) {
return __vector_bitcast<_ToT>(
_mm_shuffle_epi8(__vector_bitcast<_LLong>(__k),
_mm_setr_epi8(7, 15, -1, -1, -1, -1, -1, -1, -1,
-1, -1, -1, -1, -1, -1, -1)));
} else {
auto __y = _mm_packs_epi32(__vector_bitcast<_LLong>(__k), __m128i());
__y = _mm_packs_epi32(__y, __m128i());
return __vector_bitcast<_ToT>(_mm_packs_epi16(__y, __m128i()));
}
return __vector_permute<7, 15, -1, -1, -1, -1, -1, -1, -1, -1,
-1, -1, -1, -1, -1, -1>(
__vector_bitcast<_ToT>(__k));
} else if constexpr (_FromBytes == 4 && _ToBytes == 1) {
if constexpr(__have_ssse3) {
return __vector_bitcast<_ToT>(
_mm_shuffle_epi8(__vector_bitcast<_LLong>(__k),
_mm_setr_epi8(3, 7, 11, 15, -1, -1, -1, -1, -1,
-1, -1, -1, -1, -1, -1, -1)));
} else {
const auto __y = _mm_packs_epi32(__vector_bitcast<_LLong>(__k), __m128i());
return __vector_bitcast<_ToT>(_mm_packs_epi16(__y, __m128i()));
}
return __vector_permute<3, 7, 11, 15, -1, -1, -1, -1, -1, -1,
-1, -1, -1, -1, -1, -1>(
__vector_bitcast<_ToT>(__k));
} else if constexpr (_FromBytes == 2 && _ToBytes == 1) {
return __vector_bitcast<_ToT>(_mm_packs_epi16(__vector_bitcast<_LLong>(__k), __m128i()));
} else {
static_assert(!std::is_same_v<_Tp, _Tp>, "should be unreachable");
}
}
else if constexpr (sizeof(_To) == 32 && sizeof(__k) == 32)
{
if constexpr (_FromBytes == _ToBytes) {
__assert_unreachable<_Tp>();
} else if constexpr (_FromBytes == _ToBytes * 2) {
const auto __y = __vector_bitcast<_LLong>(__k);
return __vector_bitcast<_ToT>(
_mm256_castsi128_si256(_mm_packs_epi16(__lo128(__y), __hi128(__y))));
} else if constexpr (_FromBytes == _ToBytes * 4) {
const auto __y = __vector_bitcast<_LLong>(__k);
return __vector_bitcast<_ToT>(_mm256_castsi128_si256(
_mm_packs_epi16(_mm_packs_epi16(__lo128(__y), __hi128(__y)), __m128i())));
} else if constexpr (_FromBytes == _ToBytes * 8) {
const auto __y = __vector_bitcast<_LLong>(__k);
return __vector_bitcast<_ToT>(_mm256_castsi128_si256(
_mm_shuffle_epi8(_mm_packs_epi16(__lo128(__y), __hi128(__y)),
_mm_setr_epi8(3, 7, 11, 15, -1, -1, -1, -1, -1, -1,
-1, -1, -1, -1, -1, -1))));
} else if constexpr (_FromBytes * 2 == _ToBytes) {
auto __y = __xzyw(__to_intrin(__k));
if constexpr(std::is_floating_point_v<_Tp>) {
return __vector_bitcast<_ToT>(_mm256_unpacklo_ps(__y, __y));
} else {
return __vector_bitcast<_ToT>(_mm256_unpacklo_epi8(__y, __y));
}
} else if constexpr (_FromBytes * 4 == _ToBytes) {
auto __y = _mm_unpacklo_epi8(__lo128(__vector_bitcast<_LLong>(__k)),
__lo128(__vector_bitcast<_LLong>(__k)));
return __vector_bitcast<_ToT>(
__concat(_mm_unpacklo_epi16(__y, __y), _mm_unpackhi_epi16(__y, __y)));
} else if constexpr (_FromBytes == 1 && _ToBytes == 8) {
auto __y = _mm_unpacklo_epi8(__lo128(__vector_bitcast<_LLong>(__k)),
__lo128(__vector_bitcast<_LLong>(__k)));
__y = _mm_unpacklo_epi16(__y, __y);
return __vector_bitcast<_ToT>(
__concat(_mm_unpacklo_epi32(__y, __y), _mm_unpackhi_epi32(__y, __y)));
} else {
__assert_unreachable<_Tp>();
}
}
else if constexpr (sizeof(_To) == 32 && sizeof(__k) == 16)
{
if constexpr (_FromBytes == _ToBytes) {
return __vector_bitcast<_ToT>(
__intrinsic_type_t<_Tp, 32 / sizeof(_Tp)>(__zero_extend(__to_intrin(__k))));
} else if constexpr (_FromBytes * 2 == _ToBytes) {
return __vector_bitcast<_ToT>(__concat(_mm_unpacklo_epi8(__vector_bitcast<_LLong>(__k), __vector_bitcast<_LLong>(__k)),
_mm_unpackhi_epi8(__vector_bitcast<_LLong>(__k), __vector_bitcast<_LLong>(__k))));
} else if constexpr (_FromBytes * 4 == _ToBytes) {
if constexpr (__have_avx2) {
return __vector_bitcast<_ToT>(_mm256_shuffle_epi8(
__concat(__vector_bitcast<_LLong>(__k), __vector_bitcast<_LLong>(__k)),
_mm256_setr_epi8(0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3,
4, 4, 4, 4, 5, 5, 5, 5, 6, 6, 6, 6, 7, 7, 7,
7)));
} else {
return __vector_bitcast<_ToT>(
__concat(_mm_shuffle_epi8(__vector_bitcast<_LLong>(__k),
_mm_setr_epi8(0, 0, 0, 0, 1, 1, 1, 1, 2,
2, 2, 2, 3, 3, 3, 3)),
_mm_shuffle_epi8(__vector_bitcast<_LLong>(__k),
_mm_setr_epi8(4, 4, 4, 4, 5, 5, 5, 5, 6,
6, 6, 6, 7, 7, 7, 7))));
}
} else if constexpr (_FromBytes * 8 == _ToBytes) {
if constexpr (__have_avx2) {
return __vector_bitcast<_ToT>(_mm256_shuffle_epi8(
__concat(__vector_bitcast<_LLong>(__k), __vector_bitcast<_LLong>(__k)),
_mm256_setr_epi8(0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1,
2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3,
3)));
} else {
return __vector_bitcast<_ToT>(
__concat(_mm_shuffle_epi8(__vector_bitcast<_LLong>(__k),
_mm_setr_epi8(0, 0, 0, 0, 0, 0, 0, 0, 1,
1, 1, 1, 1, 1, 1, 1)),
_mm_shuffle_epi8(__vector_bitcast<_LLong>(__k),
_mm_setr_epi8(2, 2, 2, 2, 2, 2, 2, 2, 3,
3, 3, 3, 3, 3, 3, 3))));
}
} else if constexpr (_FromBytes == _ToBytes * 2) {
return __vector_bitcast<_ToT>(
__m256i(__zero_extend(_mm_packs_epi16(__vector_bitcast<_LLong>(__k), __m128i()))));
} else if constexpr (_FromBytes == 8 && _ToBytes == 2) {
return __vector_bitcast<_ToT>(__m256i(__zero_extend(
_mm_shuffle_epi8(__vector_bitcast<_LLong>(__k),
_mm_setr_epi8(6, 7, 14, 15, -1, -1, -1, -1, -1, -1,
-1, -1, -1, -1, -1, -1)))));
} else if constexpr (_FromBytes == 4 && _ToBytes == 1) {
return __vector_bitcast<_ToT>(__m256i(__zero_extend(
_mm_shuffle_epi8(__vector_bitcast<_LLong>(__k),
_mm_setr_epi8(3, 7, 11, 15, -1, -1, -1, -1, -1, -1,
-1, -1, -1, -1, -1, -1)))));
} else if constexpr (_FromBytes == 8 && _ToBytes == 1) {
return __vector_bitcast<_ToT>(__m256i(__zero_extend(
_mm_shuffle_epi8(__vector_bitcast<_LLong>(__k),
_mm_setr_epi8(7, 15, -1, -1, -1, -1, -1, -1, -1, -1,
-1, -1, -1, -1, -1, -1)))));
} else {
static_assert(!std::is_same_v<_Tp, _Tp>, "should be unreachable");
}
}
else if constexpr (sizeof(_To) == 16 && sizeof(__k) == 32)
{
if constexpr (_FromBytes == _ToBytes) {
return __vector_bitcast<_ToT>(__lo128(__k));
} else if constexpr (_FromBytes == _ToBytes * 2) {
auto __y = __vector_bitcast<_LLong>(__k);
return __vector_bitcast<_ToT>(_mm_packs_epi16(__lo128(__y), __hi128(__y)));
} else if constexpr (_FromBytes == _ToBytes * 4) {
auto __y = __vector_bitcast<_LLong>(__k);
return __vector_bitcast<_ToT>(
_mm_packs_epi16(_mm_packs_epi16(__lo128(__y), __hi128(__y)), __m128i()));
} else if constexpr (_FromBytes == 8 && _ToBytes == 1) {
auto __y = __vector_bitcast<_LLong>(__k);
return __vector_bitcast<_ToT>(
_mm_shuffle_epi8(_mm_packs_epi16(__lo128(__y), __hi128(__y)),
_mm_setr_epi8(3, 7, 11, 15, -1, -1, -1, -1, -1, -1,
-1, -1, -1, -1, -1, -1)));
} else if constexpr (_FromBytes * 2 == _ToBytes) {
auto __y = __lo128(__vector_bitcast<_LLong>(__k));
return __vector_bitcast<_ToT>(_mm_unpacklo_epi8(__y, __y));
} else if constexpr (_FromBytes * 4 == _ToBytes) {
auto __y = __lo128(__vector_bitcast<_LLong>(__k));
__y = _mm_unpacklo_epi8(__y, __y);
return __vector_bitcast<_ToT>(_mm_unpacklo_epi8(__y, __y));
} else if constexpr (_FromBytes * 8 == _ToBytes) {
auto __y = __lo128(__vector_bitcast<_LLong>(__k));
__y = _mm_unpacklo_epi8(__y, __y);
__y = _mm_unpacklo_epi8(__y, __y);
return __vector_bitcast<_ToT>(_mm_unpacklo_epi8(__y, __y));
} else {
static_assert(!std::is_same_v<_Tp, _Tp>, "should be unreachable");
}
}
#endif
else
{
using _I = __int_for_sizeof_t<_ToT>;
return reinterpret_cast<_To>(
__generate_vector<__vector_type_t<_I, _ToN>>([&](auto __i) constexpr {
return __i >= _FromN || __k[int(__i)] == 0 ? _I() : ~_I();
}));
}
} else {
__assert_unreachable<_To>();
}
}
template <class _Abi> struct _SimdMathFallback {
using _SuperImpl = typename _Abi::_SimdImpl;
#define _GLIBCXX_SIMD_MATH_FALLBACK(__name) \
template <typename _Tp, typename... _More> \
static _Tp __##__name(const _Tp& __x, const _More&... __more) \
{ \
if constexpr ((__is_vectorizable_v<_Tp> && ... && \
__is_vectorizable_v<_More>)) \
return std::__name(__x, __more...); \
else if constexpr (__is_vectorizable_v<_Tp>) \
return std::__name(__x, __more[0]...); \
else \
return __generate_vector<_Tp>( \
[&](auto __i) { return std::__name(__x[__i], __more[__i]...); }); \
}
#define _GLIBCXX_SIMD_MATH_FALLBACK_MASKRET(__name) \
template <typename _Tp, typename... _More> \
static \
typename _Tp::mask_type __##__name(const _Tp& __x, const _More&... __more) \
{ \
if constexpr ((__is_vectorizable_v<_Tp> && ... && \
__is_vectorizable_v<_More>)) \
return std::__name(__x, __more...); \
else if constexpr (__is_vectorizable_v<_Tp>) \
return std::__name(__x, __more[0]...); \
else \
return __generate_vector<_Tp>( \
[&](auto __i) { return std::__name(__x[__i], __more[__i]...); }); \
}
#define _GLIBCXX_SIMD_MATH_FALLBACK_FIXEDRET(_RetTp,__name) \
template <typename _Tp, typename... _More> \
static auto __##__name(const _Tp& __x, const _More&... __more) \
{ \
if constexpr (__is_vectorizable_v<_Tp>) \
return _SimdTuple<_RetTp, simd_abi::scalar>{ \
std::__name(__x, __more...)}; \
else \
return __fixed_size_storage_t<_RetTp, _VectorTraits<_Tp>::_S_width>:: \
__generate([&](auto __meta) constexpr { \
return __meta.__generator( \
[&](auto __i) { \
return std::__name(__x[__meta._S_offset + __i], \
__more[__meta._S_offset + __i]...); \
}, \
static_cast<_RetTp*>(nullptr)); \
}); \
}
_GLIBCXX_SIMD_MATH_FALLBACK(acos)
_GLIBCXX_SIMD_MATH_FALLBACK(asin)
_GLIBCXX_SIMD_MATH_FALLBACK(atan)
_GLIBCXX_SIMD_MATH_FALLBACK(atan2)
_GLIBCXX_SIMD_MATH_FALLBACK(cos)
_GLIBCXX_SIMD_MATH_FALLBACK(sin)
_GLIBCXX_SIMD_MATH_FALLBACK(tan)
_GLIBCXX_SIMD_MATH_FALLBACK(acosh)
_GLIBCXX_SIMD_MATH_FALLBACK(asinh)
_GLIBCXX_SIMD_MATH_FALLBACK(atanh)
_GLIBCXX_SIMD_MATH_FALLBACK(cosh)
_GLIBCXX_SIMD_MATH_FALLBACK(sinh)
_GLIBCXX_SIMD_MATH_FALLBACK(tanh)
_GLIBCXX_SIMD_MATH_FALLBACK(exp)
_GLIBCXX_SIMD_MATH_FALLBACK(exp2)
_GLIBCXX_SIMD_MATH_FALLBACK(expm1)
_GLIBCXX_SIMD_MATH_FALLBACK(ldexp)
_GLIBCXX_SIMD_MATH_FALLBACK_FIXEDRET(int, ilogb)
_GLIBCXX_SIMD_MATH_FALLBACK(log)
_GLIBCXX_SIMD_MATH_FALLBACK(log10)
_GLIBCXX_SIMD_MATH_FALLBACK(log1p)
_GLIBCXX_SIMD_MATH_FALLBACK(log2)
_GLIBCXX_SIMD_MATH_FALLBACK(logb)
_GLIBCXX_SIMD_MATH_FALLBACK(scalbn)
_GLIBCXX_SIMD_MATH_FALLBACK(scalbln)
_GLIBCXX_SIMD_MATH_FALLBACK(cbrt)
_GLIBCXX_SIMD_MATH_FALLBACK(abs)
_GLIBCXX_SIMD_MATH_FALLBACK(fabs)
_GLIBCXX_SIMD_MATH_FALLBACK(pow)
_GLIBCXX_SIMD_MATH_FALLBACK(sqrt)
_GLIBCXX_SIMD_MATH_FALLBACK(erf)
_GLIBCXX_SIMD_MATH_FALLBACK(erfc)
_GLIBCXX_SIMD_MATH_FALLBACK(lgamma)
_GLIBCXX_SIMD_MATH_FALLBACK(tgamma)
_GLIBCXX_SIMD_MATH_FALLBACK(ceil)
_GLIBCXX_SIMD_MATH_FALLBACK(floor)
_GLIBCXX_SIMD_MATH_FALLBACK(nearbyint)
_GLIBCXX_SIMD_MATH_FALLBACK(rint)
_GLIBCXX_SIMD_MATH_FALLBACK_FIXEDRET(long, lrint)
_GLIBCXX_SIMD_MATH_FALLBACK_FIXEDRET(long long, llrint)
_GLIBCXX_SIMD_MATH_FALLBACK(round)
_GLIBCXX_SIMD_MATH_FALLBACK_FIXEDRET(long, lround)
_GLIBCXX_SIMD_MATH_FALLBACK_FIXEDRET(long long, llround)
_GLIBCXX_SIMD_MATH_FALLBACK(trunc)
_GLIBCXX_SIMD_MATH_FALLBACK(fmod)
_GLIBCXX_SIMD_MATH_FALLBACK(remainder)
template <typename _Tp, typename _TVT = _VectorTraits<_Tp>>
static _Tp __remquo(const _Tp __x,
const _Tp __y,
__fixed_size_storage_t<int, _TVT::_S_width>* __z)
{
return __generate_vector<_Tp>([&](auto __i) {
int __tmp;
auto __r = std::remquo(__x[__i], __y[__i], &__tmp);
__z->__set(__i, __tmp);
return __r;
});
}
_GLIBCXX_SIMD_MATH_FALLBACK(nextafter)
_GLIBCXX_SIMD_MATH_FALLBACK(fdim)
_GLIBCXX_SIMD_MATH_FALLBACK(fmax)
_GLIBCXX_SIMD_MATH_FALLBACK(fmin)
_GLIBCXX_SIMD_MATH_FALLBACK(fma)
_GLIBCXX_SIMD_MATH_FALLBACK_FIXEDRET(int, fpclassify)
template <class _Tp>
_GLIBCXX_SIMD_INTRINSIC simd_mask<_Tp, _Abi>
__isfinite(const simd<_Tp, _Abi>& __x)
{
return simd<_Tp, _Abi>([&](auto __i) { return std::isfinite(__x[__i]); });
}
template <class _Tp>
_GLIBCXX_SIMD_INTRINSIC simd_mask<_Tp, _Abi>
__isinf(const simd<_Tp, _Abi>& __x)
{
return simd<_Tp, _Abi>([&](auto __i) { return std::isinf(__x[__i]); });
}
template <class _Tp>
_GLIBCXX_SIMD_INTRINSIC simd_mask<_Tp, _Abi>
__isnan(const simd<_Tp, _Abi>& __x)
{
return simd<_Tp, _Abi>([&](auto __i) { return std::isnan(__x[__i]); });
}
template <class _Tp>
_GLIBCXX_SIMD_INTRINSIC simd_mask<_Tp, _Abi>
__isnormal(const simd<_Tp, _Abi>& __x)
{
return simd<_Tp, _Abi>([&](auto __i) { return std::isnormal(__x[__i]); });
}
template <class _Tp>
_GLIBCXX_SIMD_INTRINSIC simd_mask<_Tp, _Abi>
__signbit(const simd<_Tp, _Abi>& __x)
{
return simd<_Tp, _Abi>([&](auto __i) { return std::signbit(__x[__i]); });
}
template <typename _Tp, typename _TVT = _VectorTraits<_Tp>>
_GLIBCXX_SIMD_INTRINSIC static constexpr auto
__isgreater(const _Tp& __x, const _Tp& __y)
{
return _SuperImpl::__less(__y, __x);
}
template <typename _Tp, typename _TVT = _VectorTraits<_Tp>>
_GLIBCXX_SIMD_INTRINSIC static constexpr auto
__isgreaterequal(const _Tp& __x, const _Tp& __y)
{
return _SuperImpl::__less_equal(__y, __x);
}
template <typename _Tp, typename _TVT = _VectorTraits<_Tp>>
_GLIBCXX_SIMD_INTRINSIC static constexpr auto
__isless(const _Tp& __x, const _Tp& __y)
{
return _SuperImpl::__less(__x, __y);
}
template <typename _Tp, typename _TVT = _VectorTraits<_Tp>>
_GLIBCXX_SIMD_INTRINSIC static constexpr auto
__islessequal(const _Tp& __x, const _Tp& __y)
{
return _SuperImpl::__less_equal(__x, __y);
}
template <typename _Tp, typename _TVT = _VectorTraits<_Tp>>
_GLIBCXX_SIMD_INTRINSIC static constexpr auto
__islessgreater(const _Tp& __x, const _Tp& __y)
{
return __or(_SuperImpl::__less(__y, __x), _SuperImpl::__less(__x, __y));
}
template <typename _Tp, typename _TVT = _VectorTraits<_Tp>>
_GLIBCXX_SIMD_INTRINSIC static constexpr auto
__isunordered(const _Tp& __x, const _Tp& __y)
{
return __cmpunord(__x, __y);
}
#undef _GLIBCXX_SIMD_MATH_FALLBACK
#undef _GLIBCXX_SIMD_MATH_FALLBACK_FIXEDRET
};
struct _SimdImplScalar : _SimdMathFallback<simd_abi::scalar> {
using abi_type = std::experimental::simd_abi::scalar;
using _MaskMember = bool;
template <class _Tp> using _SimdMember = _Tp;
template <class _Tp> using _Simd = std::experimental::simd<_Tp, abi_type>;
template <class _Tp> using _TypeTag = _Tp *;
template <class _Tp> _GLIBCXX_SIMD_INTRINSIC static constexpr _Tp __broadcast(_Tp __x) noexcept
{
return __x;
}
template <class _F, class _Tp>
_GLIBCXX_SIMD_INTRINSIC static constexpr _Tp
__generator(_F&& __gen, _TypeTag<_Tp>)
{
return __gen(_SizeConstant<0>());
}
template <class _Tp, class _U, class _F>
static inline _Tp __load(const _U *__mem, _F, _TypeTag<_Tp>) noexcept
{
return static_cast<_Tp>(__mem[0]);
}
template <class _Tp, class _U, class _F>
static inline _Tp __masked_load(_Tp __merge, bool __k, const _U *__mem, _F) noexcept
{
if (__k) {
__merge = static_cast<_Tp>(__mem[0]);
}
return __merge;
}
template <class _Tp, class _U, class _F>
static inline void __store(_Tp __v, _U *__mem, _F, _TypeTag<_Tp>) noexcept
{
__mem[0] = static_cast<_Tp>(__v);
}
template <class _Tp, class _U, class _F>
static inline void __masked_store(const _Tp __v, _U *__mem, _F, const bool __k) noexcept
{
if (__k) {
__mem[0] = __v;
}
}
template <class _Tp> static inline bool __negate(_Tp __x) noexcept { return !__x; }
template <class _Tp, class _BinaryOperation>
static inline _Tp __reduce(const _Simd<_Tp> &__x, _BinaryOperation &)
{
return __x._M_data;
}
template <class _Tp> static inline _Tp __min(const _Tp __a, const _Tp __b)
{
return std::min(__a, __b);
}
template <class _Tp> static inline _Tp __max(const _Tp __a, const _Tp __b)
{
return std::max(__a, __b);
}
template <class _Tp> static inline _Tp __complement(_Tp __x) noexcept
{
return static_cast<_Tp>(~__x);
}
template <class _Tp> static inline _Tp __unary_minus(_Tp __x) noexcept
{
return static_cast<_Tp>(-__x);
}
template <class _Tp> static inline _Tp __plus(_Tp __x, _Tp __y)
{
return static_cast<_Tp>(__promote_preserving_unsigned(__x) +
__promote_preserving_unsigned(__y));
}
template <class _Tp> static inline _Tp __minus(_Tp __x, _Tp __y)
{
return static_cast<_Tp>(__promote_preserving_unsigned(__x) -
__promote_preserving_unsigned(__y));
}
template <class _Tp> static inline constexpr _Tp __multiplies(_Tp __x, _Tp __y)
{
return static_cast<_Tp>(__promote_preserving_unsigned(__x) *
__promote_preserving_unsigned(__y));
}
template <class _Tp> static inline _Tp __divides(_Tp __x, _Tp __y)
{
return static_cast<_Tp>(__promote_preserving_unsigned(__x) /
__promote_preserving_unsigned(__y));
}
template <class _Tp> static inline _Tp __modulus(_Tp __x, _Tp __y)
{
return static_cast<_Tp>(__promote_preserving_unsigned(__x) %
__promote_preserving_unsigned(__y));
}
template <class _Tp>
static inline _Tp __bit_and(_Tp __x, _Tp __y)
{
if constexpr (is_floating_point_v<_Tp>)
{
using _I = __int_for_sizeof_t<_Tp>;
const _I __r = reinterpret_cast<const __may_alias<_I>&>(__x) &
reinterpret_cast<const __may_alias<_I>&>(__y);
return reinterpret_cast<const __may_alias<_Tp>&>(__r);
}
else
{
return static_cast<_Tp>(__promote_preserving_unsigned(__x) &
__promote_preserving_unsigned(__y));
}
}
template <class _Tp>
static inline _Tp __bit_or(_Tp __x, _Tp __y)
{
if constexpr (is_floating_point_v<_Tp>)
{
using _I = __int_for_sizeof_t<_Tp>;
const _I __r = reinterpret_cast<const __may_alias<_I>&>(__x) |
reinterpret_cast<const __may_alias<_I>&>(__y);
return reinterpret_cast<const __may_alias<_Tp>&>(__r);
}
else
{
return static_cast<_Tp>(__promote_preserving_unsigned(__x) |
__promote_preserving_unsigned(__y));
}
}
template <class _Tp>
static inline _Tp __bit_xor(_Tp __x, _Tp __y)
{
if constexpr (is_floating_point_v<_Tp>)
{
using _I = __int_for_sizeof_t<_Tp>;
const _I __r = reinterpret_cast<const __may_alias<_I>&>(__x) ^
reinterpret_cast<const __may_alias<_I>&>(__y);
return reinterpret_cast<const __may_alias<_Tp>&>(__r);
}
else
{
return static_cast<_Tp>(__promote_preserving_unsigned(__x) ^
__promote_preserving_unsigned(__y));
}
}
template <class _Tp> static inline _Tp __bit_shift_left(_Tp __x, int __y)
{
return static_cast<_Tp>(__promote_preserving_unsigned(__x) << __y);
}
template <class _Tp> static inline _Tp __bit_shift_right(_Tp __x, int __y)
{
return static_cast<_Tp>(__promote_preserving_unsigned(__x) >> __y);
}
template <class _Tp> _GLIBCXX_SIMD_INTRINSIC static _Tp __abs(_Tp __x) { return _Tp(std::abs(__x)); }
template <class _Tp> _GLIBCXX_SIMD_INTRINSIC static _Tp __sqrt(_Tp __x) { return std::sqrt(__x); }
template <class _Tp> _GLIBCXX_SIMD_INTRINSIC static _Tp __trunc(_Tp __x) { return std::trunc(__x); }
template <class _Tp> _GLIBCXX_SIMD_INTRINSIC static _Tp __floor(_Tp __x) { return std::floor(__x); }
template <class _Tp> _GLIBCXX_SIMD_INTRINSIC static _Tp __ceil(_Tp __x) { return std::ceil(__x); }
template <typename _Tp>
_GLIBCXX_SIMD_INTRINSIC static _Tp
__remquo(_Tp __x, _Tp __y, _SimdTuple<int, simd_abi::_ScalarAbi>* __z)
{
return std::remquo(__x, __y, &__z->first);
}
template <typename _Tp>
_GLIBCXX_SIMD_INTRINSIC static _Tp __remquo(_Tp __x, _Tp __y, int* __z)
{
return std::remquo(__x, __y, __z);
}
template <class _Tp> _GLIBCXX_SIMD_INTRINSIC static _SimdTuple<int, abi_type> __fpclassify(_Tp __x)
{
return {std::fpclassify(__x)};
}
template <class _Tp> _GLIBCXX_SIMD_INTRINSIC static bool __isfinite(_Tp __x) { return std::isfinite(__x); }
template <class _Tp> _GLIBCXX_SIMD_INTRINSIC static bool __isinf(_Tp __x) { return std::isinf(__x); }
template <class _Tp> _GLIBCXX_SIMD_INTRINSIC static bool __isnan(_Tp __x) { return std::isnan(__x); }
template <class _Tp> _GLIBCXX_SIMD_INTRINSIC static bool __isnormal(_Tp __x) { return std::isnormal(__x); }
template <class _Tp> _GLIBCXX_SIMD_INTRINSIC static bool __signbit(_Tp __x) { return std::signbit(__x); }
template <class _Tp> _GLIBCXX_SIMD_INTRINSIC static bool __isunordered(_Tp __x, _Tp __y) { return std::isunordered(__x, __y); }
template <class _Tp> static inline void __increment(_Tp &__x) { ++__x; }
template <class _Tp> static inline void __decrement(_Tp &__x) { --__x; }
template <class _Tp> static bool __equal_to(_Tp __x, _Tp __y) { return __x == __y; }
template <class _Tp> static bool __not_equal_to(_Tp __x, _Tp __y) { return __x != __y; }
template <class _Tp> static bool __less(_Tp __x, _Tp __y) { return __x < __y; }
template <class _Tp> static bool __less_equal(_Tp __x, _Tp __y) { return __x <= __y; }
template <class _Tp, class _U> static void __set(_Tp &__v, int __i, _U &&__x) noexcept
{
_GLIBCXX_DEBUG_ASSERT(__i == 0);
__unused(__i);
__v = std::forward<_U>(__x);
}
template <typename _Tp> _GLIBCXX_SIMD_INTRINSIC static void __masked_assign(bool __k, _Tp &__lhs, _Tp __rhs)
{
if (__k) {
__lhs = __rhs;
}
}
template <template <typename> class _Op, typename _Tp>
_GLIBCXX_SIMD_INTRINSIC static void __masked_cassign(const bool __k, _Tp &__lhs, const _Tp __rhs)
{
if (__k) {
__lhs = _Op<_Tp>{}(__lhs, __rhs);
}
}
template <template <typename> class _Op, typename _Tp>
_GLIBCXX_SIMD_INTRINSIC static _Tp __masked_unary(const bool __k, const _Tp __v)
{
return static_cast<_Tp>(__k ? _Op<_Tp>{}(__v) : __v);
}
};
struct _MaskImplScalar {
template <class _Tp> using _TypeTag = _Tp *;
template <class _Tp>
_GLIBCXX_SIMD_INTRINSIC static bool __from_bitset(std::bitset<1> __bs, _TypeTag<_Tp>) noexcept
{
return __bs[0];
}
template <class _F>
_GLIBCXX_SIMD_INTRINSIC static bool __masked_load(bool __merge, bool __mask, const bool *__mem,
_F) noexcept
{
if (__mask) {
__merge = __mem[0];
}
return __merge;
}
template <class _F> _GLIBCXX_SIMD_INTRINSIC static void __store(bool __v, bool *__mem, _F) noexcept
{
__mem[0] = __v;
}
template <class _F>
_GLIBCXX_SIMD_INTRINSIC static void __masked_store(const bool __v, bool *__mem, _F,
const bool __k) noexcept
{
if (__k) {
__mem[0] = __v;
}
}
static constexpr bool __logical_and(bool __x, bool __y) { return __x && __y; }
static constexpr bool __logical_or(bool __x, bool __y) { return __x || __y; }
static constexpr bool __bit_and(bool __x, bool __y) { return __x && __y; }
static constexpr bool __bit_or(bool __x, bool __y) { return __x || __y; }
static constexpr bool __bit_xor(bool __x, bool __y) { return __x != __y; }
static void __set(bool &__k, int __i, bool __x) noexcept
{
_GLIBCXX_DEBUG_ASSERT(__i == 0);
__unused(__i);
__k = __x;
}
_GLIBCXX_SIMD_INTRINSIC static void __masked_assign(bool __k, bool &__lhs, bool __rhs)
{
if (__k) {
__lhs = __rhs;
}
}
};
template <class _Tp, size_t _N> constexpr bool __is_sse_ps()
{
return __have_sse && std::is_same_v<_Tp, float> && _N == 4;
}
template <class _Tp, size_t _N> constexpr bool __is_sse_pd()
{
return __have_sse2 && std::is_same_v<_Tp, double> && _N == 2;
}
template <class _Tp, size_t _N> constexpr bool __is_avx_ps()
{
return __have_avx && std::is_same_v<_Tp, float> && _N == 8;
}
template <class _Tp, size_t _N> constexpr bool __is_avx_pd()
{
return __have_avx && std::is_same_v<_Tp, double> && _N == 4;
}
template <class _Tp, size_t _N> constexpr bool __is_avx512_ps()
{
return __have_avx512f && std::is_same_v<_Tp, float> && _N == 16;
}
template <class _Tp, size_t _N> constexpr bool __is_avx512_pd()
{
return __have_avx512f && std::is_same_v<_Tp, double> && _N == 8;
}
template <class _Tp, size_t _N> constexpr bool __is_neon_ps()
{
return __have_neon && std::is_same_v<_Tp, float> && _N == 4;
}
template <class _Tp, size_t _N> constexpr bool __is_neon_pd()
{
return __have_neon && std::is_same_v<_Tp, double> && _N == 2;
}
template <class _Abi> struct _SimdImplBuiltin : _SimdMathFallback<_Abi> {
using abi_type = _Abi;
template <class _Tp> using _TypeTag = _Tp *;
template <class _Tp>
using _SimdMember = typename _Abi::template __traits<_Tp>::_SimdMember;
template <class _Tp>
using _MaskMember = typename _Abi::template __traits<_Tp>::_MaskMember;
template <class _Tp> static constexpr size_t _S_full_size = _SimdMember<_Tp>::_S_width;
using _SuperImpl = typename _Abi::_SimdImpl;
template <class _Tp, size_t _N>
_GLIBCXX_SIMD_INTRINSIC static simd<_Tp, _Abi> __make_simd(_SimdWrapper<_Tp, _N> __x)
{
return {__private_init, __x};
}
template <class _Tp, size_t _N>
_GLIBCXX_SIMD_INTRINSIC static simd<_Tp, _Abi> __make_simd(__intrinsic_type_t<_Tp, _N> __x)
{
return {__private_init, __vector_bitcast<_Tp>(__x)};
}
template <class _Tp>
_GLIBCXX_SIMD_INTRINSIC static constexpr _SimdMember<_Tp> __broadcast(_Tp __x) noexcept
{
return __vector_broadcast<_S_full_size<_Tp>>(__x);
}
template <class _F, class _Tp>
inline static constexpr _SimdMember<_Tp>
__generator(_F&& __gen, _TypeTag<_Tp>)
{
return __generate_wrapper<_Tp, _S_full_size<_Tp>>(std::forward<_F>(__gen));
}
template <class _Tp, class _U, class _F>
_GLIBCXX_SIMD_INTRINSIC static _SimdMember<_Tp> __load(const _U *__mem, _F,
_TypeTag<_Tp>) _GLIBCXX_SIMD_NOEXCEPT_OR_IN_TEST
{
constexpr size_t _N = _SimdMember<_Tp>::_S_width;
constexpr size_t __max_load_size =
(sizeof(_U) >= 4 && __have_avx512f) || __have_avx512bw
? 64
: (std::is_floating_point_v<_U> && __have_avx) || __have_avx2 ? 32 : 16;
if constexpr (sizeof(_U) > 8) {
return __generate_wrapper<_Tp, _N>(
[&](auto __i) constexpr { return static_cast<_Tp>(__mem[__i]); });
} else if constexpr (std::is_same_v<_U, _Tp>) {
return __vector_load<_U, _N>(__mem, _F());
} else if constexpr (sizeof(_U) * _N < 16) {
return __convert<_SimdMember<_Tp>>(
__vector_load16<_U, sizeof(_U) * _N>(__mem, _F()));
} else if constexpr (sizeof(_U) * _N <= __max_load_size) {
return __convert<_SimdMember<_Tp>>(__vector_load<_U, _N>(__mem, _F()));
} else if constexpr (sizeof(_U) * _N == 2 * __max_load_size) {
return __convert<_SimdMember<_Tp>>(
__vector_load<_U, _N / 2>(__mem, _F()),
__vector_load<_U, _N / 2>(__mem + _N / 2, _F()));
} else if constexpr (sizeof(_U) * _N == 4 * __max_load_size) {
return __convert<_SimdMember<_Tp>>(
__vector_load<_U, _N / 4>(__mem, _F()),
__vector_load<_U, _N / 4>(__mem + 1 * _N / 4, _F()),
__vector_load<_U, _N / 4>(__mem + 2 * _N / 4, _F()),
__vector_load<_U, _N / 4>(__mem + 3 * _N / 4, _F()));
} else if constexpr (sizeof(_U) * _N == 8 * __max_load_size) {
return __convert<_SimdMember<_Tp>>(
__vector_load<_U, _N / 8>(__mem, _F()),
__vector_load<_U, _N / 8>(__mem + 1 * _N / 8, _F()),
__vector_load<_U, _N / 8>(__mem + 2 * _N / 8, _F()),
__vector_load<_U, _N / 8>(__mem + 3 * _N / 8, _F()),
__vector_load<_U, _N / 8>(__mem + 4 * _N / 8, _F()),
__vector_load<_U, _N / 8>(__mem + 5 * _N / 8, _F()),
__vector_load<_U, _N / 8>(__mem + 6 * _N / 8, _F()),
__vector_load<_U, _N / 8>(__mem + 7 * _N / 8, _F()));
} else {
__assert_unreachable<_Tp>();
}
}
template <class _Tp, size_t _N, class _U, class _F>
static inline _SimdWrapper<_Tp, _N> __masked_load(_SimdWrapper<_Tp, _N> __merge,
_MaskMember<_Tp> __k,
const _U *__mem,
_F) _GLIBCXX_SIMD_NOEXCEPT_OR_IN_TEST
{
__bit_iteration(__vector_to_bitset(__k._M_data).to_ullong(), [&](auto __i) {
__merge.__set(__i, static_cast<_Tp>(__mem[__i]));
});
return __merge;
}
template <class _Tp, class _U, class _F>
_GLIBCXX_SIMD_INTRINSIC static void __store(_SimdMember<_Tp> __v, _U *__mem, _F,
_TypeTag<_Tp>) _GLIBCXX_SIMD_NOEXCEPT_OR_IN_TEST
{
constexpr size_t _N = _SimdMember<_Tp>::_S_width;
constexpr size_t __max_store_size =
(sizeof(_U) >= 4 && __have_avx512f) || __have_avx512bw
? 64
: (std::is_floating_point_v<_U> && __have_avx) || __have_avx2 ? 32 : 16;
if constexpr (sizeof(_U) > 8) {
__execute_n_times<_N>([&](auto __i) constexpr { __mem[__i] = __v[__i]; });
} else if constexpr (std::is_same_v<_U, _Tp>) {
__vector_store(__v._M_data, __mem, _F());
} else if constexpr (sizeof(_U) * _N < 16) {
__vector_store<sizeof(_U) * _N>(__convert<__vector_type16_t<_U>>(__v),
__mem, _F());
} else if constexpr (sizeof(_U) * _N <= __max_store_size) {
__vector_store(__convert<__vector_type_t<_U, _N>>(__v), __mem, _F());
} else {
constexpr size_t __vsize = __max_store_size / sizeof(_U);
constexpr size_t __stores = _N / __vsize;
using _V = __vector_type_t<_U, __vsize>;
const std::array<_V, __stores> __converted = __convert_all<_V>(__v);
__execute_n_times<__stores>([&](auto __i) constexpr {
__vector_store(__converted[__i], __mem + __i * __vsize, _F());
});
}
}
template <class _Tp, size_t _N, class _U, class _F>
static inline void __masked_store(const _SimdWrapper<_Tp, _N> __v, _U *__mem, _F,
const _MaskMember<_Tp> __k) _GLIBCXX_SIMD_NOEXCEPT_OR_IN_TEST
{
[[maybe_unused]] const auto __vi = __to_intrin(__v);
constexpr size_t __max_store_size =
(sizeof(_U) >= 4 && __have_avx512f) || __have_avx512bw
? 64
: (std::is_floating_point_v<_U> && __have_avx) || __have_avx2 ? 32 : 16;
if constexpr (std::is_same_v<_Tp, _U> ||
(std::is_integral_v<_Tp> && std::is_integral_v<_U> &&
sizeof(_Tp) == sizeof(_U))) {
const auto __kk = [&]() {
if constexpr (__is_bitmask_v<decltype(__k)>) {
return _MaskMember<_U>(__k._M_data);
} else {
return __wrapper_bitcast<_U>(__k);
}
}();
__maskstore(__wrapper_bitcast<_U>(__v), __mem, _F(), __kk);
} else if constexpr (sizeof(_U) <= 8 &&
!__converts_via_decomposition_v<
_Tp, _U, __max_store_size>
) {
using _VV = _SimdWrapper<_U, std::clamp(_N, 16 / sizeof(_U), __max_store_size / sizeof(_U))>;
using _V = typename _VV::_BuiltinType;
constexpr bool __prefer_bitmask =
(__have_avx512f && sizeof(_U) >= 4) || __have_avx512bw;
using _M = _SimdWrapper<std::conditional_t<__prefer_bitmask, bool, _U>, _VV::_S_width>;
constexpr size_t _VN = _VectorTraits<_V>::_S_width;
if constexpr (_VN >= _N) {
__maskstore(_VV(__convert<_V>(__v)), __mem,
std::conditional_t<(_VectorTraits<_V>::_S_width > _N),
overaligned_tag<sizeof(_U) * _N>, _F>(),
__convert_mask<_M>(__k));
} else if constexpr (_VN * 2 == _N) {
const std::array<_V, 2> converted = __convert_all<_V>(__v);
__maskstore(_VV(converted[0]), __mem, _F(), __convert_mask<_M>(__extract_part<0, 2>(__k)));
__maskstore(_VV(converted[1]), __mem + _VV::_S_width, _F(), __convert_mask<_M>(__extract_part<1, 2>(__k)));
} else if constexpr (_VN * 4 == _N) {
const std::array<_V, 4> converted = __convert_all<_V>(__v);
__maskstore(_VV(converted[0]), __mem, _F(), __convert_mask<_M>(__extract_part<0, 4>(__k)));
__maskstore(_VV(converted[1]), __mem + 1 * _VV::_S_width, _F(), __convert_mask<_M>(__extract_part<1, 4>(__k)));
__maskstore(_VV(converted[2]), __mem + 2 * _VV::_S_width, _F(), __convert_mask<_M>(__extract_part<2, 4>(__k)));
__maskstore(_VV(converted[3]), __mem + 3 * _VV::_S_width, _F(), __convert_mask<_M>(__extract_part<3, 4>(__k)));
} else if constexpr (_VN * 8 == _N) {
const std::array<_V, 8> converted = __convert_all<_V>(__v);
__maskstore(_VV(converted[0]), __mem, _F(), __convert_mask<_M>(__extract_part<0, 8>(__k)));
__maskstore(_VV(converted[1]), __mem + 1 * _VV::_S_width, _F(), __convert_mask<_M>(__extract_part<1, 8>(__k)));
__maskstore(_VV(converted[2]), __mem + 2 * _VV::_S_width, _F(), __convert_mask<_M>(__extract_part<2, 8>(__k)));
__maskstore(_VV(converted[3]), __mem + 3 * _VV::_S_width, _F(), __convert_mask<_M>(__extract_part<3, 8>(__k)));
__maskstore(_VV(converted[4]), __mem + 4 * _VV::_S_width, _F(), __convert_mask<_M>(__extract_part<4, 8>(__k)));
__maskstore(_VV(converted[5]), __mem + 5 * _VV::_S_width, _F(), __convert_mask<_M>(__extract_part<5, 8>(__k)));
__maskstore(_VV(converted[6]), __mem + 6 * _VV::_S_width, _F(), __convert_mask<_M>(__extract_part<6, 8>(__k)));
__maskstore(_VV(converted[7]), __mem + 7 * _VV::_S_width, _F(), __convert_mask<_M>(__extract_part<7, 8>(__k)));
} else {
__assert_unreachable<_Tp>();
}
} else {
__bit_iteration(__vector_to_bitset(__k._M_data).to_ullong(),
[&](auto __i) constexpr { __mem[__i] = static_cast<_U>(__v[__i]); });
}
}
template <class _Tp, size_t _N>
_GLIBCXX_SIMD_INTRINSIC static constexpr _SimdWrapper<_Tp, _N> __complement(_SimdWrapper<_Tp, _N> __x) noexcept
{
return ~__x._M_data;
}
template <class _Tp, size_t _N>
_GLIBCXX_SIMD_INTRINSIC static constexpr _SimdWrapper<_Tp, _N> __unary_minus(_SimdWrapper<_Tp, _N> __x) noexcept
{
return -__x._M_data;
}
template <class _Tp, size_t _N>
_GLIBCXX_SIMD_INTRINSIC static constexpr _SimdWrapper<_Tp, _N> __plus(_SimdWrapper<_Tp, _N> __x,
_SimdWrapper<_Tp, _N> __y)
{
return __x._M_data + __y._M_data;
}
template <class _Tp, size_t _N>
_GLIBCXX_SIMD_INTRINSIC static constexpr _SimdWrapper<_Tp, _N> __minus(_SimdWrapper<_Tp, _N> __x,
_SimdWrapper<_Tp, _N> __y)
{
return __x._M_data - __y._M_data;
}
template <class _Tp, size_t _N>
_GLIBCXX_SIMD_INTRINSIC static constexpr _SimdWrapper<_Tp, _N> __multiplies(
_SimdWrapper<_Tp, _N> __x, _SimdWrapper<_Tp, _N> __y)
{
return __x._M_data * __y._M_data;
}
template <class _Tp, size_t _N>
_GLIBCXX_SIMD_INTRINSIC static constexpr _SimdWrapper<_Tp, _N> __divides(
_SimdWrapper<_Tp, _N> __x, _SimdWrapper<_Tp, _N> __y)
{
return __x._M_data / __y._M_data;
}
template <class _Tp, size_t _N>
_GLIBCXX_SIMD_INTRINSIC static constexpr _SimdWrapper<_Tp, _N> __modulus(_SimdWrapper<_Tp, _N> __x, _SimdWrapper<_Tp, _N> __y)
{
static_assert(std::is_integral<_Tp>::value, "modulus is only supported for integral types");
return __x._M_data % __y._M_data;
}
template <class _Tp, size_t _N>
_GLIBCXX_SIMD_INTRINSIC static constexpr _SimdWrapper<_Tp, _N> __bit_and(_SimdWrapper<_Tp, _N> __x, _SimdWrapper<_Tp, _N> __y)
{
return __and(__x._M_data, __y._M_data);
}
template <class _Tp, size_t _N>
_GLIBCXX_SIMD_INTRINSIC static constexpr _SimdWrapper<_Tp, _N> __bit_or(_SimdWrapper<_Tp, _N> __x, _SimdWrapper<_Tp, _N> __y)
{
return __or(__x._M_data, __y._M_data);
}
template <class _Tp, size_t _N>
_GLIBCXX_SIMD_INTRINSIC static constexpr _SimdWrapper<_Tp, _N> __bit_xor(_SimdWrapper<_Tp, _N> __x, _SimdWrapper<_Tp, _N> __y)
{
return __xor(__x._M_data, __y._M_data);
}
template <class _Tp, size_t _N>
_GLIBCXX_SIMD_INTRINSIC static _SimdWrapper<_Tp, _N> __bit_shift_left(_SimdWrapper<_Tp, _N> __x, _SimdWrapper<_Tp, _N> __y)
{
return __x._M_data << __y._M_data;
}
template <class _Tp, size_t _N>
_GLIBCXX_SIMD_INTRINSIC static _SimdWrapper<_Tp, _N> __bit_shift_right(_SimdWrapper<_Tp, _N> __x, _SimdWrapper<_Tp, _N> __y)
{
return __x._M_data >> __y._M_data;
}
template <class _Tp, size_t _N>
_GLIBCXX_SIMD_INTRINSIC static constexpr _SimdWrapper<_Tp, _N> __bit_shift_left(_SimdWrapper<_Tp, _N> __x, int __y)
{
return __x._M_data << __y;
}
template <class _Tp, size_t _N>
_GLIBCXX_SIMD_INTRINSIC static constexpr _SimdWrapper<_Tp, _N> __bit_shift_right(_SimdWrapper<_Tp, _N> __x,
int __y)
{
return __x._M_data >> __y;
}
template <class _Tp, size_t _N>
_GLIBCXX_SIMD_INTRINSIC static constexpr _MaskMember<_Tp> __equal_to(
_SimdWrapper<_Tp, _N> __x, _SimdWrapper<_Tp, _N> __y)
{
return _ToWrapper(__x._M_data == __y._M_data);
}
template <class _Tp, size_t _N>
_GLIBCXX_SIMD_INTRINSIC static constexpr _MaskMember<_Tp> __not_equal_to(
_SimdWrapper<_Tp, _N> __x, _SimdWrapper<_Tp, _N> __y)
{
return _ToWrapper(__x._M_data != __y._M_data);
}
template <class _Tp, size_t _N>
_GLIBCXX_SIMD_INTRINSIC static constexpr _MaskMember<_Tp> __less(_SimdWrapper<_Tp, _N> __x,
_SimdWrapper<_Tp, _N> __y)
{
return _ToWrapper(__x._M_data < __y._M_data);
}
template <class _Tp, size_t _N>
_GLIBCXX_SIMD_INTRINSIC static constexpr _MaskMember<_Tp> __less_equal(_SimdWrapper<_Tp, _N> __x,
_SimdWrapper<_Tp, _N> __y)
{
return _ToWrapper(__x._M_data <= __y._M_data);
}
template <class _Tp, size_t _N>
_GLIBCXX_SIMD_INTRINSIC static constexpr _MaskMember<_Tp> __negate(_SimdWrapper<_Tp, _N> __x) noexcept
{
return _ToWrapper(!__x._M_data);
}
template <class _Tp, size_t _N>
_GLIBCXX_SIMD_NORMAL_MATH _GLIBCXX_SIMD_INTRINSIC static constexpr _SimdWrapper<_Tp, _N> __min(_SimdWrapper<_Tp, _N> __a,
_SimdWrapper<_Tp, _N> __b)
{
return __a._M_data < __b._M_data ? __a._M_data : __b._M_data;
}
template <class _Tp, size_t _N>
_GLIBCXX_SIMD_NORMAL_MATH _GLIBCXX_SIMD_INTRINSIC static constexpr _SimdWrapper<_Tp, _N> __max(_SimdWrapper<_Tp, _N> __a,
_SimdWrapper<_Tp, _N> __b)
{
return __a._M_data > __b._M_data ? __a._M_data : __b._M_data;
}
template <class _Tp, size_t _N>
_GLIBCXX_SIMD_NORMAL_MATH _GLIBCXX_SIMD_INTRINSIC static constexpr std::pair<_SimdWrapper<_Tp, _N>, _SimdWrapper<_Tp, _N>>
__minmax(_SimdWrapper<_Tp, _N> __a, _SimdWrapper<_Tp, _N> __b)
{
return {__a._M_data < __b._M_data ? __a._M_data : __b._M_data, __a._M_data < __b._M_data ? __b._M_data : __a._M_data};
}
template <class _Tp, class _BinaryOperation>
_GLIBCXX_SIMD_INTRINSIC static _Tp
__reduce(simd<_Tp, _Abi> __x, _BinaryOperation&& __binary_op)
{
constexpr size_t _N = simd_size_v<_Tp, _Abi>;
if constexpr (sizeof(__x) > __min_vector_size && _N > 2)
{
using _A = simd_abi::deduce_t<_Tp, _N / 2>;
using _V = std::experimental::simd<_Tp, _A>;
return _A::_SimdImpl::__reduce(
__binary_op(
_V(__private_init, __extract<0, 2>(__data(__x)._M_data)),
_V(__private_init, __extract<1, 2>(__data(__x)._M_data))),
std::forward<_BinaryOperation>(__binary_op));
}
#if _GLIBCXX_SIMD_HAVE_NEON
else if constexpr (sizeof(__x) == 8 || sizeof(__x) == 16)
{
static_assert(_N <= 8);
if constexpr (_N == 8)
{
__x = __binary_op(
__x, __make_simd<_Tp, _N>(
__vector_permute<1, 0, 3, 2, 5, 4, 7, 6>(__x._M_data)));
__x = __binary_op(
__x, __make_simd<_Tp, _N>(
__vector_permute<3, 2, 1, 0, 7, 6, 5, 4>(__x._M_data)));
__x = __binary_op(
__x, __make_simd<_Tp, _N>(
__vector_permute<7, 6, 5, 4, 3, 2, 1, 0>(__x._M_data)));
return __x[0];
}
else if constexpr (_N == 4)
{
__x = __binary_op(
__x, __make_simd<_Tp, _N>(
__vector_permute<1, 0, 3, 2>(__x._M_data)));
__x = __binary_op(
__x, __make_simd<_Tp, _N>(
__vector_permute<3, 2, 1, 0>(__x._M_data)));
return __x[0];
}
else
{
static_assert(_N == 2);
__x = __binary_op(
__x, __make_simd<_Tp, _N>(__vector_permute<1, 0>(__x._M_data)));
return __x[0];
}
}
#endif
else if constexpr (sizeof(__x) == 16)
{
if constexpr (_N == 16)
{
const auto __y = __x._M_data;
__x = __binary_op(
__make_simd<_Tp, _N>(__vector_permute<0, 0, 1, 1, 2, 2, 3, 3, 4,
4, 5, 5, 6, 6, 7, 7>(__y)),
__make_simd<_Tp, _N>(
__vector_permute<8, 8, 9, 9, 10, 10, 11, 11, 12, 12, 13, 13,
14, 14, 15, 15>(__y)));
}
if constexpr (_N >= 8)
{
const auto __y = __vector_bitcast<short>(__x._M_data);
__x =
__binary_op(__make_simd<_Tp, _N>(__vector_bitcast<_Tp>(
__vector_permute<0, 0, 1, 1, 2, 2, 3, 3>(__y))),
__make_simd<_Tp, _N>(__vector_bitcast<_Tp>(
__vector_permute<4, 4, 5, 5, 6, 6, 7, 7>(__y))));
}
if constexpr (_N >= 4)
{
using _U =
std::conditional_t<std::is_floating_point_v<_Tp>, float, int>;
const auto __y = __vector_bitcast<_U>(__x._M_data);
__x = __binary_op(__x, __make_simd<_Tp, _N>(__vector_bitcast<_Tp>(
__vector_permute<3, 2, 1, 0>(__y))));
}
using _U =
std::conditional_t<std::is_floating_point_v<_Tp>, double, _LLong>;
const auto __y = __vector_bitcast<_U>(__x._M_data);
__x = __binary_op(__x, __make_simd<_Tp, _N>(__vector_bitcast<_Tp>(
__vector_permute<1, 1>(__y))));
return __x[0];
}
else
__assert_unreachable<_Tp>();
}
template <class _Tp, size_t _N>
_GLIBCXX_SIMD_INTRINSIC static _SimdWrapper<_Tp, _N>
__abs(_SimdWrapper<_Tp, _N> __x) noexcept
{
if constexpr (std::is_floating_point_v<_Tp>)
return __and(_S_absmask<__vector_type_t<_Tp, _N>>, __x._M_data);
else
return __x._M_data < 0 ? -__x._M_data : __x._M_data;
}
template <typename _Tp, typename _TVT = _VectorTraits<_Tp>>
_GLIBCXX_SIMD_INTRINSIC static _Tp __nearbyint(_Tp __x_) noexcept
{
using value_type = typename _TVT::value_type;
using _V = typename _TVT::type;
const _V __x = __x_;
const _V __absx = __and(__x, _S_absmask<_V>);
static_assert(CHAR_BIT * sizeof(1ull) >=
std::numeric_limits<value_type>::digits);
constexpr _V __shifter_abs =
_V() + (1ull << (std::numeric_limits<value_type>::digits - 1));
const _V __shifter = __or(__and(_S_signmask<_V>, __x), __shifter_abs);
_V __shifted = __x + __shifter;
__shifted -= __shifter;
return __absx < __shifter_abs ? __shifted : __x;
}
template <typename _Tp, typename _TVT = _VectorTraits<_Tp>>
_GLIBCXX_SIMD_INTRINSIC static _Tp __rint(_Tp __x) noexcept
{
return _SuperImpl::__nearbyint(__x);
}
template <class _Tp, size_t _N>
_GLIBCXX_SIMD_INTRINSIC static _SimdWrapper<_Tp, _N>
__trunc(_SimdWrapper<_Tp, _N> __x)
{
using _V = __vector_type_t<_Tp, _N>;
const _V __absx = __and(__x._M_data, _S_absmask<_V>);
static_assert(CHAR_BIT * sizeof(1ull) >=
std::numeric_limits<_Tp>::digits);
constexpr _Tp __shifter = 1ull << (std::numeric_limits<_Tp>::digits - 1);
_V __truncated = (__absx + __shifter) - __shifter;
__truncated -= __truncated > __absx ? _V() + 1 : _V();
return __absx < __shifter ? __or(__xor(__absx, __x._M_data), __truncated)
: __x._M_data;
}
template <class _Tp, size_t _N>
_GLIBCXX_SIMD_INTRINSIC static _SimdWrapper<_Tp, _N>
__round(_SimdWrapper<_Tp, _N> __x)
{
using _V = __vector_type_t<_Tp, _N>;
const _V __absx = __and(__x._M_data, _S_absmask<_V>);
static_assert(CHAR_BIT * sizeof(1ull) >=
std::numeric_limits<_Tp>::digits);
constexpr _Tp __shifter = 1ull << (std::numeric_limits<_Tp>::digits - 1);
_V __truncated = (__absx + __shifter) - __shifter;
__truncated -= __truncated > __absx ? _V() + 1 : _V();
const _V __rounded =
__or(__xor(__absx, __x._M_data),
__truncated + (__absx - __truncated >= _Tp(.5) ? _V() + 1 : _V()));
return __absx < __shifter ? __rounded : __x._M_data;
}
template <class _Tp, size_t _N>
_GLIBCXX_SIMD_INTRINSIC static _SimdWrapper<_Tp, _N> __floor(_SimdWrapper<_Tp, _N> __x)
{
const auto __y = _SuperImpl::__trunc(__x)._M_data;
const auto __negative_input = __vector_bitcast<_Tp>(__x._M_data < __vector_broadcast<_N, _Tp>(0));
const auto __mask = __andnot(__vector_bitcast<_Tp>(__y == __x._M_data), __negative_input);
return __or(__andnot(__mask, __y), __and(__mask, __y - __vector_broadcast<_N, _Tp>(1)));
}
template <class _Tp, size_t _N> _GLIBCXX_SIMD_INTRINSIC static _SimdWrapper<_Tp, _N> __ceil(_SimdWrapper<_Tp, _N> __x)
{
const auto __y = _SuperImpl::__trunc(__x)._M_data;
const auto __negative_input = __vector_bitcast<_Tp>(__x._M_data < __vector_broadcast<_N, _Tp>(0));
const auto __inv_mask = __or(__vector_bitcast<_Tp>(__y == __x._M_data), __negative_input);
return __or(__and(__inv_mask, __y),
__andnot(__inv_mask, __y + __vector_broadcast<_N, _Tp>(1)));
}
template <class _Tp, size_t _N>
_GLIBCXX_SIMD_INTRINSIC static _MaskMember<_Tp> __isnan(_SimdWrapper<_Tp, _N> __x)
{
#if __FINITE_MATH_ONLY__
__unused(__x);
return {};
#else
return __cmpunord(__x._M_data, __x._M_data);
#endif
}
template <class _Tp, size_t _N>
_GLIBCXX_SIMD_INTRINSIC static _MaskMember<_Tp> __isfinite(_SimdWrapper<_Tp, _N> __x)
{
#if __FINITE_MATH_ONLY__
__unused(__x);
return __vector_bitcast<_N>(_Tp()) == __vector_bitcast<_N>(_Tp());
#else
using _I = __int_for_sizeof_t<_Tp>;
const auto __inf = __vector_bitcast<_I>(
__vector_broadcast<_N>(std::numeric_limits<_Tp>::infinity()));
return __vector_bitcast<_Tp>(__inf >
(__vector_bitcast<_I>(__x) & __inf));
#endif
}
template <class _Tp, size_t _N>
_GLIBCXX_SIMD_INTRINSIC static _MaskMember<_Tp> __isunordered(_SimdWrapper<_Tp, _N> __x,
_SimdWrapper<_Tp, _N> __y)
{
return __cmpunord(__x._M_data, __y._M_data);
}
template <class _Tp, size_t _N>
_GLIBCXX_SIMD_INTRINSIC static _MaskMember<_Tp> __signbit(_SimdWrapper<_Tp, _N> __x)
{
using _I = __int_for_sizeof_t<_Tp>;
const auto __xx = __vector_bitcast<_I>(__x._M_data);
return __vector_bitcast<_Tp>(__xx >> std::numeric_limits<_I>::digits);
}
template <class _Tp, size_t _N>
_GLIBCXX_SIMD_INTRINSIC static _MaskMember<_Tp> __isinf(_SimdWrapper<_Tp, _N> __x)
{
#if __FINITE_MATH_ONLY__
__unused(__x);
return {};
#else
return _SuperImpl::template __equal_to<_Tp, _N>(
_SuperImpl::__abs(__x),
__vector_broadcast<_N>(std::numeric_limits<_Tp>::infinity()));
#endif
}
template <class _Tp, size_t _N>
_GLIBCXX_SIMD_INTRINSIC static _MaskMember<_Tp>
__isnormal(_SimdWrapper<_Tp, _N> __x)
{
#if __FINITE_MATH_ONLY__
return _SuperImpl::template __less_equal<_Tp, _N>(
__vector_broadcast<_N>(std::numeric_limits<_Tp>::min()), _SuperImpl::__abs(__x));
#else
return __and(
_SuperImpl::template __less_equal<_Tp, _N>(
__vector_broadcast<_N>(std::numeric_limits<_Tp>::min()), _SuperImpl::__abs(__x)),
_SuperImpl::template __less<_Tp, _N>(
_SuperImpl::__abs(__x),
__vector_broadcast<_N>(std::numeric_limits<_Tp>::infinity())));
#endif
}
template <class _Tp, size_t _N>
_GLIBCXX_SIMD_INTRINSIC static __fixed_size_storage_t<int, _N> __fpclassify(_SimdWrapper<_Tp, _N> __x)
{
constexpr auto __fp_normal = __vector_bitcast<_Tp>(
__vector_broadcast<_N, __int_for_sizeof_t<_Tp>>(FP_NORMAL));
constexpr auto __fp_nan = __vector_bitcast<_Tp>(
__vector_broadcast<_N, __int_for_sizeof_t<_Tp>>(FP_NAN));
constexpr auto __fp_infinite = __vector_bitcast<_Tp>(
__vector_broadcast<_N, __int_for_sizeof_t<_Tp>>(FP_INFINITE));
constexpr auto __fp_subnormal = __vector_bitcast<_Tp>(
__vector_broadcast<_N, __int_for_sizeof_t<_Tp>>(FP_SUBNORMAL));
constexpr auto __fp_zero = __vector_bitcast<_Tp>(
__vector_broadcast<_N, __int_for_sizeof_t<_Tp>>(FP_ZERO));
const auto __tmp = __vector_bitcast<_LLong>(
_SuperImpl::__abs(__x)._M_data < std::numeric_limits<_Tp>::min()
? (__x._M_data == 0 ? __fp_zero : __fp_subnormal)
: __blend(__isinf(__x)._M_data,
__blend(__isnan(__x)._M_data, __fp_normal, __fp_nan),
__fp_infinite));
if constexpr (sizeof(_Tp) == sizeof(int))
{
if constexpr (__fixed_size_storage_t<int, _N>::_S_tuple_size == 1)
{
return {__vector_bitcast<int>(__tmp)};
}
else if constexpr (__fixed_size_storage_t<int, _N>::_S_tuple_size == 2)
{
return {__extract<0, 2>(__vector_bitcast<int>(__tmp)),
__extract<1, 2>(__vector_bitcast<int>(__tmp))};
}
else
{
__assert_unreachable<_Tp>();
}
}
else if constexpr (_N == 2 && sizeof(_Tp) == 8 &&
__fixed_size_storage_t<int, _N>::_S_tuple_size == 2)
{
return {int(__tmp[0]), {int(__tmp[1])}};
}
else if constexpr (_N == 4 && sizeof(_Tp) == 8 &&
__fixed_size_storage_t<int, _N>::_S_tuple_size == 1)
{
#if _GLIBCXX_SIMD_X86INTRIN
return {_mm_packs_epi32(__lo128(__tmp), __hi128(__tmp))};
#else
return {__make_wrapper<int>(__tmp[0], __tmp[1], __tmp[2], __tmp[3])};
#endif
}
else if constexpr (_N == 2 && sizeof(_Tp) == 8 &&
__fixed_size_storage_t<int, _N>::_S_tuple_size == 1)
return {__make_wrapper<int>(__tmp[0], __tmp[1])};
else
{
__assert_unreachable<_Tp>();
}
}
template <class _Tp, size_t _N> _GLIBCXX_SIMD_INTRINSIC static void __increment(_SimdWrapper<_Tp, _N> &__x)
{
__x = __x._M_data + 1;
}
template <class _Tp, size_t _N> _GLIBCXX_SIMD_INTRINSIC static void __decrement(_SimdWrapper<_Tp, _N> &__x)
{
__x = __x._M_data - 1;
}
template <class _Tp, size_t _N, class _U>
_GLIBCXX_SIMD_INTRINSIC static void __set(_SimdWrapper<_Tp, _N> &__v, int __i, _U &&__x) noexcept
{
__v.__set(__i, std::forward<_U>(__x));
}
template <class _Tp, class _K, size_t _N>
_GLIBCXX_SIMD_INTRINSIC static void __masked_assign(_SimdWrapper<_K, _N> __k,
_SimdWrapper<_Tp, _N> &__lhs,
__id<_SimdWrapper<_Tp, _N>> __rhs)
{
__lhs = __blend(__k._M_data, __lhs._M_data, __rhs._M_data);
}
template <class _Tp, class _K, size_t _N>
_GLIBCXX_SIMD_INTRINSIC static void __masked_assign(_SimdWrapper<_K, _N> __k, _SimdWrapper<_Tp, _N> &__lhs,
__id<_Tp> __rhs)
{
if (__builtin_constant_p(__rhs) && __rhs == 0 && std::is_same<_K, _Tp>::value) {
if constexpr (!__is_bitmask(__k)) {
__lhs._M_data = __andnot(__k._M_data, __lhs._M_data);
return;
} else {
__lhs._M_data = __auto_bitcast(__blend(__k, __lhs, __intrinsic_type_t<_Tp, _N>()));
return;
}
}
__lhs._M_data = __blend(__k._M_data, __lhs._M_data, __vector_broadcast<_N>(__rhs));
}
template <template <typename> class _Op, class _Tp, class _K, size_t _N>
_GLIBCXX_SIMD_INTRINSIC static void __masked_cassign(const _SimdWrapper<_K, _N> __k, _SimdWrapper<_Tp, _N> &__lhs,
const __id<_SimdWrapper<_Tp, _N>> __rhs)
{
__lhs._M_data = __blend(__k._M_data, __lhs._M_data, _Op<void>{}(__lhs._M_data, __rhs._M_data));
}
template <template <typename> class _Op, class _Tp, class _K, size_t _N>
_GLIBCXX_SIMD_INTRINSIC static void __masked_cassign(const _SimdWrapper<_K, _N> __k, _SimdWrapper<_Tp, _N> &__lhs,
const __id<_Tp> __rhs)
{
__lhs._M_data = __blend(__k._M_data, __lhs._M_data, _Op<void>{}(__lhs._M_data, __vector_broadcast<_N>(__rhs)));
}
template <template <typename> class _Op, class _Tp, class _K, size_t _N>
_GLIBCXX_SIMD_INTRINSIC static _SimdWrapper<_Tp, _N> __masked_unary(const _SimdWrapper<_K, _N> __k,
const _SimdWrapper<_Tp, _N> __v)
{
auto __vv = __make_simd(__v);
_Op<decltype(__vv)> __op;
return __blend(__k, __v, __data(__op(__vv)));
}
};
template <class _Abi> struct _MaskImplBuiltin {
template <class _Tp> using _TypeTag = _Tp *;
template <class _Tp>
using _SimdMember = typename _Abi::template __traits<_Tp>::_SimdMember;
template <class _Tp>
using _MaskMember = typename _Abi::template __traits<_Tp>::_MaskMember;
template <class _Tp, size_t _N, class _F>
static inline _SimdWrapper<_Tp, _N> __masked_load(_SimdWrapper<_Tp, _N> __merge,
_SimdWrapper<_Tp, _N> __mask,
const bool* __mem,
_F) noexcept
{
auto __tmp = __wrapper_bitcast<__int_for_sizeof_t<_Tp>>(__merge);
__bit_iteration(__vector_to_bitset(__mask._M_data).to_ullong(),
[&](auto __i) { __tmp.__set(__i, -__mem[__i]); });
__merge = __wrapper_bitcast<_Tp>(__tmp);
return __merge;
}
template <class _Tp, size_t _N, class _F>
_GLIBCXX_SIMD_INTRINSIC static void __store(_SimdWrapper<_Tp, _N> __v, bool *__mem, _F) noexcept
{
__execute_n_times<_N>([&](auto __i) constexpr { __mem[__i] = __v[__i]; });
}
template <class _Tp, size_t _N, class _F>
static inline void __masked_store(const _SimdWrapper<_Tp, _N> __v, bool *__mem, _F,
const _SimdWrapper<_Tp, _N> __k) noexcept
{
__bit_iteration(__vector_to_bitset(__k._M_data).to_ullong(),
[&](auto __i) constexpr { __mem[__i] = __v[__i]; });
}
template <size_t _N, class _Tp>
_GLIBCXX_SIMD_INTRINSIC static _MaskMember<_Tp> __from_bitset(std::bitset<_N> __bits, _TypeTag<_Tp>)
{
return __convert_mask<typename _MaskMember<_Tp>::_BuiltinType>(__bits);
}
template <class _Tp, size_t _N>
_GLIBCXX_SIMD_INTRINSIC static constexpr _SimdWrapper<_Tp, _N>
__logical_and(const _SimdWrapper<_Tp, _N>& __x,
const _SimdWrapper<_Tp, _N>& __y)
{
return __and(__x._M_data, __y._M_data);
}
template <class _Tp, size_t _N>
_GLIBCXX_SIMD_INTRINSIC static constexpr _SimdWrapper<_Tp, _N>
__logical_or(const _SimdWrapper<_Tp, _N>& __x,
const _SimdWrapper<_Tp, _N>& __y)
{
return __or(__x._M_data, __y._M_data);
}
template <class _Tp, size_t _N>
_GLIBCXX_SIMD_INTRINSIC static constexpr _SimdWrapper<_Tp, _N>
__bit_and(const _SimdWrapper<_Tp, _N>& __x,
const _SimdWrapper<_Tp, _N>& __y)
{
return __and(__x._M_data, __y._M_data);
}
template <class _Tp, size_t _N>
_GLIBCXX_SIMD_INTRINSIC static constexpr _SimdWrapper<_Tp, _N>
__bit_or(const _SimdWrapper<_Tp, _N>& __x, const _SimdWrapper<_Tp, _N>& __y)
{
return __or(__x._M_data, __y._M_data);
}
template <class _Tp, size_t _N>
_GLIBCXX_SIMD_INTRINSIC static constexpr _SimdWrapper<_Tp, _N>
__bit_xor(const _SimdWrapper<_Tp, _N>& __x,
const _SimdWrapper<_Tp, _N>& __y)
{
return __xor(__x._M_data, __y._M_data);
}
template <class _Tp, size_t _N>
static void __set(_SimdWrapper<_Tp, _N>& __k, int __i, bool __x) noexcept
{
if constexpr (std::is_same_v<_Tp, bool>)
__k.__set(__i, __x);
else
__k._M_data[__i] = __bit_cast<_Tp>(__int_for_sizeof_t<_Tp>(-__x));
}
template <class _Tp, size_t _N>
_GLIBCXX_SIMD_INTRINSIC static void __masked_assign(_SimdWrapper<_Tp, _N> __k, _SimdWrapper<_Tp, _N> &__lhs,
__id<_SimdWrapper<_Tp, _N>> __rhs)
{
__lhs = __blend(__k._M_data, __lhs._M_data, __rhs._M_data);
}
template <class _Tp, size_t _N>
_GLIBCXX_SIMD_INTRINSIC static void __masked_assign(_SimdWrapper<_Tp, _N> __k, _SimdWrapper<_Tp, _N> &__lhs, bool __rhs)
{
if (__builtin_constant_p(__rhs)) {
if (__rhs == false) {
__lhs = __andnot(__k._M_data, __lhs._M_data);
} else {
__lhs = __or(__k._M_data, __lhs._M_data);
}
return;
}
__lhs = __blend(__k, __lhs, __data(simd_mask<_Tp, _Abi>(__rhs)));
}
};
#if _GLIBCXX_SIMD_X86INTRIN
template <class _Abi> struct __x86_simd_impl : _SimdImplBuiltin<_Abi> {
using _Base = _SimdImplBuiltin<_Abi>;
template <typename _Tp>
using _MaskMember = typename _Base::template _MaskMember<_Tp>;
template <class _Tp, size_t _N, class _U, class _F>
static inline _SimdWrapper<_Tp, _N>
__masked_load(_SimdWrapper<_Tp, _N> __merge,
_MaskMember<_Tp> __k,
const _U* __mem,
_F) _GLIBCXX_SIMD_NOEXCEPT_OR_IN_TEST
{
if constexpr (std::is_same_v<_Tp, _U> ||
(sizeof(_Tp) == sizeof(_U) &&
std::is_integral_v<_Tp> ==
std::is_integral_v<_U>)
)
{
[[maybe_unused]] const auto __intrin = __to_intrin(__merge);
constexpr bool __have_avx512bw_vl_or_zmm =
__have_avx512bw_vl || (__have_avx512bw && sizeof(__merge) == 64);
if constexpr (__have_avx512bw_vl_or_zmm && sizeof(_Tp) == 1)
{
if constexpr (sizeof(__merge) == 16)
{
__merge = __vector_bitcast<_Tp>(_mm_mask_loadu_epi8(
__intrin, _mm_movemask_epi8(__to_intrin(__k)), __mem));
}
else if constexpr (sizeof(__merge) == 32)
{
__merge = __vector_bitcast<_Tp>(_mm256_mask_loadu_epi8(
__intrin, _mm256_movemask_epi8(__to_intrin(__k)), __mem));
}
else if constexpr (sizeof(__merge) == 64)
{
__merge = __vector_bitcast<_Tp>(
_mm512_mask_loadu_epi8(__intrin, __k, __mem));
}
else
{
__assert_unreachable<_Tp>();
}
}
else if constexpr (__have_avx512bw_vl_or_zmm && sizeof(_Tp) == 2)
{
if constexpr (sizeof(__merge) == 16)
{
__merge = __vector_bitcast<_Tp>(_mm_mask_loadu_epi16(
__intrin, movemask_epi16(__to_intrin(__k)), __mem));
}
else if constexpr (sizeof(__merge) == 32)
{
__merge = __vector_bitcast<_Tp>(_mm256_mask_loadu_epi16(
__intrin, movemask_epi16(__to_intrin(__k)), __mem));
}
else if constexpr (sizeof(__merge) == 64)
{
__merge = __vector_bitcast<_Tp>(
_mm512_mask_loadu_epi16(__intrin, __k, __mem));
}
else
{
__assert_unreachable<_Tp>();
}
}
else if constexpr (__have_avx2 && sizeof(_Tp) == 4 &&
std::is_integral_v<_U>)
{
if constexpr (sizeof(__merge) == 16)
{
__merge =
(~__k._M_data & __merge._M_data) |
__vector_bitcast<_Tp>(_mm_maskload_epi32(
reinterpret_cast<const int*>(__mem), __to_intrin(__k)));
}
else if constexpr (sizeof(__merge) == 32)
{
__merge =
(~__k._M_data & __merge._M_data) |
__vector_bitcast<_Tp>(_mm256_maskload_epi32(
reinterpret_cast<const int*>(__mem), __to_intrin(__k)));
}
else if constexpr (__have_avx512f && sizeof(__merge) == 64)
{
__merge = __vector_bitcast<_Tp>(
_mm512_mask_loadu_epi32(__intrin, __k, __mem));
}
else
{
__assert_unreachable<_Tp>();
}
}
else if constexpr (__have_avx && sizeof(_Tp) == 4)
{
if constexpr (sizeof(__merge) == 16)
{
__merge = __or(__andnot(__k._M_data, __merge._M_data),
__vector_bitcast<_Tp>(_mm_maskload_ps(
reinterpret_cast<const float*>(__mem),
__vector_bitcast<_LLong>(__k))));
}
else if constexpr (sizeof(__merge) == 32)
{
__merge =
__or(__andnot(__k._M_data, __merge._M_data),
_mm256_maskload_ps(reinterpret_cast<const float*>(__mem),
__vector_bitcast<_LLong>(__k)));
}
else if constexpr (__have_avx512f && sizeof(__merge) == 64)
{
__merge = __vector_bitcast<_Tp>(
_mm512_mask_loadu_ps(__intrin, __k, __mem));
}
else
{
__assert_unreachable<_Tp>();
}
}
else if constexpr (__have_avx2 && sizeof(_Tp) == 8 &&
std::is_integral_v<_U>)
{
if constexpr (sizeof(__merge) == 16)
{
__merge =
(~__k._M_data & __merge._M_data) |
__vector_bitcast<_Tp>(_mm_maskload_epi64(
reinterpret_cast<const _LLong*>(__mem), __to_intrin(__k)));
}
else if constexpr (sizeof(__merge) == 32)
{
__merge =
(~__k._M_data & __merge._M_data) |
__vector_bitcast<_Tp>(_mm256_maskload_epi64(
reinterpret_cast<const _LLong*>(__mem), __to_intrin(__k)));
}
else if constexpr (__have_avx512f && sizeof(__merge) == 64)
{
__merge = __vector_bitcast<_Tp>(
_mm512_mask_loadu_epi64(__intrin, __k, __mem));
}
else
{
__assert_unreachable<_Tp>();
}
}
else if constexpr (__have_avx && sizeof(_Tp) == 8)
{
if constexpr (sizeof(__merge) == 16)
{
__merge = __or(__andnot(__k._M_data, __merge._M_data),
__vector_bitcast<_Tp>(_mm_maskload_pd(
reinterpret_cast<const double*>(__mem),
__vector_bitcast<_LLong>(__k))));
}
else if constexpr (sizeof(__merge) == 32)
{
__merge = __or(
__andnot(__k._M_data, __merge._M_data),
_mm256_maskload_pd(reinterpret_cast<const double*>(__mem),
__vector_bitcast<_LLong>(__k)));
}
else if constexpr (__have_avx512f && sizeof(__merge) == 64)
{
__merge = __vector_bitcast<_Tp>(
_mm512_mask_loadu_pd(__intrin, __k, __mem));
}
else
{
__assert_unreachable<_Tp>();
}
}
else
{
__bit_iteration(__vector_to_bitset(__k._M_data).to_ullong(),
[&](auto __i) {
__merge.__set(__i, static_cast<_Tp>(__mem[__i]));
});
}
}
else if constexpr (sizeof(_U) <= 8 &&
!__converts_via_decomposition_v<
_U, _Tp,
sizeof(__merge)>
)
{
using _A = simd_abi::deduce_t<
_U, std::max(_N, 16 / sizeof(_U))
>;
using _ATraits = _SimdTraits<_U, _A>;
using _AImpl = typename _ATraits::_SimdImpl;
typename _ATraits::_SimdMember __uncvted{};
typename _ATraits::_MaskMember __kk;
if constexpr (__is_fixed_size_abi_v<_A>)
{
__kk = __vector_to_bitset(__k._M_data);
}
else
{
__kk = __convert_mask<typename _ATraits::_MaskMember>(__k);
}
__uncvted = _AImpl::__masked_load(__uncvted, __kk, __mem, _F());
_SimdConverter<_U, _A, _Tp, _Abi> __converter;
_Base::__masked_assign(__k, __merge, __converter(__uncvted));
}
else
{
__bit_iteration(
__vector_to_bitset(__k._M_data).to_ullong(),
[&](auto __i) { __merge.__set(__i, static_cast<_Tp>(__mem[__i])); });
}
return __merge;
}
template <class _Tp, size_t _N, class _U, class _F>
static inline void __masked_store(const _SimdWrapper<_Tp, _N> __v, _U *__mem, _F,
const _MaskMember<_Tp> __k) _GLIBCXX_SIMD_NOEXCEPT_OR_IN_TEST
{
if constexpr (std::is_integral_v<_Tp> && std::is_integral_v<_U> &&
sizeof(_Tp) > sizeof(_U) && __have_avx512f &&
(sizeof(_Tp) >= 4 || __have_avx512bw) &&
(sizeof(__v) == 64 || __have_avx512vl)) {
[[maybe_unused]] const auto __vi = __to_intrin(__v);
const auto __kk = [&]() {
if constexpr (__is_bitmask_v<decltype(__k)>) {
return __k;
} else {
return __convert_mask<_SimdWrapper<bool, _N>>(__k);
}
}();
if constexpr (sizeof(_Tp) == 8 && sizeof(_U) == 4) {
if constexpr (sizeof(__vi) == 64) {
_mm512_mask_cvtepi64_storeu_epi32(__mem, __kk, __vi);
} else if constexpr (sizeof(__vi) == 32) {
_mm256_mask_cvtepi64_storeu_epi32(__mem, __kk, __vi);
} else if constexpr (sizeof(__vi) == 16) {
_mm_mask_cvtepi64_storeu_epi32(__mem, __kk, __vi);
}
} else if constexpr (sizeof(_Tp) == 8 && sizeof(_U) == 2) {
if constexpr (sizeof(__vi) == 64) {
_mm512_mask_cvtepi64_storeu_epi16(__mem, __kk, __vi);
} else if constexpr (sizeof(__vi) == 32) {
_mm256_mask_cvtepi64_storeu_epi16(__mem, __kk, __vi);
} else if constexpr (sizeof(__vi) == 16) {
_mm_mask_cvtepi64_storeu_epi16(__mem, __kk, __vi);
}
} else if constexpr (sizeof(_Tp) == 8 && sizeof(_U) == 1) {
if constexpr (sizeof(__vi) == 64) {
_mm512_mask_cvtepi64_storeu_epi8(__mem, __kk, __vi);
} else if constexpr (sizeof(__vi) == 32) {
_mm256_mask_cvtepi64_storeu_epi8(__mem, __kk, __vi);
} else if constexpr (sizeof(__vi) == 16) {
_mm_mask_cvtepi64_storeu_epi8(__mem, __kk, __vi);
}
} else if constexpr (sizeof(_Tp) == 4 && sizeof(_U) == 2) {
if constexpr (sizeof(__vi) == 64) {
_mm512_mask_cvtepi32_storeu_epi16(__mem, __kk, __vi);
} else if constexpr (sizeof(__vi) == 32) {
_mm256_mask_cvtepi32_storeu_epi16(__mem, __kk, __vi);
} else if constexpr (sizeof(__vi) == 16) {
_mm_mask_cvtepi32_storeu_epi16(__mem, __kk, __vi);
}
} else if constexpr (sizeof(_Tp) == 4 && sizeof(_U) == 1) {
if constexpr (sizeof(__vi) == 64) {
_mm512_mask_cvtepi32_storeu_epi8(__mem, __kk, __vi);
} else if constexpr (sizeof(__vi) == 32) {
_mm256_mask_cvtepi32_storeu_epi8(__mem, __kk, __vi);
} else if constexpr (sizeof(__vi) == 16) {
_mm_mask_cvtepi32_storeu_epi8(__mem, __kk, __vi);
}
} else if constexpr (sizeof(_Tp) == 2 && sizeof(_U) == 1) {
if constexpr (sizeof(__vi) == 64) {
_mm512_mask_cvtepi16_storeu_epi8(__mem, __kk, __vi);
} else if constexpr (sizeof(__vi) == 32) {
_mm256_mask_cvtepi16_storeu_epi8(__mem, __kk, __vi);
} else if constexpr (sizeof(__vi) == 16) {
_mm_mask_cvtepi16_storeu_epi8(__mem, __kk, __vi);
}
} else {
__assert_unreachable<_Tp>();
}
} else {
_Base::__masked_store(__v,__mem,_F(),__k);
}
}
template <typename _Tp, size_t _N>
_GLIBCXX_SIMD_INTRINSIC static constexpr _SimdWrapper<_Tp, _N>
__multiplies(_SimdWrapper<_Tp, _N> __x, _SimdWrapper<_Tp, _N> __y)
{
if (__builtin_is_constant_evaluated())
return __x._M_data * __y._M_data;
else if constexpr (sizeof(_Tp) == 1)
{
const auto __high_byte = __vector_broadcast<_N / 2, short>(-256);
const auto __even =
__vector_bitcast<short>(__x) * __vector_bitcast<short>(__y);
const auto __odd = (__vector_bitcast<short>(__x) >> 8) *
(__vector_bitcast<short>(__y) & __high_byte);
if constexpr (__have_avx512bw)
return __blend(0xaaaa'aaaa'aaaa'aaaaLL,
__vector_bitcast<_Tp>(__even),
__vector_bitcast<_Tp>(__odd));
else if constexpr (__have_sse4_1)
return __vector_bitcast<_Tp>(__blend(__high_byte, __even, __odd));
else
return __vector_bitcast<_Tp>(__andnot(__high_byte, __even) | __odd);
}
else
return _Base::__multiplies(__x, __y);
}
template <typename _Tp, size_t _N>
_GLIBCXX_SIMD_INTRINSIC static constexpr _SimdWrapper<_Tp, _N>
__divides(_SimdWrapper<_Tp, _N> __x, _SimdWrapper<_Tp, _N> __y)
{
if (__builtin_is_constant_evaluated())
return __x._M_data / __y._M_data;
else if constexpr (is_integral_v<_Tp> && sizeof(_Tp) <= 4)
{
using _FloatV = typename __vector_type<conditional_t<sizeof(_Tp) ==4, double, float>,
__have_avx512f ? 64 : __have_avx ? 32 : 16>::type;
const auto __xf = __convert_all<_FloatV>(__x);
const auto __yf = __convert_all<_FloatV>(__y);
using _R = __vector_type_t<_Tp, _N>;
if constexpr(__is_vector_type_v<remove_const_t<decltype(__xf)>>)
return __vector_convert<_R>(__xf / __yf);
else if constexpr(__xf.size() == 2)
return __vector_convert<_R>(__xf[0] / __yf[0], __xf[1] / __yf[1]);
else if constexpr(__xf.size() == 4)
return __vector_convert<_R>(__xf[0] / __yf[0], __xf[1] / __yf[1],
__xf[2] / __yf[2], __xf[3] / __yf[3]);
else
__assert_unreachable<_Tp>();
}
else
return _Base::__divides(__x, __y);
}
#ifndef _GLIBCXX_SIMD_NO_SHIFT_OPT
template <typename _Tp, typename _TVT = _VectorTraits<_Tp>>
inline _GLIBCXX_SIMD_CONST static typename _TVT::type
__bit_shift_left(_Tp __xx, int __y)
{
using _V = typename _TVT::type;
using _U = typename _TVT::value_type;
_V __x = __xx;
[[maybe_unused]] const auto __ix = __to_intrin(__x);
if (__builtin_is_constant_evaluated())
return __x << __y;
#if __cplusplus > 201703
else if constexpr (sizeof(_U) == 1 && is_signed_v<_U>)
return __vector_bitcast<_U>(
__bit_shift_left(__vector_bitcast<make_unsigned_t<_U>>(__x), __y));
#endif
else if constexpr (sizeof(_U) == 1)
{
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
const _UChar __mask = 0xff << __y;
return __vector_bitcast<_U>(
__vector_bitcast<_UChar>(__vector_bitcast<unsigned>(__x)
<< __y) &
__mask);
}
else if (__y >= 8 && __y < 32)
return _V();
else
__builtin_unreachable();
}
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
return __vector_bitcast<_U>(_mm_sll_epi16(__ix, __shift) & __k);
}
}
return __x << __y;
}
template <typename _Tp, typename _TVT = _VectorTraits<_Tp>>
inline _GLIBCXX_SIMD_CONST static typename _TVT::type
__bit_shift_left(_Tp __xx, typename _TVT::type __y)
{
using _V = typename _TVT::type;
using _U = typename _TVT::value_type;
_V __x = __xx;
[[maybe_unused]] const auto __ix = __to_intrin(__x);
[[maybe_unused]] const auto __iy = __to_intrin(__y);
if (__builtin_is_constant_evaluated())
return __x << __y;
#if __cplusplus > 201703
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
else if constexpr (sizeof __ix == 16 && __have_avx512bw_vl)
return __vector_bitcast<_U>(_mm256_cvtepi16_epi8(_mm256_sllv_epi16(
_mm256_cvtepu8_epi16(__ix), _mm256_cvtepu8_epi16(__iy))));
else if constexpr (sizeof __ix == 16 && __have_avx512bw)
return __vector_bitcast<_U>(
__lo128(_mm512_cvtepi16_epi8(_mm512_sllv_epi16(
_mm512_cvtepu8_epi16(_mm256_castsi128_si256(__ix)),
_mm512_cvtepu8_epi16(_mm256_castsi128_si256(__iy))))));
else if constexpr (__have_sse4_1)
{
auto __mask = __vector_bitcast<_U>(__vector_bitcast<short>(__y) << 5);
auto __x4 = __vector_bitcast<_U>(__vector_bitcast<short>(__x) << 4);
__x4 &= char(0xf0);
__x = __blend(__mask, __x, __x4);
__mask += __mask;
auto __x2 = __vector_bitcast<_U>(__vector_bitcast<short>(__x) << 2);
__x2 &= char(0xfc);
__x = __blend(__mask, __x, __x2);
__mask += __mask;
auto __x1 = __x + __x;
__x = __blend(__mask, __x, __x1);
return __x & ((__y & char(0xf8)) == 0);
}
else
{
auto __mask = __vector_bitcast<_UChar>(__vector_bitcast<short>(__y) << 5);
auto __x4 = __vector_bitcast<_U>(__vector_bitcast<short>(__x) << 4);
__x4 &= char(0xf0);
__x = __blend(__vector_bitcast<_SChar>(__mask) < 0, __x, __x4);
__mask += __mask;
auto __x2 = __vector_bitcast<_U>(__vector_bitcast<short>(__x) << 2);
__x2 &= char(0xfc);
__x = __blend(__vector_bitcast<_SChar>(__mask) < 0, __x, __x2);
__mask += __mask;
auto __x1 = __x + __x;
__x = __blend(__vector_bitcast<_SChar>(__mask) < 0, __x, __x1);
return __x & ((__y & char(0xf8)) == 0);
}
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
return __vector_bitcast<_U>(_mm_sllv_epi16(__ix, __iy));
else if constexpr (sizeof __ix == 16 && __have_avx512bw)
return __vector_bitcast<_U>(__lo128(_mm512_sllv_epi16(
_mm512_castsi128_si512(__ix), _mm512_castsi128_si512(__iy))));
else if constexpr (sizeof __ix == 16 && __have_avx2)
{
const auto __ux = __vector_bitcast<unsigned>(__x);
const auto __uy = __vector_bitcast<unsigned>(__y);
return __vector_bitcast<_U>(_mm_blend_epi16(
__auto_bitcast(__ux << (__uy & 0x0000ffffu)),
__auto_bitcast((__ux & 0xffff0000u) << (__uy >> 16)), 0xaa));
}
else if constexpr (sizeof __ix == 16)
{
__y += 0x3f8 >> 3;
return __x *
__vector_bitcast<_U>(
__vector_convert<__vector_type16_t<int>>(
__vector_bitcast<float>(__vector_bitcast<unsigned>(__y)
<< 23)) |
(__vector_convert<__vector_type16_t<int>>(
__vector_bitcast<float>(
(__vector_bitcast<unsigned>(__y) >> 16) << 23))
<< 16));
}
else
__assert_unreachable<_Tp>();
}
else if constexpr (sizeof(_U) == 4 && sizeof __ix == 16 && !__have_avx2)
return __vector_bitcast<_U>(
__vector_bitcast<unsigned>(__x) *
__vector_convert<__vector_type16_t<int>>(
__vector_bitcast<float>((__y << 23) + 0x3f80'0000)));
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
#endif
#ifndef _GLIBCXX_SIMD_NO_SHIFT_OPT
template <typename _Tp, typename _TVT = _VectorTraits<_Tp>>
inline _GLIBCXX_SIMD_CONST static typename _TVT::type
__bit_shift_right(_Tp __xx, int __y)
{
using _V = typename _TVT::type;
using _U = typename _TVT::value_type;
_V __x = __xx;
[[maybe_unused]] const auto __ix = __to_intrin(__x);
if (__builtin_is_constant_evaluated())
return __x >> __y;
else if constexpr (sizeof(_U) == 1 && is_unsigned_v<_U>)
return __vector_bitcast<_U>(__vector_bitcast<_UShort>(__x) >> __y) &
_U(0xff >> __y);
else if constexpr (sizeof(_U) == 1 && is_signed_v<_U>)
return __vector_bitcast<_U>(
(__vector_bitcast<_UShort>(__vector_bitcast<short>(__x) >> (__y + 8))
<< 8) |
(__vector_bitcast<_UShort>(
__vector_bitcast<short>(__vector_bitcast<_UShort>(__x) << 8) >>
__y) >>
8));
else if constexpr (sizeof(_U) == 8 && is_signed_v<_U>)
{
if (__y > 32)
return (__vector_bitcast<_U>(__vector_bitcast<int>(__x) >> 32) &
_U(0xffff'ffff'0000'0000ull)) |
__vector_bitcast<_U>(__vector_bitcast<int>(
__vector_bitcast<_ULLong>(__x) >> 32) >>
(__y - 32));
else
return __vector_bitcast<_U>(__vector_bitcast<_ULLong>(__x) >> __y) |
__vector_bitcast<_U>(
__vector_bitcast<int>(__x & -0x8000'0000'0000'0000ll) >>
__y);
}
else
return __x >> __y;
}
template <typename _Tp, typename _TVT = _VectorTraits<_Tp>>
inline _GLIBCXX_SIMD_CONST static typename _TVT::type
__bit_shift_right(_Tp __xx, typename _TVT::type __y)
{
using _V = typename _TVT::type;
using _U = typename _TVT::value_type;
_V __x = __xx;
[[maybe_unused]] const auto __ix = __to_intrin(__x);
[[maybe_unused]] const auto __iy = __to_intrin(__y);
if (__builtin_is_constant_evaluated())
return __x >> __y;
else if constexpr (sizeof(_U) == 1)
{
if constexpr (sizeof(__x) == 16 && __have_avx512bw_vl)
return __vector_bitcast<_U>(_mm256_cvtepi16_epi8(
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
else if constexpr (__have_avx2)
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
else if constexpr (__have_sse4_1 && is_unsigned_v<_U>)
{
auto __mask =
__vector_bitcast<_U>(__vector_bitcast<_UShort>(__y) << 5);
auto __x4 = __vector_bitcast<_U>(
(__vector_bitcast<_UShort>(__x) >> 4) & _UShort(0xff0f));
__x = __blend(__mask, __x, __x4);
__mask += __mask;
auto __x2 = __vector_bitcast<_U>(
(__vector_bitcast<_UShort>(__x) >> 2) & _UShort(0xff3f));
__x = __blend(__mask, __x, __x2);
__mask += __mask;
auto __x1 = __vector_bitcast<_U>(
(__vector_bitcast<_UShort>(__x) >> 1) & _UShort(0xff7f));
__x = __blend(__mask, __x, __x1);
return __x & ((__y & char(0xf8)) == 0);
}
else if constexpr (__have_sse4_1 && is_signed_v<_U>)
{
auto __mask =
__vector_bitcast<_UChar>(__vector_bitcast<_UShort>(__y) << 5);
auto __maskl = [&]() {
return __vector_bitcast<_UShort>(__mask) << 8;
};
auto __xh = __vector_bitcast<short>(__x);
auto __xl = __vector_bitcast<short>(__x) << 8;
auto __xh4 = __xh >> 4;
auto __xl4 = __xl >> 4;
__xh = __blend(__mask, __xh, __xh4);
__xl = __blend(__maskl(), __xl, __xl4);
__mask += __mask;
auto __xh2 = __xh >> 2;
auto __xl2 = __xl >> 2;
__xh = __blend(__mask, __xh, __xh2);
__xl = __blend(__maskl(), __xl, __xl2);
__mask += __mask;
auto __xh1 = __xh >> 1;
auto __xl1 = __xl >> 1;
__xh = __blend(__mask, __xh, __xh1);
__xl = __blend(__maskl(), __xl, __xl1);
__x = __vector_bitcast<_U>((__xh & short(0xff00))) |
__vector_bitcast<_U>(__vector_bitcast<_UShort>(__xl) >> 8);
return __x & ((__y & char(0xf8)) == 0);
}
else if constexpr (is_unsigned_v<_U>)
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
return __x & ((__y & char(0xf8)) == 0);
}
else
{
static_assert(is_signed_v<_U>);
auto __maskh = __vector_bitcast<_UShort>(__y) << 5;
auto __maskl = __vector_bitcast<_UShort>(__y) << (5 + 8);
auto __xh = __vector_bitcast<short>(__x);
auto __xl = __vector_bitcast<short>(__x) << 8;
auto __xh4 = __xh >> 4;
auto __xl4 = __xl >> 4;
__xh = __blend(__maskh > 0x7fff, __xh, __xh4);
__xl = __blend(__maskl > 0x7fff, __xl, __xl4);
__maskh += __maskh;
__maskl += __maskl;
auto __xh2 = __xh >> 2;
auto __xl2 = __xl >> 2;
__xh = __blend(__maskh > 0x7fff, __xh, __xh2);
__xl = __blend(__maskl > 0x7fff, __xl, __xl2);
__maskh += __maskh;
__maskl += __maskl;
auto __xh1 = __xh >> 1;
auto __xl1 = __xl >> 1;
__xh = __blend(__maskh > 0x7fff, __xh, __xh1);
__xl = __blend(__maskl > 0x7fff, __xl, __xl1);
__x = __vector_bitcast<_U>((__xh & short(0xff00))) |
__vector_bitcast<_U>(__vector_bitcast<_UShort>(__xl) >> 8);
return __x & ((__y & char(0xf8)) == 0);
}
}
else if constexpr (sizeof(_U) == 2)
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
if constexpr (__have_avx512bw_vl && sizeof(_Tp) == 16)
return __vector_bitcast<_U>(is_signed_v<_U>
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
return __vector_bitcast<_U>(
__blend_0xaa(((__vector_bitcast<int>(__x) << 16) >>
(__vector_bitcast<int>(__y) & 0xffffu)) >> 16,
__vector_bitcast<int>(__x) >>
(__vector_bitcast<int>(__y) >> 16)));
else if constexpr (__have_avx2 && is_unsigned_v<_U>)
return __vector_bitcast<_U>(
__blend_0xaa((__vector_bitcast<_UInt>(__x) & 0xffffu) >>
(__vector_bitcast<_UInt>(__y) & 0xffffu),
__vector_bitcast<_UInt>(__x) >>
(__vector_bitcast<_UInt>(__y) >> 16)));
else if constexpr (__have_sse4_1)
{
auto __mask = __vector_bitcast<_UShort>(__y);
__mask = (__mask << 3) | (__mask << 11);
__x = __blend(__mask, __x, _V());
__x = __blend(__mask += __mask, __x, __x >> 8);
__x = __blend(__mask += __mask, __x, __x >> 4);
__x = __blend(__mask += __mask, __x, __x >> 2);
return __vector_bitcast<_U>(__blend(__mask + __mask, __x, __x >> 1));
}
else
{
auto __k = __vector_bitcast<_UShort>(__y) << 11;
auto __mask = [](__vector_type16_t<_UShort> __kk) {
return __vector_bitcast<short>(__kk) < 0;
};
__x = __blend(__mask(__k), __x, _V());
__x = __blend(__mask(__k += __k), __x, __x >> 8);
__x = __blend(__mask(__k += __k), __x, __x >> 4);
__x = __blend(__mask(__k += __k), __x, __x >> 2);
return __vector_bitcast<_U>(__blend(__mask(__k + __k), __x, __x >> 1));
}
}
else if constexpr (sizeof(_U) == 4 && !__have_avx2)
{
if constexpr (is_unsigned_v<_U>)
{
const __m128 __factor_f =
reinterpret_cast<__m128>(0x4f00'0000u - (__y << 23));
const __m128i __factor = __builtin_constant_p(__factor_f)
? __to_intrin(__make_vector<int>(
__factor_f[0], __factor_f[1],
__factor_f[2], __factor_f[3]))
: _mm_cvttps_epi32(__factor_f);
const auto __r02 = _mm_srli_epi64(_mm_mul_epu32(__ix, __factor), 31);
const auto __r13 = _mm_mul_epu32(_mm_srli_si128(__ix, 4),
_mm_srli_si128(__factor, 4));
if constexpr (__have_sse4_1)
return __vector_bitcast<_U>(
_mm_blend_epi16(_mm_slli_epi64(__r13, 1), __r02, 0x33));
else
return __vector_bitcast<_U>(
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
return __vector_bitcast<_U>(
_mm_blend_epi16(_mm_blend_epi16(__r1, __r0, 0x3),
_mm_blend_epi16(__r3, __r2, 0x30), 0xf0));
else
return __vector_bitcast<_U>(_mm_unpacklo_epi64(
_mm_unpacklo_epi32(__r0, _mm_srli_si128(__r1, 4)),
_mm_unpackhi_epi32(__r2, _mm_srli_si128(__r3, 4))));
}
}
else
return __x >> __y;
}
#endif
template <class _Tp, size_t _N>
_GLIBCXX_SIMD_INTRINSIC static constexpr _MaskMember<_Tp> __equal_to(
_SimdWrapper<_Tp, _N> __x, _SimdWrapper<_Tp, _N> __y)
{
if constexpr (sizeof(__x) == 64) {
[[maybe_unused]] const auto __xi = __to_intrin(__x);
[[maybe_unused]] const auto __yi = __to_intrin(__y);
if constexpr (std::is_floating_point_v<_Tp>) {
if constexpr (sizeof(_Tp) == 8) { return _mm512_cmp_pd_mask(__xi, __yi, _CMP_EQ_OQ);
} else if constexpr (sizeof(_Tp) == 4) { return _mm512_cmp_ps_mask(__xi, __yi, _CMP_EQ_OQ);
} else { __assert_unreachable<_Tp>(); }
} else {
if constexpr (sizeof(_Tp) == 8) { return _mm512_cmpeq_epi64_mask(__xi, __yi);
} else if constexpr (sizeof(_Tp) == 4) { return _mm512_cmpeq_epi32_mask(__xi, __yi);
} else if constexpr (sizeof(_Tp) == 2) { return _mm512_cmpeq_epi16_mask(__xi, __yi);
} else if constexpr (sizeof(_Tp) == 1) { return _mm512_cmpeq_epi8_mask(__xi, __yi);
} else { __assert_unreachable<_Tp>(); }
}
} else
return _Base::__equal_to(__x,__y);
}
template <class _Tp, size_t _N>
_GLIBCXX_SIMD_INTRINSIC static constexpr _MaskMember<_Tp> __not_equal_to(
_SimdWrapper<_Tp, _N> __x, _SimdWrapper<_Tp, _N> __y)
{
if constexpr (sizeof(__x) == 64) {
[[maybe_unused]] const auto __xi = __to_intrin(__x);
[[maybe_unused]] const auto __yi = __to_intrin(__y);
if constexpr (std::is_floating_point_v<_Tp>) {
if constexpr (sizeof(_Tp) == 8) { return _mm512_cmp_pd_mask(__xi, __yi, _CMP_NEQ_UQ);
} else if constexpr (sizeof(_Tp) == 4) { return _mm512_cmp_ps_mask(__xi, __yi, _CMP_NEQ_UQ);
} else { __assert_unreachable<_Tp>(); }
} else {
if constexpr (sizeof(_Tp) == 8) { return ~_mm512_cmpeq_epi64_mask(__xi, __yi);
} else if constexpr (sizeof(_Tp) == 4) { return ~_mm512_cmpeq_epi32_mask(__xi, __yi);
} else if constexpr (sizeof(_Tp) == 2) { return ~_mm512_cmpeq_epi16_mask(__xi, __yi);
} else if constexpr (sizeof(_Tp) == 1) { return ~_mm512_cmpeq_epi8_mask(__xi, __yi);
} else { __assert_unreachable<_Tp>(); }
}
} else
return _Base::__not_equal_to(__x, __y);
}
template <class _Tp, size_t _N>
_GLIBCXX_SIMD_INTRINSIC static constexpr _MaskMember<_Tp>
__less(_SimdWrapper<_Tp, _N> __x, _SimdWrapper<_Tp, _N> __y)
{
if constexpr (sizeof(__x) == 64)
{
constexpr auto __k1 = _Abi::template __implicit_mask<_Tp>();
[[maybe_unused]] const auto __xi = __to_intrin(__x);
[[maybe_unused]] const auto __yi = __to_intrin(__y);
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
else
return _Base::__less(__x, __y);
}
template <class _Tp, size_t _N>
_GLIBCXX_SIMD_INTRINSIC static constexpr _MaskMember<_Tp> __less_equal(_SimdWrapper<_Tp, _N> __x,
_SimdWrapper<_Tp, _N> __y)
{
if constexpr (sizeof(__x) == 64) {
[[maybe_unused]] const auto __xi = __to_intrin(__x);
[[maybe_unused]] const auto __yi = __to_intrin(__y);
if constexpr (std::is_floating_point_v<_Tp>) {
if constexpr (sizeof(_Tp) == 8) { return _mm512_cmp_pd_mask(__xi, __yi, _CMP_LE_OS);
} else if constexpr (sizeof(_Tp) == 4) { return _mm512_cmp_ps_mask(__xi, __yi, _CMP_LE_OS);
} else { __assert_unreachable<_Tp>(); }
} else if constexpr (std::is_signed_v<_Tp>) {
if constexpr (sizeof(_Tp) == 8) { return _mm512_cmple_epi64_mask(__xi, __yi);
} else if constexpr (sizeof(_Tp) == 4) { return _mm512_cmple_epi32_mask(__xi, __yi);
} else if constexpr (sizeof(_Tp) == 2) { return _mm512_cmple_epi16_mask(__xi, __yi);
} else if constexpr (sizeof(_Tp) == 1) { return _mm512_cmple_epi8_mask(__xi, __yi);
} else { __assert_unreachable<_Tp>(); }
} else {
static_assert(std::is_unsigned_v<_Tp>);
if constexpr (sizeof(_Tp) == 8) { return _mm512_cmple_epu64_mask(__xi, __yi);
} else if constexpr (sizeof(_Tp) == 4) { return _mm512_cmple_epu32_mask(__xi, __yi);
} else if constexpr (sizeof(_Tp) == 2) { return _mm512_cmple_epu16_mask(__xi, __yi);
} else if constexpr (sizeof(_Tp) == 1) { return _mm512_cmple_epu8_mask(__xi, __yi);
} else { __assert_unreachable<_Tp>(); }
}
} else
return _Base::__less_equal(__x, __y);
}
template <class _Tp, size_t _N>
_GLIBCXX_SIMD_INTRINSIC static constexpr _MaskMember<_Tp> __negate(_SimdWrapper<_Tp, _N> __x) noexcept
{
if constexpr (__is_abi<_Abi, simd_abi::_Avx512Abi>()) {
return __equal_to(__x, _SimdWrapper<_Tp, _N>());
} else {
return _Base::__negate(__x);
}
}
using _Base::__abs;
template <class _Tp, size_t _N> _GLIBCXX_SIMD_INTRINSIC static _SimdWrapper<_Tp, _N> __sqrt(_SimdWrapper<_Tp, _N> __x)
{
if constexpr (__is_sse_ps <_Tp, _N>()) { return _mm_sqrt_ps(__x);
} else if constexpr (__is_sse_pd <_Tp, _N>()) { return _mm_sqrt_pd(__x);
} else if constexpr (__is_avx_ps <_Tp, _N>()) { return _mm256_sqrt_ps(__x);
} else if constexpr (__is_avx_pd <_Tp, _N>()) { return _mm256_sqrt_pd(__x);
} else if constexpr (__is_avx512_ps<_Tp, _N>()) { return _mm512_sqrt_ps(__x);
} else if constexpr (__is_avx512_pd<_Tp, _N>()) { return _mm512_sqrt_pd(__x);
} else { __assert_unreachable<_Tp>(); }
}
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
return _mm_round_ps(__x, 0x3);
} else if constexpr (__have_sse4_1 && __is_sse_pd<_Tp, _N>()) {
return _mm_round_pd(__x, 0x3);
} else if constexpr (__is_sse_ps<_Tp, _N>()) {
auto __truncated = _mm_cvtepi32_ps(_mm_cvttps_epi32(__x));
const auto __no_fractional_values = __vector_bitcast<float>(
__vector_bitcast<int>(__vector_bitcast<_UInt>(__x._M_data) & 0x7f800000u) <
0x4b000000);
return __blend(__no_fractional_values, __x, __truncated);
} else {
return _Base::__trunc(__x);
}
}
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
__truncated = _mm_round_ps(__x._M_data,
_MM_FROUND_TO_ZERO | _MM_FROUND_NO_EXC);
else if constexpr (__have_sse4_1 && __is_sse_pd<_Tp, _N>())
__truncated = _mm_round_pd(__x._M_data,
_MM_FROUND_TO_ZERO | _MM_FROUND_NO_EXC);
else if constexpr (__is_sse_ps<_Tp, _N>())
__truncated = _mm_cvtepi32_ps(_mm_cvttps_epi32(__to_intrin(__x)));
else
return _Base::__round(__x);
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
return _mm_floor_ps(__x);
} else if constexpr (__have_sse4_1 && __is_sse_pd<_Tp, _N>()) {
return _mm_floor_pd(__x);
} else {
return _Base::__floor(__x);
}
}
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
return _mm_ceil_ps(__x);
} else if constexpr (__have_sse4_1 && __is_sse_pd<_Tp, _N>()) {
return _mm_ceil_pd(__x);
} else {
return _Base::__ceil(__x);
}
}
template <class _Tp, size_t _N>
_GLIBCXX_SIMD_INTRINSIC static _MaskMember<_Tp> __signbit(_SimdWrapper<_Tp, _N> __x)
{
using _I = __int_for_sizeof_t<_Tp>;
if constexpr (__have_avx512dq && __is_avx512_ps<_Tp, _N>()) {
return _mm512_movepi32_mask(__vector_bitcast<_LLong>(__x));
} else if constexpr (__have_avx512dq && __is_avx512_pd<_Tp, _N>()) {
return _mm512_movepi64_mask(__vector_bitcast<_LLong>(__x));
} else if constexpr (sizeof(__x) == 64) {
const auto __signmask = __vector_broadcast<_N>(std::numeric_limits<_I>::min());
return __equal_to(_SimdWrapper<_I, _N>(__vector_bitcast<_I>(__x._M_data) & __signmask),
_SimdWrapper<_I, _N>(__signmask));
} else {
const auto __xx = __vector_bitcast<_I>(__x._M_data);
[[maybe_unused]] constexpr _I __signmask = std::numeric_limits<_I>::min();
if constexpr ((sizeof(_Tp) == 4 && (__have_avx2 || sizeof(__x) == 16)) ||
__have_avx512vl) {
return __vector_bitcast<_Tp>(__xx >> std::numeric_limits<_I>::digits);
} else if constexpr ((__have_avx2 || (__have_ssse3 && sizeof(__x) == 16))) {
return __vector_bitcast<_Tp>((__xx & __signmask) == __signmask);
} else {
constexpr auto __one = __vector_broadcast<_N, _Tp>(1);
return __vector_bitcast<_Tp>(
__vector_bitcast<_Tp>((__xx & __signmask) | __vector_bitcast<_I>(__one))
!= __one);
}
}
}
template <class _Tp>
_GLIBCXX_SIMD_INTRINSIC static auto __isnonzerovalue_mask(_Tp __x)
{
using _Traits = _VectorTraits<_Tp>;
if constexpr (__have_avx512dq_vl)
{
if constexpr (_Traits::template __is<float, 4>)
return _knot_mask8(_mm_fpclass_ps_mask(__x, 0x9f));
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
using _U = typename _Traits::value_type;
constexpr size_t _N = _Traits::_S_width;
const auto __a =
__x * std::numeric_limits<_U>::infinity();
const auto __b = __x * _U();
if constexpr (__have_avx512vl && __is_sse_ps<_U, _N>())
{
return _mm_cmp_ps_mask(__a, __b, _CMP_ORD_Q);
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
template <class _Tp, size_t _N>
_GLIBCXX_SIMD_INTRINSIC static _MaskMember<_Tp>
__isfinite(_SimdWrapper<_Tp, _N> __x)
{
#if __FINITE_MATH_ONLY__
__unused(__x);
return __equal_to(_SimdWrapper<_Tp, _N>(), _SimdWrapper<_Tp, _N>());
#else
return __cmpord(__x._M_data, __x._M_data * _Tp());
#endif
}
template <class _Tp, size_t _N>
_GLIBCXX_SIMD_INTRINSIC static _MaskMember<_Tp> __isinf(_SimdWrapper<_Tp, _N> __x)
{
#if __FINITE_MATH_ONLY__
__unused(__x);
return {};
#else
if constexpr (__is_avx512_pd<_Tp, _N>() && __have_avx512dq)
return _mm512_fpclass_pd_mask(__x, 0x18);
else if constexpr (__is_avx512_ps<_Tp, _N>() && __have_avx512dq)
return _mm512_fpclass_ps_mask(__x, 0x18);
else if constexpr (__have_avx512dq_vl)
{
if constexpr (__is_sse_pd<_Tp, _N>())
return __vector_bitcast<double>(
_mm_movm_epi64(_mm_fpclass_pd_mask(__x, 0x18)));
else if constexpr (__is_avx_pd<_Tp, _N>())
return __vector_bitcast<double>(
_mm256_movm_epi64(_mm256_fpclass_pd_mask(__x, 0x18)));
else if constexpr (__is_sse_ps<_Tp, _N>())
return __vector_bitcast<float>(
_mm_movm_epi32(_mm_fpclass_ps_mask(__x, 0x18)));
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
template <class _Tp, size_t _N>
_GLIBCXX_SIMD_INTRINSIC static _MaskMember<_Tp>
__isnormal(_SimdWrapper<_Tp, _N> __x)
{
if constexpr (__have_avx512dq)
{
if constexpr (__have_avx512vl && __is_sse_ps<_Tp, _N>())
return __vector_bitcast<float>(
_mm_movm_epi32(_knot_mask8(_mm_fpclass_ps_mask(__x, 0xbf))));
else if constexpr (__have_avx512vl && __is_avx_ps<_Tp, _N>())
return __vector_bitcast<float>(_mm256_movm_epi32(
_knot_mask8(_mm256_fpclass_ps_mask(__x, 0xbf))));
else if constexpr (__is_avx512_ps<_Tp, _N>())
return _knot_mask16(_mm512_fpclass_ps_mask(__x, 0xbf));
else if constexpr (__have_avx512vl && __is_sse_pd<_Tp, _N>())
return __vector_bitcast<double>(
_mm_movm_epi64(_knot_mask8(_mm_fpclass_pd_mask(__x, 0xbf))));
else if constexpr (__have_avx512vl && __is_avx_pd<_Tp, _N>())
return __vector_bitcast<double>(_mm256_movm_epi64(
_knot_mask8(_mm256_fpclass_pd_mask(__x, 0xbf))));
else if constexpr (__is_avx512_pd<_Tp, _N>())
return _knot_mask8(_mm512_fpclass_pd_mask(__x, 0xbf));
else
__assert_unreachable<_Tp>();
}
else
return _Base::__isnormal(__x);
}
using _Base::__isnan;
template <class _Tp, size_t _N>
_GLIBCXX_SIMD_INTRINSIC static __fixed_size_storage_t<int, _N> __fpclassify(_SimdWrapper<_Tp, _N> __x)
{
if constexpr (__is_avx512_pd<_Tp, _N>()) {
if constexpr (__have_avx512vl) {
auto &&__b = [](int __y) { return __to_intrin(__vector_broadcast<_N>(__y)); };
return {_mm256_mask_mov_epi32(
_mm256_mask_mov_epi32(
_mm256_mask_mov_epi32(__b(FP_NORMAL), __isnan(__x), __b(FP_NAN)),
__isinf(__x), __b(FP_INFINITE)),
_mm512_cmp_pd_mask(
__abs(__x),
__vector_broadcast<_N>(std::numeric_limits<double>::min()),
_CMP_LT_OS),
_mm256_mask_mov_epi32(
__b(FP_SUBNORMAL),
_mm512_cmp_pd_mask(__x, _mm512_setzero_pd(), _CMP_EQ_OQ),
__b(FP_ZERO)))};
} else {
auto &&__b = [](int __y) {
return _mm512_castsi256_si512(__to_intrin(__vector_broadcast<_N>(__y)));
};
return {__lo256(_mm512_mask_mov_epi32(
_mm512_mask_mov_epi32(
_mm512_mask_mov_epi32(__b(FP_NORMAL), __isnan(__x), __b(FP_NAN)),
__isinf(__x), __b(FP_INFINITE)),
_mm512_cmp_pd_mask(
__abs(__x),
__vector_broadcast<_N>(std::numeric_limits<double>::min()),
_CMP_LT_OS),
_mm512_mask_mov_epi32(
__b(FP_SUBNORMAL),
_mm512_cmp_pd_mask(__x, _mm512_setzero_pd(), _CMP_EQ_OQ),
__b(FP_ZERO))))};
}
} else {
return _Base::__fpclassify(__x);
}
}
};
template <class _Abi>
struct __x86_mask_impl : _MaskImplBuiltin<_Abi>
{
using _Base = _MaskImplBuiltin<_Abi>;
template <class _Tp, size_t _N, class _F>
static inline _SimdWrapper<_Tp, _N> __masked_load(_SimdWrapper<_Tp, _N> __merge,
_SimdWrapper<_Tp, _N> __mask,
const bool* __mem,
_F) noexcept
{
if constexpr (__is_abi<_Abi, simd_abi::_Avx512Abi>())
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
__bit_iteration(__mask, [&](auto __i) { __merge.__set(__i, __mem[__i]); });
return __merge;
}
}
else if constexpr (__have_avx512bw_vl && _N == 32 && sizeof(_Tp) == 1)
{
const auto __k = __convert_mask<_SimdWrapper<bool, _N>>(__mask);
__merge = _ToWrapper(
_mm256_mask_sub_epi8(__vector_bitcast<_LLong>(__merge), __k, __m256i(),
_mm256_mask_loadu_epi8(__m256i(), __k, __mem)));
}
else if constexpr (__have_avx512bw_vl && _N == 16 && sizeof(_Tp) == 1)
{
const auto __k = __convert_mask<_SimdWrapper<bool, _N>>(__mask);
__merge = _ToWrapper(
_mm_mask_sub_epi8(__vector_bitcast<_LLong>(__merge), __k, __m128i(),
_mm_mask_loadu_epi8(__m128i(), __k, __mem)));
}
else if constexpr (__have_avx512bw_vl && _N == 16 && sizeof(_Tp) == 2)
{
const auto __k = __convert_mask<_SimdWrapper<bool, _N>>(__mask);
__merge = _ToWrapper(_mm256_mask_sub_epi16(
__vector_bitcast<_LLong>(__merge), __k, __m256i(),
_mm256_cvtepi8_epi16(_mm_mask_loadu_epi8(__m128i(), __k, __mem))));
}
else if constexpr (__have_avx512bw_vl && _N == 8 && sizeof(_Tp) == 2)
{
const auto __k = __convert_mask<_SimdWrapper<bool, _N>>(__mask);
__merge = _ToWrapper(_mm_mask_sub_epi16(
__vector_bitcast<_LLong>(__merge), __k, __m128i(),
_mm_cvtepi8_epi16(_mm_mask_loadu_epi8(__m128i(), __k, __mem))));
}
else if constexpr (__have_avx512bw_vl && _N == 8 && sizeof(_Tp) == 4)
{
const auto __k = __convert_mask<_SimdWrapper<bool, _N>>(__mask);
__merge = _ToWrapper(_mm256_mask_sub_epi32(
__vector_bitcast<_LLong>(__merge), __k, __m256i(),
_mm256_cvtepi8_epi32(_mm_mask_loadu_epi8(__m128i(), __k, __mem))));
}
else if constexpr (__have_avx512bw_vl && _N == 4 && sizeof(_Tp) == 4)
{
const auto __k = __convert_mask<_SimdWrapper<bool, _N>>(__mask);
__merge = _ToWrapper(_mm_mask_sub_epi32(
__vector_bitcast<_LLong>(__merge), __k, __m128i(),
_mm_cvtepi8_epi32(_mm_mask_loadu_epi8(__m128i(), __k, __mem))));
}
else if constexpr (__have_avx512bw_vl && _N == 4 && sizeof(_Tp) == 8)
{
const auto __k = __convert_mask<_SimdWrapper<bool, _N>>(__mask);
__merge = _ToWrapper(_mm256_mask_sub_epi64(
__vector_bitcast<_LLong>(__merge), __k, __m256i(),
_mm256_cvtepi8_epi64(_mm_mask_loadu_epi8(__m128i(), __k, __mem))));
}
else if constexpr (__have_avx512bw_vl && _N == 2 && sizeof(_Tp) == 8)
{
const auto __k = __convert_mask<_SimdWrapper<bool, _N>>(__mask);
__merge = _ToWrapper(_mm_mask_sub_epi64(
__vector_bitcast<_LLong>(__merge), __k, __m128i(),
_mm_cvtepi8_epi64(_mm_mask_loadu_epi8(__m128i(), __k, __mem))));
}
else
{
return _Base::__masked_load(__merge, __mask, __mem, _F{});
}
return __merge;
}
template <class _Tp, size_t _N, class _F>
_GLIBCXX_SIMD_INTRINSIC static void
__store(_SimdWrapper<_Tp, _N> __v, bool* __mem, _F) noexcept
{
if constexpr (__is_abi<_Abi, simd_abi::_SseAbi>())
{
if constexpr (_N == 2 && __have_sse2)
{
const auto __k = __vector_bitcast<int>(__v);
__mem[0] = -__k[1];
__mem[1] = -__k[3];
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
const __m64 __kk = _mm_cvtps_pi8(__and(__k, _mm_set1_ps(1.f)));
__vector_store<4>(__kk, __mem, _F());
_mm_empty();
}
else if constexpr (_N == 8 && __have_sse2)
{
__vector_store<8>(
_mm_packs_epi16(__to_intrin(__vector_bitcast<ushort>(__v) >> 15),
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
else if constexpr (__is_abi<_Abi, simd_abi::_AvxAbi>())
{
if constexpr (_N == 4 && __have_avx)
{
auto __k = __vector_bitcast<_LLong>(__v);
int __bool4;
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
const auto __x = _mm256_srli_epi16(__to_intrin(__v), 15);
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
else if constexpr (__is_abi<_Abi, simd_abi::_Avx512Abi>())
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
template <class _Tp, size_t _N, class _F>
static inline void __masked_store(const _SimdWrapper<_Tp, _N> __v,
bool* __mem,
_F,
const _SimdWrapper<_Tp, _N> __k) noexcept
{
if constexpr (__is_abi<_Abi, simd_abi::_Avx512Abi>())
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
};
struct _MaskImplSse : __x86_mask_impl<simd_abi::__sse> {};
struct _SimdImplSse : __x86_simd_impl<simd_abi::__sse> {};
struct _MaskImplAvx : __x86_mask_impl<simd_abi::__avx> {};
struct _SimdImplAvx : __x86_simd_impl<simd_abi::__avx> {};
struct _SimdImplAvx512 : __x86_simd_impl<simd_abi::__avx512> {};
struct _MaskImplAvx512 : __x86_mask_impl<simd_abi::__avx512> {};
#endif
#if _GLIBCXX_SIMD_HAVE_NEON
template <int _Bytes>
struct _SimdImplNeon : _SimdImplBuiltin<simd_abi::_NeonAbi<_Bytes>>
{
using _Base = _SimdImplBuiltin<simd_abi::_NeonAbi<_Bytes>>;
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
}
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
}
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
}
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
}
};
template <int _Bytes>
struct _MaskImplNeon : _MaskImplBuiltin<simd_abi::_NeonAbi<_Bytes>>
{
};
#endif
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
template <size_t _Count, size_t _Begin> struct _BinaryTreeReduce {
static_assert(_Count > 0,
"_BinaryTreeReduce requires at least one simd object to work with");
template <class _Tp, class... _As, class _BinaryOperation>
auto operator()(const _SimdTuple<_Tp, _As...> &__tup,
const _BinaryOperation &__binary_op) const noexcept
{
constexpr size_t __left = __next_power_of_2(_Count) / 2;
constexpr size_t __right = _Count - __left;
return __binary_op(_BinaryTreeReduce<__left, _Begin>()(__tup, __binary_op),
_BinaryTreeReduce<__right, _Begin + __left>()(__tup, __binary_op));
}
};
template <size_t _Begin> struct _BinaryTreeReduce<1, _Begin> {
template <class _Tp, class... _As, class _BinaryOperation>
auto operator()(const _SimdTuple<_Tp, _As...> &__tup, const _BinaryOperation &) const
noexcept
{
return __get_simd_at<_Begin>(__tup);
}
};
template <size_t _Begin> struct _BinaryTreeReduce<2, _Begin> {
template <class _Tp, class... _As, class _BinaryOperation>
auto operator()(const _SimdTuple<_Tp, _As...> &__tup,
const _BinaryOperation &__binary_op) const noexcept
{
return __binary_op(__get_simd_at<_Begin>(__tup),
__get_simd_at<_Begin + 1>(__tup));
}
};
template <class _Tp, class _A0, class _A1, class _BinaryOperation>
_GLIBCXX_SIMD_INTRINSIC simd<_Tp, _A1> __vec_to_scalar_reduction_first_pair(
const simd<_Tp, _A0> __left, const simd<_Tp, _A1> __right, const _BinaryOperation &__binary_op,
_SizeConstant<2>) noexcept
{
const std::array<simd<_Tp, _A1>, 2> __splitted = split<simd<_Tp, _A1>>(__left);
return __binary_op(__binary_op(__splitted[0], __right), __splitted[1]);
}
template <class _Tp, class _A0, class _A1, class _BinaryOperation>
_GLIBCXX_SIMD_INTRINSIC simd<_Tp, _A1> __vec_to_scalar_reduction_first_pair(
const simd<_Tp, _A0> __left, const simd<_Tp, _A1> __right, const _BinaryOperation &__binary_op,
_SizeConstant<4>) noexcept
{
constexpr auto _N0 = simd_size_v<_Tp, _A0> / 2;
const auto __left2 = split<simd<_Tp, simd_abi::deduce_t<_Tp, _N0>>>(__left);
const std::array<simd<_Tp, _A1>, 2> __splitted =
split<simd<_Tp, _A1>>(__binary_op(__left2[0], __left2[1]));
return __binary_op(__binary_op(__splitted[0], __right), __splitted[1]);
}
template <class _Tp, class _A0, class _A1, class _BinaryOperation, size_t _Factor>
_GLIBCXX_SIMD_INTRINSIC simd<_Tp, simd_abi::scalar> __vec_to_scalar_reduction_first_pair(
const simd<_Tp, _A0> __left, const simd<_Tp, _A1> __right, const _BinaryOperation &__binary_op,
_SizeConstant<_Factor>) noexcept
{
return __binary_op(std::experimental::reduce(__left, __binary_op), std::experimental::reduce(__right, __binary_op));
}
template <class _Tp, class _A0, class _BinaryOperation>
_GLIBCXX_SIMD_INTRINSIC _Tp __vec_to_scalar_reduction(const _SimdTuple<_Tp, _A0> &__tup,
const _BinaryOperation &__binary_op) noexcept
{
return std::experimental::reduce(simd<_Tp, _A0>(__private_init, __tup.first), __binary_op);
}
template <class _Tp, class _A0, class _A1, class... _As, class _BinaryOperation>
_GLIBCXX_SIMD_INTRINSIC _Tp __vec_to_scalar_reduction(const _SimdTuple<_Tp, _A0, _A1, _As...> &__tup,
const _BinaryOperation &__binary_op) noexcept
{
return __vec_to_scalar_reduction(
__simd_tuple_concat(
__make_simd_tuple(
__vec_to_scalar_reduction_first_pair<_Tp, _A0, _A1, _BinaryOperation>(
{__private_init, __tup.first}, {__private_init, __tup.second.first},
__binary_op,
_SizeConstant<simd_size_v<_Tp, _A0> / simd_size_v<_Tp, _A1>>())),
__tup.second.second),
__binary_op);
}
template <int _N> struct _SimdImplFixedSize {
using _MaskMember = std::bitset<_N>;
template <class _Tp> using _SimdMember = __fixed_size_storage_t<_Tp, _N>;
template <class _Tp>
static constexpr std::size_t _S_tuple_size = _SimdMember<_Tp>::_S_tuple_size;
template <class _Tp> using _Simd = std::experimental::simd<_Tp, simd_abi::fixed_size<_N>>;
template <class _Tp> using _TypeTag = _Tp *;
template <class _Tp> static constexpr inline _SimdMember<_Tp> __broadcast(_Tp __x) noexcept
{
return _SimdMember<_Tp>::__generate(
[&](auto __meta) constexpr { return __meta.__broadcast(__x); });
}
template <class _F, class _Tp>
static constexpr inline _SimdMember<_Tp>
__generator(_F&& __gen, _TypeTag<_Tp>)
{
return _SimdMember<_Tp>::__generate([&__gen](auto __meta) constexpr {
return __meta.__generator(
[&](auto __i) constexpr {
static_assert(__i < _N);
return __gen(_SizeConstant<__meta._S_offset + __i>());
},
_TypeTag<_Tp>());
});
}
template <class _Tp, class _U, class _F>
static inline _SimdMember<_Tp> __load(const _U *__mem, _F __f,
_TypeTag<_Tp>) _GLIBCXX_SIMD_NOEXCEPT_OR_IN_TEST
{
return _SimdMember<_Tp>::__generate(
[&](auto __meta) { return __meta.__load(&__mem[__meta._S_offset], __f, _TypeTag<_Tp>()); });
}
template <class _Tp, class... _As, class _U, class _F>
static inline _SimdTuple<_Tp, _As...>
__masked_load(const _SimdTuple<_Tp, _As...>& __old,
const _MaskMember __bits,
const _U* __mem,
_F __f) _GLIBCXX_SIMD_NOEXCEPT_OR_IN_TEST
{
auto __merge = __old;
__for_each(__merge, [&](auto __meta, auto& __native) {
__native = __meta.__masked_load(__native, __meta.__make_mask(__bits),
&__mem[__meta._S_offset], __f);
});
return __merge;
}
template <class _Tp, class _U, class _F>
static inline void __store(const _SimdMember<_Tp>& __v,
_U* __mem,
_F __f,
_TypeTag<_Tp>) _GLIBCXX_SIMD_NOEXCEPT_OR_IN_TEST
{
__for_each(__v, [&](auto __meta, auto __native) {
__meta.__store(__native, &__mem[__meta._S_offset], __f, _TypeTag<_Tp>());
});
}
template <class _Tp, class... _As, class _U, class _F>
static inline void __masked_store(const _SimdTuple<_Tp, _As...>& __v,
_U* __mem,
_F __f,
const _MaskMember __bits)
_GLIBCXX_SIMD_NOEXCEPT_OR_IN_TEST
{
__for_each(__v, [&](auto __meta, auto __native) {
__meta.__masked_store(__native, &__mem[__meta._S_offset], __f,
__meta.__make_mask(__bits));
});
}
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
private:
template <class _Tp, class... _As, class _BinaryOperation, size_t... _Counts,
size_t... _Begins>
static inline _Tp __reduce(const _SimdTuple<_Tp, _As...> &__tup,
const _BinaryOperation &__binary_op,
std::index_sequence<_Counts...>, std::index_sequence<_Begins...>)
{
const auto __reduced_vec =
__make_simd_tuple(_BinaryTreeReduce<_Counts, _Begins>()(__tup, __binary_op)...);
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
template <typename _Tp, typename... _As>
static inline constexpr _SimdTuple<_Tp, _As...>
__complement(const _SimdTuple<_Tp, _As...>& __x) noexcept
{
return __x.__apply_per_chunk([](auto __impl, auto __xx) constexpr {
return __impl.__complement(__xx);
});
}
template <typename _Tp, typename... _As>
static inline constexpr _SimdTuple<_Tp, _As...>
__unary_minus(const _SimdTuple<_Tp, _As...>& __x) noexcept
{
return __x.__apply_per_chunk([](auto __impl, auto __xx) constexpr {
return __impl.__unary_minus(__xx);
});
}
#define _GLIBCXX_SIMD_FIXED_OP(name_,op_) \
template <typename _Tp, typename... _As> \
static inline constexpr _SimdTuple<_Tp, _As...> name_( \
const _SimdTuple<_Tp, _As...>& __x, const _SimdTuple<_Tp, _As...>& __y) \
{ \
return __x.__apply_per_chunk( \
[](auto __impl, auto __xx, auto __yy) constexpr { \
return __impl.name_(__xx, __yy); \
}, \
__y); \
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
#define _GLIBCXX_SIMD_APPLY_ON_TUPLE(_RetTp,__name) \
template <typename _Tp, typename... _As, typename... _More> \
static inline __fixed_size_storage_t<_RetTp, \
_SimdTuple<_Tp, _As...>::size()> \
__##__name(const _SimdTuple<_Tp, _As...>& __x, const _More&... __more) \
{ \
if constexpr (sizeof...(_More) == 0) \
{ \
if constexpr (is_same_v<_Tp, _RetTp>) \
return __x.__apply_per_chunk([](auto __impl, auto __xx) constexpr { \
using _V = typename decltype(__impl)::simd_type; \
return __data(__name(_V(__private_init, __xx))); \
}); \
else \
return __optimize_simd_tuple(__x.template __apply_r<_RetTp>( \
[](auto __impl, auto __xx) { return __impl.__##__name(__xx); })); \
} \
else if constexpr (is_same_v<_Tp, _RetTp> && \
(... && \
std::is_same_v<_SimdTuple<_Tp, _As...>, _More>)) \
return __x.__apply_per_chunk( \
[](auto __impl, auto __xx, auto... __pack) constexpr { \
using _V = typename decltype(__impl)::simd_type; \
return __data( \
__name(_V(__private_init, __xx), _V(__private_init, __pack)...)); \
}, \
__more...); \
else if constexpr (is_same_v<_Tp, _RetTp>) \
return __x.__apply_per_chunk( \
[](auto __impl, auto __xx, auto... __pack) constexpr { \
using _V = typename decltype(__impl)::simd_type; \
return __data( \
__name(_V(__private_init, __xx), __autocvt_to_simd(__pack)...)); \
}, \
__more...); \
else \
__assert_unreachable<_Tp>(); \
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
_GLIBCXX_SIMD_APPLY_ON_TUPLE(_Tp, scalbn)
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
_GLIBCXX_SIMD_APPLY_ON_TUPLE(_Tp, nextafter)
_GLIBCXX_SIMD_APPLY_ON_TUPLE(_Tp, fdim)
_GLIBCXX_SIMD_APPLY_ON_TUPLE(_Tp, fmax)
_GLIBCXX_SIMD_APPLY_ON_TUPLE(_Tp, fmin)
_GLIBCXX_SIMD_APPLY_ON_TUPLE(_Tp, fma)
_GLIBCXX_SIMD_APPLY_ON_TUPLE(int, fpclassify)
#undef _GLIBCXX_SIMD_APPLY_ON_TUPLE
template <typename _Tp, typename... _Abis>
static _SimdTuple<_Tp, _Abis...> __remquo(
const _SimdTuple<_Tp, _Abis...>& __x,
const _SimdTuple<_Tp, _Abis...>& __y,
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
__frexp(const _SimdTuple<_Tp, _As...>& __x,
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
#define _GLIBCXX_SIMD_TEST_ON_TUPLE_(name_) \
template <typename _Tp, typename... _As> \
static inline _MaskMember __##name_( \
const _SimdTuple<_Tp, _As...>& __x) noexcept \
{ \
return __test([](auto __impl, auto __xx) { return __impl.__##name_(__xx); }, \
__x); \
}
_GLIBCXX_SIMD_TEST_ON_TUPLE_(isinf)
_GLIBCXX_SIMD_TEST_ON_TUPLE_(isfinite)
_GLIBCXX_SIMD_TEST_ON_TUPLE_(isnan)
_GLIBCXX_SIMD_TEST_ON_TUPLE_(isnormal)
_GLIBCXX_SIMD_TEST_ON_TUPLE_(signbit)
#undef _GLIBCXX_SIMD_TEST_ON_TUPLE_
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
#define _GLIBCXX_SIMD_CMP_OPERATIONS(__cmp) \
template <typename _Tp, typename... _As> \
_GLIBCXX_SIMD_INTRINSIC static _MaskMember __cmp( \
const _SimdTuple<_Tp, _As...>& __x, const _SimdTuple<_Tp, _As...>& __y) \
{ \
return __test([](auto __impl, auto __xx, \
auto __yy) { return __impl.__cmp(__xx, __yy); }, \
__x, __y); \
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
template <typename _Tp, typename... _As, typename _U>
_GLIBCXX_SIMD_INTRINSIC static void __set(_SimdTuple<_Tp, _As...> &__v, int __i, _U &&__x) noexcept
{
__v.__set(__i, std::forward<_U>(__x));
}
template <typename _Tp, typename... _As>
_GLIBCXX_SIMD_INTRINSIC static void
__masked_assign(const _MaskMember __bits,
_SimdTuple<_Tp, _As...>& __lhs,
const __id<_SimdTuple<_Tp, _As...>>& __rhs)
{
__for_each(__lhs, __rhs,
[&](auto __meta, auto& __native_lhs, auto __native_rhs) constexpr {
__meta.__masked_assign(__meta.__make_mask(__bits), __native_lhs,
__native_rhs);
});
}
template <typename _Tp, typename... _As>
_GLIBCXX_SIMD_INTRINSIC static void
__masked_assign(const _MaskMember __bits,
_SimdTuple<_Tp, _As...>& __lhs,
const __id<_Tp> __rhs)
{
__for_each(__lhs, [&](auto __meta, auto& __native_lhs) constexpr {
__meta.__masked_assign(__meta.__make_mask(__bits), __native_lhs, __rhs);
});
}
template <template <typename> class _Op, typename _Tp, typename... _As>
static inline void __masked_cassign(const _MaskMember __bits,
_SimdTuple<_Tp, _As...>& __lhs,
const _SimdTuple<_Tp, _As...>& __rhs)
{
__for_each(__lhs, __rhs,
[&](auto __meta, auto& __native_lhs, auto __native_rhs) constexpr {
__meta.template __masked_cassign<_Op>(
__meta.__make_mask(__bits), __native_lhs, __native_rhs);
});
}
template <template <typename> class _Op, typename _Tp, typename... _As>
static inline void __masked_cassign(const _MaskMember __bits,
_SimdTuple<_Tp, _As...>& __lhs,
const _Tp& __rhs)
{
__for_each(__lhs, [&](auto __meta, auto& __native_lhs) constexpr {
__meta.template __masked_cassign<_Op>(__meta.__make_mask(__bits),
__native_lhs, __rhs);
});
}
template <template <typename> class _Op, typename _Tp, typename... _As>
static inline _SimdTuple<_Tp, _As...>
__masked_unary(const _MaskMember __bits,
const _SimdTuple<_Tp, _As...> __v)
{
return __v.__apply_wrapped([&__bits](auto __meta, auto __native) constexpr {
return __meta.template __masked_unary<_Op>(__meta.__make_mask(__bits),
__native);
});
}
};
template <int _N> struct _MaskImplFixedSize {
static_assert(sizeof(_ULLong) * CHAR_BIT >= _N,
"The fixed_size implementation relies on one "
"_ULLong being able to store all boolean "
"elements.");
using _MaskMember = std::bitset<_N>;
template <typename _Tp> using _TypeTag = _Tp *;
template <typename _Tp>
_GLIBCXX_SIMD_INTRINSIC static _MaskMember __from_bitset(const _MaskMember &__bs,
_TypeTag<_Tp>) noexcept
{
return __bs;
}
template <typename _F> static inline _MaskMember __load(const bool *__mem, _F __f) noexcept
{
_ULLong __r = 0;
using _Vs = __fixed_size_storage_t<_UChar, _N>;
__for_each(_Vs{}, [&](auto __meta, auto) {
__r |= __meta.__mask_to_shifted_ullong(
__meta._S_mask_impl.__load(&__mem[__meta._S_offset], __f, _SizeConstant<__meta.size()>()));
});
return __r;
}
template <typename _F>
static inline _MaskMember __masked_load(_MaskMember __merge,
_MaskMember __mask, const bool *__mem,
_F) noexcept
{
__bit_iteration(__mask.to_ullong(), [&](auto __i) { __merge[__i] = __mem[__i]; });
return __merge;
}
template <typename _F>
static inline void __store(_MaskMember __bs, bool *__mem, _F __f) noexcept
{
#if _GLIBCXX_SIMD_HAVE_AVX512BW
const __m512i bool64 = _mm512_movm_epi8(__bs.to_ullong()) & 0x0101010101010101ULL;
__vector_store<_N>(bool64, __mem, __f);
#elif _GLIBCXX_SIMD_HAVE_BMI2
#ifdef __x86_64__
__unused(__f);
__execute_n_times<_N / 8>([&](auto __i) {
constexpr size_t __offset = __i * 8;
const _ULLong bool8 =
_pdep_u64(__bs.to_ullong() >> __offset, 0x0101010101010101ULL);
std::memcpy(&__mem[__offset], &bool8, 8);
});
if (_N % 8 > 0) {
constexpr size_t __offset = (_N / 8) * 8;
const _ULLong bool8 =
_pdep_u64(__bs.to_ullong() >> __offset, 0x0101010101010101ULL);
std::memcpy(&__mem[__offset], &bool8, _N % 8);
}
#else
__unused(__f);
__execute_n_times<_N / 4>([&](auto __i) {
constexpr size_t __offset = __i * 4;
const _ULLong __bool4 =
_pdep_u32(__bs.to_ullong() >> __offset, 0x01010101U);
std::memcpy(&__mem[__offset], &__bool4, 4);
});
if (_N % 4 > 0) {
constexpr size_t __offset = (_N / 4) * 4;
const _ULLong __bool4 =
_pdep_u32(__bs.to_ullong() >> __offset, 0x01010101U);
std::memcpy(&__mem[__offset], &__bool4, _N % 4);
}
#endif
#elif _GLIBCXX_SIMD_HAVE_SSE2
using _V = simd<_UChar, simd_abi::__sse>;
_ULLong __bits = __bs.to_ullong();
__execute_n_times<(_N + 15) / 16>([&](auto __i) {
constexpr size_t __offset = __i * 16;
constexpr size_t __remaining = _N - __offset;
if constexpr (__remaining == 1) {
__mem[__offset] = static_cast<bool>(__bits >> __offset);
} else if constexpr (__remaining <= 4) {
const _UInt __bool4 = ((__bits >> __offset) * 0x00204081U) & 0x01010101U;
std::memcpy(&__mem[__offset], &__bool4, __remaining);
} else if constexpr (__remaining <= 7) {
const _ULLong bool8 =
((__bits >> __offset) * 0x40810204081ULL) & 0x0101010101010101ULL;
std::memcpy(&__mem[__offset], &bool8, __remaining);
} else if constexpr (__have_sse2) {
auto __tmp = _mm_cvtsi32_si128(__bits >> __offset);
__tmp = _mm_unpacklo_epi8(__tmp, __tmp);
__tmp = _mm_unpacklo_epi16(__tmp, __tmp);
__tmp = _mm_unpacklo_epi32(__tmp, __tmp);
_V __tmp2(__tmp);
__tmp2 &= _V([](auto __j) {
return static_cast<_UChar>(1 << (__j % CHAR_BIT));
});
const __m128i __bool16 = __intrin_bitcast<__m128i>(
__vector_bitcast<_UChar>(__data(__tmp2 == 0)) +
1);
if constexpr (__remaining >= 16) {
__vector_store<16>(__bool16, &__mem[__offset], __f);
} else if constexpr (__remaining & 3) {
constexpr int to_shift = 16 - int(__remaining);
_mm_maskmoveu_si128(__bool16,
_mm_srli_si128(~__m128i(), to_shift),
reinterpret_cast<char *>(&__mem[__offset]));
} else
if constexpr (__remaining >= 8) {
__vector_store<8>(__bool16, &__mem[__offset], __f);
if constexpr (__remaining == 12) {
__vector_store<4>(_mm_unpackhi_epi64(__bool16, __bool16),
&__mem[__offset + 8], __f);
}
}
} else {
__assert_unreachable<_F>();
}
});
#else
using _Vs = __fixed_size_storage_t<_UChar, _N>;
__for_each(_Vs{}, [&](auto __meta, auto) {
__meta._S_mask_impl.__store(__meta.__make_mask(__bs), &__mem[__meta._S_offset], __f);
});
#endif
}
template <typename _F>
static inline void __masked_store(const _MaskMember __v, bool *__mem, _F,
const _MaskMember __k) noexcept
{
__bit_iteration(__k, [&](auto __i) { __mem[__i] = __v[__i]; });
}
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
_GLIBCXX_SIMD_INTRINSIC static void __set(_MaskMember &__k, int __i, bool __x) noexcept
{
__k.set(__i, __x);
}
_GLIBCXX_SIMD_INTRINSIC static void __masked_assign(const _MaskMember __k,
_MaskMember &__lhs,
const _MaskMember __rhs)
{
__lhs = (__lhs & ~__k) | (__rhs & __k);
}
_GLIBCXX_SIMD_INTRINSIC static void __masked_assign(const _MaskMember __k,
_MaskMember &__lhs, const bool __rhs)
{
if (__rhs) {
__lhs |= __k;
} else {
__lhs &= ~__k;
}
}
};
template <typename _From, typename _To, typename _Abi>
struct _SimdConverter<_From, _Abi, _To, _Abi>
{
template <typename _Tp>
using _SimdMember = typename _Abi::template __traits<_Tp>::_SimdMember;
using _Arg = _SimdMember<_From>;
using _Ret = _SimdMember<_To>;
using _V = __vector_type_t<_To, simd_size_v<_To, _Abi>>;
_GLIBCXX_SIMD_INTRINSIC decltype(auto) operator()(const _Arg& __a)
{
if constexpr (is_same_v<_To, _From>)
return __a;
else
return __convert<_V>(__a);
}
template <typename... _More>
_GLIBCXX_SIMD_INTRINSIC _Ret operator()(_Arg __a, _More... __more)
{
static_assert(sizeof(_From) >= (sizeof...(_More)+1) * sizeof(_To));
return __convert<_V>(__a, __more...);
}
_GLIBCXX_SIMD_INTRINSIC auto __all(const _Arg& __a)
{
return __convert_all<_V>(__a);
}
};
template <typename _From, typename _To>
struct _SimdConverter<_From, simd_abi::scalar, _To, simd_abi::scalar>
{
_GLIBCXX_SIMD_INTRINSIC _To operator()(_From __a)
{
return static_cast<_To>(__a);
}
};
template <typename _From, typename _To, typename _Abi>
struct _SimdConverter<_From, _Abi, _To, simd_abi::scalar>
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
template <typename _From, typename _To, typename _Abi>
struct _SimdConverter<_From, simd_abi::scalar, _To, _Abi>
{
using _Ret = typename _Abi::template __traits<_To>::_SimdMember;
template <typename... _More>
_GLIBCXX_SIMD_INTRINSIC constexpr _Ret operator()(_From __a, _More... __more)
{
static_assert(sizeof...(_More) + 1 == _Ret::_S_width);
static_assert(std::conjunction_v<std::is_same<_From, _More>...>);
return __make_vector<_To>(__a, __more...);
}
};
template <typename _From, typename _To, typename _AFrom, typename _ATo>
struct _SimdConverter<_From, _AFrom, _To, _ATo>
{
using _Arg = typename _AFrom::template __traits<_From>::_SimdMember;
using _Ret = typename _ATo::template __traits<_To>::_SimdMember;
using _V = __vector_type_t<_To, simd_size_v<_To, _ATo>>;
_GLIBCXX_SIMD_INTRINSIC auto __all(_Arg __a)
{
return __convert_all<_V>(__a);
}
template <typename... _More>
_GLIBCXX_SIMD_INTRINSIC _Ret operator()(_Arg __a, _More... __more)
{
static_assert(std::conjunction_v<std::is_same<_Arg, _More>...>);
return __convert<_V>(__a, __more...);
}
};
template <typename _From, typename _To>
struct _SimdConverter<_From, simd_abi::scalar, _To, simd_abi::fixed_size<1>> {
_SimdTuple<_To, simd_abi::scalar> operator()(_From __x) { return {static_cast<_To>(__x)}; }
};
template <typename _From, typename _To>
struct _SimdConverter<_From, simd_abi::fixed_size<1>, _To, simd_abi::scalar> {
_GLIBCXX_SIMD_INTRINSIC _To operator()(_SimdTuple<_From, simd_abi::scalar> __x)
{
return {static_cast<_To>(__x.first)};
}
};
template <typename _Tp, int _N>
struct _SimdConverter<_Tp, simd_abi::fixed_size<_N>, _Tp, simd_abi::fixed_size<_N>> {
using _Arg = __fixed_size_storage_t<_Tp, _N>;
_GLIBCXX_SIMD_INTRINSIC const _Arg &operator()(const _Arg &__x) { return __x; }
};
template <size_t _ChunkSize, typename _Tp> struct determine_required_input_chunks;
template <typename _Tp, typename... _Abis>
struct determine_required_input_chunks<0, _SimdTuple<_Tp, _Abis...>>
: public std::integral_constant<size_t, 0> {
};
template <size_t _ChunkSize, typename _Tp, typename _Abi0, typename... _Abis>
struct determine_required_input_chunks<_ChunkSize, _SimdTuple<_Tp, _Abi0, _Abis...>>
: public std::integral_constant<
size_t, determine_required_input_chunks<_ChunkSize - simd_size_v<_Tp, _Abi0>,
_SimdTuple<_Tp, _Abis...>>::value> {
};
template <typename _From, typename _To> struct _FixedSizeConverter {
struct _OneToMultipleChunks {
};
template <int _N> struct _MultipleToOneChunk {
};
struct _EqualChunks {
};
template <typename _FromAbi,
typename _ToAbi,
size_t _ToSize = simd_size_v<_To, _ToAbi>,
size_t _FromSize = simd_size_v<_From, _FromAbi>>
using _ChunkRelation = std::conditional_t<
(_ToSize < _FromSize),
_OneToMultipleChunks,
std::conditional_t<(_ToSize == _FromSize),
_EqualChunks,
_MultipleToOneChunk<int(_ToSize / _FromSize)>>>;
template <typename... _Abis>
using _ReturnType = __fixed_size_storage_t<_To, _SimdTuple<_From, _Abis...>::size()>;
protected:
template <typename _A0>
_GLIBCXX_SIMD_INTRINSIC _ReturnType<_A0> __impl(_OneToMultipleChunks, const _SimdTuple<_From, _A0> &__x)
{
using _R = _ReturnType<_A0>;
_SimdConverter<_From, _A0, _To, typename _R::_First_abi> __native_cvt;
auto &&__multiple_return_chunks = __native_cvt.__all(__x.first);
return __to_simd_tuple<_To, typename _R::_First_abi>(__multiple_return_chunks);
}
template <typename... _Abis>
_GLIBCXX_SIMD_INTRINSIC _ReturnType<_Abis...> __impl(_OneToMultipleChunks,
const _SimdTuple<_From, _Abis...> &__x)
{
using _R = _ReturnType<_Abis...>;
using _Arg = _SimdTuple<_From, _Abis...>;
constexpr size_t __first_chunk = simd_size_v<_From, typename _Arg::_First_abi>;
_SimdConverter<_From, typename _Arg::_First_abi, _To, typename _R::_First_abi>
__native_cvt;
auto &&__multiple_return_chunks = __native_cvt.__all(__x.first);
constexpr size_t __n_output_chunks =
__first_chunk / simd_size_v<_To, typename _R::_First_abi>;
return __simd_tuple_concat(
__to_simd_tuple<_To, typename _R::_First_abi>(__multiple_return_chunks),
__impl(_ChunkRelation<typename _Arg::_Second_type::_First_abi,
typename __simd_tuple_element<__n_output_chunks, _R>::type::abi_type>(),
__x.second));
}
template <int _N, typename _A0, typename... _Abis>
_GLIBCXX_SIMD_INTRINSIC _ReturnType<_A0, _Abis...> __impl(_MultipleToOneChunk<_N>,
const _SimdTuple<_From, _A0, _Abis...> &__x)
{
return __impl_mto(std::integral_constant<bool, sizeof...(_Abis) + 1 == _N>(),
std::make_index_sequence<_N>(), __x);
}
template <size_t... _Indexes, typename _A0, typename... _Abis>
_GLIBCXX_SIMD_INTRINSIC _ReturnType<_A0, _Abis...> __impl_mto(true_type,
std::index_sequence<_Indexes...>,
const _SimdTuple<_From, _A0, _Abis...> &__x)
{
using _R = _ReturnType<_A0, _Abis...>;
_SimdConverter<_From, _A0, _To, typename _R::_First_abi> __native_cvt;
return {__native_cvt(__get_tuple_at<_Indexes>(__x)...)};
}
template <size_t... _Indexes, typename _A0, typename... _Abis>
_GLIBCXX_SIMD_INTRINSIC _ReturnType<_A0, _Abis...> __impl_mto(false_type,
std::index_sequence<_Indexes...>,
const _SimdTuple<_From, _A0, _Abis...> &__x)
{
using _R = _ReturnType<_A0, _Abis...>;
_SimdConverter<_From, _A0, _To, typename _R::_First_abi> __native_cvt;
return {
__native_cvt(__get_tuple_at<_Indexes>(__x)...),
__impl(
_ChunkRelation<
typename __simd_tuple_element<sizeof...(_Indexes),
_SimdTuple<_From, _A0, _Abis...>>::type::abi_type,
typename _R::_Second_type::_First_abi>(),
__simd_tuple_pop_front<sizeof...(_Indexes)>(__x))};
}
template <typename _A0>
_GLIBCXX_SIMD_INTRINSIC _ReturnType<_A0> __impl(_EqualChunks, const _SimdTuple<_From, _A0> &__x)
{
_SimdConverter<_From, _A0, _To, typename _ReturnType<_A0>::_First_abi> __native_cvt;
return {__native_cvt(__x.first)};
}
template <typename _A0, typename _A1, typename... _Abis>
_GLIBCXX_SIMD_INTRINSIC _ReturnType<_A0, _A1, _Abis...> __impl(
_EqualChunks, const _SimdTuple<_From, _A0, _A1, _Abis...> &__x)
{
using _R = _ReturnType<_A0, _A1, _Abis...>;
using _Rem = typename _R::_Second_type;
_SimdConverter<_From, _A0, _To, typename _R::_First_abi> __native_cvt;
return {__native_cvt(__x.first),
__impl(_ChunkRelation<_A1, typename _Rem::_First_abi>(), __x.second)};
}
};
template <typename _From, typename _To, int _N>
struct _SimdConverter<_From,
simd_abi::fixed_size<_N>,
_To,
simd_abi::fixed_size<_N>>
: public _FixedSizeConverter<_From, _To>
{
using _Base = _FixedSizeConverter<_From, _To>;
using _Ret = __fixed_size_storage_t<_To, _N>;
using _Arg = __fixed_size_storage_t<_From, _N>;
_GLIBCXX_SIMD_INTRINSIC _Ret operator()(const _Arg& __x)
{
if constexpr (__is_abi<typename _Ret::_First_abi, simd_abi::scalar>())
{
return __call_with_subscripts(
__x, make_index_sequence<_N>(), [](auto... __values) constexpr -> _Ret {
return __to_simd_tuple<_To, simd_abi::scalar>(
array<_To, _N>{static_cast<_To>(__values)...});
});
}
else
{
using _CR =
typename _Base::template _ChunkRelation<typename _Arg::_First_abi,
typename _Ret::_First_abi>;
return _Base::__impl(_CR(), __x);
}
}
};
template <typename _From, typename _A, typename _To, int _N>
struct _SimdConverter<_From, _A, _To, simd_abi::fixed_size<_N>> {
using __traits = _SimdTraits<_From, _A>;
using _Arg = typename __traits::_SimdMember;
using _ReturnType = __fixed_size_storage_t<_To, _N>;
static_assert(_N == simd_size_v<_From, _A>,
"_SimdConverter to fixed_size only works for equal element counts");
_GLIBCXX_SIMD_INTRINSIC _ReturnType operator()(_Arg __x)
{
return __impl(std::make_index_sequence<_ReturnType::_S_tuple_size>(), __x);
}
private:
_ReturnType __impl(std::index_sequence<0>, _Arg __x)
{
_SimdConverter<_From, _A, _To, typename _ReturnType::_First_abi> __native_cvt;
return {__native_cvt(__x)};
}
template <size_t... _Indexes> _ReturnType __impl(std::index_sequence<_Indexes...>, _Arg __x)
{
_SimdConverter<_From, _A, _To, typename _ReturnType::_First_abi> __native_cvt;
const auto &__tmp = __native_cvt.__all(__x);
return {__tmp[_Indexes]...};
}
};
template <typename _From, int _N, typename _To, typename _A>
struct _SimdConverter<_From, simd_abi::fixed_size<_N>, _To, _A> {
using __traits = _SimdTraits<_To, _A>;
using _ReturnType = typename __traits::_SimdMember;
using _Arg = __fixed_size_storage_t<_From, _N>;
static_assert(_N == simd_size_v<_To, _A>,
"_SimdConverter to fixed_size only works for equal element counts");
_GLIBCXX_SIMD_INTRINSIC _ReturnType operator()(_Arg __x)
{
return __impl(std::make_index_sequence<_Arg::_S_tuple_size>(), __x);
}
private:
template <size_t... _Indexes> _ReturnType __impl(std::index_sequence<_Indexes...>, _Arg __x)
{
_SimdConverter<_From, typename _Arg::_First_abi, _To, _A> __native_cvt;
return __native_cvt(__get_tuple_at<_Indexes>(__x)...);
}
};
_GLIBCXX_SIMD_END_NAMESPACE
#endif
#endif
#ifndef _GLIBCXX_EXPERIMENTAL_SIMD_MATH_H_
#define _GLIBCXX_EXPERIMENTAL_SIMD_MATH_H_ 
#if __cplusplus >= 201703L
#include <utility>
#include <iomanip>
_GLIBCXX_SIMD_BEGIN_NAMESPACE
template <class _Tp, class _V> using __samesize = fixed_size_simd<_Tp, _V::size()>;
template <class _DoubleR, class _Tp, class _Abi> struct __math_return_type;
template <class _DoubleR, class _Tp, class _Abi>
using __math_return_type_t = typename __math_return_type<_DoubleR, _Tp, _Abi>::type;
template <class _Tp, class _Abi> struct __math_return_type<double, _Tp, _Abi> {
using type = std::experimental::simd<_Tp, _Abi>;
};
template <class _Tp, class _Abi> struct __math_return_type<bool, _Tp, _Abi> {
using type = std::experimental::simd_mask<_Tp, _Abi>;
};
template <class _DoubleR, class _Tp, class _Abi> struct __math_return_type {
using type = std::experimental::fixed_size_simd<_DoubleR, simd_size_v<_Tp, _Abi>>;
};
#define _GLIBCXX_SIMD_MATH_CALL_(__name) \
template <class _Tp, class _Abi, class..., \
class _R = std::experimental::__math_return_type_t< \
decltype(std::__name(std::declval<double>())), _Tp, _Abi>> \
enable_if_t<std::is_floating_point_v<_Tp>, _R> __name( \
std::experimental::simd<_Tp, _Abi> __x) \
{ \
return {std::experimental::__private_init, \
_Abi::_SimdImpl::__##__name(std::experimental::__data(__x))}; \
}
template <class _U, class _Tp, class _Abi> struct __extra_argument_type;
template <class _Tp, class _Abi> struct __extra_argument_type<_Tp *, _Tp, _Abi> {
using type = std::experimental::simd<_Tp, _Abi> *;
static constexpr double *declval();
_GLIBCXX_SIMD_INTRINSIC static constexpr auto __data(type __x) { return &std::experimental::__data(*__x); }
static constexpr bool __needs_temporary_scalar = true;
};
template <class _U, class _Tp, class _Abi> struct __extra_argument_type<_U *, _Tp, _Abi> {
static_assert(std::is_integral_v<_U>);
using type = std::experimental::fixed_size_simd<_U, std::experimental::simd_size_v<_Tp, _Abi>> *;
static constexpr _U *declval();
_GLIBCXX_SIMD_INTRINSIC static constexpr auto __data(type __x) { return &std::experimental::__data(*__x); }
static constexpr bool __needs_temporary_scalar = true;
};
template <class _Tp, class _Abi> struct __extra_argument_type<_Tp, _Tp, _Abi> {
using type = std::experimental::simd<_Tp, _Abi>;
static constexpr double declval();
_GLIBCXX_SIMD_INTRINSIC static constexpr decltype(auto) __data(const type &__x)
{
return std::experimental::__data(__x);
}
static constexpr bool __needs_temporary_scalar = false;
};
template <class _U, class _Tp, class _Abi> struct __extra_argument_type {
static_assert(std::is_integral_v<_U>);
using type = std::experimental::fixed_size_simd<_U, std::experimental::simd_size_v<_Tp, _Abi>>;
static constexpr _U declval();
_GLIBCXX_SIMD_INTRINSIC static constexpr decltype(auto) __data(const type &__x)
{
return std::experimental::__data(__x);
}
static constexpr bool __needs_temporary_scalar = false;
};
#define _GLIBCXX_SIMD_MATH_CALL2_(__name,arg2_) \
template <class _Tp, class _Abi, class..., \
class _Arg2 = \
std::experimental::__extra_argument_type<arg2_, _Tp, _Abi>, \
class _R = std::experimental::__math_return_type_t< \
decltype(std::__name(std::declval<double>(), _Arg2::declval())), \
_Tp, _Abi>> \
enable_if_t<std::is_floating_point_v<_Tp>, _R> __name( \
const std::experimental::simd<_Tp, _Abi>& __x, \
const typename _Arg2::type& __y) \
{ \
return {std::experimental::__private_init, \
_Abi::_SimdImpl::__##__name(std::experimental::__data(__x), \
_Arg2::__data(__y))}; \
} \
template <class _U, class _Tp, class _Abi> \
_GLIBCXX_SIMD_INTRINSIC std::experimental::__math_return_type_t< \
decltype(std::__name( \
std::declval<double>(), \
std::declval<enable_if_t< \
std::conjunction_v< \
std::is_same<arg2_, _Tp>, \
std::negation<std::is_same<__remove_cvref_t<_U>, \
std::experimental::simd<_Tp, _Abi>>>, \
std::is_convertible<_U, std::experimental::simd<_Tp, _Abi>>, \
std::is_floating_point<_Tp>>, \
double>>())), \
_Tp, _Abi> \
__name(_U&& __xx, const std::experimental::simd<_Tp, _Abi>& __yy) \
{ \
return std::experimental::__name( \
std::experimental::simd<_Tp, _Abi>(std::forward<_U>(__xx)), __yy); \
}
#define _GLIBCXX_SIMD_MATH_CALL3_(__name,arg2_,arg3_) \
template < \
class _Tp, class _Abi, class..., \
class _Arg2 = std::experimental::__extra_argument_type<arg2_, _Tp, _Abi>, \
class _Arg3 = std::experimental::__extra_argument_type<arg3_, _Tp, _Abi>, \
class _R = std::experimental::__math_return_type_t< \
decltype(std::__name(std::declval<double>(), _Arg2::declval(), \
_Arg3::declval())), \
_Tp, _Abi>> \
enable_if_t<std::is_floating_point_v<_Tp>, _R> __name( \
std::experimental::simd<_Tp, _Abi> __x, typename _Arg2::type __y, \
typename _Arg3::type __z) \
{ \
return {std::experimental::__private_init, \
_Abi::_SimdImpl::__##__name(std::experimental::__data(__x), \
_Arg2::__data(__y), \
_Arg3::__data(__z))}; \
} \
template <class _Tp, class _U, class _V, class..., \
class _TT = __remove_cvref_t<_Tp>, \
class _UU = __remove_cvref_t<_U>, \
class _VV = __remove_cvref_t<_V>, \
class _Simd = \
std::conditional_t<std::experimental::is_simd_v<_UU>, _UU, _VV>> \
_GLIBCXX_SIMD_INTRINSIC decltype(std::experimental::__name( \
_Simd(std::declval<_Tp>()), _Simd(std::declval<_U>()), \
_Simd(std::declval<_V>()))) \
__name(_Tp&& __xx, _U&& __yy, _V&& __zz) \
{ \
return std::experimental::__name(_Simd(std::forward<_Tp>(__xx)), \
_Simd(std::forward<_U>(__yy)), \
_Simd(std::forward<_V>(__zz))); \
}
template <typename _Abi>
_GLIBCXX_SIMD_ALWAYS_INLINE static simd<float, _Abi>
__cosSeries(const simd<float, _Abi>& __x)
{
const simd<float, _Abi> __x2 = __x * __x;
simd<float, _Abi> __y;
__y = 0x1.ap-16f;
__y = __y * __x2 - 0x1.6c1p-10f;
__y = __y * __x2 + 0x1.555556p-5f;
return __y * (__x2 * __x2) - .5f * __x2 + 1.f;
}
template <typename _Abi>
_GLIBCXX_SIMD_ALWAYS_INLINE static simd<double, _Abi>
__cosSeries(const simd<double, _Abi>& __x)
{
const simd<double, _Abi> __x2 = __x * __x;
simd<double, _Abi> __y;
__y = 0x1.AC00000000000p-45;
__y = __y * __x2 - 0x1.9394000000000p-37;
__y = __y * __x2 + 0x1.1EED8C0000000p-29;
__y = __y * __x2 - 0x1.27E4FB7400000p-22;
__y = __y * __x2 + 0x1.A01A01A018000p-16;
__y = __y * __x2 - 0x1.6C16C16C16C00p-10;
__y = __y * __x2 + 0x1.5555555555554p-5;
return (__y * __x2 - .5f) * __x2 + 1.f;
}
template <typename _Abi>
_GLIBCXX_SIMD_ALWAYS_INLINE static simd<float, _Abi>
__sinSeries(const simd<float, _Abi>& __x)
{
const simd<float, _Abi> __x2 = __x * __x;
simd<float, _Abi> __y;
__y = -0x1.9CC000p-13f;
__y = __y * __x2 + 0x1.111100p-7f;
__y = __y * __x2 - 0x1.555556p-3f;
return __y * (__x2 * __x) + __x;
}
template <typename _Abi>
_GLIBCXX_SIMD_ALWAYS_INLINE static simd<double, _Abi>
__sinSeries(const simd<double, _Abi>& __x)
{
const simd<double, _Abi> __x2 = __x * __x;
simd<double, _Abi> __y;
__y = -0x1.ACF0000000000p-41;
__y = __y * __x2 + 0x1.6124400000000p-33;
__y = __y * __x2 - 0x1.AE64567000000p-26;
__y = __y * __x2 + 0x1.71DE3A5540000p-19;
__y = __y * __x2 - 0x1.A01A01A01A000p-13;
__y = __y * __x2 + 0x1.1111111111110p-7;
__y = __y * __x2 - 0x1.5555555555555p-3;
return __y * (__x2 * __x) + __x;
}
template <int _Bits, typename _Tp, typename _Abi>
_GLIBCXX_SIMD_INTRINSIC simd<_Tp, _Abi> __zero_low_bits(simd<_Tp, _Abi> __x)
{
const simd<_Tp, _Abi> __bitmask =
__bit_cast<_Tp>(~std::make_unsigned_t<__int_for_sizeof_t<_Tp>>() << _Bits);
return {__private_init,
_Abi::_SimdImpl::__bit_and(__data(__x), __data(__bitmask))};
}
template <class _Tp, class _Abi>
struct __folded
{
simd<_Tp, _Abi> _M_x;
rebind_simd_t<int, simd<_Tp, _Abi>> _M_quadrant;
};
namespace __math_float
{
inline constexpr float __pi_over_4 = 0x1.921FB6p-1f;
inline constexpr float __2_over_pi = 0x1.45F306p-1f;
inline constexpr float __pi_2_5bits0 =
0x1.921fc0p0f;
inline constexpr float __pi_2_5bits0_rem =
-0x1.5777a6p-21f;
}
namespace __math_double
{
inline constexpr double __pi_over_4 = 0x1.921fb54442d18p-1;
inline constexpr double __2_over_pi = 0x1.45F306DC9C883p-1;
inline constexpr double __pi_2 = 0x1.921fb54442d18p0;
}
template <class _Abi>
_GLIBCXX_SIMD_ALWAYS_INLINE __folded<float, _Abi>
__fold_input(const simd<float, _Abi>& __x)
{
using _V = simd<float, _Abi>;
using _IV = rebind_simd_t<int, _V>;
using namespace __math_float;
__folded<float, _Abi> __r;
__r._M_x = abs(__x);
#if 0
constexpr float __1_over_pi = 0x1.45F306p-2f;
const auto __y = (__r._M_x * __1_over_pi + 0x1.8p23f) - 0x1.8p23f;
constexpr float __pi0 = 0x1.920000p1f;
constexpr float __pi1 = 0x1.fb4000p-11f;
constexpr float __pi2 = 0x1.444000p-23f;
constexpr float __pi3 = 0x1.68c234p-38f;
__r._M_x - __y*__pi0 - __y*__pi1 - __y*__pi2 - __y*__pi3
#else
if (_GLIBCXX_SIMD_IS_UNLIKELY(all_of(__r._M_x < __pi_over_4)))
{
__r._M_quadrant = 0;
}
else if (_GLIBCXX_SIMD_IS_LIKELY(all_of(__r._M_x < 6 * __pi_over_4)))
{
const _V __y = nearbyint(__r._M_x * __2_over_pi);
__r._M_quadrant = static_simd_cast<_IV>(__y) & 3;
__r._M_x -= __y * __pi_2_5bits0;
__r._M_x -= __y * __pi_2_5bits0_rem;
}
else
{
using __math_double::__2_over_pi;
using __math_double::__pi_2;
using _VD = rebind_simd_t<double, _V>;
_VD __xd = static_simd_cast<_VD>(__r._M_x);
_VD __y = nearbyint(__xd * __2_over_pi);
__r._M_quadrant = static_simd_cast<_IV>(__y) & 3;
__r._M_x = static_simd_cast<_V>(__xd - __y * __pi_2);
}
#endif
return __r;
}
template <typename _Abi>
_GLIBCXX_SIMD_ALWAYS_INLINE __folded<double, _Abi>
__fold_input(const simd<double, _Abi>& __x)
{
using _V = simd<double, _Abi>;
using _IV = rebind_simd_t<int, _V>;
using namespace __math_double;
__folded<double, _Abi> __r;
__r._M_x = abs(__x);
if (_GLIBCXX_SIMD_IS_UNLIKELY(all_of(__r._M_x < __pi_over_4))) {
__r._M_quadrant = 0;
return __r;
}
const _V __y = nearbyint(__r._M_x / (2 * __pi_over_4));
__r._M_quadrant = static_simd_cast<_IV>(__y) & 3;
if (_GLIBCXX_SIMD_IS_LIKELY(all_of(__r._M_x < 1025 * __pi_over_4)))
{
__r._M_x -= __y * 0x1.921FB54443000p0;
__r._M_x -= __y * -0x1.73DCB3B39A000p-43;
__r._M_x -= __y * 0x1.45C06E0E68948p-86;
}
else if (_GLIBCXX_SIMD_IS_LIKELY(all_of(__y <= 0x1.0p30)))
{
__r._M_x -= __y * 0x1.921FB40000000p0;
__r._M_x -= __y * 0x1.4442D00000000p-24;
__r._M_x -= __y * 0x1.8469898CC5170p-48;
}
else
{
const _V __y_hi = __zero_low_bits<26>(__y);
const _V __y_lo = __y - __y_hi;
const auto __pi_2_1 = 0x1.921FB50000000p0;
const auto __pi_2_2 = 0x1.110B460000000p-26;
const auto __pi_2_3 = 0x1.1A62630000000p-54;
const auto __pi_2_4 = 0x1.8A2E03707344Ap-81;
__r._M_x = __r._M_x
- __y_hi * __pi_2_1
- max(__y_hi * __pi_2_2, __y_lo * __pi_2_1)
- min(__y_hi * __pi_2_2, __y_lo * __pi_2_1)
- max(__y_hi * __pi_2_3, __y_lo * __pi_2_2)
- min(__y_hi * __pi_2_3, __y_lo * __pi_2_2)
- max(__y * __pi_2_4, __y_lo * __pi_2_3)
- min(__y * __pi_2_4, __y_lo * __pi_2_3);
}
return __r;
}
template <class _Abi>
rebind_simd_t<int, simd<float, _Abi>> __extract_exponent_bits(const simd<float, _Abi> &__v)
{
using namespace std::experimental::__proposed;
using namespace std::experimental::__proposed::float_bitwise_operators;
constexpr simd<float, _Abi> __exponent_mask =
std::numeric_limits<float>::infinity();
return simd_reinterpret_cast<rebind_simd_t<int, simd<float, _Abi>>>(__v & __exponent_mask);
}
template <class _Abi>
rebind_simd_t<int, simd<double, _Abi>> __extract_exponent_bits(const simd<double, _Abi> &__v)
{
using namespace std::experimental::__proposed;
using namespace std::experimental::__proposed::float_bitwise_operators;
const simd<double, _Abi> __exponent_mask =
std::numeric_limits<double>::infinity();
constexpr auto _N = simd_size_v<double, _Abi> * 2;
constexpr auto _Max = simd_abi::max_fixed_size<int>;
if constexpr (_N > _Max) {
const auto tup = split<_Max / 2, (_N - _Max) / 2>(__v & __exponent_mask);
return concat(
shuffle<strided<2, 1>>(
simd_reinterpret_cast<simd<int, simd_abi::deduce_t<int, _Max>>>(
std::get<0>(tup))),
shuffle<strided<2, 1>>(
simd_reinterpret_cast<simd<int, simd_abi::deduce_t<int, _N - _Max>>>(
std::get<1>(tup))));
} else {
return shuffle<strided<2, 1>>(
simd_reinterpret_cast<simd<int, simd_abi::deduce_t<int, _N>>>(__v &
__exponent_mask));
}
}
template <class ImplFun, class FallbackFun, class... _Args>
_GLIBCXX_SIMD_INTRINSIC auto __impl_or_fallback_dispatch(int, ImplFun&& __impl_fun,
FallbackFun&&, _Args&&... __args)
-> decltype(__impl_fun(std::forward<_Args>(__args)...))
{
return __impl_fun(std::forward<_Args>(__args)...);
}
template <class ImplFun, class FallbackFun, class... _Args>
inline auto __impl_or_fallback_dispatch(float, ImplFun&&, FallbackFun&& __fallback_fun,
_Args&&... __args)
-> decltype(__fallback_fun(std::forward<_Args>(__args)...))
{
return __fallback_fun(std::forward<_Args>(__args)...);
}
template <class... _Args> _GLIBCXX_SIMD_INTRINSIC auto __impl_or_fallback(_Args&&... __args)
{
return __impl_or_fallback_dispatch(int(), std::forward<_Args>(__args)...);
}
_GLIBCXX_SIMD_MATH_CALL_(acos)
_GLIBCXX_SIMD_MATH_CALL_(asin)
_GLIBCXX_SIMD_MATH_CALL_(atan)
_GLIBCXX_SIMD_MATH_CALL2_(atan2, _Tp)
template <class _Tp, class _Abi>
enable_if_t<std::is_floating_point_v<_Tp>, simd<_Tp, _Abi>>
cos(const simd<_Tp, _Abi>& __x)
{
using _V = simd<_Tp, _Abi>;
if constexpr (__is_abi<_Abi, simd_abi::scalar>() ||
__is_fixed_size_abi_v<_Abi>)
{
return {__private_init, _Abi::_SimdImpl::__cos(__data(__x))};
}
else
{
if constexpr (is_same_v<_Tp, float>)
if (_GLIBCXX_SIMD_IS_UNLIKELY(any_of(abs(__x) >= 393382)))
return static_simd_cast<_V>(
cos(static_simd_cast<rebind_simd_t<double, _V>>(__x)));
const auto __f = __fold_input(__x);
using namespace std::experimental::__proposed::float_bitwise_operators;
const _V __sign_flip =
_V(-0.f) & static_simd_cast<_V>((1 + __f._M_quadrant) << 30);
const auto __need_cos = (__f._M_quadrant & 1) == 0;
if (_GLIBCXX_SIMD_IS_UNLIKELY(all_of(__need_cos)))
{
return __sign_flip ^ __cosSeries(__f._M_x);
}
else if (_GLIBCXX_SIMD_IS_UNLIKELY(none_of(__need_cos)))
{
return __sign_flip ^ __sinSeries(__f._M_x);
}
else
{
_V __r = __sinSeries(__f._M_x);
where(__need_cos.__cvt(), __r) = __cosSeries(__f._M_x);
return __r ^ __sign_flip;
}
}
}
template <class _Tp>
_GLIBCXX_SIMD_ALWAYS_INLINE
enable_if_t<std::is_floating_point<_Tp>::value, simd<_Tp, simd_abi::scalar>>
cos(simd<_Tp, simd_abi::scalar> __x)
{
return std::cos(__data(__x));
}
template <class _Tp, class _Abi>
enable_if_t<std::is_floating_point_v<_Tp>, simd<_Tp, _Abi>>
sin(const simd<_Tp, _Abi>& __x)
{
using _V = simd<_Tp, _Abi>;
if constexpr (__is_abi<_Abi, simd_abi::scalar>() ||
__is_fixed_size_abi_v<_Abi>)
{
return {__private_init, _Abi::_SimdImpl::__sin(__data(__x))};
}
else
{
if constexpr (is_same_v<_Tp, float>)
if (_GLIBCXX_SIMD_IS_UNLIKELY(any_of(abs(__x) >= 527449)))
return static_simd_cast<_V>(
sin(static_simd_cast<rebind_simd_t<double, _V>>(__x)));
const auto __f = __fold_input(__x);
using namespace std::experimental::__proposed::float_bitwise_operators;
const auto __sign_flip =
(__x ^ static_simd_cast<_V>(1 - __f._M_quadrant)) & _V(_Tp(-0.));
const auto __need_sin = (__f._M_quadrant & 1) == 0;
if (_GLIBCXX_SIMD_IS_UNLIKELY(all_of(__need_sin)))
{
return __sign_flip ^ __sinSeries(__f._M_x);
}
else if (_GLIBCXX_SIMD_IS_UNLIKELY(none_of(__need_sin)))
{
return __sign_flip ^ __cosSeries(__f._M_x);
}
else
{
_V __r = __cosSeries(__f._M_x);
where(__need_sin.__cvt(), __r) = __sinSeries(__f._M_x);
return __sign_flip ^ __r;
}
}
}
template <class _Tp>
_GLIBCXX_SIMD_ALWAYS_INLINE
enable_if_t<std::is_floating_point<_Tp>::value, simd<_Tp, simd_abi::scalar>>
sin(simd<_Tp, simd_abi::scalar> __x)
{
return std::sin(__data(__x));
}
_GLIBCXX_SIMD_MATH_CALL_(tan)
_GLIBCXX_SIMD_MATH_CALL_(acosh)
_GLIBCXX_SIMD_MATH_CALL_(asinh)
_GLIBCXX_SIMD_MATH_CALL_(atanh)
_GLIBCXX_SIMD_MATH_CALL_(cosh)
_GLIBCXX_SIMD_MATH_CALL_(sinh)
_GLIBCXX_SIMD_MATH_CALL_(tanh)
_GLIBCXX_SIMD_MATH_CALL_(exp)
_GLIBCXX_SIMD_MATH_CALL_(exp2)
_GLIBCXX_SIMD_MATH_CALL_(expm1)
template <class _Tp, size_t _N> _SimdWrapper<_Tp, _N> __getexp(_SimdWrapper<_Tp, _N> __x)
{
if constexpr (__have_avx512vl && __is_sse_ps<_Tp, _N>()) {
return _mm_getexp_ps(__x);
} else if constexpr (__have_avx512f && __is_sse_ps<_Tp, _N>()) {
return __lo128(_mm512_getexp_ps(__auto_bitcast(__x)));
} else if constexpr (__have_avx512vl && __is_sse_pd<_Tp, _N>()) {
return _mm_getexp_pd(__x);
} else if constexpr (__have_avx512f && __is_sse_pd<_Tp, _N>()) {
return __lo128(_mm512_getexp_pd(__auto_bitcast(__x)));
} else if constexpr (__have_avx512vl && __is_avx_ps<_Tp, _N>()) {
return _mm256_getexp_ps(__x);
} else if constexpr (__have_avx512f && __is_avx_ps<_Tp, _N>()) {
return __lo256(_mm512_getexp_ps(__auto_bitcast(__x)));
} else if constexpr (__have_avx512vl && __is_avx_pd<_Tp, _N>()) {
return _mm256_getexp_pd(__x);
} else if constexpr (__have_avx512f && __is_avx_pd<_Tp, _N>()) {
return __lo256(_mm512_getexp_pd(__auto_bitcast(__x)));
} else if constexpr (__is_avx512_ps<_Tp, _N>()) {
return _mm512_getexp_ps(__x);
} else if constexpr (__is_avx512_pd<_Tp, _N>()) {
return _mm512_getexp_pd(__x);
} else {
__assert_unreachable<_Tp>();
}
}
#if _GLIBCXX_SIMD_X86INTRIN
template <class _Tp, size_t _N> _SimdWrapper<_Tp, _N> __getmant_avx512(_SimdWrapper<_Tp, _N> __x)
{
if constexpr (__have_avx512vl && __is_sse_ps<_Tp, _N>()) {
return _mm_getmant_ps(__x, _MM_MANT_NORM_p5_1, _MM_MANT_SIGN_src);
} else if constexpr (__have_avx512f && __is_sse_ps<_Tp, _N>()) {
return __lo128(
_mm512_getmant_ps(__auto_bitcast(__x), _MM_MANT_NORM_p5_1, _MM_MANT_SIGN_src));
} else if constexpr (__have_avx512vl && __is_sse_pd<_Tp, _N>()) {
return _mm_getmant_pd(__x, _MM_MANT_NORM_p5_1, _MM_MANT_SIGN_src);
} else if constexpr (__have_avx512f && __is_sse_pd<_Tp, _N>()) {
return __lo128(
_mm512_getmant_pd(__auto_bitcast(__x), _MM_MANT_NORM_p5_1, _MM_MANT_SIGN_src));
} else if constexpr (__have_avx512vl && __is_avx_ps<_Tp, _N>()) {
return _mm256_getmant_ps(__x, _MM_MANT_NORM_p5_1, _MM_MANT_SIGN_src);
} else if constexpr (__have_avx512f && __is_avx_ps<_Tp, _N>()) {
return __lo256(
_mm512_getmant_ps(__auto_bitcast(__x), _MM_MANT_NORM_p5_1, _MM_MANT_SIGN_src));
} else if constexpr (__have_avx512vl && __is_avx_pd<_Tp, _N>()) {
return _mm256_getmant_pd(__x, _MM_MANT_NORM_p5_1, _MM_MANT_SIGN_src);
} else if constexpr (__have_avx512f && __is_avx_pd<_Tp, _N>()) {
return __lo256(
_mm512_getmant_pd(__auto_bitcast(__x), _MM_MANT_NORM_p5_1, _MM_MANT_SIGN_src));
} else if constexpr (__is_avx512_ps<_Tp, _N>()) {
return _mm512_getmant_ps(__x, _MM_MANT_NORM_p5_1, _MM_MANT_SIGN_src);
} else if constexpr (__is_avx512_pd<_Tp, _N>()) {
return _mm512_getmant_pd(__x, _MM_MANT_NORM_p5_1, _MM_MANT_SIGN_src);
} else {
__assert_unreachable<_Tp>();
}
}
#endif
template <class _Tp, class _Abi>
enable_if_t<std::is_floating_point_v<_Tp>, simd<_Tp, _Abi>> frexp(
const simd<_Tp, _Abi> &__x, __samesize<int, simd<_Tp, _Abi>> *__exp)
{
if constexpr (simd_size_v<_Tp, _Abi> == 1) {
int __tmp;
const auto __r = std::frexp(__x[0], &__tmp);
(*__exp)[0] = __tmp;
return __r;
} else if constexpr (__is_fixed_size_abi_v<_Abi>) {
return {__private_init, _Abi::_SimdImpl::__frexp(__data(__x), __data(*__exp))};
#if _GLIBCXX_SIMD_X86INTRIN
} else if constexpr (__have_avx512f) {
using _IV = __samesize<int, simd<_Tp, _Abi>>;
constexpr size_t _N = simd_size_v<_Tp, _Abi>;
constexpr size_t NI = _N < 4 ? 4 : _N;
const auto __v = __data(__x);
const auto __isnonzero = _Abi::_SimdImpl::__isnonzerovalue_mask(__v._M_data);
const auto __e =
__to_intrin(__blend(__isnonzero, __vector_type_t<int, NI>(),
1 + __convert<_SimdWrapper<int, NI>>(__getexp(__v))._M_data));
__vector_store<_N * sizeof(int)>(__e, __exp, overaligned<alignof(_IV)>);
return {__private_init, __blend(__isnonzero, __v, __getmant_avx512(__v))};
#endif
} else {
static_assert(sizeof(_Tp) == 4 || sizeof(_Tp) == 8);
using _V = simd<_Tp, _Abi>;
using _IV = rebind_simd_t<int, _V>;
using _IM = typename _IV::mask_type;
using _Limits = std::numeric_limits<_Tp>;
using namespace std::experimental::__proposed;
using namespace std::experimental::__proposed::float_bitwise_operators;
constexpr int __exp_shift = sizeof(_Tp) == 4 ? 23 : 20;
constexpr int __exp_adjust = sizeof(_Tp) == 4 ? 0x7e : 0x3fe;
constexpr int __exp_offset = sizeof(_Tp) == 4 ? 0x70 : 0x200;
constexpr _Tp __subnorm_scale = sizeof(_Tp) == 4 ? 0x1p112 : 0x1p512;
constexpr _V __exponent_mask =
_Limits::infinity();
constexpr _V __p5_1_exponent =
_Tp(sizeof(_Tp) == 4 ? -0x1.fffffep-1 : -0x1.fffffffffffffp-1);
_V __mant = __p5_1_exponent & (__exponent_mask | __x);
const _IV __exponent_bits = __extract_exponent_bits(__x);
if (_GLIBCXX_SIMD_IS_LIKELY(all_of(isnormal(__x)))) {
*__exp = simd_cast<__samesize<int, _V>>((__exponent_bits >> __exp_shift) -
__exp_adjust);
return __mant;
}
const auto __iszero_inf_nan = isunordered(__x * _Limits::infinity(), __x * _V());
const _V __scaled_subnormal = __x * __subnorm_scale;
const _V __mant_subnormal = __p5_1_exponent & (__exponent_mask | __scaled_subnormal);
where(!isnormal(__x), __mant) = __mant_subnormal;
where(__iszero_inf_nan, __mant) = __x;
_IV __e = __extract_exponent_bits(__scaled_subnormal);
const _IM __value_isnormal = static_simd_cast<_IM>(isnormal(__x));
where(__value_isnormal, __e) = __exponent_bits;
const _IV __offset = (simd_reinterpret_cast<_IV>(__value_isnormal) & _IV(__exp_adjust)) |
(simd_reinterpret_cast<_IV>((__exponent_bits == 0) &
(static_simd_cast<_IM>(__x != 0))) &
_IV(__exp_adjust + __exp_offset));
*__exp = simd_cast<__samesize<int, _V>>((__e >> __exp_shift) - __offset);
return __mant;
}
}
_GLIBCXX_SIMD_MATH_CALL2_(ldexp, int)
_GLIBCXX_SIMD_MATH_CALL_(ilogb)
_GLIBCXX_SIMD_MATH_CALL_(log)
_GLIBCXX_SIMD_MATH_CALL_(log10)
_GLIBCXX_SIMD_MATH_CALL_(log1p)
_GLIBCXX_SIMD_MATH_CALL_(log2)
template <class _Tp, class _Abi>
enable_if_t<std::is_floating_point<_Tp>::value, simd<_Tp, _Abi>> logb(
const simd<_Tp, _Abi> &__x)
{
constexpr size_t _N = simd_size_v<_Tp, _Abi>;
if constexpr (_N == 1) {
return std::logb(__x[0]);
} else if constexpr (__is_fixed_size_abi_v<_Abi>) {
return {__private_init,
__data(__x).__apply_per_chunk([](auto __impl, auto __xx) {
using _V = typename decltype(__impl)::simd_type;
return __data(
std::experimental::logb(_V(__private_init, __xx)));
})};
}
else if constexpr (__have_avx512vl && __is_sse_ps<_Tp, _N>())
{
return {__private_init, _mm_getexp_ps(__data(__x))};
}
else if constexpr (__have_avx512vl && __is_sse_pd<_Tp, _N>())
{
return {__private_init, _mm_getexp_pd(__data(__x))};
}
else if constexpr (__have_avx512vl && __is_avx_ps<_Tp, _N>())
{
return {__private_init, _mm256_getexp_ps(__data(__x))};
}
else if constexpr (__have_avx512vl && __is_avx_pd<_Tp, _N>())
{
return {__private_init, _mm256_getexp_pd(__data(__x))};
}
else if constexpr (__have_avx512f && __is_avx_ps<_Tp, _N>())
{
return {__private_init,
__lo256(_mm512_getexp_ps(__auto_bitcast(__data(__x))))};
}
else if constexpr (__have_avx512f && __is_avx_pd<_Tp, _N>())
{
return {__private_init,
__lo256(_mm512_getexp_pd(__auto_bitcast(__data(__x))))};
}
else if constexpr (__is_avx512_ps<_Tp, _N>())
{
return {__private_init, _mm512_getexp_ps(__data(__x))};
}
else if constexpr (__is_avx512_pd<_Tp, _N>())
{
return {__private_init, _mm512_getexp_pd(__data(__x))};
}
else
{
using _V = simd<_Tp, _Abi>;
using namespace std::experimental::__proposed;
auto __is_normal = isnormal(__x);
const _V abs_x = abs(__x);
auto&& __exponent = [](const _V& __v) {
using namespace std::experimental::__proposed;
using _IV = rebind_simd_t<
std::conditional_t<sizeof(_Tp) == sizeof(_LLong), _LLong, int>,
_V>;
return (simd_reinterpret_cast<_IV>(__v) >>
(std::numeric_limits<_Tp>::digits - 1)) -
(std::numeric_limits<_Tp>::max_exponent - 1);
};
_V __r = static_simd_cast<_V>(__exponent(abs_x));
if (_GLIBCXX_SIMD_IS_LIKELY(all_of(__is_normal)))
{
return __r;
}
const auto __is_zero = __x == 0;
const auto __is_nan = isnan(__x);
const auto __is_inf = isinf(__x);
where(__is_zero, __r) = -std::numeric_limits<_Tp>::infinity();
where(__is_nan, __r) = __x;
where(__is_inf, __r) = std::numeric_limits<_Tp>::infinity();
__is_normal |= __is_zero || __is_nan || __is_inf;
if (all_of(__is_normal))
{
return __r;
}
const _V __scaled = abs_x * _Tp(0x1p112);
_V __scaled_exp = static_simd_cast<_V>(__exponent(__scaled) - 112);
where(__is_normal, __scaled_exp) = __r;
return __scaled_exp;
}
}
template <typename _Tp, typename _Abi>
enable_if_t<std::is_floating_point_v<_Tp>, simd<_Tp, _Abi>>
modf(const simd<_Tp, _Abi>& __x, simd<_Tp, _Abi>* __iptr)
{
const auto __integral = trunc(__x);
*__iptr = __integral;
auto __r = __x - __integral;
where(isinf(__x), __r) = _Tp();
return copysign(__r, __x);
}
_GLIBCXX_SIMD_MATH_CALL2_(scalbn, int)
_GLIBCXX_SIMD_MATH_CALL2_(scalbln, long)
_GLIBCXX_SIMD_MATH_CALL_(cbrt)
_GLIBCXX_SIMD_MATH_CALL_(abs)
_GLIBCXX_SIMD_MATH_CALL_(fabs)
template <class _Tp, class _Abi>
enable_if_t<!std::is_floating_point_v<_Tp> && std::is_signed_v<_Tp>, simd<_Tp, _Abi>> abs(
const simd<_Tp, _Abi> &__x)
{
return {__private_init, _Abi::_SimdImpl::__abs(__data(__x))};
}
template <class _Tp, class _Abi>
enable_if_t<!std::is_floating_point_v<_Tp> && std::is_signed_v<_Tp>, simd<_Tp, _Abi>> fabs(
const simd<_Tp, _Abi> &__x)
{
return {__private_init, _Abi::_SimdImpl::__abs(__data(__x))};
}
#define _GLIBCXX_SIMD_CVTING2(_NAME) \
template <typename _Tp, typename _Abi> \
_GLIBCXX_SIMD_INTRINSIC simd<_Tp, _Abi> _NAME( \
const simd<_Tp, _Abi>& __x, const __id<simd<_Tp, _Abi>>& __y) \
{ \
return _NAME(__x, __y); \
} \
template <typename _Tp, typename _Abi> \
_GLIBCXX_SIMD_INTRINSIC simd<_Tp, _Abi> _NAME( \
const __id<simd<_Tp, _Abi>>& __x, const simd<_Tp, _Abi>& __y) \
{ \
return _NAME(__x, __y); \
}
#define _GLIBCXX_SIMD_CVTING3(_NAME) \
template <typename _Tp, typename _Abi> \
_GLIBCXX_SIMD_INTRINSIC simd<_Tp, _Abi> _NAME( \
const __id<simd<_Tp, _Abi>>& __x, const simd<_Tp, _Abi>& __y, \
const simd<_Tp, _Abi>& __z) \
{ \
return _NAME(__x, __y, __z); \
} \
template <typename _Tp, typename _Abi> \
_GLIBCXX_SIMD_INTRINSIC simd<_Tp, _Abi> _NAME( \
const simd<_Tp, _Abi>& __x, const __id<simd<_Tp, _Abi>>& __y, \
const simd<_Tp, _Abi>& __z) \
{ \
return _NAME(__x, __y, __z); \
} \
template <typename _Tp, typename _Abi> \
_GLIBCXX_SIMD_INTRINSIC simd<_Tp, _Abi> _NAME( \
const simd<_Tp, _Abi>& __x, const simd<_Tp, _Abi>& __y, \
const __id<simd<_Tp, _Abi>>& __z) \
{ \
return _NAME(__x, __y, __z); \
} \
template <typename _Tp, typename _Abi> \
_GLIBCXX_SIMD_INTRINSIC simd<_Tp, _Abi> _NAME( \
const simd<_Tp, _Abi>& __x, const __id<simd<_Tp, _Abi>>& __y, \
const __id<simd<_Tp, _Abi>>& __z) \
{ \
return _NAME(__x, __y, __z); \
} \
template <typename _Tp, typename _Abi> \
_GLIBCXX_SIMD_INTRINSIC simd<_Tp, _Abi> _NAME( \
const __id<simd<_Tp, _Abi>>& __x, const simd<_Tp, _Abi>& __y, \
const __id<simd<_Tp, _Abi>>& __z) \
{ \
return _NAME(__x, __y, __z); \
} \
template <typename _Tp, typename _Abi> \
_GLIBCXX_SIMD_INTRINSIC simd<_Tp, _Abi> _NAME( \
const __id<simd<_Tp, _Abi>>& __x, const __id<simd<_Tp, _Abi>>& __y, \
const simd<_Tp, _Abi>& __z) \
{ \
return _NAME(__x, __y, __z); \
}
template <typename _R, typename _ToApply, typename _Tp, typename... _Tps>
_GLIBCXX_SIMD_INTRINSIC _R __fixed_size_apply(_ToApply&& __apply,
const _Tp& __arg0,
const _Tps&... __args)
{
return {__private_init, __data(__arg0).__apply_per_chunk(
[&](auto __impl, const auto&... __inner) {
using _V = typename decltype(__impl)::simd_type;
return __data(__apply(_V(__private_init, __inner)...));
},
__data(__args)...)};
}
template <typename _VV> __remove_cvref_t<_VV> __hypot(_VV __x, _VV __y)
{
using _V = __remove_cvref_t<_VV>;
using _Tp = typename _V::value_type;
if constexpr (_V::size() == 1)
{
return std::hypot(_Tp(__x[0]), _Tp(__y[0]));
}
else if constexpr (__is_fixed_size_abi_v<typename _V::abi_type>)
{
return __fixed_size_apply<_V>(
[](auto __a, auto __b) { return hypot(__a, __b); }, __x, __y);
}
else
{
using namespace __proposed::float_bitwise_operators;
using _Limits = std::numeric_limits<_Tp>;
_V __absx = abs(__x);
_V __absy = abs(__y);
_V __hi = max(__absx, __absy);
_V __lo = min(__absy, __absx);
constexpr _V __inf(_Limits::infinity());
if (_GLIBCXX_SIMD_IS_LIKELY(all_of(isnormal(__x)) &&
all_of(isnormal(__y))))
{
const _V __hi_exp = __hi & __inf;
const _V __scale = (__hi_exp ^ __inf) * _Tp(.5);
constexpr _V __mant_mask = _Limits::min() - _Limits::denorm_min();
const _V __h1 = (__hi & __mant_mask) | _V(1);
const _V __l1 = __lo * __scale;
return __hi_exp * sqrt(__h1 * __h1 + __l1 * __l1);
}
else
{
_V __scale = _V(1 / _Limits::min());
where(__hi >= _Limits::min(), __scale) =
((__hi & __inf) ^ __inf) * _Tp(.5);
_V __hi_exp = _Limits::min();
where(__hi >= _Limits::min(), __hi_exp) = __hi & __inf;
_V __h1 = __hi * __scale;
_V __l1 = __lo * __scale;
_V __r = __hi_exp * sqrt(__h1 * __h1 + __l1 * __l1);
#ifdef __STDC_IEC_559__
_V __fixup = __hi;
where(isunordered(__x, __y), __fixup) = _Limits::quiet_NaN();
where(isinf(__absx) || isinf(__absy), __fixup) = __inf;
where(!(__lo == 0 || isunordered(__x, __y) ||
(isinf(__absx) || isinf(__absy))),
__fixup) = __r;
__r = __fixup;
#endif
return __r;
}
}
}
template <typename _Tp, typename _Abi>
_GLIBCXX_SIMD_INTRINSIC simd<_Tp, _Abi>
hypot(const simd<_Tp, _Abi>& __x, const simd<_Tp, _Abi>& __y)
{
return __hypot<conditional_t<__is_fixed_size_abi_v<_Abi>,
const simd<_Tp, _Abi>&, simd<_Tp, _Abi>>>(__x,
__y);
}
_GLIBCXX_SIMD_CVTING2(hypot)
template <typename _VV> __remove_cvref_t<_VV> __hypot(_VV __x, _VV __y, _VV __z)
{
using _V = __remove_cvref_t<_VV>;
using _Abi = typename _V::abi_type;
using _Tp = typename _V::value_type;
if constexpr (__is_fixed_size_abi_v<_Abi> && _V::size() > 1)
{
return __fixed_size_apply<simd<_Tp, _Abi>>(
[](auto __a, auto __b, auto __c) { return hypot(__a, __b, __c); }, __x,
__y, __z);
}
else
{
using namespace __proposed::float_bitwise_operators;
using _Limits = std::numeric_limits<_Tp>;
const _V __absx = abs(__x);
const _V __absy = abs(__y);
const _V __absz = abs(__z);
_V __hi = max(max(__absx, __absy), __absz);
_V __l0 = min(__absz, max(__absx, __absy));
_V __l1 = min(__absy, __absx);
if constexpr (numeric_limits<_Tp>::digits == 64 &&
numeric_limits<_Tp>::max_exponent == 0x4000 &&
numeric_limits<_Tp>::min_exponent == -0x3FFD &&
_V::size() == 1)
{
#ifdef __STDC_IEC_559__
if (isinf(__absx[0]) || isinf(__absy[0]) || isinf(__absz[0]))
return _Limits::infinity();
else if (isunordered(__absx[0], __absy[0]+__absz[0]))
return _Limits::quiet_NaN();
else if (__l0[0] == 0 && __l1[0] == 0)
return __hi;
#endif
_V __hi_exp = __hi;
const _ULLong __tmp = 0x8000'0000'0000'0000ull;
std::memcpy(&__hi_exp, &__tmp, 8);
const _V __scale = 1 / __hi_exp;
__hi *= __scale;
__l0 *= __scale;
__l1 *= __scale;
return __hi_exp * sqrt((__l0 * __l0 + __l1 * __l1) + __hi * __hi);
}
else
{
constexpr _V __inf(_Limits::infinity());
if (_GLIBCXX_SIMD_IS_LIKELY(all_of(isnormal(__x)) &&
all_of(isnormal(__y)) &&
all_of(isnormal(__z))))
{
const _V __hi_exp = __hi & __inf;
const _V __scale = (__hi_exp ^ __inf) * _Tp(.5);
constexpr _V __mant_mask = _Limits::min() - _Limits::denorm_min();
const _V __h1 = (__hi & __mant_mask) | _V(1);
__l0 *= __scale;
__l1 *= __scale;
const _V __lo =
__l0 * __l0 + __l1 * __l1;
return __hi_exp * sqrt(__lo + __h1 * __h1);
}
else
{
_V __scale = _V(1 / _Limits::min());
where(__hi >= _Limits::min(), __scale) =
((__hi & __inf) ^ __inf) * _Tp(.5);
_V __hi_exp = _Limits::min();
where(__hi >= _Limits::min(), __hi_exp) =
__hi & __inf;
_V __h1 = __hi * __scale;
__l0 *= __scale;
__l1 *= __scale;
_V __lo =
__l0 * __l0 + __l1 * __l1;
_V __r = __hi_exp * sqrt(__lo + __h1 * __h1);
#ifdef __STDC_IEC_559__
_V __fixup = __hi;
where(isunordered(__x, __y + __z), __fixup) =
_Limits::quiet_NaN();
where(isinf(__absx) || isinf(__absy) || isinf(__absz), __fixup) =
__inf;
where(!(__lo == 0 || isunordered(__x, __y + __z) ||
isinf(__absx) || isinf(__absy) || isinf(__absz)),
__fixup) = __r;
__r = __fixup;
#endif
return __r;
}
}
}
}
template <typename _Tp, typename _Abi>
_GLIBCXX_SIMD_INTRINSIC simd<_Tp, _Abi> hypot(const simd<_Tp, _Abi>& __x,
const simd<_Tp, _Abi>& __y,
const simd<_Tp, _Abi>& __z)
{
return __hypot<conditional_t<__is_fixed_size_abi_v<_Abi>,
const simd<_Tp, _Abi>&, simd<_Tp, _Abi>>>(
__x, __y, __z);
}
_GLIBCXX_SIMD_CVTING3(hypot)
_GLIBCXX_SIMD_MATH_CALL2_(pow, _Tp)
_GLIBCXX_SIMD_MATH_CALL_(sqrt)
_GLIBCXX_SIMD_MATH_CALL_(erf)
_GLIBCXX_SIMD_MATH_CALL_(erfc)
_GLIBCXX_SIMD_MATH_CALL_(lgamma)
_GLIBCXX_SIMD_MATH_CALL_(tgamma)
_GLIBCXX_SIMD_MATH_CALL_(ceil)
_GLIBCXX_SIMD_MATH_CALL_(floor)
_GLIBCXX_SIMD_MATH_CALL_(nearbyint)
_GLIBCXX_SIMD_MATH_CALL_(rint)
_GLIBCXX_SIMD_MATH_CALL_(lrint)
_GLIBCXX_SIMD_MATH_CALL_(llrint)
_GLIBCXX_SIMD_MATH_CALL_(round)
_GLIBCXX_SIMD_MATH_CALL_(lround)
_GLIBCXX_SIMD_MATH_CALL_(llround)
_GLIBCXX_SIMD_MATH_CALL_(trunc)
_GLIBCXX_SIMD_MATH_CALL2_(fmod, _Tp)
_GLIBCXX_SIMD_MATH_CALL2_(remainder, _Tp)
_GLIBCXX_SIMD_MATH_CALL3_(remquo, _Tp, int *)
template <typename _Tp, typename _Abi>
enable_if_t<std::is_floating_point_v<_Tp>, simd<_Tp, _Abi>>
copysign(const simd<_Tp, _Abi>& __x, const simd<_Tp, _Abi>& __y)
{
using namespace std::experimental::__proposed::float_bitwise_operators;
const auto __signmask = -simd<_Tp, _Abi>();
return (__x & (__x ^ __signmask)) | (__y & __signmask);
}
_GLIBCXX_SIMD_MATH_CALL2_(nextafter, _Tp)
_GLIBCXX_SIMD_MATH_CALL2_(fdim, _Tp)
_GLIBCXX_SIMD_MATH_CALL2_(fmax, _Tp)
_GLIBCXX_SIMD_MATH_CALL2_(fmin, _Tp)
_GLIBCXX_SIMD_MATH_CALL3_(fma, _Tp, _Tp)
_GLIBCXX_SIMD_MATH_CALL_(fpclassify)
_GLIBCXX_SIMD_MATH_CALL_(isfinite)
template <class _Tp, class _Abi, class...,
class _R = std::experimental::__math_return_type_t<bool, _Tp, _Abi>>
enable_if_t<std::is_floating_point_v<_Tp>, _R> isinf(
std::experimental::simd<_Tp, _Abi> __x)
{
return {std::experimental::__private_init,
_Abi::_SimdImpl::__isinf(std::experimental::__data(__x))};
}
template <class _Tp, class _Abi, class...,
class _R = std::experimental::__math_return_type_t<bool, _Tp, _Abi>>
enable_if_t<std::is_floating_point_v<_Tp>, _R> isnan(
std::experimental::simd<_Tp, _Abi> __x)
{
return {std::experimental::__private_init,
_Abi::_SimdImpl::__isnan(std::experimental::__data(__x))};
}
_GLIBCXX_SIMD_MATH_CALL_(isnormal)
template <class..., class _Tp, class _Abi>
std::experimental::simd_mask<_Tp, _Abi>
signbit(std::experimental::simd<_Tp, _Abi> __x)
{
if constexpr (std::is_integral_v<_Tp>)
{
if constexpr (std::is_unsigned_v<_Tp>)
return std::experimental::simd_mask<_Tp, _Abi>{};
else
return __x < 0;
}
else
return {std::experimental::__private_init,
_Abi::_SimdImpl::__signbit(std::experimental::__data(__x))};
}
_GLIBCXX_SIMD_MATH_CALL2_(isgreater, _Tp)
_GLIBCXX_SIMD_MATH_CALL2_(isgreaterequal, _Tp)
_GLIBCXX_SIMD_MATH_CALL2_(isless, _Tp)
_GLIBCXX_SIMD_MATH_CALL2_(islessequal, _Tp)
_GLIBCXX_SIMD_MATH_CALL2_(islessgreater, _Tp)
_GLIBCXX_SIMD_MATH_CALL2_(isunordered, _Tp)
template <class _Tp, class _Abi>
enable_if_t<std::is_floating_point_v<_Tp>, simd<_Tp, _Abi>> assoc_laguerre(
const std::experimental::fixed_size_simd<unsigned, std::experimental::simd_size_v<_Tp, _Abi>> &__n,
const std::experimental::fixed_size_simd<unsigned, std::experimental::simd_size_v<_Tp, _Abi>> &__m,
const std::experimental::simd<_Tp, _Abi> &__x)
{
return std::experimental::simd<_Tp, _Abi>([&](auto __i) { return std::assoc_laguerre(__n[__i], __m[__i], __x[__i]); });
}
template <class _Tp, class _Abi>
enable_if_t<std::is_floating_point_v<_Tp>, simd<_Tp, _Abi>> assoc_legendre(
const std::experimental::fixed_size_simd<unsigned, std::experimental::simd_size_v<_Tp, _Abi>> &__n,
const std::experimental::fixed_size_simd<unsigned, std::experimental::simd_size_v<_Tp, _Abi>> &__m,
const std::experimental::simd<_Tp, _Abi> &__x)
{
return std::experimental::simd<_Tp, _Abi>([&](auto __i) { return std::assoc_legendre(__n[__i], __m[__i], __x[__i]); });
}
_GLIBCXX_SIMD_MATH_CALL2_(beta, _Tp)
_GLIBCXX_SIMD_MATH_CALL_(comp_ellint_1)
_GLIBCXX_SIMD_MATH_CALL_(comp_ellint_2)
_GLIBCXX_SIMD_MATH_CALL2_(comp_ellint_3, _Tp)
_GLIBCXX_SIMD_MATH_CALL2_(cyl_bessel_i, _Tp)
_GLIBCXX_SIMD_MATH_CALL2_(cyl_bessel_j, _Tp)
_GLIBCXX_SIMD_MATH_CALL2_(cyl_bessel_k, _Tp)
_GLIBCXX_SIMD_MATH_CALL2_(cyl_neumann, _Tp)
_GLIBCXX_SIMD_MATH_CALL2_(ellint_1, _Tp)
_GLIBCXX_SIMD_MATH_CALL2_(ellint_2, _Tp)
_GLIBCXX_SIMD_MATH_CALL3_(ellint_3, _Tp, _Tp)
_GLIBCXX_SIMD_MATH_CALL_(expint)
template <class _Tp, class _Abi>
enable_if_t<std::is_floating_point_v<_Tp>, simd<_Tp, _Abi>> hermite(
const std::experimental::fixed_size_simd<unsigned, std::experimental::simd_size_v<_Tp, _Abi>> &__n,
const std::experimental::simd<_Tp, _Abi> &__x)
{
return std::experimental::simd<_Tp, _Abi>([&](auto __i) { return std::hermite(__n[__i], __x[__i]); });
}
template <class _Tp, class _Abi>
enable_if_t<std::is_floating_point_v<_Tp>, simd<_Tp, _Abi>> laguerre(
const std::experimental::fixed_size_simd<unsigned, std::experimental::simd_size_v<_Tp, _Abi>> &__n,
const std::experimental::simd<_Tp, _Abi> &__x)
{
return std::experimental::simd<_Tp, _Abi>([&](auto __i) { return std::laguerre(__n[__i], __x[__i]); });
}
template <class _Tp, class _Abi>
enable_if_t<std::is_floating_point_v<_Tp>, simd<_Tp, _Abi>> legendre(
const std::experimental::fixed_size_simd<unsigned, std::experimental::simd_size_v<_Tp, _Abi>> &__n,
const std::experimental::simd<_Tp, _Abi> &__x)
{
return std::experimental::simd<_Tp, _Abi>([&](auto __i) { return std::legendre(__n[__i], __x[__i]); });
}
_GLIBCXX_SIMD_MATH_CALL_(riemann_zeta)
template <class _Tp, class _Abi>
enable_if_t<std::is_floating_point_v<_Tp>, simd<_Tp, _Abi>> sph_bessel(
const std::experimental::fixed_size_simd<unsigned, std::experimental::simd_size_v<_Tp, _Abi>> &__n,
const std::experimental::simd<_Tp, _Abi> &__x)
{
return std::experimental::simd<_Tp, _Abi>([&](auto __i) { return std::sph_bessel(__n[__i], __x[__i]); });
}
template <class _Tp, class _Abi>
enable_if_t<std::is_floating_point_v<_Tp>, simd<_Tp, _Abi>> sph_legendre(
const std::experimental::fixed_size_simd<unsigned, std::experimental::simd_size_v<_Tp, _Abi>> &__l,
const std::experimental::fixed_size_simd<unsigned, std::experimental::simd_size_v<_Tp, _Abi>> &__m,
const std::experimental::simd<_Tp, _Abi> &theta)
{
return std::experimental::simd<_Tp, _Abi>([&](auto __i) { return std::assoc_legendre(__l[__i], __m[__i], theta[__i]); });
}
template <class _Tp, class _Abi>
enable_if_t<std::is_floating_point_v<_Tp>, simd<_Tp, _Abi>> sph_neumann(
const std::experimental::fixed_size_simd<unsigned, std::experimental::simd_size_v<_Tp, _Abi>> &__n,
const std::experimental::simd<_Tp, _Abi> &__x)
{
return std::experimental::simd<_Tp, _Abi>([&](auto __i) { return std::sph_neumann(__n[__i], __x[__i]); });
}
#undef _GLIBCXX_SIMD_MATH_CALL_
#undef _GLIBCXX_SIMD_MATH_CALL2_
#undef _GLIBCXX_SIMD_MATH_CALL3_
_GLIBCXX_SIMD_END_NAMESPACE
#endif
#endif
#pragma GCC diagnostic pop
#if defined __GNUC__ && __GNUC__ < 9
#undef __gnu__
#endif
#endif
