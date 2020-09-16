#ifndef _GLIBCXX_EXPERIMENTAL_SIMD
#define _GLIBCXX_EXPERIMENTAL_SIMD 
#define __cpp_lib_experimental_parallel_simd 201803
#pragma GCC diagnostic push
#ifndef __clang__
#pragma GCC diagnostic ignored "-Wpsabi"
#endif
#ifndef __OPTIMIZE__
#pragma GCC diagnostic ignored "-Wold-style-cast"
#endif
#ifndef _GLIBCXX_EXPERIMENTAL_SIMD_DETAIL_H_
#define _GLIBCXX_EXPERIMENTAL_SIMD_DETAIL_H_ 
#if __cplusplus >= 201703L
#include <cstddef>
#include <cstdint>
#define Vir_SIMD_VERSION_STRING "2.0.0"
#define _GLIBCXX_SIMD_BEGIN_NAMESPACE \
namespace std _GLIBCXX_VISIBILITY(default) \
{ \
_GLIBCXX_BEGIN_NAMESPACE_VERSION \
namespace experimental { \
inline namespace parallelism_v2 {
#define _GLIBCXX_SIMD_END_NAMESPACE \
} \
} \
_GLIBCXX_END_NAMESPACE_VERSION \
}
#if defined __ARM_NEON
#define _GLIBCXX_SIMD_HAVE_NEON 1
#else
#define _GLIBCXX_SIMD_HAVE_NEON 0
#endif
#if defined __ARM_NEON && (__ARM_ARCH >= 8 || defined __aarch64__)
#define _GLIBCXX_SIMD_HAVE_NEON_A32 1
#else
#define _GLIBCXX_SIMD_HAVE_NEON_A32 0
#endif
#if defined __ARM_NEON && defined __aarch64__
#define _GLIBCXX_SIMD_HAVE_NEON_A64 1
#else
#define _GLIBCXX_SIMD_HAVE_NEON_A64 0
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
#ifdef __clang__
#define _GLIBCXX_SIMD_NORMAL_MATH 
#else
#define _GLIBCXX_SIMD_NORMAL_MATH \
[[__gnu__::__optimize__("finite-math-only,no-signed-zeros")]]
#endif
#define _GLIBCXX_SIMD_NEVER_INLINE [[__gnu__::__noinline__]]
#define _GLIBCXX_SIMD_INTRINSIC \
[[__gnu__::__always_inline__, __gnu__::__artificial__]] inline
#define _GLIBCXX_SIMD_ALWAYS_INLINE [[__gnu__::__always_inline__]] inline
#define _GLIBCXX_SIMD_IS_UNLIKELY(__x) __builtin_expect(__x, 0)
#define _GLIBCXX_SIMD_IS_LIKELY(__x) __builtin_expect(__x, 1)
#if defined __STRICT_ANSI__ && __STRICT_ANSI__
#define _GLIBCXX_SIMD_CONSTEXPR 
#define _GLIBCXX_SIMD_USE_CONSTEXPR_API const
#else
#define _GLIBCXX_SIMD_CONSTEXPR constexpr
#define _GLIBCXX_SIMD_USE_CONSTEXPR_API constexpr
#endif
#if defined __clang__
#define _GLIBCXX_SIMD_USE_CONSTEXPR const
#else
#define _GLIBCXX_SIMD_USE_CONSTEXPR constexpr
#endif
#define _GLIBCXX_SIMD_LIST_BINARY(__macro) __macro(|) __macro(&) __macro(^)
#define _GLIBCXX_SIMD_LIST_SHIFTS(__macro) __macro(<<) __macro(>>)
#define _GLIBCXX_SIMD_LIST_ARITHMETICS(__macro) \
__macro(+) __macro(-) __macro(*) __macro(/) __macro(%)
#define _GLIBCXX_SIMD_ALL_BINARY(__macro) \
_GLIBCXX_SIMD_LIST_BINARY(__macro) static_assert(true)
#define _GLIBCXX_SIMD_ALL_SHIFTS(__macro) \
_GLIBCXX_SIMD_LIST_SHIFTS(__macro) static_assert(true)
#define _GLIBCXX_SIMD_ALL_ARITHMETICS(__macro) \
_GLIBCXX_SIMD_LIST_ARITHMETICS(__macro) static_assert(true)
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
#define _GLIBCXX_SIMD_WORKAROUND_PR89229 1
#define _GLIBCXX_SIMD_WORKAROUND_PR90993 1
#if _GLIBCXX_SIMD_X86INTRIN
#define _GLIBCXX_SIMD_WORKAROUND_XXX_1 1
#endif
#define _GLIBCXX_SIMD_WORKAROUND_PR90424 1
#if _GLIBCXX_SIMD_X86INTRIN
#define _GLIBCXX_SIMD_WORKAROUND_XXX_3 1
#endif
#define _GLIBCXX_SIMD_WORKAROUND_XXX_4 1
#if __GNUC__ < 10 && defined __SSSE3__ && _GLIBCXX_SIMD_X86INTRIN
#define _GLIBCXX_SIMD_WORKAROUND_PR91533 1
#endif
#if __GNUC__ < 10 && defined __aarch64__
#define _GLIBCXX_SIMD_WORKAROUND_XXX_5 1
#endif
#define _GLIBCXX_SIMD_FIX_P2TS_ISSUE65 1
#define _GLIBCXX_SIMD_FIX_P2TS_ISSUE66 1
#endif
#endif
#ifndef _GLIBCXX_EXPERIMENTAL_SIMD_H
#define _GLIBCXX_EXPERIMENTAL_SIMD_H 
#if __cplusplus >= 201703L
#include <type_traits>
namespace std {
template <template <typename> class _Trait, typename _Tp, typename = void>
struct __value_exists_impl : std::false_type
{
};
template <template <typename> class _Trait, typename _Tp>
struct __value_exists_impl<_Trait, _Tp,
std::void_t<decltype(_Trait<_Tp>::value)>>
: std::true_type
{
};
template <typename _Tp, bool = std::is_arithmetic_v<_Tp>> struct __digits_impl
{
};
template <typename _Tp> struct __digits_impl<_Tp, true>
{
static inline constexpr int value
= sizeof(_Tp) * __CHAR_BIT__ - std::is_signed_v<_Tp>;
};
template <> struct __digits_impl<float, true>
{
static inline constexpr int value = __FLT_MANT_DIG__;
};
template <> struct __digits_impl<double, true>
{
static inline constexpr int value = __DBL_MANT_DIG__;
};
template <> struct __digits_impl<long double, true>
{
static inline constexpr int value = __LDBL_MANT_DIG__;
};
template <typename _Tp, bool = std::is_arithmetic_v<_Tp>> struct __digits10_impl
{
};
template <typename _Tp> struct __digits10_impl<_Tp, true>
{
static inline constexpr int value = __digits_impl<_Tp>::value * 643L / 2136;
};
template <> struct __digits10_impl<float, true>
{
static inline constexpr int value = __FLT_DIG__;
};
template <> struct __digits10_impl<double, true>
{
static inline constexpr int value = __DBL_DIG__;
};
template <> struct __digits10_impl<long double, true>
{
static inline constexpr int value = __LDBL_DIG__;
};
template <typename _Tp, bool = std::is_arithmetic_v<_Tp>>
struct __max_digits10_impl
{
};
template <typename _Tp> struct __max_digits10_impl<_Tp, true>
{
static inline constexpr int value
= std::is_floating_point_v<_Tp>
? 2 + __digits_impl<_Tp>::value * 643L / 2136
: __digits10_impl<_Tp>::value + 1;
};
template <typename _Tp> struct __max_exponent_impl
{
};
template <> struct __max_exponent_impl<float>
{
static inline constexpr int value = __FLT_MAX_EXP__;
};
template <> struct __max_exponent_impl<double>
{
static inline constexpr int value = __DBL_MAX_EXP__;
};
template <> struct __max_exponent_impl<long double>
{
static inline constexpr int value = __LDBL_MAX_EXP__;
};
template <typename _Tp> struct __max_exponent10_impl
{
};
template <> struct __max_exponent10_impl<float>
{
static inline constexpr int value = __FLT_MAX_10_EXP__;
};
template <> struct __max_exponent10_impl<double>
{
static inline constexpr int value = __DBL_MAX_10_EXP__;
};
template <> struct __max_exponent10_impl<long double>
{
static inline constexpr int value = __LDBL_MAX_10_EXP__;
};
template <typename _Tp> struct __min_exponent_impl
{
};
template <> struct __min_exponent_impl<float>
{
static inline constexpr int value = __FLT_MIN_EXP__;
};
template <> struct __min_exponent_impl<double>
{
static inline constexpr int value = __DBL_MIN_EXP__;
};
template <> struct __min_exponent_impl<long double>
{
static inline constexpr int value = __LDBL_MIN_EXP__;
};
template <typename _Tp> struct __min_exponent10_impl
{
};
template <> struct __min_exponent10_impl<float>
{
static inline constexpr int value = __FLT_MIN_10_EXP__;
};
template <> struct __min_exponent10_impl<double>
{
static inline constexpr int value = __DBL_MIN_10_EXP__;
};
template <> struct __min_exponent10_impl<long double>
{
static inline constexpr int value = __LDBL_MIN_10_EXP__;
};
template <typename _Tp, bool = std::is_arithmetic_v<_Tp>> struct __radix_impl
{
};
template <typename _Tp> struct __radix_impl<_Tp, true>
{
static inline constexpr int value
= std::is_floating_point_v<_Tp> ? __FLT_RADIX__ : 2;
};
template <template <typename> class _Trait, typename _Tp>
struct __value_exists : __value_exists_impl<_Trait, _Tp>
{
};
template <template <typename> class _Trait, typename _Tp>
inline constexpr bool __value_exists_v = __value_exists<_Trait, _Tp>::value;
template <template <typename> class _Trait, typename _Tp, typename _Up = _Tp>
inline constexpr _Up
__value_or(_Up __def = _Up()) noexcept
{
if constexpr (__value_exists_v<_Trait, _Tp>)
return static_cast<_Up>(_Trait<_Tp>::value);
else
return __def;
}
template <typename _Tp, bool = std::is_arithmetic_v<_Tp>> struct __norm_min_impl
{
};
template <typename _Tp> struct __norm_min_impl<_Tp, true>
{
static inline constexpr _Tp value = 1;
};
template <> struct __norm_min_impl<float, true>
{
static inline constexpr float value = __FLT_MIN__;
};
template <> struct __norm_min_impl<double, true>
{
static inline constexpr double value = __DBL_MIN__;
};
template <> struct __norm_min_impl<long double, true>
{
static inline constexpr long double value = __LDBL_MIN__;
};
template <typename _Tp> struct __denorm_min_impl : __norm_min_impl<_Tp>
{
};
#if __FLT_HAS_DENORM__
template <> struct __denorm_min_impl<float>
{
static inline constexpr float value = __FLT_DENORM_MIN__;
};
#endif
#if __DBL_HAS_DENORM__
template <> struct __denorm_min_impl<double>
{
static inline constexpr double value = __DBL_DENORM_MIN__;
};
#endif
#if __LDBL_HAS_DENORM__
template <> struct __denorm_min_impl<long double>
{
static inline constexpr long double value = __LDBL_DENORM_MIN__;
};
#endif
template <typename _Tp> struct __epsilon_impl
{
};
template <> struct __epsilon_impl<float>
{
static inline constexpr float value = __FLT_EPSILON__;
};
template <> struct __epsilon_impl<double>
{
static inline constexpr double value = __DBL_EPSILON__;
};
template <> struct __epsilon_impl<long double>
{
static inline constexpr long double value = __LDBL_EPSILON__;
};
template <typename _Tp, bool = std::is_arithmetic_v<_Tp>>
struct __finite_min_impl
{
};
template <typename _Tp> struct __finite_min_impl<_Tp, true>
{
static inline constexpr _Tp value
= std::is_unsigned_v<_Tp> ? _Tp()
: -2 * (_Tp(1) << __digits_impl<_Tp>::value - 1);
};
template <> struct __finite_min_impl<float, true>
{
static inline constexpr float value = -__FLT_MAX__;
};
template <> struct __finite_min_impl<double, true>
{
static inline constexpr double value = -__DBL_MAX__;
};
template <> struct __finite_min_impl<long double, true>
{
static inline constexpr long double value = -__LDBL_MAX__;
};
template <typename _Tp, bool = std::is_arithmetic_v<_Tp>>
struct __finite_max_impl
{
};
template <typename _Tp> struct __finite_max_impl<_Tp, true>
{
static inline constexpr _Tp value = ~__finite_min_impl<_Tp>::value;
};
template <> struct __finite_max_impl<float, true>
{
static inline constexpr float value = __FLT_MAX__;
};
template <> struct __finite_max_impl<double, true>
{
static inline constexpr double value = __DBL_MAX__;
};
template <> struct __finite_max_impl<long double, true>
{
static inline constexpr long double value = __LDBL_MAX__;
};
template <typename _Tp> struct __infinity_impl
{
};
#if __FLT_HAS_INFINITY__
template <> struct __infinity_impl<float>
{
static inline constexpr float value = __builtin_inff();
};
#endif
#if __DBL_HAS_INFINITY__
template <> struct __infinity_impl<double>
{
static inline constexpr double value = __builtin_inf();
};
#endif
#if __LDBL_HAS_INFINITY__
template <> struct __infinity_impl<long double>
{
static inline constexpr long double value = __builtin_infl();
};
#endif
template <typename _Tp> struct __quiet_NaN_impl
{
};
#if __FLT_HAS_QUIET_NAN__
template <> struct __quiet_NaN_impl<float>
{
static inline constexpr float value = __builtin_nanf("");
};
#endif
#if __DBL_HAS_QUIET_NAN__
template <> struct __quiet_NaN_impl<double>
{
static inline constexpr double value = __builtin_nan("");
};
#endif
#if __LDBL_HAS_QUIET_NAN__
template <> struct __quiet_NaN_impl<long double>
{
static inline constexpr long double value = __builtin_nanl("");
};
#endif
template <typename _Tp, bool = std::is_floating_point_v<_Tp>>
struct __reciprocal_overflow_threshold_impl
{
};
template <typename _Tp> struct __reciprocal_overflow_threshold_impl<_Tp, true>
{
static constexpr _Tp _S_search(_Tp __ok, _Tp __overflows)
{
const _Tp __mid = (__ok + __overflows) / 2;
if (__mid == __ok || __mid == __overflows)
return __ok;
else if (_Tp(1) / (__radix_impl<_Tp>::value * __mid)
<= __finite_max_impl<_Tp>::value / __radix_impl<_Tp>::value)
return _S_search(__mid, __overflows);
else
return _S_search(__ok, __mid);
}
static inline constexpr _Tp value
= _S_search(_Tp(1.01) / __finite_max_impl<_Tp>::value,
_Tp(0.99) / __finite_max_impl<_Tp>::value);
};
template <typename _Tp, bool = std::is_floating_point_v<_Tp>>
struct __round_error_impl
{
};
template <typename _Tp> struct __round_error_impl<_Tp, true>
{
static inline constexpr _Tp value = 0.5;
};
template <typename _Tp> struct __signaling_NaN_impl
{
};
#if __FLT_HAS_QUIET_NAN__
template <> struct __signaling_NaN_impl<float>
{
static inline constexpr float value = __builtin_nansf("");
};
#endif
#if __DBL_HAS_QUIET_NAN__
template <> struct __signaling_NaN_impl<double>
{
static inline constexpr double value = __builtin_nans("");
};
#endif
#if __LDBL_HAS_QUIET_NAN__
template <> struct __signaling_NaN_impl<long double>
{
static inline constexpr long double value = __builtin_nansl("");
};
#endif
template <typename _Tp>
struct __denorm_min : __denorm_min_impl<std::remove_cv_t<_Tp>>
{
};
template <typename _Tp> struct __epsilon : __epsilon_impl<std::remove_cv_t<_Tp>>
{
};
template <typename _Tp>
struct __finite_max : __finite_max_impl<std::remove_cv_t<_Tp>>
{
};
template <typename _Tp>
struct __finite_min : __finite_min_impl<std::remove_cv_t<_Tp>>
{
};
template <typename _Tp>
struct __infinity : __infinity_impl<std::remove_cv_t<_Tp>>
{
};
template <typename _Tp>
struct __norm_min : __norm_min_impl<std::remove_cv_t<_Tp>>
{
};
template <typename _Tp>
struct __quiet_NaN : __quiet_NaN_impl<std::remove_cv_t<_Tp>>
{
};
template <typename _Tp>
struct __reciprocal_overflow_threshold
: __reciprocal_overflow_threshold_impl<std::remove_cv_t<_Tp>>
{
};
template <typename _Tp>
struct __round_error : __round_error_impl<std::remove_cv_t<_Tp>>
{
};
template <typename _Tp>
struct __signaling_NaN : __signaling_NaN_impl<std::remove_cv_t<_Tp>>
{
};
template <typename _Tp>
inline constexpr auto __denorm_min_v = __denorm_min<_Tp>::value;
template <typename _Tp>
inline constexpr auto __epsilon_v = __epsilon<_Tp>::value;
template <typename _Tp>
inline constexpr auto __finite_max_v = __finite_max<_Tp>::value;
template <typename _Tp>
inline constexpr auto __finite_min_v = __finite_min<_Tp>::value;
template <typename _Tp>
inline constexpr auto __infinity_v = __infinity<_Tp>::value;
template <typename _Tp>
inline constexpr auto __norm_min_v = __norm_min<_Tp>::value;
template <typename _Tp>
inline constexpr auto __quiet_NaN_v = __quiet_NaN<_Tp>::value;
template <typename _Tp>
inline constexpr auto __reciprocal_overflow_threshold_v
= __reciprocal_overflow_threshold<_Tp>::value;
template <typename _Tp>
inline constexpr auto __round_error_v = __round_error<_Tp>::value;
template <typename _Tp>
inline constexpr auto __signaling_NaN_v = __signaling_NaN<_Tp>::value;
template <typename _Tp> struct __digits : __digits_impl<std::remove_cv_t<_Tp>>
{
};
template <typename _Tp>
struct __digits10 : __digits10_impl<std::remove_cv_t<_Tp>>
{
};
template <typename _Tp>
struct __max_digits10 : __max_digits10_impl<std::remove_cv_t<_Tp>>
{
};
template <typename _Tp>
struct __max_exponent : __max_exponent_impl<std::remove_cv_t<_Tp>>
{
};
template <typename _Tp>
struct __max_exponent10 : __max_exponent10_impl<std::remove_cv_t<_Tp>>
{
};
template <typename _Tp>
struct __min_exponent : __min_exponent_impl<std::remove_cv_t<_Tp>>
{
};
template <typename _Tp>
struct __min_exponent10 : __min_exponent10_impl<std::remove_cv_t<_Tp>>
{
};
template <typename _Tp> struct __radix : __radix_impl<std::remove_cv_t<_Tp>>
{
};
template <typename _Tp> inline constexpr auto __digits_v = __digits<_Tp>::value;
template <typename _Tp>
inline constexpr auto __digits10_v = __digits10<_Tp>::value;
template <typename _Tp>
inline constexpr auto __max_digits10_v = __max_digits10<_Tp>::value;
template <typename _Tp>
inline constexpr auto __max_exponent_v = __max_exponent<_Tp>::value;
template <typename _Tp>
inline constexpr auto __max_exponent10_v = __max_exponent10<_Tp>::value;
template <typename _Tp>
inline constexpr auto __min_exponent_v = __min_exponent<_Tp>::value;
template <typename _Tp>
inline constexpr auto __min_exponent10_v = __min_exponent10<_Tp>::value;
template <typename _Tp> inline constexpr auto __radix_v = __radix<_Tp>::value;
template <typename _Tp> struct __has_iec559_storage_format : std::true_type
{
};
template <typename _Tp>
inline constexpr bool __has_iec559_storage_format_v
= __has_iec559_storage_format<_Tp>::value;
template <template <typename> class _Trait, typename _Tp>
struct __has_iec559_behavior : std::false_type
{
};
template <template <typename> class _Trait, typename _Tp>
inline constexpr bool __has_iec559_behavior_v
= __has_iec559_behavior<_Trait, _Tp>::value;
#if !__FINITE_MATH_ONLY__
#if __FLT_HAS_QUIET_NAN__
template <> struct __has_iec559_behavior<__quiet_NaN, float> : std::true_type
{
};
#endif
#if __DBL_HAS_QUIET_NAN__
template <> struct __has_iec559_behavior<__quiet_NaN, double> : std::true_type
{
};
#endif
#if __LDBL_HAS_QUIET_NAN__
template <>
struct __has_iec559_behavior<__quiet_NaN, long double> : std::true_type
{
};
#endif
#if __FLT_HAS_INFINITY__
template <> struct __has_iec559_behavior<__infinity, float> : std::true_type
{
};
#endif
#if __DBL_HAS_INFINITY__
template <> struct __has_iec559_behavior<__infinity, double> : std::true_type
{
};
#endif
#if __LDBL_HAS_INFINITY__
template <>
struct __has_iec559_behavior<__infinity, long double> : std::true_type
{
};
#endif
#ifdef __SUPPORT_SNAN__
#if __FLT_HAS_QUIET_NAN__
template <>
struct __has_iec559_behavior<__signaling_NaN, float> : std::true_type
{
};
#endif
#if __DBL_HAS_QUIET_NAN__
template <>
struct __has_iec559_behavior<__signaling_NaN, double> : std::true_type
{
};
#endif
#if __LDBL_HAS_QUIET_NAN__
template <>
struct __has_iec559_behavior<__signaling_NaN, long double> : std::true_type
{
};
#endif
#endif
#endif
}
#include <bitset>
#ifdef _GLIBCXX_DEBUG_UB
#include <cstdio>
#endif
#include <cstring>
#include <functional>
#include <iosfwd>
#include <utility>
#if _GLIBCXX_SIMD_X86INTRIN
#include <x86intrin.h>
#elif _GLIBCXX_SIMD_HAVE_NEON
#include <arm_neon.h>
#endif
_GLIBCXX_SIMD_BEGIN_NAMESPACE
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
constexpr std::size_t
__next_power_of_2(std::size_t __x)
{
return (__x & (__x - 1)) == 0 ? __x
: __next_power_of_2((__x | (__x >> 1)) + 1);
}
namespace simd_abi {
struct _Scalar;
template <int _Np> struct _Fixed;
template <int _UsedBytes> struct _VecBuiltin;
template <int _UsedBytes> struct _VecBltnBtmsk;
template <typename _Tp, int _Np> using _VecN = _VecBuiltin<sizeof(_Tp) * _Np>;
template <int _UsedBytes = 16> using _Sse = _VecBuiltin<_UsedBytes>;
template <int _UsedBytes = 32> using _Avx = _VecBuiltin<_UsedBytes>;
template <int _UsedBytes = 64> using _Avx512 = _VecBltnBtmsk<_UsedBytes>;
template <int _UsedBytes = 16> using _Neon = _VecBuiltin<_UsedBytes>;
using __sse = _Sse<>;
using __avx = _Avx<>;
using __avx512 = _Avx512<>;
using __neon = _Neon<>;
using __neon128 = _Neon<16>;
using __neon64 = _Neon<8>;
template <typename _Tp, size_t _Np, typename...> struct deduce;
template <int _Np> using fixed_size = _Fixed<_Np>;
using scalar = _Scalar;
}
template <typename _Tp> struct is_simd;
template <typename _Tp> struct is_simd_mask;
template <typename _Tp, typename _Abi> class simd;
template <typename _Tp, typename _Abi> class simd_mask;
template <typename _Tp, typename _Abi> struct simd_size;
struct element_aligned_tag
{
template <typename _Tp, typename _Up = typename _Tp::value_type>
static constexpr size_t _S_alignment = alignof(_Up);
template <typename _Tp, typename _Up>
_GLIBCXX_SIMD_INTRINSIC static constexpr _Up* _S_apply(_Up* __ptr)
{
return __ptr;
}
};
struct vector_aligned_tag
{
template <typename _Tp, typename _Up = typename _Tp::value_type>
static constexpr size_t _S_alignment
= __next_power_of_2(sizeof(_Up) * _Tp::size());
template <typename _Tp, typename _Up>
_GLIBCXX_SIMD_INTRINSIC static constexpr _Up* _S_apply(_Up* __ptr)
{
return static_cast<_Up*>(
__builtin_assume_aligned(__ptr, _S_alignment<_Tp, _Up>));
}
};
template <size_t _Np> struct overaligned_tag
{
template <typename _Tp, typename _Up = typename _Tp::value_type>
static constexpr size_t _S_alignment = _Np;
template <typename _Tp, typename _Up>
_GLIBCXX_SIMD_INTRINSIC static constexpr _Up* _S_apply(_Up* __ptr)
{
return static_cast<_Up*>(__builtin_assume_aligned(__ptr, _Np));
}
};
inline constexpr element_aligned_tag element_aligned = {};
inline constexpr vector_aligned_tag vector_aligned = {};
template <size_t _Np> inline constexpr overaligned_tag<_Np> overaligned = {};
template <size_t _X> using _SizeConstant = integral_constant<size_t, _X>;
template <typename _Fp, size_t... _I>
_GLIBCXX_SIMD_INTRINSIC constexpr void
__execute_on_index_sequence(_Fp&& __f, std::index_sequence<_I...>)
{
((void)__f(_SizeConstant<_I>()), ...);
}
template <typename _Fp>
_GLIBCXX_SIMD_INTRINSIC constexpr void
__execute_on_index_sequence(_Fp&&, std::index_sequence<>)
{}
template <size_t _Np, typename _Fp>
_GLIBCXX_SIMD_INTRINSIC constexpr void
__execute_n_times(_Fp&& __f)
{
__execute_on_index_sequence(static_cast<_Fp&&>(__f),
std::make_index_sequence<_Np>{});
}
template <typename _R, typename _Fp, size_t... _I>
_GLIBCXX_SIMD_INTRINSIC constexpr _R
__execute_on_index_sequence_with_return(_Fp&& __f, std::index_sequence<_I...>)
{
return _R{__f(_SizeConstant<_I>())...};
}
template <size_t _Np, typename _R, typename _Fp>
_GLIBCXX_SIMD_INTRINSIC constexpr _R
__generate_from_n_evaluations(_Fp&& __f)
{
return __execute_on_index_sequence_with_return<_R>(
static_cast<_Fp&&>(__f), std::make_index_sequence<_Np>{});
}
template <size_t... _I, typename _F0, typename _FArgs>
_GLIBCXX_SIMD_INTRINSIC constexpr auto
__call_with_n_evaluations(std::index_sequence<_I...>, _F0&& __f0,
_FArgs&& __fargs)
{
return __f0(__fargs(_SizeConstant<_I>())...);
}
template <size_t _Np, typename _F0, typename _FArgs>
_GLIBCXX_SIMD_INTRINSIC constexpr auto
__call_with_n_evaluations(_F0&& __f0, _FArgs&& __fargs)
{
return __call_with_n_evaluations(std::make_index_sequence<_Np>{},
static_cast<_F0&&>(__f0),
static_cast<_FArgs&&>(__fargs));
}
template <size_t _First = 0, size_t... _It, typename _Tp, typename _Fp>
_GLIBCXX_SIMD_INTRINSIC constexpr auto
__call_with_subscripts(_Tp&& __x, index_sequence<_It...>, _Fp&& __fun)
{
return __fun(__x[_First + _It]...);
}
template <size_t _Np, size_t _First = 0, typename _Tp, typename _Fp>
_GLIBCXX_SIMD_INTRINSIC constexpr auto
__call_with_subscripts(_Tp&& __x, _Fp&& __fun)
{
return __call_with_subscripts<_First>(static_cast<_Tp&&>(__x),
std::make_index_sequence<_Np>(),
static_cast<_Fp&&>(__fun));
}
using _UChar = unsigned char;
using _SChar = signed char;
using _UShort = unsigned short;
using _UInt = unsigned int;
using _ULong = unsigned long;
using _ULLong = unsigned long long;
using _LLong = long long;
template <typename _Tp> struct __identity
{
using type = _Tp;
};
template <typename _Tp> using __id = typename __identity<_Tp>::type;
template <typename _T0, typename...> struct __first_of_pack
{
using type = _T0;
};
template <typename... _Ts>
using __first_of_pack_t = typename __first_of_pack<_Ts...>::type;
template <typename _Tp>
typename _Tp::value_type
__value_type_or_identity_impl(int);
template <typename _Tp>
_Tp
__value_type_or_identity_impl(float);
template <typename _Tp>
using __value_type_or_identity_t
= decltype(__value_type_or_identity_impl<_Tp>(int()));
template <typename _Tp>
struct __is_vectorizable : public std::is_arithmetic<_Tp>
{
};
template <> struct __is_vectorizable<bool> : public false_type
{
};
template <typename _Tp>
inline constexpr bool __is_vectorizable_v = __is_vectorizable<_Tp>::value;
template <typename _Tp, typename = enable_if_t<__is_vectorizable_v<_Tp>>>
using _Vectorizable = _Tp;
template <typename _Ptr, typename _ValueType>
struct __is_possible_loadstore_conversion
: conjunction<__is_vectorizable<_Ptr>, __is_vectorizable<_ValueType>>
{
};
template <> struct __is_possible_loadstore_conversion<bool, bool> : true_type
{
};
template <typename _Ptr, typename _ValueType,
typename = enable_if_t<
__is_possible_loadstore_conversion<_Ptr, _ValueType>::value>>
using _LoadStorePtr = _Ptr;
template <typename _Tp, typename = std::void_t<>>
struct __is_bitmask : false_type
{
};
template <typename _Tp>
inline constexpr bool __is_bitmask_v = __is_bitmask<_Tp>::value;
template <typename _Tp>
struct __is_bitmask<_Tp, std::void_t<decltype(std::declval<unsigned&>()
= std::declval<_Tp>() & 1u)>>
: true_type
{
};
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpedantic"
template <size_t _Bytes>
constexpr auto
__int_for_sizeof()
{
if constexpr (_Bytes == sizeof(int))
return int();
#ifdef __clang__
else if constexpr (_Bytes == sizeof(char))
return char();
#else
else if constexpr (_Bytes == sizeof(_SChar))
return _SChar();
#endif
else if constexpr (_Bytes == sizeof(short))
return short();
#ifndef __clang__
else if constexpr (_Bytes == sizeof(long))
return long();
#endif
else if constexpr (_Bytes == sizeof(_LLong))
return _LLong();
#ifdef __SIZEOF_INT128__
else if constexpr (_Bytes == sizeof(__int128))
return __int128();
#endif
else if constexpr (_Bytes % sizeof(int) == 0)
{
constexpr size_t _Np = _Bytes / sizeof(int);
struct _Ip
{
int _M_data[_Np];
_GLIBCXX_SIMD_INTRINSIC
constexpr _Ip operator&(_Ip __rhs) const
{
return __generate_from_n_evaluations<_Np, _Ip>(
[&](auto __i) { return __rhs._M_data[__i] & _M_data[__i]; });
}
_GLIBCXX_SIMD_INTRINSIC
constexpr _Ip operator|(_Ip __rhs) const
{
return __generate_from_n_evaluations<_Np, _Ip>(
[&](auto __i) { return __rhs._M_data[__i] | _M_data[__i]; });
}
_GLIBCXX_SIMD_INTRINSIC
constexpr _Ip operator^(_Ip __rhs) const
{
return __generate_from_n_evaluations<_Np, _Ip>(
[&](auto __i) { return __rhs._M_data[__i] ^ _M_data[__i]; });
}
_GLIBCXX_SIMD_INTRINSIC
constexpr _Ip operator~() const
{
return __generate_from_n_evaluations<_Np, _Ip>(
[&](auto __i) { return ~_M_data[__i]; });
}
};
return _Ip{};
}
else
static_assert(_Bytes != _Bytes, "this should be unreachable");
}
#pragma GCC diagnostic pop
template <typename _Tp>
using __int_for_sizeof_t = decltype(__int_for_sizeof<sizeof(_Tp)>());
template <size_t _Np>
using __int_with_sizeof_t = decltype(__int_for_sizeof<_Np>());
template <typename _Tp> struct __is_fixed_size_abi : false_type
{
};
template <int _Np>
struct __is_fixed_size_abi<simd_abi::fixed_size<_Np>> : true_type
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
constexpr inline bool __have_neon_a32 = _GLIBCXX_SIMD_HAVE_NEON_A32;
constexpr inline bool __have_neon_a64 = _GLIBCXX_SIMD_HAVE_NEON_A64;
#ifdef __POWER9_VECTOR__
constexpr inline bool __have_power9vec = true;
#else
constexpr inline bool __have_power9vec = false;
#endif
#if defined __POWER8_VECTOR__
constexpr inline bool __have_power8vec = true;
#else
constexpr inline bool __have_power8vec = __have_power9vec;
#endif
#if defined __VSX__
constexpr inline bool __have_power_vsx = true;
#else
constexpr inline bool __have_power_vsx = __have_power8vec;
#endif
#if defined __ALTIVEC__
constexpr inline bool __have_power_vmx = true;
#else
constexpr inline bool __have_power_vmx = __have_power_vsx;
#endif
template <typename _Abi>
constexpr bool
__is_scalar_abi()
{
return std::is_same_v<simd_abi::scalar, _Abi>;
}
template <template <int> class _Abi, int _Bytes>
constexpr int
__abi_bytes_impl(_Abi<_Bytes>*)
{
return _Bytes;
}
template <typename _Tp>
constexpr int
__abi_bytes_impl(_Tp*)
{
return -1;
}
template <typename _Abi>
inline constexpr int __abi_bytes_v
= __abi_bytes_impl(static_cast<_Abi*>(nullptr));
template <typename _Abi>
constexpr bool
__is_builtin_bitmask_abi()
{
return std::is_same_v<simd_abi::_VecBltnBtmsk<__abi_bytes_v<_Abi>>, _Abi>;
}
template <typename _Abi>
constexpr bool
__is_sse_abi()
{
constexpr auto _Bytes = __abi_bytes_v<_Abi>;
return _Bytes <= 16 && std::is_same_v<simd_abi::_VecBuiltin<_Bytes>, _Abi>;
}
template <typename _Abi>
constexpr bool
__is_avx_abi()
{
constexpr auto _Bytes = __abi_bytes_v<_Abi>;
return _Bytes > 16 && _Bytes <= 32
&& std::is_same_v<simd_abi::_VecBuiltin<_Bytes>, _Abi>;
}
template <typename _Abi>
constexpr bool
__is_avx512_abi()
{
constexpr auto _Bytes = __abi_bytes_v<_Abi>;
return _Bytes <= 64 && std::is_same_v<simd_abi::_Avx512<_Bytes>, _Abi>;
}
template <typename _Abi>
constexpr bool
__is_neon_abi()
{
constexpr auto _Bytes = __abi_bytes_v<_Abi>;
return _Bytes <= 16 && std::is_same_v<simd_abi::_VecBuiltin<_Bytes>, _Abi>;
}
template <typename, typename _Up> struct __make_dependent
{
using type = _Up;
};
template <typename _Tp, typename _Up>
using __make_dependent_t = typename __make_dependent<_Tp, _Up>::type;
template <typename... _Args>
[[noreturn]] _GLIBCXX_SIMD_ALWAYS_INLINE void
__invoke_ub([[maybe_unused]] const char* __msg,
[[maybe_unused]] const _Args&... __args)
{
#ifdef _GLIBCXX_DEBUG_UB
__builtin_fprintf(stderr, __msg, __args...);
__builtin_trap();
#else
__builtin_unreachable();
#endif
}
template <typename _Tp> struct __assert_unreachable
{
static_assert(!std::is_same_v<_Tp, _Tp>, "this should be unreachable");
};
template <typename _Tp, typename _Ap, size_t _Np = simd_size<_Tp, _Ap>::value>
constexpr size_t
__size_or_zero_dispatch(int)
{
return _Np;
}
template <typename _Tp, typename _Ap>
constexpr size_t
__size_or_zero_dispatch(float)
{
return 0;
}
template <typename _Tp, typename _Ap>
inline constexpr size_t __size_or_zero_v = __size_or_zero_dispatch<_Tp, _Ap>(0);
inline constexpr std::size_t
__div_roundup(std::size_t __a, std::size_t __b)
{
return (__a + __b - 1) / __b;
}
class _ExactBool
{
const bool _M_data;
public:
_GLIBCXX_SIMD_INTRINSIC constexpr _ExactBool(bool __b) : _M_data(__b) {}
_ExactBool(int) = delete;
_GLIBCXX_SIMD_INTRINSIC constexpr operator bool() const { return _M_data; }
};
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
static constexpr size_t _S_full_size = 0;
static constexpr bool _S_is_partial = false;
static constexpr size_t _S_simd_align = 1;
struct _SimdImpl;
struct _SimdMember
{
};
struct _SimdCastType;
static constexpr size_t _S_mask_align = 1;
struct _MaskImpl;
struct _MaskMember
{
};
struct _MaskCastType;
};
template <typename _Tp, typename _Abi, typename = std::void_t<>>
struct _SimdTraits : _InvalidTraits
{
};
inline constexpr struct _PrivateInit
{
} __private_init = {};
inline constexpr struct _BitsetInit
{
} __bitset_init = {};
template <typename _From, typename _To, bool = std::is_arithmetic<_From>::value,
bool = std::is_arithmetic<_To>::value>
struct __is_narrowing_conversion;
template <typename _From, typename _To>
struct __is_narrowing_conversion<_From, _To, true, true>
: public __bool_constant<(
__digits<_From>::value > __digits<_To>::value
|| __finite_max<_From>::value > __finite_max<_To>::value
|| __finite_min<_From>::value < __finite_min<_To>::value
|| (std::is_signed<_From>::value && std::is_unsigned<_To>::value))>
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
template <typename _Tp, typename _Ap>
_GLIBCXX_SIMD_INTRINSIC constexpr const auto&
__data(const simd<_Tp, _Ap>& __x);
template <typename _Tp, typename _Ap>
_GLIBCXX_SIMD_INTRINSIC constexpr auto&
__data(simd<_Tp, _Ap>& __x);
template <typename _Tp, typename _Ap>
_GLIBCXX_SIMD_INTRINSIC constexpr const auto&
__data(const simd_mask<_Tp, _Ap>& __x);
template <typename _Tp, typename _Ap>
_GLIBCXX_SIMD_INTRINSIC constexpr auto&
__data(simd_mask<_Tp, _Ap>& __x);
template <typename _FromT, typename _FromA, typename _ToT, typename _ToA,
typename = void>
struct _SimdConverter;
template <typename _Tp, typename _Ap>
struct _SimdConverter<_Tp, _Ap, _Tp, _Ap, void>
{
template <typename _Up>
_GLIBCXX_SIMD_INTRINSIC const _Up& operator()(const _Up& __x)
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
template <size_t _Size> struct __bool_storage_member_type;
template <size_t _Size>
using __bool_storage_member_type_t =
typename __bool_storage_member_type<_Size>::type;
template <typename _Tp, typename... _Abis> struct _SimdTuple;
template <typename _Tp, int _Np> struct __fixed_size_storage;
template <typename _Tp, int _Np>
using __fixed_size_storage_t = typename __fixed_size_storage<_Tp, _Np>::type;
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
template <typename _Tp> struct __is_simd_wrapper : false_type
{
};
template <typename _Tp, size_t _Np>
struct __is_simd_wrapper<_SimdWrapper<_Tp, _Np>> : true_type
{
};
template <typename _Tp>
inline constexpr bool __is_simd_wrapper_v = __is_simd_wrapper<_Tp>::value;
struct _BitOps
{
static constexpr _UInt _S_popcount(_UInt __x)
{
return __builtin_popcount(__x);
}
static constexpr _ULong _S_popcount(_ULong __x)
{
return __builtin_popcountl(__x);
}
static constexpr _ULLong _S_popcount(_ULLong __x)
{
return __builtin_popcountll(__x);
}
static constexpr _UInt _S_ctz(_UInt __x) { return __builtin_ctz(__x); }
static constexpr _ULong _S_ctz(_ULong __x) { return __builtin_ctzl(__x); }
static constexpr _ULLong _S_ctz(_ULLong __x) { return __builtin_ctzll(__x); }
static constexpr _UInt _S_clz(_UInt __x) { return __builtin_clz(__x); }
static constexpr _ULong _S_clz(_ULong __x) { return __builtin_clzl(__x); }
static constexpr _ULLong _S_clz(_ULLong __x) { return __builtin_clzll(__x); }
template <typename _Tp, typename _Fp>
static void _S_bit_iteration(_Tp __mask, _Fp&& __f)
{
static_assert(sizeof(_ULLong) >= sizeof(_Tp));
std::conditional_t<sizeof(_Tp) <= sizeof(_UInt), _UInt, _ULLong> __k;
if constexpr (std::is_convertible_v<_Tp, decltype(__k)>)
__k = __mask;
else
__k = __mask.to_ullong();
switch (_S_popcount(__k))
{
default:
do
{
__f(_S_ctz(__k));
__k &= (__k - 1);
}
while (__k);
break;
case 2:
__f(_S_ctz(__k));
[[fallthrough]];
case 1:
__f(_S_popcount(~decltype(__k)()) - 1 - _S_clz(__k));
[[fallthrough]];
case 0:
break;
}
}
template <typename _Tp>
_GLIBCXX_SIMD_INTRINSIC _GLIBCXX_CONST static auto _S_firstbit(_Tp __bits)
{
static_assert(std::is_integral_v<_Tp>,
"_S_firstbit requires an integral argument");
if constexpr (sizeof(_Tp) <= sizeof(int))
return __builtin_ctz(__bits);
else if constexpr (alignof(_ULLong) == 8)
return __builtin_ctzll(__bits);
else
{
_UInt __lo = __bits;
return __lo == 0 ? 32 + __builtin_ctz(__bits >> 32)
: __builtin_ctz(__lo);
}
}
template <typename _Tp>
_GLIBCXX_SIMD_INTRINSIC _GLIBCXX_CONST static auto _S_lastbit(_Tp __bits)
{
static_assert(std::is_integral_v<_Tp>,
"_S_lastbit requires an integral argument");
if constexpr (sizeof(_Tp) <= sizeof(int))
return 31 - __builtin_clz(__bits);
else if constexpr (alignof(_ULLong) == 8)
return 63 - __builtin_clzll(__bits);
else
{
_UInt __lo = __bits;
_UInt __hi = __bits >> 32u;
return __hi == 0 ? 31 - __builtin_clz(__lo) : 63 - __builtin_clz(__hi);
}
}
};
template <typename _Tp = void> struct __increment
{
constexpr _Tp operator()(_Tp __a) const { return ++__a; }
};
template <> struct __increment<void>
{
template <typename _Tp> constexpr _Tp operator()(_Tp __a) const
{
return ++__a;
}
};
template <typename _Tp = void> struct __decrement
{
constexpr _Tp operator()(_Tp __a) const { return --__a; }
};
template <> struct __decrement<void>
{
template <typename _Tp> constexpr _Tp operator()(_Tp __a) const
{
return --__a;
}
};
template <typename _From, typename _To,
typename = enable_if_t<negation<
__is_narrowing_conversion<__remove_cvref_t<_From>, _To>>::value>>
using _ValuePreserving = _From;
template <typename _From, typename _To,
typename _DecayedFrom = __remove_cvref_t<_From>,
typename = enable_if_t<conjunction<
is_convertible<_From, _To>,
disjunction<
is_same<_DecayedFrom, _To>, is_same<_DecayedFrom, int>,
conjunction<is_same<_DecayedFrom, _UInt>, is_unsigned<_To>>,
negation<__is_narrowing_conversion<_DecayedFrom, _To>>>>::value>>
using _ValuePreservingOrInt = _From;
template <typename _Tp, size_t _Bytes, typename = std::void_t<>>
struct __intrinsic_type;
template <typename _Tp, size_t _Size>
using __intrinsic_type_t =
typename __intrinsic_type<_Tp, _Size * sizeof(_Tp)>::type;
template <typename _Tp>
using __intrinsic_type2_t = typename __intrinsic_type<_Tp, 2>::type;
template <typename _Tp>
using __intrinsic_type4_t = typename __intrinsic_type<_Tp, 4>::type;
template <typename _Tp>
using __intrinsic_type8_t = typename __intrinsic_type<_Tp, 8>::type;
template <typename _Tp>
using __intrinsic_type16_t = typename __intrinsic_type<_Tp, 16>::type;
template <typename _Tp>
using __intrinsic_type32_t = typename __intrinsic_type<_Tp, 32>::type;
template <typename _Tp>
using __intrinsic_type64_t = typename __intrinsic_type<_Tp, 64>::type;
template <typename _Tp>
using __intrinsic_type128_t = typename __intrinsic_type<_Tp, 128>::type;
template <size_t _Np, bool _Sanitized = false> struct _BitMask;
template <size_t _Np, bool _Sanitized>
struct __is_bitmask<_BitMask<_Np, _Sanitized>, void> : true_type
{
};
template <size_t _Np> using _SanitizedBitMask = _BitMask<_Np, true>;
template <size_t _Np, bool _Sanitized> struct _BitMask
{
static_assert(_Np > 0);
static constexpr size_t _NBytes = __div_roundup(_Np, __CHAR_BIT__);
using _Tp = conditional_t<_Np == 1, bool,
make_unsigned_t<__int_with_sizeof_t<std::min(
sizeof(_ULLong), __next_power_of_2(_NBytes))>>>;
static constexpr int _S_array_size = __div_roundup(_NBytes, sizeof(_Tp));
_Tp _M_bits[_S_array_size];
static constexpr int _S_unused_bits
= _Np == 1 ? 0 : _S_array_size * sizeof(_Tp) * __CHAR_BIT__ - _Np;
static constexpr _Tp _S_bitmask = +_Tp(~_Tp()) >> _S_unused_bits;
constexpr _BitMask() noexcept = default;
constexpr _BitMask(unsigned long long __x) noexcept
: _M_bits{static_cast<_Tp>(__x)}
{}
_BitMask(std::bitset<_Np> __x) noexcept : _BitMask(__x.to_ullong()) {}
constexpr _BitMask(const _BitMask&) noexcept = default;
template <bool _RhsSanitized, typename = enable_if_t<_RhsSanitized == false
&& _Sanitized == true>>
constexpr _BitMask(const _BitMask<_Np, _RhsSanitized>& __rhs) noexcept
: _BitMask(__rhs._M_sanitized())
{}
constexpr operator _SimdWrapper<bool, _Np>() const noexcept
{
static_assert(_S_array_size == 1);
return _M_bits[0];
}
constexpr _Tp _M_to_bits() const noexcept
{
static_assert(_S_array_size == 1);
return _M_bits[0];
}
constexpr unsigned long long to_ullong() const noexcept
{
static_assert(_S_array_size == 1);
return _M_bits[0];
}
constexpr unsigned long to_ulong() const noexcept
{
static_assert(_S_array_size == 1);
return _M_bits[0];
}
constexpr std::bitset<_Np> _M_to_bitset() const noexcept
{
static_assert(_S_array_size == 1);
return _M_bits[0];
}
constexpr decltype(auto) _M_sanitized() const noexcept
{
if constexpr (_Sanitized)
return *this;
else if constexpr (_Np == 1)
return _SanitizedBitMask<_Np>(_M_bits[0]);
else
{
_SanitizedBitMask<_Np> __r = {};
for (int __i = 0; __i < _S_array_size; ++__i)
__r._M_bits[__i] = _M_bits[__i];
if constexpr (_S_unused_bits > 0)
__r._M_bits[_S_array_size - 1] &= _S_bitmask;
return __r;
}
}
template <size_t _Mp, bool _LSanitized>
constexpr _BitMask<_Np + _Mp, _Sanitized>
_M_prepend(_BitMask<_Mp, _LSanitized> __lsb) const noexcept
{
constexpr size_t _RN = _Np + _Mp;
using _Rp = _BitMask<_RN, _Sanitized>;
if constexpr (_Rp::_S_array_size == 1)
{
_Rp __r{{_M_bits[0]}};
__r._M_bits[0] <<= _Mp;
__r._M_bits[0] |= __lsb._M_sanitized()._M_bits[0];
return __r;
}
else
__assert_unreachable<_Rp>();
}
template <size_t _DropLsb, size_t _NewSize = _Np - _DropLsb>
constexpr auto _M_extract() const noexcept
{
static_assert(_Np > _DropLsb);
static_assert(_DropLsb + _NewSize <= sizeof(_ULLong) * __CHAR_BIT__,
"not implemented for bitmasks larger than one ullong");
if constexpr (_NewSize == 1)
return _SanitizedBitMask<1>(_M_bits[0] & (_Tp(1) << _DropLsb));
else
return _BitMask<_NewSize,
((_NewSize + _DropLsb == sizeof(_Tp) * __CHAR_BIT__
&& _NewSize + _DropLsb <= _Np)
|| ((_Sanitized || _Np == sizeof(_Tp) * __CHAR_BIT__)
&& _NewSize + _DropLsb >= _Np))>(_M_bits[0]
>> _DropLsb);
}
constexpr bool all() const noexcept
{
if constexpr (_Np == 1)
return _M_bits[0];
else if constexpr (!_Sanitized)
return _M_sanitized().all();
else
{
constexpr _Tp __allbits = ~_Tp();
for (int __i = 0; __i < _S_array_size - 1; ++__i)
if (_M_bits[__i] != __allbits)
return false;
return _M_bits[_S_array_size - 1] == _S_bitmask;
}
}
constexpr bool any() const noexcept
{
if constexpr (_Np == 1)
return _M_bits[0];
else if constexpr (!_Sanitized)
return _M_sanitized().any();
else
{
for (int __i = 0; __i < _S_array_size - 1; ++__i)
if (_M_bits[__i] != 0)
return true;
return _M_bits[_S_array_size - 1] != 0;
}
}
constexpr bool none() const noexcept
{
if constexpr (_Np == 1)
return !_M_bits[0];
else if constexpr (!_Sanitized)
return _M_sanitized().none();
else
{
for (int __i = 0; __i < _S_array_size - 1; ++__i)
if (_M_bits[__i] != 0)
return false;
return _M_bits[_S_array_size - 1] == 0;
}
}
constexpr int count() const noexcept
{
if constexpr (_Np == 1)
return _M_bits[0];
else if constexpr (!_Sanitized)
return _M_sanitized().none();
else
{
int __result = __builtin_popcountll(_M_bits[0]);
for (int __i = 1; __i < _S_array_size; ++__i)
__result += __builtin_popcountll(_M_bits[__i]);
return __result;
}
}
constexpr bool operator[](size_t __i) const noexcept
{
if constexpr (_Np == 1)
return _M_bits[0];
else if constexpr (_S_array_size == 1)
return (_M_bits[0] >> __i) & 1;
else
{
const size_t __j = __i / (sizeof(_Tp) * __CHAR_BIT__);
const size_t __shift = __i % (sizeof(_Tp) * __CHAR_BIT__);
return (_M_bits[__j] >> __shift) & 1;
}
}
template <size_t __i>
constexpr bool operator[](_SizeConstant<__i>) const noexcept
{
static_assert(__i < _Np);
constexpr size_t __j = __i / (sizeof(_Tp) * __CHAR_BIT__);
constexpr size_t __shift = __i % (sizeof(_Tp) * __CHAR_BIT__);
return static_cast<bool>(_M_bits[__j] & (_Tp(1) << __shift));
}
constexpr void set(size_t __i, bool __x) noexcept
{
if constexpr (_Np == 1)
_M_bits[0] = __x;
else if constexpr (_S_array_size == 1)
{
_M_bits[0] &= ~_Tp(_Tp(1) << __i);
_M_bits[0] |= _Tp(_Tp(__x) << __i);
}
else
{
const size_t __j = __i / (sizeof(_Tp) * __CHAR_BIT__);
const size_t __shift = __i % (sizeof(_Tp) * __CHAR_BIT__);
_M_bits[__j] &= ~_Tp(_Tp(1) << __shift);
_M_bits[__j] |= _Tp(_Tp(__x) << __shift);
}
}
template <size_t __i>
constexpr void set(_SizeConstant<__i>, bool __x) noexcept
{
static_assert(__i < _Np);
if constexpr (_Np == 1)
_M_bits[0] = __x;
else
{
constexpr size_t __j = __i / (sizeof(_Tp) * __CHAR_BIT__);
constexpr size_t __shift = __i % (sizeof(_Tp) * __CHAR_BIT__);
constexpr _Tp __mask = ~_Tp(_Tp(1) << __shift);
_M_bits[__j] &= __mask;
_M_bits[__j] |= _Tp(_Tp(__x) << __shift);
}
}
constexpr _BitMask operator~() const noexcept
{
if constexpr (_Np == 1)
return !_M_bits[0];
else
{
_BitMask __result{};
for (int __i = 0; __i < _S_array_size - 1; ++__i)
__result._M_bits[__i] = ~_M_bits[__i];
if constexpr (_Sanitized)
__result._M_bits[_S_array_size - 1]
= _M_bits[_S_array_size - 1] ^ _S_bitmask;
else
__result._M_bits[_S_array_size - 1] = ~_M_bits[_S_array_size - 1];
return __result;
}
}
constexpr _BitMask& operator^=(const _BitMask& __b) & noexcept
{
__execute_n_times<_S_array_size>(
[&](auto __i) { _M_bits[__i] ^= __b._M_bits[__i]; });
return *this;
}
constexpr _BitMask& operator|=(const _BitMask& __b) & noexcept
{
__execute_n_times<_S_array_size>(
[&](auto __i) { _M_bits[__i] |= __b._M_bits[__i]; });
return *this;
}
constexpr _BitMask& operator&=(const _BitMask& __b) & noexcept
{
__execute_n_times<_S_array_size>(
[&](auto __i) { _M_bits[__i] &= __b._M_bits[__i]; });
return *this;
}
friend constexpr _BitMask operator^(const _BitMask& __a,
const _BitMask& __b) noexcept
{
_BitMask __r = __a;
__r ^= __b;
return __r;
}
friend constexpr _BitMask operator|(const _BitMask& __a,
const _BitMask& __b) noexcept
{
_BitMask __r = __a;
__r |= __b;
return __r;
}
friend constexpr _BitMask operator&(const _BitMask& __a,
const _BitMask& __b) noexcept
{
_BitMask __r = __a;
__r &= __b;
return __r;
}
_GLIBCXX_SIMD_INTRINSIC
constexpr bool _M_is_constprop() const
{
if constexpr (_S_array_size == 0)
return __builtin_constant_p(_M_bits[0]);
else
{
for (int __i = 0; __i < _S_array_size; ++__i)
if (!__builtin_constant_p(_M_bits[__i]))
return false;
return true;
}
}
};
template <typename _Tp = void>
static inline constexpr int __min_vector_size = 2 * sizeof(_Tp);
#if _GLIBCXX_SIMD_HAVE_NEON
template <> inline constexpr int __min_vector_size<void> = 8;
#else
template <> inline constexpr int __min_vector_size<void> = 16;
#endif
template <typename _Tp, size_t _Np, typename = void> struct __vector_type_n
{
};
template <typename _Tp> struct __vector_type_n<_Tp, 0, void>
{
};
template <typename _Tp>
struct __vector_type_n<_Tp, 1, enable_if_t<__is_vectorizable_v<_Tp>>>
{
using type = _Tp;
};
template <typename _Tp, size_t _Np>
struct __vector_type_n<_Tp, _Np,
enable_if_t<__is_vectorizable_v<_Tp> && _Np >= 2>>
{
static constexpr size_t _S_Np2 = __next_power_of_2(_Np * sizeof(_Tp));
static constexpr size_t _S_Bytes =
#ifdef __i386__
_S_Np2 == 8 ? 16 :
#endif
_S_Np2 < __min_vector_size<_Tp> ? __min_vector_size<_Tp>
: _S_Np2;
using type [[__gnu__::__vector_size__(_S_Bytes)]] = _Tp;
};
template <typename _Tp, size_t _Bytes, size_t = _Bytes % sizeof(_Tp)>
struct __vector_type;
template <typename _Tp, size_t _Bytes>
struct __vector_type<_Tp, _Bytes, 0>
: __vector_type_n<_Tp, _Bytes / sizeof(_Tp)>
{
};
template <typename _Tp, size_t _Size>
using __vector_type_t = typename __vector_type_n<_Tp, _Size>::type;
template <typename _Tp>
using __vector_type2_t = typename __vector_type<_Tp, 2>::type;
template <typename _Tp>
using __vector_type4_t = typename __vector_type<_Tp, 4>::type;
template <typename _Tp>
using __vector_type8_t = typename __vector_type<_Tp, 8>::type;
template <typename _Tp>
using __vector_type16_t = typename __vector_type<_Tp, 16>::type;
template <typename _Tp>
using __vector_type32_t = typename __vector_type<_Tp, 32>::type;
template <typename _Tp>
using __vector_type64_t = typename __vector_type<_Tp, 64>::type;
template <typename _Tp>
using __vector_type128_t = typename __vector_type<_Tp, 128>::type;
template <typename _Tp, typename = std::void_t<>>
struct __is_vector_type : false_type
{
};
template <typename _Tp>
struct __is_vector_type<
_Tp, std::void_t<typename __vector_type<
std::remove_reference_t<decltype(std::declval<_Tp>()[0])>,
sizeof(_Tp)>::type>>
: std::is_same<_Tp, typename __vector_type<std::remove_reference_t<decltype(
std::declval<_Tp>()[0])>,
sizeof(_Tp)>::type>
{
};
template <typename _Tp>
inline constexpr bool __is_vector_type_v = __is_vector_type<_Tp>::value;
template <typename _Tp, typename = std::void_t<>> struct _VectorTraitsImpl;
template <typename _Tp>
struct _VectorTraitsImpl<_Tp, enable_if_t<__is_vector_type_v<_Tp>>>
{
using type = _Tp;
using value_type = std::remove_reference_t<decltype(std::declval<_Tp>()[0])>;
static constexpr int _S_full_size = sizeof(_Tp) / sizeof(value_type);
using _Wrapper = _SimdWrapper<value_type, _S_full_size>;
template <typename _Up, int _W = _S_full_size>
static constexpr bool _S_is
= std::is_same_v<value_type, _Up> && _W == _S_full_size;
};
template <typename _Tp, size_t _Np>
struct _VectorTraitsImpl<_SimdWrapper<_Tp, _Np>,
std::void_t<__vector_type_t<_Tp, _Np>>>
{
using type = __vector_type_t<_Tp, _Np>;
using value_type = _Tp;
static constexpr int _S_full_size = sizeof(type) / sizeof(value_type);
using _Wrapper = _SimdWrapper<_Tp, _Np>;
static constexpr bool _S_is_partial = (_Np == _S_full_size);
static constexpr int _S_partial_width = _Np;
template <typename _Up, int _W = _S_full_size>
static constexpr bool _S_is
= std::is_same_v<value_type, _Up> && _W == _S_full_size;
};
template <typename _Tp, typename = typename _VectorTraitsImpl<_Tp>::type>
using _VectorTraits = _VectorTraitsImpl<_Tp>;
template <typename _V>
_GLIBCXX_SIMD_INTRINSIC constexpr auto
__as_vector(_V __x)
{
if constexpr (__is_vector_type_v<_V>)
return __x;
else if constexpr (is_simd<_V>::value || is_simd_mask<_V>::value)
return __data(__x)._M_data;
else if constexpr (__is_vectorizable_v<_V>)
return __vector_type_t<_V, 2>{__x};
else
return __x._M_data;
}
template <size_t _Np = 0, typename _V>
_GLIBCXX_SIMD_INTRINSIC constexpr auto
__as_wrapper(_V __x)
{
if constexpr (__is_vector_type_v<_V>)
return _SimdWrapper<typename _VectorTraits<_V>::value_type,
(_Np > 0 ? _Np : _VectorTraits<_V>::_S_full_size)>(__x);
else if constexpr (is_simd<_V>::value || is_simd_mask<_V>::value)
{
static_assert(_V::size() == _Np);
return __data(__x);
}
else
{
static_assert(_V::_S_size == _Np);
return __x;
}
}
template <typename _To, typename _From>
_GLIBCXX_SIMD_INTRINSIC constexpr _To
__intrin_bitcast(_From __v)
{
static_assert(__is_vector_type_v<_From> && __is_vector_type_v<_To>);
if constexpr (sizeof(_To) == sizeof(_From))
return reinterpret_cast<_To>(__v);
else if constexpr (sizeof(_From) > sizeof(_To))
if constexpr (sizeof(_To) >= 16)
return reinterpret_cast<const __may_alias<_To>&>(__v);
else
{
_To __r;
__builtin_memcpy(&__r, &__v, sizeof(_To));
return __r;
}
#if _GLIBCXX_SIMD_X86INTRIN && !defined __clang__
else if constexpr (__have_avx && sizeof(_From) == 16 && sizeof(_To) == 32)
return reinterpret_cast<_To>(__builtin_ia32_ps256_ps(
reinterpret_cast<__vector_type_t<float, 4>>(__v)));
else if constexpr (__have_avx512f && sizeof(_From) == 16 && sizeof(_To) == 64)
return reinterpret_cast<_To>(__builtin_ia32_ps512_ps(
reinterpret_cast<__vector_type_t<float, 4>>(__v)));
else if constexpr (__have_avx512f && sizeof(_From) == 32 && sizeof(_To) == 64)
return reinterpret_cast<_To>(__builtin_ia32_ps512_256ps(
reinterpret_cast<__vector_type_t<float, 8>>(__v)));
#endif
else if constexpr (sizeof(__v) <= 8)
return reinterpret_cast<_To>(
__vector_type_t<__int_for_sizeof_t<_From>, sizeof(_To) / sizeof(_From)>{
reinterpret_cast<__int_for_sizeof_t<_From>>(__v)});
else
{
static_assert(sizeof(_To) > sizeof(_From));
_To __r = {};
__builtin_memcpy(&__r, &__v, sizeof(_From));
return __r;
}
}
template <typename _To, size_t _NN = 0, typename _From,
typename _FromVT = _VectorTraits<_From>,
size_t _Np = _NN == 0 ? sizeof(_From) / sizeof(_To) : _NN>
_GLIBCXX_SIMD_INTRINSIC constexpr __vector_type_t<_To, _Np>
__vector_bitcast(_From __x)
{
using _R = __vector_type_t<_To, _Np>;
return __intrin_bitcast<_R>(__x);
}
template <typename _To, size_t _NN = 0, typename _Tp, size_t _Nx,
size_t _Np
= _NN == 0 ? sizeof(_SimdWrapper<_Tp, _Nx>) / sizeof(_To) : _NN>
_GLIBCXX_SIMD_INTRINSIC constexpr __vector_type_t<_To, _Np>
__vector_bitcast(const _SimdWrapper<_Tp, _Nx>& __x)
{
static_assert(_Np > 1);
return __intrin_bitcast<__vector_type_t<_To, _Np>>(__x._M_data);
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
template <typename _To, typename _Tp, typename _TVT = _VectorTraits<_Tp>>
_To __convert_x86(_Tp, _Tp, _Tp, _Tp, _Tp, _Tp, _Tp, _Tp, _Tp, _Tp, _Tp, _Tp,
_Tp, _Tp, _Tp, _Tp);
#endif
template <typename _To, typename _From>
_GLIBCXX_SIMD_INTRINSIC constexpr _To
__bit_cast(const _From __x)
{
static_assert(sizeof(_To) == sizeof(_From));
constexpr bool __to_is_vectorizable
= std::is_arithmetic_v<_To> || std::is_enum_v<_To>;
constexpr bool __from_is_vectorizable
= std::is_arithmetic_v<_From> || std::is_enum_v<_From>;
if constexpr (__is_vector_type_v<_To> && __is_vector_type_v<_From>)
return reinterpret_cast<_To>(__x);
else if constexpr (__is_vector_type_v<_To> && __from_is_vectorizable)
{
using _FV [[gnu::vector_size(sizeof(_From))]] = _From;
return reinterpret_cast<_To>(_FV{__x});
}
else if constexpr (__to_is_vectorizable && __from_is_vectorizable)
{
using _TV [[gnu::vector_size(sizeof(_To))]] = _To;
using _FV [[gnu::vector_size(sizeof(_From))]] = _From;
return reinterpret_cast<_TV>(_FV{__x})[0];
}
else if constexpr (__to_is_vectorizable && __is_vector_type_v<_From>)
{
using _TV [[gnu::vector_size(sizeof(_To))]] = _To;
return reinterpret_cast<_TV>(__x)[0];
}
else
{
_To __r;
__builtin_memcpy(reinterpret_cast<char*>(&__r),
reinterpret_cast<const char*>(&__x), sizeof(_To));
return __r;
}
}
template <typename _Tp, typename _TVT = _VectorTraits<_Tp>,
typename _R
= __intrinsic_type_t<typename _TVT::value_type, _TVT::_S_full_size>>
_GLIBCXX_SIMD_INTRINSIC constexpr _R
__to_intrin(_Tp __x)
{
static_assert(sizeof(__x) <= sizeof(_R),
"__to_intrin may never drop values off the end");
if constexpr (sizeof(__x) == sizeof(_R))
return reinterpret_cast<_R>(__as_vector(__x));
else
{
using _Up = __int_for_sizeof_t<_Tp>;
return reinterpret_cast<_R>(
__vector_type_t<_Up, sizeof(_R) / sizeof(_Up)>{__bit_cast<_Up>(__x)});
}
}
template <typename _Tp, typename... _Args>
_GLIBCXX_SIMD_INTRINSIC constexpr __vector_type_t<_Tp, sizeof...(_Args)>
__make_vector(const _Args&... __args)
{
return __vector_type_t<_Tp, sizeof...(_Args)>{static_cast<_Tp>(__args)...};
}
template <size_t _Np, typename _Tp>
_GLIBCXX_SIMD_INTRINSIC constexpr __vector_type_t<_Tp, _Np>
__vector_broadcast(_Tp __x)
{
return __call_with_n_evaluations<_Np>(
[](auto... __xx) { return __vector_type_t<_Tp, _Np>{__xx...}; },
[&__x](int) { return __x; });
}
template <typename _Tp, size_t _Np, typename _Gp, size_t... _I>
_GLIBCXX_SIMD_INTRINSIC constexpr __vector_type_t<_Tp, _Np>
__generate_vector_impl(_Gp&& __gen, std::index_sequence<_I...>)
{
#ifdef _GLIBCXX_SIMD_WORKAROUND_PR89229
if constexpr (__have_avx512f && !__have_avx512vl && sizeof(_Tp) == 8
&& std::is_integral_v<_Tp>)
if (!__builtin_is_constant_evaluated())
[] { asm("" ::: "memory"); }();
#endif
return __vector_type_t<_Tp, _Np>{
static_cast<_Tp>(__gen(_SizeConstant<_I>()))...};
}
template <typename _V, typename _VVT = _VectorTraits<_V>, typename _Gp>
_GLIBCXX_SIMD_INTRINSIC constexpr _V
__generate_vector(_Gp&& __gen)
{
if constexpr (__is_vector_type_v<_V>)
return __generate_vector_impl<typename _VVT::value_type, _VVT::_S_full_size>(
static_cast<_Gp&&>(__gen), std::make_index_sequence<_VVT::_S_full_size>());
else
return __generate_vector_impl<typename _VVT::value_type,
_VVT::_S_partial_width>(
static_cast<_Gp&&>(__gen),
std::make_index_sequence<_VVT::_S_partial_width>());
}
template <typename _Tp, size_t _Np, typename _Gp>
_GLIBCXX_SIMD_INTRINSIC constexpr __vector_type_t<_Tp, _Np>
__generate_vector(_Gp&& __gen)
{
return __generate_vector_impl<_Tp, _Np>(static_cast<_Gp&&>(__gen),
std::make_index_sequence<_Np>());
}
template <typename _TW>
_GLIBCXX_SIMD_INTRINSIC constexpr _TW
__xor(_TW __a, _TW __b) noexcept
{
if constexpr (__is_vector_type_v<_TW> || __is_simd_wrapper_v<_TW>)
{
using _Tp = typename conditional_t<__is_simd_wrapper_v<_TW>, _TW,
_VectorTraitsImpl<_TW>>::value_type;
if constexpr (std::is_floating_point_v<_Tp>)
{
using _Ip = make_unsigned_t<__int_for_sizeof_t<_Tp>>;
return __vector_bitcast<_Tp>(__vector_bitcast<_Ip>(__a)
^ __vector_bitcast<_Ip>(__b));
}
else if constexpr (__is_vector_type_v<_TW>)
return __a ^ __b;
else
return __a._M_data ^ __b._M_data;
}
else
return __a ^ __b;
}
template <typename _TW>
_GLIBCXX_SIMD_INTRINSIC constexpr _TW
__or(_TW __a, _TW __b) noexcept
{
if constexpr (__is_vector_type_v<_TW> || __is_simd_wrapper_v<_TW>)
{
using _Tp = typename conditional_t<__is_simd_wrapper_v<_TW>, _TW,
_VectorTraitsImpl<_TW>>::value_type;
if constexpr (std::is_floating_point_v<_Tp>)
{
using _Ip = make_unsigned_t<__int_for_sizeof_t<_Tp>>;
return __vector_bitcast<_Tp>(__vector_bitcast<_Ip>(__a)
| __vector_bitcast<_Ip>(__b));
}
else if constexpr (__is_vector_type_v<_TW>)
return __a | __b;
else
return __a._M_data | __b._M_data;
}
else
return __a | __b;
}
template <typename _TW>
_GLIBCXX_SIMD_INTRINSIC constexpr _TW
__and(_TW __a, _TW __b) noexcept
{
if constexpr (__is_vector_type_v<_TW> || __is_simd_wrapper_v<_TW>)
{
using _Tp = typename conditional_t<__is_simd_wrapper_v<_TW>, _TW,
_VectorTraitsImpl<_TW>>::value_type;
if constexpr (std::is_floating_point_v<_Tp>)
{
using _Ip = make_unsigned_t<__int_for_sizeof_t<_Tp>>;
return __vector_bitcast<_Tp>(__vector_bitcast<_Ip>(__a)
& __vector_bitcast<_Ip>(__b));
}
else if constexpr (__is_vector_type_v<_TW>)
return __a & __b;
else
return __a._M_data & __b._M_data;
}
else
return __a & __b;
}
#if _GLIBCXX_SIMD_X86INTRIN && !defined __clang__
static constexpr struct
{
_GLIBCXX_SIMD_INTRINSIC __v4sf operator()(__v4sf __a,
__v4sf __b) const noexcept
{
return __builtin_ia32_andnps(__a, __b);
}
_GLIBCXX_SIMD_INTRINSIC __v2df operator()(__v2df __a,
__v2df __b) const noexcept
{
return __builtin_ia32_andnpd(__a, __b);
}
_GLIBCXX_SIMD_INTRINSIC __v2di operator()(__v2di __a,
__v2di __b) const noexcept
{
return __builtin_ia32_pandn128(__a, __b);
}
_GLIBCXX_SIMD_INTRINSIC __v8sf operator()(__v8sf __a,
__v8sf __b) const noexcept
{
return __builtin_ia32_andnps256(__a, __b);
}
_GLIBCXX_SIMD_INTRINSIC __v4df operator()(__v4df __a,
__v4df __b) const noexcept
{
return __builtin_ia32_andnpd256(__a, __b);
}
_GLIBCXX_SIMD_INTRINSIC __v4di operator()(__v4di __a,
__v4di __b) const noexcept
{
if constexpr (__have_avx2)
return __builtin_ia32_andnotsi256(__a, __b);
else
return reinterpret_cast<__v4di>(
__builtin_ia32_andnpd256(reinterpret_cast<__v4df>(__a),
reinterpret_cast<__v4df>(__b)));
}
_GLIBCXX_SIMD_INTRINSIC __v16sf operator()(__v16sf __a,
__v16sf __b) const noexcept
{
if constexpr (__have_avx512dq)
return _mm512_andnot_ps(__a, __b);
else
return reinterpret_cast<__v16sf>(
_mm512_andnot_si512(reinterpret_cast<__v8di>(__a),
reinterpret_cast<__v8di>(__b)));
}
_GLIBCXX_SIMD_INTRINSIC __v8df operator()(__v8df __a,
__v8df __b) const noexcept
{
if constexpr (__have_avx512dq)
return _mm512_andnot_pd(__a, __b);
else
return reinterpret_cast<__v8df>(
_mm512_andnot_si512(reinterpret_cast<__v8di>(__a),
reinterpret_cast<__v8di>(__b)));
}
_GLIBCXX_SIMD_INTRINSIC __v8di operator()(__v8di __a,
__v8di __b) const noexcept
{
return _mm512_andnot_si512(__a, __b);
}
} _S_x86_andnot;
#endif
template <typename _TW>
_GLIBCXX_SIMD_INTRINSIC constexpr _TW
__andnot(_TW __a, _TW __b) noexcept
{
if constexpr (__is_vector_type_v<_TW> || __is_simd_wrapper_v<_TW>)
{
using _TVT
= conditional_t<__is_simd_wrapper_v<_TW>, _TW, _VectorTraitsImpl<_TW>>;
using _Tp = typename _TVT::value_type;
#if _GLIBCXX_SIMD_X86INTRIN && !defined __clang__
if constexpr (sizeof(_TW) >= 16)
{
const auto __ai = __to_intrin(__a);
const auto __bi = __to_intrin(__b);
if (!__builtin_is_constant_evaluated()
&& !(__builtin_constant_p(__ai) && __builtin_constant_p(__bi)))
{
const auto __r = _S_x86_andnot(__ai, __bi);
if constexpr (is_convertible_v<decltype(__r), _TW>)
return __r;
else
return reinterpret_cast<typename _TVT::type>(__r);
}
}
#endif
using _Ip = make_unsigned_t<__int_for_sizeof_t<_Tp>>;
return __vector_bitcast<_Tp>(~__vector_bitcast<_Ip>(__a)
& __vector_bitcast<_Ip>(__b));
}
else
return ~__a & __b;
}
template <typename _Tp, typename _TVT = _VectorTraits<_Tp>>
_GLIBCXX_SIMD_INTRINSIC constexpr _Tp
__not(_Tp __a) noexcept
{
if constexpr (std::is_floating_point_v<typename _TVT::value_type>)
return reinterpret_cast<typename _TVT::type>(
~__vector_bitcast<unsigned>(__a));
else
return ~__a;
}
template <typename _Tp, typename _TVT = _VectorTraits<_Tp>,
typename _R
= __vector_type_t<typename _TVT::value_type, _TVT::_S_full_size * 2>>
constexpr _R
__concat(_Tp a_, _Tp b_)
{
#ifdef _GLIBCXX_SIMD_WORKAROUND_XXX_1
using _W
= std::conditional_t<std::is_floating_point_v<typename _TVT::value_type>,
double,
conditional_t<(sizeof(_Tp) >= 2 * sizeof(long long)),
long long, typename _TVT::value_type>>;
constexpr int input_width = sizeof(_Tp) / sizeof(_W);
const auto __a = __vector_bitcast<_W>(a_);
const auto __b = __vector_bitcast<_W>(b_);
using _Up = __vector_type_t<_W, sizeof(_R) / sizeof(_W)>;
#else
constexpr int input_width = _TVT::_S_full_size;
const _Tp& __a = a_;
const _Tp& __b = b_;
using _Up = _R;
#endif
if constexpr (input_width == 2)
return reinterpret_cast<_R>(_Up{__a[0], __a[1], __b[0], __b[1]});
else if constexpr (input_width == 4)
return reinterpret_cast<_R>(
_Up{__a[0], __a[1], __a[2], __a[3], __b[0], __b[1], __b[2], __b[3]});
else if constexpr (input_width == 8)
return reinterpret_cast<_R>(
_Up{__a[0], __a[1], __a[2], __a[3], __a[4], __a[5], __a[6], __a[7],
__b[0], __b[1], __b[2], __b[3], __b[4], __b[5], __b[6], __b[7]});
else if constexpr (input_width == 16)
return reinterpret_cast<_R>(
_Up{__a[0], __a[1], __a[2], __a[3], __a[4], __a[5], __a[6],
__a[7], __a[8], __a[9], __a[10], __a[11], __a[12], __a[13],
__a[14], __a[15], __b[0], __b[1], __b[2], __b[3], __b[4],
__b[5], __b[6], __b[7], __b[8], __b[9], __b[10], __b[11],
__b[12], __b[13], __b[14], __b[15]});
else if constexpr (input_width == 32)
return reinterpret_cast<_R>(_Up{
__a[0], __a[1], __a[2], __a[3], __a[4], __a[5], __a[6], __a[7],
__a[8], __a[9], __a[10], __a[11], __a[12], __a[13], __a[14], __a[15],
__a[16], __a[17], __a[18], __a[19], __a[20], __a[21], __a[22], __a[23],
__a[24], __a[25], __a[26], __a[27], __a[28], __a[29], __a[30], __a[31],
__b[0], __b[1], __b[2], __b[3], __b[4], __b[5], __b[6], __b[7],
__b[8], __b[9], __b[10], __b[11], __b[12], __b[13], __b[14], __b[15],
__b[16], __b[17], __b[18], __b[19], __b[20], __b[21], __b[22], __b[23],
__b[24], __b[25], __b[26], __b[27], __b[28], __b[29], __b[30], __b[31]});
}
template <typename _Tp, typename _TVT = _VectorTraits<_Tp>>
struct _ZeroExtendProxy
{
using value_type = typename _TVT::value_type;
static constexpr size_t _Np = _TVT::_S_full_size;
const _Tp __x;
template <typename _To, typename _ToVT = _VectorTraits<_To>,
typename
= enable_if_t<is_same_v<typename _ToVT::value_type, value_type>>>
_GLIBCXX_SIMD_INTRINSIC operator _To() const
{
constexpr size_t _ToN = _ToVT::_S_full_size;
if constexpr (_ToN == _Np)
return __x;
else if constexpr (_ToN == 2 * _Np)
{
#ifdef _GLIBCXX_SIMD_WORKAROUND_XXX_3
if constexpr (__have_avx && _TVT::template _S_is<float, 4>)
return __vector_bitcast<value_type>(
_mm256_insertf128_ps(__m256(), __x, 0));
else if constexpr (__have_avx && _TVT::template _S_is<double, 2>)
return __vector_bitcast<value_type>(
_mm256_insertf128_pd(__m256d(), __x, 0));
else if constexpr (__have_avx2 && _Np * sizeof(value_type) == 16)
return __vector_bitcast<value_type>(
_mm256_insertf128_si256(__m256i(), __to_intrin(__x), 0));
else if constexpr (__have_avx512f && _TVT::template _S_is<float, 8>)
{
if constexpr (__have_avx512dq)
return __vector_bitcast<value_type>(
_mm512_insertf32x8(__m512(), __x, 0));
else
return reinterpret_cast<__m512>(
_mm512_insertf64x4(__m512d(), reinterpret_cast<__m256d>(__x),
0));
}
else if constexpr (__have_avx512f && _TVT::template _S_is<double, 4>)
return __vector_bitcast<value_type>(
_mm512_insertf64x4(__m512d(), __x, 0));
else if constexpr (__have_avx512f && _Np * sizeof(value_type) == 32)
return __vector_bitcast<value_type>(
_mm512_inserti64x4(__m512i(), __to_intrin(__x), 0));
#endif
return __concat(__x, _Tp());
}
else if constexpr (_ToN == 4 * _Np)
{
#ifdef _GLIBCXX_SIMD_WORKAROUND_XXX_3
if constexpr (__have_avx512dq && _TVT::template _S_is<double, 2>)
{
return __vector_bitcast<value_type>(
_mm512_insertf64x2(__m512d(), __x, 0));
}
else if constexpr (__have_avx512f
&& std::is_floating_point_v<value_type>)
{
return __vector_bitcast<value_type>(
_mm512_insertf32x4(__m512(), reinterpret_cast<__m128>(__x), 0));
}
else if constexpr (__have_avx512f && _Np * sizeof(value_type) == 16)
{
return __vector_bitcast<value_type>(
_mm512_inserti32x4(__m512i(), __to_intrin(__x), 0));
}
#endif
return __concat(__concat(__x, _Tp()),
__vector_type_t<value_type, _Np * 2>());
}
else if constexpr (_ToN == 8 * _Np)
return __concat(operator __vector_type_t<value_type, _Np * 4>(),
__vector_type_t<value_type, _Np * 4>());
else if constexpr (_ToN == 16 * _Np)
return __concat(operator __vector_type_t<value_type, _Np * 8>(),
__vector_type_t<value_type, _Np * 8>());
else
__assert_unreachable<_Tp>();
}
};
template <typename _Tp, typename _TVT = _VectorTraits<_Tp>>
_GLIBCXX_SIMD_INTRINSIC _ZeroExtendProxy<_Tp, _TVT>
__zero_extend(_Tp __x)
{
return {__x};
}
template <
int _Offset, int _SplitBy, typename _Tp, typename _TVT = _VectorTraits<_Tp>,
typename _R
= __vector_type_t<typename _TVT::value_type, _TVT::_S_full_size / _SplitBy>>
_GLIBCXX_SIMD_INTRINSIC constexpr _R
__extract(_Tp __in)
{
using value_type = typename _TVT::value_type;
#if _GLIBCXX_SIMD_X86INTRIN
if constexpr (sizeof(_Tp) == 64 && _SplitBy == 4 && _Offset > 0)
{
if constexpr (__have_avx512dq && std::is_same_v<double, value_type>)
return _mm512_extractf64x2_pd(__to_intrin(__in), _Offset);
else if constexpr (std::is_floating_point_v<value_type>)
return __vector_bitcast<value_type>(
_mm512_extractf32x4_ps(__intrin_bitcast<__m512>(__in), _Offset));
else
return reinterpret_cast<_R>(
_mm512_extracti32x4_epi32(__intrin_bitcast<__m512i>(__in), _Offset));
}
else
#endif
{
#ifdef _GLIBCXX_SIMD_WORKAROUND_XXX_1
using _W = std::conditional_t<
std::is_floating_point_v<value_type>, double,
std::conditional_t<(sizeof(_R) >= 16), long long, value_type>>;
static_assert(sizeof(_R) % sizeof(_W) == 0);
constexpr int __return_width = sizeof(_R) / sizeof(_W);
using _Up = __vector_type_t<_W, __return_width>;
const auto __x = __vector_bitcast<_W>(__in);
#else
constexpr int __return_width = _TVT::_S_full_size / _SplitBy;
using _Up = _R;
const __vector_type_t<value_type, _TVT::_S_full_size>& __x
= __in;
#endif
constexpr int _O = _Offset * __return_width;
return __call_with_subscripts<__return_width, _O>(
__x, [](auto... __entries) {
return reinterpret_cast<_R>(_Up{__entries...});
});
}
}
template <typename _Tp,
typename _R
= __vector_type8_t<typename _VectorTraits<_Tp>::value_type>>
_GLIBCXX_SIMD_INTRINSIC constexpr _R
__lo64(_Tp __x)
{
_R __r{};
__builtin_memcpy(&__r, &__x, 8);
return __r;
}
template <typename _Tp,
typename _R
= __vector_type8_t<typename _VectorTraits<_Tp>::value_type>>
_GLIBCXX_SIMD_INTRINSIC constexpr _R
__hi64(_Tp __x)
{
static_assert(sizeof(_Tp) == 16, "use __hi64z if you meant it");
_R __r{};
__builtin_memcpy(&__r, reinterpret_cast<const char*>(&__x) + 8, 8);
return __r;
}
template <typename _Tp,
typename _R
= __vector_type8_t<typename _VectorTraits<_Tp>::value_type>>
_GLIBCXX_SIMD_INTRINSIC constexpr _R
__hi64z([[maybe_unused]] _Tp __x)
{
_R __r{};
if constexpr (sizeof(_Tp) == 16)
__builtin_memcpy(&__r, reinterpret_cast<const char*>(&__x) + 8, 8);
return __r;
}
template <typename _Tp>
_GLIBCXX_SIMD_INTRINSIC constexpr auto
__lo128(_Tp __x)
{
return __extract<0, sizeof(_Tp) / 16>(__x);
}
template <typename _Tp>
_GLIBCXX_SIMD_INTRINSIC constexpr auto
__hi128(_Tp __x)
{
static_assert(sizeof(__x) == 32);
return __extract<1, 2>(__x);
}
template <typename _Tp>
_GLIBCXX_SIMD_INTRINSIC constexpr auto
__lo256(_Tp __x)
{
static_assert(sizeof(__x) == 64);
return __extract<0, 2>(__x);
}
template <typename _Tp>
_GLIBCXX_SIMD_INTRINSIC constexpr auto
__hi256(_Tp __x)
{
static_assert(sizeof(__x) == 64);
return __extract<1, 2>(__x);
}
template <typename _Tp> struct _AutoCast
{
static_assert(__is_vector_type_v<_Tp>);
const _Tp __x;
template <typename _Up, typename _UVT = _VectorTraits<_Up>>
_GLIBCXX_SIMD_INTRINSIC constexpr operator _Up() const
{
return __intrin_bitcast<typename _UVT::type>(__x);
}
};
template <typename _Tp>
_GLIBCXX_SIMD_INTRINSIC constexpr _AutoCast<_Tp>
__auto_bitcast(const _Tp& __x)
{
return {__x};
}
template <typename _Tp, size_t _Np>
_GLIBCXX_SIMD_INTRINSIC constexpr _AutoCast<
typename _SimdWrapper<_Tp, _Np>::_BuiltinType>
__auto_bitcast(const _SimdWrapper<_Tp, _Np>& __x)
{
return {__x._M_data};
}
#if _GLIBCXX_SIMD_HAVE_SSE_ABI
#if _GLIBCXX_SIMD_HAVE_AVX512F && _GLIBCXX_SIMD_X86INTRIN
template <size_t _Size> struct __bool_storage_member_type
{
static_assert((_Size & (_Size - 1)) != 0,
"This trait may only be used for non-power-of-2 sizes. "
"Power-of-2 sizes must be specialized.");
using type =
typename __bool_storage_member_type<__next_power_of_2(_Size)>::type;
};
template <> struct __bool_storage_member_type<1>
{
using type = bool;
};
template <> struct __bool_storage_member_type<2>
{
using type = __mmask8;
};
template <> struct __bool_storage_member_type<4>
{
using type = __mmask8;
};
template <> struct __bool_storage_member_type<8>
{
using type = __mmask8;
};
template <> struct __bool_storage_member_type<16>
{
using type = __mmask16;
};
template <> struct __bool_storage_member_type<32>
{
using type = __mmask32;
};
template <> struct __bool_storage_member_type<64>
{
using type = __mmask64;
};
#endif
#if _GLIBCXX_SIMD_HAVE_SSE
template <typename _Tp, size_t _Bytes>
struct __intrinsic_type<
_Tp, _Bytes, std::enable_if_t<__is_vectorizable_v<_Tp> && _Bytes <= 64>>
{
static_assert(!std::is_same_v<_Tp, long double>,
"no __intrinsic_type support for long double on x86");
static constexpr std::size_t _S_VBytes
= _Bytes <= 16 ? 16 : _Bytes <= 32 ? 32 : 64;
using type [[__gnu__::__vector_size__(_S_VBytes)]]
= std::conditional_t<std::is_integral_v<_Tp>, long long int, _Tp>;
};
#endif
#endif
#if _GLIBCXX_SIMD_HAVE_NEON
template <typename _Tp, size_t _Bytes>
struct __intrinsic_type<_Tp, _Bytes,
enable_if_t<__is_vectorizable_v<_Tp> && _Bytes <= 16>>
{
static constexpr int _S_VBytes = _Bytes <= 8 ? 8 : 16;
using _Ip = __int_for_sizeof_t<_Tp>;
using _Up = conditional_t<
is_floating_point_v<_Tp>, _Tp,
conditional_t<is_unsigned_v<_Tp>, make_unsigned_t<_Ip>, _Ip>>;
using type [[__gnu__::__vector_size__(_S_VBytes)]] = _Up;
};
#endif
#ifdef __ALTIVEC__
template <typename _Tp> struct __intrinsic_type_impl;
#define _GLIBCXX_SIMD_PPC_INTRIN(_Tp) \
template <> struct __intrinsic_type_impl<_Tp> \
{ \
using type = __vector _Tp; \
}
_GLIBCXX_SIMD_PPC_INTRIN(float);
_GLIBCXX_SIMD_PPC_INTRIN(double);
_GLIBCXX_SIMD_PPC_INTRIN(signed char);
_GLIBCXX_SIMD_PPC_INTRIN(unsigned char);
_GLIBCXX_SIMD_PPC_INTRIN(signed short);
_GLIBCXX_SIMD_PPC_INTRIN(unsigned short);
_GLIBCXX_SIMD_PPC_INTRIN(signed int);
_GLIBCXX_SIMD_PPC_INTRIN(unsigned int);
_GLIBCXX_SIMD_PPC_INTRIN(signed long);
_GLIBCXX_SIMD_PPC_INTRIN(unsigned long);
_GLIBCXX_SIMD_PPC_INTRIN(signed long long);
_GLIBCXX_SIMD_PPC_INTRIN(unsigned long long);
#undef _GLIBCXX_SIMD_PPC_INTRIN
template <typename _Tp, size_t _Bytes>
struct __intrinsic_type<
_Tp, _Bytes, std::enable_if_t<__is_vectorizable_v<_Tp> && _Bytes <= 16>>
{
static_assert(!std::is_same_v<_Tp, long double>,
"no __intrinsic_type support for long double on PPC");
#ifndef __VSX__
static_assert(!std::is_same_v<_Tp, double>,
"no __intrinsic_type support for double on PPC w/o VSX");
#endif
#ifndef __POWER8_VECTOR__
static_assert(!(std::is_integral_v<_Tp> && sizeof(_Tp) > 4),
"no __intrinsic_type support for integers larger than 4 Bytes "
"on PPC w/o POWER8 vectors");
#endif
using type = typename __intrinsic_type_impl<conditional_t<
is_floating_point_v<_Tp>, _Tp, __int_for_sizeof_t<_Tp>>>::type;
};
#endif
template <size_t _Width>
struct _SimdWrapper<
bool, _Width, std::void_t<typename __bool_storage_member_type<_Width>::type>>
{
using _BuiltinType = typename __bool_storage_member_type<_Width>::type;
using value_type = bool;
static constexpr size_t _S_full_size = sizeof(_BuiltinType) * __CHAR_BIT__;
_GLIBCXX_SIMD_INTRINSIC constexpr _SimdWrapper<bool, _S_full_size>
__as_full_vector() const
{
return _M_data;
}
_GLIBCXX_SIMD_INTRINSIC constexpr _SimdWrapper() = default;
_GLIBCXX_SIMD_INTRINSIC constexpr _SimdWrapper(_BuiltinType __k)
: _M_data(__k){};
_GLIBCXX_SIMD_INTRINSIC operator const _BuiltinType &() const
{
return _M_data;
}
_GLIBCXX_SIMD_INTRINSIC operator _BuiltinType&() { return _M_data; }
_GLIBCXX_SIMD_INTRINSIC _BuiltinType __intrin() const { return _M_data; }
_GLIBCXX_SIMD_INTRINSIC constexpr value_type operator[](size_t __i) const
{
return _M_data & (_BuiltinType(1) << __i);
}
template <size_t __i>
_GLIBCXX_SIMD_INTRINSIC constexpr value_type
operator[](_SizeConstant<__i>) const
{
return _M_data & (_BuiltinType(1) << __i);
}
_GLIBCXX_SIMD_INTRINSIC constexpr void _M_set(size_t __i, value_type __x)
{
if (__x)
_M_data |= (_BuiltinType(1) << __i);
else
_M_data &= ~(_BuiltinType(1) << __i);
}
_GLIBCXX_SIMD_INTRINSIC
constexpr bool _M_is_constprop() const
{
return __builtin_constant_p(_M_data);
}
_GLIBCXX_SIMD_INTRINSIC constexpr bool _M_is_constprop_none_of() const
{
if (__builtin_constant_p(_M_data))
{
constexpr int __nbits = sizeof(_BuiltinType) * __CHAR_BIT__;
constexpr _BuiltinType __active_mask
= ~_BuiltinType() >> (__nbits - _Width);
return (_M_data & __active_mask) == 0;
}
return false;
}
_GLIBCXX_SIMD_INTRINSIC constexpr bool _M_is_constprop_all_of() const
{
if (__builtin_constant_p(_M_data))
{
constexpr int __nbits = sizeof(_BuiltinType) * __CHAR_BIT__;
constexpr _BuiltinType __active_mask
= ~_BuiltinType() >> (__nbits - _Width);
return (_M_data & __active_mask) == __active_mask;
}
return false;
}
_BuiltinType _M_data;
};
template <bool _MustZeroInitPadding, typename _BuiltinType>
struct _SimdWrapperBase;
template <typename _BuiltinType>
struct _SimdWrapperBase<false, _BuiltinType>
{
_BuiltinType _M_data;
_GLIBCXX_SIMD_INTRINSIC constexpr _SimdWrapperBase() = default;
_GLIBCXX_SIMD_INTRINSIC constexpr _SimdWrapperBase(_BuiltinType __init)
: _M_data(__init)
{}
};
template <typename _BuiltinType>
struct _SimdWrapperBase<true, _BuiltinType>
{
_BuiltinType _M_data;
_GLIBCXX_SIMD_INTRINSIC constexpr _SimdWrapperBase() : _M_data() {}
_GLIBCXX_SIMD_INTRINSIC constexpr _SimdWrapperBase(_BuiltinType __init)
: _M_data(__init)
{}
};
template <typename _Tp, size_t _Width>
struct _SimdWrapper<
_Tp, _Width,
std::void_t<__vector_type_t<_Tp, _Width>, __intrinsic_type_t<_Tp, _Width>>>
: _SimdWrapperBase<__has_iec559_behavior<__signaling_NaN, _Tp>::value
&& sizeof(_Tp) * _Width
== sizeof(__vector_type_t<_Tp, _Width>),
__vector_type_t<_Tp, _Width>>
{
using _Base
= _SimdWrapperBase<__has_iec559_behavior<__signaling_NaN, _Tp>::value
&& sizeof(_Tp) * _Width
== sizeof(__vector_type_t<_Tp, _Width>),
__vector_type_t<_Tp, _Width>>;
static_assert(__is_vectorizable_v<_Tp>);
static_assert(_Width >= 2);
using _BuiltinType = __vector_type_t<_Tp, _Width>;
using value_type = _Tp;
static inline constexpr size_t _S_full_size
= sizeof(_BuiltinType) / sizeof(value_type);
static inline constexpr int _S_size = _Width;
static inline constexpr bool _S_is_partial = _S_full_size != _S_size;
using _Base::_M_data;
_GLIBCXX_SIMD_INTRINSIC constexpr _SimdWrapper<_Tp, _S_full_size>
__as_full_vector() const
{
return _M_data;
}
_GLIBCXX_SIMD_INTRINSIC constexpr _SimdWrapper(
std::initializer_list<_Tp> __init)
: _Base(__generate_from_n_evaluations<_Width, _BuiltinType>(
[&](auto __i) { return __init.begin()[__i.value]; }))
{}
_GLIBCXX_SIMD_INTRINSIC constexpr _SimdWrapper() = default;
_GLIBCXX_SIMD_INTRINSIC constexpr _SimdWrapper(const _SimdWrapper&) = default;
_GLIBCXX_SIMD_INTRINSIC constexpr _SimdWrapper(_SimdWrapper&&) = default;
_GLIBCXX_SIMD_INTRINSIC constexpr _SimdWrapper& operator=(const _SimdWrapper&)
= default;
_GLIBCXX_SIMD_INTRINSIC constexpr _SimdWrapper& operator=(_SimdWrapper&&)
= default;
template <typename _V, typename = std::enable_if_t<std::disjunction_v<
is_same<_V, __vector_type_t<_Tp, _Width>>,
is_same<_V, __intrinsic_type_t<_Tp, _Width>>>>>
_GLIBCXX_SIMD_INTRINSIC constexpr _SimdWrapper(_V __x)
: _Base(__vector_bitcast<_Tp, _Width>(
__x))
{}
template <typename... _As,
typename
= enable_if_t<((std::is_same_v<simd_abi::scalar, _As> && ...)
&& sizeof...(_As) <= _Width)>>
_GLIBCXX_SIMD_INTRINSIC constexpr operator _SimdTuple<_Tp, _As...>() const
{
const auto& dd = _M_data;
return __generate_from_n_evaluations<sizeof...(_As),
_SimdTuple<_Tp, _As...>>([&](
auto __i) constexpr { return dd[int(__i)]; });
}
_GLIBCXX_SIMD_INTRINSIC constexpr operator const _BuiltinType &() const
{
return _M_data;
}
_GLIBCXX_SIMD_INTRINSIC constexpr operator _BuiltinType&() { return _M_data; }
_GLIBCXX_SIMD_INTRINSIC constexpr _Tp operator[](size_t __i) const
{
return _M_data[__i];
}
template <size_t __i>
_GLIBCXX_SIMD_INTRINSIC constexpr _Tp operator[](_SizeConstant<__i>) const
{
return _M_data[__i];
}
_GLIBCXX_SIMD_INTRINSIC constexpr void _M_set(size_t __i, _Tp __x)
{
_M_data[__i] = __x;
}
_GLIBCXX_SIMD_INTRINSIC
constexpr bool _M_is_constprop() const
{
return __builtin_constant_p(_M_data);
}
_GLIBCXX_SIMD_INTRINSIC constexpr bool _M_is_constprop_none_of() const
{
if (__builtin_constant_p(_M_data))
{
bool __r = true;
if constexpr (std::is_floating_point_v<_Tp>)
{
using _Ip = __int_for_sizeof_t<_Tp>;
const auto __intdata = __vector_bitcast<_Ip>(_M_data);
__execute_n_times<_Width>(
[&](auto __i) { __r &= __intdata[__i.value] == _Ip(); });
}
else
__execute_n_times<_Width>(
[&](auto __i) { __r &= _M_data[__i.value] == _Tp(); });
return __r;
}
return false;
}
_GLIBCXX_SIMD_INTRINSIC constexpr bool _M_is_constprop_all_of() const
{
if (__builtin_constant_p(_M_data))
{
bool __r = true;
if constexpr (std::is_floating_point_v<_Tp>)
{
using _Ip = __int_for_sizeof_t<_Tp>;
const auto __intdata = __vector_bitcast<_Ip>(_M_data);
__execute_n_times<_Width>(
[&](auto __i) { __r &= __intdata[__i.value] == ~_Ip(); });
}
else
__execute_n_times<_Width>(
[&](auto __i) { __r &= _M_data[__i.value] == ~_Tp(); });
return __r;
}
return false;
}
};
template <typename _Tp>
constexpr size_t
__vectorized_sizeof()
{
if constexpr (!__is_vectorizable_v<_Tp>)
return 0;
if constexpr (sizeof(_Tp) <= 8)
{
if constexpr (__have_avx512bw)
return 64;
if constexpr (__have_avx512f && sizeof(_Tp) >= 4)
return 64;
if constexpr (__have_avx2)
return 32;
if constexpr (__have_avx && std::is_floating_point_v<_Tp>)
return 32;
if constexpr (__have_sse2)
return 16;
if constexpr (__have_sse && std::is_same_v<_Tp, float>)
return 16;
if constexpr (__have_power8vec || (__have_power_vmx && (sizeof(_Tp) < 8))
|| (__have_power_vsx && std::is_floating_point_v<_Tp>) )
return 16;
if constexpr (__have_neon_a64
|| (__have_neon_a32 && !is_same_v<_Tp, double>) )
return 16;
if constexpr (__have_neon
&& sizeof(_Tp) < 8
&& (
#ifdef __clang__
#ifdef __FAST_MATH__
true
#else
false
#endif
#else
__GCC_IEC_559 == 0
#endif
|| !std::is_floating_point_v<_Tp>) )
return 16;
}
return sizeof(_Tp);
}
namespace simd_abi {
template <typename _Tp>
inline constexpr int max_fixed_size
= (__have_avx512bw && sizeof(_Tp) == 1) ? 64 : 32;
#if defined __x86_64__ || defined __aarch64__
template <typename _Tp>
using compatible
= std::conditional_t<(sizeof(_Tp) <= 8), _VecBuiltin<16>, scalar>;
#elif defined __ARM_NEON
template <typename _Tp>
using compatible
= std::conditional_t<(sizeof(_Tp) < 8), _VecBuiltin<16>, scalar>;
#else
template <typename> using compatible = scalar;
#endif
template <typename _Tp>
constexpr auto
__determine_native_abi()
{
constexpr size_t __bytes = __vectorized_sizeof<_Tp>();
if constexpr (__bytes == sizeof(_Tp))
return static_cast<scalar*>(nullptr);
else if constexpr (__have_avx512vl || (__have_avx512f && __bytes == 64))
return static_cast<_VecBltnBtmsk<__bytes>*>(nullptr);
else
return static_cast<_VecBuiltin<__bytes>*>(nullptr);
}
template <typename _Tp, typename = enable_if_t<__is_vectorizable_v<_Tp>>>
using native = std::remove_pointer_t<decltype(__determine_native_abi<_Tp>())>;
#if defined _GLIBCXX_SIMD_DEFAULT_ABI
template <typename _Tp> using __default_abi = _GLIBCXX_SIMD_DEFAULT_ABI<_Tp>;
#else
template <typename _Tp> using __default_abi = compatible<_Tp>;
#endif
}
template <typename _Tp, typename = std::void_t<>> struct is_abi_tag : false_type
{
};
template <typename _Tp>
struct is_abi_tag<_Tp, std::void_t<typename _Tp::_IsValidAbiTag>>
: public _Tp::_IsValidAbiTag
{
};
template <typename _Tp>
inline constexpr bool is_abi_tag_v = is_abi_tag<_Tp>::value;
template <typename _Tp> struct is_simd : public false_type
{
};
template <typename _Tp> inline constexpr bool is_simd_v = is_simd<_Tp>::value;
template <typename _Tp> struct is_simd_mask : public false_type
{
};
template <typename _Tp>
inline constexpr bool is_simd_mask_v = is_simd_mask<_Tp>::value;
template <typename _Tp, typename _Abi, typename = void> struct __simd_size_impl
{
};
template <typename _Tp, typename _Abi>
struct __simd_size_impl<
_Tp, _Abi,
enable_if_t<std::conjunction_v<__is_vectorizable<_Tp>,
std::experimental::is_abi_tag<_Abi>>>>
: _SizeConstant<_Abi::template _S_size<_Tp>>
{
};
template <typename _Tp, typename _Abi = simd_abi::__default_abi<_Tp>>
struct simd_size : __simd_size_impl<_Tp, _Abi>
{
};
template <typename _Tp, typename _Abi = simd_abi::__default_abi<_Tp>>
inline constexpr size_t simd_size_v = simd_size<_Tp, _Abi>::value;
template <typename _Tp, std::size_t _Np, typename = void> struct __deduce_impl;
namespace simd_abi {
template <typename _Tp, std::size_t _Np, typename...>
struct deduce : std::experimental::__deduce_impl<_Tp, _Np>
{
};
template <typename _Tp, size_t _Np, typename... _Abis>
using deduce_t = typename deduce<_Tp, _Np, _Abis...>::type;
}
template <typename _Tp, typename _V, typename = void> struct rebind_simd;
template <typename _Tp, typename _Up, typename _Abi>
struct rebind_simd<
_Tp, simd<_Up, _Abi>,
void_t<simd_abi::deduce_t<_Tp, simd_size_v<_Up, _Abi>, _Abi>>>
{
using type = simd<_Tp, simd_abi::deduce_t<_Tp, simd_size_v<_Up, _Abi>, _Abi>>;
};
template <typename _Tp, typename _Up, typename _Abi>
struct rebind_simd<
_Tp, simd_mask<_Up, _Abi>,
void_t<simd_abi::deduce_t<_Tp, simd_size_v<_Up, _Abi>, _Abi>>>
{
using type
= simd_mask<_Tp, simd_abi::deduce_t<_Tp, simd_size_v<_Up, _Abi>, _Abi>>;
};
template <typename _Tp, typename _V>
using rebind_simd_t = typename rebind_simd<_Tp, _V>::type;
template <int _Np, typename _V, typename = void> struct resize_simd;
template <int _Np, typename _Tp, typename _Abi>
struct resize_simd<_Np, simd<_Tp, _Abi>,
void_t<simd_abi::deduce_t<_Tp, _Np, _Abi>>>
{
using type = simd<_Tp, simd_abi::deduce_t<_Tp, _Np, _Abi>>;
};
template <int _Np, typename _Tp, typename _Abi>
struct resize_simd<_Np, simd_mask<_Tp, _Abi>,
void_t<simd_abi::deduce_t<_Tp, _Np, _Abi>>>
{
using type = simd_mask<_Tp, simd_abi::deduce_t<_Tp, _Np, _Abi>>;
};
template <int _Np, typename _V>
using resize_simd_t = typename resize_simd<_Np, _V>::type;
template <typename _Tp, typename _Up = typename _Tp::value_type>
struct memory_alignment
: public _SizeConstant<vector_aligned_tag::_S_alignment<_Tp, _Up>>
{
};
template <typename _Tp, typename _Up = typename _Tp::value_type>
inline constexpr size_t memory_alignment_v = memory_alignment<_Tp, _Up>::value;
template <typename _Tp, typename _Abi = simd_abi::__default_abi<_Tp>>
class simd;
template <typename _Tp, typename _Abi>
struct is_simd<simd<_Tp, _Abi>> : public true_type
{
};
template <typename _Tp> using native_simd = simd<_Tp, simd_abi::native<_Tp>>;
template <typename _Tp, int _Np>
using fixed_size_simd = simd<_Tp, simd_abi::fixed_size<_Np>>;
template <typename _Tp, size_t _Np>
using __deduced_simd = simd<_Tp, simd_abi::deduce_t<_Tp, _Np>>;
template <typename _Tp, typename _Abi = simd_abi::__default_abi<_Tp>>
class simd_mask;
template <typename _Tp, typename _Abi>
struct is_simd_mask<simd_mask<_Tp, _Abi>> : public true_type
{
};
template <typename _Tp>
using native_simd_mask = simd_mask<_Tp, simd_abi::native<_Tp>>;
template <typename _Tp, int _Np>
using fixed_size_simd_mask = simd_mask<_Tp, simd_abi::fixed_size<_Np>>;
template <typename _Tp, size_t _Np>
using __deduced_simd_mask = simd_mask<_Tp, simd_abi::deduce_t<_Tp, _Np>>;
template <typename _Tp, typename _Up, typename _Ap, bool = is_simd_v<_Tp>,
typename = void>
struct __static_simd_cast_return_type;
template <typename _Tp, typename _A0, typename _Up, typename _Ap>
struct __static_simd_cast_return_type<simd_mask<_Tp, _A0>, _Up, _Ap, false,
void>
: __static_simd_cast_return_type<simd<_Tp, _A0>, _Up, _Ap>
{
};
template <typename _Tp, typename _Up, typename _Ap>
struct __static_simd_cast_return_type<
_Tp, _Up, _Ap, true, enable_if_t<_Tp::size() == simd_size_v<_Up, _Ap>>>
{
using type = _Tp;
};
template <typename _Tp, typename _Ap>
struct __static_simd_cast_return_type<_Tp, _Tp, _Ap, false,
#ifdef _GLIBCXX_SIMD_FIX_P2TS_ISSUE66
enable_if_t<__is_vectorizable_v<_Tp>>
#else
void
#endif
>
{
using type = simd<_Tp, _Ap>;
};
template <typename _Tp, typename = void> struct __safe_make_signed
{
using type = _Tp;
};
template <typename _Tp>
struct __safe_make_signed<_Tp, enable_if_t<std::is_integral_v<_Tp>>>
{
using type = std::make_signed_t<std::make_unsigned_t<_Tp>>;
};
template <typename _Tp>
using safe_make_signed_t = typename __safe_make_signed<_Tp>::type;
template <typename _Tp, typename _Up, typename _Ap>
struct __static_simd_cast_return_type<_Tp, _Up, _Ap, false,
#ifdef _GLIBCXX_SIMD_FIX_P2TS_ISSUE66
enable_if_t<__is_vectorizable_v<_Tp>>
#else
void
#endif
>
{
using type = std::conditional_t<
(std::is_integral_v<_Up> && std::is_integral_v<_Tp> &&
#ifndef _GLIBCXX_SIMD_FIX_P2TS_ISSUE65
std::is_signed_v<_Up> != std::is_signed_v<_Tp> &&
#endif
std::is_same_v<safe_make_signed_t<_Up>, safe_make_signed_t<_Tp>>),
simd<_Tp, _Ap>, fixed_size_simd<_Tp, simd_size_v<_Up, _Ap>>>;
};
template <typename _Tp, typename _Up, typename _Ap,
typename _R
= typename __static_simd_cast_return_type<_Tp, _Up, _Ap>::type>
_GLIBCXX_SIMD_INTRINSIC _GLIBCXX_SIMD_CONSTEXPR _R
static_simd_cast(const simd<_Up, _Ap>& __x)
{
if constexpr (std::is_same<_R, simd<_Up, _Ap>>::value)
{
return __x;
}
else
{
_SimdConverter<_Up, _Ap, typename _R::value_type, typename _R::abi_type>
__c;
return _R(__private_init, __c(__data(__x)));
}
}
namespace __proposed {
template <typename _Tp, typename _Up, typename _Ap,
typename _R
= typename __static_simd_cast_return_type<_Tp, _Up, _Ap>::type>
_GLIBCXX_SIMD_INTRINSIC _GLIBCXX_SIMD_CONSTEXPR typename _R::mask_type
static_simd_cast(const simd_mask<_Up, _Ap>& __x)
{
using _RM = typename _R::mask_type;
return {__private_init, _RM::abi_type::_MaskImpl::template _S_convert<
typename _RM::simd_type::value_type>(__x)};
}
}
template <typename _Tp, typename _Up, typename _Ap,
typename _To = __value_type_or_identity_t<_Tp>>
_GLIBCXX_SIMD_INTRINSIC _GLIBCXX_SIMD_CONSTEXPR auto
simd_cast(const simd<_ValuePreserving<_Up, _To>, _Ap>& __x)
-> decltype(static_simd_cast<_Tp>(__x))
{
return static_simd_cast<_Tp>(__x);
}
namespace __proposed {
template <typename _Tp, typename _Up, typename _Ap,
typename _To = __value_type_or_identity_t<_Tp>>
_GLIBCXX_SIMD_INTRINSIC _GLIBCXX_SIMD_CONSTEXPR auto
simd_cast(const simd_mask<_ValuePreserving<_Up, _To>, _Ap>& __x)
-> decltype(static_simd_cast<_Tp>(__x))
{
return static_simd_cast<_Tp>(__x);
}
}
namespace __proposed {
template <typename _Tp, typename _Up, typename _Ap>
_GLIBCXX_SIMD_INTRINSIC _GLIBCXX_SIMD_CONSTEXPR enable_if_t<
conjunction_v<is_simd<_Tp>, is_same<typename _Tp::value_type, _Up>>, _Tp>
resizing_simd_cast(const simd<_Up, _Ap>& __x)
{
if constexpr (is_same_v<typename _Tp::abi_type, _Ap>)
return __x;
else if constexpr (simd_size_v<_Up, _Ap> == 1)
{
_Tp __r{};
__r[0] = __x[0];
return __r;
}
else if constexpr (_Tp::size() == 1)
return __x[0];
else if constexpr (sizeof(_Tp) == sizeof(__x) && !__is_fixed_size_abi_v<_Ap>)
return {__private_init,
__vector_bitcast<typename _Tp::value_type, _Tp::size()>(
_Ap::_S_masked(__data(__x))._M_data)};
else
{
_Tp __r{};
__builtin_memcpy(&__data(__r), &__data(__x),
sizeof(_Up)
* std::min(_Tp::size(), simd_size_v<_Up, _Ap>));
return __r;
}
}
template <typename _Tp, typename _Up, typename _Ap>
_GLIBCXX_SIMD_INTRINSIC
_GLIBCXX_SIMD_CONSTEXPR enable_if_t<is_simd_mask_v<_Tp>, _Tp>
resizing_simd_cast(const simd_mask<_Up, _Ap>& __x)
{
return {__private_init, _Tp::abi_type::_MaskImpl::template _S_convert<
typename _Tp::simd_type::value_type>(__x)};
}
}
template <typename _Tp, int _Np>
_GLIBCXX_SIMD_INTRINSIC fixed_size_simd<_Tp, _Np>
to_fixed_size(const fixed_size_simd<_Tp, _Np>& __x)
{
return __x;
}
template <typename _Tp, int _Np>
_GLIBCXX_SIMD_INTRINSIC fixed_size_simd_mask<_Tp, _Np>
to_fixed_size(const fixed_size_simd_mask<_Tp, _Np>& __x)
{
return __x;
}
template <typename _Tp, typename _Ap>
_GLIBCXX_SIMD_INTRINSIC auto
to_fixed_size(const simd<_Tp, _Ap>& __x)
{
return simd<_Tp, simd_abi::fixed_size<simd_size_v<_Tp, _Ap>>>([&__x](
auto __i) constexpr { return __x[__i]; });
}
template <typename _Tp, typename _Ap>
_GLIBCXX_SIMD_INTRINSIC auto
to_fixed_size(const simd_mask<_Tp, _Ap>& __x)
{
constexpr int _Np = simd_mask<_Tp, _Ap>::size();
fixed_size_simd_mask<_Tp, _Np> __r;
__execute_n_times<_Np>([&](auto __i) constexpr { __r[__i] = __x[__i]; });
return __r;
}
template <typename _Tp, int _Np>
_GLIBCXX_SIMD_INTRINSIC
enable_if_t<(_Np == native_simd<_Tp>::size()), native_simd<_Tp>>
to_native(const fixed_size_simd<_Tp, _Np>& __x)
{
alignas(memory_alignment_v<native_simd<_Tp>>) _Tp __mem[_Np];
__x.copy_to(__mem, vector_aligned);
return {__mem, vector_aligned};
}
template <typename _Tp, size_t _Np>
_GLIBCXX_SIMD_INTRINSIC
enable_if_t<(_Np == native_simd_mask<_Tp>::size()), native_simd_mask<_Tp>>
to_native(const fixed_size_simd_mask<_Tp, _Np>& __x)
{
return native_simd_mask<_Tp>([&](auto __i) constexpr { return __x[__i]; });
}
template <typename _Tp, size_t _Np>
_GLIBCXX_SIMD_INTRINSIC enable_if_t<(_Np == simd<_Tp>::size()), simd<_Tp>>
to_compatible(const simd<_Tp, simd_abi::fixed_size<_Np>>& __x)
{
alignas(memory_alignment_v<simd<_Tp>>) _Tp __mem[_Np];
__x.copy_to(__mem, vector_aligned);
return {__mem, vector_aligned};
}
template <typename _Tp, size_t _Np>
_GLIBCXX_SIMD_INTRINSIC
enable_if_t<(_Np == simd_mask<_Tp>::size()), simd_mask<_Tp>>
to_compatible(const simd_mask<_Tp, simd_abi::fixed_size<_Np>>& __x)
{
return simd_mask<_Tp>([&](auto __i) constexpr { return __x[__i]; });
}
template <typename _M, typename _Tp> class const_where_expression
{
using _V = _Tp;
static_assert(std::is_same_v<_V, __remove_cvref_t<_Tp>>);
struct Wrapper
{
using value_type = _V;
};
protected:
using _Impl = typename _V::_Impl;
using value_type = typename std::conditional_t<std::is_arithmetic<_V>::value,
Wrapper, _V>::value_type;
_GLIBCXX_SIMD_INTRINSIC friend const _M&
__get_mask(const const_where_expression& __x)
{
return __x._M_k;
}
_GLIBCXX_SIMD_INTRINSIC friend const _Tp&
__get_lvalue(const const_where_expression& __x)
{
return __x._M_value;
}
const _M& _M_k;
_Tp& _M_value;
public:
const_where_expression(const const_where_expression&) = delete;
const_where_expression& operator=(const const_where_expression&) = delete;
_GLIBCXX_SIMD_INTRINSIC const_where_expression(const _M& __kk, const _Tp& dd)
: _M_k(__kk), _M_value(const_cast<_Tp&>(dd))
{}
_GLIBCXX_SIMD_INTRINSIC _V operator-() const&&
{
return {__private_init,
_Impl::template _S_masked_unary<std::negate>(__data(_M_k),
__data(_M_value))};
}
template <typename _Up, typename _Flags>
[[nodiscard]] _GLIBCXX_SIMD_INTRINSIC _V
copy_from(const _LoadStorePtr<_Up, value_type>* __mem, _Flags) const&&
{
return {__private_init,
_Impl::_S_masked_load(__data(_M_value), __data(_M_k),
_Flags::template _S_apply<_V>(__mem))};
}
template <typename _Up, typename _Flags>
_GLIBCXX_SIMD_INTRINSIC void copy_to(_LoadStorePtr<_Up, value_type>* __mem,
_Flags) const&&
{
_Impl::_S_masked_store(__data(_M_value),
_Flags::template _S_apply<_V>(__mem), __data(_M_k));
}
};
template <typename _Tp> class const_where_expression<bool, _Tp>
{
using _M = bool;
using _V = _Tp;
static_assert(std::is_same_v<_V, __remove_cvref_t<_Tp>>);
struct Wrapper
{
using value_type = _V;
};
protected:
using value_type = typename std::conditional_t<std::is_arithmetic<_V>::value,
Wrapper, _V>::value_type;
_GLIBCXX_SIMD_INTRINSIC friend const _M&
__get_mask(const const_where_expression& __x)
{
return __x._M_k;
}
_GLIBCXX_SIMD_INTRINSIC friend const _Tp&
__get_lvalue(const const_where_expression& __x)
{
return __x._M_value;
}
const bool _M_k;
_Tp& _M_value;
public:
const_where_expression(const const_where_expression&) = delete;
const_where_expression& operator=(const const_where_expression&) = delete;
_GLIBCXX_SIMD_INTRINSIC const_where_expression(const bool __kk, const _Tp& dd)
: _M_k(__kk), _M_value(const_cast<_Tp&>(dd))
{}
_GLIBCXX_SIMD_INTRINSIC _V operator-() const&&
{
return _M_k ? -_M_value : _M_value;
}
template <typename _Up, typename _Flags>
[[nodiscard]] _GLIBCXX_SIMD_INTRINSIC _V
copy_from(const _LoadStorePtr<_Up, value_type>* __mem, _Flags) const&&
{
return _M_k ? static_cast<_V>(__mem[0]) : _M_value;
}
template <typename _Up, typename _Flags>
_GLIBCXX_SIMD_INTRINSIC void copy_to(_LoadStorePtr<_Up, value_type>* __mem,
_Flags) const&&
{
if (_M_k)
{
__mem[0] = _M_value;
}
}
};
template <typename _M, typename _Tp>
class where_expression : public const_where_expression<_M, _Tp>
{
using _Impl = typename const_where_expression<_M, _Tp>::_Impl;
static_assert(!std::is_const<_Tp>::value,
"where_expression may only be instantiated with __a non-const "
"_Tp parameter");
using typename const_where_expression<_M, _Tp>::value_type;
using const_where_expression<_M, _Tp>::_M_k;
using const_where_expression<_M, _Tp>::_M_value;
static_assert(
std::is_same<typename _M::abi_type, typename _Tp::abi_type>::value, "");
static_assert(_M::size() == _Tp::size(), "");
_GLIBCXX_SIMD_INTRINSIC friend _Tp& __get_lvalue(where_expression& __x)
{
return __x._M_value;
}
public:
where_expression(const where_expression&) = delete;
where_expression& operator=(const where_expression&) = delete;
_GLIBCXX_SIMD_INTRINSIC where_expression(const _M& __kk, _Tp& dd)
: const_where_expression<_M, _Tp>(__kk, dd)
{}
template <typename _Up> _GLIBCXX_SIMD_INTRINSIC void operator=(_Up&& __x) &&
{
_Impl::_S_masked_assign(__data(_M_k), __data(_M_value),
__to_value_type_or_member_type<_Tp>(
static_cast<_Up&&>(__x)));
}
#define _GLIBCXX_SIMD_OP_(__op,__name) \
template <typename _Up> \
_GLIBCXX_SIMD_INTRINSIC void operator __op##=(_Up&& __x)&& \
{ \
_Impl::template _S_masked_cassign( \
__data(_M_k), __data(_M_value), \
__to_value_type_or_member_type<_Tp>(static_cast<_Up&&>(__x)), \
[](auto __impl, auto __lhs, auto __rhs) constexpr { \
return __impl.__name(__lhs, __rhs); \
}); \
} \
static_assert(true)
_GLIBCXX_SIMD_OP_(+, _S_plus);
_GLIBCXX_SIMD_OP_(-, _S_minus);
_GLIBCXX_SIMD_OP_(*, _S_multiplies);
_GLIBCXX_SIMD_OP_(/, _S_divides);
_GLIBCXX_SIMD_OP_(%, _S_modulus);
_GLIBCXX_SIMD_OP_(&, _S_bit_and);
_GLIBCXX_SIMD_OP_(|, _S_bit_or);
_GLIBCXX_SIMD_OP_(^, _S_bit_xor);
_GLIBCXX_SIMD_OP_(<<, _S_shift_left);
_GLIBCXX_SIMD_OP_(>>, _S_shift_right);
#undef _GLIBCXX_SIMD_OP_
_GLIBCXX_SIMD_INTRINSIC void operator++() &&
{
__data(_M_value)
= _Impl::template _S_masked_unary<__increment>(__data(_M_k),
__data(_M_value));
}
_GLIBCXX_SIMD_INTRINSIC void operator++(int) &&
{
__data(_M_value)
= _Impl::template _S_masked_unary<__increment>(__data(_M_k),
__data(_M_value));
}
_GLIBCXX_SIMD_INTRINSIC void operator--() &&
{
__data(_M_value)
= _Impl::template _S_masked_unary<__decrement>(__data(_M_k),
__data(_M_value));
}
_GLIBCXX_SIMD_INTRINSIC void operator--(int) &&
{
__data(_M_value)
= _Impl::template _S_masked_unary<__decrement>(__data(_M_k),
__data(_M_value));
}
template <typename _Up, typename _Flags>
_GLIBCXX_SIMD_INTRINSIC void
copy_from(const _LoadStorePtr<_Up, value_type>* __mem, _Flags) &&
{
__data(_M_value)
= _Impl::_S_masked_load(__data(_M_value), __data(_M_k),
_Flags::template _S_apply<_Tp>(__mem));
}
};
template <typename _Tp>
class where_expression<bool, _Tp> : public const_where_expression<bool, _Tp>
{
using _M = bool;
using typename const_where_expression<_M, _Tp>::value_type;
using const_where_expression<_M, _Tp>::_M_k;
using const_where_expression<_M, _Tp>::_M_value;
public:
where_expression(const where_expression&) = delete;
where_expression& operator=(const where_expression&) = delete;
_GLIBCXX_SIMD_INTRINSIC where_expression(const _M& __kk, _Tp& dd)
: const_where_expression<_M, _Tp>(__kk, dd)
{}
#define _GLIBCXX_SIMD_OP_(__op) \
template <typename _Up> \
_GLIBCXX_SIMD_INTRINSIC void operator __op(_Up&& __x)&& \
{ \
if (_M_k) \
{ \
_M_value __op static_cast<_Up&&>(__x); \
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
_GLIBCXX_SIMD_INTRINSIC void operator++() &&
{
if (_M_k)
{
++_M_value;
}
}
_GLIBCXX_SIMD_INTRINSIC void operator++(int) &&
{
if (_M_k)
{
++_M_value;
}
}
_GLIBCXX_SIMD_INTRINSIC void operator--() &&
{
if (_M_k)
{
--_M_value;
}
}
_GLIBCXX_SIMD_INTRINSIC void operator--(int) &&
{
if (_M_k)
{
--_M_value;
}
}
template <typename _Up, typename _Flags>
_GLIBCXX_SIMD_INTRINSIC void
copy_from(const _LoadStorePtr<_Up, value_type>* __mem, _Flags) &&
{
if (_M_k)
{
_M_value = __mem[0];
}
}
};
template <typename _Tp, typename _Ap>
_GLIBCXX_SIMD_INTRINSIC where_expression<simd_mask<_Tp, _Ap>, simd<_Tp, _Ap>>
where(const typename simd<_Tp, _Ap>::mask_type& __k, simd<_Tp, _Ap>& __value)
{
return {__k, __value};
}
template <typename _Tp, typename _Ap>
_GLIBCXX_SIMD_INTRINSIC
const_where_expression<simd_mask<_Tp, _Ap>, simd<_Tp, _Ap>>
where(const typename simd<_Tp, _Ap>::mask_type& __k,
const simd<_Tp, _Ap>& __value)
{
return {__k, __value};
}
template <typename _Tp, typename _Ap>
_GLIBCXX_SIMD_INTRINSIC
where_expression<simd_mask<_Tp, _Ap>, simd_mask<_Tp, _Ap>>
where(const std::remove_const_t<simd_mask<_Tp, _Ap>>& __k,
simd_mask<_Tp, _Ap>& __value)
{
return {__k, __value};
}
template <typename _Tp, typename _Ap>
_GLIBCXX_SIMD_INTRINSIC
const_where_expression<simd_mask<_Tp, _Ap>, simd_mask<_Tp, _Ap>>
where(const std::remove_const_t<simd_mask<_Tp, _Ap>>& __k,
const simd_mask<_Tp, _Ap>& __value)
{
return {__k, __value};
}
template <typename _Tp>
_GLIBCXX_SIMD_INTRINSIC where_expression<bool, _Tp>
where(_ExactBool __k, _Tp& __value)
{
return {__k, __value};
}
template <typename _Tp>
_GLIBCXX_SIMD_INTRINSIC const_where_expression<bool, _Tp>
where(_ExactBool __k, const _Tp& __value)
{
return {__k, __value};
}
template <typename _Tp, typename _Ap>
void
where(bool __k, simd<_Tp, _Ap>& __value)
= delete;
template <typename _Tp, typename _Ap>
void
where(bool __k, const simd<_Tp, _Ap>& __value)
= delete;
namespace __proposed {
template <size_t _Np> class where_range
{
const std::bitset<_Np> __bits;
public:
where_range(std::bitset<_Np> __b) : __bits(__b) {}
class iterator
{
size_t __mask;
size_t __bit;
_GLIBCXX_SIMD_INTRINSIC void __next_bit()
{
__bit = __builtin_ctzl(__mask);
}
_GLIBCXX_SIMD_INTRINSIC void __reset_lsb()
{
__mask &= (__mask - 1);
}
public:
iterator(decltype(__mask) __m) : __mask(__m) { __next_bit(); }
iterator(const iterator&) = default;
iterator(iterator&&) = default;
_GLIBCXX_SIMD_ALWAYS_INLINE size_t operator->() const { return __bit; }
_GLIBCXX_SIMD_ALWAYS_INLINE size_t operator*() const { return __bit; }
_GLIBCXX_SIMD_ALWAYS_INLINE iterator& operator++()
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
_GLIBCXX_SIMD_ALWAYS_INLINE bool operator==(const iterator& __rhs) const
{
return __mask == __rhs.__mask;
}
_GLIBCXX_SIMD_ALWAYS_INLINE bool operator!=(const iterator& __rhs) const
{
return __mask != __rhs.__mask;
}
};
iterator begin() const { return __bits.to_ullong(); }
iterator end() const { return 0; }
};
template <typename _Tp, typename _Ap>
where_range<simd_size_v<_Tp, _Ap>>
where(const simd_mask<_Tp, _Ap>& __k)
{
return __k.__to_bitset();
}
}
template <typename _Tp, typename _Abi, typename _BinaryOperation = std::plus<>>
_GLIBCXX_SIMD_INTRINSIC _GLIBCXX_SIMD_CONSTEXPR _Tp
reduce(const simd<_Tp, _Abi>& __v,
_BinaryOperation __binary_op = _BinaryOperation())
{
return _Abi::_SimdImpl::_S_reduce(__v, __binary_op);
}
template <typename _M, typename _V, typename _BinaryOperation = std::plus<>>
_GLIBCXX_SIMD_INTRINSIC typename _V::value_type
reduce(const const_where_expression<_M, _V>& __x,
typename _V::value_type __identity_element, _BinaryOperation __binary_op)
{
if (__builtin_expect(none_of(__get_mask(__x)), false))
return __identity_element;
_V __tmp = __identity_element;
_V::_Impl::_S_masked_assign(__data(__get_mask(__x)), __data(__tmp),
__data(__get_lvalue(__x)));
return reduce(__tmp, __binary_op);
}
template <typename _M, typename _V>
_GLIBCXX_SIMD_INTRINSIC typename _V::value_type
reduce(const const_where_expression<_M, _V>& __x, std::plus<> __binary_op = {})
{
return reduce(__x, 0, __binary_op);
}
template <typename _M, typename _V>
_GLIBCXX_SIMD_INTRINSIC typename _V::value_type
reduce(const const_where_expression<_M, _V>& __x, std::multiplies<> __binary_op)
{
return reduce(__x, 1, __binary_op);
}
template <typename _M, typename _V>
_GLIBCXX_SIMD_INTRINSIC typename _V::value_type
reduce(const const_where_expression<_M, _V>& __x, std::bit_and<> __binary_op)
{
return reduce(__x, ~typename _V::value_type(), __binary_op);
}
template <typename _M, typename _V>
_GLIBCXX_SIMD_INTRINSIC typename _V::value_type
reduce(const const_where_expression<_M, _V>& __x, std::bit_or<> __binary_op)
{
return reduce(__x, 0, __binary_op);
}
template <typename _M, typename _V>
_GLIBCXX_SIMD_INTRINSIC typename _V::value_type
reduce(const const_where_expression<_M, _V>& __x, std::bit_xor<> __binary_op)
{
return reduce(__x, 0, __binary_op);
}
template <typename _Tp, typename _Ap>
_GLIBCXX_SIMD_INTRINSIC _GLIBCXX_SIMD_CONSTEXPR simd<_Tp, _Ap>
min(const simd<_Tp, _Ap>& __a, const simd<_Tp, _Ap>& __b)
{
return {__private_init, _Ap::_SimdImpl::_S_min(__data(__a), __data(__b))};
}
template <typename _Tp, typename _Ap>
_GLIBCXX_SIMD_INTRINSIC _GLIBCXX_SIMD_CONSTEXPR simd<_Tp, _Ap>
max(const simd<_Tp, _Ap>& __a, const simd<_Tp, _Ap>& __b)
{
return {__private_init, _Ap::_SimdImpl::_S_max(__data(__a), __data(__b))};
}
template <typename _Tp, typename _Ap>
_GLIBCXX_SIMD_INTRINSIC
_GLIBCXX_SIMD_CONSTEXPR std::pair<simd<_Tp, _Ap>, simd<_Tp, _Ap>>
minmax(const simd<_Tp, _Ap>& __a, const simd<_Tp, _Ap>& __b)
{
const auto pair_of_members
= _Ap::_SimdImpl::_S_minmax(__data(__a), __data(__b));
return {simd<_Tp, _Ap>(__private_init, pair_of_members.first),
simd<_Tp, _Ap>(__private_init, pair_of_members.second)};
}
template <typename _Tp, typename _Ap>
_GLIBCXX_SIMD_INTRINSIC _GLIBCXX_SIMD_CONSTEXPR simd<_Tp, _Ap>
clamp(const simd<_Tp, _Ap>& __v, const simd<_Tp, _Ap>& __lo,
const simd<_Tp, _Ap>& __hi)
{
using _Impl = typename _Ap::_SimdImpl;
return {__private_init,
_Impl::_S_min(__data(__hi),
_Impl::_S_max(__data(__lo), __data(__v)))};
}
namespace _P0918 {
template <int _Stride, int _Offset = 0> struct strided
{
static constexpr int _S_stride = _Stride;
static constexpr int _S_offset = _Offset;
template <typename _Tp, typename _Ap>
using __shuffle_return_type = simd<
_Tp, simd_abi::deduce_t<
_Tp, __div_roundup(simd_size_v<_Tp, _Ap> - _Offset, _Stride), _Ap>>;
template <typename _Tp> static constexpr auto _S_src_index(_Tp __dst_index)
{
return _Offset + __dst_index * _Stride;
}
};
template <typename _P, typename _Tp, typename _Ap,
typename _R = typename _P::template __shuffle_return_type<_Tp, _Ap>,
typename
= decltype(_P::_S_src_index(std::experimental::_SizeConstant<0>()))>
_GLIBCXX_SIMD_INTRINSIC _R
shuffle(const simd<_Tp, _Ap>& __x)
{
return _R([&__x](auto __i) constexpr { return __x[_P::_S_src_index(__i)]; });
}
}
namespace __proposed {
using namespace _P0918;
}
template <size_t... _Sizes, typename _Tp, typename _Ap,
typename = enable_if_t<((_Sizes + ...) == simd<_Tp, _Ap>::size())>>
inline std::tuple<simd<_Tp, simd_abi::deduce_t<_Tp, _Sizes>>...>
split(const simd<_Tp, _Ap>&);
template <int _Index, int _Total, int _Combine = 1, typename _Tp, size_t _Np>
_GLIBCXX_SIMD_INTRINSIC
_GLIBCXX_CONST _SimdWrapper<_Tp, _Np / _Total * _Combine>
__extract_part(const _SimdWrapper<_Tp, _Np> __x);
template <int Index, int Parts, int _Combine = 1, typename _Tp, typename _A0,
typename... _As>
_GLIBCXX_SIMD_INTRINSIC auto
__extract_part(const _SimdTuple<_Tp, _A0, _As...>& __x);
template <size_t _V0, size_t... _Values> struct _SizeList
{
template <size_t _I> static constexpr size_t _S_at(_SizeConstant<_I> = {})
{
if constexpr (_I == 0)
{
return _V0;
}
else
{
return _SizeList<_Values...>::template _S_at<_I - 1>();
}
}
template <size_t _I> static constexpr auto _S_before(_SizeConstant<_I> = {})
{
if constexpr (_I == 0)
{
return _SizeConstant<0>();
}
else
{
return _SizeConstant<
_V0 + _SizeList<_Values...>::template _S_before<_I - 1>()>();
}
}
template <size_t _Np>
static constexpr auto _S_pop_front(_SizeConstant<_Np> = {})
{
if constexpr (_Np == 0)
{
return _SizeList();
}
else
{
return _SizeList<_Values...>::template _S_pop_front<_Np - 1>();
}
}
};
template <typename _Tp, size_t _Np>
_GLIBCXX_SIMD_INTRINSIC _SimdWrapper<_Tp, _Np / 2>
__extract_center(_SimdWrapper<_Tp, _Np> __x)
{
static_assert(_Np >= 4);
static_assert(_Np % 4 == 0);
#if _GLIBCXX_SIMD_X86INTRIN
if constexpr (__have_avx512f && sizeof(_Tp) * _Np == 64)
{
const auto __intrin = __to_intrin(__x);
if constexpr (std::is_integral_v<_Tp>)
return __vector_bitcast<_Tp>(_mm512_castsi512_si256(
_mm512_shuffle_i32x4(__intrin, __intrin,
1 + 2 * 0x4 + 2 * 0x10 + 3 * 0x40)));
else if constexpr (sizeof(_Tp) == 4)
return __vector_bitcast<_Tp>(_mm512_castps512_ps256(
_mm512_shuffle_f32x4(__intrin, __intrin,
1 + 2 * 0x4 + 2 * 0x10 + 3 * 0x40)));
else if constexpr (sizeof(_Tp) == 8)
return __vector_bitcast<_Tp>(_mm512_castpd512_pd256(
_mm512_shuffle_f64x2(__intrin, __intrin,
1 + 2 * 0x4 + 2 * 0x10 + 3 * 0x40)));
else
__assert_unreachable<_Tp>();
}
else if constexpr (sizeof(_Tp) * _Np == 32 && std::is_floating_point_v<_Tp>)
return __vector_bitcast<_Tp>(
_mm_shuffle_pd(__lo128(__vector_bitcast<double>(__x)),
__hi128(__vector_bitcast<double>(__x)), 1));
else if constexpr (sizeof(__x) == 32 && sizeof(_Tp) * _Np <= 32)
return __vector_bitcast<_Tp>(
_mm_alignr_epi8(__hi128(__vector_bitcast<_LLong>(__x)),
__lo128(__vector_bitcast<_LLong>(__x)),
sizeof(_Tp) * _Np / 4));
else
#endif
{
__vector_type_t<_Tp, _Np / 2> __r;
__builtin_memcpy(&__r,
reinterpret_cast<const char*>(&__x)
+ sizeof(_Tp) * _Np / 4,
sizeof(_Tp) * _Np / 2);
return __r;
}
}
template <typename _Tp, typename _A0, typename... _As>
_GLIBCXX_SIMD_INTRINSIC
_SimdWrapper<_Tp, _SimdTuple<_Tp, _A0, _As...>::_S_size() / 2>
__extract_center(const _SimdTuple<_Tp, _A0, _As...>& __x)
{
if constexpr (sizeof...(_As) == 0)
return __extract_center(__x.first);
else
return __extract_part<1, 4, 2>(__x);
}
template <size_t... _Sizes, typename _Tp, typename... _As>
auto
__split_wrapper(_SizeList<_Sizes...>, const _SimdTuple<_Tp, _As...>& __x)
{
return std::experimental::split<_Sizes...>(
fixed_size_simd<_Tp, _SimdTuple<_Tp, _As...>::_S_size()>(__private_init,
__x));
}
template <typename _V, typename _Ap,
size_t Parts = simd_size_v<typename _V::value_type, _Ap> / _V::size()>
inline enable_if_t<
(is_simd<_V>::value
&& simd_size_v<typename _V::value_type, _Ap> == Parts * _V::size()),
std::array<_V, Parts>>
split(const simd<typename _V::value_type, _Ap>& __x)
{
using _Tp = typename _V::value_type;
if constexpr (Parts == 1)
{
return {simd_cast<_V>(__x)};
}
else if (__x._M_is_constprop())
{
return __generate_from_n_evaluations<Parts, std::array<_V, Parts>>([&](
auto __i) constexpr {
return _V([&](auto __j) constexpr {
return __x[__i * _V::size() + __j];
});
});
}
else if constexpr (
__is_fixed_size_abi_v<_Ap>
&& (std::is_same_v<typename _V::abi_type, simd_abi::scalar>
|| (__is_fixed_size_abi_v<typename _V::abi_type>
&& sizeof(_V) == sizeof(_Tp) * _V::size()
)))
{
#ifdef _GLIBCXX_SIMD_USE_ALIASING_LOADS
const __may_alias<_Tp>* const __element_ptr
= reinterpret_cast<const __may_alias<_Tp>*>(&__data(__x));
return __generate_from_n_evaluations<Parts, std::array<_V, Parts>>([&](
auto __i) constexpr {
return _V(__element_ptr + __i * _V::size(), vector_aligned);
});
#else
const auto& __xx = __data(__x);
return __generate_from_n_evaluations<Parts, std::array<_V, Parts>>([&](
auto __i) constexpr {
[[maybe_unused]] constexpr size_t __offset
= decltype(__i)::value * _V::size();
return _V([&](auto __j) constexpr {
constexpr _SizeConstant<__j + __offset> __k;
return __xx[__k];
});
});
#endif
}
else if constexpr (std::is_same_v<typename _V::abi_type, simd_abi::scalar>)
{
return __generate_from_n_evaluations<Parts, std::array<_V, Parts>>([&](
auto __i) constexpr { return __x[__i]; });
}
else
{
return __generate_from_n_evaluations<Parts, std::array<_V, Parts>>([&](
auto __i) constexpr {
if constexpr (__is_fixed_size_abi_v<typename _V::abi_type>)
{
return _V([&](auto __j) constexpr {
return __x[__i * _V::size() + __j];
});
}
else
{
return _V(__private_init,
__extract_part<decltype(__i)::value, Parts>(__data(__x)));
}
});
}
}
template <typename _V, typename _Ap,
size_t _Parts
= simd_size_v<typename _V::simd_type::value_type, _Ap> / _V::size()>
enable_if_t<
(is_simd_mask_v<
_V> && simd_size_v<typename _V::simd_type::value_type, _Ap> == _Parts * _V::size()),
std::array<_V, _Parts>>
split(const simd_mask<typename _V::simd_type::value_type, _Ap>& __x)
{
if constexpr (std::is_same_v<_Ap, typename _V::abi_type>)
{
return {__x};
}
else if constexpr (_Parts == 1)
{
return {__proposed::static_simd_cast<_V>(__x)};
}
else if constexpr (_Parts == 2 && __is_sse_abi<typename _V::abi_type>()
&& __is_avx_abi<_Ap>())
{
return {_V(__private_init, __lo128(__data(__x))),
_V(__private_init, __hi128(__data(__x)))};
}
else if constexpr (_V::size() <= __CHAR_BIT__ * sizeof(_ULLong))
{
const std::bitset __bits = __x.__to_bitset();
return __generate_from_n_evaluations<_Parts, std::array<_V, _Parts>>([&](
auto __i) constexpr {
constexpr size_t __offset = __i * _V::size();
return _V(__bitset_init, (__bits >> __offset).to_ullong());
});
}
else
{
return __generate_from_n_evaluations<_Parts, std::array<_V, _Parts>>([&](
auto __i) constexpr {
constexpr size_t __offset = __i * _V::size();
return _V(
__private_init, [&](auto __j) constexpr {
return __x[__j + __offset];
});
});
}
}
template <size_t... _Sizes, typename _Tp, typename _Ap, typename>
_GLIBCXX_SIMD_ALWAYS_INLINE
std::tuple<simd<_Tp, simd_abi::deduce_t<_Tp, _Sizes>>...>
split(const simd<_Tp, _Ap>& __x)
{
using _SL = _SizeList<_Sizes...>;
using _Tuple = std::tuple<__deduced_simd<_Tp, _Sizes>...>;
constexpr size_t _Np = simd_size_v<_Tp, _Ap>;
constexpr size_t _N0 = _SL::template _S_at<0>();
using _V = __deduced_simd<_Tp, _N0>;
if (__x._M_is_constprop())
return __generate_from_n_evaluations<sizeof...(_Sizes), _Tuple>([&](
auto __i) constexpr {
using _Vi = __deduced_simd<_Tp, _SL::_S_at(__i)>;
constexpr size_t __offset = _SL::_S_before(__i);
return _Vi([&](auto __j) constexpr { return __x[__offset + __j]; });
});
else if constexpr (_Np == _N0)
{
static_assert(sizeof...(_Sizes) == 1);
return {simd_cast<_V>(__x)};
}
else if constexpr
(__is_fixed_size_abi_v<
_Ap> && __fixed_size_storage_t<_Tp, _Np>::_S_first_size == _N0)
{
static_assert(!__is_fixed_size_abi_v<typename _V::abi_type>,
"How can <_Tp, _Np> be __a single _SimdTuple entry but __a "
"fixed_size_simd "
"when deduced?");
return std::tuple_cat(
std::make_tuple(_V(__private_init, __data(__x).first)),
__split_wrapper(_SL::template _S_pop_front<1>(), __data(__x).second));
}
else if constexpr ((!std::is_same_v<simd_abi::scalar,
simd_abi::deduce_t<_Tp, _Sizes>> && ...)
&& (!__is_fixed_size_abi_v<
simd_abi::deduce_t<_Tp, _Sizes>> && ...))
{
if constexpr (((_Sizes * 2 == _Np) && ...))
return {{__private_init, __extract_part<0, 2>(__data(__x))},
{__private_init, __extract_part<1, 2>(__data(__x))}};
else if constexpr (std::is_same_v<_SizeList<_Sizes...>,
_SizeList<_Np / 3, _Np / 3, _Np / 3>>)
return {{__private_init, __extract_part<0, 3>(__data(__x))},
{__private_init, __extract_part<1, 3>(__data(__x))},
{__private_init, __extract_part<2, 3>(__data(__x))}};
else if constexpr (std::is_same_v<_SizeList<_Sizes...>,
_SizeList<2 * _Np / 3, _Np / 3>>)
return {{__private_init, __extract_part<0, 3, 2>(__data(__x))},
{__private_init, __extract_part<2, 3>(__data(__x))}};
else if constexpr (std::is_same_v<_SizeList<_Sizes...>,
_SizeList<_Np / 3, 2 * _Np / 3>>)
return {{__private_init, __extract_part<0, 3>(__data(__x))},
{__private_init, __extract_part<1, 3, 2>(__data(__x))}};
else if constexpr (std::is_same_v<_SizeList<_Sizes...>,
_SizeList<_Np / 2, _Np / 4, _Np / 4>>)
return {{__private_init, __extract_part<0, 2>(__data(__x))},
{__private_init, __extract_part<2, 4>(__data(__x))},
{__private_init, __extract_part<3, 4>(__data(__x))}};
else if constexpr (std::is_same_v<_SizeList<_Sizes...>,
_SizeList<_Np / 4, _Np / 4, _Np / 2>>)
return {{__private_init, __extract_part<0, 4>(__data(__x))},
{__private_init, __extract_part<1, 4>(__data(__x))},
{__private_init, __extract_part<1, 2>(__data(__x))}};
else if constexpr (std::is_same_v<_SizeList<_Sizes...>,
_SizeList<_Np / 4, _Np / 2, _Np / 4>>)
return {{__private_init, __extract_part<0, 4>(__data(__x))},
{__private_init, __extract_center(__data(__x))},
{__private_init, __extract_part<3, 4>(__data(__x))}};
else if constexpr (((_Sizes * 4 == _Np) && ...))
return {{__private_init, __extract_part<0, 4>(__data(__x))},
{__private_init, __extract_part<1, 4>(__data(__x))},
{__private_init, __extract_part<2, 4>(__data(__x))},
{__private_init, __extract_part<3, 4>(__data(__x))}};
}
#ifdef _GLIBCXX_SIMD_USE_ALIASING_LOADS
const __may_alias<_Tp>* const __element_ptr
= reinterpret_cast<const __may_alias<_Tp>*>(&__x);
return __generate_from_n_evaluations<sizeof...(_Sizes), _Tuple>([&](
auto __i) constexpr {
using _Vi = __deduced_simd<_Tp, _SL::_S_at(__i)>;
constexpr size_t __offset = _SL::_S_before(__i);
constexpr size_t __base_align = alignof(simd<_Tp, _Ap>);
constexpr size_t __a
= __base_align - ((__offset * sizeof(_Tp)) % __base_align);
constexpr size_t __b = ((__a - 1) & __a) ^ __a;
constexpr size_t __alignment = __b == 0 ? __a : __b;
return _Vi(__element_ptr + __offset, overaligned<__alignment>);
});
#else
return __generate_from_n_evaluations<sizeof...(_Sizes), _Tuple>([&](
auto __i) constexpr {
using _Vi = __deduced_simd<_Tp, _SL::_S_at(__i)>;
const auto& __xx = __data(__x);
using _Offset = decltype(_SL::_S_before(__i));
return _Vi([&](auto __j) constexpr {
constexpr _SizeConstant<_Offset::value + __j> __k;
return __xx[__k];
});
});
#endif
}
template <size_t _I, typename _Tp, typename _Ap, typename... _As>
_GLIBCXX_SIMD_INTRINSIC constexpr _Tp
__subscript_in_pack(const simd<_Tp, _Ap>& __x, const simd<_Tp, _As>&... __xs)
{
if constexpr (_I < simd_size_v<_Tp, _Ap>)
return __x[_I];
else
return __subscript_in_pack<_I - simd_size_v<_Tp, _Ap>>(__xs...);
}
template <typename _Tp, typename _A0, typename... _As>
_GLIBCXX_SIMD_INTRINSIC void
__store_pack_of_simd(char* __mem, const simd<_Tp, _A0>& __x0,
const simd<_Tp, _As>&... __xs)
{
constexpr size_t __n_bytes = sizeof(_Tp) * simd_size_v<_Tp, _A0>;
__builtin_memcpy(__mem, &__data(__x0), __n_bytes);
if constexpr (sizeof...(__xs) > 0)
__store_pack_of_simd(__mem + __n_bytes, __xs...);
}
template <typename _Tp, typename... _As>
inline _GLIBCXX_SIMD_CONSTEXPR
simd<_Tp, simd_abi::deduce_t<_Tp, (simd_size_v<_Tp, _As> + ...)>>
concat(const simd<_Tp, _As>&... __xs)
{
using _Rp = __deduced_simd<_Tp, (simd_size_v<_Tp, _As> + ...)>;
if constexpr(sizeof...(__xs) == 1)
return simd_cast<_Rp>(__xs...);
else if ((... && __xs._M_is_constprop()))
return simd<_Tp,
simd_abi::deduce_t<_Tp, (simd_size_v<_Tp, _As> + ...)>>([&](
auto __i) constexpr { return __subscript_in_pack<__i>(__xs...); });
else
{
_Rp __r{};
__store_pack_of_simd(reinterpret_cast<char*>(&__data(__r)), __xs...);
return __r;
}
}
template <typename _Tp, typename _Abi, size_t _Np>
_GLIBCXX_SIMD_ALWAYS_INLINE _GLIBCXX_SIMD_CONSTEXPR
__deduced_simd<_Tp, simd_size_v<_Tp, _Abi> * _Np>
concat(const std::array<simd<_Tp, _Abi>, _Np>& __x)
{
return __call_with_subscripts<_Np>(__x, [](const auto&... __xs) {
return concat(__xs...);
});
}
template <typename _Up, typename _Accessor = _Up,
typename _ValueType = typename _Up::value_type>
class _SmartReference
{
friend _Accessor;
int _M_index;
_Up& _M_obj;
_GLIBCXX_SIMD_INTRINSIC constexpr _ValueType _M_read() const noexcept
{
if constexpr (std::is_arithmetic_v<_Up>)
return _M_obj;
else
return _M_obj[_M_index];
}
template <typename _Tp>
_GLIBCXX_SIMD_INTRINSIC constexpr void _M_write(_Tp&& __x) const
{
_Accessor::_S_set(_M_obj, _M_index, static_cast<_Tp&&>(__x));
}
public:
_GLIBCXX_SIMD_INTRINSIC constexpr _SmartReference(_Up& __o, int __i) noexcept
: _M_index(__i), _M_obj(__o)
{}
using value_type = _ValueType;
_GLIBCXX_SIMD_INTRINSIC _SmartReference(const _SmartReference&) = delete;
_GLIBCXX_SIMD_INTRINSIC constexpr operator value_type() const noexcept
{
return _M_read();
}
template <typename _Tp,
typename = _ValuePreservingOrInt<__remove_cvref_t<_Tp>, value_type>>
_GLIBCXX_SIMD_INTRINSIC constexpr _SmartReference operator=(_Tp&& __x) &&
{
_M_write(static_cast<_Tp&&>(__x));
return {_M_obj, _M_index};
}
#define _GLIBCXX_SIMD_OP_(__op) \
template <typename _Tp, \
typename _TT \
= decltype(std::declval<value_type>() __op std::declval<_Tp>()), \
typename = _ValuePreservingOrInt<__remove_cvref_t<_Tp>, _TT>, \
typename = _ValuePreservingOrInt<_TT, value_type>> \
_GLIBCXX_SIMD_INTRINSIC constexpr _SmartReference operator __op##=( \
_Tp&& __x)&& \
{ \
const value_type& __lhs = _M_read(); \
_M_write(__lhs __op __x); \
return {_M_obj, _M_index}; \
}
_GLIBCXX_SIMD_ALL_ARITHMETICS(_GLIBCXX_SIMD_OP_);
_GLIBCXX_SIMD_ALL_SHIFTS(_GLIBCXX_SIMD_OP_);
_GLIBCXX_SIMD_ALL_BINARY(_GLIBCXX_SIMD_OP_);
#undef _GLIBCXX_SIMD_OP_
template <typename _Tp = void,
typename = decltype(
++std::declval<std::conditional_t<true, value_type, _Tp>&>())>
_GLIBCXX_SIMD_INTRINSIC constexpr _SmartReference operator++() &&
{
value_type __x = _M_read();
_M_write(++__x);
return {_M_obj, _M_index};
}
template <typename _Tp = void,
typename = decltype(
std::declval<std::conditional_t<true, value_type, _Tp>&>()++)>
_GLIBCXX_SIMD_INTRINSIC constexpr value_type operator++(int) &&
{
const value_type __r = _M_read();
value_type __x = __r;
_M_write(++__x);
return __r;
}
template <typename _Tp = void,
typename = decltype(
--std::declval<std::conditional_t<true, value_type, _Tp>&>())>
_GLIBCXX_SIMD_INTRINSIC constexpr _SmartReference operator--() &&
{
value_type __x = _M_read();
_M_write(--__x);
return {_M_obj, _M_index};
}
template <typename _Tp = void,
typename = decltype(
std::declval<std::conditional_t<true, value_type, _Tp>&>()--)>
_GLIBCXX_SIMD_INTRINSIC constexpr value_type operator--(int) &&
{
const value_type __r = _M_read();
value_type __x = __r;
_M_write(--__x);
return __r;
}
_GLIBCXX_SIMD_INTRINSIC friend void
swap(_SmartReference&& __a, _SmartReference&& __b) noexcept(
conjunction<
std::is_nothrow_constructible<value_type, _SmartReference&&>,
std::is_nothrow_assignable<_SmartReference&&, value_type&&>>::value)
{
value_type __tmp = static_cast<_SmartReference&&>(__a);
static_cast<_SmartReference&&>(__a) = static_cast<value_type>(__b);
static_cast<_SmartReference&&>(__b) = std::move(__tmp);
}
_GLIBCXX_SIMD_INTRINSIC friend void
swap(value_type& __a, _SmartReference&& __b) noexcept(
conjunction<
std::is_nothrow_constructible<value_type, value_type&&>,
std::is_nothrow_assignable<value_type&, value_type&&>,
std::is_nothrow_assignable<_SmartReference&&, value_type&&>>::value)
{
value_type __tmp(std::move(__a));
__a = static_cast<value_type>(__b);
static_cast<_SmartReference&&>(__b) = std::move(__tmp);
}
_GLIBCXX_SIMD_INTRINSIC friend void
swap(_SmartReference&& __a, value_type& __b) noexcept(
conjunction<
std::is_nothrow_constructible<value_type, _SmartReference&&>,
std::is_nothrow_assignable<value_type&, value_type&&>,
std::is_nothrow_assignable<_SmartReference&&, value_type&&>>::value)
{
value_type __tmp(__a);
static_cast<_SmartReference&&>(__a) = std::move(__b);
__b = std::move(__tmp);
}
};
template <int _Bytes> struct __scalar_abi_wrapper
{
template <typename _Tp> static constexpr size_t _S_full_size = 1;
template <typename _Tp> static constexpr size_t _S_size = 1;
template <typename _Tp> static constexpr size_t _S_is_partial = false;
template <typename _Tp, typename _Abi = simd_abi::scalar>
static constexpr bool _S_is_valid_v
= _Abi::template _IsValid<_Tp>::value && sizeof(_Tp) == _Bytes;
};
template <typename _Tp> struct __decay_abi
{
using type = _Tp;
};
template <int _Bytes> struct __decay_abi<__scalar_abi_wrapper<_Bytes>>
{
using type = simd_abi::scalar;
};
template <template <int> class _Abi, int _Bytes, typename _Tp>
struct __find_next_valid_abi
{
static constexpr auto _S_choose()
{
constexpr int _NextBytes = __next_power_of_2(_Bytes) / 2;
using _NextAbi = _Abi<_NextBytes>;
if constexpr (_NextBytes < sizeof(_Tp) * 2)
return _Abi<_Bytes>();
else if constexpr (_NextAbi::template _S_is_partial<_Tp> == false
&& _NextAbi::template _S_is_valid_v<_Tp>)
return _NextAbi();
else
return __find_next_valid_abi<_Abi, _NextBytes, _Tp>::_S_choose();
}
using type = decltype(_S_choose());
};
template <int _Bytes, typename _Tp>
struct __find_next_valid_abi<__scalar_abi_wrapper, _Bytes, _Tp>
{
using type = simd_abi::scalar;
};
template <template <int> class...> struct _AbiList
{
template <typename, int> static constexpr bool _S_has_valid_abi = false;
template <typename, int> using _FirstValidAbi = void;
template <typename, int> using _BestAbi = void;
};
template <template <int> class _A0, template <int> class... _Rest>
struct _AbiList<_A0, _Rest...>
{
template <typename _Tp, int _Np>
static constexpr bool _S_has_valid_abi
= _A0<sizeof(_Tp) * _Np>::template _S_is_valid_v<
_Tp> || _AbiList<_Rest...>::template _S_has_valid_abi<_Tp, _Np>;
template <typename _Tp, int _Np>
using _FirstValidAbi = std::conditional_t<
_A0<sizeof(_Tp) * _Np>::template _S_is_valid_v<_Tp>,
typename __decay_abi<_A0<sizeof(_Tp) * _Np>>::type,
typename _AbiList<_Rest...>::template _FirstValidAbi<_Tp, _Np>>;
template <typename _Tp, int _Np> static constexpr auto _S_determine_best_abi()
{
static_assert(_Np >= 1);
constexpr int _Bytes = sizeof(_Tp) * _Np;
if constexpr (_Np == 1)
return __make_dependent_t<_Tp, simd_abi::scalar>{};
else
{
constexpr int __fullsize = _A0<_Bytes>::template _S_full_size<_Tp>;
if constexpr (_A0<_Bytes>::template _S_is_valid_v<
_Tp> && __fullsize / 2 < _Np)
return typename __decay_abi<_A0<_Bytes>>::type{};
else
{
using _B = typename __find_next_valid_abi<_A0, _Bytes, _Tp>::type;
if constexpr (_B::template _S_is_valid_v<
_Tp> && _B::template _S_size<_Tp> <= _Np)
return _B{};
else
return typename _AbiList<_Rest...>::template _BestAbi<_Tp, _Np>{};
}
}}
template <typename _Tp, int _Np>
using _BestAbi = decltype(_S_determine_best_abi<_Tp, _Np>());
};
using _AllNativeAbis = _AbiList<simd_abi::_VecBltnBtmsk, simd_abi::_VecBuiltin,
__scalar_abi_wrapper>;
template <typename _Tp, typename _Abi>
struct _SimdTraits<_Tp, _Abi,
std::void_t<typename _Abi::template _IsValid<_Tp>>>
: _Abi::template __traits<_Tp>
{
};
template <typename _Tp, std::size_t _Np>
struct __deduce_impl<
_Tp, _Np, enable_if_t<_AllNativeAbis::template _S_has_valid_abi<_Tp, _Np>>>
{
using type = _AllNativeAbis::_FirstValidAbi<_Tp, _Np>;
};
template <typename _Tp, std::size_t _Np, typename = void>
struct __deduce_fixed_size_fallback
{
};
template <typename _Tp, std::size_t _Np>
struct __deduce_fixed_size_fallback<
_Tp, _Np, enable_if_t<simd_abi::fixed_size<_Np>::template _S_is_valid_v<_Tp>>>
{
using type = simd_abi::fixed_size<_Np>;
};
template <typename _Tp, std::size_t _Np, typename>
struct __deduce_impl : public __deduce_fixed_size_fallback<_Tp, _Np>
{
};
template <typename _Tp, typename _Abi>
class simd_mask : public _SimdTraits<_Tp, _Abi>::_MaskBase
{
using _Traits = _SimdTraits<_Tp, _Abi>;
using _MemberType = typename _Traits::_MaskMember;
using _Ip = __int_for_sizeof_t<_Tp>;
static constexpr _Ip* _S_type_tag = nullptr;
friend typename _Traits::_MaskBase;
friend class simd<_Tp, _Abi>;
friend typename _Traits::_SimdImpl;
public:
using _Impl = typename _Traits::_MaskImpl;
friend _Impl;
using value_type = bool;
using reference = _SmartReference<_MemberType, _Impl, value_type>;
using simd_type = simd<_Tp, _Abi>;
using abi_type = _Abi;
static constexpr size_t size() { return __size_or_zero_v<_Tp, _Abi>; }
simd_mask() = default;
simd_mask(const simd_mask&) = default;
simd_mask(simd_mask&&) = default;
simd_mask& operator=(const simd_mask&) = default;
simd_mask& operator=(simd_mask&&) = default;
_GLIBCXX_SIMD_ALWAYS_INLINE explicit simd_mask(
typename _Traits::_MaskCastType __init)
: _M_data{__init}
{}
_GLIBCXX_SIMD_ALWAYS_INLINE static simd_mask
__from_bitset(std::bitset<size()> bs)
{
return {__bitset_init, bs};
}
_GLIBCXX_SIMD_ALWAYS_INLINE std::bitset<size()> __to_bitset() const
{
return _Impl::_S_to_bits(_M_data)._M_to_bitset();
}
_GLIBCXX_SIMD_ALWAYS_INLINE explicit _GLIBCXX_SIMD_CONSTEXPR
simd_mask(value_type __x)
: _M_data(_Impl::template _S_broadcast<_Ip>(__x))
{}
#ifdef _GLIBCXX_SIMD_ENABLE_IMPLICIT_MASK_CAST
template <typename _Up, typename _A2,
typename = enable_if_t<simd_size_v<_Up, _A2> == size()>>
_GLIBCXX_SIMD_ALWAYS_INLINE explicit(
sizeof(_MemberType) != sizeof(typename _SimdTraits<_Up, _A2>::_MaskMember))
simd_mask(const simd_mask<_Up, _A2>& __x)
: simd_mask(__proposed::static_simd_cast<simd_mask>(__x))
{}
#else
template <typename _Up, typename = enable_if_t<conjunction<
is_same<abi_type, simd_abi::fixed_size<size()>>,
is_same<_Up, _Up>>::value>>
_GLIBCXX_SIMD_ALWAYS_INLINE
simd_mask(const simd_mask<_Up, simd_abi::fixed_size<size()>>& __x)
: _M_data(_Impl::_S_from_bitmask(__data(__x), _S_type_tag))
{}
#endif
template <typename _Flags>
_GLIBCXX_SIMD_ALWAYS_INLINE simd_mask(const value_type* __mem, _Flags)
: _M_data(
_Impl::template _S_load<_Ip>(_Flags::template _S_apply<simd_mask>(__mem)))
{}
template <typename _Flags>
_GLIBCXX_SIMD_ALWAYS_INLINE simd_mask(const value_type* __mem, simd_mask __k,
_Flags)
: _M_data{}
{
_M_data
= _Impl::_S_masked_load(_M_data, __k._M_data,
_Flags::template _S_apply<simd_mask>(__mem));
}
template <typename _Flags>
_GLIBCXX_SIMD_ALWAYS_INLINE void copy_from(const value_type* __mem, _Flags)
{
_M_data = _Impl::template _S_load<_Ip>(
_Flags::template _S_apply<simd_mask>(__mem));
}
template <typename _Flags>
_GLIBCXX_SIMD_ALWAYS_INLINE void copy_to(value_type* __mem, _Flags) const
{
_Impl::_S_store(_M_data, _Flags::template _S_apply<simd_mask>(__mem));
}
_GLIBCXX_SIMD_ALWAYS_INLINE reference operator[](size_t __i)
{
if (__i >= size())
__invoke_ub("Subscript %d is out of range [0, %d]", __i, size() - 1);
return {_M_data, int(__i)};
}
_GLIBCXX_SIMD_ALWAYS_INLINE value_type operator[](size_t __i) const
{
if (__i >= size())
__invoke_ub("Subscript %d is out of range [0, %d]", __i, size() - 1);
if constexpr (__is_scalar_abi<_Abi>())
return _M_data;
else
return static_cast<bool>(_M_data[__i]);
}
_GLIBCXX_SIMD_ALWAYS_INLINE simd_mask operator!() const
{
return {__private_init, _Impl::_S_bit_not(_M_data)};
}
#ifdef _GLIBCXX_SIMD_ENABLE_IMPLICIT_MASK_CAST
template <typename _Up, typename _A2,
typename
= enable_if_t<is_convertible_v<simd_mask<_Up, _A2>, simd_mask>>>
_GLIBCXX_SIMD_ALWAYS_INLINE friend simd_mask
operator&&(const simd_mask& __x, const simd_mask<_Up, _A2>& __y)
{
return {__private_init,
_Impl::_S_logical_and(__x._M_data, simd_mask(__y)._M_data)};
}
template <typename _Up, typename _A2,
typename
= enable_if_t<is_convertible_v<simd_mask<_Up, _A2>, simd_mask>>>
_GLIBCXX_SIMD_ALWAYS_INLINE friend simd_mask
operator||(const simd_mask& __x, const simd_mask<_Up, _A2>& __y)
{
return {__private_init,
_Impl::_S_logical_or(__x._M_data, simd_mask(__y)._M_data)};
}
#endif
_GLIBCXX_SIMD_ALWAYS_INLINE friend simd_mask operator&&(const simd_mask& __x,
const simd_mask& __y)
{
return {__private_init, _Impl::_S_logical_and(__x._M_data, __y._M_data)};
}
_GLIBCXX_SIMD_ALWAYS_INLINE friend simd_mask operator||(const simd_mask& __x,
const simd_mask& __y)
{
return {__private_init, _Impl::_S_logical_or(__x._M_data, __y._M_data)};
}
_GLIBCXX_SIMD_ALWAYS_INLINE friend simd_mask operator&(const simd_mask& __x,
const simd_mask& __y)
{
return {__private_init, _Impl::_S_bit_and(__x._M_data, __y._M_data)};
}
_GLIBCXX_SIMD_ALWAYS_INLINE friend simd_mask operator|(const simd_mask& __x,
const simd_mask& __y)
{
return {__private_init, _Impl::_S_bit_or(__x._M_data, __y._M_data)};
}
_GLIBCXX_SIMD_ALWAYS_INLINE friend simd_mask operator^(const simd_mask& __x,
const simd_mask& __y)
{
return {__private_init, _Impl::_S_bit_xor(__x._M_data, __y._M_data)};
}
_GLIBCXX_SIMD_ALWAYS_INLINE friend simd_mask& operator&=(simd_mask& __x,
const simd_mask& __y)
{
__x._M_data = _Impl::_S_bit_and(__x._M_data, __y._M_data);
return __x;
}
_GLIBCXX_SIMD_ALWAYS_INLINE friend simd_mask& operator|=(simd_mask& __x,
const simd_mask& __y)
{
__x._M_data = _Impl::_S_bit_or(__x._M_data, __y._M_data);
return __x;
}
_GLIBCXX_SIMD_ALWAYS_INLINE friend simd_mask& operator^=(simd_mask& __x,
const simd_mask& __y)
{
__x._M_data = _Impl::_S_bit_xor(__x._M_data, __y._M_data);
return __x;
}
_GLIBCXX_SIMD_ALWAYS_INLINE _GLIBCXX_SIMD_CONSTEXPR friend simd_mask
operator==(const simd_mask& __x, const simd_mask& __y)
{
return !operator!=(__x, __y);
}
_GLIBCXX_SIMD_ALWAYS_INLINE _GLIBCXX_SIMD_CONSTEXPR friend simd_mask
operator!=(const simd_mask& __x, const simd_mask& __y)
{
return {__private_init, _Impl::_S_bit_xor(__x._M_data, __y._M_data)};
}
_GLIBCXX_SIMD_INTRINSIC _GLIBCXX_SIMD_CONSTEXPR
simd_mask(_PrivateInit, typename _Traits::_MaskMember __init)
: _M_data(__init)
{}
template <typename _Fp,
typename = decltype(bool(std::declval<_Fp>()(size_t())))>
_GLIBCXX_SIMD_INTRINSIC constexpr simd_mask(_PrivateInit, _Fp&& __gen)
: _M_data()
{
__execute_n_times<size()>(
[&](auto __i) constexpr { _Impl::_S_set(_M_data, __i, __gen(__i)); });
}
_GLIBCXX_SIMD_INTRINSIC simd_mask(_BitsetInit, std::bitset<size()> __init)
: _M_data(
_Impl::_S_from_bitmask(_SanitizedBitMask<size()>(__init), _S_type_tag))
{}
struct _CvtProxy
{
template <typename _Up, typename _A2,
typename
= enable_if_t<simd_size_v<_Up, _A2> == simd_size_v<_Tp, _Abi>>>
operator simd_mask<_Up, _A2>() &&
{
using namespace std::experimental::__proposed;
return static_simd_cast<simd_mask<_Up, _A2>>(_M_data);
}
const simd_mask<_Tp, _Abi>& _M_data;
};
_GLIBCXX_SIMD_INTRINSIC _CvtProxy __cvt() const { return {*this}; }
#ifdef __GXX_CONDITIONAL_IS_OVERLOADABLE__
_GLIBCXX_SIMD_ALWAYS_INLINE _GLIBCXX_SIMD_CONSTEXPR friend simd_mask
operator?:(const simd_mask& __k, const simd_mask& __where_true,
const simd_mask& __where_false)
{
auto __ret = __where_false;
_Impl::_S_masked_assign(__k._M_data, __ret._M_data, __where_true._M_data);
return __ret;
}
template <typename _U1, typename _U2,
typename _Rp = simd<common_type_t<_U1, _U2>, _Abi>,
typename = enable_if_t<conjunction_v<
is_convertible<_U1, _Rp>, is_convertible<_U2, _Rp>,
is_convertible<simd_mask, typename _Rp::mask_type>>>>
_GLIBCXX_SIMD_ALWAYS_INLINE _GLIBCXX_SIMD_CONSTEXPR friend _Rp
operator?:(const simd_mask& __k, const _U1& __where_true,
const _U2& __where_false)
{
_Rp __ret = __where_false;
_Rp::_Impl::_S_masked_assign(__data(
static_cast<typename _Rp::mask_type>(__k)),
__data(__ret),
__data(static_cast<_Rp>(__where_true)));
return __ret;
}
#ifdef _GLIBCXX_SIMD_ENABLE_IMPLICIT_MASK_CAST
template <typename _Kp, typename _Ak, typename _Up, typename _Au,
typename = enable_if_t<
conjunction_v<is_convertible<simd_mask<_Kp, _Ak>, simd_mask>,
is_convertible<simd_mask<_Up, _Au>, simd_mask>>>>
_GLIBCXX_SIMD_ALWAYS_INLINE _GLIBCXX_SIMD_CONSTEXPR friend simd_mask
operator?:(const simd_mask<_Kp, _Ak>& __k, const simd_mask& __where_true,
const simd_mask<_Up, _Au>& __where_false)
{
simd_mask __ret = __where_false;
_Impl::_S_masked_assign(simd_mask(__k)._M_data, __ret._M_data,
__where_true._M_data);
return __ret;
}
#endif
#endif
_GLIBCXX_SIMD_INTRINSIC
constexpr bool _M_is_constprop() const
{
if constexpr (__is_scalar_abi<_Abi>())
return __builtin_constant_p(_M_data);
else
return _M_data._M_is_constprop();
}
private:
friend const auto& __data<_Tp, abi_type>(const simd_mask&);
friend auto& __data<_Tp, abi_type>(simd_mask&);
alignas(_Traits::_S_mask_align) _MemberType _M_data;
};
template <typename _Tp, typename _Ap>
_GLIBCXX_SIMD_INTRINSIC constexpr const auto&
__data(const simd_mask<_Tp, _Ap>& __x)
{
return __x._M_data;
}
template <typename _Tp, typename _Ap>
_GLIBCXX_SIMD_INTRINSIC constexpr auto&
__data(simd_mask<_Tp, _Ap>& __x)
{
return __x._M_data;
}
template <typename _Tp, typename _Abi>
_GLIBCXX_SIMD_ALWAYS_INLINE _GLIBCXX_SIMD_CONSTEXPR bool
all_of(const simd_mask<_Tp, _Abi>& __k) noexcept
{
if (__builtin_is_constant_evaluated() || __k._M_is_constprop())
{
for (size_t __i = 0; __i < simd_size_v<_Tp, _Abi>; ++__i)
if (!__k[__i])
return false;
return true;
}
else
return _Abi::_MaskImpl::_S_all_of(__k);
}
template <typename _Tp, typename _Abi>
_GLIBCXX_SIMD_ALWAYS_INLINE _GLIBCXX_SIMD_CONSTEXPR bool
any_of(const simd_mask<_Tp, _Abi>& __k) noexcept
{
if (__builtin_is_constant_evaluated() || __k._M_is_constprop())
{
for (size_t __i = 0; __i < simd_size_v<_Tp, _Abi>; ++__i)
if (__k[__i])
return true;
return false;
}
else
return _Abi::_MaskImpl::_S_any_of(__k);
}
template <typename _Tp, typename _Abi>
_GLIBCXX_SIMD_ALWAYS_INLINE _GLIBCXX_SIMD_CONSTEXPR bool
none_of(const simd_mask<_Tp, _Abi>& __k) noexcept
{
if (__builtin_is_constant_evaluated() || __k._M_is_constprop())
{
for (size_t __i = 0; __i < simd_size_v<_Tp, _Abi>; ++__i)
if (__k[__i])
return false;
return true;
}
else
return _Abi::_MaskImpl::_S_none_of(__k);
}
template <typename _Tp, typename _Abi>
_GLIBCXX_SIMD_ALWAYS_INLINE _GLIBCXX_SIMD_CONSTEXPR bool
some_of(const simd_mask<_Tp, _Abi>& __k) noexcept
{
if (__builtin_is_constant_evaluated() || __k._M_is_constprop())
{
for (size_t __i = 1; __i < simd_size_v<_Tp, _Abi>; ++__i)
if (__k[__i] != __k[__i - 1])
return true;
return false;
}
else
return _Abi::_MaskImpl::_S_some_of(__k);
}
template <typename _Tp, typename _Abi>
_GLIBCXX_SIMD_ALWAYS_INLINE _GLIBCXX_SIMD_CONSTEXPR int
popcount(const simd_mask<_Tp, _Abi>& __k) noexcept
{
if (__builtin_is_constant_evaluated() || __k._M_is_constprop())
{
const int __r = __call_with_subscripts<simd_size_v<_Tp, _Abi>>(
__k, [](auto... __elements) { return ((__elements != 0) + ...); });
if (__builtin_is_constant_evaluated() || __builtin_constant_p(__r))
return __r;
}
return _Abi::_MaskImpl::_S_popcount(__k);
}
template <typename _Tp, typename _Abi>
_GLIBCXX_SIMD_ALWAYS_INLINE _GLIBCXX_SIMD_CONSTEXPR int
find_first_set(const simd_mask<_Tp, _Abi>& __k)
{
if (__builtin_is_constant_evaluated() || __k._M_is_constprop())
{
constexpr size_t _Np = simd_size_v<_Tp, _Abi>;
const size_t _Idx = __call_with_n_evaluations<_Np>(
[](auto... __indexes) { return std::min({__indexes...}); },
[&](auto __i) { return __k[__i] ? +__i : _Np; });
if (_Idx >= _Np) __invoke_ub("find_first_set(empty mask) is UB");
if (__builtin_constant_p(_Idx))
return _Idx;
}
return _Abi::_MaskImpl::_S_find_first_set(__k);
}
template <typename _Tp, typename _Abi>
_GLIBCXX_SIMD_ALWAYS_INLINE _GLIBCXX_SIMD_CONSTEXPR int
find_last_set(const simd_mask<_Tp, _Abi>& __k)
{
if (__builtin_is_constant_evaluated() || __k._M_is_constprop())
{
constexpr size_t _Np = simd_size_v<_Tp, _Abi>;
const int _Idx = __call_with_n_evaluations<_Np>(
[](auto... __indexes) { return std::max({__indexes...}); },
[&](auto __i) { return __k[__i] ? int(__i) : -1; });
if (_Idx < 0) __invoke_ub("find_first_set(empty mask) is UB");
if (__builtin_constant_p(_Idx))
return _Idx;
}
return _Abi::_MaskImpl::_S_find_last_set(__k);
}
_GLIBCXX_SIMD_ALWAYS_INLINE _GLIBCXX_SIMD_CONSTEXPR bool
all_of(_ExactBool __x) noexcept
{
return __x;
}
_GLIBCXX_SIMD_ALWAYS_INLINE _GLIBCXX_SIMD_CONSTEXPR bool
any_of(_ExactBool __x) noexcept
{
return __x;
}
_GLIBCXX_SIMD_ALWAYS_INLINE _GLIBCXX_SIMD_CONSTEXPR bool
none_of(_ExactBool __x) noexcept
{
return !__x;
}
_GLIBCXX_SIMD_ALWAYS_INLINE _GLIBCXX_SIMD_CONSTEXPR bool
some_of(_ExactBool) noexcept
{
return false;
}
_GLIBCXX_SIMD_ALWAYS_INLINE _GLIBCXX_SIMD_CONSTEXPR int
popcount(_ExactBool __x) noexcept
{
return __x;
}
_GLIBCXX_SIMD_ALWAYS_INLINE _GLIBCXX_SIMD_CONSTEXPR int
find_first_set(_ExactBool)
{
return 0;
}
_GLIBCXX_SIMD_ALWAYS_INLINE _GLIBCXX_SIMD_CONSTEXPR int
find_last_set(_ExactBool)
{
return 0;
}
template <typename _V, typename _Impl, bool> class _SimdIntOperators
{
};
template <typename _V, typename _Impl> class _SimdIntOperators<_V, _Impl, true>
{
_GLIBCXX_SIMD_INTRINSIC const _V& __derived() const
{
return *static_cast<const _V*>(this);
}
template <typename _Tp>
_GLIBCXX_SIMD_INTRINSIC static _GLIBCXX_SIMD_CONSTEXPR _V
_S_make_derived(_Tp&& __d)
{
return {__private_init, static_cast<_Tp&&>(__d)};
}
public:
_GLIBCXX_SIMD_CONSTEXPR friend _V& operator%=(_V& __lhs, const _V& __x)
{
return __lhs = __lhs % __x;
}
_GLIBCXX_SIMD_CONSTEXPR friend _V& operator&=(_V& __lhs, const _V& __x)
{
return __lhs = __lhs & __x;
}
_GLIBCXX_SIMD_CONSTEXPR friend _V& operator|=(_V& __lhs, const _V& __x)
{
return __lhs = __lhs | __x;
}
_GLIBCXX_SIMD_CONSTEXPR friend _V& operator^=(_V& __lhs, const _V& __x)
{
return __lhs = __lhs ^ __x;
}
_GLIBCXX_SIMD_CONSTEXPR friend _V& operator<<=(_V& __lhs, const _V& __x)
{
return __lhs = __lhs << __x;
}
_GLIBCXX_SIMD_CONSTEXPR friend _V& operator>>=(_V& __lhs, const _V& __x)
{
return __lhs = __lhs >> __x;
}
_GLIBCXX_SIMD_CONSTEXPR friend _V& operator<<=(_V& __lhs, int __x)
{
return __lhs = __lhs << __x;
}
_GLIBCXX_SIMD_CONSTEXPR friend _V& operator>>=(_V& __lhs, int __x)
{
return __lhs = __lhs >> __x;
}
_GLIBCXX_SIMD_CONSTEXPR friend _V operator%(const _V& __x, const _V& __y)
{
return _SimdIntOperators::_S_make_derived(
_Impl::_S_modulus(__data(__x), __data(__y)));
}
_GLIBCXX_SIMD_CONSTEXPR friend _V operator&(const _V& __x, const _V& __y)
{
return _SimdIntOperators::_S_make_derived(
_Impl::_S_bit_and(__data(__x), __data(__y)));
}
_GLIBCXX_SIMD_CONSTEXPR friend _V operator|(const _V& __x, const _V& __y)
{
return _SimdIntOperators::_S_make_derived(
_Impl::_S_bit_or(__data(__x), __data(__y)));
}
_GLIBCXX_SIMD_CONSTEXPR friend _V operator^(const _V& __x, const _V& __y)
{
return _SimdIntOperators::_S_make_derived(
_Impl::_S_bit_xor(__data(__x), __data(__y)));
}
_GLIBCXX_SIMD_CONSTEXPR friend _V operator<<(const _V& __x, const _V& __y)
{
return _SimdIntOperators::_S_make_derived(
_Impl::_S_bit_shift_left(__data(__x), __data(__y)));
}
_GLIBCXX_SIMD_CONSTEXPR friend _V operator>>(const _V& __x, const _V& __y)
{
return _SimdIntOperators::_S_make_derived(
_Impl::_S_bit_shift_right(__data(__x), __data(__y)));
}
template <typename _VV = _V>
_GLIBCXX_SIMD_CONSTEXPR friend _V operator<<(const _V& __x, int __y)
{
using _Tp = typename _VV::value_type;
if (__y < 0)
__invoke_ub(
"The behavior is undefined if the right operand of a shift operation "
"is negative. [expr.shift]\nA shift by %d was requested",
__y);
if (size_t(__y) >= sizeof(std::declval<_Tp>() << __y) * __CHAR_BIT__)
__invoke_ub(
"The behavior is undefined if the right operand of a shift operation "
"is greater than or equal to the width of the promoted left operand. "
"[expr.shift]\nA shift by %d was requested",
__y);
return _SimdIntOperators::_S_make_derived(
_Impl::_S_bit_shift_left(__data(__x), __y));
}
template <typename _VV = _V>
_GLIBCXX_SIMD_CONSTEXPR friend _V operator>>(const _V& __x, int __y)
{
using _Tp = typename _VV::value_type;
if (__y < 0)
__invoke_ub(
"The behavior is undefined if the right operand of a shift operation "
"is negative. [expr.shift]\nA shift by %d was requested",
__y);
if (size_t(__y) >= sizeof(std::declval<_Tp>() << __y) * __CHAR_BIT__)
__invoke_ub(
"The behavior is undefined if the right operand of a shift operation "
"is greater than or equal to the width of the promoted left operand. "
"[expr.shift]\nA shift by %d was requested",
__y);
return _SimdIntOperators::_S_make_derived(
_Impl::_S_bit_shift_right(__data(__x), __y));
}
_GLIBCXX_SIMD_CONSTEXPR _V operator~() const
{
return {__private_init, _Impl::_S_complement(__derived()._M_data)};
}
};
template <typename _Tp, typename _Abi>
class simd : public _SimdIntOperators<
simd<_Tp, _Abi>, typename _SimdTraits<_Tp, _Abi>::_SimdImpl,
conjunction<std::is_integral<_Tp>,
typename _SimdTraits<_Tp, _Abi>::_IsValid>::value>,
public _SimdTraits<_Tp, _Abi>::_SimdBase
{
using _Traits = _SimdTraits<_Tp, _Abi>;
using _MemberType = typename _Traits::_SimdMember;
using _CastType = typename _Traits::_SimdCastType;
static constexpr _Tp* _S_type_tag = nullptr;
friend typename _Traits::_SimdBase;
public:
using _Impl = typename _Traits::_SimdImpl;
friend _Impl;
friend _SimdIntOperators<simd, _Impl, true>;
using value_type = _Tp;
using reference = _SmartReference<_MemberType, _Impl, value_type>;
using mask_type = simd_mask<_Tp, _Abi>;
using abi_type = _Abi;
static constexpr size_t size() { return __size_or_zero_v<_Tp, _Abi>; }
_GLIBCXX_SIMD_CONSTEXPR simd() = default;
_GLIBCXX_SIMD_CONSTEXPR simd(const simd&) = default;
_GLIBCXX_SIMD_CONSTEXPR simd(simd&&) noexcept = default;
_GLIBCXX_SIMD_CONSTEXPR simd& operator=(const simd&) = default;
_GLIBCXX_SIMD_CONSTEXPR simd& operator=(simd&&) noexcept = default;
template <typename _Up, typename = _ValuePreservingOrInt<_Up, value_type>>
_GLIBCXX_SIMD_ALWAYS_INLINE _GLIBCXX_SIMD_CONSTEXPR simd(_Up&& __x)
: _M_data(
_Impl::_S_broadcast(static_cast<value_type>(static_cast<_Up&&>(__x))))
{}
template <typename _Up>
_GLIBCXX_SIMD_ALWAYS_INLINE _GLIBCXX_SIMD_CONSTEXPR
simd(const simd<_Up, simd_abi::fixed_size<size()>>& __x,
enable_if_t<
conjunction<std::is_same<simd_abi::fixed_size<size()>, abi_type>,
std::negation<__is_narrowing_conversion<_Up, value_type>>,
__converts_to_higher_integer_rank<_Up, value_type>>::value,
void*> = nullptr)
: simd{static_cast<std::array<_Up, size()>>(__x).data(), vector_aligned}
{}
#ifdef _GLIBCXX_SIMD_ENABLE_STATIC_CAST
template <typename _Up, typename _A2,
typename = decltype(
static_simd_cast<simd>(std::declval<const simd<_Up, _A2>&>()))>
_GLIBCXX_SIMD_ALWAYS_INLINE explicit _GLIBCXX_SIMD_CONSTEXPR
simd(const simd<_Up, _A2>& __x)
: simd(static_simd_cast<simd>(__x))
{}
#endif
template <typename _Fp>
_GLIBCXX_SIMD_ALWAYS_INLINE explicit _GLIBCXX_SIMD_CONSTEXPR
simd(_Fp&& __gen, _ValuePreservingOrInt<decltype(std::declval<_Fp>()(
std::declval<_SizeConstant<0>&>())),
value_type>* = nullptr)
: _M_data(_Impl::_S_generator(static_cast<_Fp&&>(__gen), _S_type_tag))
{}
template <typename _Up, typename _Flags>
_GLIBCXX_SIMD_ALWAYS_INLINE simd(const _Up* __mem, _Flags)
: _M_data(
_Impl::_S_load(_Flags::template _S_apply<simd>(__mem), _S_type_tag))
{}
template <typename _Up, typename _Flags>
_GLIBCXX_SIMD_ALWAYS_INLINE void copy_from(const _Vectorizable<_Up>* __mem,
_Flags)
{
_M_data = static_cast<decltype(_M_data)>(
_Impl::_S_load(_Flags::template _S_apply<simd>(__mem), _S_type_tag));
}
template <typename _Up, typename _Flags>
_GLIBCXX_SIMD_ALWAYS_INLINE void copy_to(_Vectorizable<_Up>* __mem,
_Flags) const
{
_Impl::_S_store(_M_data, _Flags::template _S_apply<simd>(__mem),
_S_type_tag);
}
_GLIBCXX_SIMD_ALWAYS_INLINE _GLIBCXX_SIMD_CONSTEXPR reference
operator[](size_t __i)
{
return {_M_data, int(__i)};
}
_GLIBCXX_SIMD_ALWAYS_INLINE _GLIBCXX_SIMD_CONSTEXPR value_type operator[]([
[maybe_unused]] size_t __i) const
{
if constexpr (__is_scalar_abi<_Abi>())
{
_GLIBCXX_DEBUG_ASSERT(__i == 0);
return _M_data;
}
else
{
return _M_data[__i];
}
}
_GLIBCXX_SIMD_ALWAYS_INLINE _GLIBCXX_SIMD_CONSTEXPR simd& operator++()
{
_Impl::_S_increment(_M_data);
return *this;
}
_GLIBCXX_SIMD_ALWAYS_INLINE _GLIBCXX_SIMD_CONSTEXPR simd operator++(int)
{
simd __r = *this;
_Impl::_S_increment(_M_data);
return __r;
}
_GLIBCXX_SIMD_ALWAYS_INLINE _GLIBCXX_SIMD_CONSTEXPR simd& operator--()
{
_Impl::_S_decrement(_M_data);
return *this;
}
_GLIBCXX_SIMD_ALWAYS_INLINE _GLIBCXX_SIMD_CONSTEXPR simd operator--(int)
{
simd __r = *this;
_Impl::_S_decrement(_M_data);
return __r;
}
_GLIBCXX_SIMD_ALWAYS_INLINE _GLIBCXX_SIMD_CONSTEXPR mask_type
operator!() const
{
return {__private_init, _Impl::_S_negate(_M_data)};
}
_GLIBCXX_SIMD_ALWAYS_INLINE _GLIBCXX_SIMD_CONSTEXPR simd operator+() const
{
return *this;
}
_GLIBCXX_SIMD_ALWAYS_INLINE _GLIBCXX_SIMD_CONSTEXPR simd operator-() const
{
return {__private_init, _Impl::_S_unary_minus(_M_data)};
}
_GLIBCXX_SIMD_ALWAYS_INLINE explicit _GLIBCXX_SIMD_CONSTEXPR
simd(_CastType __init)
: _M_data(__init)
{}
_GLIBCXX_SIMD_ALWAYS_INLINE _GLIBCXX_SIMD_CONSTEXPR friend simd&
operator+=(simd& __lhs, const simd& __x)
{
return __lhs = __lhs + __x;
}
_GLIBCXX_SIMD_ALWAYS_INLINE _GLIBCXX_SIMD_CONSTEXPR friend simd&
operator-=(simd& __lhs, const simd& __x)
{
return __lhs = __lhs - __x;
}
_GLIBCXX_SIMD_ALWAYS_INLINE _GLIBCXX_SIMD_CONSTEXPR friend simd&
operator*=(simd& __lhs, const simd& __x)
{
return __lhs = __lhs * __x;
}
_GLIBCXX_SIMD_ALWAYS_INLINE _GLIBCXX_SIMD_CONSTEXPR friend simd&
operator/=(simd& __lhs, const simd& __x)
{
return __lhs = __lhs / __x;
}
_GLIBCXX_SIMD_ALWAYS_INLINE _GLIBCXX_SIMD_CONSTEXPR friend simd
operator+(const simd& __x, const simd& __y)
{
return {__private_init, _Impl::_S_plus(__x._M_data, __y._M_data)};
}
_GLIBCXX_SIMD_ALWAYS_INLINE _GLIBCXX_SIMD_CONSTEXPR friend simd
operator-(const simd& __x, const simd& __y)
{
return {__private_init, _Impl::_S_minus(__x._M_data, __y._M_data)};
}
_GLIBCXX_SIMD_ALWAYS_INLINE _GLIBCXX_SIMD_CONSTEXPR friend simd
operator*(const simd& __x, const simd& __y)
{
return {__private_init, _Impl::_S_multiplies(__x._M_data, __y._M_data)};
}
_GLIBCXX_SIMD_ALWAYS_INLINE _GLIBCXX_SIMD_CONSTEXPR friend simd
operator/(const simd& __x, const simd& __y)
{
return {__private_init, _Impl::_S_divides(__x._M_data, __y._M_data)};
}
_GLIBCXX_SIMD_ALWAYS_INLINE _GLIBCXX_SIMD_CONSTEXPR friend mask_type
operator==(const simd& __x, const simd& __y)
{
return simd::_S_make_mask(_Impl::_S_equal_to(__x._M_data, __y._M_data));
}
_GLIBCXX_SIMD_ALWAYS_INLINE _GLIBCXX_SIMD_CONSTEXPR friend mask_type
operator!=(const simd& __x, const simd& __y)
{
return simd::_S_make_mask(_Impl::_S_not_equal_to(__x._M_data, __y._M_data));
}
_GLIBCXX_SIMD_ALWAYS_INLINE _GLIBCXX_SIMD_CONSTEXPR friend mask_type
operator<(const simd& __x, const simd& __y)
{
return simd::_S_make_mask(_Impl::_S_less(__x._M_data, __y._M_data));
}
_GLIBCXX_SIMD_ALWAYS_INLINE _GLIBCXX_SIMD_CONSTEXPR friend mask_type
operator<=(const simd& __x, const simd& __y)
{
return simd::_S_make_mask(_Impl::_S_less_equal(__x._M_data, __y._M_data));
}
_GLIBCXX_SIMD_ALWAYS_INLINE _GLIBCXX_SIMD_CONSTEXPR friend mask_type
operator>(const simd& __x, const simd& __y)
{
return simd::_S_make_mask(_Impl::_S_less(__y._M_data, __x._M_data));
}
_GLIBCXX_SIMD_ALWAYS_INLINE _GLIBCXX_SIMD_CONSTEXPR friend mask_type
operator>=(const simd& __x, const simd& __y)
{
return simd::_S_make_mask(_Impl::_S_less_equal(__y._M_data, __x._M_data));
}
#ifdef __GXX_CONDITIONAL_IS_OVERLOADABLE__
_GLIBCXX_SIMD_ALWAYS_INLINE _GLIBCXX_SIMD_CONSTEXPR friend simd
operator?:(const mask_type& __k, const simd& __where_true,
const simd& __where_false)
{
auto __ret = __where_false;
_Impl::_S_masked_assign(__data(__k), __data(__ret), __data(__where_true));
return __ret;
}
#endif
_GLIBCXX_SIMD_INTRINSIC _GLIBCXX_SIMD_CONSTEXPR
simd(_PrivateInit, const _MemberType& __init)
: _M_data(__init)
{}
_GLIBCXX_SIMD_INTRINSIC simd(_BitsetInit, std::bitset<size()> __init)
: _M_data()
{
where(mask_type(__bitset_init, __init), *this) = ~*this;
}
_GLIBCXX_SIMD_INTRINSIC
constexpr bool _M_is_constprop() const
{
if constexpr (__is_scalar_abi<_Abi>())
return __builtin_constant_p(_M_data);
else
return _M_data._M_is_constprop();
}
private:
_GLIBCXX_SIMD_INTRINSIC _GLIBCXX_SIMD_CONSTEXPR static mask_type
_S_make_mask(typename mask_type::_MemberType __k)
{
return {__private_init, __k};
}
friend const auto& __data<value_type, abi_type>(const simd&);
friend auto& __data<value_type, abi_type>(simd&);
alignas(_Traits::_S_simd_align) _MemberType _M_data;
};
template <typename _Tp, typename _Ap>
_GLIBCXX_SIMD_INTRINSIC constexpr const auto&
__data(const simd<_Tp, _Ap>& __x)
{
return __x._M_data;
}
template <typename _Tp, typename _Ap>
_GLIBCXX_SIMD_INTRINSIC constexpr auto&
__data(simd<_Tp, _Ap>& __x)
{
return __x._M_data;
}
namespace __float_bitwise_operators {
template <typename _Tp, typename _Ap>
_GLIBCXX_SIMD_INTRINSIC _GLIBCXX_SIMD_CONSTEXPR simd<_Tp, _Ap>
operator^(const simd<_Tp, _Ap>& __a, const simd<_Tp, _Ap>& __b)
{
return {__private_init, _Ap::_SimdImpl::_S_bit_xor(__data(__a), __data(__b))};
}
template <typename _Tp, typename _Ap>
_GLIBCXX_SIMD_INTRINSIC _GLIBCXX_SIMD_CONSTEXPR simd<_Tp, _Ap>
operator|(const simd<_Tp, _Ap>& __a, const simd<_Tp, _Ap>& __b)
{
return {__private_init, _Ap::_SimdImpl::_S_bit_or(__data(__a), __data(__b))};
}
template <typename _Tp, typename _Ap>
_GLIBCXX_SIMD_INTRINSIC _GLIBCXX_SIMD_CONSTEXPR simd<_Tp, _Ap>
operator&(const simd<_Tp, _Ap>& __a, const simd<_Tp, _Ap>& __b)
{
return {__private_init, _Ap::_SimdImpl::_S_bit_and(__data(__a), __data(__b))};
}
}
_GLIBCXX_SIMD_END_NAMESPACE
#endif
#endif
#ifndef _GLIBCXX_EXPERIMENTAL_SIMD_FIXED_SIZE_H_
#define _GLIBCXX_EXPERIMENTAL_SIMD_FIXED_SIZE_H_ 
#if __cplusplus >= 201703L
#include <array>
_GLIBCXX_SIMD_BEGIN_NAMESPACE
template <size_t _I, typename _Tp> struct __simd_tuple_element;
template <typename _Tp, typename _A0, typename... _As>
struct __simd_tuple_element<0, _SimdTuple<_Tp, _A0, _As...>>
{
using type = std::experimental::simd<_Tp, _A0>;
};
template <size_t _I, typename _Tp, typename _A0, typename... _As>
struct __simd_tuple_element<_I, _SimdTuple<_Tp, _A0, _As...>>
{
using type =
typename __simd_tuple_element<_I - 1, _SimdTuple<_Tp, _As...>>::type;
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
_GLIBCXX_SIMD_INTRINSIC constexpr _SimdTuple<_Tp, simd_abi::scalar, _A10,
_A1s...>
__simd_tuple_concat(const _Tp& __left,
const _SimdTuple<_Tp, _A10, _A1s...>& __right)
{
return {__left, __right};
}
template <size_t _Np, typename _Tp>
_GLIBCXX_SIMD_INTRINSIC constexpr decltype(auto)
__simd_tuple_pop_front(_Tp&& __x)
{
if constexpr (_Np == 0)
return static_cast<_Tp&&>(__x);
else
{
using _Up = __remove_cvref_t<_Tp>;
static_assert(_Np >= _Up::_S_first_size);
return __simd_tuple_pop_front<_Np - _Up::_S_first_size>(__x.second);
}
}
struct __as_simd
{
};
struct __as_simd_tuple
{
};
template <typename _Tp, typename _A0, typename... _Abis>
_GLIBCXX_SIMD_INTRINSIC constexpr simd<_Tp, _A0>
__simd_tuple_get_impl(__as_simd, const _SimdTuple<_Tp, _A0, _Abis...>& __t,
_SizeConstant<0>)
{
return {__private_init, __t.first};
}
template <typename _Tp, typename _A0, typename... _Abis>
_GLIBCXX_SIMD_INTRINSIC constexpr const auto&
__simd_tuple_get_impl(__as_simd_tuple,
const _SimdTuple<_Tp, _A0, _Abis...>& __t,
_SizeConstant<0>)
{
return __t.first;
}
template <typename _Tp, typename _A0, typename... _Abis>
_GLIBCXX_SIMD_INTRINSIC constexpr auto&
__simd_tuple_get_impl(__as_simd_tuple, _SimdTuple<_Tp, _A0, _Abis...>& __t,
_SizeConstant<0>)
{
return __t.first;
}
template <typename _R, size_t _Np, typename _Tp, typename... _Abis>
_GLIBCXX_SIMD_INTRINSIC constexpr auto
__simd_tuple_get_impl(_R, const _SimdTuple<_Tp, _Abis...>& __t,
_SizeConstant<_Np>)
{
return __simd_tuple_get_impl(_R(), __t.second, _SizeConstant<_Np - 1>());
}
template <size_t _Np, typename _Tp, typename... _Abis>
_GLIBCXX_SIMD_INTRINSIC constexpr auto&
__simd_tuple_get_impl(__as_simd_tuple, _SimdTuple<_Tp, _Abis...>& __t,
_SizeConstant<_Np>)
{
return __simd_tuple_get_impl(__as_simd_tuple(), __t.second,
_SizeConstant<_Np - 1>());
}
template <size_t _Np, typename _Tp, typename... _Abis>
_GLIBCXX_SIMD_INTRINSIC constexpr auto
__get_simd_at(const _SimdTuple<_Tp, _Abis...>& __t)
{
return __simd_tuple_get_impl(__as_simd(), __t, _SizeConstant<_Np>());
}
template <size_t _Np, typename _Tp, typename... _Abis>
_GLIBCXX_SIMD_INTRINSIC constexpr auto
__get_tuple_at(const _SimdTuple<_Tp, _Abis...>& __t)
{
return __simd_tuple_get_impl(__as_simd_tuple(), __t, _SizeConstant<_Np>());
}
template <size_t _Np, typename _Tp, typename... _Abis>
_GLIBCXX_SIMD_INTRINSIC constexpr auto&
__get_tuple_at(_SimdTuple<_Tp, _Abis...>& __t)
{
return __simd_tuple_get_impl(__as_simd_tuple(), __t, _SizeConstant<_Np>());
}
template <typename _Tp, typename _Abi, size_t _Offset>
struct __tuple_element_meta : public _Abi::_SimdImpl
{
static_assert(is_same_v<typename _Abi::_SimdImpl::abi_type,
_Abi>);
using value_type = _Tp;
using abi_type = _Abi;
using _Traits = _SimdTraits<_Tp, _Abi>;
using _MaskImpl = typename _Abi::_MaskImpl;
using _MaskMember = typename _Traits::_MaskMember;
using simd_type = std::experimental::simd<_Tp, _Abi>;
static constexpr size_t _S_offset = _Offset;
static constexpr size_t _S_size() { return simd_size<_Tp, _Abi>::value; }
static constexpr _MaskImpl _S_mask_impl = {};
template <size_t _Np, bool _Sanitized>
_GLIBCXX_SIMD_INTRINSIC static auto
_S_submask(_BitMask<_Np, _Sanitized> __bits)
{
return __bits.template _M_extract<_Offset, _S_size()>();
}
template <size_t _Np, bool _Sanitized>
_GLIBCXX_SIMD_INTRINSIC static _MaskMember
_S_make_mask(_BitMask<_Np, _Sanitized> __bits)
{
return _MaskImpl::template _S_convert<_Tp>(
__bits.template _M_extract<_Offset, _S_size()>()._M_sanitized());
}
_GLIBCXX_SIMD_INTRINSIC static _ULLong
_S_mask_to_shifted_ullong(_MaskMember __k)
{
return _MaskImpl::_S_to_bits(__k).to_ullong() << _Offset;
}
};
template <size_t _Offset, typename _Tp, typename _Abi, typename... _As>
__tuple_element_meta<_Tp, _Abi, _Offset>
__make_meta(const _SimdTuple<_Tp, _Abi, _As...>&)
{
return {};
}
template <size_t _Offset, typename _Base> struct _WithOffset : public _Base
{
static inline constexpr size_t _S_offset = _Offset;
_GLIBCXX_SIMD_INTRINSIC char* _M_as_charptr()
{
return reinterpret_cast<char*>(this)
+ _S_offset * sizeof(typename _Base::value_type);
}
_GLIBCXX_SIMD_INTRINSIC const char* _M_as_charptr() const
{
return reinterpret_cast<const char*>(this)
+ _S_offset * sizeof(typename _Base::value_type);
}
};
template <size_t _O0, size_t _O1, typename _Base>
struct _WithOffset<_O0, _WithOffset<_O1, _Base>>
{
};
template <size_t _Offset, typename _Tp>
decltype(auto)
__add_offset(_Tp& __base)
{
return static_cast<_WithOffset<_Offset, __remove_cvref_t<_Tp>>&>(__base);
}
template <size_t _Offset, typename _Tp>
decltype(auto)
__add_offset(const _Tp& __base)
{
return static_cast<const _WithOffset<_Offset, __remove_cvref_t<_Tp>>&>(
__base);
}
template <size_t _Offset, size_t _ExistingOffset, typename _Tp>
decltype(auto)
__add_offset(_WithOffset<_ExistingOffset, _Tp>& __base)
{
return static_cast<_WithOffset<_Offset + _ExistingOffset, _Tp>&>(
static_cast<_Tp&>(__base));
}
template <size_t _Offset, size_t _ExistingOffset, typename _Tp>
decltype(auto)
__add_offset(const _WithOffset<_ExistingOffset, _Tp>& __base)
{
return static_cast<const _WithOffset<_Offset + _ExistingOffset, _Tp>&>(
static_cast<const _Tp&>(__base));
}
template <typename _Tp> constexpr inline size_t __offset = 0;
template <size_t _Offset, typename _Tp>
constexpr inline size_t
__offset<_WithOffset<_Offset, _Tp>> = _WithOffset<_Offset, _Tp>::_S_offset;
template <typename _Tp>
constexpr inline size_t __offset<const _Tp> = __offset<_Tp>;
template <typename _Tp> constexpr inline size_t __offset<_Tp&> = __offset<_Tp>;
template <typename _Tp> constexpr inline size_t __offset<_Tp&&> = __offset<_Tp>;
template <typename _Tp> struct _SimdTuple<_Tp>
{
using value_type = _Tp;
static constexpr size_t _S_tuple_size = 0;
static constexpr size_t _S_size() { return 0; }
};
template <typename _FirstType, typename _SecondType> struct _SimdTupleData
{
_FirstType first;
_SecondType second;
_GLIBCXX_SIMD_INTRINSIC
constexpr bool _M_is_constprop() const
{
if constexpr(is_class_v<_FirstType>)
return first._M_is_constprop() && second._M_is_constprop();
else
return __builtin_constant_p(first) && second._M_is_constprop();
}
};
template <typename _FirstType, typename _Tp>
struct _SimdTupleData<_FirstType, _SimdTuple<_Tp>>
{
_FirstType first;
static constexpr _SimdTuple<_Tp> second = {};
_GLIBCXX_SIMD_INTRINSIC
constexpr bool _M_is_constprop() const
{
if constexpr(is_class_v<_FirstType>)
return first._M_is_constprop();
else
return __builtin_constant_p(first);
}
};
template <typename _Tp, typename _Abi0, typename... _Abis>
struct _SimdTuple<_Tp, _Abi0, _Abis...>
: _SimdTupleData<typename _SimdTraits<_Tp, _Abi0>::_SimdMember,
_SimdTuple<_Tp, _Abis...>>
{
static_assert(!__is_fixed_size_abi_v<_Abi0>);
using value_type = _Tp;
using _FirstType = typename _SimdTraits<_Tp, _Abi0>::_SimdMember;
using _FirstAbi = _Abi0;
using _SecondType = _SimdTuple<_Tp, _Abis...>;
static constexpr size_t _S_tuple_size = sizeof...(_Abis) + 1;
static constexpr size_t _S_size()
{
return simd_size_v<_Tp, _Abi0> + _SecondType::_S_size();
}
static constexpr size_t _S_first_size = simd_size_v<_Tp, _Abi0>;
static constexpr bool _S_is_homogeneous
= (std::is_same_v<_Abi0, _Abis> && ...);
using _Base = _SimdTupleData<typename _SimdTraits<_Tp, _Abi0>::_SimdMember,
_SimdTuple<_Tp, _Abis...>>;
using _Base::first;
using _Base::second;
_GLIBCXX_SIMD_INTRINSIC constexpr _SimdTuple() = default;
_GLIBCXX_SIMD_INTRINSIC constexpr _SimdTuple(const _SimdTuple&) = default;
_GLIBCXX_SIMD_INTRINSIC constexpr _SimdTuple& operator=(const _SimdTuple&)
= default;
template <typename _Up>
_GLIBCXX_SIMD_INTRINSIC constexpr _SimdTuple(_Up&& __x)
: _Base{static_cast<_Up&&>(__x)}
{}
template <typename _Up, typename _Up2>
_GLIBCXX_SIMD_INTRINSIC constexpr _SimdTuple(_Up&& __x, _Up2&& __y)
: _Base{static_cast<_Up&&>(__x), static_cast<_Up2&&>(__y)}
{}
template <typename _Up>
_GLIBCXX_SIMD_INTRINSIC constexpr _SimdTuple(_Up&& __x, _SimdTuple<_Tp>)
: _Base{static_cast<_Up&&>(__x)}
{}
_GLIBCXX_SIMD_INTRINSIC char* _M_as_charptr()
{
return reinterpret_cast<char*>(this);
}
_GLIBCXX_SIMD_INTRINSIC const char* _M_as_charptr() const
{
return reinterpret_cast<const char*>(this);
}
template <size_t _Np> _GLIBCXX_SIMD_INTRINSIC constexpr auto& _M_at()
{
if constexpr (_Np == 0)
return first;
else
return second.template _M_at<_Np - 1>();
}
template <size_t _Np>
_GLIBCXX_SIMD_INTRINSIC constexpr const auto& _M_at() const
{
if constexpr (_Np == 0)
return first;
else
return second.template _M_at<_Np - 1>();
}
template <size_t _Np>
_GLIBCXX_SIMD_INTRINSIC constexpr auto _M_simd_at() const
{
if constexpr (_Np == 0)
return simd<_Tp, _Abi0>(__private_init, first);
else
return second.template _M_simd_at<_Np - 1>();
}
template <size_t _Offset = 0, typename _Fp>
_GLIBCXX_SIMD_INTRINSIC static constexpr _SimdTuple
_S_generate(_Fp&& __gen, _SizeConstant<_Offset> = {})
{
auto&& __first = __gen(__tuple_element_meta<_Tp, _Abi0, _Offset>());
if constexpr (_S_tuple_size == 1)
return {__first};
else
return {__first, _SecondType::_S_generate(
static_cast<_Fp&&>(__gen),
_SizeConstant<_Offset + simd_size_v<_Tp, _Abi0>>())};
}
template <size_t _Offset = 0, typename _Fp, typename... _More>
_GLIBCXX_SIMD_INTRINSIC _SimdTuple
_M_apply_wrapped(_Fp&& __fun, const _More&... __more) const
{
auto&& __first = __fun(__make_meta<_Offset>(*this), first, __more.first...);
if constexpr (_S_tuple_size == 1)
return {__first};
else
return {
__first,
second.template _M_apply_wrapped<_Offset + simd_size_v<_Tp, _Abi0>>(
static_cast<_Fp&&>(__fun), __more.second...)};
}
template <typename _Tup>
_GLIBCXX_SIMD_INTRINSIC constexpr decltype(auto)
_M_extract_argument(_Tup&& __tup) const
{
using _TupT = typename __remove_cvref_t<_Tup>::value_type;
if constexpr (is_same_v<_SimdTuple, __remove_cvref_t<_Tup>>)
return __tup.first;
else if (__builtin_is_constant_evaluated())
return __fixed_size_storage_t<_TupT, _S_first_size>::_S_generate([&](
auto __meta) constexpr {
return __meta._S_generator(
[&](auto __i) constexpr { return __tup[__i]; },
static_cast<_TupT*>(nullptr));
});
else
return [&]() {
__fixed_size_storage_t<_TupT, _S_first_size> __r;
__builtin_memcpy(__r._M_as_charptr(), __tup._M_as_charptr(),
sizeof(__r));
return __r;
}();
}
template <typename _Tup>
_GLIBCXX_SIMD_INTRINSIC constexpr auto& _M_skip_argument(_Tup&& __tup) const
{
static_assert(_S_tuple_size > 1);
using _Up = __remove_cvref_t<_Tup>;
constexpr size_t __off = __offset<_Up>;
if constexpr (_S_first_size == _Up::_S_first_size && __off == 0)
return __tup.second;
else if constexpr (_S_first_size > _Up::_S_first_size
&& _S_first_size % _Up::_S_first_size == 0 && __off == 0)
return __simd_tuple_pop_front<_S_first_size>(__tup);
else if constexpr (_S_first_size + __off < _Up::_S_first_size)
return __add_offset<_S_first_size>(__tup);
else if constexpr (_S_first_size + __off == _Up::_S_first_size)
return __tup.second;
else
__assert_unreachable<_Tup>();
}
template <size_t _Offset, typename... _More>
_GLIBCXX_SIMD_INTRINSIC constexpr void
_M_assign_front(const _SimdTuple<_Tp, _Abi0, _More...>& __x) &
{
static_assert(_Offset == 0);
first = __x.first;
if constexpr (sizeof...(_More) > 0)
{
static_assert(sizeof...(_Abis) >= sizeof...(_More));
second.template _M_assign_front<0>(__x.second);
}
}
template <size_t _Offset>
_GLIBCXX_SIMD_INTRINSIC constexpr void
_M_assign_front(const _FirstType& __x) &
{
static_assert(_Offset == 0);
first = __x;
}
template <size_t _Offset, typename... _As>
_GLIBCXX_SIMD_INTRINSIC constexpr void
_M_assign_front(const _SimdTuple<_Tp, _As...>& __x) &
{
__builtin_memcpy(_M_as_charptr() + _Offset * sizeof(value_type),
__x._M_as_charptr(),
sizeof(_Tp) * _SimdTuple<_Tp, _As...>::_S_size());
}
template <typename _Fp, typename... _More>
_GLIBCXX_SIMD_INTRINSIC constexpr _SimdTuple
_M_apply_per_chunk(_Fp&& __fun, _More&&... __more) const
{
if constexpr ((...
|| conjunction_v<
is_lvalue_reference<_More>,
negation<is_const<remove_reference_t<_More>>>>) )
{
auto&& __first = [&](auto... __args) constexpr
{
auto __r
= __fun(__tuple_element_meta<_Tp, _Abi0, 0>(), first, __args...);
[[maybe_unused]] auto&& __ignore_me = {(
[](auto&& __dst, const auto& __src) {
if constexpr (is_assignable_v<decltype(__dst), decltype(__dst)>)
{
__dst.template _M_assign_front<__offset<decltype(__dst)>>(
__src);
}
}(static_cast<_More&&>(__more), __args),
0)...};
return __r;
}
(_M_extract_argument(__more)...);
if constexpr (_S_tuple_size == 1)
return {__first};
else
return {__first,
second._M_apply_per_chunk(static_cast<_Fp&&>(__fun),
_M_skip_argument(__more)...)};
}
else
{
auto&& __first = __fun(__tuple_element_meta<_Tp, _Abi0, 0>(), first,
_M_extract_argument(__more)...);
if constexpr (_S_tuple_size == 1)
return {__first};
else
return {__first,
second._M_apply_per_chunk(static_cast<_Fp&&>(__fun),
_M_skip_argument(__more)...)};
}
}
template <typename _R = _Tp, typename _Fp, typename... _More>
_GLIBCXX_SIMD_INTRINSIC auto _M_apply_r(_Fp&& __fun,
const _More&... __more) const
{
auto&& __first
= __fun(__tuple_element_meta<_Tp, _Abi0, 0>(), first, __more.first...);
if constexpr (_S_tuple_size == 1)
return __first;
else
return __simd_tuple_concat<_R>(
__first, second.template _M_apply_r<_R>(static_cast<_Fp&&>(__fun),
__more.second...));
}
template <typename _Fp, typename... _More>
_GLIBCXX_SIMD_INTRINSIC constexpr friend _SanitizedBitMask<_S_size()>
_M_test(const _Fp& __fun, const _SimdTuple& __x, const _More&... __more)
{
const _SanitizedBitMask<_S_first_size> __first
= _Abi0::_MaskImpl::_S_to_bits(
__fun(__tuple_element_meta<_Tp, _Abi0, 0>(), __x.first,
__more.first...));
if constexpr (_S_tuple_size == 1)
return __first;
else
return _M_test(__fun, __x.second, __more.second...)._M_prepend(__first);
}
template <typename _Up, _Up _I>
_GLIBCXX_SIMD_INTRINSIC constexpr _Tp
operator[](std::integral_constant<_Up, _I>) const noexcept
{
if constexpr (_I < simd_size_v<_Tp, _Abi0>)
return _M_subscript_read(_I);
else
return second[std::integral_constant<_Up,
_I - simd_size_v<_Tp, _Abi0>>()];
}
_Tp operator[](size_t __i) const noexcept
{
if constexpr (_S_tuple_size == 1)
return _M_subscript_read(__i);
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
? _M_subscript_read(__i)
: second[__i - simd_size_v<_Tp, _Abi0>];
#endif
}
}
void _M_set(size_t __i, _Tp __val) noexcept
{
if constexpr (_S_tuple_size == 1)
return _M_subscript_write(__i, __val);
else
{
#ifdef _GLIBCXX_SIMD_USE_ALIASING_LOADS
reinterpret_cast<__may_alias<_Tp>*>(this)[__i] = __val;
#else
if (__i < simd_size_v<_Tp, _Abi0>)
_M_subscript_write(__i, __val);
else
second._M_set(__i - simd_size_v<_Tp, _Abi0>, __val);
#endif
}
}
private:
_Tp _M_subscript_read([[maybe_unused]] size_t __i) const noexcept
{
if constexpr (__is_vectorizable_v<_FirstType>)
return first;
else
return first[__i];
}
void _M_subscript_write([[maybe_unused]] size_t __i, _Tp __y) noexcept
{
if constexpr (__is_vectorizable_v<_FirstType>)
first = __y;
else
first._M_set(__i, __y);
}
};
template <typename _Tp, typename _A0>
_GLIBCXX_SIMD_INTRINSIC _SimdTuple<_Tp, _A0>
__make_simd_tuple(std::experimental::simd<_Tp, _A0> __x0)
{
return {__data(__x0)};
}
template <typename _Tp, typename _A0, typename... _As>
_GLIBCXX_SIMD_INTRINSIC _SimdTuple<_Tp, _A0, _As...>
__make_simd_tuple(const std::experimental::simd<_Tp, _A0>& __x0,
const std::experimental::simd<_Tp, _As>&... __xs)
{
return {__data(__x0), __make_simd_tuple(__xs...)};
}
template <typename _Tp, typename _A0>
_GLIBCXX_SIMD_INTRINSIC _SimdTuple<_Tp, _A0>
__make_simd_tuple(const typename _SimdTraits<_Tp, _A0>::_SimdMember& __arg0)
{
return {__arg0};
}
template <typename _Tp, typename _A0, typename _A1, typename... _Abis>
_GLIBCXX_SIMD_INTRINSIC _SimdTuple<_Tp, _A0, _A1, _Abis...>
__make_simd_tuple(
const typename _SimdTraits<_Tp, _A0>::_SimdMember& __arg0,
const typename _SimdTraits<_Tp, _A1>::_SimdMember& __arg1,
const typename _SimdTraits<_Tp, _Abis>::_SimdMember&... __args)
{
return {__arg0, __make_simd_tuple<_Tp, _A1, _Abis...>(__arg1, __args...)};
}
template <typename _Tp, size_t _Np, typename _V, size_t _NV, typename... _VX>
_GLIBCXX_SIMD_INTRINSIC constexpr __fixed_size_storage_t<_Tp, _Np>
__to_simd_tuple(const std::array<_V, _NV>& __from, const _VX... __fromX);
template <typename _Tp, size_t _Np,
size_t _Offset = 0,
typename _R = __fixed_size_storage_t<_Tp, _Np>, typename _V0,
typename _V0VT = _VectorTraits<_V0>, typename... _VX>
_GLIBCXX_SIMD_INTRINSIC _R constexpr __to_simd_tuple(const _V0 __from0,
const _VX... __fromX)
{
static_assert(std::is_same_v<typename _V0VT::value_type, _Tp>);
static_assert(_Offset < _V0VT::_S_full_size);
using _R0 = __vector_type_t<_Tp, _R::_S_first_size>;
if constexpr (_R::_S_tuple_size == 1)
{
if constexpr (_Np == 1)
return _R{__from0[_Offset]};
else if constexpr (_Offset == 0 && _V0VT::_S_full_size >= _Np)
return _R{__intrin_bitcast<_R0>(__from0)};
else if constexpr (_Offset * 2 == _V0VT::_S_full_size
&& _V0VT::_S_full_size / 2 >= _Np)
return _R{__intrin_bitcast<_R0>(__extract_part<1, 2>(__from0))};
else if constexpr (_Offset * 4 == _V0VT::_S_full_size
&& _V0VT::_S_full_size / 4 >= _Np)
return _R{__intrin_bitcast<_R0>(__extract_part<1, 4>(__from0))};
else
__assert_unreachable<_Tp>();
}
else
{
if constexpr (1 == _R::_S_first_size)
{
if constexpr (_Offset + 1 < _V0VT::_S_full_size)
return _R{__from0[_Offset],
__to_simd_tuple<_Tp, _Np - 1, _Offset + 1>(__from0,
__fromX...)};
else
return _R{__from0[_Offset],
__to_simd_tuple<_Tp, _Np - 1, 0>(__fromX...)};
}
else if constexpr (_V0VT::_S_full_size == _R::_S_first_size
&& _Offset == 0)
return _R{__from0,
__to_simd_tuple<_Tp, _Np - _R::_S_first_size>(__fromX...)};
else if constexpr (_V0VT::_S_full_size > _R::_S_first_size
&& _Offset == 0)
return _R{__intrin_bitcast<_R0>(__from0),
__to_simd_tuple<_Tp, _Np - _R::_S_first_size,
_R::_S_first_size>(__from0, __fromX...)};
else if constexpr (_Offset * 4 == _V0VT::_S_full_size
&& _V0VT::_S_full_size >= 4 * _R::_S_first_size)
return _R{__intrin_bitcast<_R0>(__extract_part<2, 4>(__from0)),
__to_simd_tuple<_Tp, _Np - _R::_S_first_size,
_Offset + _R::_S_first_size>(__from0,
__fromX...)};
else if constexpr (_Offset * 2 == _V0VT::_S_full_size
&& _V0VT::_S_full_size >= 4 * _R::_S_first_size)
return _R{__intrin_bitcast<_R0>(__extract_part<2, 4>(__from0)),
__to_simd_tuple<_Tp, _Np - _R::_S_first_size,
_Offset + _R::_S_first_size>(__from0,
__fromX...)};
else if constexpr (_Offset * 2 == _V0VT::_S_full_size
&& _V0VT::_S_full_size / 2 >= _R::_S_first_size)
return _R{__intrin_bitcast<_R0>(__extract_part<1, 2>(__from0)),
__to_simd_tuple<_Tp, _Np - _R::_S_first_size, 0>(__fromX...)};
else
__assert_unreachable<_Tp>();
}
}
template <typename _Tp, size_t _Np, typename _V, size_t _NV, typename... _VX>
_GLIBCXX_SIMD_INTRINSIC constexpr __fixed_size_storage_t<_Tp, _Np>
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
return __to_simd_tuple<_Tp, _Np>(__args..., __fromX...);
});
}
template <size_t, typename _Tp> using __to_tuple_helper = _Tp;
template <typename _Tp, typename _A0, size_t _NOut, size_t _Np,
size_t... _Indexes>
_GLIBCXX_SIMD_INTRINSIC __fixed_size_storage_t<_Tp, _NOut>
__to_simd_tuple_impl(
std::index_sequence<_Indexes...>,
const std::array<__vector_type_t<_Tp, simd_size_v<_Tp, _A0>>, _Np>& __args)
{
return __make_simd_tuple<_Tp, __to_tuple_helper<_Indexes, _A0>...>(
__args[_Indexes]...);
}
template <typename _Tp, typename _A0, size_t _NOut, size_t _Np,
typename _R = __fixed_size_storage_t<_Tp, _NOut>>
_GLIBCXX_SIMD_INTRINSIC _R
__to_simd_tuple_sized(
const std::array<__vector_type_t<_Tp, simd_size_v<_Tp, _A0>>, _Np>& __args)
{
static_assert(_Np * simd_size_v<_Tp, _A0> >= _NOut);
return __to_simd_tuple_impl<_Tp, _A0, _NOut>(
std::make_index_sequence<_R::_S_tuple_size>(), __args);
}
template <typename _Tp>
_GLIBCXX_SIMD_INTRINSIC _SimdTuple<_Tp>
__optimize_simd_tuple(const _SimdTuple<_Tp>)
{
return {};
}
template <typename _Tp, typename _Ap>
_GLIBCXX_SIMD_INTRINSIC const _SimdTuple<_Tp, _Ap>&
__optimize_simd_tuple(const _SimdTuple<_Tp, _Ap>& __x)
{
return __x;
}
template <typename _Tp, typename _A0, typename _A1, typename... _Abis,
typename _R = __fixed_size_storage_t<
_Tp, _SimdTuple<_Tp, _A0, _A1, _Abis...>::_S_size()>>
_GLIBCXX_SIMD_INTRINSIC _R
__optimize_simd_tuple(const _SimdTuple<_Tp, _A0, _A1, _Abis...>& __x)
{
using _Tup = _SimdTuple<_Tp, _A0, _A1, _Abis...>;
if constexpr (std::is_same_v<_R, _Tup>)
return __x;
else if constexpr (is_same_v<typename _R::_FirstType,
typename _Tup::_FirstType>)
return {__x.first, __optimize_simd_tuple(__x.second)};
else if constexpr (__is_scalar_abi<_A0>() || _A0::template _S_is_partial<_Tp>)
return {
__generate_from_n_evaluations<_R::_S_first_size, typename _R::_FirstType>(
[&](auto __i) { return __x[__i]; }),
__optimize_simd_tuple(__simd_tuple_pop_front<_R::_S_first_size>(__x))};
else if constexpr (_R::_S_first_size
== simd_size_v<
_Tp,
_A0> + simd_size_v<_Tp, _A1> && is_same_v<_A0, _A1>)
return {__concat(__x.template _M_at<0>(), __x.template _M_at<1>()),
__optimize_simd_tuple(__x.second.second)};
else if constexpr (sizeof...(_Abis) >= 2
&& _R::_S_first_size == (4 * simd_size_v<_Tp, _A0>)
&& simd_size_v<_Tp, _A0> == __simd_tuple_element_t<
(sizeof...(_Abis) >= 2 ? 3 : 0), _Tup>::size())
return {__concat(__concat(__x.template _M_at<0>(), __x.template _M_at<1>()),
__concat(__x.template _M_at<2>(),
__x.template _M_at<3>())),
__optimize_simd_tuple(__x.second.second.second.second)};
else
{
static_assert(sizeof(_R) == sizeof(__x));
_R __r;
__builtin_memcpy(__r._M_as_charptr(), __x._M_as_charptr(),
sizeof(_Tp) * _R::_S_size());
return __r;
}
}
template <size_t _Offset = 0, typename _Tp, typename _A0, typename _Fp>
_GLIBCXX_SIMD_INTRINSIC constexpr void
__for_each(const _SimdTuple<_Tp, _A0>& __t, _Fp&& __fun)
{
static_cast<_Fp&&>(__fun)(__make_meta<_Offset>(__t), __t.first);
}
template <size_t _Offset = 0, typename _Tp, typename _A0, typename _A1,
typename... _As, typename _Fp>
_GLIBCXX_SIMD_INTRINSIC constexpr void
__for_each(const _SimdTuple<_Tp, _A0, _A1, _As...>& __t, _Fp&& __fun)
{
__fun(__make_meta<_Offset>(__t), __t.first);
__for_each<_Offset + simd_size<_Tp, _A0>::value>(__t.second,
static_cast<_Fp&&>(__fun));
}
template <size_t _Offset = 0, typename _Tp, typename _A0, typename _Fp>
_GLIBCXX_SIMD_INTRINSIC constexpr void
__for_each(_SimdTuple<_Tp, _A0>& __t, _Fp&& __fun)
{
static_cast<_Fp&&>(__fun)(__make_meta<_Offset>(__t), __t.first);
}
template <size_t _Offset = 0, typename _Tp, typename _A0, typename _A1,
typename... _As, typename _Fp>
_GLIBCXX_SIMD_INTRINSIC constexpr void
__for_each(_SimdTuple<_Tp, _A0, _A1, _As...>& __t, _Fp&& __fun)
{
__fun(__make_meta<_Offset>(__t), __t.first);
__for_each<_Offset + simd_size<_Tp, _A0>::value>(__t.second,
static_cast<_Fp&&>(__fun));
}
template <size_t _Offset = 0, typename _Tp, typename _A0, typename _Fp>
_GLIBCXX_SIMD_INTRINSIC constexpr void
__for_each(_SimdTuple<_Tp, _A0>& __a, const _SimdTuple<_Tp, _A0>& __b,
_Fp&& __fun)
{
static_cast<_Fp&&>(__fun)(__make_meta<_Offset>(__a), __a.first, __b.first);
}
template <size_t _Offset = 0, typename _Tp, typename _A0, typename _A1,
typename... _As, typename _Fp>
_GLIBCXX_SIMD_INTRINSIC constexpr void
__for_each(_SimdTuple<_Tp, _A0, _A1, _As...>& __a,
const _SimdTuple<_Tp, _A0, _A1, _As...>& __b, _Fp&& __fun)
{
__fun(__make_meta<_Offset>(__a), __a.first, __b.first);
__for_each<_Offset + simd_size<_Tp, _A0>::value>(__a.second, __b.second,
static_cast<_Fp&&>(__fun));
}
template <size_t _Offset = 0, typename _Tp, typename _A0, typename _Fp>
_GLIBCXX_SIMD_INTRINSIC constexpr void
__for_each(const _SimdTuple<_Tp, _A0>& __a, const _SimdTuple<_Tp, _A0>& __b,
_Fp&& __fun)
{
static_cast<_Fp&&>(__fun)(__make_meta<_Offset>(__a), __a.first, __b.first);
}
template <size_t _Offset = 0, typename _Tp, typename _A0, typename _A1,
typename... _As, typename _Fp>
_GLIBCXX_SIMD_INTRINSIC constexpr void
__for_each(const _SimdTuple<_Tp, _A0, _A1, _As...>& __a,
const _SimdTuple<_Tp, _A0, _A1, _As...>& __b, _Fp&& __fun)
{
__fun(__make_meta<_Offset>(__a), __a.first, __b.first);
__for_each<_Offset + simd_size<_Tp, _A0>::value>(__a.second, __b.second,
static_cast<_Fp&&>(__fun));
}
template <int _Index, int _Total, int _Combine, typename _Tp, typename _A0,
typename... _As>
_GLIBCXX_SIMD_INTRINSIC auto
__extract_part(const _SimdTuple<_Tp, _A0, _As...>& __x)
{
using _Tuple = _SimdTuple<_Tp, _A0, _As...>;
static_assert(_Index + _Combine <= _Total && _Index >= 0 && _Total >= 1);
constexpr size_t _Np = _Tuple::_S_size();
static_assert(_Np >= _Total && _Np % _Total == 0);
constexpr size_t __values_per_part = _Np / _Total;
[[maybe_unused]] constexpr size_t __values_to_skip
= _Index * __values_per_part;
constexpr size_t __return_size = __values_per_part * _Combine;
using _RetAbi = simd_abi::deduce_t<_Tp, __return_size>;
if constexpr (_Index == 0 && _Tuple::_S_first_size == __return_size)
return __x.first._M_data;
else if constexpr (_Index == 0 && _Total == _Combine)
return __x;
else if constexpr (_Index == 0 && _Tuple::_S_first_size >= __return_size)
return __intrin_bitcast<__vector_type_t<_Tp, __return_size>>(
__as_vector(__x.first));
else if constexpr (__values_to_skip >= _Tuple::_S_first_size)
{
if constexpr (_Tuple::_S_first_size % __values_per_part == 0)
{
constexpr int __parts_in_first
= _Tuple::_S_first_size / __values_per_part;
return __extract_part<_Index - __parts_in_first,
_Total - __parts_in_first, _Combine>(
__x.second);
}
else
return __extract_part<__values_to_skip - _Tuple::_S_first_size,
_Np - _Tuple::_S_first_size, __return_size>(
__x.second);
}
else if constexpr (__return_size > _Tuple::_S_first_size - __values_to_skip)
{
#ifdef _GLIBCXX_SIMD_USE_ALIASING_LOADS
const __may_alias<_Tp>* const element_ptr
= reinterpret_cast<const __may_alias<_Tp>*>(&__x) + __values_to_skip;
return __as_vector(simd<_Tp, _RetAbi>(element_ptr, element_aligned));
#else
[[maybe_unused]] constexpr size_t __offset = __values_to_skip;
return __as_vector(simd<_Tp, _RetAbi>([&](auto __i) constexpr {
constexpr _SizeConstant<__i + __offset> __k;
return __x[__k];
}));
#endif
}
else if constexpr (_Tuple::_S_first_size % __values_per_part == 0)
return __extract_part<_Index, _Tuple::_S_first_size / __values_per_part,
_Combine>(__x.first);
else
return __extract_part<__values_to_skip, _Tuple::_S_first_size,
_Combine * __values_per_part>(__x.first);
}
template <typename _Tp, int _Np, typename _Tuple,
typename _Next = simd<_Tp, _AllNativeAbis::_BestAbi<_Tp, _Np>>,
int _Remain = _Np - int(_Next::size())>
struct __fixed_size_storage_builder;
template <typename _Tp, int _Np>
struct __fixed_size_storage
: public __fixed_size_storage_builder<_Tp, _Np, _SimdTuple<_Tp>>
{
};
template <typename _Tp, int _Np, typename... _As, typename _Next>
struct __fixed_size_storage_builder<_Tp, _Np, _SimdTuple<_Tp, _As...>, _Next, 0>
{
using type = _SimdTuple<_Tp, _As..., typename _Next::abi_type>;
};
template <typename _Tp, int _Np, typename... _As, typename _Next, int _Remain>
struct __fixed_size_storage_builder<_Tp, _Np, _SimdTuple<_Tp, _As...>, _Next,
_Remain>
{
using type = typename __fixed_size_storage_builder<
_Tp, _Remain, _SimdTuple<_Tp, _As..., typename _Next::abi_type>>::type;
};
template <typename _Tp> struct _SeqOp;
template <size_t _I0, size_t... _Is>
struct _SeqOp<std::index_sequence<_I0, _Is...>>
{
using _FirstPlusOne = std::index_sequence<_I0 + 1, _Is...>;
using _NotFirstPlusOne = std::index_sequence<_I0, (_Is + 1)...>;
template <size_t _First, size_t _Add>
using _Prepend = std::index_sequence<_First, _I0 + _Add, (_Is + _Add)...>;
};
template <typename _Tp> struct _AbisInSimdTuple;
template <typename _Tp> struct _AbisInSimdTuple<_SimdTuple<_Tp>>
{
using _Counts = std::index_sequence<0>;
using _Begins = std::index_sequence<0>;
};
template <typename _Tp, typename _Ap>
struct _AbisInSimdTuple<_SimdTuple<_Tp, _Ap>>
{
using _Counts = std::index_sequence<1>;
using _Begins = std::index_sequence<0>;
};
template <typename _Tp, typename _A0, typename... _As>
struct _AbisInSimdTuple<_SimdTuple<_Tp, _A0, _A0, _As...>>
{
using _Counts = typename _SeqOp<typename _AbisInSimdTuple<
_SimdTuple<_Tp, _A0, _As...>>::_Counts>::_FirstPlusOne;
using _Begins = typename _SeqOp<typename _AbisInSimdTuple<
_SimdTuple<_Tp, _A0, _As...>>::_Begins>::_NotFirstPlusOne;
};
template <typename _Tp, typename _A0, typename _A1, typename... _As>
struct _AbisInSimdTuple<_SimdTuple<_Tp, _A0, _A1, _As...>>
{
using _Counts = typename _SeqOp<typename _AbisInSimdTuple<
_SimdTuple<_Tp, _A1, _As...>>::_Counts>::template _Prepend<1, 0>;
using _Begins = typename _SeqOp<typename _AbisInSimdTuple<
_SimdTuple<_Tp, _A1, _As...>>::_Begins>::template _Prepend<0, 1>;
};
template <typename _Tp, bool = std::is_arithmetic_v<__remove_cvref_t<_Tp>>>
struct __autocvt_to_simd
{
_Tp _M_data;
using _TT = __remove_cvref_t<_Tp>;
operator _TT() { return _M_data; }
operator _TT&()
{
static_assert(std::is_lvalue_reference<_Tp>::value, "");
static_assert(!std::is_const<_Tp>::value, "");
return _M_data;
}
operator _TT*()
{
static_assert(std::is_lvalue_reference<_Tp>::value, "");
static_assert(!std::is_const<_Tp>::value, "");
return &_M_data;
}
constexpr inline __autocvt_to_simd(_Tp dd) : _M_data(dd) {}
template <typename _Abi> operator simd<typename _TT::value_type, _Abi>()
{
return {__private_init, _M_data};
}
template <typename _Abi> operator simd<typename _TT::value_type, _Abi> &()
{
return *reinterpret_cast<simd<typename _TT::value_type, _Abi>*>(&_M_data);
}
template <typename _Abi> operator simd<typename _TT::value_type, _Abi> *()
{
return reinterpret_cast<simd<typename _TT::value_type, _Abi>*>(&_M_data);
}
};
template <typename _Tp> __autocvt_to_simd(_Tp &&) -> __autocvt_to_simd<_Tp>;
template <typename _Tp> struct __autocvt_to_simd<_Tp, true>
{
using _TT = __remove_cvref_t<_Tp>;
_Tp _M_data;
fixed_size_simd<_TT, 1> _M_fd;
constexpr inline __autocvt_to_simd(_Tp dd) : _M_data(dd), _M_fd(_M_data) {}
~__autocvt_to_simd() { _M_data = __data(_M_fd).first; }
operator fixed_size_simd<_TT, 1>() { return _M_fd; }
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
struct _CommonImplFixedSize;
template <int _Np> struct _SimdImplFixedSize;
template <int _Np> struct _MaskImplFixedSize;
template <int _Np> struct simd_abi::_Fixed
{
template <typename _Tp> static constexpr size_t _S_size = _Np;
template <typename _Tp> static constexpr size_t _S_full_size = _Np;
struct _IsValidAbiTag : public __bool_constant<(_Np > 0)>
{
};
template <typename _Tp>
struct _IsValidSizeFor
: __bool_constant<(_Np <= simd_abi::max_fixed_size<_Tp>)>
{
};
template <typename _Tp>
struct _IsValid
: conjunction<_IsValidAbiTag, __is_vectorizable<_Tp>, _IsValidSizeFor<_Tp>>
{
};
template <typename _Tp>
static constexpr bool _S_is_valid_v = _IsValid<_Tp>::value;
_GLIBCXX_SIMD_INTRINSIC static constexpr _SanitizedBitMask<_Np>
_S_masked(_BitMask<_Np> __x)
{
return __x._M_sanitized();
}
_GLIBCXX_SIMD_INTRINSIC static constexpr _SanitizedBitMask<_Np>
_S_masked(_SanitizedBitMask<_Np> __x)
{
return __x;
}
using _CommonImpl = _CommonImplFixedSize;
using _SimdImpl = _SimdImplFixedSize<_Np>;
using _MaskImpl = _MaskImplFixedSize<_Np>;
template <typename _Tp, bool = _S_is_valid_v<_Tp>>
struct __traits : _InvalidTraits
{
};
template <typename _Tp> struct __traits<_Tp, true>
{
using _IsValid = true_type;
using _SimdImpl = _SimdImplFixedSize<_Np>;
using _MaskImpl = _MaskImplFixedSize<_Np>;
using _SimdMember = __fixed_size_storage_t<_Tp, _Np>;
using _MaskMember = _SanitizedBitMask<_Np>;
static constexpr size_t _S_simd_align
= __next_power_of_2(_Np * sizeof(_Tp));
static constexpr size_t _S_mask_align = alignof(_MaskMember);
struct _SimdBase
{
_SimdBase(const _SimdBase&) {}
_SimdBase() = default;
explicit operator const _SimdMember &() const
{
return static_cast<const simd<_Tp, _Fixed>*>(this)->_M_data;
}
explicit operator std::array<_Tp, _Np>() const
{
std::array<_Tp, _Np> __r;
static_assert(sizeof(__r) <= sizeof(_SimdMember), "");
__builtin_memcpy(__r.data(), &static_cast<const _SimdMember&>(*this),
sizeof(__r));
return __r;
}
};
struct _MaskBase
{
};
struct _SimdCastType
{
_SimdCastType(const std::array<_Tp, _Np>&);
_SimdCastType(const _SimdMember& dd) : _M_data(dd) {}
explicit operator const _SimdMember &() const { return _M_data; }
private:
const _SimdMember& _M_data;
};
class _MaskCastType
{
_MaskCastType() = delete;
};
};
};
struct _CommonImplFixedSize
{
template <typename _Tp, typename... _As>
_GLIBCXX_SIMD_INTRINSIC static void
_S_store(const _SimdTuple<_Tp, _As...>& __x, void* __addr)
{
constexpr size_t _Np = _SimdTuple<_Tp, _As...>::_S_size();
__builtin_memcpy(__addr, &__x, _Np * sizeof(_Tp));
}
};
template <int _Np> struct _SimdImplFixedSize
{
using _MaskMember = _SanitizedBitMask<_Np>;
template <typename _Tp> using _SimdMember = __fixed_size_storage_t<_Tp, _Np>;
template <typename _Tp>
static constexpr std::size_t _S_tuple_size = _SimdMember<_Tp>::_S_tuple_size;
template <typename _Tp>
using _Simd = std::experimental::simd<_Tp, simd_abi::fixed_size<_Np>>;
template <typename _Tp> using _TypeTag = _Tp*;
template <typename _Tp>
static constexpr inline _SimdMember<_Tp> _S_broadcast(_Tp __x) noexcept
{
return _SimdMember<_Tp>::_S_generate([&](auto __meta) constexpr {
return __meta._S_broadcast(__x);
});
}
template <typename _Fp, typename _Tp>
static constexpr inline _SimdMember<_Tp> _S_generator(_Fp&& __gen,
_TypeTag<_Tp>)
{
return _SimdMember<_Tp>::_S_generate([&__gen](auto __meta) constexpr {
return __meta._S_generator(
[&](auto __i) constexpr {
return __i < _Np ? __gen(_SizeConstant<__meta._S_offset + __i>()) : 0;
},
_TypeTag<_Tp>());
});
}
template <typename _Tp, typename _Up>
static inline _SimdMember<_Tp> _S_load(const _Up* __mem,
_TypeTag<_Tp>) noexcept
{
return _SimdMember<_Tp>::_S_generate([&](auto __meta) {
return __meta._S_load(&__mem[__meta._S_offset], _TypeTag<_Tp>());
});
}
template <typename _Tp, typename... _As, typename _Up>
static inline _SimdTuple<_Tp, _As...>
_S_masked_load(const _SimdTuple<_Tp, _As...>& __old, const _MaskMember __bits,
const _Up* __mem) noexcept
{
auto __merge = __old;
__for_each(__merge, [&](auto __meta, auto& __native) {
if (__meta._S_submask(__bits).any())
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Warray-bounds"
__native = __meta._S_masked_load(__native, __meta._S_make_mask(__bits),
__mem + __meta._S_offset);
#pragma GCC diagnostic pop
});
return __merge;
}
template <typename _Tp, typename _Up>
static inline void _S_store(const _SimdMember<_Tp>& __v, _Up* __mem,
_TypeTag<_Tp>) noexcept
{
__for_each(__v, [&](auto __meta, auto __native) {
__meta._S_store(__native, &__mem[__meta._S_offset], _TypeTag<_Tp>());
});
}
template <typename _Tp, typename... _As, typename _Up>
static inline void _S_masked_store(const _SimdTuple<_Tp, _As...>& __v,
_Up* __mem,
const _MaskMember __bits) noexcept
{
__for_each(__v, [&](auto __meta, auto __native) {
if (__meta._S_submask(__bits).any())
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Warray-bounds"
__meta._S_masked_store(__native, __mem + __meta._S_offset,
__meta._S_make_mask(__bits));
#pragma GCC diagnostic pop
});
}
template <typename _Tp, typename... _As>
static inline _MaskMember
_S_negate(const _SimdTuple<_Tp, _As...>& __x) noexcept
{
_MaskMember __bits = 0;
__for_each(
__x, [&__bits](auto __meta, auto __native) constexpr {
__bits |= __meta._S_mask_to_shifted_ullong(__meta._S_negate(__native));
});
return __bits;
}
template <typename _Tp, typename _BinaryOperation>
static constexpr inline _Tp _S_reduce(const _Simd<_Tp>& __x,
const _BinaryOperation& __binary_op)
{
using _Tup = _SimdMember<_Tp>;
const _Tup& __tup = __data(__x);
if constexpr (_Tup::_S_tuple_size == 1)
return _Tup::_FirstAbi::_SimdImpl::_S_reduce(
__tup.template _M_simd_at<0>(), __binary_op);
else if constexpr (_Tup::_S_tuple_size == 2
&& _Tup::_S_size() > 2
&& _Tup::_SecondType::_S_size() == 1)
{
return __binary_op(simd<_Tp, simd_abi::scalar>(
reduce(__tup.template _M_simd_at<0>(),
__binary_op)),
__tup.template _M_simd_at<1>())[0];
}
else if constexpr (_Tup::_S_tuple_size == 2
&& _Tup::_S_size() > 4
&& _Tup::_SecondType::_S_size() == 2)
{
return __binary_op(
simd<_Tp, simd_abi::scalar>(
reduce(__tup.template _M_simd_at<0>(), __binary_op)),
simd<_Tp, simd_abi::scalar>(
reduce(__tup.template _M_simd_at<1>(), __binary_op)))[0];
}
else
{
const auto& __x2
= __call_with_n_evaluations<__div_roundup(_Tup::_S_tuple_size, 2)>(
[](auto __first_simd, auto... __remaining) {
if constexpr (sizeof...(__remaining) == 0)
return __first_simd;
else
{
using _Tup2
= _SimdTuple<_Tp, typename decltype(__first_simd)::abi_type,
typename decltype(__remaining)::abi_type...>;
return fixed_size_simd<_Tp, _Tup2::_S_size()>(
__private_init,
__make_simd_tuple(__first_simd, __remaining...));
}
},
[&](auto __i) {
auto __left = __tup.template _M_simd_at<2 * __i>();
if constexpr (2 * __i + 1 == _Tup::_S_tuple_size)
return __left;
else
{
auto __right = __tup.template _M_simd_at<2 * __i + 1>();
using _LT = decltype(__left);
using _RT = decltype(__right);
if constexpr (_LT::size() == _RT::size())
return __binary_op(__left, __right);
else
{
_GLIBCXX_SIMD_USE_CONSTEXPR_API
typename _LT::mask_type __k(
__private_init, [](auto __j) constexpr {
return __j < _RT::size();
});
_LT __ext_right = __left;
where(__k, __ext_right)
= __proposed::resizing_simd_cast<_LT>(__right);
where(__k, __left) = __binary_op(__left, __ext_right);
return __left;
}
}
});
return reduce(__x2, __binary_op);
}
}
template <typename _Tp, typename... _As>
static inline constexpr _SimdTuple<_Tp, _As...>
_S_min(const _SimdTuple<_Tp, _As...>& __a, const _SimdTuple<_Tp, _As...>& __b)
{
return __a._M_apply_per_chunk(
[](auto __impl, auto __aa, auto __bb) constexpr {
return __impl._S_min(__aa, __bb);
},
__b);
}
template <typename _Tp, typename... _As>
static inline constexpr _SimdTuple<_Tp, _As...>
_S_max(const _SimdTuple<_Tp, _As...>& __a, const _SimdTuple<_Tp, _As...>& __b)
{
return __a._M_apply_per_chunk(
[](auto __impl, auto __aa, auto __bb) constexpr {
return __impl._S_max(__aa, __bb);
},
__b);
}
template <typename _Tp, typename... _As>
static inline constexpr _SimdTuple<_Tp, _As...>
_S_complement(const _SimdTuple<_Tp, _As...>& __x) noexcept
{
return __x._M_apply_per_chunk([](auto __impl, auto __xx) constexpr {
return __impl._S_complement(__xx);
});
}
template <typename _Tp, typename... _As>
static inline constexpr _SimdTuple<_Tp, _As...>
_S_unary_minus(const _SimdTuple<_Tp, _As...>& __x) noexcept
{
return __x._M_apply_per_chunk([](auto __impl, auto __xx) constexpr {
return __impl._S_unary_minus(__xx);
});
}
#define _GLIBCXX_SIMD_FIXED_OP(name_,op_) \
template <typename _Tp, typename... _As> \
static inline constexpr _SimdTuple<_Tp, _As...> name_( \
const _SimdTuple<_Tp, _As...> __x, const _SimdTuple<_Tp, _As...> __y) \
{ \
return __x._M_apply_per_chunk( \
[](auto __impl, auto __xx, auto __yy) constexpr { \
return __impl.name_(__xx, __yy); \
}, \
__y); \
}
_GLIBCXX_SIMD_FIXED_OP(_S_plus, +)
_GLIBCXX_SIMD_FIXED_OP(_S_minus, -)
_GLIBCXX_SIMD_FIXED_OP(_S_multiplies, *)
_GLIBCXX_SIMD_FIXED_OP(_S_divides, /)
_GLIBCXX_SIMD_FIXED_OP(_S_modulus, %)
_GLIBCXX_SIMD_FIXED_OP(_S_bit_and, &)
_GLIBCXX_SIMD_FIXED_OP(_S_bit_or, |)
_GLIBCXX_SIMD_FIXED_OP(_S_bit_xor, ^)
_GLIBCXX_SIMD_FIXED_OP(_S_bit_shift_left, <<)
_GLIBCXX_SIMD_FIXED_OP(_S_bit_shift_right, >>)
#undef _GLIBCXX_SIMD_FIXED_OP
template <typename _Tp, typename... _As>
static inline constexpr _SimdTuple<_Tp, _As...>
_S_bit_shift_left(const _SimdTuple<_Tp, _As...>& __x, int __y)
{
return __x._M_apply_per_chunk([__y](auto __impl, auto __xx) constexpr {
return __impl._S_bit_shift_left(__xx, __y);
});
}
template <typename _Tp, typename... _As>
static inline constexpr _SimdTuple<_Tp, _As...>
_S_bit_shift_right(const _SimdTuple<_Tp, _As...>& __x, int __y)
{
return __x._M_apply_per_chunk([__y](auto __impl, auto __xx) constexpr {
return __impl._S_bit_shift_right(__xx, __y);
});
}
#define _GLIBCXX_SIMD_APPLY_ON_TUPLE(_RetTp,__name) \
template <typename _Tp, typename... _As, typename... _More> \
static inline __fixed_size_storage_t<_RetTp, _Np> _S_##__name( \
const _SimdTuple<_Tp, _As...>& __x, const _More&... __more) \
{ \
if constexpr (sizeof...(_More) == 0) \
{ \
if constexpr (is_same_v<_Tp, _RetTp>) \
return __x._M_apply_per_chunk([](auto __impl, auto __xx) constexpr { \
using _V = typename decltype(__impl)::simd_type; \
return __data(__name(_V(__private_init, __xx))); \
}); \
else \
return __optimize_simd_tuple(__x.template _M_apply_r<_RetTp>( \
[](auto __impl, auto __xx) { return __impl._S_##__name(__xx); })); \
} \
else if constexpr ( \
is_same_v< \
_Tp, \
_RetTp> && (... && std::is_same_v<_SimdTuple<_Tp, _As...>, _More>) ) \
return __x._M_apply_per_chunk( \
[](auto __impl, auto __xx, auto... __pack) constexpr { \
using _V = typename decltype(__impl)::simd_type; \
return __data( \
__name(_V(__private_init, __xx), _V(__private_init, __pack)...)); \
}, \
__more...); \
else if constexpr (is_same_v<_Tp, _RetTp>) \
return __x._M_apply_per_chunk( \
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
static _SimdTuple<_Tp, _Abis...> _S_remquo(
const _SimdTuple<_Tp, _Abis...>& __x, const _SimdTuple<_Tp, _Abis...>& __y,
__fixed_size_storage_t<int, _SimdTuple<_Tp, _Abis...>::_S_size()>* __z)
{
return __x._M_apply_per_chunk(
[](auto __impl, const auto __xx, const auto __yy, auto& __zz) {
return __impl._S_remquo(__xx, __yy, &__zz);
},
__y, *__z);
}
template <typename _Tp, typename... _As>
static inline _SimdTuple<_Tp, _As...>
_S_frexp(const _SimdTuple<_Tp, _As...>& __x,
__fixed_size_storage_t<int, _Np>& __exp) noexcept
{
return __x._M_apply_per_chunk(
[](auto __impl, const auto& __a, auto& __b) {
return __data(
frexp(typename decltype(__impl)::simd_type(__private_init, __a),
__autocvt_to_simd(__b)));
},
__exp);
}
#define _GLIBCXX_SIMD_TEST_ON_TUPLE_(name_) \
template <typename _Tp, typename... _As> \
static inline _MaskMember _S_##name_( \
const _SimdTuple<_Tp, _As...>& __x) noexcept \
{ \
return _M_test([](auto __impl, \
auto __xx) { return __impl._S_##name_(__xx); }, \
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
_S_increment(_SimdTuple<_Ts...>& __x)
{
__for_each(
__x,
[](auto __meta, auto& native) constexpr { __meta._S_increment(native); });
}
template <typename... _Ts>
_GLIBCXX_SIMD_INTRINSIC static constexpr void
_S_decrement(_SimdTuple<_Ts...>& __x)
{
__for_each(
__x,
[](auto __meta, auto& native) constexpr { __meta._S_decrement(native); });
}
#define _GLIBCXX_SIMD_CMP_OPERATIONS(__cmp) \
template <typename _Tp, typename... _As> \
_GLIBCXX_SIMD_INTRINSIC constexpr static _MaskMember __cmp( \
const _SimdTuple<_Tp, _As...>& __x, const _SimdTuple<_Tp, _As...>& __y) \
{ \
return _M_test( \
[](auto __impl, auto __xx, auto __yy) constexpr { \
return __impl.__cmp(__xx, __yy); \
}, \
__x, __y); \
}
_GLIBCXX_SIMD_CMP_OPERATIONS(_S_equal_to)
_GLIBCXX_SIMD_CMP_OPERATIONS(_S_not_equal_to)
_GLIBCXX_SIMD_CMP_OPERATIONS(_S_less)
_GLIBCXX_SIMD_CMP_OPERATIONS(_S_less_equal)
_GLIBCXX_SIMD_CMP_OPERATIONS(_S_isless)
_GLIBCXX_SIMD_CMP_OPERATIONS(_S_islessequal)
_GLIBCXX_SIMD_CMP_OPERATIONS(_S_isgreater)
_GLIBCXX_SIMD_CMP_OPERATIONS(_S_isgreaterequal)
_GLIBCXX_SIMD_CMP_OPERATIONS(_S_islessgreater)
_GLIBCXX_SIMD_CMP_OPERATIONS(_S_isunordered)
#undef _GLIBCXX_SIMD_CMP_OPERATIONS
template <typename _Tp, typename... _As, typename _Up>
_GLIBCXX_SIMD_INTRINSIC static void _S_set(_SimdTuple<_Tp, _As...>& __v,
int __i, _Up&& __x) noexcept
{
__v._M_set(__i, static_cast<_Up&&>(__x));
}
template <typename _Tp, typename... _As>
_GLIBCXX_SIMD_INTRINSIC static void
_S_masked_assign(const _MaskMember __bits, _SimdTuple<_Tp, _As...>& __lhs,
const __id<_SimdTuple<_Tp, _As...>>& __rhs)
{
__for_each(
__lhs,
__rhs, [&](auto __meta, auto& __native_lhs, auto __native_rhs) constexpr {
__meta._S_masked_assign(__meta._S_make_mask(__bits), __native_lhs,
__native_rhs);
});
}
template <typename _Tp, typename... _As>
_GLIBCXX_SIMD_INTRINSIC static void
_S_masked_assign(const _MaskMember __bits, _SimdTuple<_Tp, _As...>& __lhs,
const __id<_Tp> __rhs)
{
__for_each(
__lhs, [&](auto __meta, auto& __native_lhs) constexpr {
__meta._S_masked_assign(__meta._S_make_mask(__bits), __native_lhs,
__rhs);
});
}
template <typename _Op, typename _Tp, typename... _As>
static inline void
_S_masked_cassign(const _MaskMember __bits, _SimdTuple<_Tp, _As...>& __lhs,
const _SimdTuple<_Tp, _As...>& __rhs, _Op __op)
{
__for_each(
__lhs,
__rhs, [&](auto __meta, auto& __native_lhs, auto __native_rhs) constexpr {
__meta.template _S_masked_cassign(__meta._S_make_mask(__bits),
__native_lhs, __native_rhs, __op);
});
}
template <typename _Op, typename _Tp, typename... _As>
static inline void _S_masked_cassign(const _MaskMember __bits,
_SimdTuple<_Tp, _As...>& __lhs,
const _Tp& __rhs, _Op __op)
{
__for_each(
__lhs, [&](auto __meta, auto& __native_lhs) constexpr {
__meta.template _S_masked_cassign(__meta._S_make_mask(__bits),
__native_lhs, __rhs, __op);
});
}
template <template <typename> class _Op, typename _Tp, typename... _As>
static inline _SimdTuple<_Tp, _As...>
_S_masked_unary(const _MaskMember __bits,
const _SimdTuple<_Tp, _As...> __v)
{
return __v._M_apply_wrapped([&__bits](auto __meta,
auto __native) constexpr {
return __meta.template _S_masked_unary<_Op>(__meta._S_make_mask(__bits),
__native);
});
}
};
template <int _Np> struct _MaskImplFixedSize
{
static_assert(sizeof(_ULLong) * __CHAR_BIT__ >= _Np,
"The fixed_size implementation relies on one "
"_ULLong being able to store all boolean "
"elements.");
using _Abi = simd_abi::fixed_size<_Np>;
template <typename _Tp>
using _FirstAbi = typename __fixed_size_storage_t<_Tp, _Np>::_FirstAbi;
using _MaskMember = _SanitizedBitMask<_Np>;
template <typename _Tp> using _TypeTag = _Tp*;
template <typename>
_GLIBCXX_SIMD_INTRINSIC static constexpr _MaskMember _S_broadcast(bool __x)
{
return __x ? ~_MaskMember() : _MaskMember();
}
template <typename>
_GLIBCXX_SIMD_INTRINSIC static constexpr _MaskMember
_S_load(const bool* __mem)
{
using _Ip = __int_for_sizeof_t<bool>;
const simd<_Ip, _Abi> __bools(reinterpret_cast<const __may_alias<_Ip>*>(
__mem),
element_aligned);
return __data(__bools != 0);
}
template <bool _Sanitized>
_GLIBCXX_SIMD_INTRINSIC static constexpr _SanitizedBitMask<_Np>
_S_to_bits(_BitMask<_Np, _Sanitized> __x)
{
if constexpr (_Sanitized)
return __x;
else
return __x._M_sanitized();
}
template <typename _Tp, typename _Up, typename _UAbi>
_GLIBCXX_SIMD_INTRINSIC static constexpr _MaskMember
_S_convert(simd_mask<_Up, _UAbi> __x)
{
return _UAbi::_MaskImpl::_S_to_bits(__data(__x))
.template _M_extract<0, _Np>();
}
template <typename _Tp>
_GLIBCXX_SIMD_INTRINSIC static _MaskMember
_S_from_bitmask(_MaskMember __bits, _TypeTag<_Tp>) noexcept
{
return __bits;
}
static inline _MaskMember _S_load(const bool* __mem) noexcept
{
_ULLong __r = 0;
using _Vs = __fixed_size_storage_t<_UChar, _Np>;
__for_each(_Vs{}, [&](auto __meta, auto) {
__r |= __meta._S_mask_to_shifted_ullong(
__meta._S_mask_impl._S_load(&__mem[__meta._S_offset],
_SizeConstant<__meta._S_size()>()));
});
return __r;
}
static inline _MaskMember _S_masked_load(_MaskMember __merge,
_MaskMember __mask,
const bool* __mem) noexcept
{
_BitOps::_S_bit_iteration(__mask.to_ullong(),
[&](auto __i) { __merge.set(__i, __mem[__i]); });
return __merge;
}
static inline void _S_store(const _MaskMember __bitmask, bool* __mem) noexcept
{
if constexpr (_Np == 1)
__mem[0] = __bitmask[0];
else
_FirstAbi<_UChar>::_CommonImpl::_S_store_bool_array(__bitmask, __mem);
}
static inline void _S_masked_store(const _MaskMember __v, bool* __mem,
const _MaskMember __k) noexcept
{
_BitOps::_S_bit_iteration(__k, [&](auto __i) { __mem[__i] = __v[__i]; });
}
_GLIBCXX_SIMD_INTRINSIC static _MaskMember
_S_logical_and(const _MaskMember& __x, const _MaskMember& __y) noexcept
{
return __x & __y;
}
_GLIBCXX_SIMD_INTRINSIC static _MaskMember
_S_logical_or(const _MaskMember& __x, const _MaskMember& __y) noexcept
{
return __x | __y;
}
_GLIBCXX_SIMD_INTRINSIC static constexpr _MaskMember
_S_bit_not(const _MaskMember& __x) noexcept
{
return ~__x;
}
_GLIBCXX_SIMD_INTRINSIC static _MaskMember
_S_bit_and(const _MaskMember& __x, const _MaskMember& __y) noexcept
{
return __x & __y;
}
_GLIBCXX_SIMD_INTRINSIC static _MaskMember
_S_bit_or(const _MaskMember& __x, const _MaskMember& __y) noexcept
{
return __x | __y;
}
_GLIBCXX_SIMD_INTRINSIC static _MaskMember
_S_bit_xor(const _MaskMember& __x, const _MaskMember& __y) noexcept
{
return __x ^ __y;
}
_GLIBCXX_SIMD_INTRINSIC static void _S_set(_MaskMember& __k, int __i,
bool __x) noexcept
{
__k.set(__i, __x);
}
_GLIBCXX_SIMD_INTRINSIC static void _S_masked_assign(const _MaskMember __k,
_MaskMember& __lhs,
const _MaskMember __rhs)
{
__lhs = (__lhs & ~__k) | (__rhs & __k);
}
_GLIBCXX_SIMD_INTRINSIC static void
_S_masked_assign(const _MaskMember __k, _MaskMember& __lhs, const bool __rhs)
{
if (__rhs)
{
__lhs |= __k;
}
else
{
__lhs &= ~__k;
}
}
template <typename _Tp>
_GLIBCXX_SIMD_INTRINSIC static bool _S_all_of(simd_mask<_Tp, _Abi> __k)
{
return __data(__k).all();
}
template <typename _Tp>
_GLIBCXX_SIMD_INTRINSIC static bool _S_any_of(simd_mask<_Tp, _Abi> __k)
{
return __data(__k).any();
}
template <typename _Tp>
_GLIBCXX_SIMD_INTRINSIC static bool _S_none_of(simd_mask<_Tp, _Abi> __k)
{
return __data(__k).none();
}
template <typename _Tp>
_GLIBCXX_SIMD_INTRINSIC static bool
_S_some_of([[maybe_unused]] simd_mask<_Tp, _Abi> __k)
{
if constexpr (_Np == 1)
return false;
else
return __data(__k).any() && !__data(__k).all();
}
template <typename _Tp>
_GLIBCXX_SIMD_INTRINSIC static int _S_popcount(simd_mask<_Tp, _Abi> __k)
{
return __data(__k).count();
}
template <typename _Tp>
_GLIBCXX_SIMD_INTRINSIC static int _S_find_first_set(simd_mask<_Tp, _Abi> __k)
{
return _BitOps::_S_firstbit(__data(__k).to_ullong());
}
template <typename _Tp>
_GLIBCXX_SIMD_INTRINSIC static int _S_find_last_set(simd_mask<_Tp, _Abi> __k)
{
return _BitOps::_S_lastbit(__data(__k).to_ullong());
}
};
_GLIBCXX_SIMD_END_NAMESPACE
#endif
#endif
#ifndef _GLIBCXX_EXPERIMENTAL_SIMD_SCALAR_H_
#define _GLIBCXX_EXPERIMENTAL_SIMD_SCALAR_H_ 
#if __cplusplus >= 201703L
#include <cmath>
_GLIBCXX_SIMD_BEGIN_NAMESPACE
template <typename _Tp>
_GLIBCXX_SIMD_INTRINSIC constexpr decltype(auto)
__promote_preserving_unsigned(const _Tp& __x)
{
if constexpr (std::is_signed_v<decltype(+__x)> && std::is_unsigned_v<_Tp>)
return static_cast<unsigned int>(__x);
else
return __x;
}
struct _CommonImplScalar;
struct _CommonImplBuiltin;
struct _SimdImplScalar;
struct _MaskImplScalar;
struct simd_abi::_Scalar
{
template <typename _Tp> static constexpr size_t _S_size = 1;
template <typename _Tp> static constexpr size_t _S_full_size = 1;
template <typename _Tp> static constexpr bool _S_is_partial = false;
struct _IsValidAbiTag : true_type
{
};
template <typename _Tp> struct _IsValidSizeFor : true_type
{
};
template <typename _Tp> struct _IsValid : __is_vectorizable<_Tp>
{
};
template <typename _Tp>
static constexpr bool _S_is_valid_v = _IsValid<_Tp>::value;
_GLIBCXX_SIMD_INTRINSIC static constexpr bool _S_masked(bool __x)
{
return __x;
}
using _CommonImpl = _CommonImplScalar;
using _SimdImpl = _SimdImplScalar;
using _MaskImpl = _MaskImplScalar;
template <typename _Tp, bool = _S_is_valid_v<_Tp>>
struct __traits : _InvalidTraits
{
};
template <typename _Tp> struct __traits<_Tp, true>
{
using _IsValid = true_type;
using _SimdImpl = _SimdImplScalar;
using _MaskImpl = _MaskImplScalar;
using _SimdMember = _Tp;
using _MaskMember = bool;
static constexpr size_t _S_simd_align = alignof(_SimdMember);
static constexpr size_t _S_mask_align = alignof(_MaskMember);
struct _SimdCastType
{
_SimdCastType() = delete;
};
struct _MaskCastType
{
_MaskCastType() = delete;
};
struct _SimdBase
{
};
struct _MaskBase
{
};
};
};
struct _CommonImplScalar
{
template <typename _Tp>
_GLIBCXX_SIMD_INTRINSIC static void _S_store(_Tp __x, void* __addr)
{
__builtin_memcpy(__addr, &__x, sizeof(_Tp));
}
template <size_t _Np, bool _Sanitized>
_GLIBCXX_SIMD_INTRINSIC static constexpr void
_S_store_bool_array(_BitMask<_Np, _Sanitized> __x, bool* __mem)
{
__make_dependent_t<decltype(__x), _CommonImplBuiltin>::_S_store_bool_array(
__x, __mem);
}
};
struct _SimdImplScalar
{
using abi_type = simd_abi::scalar;
template <typename _Tp> using _TypeTag = _Tp*;
template <typename _Tp>
_GLIBCXX_SIMD_INTRINSIC static constexpr _Tp _S_broadcast(_Tp __x) noexcept
{
return __x;
}
template <typename _Fp, typename _Tp>
_GLIBCXX_SIMD_INTRINSIC static constexpr _Tp _S_generator(_Fp&& __gen,
_TypeTag<_Tp>)
{
return __gen(_SizeConstant<0>());
}
template <typename _Tp, typename _Up>
_GLIBCXX_SIMD_INTRINSIC static _Tp _S_load(const _Up* __mem,
_TypeTag<_Tp>) noexcept
{
return static_cast<_Tp>(__mem[0]);
}
template <typename _Tp, typename _Up>
static inline _Tp _S_masked_load(_Tp __merge, bool __k,
const _Up* __mem) noexcept
{
if (__k)
__merge = static_cast<_Tp>(__mem[0]);
return __merge;
}
template <typename _Tp, typename _Up>
static inline void _S_store(_Tp __v, _Up* __mem, _TypeTag<_Tp>) noexcept
{
__mem[0] = static_cast<_Up>(__v);
}
template <typename _Tp, typename _Up>
static inline void _S_masked_store(const _Tp __v, _Up* __mem,
const bool __k) noexcept
{
if (__k)
__mem[0] = __v;
}
template <typename _Tp>
static constexpr inline bool _S_negate(_Tp __x) noexcept
{
return !__x;
}
template <typename _Tp, typename _BinaryOperation>
static constexpr inline _Tp _S_reduce(const simd<_Tp, simd_abi::scalar>& __x,
_BinaryOperation&)
{
return __x._M_data;
}
template <typename _Tp>
static constexpr inline _Tp _S_min(const _Tp __a, const _Tp __b)
{
return std::min(__a, __b);
}
template <typename _Tp>
static constexpr inline _Tp _S_max(const _Tp __a, const _Tp __b)
{
return std::max(__a, __b);
}
template <typename _Tp>
static constexpr inline _Tp _S_complement(_Tp __x) noexcept
{
return static_cast<_Tp>(~__x);
}
template <typename _Tp>
static constexpr inline _Tp _S_unary_minus(_Tp __x) noexcept
{
return static_cast<_Tp>(-__x);
}
template <typename _Tp> static constexpr inline _Tp _S_plus(_Tp __x, _Tp __y)
{
return static_cast<_Tp>(__promote_preserving_unsigned(__x)
+ __promote_preserving_unsigned(__y));
}
template <typename _Tp> static constexpr inline _Tp _S_minus(_Tp __x, _Tp __y)
{
return static_cast<_Tp>(__promote_preserving_unsigned(__x)
- __promote_preserving_unsigned(__y));
}
template <typename _Tp>
static constexpr inline _Tp _S_multiplies(_Tp __x, _Tp __y)
{
return static_cast<_Tp>(__promote_preserving_unsigned(__x)
* __promote_preserving_unsigned(__y));
}
template <typename _Tp>
static constexpr inline _Tp _S_divides(_Tp __x, _Tp __y)
{
return static_cast<_Tp>(__promote_preserving_unsigned(__x)
/ __promote_preserving_unsigned(__y));
}
template <typename _Tp>
static constexpr inline _Tp _S_modulus(_Tp __x, _Tp __y)
{
return static_cast<_Tp>(__promote_preserving_unsigned(__x)
% __promote_preserving_unsigned(__y));
}
template <typename _Tp>
static constexpr inline _Tp _S_bit_and(_Tp __x, _Tp __y)
{
if constexpr (is_floating_point_v<_Tp>)
{
using _Ip = __int_for_sizeof_t<_Tp>;
return __bit_cast<_Tp>(__bit_cast<_Ip>(__x) & __bit_cast<_Ip>(__y));
}
else
return static_cast<_Tp>(__promote_preserving_unsigned(__x)
& __promote_preserving_unsigned(__y));
}
template <typename _Tp> static constexpr inline _Tp _S_bit_or(_Tp __x, _Tp __y)
{
if constexpr (is_floating_point_v<_Tp>)
{
using _Ip = __int_for_sizeof_t<_Tp>;
return __bit_cast<_Tp>(__bit_cast<_Ip>(__x) | __bit_cast<_Ip>(__y));
}
else
return static_cast<_Tp>(__promote_preserving_unsigned(__x)
| __promote_preserving_unsigned(__y));
}
template <typename _Tp>
static constexpr inline _Tp _S_bit_xor(_Tp __x, _Tp __y)
{
if constexpr (is_floating_point_v<_Tp>)
{
using _Ip = __int_for_sizeof_t<_Tp>;
return __bit_cast<_Tp>(__bit_cast<_Ip>(__x) ^ __bit_cast<_Ip>(__y));
}
else
return static_cast<_Tp>(__promote_preserving_unsigned(__x)
^ __promote_preserving_unsigned(__y));
}
template <typename _Tp>
static constexpr inline _Tp _S_bit_shift_left(_Tp __x, int __y)
{
return static_cast<_Tp>(__promote_preserving_unsigned(__x) << __y);
}
template <typename _Tp>
static constexpr inline _Tp _S_bit_shift_right(_Tp __x, int __y)
{
return static_cast<_Tp>(__promote_preserving_unsigned(__x) >> __y);
}
template <typename _Tp> using _ST = _SimdTuple<_Tp, simd_abi::scalar>;
template <typename _Tp> _GLIBCXX_SIMD_INTRINSIC static _Tp _S_acos(_Tp __x)
{
return std::acos(__x);
}
template <typename _Tp> _GLIBCXX_SIMD_INTRINSIC static _Tp _S_asin(_Tp __x)
{
return std::asin(__x);
}
template <typename _Tp> _GLIBCXX_SIMD_INTRINSIC static _Tp _S_atan(_Tp __x)
{
return std::atan(__x);
}
template <typename _Tp> _GLIBCXX_SIMD_INTRINSIC static _Tp _S_cos(_Tp __x)
{
return std::cos(__x);
}
template <typename _Tp> _GLIBCXX_SIMD_INTRINSIC static _Tp _S_sin(_Tp __x)
{
return std::sin(__x);
}
template <typename _Tp> _GLIBCXX_SIMD_INTRINSIC static _Tp _S_tan(_Tp __x)
{
return std::tan(__x);
}
template <typename _Tp> _GLIBCXX_SIMD_INTRINSIC static _Tp _S_acosh(_Tp __x)
{
return std::acosh(__x);
}
template <typename _Tp> _GLIBCXX_SIMD_INTRINSIC static _Tp _S_asinh(_Tp __x)
{
return std::asinh(__x);
}
template <typename _Tp> _GLIBCXX_SIMD_INTRINSIC static _Tp _S_atanh(_Tp __x)
{
return std::atanh(__x);
}
template <typename _Tp> _GLIBCXX_SIMD_INTRINSIC static _Tp _S_cosh(_Tp __x)
{
return std::cosh(__x);
}
template <typename _Tp> _GLIBCXX_SIMD_INTRINSIC static _Tp _S_sinh(_Tp __x)
{
return std::sinh(__x);
}
template <typename _Tp> _GLIBCXX_SIMD_INTRINSIC static _Tp _S_tanh(_Tp __x)
{
return std::tanh(__x);
}
template <typename _Tp>
_GLIBCXX_SIMD_INTRINSIC static _Tp _S_atan2(_Tp __x, _Tp __y)
{
return std::atan2(__x, __y);
}
template <typename _Tp> _GLIBCXX_SIMD_INTRINSIC static _Tp _S_exp(_Tp __x)
{
return std::exp(__x);
}
template <typename _Tp> _GLIBCXX_SIMD_INTRINSIC static _Tp _S_exp2(_Tp __x)
{
return std::exp2(__x);
}
template <typename _Tp> _GLIBCXX_SIMD_INTRINSIC static _Tp _S_expm1(_Tp __x)
{
return std::expm1(__x);
}
template <typename _Tp> _GLIBCXX_SIMD_INTRINSIC static _Tp _S_log(_Tp __x)
{
return std::log(__x);
}
template <typename _Tp> _GLIBCXX_SIMD_INTRINSIC static _Tp _S_log10(_Tp __x)
{
return std::log10(__x);
}
template <typename _Tp> _GLIBCXX_SIMD_INTRINSIC static _Tp _S_log1p(_Tp __x)
{
return std::log1p(__x);
}
template <typename _Tp> _GLIBCXX_SIMD_INTRINSIC static _Tp _S_log2(_Tp __x)
{
return std::log2(__x);
}
template <typename _Tp> _GLIBCXX_SIMD_INTRINSIC static _Tp _S_logb(_Tp __x)
{
return std::logb(__x);
}
template <typename _Tp>
_GLIBCXX_SIMD_INTRINSIC static _ST<int> _S_ilogb(_Tp __x)
{
return {std::ilogb(__x)};
}
template <typename _Tp>
_GLIBCXX_SIMD_INTRINSIC static _Tp _S_pow(_Tp __x, _Tp __y)
{
return std::pow(__x, __y);
}
template <typename _Tp> _GLIBCXX_SIMD_INTRINSIC static _Tp _S_abs(_Tp __x)
{
return std::abs(__x);
}
template <typename _Tp> _GLIBCXX_SIMD_INTRINSIC static _Tp _S_fabs(_Tp __x)
{
return std::fabs(__x);
}
template <typename _Tp> _GLIBCXX_SIMD_INTRINSIC static _Tp _S_sqrt(_Tp __x)
{
return std::sqrt(__x);
}
template <typename _Tp> _GLIBCXX_SIMD_INTRINSIC static _Tp _S_cbrt(_Tp __x)
{
return std::cbrt(__x);
}
template <typename _Tp> _GLIBCXX_SIMD_INTRINSIC static _Tp _S_erf(_Tp __x)
{
return std::erf(__x);
}
template <typename _Tp> _GLIBCXX_SIMD_INTRINSIC static _Tp _S_erfc(_Tp __x)
{
return std::erfc(__x);
}
template <typename _Tp> _GLIBCXX_SIMD_INTRINSIC static _Tp _S_lgamma(_Tp __x)
{
return std::lgamma(__x);
}
template <typename _Tp> _GLIBCXX_SIMD_INTRINSIC static _Tp _S_tgamma(_Tp __x)
{
return std::tgamma(__x);
}
template <typename _Tp> _GLIBCXX_SIMD_INTRINSIC static _Tp _S_trunc(_Tp __x)
{
return std::trunc(__x);
}
template <typename _Tp> _GLIBCXX_SIMD_INTRINSIC static _Tp _S_floor(_Tp __x)
{
return std::floor(__x);
}
template <typename _Tp> _GLIBCXX_SIMD_INTRINSIC static _Tp _S_ceil(_Tp __x)
{
return std::ceil(__x);
}
template <typename _Tp>
_GLIBCXX_SIMD_INTRINSIC static _Tp _S_nearbyint(_Tp __x)
{
return std::nearbyint(__x);
}
template <typename _Tp> _GLIBCXX_SIMD_INTRINSIC static _Tp _S_rint(_Tp __x)
{
return std::rint(__x);
}
template <typename _Tp>
_GLIBCXX_SIMD_INTRINSIC static _ST<long> _S_lrint(_Tp __x)
{
return {std::lrint(__x)};
}
template <typename _Tp>
_GLIBCXX_SIMD_INTRINSIC static _ST<long long> _S_llrint(_Tp __x)
{
return {std::llrint(__x)};
}
template <typename _Tp> _GLIBCXX_SIMD_INTRINSIC static _Tp _S_round(_Tp __x)
{
return std::round(__x);
}
template <typename _Tp>
_GLIBCXX_SIMD_INTRINSIC static _ST<long> _S_lround(_Tp __x)
{
return {std::lround(__x)};
}
template <typename _Tp>
_GLIBCXX_SIMD_INTRINSIC static _ST<long long> _S_llround(_Tp __x)
{
return {std::llround(__x)};
}
template <typename _Tp>
_GLIBCXX_SIMD_INTRINSIC static _Tp _S_ldexp(_Tp __x, _ST<int> __y)
{
return std::ldexp(__x, __y.first);
}
template <typename _Tp>
_GLIBCXX_SIMD_INTRINSIC static _Tp _S_scalbn(_Tp __x, _ST<int> __y)
{
return std::scalbn(__x, __y.first);
}
template <typename _Tp>
_GLIBCXX_SIMD_INTRINSIC static _Tp _S_scalbln(_Tp __x, _ST<long> __y)
{
return std::scalbln(__x, __y.first);
}
template <typename _Tp>
_GLIBCXX_SIMD_INTRINSIC static _Tp _S_fmod(_Tp __x, _Tp __y)
{
return std::fmod(__x, __y);
}
template <typename _Tp>
_GLIBCXX_SIMD_INTRINSIC static _Tp _S_remainder(_Tp __x, _Tp __y)
{
return std::remainder(__x, __y);
}
template <typename _Tp>
_GLIBCXX_SIMD_INTRINSIC static _Tp _S_nextafter(_Tp __x, _Tp __y)
{
return std::nextafter(__x, __y);
}
template <typename _Tp>
_GLIBCXX_SIMD_INTRINSIC static _Tp _S_fdim(_Tp __x, _Tp __y)
{
return std::fdim(__x, __y);
}
template <typename _Tp>
_GLIBCXX_SIMD_INTRINSIC static _Tp _S_fmax(_Tp __x, _Tp __y)
{
return std::fmax(__x, __y);
}
template <typename _Tp>
_GLIBCXX_SIMD_INTRINSIC static _Tp _S_fmin(_Tp __x, _Tp __y)
{
return std::fmin(__x, __y);
}
template <typename _Tp>
_GLIBCXX_SIMD_INTRINSIC static _Tp _S_fma(_Tp __x, _Tp __y, _Tp __z)
{
return std::fma(__x, __y, __z);
}
template <typename _Tp>
_GLIBCXX_SIMD_INTRINSIC static _Tp _S_remquo(_Tp __x, _Tp __y, _ST<int>* __z)
{
return std::remquo(__x, __y, &__z->first);
}
template <typename _Tp>
_GLIBCXX_SIMD_INTRINSIC constexpr static _ST<int> _S_fpclassify(_Tp __x)
{
return {std::fpclassify(__x)};
}
template <typename _Tp>
_GLIBCXX_SIMD_INTRINSIC constexpr static bool _S_isfinite(_Tp __x)
{
return std::isfinite(__x);
}
template <typename _Tp>
_GLIBCXX_SIMD_INTRINSIC constexpr static bool _S_isinf(_Tp __x)
{
return std::isinf(__x);
}
template <typename _Tp>
_GLIBCXX_SIMD_INTRINSIC constexpr static bool _S_isnan(_Tp __x)
{
return std::isnan(__x);
}
template <typename _Tp>
_GLIBCXX_SIMD_INTRINSIC constexpr static bool _S_isnormal(_Tp __x)
{
return std::isnormal(__x);
}
template <typename _Tp>
_GLIBCXX_SIMD_INTRINSIC constexpr static bool _S_signbit(_Tp __x)
{
return std::signbit(__x);
}
template <typename _Tp>
_GLIBCXX_SIMD_INTRINSIC constexpr static bool _S_isgreater(_Tp __x, _Tp __y)
{
return std::isgreater(__x, __y);
}
template <typename _Tp>
_GLIBCXX_SIMD_INTRINSIC constexpr static bool _S_isgreaterequal(_Tp __x,
_Tp __y)
{
return std::isgreaterequal(__x, __y);
}
template <typename _Tp>
_GLIBCXX_SIMD_INTRINSIC constexpr static bool _S_isless(_Tp __x, _Tp __y)
{
return std::isless(__x, __y);
}
template <typename _Tp>
_GLIBCXX_SIMD_INTRINSIC constexpr static bool _S_islessequal(_Tp __x, _Tp __y)
{
return std::islessequal(__x, __y);
}
template <typename _Tp>
_GLIBCXX_SIMD_INTRINSIC constexpr static bool _S_islessgreater(_Tp __x,
_Tp __y)
{
return std::islessgreater(__x, __y);
}
template <typename _Tp>
_GLIBCXX_SIMD_INTRINSIC constexpr static bool _S_isunordered(_Tp __x, _Tp __y)
{
return std::isunordered(__x, __y);
}
template <typename _Tp> constexpr static inline void _S_increment(_Tp& __x)
{
++__x;
}
template <typename _Tp> constexpr static inline void _S_decrement(_Tp& __x)
{
--__x;
}
template <typename _Tp>
_GLIBCXX_SIMD_INTRINSIC constexpr static bool _S_equal_to(_Tp __x, _Tp __y)
{
return __x == __y;
}
template <typename _Tp>
_GLIBCXX_SIMD_INTRINSIC constexpr static bool _S_not_equal_to(_Tp __x, _Tp __y)
{
return __x != __y;
}
template <typename _Tp>
_GLIBCXX_SIMD_INTRINSIC constexpr static bool _S_less(_Tp __x, _Tp __y)
{
return __x < __y;
}
template <typename _Tp>
_GLIBCXX_SIMD_INTRINSIC constexpr static bool _S_less_equal(_Tp __x, _Tp __y)
{
return __x <= __y;
}
template <typename _Tp, typename _Up>
constexpr static void _S_set(_Tp& __v, [[maybe_unused]] int __i,
_Up&& __x) noexcept
{
_GLIBCXX_DEBUG_ASSERT(__i == 0);
__v = static_cast<_Up&&>(__x);
}
template <typename _Tp>
_GLIBCXX_SIMD_INTRINSIC constexpr static void
_S_masked_assign(bool __k, _Tp& __lhs, _Tp __rhs)
{
if (__k)
__lhs = __rhs;
}
template <typename _Op, typename _Tp>
_GLIBCXX_SIMD_INTRINSIC constexpr static void
_S_masked_cassign(const bool __k, _Tp& __lhs, const _Tp __rhs, _Op __op)
{
if (__k)
__lhs = __op(_SimdImplScalar{}, __lhs, __rhs);
}
template <template <typename> class _Op, typename _Tp>
_GLIBCXX_SIMD_INTRINSIC constexpr static _Tp _S_masked_unary(const bool __k,
const _Tp __v)
{
return static_cast<_Tp>(__k ? _Op<_Tp>{}(__v) : __v);
}
};
struct _MaskImplScalar
{
template <typename _Tp> using _TypeTag = _Tp*;
template <typename>
_GLIBCXX_SIMD_INTRINSIC static constexpr bool _S_broadcast(bool __x)
{
return __x;
}
template <typename>
_GLIBCXX_SIMD_INTRINSIC static constexpr bool _S_load(const bool* __mem)
{
return __mem[0];
}
_GLIBCXX_SIMD_INTRINSIC static constexpr _SanitizedBitMask<1>
_S_to_bits(bool __x)
{
return __x;
}
template <typename, bool _Sanitized>
_GLIBCXX_SIMD_INTRINSIC static constexpr bool
_S_convert(_BitMask<1, _Sanitized> __x)
{
return __x[0];
}
template <typename, typename _Up, typename _UAbi>
_GLIBCXX_SIMD_INTRINSIC static constexpr bool
_S_convert(simd_mask<_Up, _UAbi> __x)
{
return __x[0];
}
template <typename _Tp>
_GLIBCXX_SIMD_INTRINSIC constexpr static bool
_S_from_bitmask(_SanitizedBitMask<1> __bits, _TypeTag<_Tp>) noexcept
{
return __bits[0];
}
_GLIBCXX_SIMD_INTRINSIC constexpr static bool
_S_masked_load(bool __merge, bool __mask, const bool* __mem) noexcept
{
if (__mask)
__merge = __mem[0];
return __merge;
}
_GLIBCXX_SIMD_INTRINSIC static void _S_store(bool __v, bool* __mem) noexcept
{
__mem[0] = __v;
}
_GLIBCXX_SIMD_INTRINSIC static void
_S_masked_store(const bool __v, bool* __mem, const bool __k) noexcept
{
if (__k)
__mem[0] = __v;
}
static constexpr bool _S_logical_and(bool __x, bool __y)
{
return __x && __y;
}
static constexpr bool _S_logical_or(bool __x, bool __y) { return __x || __y; }
static constexpr bool _S_bit_not(bool __x) { return !__x; }
static constexpr bool _S_bit_and(bool __x, bool __y) { return __x && __y; }
static constexpr bool _S_bit_or(bool __x, bool __y) { return __x || __y; }
static constexpr bool _S_bit_xor(bool __x, bool __y) { return __x != __y; }
constexpr static void _S_set(bool& __k, [[maybe_unused]] int __i,
bool __x) noexcept
{
_GLIBCXX_DEBUG_ASSERT(__i == 0);
__k = __x;
}
_GLIBCXX_SIMD_INTRINSIC static void _S_masked_assign(bool __k, bool& __lhs,
bool __rhs)
{
if (__k)
__lhs = __rhs;
}
template <typename _Tp, typename _Abi>
_GLIBCXX_SIMD_INTRINSIC constexpr static bool
_S_all_of(simd_mask<_Tp, _Abi> __k)
{
return __k._M_data;
}
template <typename _Tp, typename _Abi>
_GLIBCXX_SIMD_INTRINSIC constexpr static bool
_S_any_of(simd_mask<_Tp, _Abi> __k)
{
return __k._M_data;
}
template <typename _Tp, typename _Abi>
_GLIBCXX_SIMD_INTRINSIC constexpr static bool
_S_none_of(simd_mask<_Tp, _Abi> __k)
{
return !__k._M_data;
}
template <typename _Tp, typename _Abi>
_GLIBCXX_SIMD_INTRINSIC constexpr static bool _S_some_of(simd_mask<_Tp, _Abi>)
{
return false;
}
template <typename _Tp, typename _Abi>
_GLIBCXX_SIMD_INTRINSIC constexpr static int
_S_popcount(simd_mask<_Tp, _Abi> __k)
{
return __k._M_data;
}
template <typename _Tp, typename _Abi>
_GLIBCXX_SIMD_INTRINSIC constexpr static int
_S_find_first_set(simd_mask<_Tp, _Abi>)
{
return 0;
}
template <typename _Tp, typename _Abi>
_GLIBCXX_SIMD_INTRINSIC constexpr static int
_S_find_last_set(simd_mask<_Tp, _Abi>)
{
return 0;
}
};
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
template <typename _V>
static inline _GLIBCXX_SIMD_USE_CONSTEXPR _V _S_allbits
= reinterpret_cast<_V>(~__vector_type_t<char, sizeof(_V) / sizeof(char)>());
template <typename _V, typename = _VectorTraits<_V>>
static inline _GLIBCXX_SIMD_USE_CONSTEXPR _V _S_signmask
= __xor(_V() + 1, _V() - 1);
template <typename _V, typename = _VectorTraits<_V>>
static inline _GLIBCXX_SIMD_USE_CONSTEXPR _V _S_absmask
= __andnot(_S_signmask<_V>, _S_allbits<_V>);
template <int... _Indices, typename _Tp, typename _TVT = _VectorTraits<_Tp>>
_Tp
__vector_permute(_Tp __x)
{
static_assert(sizeof...(_Indices) == _TVT::_S_full_size);
return __make_vector<typename _TVT::value_type>(
(_Indices == -1 ? 0 : __x[_Indices == -1 ? 0 : _Indices])...);
}
template <int... _Indices, typename _Tp, typename _TVT = _VectorTraits<_Tp>>
_Tp
__vector_shuffle(_Tp __x, _Tp __y)
{
return _Tp{(_Indices == -1 ? 0
: _Indices < _TVT::_S_full_size
? __x[_Indices]
: __y[_Indices - _TVT::_S_full_size])...};
}
template <typename _Tp, typename... _Args>
_GLIBCXX_SIMD_INTRINSIC constexpr _SimdWrapper<_Tp, sizeof...(_Args)>
__make_wrapper(const _Args&... __args)
{
return __make_vector<_Tp>(__args...);
}
template <typename _Tp, size_t _ToN = 0, typename _Up, size_t _M,
size_t _Np = _ToN != 0 ? _ToN : sizeof(_Up) * _M / sizeof(_Tp)>
_GLIBCXX_SIMD_INTRINSIC constexpr _SimdWrapper<_Tp, _Np>
__wrapper_bitcast(_SimdWrapper<_Up, _M> __x)
{
static_assert(_Np > 1);
return __intrin_bitcast<__vector_type_t<_Tp, _Np>>(__x._M_data);
}
template <unsigned __shift, typename _Tp, typename _TVT = _VectorTraits<_Tp>>
_GLIBCXX_SIMD_INTRINSIC _Tp
__shift_elements_right(_Tp __v)
{
[[maybe_unused]] const auto __iv = __to_intrin(__v);
static_assert(__shift <= sizeof(_Tp));
if constexpr (__shift == 0)
return __v;
else if constexpr (__shift == sizeof(_Tp))
return _Tp();
#if _GLIBCXX_SIMD_X86INTRIN
else if constexpr (__have_sse && __shift == 8
&& _TVT::template _S_is<float, 4>)
return _mm_movehl_ps(__iv, __iv);
else if constexpr (__have_sse2 && __shift == 8
&& _TVT::template _S_is<double, 2>)
return _mm_unpackhi_pd(__iv, __iv);
else if constexpr (__have_sse2 && sizeof(_Tp) == 16)
return reinterpret_cast<typename _TVT::type>(
_mm_srli_si128(reinterpret_cast<__m128i>(__iv), __shift));
else if constexpr (__shift == 16 && sizeof(_Tp) == 32)
{
return __zero_extend(__hi128(__v));
}
else if constexpr (__have_avx2 && sizeof(_Tp) == 32 && __shift < 16)
{
const auto __vll = __vector_bitcast<_LLong>(__v);
return reinterpret_cast<typename _TVT::type>(
_mm256_alignr_epi8(_mm256_permute2x128_si256(__vll, __vll, 0x81), __vll,
__shift));
}
else if constexpr (__have_avx && sizeof(_Tp) == 32 && __shift < 16)
{
const auto __vll = __vector_bitcast<_LLong>(__v);
return reinterpret_cast<typename _TVT::type>(
__concat(_mm_alignr_epi8(__hi128(__vll), __lo128(__vll), __shift),
_mm_srli_si128(__hi128(__vll), __shift)));
}
else if constexpr (sizeof(_Tp) == 32 && __shift > 16)
return __zero_extend(__shift_elements_right<__shift - 16>(__hi128(__v)));
else if constexpr (sizeof(_Tp) == 64 && __shift == 32)
return __zero_extend(__hi256(__v));
else if constexpr (__have_avx512f && sizeof(_Tp) == 64)
{
if constexpr (__shift >= 48)
return __zero_extend(
__shift_elements_right<__shift - 48>(__extract<3, 4>(__v)));
else if constexpr (__shift >= 32)
return __zero_extend(
__shift_elements_right<__shift - 32>(__hi256(__v)));
else if constexpr (__shift % 8 == 0)
return reinterpret_cast<typename _TVT::type>(
_mm512_alignr_epi64(__m512i(), __intrin_bitcast<__m512i>(__v),
__shift / 8));
else if constexpr (__shift % 4 == 0)
return reinterpret_cast<typename _TVT::type>(
_mm512_alignr_epi32(__m512i(), __intrin_bitcast<__m512i>(__v),
__shift / 4));
else if constexpr (__have_avx512bw && __shift < 16)
{
const auto __vll = __vector_bitcast<_LLong>(__v);
return reinterpret_cast<typename _TVT::type>(
_mm512_alignr_epi8(_mm512_shuffle_i32x4(__vll, __vll, 0xf9), __vll,
__shift));
}
else if constexpr (__have_avx512bw && __shift < 32)
{
const auto __vll = __vector_bitcast<_LLong>(__v);
return reinterpret_cast<typename _TVT::type>(
_mm512_alignr_epi8(_mm512_shuffle_i32x4(__vll, __m512i(), 0xee),
_mm512_shuffle_i32x4(__vll, __vll, 0xf9),
__shift - 16));
}
else
__assert_unreachable<_Tp>();
}
#endif
else
{
constexpr int __chunksize
= __shift % 8 == 0 ? 8
: __shift % 4 == 0 ? 4 : __shift % 2 == 0 ? 2 : 1;
auto __w = __vector_bitcast<__int_with_sizeof_t<__chunksize>>(__v);
using _Up = decltype(__w);
return __intrin_bitcast<_Tp>(
__call_with_n_evaluations<(sizeof(_Tp) - __shift) / __chunksize>(
[](auto... __chunks) { return _Up{__chunks...}; },
[&](auto __i) { return __w[__shift / __chunksize + __i]; }));
}
}
template <int _Index, int _Total, int _Combine, typename _Tp, size_t _Np>
_GLIBCXX_SIMD_INTRINSIC
_GLIBCXX_CONST _SimdWrapper<_Tp, _Np / _Total * _Combine>
__extract_part(const _SimdWrapper<_Tp, _Np> __x)
{
if constexpr (_Index % 2 == 0 && _Total % 2 == 0 && _Combine % 2 == 0)
return __extract_part<_Index / 2, _Total / 2, _Combine / 2>(__x);
else
{
constexpr size_t __values_per_part = _Np / _Total;
constexpr size_t __values_to_skip = _Index * __values_per_part;
constexpr size_t __return_size = __values_per_part * _Combine;
using _R = __vector_type_t<_Tp, __return_size>;
static_assert((_Index + _Combine) * __values_per_part * sizeof(_Tp)
<= sizeof(__x),
"out of bounds __extract_part");
if (__x._M_is_constprop())
return __generate_from_n_evaluations<__return_size, _R>(
[&](auto __i) { return __x[__values_to_skip + __i]; });
if constexpr (_Index == 0 && _Total == 1)
return __x;
else if constexpr (_Index == 0)
return __intrin_bitcast<_R>(__as_vector(__x));
#if _GLIBCXX_SIMD_X86INTRIN
else if constexpr (sizeof(__x) == 32 && __return_size * sizeof(_Tp) <= 16)
{
constexpr size_t __bytes_to_skip = __values_to_skip * sizeof(_Tp);
if constexpr (__bytes_to_skip == 16)
return __vector_bitcast<_Tp, __return_size>(
__hi128(__as_vector(__x)));
else
return __vector_bitcast<_Tp, __return_size>(
_mm_alignr_epi8(__hi128(__vector_bitcast<_LLong>(__x)),
__lo128(__vector_bitcast<_LLong>(__x)),
__bytes_to_skip));
}
#endif
else if constexpr (_Index > 0
&& (__values_to_skip % __return_size != 0
|| sizeof(_R) >= 8)
&& (__values_to_skip + __return_size) * sizeof(_Tp)
<= 64
&& sizeof(__x) >= 16)
return __intrin_bitcast<_R>(
__shift_elements_right<__values_to_skip * sizeof(_Tp)>(
__as_vector(__x)));
else
{
_R __r = {};
__builtin_memcpy(&__r,
reinterpret_cast<const char*>(&__x)
+ sizeof(_Tp) * __values_to_skip,
__return_size * sizeof(_Tp));
return __r;
}
}
}
template <int _Index, int _Total, int _Combine = 1, size_t _Np>
_GLIBCXX_SIMD_INTRINSIC constexpr _SimdWrapper<bool, _Np / _Total * _Combine>
__extract_part(const _SimdWrapper<bool, _Np> __x)
{
static_assert(_Combine == 1, "_Combine != 1 not implemented");
static_assert(__have_avx512f && _Np == _Np);
static_assert(_Total >= 2 && _Index + _Combine <= _Total && _Index >= 0);
return __x._M_data >> (_Index * _Np / _Total);
}
template <typename _To, typename _From, size_t... _I>
_GLIBCXX_SIMD_INTRINSIC constexpr _To
__vector_convert(_From __a, index_sequence<_I...>)
{
using _Tp = typename _VectorTraits<_To>::value_type;
return _To{static_cast<_Tp>(__a[_I])...};
}
template <typename _To, typename _From, size_t... _I>
_GLIBCXX_SIMD_INTRINSIC constexpr _To
__vector_convert(_From __a, _From __b, index_sequence<_I...>)
{
using _Tp = typename _VectorTraits<_To>::value_type;
return _To{static_cast<_Tp>(__a[_I])..., static_cast<_Tp>(__b[_I])...};
}
template <typename _To, typename _From, size_t... _I>
_GLIBCXX_SIMD_INTRINSIC constexpr _To
__vector_convert(_From __a, _From __b, _From __c, index_sequence<_I...>)
{
using _Tp = typename _VectorTraits<_To>::value_type;
return _To{static_cast<_Tp>(__a[_I])..., static_cast<_Tp>(__b[_I])...,
static_cast<_Tp>(__c[_I])...};
}
template <typename _To, typename _From, size_t... _I>
_GLIBCXX_SIMD_INTRINSIC constexpr _To
__vector_convert(_From __a, _From __b, _From __c, _From __d,
index_sequence<_I...>)
{
using _Tp = typename _VectorTraits<_To>::value_type;
return _To{static_cast<_Tp>(__a[_I])..., static_cast<_Tp>(__b[_I])...,
static_cast<_Tp>(__c[_I])..., static_cast<_Tp>(__d[_I])...};
}
template <typename _To, typename _From, size_t... _I>
_GLIBCXX_SIMD_INTRINSIC constexpr _To
__vector_convert(_From __a, _From __b, _From __c, _From __d, _From __e,
index_sequence<_I...>)
{
using _Tp = typename _VectorTraits<_To>::value_type;
return _To{static_cast<_Tp>(__a[_I])..., static_cast<_Tp>(__b[_I])...,
static_cast<_Tp>(__c[_I])..., static_cast<_Tp>(__d[_I])...,
static_cast<_Tp>(__e[_I])...};
}
template <typename _To, typename _From, size_t... _I>
_GLIBCXX_SIMD_INTRINSIC constexpr _To
__vector_convert(_From __a, _From __b, _From __c, _From __d, _From __e,
_From __f, index_sequence<_I...>)
{
using _Tp = typename _VectorTraits<_To>::value_type;
return _To{static_cast<_Tp>(__a[_I])..., static_cast<_Tp>(__b[_I])...,
static_cast<_Tp>(__c[_I])..., static_cast<_Tp>(__d[_I])...,
static_cast<_Tp>(__e[_I])..., static_cast<_Tp>(__f[_I])...};
}
template <typename _To, typename _From, size_t... _I>
_GLIBCXX_SIMD_INTRINSIC constexpr _To
__vector_convert(_From __a, _From __b, _From __c, _From __d, _From __e,
_From __f, _From __g, index_sequence<_I...>)
{
using _Tp = typename _VectorTraits<_To>::value_type;
return _To{static_cast<_Tp>(__a[_I])..., static_cast<_Tp>(__b[_I])...,
static_cast<_Tp>(__c[_I])..., static_cast<_Tp>(__d[_I])...,
static_cast<_Tp>(__e[_I])..., static_cast<_Tp>(__f[_I])...,
static_cast<_Tp>(__g[_I])...};
}
template <typename _To, typename _From, size_t... _I>
_GLIBCXX_SIMD_INTRINSIC constexpr _To
__vector_convert(_From __a, _From __b, _From __c, _From __d, _From __e,
_From __f, _From __g, _From __h, index_sequence<_I...>)
{
using _Tp = typename _VectorTraits<_To>::value_type;
return _To{static_cast<_Tp>(__a[_I])..., static_cast<_Tp>(__b[_I])...,
static_cast<_Tp>(__c[_I])..., static_cast<_Tp>(__d[_I])...,
static_cast<_Tp>(__e[_I])..., static_cast<_Tp>(__f[_I])...,
static_cast<_Tp>(__g[_I])..., static_cast<_Tp>(__h[_I])...};
}
template <typename _To, typename _From, size_t... _I>
_GLIBCXX_SIMD_INTRINSIC constexpr _To
__vector_convert(_From __a, _From __b, _From __c, _From __d, _From __e,
_From __f, _From __g, _From __h, _From __i,
index_sequence<_I...>)
{
using _Tp = typename _VectorTraits<_To>::value_type;
return _To{static_cast<_Tp>(__a[_I])..., static_cast<_Tp>(__b[_I])...,
static_cast<_Tp>(__c[_I])..., static_cast<_Tp>(__d[_I])...,
static_cast<_Tp>(__e[_I])..., static_cast<_Tp>(__f[_I])...,
static_cast<_Tp>(__g[_I])..., static_cast<_Tp>(__h[_I])...,
static_cast<_Tp>(__i[_I])...};
}
template <typename _To, typename _From, size_t... _I>
_GLIBCXX_SIMD_INTRINSIC constexpr _To
__vector_convert(_From __a, _From __b, _From __c, _From __d, _From __e,
_From __f, _From __g, _From __h, _From __i, _From __j,
index_sequence<_I...>)
{
using _Tp = typename _VectorTraits<_To>::value_type;
return _To{static_cast<_Tp>(__a[_I])..., static_cast<_Tp>(__b[_I])...,
static_cast<_Tp>(__c[_I])..., static_cast<_Tp>(__d[_I])...,
static_cast<_Tp>(__e[_I])..., static_cast<_Tp>(__f[_I])...,
static_cast<_Tp>(__g[_I])..., static_cast<_Tp>(__h[_I])...,
static_cast<_Tp>(__i[_I])..., static_cast<_Tp>(__j[_I])...};
}
template <typename _To, typename _From, size_t... _I>
_GLIBCXX_SIMD_INTRINSIC constexpr _To
__vector_convert(_From __a, _From __b, _From __c, _From __d, _From __e,
_From __f, _From __g, _From __h, _From __i, _From __j,
_From __k, index_sequence<_I...>)
{
using _Tp = typename _VectorTraits<_To>::value_type;
return _To{static_cast<_Tp>(__a[_I])..., static_cast<_Tp>(__b[_I])...,
static_cast<_Tp>(__c[_I])..., static_cast<_Tp>(__d[_I])...,
static_cast<_Tp>(__e[_I])..., static_cast<_Tp>(__f[_I])...,
static_cast<_Tp>(__g[_I])..., static_cast<_Tp>(__h[_I])...,
static_cast<_Tp>(__i[_I])..., static_cast<_Tp>(__j[_I])...,
static_cast<_Tp>(__k[_I])...};
}
template <typename _To, typename _From, size_t... _I>
_GLIBCXX_SIMD_INTRINSIC constexpr _To
__vector_convert(_From __a, _From __b, _From __c, _From __d, _From __e,
_From __f, _From __g, _From __h, _From __i, _From __j,
_From __k, _From __l, index_sequence<_I...>)
{
using _Tp = typename _VectorTraits<_To>::value_type;
return _To{static_cast<_Tp>(__a[_I])..., static_cast<_Tp>(__b[_I])...,
static_cast<_Tp>(__c[_I])..., static_cast<_Tp>(__d[_I])...,
static_cast<_Tp>(__e[_I])..., static_cast<_Tp>(__f[_I])...,
static_cast<_Tp>(__g[_I])..., static_cast<_Tp>(__h[_I])...,
static_cast<_Tp>(__i[_I])..., static_cast<_Tp>(__j[_I])...,
static_cast<_Tp>(__k[_I])..., static_cast<_Tp>(__l[_I])...};
}
template <typename _To, typename _From, size_t... _I>
_GLIBCXX_SIMD_INTRINSIC constexpr _To
__vector_convert(_From __a, _From __b, _From __c, _From __d, _From __e,
_From __f, _From __g, _From __h, _From __i, _From __j,
_From __k, _From __l, _From __m, index_sequence<_I...>)
{
using _Tp = typename _VectorTraits<_To>::value_type;
return _To{static_cast<_Tp>(__a[_I])..., static_cast<_Tp>(__b[_I])...,
static_cast<_Tp>(__c[_I])..., static_cast<_Tp>(__d[_I])...,
static_cast<_Tp>(__e[_I])..., static_cast<_Tp>(__f[_I])...,
static_cast<_Tp>(__g[_I])..., static_cast<_Tp>(__h[_I])...,
static_cast<_Tp>(__i[_I])..., static_cast<_Tp>(__j[_I])...,
static_cast<_Tp>(__k[_I])..., static_cast<_Tp>(__l[_I])...,
static_cast<_Tp>(__m[_I])...};
}
template <typename _To, typename _From, size_t... _I>
_GLIBCXX_SIMD_INTRINSIC constexpr _To
__vector_convert(_From __a, _From __b, _From __c, _From __d, _From __e,
_From __f, _From __g, _From __h, _From __i, _From __j,
_From __k, _From __l, _From __m, _From __n,
index_sequence<_I...>)
{
using _Tp = typename _VectorTraits<_To>::value_type;
return _To{static_cast<_Tp>(__a[_I])..., static_cast<_Tp>(__b[_I])...,
static_cast<_Tp>(__c[_I])..., static_cast<_Tp>(__d[_I])...,
static_cast<_Tp>(__e[_I])..., static_cast<_Tp>(__f[_I])...,
static_cast<_Tp>(__g[_I])..., static_cast<_Tp>(__h[_I])...,
static_cast<_Tp>(__i[_I])..., static_cast<_Tp>(__j[_I])...,
static_cast<_Tp>(__k[_I])..., static_cast<_Tp>(__l[_I])...,
static_cast<_Tp>(__m[_I])..., static_cast<_Tp>(__n[_I])...};
}
template <typename _To, typename _From, size_t... _I>
_GLIBCXX_SIMD_INTRINSIC constexpr _To
__vector_convert(_From __a, _From __b, _From __c, _From __d, _From __e,
_From __f, _From __g, _From __h, _From __i, _From __j,
_From __k, _From __l, _From __m, _From __n, _From __o,
index_sequence<_I...>)
{
using _Tp = typename _VectorTraits<_To>::value_type;
return _To{static_cast<_Tp>(__a[_I])..., static_cast<_Tp>(__b[_I])...,
static_cast<_Tp>(__c[_I])..., static_cast<_Tp>(__d[_I])...,
static_cast<_Tp>(__e[_I])..., static_cast<_Tp>(__f[_I])...,
static_cast<_Tp>(__g[_I])..., static_cast<_Tp>(__h[_I])...,
static_cast<_Tp>(__i[_I])..., static_cast<_Tp>(__j[_I])...,
static_cast<_Tp>(__k[_I])..., static_cast<_Tp>(__l[_I])...,
static_cast<_Tp>(__m[_I])..., static_cast<_Tp>(__n[_I])...,
static_cast<_Tp>(__o[_I])...};
}
template <typename _To, typename _From, size_t... _I>
_GLIBCXX_SIMD_INTRINSIC constexpr _To
__vector_convert(_From __a, _From __b, _From __c, _From __d, _From __e,
_From __f, _From __g, _From __h, _From __i, _From __j,
_From __k, _From __l, _From __m, _From __n, _From __o,
_From __p, index_sequence<_I...>)
{
using _Tp = typename _VectorTraits<_To>::value_type;
return _To{static_cast<_Tp>(__a[_I])..., static_cast<_Tp>(__b[_I])...,
static_cast<_Tp>(__c[_I])..., static_cast<_Tp>(__d[_I])...,
static_cast<_Tp>(__e[_I])..., static_cast<_Tp>(__f[_I])...,
static_cast<_Tp>(__g[_I])..., static_cast<_Tp>(__h[_I])...,
static_cast<_Tp>(__i[_I])..., static_cast<_Tp>(__j[_I])...,
static_cast<_Tp>(__k[_I])..., static_cast<_Tp>(__l[_I])...,
static_cast<_Tp>(__m[_I])..., static_cast<_Tp>(__n[_I])...,
static_cast<_Tp>(__o[_I])..., static_cast<_Tp>(__p[_I])...};
}
template <typename _To, typename... _From, size_t _FromSize>
_GLIBCXX_SIMD_INTRINSIC constexpr _To
__vector_convert(_SimdWrapper<_From, _FromSize>... __xs)
{
#ifdef _GLIBCXX_SIMD_WORKAROUND_PR85048
using _From0 = __first_of_pack_t<_From...>;
using _FW = _SimdWrapper<_From0, _FromSize>;
if (!_FW::_S_is_partial && !(... && __xs._M_is_constprop()))
{
if constexpr ((sizeof...(_From) & (sizeof...(_From) - 1))
== 0)
return __convert_x86<_To>(__as_vector(__xs)...);
else
return __vector_convert<_To>(__xs..., _FW{});
}
else
#endif
return __vector_convert<_To>(
__as_vector(__xs)...,
make_index_sequence<(sizeof...(__xs) == 1 ? std::min(
_VectorTraits<_To>::_S_full_size, int(_FromSize))
: _FromSize)>());
}
template <typename _To, typename _From, typename... _More>
_GLIBCXX_SIMD_INTRINSIC constexpr auto
__convert(_From __v0, _More... __vs)
{
static_assert((true && ... && is_same_v<_From, _More>) );
if constexpr (__is_vectorizable_v<_From>)
{
using _V = typename _VectorTraits<_To>::type;
using _Tp = typename _VectorTraits<_To>::value_type;
return _V{static_cast<_Tp>(__v0), static_cast<_Tp>(__vs)...};
}
else if constexpr (__is_vector_type_v<_From>)
return __convert<_To>(__as_wrapper(__v0), __as_wrapper(__vs)...);
else
{
constexpr size_t __input_size = _From::_S_size * (1 + sizeof...(_More));
if constexpr (__is_vectorizable_v<_To>)
return __convert<__vector_type_t<_To, __input_size>>(__v0, __vs...);
else if constexpr (!__is_vector_type_v<_To>)
return _To(__convert<typename _To::_BuiltinType>(__v0, __vs...));
else
{
static_assert(
sizeof...(_More) == 0
|| _VectorTraits<_To>::_S_full_size >= __input_size,
"__convert(...) requires the input to fit into the output");
return __vector_convert<_To>(__v0, __vs...);
}
}
}
template <typename _To,
size_t _NParts = 0,
size_t _Offset = 0,
typename _From, typename _FromVT = _VectorTraits<_From>>
_GLIBCXX_SIMD_INTRINSIC auto
__convert_all(_From __v)
{
if constexpr (std::is_arithmetic_v<_To> && _NParts != 1)
{
static_assert(_Offset < _FromVT::_S_full_size);
constexpr auto _Np
= _NParts == 0 ? _FromVT::_S_partial_width - _Offset : _NParts;
return __generate_from_n_evaluations<_Np, std::array<_To, _Np>>(
[&](auto __i) { return static_cast<_To>(__v[__i + _Offset]); });
}
else
{
static_assert(__is_vector_type_v<_To>);
using _ToVT = _VectorTraits<_To>;
if constexpr (__is_vector_type_v<_From>)
return __convert_all<_To, _NParts>(__as_wrapper(__v));
else if constexpr (_NParts == 1)
{
static_assert(_Offset % _ToVT::_S_full_size == 0);
return std::array<_To, 1>{__vector_convert<_To>(
__extract_part<_Offset / _ToVT::_S_full_size,
__div_roundup(_FromVT::_S_partial_width,
_ToVT::_S_full_size)>(__v))};
}
#if _GLIBCXX_SIMD_X86INTRIN
else if constexpr (
!__have_sse4_1 && _Offset == 0
&& is_integral_v<
typename _FromVT::
value_type> && sizeof(typename _FromVT::value_type) < sizeof(typename _ToVT::value_type)
&& !(sizeof(typename _FromVT::value_type) == 4
&& is_same_v<typename _ToVT::value_type, double>) )
{
using _ToT = typename _ToVT::value_type;
using _FromT = typename _FromVT::value_type;
constexpr size_t _Np
= _NParts != 0 ? _NParts
: (_FromVT::_S_partial_width / _ToVT::_S_full_size);
using _R = std::array<_To, _Np>;
[[maybe_unused]] auto __adjust
= [](auto __n,
auto __vv) -> _SimdWrapper<_FromT, decltype(__n)::value> {
return __vector_bitcast<_FromT, decltype(__n)::value>(__vv);
};
[[maybe_unused]] const auto __vi = __to_intrin(__v);
auto&& __make_array =
[](auto __x0, [[maybe_unused]] auto __x1) {
if constexpr (_Np == 1)
return _R{__intrin_bitcast<_To>(__x0)};
else
return _R{__intrin_bitcast<_To>(__x0),
__intrin_bitcast<_To>(__x1)};
};
if constexpr (_Np == 0)
return _R{};
else if constexpr (sizeof(_FromT) == 1 && sizeof(_ToT) == 2)
{
static_assert(std::is_integral_v<_FromT>);
static_assert(std::is_integral_v<_ToT>);
if constexpr (is_unsigned_v<_FromT>)
return __make_array(_mm_unpacklo_epi8(__vi, __m128i()),
_mm_unpackhi_epi8(__vi, __m128i()));
else
return __make_array(
_mm_srai_epi16(_mm_unpacklo_epi8(__vi, __vi), 8),
_mm_srai_epi16(_mm_unpackhi_epi8(__vi, __vi), 8));
}
else if constexpr (sizeof(_FromT) == 2 && sizeof(_ToT) == 4)
{
static_assert(std::is_integral_v<_FromT>);
if constexpr (is_floating_point_v<_ToT>)
{
const auto __ints
= __convert_all<__vector_type16_t<int>, _Np>(
__adjust(_SizeConstant<_Np * 4>(), __v));
return __generate_from_n_evaluations<_Np, _R>([&](auto __i) {
return __vector_convert<_To>(__as_wrapper(__ints[__i]));
});
}
else if constexpr (is_unsigned_v<_FromT>)
return __make_array(_mm_unpacklo_epi16(__vi, __m128i()),
_mm_unpackhi_epi16(__vi, __m128i()));
else
return __make_array(
_mm_srai_epi32(_mm_unpacklo_epi16(__vi, __vi), 16),
_mm_srai_epi32(_mm_unpackhi_epi16(__vi, __vi), 16));
}
else if constexpr (sizeof(_FromT) == 4 && sizeof(_ToT) == 8
&& is_integral_v<_FromT> && is_integral_v<_ToT>)
{
if constexpr (is_unsigned_v<_FromT>)
return __make_array(_mm_unpacklo_epi32(__vi, __m128i()),
_mm_unpackhi_epi32(__vi, __m128i()));
else
return __make_array(
_mm_unpacklo_epi32(__vi, _mm_srai_epi32(__vi, 31)),
_mm_unpackhi_epi32(__vi, _mm_srai_epi32(__vi, 31)));
}
else if constexpr (sizeof(_FromT) == 4 && sizeof(_ToT) == 8
&& is_integral_v<_FromT> && is_integral_v<_ToT>)
{
if constexpr (is_unsigned_v<_FromT>)
return __make_array(_mm_unpacklo_epi32(__vi, __m128i()),
_mm_unpackhi_epi32(__vi, __m128i()));
else
return __make_array(
_mm_unpacklo_epi32(__vi, _mm_srai_epi32(__vi, 31)),
_mm_unpackhi_epi32(__vi, _mm_srai_epi32(__vi, 31)));
}
else if constexpr (sizeof(_FromT) == 1 && sizeof(_ToT) >= 4
&& is_signed_v<_FromT>)
{
const __m128i __vv[2] = {_mm_unpacklo_epi8(__vi, __vi),
_mm_unpackhi_epi8(__vi, __vi)};
const __vector_type_t<int, 4> __vvvv[4]
= {__vector_bitcast<int>(_mm_unpacklo_epi16(__vv[0], __vv[0])),
__vector_bitcast<int>(_mm_unpackhi_epi16(__vv[0], __vv[0])),
__vector_bitcast<int>(_mm_unpacklo_epi16(__vv[1], __vv[1])),
__vector_bitcast<int>(_mm_unpackhi_epi16(__vv[1], __vv[1]))};
if constexpr (sizeof(_ToT) == 4)
return __generate_from_n_evaluations<_Np, _R>([&](auto __i) {
return __vector_convert<_To>(
_SimdWrapper<int, 4>(__vvvv[__i] >> 24));
});
else if constexpr (is_integral_v<_ToT>)
return __generate_from_n_evaluations<_Np, _R>([&](auto __i) {
const auto __signbits = __to_intrin(__vvvv[__i / 2] >> 31);
const auto __sx32 = __to_intrin(__vvvv[__i / 2] >> 24);
return __vector_bitcast<_ToT>(
__i % 2 == 0 ? _mm_unpacklo_epi32(__sx32, __signbits)
: _mm_unpackhi_epi32(__sx32, __signbits));
});
else
return __generate_from_n_evaluations<_Np, _R>([&](auto __i) {
const _SimdWrapper<int, 4> __int4 = __vvvv[__i / 2] >> 24;
return __vector_convert<_To>(
__i % 2 == 0 ? __int4
: _SimdWrapper<int, 4>(
_mm_unpackhi_epi64(__to_intrin(__int4),
__to_intrin(__int4))));
});
}
else if constexpr (sizeof(_FromT) == 1 && sizeof(_ToT) == 4)
{
const auto __shorts = __convert_all<__vector_type16_t<
conditional_t<is_signed_v<_FromT>, short, unsigned short>>>(
__adjust(_SizeConstant<(_Np + 1) / 2 * 8>(), __v));
return __generate_from_n_evaluations<_Np, _R>([&](auto __i) {
return __convert_all<_To>(__shorts[__i / 2])[__i % 2];
});
}
else if constexpr (sizeof(_FromT) == 2 && sizeof(_ToT) == 8
&& is_signed_v<_FromT> && is_integral_v<_ToT>)
{
const __m128i __vv[2] = {_mm_unpacklo_epi16(__vi, __vi),
_mm_unpackhi_epi16(__vi, __vi)};
const __vector_type16_t<int> __vvvv[4]
= {__vector_bitcast<int>(
_mm_unpacklo_epi32(_mm_srai_epi32(__vv[0], 16),
_mm_srai_epi32(__vv[0], 31))),
__vector_bitcast<int>(
_mm_unpackhi_epi32(_mm_srai_epi32(__vv[0], 16),
_mm_srai_epi32(__vv[0], 31))),
__vector_bitcast<int>(
_mm_unpacklo_epi32(_mm_srai_epi32(__vv[1], 16),
_mm_srai_epi32(__vv[1], 31))),
__vector_bitcast<int>(
_mm_unpackhi_epi32(_mm_srai_epi32(__vv[1], 16),
_mm_srai_epi32(__vv[1], 31)))};
return __generate_from_n_evaluations<_Np, _R>(
[&](auto __i) { return __vector_bitcast<_ToT>(__vvvv[__i]); });
}
else if constexpr (sizeof(_FromT) <= 2 && sizeof(_ToT) == 8)
{
const auto __ints = __convert_all<__vector_type16_t<
conditional_t<is_signed_v<_FromT> || is_floating_point_v<_ToT>,
int, unsigned int>>>(
__adjust(_SizeConstant<(_Np + 1) / 2 * 4>(), __v));
return __generate_from_n_evaluations<_Np, _R>([&](auto __i) {
return __convert_all<_To>(__ints[__i / 2])[__i % 2];
});
}
else
__assert_unreachable<_To>();
}
#endif
else if constexpr ((_FromVT::_S_partial_width - _Offset)
> _ToVT::_S_full_size)
{
constexpr size_t _NTotal
= (_FromVT::_S_partial_width - _Offset) / _ToVT::_S_full_size;
constexpr size_t _Np = _NParts == 0 ? _NTotal : _NParts;
static_assert(
_Np <= _NTotal
|| (_Np == _NTotal + 1
&& (_FromVT::_S_partial_width - _Offset) % _ToVT::_S_full_size
> 0));
using _R = std::array<_To, _Np>;
if constexpr (_Np == 1)
return _R{__vector_convert<_To>(
__extract_part<_Offset, _FromVT::_S_partial_width,
_ToVT::_S_full_size>(__v))};
else
return __generate_from_n_evaluations<_Np, _R>([&](
auto __i) constexpr {
auto __part = __extract_part<__i * _ToVT::_S_full_size + _Offset,
_FromVT::_S_partial_width,
_ToVT::_S_full_size>(__v);
return __vector_convert<_To>(__part);
});
}
else if constexpr (_Offset == 0)
return std::array<_To, 1>{__vector_convert<_To>(__v)};
else
return std::array<_To, 1>{__vector_convert<_To>(
__extract_part<_Offset, _FromVT::_S_partial_width,
_FromVT::_S_partial_width - _Offset>(__v))};
}
}
template <typename _Tp, typename _Mp, typename _Abi, size_t _Np>
struct _GnuTraits
{
using _IsValid = true_type;
using _SimdImpl = typename _Abi::_SimdImpl;
using _MaskImpl = typename _Abi::_MaskImpl;
using _SimdMember = _SimdWrapper<_Tp, _Np>;
using _MaskMember = _SimdWrapper<_Mp, _Np>;
static constexpr size_t _S_simd_align = alignof(_SimdMember);
static constexpr size_t _S_mask_align = alignof(_MaskMember);
static constexpr size_t _S_full_size = _SimdMember::_S_full_size;
static constexpr bool _S_is_partial = _SimdMember::_S_is_partial;
struct _SimdBase2
{
explicit operator __intrinsic_type_t<_Tp, _Np>() const
{
return __to_intrin(static_cast<const simd<_Tp, _Abi>*>(this)->_M_data);
}
explicit operator __vector_type_t<_Tp, _Np>() const
{
return static_cast<const simd<_Tp, _Abi>*>(this)->_M_data.__builtin();
}
};
struct _SimdBase1
{
explicit operator __intrinsic_type_t<_Tp, _Np>() const
{
return __data(*static_cast<const simd<_Tp, _Abi>*>(this));
}
};
using _SimdBase
= std::conditional_t<std::is_same<__intrinsic_type_t<_Tp, _Np>,
__vector_type_t<_Tp, _Np>>::value,
_SimdBase1, _SimdBase2>;
struct _MaskBase2
{
explicit operator __intrinsic_type_t<_Tp, _Np>() const
{
return static_cast<const simd_mask<_Tp, _Abi>*>(this)->_M_data.__intrin();
}
explicit operator __vector_type_t<_Tp, _Np>() const
{
return static_cast<const simd_mask<_Tp, _Abi>*>(this)->_M_data._M_data;
}
};
struct _MaskBase1
{
explicit operator __intrinsic_type_t<_Tp, _Np>() const
{
return __data(*static_cast<const simd_mask<_Tp, _Abi>*>(this));
}
};
using _MaskBase
= std::conditional_t<std::is_same<__intrinsic_type_t<_Tp, _Np>,
__vector_type_t<_Tp, _Np>>::value,
_MaskBase1, _MaskBase2>;
class _MaskCastType
{
using _Up = __intrinsic_type_t<_Tp, _Np>;
_Up _M_data;
public:
_MaskCastType(_Up __x) : _M_data(__x) {}
operator _MaskMember() const { return _M_data; }
};
class _SimdCastType1
{
using _Ap = __intrinsic_type_t<_Tp, _Np>;
_SimdMember _M_data;
public:
_SimdCastType1(_Ap __a) : _M_data(__vector_bitcast<_Tp>(__a)) {}
operator _SimdMember() const { return _M_data; }
};
class _SimdCastType2
{
using _Ap = __intrinsic_type_t<_Tp, _Np>;
using _B = __vector_type_t<_Tp, _Np>;
_SimdMember _M_data;
public:
_SimdCastType2(_Ap __a) : _M_data(__vector_bitcast<_Tp>(__a)) {}
_SimdCastType2(_B __b) : _M_data(__b) {}
operator _SimdMember() const { return _M_data; }
};
using _SimdCastType
= std::conditional_t<std::is_same<__intrinsic_type_t<_Tp, _Np>,
__vector_type_t<_Tp, _Np>>::value,
_SimdCastType1, _SimdCastType2>;
};
struct _CommonImplX86;
struct _CommonImplNeon;
struct _CommonImplBuiltin;
template <typename _Abi> struct _SimdImplBuiltin;
template <typename _Abi> struct _MaskImplBuiltin;
template <typename _Abi> struct _SimdImplX86;
template <typename _Abi> struct _MaskImplX86;
template <typename _Abi> struct _SimdImplNeon;
template <typename _Abi> struct _MaskImplNeon;
template <typename _Abi> struct _SimdImplPpc;
template <int _UsedBytes> struct simd_abi::_VecBuiltin
{
template <typename _Tp>
static constexpr size_t _S_size = _UsedBytes / sizeof(_Tp);
struct _IsValidAbiTag : __bool_constant<(_UsedBytes > 1)>
{
};
template <typename _Tp>
struct _IsValidSizeFor
: std::conjunction<
__bool_constant<(_UsedBytes / sizeof(_Tp) > 1
&& _UsedBytes % sizeof(_Tp) == 0)>,
__bool_constant<(_UsedBytes <= __vectorized_sizeof<_Tp>())>>
{
};
template <typename _Tp>
struct _IsValid : std::conjunction<_IsValidAbiTag, __is_vectorizable<_Tp>,
_IsValidSizeFor<_Tp>>
{
};
template <typename _Tp>
static constexpr bool _S_is_valid_v = _IsValid<_Tp>::value;
#if _GLIBCXX_SIMD_X86INTRIN
using _CommonImpl = _CommonImplX86;
using _SimdImpl = _SimdImplX86<_VecBuiltin<_UsedBytes>>;
using _MaskImpl = _MaskImplX86<_VecBuiltin<_UsedBytes>>;
#elif _GLIBCXX_SIMD_HAVE_NEON
using _CommonImpl = _CommonImplNeon;
using _SimdImpl = _SimdImplNeon<_VecBuiltin<_UsedBytes>>;
using _MaskImpl = _MaskImplNeon<_VecBuiltin<_UsedBytes>>;
#else
using _CommonImpl = _CommonImplBuiltin;
#ifdef __ALTIVEC__
using _SimdImpl = _SimdImplPpc<_VecBuiltin<_UsedBytes>>;
#else
using _SimdImpl = _SimdImplBuiltin<_VecBuiltin<_UsedBytes>>;
#endif
using _MaskImpl = _MaskImplBuiltin<_VecBuiltin<_UsedBytes>>;
#endif
template <typename _Tp> using _MaskValueType = __int_for_sizeof_t<_Tp>;
template <typename _Tp>
using __traits
= std::conditional_t<_S_is_valid_v<_Tp>,
_GnuTraits<_Tp, _MaskValueType<_Tp>,
_VecBuiltin<_UsedBytes>, _S_size<_Tp>>,
_InvalidTraits>;
template <typename _Tp>
static constexpr size_t _S_full_size = __traits<_Tp>::_S_full_size;
template <typename _Tp>
static constexpr bool _S_is_partial = __traits<_Tp>::_S_is_partial;
template <typename _Tp>
using _MaskMember = _SimdWrapper<_MaskValueType<_Tp>, _S_size<_Tp>>;
template <typename _Tp>
_GLIBCXX_SIMD_INTRINSIC static constexpr _MaskMember<_Tp> _S_implicit_mask()
{
using _UV = typename _MaskMember<_Tp>::_BuiltinType;
if constexpr (!_MaskMember<_Tp>::_S_is_partial)
return ~_UV();
else
{
constexpr auto __size = _S_size<_Tp>;
_GLIBCXX_SIMD_USE_CONSTEXPR auto __r = __generate_vector<_UV>(
[](auto __i) constexpr { return __i < __size ? -1 : 0; });
return __r;
}
}
template <typename _Tp>
_GLIBCXX_SIMD_INTRINSIC static constexpr __intrinsic_type_t<_Tp, _S_size<_Tp>>
_S_implicit_mask_intrin()
{
return __to_intrin(__vector_bitcast<_Tp>(_S_implicit_mask<_Tp>()._M_data));
}
template <typename _TW, typename _TVT = _VectorTraits<_TW>>
_GLIBCXX_SIMD_INTRINSIC static constexpr _TW _S_masked(_TW __x)
{
using _Tp = typename _TVT::value_type;
if constexpr (!_MaskMember<_Tp>::_S_is_partial)
return __x;
else
return __and(__as_vector(__x),
__vector_bitcast<_Tp>(_S_implicit_mask<_Tp>()));
}
template <typename _TW, typename _TVT = _VectorTraits<_TW>>
_GLIBCXX_SIMD_INTRINSIC static constexpr auto __make_padding_nonzero(_TW __x)
{
using _Tp = typename _TVT::value_type;
if constexpr (!_S_is_partial<_Tp>)
return __x;
else
{
_GLIBCXX_SIMD_USE_CONSTEXPR auto __implicit_mask
= __vector_bitcast<_Tp>(_S_implicit_mask<_Tp>());
if constexpr (std::is_integral_v<_Tp>)
return __or(__x, ~__implicit_mask);
else
{
_GLIBCXX_SIMD_USE_CONSTEXPR auto __one
= __andnot(__implicit_mask,
__vector_broadcast<_S_full_size<_Tp>>(_Tp(1)));
return __or(__and(__x, __implicit_mask), __one);
}
}
}
};
template <int _UsedBytes> struct simd_abi::_VecBltnBtmsk
{
template <typename _Tp>
static constexpr size_t _S_size = _UsedBytes / sizeof(_Tp);
struct _IsValidAbiTag : __bool_constant<(_UsedBytes > 1)>
{
};
template <typename _Tp>
struct _IsValidSizeFor
: __bool_constant<(_UsedBytes / sizeof(_Tp) > 1
&& _UsedBytes % sizeof(_Tp) == 0 && _UsedBytes <= 64
&& (_UsedBytes > 32 || __have_avx512vl))>
{
};
template <typename _Tp>
struct _IsValid
: conjunction<_IsValidAbiTag, __bool_constant<__have_avx512f>,
__bool_constant<__have_avx512bw || (sizeof(_Tp) >= 4)>,
__bool_constant<(__vectorized_sizeof<_Tp>() > sizeof(_Tp))>,
_IsValidSizeFor<_Tp>>
{
};
template <typename _Tp>
static constexpr bool _S_is_valid_v = _IsValid<_Tp>::value;
#if _GLIBCXX_SIMD_X86INTRIN
using _CommonImpl = _CommonImplX86;
using _SimdImpl = _SimdImplX86<_VecBltnBtmsk<_UsedBytes>>;
using _MaskImpl = _MaskImplX86<_VecBltnBtmsk<_UsedBytes>>;
#else
template <int> struct _MissingImpl;
using _CommonImpl = _MissingImpl<_UsedBytes>;
using _SimdImpl = _MissingImpl<_UsedBytes>;
using _MaskImpl = _MissingImpl<_UsedBytes>;
#endif
template <typename _Tp> using _MaskMember = _SimdWrapper<bool, _S_size<_Tp>>;
template <typename _Tp>
using __traits = std::conditional_t<
_S_is_valid_v<_Tp>,
_GnuTraits<_Tp, bool, _VecBltnBtmsk<_UsedBytes>, _S_size<_Tp>>,
_InvalidTraits>;
template <typename _Tp>
static constexpr size_t _S_full_size = __traits<_Tp>::_S_full_size;
template <typename _Tp>
static constexpr bool _S_is_partial = __traits<_Tp>::_S_is_partial;
private:
template <typename _Tp>
using _ImplicitMask = _SimdWrapper<bool, _S_size<_Tp>>;
public:
template <size_t _Np>
_GLIBCXX_SIMD_INTRINSIC static constexpr __bool_storage_member_type_t<_Np>
__implicit_mask_n()
{
using _Tp = __bool_storage_member_type_t<_Np>;
return _Np < sizeof(_Tp) * __CHAR_BIT__ ? _Tp((1ULL << _Np) - 1) : ~_Tp();
}
template <typename _Tp>
_GLIBCXX_SIMD_INTRINSIC static constexpr _ImplicitMask<_Tp> _S_implicit_mask()
{
return __implicit_mask_n<_S_size<_Tp>>();
}
template <typename _Tp>
_GLIBCXX_SIMD_INTRINSIC static constexpr __bool_storage_member_type_t<
_S_size<_Tp>>
_S_implicit_mask_intrin()
{
return __implicit_mask_n<_S_size<_Tp>>();
}
template <typename _Tp, size_t _Np>
_GLIBCXX_SIMD_INTRINSIC static constexpr _SimdWrapper<_Tp, _Np>
_S_masked(_SimdWrapper<_Tp, _Np> __x)
{
if constexpr (is_same_v<_Tp, bool>)
if constexpr (_Np < 8 || (_Np & (_Np - 1)) != 0)
return _MaskImpl::_S_bit_and(__x, _SimdWrapper<_Tp, _Np>(
__bool_storage_member_type_t<_Np>(
(1ULL << _Np) - 1)));
else
return __x;
else
return _S_masked(__x._M_data);
}
template <typename _TV>
_GLIBCXX_SIMD_INTRINSIC static constexpr _TV _S_masked(_TV __x)
{
using _Tp = typename _VectorTraits<_TV>::value_type;
static_assert(
!__is_bitmask_v<_TV>,
"_VecBltnBtmsk::_S_masked cannot work on bitmasks, since it doesn't "
"know the number of elements. Use _SimdWrapper<bool, N> instead.");
if constexpr (_S_is_partial<_Tp>)
{
constexpr size_t _Np = _S_size<_Tp>;
return __make_dependent_t<_TV, _CommonImpl>::_S_blend(
_S_implicit_mask<_Tp>(), _SimdWrapper<_Tp, _Np>(),
_SimdWrapper<_Tp, _Np>(__x));
}
else
return __x;
}
template <typename _TV, typename _TVT = _VectorTraits<_TV>>
_GLIBCXX_SIMD_INTRINSIC static constexpr auto __make_padding_nonzero(_TV __x)
{
using _Tp = typename _TVT::value_type;
if constexpr (!_S_is_partial<_Tp>)
return __x;
else
{
constexpr size_t _Np = _S_size<_Tp>;
if constexpr (is_integral_v<typename _TVT::value_type>)
return __x
| __generate_vector<_Tp, _S_full_size<_Tp>>(
[](auto __i) -> _Tp {
if (__i < _Np)
return 0;
else
return 1;
});
else
return __make_dependent_t<_TV, _CommonImpl>::_S_blend(
_S_implicit_mask<_Tp>(),
_SimdWrapper<_Tp, _Np>(
__vector_broadcast<_S_full_size<_Tp>>(_Tp(1))),
_SimdWrapper<_Tp, _Np>(__x))
._M_data;
}
}
};
struct _CommonImplBuiltin
{
template <typename _From, typename _To, size_t _ToSize>
static inline constexpr bool __converts_via_decomposition_v
= sizeof(_From) != sizeof(_To);
template <typename _Tp, size_t _Np, size_t _Bytes = _Np * sizeof(_Tp)>
_GLIBCXX_SIMD_INTRINSIC static __vector_type_t<_Tp, _Np>
_S_load(const void* __p)
{
static_assert(_Np > 1);
static_assert(_Bytes % sizeof(_Tp) == 0);
using _Rp = __vector_type_t<_Tp, _Np>;
if constexpr (sizeof(_Rp) == _Bytes)
{
_Rp __r;
__builtin_memcpy(&__r, __p, _Bytes);
return __r;
}
else
{
#ifdef _GLIBCXX_SIMD_WORKAROUND_PR90424
using _Up = conditional_t<
is_integral_v<_Tp>,
conditional_t<_Bytes % 4 == 0,
conditional_t<_Bytes % 8 == 0, long long, int>,
conditional_t<_Bytes % 2 == 0, short, signed char>>,
conditional_t<(_Bytes < 8 || _Np % 2 == 1 || _Np == 2), _Tp, double>>;
using _V = __vector_type_t<_Up, _Np * sizeof(_Tp) / sizeof(_Up)>;
if constexpr (sizeof(_V) != sizeof(_Rp))
{
_Rp __r{};
__builtin_memcpy(&__r, __p, _Bytes);
return __r;
}
else
#else
using _V = _Rp;
#endif
{
_V __r{};
static_assert(_Bytes <= sizeof(_V));
__builtin_memcpy(&__r, __p, _Bytes);
return reinterpret_cast<_Rp>(__r);
}
}
}
template <size_t _ReqBytes = 0, typename _TV>
_GLIBCXX_SIMD_INTRINSIC static void _S_store(_TV __x, void* __addr)
{
constexpr size_t _Bytes = _ReqBytes == 0 ? sizeof(__x) : _ReqBytes;
static_assert(sizeof(__x) >= _Bytes);
if constexpr (__is_vector_type_v<_TV>)
{
using _Tp = typename _VectorTraits<_TV>::value_type;
constexpr size_t _Np = _Bytes / sizeof(_Tp);
static_assert(_Np * sizeof(_Tp) == _Bytes);
#ifdef _GLIBCXX_SIMD_WORKAROUND_PR90424
using _Up = std::conditional_t<
(std::is_integral_v<_Tp> || _Bytes < 4),
std::conditional_t<(sizeof(__x) > sizeof(long long)), long long, _Tp>,
float>;
const auto __v = __vector_bitcast<_Up>(__x);
#else
const __vector_type_t<_Tp, _Np> __v = __x;
#endif
if constexpr ((_Bytes & (_Bytes - 1)) != 0)
{
constexpr size_t _MoreBytes = __next_power_of_2(_Bytes);
alignas(decltype(__v)) char __tmp[_MoreBytes];
__builtin_memcpy(__tmp, &__v, _MoreBytes);
__builtin_memcpy(__addr, __tmp, _Bytes);
}
else
__builtin_memcpy(__addr, &__v, _Bytes);
}
else
__builtin_memcpy(__addr, &__x, _Bytes);
}
template <typename _Tp, size_t _Np>
_GLIBCXX_SIMD_INTRINSIC static void _S_store(_SimdWrapper<_Tp, _Np> __x,
void* __addr)
{
_S_store<_Np * sizeof(_Tp)>(__x._M_data, __addr);
}
template <size_t _Np, bool _Sanitized>
_GLIBCXX_SIMD_INTRINSIC static constexpr void
_S_store_bool_array(_BitMask<_Np, _Sanitized> __x, bool* __mem)
{
if constexpr (_Np == 1)
__mem[0] = __x[0];
else if constexpr (_Np == 2)
{
short __bool2 = (__x._M_to_bits() * 0x81) & 0x0101;
_S_store<_Np>(__bool2, __mem);
}
else if constexpr (_Np == 3)
{
int __bool3 = (__x._M_to_bits() * 0x4081) & 0x010101;
_S_store<_Np>(__bool3, __mem);
}
else
{
__execute_n_times<__div_roundup(_Np, 4)>([&](auto __i) {
constexpr int __offset = __i * 4;
constexpr int __remaining = _Np - __offset;
if constexpr (__remaining > 4 && __remaining <= 7)
{
const _ULLong __bool7
= (__x.template _M_extract<__offset>()._M_to_bits()
* 0x40810204081ULL)
& 0x0101010101010101ULL;
_S_store<__remaining>(__bool7, __mem + __offset);
}
else if constexpr (__remaining >= 4)
{
int __bits = __x.template _M_extract<__offset>()._M_to_bits();
if constexpr (__remaining > 7)
__bits &= 0xf;
const int __bool4 = (__bits * 0x204081) & 0x01010101;
_S_store<4>(__bool4, __mem + __offset);
}
});
}
}
template <typename _Tp, size_t _Np>
_GLIBCXX_SIMD_INTRINSIC static constexpr auto
_S_blend(_SimdWrapper<__int_for_sizeof_t<_Tp>, _Np> __k,
_SimdWrapper<_Tp, _Np> __at0, _SimdWrapper<_Tp, _Np> __at1)
{
return __k._M_data ? __at1._M_data : __at0._M_data;
}
};
template <typename _Abi> struct _SimdImplBuiltin
{
template <typename _Tp> static constexpr size_t _S_max_store_size = 16;
using abi_type = _Abi;
template <typename _Tp> using _TypeTag = _Tp*;
template <typename _Tp>
using _SimdMember = typename _Abi::template __traits<_Tp>::_SimdMember;
template <typename _Tp>
using _MaskMember = typename _Abi::template _MaskMember<_Tp>;
template <typename _Tp>
static constexpr size_t _S_size = _Abi::template _S_size<_Tp>;
template <typename _Tp>
static constexpr size_t _S_full_size = _Abi::template _S_full_size<_Tp>;
using _CommonImpl = typename _Abi::_CommonImpl;
using _SuperImpl = typename _Abi::_SimdImpl;
using _MaskImpl = typename _Abi::_MaskImpl;
template <typename _Tp, size_t _Np>
_GLIBCXX_SIMD_INTRINSIC static simd<_Tp, _Abi>
_M_make_simd(_SimdWrapper<_Tp, _Np> __x)
{
return {__private_init, __x};
}
template <typename _Tp, size_t _Np>
_GLIBCXX_SIMD_INTRINSIC static simd<_Tp, _Abi>
_M_make_simd(__intrinsic_type_t<_Tp, _Np> __x)
{
return {__private_init, __vector_bitcast<_Tp>(__x)};
}
template <typename _Tp>
_GLIBCXX_SIMD_INTRINSIC static constexpr _SimdMember<_Tp>
_S_broadcast(_Tp __x) noexcept
{
return __vector_broadcast<_S_full_size<_Tp>>(__x);
}
template <typename _Fp, typename _Tp>
inline static constexpr _SimdMember<_Tp> _S_generator(_Fp&& __gen,
_TypeTag<_Tp>)
{
return __generate_vector<_Tp, _S_full_size<_Tp>>([&](auto __i) constexpr {
if constexpr (__i < _S_size<_Tp>)
return __gen(__i);
else
return 0;
});
}
template <typename _Tp, typename _Up>
_GLIBCXX_SIMD_INTRINSIC static _SimdMember<_Tp>
_S_load(const _Up* __mem, _TypeTag<_Tp>) noexcept
{
constexpr size_t _Np = _S_size<_Tp>;
constexpr size_t __max_load_size
= (sizeof(_Up) >= 4 && __have_avx512f) || __have_avx512bw
? 64
: (std::is_floating_point_v<_Up> && __have_avx) || __have_avx2 ? 32
: 16;
constexpr size_t __bytes_to_load = sizeof(_Up) * _Np;
if constexpr (sizeof(_Up) > 8)
return __generate_vector<_Tp, _SimdMember<_Tp>::_S_full_size>([&](
auto __i) constexpr {
return static_cast<_Tp>(__i < _Np ? __mem[__i] : 0);
});
else if constexpr (std::is_same_v<_Up, _Tp>)
return _CommonImpl::template _S_load<_Tp, _S_full_size<_Tp>,
_Np * sizeof(_Tp)>(__mem);
else if constexpr (__bytes_to_load <= __max_load_size)
return __convert<_SimdMember<_Tp>>(
_CommonImpl::template _S_load<_Up, _Np>(__mem));
else if constexpr (__bytes_to_load % __max_load_size == 0)
{
constexpr size_t __n_loads = __bytes_to_load / __max_load_size;
constexpr size_t __elements_per_load = _Np / __n_loads;
return __call_with_n_evaluations<__n_loads>(
[](auto... __uncvted) {
return __convert<_SimdMember<_Tp>>(__uncvted...);
},
[&](auto __i) {
return _CommonImpl::template _S_load<_Up, __elements_per_load>(
__mem + __i * __elements_per_load);
});
}
else if constexpr (__bytes_to_load % (__max_load_size / 2) == 0
&& __max_load_size > 16)
{
constexpr size_t __n_loads = __bytes_to_load / (__max_load_size / 2);
constexpr size_t __elements_per_load = _Np / __n_loads;
return __call_with_n_evaluations<__n_loads>(
[](auto... __uncvted) {
return __convert<_SimdMember<_Tp>>(__uncvted...);
},
[&](auto __i) {
return _CommonImpl::template _S_load<_Up, __elements_per_load>(
__mem + __i * __elements_per_load);
});
}
else
return __call_with_subscripts(
__mem, make_index_sequence<_Np>(), [](auto... __args) {
return __vector_type_t<_Tp, _S_full_size<_Tp>>{
static_cast<_Tp>(__args)...};
});
}
template <typename _Tp, size_t _Np, typename _Up>
static inline _SimdWrapper<_Tp, _Np>
_S_masked_load(_SimdWrapper<_Tp, _Np> __merge, _MaskMember<_Tp> __k,
const _Up* __mem) noexcept
{
_BitOps::_S_bit_iteration(_MaskImpl::_S_to_bits(__k), [&](auto __i) {
__merge._M_set(__i, static_cast<_Tp>(__mem[__i]));
});
return __merge;
}
template <typename _Tp, typename _Up>
_GLIBCXX_SIMD_INTRINSIC static void _S_store(_SimdMember<_Tp> __v, _Up* __mem,
_TypeTag<_Tp>) noexcept
{
constexpr size_t _Np = _S_size<_Tp>;
constexpr size_t __max_store_size
= _SuperImpl::template _S_max_store_size<_Up>;
if constexpr (sizeof(_Up) > 8)
__execute_n_times<_Np>([&](auto __i) constexpr {
__mem[__i] = __v[__i];
});
else if constexpr (std::is_same_v<_Up, _Tp>)
_CommonImpl::_S_store(__v, __mem);
else if constexpr (sizeof(_Up) * _Np <= __max_store_size)
_CommonImpl::_S_store(_SimdWrapper<_Up, _Np>(__convert<_Up>(__v)), __mem);
else
{
constexpr size_t __vsize = __max_store_size / sizeof(_Up);
constexpr size_t __stores = __div_roundup(_Np, __vsize);
constexpr size_t __full_stores = _Np / __vsize;
using _V = __vector_type_t<_Up, __vsize>;
const std::array<_V, __stores> __converted
= __convert_all<_V, __stores>(__v);
__execute_n_times<__full_stores>([&](auto __i) constexpr {
_CommonImpl::_S_store(__converted[__i], __mem + __i * __vsize);
});
if constexpr (__full_stores < __stores)
_CommonImpl::template _S_store<(_Np - __full_stores * __vsize)
* sizeof(_Up)>(
__converted[__full_stores], __mem + __full_stores * __vsize);
}
}
template <typename _Tp, std::size_t _Np>
_GLIBCXX_SIMD_INTRINSIC static void
_S_masked_store_nocvt(_SimdWrapper<_Tp, _Np> __v, _Tp* __mem,
_MaskMember<_Tp> __k)
{
_BitOps::_S_bit_iteration(
_MaskImpl::_S_to_bits(__k), [&](auto __i) constexpr {
__mem[__i] = __v[__i];
});
}
template <typename _TW, typename _TVT = _VectorTraits<_TW>,
typename _Tp = typename _TVT::value_type, typename _Up>
static inline void _S_masked_store(const _TW __v, _Up* __mem,
const _MaskMember<_Tp> __k) noexcept
{
constexpr size_t _TV_size = _S_size<_Tp>;
[[maybe_unused]] const auto __vi = __to_intrin(__v);
constexpr size_t __max_store_size
= _SuperImpl::template _S_max_store_size<_Up>;
if constexpr (
std::is_same_v<
_Tp,
_Up> || (std::is_integral_v<_Tp> && std::is_integral_v<_Up> && sizeof(_Tp) == sizeof(_Up)))
{
const _MaskMember<_Up> __kk = [&]() {
if constexpr (__is_bitmask_v<decltype(__k)>)
return _MaskMember<_Up>(__k._M_data);
else
return __wrapper_bitcast<__int_for_sizeof_t<_Up>>(__k);
}();
_SuperImpl::_S_masked_store_nocvt(__wrapper_bitcast<_Up>(__v), __mem,
__kk);
}
else if constexpr (__vectorized_sizeof<_Up>() > sizeof(_Up)
&& !_CommonImpl::template __converts_via_decomposition_v<
_Tp, _Up, __max_store_size>)
{
constexpr size_t _UW_size
= std::min(_TV_size, __max_store_size / sizeof(_Up));
static_assert(_UW_size <= _TV_size);
using _UW = _SimdWrapper<_Up, _UW_size>;
using _UV = __vector_type_t<_Up, _UW_size>;
using _UAbi = simd_abi::deduce_t<_Up, _UW_size>;
if constexpr (_UW_size == _TV_size)
{
const _UW __converted = __convert<_UW>(__v);
_SuperImpl::_S_masked_store_nocvt(
__converted, __mem,
_UAbi::_MaskImpl::template _S_convert<__int_for_sizeof_t<_Up>>(
__k));
}
else
{
static_assert(_UW_size * sizeof(_Up) == __max_store_size);
constexpr size_t _NFullStores = _TV_size / _UW_size;
constexpr size_t _NAllStores = __div_roundup(_TV_size, _UW_size);
constexpr size_t _NParts = _S_full_size<_Tp> / _UW_size;
const std::array<_UV, _NAllStores> __converted
= __convert_all<_UV, _NAllStores>(__v);
__execute_n_times<_NFullStores>([&](auto __i) {
_SuperImpl::_S_masked_store_nocvt(
_UW(__converted[__i]), __mem + __i * _UW_size,
_UAbi::_MaskImpl::template _S_convert<__int_for_sizeof_t<_Up>>(
__extract_part<__i, _NParts>(__k.__as_full_vector())));
});
if constexpr (_NAllStores > _NFullStores)
_SuperImpl::_S_masked_store_nocvt(
_UW(__converted[_NFullStores]), __mem + _NFullStores * _UW_size,
_UAbi::_MaskImpl::template _S_convert<__int_for_sizeof_t<_Up>>(
__extract_part<_NFullStores, _NParts>(
__k.__as_full_vector())));
}
}
else
_BitOps::_S_bit_iteration(
_MaskImpl::_S_to_bits(__k), [&](auto __i) constexpr {
__mem[__i] = static_cast<_Up>(__v[__i]);
});
}
template <typename _Tp, size_t _Np>
_GLIBCXX_SIMD_INTRINSIC static constexpr _SimdWrapper<_Tp, _Np>
_S_complement(_SimdWrapper<_Tp, _Np> __x) noexcept
{
return ~__x._M_data;
}
template <typename _Tp, size_t _Np>
_GLIBCXX_SIMD_INTRINSIC static constexpr _SimdWrapper<_Tp, _Np>
_S_unary_minus(_SimdWrapper<_Tp, _Np> __x) noexcept
{
return -__x._M_data;
}
template <typename _Tp, size_t _Np>
_GLIBCXX_SIMD_INTRINSIC static constexpr _SimdWrapper<_Tp, _Np>
_S_plus(_SimdWrapper<_Tp, _Np> __x, _SimdWrapper<_Tp, _Np> __y)
{
return __x._M_data + __y._M_data;
}
template <typename _Tp, size_t _Np>
_GLIBCXX_SIMD_INTRINSIC static constexpr _SimdWrapper<_Tp, _Np>
_S_minus(_SimdWrapper<_Tp, _Np> __x, _SimdWrapper<_Tp, _Np> __y)
{
return __x._M_data - __y._M_data;
}
template <typename _Tp, size_t _Np>
_GLIBCXX_SIMD_INTRINSIC static constexpr _SimdWrapper<_Tp, _Np>
_S_multiplies(_SimdWrapper<_Tp, _Np> __x, _SimdWrapper<_Tp, _Np> __y)
{
return __x._M_data * __y._M_data;
}
template <typename _Tp, size_t _Np>
_GLIBCXX_SIMD_INTRINSIC static constexpr _SimdWrapper<_Tp, _Np>
_S_divides(_SimdWrapper<_Tp, _Np> __x, _SimdWrapper<_Tp, _Np> __y)
{
if constexpr (!_Abi::template _S_is_partial<_Tp>)
return __x._M_data / __y._M_data;
else
return __x._M_data / _Abi::__make_padding_nonzero(__y._M_data);
}
template <typename _Tp, size_t _Np>
_GLIBCXX_SIMD_INTRINSIC static constexpr _SimdWrapper<_Tp, _Np>
_S_modulus(_SimdWrapper<_Tp, _Np> __x, _SimdWrapper<_Tp, _Np> __y)
{
if constexpr (!_Abi::template _S_is_partial<_Tp>)
return __x._M_data % __y._M_data;
else
return __as_vector(__x) % _Abi::__make_padding_nonzero(__as_vector(__y));
}
template <typename _Tp, size_t _Np>
_GLIBCXX_SIMD_INTRINSIC static constexpr _SimdWrapper<_Tp, _Np>
_S_bit_and(_SimdWrapper<_Tp, _Np> __x, _SimdWrapper<_Tp, _Np> __y)
{
return __and(__x, __y);
}
template <typename _Tp, size_t _Np>
_GLIBCXX_SIMD_INTRINSIC static constexpr _SimdWrapper<_Tp, _Np>
_S_bit_or(_SimdWrapper<_Tp, _Np> __x, _SimdWrapper<_Tp, _Np> __y)
{
return __or(__x, __y);
}
template <typename _Tp, size_t _Np>
_GLIBCXX_SIMD_INTRINSIC static constexpr _SimdWrapper<_Tp, _Np>
_S_bit_xor(_SimdWrapper<_Tp, _Np> __x, _SimdWrapper<_Tp, _Np> __y)
{
return __xor(__x, __y);
}
template <typename _Tp, size_t _Np>
_GLIBCXX_SIMD_INTRINSIC static _SimdWrapper<_Tp, _Np>
_S_bit_shift_left(_SimdWrapper<_Tp, _Np> __x, _SimdWrapper<_Tp, _Np> __y)
{
return __x._M_data << __y._M_data;
}
template <typename _Tp, size_t _Np>
_GLIBCXX_SIMD_INTRINSIC static _SimdWrapper<_Tp, _Np>
_S_bit_shift_right(_SimdWrapper<_Tp, _Np> __x, _SimdWrapper<_Tp, _Np> __y)
{
#ifdef _GLIBCXX_SIMD_WORKAROUND_XXX_5
if constexpr (sizeof(_Tp) == 8)
return __generate_vector<__vector_type_t<_Tp, _Np>>([&](auto __i) {
return __x._M_data[__i.value] >> __y._M_data[__i.value];
});
else
#endif
return __x._M_data >> __y._M_data;
}
template <typename _Tp, size_t _Np>
_GLIBCXX_SIMD_INTRINSIC static constexpr _SimdWrapper<_Tp, _Np>
_S_bit_shift_left(_SimdWrapper<_Tp, _Np> __x, int __y)
{
return __x._M_data << __y;
}
template <typename _Tp, size_t _Np>
_GLIBCXX_SIMD_INTRINSIC static constexpr _SimdWrapper<_Tp, _Np>
_S_bit_shift_right(_SimdWrapper<_Tp, _Np> __x, int __y)
{
return __x._M_data >> __y;
}
template <typename _Tp, size_t _Np>
_GLIBCXX_SIMD_INTRINSIC static constexpr _MaskMember<_Tp>
_S_equal_to(_SimdWrapper<_Tp, _Np> __x, _SimdWrapper<_Tp, _Np> __y)
{
return __x._M_data == __y._M_data;
}
template <typename _Tp, size_t _Np>
_GLIBCXX_SIMD_INTRINSIC static constexpr _MaskMember<_Tp>
_S_not_equal_to(_SimdWrapper<_Tp, _Np> __x, _SimdWrapper<_Tp, _Np> __y)
{
return __x._M_data != __y._M_data;
}
template <typename _Tp, size_t _Np>
_GLIBCXX_SIMD_INTRINSIC static constexpr _MaskMember<_Tp>
_S_less(_SimdWrapper<_Tp, _Np> __x, _SimdWrapper<_Tp, _Np> __y)
{
return __x._M_data < __y._M_data;
}
template <typename _Tp, size_t _Np>
_GLIBCXX_SIMD_INTRINSIC static constexpr _MaskMember<_Tp>
_S_less_equal(_SimdWrapper<_Tp, _Np> __x, _SimdWrapper<_Tp, _Np> __y)
{
return __x._M_data <= __y._M_data;
}
template <typename _Tp, size_t _Np>
_GLIBCXX_SIMD_INTRINSIC static constexpr _MaskMember<_Tp>
_S_negate(_SimdWrapper<_Tp, _Np> __x) noexcept
{
return !__x._M_data;
}
template <typename _Tp, size_t _Np>
_GLIBCXX_SIMD_NORMAL_MATH
_GLIBCXX_SIMD_INTRINSIC static constexpr _SimdWrapper<_Tp, _Np>
_S_min(_SimdWrapper<_Tp, _Np> __a, _SimdWrapper<_Tp, _Np> __b)
{
return __a._M_data < __b._M_data ? __a._M_data : __b._M_data;
}
template <typename _Tp, size_t _Np>
_GLIBCXX_SIMD_NORMAL_MATH
_GLIBCXX_SIMD_INTRINSIC static constexpr _SimdWrapper<_Tp, _Np>
_S_max(_SimdWrapper<_Tp, _Np> __a, _SimdWrapper<_Tp, _Np> __b)
{
return __a._M_data > __b._M_data ? __a._M_data : __b._M_data;
}
template <typename _Tp, size_t _Np>
_GLIBCXX_SIMD_NORMAL_MATH
_GLIBCXX_SIMD_INTRINSIC static constexpr std::pair<_SimdWrapper<_Tp, _Np>,
_SimdWrapper<_Tp, _Np>>
_S_minmax(_SimdWrapper<_Tp, _Np> __a, _SimdWrapper<_Tp, _Np> __b)
{
return {__a._M_data < __b._M_data ? __a._M_data : __b._M_data,
__a._M_data < __b._M_data ? __b._M_data : __a._M_data};
}
template <size_t _Np, size_t... _Is, size_t... _Zeros, typename _Tp,
typename _BinaryOperation>
_GLIBCXX_SIMD_INTRINSIC static _Tp
_S_reduce_partial(std::index_sequence<_Is...>, std::index_sequence<_Zeros...>,
simd<_Tp, _Abi> __x, _BinaryOperation&& __binary_op)
{
using _V = __vector_type_t<_Tp, _Np / 2>;
static_assert(sizeof(_V) <= sizeof(__x));
using _FullSimd = __deduced_simd<_Tp, _VectorTraits<_V>::_S_full_size>;
using _HalfSimd = __deduced_simd<_Tp, _Np / 2>;
const auto __xx = __as_vector(__x);
return _HalfSimd::abi_type::_SimdImpl::_S_reduce(
static_cast<_HalfSimd>(__as_vector(__binary_op(
static_cast<_FullSimd>(__intrin_bitcast<_V>(__xx)),
static_cast<_FullSimd>(__intrin_bitcast<_V>(
__vector_permute<(_Np / 2 + _Is)..., (int(_Zeros * 0) - 1)...>(
__xx)))))),
__binary_op);
}
template <typename _Tp, typename _BinaryOperation>
_GLIBCXX_SIMD_INTRINSIC static constexpr _Tp
_S_reduce(simd<_Tp, _Abi> __x, _BinaryOperation&& __binary_op)
{
constexpr size_t _Np = simd_size_v<_Tp, _Abi>;
if constexpr (_Np == 1)
return __x[0];
else if constexpr (_Np == 2)
return __binary_op(simd<_Tp, simd_abi::scalar>(__x[0]),
simd<_Tp, simd_abi::scalar>(__x[1]))[0];
else if constexpr (_Abi::template _S_is_partial<_Tp>)
{
[[maybe_unused]] constexpr auto __full_size
= _Abi::template _S_full_size<_Tp>;
if constexpr (_Np == 3)
return __binary_op(__binary_op(simd<_Tp, simd_abi::scalar>(__x[0]),
simd<_Tp, simd_abi::scalar>(__x[1])),
simd<_Tp, simd_abi::scalar>(__x[2]))[0];
else if constexpr (std::is_same_v<__remove_cvref_t<_BinaryOperation>,
std::plus<>>)
{
using _Ap = simd_abi::deduce_t<_Tp, __full_size>;
return _Ap::_SimdImpl::_S_reduce(
simd<_Tp, _Ap>(__private_init, _Abi::_S_masked(__as_vector(__x))),
__binary_op);
}
else if constexpr (std::is_same_v<__remove_cvref_t<_BinaryOperation>,
std::multiplies<>>)
{
using _Ap = simd_abi::deduce_t<_Tp, __full_size>;
using _TW = _SimdWrapper<_Tp, __full_size>;
_GLIBCXX_SIMD_USE_CONSTEXPR auto __implicit_mask_full
= _Abi::template _S_implicit_mask<_Tp>().__as_full_vector();
_GLIBCXX_SIMD_USE_CONSTEXPR _TW __one
= __vector_broadcast<__full_size>(_Tp(1));
const _TW __x_full = __data(__x).__as_full_vector();
const _TW __x_padded_with_ones
= _Ap::_CommonImpl::_S_blend(__implicit_mask_full, __one,
__x_full);
return _Ap::_SimdImpl::_S_reduce(
simd<_Tp, _Ap>(__private_init, __x_padded_with_ones),
__binary_op);
}
else if constexpr (_Np & 1)
{
using _Ap = simd_abi::deduce_t<_Tp, _Np - 1>;
return __binary_op(
simd<_Tp, simd_abi::scalar>(_Ap::_SimdImpl::_S_reduce(
simd<_Tp, _Ap>(__intrin_bitcast<__vector_type_t<_Tp, _Np - 1>>(
__as_vector(__x))),
__binary_op)),
simd<_Tp, simd_abi::scalar>(__x[_Np - 1]))[0];
}
else
return _S_reduce_partial<_Np>(
std::make_index_sequence<_Np / 2>(),
std::make_index_sequence<__full_size - _Np / 2>(), __x,
__binary_op);
}
else if constexpr (sizeof(__x) == 16)
{
if constexpr (_Np == 16)
{
const auto __y = __data(__x);
__x = __binary_op(_M_make_simd<_Tp, _Np>(
__vector_permute<0, 0, 1, 1, 2, 2, 3, 3, 4, 4,
5, 5, 6, 6, 7, 7>(__y)),
_M_make_simd<_Tp, _Np>(
__vector_permute<8, 8, 9, 9, 10, 10, 11, 11, 12,
12, 13, 13, 14, 14, 15, 15>(
__y)));
}
if constexpr (_Np >= 8)
{
const auto __y = __vector_bitcast<short>(__data(__x));
__x
= __binary_op(_M_make_simd<_Tp, _Np>(__vector_bitcast<_Tp>(
__vector_permute<0, 0, 1, 1, 2, 2, 3, 3>(__y))),
_M_make_simd<_Tp, _Np>(__vector_bitcast<_Tp>(
__vector_permute<4, 4, 5, 5, 6, 6, 7, 7>(__y))));
}
if constexpr (_Np >= 4)
{
using _Up
= std::conditional_t<std::is_floating_point_v<_Tp>, float, int>;
const auto __y = __vector_bitcast<_Up>(__data(__x));
__x = __binary_op(__x, _M_make_simd<_Tp, _Np>(__vector_bitcast<_Tp>(
__vector_permute<3, 2, 1, 0>(__y))));
}
using _Up
= std::conditional_t<std::is_floating_point_v<_Tp>, double, _LLong>;
const auto __y = __vector_bitcast<_Up>(__data(__x));
__x = __binary_op(__x, _M_make_simd<_Tp, _Np>(__vector_bitcast<_Tp>(
__vector_permute<1, 1>(__y))));
return __x[0];
}
else
{
static_assert(sizeof(__x) > __min_vector_size<_Tp>);
static_assert((_Np & (_Np - 1)) == 0);
using _Ap = simd_abi::deduce_t<_Tp, _Np / 2>;
using _V = std::experimental::simd<_Tp, _Ap>;
return _Ap::_SimdImpl::_S_reduce(
__binary_op(_V(__private_init, __extract<0, 2>(__as_vector(__x))),
_V(__private_init, __extract<1, 2>(__as_vector(__x)))),
static_cast<_BinaryOperation&&>(__binary_op));
}
}
#define _GLIBCXX_SIMD_MATH_FALLBACK(__name) \
template <typename _Tp, typename... _More> \
static _Tp _S_##__name(const _Tp& __x, const _More&... __more) \
{ \
return __generate_vector<_Tp>( \
[&](auto __i) { return std::__name(__x[__i], __more[__i]...); }); \
}
#define _GLIBCXX_SIMD_MATH_FALLBACK_MASKRET(__name) \
template <typename _Tp, typename... _More> \
static typename _Tp::mask_type _S_##__name(const _Tp& __x, \
const _More&... __more) \
{ \
return __generate_vector<_Tp>( \
[&](auto __i) { return std::__name(__x[__i], __more[__i]...); }); \
}
#define _GLIBCXX_SIMD_MATH_FALLBACK_FIXEDRET(_RetTp,__name) \
template <typename _Tp, typename... _More> \
static auto _S_##__name(const _Tp& __x, const _More&... __more) \
{ \
return __fixed_size_storage_t<_RetTp, \
_VectorTraits<_Tp>::_S_partial_width>:: \
_S_generate([&](auto __meta) constexpr { \
return __meta._S_generator( \
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
_GLIBCXX_SIMD_MATH_FALLBACK(fabs)
_GLIBCXX_SIMD_MATH_FALLBACK(pow)
_GLIBCXX_SIMD_MATH_FALLBACK(sqrt)
_GLIBCXX_SIMD_MATH_FALLBACK(erf)
_GLIBCXX_SIMD_MATH_FALLBACK(erfc)
_GLIBCXX_SIMD_MATH_FALLBACK(lgamma)
_GLIBCXX_SIMD_MATH_FALLBACK(tgamma)
_GLIBCXX_SIMD_MATH_FALLBACK_FIXEDRET(long, lrint)
_GLIBCXX_SIMD_MATH_FALLBACK_FIXEDRET(long long, llrint)
_GLIBCXX_SIMD_MATH_FALLBACK_FIXEDRET(long, lround)
_GLIBCXX_SIMD_MATH_FALLBACK_FIXEDRET(long long, llround)
_GLIBCXX_SIMD_MATH_FALLBACK(fmod)
_GLIBCXX_SIMD_MATH_FALLBACK(remainder)
template <typename _Tp, typename _TVT = _VectorTraits<_Tp>>
static _Tp _S_remquo(const _Tp __x, const _Tp __y,
__fixed_size_storage_t<int, _TVT::_S_partial_width>* __z)
{
return __generate_vector<_Tp>([&](auto __i) {
int __tmp;
auto __r = std::remquo(__x[__i], __y[__i], &__tmp);
__z->_M_set(__i, __tmp);
return __r;
});
}
_GLIBCXX_SIMD_MATH_FALLBACK(nextafter)
_GLIBCXX_SIMD_MATH_FALLBACK(fdim)
_GLIBCXX_SIMD_MATH_FALLBACK(fmax)
_GLIBCXX_SIMD_MATH_FALLBACK(fmin)
_GLIBCXX_SIMD_MATH_FALLBACK(fma)
template <typename _Tp, size_t _Np>
static constexpr _MaskMember<_Tp>
_S_isgreater(_SimdWrapper<_Tp, _Np> __x, _SimdWrapper<_Tp, _Np> __y) noexcept
{
using _Ip = __int_for_sizeof_t<_Tp>;
const auto __xn = __vector_bitcast<_Ip>(__x);
const auto __yn = __vector_bitcast<_Ip>(__y);
const auto __xp = __xn < 0 ? -(__xn & __finite_max_v<_Ip>) : __xn;
const auto __yp = __yn < 0 ? -(__yn & __finite_max_v<_Ip>) : __yn;
return __andnot(_SuperImpl::_S_isunordered(__x, __y)._M_data, __xp > __yp);
}
template <typename _Tp, size_t _Np>
static constexpr _MaskMember<_Tp>
_S_isgreaterequal(_SimdWrapper<_Tp, _Np> __x,
_SimdWrapper<_Tp, _Np> __y) noexcept
{
using _Ip = __int_for_sizeof_t<_Tp>;
const auto __xn = __vector_bitcast<_Ip>(__x);
const auto __yn = __vector_bitcast<_Ip>(__y);
const auto __xp = __xn < 0 ? -(__xn & __finite_max_v<_Ip>) : __xn;
const auto __yp = __yn < 0 ? -(__yn & __finite_max_v<_Ip>) : __yn;
return __andnot(_SuperImpl::_S_isunordered(__x, __y)._M_data, __xp >= __yp);
}
template <typename _Tp, size_t _Np>
static constexpr _MaskMember<_Tp>
_S_isless(_SimdWrapper<_Tp, _Np> __x, _SimdWrapper<_Tp, _Np> __y) noexcept
{
using _Ip = __int_for_sizeof_t<_Tp>;
const auto __xn = __vector_bitcast<_Ip>(__x);
const auto __yn = __vector_bitcast<_Ip>(__y);
const auto __xp = __xn < 0 ? -(__xn & __finite_max_v<_Ip>) : __xn;
const auto __yp = __yn < 0 ? -(__yn & __finite_max_v<_Ip>) : __yn;
return __andnot(_SuperImpl::_S_isunordered(__x, __y)._M_data, __xp < __yp);
}
template <typename _Tp, size_t _Np>
static constexpr _MaskMember<_Tp>
_S_islessequal(_SimdWrapper<_Tp, _Np> __x,
_SimdWrapper<_Tp, _Np> __y) noexcept
{
using _Ip = __int_for_sizeof_t<_Tp>;
const auto __xn = __vector_bitcast<_Ip>(__x);
const auto __yn = __vector_bitcast<_Ip>(__y);
const auto __xp = __xn < 0 ? -(__xn & __finite_max_v<_Ip>) : __xn;
const auto __yp = __yn < 0 ? -(__yn & __finite_max_v<_Ip>) : __yn;
return __andnot(_SuperImpl::_S_isunordered(__x, __y)._M_data, __xp <= __yp);
}
template <typename _Tp, size_t _Np>
static constexpr _MaskMember<_Tp>
_S_islessgreater(_SimdWrapper<_Tp, _Np> __x,
_SimdWrapper<_Tp, _Np> __y) noexcept
{
return __andnot(_SuperImpl::_S_isunordered(__x, __y),
_SuperImpl::_S_not_equal_to(__x, __y));
}
#undef _GLIBCXX_SIMD_MATH_FALLBACK
#undef _GLIBCXX_SIMD_MATH_FALLBACK_MASKRET
#undef _GLIBCXX_SIMD_MATH_FALLBACK_FIXEDRET
template <typename _Tp, size_t _Np>
_GLIBCXX_SIMD_INTRINSIC static _SimdWrapper<_Tp, _Np>
_S_abs(_SimdWrapper<_Tp, _Np> __x) noexcept
{
if constexpr (std::is_floating_point_v<_Tp>)
return __and(_S_absmask<__vector_type_t<_Tp, _Np>>, __x._M_data);
else
#ifdef _GLIBCXX_SIMD_WORKAROUND_PR91533
if constexpr (sizeof(__x) < 16 && std::is_signed_v<_Tp>)
{
if constexpr (sizeof(_Tp) == 4)
return __auto_bitcast(_mm_abs_epi32(__to_intrin(__x)));
else if constexpr (sizeof(_Tp) == 2)
return __auto_bitcast(_mm_abs_epi16(__to_intrin(__x)));
else
return __auto_bitcast(_mm_abs_epi8(__to_intrin(__x)));
}
else
#endif
return __x._M_data < 0 ? -__x._M_data : __x._M_data;
}
template <typename _TV, typename _UV>
_GLIBCXX_SIMD_INTRINSIC static constexpr _TV _S_plus_minus(_TV __x,
_UV __y) noexcept
{
#if defined __i386__ && !defined __SSE_MATH__
if constexpr (sizeof(__x) == 8)
{
static_assert(std::is_same_v<_TV, __vector_type_t<float, 2>>);
const auto __x4 = __vector_bitcast<float, 4>(__x);
if constexpr (std::is_same_v<_TV, _UV>)
return __vector_bitcast<float, 2>(
_S_plus_minus(__x4, __vector_bitcast<float, 4>(__y)));
else
return __vector_bitcast<float, 2>(_S_plus_minus(__x4, __y));
}
#endif
#if !defined __clang__ && __GCC_IEC_559 == 0
if (__builtin_is_constant_evaluated()
|| (__builtin_constant_p(__x) && __builtin_constant_p(__y)))
return (__x + __y) - __y;
else
return [&] {
__x += __y;
if constexpr(__have_sse)
{
if constexpr (sizeof(__x) >= 16)
asm("" : "+x"(__x));
else if constexpr (std::is_same_v<__vector_type_t<float, 2>, _TV>)
asm("" : "+x"(__x[0]), "+x"(__x[1]));
else
__assert_unreachable<_TV>();
}
else if constexpr(__have_neon)
asm("" : "+w"(__x));
else if constexpr (__have_power_vmx)
asm("" : "+v"(__x));
else
asm("" : "+g"(__x));
return __x - __y;
}();
#else
return (__x + __y) - __y;
#endif
}
template <typename _Tp, typename _TVT = _VectorTraits<_Tp>>
_GLIBCXX_SIMD_INTRINSIC static _Tp _S_nearbyint(_Tp __x_) noexcept
{
using value_type = typename _TVT::value_type;
using _V = typename _TVT::type;
const _V __x = __x_;
const _V __absx = __and(__x, _S_absmask<_V>);
static_assert(__CHAR_BIT__ * sizeof(1ull) >= __digits_v<value_type>);
_GLIBCXX_SIMD_USE_CONSTEXPR _V __shifter_abs
= _V() + (1ull << (__digits_v<value_type> - 1));
const _V __shifter = __or(__and(_S_signmask<_V>, __x), __shifter_abs);
const _V __shifted = _S_plus_minus(__x, __shifter);
return __absx < __shifter_abs ? __shifted : __x;
}
template <typename _Tp, typename _TVT = _VectorTraits<_Tp>>
_GLIBCXX_SIMD_INTRINSIC static _Tp _S_rint(_Tp __x) noexcept
{
return _SuperImpl::_S_nearbyint(__x);
}
template <typename _Tp, size_t _Np>
_GLIBCXX_SIMD_INTRINSIC static _SimdWrapper<_Tp, _Np>
_S_trunc(_SimdWrapper<_Tp, _Np> __x)
{
using _V = __vector_type_t<_Tp, _Np>;
const _V __absx = __and(__x._M_data, _S_absmask<_V>);
static_assert(__CHAR_BIT__ * sizeof(1ull) >= __digits_v<_Tp>);
constexpr _Tp __shifter = 1ull << (__digits_v<_Tp> - 1);
_V __truncated = _S_plus_minus(__absx, __shifter);
__truncated -= __truncated > __absx ? _V() + 1 : _V();
return __absx < __shifter ? __or(__xor(__absx, __x._M_data), __truncated)
: __x._M_data;
}
template <typename _Tp, size_t _Np>
_GLIBCXX_SIMD_INTRINSIC static _SimdWrapper<_Tp, _Np>
_S_round(_SimdWrapper<_Tp, _Np> __x)
{
const auto __abs_x = _SuperImpl::_S_abs(__x);
const auto __t_abs = _SuperImpl::_S_trunc(__abs_x)._M_data;
const auto __r_abs
= __t_abs + (__abs_x._M_data - __t_abs >= _Tp(.5) ? _Tp(1) : 0);
return __or(__xor(__abs_x._M_data, __x._M_data), __r_abs);
}
template <typename _Tp, size_t _Np>
_GLIBCXX_SIMD_INTRINSIC static _SimdWrapper<_Tp, _Np>
_S_floor(_SimdWrapper<_Tp, _Np> __x)
{
const auto __y = _SuperImpl::_S_trunc(__x)._M_data;
const auto __negative_input
= __vector_bitcast<_Tp>(__x._M_data < __vector_broadcast<_Np, _Tp>(0));
const auto __mask
= __andnot(__vector_bitcast<_Tp>(__y == __x._M_data), __negative_input);
return __or(__andnot(__mask, __y),
__and(__mask, __y - __vector_broadcast<_Np, _Tp>(1)));
}
template <typename _Tp, size_t _Np>
_GLIBCXX_SIMD_INTRINSIC static _SimdWrapper<_Tp, _Np>
_S_ceil(_SimdWrapper<_Tp, _Np> __x)
{
const auto __y = _SuperImpl::_S_trunc(__x)._M_data;
const auto __negative_input
= __vector_bitcast<_Tp>(__x._M_data < __vector_broadcast<_Np, _Tp>(0));
const auto __inv_mask
= __or(__vector_bitcast<_Tp>(__y == __x._M_data), __negative_input);
return __or(__and(__inv_mask, __y),
__andnot(__inv_mask, __y + __vector_broadcast<_Np, _Tp>(1)));
}
template <typename _Tp, size_t _Np>
_GLIBCXX_SIMD_INTRINSIC static _MaskMember<_Tp>
_S_isnan([[maybe_unused]] _SimdWrapper<_Tp, _Np> __x)
{
#if __FINITE_MATH_ONLY__
return {};
#elif !defined __SUPPORT_SNAN__
return ~(__x._M_data == __x._M_data);
#elif defined __STDC_IEC_559__
using _Ip = __int_for_sizeof_t<_Tp>;
const auto __absn = __vector_bitcast<_Ip>(_SuperImpl::_S_abs(__x));
const auto __infn
= __vector_bitcast<_Ip>(__vector_broadcast<_Np>(__infinity_v<_Tp>));
return __infn < __absn;
#else
#error "Not implemented: how to support SNaN but non-IEC559 floating-point?"
#endif
}
template <typename _Tp, size_t _Np>
_GLIBCXX_SIMD_INTRINSIC static _MaskMember<_Tp>
_S_isfinite([[maybe_unused]] _SimdWrapper<_Tp, _Np> __x)
{
#if __FINITE_MATH_ONLY__
using _UV = typename _MaskMember<_Tp>::_BuiltinType;
_GLIBCXX_SIMD_USE_CONSTEXPR _UV __alltrue = ~_UV();
return __alltrue;
#else
using _Ip = __int_for_sizeof_t<_Tp>;
const auto __absn = __vector_bitcast<_Ip>(_SuperImpl::_S_abs(__x));
const auto __maxn
= __vector_bitcast<_Ip>(__vector_broadcast<_Np>(__finite_max_v<_Tp>));
return __absn <= __maxn;
#endif
}
template <typename _Tp, size_t _Np>
_GLIBCXX_SIMD_INTRINSIC static _MaskMember<_Tp>
_S_isunordered(_SimdWrapper<_Tp, _Np> __x, _SimdWrapper<_Tp, _Np> __y)
{
return __or(_S_isnan(__x), _S_isnan(__y));
}
template <typename _Tp, size_t _Np>
_GLIBCXX_SIMD_INTRINSIC static _MaskMember<_Tp>
_S_signbit(_SimdWrapper<_Tp, _Np> __x)
{
using _Ip = __int_for_sizeof_t<_Tp>;
return __vector_bitcast<_Ip>(__x) < 0;
}
template <typename _Tp, size_t _Np>
_GLIBCXX_SIMD_INTRINSIC static _MaskMember<_Tp>
_S_isinf([[maybe_unused]] _SimdWrapper<_Tp, _Np> __x)
{
#if __FINITE_MATH_ONLY__
return {};
#else
return _SuperImpl::template _S_equal_to<_Tp, _Np>(_SuperImpl::_S_abs(__x),
__vector_broadcast<_Np>(
__infinity_v<_Tp>));
#endif
}
template <typename _Tp, size_t _Np>
_GLIBCXX_SIMD_INTRINSIC static _MaskMember<_Tp>
_S_isnormal(_SimdWrapper<_Tp, _Np> __x)
{
using _Ip = __int_for_sizeof_t<_Tp>;
const auto __absn = __vector_bitcast<_Ip>(_SuperImpl::_S_abs(__x));
const auto __minn
= __vector_bitcast<_Ip>(__vector_broadcast<_Np>(__norm_min_v<_Tp>));
#if __FINITE_MATH_ONLY__
return __absn >= __minn;
#else
const auto __maxn
= __vector_bitcast<_Ip>(__vector_broadcast<_Np>(__finite_max_v<_Tp>));
return __minn <= __absn && __absn <= __maxn;
#endif
}
template <typename _Tp, size_t _Np>
_GLIBCXX_SIMD_INTRINSIC static __fixed_size_storage_t<int, _Np>
_S_fpclassify(_SimdWrapper<_Tp, _Np> __x)
{
using _I = __int_for_sizeof_t<_Tp>;
const auto __xn
= __vector_bitcast<_I>(__to_intrin(_SuperImpl::_S_abs(__x)));
constexpr size_t _NI = sizeof(__xn) / sizeof(_I);
_GLIBCXX_SIMD_USE_CONSTEXPR auto __minn
= __vector_bitcast<_I>(__vector_broadcast<_NI>(__norm_min_v<_Tp>));
_GLIBCXX_SIMD_USE_CONSTEXPR auto __infn
= __vector_bitcast<_I>(__vector_broadcast<_NI>(__infinity_v<_Tp>));
_GLIBCXX_SIMD_USE_CONSTEXPR auto __fp_normal
= __vector_broadcast<_NI, _I>(FP_NORMAL);
#if !__FINITE_MATH_ONLY__
_GLIBCXX_SIMD_USE_CONSTEXPR auto __fp_nan
= __vector_broadcast<_NI, _I>(FP_NAN);
_GLIBCXX_SIMD_USE_CONSTEXPR auto __fp_infinite
= __vector_broadcast<_NI, _I>(FP_INFINITE);
#endif
#ifndef __FAST_MATH__
_GLIBCXX_SIMD_USE_CONSTEXPR auto __fp_subnormal
= __vector_broadcast<_NI, _I>(FP_SUBNORMAL);
#endif
_GLIBCXX_SIMD_USE_CONSTEXPR auto __fp_zero
= __vector_broadcast<_NI, _I>(FP_ZERO);
__vector_type_t<_I, _NI>
__tmp = __xn < __minn
#ifdef __FAST_MATH__
? __fp_zero
#else
? (__xn == 0 ? __fp_zero : __fp_subnormal)
#endif
#if __FINITE_MATH_ONLY__
: __fp_normal;
#else
: (__xn < __infn ? __fp_normal
: (__xn == __infn ? __fp_infinite : __fp_nan));
#endif
if constexpr (sizeof(_I) == sizeof(int))
{
using _FixedInt = __fixed_size_storage_t<int, _Np>;
const auto __as_int = __vector_bitcast<int, _Np>(__tmp);
if constexpr (_FixedInt::_S_tuple_size == 1)
return {__as_int};
else if constexpr (_FixedInt::_S_tuple_size == 2
&& std::is_same_v<
typename _FixedInt::_SecondType::_FirstAbi,
simd_abi::scalar>)
return {__extract<0, 2>(__as_int), __as_int[_Np - 1]};
else if constexpr (_FixedInt::_S_tuple_size == 2)
return {__extract<0, 2>(__as_int),
__auto_bitcast(__extract<1, 2>(__as_int))};
else
__assert_unreachable<_Tp>();
}
else if constexpr (_Np == 2 && sizeof(_I) == 8
&& __fixed_size_storage_t<int, _Np>::_S_tuple_size == 2)
{
const auto __aslong = __vector_bitcast<_LLong>(__tmp);
return {int(__aslong[0]), {int(__aslong[1])}};
}
#if _GLIBCXX_SIMD_X86INTRIN
else if constexpr (sizeof(_Tp) == 8 && sizeof(__tmp) == 32
&& __fixed_size_storage_t<int, _Np>::_S_tuple_size == 1)
return {_mm_packs_epi32(__to_intrin(__lo128(__tmp)),
__to_intrin(__hi128(__tmp)))};
else if constexpr (sizeof(_Tp) == 8 && sizeof(__tmp) == 64
&& __fixed_size_storage_t<int, _Np>::_S_tuple_size == 1)
return {_mm512_cvtepi64_epi32(__to_intrin(__tmp))};
#endif
else if constexpr (__fixed_size_storage_t<int, _Np>::_S_tuple_size == 1)
return {__call_with_subscripts<_Np>(__vector_bitcast<_LLong>(__tmp),
[](auto... __l) {
return __make_wrapper<int>(__l...);
})};
else
__assert_unreachable<_Tp>();
}
template <typename _Tp, size_t _Np>
_GLIBCXX_SIMD_INTRINSIC static void _S_increment(_SimdWrapper<_Tp, _Np>& __x)
{
__x = __x._M_data + 1;
}
template <typename _Tp, size_t _Np>
_GLIBCXX_SIMD_INTRINSIC static void _S_decrement(_SimdWrapper<_Tp, _Np>& __x)
{
__x = __x._M_data - 1;
}
template <typename _Tp, size_t _Np, typename _Up>
_GLIBCXX_SIMD_INTRINSIC constexpr static void
_S_set(_SimdWrapper<_Tp, _Np>& __v, int __i, _Up&& __x) noexcept
{
__v._M_set(__i, static_cast<_Up&&>(__x));
}
template <typename _Tp, typename _K, size_t _Np>
_GLIBCXX_SIMD_INTRINSIC static void
_S_masked_assign(_SimdWrapper<_K, _Np> __k, _SimdWrapper<_Tp, _Np>& __lhs,
__id<_SimdWrapper<_Tp, _Np>> __rhs)
{
if (__k._M_is_constprop_none_of())
return;
else if (__k._M_is_constprop_all_of())
__lhs = __rhs;
else
__lhs = _CommonImpl::_S_blend(__k, __lhs, __rhs);
}
template <typename _Tp, typename _K, size_t _Np>
_GLIBCXX_SIMD_INTRINSIC static void
_S_masked_assign(_SimdWrapper<_K, _Np> __k, _SimdWrapper<_Tp, _Np>& __lhs,
__id<_Tp> __rhs)
{
if (__k._M_is_constprop_none_of())
return;
else if (__k._M_is_constprop_all_of())
__lhs = __vector_broadcast<_Np>(__rhs);
else if (__builtin_constant_p(__rhs) && __rhs == 0)
{
if constexpr (!is_same_v<bool, _K>)
__lhs._M_data = __andnot(__vector_bitcast<_Tp>(__k), __lhs._M_data);
else
__lhs = _CommonImpl::_S_blend(__k, __lhs, _SimdWrapper<_Tp, _Np>());
}
else
__lhs = _CommonImpl::_S_blend(__k, __lhs,
_SimdWrapper<_Tp, _Np>(
__vector_broadcast<_Np>(__rhs)));
}
template <typename _Op, typename _Tp, typename _K, size_t _Np>
_GLIBCXX_SIMD_INTRINSIC static void
_S_masked_cassign(const _SimdWrapper<_K, _Np> __k,
_SimdWrapper<_Tp, _Np>& __lhs,
const __id<_SimdWrapper<_Tp, _Np>> __rhs, _Op __op)
{
if (__k._M_is_constprop_none_of())
return;
else if (__k._M_is_constprop_all_of())
__lhs = __op(_SuperImpl{}, __lhs, __rhs);
else
__lhs
= _CommonImpl::_S_blend(__k, __lhs, __op(_SuperImpl{}, __lhs, __rhs));
}
template <typename _Op, typename _Tp, typename _K, size_t _Np>
_GLIBCXX_SIMD_INTRINSIC static void
_S_masked_cassign(const _SimdWrapper<_K, _Np> __k,
_SimdWrapper<_Tp, _Np>& __lhs, const __id<_Tp> __rhs,
_Op __op)
{
_S_masked_cassign(__k, __lhs, __vector_broadcast<_Np>(__rhs), __op);
}
template <template <typename> class _Op, typename _Tp, typename _K,
size_t _Np>
_GLIBCXX_SIMD_INTRINSIC static _SimdWrapper<_Tp, _Np>
_S_masked_unary(const _SimdWrapper<_K, _Np> __k,
const _SimdWrapper<_Tp, _Np> __v)
{
if (__k._M_is_constprop_none_of())
return __v;
auto __vv = _M_make_simd(__v);
_Op<decltype(__vv)> __op;
if (__k._M_is_constprop_all_of())
return __data(__op(__vv));
else
return _CommonImpl::_S_blend(__k, __v, __data(__op(__vv)));
}
};
struct _MaskImplBuiltinMixin
{
template <typename _Tp> using _TypeTag = _Tp*;
template <typename _Up, size_t _ToN = 1>
_GLIBCXX_SIMD_INTRINSIC static constexpr _SimdWrapper<_Up, _ToN>
_S_to_maskvector(bool __x)
{
static_assert(is_same_v<_Up, __int_for_sizeof_t<_Up>>);
return __x ? __vector_type_t<_Up, _ToN>{~_Up()}
: __vector_type_t<_Up, _ToN>{};
}
template <typename _Up, size_t _UpN = 0, size_t _Np, bool _Sanitized,
size_t _ToN = _UpN == 0 ? _Np : _UpN>
_GLIBCXX_SIMD_INTRINSIC static constexpr _SimdWrapper<_Up, _ToN>
_S_to_maskvector(_BitMask<_Np, _Sanitized> __x)
{
static_assert(is_same_v<_Up, __int_for_sizeof_t<_Up>>);
return __generate_vector<__vector_type_t<_Up, _ToN>>([&](
auto __i) constexpr {
if constexpr (__i < _Np)
return __x[__i] ? ~_Up() : _Up();
else
return _Up();
});
}
template <typename _Up, size_t _UpN = 0, typename _Tp, size_t _Np,
size_t _ToN = _UpN == 0 ? _Np : _UpN>
_GLIBCXX_SIMD_INTRINSIC static constexpr _SimdWrapper<_Up, _ToN>
_S_to_maskvector(_SimdWrapper<_Tp, _Np> __x)
{
static_assert(is_same_v<_Up, __int_for_sizeof_t<_Up>>);
using _TW = _SimdWrapper<_Tp, _Np>;
using _UW = _SimdWrapper<_Up, _ToN>;
if constexpr (sizeof(_Up) == sizeof(_Tp) && sizeof(_TW) == sizeof(_UW))
return __wrapper_bitcast<_Up, _ToN>(__x);
else if constexpr (is_same_v<_Tp, bool>)
return _S_to_maskvector<_Up, _ToN>(_BitMask<_Np>(__x._M_data));
else
{
{
return __generate_vector<__vector_type_t<_Up, _ToN>>([&](
auto __i) constexpr {
if constexpr (__i < _Np)
return _Up(__x[__i.value]);
else
return _Up();
});
}
}
}
template <typename _Tp, size_t _Np>
_GLIBCXX_SIMD_INTRINSIC static constexpr _SanitizedBitMask<_Np>
_S_to_bits(_SimdWrapper<_Tp, _Np> __x)
{
static_assert(!is_same_v<_Tp, bool>);
static_assert(_Np <= __CHAR_BIT__ * sizeof(_ULLong));
using _Up = make_unsigned_t<__int_for_sizeof_t<_Tp>>;
const auto __bools
= __vector_bitcast<_Up>(__x) >> (sizeof(_Up) * __CHAR_BIT__ - 1);
_ULLong __r = 0;
__execute_n_times<_Np>(
[&](auto __i) { __r |= _ULLong(__bools[__i.value]) << __i; });
return __r;
}
};
template <typename _Abi> struct _MaskImplBuiltin : _MaskImplBuiltinMixin
{
using _MaskImplBuiltinMixin::_S_to_bits;
using _MaskImplBuiltinMixin::_S_to_maskvector;
template <typename _Tp>
using _SimdMember = typename _Abi::template __traits<_Tp>::_SimdMember;
template <typename _Tp>
using _MaskMember = typename _Abi::template _MaskMember<_Tp>;
using _SuperImpl = typename _Abi::_MaskImpl;
using _CommonImpl = typename _Abi::_CommonImpl;
template <typename _Tp>
static constexpr size_t _S_size = simd_size_v<_Tp, _Abi>;
template <typename _Tp>
_GLIBCXX_SIMD_INTRINSIC static constexpr _MaskMember<_Tp>
_S_broadcast(bool __x)
{
return __x ? _Abi::template _S_implicit_mask<_Tp>() : _MaskMember<_Tp>();
}
template <typename _Tp>
_GLIBCXX_SIMD_INTRINSIC static constexpr _MaskMember<_Tp>
_S_load(const bool* __mem)
{
using _I = __int_for_sizeof_t<_Tp>;
if constexpr (sizeof(_Tp) == sizeof(bool))
{
const auto __bools
= _CommonImpl::template _S_load<_I, _S_size<_Tp>>(__mem);
return __bools > 0;
}
else
return __generate_vector<_I, _S_size<_Tp>>([&](auto __i) constexpr {
return __mem[__i] ? ~_I() : _I();
});
}
template <typename _Tp, size_t _Np, bool _Sanitized>
_GLIBCXX_SIMD_INTRINSIC static constexpr auto
_S_convert(_BitMask<_Np, _Sanitized> __x)
{
if constexpr (__is_builtin_bitmask_abi<_Abi>())
return _SimdWrapper<bool, simd_size_v<_Tp, _Abi>>(__x._M_to_bits());
else
return _SuperImpl::template _S_to_maskvector<__int_for_sizeof_t<_Tp>,
_S_size<_Tp>>(
__x._M_sanitized());
}
template <typename _Tp, size_t _Np>
_GLIBCXX_SIMD_INTRINSIC static constexpr auto
_S_convert(_SimdWrapper<bool, _Np> __x)
{
if constexpr (__is_builtin_bitmask_abi<_Abi>())
return _SimdWrapper<bool, simd_size_v<_Tp, _Abi>>(__x._M_data);
else
return _SuperImpl::template _S_to_maskvector<__int_for_sizeof_t<_Tp>,
_S_size<_Tp>>(
_BitMask<_Np>(__x._M_data)._M_sanitized());
}
template <typename _Tp, typename _Up, size_t _Np>
_GLIBCXX_SIMD_INTRINSIC static constexpr auto
_S_convert(_SimdWrapper<_Up, _Np> __x)
{
if constexpr (__is_builtin_bitmask_abi<_Abi>())
return _SimdWrapper<bool, simd_size_v<_Tp, _Abi>>(
_SuperImpl::_S_to_bits(__x));
else
return _SuperImpl::template _S_to_maskvector<__int_for_sizeof_t<_Tp>,
_S_size<_Tp>>(__x);
}
template <typename _Tp, typename _Up, typename _UAbi>
_GLIBCXX_SIMD_INTRINSIC static constexpr auto
_S_convert(simd_mask<_Up, _UAbi> __x)
{
if constexpr (__is_builtin_bitmask_abi<_Abi>())
{
using _R = _SimdWrapper<bool, simd_size_v<_Tp, _Abi>>;
if constexpr (__is_builtin_bitmask_abi<_UAbi>())
return _R(__data(__x));
else if constexpr (__is_scalar_abi<_UAbi>())
return _R(__data(__x));
else if constexpr (__is_fixed_size_abi_v<_UAbi>)
return _R(__data(__x)._M_to_bits());
else
return _R(_UAbi::_MaskImpl::_S_to_bits(__data(__x))._M_to_bits());
}
else
return _SuperImpl::template _S_to_maskvector<__int_for_sizeof_t<_Tp>,
_S_size<_Tp>>(__data(__x));
}
template <typename _Tp, size_t _Np>
static inline _SimdWrapper<_Tp, _Np>
_S_masked_load(_SimdWrapper<_Tp, _Np> __merge, _SimdWrapper<_Tp, _Np> __mask,
const bool* __mem) noexcept
{
auto __tmp = __wrapper_bitcast<__int_for_sizeof_t<_Tp>>(__merge);
_BitOps::_S_bit_iteration(_SuperImpl::_S_to_bits(__mask), [&](auto __i) {
__tmp._M_set(__i, -__mem[__i]);
});
__merge = __wrapper_bitcast<_Tp>(__tmp);
return __merge;
}
template <typename _Tp, size_t _Np>
_GLIBCXX_SIMD_INTRINSIC static void _S_store(_SimdWrapper<_Tp, _Np> __v,
bool* __mem) noexcept
{
__execute_n_times<_Np>([&](auto __i) constexpr { __mem[__i] = __v[__i]; });
}
template <typename _Tp, size_t _Np>
static inline void _S_masked_store(const _SimdWrapper<_Tp, _Np> __v,
bool* __mem,
const _SimdWrapper<_Tp, _Np> __k) noexcept
{
_BitOps::_S_bit_iteration(
_SuperImpl::_S_to_bits(__k), [&](auto __i) constexpr {
__mem[__i] = __v[__i];
});
}
template <size_t _Np, typename _Tp>
_GLIBCXX_SIMD_INTRINSIC static _MaskMember<_Tp>
_S_from_bitmask(_SanitizedBitMask<_Np> __bits, _TypeTag<_Tp>)
{
return _SuperImpl::template _S_to_maskvector<_Tp, _S_size<_Tp>>(__bits);
}
template <typename _Tp, size_t _Np>
_GLIBCXX_SIMD_INTRINSIC static constexpr _SimdWrapper<_Tp, _Np>
_S_logical_and(const _SimdWrapper<_Tp, _Np>& __x,
const _SimdWrapper<_Tp, _Np>& __y)
{
return __and(__x._M_data, __y._M_data);
}
template <typename _Tp, size_t _Np>
_GLIBCXX_SIMD_INTRINSIC static constexpr _SimdWrapper<_Tp, _Np>
_S_logical_or(const _SimdWrapper<_Tp, _Np>& __x,
const _SimdWrapper<_Tp, _Np>& __y)
{
return __or(__x._M_data, __y._M_data);
}
template <typename _Tp, size_t _Np>
_GLIBCXX_SIMD_INTRINSIC static constexpr _SimdWrapper<_Tp, _Np>
_S_bit_not(const _SimdWrapper<_Tp, _Np>& __x)
{
if constexpr(_Abi::template _S_is_partial<_Tp>)
return __andnot(__x, __wrapper_bitcast<_Tp>(
_Abi::template _S_implicit_mask<_Tp>()));
else
return __not(__x._M_data);
}
template <typename _Tp, size_t _Np>
_GLIBCXX_SIMD_INTRINSIC static constexpr _SimdWrapper<_Tp, _Np>
_S_bit_and(const _SimdWrapper<_Tp, _Np>& __x,
const _SimdWrapper<_Tp, _Np>& __y)
{
return __and(__x._M_data, __y._M_data);
}
template <typename _Tp, size_t _Np>
_GLIBCXX_SIMD_INTRINSIC static constexpr _SimdWrapper<_Tp, _Np>
_S_bit_or(const _SimdWrapper<_Tp, _Np>& __x,
const _SimdWrapper<_Tp, _Np>& __y)
{
return __or(__x._M_data, __y._M_data);
}
template <typename _Tp, size_t _Np>
_GLIBCXX_SIMD_INTRINSIC static constexpr _SimdWrapper<_Tp, _Np>
_S_bit_xor(const _SimdWrapper<_Tp, _Np>& __x,
const _SimdWrapper<_Tp, _Np>& __y)
{
return __xor(__x._M_data, __y._M_data);
}
template <typename _Tp, size_t _Np>
static constexpr void _S_set(_SimdWrapper<_Tp, _Np>& __k, int __i,
bool __x) noexcept
{
if constexpr (std::is_same_v<_Tp, bool>)
__k._M_set(__i, __x);
else
{
static_assert(std::is_same_v<_Tp, __int_for_sizeof_t<_Tp>>);
if (__builtin_is_constant_evaluated())
{
__k = __generate_from_n_evaluations<_Np, __vector_type_t<_Tp, _Np>>(
[&](auto __j) {
if (__i == __j)
return _Tp(-__x);
else
return __k[+__j];
});
}
else
__k._M_data[__i] = -__x;
}
}
template <typename _Tp, size_t _Np>
_GLIBCXX_SIMD_INTRINSIC static void
_S_masked_assign(_SimdWrapper<_Tp, _Np> __k, _SimdWrapper<_Tp, _Np>& __lhs,
__id<_SimdWrapper<_Tp, _Np>> __rhs)
{
__lhs = _CommonImpl::_S_blend(__k, __lhs, __rhs);
}
template <typename _Tp, size_t _Np>
_GLIBCXX_SIMD_INTRINSIC static void
_S_masked_assign(_SimdWrapper<_Tp, _Np> __k, _SimdWrapper<_Tp, _Np>& __lhs,
bool __rhs)
{
if (__builtin_constant_p(__rhs))
{
if (__rhs == false)
__lhs = __andnot(__k, __lhs);
else
__lhs = __or(__k, __lhs);
return;
}
__lhs
= _CommonImpl::_S_blend(__k, __lhs, __data(simd_mask<_Tp, _Abi>(__rhs)));
}
template <typename _Tp>
_GLIBCXX_SIMD_INTRINSIC static bool _S_all_of(simd_mask<_Tp, _Abi> __k)
{
return __call_with_subscripts(
__data(__k), make_index_sequence<_S_size<_Tp>>(),
[](const auto... __ent) constexpr { return (... && !(__ent == 0)); });
}
template <typename _Tp>
_GLIBCXX_SIMD_INTRINSIC static bool _S_any_of(simd_mask<_Tp, _Abi> __k)
{
return __call_with_subscripts(
__data(__k), make_index_sequence<_S_size<_Tp>>(),
[](const auto... __ent) constexpr { return (... || !(__ent == 0)); });
}
template <typename _Tp>
_GLIBCXX_SIMD_INTRINSIC static bool _S_none_of(simd_mask<_Tp, _Abi> __k)
{
return __call_with_subscripts(
__data(__k), make_index_sequence<_S_size<_Tp>>(),
[](const auto... __ent) constexpr { return (... && (__ent == 0)); });
}
template <typename _Tp>
_GLIBCXX_SIMD_INTRINSIC static bool _S_some_of(simd_mask<_Tp, _Abi> __k)
{
const int __n_true = _S_popcount(__k);
return __n_true > 0 && __n_true < int(_S_size<_Tp>);
}
template <typename _Tp>
_GLIBCXX_SIMD_INTRINSIC static int _S_popcount(simd_mask<_Tp, _Abi> __k)
{
using _I = __int_for_sizeof_t<_Tp>;
if constexpr (std::is_default_constructible_v<simd<_I, _Abi>>)
return -reduce(
simd<_I, _Abi>(__private_init, __wrapper_bitcast<_I>(__data(__k))));
else
return -reduce(__bit_cast<rebind_simd_t<_I, simd<_Tp, _Abi>>>(
simd<_Tp, _Abi>(__private_init, __data(__k))));
}
template <typename _Tp>
_GLIBCXX_SIMD_INTRINSIC static int _S_find_first_set(simd_mask<_Tp, _Abi> __k)
{
return _BitOps::_S_firstbit(_SuperImpl::_S_to_bits(__data(__k))._M_to_bits());
}
template <typename _Tp>
_GLIBCXX_SIMD_INTRINSIC static int _S_find_last_set(simd_mask<_Tp, _Abi> __k)
{
return _BitOps::_S_lastbit(_SuperImpl::_S_to_bits(__data(__k))._M_to_bits());
}
};
_GLIBCXX_SIMD_END_NAMESPACE
#endif
#endif
#ifndef _GLIBCXX_EXPERIMENTAL_SIMD_CONVERTER_H_
#define _GLIBCXX_EXPERIMENTAL_SIMD_CONVERTER_H_ 
#if __cplusplus >= 201703L
_GLIBCXX_SIMD_BEGIN_NAMESPACE
template <typename _From, typename _To>
struct _SimdConverter<_From, simd_abi::scalar, _To, simd_abi::scalar,
std::enable_if_t<!std::is_same_v<_From, _To>>>
{
_GLIBCXX_SIMD_INTRINSIC constexpr _To operator()(_From __a) const noexcept
{
return static_cast<_To>(__a);
}
};
template <typename _From, typename _To, typename _Abi>
struct _SimdConverter<_From, simd_abi::scalar, _To, _Abi,
std::enable_if_t<!std::is_same_v<_Abi, simd_abi::scalar>>>
{
using _Ret = typename _Abi::template __traits<_To>::_SimdMember;
template <typename... _More>
_GLIBCXX_SIMD_INTRINSIC constexpr _Ret
operator()(_From __a, _More... __more) const noexcept
{
static_assert(sizeof...(_More) + 1 == _Abi::template _S_size<_To>);
static_assert(std::conjunction_v<std::is_same<_From, _More>...>);
return __make_vector<_To>(__a, __more...);
}
};
template <typename _From, typename _To, typename _AFrom, typename _ATo>
struct _SimdConverter<
_From, _AFrom, _To, _ATo,
std::enable_if_t<!std::disjunction_v<
__is_fixed_size_abi<_AFrom>, __is_fixed_size_abi<_ATo>,
std::is_same<_AFrom, simd_abi::scalar>,
std::is_same<_ATo, simd_abi::scalar>,
std::conjunction<std::is_same<_From, _To>, std::is_same<_AFrom, _ATo>>>>>
{
using _Arg = typename _AFrom::template __traits<_From>::_SimdMember;
using _Ret = typename _ATo::template __traits<_To>::_SimdMember;
using _V = __vector_type_t<_To, simd_size_v<_To, _ATo>>;
template <typename... _More>
_GLIBCXX_SIMD_INTRINSIC constexpr _Ret
operator()(_Arg __a, _More... __more) const noexcept
{
return __vector_convert<_V>(__a, __more...);
}
};
template <typename _From, typename _To>
struct _SimdConverter<_From, simd_abi::scalar, _To, simd_abi::fixed_size<1>,
void>
{
_GLIBCXX_SIMD_INTRINSIC constexpr _SimdTuple<_To, simd_abi::scalar>
operator()(_From __x) const noexcept
{
return {static_cast<_To>(__x)};
}
};
template <typename _From, typename _To>
struct _SimdConverter<_From, simd_abi::fixed_size<1>, _To, simd_abi::scalar,
void>
{
_GLIBCXX_SIMD_INTRINSIC constexpr _To
operator()(_SimdTuple<_From, simd_abi::scalar> __x) const noexcept
{
return {static_cast<_To>(__x.first)};
}
};
template <typename _From, typename _To, int _Np>
struct _SimdConverter<_From, simd_abi::fixed_size<_Np>, _To,
simd_abi::fixed_size<_Np>,
std::enable_if_t<!std::is_same_v<_From, _To>>>
{
using _Ret = __fixed_size_storage_t<_To, _Np>;
using _Arg = __fixed_size_storage_t<_From, _Np>;
_GLIBCXX_SIMD_INTRINSIC constexpr _Ret
operator()(const _Arg& __x) const noexcept
{
if constexpr (std::is_same_v<_From, _To>)
return __x;
else if constexpr (sizeof(_From) == sizeof(_To)
&& std::is_integral_v<_From> && std::is_integral_v<_To>)
return __bit_cast<_Ret>(__x);
else if constexpr (__is_scalar_abi<typename _Ret::_FirstAbi>())
{
return __call_with_subscripts(
__x, make_index_sequence<_Np>(),
[](auto... __values) constexpr -> _Ret {
return __make_simd_tuple<_To, decltype((void) __values,
simd_abi::scalar())...>(
static_cast<_To>(__values)...);
});
}
else if constexpr (_Arg::_S_first_size == _Ret::_S_first_size)
{
_SimdConverter<_From, typename _Arg::_FirstAbi, _To,
typename _Ret::_FirstAbi>
__native_cvt;
if constexpr (_Arg::_S_tuple_size == 1)
return {__native_cvt(__x.first)};
else
{
constexpr size_t _NRemain = _Np - _Arg::_S_first_size;
_SimdConverter<_From, simd_abi::fixed_size<_NRemain>, _To,
simd_abi::fixed_size<_NRemain>>
__remainder_cvt;
return {__native_cvt(__x.first), __remainder_cvt(__x.second)};
}
}
else if constexpr (_Arg::_S_first_size > _Ret::_S_first_size)
{
const auto __multiple_return_chunks
= __convert_all<__vector_type_t<_To, _Ret::_S_first_size>>(__x.first);
constexpr auto __converted = __multiple_return_chunks.size()
* _Ret::_FirstAbi::template _S_size<_To>;
constexpr auto __remaining = _Np - __converted;
if constexpr (_Arg::_S_tuple_size == 1 && __remaining == 0)
return __to_simd_tuple<_To, _Np>(__multiple_return_chunks);
else if constexpr (_Arg::_S_tuple_size == 1)
{
using _RetRem = __remove_cvref_t<decltype(
__simd_tuple_pop_front<__converted>(_Ret()))>;
const auto __return_chunks2
= __convert_all<__vector_type_t<_To, _RetRem::_S_first_size>, 0,
__converted>(__x.first);
constexpr auto __converted2
= __converted + __return_chunks2.size() * _RetRem::_S_first_size;
if constexpr (__converted2 == _Np)
return __to_simd_tuple<_To, _Np>(__multiple_return_chunks,
__return_chunks2);
else
{
using _RetRem2 = __remove_cvref_t<decltype(
__simd_tuple_pop_front<__return_chunks2.size()
* _RetRem::_S_first_size>(
_RetRem()))>;
const auto __return_chunks3
= __convert_all<__vector_type_t<_To, _RetRem2::_S_first_size>,
0, __converted2>(__x.first);
constexpr auto __converted3
= __converted2
+ __return_chunks3.size() * _RetRem2::_S_first_size;
if constexpr (__converted3 == _Np)
return __to_simd_tuple<_To, _Np>(__multiple_return_chunks,
__return_chunks2,
__return_chunks3);
else
{
using _RetRem3 = __remove_cvref_t<decltype(
__simd_tuple_pop_front<__return_chunks3.size()
* _RetRem2::_S_first_size>(
_RetRem2()))>;
const auto __return_chunks4 = __convert_all<
__vector_type_t<_To, _RetRem3::_S_first_size>, 0,
__converted3>(__x.first);
constexpr auto __converted4
= __converted3
+ __return_chunks4.size() * _RetRem3::_S_first_size;
if constexpr (__converted4 == _Np)
return __to_simd_tuple<_To, _Np>(__multiple_return_chunks,
__return_chunks2,
__return_chunks3,
__return_chunks4);
else
__assert_unreachable<_To>();
}
}
}
else
{
constexpr size_t _NRemain = _Np - _Arg::_S_first_size;
_SimdConverter<_From, simd_abi::fixed_size<_NRemain>, _To,
simd_abi::fixed_size<_NRemain>>
__remainder_cvt;
return __simd_tuple_concat(
__to_simd_tuple<_To, _Arg::_S_first_size>(
__multiple_return_chunks),
__remainder_cvt(__x.second));
}
}
else if constexpr (_Ret::_S_tuple_size == 1
&& _Np % _Arg::_S_first_size != 0)
{
static_assert(_Ret::_FirstAbi::template _S_is_partial<_To>);
return _Ret{__generate_from_n_evaluations<
_Np, typename _VectorTraits<typename _Ret::_FirstType>::type>(
[&](auto __i) { return static_cast<_To>(__x[__i]); })};
}
else
{
static_assert(_Arg::_S_tuple_size > 1);
constexpr auto __n
= __div_roundup(_Ret::_S_first_size, _Arg::_S_first_size);
return __call_with_n_evaluations<__n>(
[&__x](auto... __uncvted) {
_SimdConverter<_From, typename _Arg::_FirstAbi, _To,
typename _Ret::_FirstAbi>
__native_cvt;
if constexpr (_Ret::_S_tuple_size == 1)
return _Ret{__native_cvt(__uncvted...)};
else
return _Ret{
__native_cvt(__uncvted...),
_SimdConverter<
_From, simd_abi::fixed_size<_Np - _Ret::_S_first_size>, _To,
simd_abi::fixed_size<_Np - _Ret::_S_first_size>>()(
__simd_tuple_pop_front<_Ret::_S_first_size>(__x))};
},
[&__x](auto __i) { return __get_tuple_at<__i>(__x); });
}
}
};
template <typename _From, typename _Ap, typename _To, int _Np>
struct _SimdConverter<_From, _Ap, _To, simd_abi::fixed_size<_Np>,
std::enable_if_t<!__is_fixed_size_abi_v<_Ap>>>
{
static_assert(
_Np == simd_size_v<_From, _Ap>,
"_SimdConverter to fixed_size only works for equal element counts");
using _Ret = __fixed_size_storage_t<_To, _Np>;
_GLIBCXX_SIMD_INTRINSIC constexpr _Ret
operator()(typename _SimdTraits<_From, _Ap>::_SimdMember __x) const noexcept
{
if constexpr (_Ret::_S_tuple_size == 1)
return {__vector_convert<typename _Ret::_FirstType::_BuiltinType>(__x)};
else
{
using _FixedNp = simd_abi::fixed_size<_Np>;
_SimdConverter<_From, _FixedNp, _To, _FixedNp> __fixed_cvt;
using _FromFixedStorage = __fixed_size_storage_t<_From, _Np>;
if constexpr (_FromFixedStorage::_S_tuple_size == 1)
return __fixed_cvt(_FromFixedStorage{__x});
else if constexpr (_FromFixedStorage::_S_tuple_size == 2)
{
_FromFixedStorage __tmp;
static_assert(sizeof(__tmp) <= sizeof(__x));
__builtin_memcpy(&__tmp.first, &__x, sizeof(__tmp.first));
__builtin_memcpy(&__tmp.second.first,
reinterpret_cast<const char*>(&__x)
+ sizeof(__tmp.first),
sizeof(__tmp.second.first));
return __fixed_cvt(__tmp);
}
else
__assert_unreachable<_From>();
}
}
};
template <typename _From, int _Np, typename _To, typename _Ap>
struct _SimdConverter<_From, simd_abi::fixed_size<_Np>, _To, _Ap,
std::enable_if_t<!__is_fixed_size_abi_v<_Ap>>>
{
static_assert(
_Np == simd_size_v<_To, _Ap>,
"_SimdConverter to fixed_size only works for equal element counts");
using _Arg = __fixed_size_storage_t<_From, _Np>;
_GLIBCXX_SIMD_INTRINSIC constexpr typename _SimdTraits<_To, _Ap>::_SimdMember
operator()(_Arg __x) const noexcept
{
if constexpr (_Arg::_S_tuple_size == 1)
return __vector_convert<__vector_type_t<_To, _Np>>(__x.first);
else if constexpr (_Arg::_S_is_homogeneous)
return __call_with_n_evaluations<_Arg::_S_tuple_size>(
[](auto... __members) {
if constexpr ((std::is_convertible_v<decltype(__members),
_To> && ...))
return __vector_type_t<_To, _Np>{static_cast<_To>(__members)...};
else
return __vector_convert<__vector_type_t<_To, _Np>>(__members...);
},
[&](auto __i) { return __get_tuple_at<__i>(__x); });
else if constexpr (__fixed_size_storage_t<_To, _Np>::_S_tuple_size == 1)
{
_SimdConverter<_From, simd_abi::fixed_size<_Np>, _To,
simd_abi::fixed_size<_Np>>
__fixed_cvt;
return __fixed_cvt(__x).first;
}
else
{
const _SimdWrapper<_From, _Np> __xv
= __generate_from_n_evaluations<_Np, __vector_type_t<_From, _Np>>(
[&](auto __i) { return __x[__i]; });
return __vector_convert<__vector_type_t<_To, _Np>>(__xv);
}
}
};
_GLIBCXX_SIMD_END_NAMESPACE
#endif
#endif
#if _GLIBCXX_SIMD_X86INTRIN
#ifndef _GLIBCXX_EXPERIMENTAL_SIMD_X86_H_
#define _GLIBCXX_EXPERIMENTAL_SIMD_X86_H_ 
#if __cplusplus >= 201703L
#if !_GLIBCXX_SIMD_X86INTRIN
#error \
"simd_x86.h may only be included when MMX or SSE on x86(_64) are available"
#endif
_GLIBCXX_SIMD_BEGIN_NAMESPACE
template <typename _Tp, size_t _Np>
_GLIBCXX_SIMD_INTRINSIC constexpr _SimdWrapper<__int_for_sizeof_t<_Tp>, _Np>
__to_masktype(_SimdWrapper<_Tp, _Np> __x)
{
return reinterpret_cast<__vector_type_t<__int_for_sizeof_t<_Tp>, _Np>>(
__x._M_data);
}
template <typename _TV,
typename _TVT
= std::enable_if_t<__is_vector_type_v<_TV>, _VectorTraits<_TV>>,
typename _Up = __int_for_sizeof_t<typename _TVT::value_type>>
_GLIBCXX_SIMD_INTRINSIC constexpr __vector_type_t<_Up, _TVT::_S_full_size>
__to_masktype(_TV __x)
{
return reinterpret_cast<__vector_type_t<_Up, _TVT::_S_full_size>>(__x);
}
template <typename _Ap, typename _B, typename _Tp = std::common_type_t<_Ap, _B>,
typename _Trait = _VectorTraits<_Tp>>
_GLIBCXX_SIMD_INTRINSIC constexpr _Tp
__interleave128_lo(const _Ap& __av, const _B& __bv)
{
const _Tp __a(__av);
const _Tp __b(__bv);
if constexpr (sizeof(_Tp) == 16 && _Trait::_S_full_size == 2)
return _Tp{__a[0], __b[0]};
else if constexpr (sizeof(_Tp) == 16 && _Trait::_S_full_size == 4)
return _Tp{__a[0], __b[0], __a[1], __b[1]};
else if constexpr (sizeof(_Tp) == 16 && _Trait::_S_full_size == 8)
return _Tp{__a[0], __b[0], __a[1], __b[1], __a[2], __b[2], __a[3], __b[3]};
else if constexpr (sizeof(_Tp) == 16 && _Trait::_S_full_size == 16)
return _Tp{__a[0], __b[0], __a[1], __b[1], __a[2], __b[2], __a[3], __b[3],
__a[4], __b[4], __a[5], __b[5], __a[6], __b[6], __a[7], __b[7]};
else if constexpr (sizeof(_Tp) == 32 && _Trait::_S_full_size == 4)
return _Tp{__a[0], __b[0], __a[2], __b[2]};
else if constexpr (sizeof(_Tp) == 32 && _Trait::_S_full_size == 8)
return _Tp{__a[0], __b[0], __a[1], __b[1], __a[4], __b[4], __a[5], __b[5]};
else if constexpr (sizeof(_Tp) == 32 && _Trait::_S_full_size == 16)
return _Tp{__a[0], __b[0], __a[1], __b[1], __a[2], __b[2],
__a[3], __b[3], __a[8], __b[8], __a[9], __b[9],
__a[10], __b[10], __a[11], __b[11]};
else if constexpr (sizeof(_Tp) == 32 && _Trait::_S_full_size == 32)
return _Tp{__a[0], __b[0], __a[1], __b[1], __a[2], __b[2], __a[3],
__b[3], __a[4], __b[4], __a[5], __b[5], __a[6], __b[6],
__a[7], __b[7], __a[16], __b[16], __a[17], __b[17], __a[18],
__b[18], __a[19], __b[19], __a[20], __b[20], __a[21], __b[21],
__a[22], __b[22], __a[23], __b[23]};
else if constexpr (sizeof(_Tp) == 64 && _Trait::_S_full_size == 8)
return _Tp{__a[0], __b[0], __a[2], __b[2], __a[4], __b[4], __a[6], __b[6]};
else if constexpr (sizeof(_Tp) == 64 && _Trait::_S_full_size == 16)
return _Tp{__a[0], __b[0], __a[1], __b[1], __a[4], __b[4],
__a[5], __b[5], __a[8], __b[8], __a[9], __b[9],
__a[12], __b[12], __a[13], __b[13]};
else if constexpr (sizeof(_Tp) == 64 && _Trait::_S_full_size == 32)
return _Tp{__a[0], __b[0], __a[1], __b[1], __a[2], __b[2], __a[3],
__b[3], __a[8], __b[8], __a[9], __b[9], __a[10], __b[10],
__a[11], __b[11], __a[16], __b[16], __a[17], __b[17], __a[18],
__b[18], __a[19], __b[19], __a[24], __b[24], __a[25], __b[25],
__a[26], __b[26], __a[27], __b[27]};
else if constexpr (sizeof(_Tp) == 64 && _Trait::_S_full_size == 64)
return _Tp{__a[0], __b[0], __a[1], __b[1], __a[2], __b[2], __a[3],
__b[3], __a[4], __b[4], __a[5], __b[5], __a[6], __b[6],
__a[7], __b[7], __a[16], __b[16], __a[17], __b[17], __a[18],
__b[18], __a[19], __b[19], __a[20], __b[20], __a[21], __b[21],
__a[22], __b[22], __a[23], __b[23], __a[32], __b[32], __a[33],
__b[33], __a[34], __b[34], __a[35], __b[35], __a[36], __b[36],
__a[37], __b[37], __a[38], __b[38], __a[39], __b[39], __a[48],
__b[48], __a[49], __b[49], __a[50], __b[50], __a[51], __b[51],
__a[52], __b[52], __a[53], __b[53], __a[54], __b[54], __a[55],
__b[55]};
else
__assert_unreachable<_Tp>();
}
template <typename _Tp, typename _TVT = _VectorTraits<_Tp>>
_GLIBCXX_SIMD_INTRINSIC constexpr bool
__is_zero(_Tp __a)
{
if (!__builtin_is_constant_evaluated())
{
if constexpr (__have_avx)
{
if constexpr (_TVT::template _S_is<float, 8>)
return _mm256_testz_ps(__a, __a);
else if constexpr (_TVT::template _S_is<double, 4>)
return _mm256_testz_pd(__a, __a);
else if constexpr (sizeof(_Tp) == 32)
return _mm256_testz_si256(__to_intrin(__a), __to_intrin(__a));
else if constexpr (_TVT::template _S_is<float>)
return _mm_testz_ps(__to_intrin(__a), __to_intrin(__a));
else if constexpr (_TVT::template _S_is<double, 2>)
return _mm_testz_pd(__a, __a);
else
return _mm_testz_si128(__to_intrin(__a), __to_intrin(__a));
}
else if constexpr (__have_sse4_1)
return _mm_testz_si128(__intrin_bitcast<__m128i>(__a),
__intrin_bitcast<__m128i>(__a));
}
else if constexpr (sizeof(_Tp) <= 8)
return reinterpret_cast<__int_for_sizeof_t<_Tp>>(__a) == 0;
else
{
const auto __b = __vector_bitcast<_LLong>(__a);
if constexpr (sizeof(__b) == 16)
return (__b[0] | __b[1]) == 0;
else if constexpr (sizeof(__b) == 32)
return __is_zero(__lo128(__b) | __hi128(__b));
else if constexpr (sizeof(__b) == 64)
return __is_zero(__lo256(__b) | __hi256(__b));
else
__assert_unreachable<_Tp>();
}
}
template <typename _Tp, typename _TVT = _VectorTraits<_Tp>>
_GLIBCXX_SIMD_INTRINSIC _GLIBCXX_CONST int
__movemask(_Tp __a)
{
if constexpr (sizeof(_Tp) == 32)
{
if constexpr (_TVT::template _S_is<float>)
return _mm256_movemask_ps(__to_intrin(__a));
else if constexpr (_TVT::template _S_is<double>)
return _mm256_movemask_pd(__to_intrin(__a));
else
return _mm256_movemask_epi8(__to_intrin(__a));
}
else if constexpr (_TVT::template _S_is<float>)
return _mm_movemask_ps(__to_intrin(__a));
else if constexpr (_TVT::template _S_is<double>)
return _mm_movemask_pd(__to_intrin(__a));
else
return _mm_movemask_epi8(__to_intrin(__a));
}
template <typename _TI, typename _TVT = _VectorTraits<_TI>>
_GLIBCXX_SIMD_INTRINSIC _GLIBCXX_CONST constexpr int
__testz(_TI __a, _TI __b)
{
static_assert(
is_same_v<
_TI, __intrinsic_type_t<typename _TVT::value_type, _TVT::_S_full_size>>);
if (!__builtin_is_constant_evaluated())
{
if constexpr (sizeof(_TI) == 32)
{
if constexpr (_TVT::template _S_is<float>)
return _mm256_testz_ps(__to_intrin(__a), __to_intrin(__b));
else if constexpr (_TVT::template _S_is<double>)
return _mm256_testz_pd(__to_intrin(__a), __to_intrin(__b));
else
return _mm256_testz_si256(__to_intrin(__a), __to_intrin(__b));
}
else if constexpr (_TVT::template _S_is<float> && __have_avx)
return _mm_testz_ps(__to_intrin(__a), __to_intrin(__b));
else if constexpr (_TVT::template _S_is<double> && __have_avx)
return _mm_testz_pd(__to_intrin(__a), __to_intrin(__b));
else if constexpr (__have_sse4_1)
return _mm_testz_si128(__intrin_bitcast<__m128i>(__to_intrin(__a)),
__intrin_bitcast<__m128i>(__to_intrin(__b)));
else
return __movemask(0 == __and(__a, __b)) != 0;
}
else
return __is_zero(__and(__a, __b));
}
template <typename _TI, typename _TVT = _VectorTraits<_TI>>
_GLIBCXX_SIMD_INTRINSIC _GLIBCXX_CONST constexpr int
__testc(_TI __a, _TI __b)
{
static_assert(
is_same_v<
_TI, __intrinsic_type_t<typename _TVT::value_type, _TVT::_S_full_size>>);
if (__builtin_is_constant_evaluated())
return __is_zero(__andnot(__a, __b));
if constexpr (sizeof(_TI) == 32)
{
if constexpr (_TVT::template _S_is<float>)
return _mm256_testc_ps(__a, __b);
else if constexpr (_TVT::template _S_is<double>)
return _mm256_testc_pd(__a, __b);
else
return _mm256_testc_si256(__to_intrin(__a), __to_intrin(__b));
}
else if constexpr (_TVT::template _S_is<float> && __have_avx)
return _mm_testc_ps(__to_intrin(__a), __to_intrin(__b));
else if constexpr (_TVT::template _S_is<double> && __have_avx)
return _mm_testc_pd(__to_intrin(__a), __to_intrin(__b));
else
{
static_assert(is_same_v<_TI, _TI> && __have_sse4_1);
return _mm_testc_si128(__intrin_bitcast<__m128i>(__to_intrin(__a)),
__intrin_bitcast<__m128i>(__to_intrin(__b)));
}
}
template <typename _TI, typename _TVT = _VectorTraits<_TI>>
_GLIBCXX_SIMD_INTRINSIC _GLIBCXX_CONST constexpr int
__testnzc(_TI __a, _TI __b)
{
static_assert(
is_same_v<
_TI, __intrinsic_type_t<typename _TVT::value_type, _TVT::_S_full_size>>);
if (!__builtin_is_constant_evaluated())
{
if constexpr (sizeof(_TI) == 32)
{
if constexpr (_TVT::template _S_is<float>)
return _mm256_testnzc_ps(__a, __b);
else if constexpr (_TVT::template _S_is<double>)
return _mm256_testnzc_pd(__a, __b);
else
return _mm256_testnzc_si256(__to_intrin(__a), __to_intrin(__b));
}
else if constexpr (_TVT::template _S_is<float> && __have_avx)
return _mm_testnzc_ps(__to_intrin(__a), __to_intrin(__b));
else if constexpr (_TVT::template _S_is<double> && __have_avx)
return _mm_testnzc_pd(__to_intrin(__a), __to_intrin(__b));
else if constexpr (__have_sse4_1)
return _mm_testnzc_si128(__intrin_bitcast<__m128i>(__to_intrin(__a)),
__intrin_bitcast<__m128i>(__to_intrin(__b)));
else
return __movemask(0 == __and(__a, __b)) == 0
&& __movemask(0 == __andnot(__a, __b)) == 0;
}
else
return !(__is_zero(__and(__a, __b)) || __is_zero(__andnot(__a, __b)));
}
template <typename _Tp, typename _TVT = _VectorTraits<_Tp>>
_GLIBCXX_SIMD_INTRINSIC _Tp
__xzyw(_Tp __a)
{
if constexpr (sizeof(_Tp) == 16)
{
const auto __x = __vector_bitcast<conditional_t<
is_floating_point_v<typename _TVT::value_type>, float, int>>(__a);
return reinterpret_cast<_Tp>(
decltype(__x){__x[0], __x[2], __x[1], __x[3]});
}
else if constexpr (sizeof(_Tp) == 32)
{
const auto __x = __vector_bitcast<conditional_t<
is_floating_point_v<typename _TVT::value_type>, double, _LLong>>(__a);
return reinterpret_cast<_Tp>(
decltype(__x){__x[0], __x[2], __x[1], __x[3]});
}
else if constexpr (sizeof(_Tp) == 64)
{
const auto __x = __vector_bitcast<conditional_t<
is_floating_point_v<typename _TVT::value_type>, double, _LLong>>(__a);
return reinterpret_cast<_Tp>(decltype(
__x){__x[0], __x[1], __x[4], __x[5], __x[2], __x[3], __x[6], __x[7]});
}
else
__assert_unreachable<_Tp>();
}
template <typename _Tp>
_GLIBCXX_SIMD_INTRINSIC auto
__maskload_epi32(const int* __ptr, _Tp __k)
{
if constexpr (sizeof(__k) == 16)
return _mm_maskload_epi32(__ptr, __k);
else
return _mm256_maskload_epi32(__ptr, __k);
}
template <typename _Tp>
_GLIBCXX_SIMD_INTRINSIC auto
__maskload_epi64(const _LLong* __ptr, _Tp __k)
{
if constexpr (sizeof(__k) == 16)
return _mm_maskload_epi64(__ptr, __k);
else
return _mm256_maskload_epi64(__ptr, __k);
}
template <typename _Tp>
_GLIBCXX_SIMD_INTRINSIC auto
__maskload_ps(const float* __ptr, _Tp __k)
{
if constexpr (sizeof(__k) == 16)
return _mm_maskload_ps(__ptr, __k);
else
return _mm256_maskload_ps(__ptr, __k);
}
template <typename _Tp>
_GLIBCXX_SIMD_INTRINSIC auto
__maskload_pd(const double* __ptr, _Tp __k)
{
if constexpr (sizeof(__k) == 16)
return _mm_maskload_pd(__ptr, __k);
else
return _mm256_maskload_pd(__ptr, __k);
}
#ifdef _GLIBCXX_SIMD_WORKAROUND_PR85048
#ifndef _GLIBCXX_EXPERIMENTAL_SIMD_X86_CONVERSIONS_H
#define _GLIBCXX_EXPERIMENTAL_SIMD_X86_CONVERSIONS_H 
#if __cplusplus >= 201703L
template <typename _To, typename _V, typename _Traits>
_GLIBCXX_SIMD_INTRINSIC _To
__convert_x86(_V __v)
{
static_assert(__is_vector_type_v<_V>);
using _Tp = typename _Traits::value_type;
constexpr size_t _Np = _Traits::_S_full_size;
[[maybe_unused]] const auto __intrin = __to_intrin(__v);
using _Up = typename _VectorTraits<_To>::value_type;
constexpr size_t _M = _VectorTraits<_To>::_S_full_size;
[[maybe_unused]] constexpr bool __x_to_x
= sizeof(__v) <= 16 && sizeof(_To) <= 16;
[[maybe_unused]] constexpr bool __x_to_y
= sizeof(__v) <= 16 && sizeof(_To) == 32;
[[maybe_unused]] constexpr bool __x_to_z
= sizeof(__v) <= 16 && sizeof(_To) == 64;
[[maybe_unused]] constexpr bool __y_to_x
= sizeof(__v) == 32 && sizeof(_To) <= 16;
[[maybe_unused]] constexpr bool __y_to_y
= sizeof(__v) == 32 && sizeof(_To) == 32;
[[maybe_unused]] constexpr bool __y_to_z
= sizeof(__v) == 32 && sizeof(_To) == 64;
[[maybe_unused]] constexpr bool __z_to_x
= sizeof(__v) == 64 && sizeof(_To) <= 16;
[[maybe_unused]] constexpr bool __z_to_y
= sizeof(__v) == 64 && sizeof(_To) == 32;
[[maybe_unused]] constexpr bool __z_to_z
= sizeof(__v) == 64 && sizeof(_To) == 64;
[[maybe_unused]] constexpr bool __i_to_i
= is_integral_v<_Up> && is_integral_v<_Tp>;
[[maybe_unused]] constexpr bool __i8_to_i16
= __i_to_i && sizeof(_Tp) == 1 && sizeof(_Up) == 2;
[[maybe_unused]] constexpr bool __i8_to_i32
= __i_to_i && sizeof(_Tp) == 1 && sizeof(_Up) == 4;
[[maybe_unused]] constexpr bool __i8_to_i64
= __i_to_i && sizeof(_Tp) == 1 && sizeof(_Up) == 8;
[[maybe_unused]] constexpr bool __i16_to_i8
= __i_to_i && sizeof(_Tp) == 2 && sizeof(_Up) == 1;
[[maybe_unused]] constexpr bool __i16_to_i32
= __i_to_i && sizeof(_Tp) == 2 && sizeof(_Up) == 4;
[[maybe_unused]] constexpr bool __i16_to_i64
= __i_to_i && sizeof(_Tp) == 2 && sizeof(_Up) == 8;
[[maybe_unused]] constexpr bool __i32_to_i8
= __i_to_i && sizeof(_Tp) == 4 && sizeof(_Up) == 1;
[[maybe_unused]] constexpr bool __i32_to_i16
= __i_to_i && sizeof(_Tp) == 4 && sizeof(_Up) == 2;
[[maybe_unused]] constexpr bool __i32_to_i64
= __i_to_i && sizeof(_Tp) == 4 && sizeof(_Up) == 8;
[[maybe_unused]] constexpr bool __i64_to_i8
= __i_to_i && sizeof(_Tp) == 8 && sizeof(_Up) == 1;
[[maybe_unused]] constexpr bool __i64_to_i16
= __i_to_i && sizeof(_Tp) == 8 && sizeof(_Up) == 2;
[[maybe_unused]] constexpr bool __i64_to_i32
= __i_to_i && sizeof(_Tp) == 8 && sizeof(_Up) == 4;
[[maybe_unused]] constexpr bool __s64_to_f32
= is_integral_v<_Tp> && is_signed_v<_Tp> && sizeof(_Tp) == 8
&& is_floating_point_v<_Up> && sizeof(_Up) == 4;
[[maybe_unused]] constexpr bool __s32_to_f32
= is_integral_v<_Tp> && is_signed_v<_Tp> && sizeof(_Tp) == 4
&& is_floating_point_v<_Up> && sizeof(_Up) == 4;
[[maybe_unused]] constexpr bool __s16_to_f32
= is_integral_v<_Tp> && is_signed_v<_Tp> && sizeof(_Tp) == 2
&& is_floating_point_v<_Up> && sizeof(_Up) == 4;
[[maybe_unused]] constexpr bool __s8_to_f32
= is_integral_v<_Tp> && is_signed_v<_Tp> && sizeof(_Tp) == 1
&& is_floating_point_v<_Up> && sizeof(_Up) == 4;
[[maybe_unused]] constexpr bool __u64_to_f32
= is_integral_v<_Tp> && is_unsigned_v<_Tp> && sizeof(_Tp) == 8
&& is_floating_point_v<_Up> && sizeof(_Up) == 4;
[[maybe_unused]] constexpr bool __u32_to_f32
= is_integral_v<_Tp> && is_unsigned_v<_Tp> && sizeof(_Tp) == 4
&& is_floating_point_v<_Up> && sizeof(_Up) == 4;
[[maybe_unused]] constexpr bool __u16_to_f32
= is_integral_v<_Tp> && is_unsigned_v<_Tp> && sizeof(_Tp) == 2
&& is_floating_point_v<_Up> && sizeof(_Up) == 4;
[[maybe_unused]] constexpr bool __u8_to_f32
= is_integral_v<_Tp> && is_unsigned_v<_Tp> && sizeof(_Tp) == 1
&& is_floating_point_v<_Up> && sizeof(_Up) == 4;
[[maybe_unused]] constexpr bool __s64_to_f64
= is_integral_v<_Tp> && is_signed_v<_Tp> && sizeof(_Tp) == 8
&& is_floating_point_v<_Up> && sizeof(_Up) == 8;
[[maybe_unused]] constexpr bool __s32_to_f64
= is_integral_v<_Tp> && is_signed_v<_Tp> && sizeof(_Tp) == 4
&& is_floating_point_v<_Up> && sizeof(_Up) == 8;
[[maybe_unused]] constexpr bool __u64_to_f64
= is_integral_v<_Tp> && is_unsigned_v<_Tp> && sizeof(_Tp) == 8
&& is_floating_point_v<_Up> && sizeof(_Up) == 8;
[[maybe_unused]] constexpr bool __u32_to_f64
= is_integral_v<_Tp> && is_unsigned_v<_Tp> && sizeof(_Tp) == 4
&& is_floating_point_v<_Up> && sizeof(_Up) == 8;
[[maybe_unused]] constexpr bool __f32_to_s64
= is_integral_v<_Up> && is_signed_v<_Up> && sizeof(_Up) == 8
&& is_floating_point_v<_Tp> && sizeof(_Tp) == 4;
[[maybe_unused]] constexpr bool __f32_to_s32
= is_integral_v<_Up> && is_signed_v<_Up> && sizeof(_Up) == 4
&& is_floating_point_v<_Tp> && sizeof(_Tp) == 4;
[[maybe_unused]] constexpr bool __f32_to_u64
= is_integral_v<_Up> && is_unsigned_v<_Up> && sizeof(_Up) == 8
&& is_floating_point_v<_Tp> && sizeof(_Tp) == 4;
[[maybe_unused]] constexpr bool __f32_to_u32
= is_integral_v<_Up> && is_unsigned_v<_Up> && sizeof(_Up) == 4
&& is_floating_point_v<_Tp> && sizeof(_Tp) == 4;
[[maybe_unused]] constexpr bool __f64_to_s64
= is_integral_v<_Up> && is_signed_v<_Up> && sizeof(_Up) == 8
&& is_floating_point_v<_Tp> && sizeof(_Tp) == 8;
[[maybe_unused]] constexpr bool __f64_to_s32
= is_integral_v<_Up> && is_signed_v<_Up> && sizeof(_Up) == 4
&& is_floating_point_v<_Tp> && sizeof(_Tp) == 8;
[[maybe_unused]] constexpr bool __f64_to_u64
= is_integral_v<_Up> && is_unsigned_v<_Up> && sizeof(_Up) == 8
&& is_floating_point_v<_Tp> && sizeof(_Tp) == 8;
[[maybe_unused]] constexpr bool __f64_to_u32
= is_integral_v<_Up> && is_unsigned_v<_Up> && sizeof(_Up) == 4
&& is_floating_point_v<_Tp> && sizeof(_Tp) == 8;
[[maybe_unused]] constexpr bool __ibw_to_f32
= is_integral_v<_Tp> && sizeof(_Tp) <= 2
&& is_floating_point_v<_Up> && sizeof(_Up) == 4;
[[maybe_unused]] constexpr bool __ibw_to_f64
= is_integral_v<_Tp> && sizeof(_Tp) <= 2
&& is_floating_point_v<_Up> && sizeof(_Up) == 8;
[[maybe_unused]] constexpr bool __f32_to_ibw
= is_integral_v<_Up> && sizeof(_Up) <= 2
&& is_floating_point_v<_Tp> && sizeof(_Tp) == 4;
[[maybe_unused]] constexpr bool __f64_to_ibw
= is_integral_v<_Up> && sizeof(_Up) <= 2
&& is_floating_point_v<_Tp> && sizeof(_Tp) == 8;
[[maybe_unused]] constexpr bool __f32_to_f64
= is_floating_point_v<_Tp> && sizeof(_Tp) == 4
&& is_floating_point_v<_Up> && sizeof(_Up) == 8;
[[maybe_unused]] constexpr bool __f64_to_f32
= is_floating_point_v<_Tp> && sizeof(_Tp) == 8
&& is_floating_point_v<_Up> && sizeof(_Up) == 4;
if constexpr (__i_to_i && __y_to_x && !__have_avx2)
return __convert_x86<_To>(__lo128(__v), __hi128(__v));
else if constexpr (__i_to_i && __x_to_y && !__have_avx2)
return __concat(__convert_x86<__vector_type_t<_Up, _M / 2>>(__v),
__convert_x86<__vector_type_t<_Up, _M / 2>>(
__extract_part<1, _Np / _M * 2>(__v)));
else if constexpr (__i_to_i)
{
static_assert(__x_to_x || __have_avx2,
"integral conversions with ymm registers require AVX2");
static_assert(__have_avx512bw
|| ((sizeof(_Tp) >= 4 || sizeof(__v) < 64)
&& (sizeof(_Up) >= 4 || sizeof(_To) < 64)),
"8/16-bit integers in zmm registers require AVX512BW");
static_assert((sizeof(__v) < 64 && sizeof(_To) < 64) || __have_avx512f,
"integral conversions with ymm registers require AVX2");
}
if constexpr (is_floating_point_v<_Tp> == is_floating_point_v<_Up> &&
sizeof(_Tp) == sizeof(_Up))
{
if constexpr (_Np >= _M)
return __intrin_bitcast<_To>(__v);
else
return __zero_extend(__vector_bitcast<_Up>(__v));
}
else if constexpr (_Np < _M && sizeof(_To) > 16)
return __zero_extend(
__convert_x86<__vector_type_t<
_Up, (16 / sizeof(_Up) > _Np) ? 16 / sizeof(_Up) : _Np>>(__v));
else if constexpr (_Np > _M && sizeof(__v) > 16)
return __convert_x86<_To>(__extract_part<0, _Np / _M>(__v));
else if constexpr (__i64_to_i32)
{
if constexpr (__x_to_x && __have_avx512vl)
return __intrin_bitcast<_To>(_mm_cvtepi64_epi32(__intrin));
else if constexpr (__x_to_x)
return __auto_bitcast(
_mm_shuffle_ps(__vector_bitcast<float>(__v), __m128(), 8));
else if constexpr (__y_to_x && __have_avx512vl)
return __intrin_bitcast<_To>(_mm256_cvtepi64_epi32(__intrin));
else if constexpr (__y_to_x && __have_avx512f)
return __intrin_bitcast<_To>(
__lo128(_mm512_cvtepi64_epi32(__auto_bitcast(__v))));
else if constexpr (__y_to_x)
return __intrin_bitcast<_To>(
__lo128(_mm256_permute4x64_epi64(_mm256_shuffle_epi32(__intrin, 8),
0 + 4 * 2)));
else if constexpr (__z_to_y)
return __intrin_bitcast<_To>(_mm512_cvtepi64_epi32(__intrin));
}
else if constexpr (__i64_to_i16)
{
if constexpr (__x_to_x && __have_avx512vl)
return __intrin_bitcast<_To>(_mm_cvtepi64_epi16(__intrin));
else if constexpr (__x_to_x && __have_avx512f)
return __intrin_bitcast<_To>(
__lo128(_mm512_cvtepi64_epi16(__auto_bitcast(__v))));
else if constexpr (__x_to_x && __have_ssse3)
{
return __intrin_bitcast<_To>(
_mm_shuffle_epi8(__intrin,
_mm_setr_epi8(0, 1, 8, 9, -0x80, -0x80, -0x80,
-0x80, -0x80, -0x80, -0x80, -0x80,
-0x80, -0x80, -0x80, -0x80)));
}
else if constexpr (__y_to_x && __have_avx512vl)
return __intrin_bitcast<_To>(_mm256_cvtepi64_epi16(__intrin));
else if constexpr (__y_to_x && __have_avx512f)
return __intrin_bitcast<_To>(
__lo128(_mm512_cvtepi64_epi16(__auto_bitcast(__v))));
else if constexpr (__y_to_x)
{
const auto __a = _mm256_shuffle_epi8(
__intrin,
_mm256_setr_epi8(0, 1, 8, 9, -0x80, -0x80, -0x80, -0x80, -0x80,
-0x80, -0x80, -0x80, -0x80, -0x80, -0x80, -0x80,
-0x80, -0x80, -0x80, -0x80, 0, 1, 8, 9, -0x80,
-0x80, -0x80, -0x80, -0x80, -0x80, -0x80, -0x80));
return __intrin_bitcast<_To>(__lo128(__a) | __hi128(__a));
}
else if constexpr (__z_to_x)
return __intrin_bitcast<_To>(_mm512_cvtepi64_epi16(__intrin));
}
else if constexpr (__i64_to_i8)
{
if constexpr (__x_to_x && __have_avx512vl)
return __intrin_bitcast<_To>(_mm_cvtepi64_epi8(__intrin));
else if constexpr (__x_to_x && __have_avx512f)
return __intrin_bitcast<_To>(
__lo128(_mm512_cvtepi64_epi8(__zero_extend(__intrin))));
else if constexpr (__y_to_x && __have_avx512vl)
return __intrin_bitcast<_To>(_mm256_cvtepi64_epi8(__intrin));
else if constexpr (__y_to_x && __have_avx512f)
return __intrin_bitcast<_To>(
_mm512_cvtepi64_epi8(__zero_extend(__intrin)));
else if constexpr (__z_to_x)
return __intrin_bitcast<_To>(_mm512_cvtepi64_epi8(__intrin));
}
else if constexpr (__i32_to_i64)
{
if constexpr (__have_sse4_1 && __x_to_x)
return __intrin_bitcast<_To>(is_signed_v<_Tp>
? _mm_cvtepi32_epi64(__intrin)
: _mm_cvtepu32_epi64(__intrin));
else if constexpr (__x_to_x)
{
return __intrin_bitcast<_To>(
_mm_unpacklo_epi32(__intrin, is_signed_v<_Tp>
? _mm_srai_epi32(__intrin, 31)
: __m128i()));
}
else if constexpr (__x_to_y)
return __intrin_bitcast<_To>(is_signed_v<_Tp>
? _mm256_cvtepi32_epi64(__intrin)
: _mm256_cvtepu32_epi64(__intrin));
else if constexpr (__y_to_z)
return __intrin_bitcast<_To>(is_signed_v<_Tp>
? _mm512_cvtepi32_epi64(__intrin)
: _mm512_cvtepu32_epi64(__intrin));
}
else if constexpr (__i32_to_i16)
{
if constexpr (__x_to_x && __have_avx512vl)
return __intrin_bitcast<_To>(_mm_cvtepi32_epi16(__intrin));
else if constexpr (__x_to_x && __have_avx512f)
return __intrin_bitcast<_To>(
__lo128(_mm512_cvtepi32_epi16(__auto_bitcast(__v))));
else if constexpr (__x_to_x && __have_ssse3)
return __intrin_bitcast<_To>(_mm_shuffle_epi8(
__intrin, _mm_setr_epi8(0, 1, 4, 5, 8, 9, 12, 13, -0x80, -0x80, -0x80,
-0x80, -0x80, -0x80, -0x80, -0x80)));
else if constexpr (__x_to_x)
{
auto __a = _mm_unpacklo_epi16(__intrin, __m128i());
auto __b = _mm_unpackhi_epi16(__intrin, __m128i());
auto __c = _mm_unpacklo_epi16(__a, __b);
auto __d = _mm_unpackhi_epi16(__a, __b);
return __intrin_bitcast<_To>(
_mm_unpacklo_epi16(__c, __d));
}
else if constexpr (__y_to_x && __have_avx512vl)
return __intrin_bitcast<_To>(_mm256_cvtepi32_epi16(__intrin));
else if constexpr (__y_to_x && __have_avx512f)
return __intrin_bitcast<_To>(
__lo128(_mm512_cvtepi32_epi16(__auto_bitcast(__v))));
else if constexpr (__y_to_x)
{
auto __a = _mm256_shuffle_epi8(
__intrin,
_mm256_setr_epi8(0, 1, 4, 5, 8, 9, 12, 13, -0x80, -0x80, -0x80,
-0x80, -0x80, -0x80, -0x80, -0x80, 0, 1, 4, 5, 8,
9, 12, 13, -0x80, -0x80, -0x80, -0x80, -0x80,
-0x80, -0x80, -0x80));
return __intrin_bitcast<_To>(__lo128(
_mm256_permute4x64_epi64(__a,
0xf8)));
}
else if constexpr (__z_to_y)
return __intrin_bitcast<_To>(_mm512_cvtepi32_epi16(__intrin));
}
else if constexpr (__i32_to_i8)
{
if constexpr (__x_to_x && __have_avx512vl)
return __intrin_bitcast<_To>(_mm_cvtepi32_epi8(__intrin));
else if constexpr (__x_to_x && __have_avx512f)
return __intrin_bitcast<_To>(
__lo128(_mm512_cvtepi32_epi8(__zero_extend(__intrin))));
else if constexpr (__x_to_x && __have_ssse3)
{
return __intrin_bitcast<_To>(
_mm_shuffle_epi8(__intrin,
_mm_setr_epi8(0, 4, 8, 12, -0x80, -0x80, -0x80,
-0x80, -0x80, -0x80, -0x80, -0x80,
-0x80, -0x80, -0x80, -0x80)));
}
else if constexpr (__x_to_x)
{
const auto __a
= _mm_unpacklo_epi8(__intrin, __intrin);
const auto __b
= _mm_unpackhi_epi8(__intrin, __intrin);
const auto __c = _mm_unpacklo_epi8(__a, __b);
const auto __d = _mm_unpackhi_epi8(__a, __b);
const auto __e = _mm_unpacklo_epi8(__c, __d);
return __intrin_bitcast<_To>(__e & _mm_cvtsi32_si128(-1));
}
else if constexpr (__y_to_x && __have_avx512vl)
return __intrin_bitcast<_To>(_mm256_cvtepi32_epi8(__intrin));
else if constexpr (__y_to_x && __have_avx512f)
return __intrin_bitcast<_To>(
_mm512_cvtepi32_epi8(__zero_extend(__intrin)));
else if constexpr (__z_to_x)
return __intrin_bitcast<_To>(_mm512_cvtepi32_epi8(__intrin));
}
else if constexpr (__i16_to_i64)
{
if constexpr (__x_to_x && __have_sse4_1)
return __intrin_bitcast<_To>(is_signed_v<_Tp>
? _mm_cvtepi16_epi64(__intrin)
: _mm_cvtepu16_epi64(__intrin));
else if constexpr (__x_to_x && is_signed_v<_Tp>)
{
auto __x = _mm_srai_epi16(__intrin, 15);
auto __y = _mm_unpacklo_epi16(__intrin, __x);
__x = _mm_unpacklo_epi16(__x, __x);
return __intrin_bitcast<_To>(_mm_unpacklo_epi32(__y, __x));
}
else if constexpr (__x_to_x)
return __intrin_bitcast<_To>(
_mm_unpacklo_epi32(_mm_unpacklo_epi16(__intrin, __m128i()),
__m128i()));
else if constexpr (__x_to_y)
return __intrin_bitcast<_To>(is_signed_v<_Tp>
? _mm256_cvtepi16_epi64(__intrin)
: _mm256_cvtepu16_epi64(__intrin));
else if constexpr (__x_to_z)
return __intrin_bitcast<_To>(is_signed_v<_Tp>
? _mm512_cvtepi16_epi64(__intrin)
: _mm512_cvtepu16_epi64(__intrin));
}
else if constexpr (__i16_to_i32)
{
if constexpr (__x_to_x && __have_sse4_1)
return __intrin_bitcast<_To>(is_signed_v<_Tp>
? _mm_cvtepi16_epi32(__intrin)
: _mm_cvtepu16_epi32(__intrin));
else if constexpr (__x_to_x && is_signed_v<_Tp>)
return __intrin_bitcast<_To>(
_mm_srai_epi32(_mm_unpacklo_epi16(__intrin, __intrin), 16));
else if constexpr (__x_to_x && is_unsigned_v<_Tp>)
return __intrin_bitcast<_To>(_mm_unpacklo_epi16(__intrin, __m128i()));
else if constexpr (__x_to_y)
return __intrin_bitcast<_To>(is_signed_v<_Tp>
? _mm256_cvtepi16_epi32(__intrin)
: _mm256_cvtepu16_epi32(__intrin));
else if constexpr (__y_to_z)
return __intrin_bitcast<_To>(is_signed_v<_Tp>
? _mm512_cvtepi16_epi32(__intrin)
: _mm512_cvtepu16_epi32(__intrin));
}
else if constexpr (__i16_to_i8)
{
if constexpr (__x_to_x && __have_avx512bw_vl)
return __intrin_bitcast<_To>(_mm_cvtepi16_epi8(__intrin));
else if constexpr (__x_to_x && __have_avx512bw)
return __intrin_bitcast<_To>(
__lo128(_mm512_cvtepi16_epi8(__zero_extend(__intrin))));
else if constexpr (__x_to_x && __have_ssse3)
return __intrin_bitcast<_To>(_mm_shuffle_epi8(
__intrin, _mm_setr_epi8(0, 2, 4, 6, 8, 10, 12, 14, -0x80, -0x80,
-0x80, -0x80, -0x80, -0x80, -0x80, -0x80)));
else if constexpr (__x_to_x)
{
auto __a
= _mm_unpacklo_epi8(__intrin, __intrin);
auto __b
= _mm_unpackhi_epi8(__intrin, __intrin);
auto __c = _mm_unpacklo_epi8(__a, __b);
auto __d = _mm_unpackhi_epi8(__a, __b);
auto __e = _mm_unpacklo_epi8(__c, __d);
auto __f = _mm_unpackhi_epi8(__c, __d);
return __intrin_bitcast<_To>(_mm_unpacklo_epi8(__e, __f));
}
else if constexpr (__y_to_x && __have_avx512bw_vl)
return __intrin_bitcast<_To>(_mm256_cvtepi16_epi8(__intrin));
else if constexpr (__y_to_x && __have_avx512bw)
return __intrin_bitcast<_To>(
__lo256(_mm512_cvtepi16_epi8(__zero_extend(__intrin))));
else if constexpr (__y_to_x)
{
auto __a = _mm256_shuffle_epi8(
__intrin,
_mm256_setr_epi8(0, 2, 4, 6, 8, 10, 12, 14, -0x80, -0x80, -0x80,
-0x80, -0x80, -0x80, -0x80, -0x80, -0x80, -0x80,
-0x80, -0x80, -0x80, -0x80, -0x80, -0x80, 0, 2, 4,
6, 8, 10, 12, 14));
return __intrin_bitcast<_To>(__lo128(__a) | __hi128(__a));
}
else if constexpr (__z_to_y && __have_avx512bw)
return __intrin_bitcast<_To>(_mm512_cvtepi16_epi8(__intrin));
else if constexpr (__z_to_y)
__assert_unreachable<_Tp>();
}
else if constexpr (__i8_to_i64)
{
if constexpr (__x_to_x && __have_sse4_1)
return __intrin_bitcast<_To>(is_signed_v<_Tp>
? _mm_cvtepi8_epi64(__intrin)
: _mm_cvtepu8_epi64(__intrin));
else if constexpr (__x_to_x && is_signed_v<_Tp>)
{
if constexpr (__have_ssse3)
{
auto __dup = _mm_unpacklo_epi8(__intrin, __intrin);
auto __epi16 = _mm_srai_epi16(__dup, 8);
_mm_shuffle_epi8(__epi16, _mm_setr_epi8(0, 1, 1, 1, 1, 1, 1, 1, 2,
3, 3, 3, 3, 3, 3, 3));
}
else
{
auto __x = _mm_unpacklo_epi8(__intrin, __intrin);
__x = _mm_unpacklo_epi16(__x, __x);
return __intrin_bitcast<_To>(
_mm_unpacklo_epi32(_mm_srai_epi32(__x, 24),
_mm_srai_epi32(__x, 31)));
}
}
else if constexpr (__x_to_x)
{
return __intrin_bitcast<_To>(_mm_unpacklo_epi32(
_mm_unpacklo_epi16(_mm_unpacklo_epi8(__intrin, __m128i()),
__m128i()),
__m128i()));
}
else if constexpr (__x_to_y)
return __intrin_bitcast<_To>(is_signed_v<_Tp>
? _mm256_cvtepi8_epi64(__intrin)
: _mm256_cvtepu8_epi64(__intrin));
else if constexpr (__x_to_z)
return __intrin_bitcast<_To>(is_signed_v<_Tp>
? _mm512_cvtepi8_epi64(__intrin)
: _mm512_cvtepu8_epi64(__intrin));
}
else if constexpr (__i8_to_i32)
{
if constexpr (__x_to_x && __have_sse4_1)
return __intrin_bitcast<_To>(is_signed_v<_Tp>
? _mm_cvtepi8_epi32(__intrin)
: _mm_cvtepu8_epi32(__intrin));
else if constexpr (__x_to_x && is_signed_v<_Tp>)
{
const auto __x = _mm_unpacklo_epi8(__intrin, __intrin);
return __intrin_bitcast<_To>(
_mm_srai_epi32(_mm_unpacklo_epi16(__x, __x), 24));
}
else if constexpr (__x_to_x && is_unsigned_v<_Tp>)
return __intrin_bitcast<_To>(
_mm_unpacklo_epi16(_mm_unpacklo_epi8(__intrin, __m128i()),
__m128i()));
else if constexpr (__x_to_y)
return __intrin_bitcast<_To>(is_signed_v<_Tp>
? _mm256_cvtepi8_epi32(__intrin)
: _mm256_cvtepu8_epi32(__intrin));
else if constexpr (__x_to_z)
return __intrin_bitcast<_To>(is_signed_v<_Tp>
? _mm512_cvtepi8_epi32(__intrin)
: _mm512_cvtepu8_epi32(__intrin));
}
else if constexpr (__i8_to_i16)
{
if constexpr (__x_to_x && __have_sse4_1)
return __intrin_bitcast<_To>(is_signed_v<_Tp>
? _mm_cvtepi8_epi16(__intrin)
: _mm_cvtepu8_epi16(__intrin));
else if constexpr (__x_to_x && is_signed_v<_Tp>)
return __intrin_bitcast<_To>(
_mm_srai_epi16(_mm_unpacklo_epi8(__intrin, __intrin), 8));
else if constexpr (__x_to_x && is_unsigned_v<_Tp>)
return __intrin_bitcast<_To>(_mm_unpacklo_epi8(__intrin, __m128i()));
else if constexpr (__x_to_y)
return __intrin_bitcast<_To>(is_signed_v<_Tp>
? _mm256_cvtepi8_epi16(__intrin)
: _mm256_cvtepu8_epi16(__intrin));
else if constexpr (__y_to_z && __have_avx512bw)
return __intrin_bitcast<_To>(is_signed_v<_Tp>
? _mm512_cvtepi8_epi16(__intrin)
: _mm512_cvtepu8_epi16(__intrin));
else if constexpr (__y_to_z)
__assert_unreachable<_Tp>();
}
else if constexpr (__f32_to_s64)
{
if constexpr (__have_avx512dq_vl && __x_to_x)
return __intrin_bitcast<_To>(_mm_cvttps_epi64(__intrin));
else if constexpr (__have_avx512dq_vl && __x_to_y)
return __intrin_bitcast<_To>(_mm256_cvttps_epi64(__intrin));
else if constexpr (__have_avx512dq && __y_to_z)
return __intrin_bitcast<_To>(_mm512_cvttps_epi64(__intrin));
}
else if constexpr (__f32_to_u64)
{
if constexpr (__have_avx512dq_vl && __x_to_x)
return __intrin_bitcast<_To>(_mm_cvttps_epu64(__intrin));
else if constexpr (__have_avx512dq_vl && __x_to_y)
return __intrin_bitcast<_To>(_mm256_cvttps_epu64(__intrin));
else if constexpr (__have_avx512dq && __y_to_z)
return __intrin_bitcast<_To>(_mm512_cvttps_epu64(__intrin));
}
else if constexpr (__f32_to_s32)
{
if constexpr (__x_to_x || __y_to_y || __z_to_z)
{
}
else
__assert_unreachable<_Tp>();
}
else if constexpr (__f32_to_u32)
{
if constexpr (__have_avx512vl && __x_to_x)
return __auto_bitcast(_mm_cvttps_epu32(__intrin));
else if constexpr (__have_avx512f && __x_to_x)
return __auto_bitcast(
__lo128(_mm512_cvttps_epu32(__auto_bitcast(__v))));
else if constexpr (__have_avx512vl && __y_to_y)
return __vector_bitcast<_Up>(_mm256_cvttps_epu32(__intrin));
else if constexpr (__have_avx512f && __y_to_y)
return __vector_bitcast<_Up>(
__lo256(_mm512_cvttps_epu32(__auto_bitcast(__v))));
else if constexpr (__x_to_x || __y_to_y || __z_to_z)
{
}
else
__assert_unreachable<_Tp>();
}
else if constexpr (__f32_to_ibw)
return __convert_x86<_To>(__convert_x86<__vector_type_t<int, _Np>>(__v));
else if constexpr (__f64_to_s64)
{
if constexpr (__have_avx512dq_vl && __x_to_x)
return __intrin_bitcast<_To>(_mm_cvttpd_epi64(__intrin));
else if constexpr (__have_avx512dq_vl && __y_to_y)
return __intrin_bitcast<_To>(_mm256_cvttpd_epi64(__intrin));
else if constexpr (__have_avx512dq && __z_to_z)
return __intrin_bitcast<_To>(_mm512_cvttpd_epi64(__intrin));
}
else if constexpr (__f64_to_u64)
{
if constexpr (__have_avx512dq_vl && __x_to_x)
return __intrin_bitcast<_To>(_mm_cvttpd_epu64(__intrin));
else if constexpr (__have_avx512dq_vl && __y_to_y)
return __intrin_bitcast<_To>(_mm256_cvttpd_epu64(__intrin));
else if constexpr (__have_avx512dq && __z_to_z)
return __intrin_bitcast<_To>(_mm512_cvttpd_epu64(__intrin));
}
else if constexpr (__f64_to_s32)
{
if constexpr (__x_to_x)
return __intrin_bitcast<_To>(_mm_cvttpd_epi32(__intrin));
else if constexpr (__y_to_x)
return __intrin_bitcast<_To>(_mm256_cvttpd_epi32(__intrin));
else if constexpr (__z_to_y)
return __intrin_bitcast<_To>(_mm512_cvttpd_epi32(__intrin));
}
else if constexpr (__f64_to_u32)
{
if constexpr (__have_avx512vl && __x_to_x)
return __intrin_bitcast<_To>(_mm_cvttpd_epu32(__intrin));
else if constexpr (__have_sse4_1 && __x_to_x)
return __vector_bitcast<_Up, _M>(
_mm_cvttpd_epi32(_mm_floor_pd(__intrin) - 0x8000'0000u))
^ 0x8000'0000u;
else if constexpr (__x_to_x)
{
}
else if constexpr (__have_avx512vl && __y_to_x)
return __intrin_bitcast<_To>(_mm256_cvttpd_epu32(__intrin));
else if constexpr (__y_to_x)
{
return __intrin_bitcast<_To>(
__vector_bitcast<_Up>(
_mm256_cvttpd_epi32(_mm256_floor_pd(__intrin) - 0x8000'0000u))
^ 0x8000'0000u);
}
else if constexpr (__z_to_y)
return __intrin_bitcast<_To>(_mm512_cvttpd_epu32(__intrin));
}
else if constexpr (__f64_to_ibw)
{
return __convert_x86<_To>(
__convert_x86<__vector_type_t<int, (_Np < 4 ? 4 : _Np)>>(__v));
}
else if constexpr (__s64_to_f32)
{
if constexpr (__x_to_x && __have_avx512dq_vl)
return __intrin_bitcast<_To>(_mm_cvtepi64_ps(__intrin));
else if constexpr (__y_to_x && __have_avx512dq_vl)
return __intrin_bitcast<_To>(_mm256_cvtepi64_ps(__intrin));
else if constexpr (__z_to_y && __have_avx512dq)
return __intrin_bitcast<_To>(_mm512_cvtepi64_ps(__intrin));
else if constexpr (__z_to_y)
return __intrin_bitcast<_To>(
_mm512_cvtpd_ps(__convert_x86<__vector_type_t<double, 8>>(__v)));
}
else if constexpr (__u64_to_f32)
{
if constexpr (__x_to_x && __have_avx512dq_vl)
return __intrin_bitcast<_To>(_mm_cvtepu64_ps(__intrin));
else if constexpr (__y_to_x && __have_avx512dq_vl)
return __intrin_bitcast<_To>(_mm256_cvtepu64_ps(__intrin));
else if constexpr (__z_to_y && __have_avx512dq)
return __intrin_bitcast<_To>(_mm512_cvtepu64_ps(__intrin));
else if constexpr (__z_to_y)
{
return __intrin_bitcast<_To>(
__lo256(_mm512_cvtepu32_ps(__auto_bitcast(
_mm512_cvtepi64_epi32(_mm512_srai_epi64(__intrin, 32)))))
* 0x100000000LL
+ __lo256(_mm512_cvtepu32_ps(
__auto_bitcast(_mm512_cvtepi64_epi32(__intrin)))));
}
}
else if constexpr (__s32_to_f32)
{
}
else if constexpr (__u32_to_f32)
{
if constexpr (__x_to_x && __have_avx512vl)
{
}
else if constexpr (__x_to_x && __have_avx512f)
return __intrin_bitcast<_To>(
__lo128(_mm512_cvtepu32_ps(__auto_bitcast(__v))));
else if constexpr (__x_to_x && (__have_fma || __have_fma4))
return __auto_bitcast(0x10000 * _mm_cvtepi32_ps(__to_intrin(__v >> 16))
+ _mm_cvtepi32_ps(__to_intrin(__v & 0xffff)));
else if constexpr (__y_to_y && __have_avx512vl)
{
}
else if constexpr (__y_to_y && __have_avx512f)
return __intrin_bitcast<_To>(
__lo256(_mm512_cvtepu32_ps(__auto_bitcast(__v))));
else if constexpr (__y_to_y)
return 0x10000 * _mm256_cvtepi32_ps(__to_intrin(__v >> 16))
+ _mm256_cvtepi32_ps(__to_intrin(__v & 0xffff));
}
else if constexpr (__ibw_to_f32)
{
if constexpr (_M <= 4 || __have_avx2)
return __convert_x86<_To>(__convert_x86<__vector_type_t<int, _M>>(__v));
else
{
static_assert(__x_to_y);
__m128i __a, __b;
if constexpr (__have_sse4_1)
{
__a = sizeof(_Tp) == 2
? (is_signed_v<_Tp> ? _mm_cvtepi16_epi32(__intrin)
: _mm_cvtepu16_epi32(__intrin))
: (is_signed_v<_Tp> ? _mm_cvtepi8_epi32(__intrin)
: _mm_cvtepu8_epi32(__intrin));
const auto __w
= _mm_shuffle_epi32(__intrin, sizeof(_Tp) == 2 ? 0xee : 0xe9);
__b = sizeof(_Tp) == 2
? (is_signed_v<_Tp> ? _mm_cvtepi16_epi32(__w)
: _mm_cvtepu16_epi32(__w))
: (is_signed_v<_Tp> ? _mm_cvtepi8_epi32(__w)
: _mm_cvtepu8_epi32(__w));
}
else
{
__m128i __tmp;
if constexpr (sizeof(_Tp) == 1)
{
__tmp
= is_signed_v<_Tp>
? _mm_srai_epi16(_mm_unpacklo_epi8(__intrin, __intrin),
8)
: _mm_unpacklo_epi8(__intrin, __m128i());
}
else
{
static_assert(sizeof(_Tp) == 2);
__tmp = __intrin;
}
__a = is_signed_v<_Tp>
? _mm_srai_epi32(_mm_unpacklo_epi16(__tmp, __tmp), 16)
: _mm_unpacklo_epi16(__tmp, __m128i());
__b = is_signed_v<_Tp>
? _mm_srai_epi32(_mm_unpackhi_epi16(__tmp, __tmp), 16)
: _mm_unpackhi_epi16(__tmp, __m128i());
}
return __convert_x86<_To>(__vector_bitcast<int>(__a),
__vector_bitcast<int>(__b));
}
}
else if constexpr (__s64_to_f64)
{
if constexpr (__x_to_x && __have_avx512dq_vl)
return __intrin_bitcast<_To>(_mm_cvtepi64_pd(__intrin));
else if constexpr (__y_to_y && __have_avx512dq_vl)
return __intrin_bitcast<_To>(_mm256_cvtepi64_pd(__intrin));
else if constexpr (__z_to_z && __have_avx512dq)
return __intrin_bitcast<_To>(_mm512_cvtepi64_pd(__intrin));
else if constexpr (__z_to_z)
{
return __intrin_bitcast<_To>(
_mm512_cvtepi32_pd(_mm512_cvtepi64_epi32(__to_intrin(__v >> 32)))
* 0x100000000LL
+ _mm512_cvtepu32_pd(_mm512_cvtepi64_epi32(__intrin)));
}
}
else if constexpr (__u64_to_f64)
{
if constexpr (__x_to_x && __have_avx512dq_vl)
return __intrin_bitcast<_To>(_mm_cvtepu64_pd(__intrin));
else if constexpr (__y_to_y && __have_avx512dq_vl)
return __intrin_bitcast<_To>(_mm256_cvtepu64_pd(__intrin));
else if constexpr (__z_to_z && __have_avx512dq)
return __intrin_bitcast<_To>(_mm512_cvtepu64_pd(__intrin));
else if constexpr (__z_to_z)
{
return __intrin_bitcast<_To>(
_mm512_cvtepu32_pd(_mm512_cvtepi64_epi32(__to_intrin(__v >> 32)))
* 0x100000000LL
+ _mm512_cvtepu32_pd(_mm512_cvtepi64_epi32(__intrin)));
}
}
else if constexpr (__s32_to_f64)
{
if constexpr (__x_to_x)
return __intrin_bitcast<_To>(_mm_cvtepi32_pd(__intrin));
else if constexpr (__x_to_y)
return __intrin_bitcast<_To>(_mm256_cvtepi32_pd(__intrin));
else if constexpr (__y_to_z)
return __intrin_bitcast<_To>(_mm512_cvtepi32_pd(__intrin));
}
else if constexpr (__u32_to_f64)
{
if constexpr (__x_to_x && __have_avx512vl)
return __intrin_bitcast<_To>(_mm_cvtepu32_pd(__intrin));
else if constexpr (__x_to_x && __have_avx512f)
return __intrin_bitcast<_To>(
__lo128(_mm512_cvtepu32_pd(__auto_bitcast(__v))));
else if constexpr (__x_to_x)
return __intrin_bitcast<_To>(
_mm_cvtepi32_pd(__to_intrin(__v ^ 0x8000'0000u)) + 0x8000'0000u);
else if constexpr (__x_to_y && __have_avx512vl)
return __intrin_bitcast<_To>(_mm256_cvtepu32_pd(__intrin));
else if constexpr (__x_to_y && __have_avx512f)
return __intrin_bitcast<_To>(
__lo256(_mm512_cvtepu32_pd(__auto_bitcast(__v))));
else if constexpr (__x_to_y)
return __intrin_bitcast<_To>(
_mm256_cvtepi32_pd(__to_intrin(__v ^ 0x8000'0000u)) + 0x8000'0000u);
else if constexpr (__y_to_z)
return __intrin_bitcast<_To>(_mm512_cvtepu32_pd(__intrin));
}
else if constexpr (__ibw_to_f64)
{
return __convert_x86<_To>(
__convert_x86<__vector_type_t<int, std::max(size_t(4), _M)>>(__v));
}
else if constexpr (__f32_to_f64)
{
if constexpr (__x_to_x)
return __intrin_bitcast<_To>(_mm_cvtps_pd(__intrin));
else if constexpr (__x_to_y)
return __intrin_bitcast<_To>(_mm256_cvtps_pd(__intrin));
else if constexpr (__y_to_z)
return __intrin_bitcast<_To>(_mm512_cvtps_pd(__intrin));
}
else if constexpr (__f64_to_f32)
{
if constexpr (__x_to_x)
return __intrin_bitcast<_To>(_mm_cvtpd_ps(__intrin));
else if constexpr (__y_to_x)
return __intrin_bitcast<_To>(_mm256_cvtpd_ps(__intrin));
else if constexpr (__z_to_y)
return __intrin_bitcast<_To>(_mm512_cvtpd_ps(__intrin));
}
else
__assert_unreachable<_Tp>();
return __vector_convert<_To>(__v, make_index_sequence<std::min(_M, _Np)>());
}
template <typename _To, typename _V, typename _Traits>
_GLIBCXX_SIMD_INTRINSIC _To
__convert_x86(_V __v0, _V __v1)
{
static_assert(__is_vector_type_v<_V>);
using _Tp = typename _Traits::value_type;
constexpr size_t _Np = _Traits::_S_full_size;
[[maybe_unused]] const auto __i0 = __to_intrin(__v0);
[[maybe_unused]] const auto __i1 = __to_intrin(__v1);
using _Up = typename _VectorTraits<_To>::value_type;
constexpr size_t _M = _VectorTraits<_To>::_S_full_size;
static_assert(2 * _Np <= _M, "__v1 would be discarded; use the one-argument "
"__convert_x86 overload instead");
[[maybe_unused]] constexpr bool __x_to_x
= sizeof(__v0) <= 16 && sizeof(_To) <= 16;
[[maybe_unused]] constexpr bool __x_to_y
= sizeof(__v0) <= 16 && sizeof(_To) == 32;
[[maybe_unused]] constexpr bool __x_to_z
= sizeof(__v0) <= 16 && sizeof(_To) == 64;
[[maybe_unused]] constexpr bool __y_to_x
= sizeof(__v0) == 32 && sizeof(_To) <= 16;
[[maybe_unused]] constexpr bool __y_to_y
= sizeof(__v0) == 32 && sizeof(_To) == 32;
[[maybe_unused]] constexpr bool __y_to_z
= sizeof(__v0) == 32 && sizeof(_To) == 64;
[[maybe_unused]] constexpr bool __z_to_x
= sizeof(__v0) == 64 && sizeof(_To) <= 16;
[[maybe_unused]] constexpr bool __z_to_y
= sizeof(__v0) == 64 && sizeof(_To) == 32;
[[maybe_unused]] constexpr bool __z_to_z
= sizeof(__v0) == 64 && sizeof(_To) == 64;
[[maybe_unused]] constexpr bool __i_to_i
= std::is_integral_v<_Up> && std::is_integral_v<_Tp>;
[[maybe_unused]] constexpr bool __i8_to_i16
= __i_to_i && sizeof(_Tp) == 1 && sizeof(_Up) == 2;
[[maybe_unused]] constexpr bool __i8_to_i32
= __i_to_i && sizeof(_Tp) == 1 && sizeof(_Up) == 4;
[[maybe_unused]] constexpr bool __i8_to_i64
= __i_to_i && sizeof(_Tp) == 1 && sizeof(_Up) == 8;
[[maybe_unused]] constexpr bool __i16_to_i8
= __i_to_i && sizeof(_Tp) == 2 && sizeof(_Up) == 1;
[[maybe_unused]] constexpr bool __i16_to_i32
= __i_to_i && sizeof(_Tp) == 2 && sizeof(_Up) == 4;
[[maybe_unused]] constexpr bool __i16_to_i64
= __i_to_i && sizeof(_Tp) == 2 && sizeof(_Up) == 8;
[[maybe_unused]] constexpr bool __i32_to_i8
= __i_to_i && sizeof(_Tp) == 4 && sizeof(_Up) == 1;
[[maybe_unused]] constexpr bool __i32_to_i16
= __i_to_i && sizeof(_Tp) == 4 && sizeof(_Up) == 2;
[[maybe_unused]] constexpr bool __i32_to_i64
= __i_to_i && sizeof(_Tp) == 4 && sizeof(_Up) == 8;
[[maybe_unused]] constexpr bool __i64_to_i8
= __i_to_i && sizeof(_Tp) == 8 && sizeof(_Up) == 1;
[[maybe_unused]] constexpr bool __i64_to_i16
= __i_to_i && sizeof(_Tp) == 8 && sizeof(_Up) == 2;
[[maybe_unused]] constexpr bool __i64_to_i32
= __i_to_i && sizeof(_Tp) == 8 && sizeof(_Up) == 4;
[[maybe_unused]] constexpr bool __i64_to_f32
= is_integral_v<_Tp> && sizeof(_Tp) == 8
&& is_floating_point_v<_Up> && sizeof(_Up) == 4;
[[maybe_unused]] constexpr bool __s32_to_f32
= is_integral_v<_Tp> && is_signed_v<_Tp> && sizeof(_Tp) == 4
&& is_floating_point_v<_Up> && sizeof(_Up) == 4;
[[maybe_unused]] constexpr bool __s16_to_f32
= is_integral_v<_Tp> && is_signed_v<_Tp> && sizeof(_Tp) == 2
&& is_floating_point_v<_Up> && sizeof(_Up) == 4;
[[maybe_unused]] constexpr bool __s8_to_f32
= is_integral_v<_Tp> && is_signed_v<_Tp> && sizeof(_Tp) == 1
&& is_floating_point_v<_Up> && sizeof(_Up) == 4;
[[maybe_unused]] constexpr bool __u32_to_f32
= is_integral_v<_Tp> && is_unsigned_v<_Tp> && sizeof(_Tp) == 4
&& is_floating_point_v<_Up> && sizeof(_Up) == 4;
[[maybe_unused]] constexpr bool __u16_to_f32
= is_integral_v<_Tp> && is_unsigned_v<_Tp> && sizeof(_Tp) == 2
&& is_floating_point_v<_Up> && sizeof(_Up) == 4;
[[maybe_unused]] constexpr bool __u8_to_f32
= is_integral_v<_Tp> && is_unsigned_v<_Tp> && sizeof(_Tp) == 1
&& is_floating_point_v<_Up> && sizeof(_Up) == 4;
[[maybe_unused]] constexpr bool __s64_to_f64
= is_integral_v<_Tp> && is_signed_v<_Tp> && sizeof(_Tp) == 8
&& is_floating_point_v<_Up> && sizeof(_Up) == 8;
[[maybe_unused]] constexpr bool __s32_to_f64
= is_integral_v<_Tp> && is_signed_v<_Tp> && sizeof(_Tp) == 4
&& is_floating_point_v<_Up> && sizeof(_Up) == 8;
[[maybe_unused]] constexpr bool __s16_to_f64
= is_integral_v<_Tp> && is_signed_v<_Tp> && sizeof(_Tp) == 2
&& is_floating_point_v<_Up> && sizeof(_Up) == 8;
[[maybe_unused]] constexpr bool __s8_to_f64
= is_integral_v<_Tp> && is_signed_v<_Tp> && sizeof(_Tp) == 1
&& is_floating_point_v<_Up> && sizeof(_Up) == 8;
[[maybe_unused]] constexpr bool __u64_to_f64
= is_integral_v<_Tp> && is_unsigned_v<_Tp> && sizeof(_Tp) == 8
&& is_floating_point_v<_Up> && sizeof(_Up) == 8;
[[maybe_unused]] constexpr bool __u32_to_f64
= is_integral_v<_Tp> && is_unsigned_v<_Tp> && sizeof(_Tp) == 4
&& is_floating_point_v<_Up> && sizeof(_Up) == 8;
[[maybe_unused]] constexpr bool __u16_to_f64
= is_integral_v<_Tp> && is_unsigned_v<_Tp> && sizeof(_Tp) == 2
&& is_floating_point_v<_Up> && sizeof(_Up) == 8;
[[maybe_unused]] constexpr bool __u8_to_f64
= is_integral_v<_Tp> && is_unsigned_v<_Tp> && sizeof(_Tp) == 1
&& is_floating_point_v<_Up> && sizeof(_Up) == 8;
[[maybe_unused]] constexpr bool __f32_to_s64
= is_integral_v<_Up> && is_signed_v<_Up> && sizeof(_Up) == 8
&& is_floating_point_v<_Tp> && sizeof(_Tp) == 4;
[[maybe_unused]] constexpr bool __f32_to_s32
= is_integral_v<_Up> && is_signed_v<_Up> && sizeof(_Up) == 4
&& is_floating_point_v<_Tp> && sizeof(_Tp) == 4;
[[maybe_unused]] constexpr bool __f32_to_u64
= is_integral_v<_Up> && is_unsigned_v<_Up> && sizeof(_Up) == 8
&& is_floating_point_v<_Tp> && sizeof(_Tp) == 4;
[[maybe_unused]] constexpr bool __f32_to_u32
= is_integral_v<_Up> && is_unsigned_v<_Up> && sizeof(_Up) == 4
&& is_floating_point_v<_Tp> && sizeof(_Tp) == 4;
[[maybe_unused]] constexpr bool __f64_to_s64
= is_integral_v<_Up> && is_signed_v<_Up> && sizeof(_Up) == 8
&& is_floating_point_v<_Tp> && sizeof(_Tp) == 8;
[[maybe_unused]] constexpr bool __f64_to_s32
= is_integral_v<_Up> && is_signed_v<_Up> && sizeof(_Up) == 4
&& is_floating_point_v<_Tp> && sizeof(_Tp) == 8;
[[maybe_unused]] constexpr bool __f64_to_u64
= is_integral_v<_Up> && is_unsigned_v<_Up> && sizeof(_Up) == 8
&& is_floating_point_v<_Tp> && sizeof(_Tp) == 8;
[[maybe_unused]] constexpr bool __f64_to_u32
= is_integral_v<_Up> && is_unsigned_v<_Up> && sizeof(_Up) == 4
&& is_floating_point_v<_Tp> && sizeof(_Tp) == 8;
[[maybe_unused]] constexpr bool __f32_to_ibw
= is_integral_v<_Up> && sizeof(_Up) <= 2
&& is_floating_point_v<_Tp> && sizeof(_Tp) == 4;
[[maybe_unused]] constexpr bool __f64_to_ibw
= is_integral_v<_Up> && sizeof(_Up) <= 2
&& is_floating_point_v<_Tp> && sizeof(_Tp) == 8;
[[maybe_unused]] constexpr bool __f32_to_f64
= is_floating_point_v<_Tp> && sizeof(_Tp) == 4
&& is_floating_point_v<_Up> && sizeof(_Up) == 8;
[[maybe_unused]] constexpr bool __f64_to_f32
= is_floating_point_v<_Tp> && sizeof(_Tp) == 8
&& is_floating_point_v<_Up> && sizeof(_Up) == 4;
if constexpr (__i_to_i && __y_to_x && !__have_avx2)
return __convert_x86<_To>(__lo128(__v0), __hi128(__v0), __lo128(__v1),
__hi128(__v1));
else if constexpr (__i_to_i)
{
static_assert(__x_to_x || __have_avx2,
"integral conversions with ymm registers require AVX2");
static_assert(__have_avx512bw
|| ((sizeof(_Tp) >= 4 || sizeof(__v0) < 64)
&& (sizeof(_Up) >= 4 || sizeof(_To) < 64)),
"8/16-bit integers in zmm registers require AVX512BW");
static_assert((sizeof(__v0) < 64 && sizeof(_To) < 64) || __have_avx512f,
"integral conversions with ymm registers require AVX2");
}
if constexpr (sizeof(__v0) < 16 || (sizeof(__v0) == 16 && __have_avx2)
|| (sizeof(__v0) == 16 && __have_avx
&& std::is_floating_point_v<_Tp>)
|| (sizeof(__v0) == 32 && __have_avx512f
&& (sizeof(_Tp) >= 4 || __have_avx512bw)))
{
return __convert_x86<_To>(__concat(__v0, __v1));
}
else
{
static_assert(!(
std::is_floating_point_v<
_Tp> == std::is_floating_point_v<_Up> && sizeof(_Tp) == sizeof(_Up)));
if constexpr (2 * _Np < _M && sizeof(_To) > 16)
{
constexpr size_t Min = 16 / sizeof(_Up);
return __zero_extend(
__convert_x86<
__vector_type_t<_Up, (Min > 2 * _Np) ? Min : 2 * _Np>>(__v0,
__v1));
}
else if constexpr (__i64_to_i32)
{
if constexpr (__x_to_x)
return __auto_bitcast(
_mm_shuffle_ps(__auto_bitcast(__v0), __auto_bitcast(__v1), 0x88));
else if constexpr (__y_to_y)
{
return __auto_bitcast(
__xzyw(_mm256_shuffle_ps(__auto_bitcast(__v0),
__auto_bitcast(__v1), 0x88)));
}
else if constexpr (__z_to_z)
return __intrin_bitcast<_To>(__concat(_mm512_cvtepi64_epi32(__i0),
_mm512_cvtepi64_epi32(__i1)));
}
else if constexpr (__i64_to_i16)
{
if constexpr (__x_to_x)
{
if constexpr (__have_sse4_1)
{
return __intrin_bitcast<_To>(_mm_shuffle_epi8(
_mm_blend_epi16(__i0, _mm_slli_si128(__i1, 4), 0x44),
_mm_setr_epi8(0, 1, 8, 9, 4, 5, 12, 13, -0x80, -0x80, -0x80,
-0x80, -0x80, -0x80, -0x80, -0x80)));
}
else
{
return __vector_type_t<_Up, _M>{_Up(__v0[0]), _Up(__v0[1]),
_Up(__v1[0]), _Up(__v1[1])};
}
}
else if constexpr (__y_to_x)
{
auto __a
= _mm256_unpacklo_epi16(__i0, __i1);
auto __b
= _mm256_unpackhi_epi16(__i0, __i1);
auto __c = _mm256_unpacklo_epi16(__a, __b);
return __intrin_bitcast<_To>(
_mm_unpacklo_epi32(__lo128(__c), __hi128(__c)));
}
else if constexpr (__z_to_y)
return __intrin_bitcast<_To>(__concat(_mm512_cvtepi64_epi16(__i0),
_mm512_cvtepi64_epi16(__i1)));
}
else if constexpr (__i64_to_i8)
{
if constexpr (__x_to_x && __have_sse4_1)
{
return __intrin_bitcast<_To>(_mm_shuffle_epi8(
_mm_blend_epi16(__i0, _mm_slli_si128(__i1, 4), 0x44),
_mm_setr_epi8(0, 8, 4, 12, -0x80, -0x80, -0x80, -0x80, -0x80,
-0x80, -0x80, -0x80, -0x80, -0x80, -0x80,
-0x80)));
}
else if constexpr (__x_to_x && __have_ssse3)
{
return __intrin_bitcast<_To>(_mm_unpacklo_epi16(
_mm_shuffle_epi8(__i0, _mm_setr_epi8(0, 8, -0x80, -0x80, -0x80,
-0x80, -0x80, -0x80, -0x80,
-0x80, -0x80, -0x80, -0x80,
-0x80, -0x80, -0x80)),
_mm_shuffle_epi8(__i1, _mm_setr_epi8(0, 8, -0x80, -0x80, -0x80,
-0x80, -0x80, -0x80, -0x80,
-0x80, -0x80, -0x80, -0x80,
-0x80, -0x80, -0x80))));
}
else if constexpr (__x_to_x)
{
return __vector_type_t<_Up, _M>{_Up(__v0[0]), _Up(__v0[1]),
_Up(__v1[0]), _Up(__v1[1])};
}
else if constexpr (__y_to_x)
{
const auto __a = _mm256_shuffle_epi8(
_mm256_blend_epi32(__i0, _mm256_slli_epi64(__i1, 32), 0xAA),
_mm256_setr_epi8(0, 8, -0x80, -0x80, 4, 12, -0x80, -0x80, -0x80,
-0x80, -0x80, -0x80, -0x80, -0x80, -0x80,
-0x80, -0x80, -0x80, 0, 8, -0x80, -0x80, 4, 12,
-0x80, -0x80, -0x80, -0x80, -0x80, -0x80,
-0x80, -0x80));
return __intrin_bitcast<_To>(__lo128(__a) | __hi128(__a));
}
}
else if constexpr (__i32_to_i16)
{
if constexpr (__x_to_x)
{
if constexpr (__have_sse4_1)
{
return __intrin_bitcast<_To>(_mm_shuffle_epi8(
_mm_blend_epi16(__i0, _mm_slli_si128(__i1, 2), 0xaa),
_mm_setr_epi8(0, 1, 4, 5, 8, 9, 12, 13, 2, 3, 6, 7, 10, 11,
14, 15)));
}
else if constexpr (__have_ssse3)
{
return __intrin_bitcast<_To>(
_mm_hadd_epi16(__to_intrin(__v0 << 16),
__to_intrin(__v1 << 16)));
}
else
{
auto __a = _mm_unpacklo_epi16(__i0, __i1);
auto __b = _mm_unpackhi_epi16(__i0, __i1);
auto __c = _mm_unpacklo_epi16(__a, __b);
auto __d = _mm_unpackhi_epi16(__a, __b);
return __intrin_bitcast<_To>(
_mm_unpacklo_epi16(__c, __d));
}
}
else if constexpr (__y_to_y)
{
const auto __shuf
= _mm256_setr_epi8(0, 1, 4, 5, 8, 9, 12, 13, -0x80, -0x80,
-0x80, -0x80, -0x80, -0x80, -0x80, -0x80, 0,
1, 4, 5, 8, 9, 12, 13, -0x80, -0x80, -0x80,
-0x80, -0x80, -0x80, -0x80, -0x80);
auto __a = _mm256_shuffle_epi8(__i0, __shuf);
auto __b = _mm256_shuffle_epi8(__i1, __shuf);
return __intrin_bitcast<_To>(
__xzyw(_mm256_unpacklo_epi64(__a, __b)));
}
}
else if constexpr (__i32_to_i8)
{
if constexpr (__x_to_x && __have_ssse3)
{
const auto shufmask
= _mm_setr_epi8(0, 4, 8, 12, -0x80, -0x80, -0x80, -0x80, -0x80,
-0x80, -0x80, -0x80, -0x80, -0x80, -0x80,
-0x80);
return __intrin_bitcast<_To>(
_mm_unpacklo_epi32(_mm_shuffle_epi8(__i0, shufmask),
_mm_shuffle_epi8(__i1, shufmask)));
}
else if constexpr (__x_to_x)
{
auto __a = _mm_unpacklo_epi8(__i0, __i1);
auto __b = _mm_unpackhi_epi8(__i0, __i1);
auto __c = _mm_unpacklo_epi8(__a, __b);
auto __d = _mm_unpackhi_epi8(__a, __b);
auto __e = _mm_unpacklo_epi8(__c, __d);
return __intrin_bitcast<_To>(__e & __m128i{-1, 0});
}
else if constexpr (__y_to_x)
{
const auto __a = _mm256_shuffle_epi8(
_mm256_blend_epi16(__i0, _mm256_slli_epi32(__i1, 16), 0xAA),
_mm256_setr_epi8(0, 4, 8, 12, -0x80, -0x80, -0x80, -0x80, 2, 6,
10, 14, -0x80, -0x80, -0x80, -0x80, -0x80,
-0x80, -0x80, -0x80, 0, 4, 8, 12, -0x80, -0x80,
-0x80, -0x80, 2, 6, 10, 14));
return __intrin_bitcast<_To>(__lo128(__a) | __hi128(__a));
}
}
else if constexpr (__i16_to_i8)
{
if constexpr (__x_to_x && __have_ssse3)
{
const auto __shuf = reinterpret_cast<__m128i>(
__vector_type_t<_UChar, 16>{0, 2, 4, 6, 8, 10, 12, 14, 0x80,
0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
0x80});
return __intrin_bitcast<_To>(
_mm_unpacklo_epi64(_mm_shuffle_epi8(__i0, __shuf),
_mm_shuffle_epi8(__i1, __shuf)));
}
else if constexpr (__x_to_x)
{
auto __a = _mm_unpacklo_epi8(__i0, __i1);
auto __b = _mm_unpackhi_epi8(__i0, __i1);
auto __c = _mm_unpacklo_epi8(__a, __b);
auto __d = _mm_unpackhi_epi8(__a, __b);
auto __e = _mm_unpacklo_epi8(__c, __d);
auto __f = _mm_unpackhi_epi8(__c, __d);
return __intrin_bitcast<_To>(_mm_unpacklo_epi8(__e, __f));
}
else if constexpr (__y_to_y)
{
return __intrin_bitcast<_To>(__xzyw(_mm256_shuffle_epi8(
(__to_intrin(__v0) & _mm256_set1_epi32(0x00ff00ff))
| _mm256_slli_epi16(__i1, 8),
_mm256_setr_epi8(0, 2, 4, 6, 8, 10, 12, 14, 1, 3, 5, 7, 9, 11,
13, 15, 0, 2, 4, 6, 8, 10, 12, 14, 1, 3, 5, 7,
9, 11, 13, 15))));
}
}
else if constexpr (__i64_to_f32)
{
if constexpr (__x_to_x)
return __make_wrapper<float>(__v0[0], __v0[1], __v1[0], __v1[1]);
else if constexpr (__y_to_y)
{
static_assert(__y_to_y && __have_avx2);
const auto __a = _mm256_unpacklo_epi32(__i0, __i1);
const auto __b = _mm256_unpackhi_epi32(__i0, __i1);
const auto __lo32 = _mm256_unpacklo_epi32(__a, __b);
const auto __hi32
= __vector_bitcast<conditional_t<is_signed_v<_Tp>, int, _UInt>>(
_mm256_unpackhi_epi32(__a, __b));
const auto __hi
= 0x100000000LL
* __convert_x86<__vector_type_t<float, 8>>(__hi32);
const auto __mid
= 0x10000 * _mm256_cvtepi32_ps(_mm256_srli_epi32(__lo32, 16));
const auto __lo
= _mm256_cvtepi32_ps(_mm256_set1_epi32(0x0000ffffu) & __lo32);
return __xzyw((__hi + __mid) + __lo);
}
else if constexpr (__z_to_z && __have_avx512dq)
{
return std::is_signed_v<_Tp> ? __concat(_mm512_cvtepi64_ps(__i0),
_mm512_cvtepi64_ps(__i1))
: __concat(_mm512_cvtepu64_ps(__i0),
_mm512_cvtepu64_ps(__i1));
}
else if constexpr (__z_to_z && std::is_signed_v<_Tp>)
{
const __m512 __hi32 = _mm512_cvtepi32_ps(
__concat(_mm512_cvtepi64_epi32(__to_intrin(__v0 >> 32)),
_mm512_cvtepi64_epi32(__to_intrin(__v1 >> 32))));
const __m512i __lo32 = __concat(_mm512_cvtepi64_epi32(__i0),
_mm512_cvtepi64_epi32(__i1));
const __m512 __hi16
= _mm512_cvtepu32_ps(_mm512_set1_epi32(0xffff0000u) & __lo32);
const __m512 __lo16
= _mm512_cvtepi32_ps(_mm512_set1_epi32(0x0000ffffu) & __lo32);
return (__hi32 * 0x100000000LL + __hi16) + __lo16;
}
else if constexpr (__z_to_z && std::is_unsigned_v<_Tp>)
{
return __intrin_bitcast<_To>(
_mm512_cvtepu32_ps(
__concat(_mm512_cvtepi64_epi32(_mm512_srai_epi64(__i0, 32)),
_mm512_cvtepi64_epi32(_mm512_srai_epi64(__i1, 32))))
* 0x100000000LL
+ _mm512_cvtepu32_ps(__concat(_mm512_cvtepi64_epi32(__i0),
_mm512_cvtepi64_epi32(__i1))));
}
}
else if constexpr (__f64_to_s32)
{
}
else if constexpr (__f64_to_u32)
{
if constexpr (__x_to_x && __have_sse4_1)
{
return __vector_bitcast<_Up, _M>(_mm_unpacklo_epi64(
_mm_cvttpd_epi32(_mm_floor_pd(__i0) - 0x8000'0000u),
_mm_cvttpd_epi32(_mm_floor_pd(__i1) - 0x8000'0000u)))
^ 0x8000'0000u;
}
else if constexpr (__y_to_y)
{
return __vector_bitcast<_Up>(
__concat(_mm256_cvttpd_epi32(_mm256_floor_pd(__i0)
- 0x8000'0000u),
_mm256_cvttpd_epi32(_mm256_floor_pd(__i1)
- 0x8000'0000u)))
^ 0x8000'0000u;
}
}
else if constexpr (__f64_to_ibw)
{
return __convert_x86<_To>(
__convert_x86<__vector_type_t<int, _Np * 2>>(__v0, __v1));
}
else if constexpr (__f32_to_ibw)
{
return __convert_x86<_To>(
__convert_x86<__vector_type_t<int, _Np>>(__v0),
__convert_x86<__vector_type_t<int, _Np>>(__v1));
}
if constexpr (sizeof(_To) >= 32)
return __concat(__convert_x86<__vector_type_t<_Up, _M / 2>>(__v0),
__convert_x86<__vector_type_t<_Up, _M / 2>>(__v1));
else if constexpr (sizeof(_To) == 16)
{
const auto __lo = __to_intrin(__convert_x86<_To>(__v0));
const auto __hi = __to_intrin(__convert_x86<_To>(__v1));
if constexpr (sizeof(_Up) * _Np == 8)
{
if constexpr (is_floating_point_v<_Up>)
return __auto_bitcast(
_mm_unpacklo_pd(__vector_bitcast<double>(__lo),
__vector_bitcast<double>(__hi)));
else
return __intrin_bitcast<_To>(_mm_unpacklo_epi64(__lo, __hi));
}
else if constexpr (sizeof(_Up) * _Np == 4)
{
if constexpr (is_floating_point_v<_Up>)
return __auto_bitcast(
_mm_unpacklo_ps(__vector_bitcast<float>(__lo),
__vector_bitcast<float>(__hi)));
else
return __intrin_bitcast<_To>(_mm_unpacklo_epi32(__lo, __hi));
}
else if constexpr (sizeof(_Up) * _Np == 2)
return __intrin_bitcast<_To>(_mm_unpacklo_epi16(__lo, __hi));
else
__assert_unreachable<_Tp>();
}
else
return __vector_convert<_To>(__v0, __v1, make_index_sequence<_Np>());
}
}
template <typename _To, typename _V, typename _Traits>
_GLIBCXX_SIMD_INTRINSIC _To
__convert_x86(_V __v0, _V __v1, _V __v2, _V __v3)
{
static_assert(__is_vector_type_v<_V>);
using _Tp = typename _Traits::value_type;
constexpr size_t _Np = _Traits::_S_full_size;
[[maybe_unused]] const auto __i0 = __to_intrin(__v0);
[[maybe_unused]] const auto __i1 = __to_intrin(__v1);
[[maybe_unused]] const auto __i2 = __to_intrin(__v2);
[[maybe_unused]] const auto __i3 = __to_intrin(__v3);
using _Up = typename _VectorTraits<_To>::value_type;
constexpr size_t _M = _VectorTraits<_To>::_S_full_size;
static_assert(4 * _Np <= _M,
"__v2/__v3 would be discarded; use the two/one-argument "
"__convert_x86 overload instead");
[[maybe_unused]] constexpr bool __x_to_x
= sizeof(__v0) <= 16 && sizeof(_To) <= 16;
[[maybe_unused]] constexpr bool __x_to_y
= sizeof(__v0) <= 16 && sizeof(_To) == 32;
[[maybe_unused]] constexpr bool __x_to_z
= sizeof(__v0) <= 16 && sizeof(_To) == 64;
[[maybe_unused]] constexpr bool __y_to_x
= sizeof(__v0) == 32 && sizeof(_To) <= 16;
[[maybe_unused]] constexpr bool __y_to_y
= sizeof(__v0) == 32 && sizeof(_To) == 32;
[[maybe_unused]] constexpr bool __y_to_z
= sizeof(__v0) == 32 && sizeof(_To) == 64;
[[maybe_unused]] constexpr bool __z_to_x
= sizeof(__v0) == 64 && sizeof(_To) <= 16;
[[maybe_unused]] constexpr bool __z_to_y
= sizeof(__v0) == 64 && sizeof(_To) == 32;
[[maybe_unused]] constexpr bool __z_to_z
= sizeof(__v0) == 64 && sizeof(_To) == 64;
[[maybe_unused]] constexpr bool __i_to_i
= std::is_integral_v<_Up> && std::is_integral_v<_Tp>;
[[maybe_unused]] constexpr bool __i8_to_i16
= __i_to_i && sizeof(_Tp) == 1 && sizeof(_Up) == 2;
[[maybe_unused]] constexpr bool __i8_to_i32
= __i_to_i && sizeof(_Tp) == 1 && sizeof(_Up) == 4;
[[maybe_unused]] constexpr bool __i8_to_i64
= __i_to_i && sizeof(_Tp) == 1 && sizeof(_Up) == 8;
[[maybe_unused]] constexpr bool __i16_to_i8
= __i_to_i && sizeof(_Tp) == 2 && sizeof(_Up) == 1;
[[maybe_unused]] constexpr bool __i16_to_i32
= __i_to_i && sizeof(_Tp) == 2 && sizeof(_Up) == 4;
[[maybe_unused]] constexpr bool __i16_to_i64
= __i_to_i && sizeof(_Tp) == 2 && sizeof(_Up) == 8;
[[maybe_unused]] constexpr bool __i32_to_i8
= __i_to_i && sizeof(_Tp) == 4 && sizeof(_Up) == 1;
[[maybe_unused]] constexpr bool __i32_to_i16
= __i_to_i && sizeof(_Tp) == 4 && sizeof(_Up) == 2;
[[maybe_unused]] constexpr bool __i32_to_i64
= __i_to_i && sizeof(_Tp) == 4 && sizeof(_Up) == 8;
[[maybe_unused]] constexpr bool __i64_to_i8
= __i_to_i && sizeof(_Tp) == 8 && sizeof(_Up) == 1;
[[maybe_unused]] constexpr bool __i64_to_i16
= __i_to_i && sizeof(_Tp) == 8 && sizeof(_Up) == 2;
[[maybe_unused]] constexpr bool __i64_to_i32
= __i_to_i && sizeof(_Tp) == 8 && sizeof(_Up) == 4;
[[maybe_unused]] constexpr bool __i64_to_f32
= is_integral_v<_Tp> && sizeof(_Tp) == 8
&& is_floating_point_v<_Up> && sizeof(_Up) == 4;
[[maybe_unused]] constexpr bool __s32_to_f32
= is_integral_v<_Tp> && is_signed_v<_Tp> && sizeof(_Tp) == 4
&& is_floating_point_v<_Up> && sizeof(_Up) == 4;
[[maybe_unused]] constexpr bool __s16_to_f32
= is_integral_v<_Tp> && is_signed_v<_Tp> && sizeof(_Tp) == 2
&& is_floating_point_v<_Up> && sizeof(_Up) == 4;
[[maybe_unused]] constexpr bool __s8_to_f32
= is_integral_v<_Tp> && is_signed_v<_Tp> && sizeof(_Tp) == 1
&& is_floating_point_v<_Up> && sizeof(_Up) == 4;
[[maybe_unused]] constexpr bool __u32_to_f32
= is_integral_v<_Tp> && is_unsigned_v<_Tp> && sizeof(_Tp) == 4
&& is_floating_point_v<_Up> && sizeof(_Up) == 4;
[[maybe_unused]] constexpr bool __u16_to_f32
= is_integral_v<_Tp> && is_unsigned_v<_Tp> && sizeof(_Tp) == 2
&& is_floating_point_v<_Up> && sizeof(_Up) == 4;
[[maybe_unused]] constexpr bool __u8_to_f32
= is_integral_v<_Tp> && is_unsigned_v<_Tp> && sizeof(_Tp) == 1
&& is_floating_point_v<_Up> && sizeof(_Up) == 4;
[[maybe_unused]] constexpr bool __s64_to_f64
= is_integral_v<_Tp> && is_signed_v<_Tp> && sizeof(_Tp) == 8
&& is_floating_point_v<_Up> && sizeof(_Up) == 8;
[[maybe_unused]] constexpr bool __s32_to_f64
= is_integral_v<_Tp> && is_signed_v<_Tp> && sizeof(_Tp) == 4
&& is_floating_point_v<_Up> && sizeof(_Up) == 8;
[[maybe_unused]] constexpr bool __s16_to_f64
= is_integral_v<_Tp> && is_signed_v<_Tp> && sizeof(_Tp) == 2
&& is_floating_point_v<_Up> && sizeof(_Up) == 8;
[[maybe_unused]] constexpr bool __s8_to_f64
= is_integral_v<_Tp> && is_signed_v<_Tp> && sizeof(_Tp) == 1
&& is_floating_point_v<_Up> && sizeof(_Up) == 8;
[[maybe_unused]] constexpr bool __u64_to_f64
= is_integral_v<_Tp> && is_unsigned_v<_Tp> && sizeof(_Tp) == 8
&& is_floating_point_v<_Up> && sizeof(_Up) == 8;
[[maybe_unused]] constexpr bool __u32_to_f64
= is_integral_v<_Tp> && is_unsigned_v<_Tp> && sizeof(_Tp) == 4
&& is_floating_point_v<_Up> && sizeof(_Up) == 8;
[[maybe_unused]] constexpr bool __u16_to_f64
= is_integral_v<_Tp> && is_unsigned_v<_Tp> && sizeof(_Tp) == 2
&& is_floating_point_v<_Up> && sizeof(_Up) == 8;
[[maybe_unused]] constexpr bool __u8_to_f64
= is_integral_v<_Tp> && is_unsigned_v<_Tp> && sizeof(_Tp) == 1
&& is_floating_point_v<_Up> && sizeof(_Up) == 8;
[[maybe_unused]] constexpr bool __f32_to_s64
= is_integral_v<_Up> && is_signed_v<_Up> && sizeof(_Up) == 8
&& is_floating_point_v<_Tp> && sizeof(_Tp) == 4;
[[maybe_unused]] constexpr bool __f32_to_s32
= is_integral_v<_Up> && is_signed_v<_Up> && sizeof(_Up) == 4
&& is_floating_point_v<_Tp> && sizeof(_Tp) == 4;
[[maybe_unused]] constexpr bool __f32_to_u64
= is_integral_v<_Up> && is_unsigned_v<_Up> && sizeof(_Up) == 8
&& is_floating_point_v<_Tp> && sizeof(_Tp) == 4;
[[maybe_unused]] constexpr bool __f32_to_u32
= is_integral_v<_Up> && is_unsigned_v<_Up> && sizeof(_Up) == 4
&& is_floating_point_v<_Tp> && sizeof(_Tp) == 4;
[[maybe_unused]] constexpr bool __f64_to_s64
= is_integral_v<_Up> && is_signed_v<_Up> && sizeof(_Up) == 8
&& is_floating_point_v<_Tp> && sizeof(_Tp) == 8;
[[maybe_unused]] constexpr bool __f64_to_s32
= is_integral_v<_Up> && is_signed_v<_Up> && sizeof(_Up) == 4
&& is_floating_point_v<_Tp> && sizeof(_Tp) == 8;
[[maybe_unused]] constexpr bool __f64_to_u64
= is_integral_v<_Up> && is_unsigned_v<_Up> && sizeof(_Up) == 8
&& is_floating_point_v<_Tp> && sizeof(_Tp) == 8;
[[maybe_unused]] constexpr bool __f64_to_u32
= is_integral_v<_Up> && is_unsigned_v<_Up> && sizeof(_Up) == 4
&& is_floating_point_v<_Tp> && sizeof(_Tp) == 8;
[[maybe_unused]] constexpr bool __f32_to_ibw
= is_integral_v<_Up> && sizeof(_Up) <= 2
&& is_floating_point_v<_Tp> && sizeof(_Tp) == 4;
[[maybe_unused]] constexpr bool __f64_to_ibw
= is_integral_v<_Up> && sizeof(_Up) <= 2
&& is_floating_point_v<_Tp> && sizeof(_Tp) == 8;
[[maybe_unused]] constexpr bool __f32_to_f64
= is_floating_point_v<_Tp> && sizeof(_Tp) == 4
&& is_floating_point_v<_Up> && sizeof(_Up) == 8;
[[maybe_unused]] constexpr bool __f64_to_f32
= is_floating_point_v<_Tp> && sizeof(_Tp) == 8
&& is_floating_point_v<_Up> && sizeof(_Up) == 4;
if constexpr (__i_to_i && __y_to_x && !__have_avx2)
{
return __convert_x86<_To>(__lo128(__v0), __hi128(__v0), __lo128(__v1),
__hi128(__v1), __lo128(__v2), __hi128(__v2),
__lo128(__v3), __hi128(__v3));
}
else if constexpr (__i_to_i)
{
static_assert(__x_to_x || __have_avx2,
"integral conversions with ymm registers require AVX2");
static_assert(__have_avx512bw
|| ((sizeof(_Tp) >= 4 || sizeof(__v0) < 64)
&& (sizeof(_Up) >= 4 || sizeof(_To) < 64)),
"8/16-bit integers in zmm registers require AVX512BW");
static_assert((sizeof(__v0) < 64 && sizeof(_To) < 64) || __have_avx512f,
"integral conversions with ymm registers require AVX2");
}
if constexpr (sizeof(__v0) < 16 || (sizeof(__v0) == 16 && __have_avx2)
|| (sizeof(__v0) == 16 && __have_avx
&& std::is_floating_point_v<_Tp>)
|| (sizeof(__v0) == 32 && __have_avx512f))
{
return __convert_x86<_To>(__concat(__v0, __v1), __concat(__v2, __v3));
}
else
{
static_assert(!(
std::is_floating_point_v<
_Tp> == std::is_floating_point_v<_Up> && sizeof(_Tp) == sizeof(_Up)));
if constexpr (4 * _Np < _M && sizeof(_To) > 16)
{
constexpr size_t Min = 16 / sizeof(_Up);
return __zero_extend(
__convert_x86<
__vector_type_t<_Up, (Min > 4 * _Np) ? Min : 4 * _Np>>(__v0, __v1,
__v2,
__v3));
}
else if constexpr (__i64_to_i16)
{
if constexpr (__x_to_x && __have_sse4_1)
{
return __intrin_bitcast<_To>(_mm_shuffle_epi8(
_mm_blend_epi16(_mm_blend_epi16(__i0, _mm_slli_si128(__i1, 2),
0x22),
_mm_blend_epi16(_mm_slli_si128(__i2, 4),
_mm_slli_si128(__i3, 6), 0x88),
0xcc),
_mm_setr_epi8(0, 1, 8, 9, 2, 3, 10, 11, 4, 5, 12, 13, 6, 7, 14,
15)));
}
else if constexpr (__y_to_y && __have_avx2)
{
return __intrin_bitcast<_To>(_mm256_shuffle_epi8(
__xzyw(_mm256_blend_epi16(
__auto_bitcast(
_mm256_shuffle_ps(__vector_bitcast<float>(__v0),
__vector_bitcast<float>(__v2),
0x88)),
__to_intrin(__vector_bitcast<int>(_mm256_shuffle_ps(
__vector_bitcast<float>(__v1),
__vector_bitcast<float>(__v3), 0x88))
<< 16),
0xaa)
),
_mm256_setr_epi8(0, 1, 4, 5, 8, 9, 12, 13, 2, 3, 6, 7, 10, 11,
14, 15, 0, 1, 4, 5, 8, 9, 12, 13, 2, 3, 6, 7,
10, 11, 14, 15)));
}
}
else if constexpr (__i64_to_i8)
{
if constexpr (__x_to_x)
{
}
else if constexpr (__y_to_x)
{
auto __a = _mm256_srli_epi32(_mm256_slli_epi32(__i0, 24), 24)
| _mm256_srli_epi32(_mm256_slli_epi32(__i1, 24), 16)
| _mm256_srli_epi32(_mm256_slli_epi32(__i2, 24), 8)
| _mm256_slli_epi32(
__i3, 24);
auto __b = _mm256_unpackhi_epi64(
__a, __a);
auto __c = _mm256_unpacklo_epi8(
__a, __b);
return __intrin_bitcast<_To>(
_mm_unpacklo_epi16(__lo128(__c),
__hi128(__c)));
}
}
else if constexpr (__i32_to_i8)
{
if constexpr (__x_to_x)
{
if constexpr (__have_ssse3)
{
const auto __x0 = __vector_bitcast<_UInt>(__v0) & 0xff;
const auto __x1 = (__vector_bitcast<_UInt>(__v1) & 0xff) << 8;
const auto __x2 = (__vector_bitcast<_UInt>(__v2) & 0xff)
<< 16;
const auto __x3 = __vector_bitcast<_UInt>(__v3) << 24;
return __intrin_bitcast<_To>(
_mm_shuffle_epi8(__to_intrin(__x0 | __x1 | __x2 | __x3),
_mm_setr_epi8(0, 4, 8, 12, 1, 5, 9, 13, 2,
6, 10, 14, 3, 7, 11, 15)));
}
else
{
auto __a
= _mm_unpacklo_epi8(__i0, __i2);
auto __b
= _mm_unpackhi_epi8(__i0, __i2);
auto __c
= _mm_unpacklo_epi8(__i1, __i3);
auto __d
= _mm_unpackhi_epi8(__i1, __i3);
auto __e = _mm_unpacklo_epi8(__a, __c);
auto __f = _mm_unpackhi_epi8(__a, __c);
auto __g = _mm_unpacklo_epi8(__b, __d);
auto __h = _mm_unpackhi_epi8(__b, __d);
return __intrin_bitcast<_To>(_mm_unpacklo_epi8(
_mm_unpacklo_epi8(__e, __g),
_mm_unpacklo_epi8(__f, __h)
));
}
}
else if constexpr (__y_to_y)
{
const auto __a = _mm256_shuffle_epi8(
__to_intrin((__vector_bitcast<_UShort>(_mm256_blend_epi16(
__i0, _mm256_slli_epi32(__i1, 16), 0xAA))
& 0xff)
| (__vector_bitcast<_UShort>(_mm256_blend_epi16(
__i2, _mm256_slli_epi32(__i3, 16), 0xAA))
<< 8)),
_mm256_setr_epi8(0, 4, 8, 12, 2, 6, 10, 14, 1, 5, 9, 13, 3, 7,
11, 15, 0, 4, 8, 12, 2, 6, 10, 14, 1, 5, 9, 13,
3, 7, 11, 15));
return __intrin_bitcast<_To>(_mm256_permutevar8x32_epi32(
__a, _mm256_setr_epi32(0, 4, 1, 5, 2, 6, 3, 7)));
}
}
else if constexpr (__i64_to_f32)
{
if constexpr (__x_to_y)
{
return __make_wrapper<float>(__v0[0], __v0[1], __v1[0], __v1[1],
__v2[0], __v2[1], __v3[0], __v3[1]);
const auto __a = _mm_unpacklo_epi32(__i0, __i1);
const auto __b = _mm_unpackhi_epi32(__i0, __i1);
const auto __c = _mm_unpacklo_epi32(__i2, __i3);
const auto __d = _mm_unpackhi_epi32(__i2, __i3);
const auto __lo32a = _mm_unpacklo_epi32(__a, __b);
const auto __lo32b = _mm_unpacklo_epi32(__c, __d);
const auto __hi32
= __vector_bitcast<conditional_t<is_signed_v<_Tp>, int, _UInt>>(
__concat(_mm_unpackhi_epi32(__a, __b),
_mm_unpackhi_epi32(__c, __d)));
const auto __hi
= 0x100000000LL
* __convert_x86<__vector_type_t<float, 8>>(__hi32);
const auto __mid
= 0x10000
* _mm256_cvtepi32_ps(__concat(_mm_srli_epi32(__lo32a, 16),
_mm_srli_epi32(__lo32b, 16)));
const auto __lo = _mm256_cvtepi32_ps(
__concat(_mm_set1_epi32(0x0000ffffu) & __lo32a,
_mm_set1_epi32(0x0000ffffu) & __lo32b));
return (__hi + __mid) + __lo;
}
}
else if constexpr (__f64_to_ibw)
{
return __convert_x86<_To>(
__convert_x86<__vector_type_t<int, _Np * 2>>(__v0, __v1),
__convert_x86<__vector_type_t<int, _Np * 2>>(__v2, __v3));
}
else if constexpr (__f32_to_ibw)
{
return __convert_x86<_To>(
__convert_x86<__vector_type_t<int, _Np>>(__v0),
__convert_x86<__vector_type_t<int, _Np>>(__v1),
__convert_x86<__vector_type_t<int, _Np>>(__v2),
__convert_x86<__vector_type_t<int, _Np>>(__v3));
}
if constexpr (sizeof(_To) >= 32)
return __concat(__convert_x86<__vector_type_t<_Up, _M / 2>>(__v0, __v1),
__convert_x86<__vector_type_t<_Up, _M / 2>>(__v2,
__v3));
else if constexpr (sizeof(_To) == 16)
{
const auto __lo = __to_intrin(__convert_x86<_To>(__v0, __v1));
const auto __hi = __to_intrin(__convert_x86<_To>(__v2, __v3));
if constexpr (sizeof(_Up) * _Np * 2 == 8)
{
if constexpr (is_floating_point_v<_Up>)
return __auto_bitcast(_mm_unpacklo_pd(__lo, __hi));
else
return __intrin_bitcast<_To>(_mm_unpacklo_epi64(__lo, __hi));
}
else if constexpr (sizeof(_Up) * _Np * 2 == 4)
{
if constexpr (is_floating_point_v<_Up>)
return __auto_bitcast(_mm_unpacklo_ps(__lo, __hi));
else
return __intrin_bitcast<_To>(_mm_unpacklo_epi32(__lo, __hi));
}
else
__assert_unreachable<_Tp>();
}
else
return __vector_convert<_To>(__v0, __v1, __v2, __v3,
make_index_sequence<_Np>());
}
}
template <typename _To, typename _V, typename _Traits>
_GLIBCXX_SIMD_INTRINSIC _To
__convert_x86(_V __v0, _V __v1, _V __v2, _V __v3, _V __v4, _V __v5, _V __v6,
_V __v7)
{
static_assert(__is_vector_type_v<_V>);
using _Tp = typename _Traits::value_type;
constexpr size_t _Np = _Traits::_S_full_size;
[[maybe_unused]] const auto __i0 = __to_intrin(__v0);
[[maybe_unused]] const auto __i1 = __to_intrin(__v1);
[[maybe_unused]] const auto __i2 = __to_intrin(__v2);
[[maybe_unused]] const auto __i3 = __to_intrin(__v3);
[[maybe_unused]] const auto __i4 = __to_intrin(__v4);
[[maybe_unused]] const auto __i5 = __to_intrin(__v5);
[[maybe_unused]] const auto __i6 = __to_intrin(__v6);
[[maybe_unused]] const auto __i7 = __to_intrin(__v7);
using _Up = typename _VectorTraits<_To>::value_type;
constexpr size_t _M = _VectorTraits<_To>::_S_full_size;
static_assert(8 * _Np <= _M,
"__v4-__v7 would be discarded; use the four/two/one-argument "
"__convert_x86 overload instead");
[[maybe_unused]] constexpr bool __x_to_x
= sizeof(__v0) <= 16 && sizeof(_To) <= 16;
[[maybe_unused]] constexpr bool __x_to_y
= sizeof(__v0) <= 16 && sizeof(_To) == 32;
[[maybe_unused]] constexpr bool __x_to_z
= sizeof(__v0) <= 16 && sizeof(_To) == 64;
[[maybe_unused]] constexpr bool __y_to_x
= sizeof(__v0) == 32 && sizeof(_To) <= 16;
[[maybe_unused]] constexpr bool __y_to_y
= sizeof(__v0) == 32 && sizeof(_To) == 32;
[[maybe_unused]] constexpr bool __y_to_z
= sizeof(__v0) == 32 && sizeof(_To) == 64;
[[maybe_unused]] constexpr bool __z_to_x
= sizeof(__v0) == 64 && sizeof(_To) <= 16;
[[maybe_unused]] constexpr bool __z_to_y
= sizeof(__v0) == 64 && sizeof(_To) == 32;
[[maybe_unused]] constexpr bool __z_to_z
= sizeof(__v0) == 64 && sizeof(_To) == 64;
[[maybe_unused]] constexpr bool __i_to_i
= std::is_integral_v<_Up> && std::is_integral_v<_Tp>;
[[maybe_unused]] constexpr bool __i64_to_i8
= __i_to_i && sizeof(_Tp) == 8 && sizeof(_Up) == 1;
[[maybe_unused]] constexpr bool __f64_to_i8
= is_integral_v<_Up> && sizeof(_Up) == 1
&& is_floating_point_v<_Tp> && sizeof(_Tp) == 8;
if constexpr (__i_to_i)
{
static_assert(__x_to_x || __have_avx2,
"integral conversions with ymm registers require AVX2");
static_assert(__have_avx512bw
|| ((sizeof(_Tp) >= 4 || sizeof(__v0) < 64)
&& (sizeof(_Up) >= 4 || sizeof(_To) < 64)),
"8/16-bit integers in zmm registers require AVX512BW");
static_assert((sizeof(__v0) < 64 && sizeof(_To) < 64) || __have_avx512f,
"integral conversions with ymm registers require AVX2");
}
if constexpr (sizeof(__v0) < 16 || (sizeof(__v0) == 16 && __have_avx2)
|| (sizeof(__v0) == 16 && __have_avx
&& std::is_floating_point_v<_Tp>)
|| (sizeof(__v0) == 32 && __have_avx512f))
{
return __convert_x86<_To>(__concat(__v0, __v1), __concat(__v2, __v3),
__concat(__v4, __v5), __concat(__v6, __v7));
}
else
{
static_assert(!(
std::is_floating_point_v<
_Tp> == std::is_floating_point_v<_Up> && sizeof(_Tp) == sizeof(_Up)));
static_assert(!(8 * _Np < _M && sizeof(_To) > 16),
"zero extension should be impossible");
if constexpr (__i64_to_i8)
{
if constexpr (__x_to_x && __have_ssse3)
{
return __intrin_bitcast<_To>(_mm_shuffle_epi8(
__to_intrin((((__v0 & 0xff) | ((__v1 & 0xff) << 8))
| (((__v2 & 0xff) << 16) | ((__v3 & 0xff) << 24)))
| ((((__v4 & 0xff) << 32) | ((__v5 & 0xff) << 40))
| (((__v6 & 0xff) << 48) | (__v7 << 56)))),
_mm_setr_epi8(0, 8, 1, 9, 2, 10, 3, 11, 4, 12, 5, 13, 6, 14, 7,
15)));
}
else if constexpr (__x_to_x)
{
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
}
else if constexpr (__y_to_y)
{
auto __a =
__to_intrin((((__v0 & 0xff) | ((__v1 & 0xff) << 8))
| (((__v2 & 0xff) << 16) | ((__v3 & 0xff) << 24)))
| ((((__v4 & 0xff) << 32) | ((__v5 & 0xff) << 40))
| (((__v6 & 0xff) << 48) | ((__v7 << 56)))));
auto __b = _mm256_shuffle_epi8(
__a, _mm256_setr_epi8(0, 8, 1, 9, 2, 10, 3, 11, 4, 12, 5, 13, 6,
14, 7, 15, 0, 8, 1, 9, 2, 10, 3, 11, 4,
12, 5, 13, 6, 14, 7, 15));
auto __c = __xzyw(__b);
return __intrin_bitcast<_To>(_mm256_shuffle_epi8(
__c, _mm256_setr_epi8(0, 1, 8, 9, 2, 3, 10, 11, 4, 5, 12, 13, 6,
7, 14, 15, 0, 1, 8, 9, 2, 3, 10, 11, 4, 5,
12, 13, 6, 7, 14, 15)));
}
else if constexpr (__z_to_z)
{
return __concat(
__convert_x86<__vector_type_t<_Up, _M / 2>>(__v0, __v1, __v2,
__v3),
__convert_x86<__vector_type_t<_Up, _M / 2>>(__v4, __v5, __v6,
__v7));
}
}
else if constexpr (__f64_to_i8)
{
return __convert_x86<_To>(
__convert_x86<__vector_type_t<int, _Np * 2>>(__v0, __v1),
__convert_x86<__vector_type_t<int, _Np * 2>>(__v2, __v3),
__convert_x86<__vector_type_t<int, _Np * 2>>(__v4, __v5),
__convert_x86<__vector_type_t<int, _Np * 2>>(__v6, __v7));
}
else
__assert_unreachable<_Tp>();
if constexpr (sizeof(_To) >= 32)
return __concat(
__convert_x86<__vector_type_t<_Up, _M / 2>>(__v0, __v1, __v2, __v3),
__convert_x86<__vector_type_t<_Up, _M / 2>>(__v4, __v5, __v6, __v7));
else if constexpr (sizeof(_To) == 16)
{
const auto __lo
= __to_intrin(__convert_x86<_To>(__v0, __v1, __v2, __v3));
const auto __hi
= __to_intrin(__convert_x86<_To>(__v4, __v5, __v6, __v7));
static_assert(sizeof(_Up) == 1 && _Np == 2);
return __intrin_bitcast<_To>(_mm_unpacklo_epi64(__lo, __hi));
}
else
{
__assert_unreachable<_Tp>();
}
}
}
template <typename _To, typename _V, typename _Traits>
_GLIBCXX_SIMD_INTRINSIC _To
__convert_x86(_V __v0, _V __v1, _V __v2, _V __v3, _V __v4, _V __v5, _V __v6,
_V __v7, _V __v8, _V __v9, _V __v10, _V __v11, _V __v12, _V __v13,
_V __v14, _V __v15)
{
return __convert_x86<_To>(__concat(__v0, __v1), __concat(__v2, __v3),
__concat(__v4, __v5), __concat(__v6, __v7),
__concat(__v8, __v9), __concat(__v10, __v11),
__concat(__v12, __v13), __concat(__v14, __v15));
}
#endif
#endif
#endif
template <typename _Tp, size_t _Np>
constexpr bool
__is_sse_ps()
{
return __have_sse
&& std::is_same_v<_Tp,
float> && sizeof(__intrinsic_type_t<_Tp, _Np>) == 16;
}
template <typename _Tp, size_t _Np>
constexpr bool
__is_sse_pd()
{
return __have_sse2
&& std::is_same_v<
_Tp, double> && sizeof(__intrinsic_type_t<_Tp, _Np>) == 16;
}
template <typename _Tp, size_t _Np>
constexpr bool
__is_avx_ps()
{
return __have_avx
&& std::is_same_v<_Tp,
float> && sizeof(__intrinsic_type_t<_Tp, _Np>) == 32;
}
template <typename _Tp, size_t _Np>
constexpr bool
__is_avx_pd()
{
return __have_avx
&& std::is_same_v<
_Tp, double> && sizeof(__intrinsic_type_t<_Tp, _Np>) == 32;
}
template <typename _Tp, size_t _Np>
constexpr bool
__is_avx512_ps()
{
return __have_avx512f
&& std::is_same_v<_Tp,
float> && sizeof(__intrinsic_type_t<_Tp, _Np>) == 64;
}
template <typename _Tp, size_t _Np>
constexpr bool
__is_avx512_pd()
{
return __have_avx512f
&& std::is_same_v<
_Tp, double> && sizeof(__intrinsic_type_t<_Tp, _Np>) == 64;
}
struct _MaskImplX86Mixin;
struct _CommonImplX86 : _CommonImplBuiltin
{
#ifdef _GLIBCXX_SIMD_WORKAROUND_PR85048
template <typename _From, typename _To, size_t _ToSize>
static constexpr bool _S_converts_via_decomposition()
{
if constexpr (is_integral_v<
_From> && is_integral_v<_To> && sizeof(_From) == 8
&& _ToSize == 16)
return (sizeof(_To) == 2 && !__have_ssse3)
|| (sizeof(_To) == 1 && !__have_avx512f);
else if constexpr (is_floating_point_v<_From> && is_integral_v<_To>)
return ((sizeof(_From) == 4 || sizeof(_From) == 8) && sizeof(_To) == 8
&& !__have_avx512dq)
|| (sizeof(_From) == 8 && sizeof(_To) == 4 && !__have_sse4_1
&& _ToSize == 16);
else if constexpr (
is_integral_v<_From> && is_floating_point_v<_To> && sizeof(_From) == 8
&& !__have_avx512dq)
return (sizeof(_To) == 4 && _ToSize == 16)
|| (sizeof(_To) == 8 && _ToSize < 64);
else
return false;
}
template <typename _From, typename _To, size_t _ToSize>
static inline constexpr bool __converts_via_decomposition_v
= _S_converts_via_decomposition<_From, _To, _ToSize>();
#endif
using _CommonImplBuiltin::_S_store;
template <typename _Tp, size_t _Np>
_GLIBCXX_SIMD_INTRINSIC static void _S_store(_SimdWrapper<_Tp, _Np> __x,
void* __addr)
{
constexpr size_t _Bytes = _Np * sizeof(_Tp);
if constexpr ((_Bytes & (_Bytes - 1)) != 0 && __have_avx512bw_vl)
{
const auto __v = __to_intrin(__x);
if constexpr (_Bytes & 1)
{
if constexpr (_Bytes < 16)
_mm_mask_storeu_epi8(__addr, 0xffffu >> (16 - _Bytes),
__intrin_bitcast<__m128i>(__v));
else if constexpr (_Bytes < 32)
_mm256_mask_storeu_epi8(__addr, 0xffffffffu >> (32 - _Bytes),
__intrin_bitcast<__m256i>(__v));
else
_mm512_mask_storeu_epi8(__addr,
0xffffffffffffffffull >> (64 - _Bytes),
__intrin_bitcast<__m512i>(__v));
}
else if constexpr (_Bytes & 2)
{
if constexpr (_Bytes < 16)
_mm_mask_storeu_epi16(__addr, 0xffu >> (8 - _Bytes / 2),
__intrin_bitcast<__m128i>(__v));
else if constexpr (_Bytes < 32)
_mm256_mask_storeu_epi16(__addr, 0xffffu >> (16 - _Bytes / 2),
__intrin_bitcast<__m256i>(__v));
else
_mm512_mask_storeu_epi16(__addr,
0xffffffffull >> (32 - _Bytes / 2),
__intrin_bitcast<__m512i>(__v));
}
else if constexpr (_Bytes & 4)
{
if constexpr (_Bytes < 16)
_mm_mask_storeu_epi32(__addr, 0xfu >> (4 - _Bytes / 4),
__intrin_bitcast<__m128i>(__v));
else if constexpr (_Bytes < 32)
_mm256_mask_storeu_epi32(__addr, 0xffu >> (8 - _Bytes / 4),
__intrin_bitcast<__m256i>(__v));
else
_mm512_mask_storeu_epi32(__addr, 0xffffull >> (16 - _Bytes / 4),
__intrin_bitcast<__m512i>(__v));
}
else
{
static_assert(
_Bytes > 16,
"_Bytes < 16 && (_Bytes & 7) == 0 && (_Bytes & (_Bytes "
"- 1)) != 0 is impossible");
if constexpr (_Bytes < 32)
_mm256_mask_storeu_epi64(__addr, 0xfu >> (4 - _Bytes / 8),
__intrin_bitcast<__m256i>(__v));
else
_mm512_mask_storeu_epi64(__addr, 0xffull >> (8 - _Bytes / 8),
__intrin_bitcast<__m512i>(__v));
}
}
else
_CommonImplBuiltin::_S_store(__x, __addr);
}
template <size_t _Np, bool _Sanitized>
_GLIBCXX_SIMD_INTRINSIC static constexpr void
_S_store_bool_array(const _BitMask<_Np, _Sanitized> __x, bool* __mem)
{
if constexpr (__have_avx512bw_vl)
_S_store<_Np>(1 & __vector_bitcast<_UChar, _Np>([=]() constexpr {
if constexpr (_Np <= 16)
return _mm_movm_epi8(__x._M_to_bits());
else if constexpr (_Np <= 32)
return _mm256_movm_epi8(__x._M_to_bits());
else if constexpr (_Np <= 64)
return _mm512_movm_epi8(__x._M_to_bits());
else
__assert_unreachable<_SizeConstant<_Np>>();
}()),
__mem);
else if constexpr (__have_bmi2)
{
if constexpr (_Np <= 4)
_S_store<_Np>(_pdep_u32(__x._M_to_bits(), 0x01010101U), __mem);
else
__execute_n_times<__div_roundup(_Np, sizeof(size_t))>([&](auto __i) {
constexpr size_t __offset = __i * sizeof(size_t);
constexpr int __todo = std::min(sizeof(size_t), _Np - __offset);
if constexpr (__todo == 1)
__mem[__offset] = __x[__offset];
else
{
const auto __bools =
#ifdef __x86_64__
_pdep_u64(__x.template _M_extract<__offset>().to_ullong(),
0x0101010101010101ULL);
#else
_pdep_u32(__x.template _M_extract<__offset>()._M_to_bits(),
0x01010101U);
#endif
_S_store<__todo>(__bools, __mem + __offset);
}
});
}
else if constexpr (__have_sse2 && _Np > 7)
__execute_n_times<__div_roundup(_Np, 16)>([&](auto __i) {
constexpr int __offset = __i * 16;
constexpr int __todo = std::min(16, int(_Np) - __offset);
const int __bits = __x.template _M_extract<__offset>()._M_to_bits();
__vector_type16_t<_UChar> __bools;
if constexpr (__have_avx512f)
{
auto __as32bits
= _mm512_maskz_mov_epi32(__bits,
__to_intrin(__vector_broadcast<16>(1)));
auto __as16bits = __xzyw(
_mm256_packs_epi32(__lo256(__as32bits),
__todo > 8 ? __hi256(__as32bits) : __m256i()));
__bools = __vector_bitcast<_UChar>(
_mm_packs_epi16(__lo128(__as16bits), __hi128(__as16bits)));
}
else
{
using _V = __vector_type_t<_UChar, 16>;
auto __tmp = _mm_cvtsi32_si128(__bits);
__tmp = _mm_unpacklo_epi8(__tmp, __tmp);
__tmp = _mm_unpacklo_epi16(__tmp, __tmp);
__tmp = _mm_unpacklo_epi32(__tmp, __tmp);
_V __tmp2 = reinterpret_cast<_V>(__tmp);
__tmp2 &= _V{1, 2, 4, 8, 16, 32, 64, 128,
1, 2, 4, 8, 16, 32, 64, 128};
__bools = (__tmp2 == 0) + 1;
}
_S_store<__todo>(__bools, __mem + __offset);
});
else
_CommonImplBuiltin::_S_store_bool_array(__x, __mem);
}
template <typename _Kp, typename _TV>
_GLIBCXX_SIMD_INTRINSIC static _TV
_S_blend_avx512(const _Kp __k, const _TV __a, const _TV __b) noexcept
{
#ifdef __clang__
return __k ? __a : __b;
#else
static_assert(__is_vector_type_v<_TV>);
using _Tp = typename _VectorTraits<_TV>::value_type;
static_assert(sizeof(_TV) >= 16);
static_assert(sizeof(_Tp) <= 8);
using _IntT = conditional_t<(sizeof(_Tp) > 2),
conditional_t<sizeof(_Tp) == 4, int, long long>,
conditional_t<sizeof(_Tp) == 1, char, short>>;
[[maybe_unused]] const auto __aa = __vector_bitcast<_IntT>(__a);
[[maybe_unused]] const auto __bb = __vector_bitcast<_IntT>(__b);
if constexpr (sizeof(_TV) == 64)
{
if constexpr (sizeof(_Tp) == 1)
return reinterpret_cast<_TV>(
__builtin_ia32_blendmb_512_mask(__aa, __bb, __k));
else if constexpr (sizeof(_Tp) == 2)
return reinterpret_cast<_TV>(
__builtin_ia32_blendmw_512_mask(__aa, __bb, __k));
else if constexpr (sizeof(_Tp) == 4 && is_floating_point_v<_Tp>)
return __builtin_ia32_blendmps_512_mask(__a, __b, __k);
else if constexpr (sizeof(_Tp) == 4)
return reinterpret_cast<_TV>(
__builtin_ia32_blendmd_512_mask(__aa, __bb, __k));
else if constexpr (sizeof(_Tp) == 8 && is_floating_point_v<_Tp>)
return __builtin_ia32_blendmpd_512_mask(__a, __b, __k);
else if constexpr (sizeof(_Tp) == 8)
return reinterpret_cast<_TV>(
__builtin_ia32_blendmq_512_mask(__aa, __bb, __k));
}
else if constexpr (sizeof(_TV) == 32)
{
if constexpr (sizeof(_Tp) == 1)
return reinterpret_cast<_TV>(
__builtin_ia32_blendmb_256_mask(__aa, __bb, __k));
else if constexpr (sizeof(_Tp) == 2)
return reinterpret_cast<_TV>(
__builtin_ia32_blendmw_256_mask(__aa, __bb, __k));
else if constexpr (sizeof(_Tp) == 4 && is_floating_point_v<_Tp>)
return __builtin_ia32_blendmps_256_mask(__a, __b, __k);
else if constexpr (sizeof(_Tp) == 4)
return reinterpret_cast<_TV>(
__builtin_ia32_blendmd_256_mask(__aa, __bb, __k));
else if constexpr (sizeof(_Tp) == 8 && is_floating_point_v<_Tp>)
return __builtin_ia32_blendmpd_256_mask(__a, __b, __k);
else if constexpr (sizeof(_Tp) == 8)
return reinterpret_cast<_TV>(
__builtin_ia32_blendmq_256_mask(__aa, __bb, __k));
}
else if constexpr (sizeof(_TV) == 16)
{
if constexpr (sizeof(_Tp) == 1)
return reinterpret_cast<_TV>(
__builtin_ia32_blendmb_128_mask(__aa, __bb, __k));
else if constexpr (sizeof(_Tp) == 2)
return reinterpret_cast<_TV>(
__builtin_ia32_blendmw_128_mask(__aa, __bb, __k));
else if constexpr (sizeof(_Tp) == 4 && is_floating_point_v<_Tp>)
return __builtin_ia32_blendmps_128_mask(__a, __b, __k);
else if constexpr (sizeof(_Tp) == 4)
return reinterpret_cast<_TV>(
__builtin_ia32_blendmd_128_mask(__aa, __bb, __k));
else if constexpr (sizeof(_Tp) == 8 && is_floating_point_v<_Tp>)
return __builtin_ia32_blendmpd_128_mask(__a, __b, __k);
else if constexpr (sizeof(_Tp) == 8)
return reinterpret_cast<_TV>(
__builtin_ia32_blendmq_128_mask(__aa, __bb, __k));
}
#endif
}
template <typename _Tp>
_GLIBCXX_SIMD_INTRINSIC static _Tp _S_blend_intrin(_Tp __k, _Tp __a,
_Tp __b) noexcept
{
static_assert(is_same_v<decltype(__to_intrin(__a)), _Tp>);
constexpr struct
{
_GLIBCXX_SIMD_INTRINSIC __m128 operator()(__m128 __a, __m128 __b,
__m128 __k) const noexcept
{
return __builtin_ia32_blendvps(__a, __b, __k);
}
_GLIBCXX_SIMD_INTRINSIC __m128d operator()(__m128d __a, __m128d __b,
__m128d __k) const noexcept
{
return __builtin_ia32_blendvpd(__a, __b, __k);
}
_GLIBCXX_SIMD_INTRINSIC __m128i operator()(__m128i __a, __m128i __b,
__m128i __k) const noexcept
{
return reinterpret_cast<__m128i>(
__builtin_ia32_pblendvb128(reinterpret_cast<__v16qi>(__a),
reinterpret_cast<__v16qi>(__b),
reinterpret_cast<__v16qi>(__k)));
}
_GLIBCXX_SIMD_INTRINSIC __m256 operator()(__m256 __a, __m256 __b,
__m256 __k) const noexcept
{
return __builtin_ia32_blendvps256(__a, __b, __k);
}
_GLIBCXX_SIMD_INTRINSIC __m256d operator()(__m256d __a, __m256d __b,
__m256d __k) const noexcept
{
return __builtin_ia32_blendvpd256(__a, __b, __k);
}
_GLIBCXX_SIMD_INTRINSIC __m256i operator()(__m256i __a, __m256i __b,
__m256i __k) const noexcept
{
if constexpr (__have_avx2)
return reinterpret_cast<__m256i>(
__builtin_ia32_pblendvb256(reinterpret_cast<__v32qi>(__a),
reinterpret_cast<__v32qi>(__b),
reinterpret_cast<__v32qi>(__k)));
else
return reinterpret_cast<__m256i>(
__builtin_ia32_blendvps256(reinterpret_cast<__v8sf>(__a),
reinterpret_cast<__v8sf>(__b),
reinterpret_cast<__v8sf>(__k)));
}
} __eval;
return __eval(__a, __b, __k);
}
template <typename _Tp, size_t _Np>
_GLIBCXX_SIMD_INTRINSIC static constexpr _SimdWrapper<_Tp, _Np>
_S_blend(_SimdWrapper<bool, _Np> __k, _SimdWrapper<_Tp, _Np> __at0,
_SimdWrapper<_Tp, _Np> __at1)
{
static_assert(is_same_v<_Tp, _Tp> && __have_avx512f);
if (__k._M_is_constprop() && __at0._M_is_constprop()
&& __at1._M_is_constprop())
return __generate_from_n_evaluations<_Np, __vector_type_t<_Tp, _Np>>([&](
auto __i) constexpr { return __k[__i] ? __at1[__i] : __at0[__i]; });
else if constexpr (sizeof(__at0) == 64
|| (__have_avx512vl && sizeof(__at0) >= 16))
return _S_blend_avx512(__k._M_data, __at0._M_data, __at1._M_data);
else
{
static_assert((__have_avx512vl && sizeof(__at0) < 16)
|| !__have_avx512vl);
constexpr size_t __size = (__have_avx512vl ? 16 : 64) / sizeof(_Tp);
return __vector_bitcast<_Tp, _Np>(
_S_blend_avx512(__k._M_data, __vector_bitcast<_Tp, __size>(__at0),
__vector_bitcast<_Tp, __size>(__at1)));
}
}
template <typename _Tp, size_t _Np>
_GLIBCXX_SIMD_INTRINSIC static constexpr _SimdWrapper<_Tp, _Np>
_S_blend(_SimdWrapper<__int_for_sizeof_t<_Tp>, _Np> __k,
_SimdWrapper<_Tp, _Np> __at0, _SimdWrapper<_Tp, _Np> __at1)
{
const auto __kk = __wrapper_bitcast<_Tp>(__k);
if (__builtin_is_constant_evaluated()
|| (__kk._M_is_constprop() && __at0._M_is_constprop()
&& __at1._M_is_constprop()))
{
auto __r = __or(__andnot(__kk, __at0), __and(__kk, __at1));
if (__r._M_is_constprop())
return __r;
}
if constexpr (((__have_avx512f && sizeof(__at0) == 64)
|| __have_avx512vl)
&& (sizeof(_Tp) >= 4 || __have_avx512bw))
return _S_blend(_SimdWrapper<bool, _Np>(
__make_dependent_t<_Tp, _MaskImplX86Mixin>::_S_to_bits(
__k)
._M_to_bits()),
__at0, __at1);
else
{
if constexpr (__have_sse4_1)
return _S_blend_intrin(__to_intrin(__kk), __to_intrin(__at0),
__to_intrin(__at1));
else
return __or(__andnot(__kk, __at0), __and(__kk, __at1));
}
}
};
template <typename _Abi> struct _SimdImplX86 : _SimdImplBuiltin<_Abi>
{
using _Base = _SimdImplBuiltin<_Abi>;
template <typename _Tp>
using _MaskMember = typename _Base::template _MaskMember<_Tp>;
template <typename _Tp>
static constexpr size_t _S_full_size = _Abi::template _S_full_size<_Tp>;
template <typename _Tp>
static constexpr size_t _S_size = _Abi::template _S_size<_Tp>;
template <typename _Tp>
static constexpr size_t _S_max_store_size
= (sizeof(_Tp) >= 4 && __have_avx512f) || __have_avx512bw
? 64
: (std::is_floating_point_v<_Tp>&& __have_avx) || __have_avx2 ? 32 : 16;
using _MaskImpl = typename _Abi::_MaskImpl;
template <typename _Tp, size_t _Np, typename _Up>
static inline _SimdWrapper<_Tp, _Np>
_S_masked_load(_SimdWrapper<_Tp, _Np> __merge, _MaskMember<_Tp> __k,
const _Up* __mem) noexcept
{
static_assert(_Np == _S_size<_Tp>);
if constexpr (std::is_same_v<_Tp, _Up> ||
(sizeof(_Tp) == sizeof(_Up)
&& std::is_integral_v<
_Tp> == std::is_integral_v<_Up>)
)
{
[[maybe_unused]] const auto __intrin = __to_intrin(__merge);
if constexpr ((__is_avx512_abi<_Abi>() || __have_avx512bw_vl)
&& sizeof(_Tp) == 1)
{
const auto __kk = _MaskImpl::_S_to_bits(__k)._M_to_bits();
if constexpr (sizeof(__intrin) == 16)
__merge = __vector_bitcast<_Tp, _Np>(
_mm_mask_loadu_epi8(__intrin, __kk, __mem));
else if constexpr (sizeof(__merge) == 32)
__merge = __vector_bitcast<_Tp, _Np>(
_mm256_mask_loadu_epi8(__intrin, __kk, __mem));
else if constexpr (sizeof(__merge) == 64)
__merge = __vector_bitcast<_Tp, _Np>(
_mm512_mask_loadu_epi8(__intrin, __kk, __mem));
else
__assert_unreachable<_Tp>();
}
else if constexpr ((__is_avx512_abi<_Abi>() || __have_avx512bw_vl)
&& sizeof(_Tp) == 2)
{
const auto __kk = _MaskImpl::_S_to_bits(__k)._M_to_bits();
if constexpr (sizeof(__intrin) == 16)
__merge = __vector_bitcast<_Tp, _Np>(
_mm_mask_loadu_epi16(__intrin, __kk, __mem));
else if constexpr (sizeof(__intrin) == 32)
__merge = __vector_bitcast<_Tp, _Np>(
_mm256_mask_loadu_epi16(__intrin, __kk, __mem));
else if constexpr (sizeof(__intrin) == 64)
__merge = __vector_bitcast<_Tp, _Np>(
_mm512_mask_loadu_epi16(__intrin, __kk, __mem));
else
__assert_unreachable<_Tp>();
}
else if constexpr ((__is_avx512_abi<_Abi>() || __have_avx512vl)
&& sizeof(_Tp) == 4 && std::is_integral_v<_Up>)
{
const auto __kk = _MaskImpl::_S_to_bits(__k)._M_to_bits();
if constexpr (sizeof(__intrin) == 16)
__merge = __vector_bitcast<_Tp, _Np>(
_mm_mask_loadu_epi32(__intrin, __kk, __mem));
else if constexpr (sizeof(__intrin) == 32)
__merge = __vector_bitcast<_Tp, _Np>(
_mm256_mask_loadu_epi32(__intrin, __kk, __mem));
else if constexpr (sizeof(__intrin) == 64)
__merge = __vector_bitcast<_Tp, _Np>(
_mm512_mask_loadu_epi32(__intrin, __kk, __mem));
else
__assert_unreachable<_Tp>();
}
else if constexpr ((__is_avx512_abi<_Abi>() || __have_avx512vl)
&& sizeof(_Tp) == 4 && std::is_floating_point_v<_Up>)
{
const auto __kk = _MaskImpl::_S_to_bits(__k)._M_to_bits();
if constexpr (sizeof(__intrin) == 16)
__merge = __vector_bitcast<_Tp, _Np>(
_mm_mask_loadu_ps(__intrin, __kk, __mem));
else if constexpr (sizeof(__intrin) == 32)
__merge = __vector_bitcast<_Tp, _Np>(
_mm256_mask_loadu_ps(__intrin, __kk, __mem));
else if constexpr (sizeof(__intrin) == 64)
__merge = __vector_bitcast<_Tp, _Np>(
_mm512_mask_loadu_ps(__intrin, __kk, __mem));
else
__assert_unreachable<_Tp>();
}
else if constexpr (__have_avx2 && sizeof(_Tp) == 4
&& std::is_integral_v<_Up>)
{
static_assert(sizeof(__intrin) == 16 || sizeof(__intrin) == 32);
__merge
= __or(__andnot(__vector_bitcast<_Tp>(__k), __merge._M_data),
__vector_bitcast<_Tp, _Np>(
__maskload_epi32(reinterpret_cast<const int*>(__mem),
__to_intrin(__k))));
}
else if constexpr (__have_avx && sizeof(_Tp) == 4)
{
static_assert(sizeof(__intrin) == 16 || sizeof(__intrin) == 32);
__merge
= __or(__andnot(__vector_bitcast<_Tp>(__k), __merge._M_data),
__vector_bitcast<_Tp, _Np>(
__maskload_ps(reinterpret_cast<const float*>(__mem),
__to_intrin(__k))));
}
else if constexpr ((__is_avx512_abi<_Abi>() || __have_avx512vl)
&& sizeof(_Tp) == 8 && std::is_integral_v<_Up>)
{
const auto __kk = _MaskImpl::_S_to_bits(__k)._M_to_bits();
if constexpr (sizeof(__intrin) == 16)
__merge = __vector_bitcast<_Tp, _Np>(
_mm_mask_loadu_epi64(__intrin, __kk, __mem));
else if constexpr (sizeof(__intrin) == 32)
__merge = __vector_bitcast<_Tp, _Np>(
_mm256_mask_loadu_epi64(__intrin, __kk, __mem));
else if constexpr (sizeof(__intrin) == 64)
__merge = __vector_bitcast<_Tp, _Np>(
_mm512_mask_loadu_epi64(__intrin, __kk, __mem));
else
__assert_unreachable<_Tp>();
}
else if constexpr ((__is_avx512_abi<_Abi>() || __have_avx512vl)
&& sizeof(_Tp) == 8 && std::is_floating_point_v<_Up>)
{
const auto __kk = _MaskImpl::_S_to_bits(__k)._M_to_bits();
if constexpr (sizeof(__intrin) == 16)
__merge = __vector_bitcast<_Tp, _Np>(
_mm_mask_loadu_pd(__intrin, __kk, __mem));
else if constexpr (sizeof(__intrin) == 32)
__merge = __vector_bitcast<_Tp, _Np>(
_mm256_mask_loadu_pd(__intrin, __kk, __mem));
else if constexpr (sizeof(__intrin) == 64)
__merge = __vector_bitcast<_Tp, _Np>(
_mm512_mask_loadu_pd(__intrin, __kk, __mem));
else
__assert_unreachable<_Tp>();
}
else if constexpr (__have_avx2 && sizeof(_Tp) == 8
&& std::is_integral_v<_Up>)
{
static_assert(sizeof(__intrin) == 16 || sizeof(__intrin) == 32);
__merge
= __or(__andnot(__vector_bitcast<_Tp>(__k), __merge._M_data),
__vector_bitcast<_Tp, _Np>(
__maskload_epi64(reinterpret_cast<const _LLong*>(__mem),
__to_intrin(__k))));
}
else if constexpr (__have_avx && sizeof(_Tp) == 8)
{
static_assert(sizeof(__intrin) == 16 || sizeof(__intrin) == 32);
__merge
= __or(__andnot(__vector_bitcast<_Tp>(__k), __merge._M_data),
__vector_bitcast<_Tp, _Np>(
__maskload_pd(reinterpret_cast<const double*>(__mem),
__to_intrin(__k))));
}
else
_BitOps::_S_bit_iteration(_MaskImpl::_S_to_bits(__k), [&](auto __i) {
__merge._M_set(__i, static_cast<_Tp>(__mem[__i]));
});
}
else
__merge = _Base::_S_masked_load(__merge, __k, __mem);
return __merge;
}
template <typename _Tp, std::size_t _Np>
_GLIBCXX_SIMD_INTRINSIC static void
_S_masked_store_nocvt(_SimdWrapper<_Tp, _Np> __v, _Tp* __mem,
_SimdWrapper<bool, _Np> __k)
{
[[maybe_unused]] const auto __vi = __to_intrin(__v);
if constexpr (sizeof(__vi) == 64)
{
static_assert(sizeof(__v) == 64 && __have_avx512f);
if constexpr (__have_avx512bw && sizeof(_Tp) == 1)
_mm512_mask_storeu_epi8(__mem, __k, __vi);
else if constexpr (__have_avx512bw && sizeof(_Tp) == 2)
_mm512_mask_storeu_epi16(__mem, __k, __vi);
else if constexpr (__have_avx512f && sizeof(_Tp) == 4)
{
if constexpr (std::is_integral_v<_Tp>)
_mm512_mask_storeu_epi32(__mem, __k, __vi);
else
_mm512_mask_storeu_ps(__mem, __k, __vi);
}
else if constexpr (__have_avx512f && sizeof(_Tp) == 8)
{
if constexpr (std::is_integral_v<_Tp>)
_mm512_mask_storeu_epi64(__mem, __k, __vi);
else
_mm512_mask_storeu_pd(__mem, __k, __vi);
}
#if 0
else if constexpr (__have_sse2)
{
using _M = __vector_type_t<_Tp, _Np>;
using _MVT = _VectorTraits<_M>;
_mm_maskmoveu_si128(__auto_bitcast(__extract<0, 4>(__v._M_data)),
__auto_bitcast(_MaskImpl::template _S_convert<_Tp, _Np>(__k._M_data)),
reinterpret_cast<char*>(__mem));
_mm_maskmoveu_si128(__auto_bitcast(__extract<1, 4>(__v._M_data)),
__auto_bitcast(_MaskImpl::template _S_convert<_Tp, _Np>(
__k._M_data >> 1 * _MVT::_S_full_size)),
reinterpret_cast<char*>(__mem) + 1 * 16);
_mm_maskmoveu_si128(__auto_bitcast(__extract<2, 4>(__v._M_data)),
__auto_bitcast(_MaskImpl::template _S_convert<_Tp, _Np>(
__k._M_data >> 2 * _MVT::_S_full_size)),
reinterpret_cast<char*>(__mem) + 2 * 16);
if constexpr (_Np > 48 / sizeof(_Tp))
_mm_maskmoveu_si128(
__auto_bitcast(__extract<3, 4>(__v._M_data)),
__auto_bitcast(_MaskImpl::template _S_convert<_Tp, _Np>(
__k._M_data >> 3 * _MVT::_S_full_size)),
reinterpret_cast<char*>(__mem) + 3 * 16);
}
#endif
else
__assert_unreachable<_Tp>();
}
else if constexpr (sizeof(__vi) == 32)
{
if constexpr (__have_avx512bw_vl && sizeof(_Tp) == 1)
_mm256_mask_storeu_epi8(__mem, __k, __vi);
else if constexpr (__have_avx512bw_vl && sizeof(_Tp) == 2)
_mm256_mask_storeu_epi16(__mem, __k, __vi);
else if constexpr (__have_avx512vl && sizeof(_Tp) == 4)
{
if constexpr (std::is_integral_v<_Tp>)
_mm256_mask_storeu_epi32(__mem, __k, __vi);
else
_mm256_mask_storeu_ps(__mem, __k, __vi);
}
else if constexpr (__have_avx512vl && sizeof(_Tp) == 8)
{
if constexpr (std::is_integral_v<_Tp>)
_mm256_mask_storeu_epi64(__mem, __k, __vi);
else
_mm256_mask_storeu_pd(__mem, __k, __vi);
}
else if constexpr (__have_avx512f
&& (sizeof(_Tp) >= 4 || __have_avx512bw))
{
_S_masked_store_nocvt(
_SimdWrapper64<_Tp>(
__intrin_bitcast<__vector_type64_t<_Tp>>(__v._M_data)),
__mem, _SimdWrapper<bool, 64 / sizeof(_Tp)>(__k._M_data));
}
else
_S_masked_store_nocvt(
__v, __mem,
_MaskImpl::template _S_to_maskvector<__int_for_sizeof_t<_Tp>, _Np>(
__k));
}
else if constexpr (sizeof(__vi) == 16)
{
if constexpr (__have_avx512bw_vl && sizeof(_Tp) == 1)
_mm_mask_storeu_epi8(__mem, __k, __vi);
else if constexpr (__have_avx512bw_vl && sizeof(_Tp) == 2)
_mm_mask_storeu_epi16(__mem, __k, __vi);
else if constexpr (__have_avx512vl && sizeof(_Tp) == 4)
{
if constexpr (std::is_integral_v<_Tp>)
_mm_mask_storeu_epi32(__mem, __k, __vi);
else
_mm_mask_storeu_ps(__mem, __k, __vi);
}
else if constexpr (__have_avx512vl && sizeof(_Tp) == 8)
{
if constexpr (std::is_integral_v<_Tp>)
_mm_mask_storeu_epi64(__mem, __k, __vi);
else
_mm_mask_storeu_pd(__mem, __k, __vi);
}
else if constexpr (__have_avx512f
&& (sizeof(_Tp) >= 4 || __have_avx512bw))
{
_S_masked_store_nocvt(
_SimdWrapper64<_Tp>(
__intrin_bitcast<__intrinsic_type64_t<_Tp>>(__v._M_data)),
__mem, _SimdWrapper<bool, 64 / sizeof(_Tp)>(__k._M_data));
}
else
_S_masked_store_nocvt(
__v, __mem,
_MaskImpl::template _S_to_maskvector<__int_for_sizeof_t<_Tp>, _Np>(
__k));
}
else
__assert_unreachable<_Tp>();
}
template <typename _Tp, size_t _Np>
_GLIBCXX_SIMD_INTRINSIC static void
_S_masked_store_nocvt(_SimdWrapper<_Tp, _Np> __v, _Tp* __mem,
_SimdWrapper<__int_for_sizeof_t<_Tp>, _Np> __k)
{
if constexpr (sizeof(__v) <= 16)
{
[[maybe_unused]] const auto __vi
= __intrin_bitcast<__m128i>(__as_vector(__v));
[[maybe_unused]] const auto __ki
= __intrin_bitcast<__m128i>(__as_vector(__k));
if constexpr (__have_avx512bw_vl && sizeof(_Tp) == 1)
_mm_mask_storeu_epi8(__mem, _mm_movepi8_mask(__ki), __vi);
else if constexpr (__have_avx512bw_vl && sizeof(_Tp) == 2)
_mm_mask_storeu_epi16(__mem, _mm_movepi16_mask(__ki), __vi);
else if constexpr (__have_avx2 && sizeof(_Tp) == 4
&& std::is_integral_v<_Tp>)
_mm_maskstore_epi32(reinterpret_cast<int*>(__mem), __ki, __vi);
else if constexpr (__have_avx && sizeof(_Tp) == 4)
_mm_maskstore_ps(reinterpret_cast<float*>(__mem), __ki,
__vector_bitcast<float>(__vi));
else if constexpr (__have_avx2 && sizeof(_Tp) == 8
&& std::is_integral_v<_Tp>)
_mm_maskstore_epi64(reinterpret_cast<_LLong*>(__mem), __ki, __vi);
else if constexpr (__have_avx && sizeof(_Tp) == 8)
_mm_maskstore_pd(reinterpret_cast<double*>(__mem), __ki,
__vector_bitcast<double>(__vi));
else if constexpr (__have_sse2)
_mm_maskmoveu_si128(__vi, __ki, reinterpret_cast<char*>(__mem));
}
else if constexpr (sizeof(__v) == 32)
{
[[maybe_unused]] const auto __vi
= __intrin_bitcast<__m256i>(__as_vector(__v));
[[maybe_unused]] const auto __ki
= __intrin_bitcast<__m256i>(__as_vector(__k));
if constexpr (__have_avx512bw_vl && sizeof(_Tp) == 1)
_mm256_mask_storeu_epi8(__mem, _mm256_movepi8_mask(__ki), __vi);
else if constexpr (__have_avx512bw_vl && sizeof(_Tp) == 2)
_mm256_mask_storeu_epi16(__mem, _mm256_movepi16_mask(__ki), __vi);
else if constexpr (__have_avx2 && sizeof(_Tp) == 4
&& std::is_integral_v<_Tp>)
_mm256_maskstore_epi32(reinterpret_cast<int*>(__mem), __ki, __vi);
else if constexpr (sizeof(_Tp) == 4)
_mm256_maskstore_ps(reinterpret_cast<float*>(__mem), __ki,
__vector_bitcast<float>(__v));
else if constexpr (__have_avx2 && sizeof(_Tp) == 8
&& std::is_integral_v<_Tp>)
_mm256_maskstore_epi64(reinterpret_cast<_LLong*>(__mem), __ki, __vi);
else if constexpr (__have_avx && sizeof(_Tp) == 8)
_mm256_maskstore_pd(reinterpret_cast<double*>(__mem), __ki,
__vector_bitcast<double>(__v));
else if constexpr (__have_sse2)
{
_mm_maskmoveu_si128(__lo128(__vi), __lo128(__ki),
reinterpret_cast<char*>(__mem));
_mm_maskmoveu_si128(__hi128(__vi), __hi128(__ki),
reinterpret_cast<char*>(__mem) + 16);
}
}
else
__assert_unreachable<_Tp>();
}
template <typename _Tp, size_t _Np, typename _Up>
_GLIBCXX_SIMD_INTRINSIC static void
_S_masked_store(const _SimdWrapper<_Tp, _Np> __v, _Up* __mem,
const _MaskMember<_Tp> __k) noexcept
{
if constexpr (std::is_integral_v<
_Tp> && std::is_integral_v<_Up> && sizeof(_Tp) > sizeof(_Up)
&& __have_avx512f && (sizeof(_Tp) >= 4 || __have_avx512bw)
&& (sizeof(__v) == 64 || __have_avx512vl))
{
const auto __vi = __to_intrin(__v);
const auto __kk = _MaskImpl::_S_to_bits(__k)._M_to_bits();
if constexpr (sizeof(_Tp) == 8 && sizeof(_Up) == 4
&& sizeof(__vi) == 64)
_mm512_mask_cvtepi64_storeu_epi32(__mem, __kk, __vi);
else if constexpr (sizeof(_Tp) == 8 && sizeof(_Up) == 4
&& sizeof(__vi) == 32)
_mm256_mask_cvtepi64_storeu_epi32(__mem, __kk, __vi);
else if constexpr (sizeof(_Tp) == 8 && sizeof(_Up) == 4
&& sizeof(__vi) == 16)
_mm_mask_cvtepi64_storeu_epi32(__mem, __kk, __vi);
else if constexpr (sizeof(_Tp) == 8 && sizeof(_Up) == 2
&& sizeof(__vi) == 64)
_mm512_mask_cvtepi64_storeu_epi16(__mem, __kk, __vi);
else if constexpr (sizeof(_Tp) == 8 && sizeof(_Up) == 2
&& sizeof(__vi) == 32)
_mm256_mask_cvtepi64_storeu_epi16(__mem, __kk, __vi);
else if constexpr (sizeof(_Tp) == 8 && sizeof(_Up) == 2
&& sizeof(__vi) == 16)
_mm_mask_cvtepi64_storeu_epi16(__mem, __kk, __vi);
else if constexpr (sizeof(_Tp) == 8 && sizeof(_Up) == 1
&& sizeof(__vi) == 64)
_mm512_mask_cvtepi64_storeu_epi8(__mem, __kk, __vi);
else if constexpr (sizeof(_Tp) == 8 && sizeof(_Up) == 1
&& sizeof(__vi) == 32)
_mm256_mask_cvtepi64_storeu_epi8(__mem, __kk, __vi);
else if constexpr (sizeof(_Tp) == 8 && sizeof(_Up) == 1
&& sizeof(__vi) == 16)
_mm_mask_cvtepi64_storeu_epi8(__mem, __kk, __vi);
else if constexpr (sizeof(_Tp) == 4 && sizeof(_Up) == 2
&& sizeof(__vi) == 64)
_mm512_mask_cvtepi32_storeu_epi16(__mem, __kk, __vi);
else if constexpr (sizeof(_Tp) == 4 && sizeof(_Up) == 2
&& sizeof(__vi) == 32)
_mm256_mask_cvtepi32_storeu_epi16(__mem, __kk, __vi);
else if constexpr (sizeof(_Tp) == 4 && sizeof(_Up) == 2
&& sizeof(__vi) == 16)
_mm_mask_cvtepi32_storeu_epi16(__mem, __kk, __vi);
else if constexpr (sizeof(_Tp) == 4 && sizeof(_Up) == 1
&& sizeof(__vi) == 64)
_mm512_mask_cvtepi32_storeu_epi8(__mem, __kk, __vi);
else if constexpr (sizeof(_Tp) == 4 && sizeof(_Up) == 1
&& sizeof(__vi) == 32)
_mm256_mask_cvtepi32_storeu_epi8(__mem, __kk, __vi);
else if constexpr (sizeof(_Tp) == 4 && sizeof(_Up) == 1
&& sizeof(__vi) == 16)
_mm_mask_cvtepi32_storeu_epi8(__mem, __kk, __vi);
else if constexpr (sizeof(_Tp) == 2 && sizeof(_Up) == 1
&& sizeof(__vi) == 64)
_mm512_mask_cvtepi16_storeu_epi8(__mem, __kk, __vi);
else if constexpr (sizeof(_Tp) == 2 && sizeof(_Up) == 1
&& sizeof(__vi) == 32)
_mm256_mask_cvtepi16_storeu_epi8(__mem, __kk, __vi);
else if constexpr (sizeof(_Tp) == 2 && sizeof(_Up) == 1
&& sizeof(__vi) == 16)
_mm_mask_cvtepi16_storeu_epi8(__mem, __kk, __vi);
else
__assert_unreachable<_Tp>();
}
else
_Base::_S_masked_store(__v, __mem, __k);
}
template <typename _V, typename _VVT = _VectorTraits<_V>>
_GLIBCXX_SIMD_INTRINSIC static constexpr _V _S_multiplies(_V __x, _V __y)
{
using _Tp = typename _VVT::value_type;
if (__builtin_is_constant_evaluated() || __x._M_is_constprop()
|| __y._M_is_constprop())
return __as_vector(__x) * __as_vector(__y);
else if constexpr (sizeof(_Tp) == 1)
{
if constexpr (sizeof(_V) == 2)
{
const auto __xs = reinterpret_cast<short>(__x._M_data);
const auto __ys = reinterpret_cast<short>(__y._M_data);
return reinterpret_cast<__vector_type_t<_Tp, 2>>(
short(((__xs * __ys) & 0xff) | ((__xs >> 8) * (__ys & 0xff00))));
}
else if constexpr (sizeof(_V) == 4 && _VVT::_S_partial_width == 3)
{
const auto __xi = reinterpret_cast<int>(__x._M_data);
const auto __yi = reinterpret_cast<int>(__y._M_data);
return reinterpret_cast<__vector_type_t<_Tp, 3>>(
((__xi * __yi) & 0xff)
| (((__xi >> 8) * (__yi & 0xff00)) & 0xff00)
| ((__xi >> 16) * (__yi & 0xff0000)));
}
else if constexpr (sizeof(_V) == 4)
{
const auto __xi = reinterpret_cast<int>(__x._M_data);
const auto __yi = reinterpret_cast<int>(__y._M_data);
return reinterpret_cast<__vector_type_t<_Tp, 4>>(
((__xi * __yi) & 0xff)
| (((__xi >> 8) * (__yi & 0xff00)) & 0xff00)
| (((__xi >> 16) * (__yi & 0xff0000)) & 0xff0000)
| ((__xi >> 24) * (__yi & 0xff000000u)));
}
else if constexpr (sizeof(_V) == 8 && __have_avx2
&& std::is_signed_v<_Tp>)
return __convert<typename _VVT::type>(
__vector_bitcast<short>(_mm_cvtepi8_epi16(__to_intrin(__x)))
* __vector_bitcast<short>(_mm_cvtepi8_epi16(__to_intrin(__y))));
else if constexpr (sizeof(_V) == 8 && __have_avx2
&& std::is_unsigned_v<_Tp>)
return __convert<typename _VVT::type>(
__vector_bitcast<short>(_mm_cvtepu8_epi16(__to_intrin(__x)))
* __vector_bitcast<short>(_mm_cvtepu8_epi16(__to_intrin(__y))));
else
{
constexpr size_t __full_size = _VVT::_S_full_size;
constexpr int _Np = sizeof(_V) >= 16 ? __full_size / 2 : 8;
using _ShortW = _SimdWrapper<short, _Np>;
const _ShortW __even = __vector_bitcast<short, _Np>(__x)
* __vector_bitcast<short, _Np>(__y);
_ShortW __high_byte = _ShortW()._M_data - 256;
const _ShortW __odd
= (__vector_bitcast<short, _Np>(__x) >> 8)
* (__vector_bitcast<short, _Np>(__y) & __high_byte._M_data);
if constexpr (__have_avx512bw && sizeof(_V) > 2)
return _CommonImplX86::_S_blend_avx512(
0xaaaa'aaaa'aaaa'aaaaLL, __vector_bitcast<_Tp>(__even),
__vector_bitcast<_Tp>(__odd));
else if constexpr (__have_sse4_1 && sizeof(_V) > 2)
return _CommonImplX86::_S_blend_intrin(__to_intrin(__high_byte),
__to_intrin(__even),
__to_intrin(__odd));
else
return __to_intrin(__or(__andnot(__high_byte, __even), __odd));
}
}
else
return _Base::_S_multiplies(__x, __y);
}
#ifdef _GLIBCXX_SIMD_WORKAROUND_PR90993
template <typename _Tp, size_t _Np>
_GLIBCXX_SIMD_INTRINSIC static constexpr _SimdWrapper<_Tp, _Np>
_S_divides(_SimdWrapper<_Tp, _Np> __x, _SimdWrapper<_Tp, _Np> __y)
{
if (!__builtin_is_constant_evaluated()
&& !__builtin_constant_p(__y._M_data))
if constexpr (is_integral_v<_Tp> && sizeof(_Tp) <= 4)
{
using _Float = conditional_t<sizeof(_Tp) == 4, double, float>;
constexpr size_t __n_intermediate
= std::min(_Np, (__have_avx512f ? 64 : __have_avx ? 32 : 16)
/ sizeof(_Float));
using _FloatV = __vector_type_t<_Float, __n_intermediate>;
constexpr size_t __n_floatv = __div_roundup(_Np, __n_intermediate);
using _R = __vector_type_t<_Tp, _Np>;
const auto __xf = __convert_all<_FloatV, __n_floatv>(__x);
const auto __yf = __convert_all<_FloatV, __n_floatv>(
_Abi::__make_padding_nonzero(__as_vector(__y)));
return __call_with_n_evaluations<__n_floatv>(
[](auto... __quotients) {
return __vector_convert<_R>(__quotients...);
},
[&__xf, &__yf](auto __i) -> _SimdWrapper<_Float, __n_intermediate> {
#if !defined __clang__ && __GCC_IEC_559 == 0
_FloatV __r;
if constexpr (__have_avx)
{
if constexpr (sizeof(_Tp) == 4)
asm("vdivpd\t{%2, %1, %0|%0, %1, %2}"
: "=x"(__r)
: "x"(__xf[__i]), "x"(__yf[__i]));
else
asm("vdivps\t{%2, %1, %0|%0, %1, %2}"
: "=x"(__r)
: "x"(__xf[__i]), "x"(__yf[__i]));
}
else
{
__r = __xf[__i];
if constexpr (sizeof(_Tp) == 4)
asm("divpd\t{%1, %0|%0, %1}" : "=x"(__r) : "x"(__yf[__i]));
else
asm("divps\t{%1, %0|%0, %1}" : "=x"(__r) : "x"(__yf[__i]));
}
return __r;
#else
return __xf[__i] / __yf[__i];
#endif
});
}
return _Base::_S_divides(__x, __y);
}
#endif
template <typename _Tp, size_t _Np>
_GLIBCXX_SIMD_INTRINSIC static constexpr _SimdWrapper<_Tp, _Np>
_S_modulus(_SimdWrapper<_Tp, _Np> __x, _SimdWrapper<_Tp, _Np> __y)
{
if (__builtin_is_constant_evaluated() || __builtin_constant_p(__y._M_data)
|| sizeof(_Tp) >= 8)
return _Base::_S_modulus(__x, __y);
else
return _Base::_S_minus(__x, _S_multiplies(__y, _S_divides(__x, __y)));
}
#ifndef _GLIBCXX_SIMD_NO_SHIFT_OPT
template <typename _Tp, typename _TVT = _VectorTraits<_Tp>>
inline _GLIBCXX_CONST static typename _TVT::type _S_bit_shift_left(_Tp __xx,
int __y)
{
using _V = typename _TVT::type;
using _Up = typename _TVT::value_type;
_V __x = __xx;
[[maybe_unused]] const auto __ix = __to_intrin(__x);
if (__builtin_is_constant_evaluated())
return __x << __y;
#if __cplusplus > 201703
else if constexpr (sizeof(_Up) == 1 && is_signed_v<_Up>)
return __vector_bitcast<_Up>(
_S_bit_shift_left(__vector_bitcast<make_unsigned_t<_Up>>(__x), __y));
#endif
else if constexpr (sizeof(_Up) == 1)
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
if constexpr (sizeof(__x) > sizeof(unsigned))
{
const _UChar __mask = 0xff << __y;
return __vector_bitcast<_Up>(
__vector_bitcast<_UChar>(__vector_bitcast<unsigned>(__x)
<< __y)
& __mask);
}
else
{
const unsigned __mask
= (0xff & (0xff << __y)) * 0x01010101u;
return reinterpret_cast<_V>(
static_cast<__int_for_sizeof_t<_V>>(
unsigned(reinterpret_cast<__int_for_sizeof_t<_V>>(__x)
<< __y)
& __mask));
}
}
else if (__y >= 8 && __y < 32)
return _V();
else
__builtin_unreachable();
}
else if constexpr (__have_avx512bw_vl && sizeof(__x) == 16)
return __vector_bitcast<_Up>(
_mm256_cvtepi16_epi8(_mm256_sllv_epi16(_mm256_cvtepi8_epi16(__ix),
_mm256_set1_epi16(__y))));
else if constexpr (__have_avx512bw && sizeof(__x) == 32)
return __vector_bitcast<_Up>(
_mm512_cvtepi16_epi8(_mm512_sllv_epi16(_mm512_cvtepi8_epi16(__ix),
_mm512_set1_epi16(__y))));
else if constexpr (__have_avx512bw && sizeof(__x) == 64)
{
const auto __shift = _mm512_set1_epi16(__y);
return __vector_bitcast<_Up>(
__concat(_mm512_cvtepi16_epi8(_mm512_sllv_epi16(
_mm512_cvtepi8_epi16(__lo256(__ix)), __shift)),
_mm512_cvtepi16_epi8(_mm512_sllv_epi16(
_mm512_cvtepi8_epi16(__hi256(__ix)), __shift))));
}
else if constexpr (__have_avx2 && sizeof(__x) == 32)
{
#if 1
const auto __shift = _mm_cvtsi32_si128(__y);
auto __k
= _mm256_sll_epi16(_mm256_slli_epi16(~__m256i(), 8), __shift);
__k |= _mm256_srli_epi16(__k, 8);
return __vector_bitcast<_Up>(_mm256_sll_epi32(__ix, __shift) & __k);
#else
const _Up __k = 0xff << __y;
return __vector_bitcast<_Up>(__vector_bitcast<int>(__x) << __y)
& __k;
#endif
}
else
{
const auto __shift = _mm_cvtsi32_si128(__y);
auto __k = _mm_sll_epi16(_mm_slli_epi16(~__m128i(), 8), __shift);
__k |= _mm_srli_epi16(__k, 8);
return __intrin_bitcast<_V>(_mm_sll_epi16(__ix, __shift) & __k);
}
}
return __x << __y;
}
template <typename _Tp, typename _TVT = _VectorTraits<_Tp>>
inline _GLIBCXX_CONST static typename _TVT::type
_S_bit_shift_left(_Tp __xx, typename _TVT::type __y)
{
using _V = typename _TVT::type;
using _Up = typename _TVT::value_type;
_V __x = __xx;
[[maybe_unused]] const auto __ix = __to_intrin(__x);
[[maybe_unused]] const auto __iy = __to_intrin(__y);
if (__builtin_is_constant_evaluated())
return __x << __y;
#if __cplusplus > 201703
else if constexpr (is_signed_v<_Up>)
return __vector_bitcast<_Up>(
_S_bit_shift_left(__vector_bitcast<make_unsigned_t<_Up>>(__x),
__vector_bitcast<make_unsigned_t<_Up>>(__y)));
#endif
else if constexpr (sizeof(_Up) == 1)
{
if constexpr (sizeof __ix == 64 && __have_avx512bw)
return __vector_bitcast<_Up>(
__concat(_mm512_cvtepi16_epi8(
_mm512_sllv_epi16(_mm512_cvtepu8_epi16(__lo256(__ix)),
_mm512_cvtepu8_epi16(__lo256(__iy)))),
_mm512_cvtepi16_epi8(_mm512_sllv_epi16(
_mm512_cvtepu8_epi16(__hi256(__ix)),
_mm512_cvtepu8_epi16(__hi256(__iy))))));
else if constexpr (sizeof __ix == 32 && __have_avx512bw)
return __vector_bitcast<_Up>(_mm512_cvtepi16_epi8(
_mm512_sllv_epi16(_mm512_cvtepu8_epi16(__ix),
_mm512_cvtepu8_epi16(__iy))));
else if constexpr (sizeof __x <= 8 && __have_avx512bw_vl)
return __intrin_bitcast<_V>(_mm_cvtepi16_epi8(
_mm_sllv_epi16(_mm_cvtepu8_epi16(__ix), _mm_cvtepu8_epi16(__iy))));
else if constexpr (sizeof __ix == 16 && __have_avx512bw_vl)
return __intrin_bitcast<_V>(_mm256_cvtepi16_epi8(
_mm256_sllv_epi16(_mm256_cvtepu8_epi16(__ix),
_mm256_cvtepu8_epi16(__iy))));
else if constexpr (sizeof __ix == 16 && __have_avx512bw)
return __intrin_bitcast<_V>(
__lo128(_mm512_cvtepi16_epi8(_mm512_sllv_epi16(
_mm512_cvtepu8_epi16(_mm256_castsi128_si256(__ix)),
_mm512_cvtepu8_epi16(_mm256_castsi128_si256(__iy))))));
else if constexpr (__have_sse4_1 && sizeof(__x) == 16)
{
auto __mask
= __vector_bitcast<_Up>(__vector_bitcast<short>(__y) << 5);
auto __x4
= __vector_bitcast<_Up>(__vector_bitcast<short>(__x) << 4);
__x4 &= char(0xf0);
__x = reinterpret_cast<_V>(_CommonImplX86::_S_blend_intrin(
__to_intrin(__mask), __to_intrin(__x), __to_intrin(__x4)));
__mask += __mask;
auto __x2
= __vector_bitcast<_Up>(__vector_bitcast<short>(__x) << 2);
__x2 &= char(0xfc);
__x = reinterpret_cast<_V>(_CommonImplX86::_S_blend_intrin(
__to_intrin(__mask), __to_intrin(__x), __to_intrin(__x2)));
__mask += __mask;
auto __x1 = __x + __x;
__x = reinterpret_cast<_V>(_CommonImplX86::_S_blend_intrin(
__to_intrin(__mask), __to_intrin(__x), __to_intrin(__x1)));
return __x & ((__y & char(0xf8)) == 0);
}
else if constexpr (sizeof(__x) == 16)
{
auto __mask
= __vector_bitcast<_UChar>(__vector_bitcast<short>(__y) << 5);
auto __x4
= __vector_bitcast<_Up>(__vector_bitcast<short>(__x) << 4);
__x4 &= char(0xf0);
__x = __vector_bitcast<_SChar>(__mask) < 0 ? __x4 : __x;
__mask += __mask;
auto __x2
= __vector_bitcast<_Up>(__vector_bitcast<short>(__x) << 2);
__x2 &= char(0xfc);
__x = __vector_bitcast<_SChar>(__mask) < 0 ? __x2 : __x;
__mask += __mask;
auto __x1 = __x + __x;
__x = __vector_bitcast<_SChar>(__mask) < 0 ? __x1 : __x;
return __x & ((__y & char(0xf8)) == 0);
}
else
return __x << __y;
}
else if constexpr (sizeof(_Up) == 2)
{
if constexpr (sizeof __ix == 64 && __have_avx512bw)
return __vector_bitcast<_Up>(_mm512_sllv_epi16(__ix, __iy));
else if constexpr (sizeof __ix == 32 && __have_avx512bw_vl)
return __vector_bitcast<_Up>(_mm256_sllv_epi16(__ix, __iy));
else if constexpr (sizeof __ix == 32 && __have_avx512bw)
return __vector_bitcast<_Up>(
__lo256(_mm512_sllv_epi16(_mm512_castsi256_si512(__ix),
_mm512_castsi256_si512(__iy))));
else if constexpr (sizeof __ix == 32 && __have_avx2)
{
const auto __ux = __vector_bitcast<unsigned>(__x);
const auto __uy = __vector_bitcast<unsigned>(__y);
return __vector_bitcast<_Up>(_mm256_blend_epi16(
__auto_bitcast(__ux << (__uy & 0x0000ffffu)),
__auto_bitcast((__ux & 0xffff0000u) << (__uy >> 16)), 0xaa));
}
else if constexpr (sizeof __ix == 16 && __have_avx512bw_vl)
return __intrin_bitcast<_V>(_mm_sllv_epi16(__ix, __iy));
else if constexpr (sizeof __ix == 16 && __have_avx512bw)
return __intrin_bitcast<_V>(
__lo128(_mm512_sllv_epi16(_mm512_castsi128_si512(__ix),
_mm512_castsi128_si512(__iy))));
else if constexpr (sizeof __ix == 16 && __have_avx2)
{
const auto __ux = __vector_bitcast<unsigned>(__ix);
const auto __uy = __vector_bitcast<unsigned>(__iy);
return __intrin_bitcast<_V>(_mm_blend_epi16(
__auto_bitcast(__ux << (__uy & 0x0000ffffu)),
__auto_bitcast((__ux & 0xffff0000u) << (__uy >> 16)), 0xaa));
}
else if constexpr (sizeof __ix == 16)
{
using _Float4 = __vector_type_t<float, 4>;
using _Int4 = __vector_type_t<int, 4>;
using _UInt4 = __vector_type_t<unsigned, 4>;
const _UInt4 __yu
= reinterpret_cast<_UInt4>(__to_intrin(__y + (0x3f8 >> 3)));
return __x
* __intrin_bitcast<_V>(
__vector_convert<_Int4>(_SimdWrapper<float, 4>(
reinterpret_cast<_Float4>(__yu << 23)))
| (__vector_convert<_Int4>(_SimdWrapper<float, 4>(
reinterpret_cast<_Float4>((__yu >> 16) << 23)))
<< 16));
}
else
__assert_unreachable<_Tp>();
}
else if constexpr (sizeof(_Up) == 4 && sizeof __ix == 16 && !__have_avx2)
return __intrin_bitcast<_V>(
__vector_bitcast<unsigned>(__ix)
* __vector_convert<__vector_type16_t<int>>(
_SimdWrapper<float, 4>(__vector_bitcast<float>(
(__vector_bitcast<unsigned, 4>(__y) << 23) + 0x3f80'0000))));
else if constexpr (sizeof(_Up) == 8 && sizeof __ix == 16 && !__have_avx2)
{
const auto __lo = _mm_sll_epi64(__ix, __iy);
const auto __hi = _mm_sll_epi64(__ix, _mm_unpackhi_epi64(__iy, __iy));
if constexpr (__have_sse4_1)
return __vector_bitcast<_Up>(_mm_blend_epi16(__lo, __hi, 0xf0));
else
return __vector_bitcast<_Up>(
_mm_move_sd(__vector_bitcast<double>(__hi),
__vector_bitcast<double>(__lo)));
}
else
return __x << __y;
}
#endif
#ifndef _GLIBCXX_SIMD_NO_SHIFT_OPT
template <typename _Tp, typename _TVT = _VectorTraits<_Tp>>
inline _GLIBCXX_CONST static typename _TVT::type _S_bit_shift_right(_Tp __xx,
int __y)
{
using _V = typename _TVT::type;
using _Up = typename _TVT::value_type;
_V __x = __xx;
[[maybe_unused]] const auto __ix = __to_intrin(__x);
if (__builtin_is_constant_evaluated())
return __x >> __y;
else if (__builtin_constant_p(__y)
&& std::is_unsigned_v<
_Up> && __y >= int(sizeof(_Up) * __CHAR_BIT__))
return _V();
else if constexpr (sizeof(_Up) == 1 && is_unsigned_v<_Up>)
return __intrin_bitcast<_V>(__vector_bitcast<_UShort>(__ix) >> __y)
& _Up(0xff >> __y);
else if constexpr (sizeof(_Up) == 1 && is_signed_v<_Up>)
return __intrin_bitcast<_V>(
(__vector_bitcast<_UShort>(__vector_bitcast<short>(__ix) >> (__y + 8))
<< 8)
| (__vector_bitcast<_UShort>(
__vector_bitcast<short>(__vector_bitcast<_UShort>(__ix) << 8)
>> __y)
>> 8));
else if constexpr (sizeof(_Up) == 8 && is_signed_v<_Up>)
{
if (__y > 32)
return (__intrin_bitcast<_V>(__vector_bitcast<int>(__ix) >> 32)
& _Up(0xffff'ffff'0000'0000ull))
| __vector_bitcast<_Up>(
__vector_bitcast<int>(__vector_bitcast<_ULLong>(__ix) >> 32)
>> (__y - 32));
else
return __intrin_bitcast<_V>(__vector_bitcast<_ULLong>(__ix) >> __y)
| __vector_bitcast<_Up>(
__vector_bitcast<int>(__ix & -0x8000'0000'0000'0000ll)
>> __y);
}
else
return __x >> __y;
}
template <typename _Tp, typename _TVT = _VectorTraits<_Tp>>
inline _GLIBCXX_CONST static typename _TVT::type
_S_bit_shift_right(_Tp __xx, typename _TVT::type __y)
{
using _V = typename _TVT::type;
using _Up = typename _TVT::value_type;
_V __x = __xx;
[[maybe_unused]] const auto __ix = __to_intrin(__x);
[[maybe_unused]] const auto __iy = __to_intrin(__y);
if (__builtin_is_constant_evaluated()
|| (__builtin_constant_p(__x) && __builtin_constant_p(__y)))
return __x >> __y;
else if constexpr (sizeof(_Up) == 1)
{
if constexpr (sizeof(__x) <= 8 && __have_avx512bw_vl)
return __intrin_bitcast<_V>(_mm_cvtepi16_epi8(
is_signed_v<_Up>
? _mm_srav_epi16(_mm_cvtepi8_epi16(__ix), _mm_cvtepi8_epi16(__iy))
: _mm_srlv_epi16(_mm_cvtepu8_epi16(__ix),
_mm_cvtepu8_epi16(__iy))));
if constexpr (sizeof(__x) == 16 && __have_avx512bw_vl)
return __intrin_bitcast<_V>(_mm256_cvtepi16_epi8(
is_signed_v<_Up> ? _mm256_srav_epi16(_mm256_cvtepi8_epi16(__ix),
_mm256_cvtepi8_epi16(__iy))
: _mm256_srlv_epi16(_mm256_cvtepu8_epi16(__ix),
_mm256_cvtepu8_epi16(__iy))));
else if constexpr (sizeof(__x) == 32 && __have_avx512bw)
return __vector_bitcast<_Up>(_mm512_cvtepi16_epi8(
is_signed_v<_Up> ? _mm512_srav_epi16(_mm512_cvtepi8_epi16(__ix),
_mm512_cvtepi8_epi16(__iy))
: _mm512_srlv_epi16(_mm512_cvtepu8_epi16(__ix),
_mm512_cvtepu8_epi16(__iy))));
else if constexpr (sizeof(__x) == 64 && is_signed_v<_Up>)
return __vector_bitcast<_Up>(_mm512_mask_mov_epi8(
_mm512_srav_epi16(__ix, _mm512_srli_epi16(__iy, 8)),
0x5555'5555'5555'5555ull,
_mm512_srav_epi16(_mm512_slli_epi16(__ix, 8),
_mm512_maskz_add_epi8(0x5555'5555'5555'5555ull,
__iy,
_mm512_set1_epi16(8)))));
else if constexpr (sizeof(__x) == 64 && is_unsigned_v<_Up>)
return __vector_bitcast<_Up>(_mm512_mask_mov_epi8(
_mm512_srlv_epi16(__ix, _mm512_srli_epi16(__iy, 8)),
0x5555'5555'5555'5555ull,
_mm512_srlv_epi16(
_mm512_maskz_mov_epi8(0x5555'5555'5555'5555ull, __ix),
_mm512_maskz_mov_epi8(0x5555'5555'5555'5555ull, __iy))));
else if constexpr (__have_avx2 && sizeof(__x) > 8)
if constexpr (is_signed_v<_Up>)
{
const auto r3 = __vector_bitcast<_UInt>(
(__vector_bitcast<int>(__x)
>> (__vector_bitcast<_UInt>(__y) >> 24)))
& 0xff000000u;
const auto r2 = __vector_bitcast<_UInt>((
(__vector_bitcast<int>(__x) << 8)
>> ((__vector_bitcast<_UInt>(__y) << 8) >> 24)))
& 0xff000000u;
const auto r1
= __vector_bitcast<_UInt>(
((__vector_bitcast<int>(__x) << 16)
>> ((__vector_bitcast<_UInt>(__y) << 16) >> 24)))
& 0xff000000u;
const auto r0 = __vector_bitcast<_UInt>(
(__vector_bitcast<int>(__x) << 24)
>> ((__vector_bitcast<_UInt>(__y) << 24) >> 24));
return __vector_bitcast<_Up>(r3 | (r2 >> 8) | (r1 >> 16)
| (r0 >> 24));
}
else
{
const auto r3 = (__vector_bitcast<_UInt>(__x)
>> (__vector_bitcast<_UInt>(__y) >> 24))
& 0xff000000u;
const auto r2 = ((__vector_bitcast<_UInt>(__x) << 8)
>> ((__vector_bitcast<_UInt>(__y) << 8) >> 24))
& 0xff000000u;
const auto r1 = ((__vector_bitcast<_UInt>(__x) << 16)
>> ((__vector_bitcast<_UInt>(__y) << 16) >> 24))
& 0xff000000u;
const auto r0 = (__vector_bitcast<_UInt>(__x) << 24)
>> ((__vector_bitcast<_UInt>(__y) << 24) >> 24);
return __vector_bitcast<_Up>(r3 | (r2 >> 8) | (r1 >> 16)
| (r0 >> 24));
}
else if constexpr (__have_sse4_1
&& is_unsigned_v<_Up> && sizeof(__x) > 2)
{
auto __x128 = __vector_bitcast<_Up>(__ix);
auto __mask
= __vector_bitcast<_Up>(__vector_bitcast<_UShort>(__iy) << 5);
auto __x4 = __vector_bitcast<_Up>(
(__vector_bitcast<_UShort>(__x128) >> 4) & _UShort(0xff0f));
__x128 = __vector_bitcast<_Up>(_CommonImplX86::_S_blend_intrin(
__to_intrin(__mask), __to_intrin(__x128), __to_intrin(__x4)));
__mask += __mask;
auto __x2 = __vector_bitcast<_Up>(
(__vector_bitcast<_UShort>(__x128) >> 2) & _UShort(0xff3f));
__x128 = __vector_bitcast<_Up>(_CommonImplX86::_S_blend_intrin(
__to_intrin(__mask), __to_intrin(__x128), __to_intrin(__x2)));
__mask += __mask;
auto __x1 = __vector_bitcast<_Up>(
(__vector_bitcast<_UShort>(__x128) >> 1) & _UShort(0xff7f));
__x128 = __vector_bitcast<_Up>(_CommonImplX86::_S_blend_intrin(
__to_intrin(__mask), __to_intrin(__x128), __to_intrin(__x1)));
return __intrin_bitcast<_V>(
__x128
& ((__vector_bitcast<_Up>(__iy) & char(0xf8))
== 0));
}
else if constexpr (__have_sse4_1 && is_signed_v<_Up> && sizeof(__x) > 2)
{
auto __mask
= __vector_bitcast<_UChar>(__vector_bitcast<_UShort>(__iy) << 5);
auto __maskl = [&]() {
return __to_intrin(__vector_bitcast<_UShort>(__mask) << 8);
};
auto __xh = __vector_bitcast<short>(__ix);
auto __xl = __vector_bitcast<short>(__ix) << 8;
auto __xh4 = __xh >> 4;
auto __xl4 = __xl >> 4;
__xh = __vector_bitcast<short>(_CommonImplX86::_S_blend_intrin(
__to_intrin(__mask), __to_intrin(__xh), __to_intrin(__xh4)));
__xl = __vector_bitcast<short>(
_CommonImplX86::_S_blend_intrin(__maskl(), __to_intrin(__xl),
__to_intrin(__xl4)));
__mask += __mask;
auto __xh2 = __xh >> 2;
auto __xl2 = __xl >> 2;
__xh = __vector_bitcast<short>(_CommonImplX86::_S_blend_intrin(
__to_intrin(__mask), __to_intrin(__xh), __to_intrin(__xh2)));
__xl = __vector_bitcast<short>(
_CommonImplX86::_S_blend_intrin(__maskl(), __to_intrin(__xl),
__to_intrin(__xl2)));
__mask += __mask;
auto __xh1 = __xh >> 1;
auto __xl1 = __xl >> 1;
__xh = __vector_bitcast<short>(_CommonImplX86::_S_blend_intrin(
__to_intrin(__mask), __to_intrin(__xh), __to_intrin(__xh1)));
__xl = __vector_bitcast<short>(
_CommonImplX86::_S_blend_intrin(__maskl(), __to_intrin(__xl),
__to_intrin(__xl1)));
return __intrin_bitcast<_V>(
(__vector_bitcast<_Up>((__xh & short(0xff00)))
| __vector_bitcast<_Up>(__vector_bitcast<_UShort>(__xl) >> 8))
& ((__vector_bitcast<_Up>(__iy) & char(0xf8))
== 0));
}
else if constexpr (is_unsigned_v<_Up> && sizeof(__x) > 2)
{
auto __mask
= __vector_bitcast<_Up>(__vector_bitcast<_UShort>(__y) << 5);
auto __x4 = __vector_bitcast<_Up>(
(__vector_bitcast<_UShort>(__x) >> 4) & _UShort(0xff0f));
__x = __mask > 0x7f ? __x4 : __x;
__mask += __mask;
auto __x2 = __vector_bitcast<_Up>(
(__vector_bitcast<_UShort>(__x) >> 2) & _UShort(0xff3f));
__x = __mask > 0x7f ? __x2 : __x;
__mask += __mask;
auto __x1 = __vector_bitcast<_Up>(
(__vector_bitcast<_UShort>(__x) >> 1) & _UShort(0xff7f));
__x = __mask > 0x7f ? __x1 : __x;
return __x & ((__y & char(0xf8)) == 0);
}
else if constexpr (sizeof(__x) > 2)
{
static_assert(is_signed_v<_Up>);
auto __maskh = __vector_bitcast<_UShort>(__y) << 5;
auto __maskl = __vector_bitcast<_UShort>(__y) << (5 + 8);
auto __xh = __vector_bitcast<short>(__x);
auto __xl = __vector_bitcast<short>(__x) << 8;
auto __xh4 = __xh >> 4;
auto __xl4 = __xl >> 4;
__xh = __maskh > 0x7fff ? __xh4 : __xh;
__xl = __maskl > 0x7fff ? __xl4 : __xl;
__maskh += __maskh;
__maskl += __maskl;
auto __xh2 = __xh >> 2;
auto __xl2 = __xl >> 2;
__xh = __maskh > 0x7fff ? __xh2 : __xh;
__xl = __maskl > 0x7fff ? __xl2 : __xl;
__maskh += __maskh;
__maskl += __maskl;
auto __xh1 = __xh >> 1;
auto __xl1 = __xl >> 1;
__xh = __maskh > 0x7fff ? __xh1 : __xh;
__xl = __maskl > 0x7fff ? __xl1 : __xl;
__x = __vector_bitcast<_Up>((__xh & short(0xff00)))
| __vector_bitcast<_Up>(__vector_bitcast<_UShort>(__xl) >> 8);
return __x & ((__y & char(0xf8)) == 0);
}
else
return __x >> __y;
}
else if constexpr (sizeof(_Up) == 2 && sizeof(__x) >= 4)
{
[[maybe_unused]] auto __blend_0xaa = [](auto __a, auto __b) {
if constexpr (sizeof(__a) == 16)
return _mm_blend_epi16(__to_intrin(__a), __to_intrin(__b), 0xaa);
else if constexpr (sizeof(__a) == 32)
return _mm256_blend_epi16(__to_intrin(__a), __to_intrin(__b), 0xaa);
else if constexpr (sizeof(__a) == 64)
return _mm512_mask_blend_epi16(0xaaaa'aaaaU, __to_intrin(__a),
__to_intrin(__b));
else
__assert_unreachable<decltype(__a)>();
};
if constexpr (__have_avx512bw_vl && sizeof(_Tp) <= 16)
return __intrin_bitcast<_V>(is_signed_v<_Up>
? _mm_srav_epi16(__ix, __iy)
: _mm_srlv_epi16(__ix, __iy));
else if constexpr (__have_avx512bw_vl && sizeof(_Tp) == 32)
return __vector_bitcast<_Up>(is_signed_v<_Up>
? _mm256_srav_epi16(__ix, __iy)
: _mm256_srlv_epi16(__ix, __iy));
else if constexpr (__have_avx512bw && sizeof(_Tp) == 64)
return __vector_bitcast<_Up>(is_signed_v<_Up>
? _mm512_srav_epi16(__ix, __iy)
: _mm512_srlv_epi16(__ix, __iy));
else if constexpr (__have_avx2 && is_signed_v<_Up>)
return __intrin_bitcast<_V>(
__blend_0xaa(((__vector_bitcast<int>(__ix) << 16)
>> (__vector_bitcast<int>(__iy) & 0xffffu))
>> 16,
__vector_bitcast<int>(__ix)
>> (__vector_bitcast<int>(__iy) >> 16)));
else if constexpr (__have_avx2 && is_unsigned_v<_Up>)
return __intrin_bitcast<_V>(
__blend_0xaa((__vector_bitcast<_UInt>(__ix) & 0xffffu)
>> (__vector_bitcast<_UInt>(__iy) & 0xffffu),
__vector_bitcast<_UInt>(__ix)
>> (__vector_bitcast<_UInt>(__iy) >> 16)));
else if constexpr (__have_sse4_1)
{
auto __mask = __vector_bitcast<_UShort>(__iy);
auto __x128 = __vector_bitcast<_Up>(__ix);
__mask = (__mask << 3) | (__mask << 11);
__x128 = __vector_bitcast<_Up>(
_mm_blendv_epi8(__to_intrin(__x128), __m128i(),
__to_intrin(__mask)));
__x128 = __vector_bitcast<_Up>(
_mm_blendv_epi8(__to_intrin(__x128), __to_intrin(__x128 >> 8),
__to_intrin(__mask += __mask)));
__x128 = __vector_bitcast<_Up>(
_mm_blendv_epi8(__to_intrin(__x128), __to_intrin(__x128 >> 4),
__to_intrin(__mask += __mask)));
__x128 = __vector_bitcast<_Up>(
_mm_blendv_epi8(__to_intrin(__x128), __to_intrin(__x128 >> 2),
__to_intrin(__mask += __mask)));
return __intrin_bitcast<_V>(
_mm_blendv_epi8(__to_intrin(__x128), __to_intrin(__x128 >> 1),
__to_intrin(__mask + __mask)));
}
else
{
auto __k = __vector_bitcast<_UShort>(__iy) << 11;
auto __x128 = __vector_bitcast<_Up>(__ix);
auto __mask = [](__vector_type16_t<_UShort> __kk) {
return __vector_bitcast<short>(__kk) < 0;
};
__x128 = __mask(__k) ? decltype(__x128)() : __x128;
__x128 = __mask(__k += __k) ? __x128 >> 8 : __x128;
__x128 = __mask(__k += __k) ? __x128 >> 4 : __x128;
__x128 = __mask(__k += __k) ? __x128 >> 2 : __x128;
return __intrin_bitcast<_V>(__mask(__k + __k) ? __x128 >> 1
: __x128);
}
}
else if constexpr (sizeof(_Up) == 4 && !__have_avx2)
{
if constexpr (is_unsigned_v<_Up>)
{
const __m128 __factor_f = reinterpret_cast<__m128>(
0x4f00'0000u - (__vector_bitcast<unsigned, 4>(__y) << 23));
const __m128i __factor
= __builtin_constant_p(__factor_f) ? __to_intrin(
__make_vector<unsigned>(__factor_f[0], __factor_f[1],
__factor_f[2], __factor_f[3]))
: _mm_cvttps_epi32(__factor_f);
const auto __r02
= _mm_srli_epi64(_mm_mul_epu32(__ix, __factor), 31);
const auto __r13 = _mm_mul_epu32(_mm_srli_si128(__ix, 4),
_mm_srli_si128(__factor, 4));
if constexpr (__have_sse4_1)
return __intrin_bitcast<_V>(
_mm_blend_epi16(_mm_slli_epi64(__r13, 1), __r02, 0x33));
else
return __intrin_bitcast<_V>(
__r02 | _mm_slli_si128(_mm_srli_epi64(__r13, 31), 4));
}
else
{
auto __shift = [](auto __a, auto __b) {
if constexpr (is_signed_v<_Up>)
return _mm_sra_epi32(__a, __b);
else
return _mm_srl_epi32(__a, __b);
};
const auto __r0
= __shift(__ix, _mm_unpacklo_epi32(__iy, __m128i()));
const auto __r1 = __shift(__ix, _mm_srli_epi64(__iy, 32));
const auto __r2
= __shift(__ix, _mm_unpackhi_epi32(__iy, __m128i()));
const auto __r3 = __shift(__ix, _mm_srli_si128(__iy, 12));
if constexpr (__have_sse4_1)
return __intrin_bitcast<_V>(
_mm_blend_epi16(_mm_blend_epi16(__r1, __r0, 0x3),
_mm_blend_epi16(__r3, __r2, 0x30), 0xf0));
else
return __intrin_bitcast<_V>(_mm_unpacklo_epi64(
_mm_unpacklo_epi32(__r0, _mm_srli_si128(__r1, 4)),
_mm_unpackhi_epi32(__r2, _mm_srli_si128(__r3, 4))));
}
}
else
return __x >> __y;
}
#endif
template <typename _Tp, size_t _Np>
_GLIBCXX_SIMD_INTRINSIC static constexpr _MaskMember<_Tp>
_S_equal_to(_SimdWrapper<_Tp, _Np> __x, _SimdWrapper<_Tp, _Np> __y)
{
if constexpr (__is_avx512_abi<_Abi>())
{
if (__builtin_is_constant_evaluated()
|| (__x._M_is_constprop() && __y._M_is_constprop()))
return _MaskImpl::_S_to_bits(
__as_wrapper<_Np>(__x._M_data == __y._M_data));
constexpr auto __k1 = _Abi::template _S_implicit_mask_intrin<_Tp>();
[[maybe_unused]] const auto __xi = __to_intrin(__x);
[[maybe_unused]] const auto __yi = __to_intrin(__y);
if constexpr (std::is_floating_point_v<_Tp>)
{
if constexpr (sizeof(__xi) == 64 && sizeof(_Tp) == 8)
return _mm512_mask_cmp_pd_mask(__k1, __xi, __yi, _CMP_EQ_OQ);
else if constexpr (sizeof(__xi) == 64 && sizeof(_Tp) == 4)
return _mm512_mask_cmp_ps_mask(__k1, __xi, __yi, _CMP_EQ_OQ);
else if constexpr (sizeof(__xi) == 32 && sizeof(_Tp) == 8)
return _mm256_mask_cmp_pd_mask(__k1, __xi, __yi, _CMP_EQ_OQ);
else if constexpr (sizeof(__xi) == 32 && sizeof(_Tp) == 4)
return _mm256_mask_cmp_ps_mask(__k1, __xi, __yi, _CMP_EQ_OQ);
else if constexpr (sizeof(__xi) == 16 && sizeof(_Tp) == 8)
return _mm_mask_cmp_pd_mask(__k1, __xi, __yi, _CMP_EQ_OQ);
else if constexpr (sizeof(__xi) == 16 && sizeof(_Tp) == 4)
return _mm_mask_cmp_ps_mask(__k1, __xi, __yi, _CMP_EQ_OQ);
else
__assert_unreachable<_Tp>();
}
else if constexpr (sizeof(__xi) == 64 && sizeof(_Tp) == 8)
return _mm512_mask_cmpeq_epi64_mask(__k1, __xi, __yi);
else if constexpr (sizeof(__xi) == 64 && sizeof(_Tp) == 4)
return _mm512_mask_cmpeq_epi32_mask(__k1, __xi, __yi);
else if constexpr (sizeof(__xi) == 64 && sizeof(_Tp) == 2)
return _mm512_mask_cmpeq_epi16_mask(__k1, __xi, __yi);
else if constexpr (sizeof(__xi) == 64 && sizeof(_Tp) == 1)
return _mm512_mask_cmpeq_epi8_mask(__k1, __xi, __yi);
else if constexpr (sizeof(__xi) == 32 && sizeof(_Tp) == 8)
return _mm256_mask_cmpeq_epi64_mask(__k1, __xi, __yi);
else if constexpr (sizeof(__xi) == 32 && sizeof(_Tp) == 4)
return _mm256_mask_cmpeq_epi32_mask(__k1, __xi, __yi);
else if constexpr (sizeof(__xi) == 32 && sizeof(_Tp) == 2)
return _mm256_mask_cmpeq_epi16_mask(__k1, __xi, __yi);
else if constexpr (sizeof(__xi) == 32 && sizeof(_Tp) == 1)
return _mm256_mask_cmpeq_epi8_mask(__k1, __xi, __yi);
else if constexpr (sizeof(__xi) == 16 && sizeof(_Tp) == 8)
return _mm_mask_cmpeq_epi64_mask(__k1, __xi, __yi);
else if constexpr (sizeof(__xi) == 16 && sizeof(_Tp) == 4)
return _mm_mask_cmpeq_epi32_mask(__k1, __xi, __yi);
else if constexpr (sizeof(__xi) == 16 && sizeof(_Tp) == 2)
return _mm_mask_cmpeq_epi16_mask(__k1, __xi, __yi);
else if constexpr (sizeof(__xi) == 16 && sizeof(_Tp) == 1)
return _mm_mask_cmpeq_epi8_mask(__k1, __xi, __yi);
else
__assert_unreachable<_Tp>();
}
else if (__builtin_is_constant_evaluated())
return _Base::_S_equal_to(__x, __y);
else if constexpr (sizeof(__x) == 8)
{
const auto __r128 = __vector_bitcast<_Tp, 16 / sizeof(_Tp)>(__x)
== __vector_bitcast<_Tp, 16 / sizeof(_Tp)>(__y);
_MaskMember<_Tp> __r64;
__builtin_memcpy(&__r64._M_data, &__r128, sizeof(__r64));
return __r64;
}
else
return _Base::_S_equal_to(__x, __y);
}
template <typename _Tp, size_t _Np>
_GLIBCXX_SIMD_INTRINSIC static constexpr _MaskMember<_Tp>
_S_not_equal_to(_SimdWrapper<_Tp, _Np> __x, _SimdWrapper<_Tp, _Np> __y)
{
if constexpr (__is_avx512_abi<_Abi>())
{
if (__builtin_is_constant_evaluated()
|| (__x._M_is_constprop() && __y._M_is_constprop()))
return _MaskImpl::_S_to_bits(
__as_wrapper<_Np>(__x._M_data != __y._M_data));
constexpr auto __k1 = _Abi::template _S_implicit_mask_intrin<_Tp>();
[[maybe_unused]] const auto __xi = __to_intrin(__x);
[[maybe_unused]] const auto __yi = __to_intrin(__y);
if constexpr (std::is_floating_point_v<_Tp>)
{
if constexpr (sizeof(__xi) == 64 && sizeof(_Tp) == 8)
return _mm512_mask_cmp_pd_mask(__k1, __xi, __yi, _CMP_NEQ_UQ);
else if constexpr (sizeof(__xi) == 64 && sizeof(_Tp) == 4)
return _mm512_mask_cmp_ps_mask(__k1, __xi, __yi, _CMP_NEQ_UQ);
else if constexpr (sizeof(__xi) == 32 && sizeof(_Tp) == 8)
return _mm256_mask_cmp_pd_mask(__k1, __xi, __yi, _CMP_NEQ_UQ);
else if constexpr (sizeof(__xi) == 32 && sizeof(_Tp) == 4)
return _mm256_mask_cmp_ps_mask(__k1, __xi, __yi, _CMP_NEQ_UQ);
else if constexpr (sizeof(__xi) == 16 && sizeof(_Tp) == 8)
return _mm_mask_cmp_pd_mask(__k1, __xi, __yi, _CMP_NEQ_UQ);
else if constexpr (sizeof(__xi) == 16 && sizeof(_Tp) == 4)
return _mm_mask_cmp_ps_mask(__k1, __xi, __yi, _CMP_NEQ_UQ);
else
__assert_unreachable<_Tp>();
}
else if constexpr (sizeof(__xi) == 64 && sizeof(_Tp) == 8)
return ~_mm512_mask_cmpeq_epi64_mask(__k1, __xi, __yi);
else if constexpr (sizeof(__xi) == 64 && sizeof(_Tp) == 4)
return ~_mm512_mask_cmpeq_epi32_mask(__k1, __xi, __yi);
else if constexpr (sizeof(__xi) == 64 && sizeof(_Tp) == 2)
return ~_mm512_mask_cmpeq_epi16_mask(__k1, __xi, __yi);
else if constexpr (sizeof(__xi) == 64 && sizeof(_Tp) == 1)
return ~_mm512_mask_cmpeq_epi8_mask(__k1, __xi, __yi);
else if constexpr (sizeof(__xi) == 32 && sizeof(_Tp) == 8)
return ~_mm256_mask_cmpeq_epi64_mask(__k1, __xi, __yi);
else if constexpr (sizeof(__xi) == 32 && sizeof(_Tp) == 4)
return ~_mm256_mask_cmpeq_epi32_mask(__k1, __xi, __yi);
else if constexpr (sizeof(__xi) == 32 && sizeof(_Tp) == 2)
return ~_mm256_mask_cmpeq_epi16_mask(__k1, __xi, __yi);
else if constexpr (sizeof(__xi) == 32 && sizeof(_Tp) == 1)
return ~_mm256_mask_cmpeq_epi8_mask(__k1, __xi, __yi);
else if constexpr (sizeof(__xi) == 16 && sizeof(_Tp) == 8)
return ~_mm_mask_cmpeq_epi64_mask(__k1, __xi, __yi);
else if constexpr (sizeof(__xi) == 16 && sizeof(_Tp) == 4)
return ~_mm_mask_cmpeq_epi32_mask(__k1, __xi, __yi);
else if constexpr (sizeof(__xi) == 16 && sizeof(_Tp) == 2)
return ~_mm_mask_cmpeq_epi16_mask(__k1, __xi, __yi);
else if constexpr (sizeof(__xi) == 16 && sizeof(_Tp) == 1)
return ~_mm_mask_cmpeq_epi8_mask(__k1, __xi, __yi);
else
__assert_unreachable<_Tp>();
}
else if constexpr (!__builtin_is_constant_evaluated() && sizeof(__x) == 8)
{
const auto __r128 = __vector_bitcast<_Tp, 16 / sizeof(_Tp)>(__x)
!= __vector_bitcast<_Tp, 16 / sizeof(_Tp)>(__y);
_MaskMember<_Tp> __r64;
__builtin_memcpy(&__r64._M_data, &__r128, sizeof(__r64));
return __r64;
}
else
return _Base::_S_not_equal_to(__x, __y);
}
template <typename _Tp, size_t _Np>
_GLIBCXX_SIMD_INTRINSIC static constexpr _MaskMember<_Tp>
_S_less(_SimdWrapper<_Tp, _Np> __x, _SimdWrapper<_Tp, _Np> __y)
{
if constexpr (__is_avx512_abi<_Abi>())
{
if (__builtin_is_constant_evaluated()
|| (__x._M_is_constprop() && __y._M_is_constprop()))
return _MaskImpl::_S_to_bits(
__as_wrapper<_Np>(__x._M_data < __y._M_data));
constexpr auto __k1 = _Abi::template _S_implicit_mask_intrin<_Tp>();
[[maybe_unused]] const auto __xi = __to_intrin(__x);
[[maybe_unused]] const auto __yi = __to_intrin(__y);
if constexpr (sizeof(__xi) == 64)
{
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
else if constexpr (sizeof(__xi) == 32)
{
if constexpr (std::is_same_v<_Tp, float>)
return _mm256_mask_cmp_ps_mask(__k1, __xi, __yi, _CMP_LT_OS);
else if constexpr (std::is_same_v<_Tp, double>)
return _mm256_mask_cmp_pd_mask(__k1, __xi, __yi, _CMP_LT_OS);
else if constexpr (std::is_signed_v<_Tp> && sizeof(_Tp) == 1)
return _mm256_mask_cmplt_epi8_mask(__k1, __xi, __yi);
else if constexpr (std::is_signed_v<_Tp> && sizeof(_Tp) == 2)
return _mm256_mask_cmplt_epi16_mask(__k1, __xi, __yi);
else if constexpr (std::is_signed_v<_Tp> && sizeof(_Tp) == 4)
return _mm256_mask_cmplt_epi32_mask(__k1, __xi, __yi);
else if constexpr (std::is_signed_v<_Tp> && sizeof(_Tp) == 8)
return _mm256_mask_cmplt_epi64_mask(__k1, __xi, __yi);
else if constexpr (std::is_unsigned_v<_Tp> && sizeof(_Tp) == 1)
return _mm256_mask_cmplt_epu8_mask(__k1, __xi, __yi);
else if constexpr (std::is_unsigned_v<_Tp> && sizeof(_Tp) == 2)
return _mm256_mask_cmplt_epu16_mask(__k1, __xi, __yi);
else if constexpr (std::is_unsigned_v<_Tp> && sizeof(_Tp) == 4)
return _mm256_mask_cmplt_epu32_mask(__k1, __xi, __yi);
else if constexpr (std::is_unsigned_v<_Tp> && sizeof(_Tp) == 8)
return _mm256_mask_cmplt_epu64_mask(__k1, __xi, __yi);
else
__assert_unreachable<_Tp>();
}
else if constexpr (sizeof(__xi) == 16)
{
if constexpr (std::is_same_v<_Tp, float>)
return _mm_mask_cmp_ps_mask(__k1, __xi, __yi, _CMP_LT_OS);
else if constexpr (std::is_same_v<_Tp, double>)
return _mm_mask_cmp_pd_mask(__k1, __xi, __yi, _CMP_LT_OS);
else if constexpr (std::is_signed_v<_Tp> && sizeof(_Tp) == 1)
return _mm_mask_cmplt_epi8_mask(__k1, __xi, __yi);
else if constexpr (std::is_signed_v<_Tp> && sizeof(_Tp) == 2)
return _mm_mask_cmplt_epi16_mask(__k1, __xi, __yi);
else if constexpr (std::is_signed_v<_Tp> && sizeof(_Tp) == 4)
return _mm_mask_cmplt_epi32_mask(__k1, __xi, __yi);
else if constexpr (std::is_signed_v<_Tp> && sizeof(_Tp) == 8)
return _mm_mask_cmplt_epi64_mask(__k1, __xi, __yi);
else if constexpr (std::is_unsigned_v<_Tp> && sizeof(_Tp) == 1)
return _mm_mask_cmplt_epu8_mask(__k1, __xi, __yi);
else if constexpr (std::is_unsigned_v<_Tp> && sizeof(_Tp) == 2)
return _mm_mask_cmplt_epu16_mask(__k1, __xi, __yi);
else if constexpr (std::is_unsigned_v<_Tp> && sizeof(_Tp) == 4)
return _mm_mask_cmplt_epu32_mask(__k1, __xi, __yi);
else if constexpr (std::is_unsigned_v<_Tp> && sizeof(_Tp) == 8)
return _mm_mask_cmplt_epu64_mask(__k1, __xi, __yi);
else
__assert_unreachable<_Tp>();
}
else
__assert_unreachable<_Tp>();
}
else if constexpr (!__builtin_is_constant_evaluated() && sizeof(__x) == 8)
{
const auto __r128 = __vector_bitcast<_Tp, 16 / sizeof(_Tp)>(__x)
< __vector_bitcast<_Tp, 16 / sizeof(_Tp)>(__y);
_MaskMember<_Tp> __r64;
__builtin_memcpy(&__r64._M_data, &__r128, sizeof(__r64));
return __r64;
}
else
return _Base::_S_less(__x, __y);
}
template <typename _Tp, size_t _Np>
_GLIBCXX_SIMD_INTRINSIC static constexpr _MaskMember<_Tp>
_S_less_equal(_SimdWrapper<_Tp, _Np> __x, _SimdWrapper<_Tp, _Np> __y)
{
if constexpr (__is_avx512_abi<_Abi>())
{
if (__builtin_is_constant_evaluated()
|| (__x._M_is_constprop() && __y._M_is_constprop()))
return _MaskImpl::_S_to_bits(
__as_wrapper<_Np>(__x._M_data <= __y._M_data));
constexpr auto __k1 = _Abi::template _S_implicit_mask_intrin<_Tp>();
[[maybe_unused]] const auto __xi = __to_intrin(__x);
[[maybe_unused]] const auto __yi = __to_intrin(__y);
if constexpr (sizeof(__xi) == 64)
{
if constexpr (std::is_same_v<_Tp, float>)
return _mm512_mask_cmp_ps_mask(__k1, __xi, __yi, _CMP_LE_OS);
else if constexpr (std::is_same_v<_Tp, double>)
return _mm512_mask_cmp_pd_mask(__k1, __xi, __yi, _CMP_LE_OS);
else if constexpr (std::is_signed_v<_Tp> && sizeof(_Tp) == 1)
return _mm512_mask_cmple_epi8_mask(__k1, __xi, __yi);
else if constexpr (std::is_signed_v<_Tp> && sizeof(_Tp) == 2)
return _mm512_mask_cmple_epi16_mask(__k1, __xi, __yi);
else if constexpr (std::is_signed_v<_Tp> && sizeof(_Tp) == 4)
return _mm512_mask_cmple_epi32_mask(__k1, __xi, __yi);
else if constexpr (std::is_signed_v<_Tp> && sizeof(_Tp) == 8)
return _mm512_mask_cmple_epi64_mask(__k1, __xi, __yi);
else if constexpr (std::is_unsigned_v<_Tp> && sizeof(_Tp) == 1)
return _mm512_mask_cmple_epu8_mask(__k1, __xi, __yi);
else if constexpr (std::is_unsigned_v<_Tp> && sizeof(_Tp) == 2)
return _mm512_mask_cmple_epu16_mask(__k1, __xi, __yi);
else if constexpr (std::is_unsigned_v<_Tp> && sizeof(_Tp) == 4)
return _mm512_mask_cmple_epu32_mask(__k1, __xi, __yi);
else if constexpr (std::is_unsigned_v<_Tp> && sizeof(_Tp) == 8)
return _mm512_mask_cmple_epu64_mask(__k1, __xi, __yi);
else
__assert_unreachable<_Tp>();
}
else if constexpr (sizeof(__xi) == 32)
{
if constexpr (std::is_same_v<_Tp, float>)
return _mm256_mask_cmp_ps_mask(__k1, __xi, __yi, _CMP_LE_OS);
else if constexpr (std::is_same_v<_Tp, double>)
return _mm256_mask_cmp_pd_mask(__k1, __xi, __yi, _CMP_LE_OS);
else if constexpr (std::is_signed_v<_Tp> && sizeof(_Tp) == 1)
return _mm256_mask_cmple_epi8_mask(__k1, __xi, __yi);
else if constexpr (std::is_signed_v<_Tp> && sizeof(_Tp) == 2)
return _mm256_mask_cmple_epi16_mask(__k1, __xi, __yi);
else if constexpr (std::is_signed_v<_Tp> && sizeof(_Tp) == 4)
return _mm256_mask_cmple_epi32_mask(__k1, __xi, __yi);
else if constexpr (std::is_signed_v<_Tp> && sizeof(_Tp) == 8)
return _mm256_mask_cmple_epi64_mask(__k1, __xi, __yi);
else if constexpr (std::is_unsigned_v<_Tp> && sizeof(_Tp) == 1)
return _mm256_mask_cmple_epu8_mask(__k1, __xi, __yi);
else if constexpr (std::is_unsigned_v<_Tp> && sizeof(_Tp) == 2)
return _mm256_mask_cmple_epu16_mask(__k1, __xi, __yi);
else if constexpr (std::is_unsigned_v<_Tp> && sizeof(_Tp) == 4)
return _mm256_mask_cmple_epu32_mask(__k1, __xi, __yi);
else if constexpr (std::is_unsigned_v<_Tp> && sizeof(_Tp) == 8)
return _mm256_mask_cmple_epu64_mask(__k1, __xi, __yi);
else
__assert_unreachable<_Tp>();
}
else if constexpr (sizeof(__xi) == 16)
{
if constexpr (std::is_same_v<_Tp, float>)
return _mm_mask_cmp_ps_mask(__k1, __xi, __yi, _CMP_LE_OS);
else if constexpr (std::is_same_v<_Tp, double>)
return _mm_mask_cmp_pd_mask(__k1, __xi, __yi, _CMP_LE_OS);
else if constexpr (std::is_signed_v<_Tp> && sizeof(_Tp) == 1)
return _mm_mask_cmple_epi8_mask(__k1, __xi, __yi);
else if constexpr (std::is_signed_v<_Tp> && sizeof(_Tp) == 2)
return _mm_mask_cmple_epi16_mask(__k1, __xi, __yi);
else if constexpr (std::is_signed_v<_Tp> && sizeof(_Tp) == 4)
return _mm_mask_cmple_epi32_mask(__k1, __xi, __yi);
else if constexpr (std::is_signed_v<_Tp> && sizeof(_Tp) == 8)
return _mm_mask_cmple_epi64_mask(__k1, __xi, __yi);
else if constexpr (std::is_unsigned_v<_Tp> && sizeof(_Tp) == 1)
return _mm_mask_cmple_epu8_mask(__k1, __xi, __yi);
else if constexpr (std::is_unsigned_v<_Tp> && sizeof(_Tp) == 2)
return _mm_mask_cmple_epu16_mask(__k1, __xi, __yi);
else if constexpr (std::is_unsigned_v<_Tp> && sizeof(_Tp) == 4)
return _mm_mask_cmple_epu32_mask(__k1, __xi, __yi);
else if constexpr (std::is_unsigned_v<_Tp> && sizeof(_Tp) == 8)
return _mm_mask_cmple_epu64_mask(__k1, __xi, __yi);
else
__assert_unreachable<_Tp>();
}
else
__assert_unreachable<_Tp>();
}
else if constexpr (!__builtin_is_constant_evaluated() && sizeof(__x) == 8)
{
const auto __r128 = __vector_bitcast<_Tp, 16 / sizeof(_Tp)>(__x)
<= __vector_bitcast<_Tp, 16 / sizeof(_Tp)>(__y);
_MaskMember<_Tp> __r64;
__builtin_memcpy(&__r64._M_data, &__r128, sizeof(__r64));
return __r64;
}
else
return _Base::_S_less_equal(__x, __y);
}
template <typename _Tp, size_t _Np>
_GLIBCXX_SIMD_INTRINSIC static constexpr _MaskMember<_Tp>
_S_negate(_SimdWrapper<_Tp, _Np> __x) noexcept
{
if constexpr (__is_avx512_abi<_Abi>())
return _S_equal_to(__x, _SimdWrapper<_Tp, _Np>());
else
return _Base::_S_negate(__x);
}
using _Base::_S_abs;
template <typename _Tp, size_t _Np>
_GLIBCXX_SIMD_INTRINSIC static _SimdWrapper<_Tp, _Np>
_S_sqrt(_SimdWrapper<_Tp, _Np> __x)
{
if constexpr (__is_sse_ps<_Tp, _Np>())
return __auto_bitcast(_mm_sqrt_ps(__to_intrin(__x)));
else if constexpr (__is_sse_pd<_Tp, _Np>())
return _mm_sqrt_pd(__x);
else if constexpr (__is_avx_ps<_Tp, _Np>())
return _mm256_sqrt_ps(__x);
else if constexpr (__is_avx_pd<_Tp, _Np>())
return _mm256_sqrt_pd(__x);
else if constexpr (__is_avx512_ps<_Tp, _Np>())
return _mm512_sqrt_ps(__x);
else if constexpr (__is_avx512_pd<_Tp, _Np>())
return _mm512_sqrt_pd(__x);
else
__assert_unreachable<_Tp>();
}
template <typename _Tp, size_t _Np>
_GLIBCXX_SIMD_INTRINSIC static _SimdWrapper<_Tp, _Np>
_S_ldexp(_SimdWrapper<_Tp, _Np> __x, __fixed_size_storage_t<int, _Np> __exp)
{
if constexpr (__is_avx512_abi<_Abi>())
{
const auto __xi = __to_intrin(__x);
constexpr _SimdConverter<int, simd_abi::fixed_size<_Np>, _Tp, _Abi>
__cvt;
const auto __expi = __to_intrin(__cvt(__exp));
constexpr auto __k1 = _Abi::template _S_implicit_mask_intrin<_Tp>();
if constexpr (sizeof(__xi) == 16)
{
if constexpr (sizeof(_Tp) == 8)
return _mm_maskz_scalef_pd(__k1, __xi, __expi);
else
return _mm_maskz_scalef_ps(__k1, __xi, __expi);
}
else if constexpr (sizeof(__xi) == 32)
{
if constexpr (sizeof(_Tp) == 8)
return _mm256_maskz_scalef_pd(__k1, __xi, __expi);
else
return _mm256_maskz_scalef_ps(__k1, __xi, __expi);
}
else
{
static_assert(sizeof(__xi) == 64);
if constexpr (sizeof(_Tp) == 8)
return _mm512_maskz_scalef_pd(__k1, __xi, __expi);
else
return _mm512_maskz_scalef_ps(__k1, __xi, __expi);
}
}
else
return _Base::_S_ldexp(__x, __exp);
}
template <typename _Tp, size_t _Np>
_GLIBCXX_SIMD_INTRINSIC static _SimdWrapper<_Tp, _Np>
_S_trunc(_SimdWrapper<_Tp, _Np> __x)
{
if constexpr (__is_avx512_ps<_Tp, _Np>())
return _mm512_roundscale_ps(__x, 0x0b);
else if constexpr (__is_avx512_pd<_Tp, _Np>())
return _mm512_roundscale_pd(__x, 0x0b);
else if constexpr (__is_avx_ps<_Tp, _Np>())
return _mm256_round_ps(__x, 0x3);
else if constexpr (__is_avx_pd<_Tp, _Np>())
return _mm256_round_pd(__x, 0x3);
else if constexpr (__have_sse4_1 && __is_sse_ps<_Tp, _Np>())
return __auto_bitcast(_mm_round_ps(__to_intrin(__x), 0x3));
else if constexpr (__have_sse4_1 && __is_sse_pd<_Tp, _Np>())
return _mm_round_pd(__x, 0x3);
else if constexpr (__is_sse_ps<_Tp, _Np>())
{
auto __truncated = _mm_cvtepi32_ps(_mm_cvttps_epi32(__to_intrin(__x)));
const auto __no_fractional_values
= __vector_bitcast<int>(__vector_bitcast<_UInt>(__to_intrin(__x))
& 0x7f800000u)
< 0x4b000000;
return __no_fractional_values ? __truncated : __to_intrin(__x);
}
else
return _Base::_S_trunc(__x);
}
template <typename _Tp, size_t _Np>
_GLIBCXX_SIMD_INTRINSIC static _SimdWrapper<_Tp, _Np>
_S_round(_SimdWrapper<_Tp, _Np> __x)
{
using _V = __vector_type_t<_Tp, _Np>;
_V __truncated;
if constexpr (__is_avx512_ps<_Tp, _Np>())
__truncated = _mm512_roundscale_ps(__x._M_data, 0x0b);
else if constexpr (__is_avx512_pd<_Tp, _Np>())
__truncated = _mm512_roundscale_pd(__x._M_data, 0x0b);
else if constexpr (__is_avx_ps<_Tp, _Np>())
__truncated
= _mm256_round_ps(__x._M_data, _MM_FROUND_TO_ZERO | _MM_FROUND_NO_EXC);
else if constexpr (__is_avx_pd<_Tp, _Np>())
__truncated
= _mm256_round_pd(__x._M_data, _MM_FROUND_TO_ZERO | _MM_FROUND_NO_EXC);
else if constexpr (__have_sse4_1 && __is_sse_ps<_Tp, _Np>())
__truncated = __auto_bitcast(
_mm_round_ps(__to_intrin(__x), _MM_FROUND_TO_ZERO | _MM_FROUND_NO_EXC));
else if constexpr (__have_sse4_1 && __is_sse_pd<_Tp, _Np>())
__truncated
= _mm_round_pd(__x._M_data, _MM_FROUND_TO_ZERO | _MM_FROUND_NO_EXC);
else if constexpr (__is_sse_ps<_Tp, _Np>())
__truncated
= __auto_bitcast(_mm_cvtepi32_ps(_mm_cvttps_epi32(__to_intrin(__x))));
else
return _Base::_S_round(__x);
const _V __rounded
= __truncated
+ (__and(_S_absmask<_V>, __x._M_data - __truncated) >= _Tp(.5)
? __or(__and(_S_signmask<_V>, __x._M_data), _V() + 1)
: _V());
if constexpr (__have_sse4_1)
return __rounded;
else
return __and(_S_absmask<_V>, __x._M_data) < 0x1p23f ? __rounded
: __x._M_data;
}
template <typename _Tp, typename _TVT = _VectorTraits<_Tp>>
_GLIBCXX_SIMD_INTRINSIC static _Tp _S_nearbyint(_Tp __x) noexcept
{
if constexpr (_TVT::template _S_is<float, 16>)
return _mm512_roundscale_ps(__x, 0x0c);
else if constexpr (_TVT::template _S_is<double, 8>)
return _mm512_roundscale_pd(__x, 0x0c);
else if constexpr (_TVT::template _S_is<float, 8>)
return _mm256_round_ps(__x, _MM_FROUND_CUR_DIRECTION | _MM_FROUND_NO_EXC);
else if constexpr (_TVT::template _S_is<double, 4>)
return _mm256_round_pd(__x, _MM_FROUND_CUR_DIRECTION | _MM_FROUND_NO_EXC);
else if constexpr (__have_sse4_1 && _TVT::template _S_is<float, 4>)
return _mm_round_ps(__x, _MM_FROUND_CUR_DIRECTION | _MM_FROUND_NO_EXC);
else if constexpr (__have_sse4_1 && _TVT::template _S_is<double, 2>)
return _mm_round_pd(__x, _MM_FROUND_CUR_DIRECTION | _MM_FROUND_NO_EXC);
else
return _Base::_S_nearbyint(__x);
}
template <typename _Tp, typename _TVT = _VectorTraits<_Tp>>
_GLIBCXX_SIMD_INTRINSIC static _Tp _S_rint(_Tp __x) noexcept
{
if constexpr (_TVT::template _S_is<float, 16>)
return _mm512_roundscale_ps(__x, 0x04);
else if constexpr (_TVT::template _S_is<double, 8>)
return _mm512_roundscale_pd(__x, 0x04);
else if constexpr (_TVT::template _S_is<float, 8>)
return _mm256_round_ps(__x, _MM_FROUND_CUR_DIRECTION);
else if constexpr (_TVT::template _S_is<double, 4>)
return _mm256_round_pd(__x, _MM_FROUND_CUR_DIRECTION);
else if constexpr (__have_sse4_1 && _TVT::template _S_is<float, 4>)
return _mm_round_ps(__x, _MM_FROUND_CUR_DIRECTION);
else if constexpr (__have_sse4_1 && _TVT::template _S_is<double, 2>)
return _mm_round_pd(__x, _MM_FROUND_CUR_DIRECTION);
else
return _Base::_S_rint(__x);
}
template <typename _Tp, size_t _Np>
_GLIBCXX_SIMD_INTRINSIC static _SimdWrapper<_Tp, _Np>
_S_floor(_SimdWrapper<_Tp, _Np> __x)
{
if constexpr (__is_avx512_ps<_Tp, _Np>())
return _mm512_roundscale_ps(__x, 0x09);
else if constexpr (__is_avx512_pd<_Tp, _Np>())
return _mm512_roundscale_pd(__x, 0x09);
else if constexpr (__is_avx_ps<_Tp, _Np>())
return _mm256_round_ps(__x, 0x1);
else if constexpr (__is_avx_pd<_Tp, _Np>())
return _mm256_round_pd(__x, 0x1);
else if constexpr (__have_sse4_1 && __is_sse_ps<_Tp, _Np>())
return __auto_bitcast(_mm_floor_ps(__to_intrin(__x)));
else if constexpr (__have_sse4_1 && __is_sse_pd<_Tp, _Np>())
return _mm_floor_pd(__x);
else
return _Base::_S_floor(__x);
}
template <typename _Tp, size_t _Np>
_GLIBCXX_SIMD_INTRINSIC static _SimdWrapper<_Tp, _Np>
_S_ceil(_SimdWrapper<_Tp, _Np> __x)
{
if constexpr (__is_avx512_ps<_Tp, _Np>())
return _mm512_roundscale_ps(__x, 0x0a);
else if constexpr (__is_avx512_pd<_Tp, _Np>())
return _mm512_roundscale_pd(__x, 0x0a);
else if constexpr (__is_avx_ps<_Tp, _Np>())
return _mm256_round_ps(__x, 0x2);
else if constexpr (__is_avx_pd<_Tp, _Np>())
return _mm256_round_pd(__x, 0x2);
else if constexpr (__have_sse4_1 && __is_sse_ps<_Tp, _Np>())
return __auto_bitcast(_mm_ceil_ps(__to_intrin(__x)));
else if constexpr (__have_sse4_1 && __is_sse_pd<_Tp, _Np>())
return _mm_ceil_pd(__x);
else
return _Base::_S_ceil(__x);
}
template <typename _Tp, size_t _Np>
_GLIBCXX_SIMD_INTRINSIC static _MaskMember<_Tp>
_S_signbit(_SimdWrapper<_Tp, _Np> __x)
{
if constexpr (__is_avx512_abi<_Abi>() && __have_avx512dq)
{
if constexpr (sizeof(__x) == 64 && sizeof(_Tp) == 4)
return _mm512_movepi32_mask(__intrin_bitcast<__m512i>(__x._M_data));
else if constexpr (sizeof(__x) == 64 && sizeof(_Tp) == 8)
return _mm512_movepi64_mask(__intrin_bitcast<__m512i>(__x._M_data));
else if constexpr (sizeof(__x) == 32 && sizeof(_Tp) == 4)
return _mm256_movepi32_mask(__intrin_bitcast<__m256i>(__x._M_data));
else if constexpr (sizeof(__x) == 32 && sizeof(_Tp) == 8)
return _mm256_movepi64_mask(__intrin_bitcast<__m256i>(__x._M_data));
else if constexpr (sizeof(__x) <= 16 && sizeof(_Tp) == 4)
return _mm_movepi32_mask(__intrin_bitcast<__m128i>(__x._M_data));
else if constexpr (sizeof(__x) <= 16 && sizeof(_Tp) == 8)
return _mm_movepi64_mask(__intrin_bitcast<__m128i>(__x._M_data));
}
else if constexpr (__is_avx512_abi<_Abi>())
{
const auto __xi = __to_intrin(__x);
[[maybe_unused]] constexpr auto __k1
= _Abi::template _S_implicit_mask_intrin<_Tp>();
if constexpr (sizeof(__xi) == 16 && sizeof(_Tp) == 4)
return _mm_movemask_ps(__xi);
else if constexpr (sizeof(__xi) == 16 && sizeof(_Tp) == 8)
return _mm_movemask_pd(__xi);
else if constexpr (sizeof(__xi) == 32 && sizeof(_Tp) == 4)
return _mm256_movemask_ps(__xi);
else if constexpr (sizeof(__xi) == 32 && sizeof(_Tp) == 8)
return _mm256_movemask_pd(__xi);
else if constexpr (sizeof(__xi) == 64 && sizeof(_Tp) == 4)
return _mm512_mask_cmplt_epi32_mask(__k1,
__intrin_bitcast<__m512i>(__xi),
__m512i());
else if constexpr (sizeof(__xi) == 64 && sizeof(_Tp) == 8)
return _mm512_mask_cmplt_epi64_mask(__k1,
__intrin_bitcast<__m512i>(__xi),
__m512i());
else
__assert_unreachable<_Tp>();
}
else
return _Base::_S_signbit(__x);
}
template <typename _Tp>
_GLIBCXX_SIMD_INTRINSIC static auto _S_isnonzerovalue_mask(_Tp __x)
{
using _Traits = _VectorTraits<_Tp>;
if constexpr (__have_avx512dq_vl)
{
if constexpr (_Traits::template _S_is<
float, 2> || _Traits::template _S_is<float, 4>)
return _knot_mask8(_mm_fpclass_ps_mask(__to_intrin(__x), 0x9f));
else if constexpr (_Traits::template _S_is<float, 8>)
return _knot_mask8(_mm256_fpclass_ps_mask(__x, 0x9f));
else if constexpr (_Traits::template _S_is<float, 16>)
return _knot_mask16(_mm512_fpclass_ps_mask(__x, 0x9f));
else if constexpr (_Traits::template _S_is<double, 2>)
return _knot_mask8(_mm_fpclass_pd_mask(__x, 0x9f));
else if constexpr (_Traits::template _S_is<double, 4>)
return _knot_mask8(_mm256_fpclass_pd_mask(__x, 0x9f));
else if constexpr (_Traits::template _S_is<double, 8>)
return _knot_mask8(_mm512_fpclass_pd_mask(__x, 0x9f));
else
__assert_unreachable<_Tp>();
}
else
{
using _Up = typename _Traits::value_type;
constexpr size_t _Np = _Traits::_S_full_size;
const auto __a = __x * __infinity_v<_Up>;
const auto __b = __x * _Up();
if constexpr (__have_avx512vl && __is_sse_ps<_Up, _Np>())
return _mm_cmp_ps_mask(__to_intrin(__a), __to_intrin(__b),
_CMP_ORD_Q);
else if constexpr (__have_avx512f && __is_sse_ps<_Up, _Np>())
return __mmask8(0xf
& _mm512_cmp_ps_mask(__auto_bitcast(__a),
__auto_bitcast(__b),
_CMP_ORD_Q));
else if constexpr (__have_avx512vl && __is_sse_pd<_Up, _Np>())
return _mm_cmp_pd_mask(__a, __b, _CMP_ORD_Q);
else if constexpr (__have_avx512f && __is_sse_pd<_Up, _Np>())
return __mmask8(0x3
& _mm512_cmp_pd_mask(__auto_bitcast(__a),
__auto_bitcast(__b),
_CMP_ORD_Q));
else if constexpr (__have_avx512vl && __is_avx_ps<_Up, _Np>())
return _mm256_cmp_ps_mask(__a, __b, _CMP_ORD_Q);
else if constexpr (__have_avx512f && __is_avx_ps<_Up, _Np>())
return __mmask8(_mm512_cmp_ps_mask(__auto_bitcast(__a),
__auto_bitcast(__b), _CMP_ORD_Q));
else if constexpr (__have_avx512vl && __is_avx_pd<_Up, _Np>())
return _mm256_cmp_pd_mask(__a, __b, _CMP_ORD_Q);
else if constexpr (__have_avx512f && __is_avx_pd<_Up, _Np>())
return __mmask8(0xf
& _mm512_cmp_pd_mask(__auto_bitcast(__a),
__auto_bitcast(__b),
_CMP_ORD_Q));
else if constexpr (__is_avx512_ps<_Up, _Np>())
return _mm512_cmp_ps_mask(__a, __b, _CMP_ORD_Q);
else if constexpr (__is_avx512_pd<_Up, _Np>())
return _mm512_cmp_pd_mask(__a, __b, _CMP_ORD_Q);
else
__assert_unreachable<_Tp>();
}
}
template <typename _Tp, size_t _Np>
_GLIBCXX_SIMD_INTRINSIC static _MaskMember<_Tp>
_S_isfinite(_SimdWrapper<_Tp, _Np> __x)
{
static_assert(is_floating_point_v<_Tp>);
#if !__FINITE_MATH_ONLY__
if constexpr (__is_avx512_abi<_Abi>() && __have_avx512dq)
{
const auto __xi = __to_intrin(__x);
constexpr auto __k1 = _Abi::template _S_implicit_mask_intrin<_Tp>();
if constexpr (sizeof(__xi) == 64 && sizeof(_Tp) == 4)
return __k1 ^ _mm512_mask_fpclass_ps_mask(__k1, __xi, 0x99);
else if constexpr (sizeof(__xi) == 64 && sizeof(_Tp) == 8)
return __k1 ^ _mm512_mask_fpclass_pd_mask(__k1, __xi, 0x99);
else if constexpr (sizeof(__xi) == 32 && sizeof(_Tp) == 4)
return __k1 ^ _mm256_mask_fpclass_ps_mask(__k1, __xi, 0x99);
else if constexpr (sizeof(__xi) == 32 && sizeof(_Tp) == 8)
return __k1 ^ _mm256_mask_fpclass_pd_mask(__k1, __xi, 0x99);
else if constexpr (sizeof(__xi) == 16 && sizeof(_Tp) == 4)
return __k1 ^ _mm_mask_fpclass_ps_mask(__k1, __xi, 0x99);
else if constexpr (sizeof(__xi) == 16 && sizeof(_Tp) == 8)
return __k1 ^ _mm_mask_fpclass_pd_mask(__k1, __xi, 0x99);
}
else if constexpr (__is_avx512_abi<_Abi>())
{
using _I = __int_for_sizeof_t<_Tp>;
const auto __inf
= __vector_bitcast<_I>(__vector_broadcast<_Np>(__infinity_v<_Tp>));
return _S_less<_I, _Np>(__vector_bitcast<_I>(__x) & __inf, __inf);
}
else
#endif
return _Base::_S_isfinite(__x);
}
template <typename _Tp, size_t _Np>
_GLIBCXX_SIMD_INTRINSIC static _MaskMember<_Tp>
_S_isinf(_SimdWrapper<_Tp, _Np> __x)
{
#if !__FINITE_MATH_ONLY__
if constexpr (__is_avx512_abi<_Abi>() && __have_avx512dq)
{
const auto __xi = __to_intrin(__x);
if constexpr (sizeof(__xi) == 64 && sizeof(_Tp) == 4)
return _mm512_fpclass_ps_mask(__xi, 0x18);
else if constexpr (sizeof(__xi) == 64 && sizeof(_Tp) == 8)
return _mm512_fpclass_pd_mask(__xi, 0x18);
else if constexpr (sizeof(__xi) == 32 && sizeof(_Tp) == 4)
return _mm256_fpclass_ps_mask(__xi, 0x18);
else if constexpr (sizeof(__xi) == 32 && sizeof(_Tp) == 8)
return _mm256_fpclass_pd_mask(__xi, 0x18);
else if constexpr (sizeof(__xi) == 16 && sizeof(_Tp) == 4)
return _mm_fpclass_ps_mask(__xi, 0x18);
else if constexpr (sizeof(__xi) == 16 && sizeof(_Tp) == 8)
return _mm_fpclass_pd_mask(__xi, 0x18);
else
__assert_unreachable<_Tp>();
}
else if constexpr (__have_avx512dq_vl)
{
if constexpr (__is_sse_pd<_Tp, _Np>())
return _mm_movm_epi64(_mm_fpclass_pd_mask(__x, 0x18));
else if constexpr (__is_avx_pd<_Tp, _Np>())
return _mm256_movm_epi64(_mm256_fpclass_pd_mask(__x, 0x18));
else if constexpr (__is_sse_ps<_Tp, _Np>())
return _mm_movm_epi32(_mm_fpclass_ps_mask(__to_intrin(__x), 0x18));
else if constexpr (__is_avx_ps<_Tp, _Np>())
return _mm256_movm_epi32(_mm256_fpclass_ps_mask(__x, 0x18));
else
__assert_unreachable<_Tp>();
}
else
#endif
return _Base::_S_isinf(__x);
}
template <typename _Tp, size_t _Np>
_GLIBCXX_SIMD_INTRINSIC static _MaskMember<_Tp>
_S_isnormal(_SimdWrapper<_Tp, _Np> __x)
{
#if __FINITE_MATH_ONLY__
[[maybe_unused]] constexpr int __mode = 0x26;
#else
[[maybe_unused]] constexpr int __mode = 0xbf;
#endif
if constexpr (__is_avx512_abi<_Abi>() && __have_avx512dq)
{
const auto __xi = __to_intrin(__x);
const auto __k1 = _Abi::template _S_implicit_mask_intrin<_Tp>();
if constexpr (sizeof(__xi) == 64 && sizeof(_Tp) == 4)
return __k1 ^ _mm512_mask_fpclass_ps_mask(__k1, __xi, __mode);
else if constexpr (sizeof(__xi) == 64 && sizeof(_Tp) == 8)
return __k1 ^ _mm512_mask_fpclass_pd_mask(__k1, __xi, __mode);
else if constexpr (sizeof(__xi) == 32 && sizeof(_Tp) == 4)
return __k1 ^ _mm256_mask_fpclass_ps_mask(__k1, __xi, __mode);
else if constexpr (sizeof(__xi) == 32 && sizeof(_Tp) == 8)
return __k1 ^ _mm256_mask_fpclass_pd_mask(__k1, __xi, __mode);
else if constexpr (sizeof(__xi) == 16 && sizeof(_Tp) == 4)
return __k1 ^ _mm_mask_fpclass_ps_mask(__k1, __xi, __mode);
else if constexpr (sizeof(__xi) == 16 && sizeof(_Tp) == 8)
return __k1 ^ _mm_mask_fpclass_pd_mask(__k1, __xi, __mode);
else
__assert_unreachable<_Tp>();
}
else if constexpr (__have_avx512dq)
{
if constexpr (__have_avx512vl && __is_sse_ps<_Tp, _Np>())
return _mm_movm_epi32(
_knot_mask8(_mm_fpclass_ps_mask(__to_intrin(__x), __mode)));
else if constexpr (__have_avx512vl && __is_avx_ps<_Tp, _Np>())
return _mm256_movm_epi32(
_knot_mask8(_mm256_fpclass_ps_mask(__x, __mode)));
else if constexpr (__is_avx512_ps<_Tp, _Np>())
return _knot_mask16(_mm512_fpclass_ps_mask(__x, __mode));
else if constexpr (__have_avx512vl && __is_sse_pd<_Tp, _Np>())
return _mm_movm_epi64(_knot_mask8(_mm_fpclass_pd_mask(__x, __mode)));
else if constexpr (__have_avx512vl && __is_avx_pd<_Tp, _Np>())
return _mm256_movm_epi64(
_knot_mask8(_mm256_fpclass_pd_mask(__x, __mode)));
else if constexpr (__is_avx512_pd<_Tp, _Np>())
return _knot_mask8(_mm512_fpclass_pd_mask(__x, __mode));
else
__assert_unreachable<_Tp>();
}
else if constexpr (__is_avx512_abi<_Abi>())
{
using _I = __int_for_sizeof_t<_Tp>;
const auto absn = __vector_bitcast<_I>(_S_abs(__x));
const auto minn
= __vector_bitcast<_I>(__vector_broadcast<_Np>(__norm_min_v<_Tp>));
#if __FINITE_MATH_ONLY__
return _S_less_equal<_I, _Np>(minn, absn);
#else
const auto infn
= __vector_bitcast<_I>(__vector_broadcast<_Np>(__infinity_v<_Tp>));
return __and(_S_less_equal<_I, _Np>(minn, absn),
_S_less<_I, _Np>(absn, infn));
#endif
}
else
return _Base::_S_isnormal(__x);
}
template <typename _Tp, size_t _Np>
_GLIBCXX_SIMD_INTRINSIC static _MaskMember<_Tp>
_S_isnan(_SimdWrapper<_Tp, _Np> __x)
{
return _S_isunordered(__x, __x);
}
template <typename _Tp, size_t _Np>
_GLIBCXX_SIMD_INTRINSIC static _MaskMember<_Tp>
_S_isunordered([[maybe_unused]] _SimdWrapper<_Tp, _Np> __x,
[[maybe_unused]] _SimdWrapper<_Tp, _Np> __y)
{
#if __FINITE_MATH_ONLY__
return {};
#else
const auto __xi = __to_intrin(__x);
const auto __yi = __to_intrin(__y);
if constexpr (__is_avx512_abi<_Abi>())
{
constexpr auto __k1 = _Abi::template _S_implicit_mask_intrin<_Tp>();
if constexpr (sizeof(__xi) == 64 && sizeof(_Tp) == 4)
return _mm512_mask_cmp_ps_mask(__k1, __xi, __yi, _CMP_UNORD_Q);
else if constexpr (sizeof(__xi) == 64 && sizeof(_Tp) == 8)
return _mm512_mask_cmp_pd_mask(__k1, __xi, __yi, _CMP_UNORD_Q);
else if constexpr (sizeof(__xi) == 32 && sizeof(_Tp) == 4)
return _mm256_mask_cmp_ps_mask(__k1, __xi, __yi, _CMP_UNORD_Q);
else if constexpr (sizeof(__xi) == 32 && sizeof(_Tp) == 8)
return _mm256_mask_cmp_pd_mask(__k1, __xi, __yi, _CMP_UNORD_Q);
else if constexpr (sizeof(__xi) == 16 && sizeof(_Tp) == 4)
return _mm_mask_cmp_ps_mask(__k1, __xi, __yi, _CMP_UNORD_Q);
else if constexpr (sizeof(__xi) == 16 && sizeof(_Tp) == 8)
return _mm_mask_cmp_pd_mask(__k1, __xi, __yi, _CMP_UNORD_Q);
}
else if constexpr (sizeof(__xi) == 32 && sizeof(_Tp) == 4)
return __to_masktype(_mm256_cmp_ps(__xi, __yi, _CMP_UNORD_Q));
else if constexpr (sizeof(__xi) == 32 && sizeof(_Tp) == 8)
return __to_masktype(_mm256_cmp_pd(__xi, __yi, _CMP_UNORD_Q));
else if constexpr (sizeof(__xi) == 16 && sizeof(_Tp) == 4)
return __auto_bitcast(_mm_cmpunord_ps(__xi, __yi));
else if constexpr (sizeof(__xi) == 16 && sizeof(_Tp) == 8)
return __to_masktype(_mm_cmpunord_pd(__xi, __yi));
else
__assert_unreachable<_Tp>();
#endif
}
template <typename _Tp, size_t _Np>
static constexpr _MaskMember<_Tp> _S_isgreater(_SimdWrapper<_Tp, _Np> __x,
_SimdWrapper<_Tp, _Np> __y)
{
const auto __xi = __to_intrin(__x);
const auto __yi = __to_intrin(__y);
if constexpr (__is_avx512_abi<_Abi>())
{
const auto __k1 = _Abi::template _S_implicit_mask_intrin<_Tp>();
if constexpr (sizeof(__xi) == 64 && sizeof(_Tp) == 4)
return _mm512_mask_cmp_ps_mask(__k1, __xi, __yi, _CMP_GT_OQ);
else if constexpr (sizeof(__xi) == 64 && sizeof(_Tp) == 8)
return _mm512_mask_cmp_pd_mask(__k1, __xi, __yi, _CMP_GT_OQ);
else if constexpr (sizeof(__xi) == 32 && sizeof(_Tp) == 4)
return _mm256_mask_cmp_ps_mask(__k1, __xi, __yi, _CMP_GT_OQ);
else if constexpr (sizeof(__xi) == 32 && sizeof(_Tp) == 8)
return _mm256_mask_cmp_pd_mask(__k1, __xi, __yi, _CMP_GT_OQ);
else if constexpr (sizeof(__xi) == 16 && sizeof(_Tp) == 4)
return _mm_mask_cmp_ps_mask(__k1, __xi, __yi, _CMP_GT_OQ);
else if constexpr (sizeof(__xi) == 16 && sizeof(_Tp) == 8)
return _mm_mask_cmp_pd_mask(__k1, __xi, __yi, _CMP_GT_OQ);
else
__assert_unreachable<_Tp>();
}
else if constexpr (__have_avx)
{
if constexpr (sizeof(__xi) == 32 && sizeof(_Tp) == 4)
return __to_masktype(_mm256_cmp_ps(__xi, __yi, _CMP_GT_OQ));
else if constexpr (sizeof(__xi) == 32 && sizeof(_Tp) == 8)
return __to_masktype(_mm256_cmp_pd(__xi, __yi, _CMP_GT_OQ));
else if constexpr (sizeof(__xi) == 16 && sizeof(_Tp) == 4)
return __auto_bitcast(_mm_cmp_ps(__xi, __yi, _CMP_GT_OQ));
else if constexpr (sizeof(__xi) == 16 && sizeof(_Tp) == 8)
return __to_masktype(_mm_cmp_pd(__xi, __yi, _CMP_GT_OQ));
else
__assert_unreachable<_Tp>();
}
else if constexpr (__have_sse2 && sizeof(__xi) == 16 && sizeof(_Tp) == 4)
{
const auto __xn = __vector_bitcast<int>(__xi);
const auto __yn = __vector_bitcast<int>(__yi);
const auto __xp = __xn < 0 ? -(__xn & 0x7fff'ffff) : __xn;
const auto __yp = __yn < 0 ? -(__yn & 0x7fff'ffff) : __yn;
return __auto_bitcast(
__and(__to_masktype(_mm_cmpord_ps(__xi, __yi)), __xp > __yp));
}
else if constexpr (__have_sse2 && sizeof(__xi) == 16 && sizeof(_Tp) == 8)
return __vector_type_t<__int_with_sizeof_t<8>, 2>{
-_mm_ucomigt_sd(__xi, __yi),
-_mm_ucomigt_sd(_mm_unpackhi_pd(__xi, __xi),
_mm_unpackhi_pd(__yi, __yi))};
else
return _Base::_S_isgreater(__x, __y);
}
template <typename _Tp, size_t _Np>
static constexpr _MaskMember<_Tp>
_S_isgreaterequal(_SimdWrapper<_Tp, _Np> __x, _SimdWrapper<_Tp, _Np> __y)
{
const auto __xi = __to_intrin(__x);
const auto __yi = __to_intrin(__y);
if constexpr (__is_avx512_abi<_Abi>())
{
const auto __k1 = _Abi::template _S_implicit_mask_intrin<_Tp>();
if constexpr (sizeof(__xi) == 64 && sizeof(_Tp) == 4)
return _mm512_mask_cmp_ps_mask(__k1, __xi, __yi, _CMP_GE_OQ);
else if constexpr (sizeof(__xi) == 64 && sizeof(_Tp) == 8)
return _mm512_mask_cmp_pd_mask(__k1, __xi, __yi, _CMP_GE_OQ);
else if constexpr (sizeof(__xi) == 32 && sizeof(_Tp) == 4)
return _mm256_mask_cmp_ps_mask(__k1, __xi, __yi, _CMP_GE_OQ);
else if constexpr (sizeof(__xi) == 32 && sizeof(_Tp) == 8)
return _mm256_mask_cmp_pd_mask(__k1, __xi, __yi, _CMP_GE_OQ);
else if constexpr (sizeof(__xi) == 16 && sizeof(_Tp) == 4)
return _mm_mask_cmp_ps_mask(__k1, __xi, __yi, _CMP_GE_OQ);
else if constexpr (sizeof(__xi) == 16 && sizeof(_Tp) == 8)
return _mm_mask_cmp_pd_mask(__k1, __xi, __yi, _CMP_GE_OQ);
else
__assert_unreachable<_Tp>();
}
else if constexpr (__have_avx)
{
if constexpr (sizeof(__xi) == 32 && sizeof(_Tp) == 4)
return __to_masktype(_mm256_cmp_ps(__xi, __yi, _CMP_GE_OQ));
else if constexpr (sizeof(__xi) == 32 && sizeof(_Tp) == 8)
return __to_masktype(_mm256_cmp_pd(__xi, __yi, _CMP_GE_OQ));
else if constexpr (sizeof(__xi) == 16 && sizeof(_Tp) == 4)
return __auto_bitcast(_mm_cmp_ps(__xi, __yi, _CMP_GE_OQ));
else if constexpr (sizeof(__xi) == 16 && sizeof(_Tp) == 8)
return __to_masktype(_mm_cmp_pd(__xi, __yi, _CMP_GE_OQ));
else
__assert_unreachable<_Tp>();
}
else if constexpr (__have_sse2 && sizeof(__xi) == 16 && sizeof(_Tp) == 4)
{
const auto __xn = __vector_bitcast<int>(__xi);
const auto __yn = __vector_bitcast<int>(__yi);
const auto __xp = __xn < 0 ? -(__xn & 0x7fff'ffff) : __xn;
const auto __yp = __yn < 0 ? -(__yn & 0x7fff'ffff) : __yn;
return __auto_bitcast(
__and(__to_masktype(_mm_cmpord_ps(__xi, __yi)), __xp >= __yp));
}
else if constexpr (__have_sse2 && sizeof(__xi) == 16 && sizeof(_Tp) == 8)
return __vector_type_t<__int_with_sizeof_t<8>, 2>{
-_mm_ucomige_sd(__xi, __yi),
-_mm_ucomige_sd(_mm_unpackhi_pd(__xi, __xi),
_mm_unpackhi_pd(__yi, __yi))};
else
return _Base::_S_isgreaterequal(__x, __y);
}
template <typename _Tp, size_t _Np>
static constexpr _MaskMember<_Tp> _S_isless(_SimdWrapper<_Tp, _Np> __x,
_SimdWrapper<_Tp, _Np> __y)
{
const auto __xi = __to_intrin(__x);
const auto __yi = __to_intrin(__y);
if constexpr (__is_avx512_abi<_Abi>())
{
const auto __k1 = _Abi::template _S_implicit_mask_intrin<_Tp>();
if constexpr (sizeof(__xi) == 64 && sizeof(_Tp) == 4)
return _mm512_mask_cmp_ps_mask(__k1, __xi, __yi, _CMP_LT_OQ);
else if constexpr (sizeof(__xi) == 64 && sizeof(_Tp) == 8)
return _mm512_mask_cmp_pd_mask(__k1, __xi, __yi, _CMP_LT_OQ);
else if constexpr (sizeof(__xi) == 32 && sizeof(_Tp) == 4)
return _mm256_mask_cmp_ps_mask(__k1, __xi, __yi, _CMP_LT_OQ);
else if constexpr (sizeof(__xi) == 32 && sizeof(_Tp) == 8)
return _mm256_mask_cmp_pd_mask(__k1, __xi, __yi, _CMP_LT_OQ);
else if constexpr (sizeof(__xi) == 16 && sizeof(_Tp) == 4)
return _mm_mask_cmp_ps_mask(__k1, __xi, __yi, _CMP_LT_OQ);
else if constexpr (sizeof(__xi) == 16 && sizeof(_Tp) == 8)
return _mm_mask_cmp_pd_mask(__k1, __xi, __yi, _CMP_LT_OQ);
else
__assert_unreachable<_Tp>();
}
else if constexpr (__have_avx)
{
if constexpr (sizeof(__xi) == 32 && sizeof(_Tp) == 4)
return __to_masktype(_mm256_cmp_ps(__xi, __yi, _CMP_LT_OQ));
else if constexpr (sizeof(__xi) == 32 && sizeof(_Tp) == 8)
return __to_masktype(_mm256_cmp_pd(__xi, __yi, _CMP_LT_OQ));
else if constexpr (sizeof(__xi) == 16 && sizeof(_Tp) == 4)
return __auto_bitcast(_mm_cmp_ps(__xi, __yi, _CMP_LT_OQ));
else if constexpr (sizeof(__xi) == 16 && sizeof(_Tp) == 8)
return __to_masktype(_mm_cmp_pd(__xi, __yi, _CMP_LT_OQ));
else
__assert_unreachable<_Tp>();
}
else if constexpr (__have_sse2 && sizeof(__xi) == 16 && sizeof(_Tp) == 4)
{
const auto __xn = __vector_bitcast<int>(__xi);
const auto __yn = __vector_bitcast<int>(__yi);
const auto __xp = __xn < 0 ? -(__xn & 0x7fff'ffff) : __xn;
const auto __yp = __yn < 0 ? -(__yn & 0x7fff'ffff) : __yn;
return __auto_bitcast(
__and(__to_masktype(_mm_cmpord_ps(__xi, __yi)), __xp < __yp));
}
else if constexpr (__have_sse2 && sizeof(__xi) == 16 && sizeof(_Tp) == 8)
return __vector_type_t<__int_with_sizeof_t<8>, 2>{
-_mm_ucomigt_sd(__yi, __xi),
-_mm_ucomigt_sd(_mm_unpackhi_pd(__yi, __yi),
_mm_unpackhi_pd(__xi, __xi))};
else
return _Base::_S_isless(__x, __y);
}
template <typename _Tp, size_t _Np>
static constexpr _MaskMember<_Tp> _S_islessequal(_SimdWrapper<_Tp, _Np> __x,
_SimdWrapper<_Tp, _Np> __y)
{
const auto __xi = __to_intrin(__x);
const auto __yi = __to_intrin(__y);
if constexpr (__is_avx512_abi<_Abi>())
{
const auto __k1 = _Abi::template _S_implicit_mask_intrin<_Tp>();
if constexpr (sizeof(__xi) == 64 && sizeof(_Tp) == 4)
return _mm512_mask_cmp_ps_mask(__k1, __xi, __yi, _CMP_LE_OQ);
else if constexpr (sizeof(__xi) == 64 && sizeof(_Tp) == 8)
return _mm512_mask_cmp_pd_mask(__k1, __xi, __yi, _CMP_LE_OQ);
else if constexpr (sizeof(__xi) == 32 && sizeof(_Tp) == 4)
return _mm256_mask_cmp_ps_mask(__k1, __xi, __yi, _CMP_LE_OQ);
else if constexpr (sizeof(__xi) == 32 && sizeof(_Tp) == 8)
return _mm256_mask_cmp_pd_mask(__k1, __xi, __yi, _CMP_LE_OQ);
else if constexpr (sizeof(__xi) == 16 && sizeof(_Tp) == 4)
return _mm_mask_cmp_ps_mask(__k1, __xi, __yi, _CMP_LE_OQ);
else if constexpr (sizeof(__xi) == 16 && sizeof(_Tp) == 8)
return _mm_mask_cmp_pd_mask(__k1, __xi, __yi, _CMP_LE_OQ);
else
__assert_unreachable<_Tp>();
}
else if constexpr (__have_avx)
{
if constexpr (sizeof(__xi) == 32 && sizeof(_Tp) == 4)
return __to_masktype(_mm256_cmp_ps(__xi, __yi, _CMP_LE_OQ));
else if constexpr (sizeof(__xi) == 32 && sizeof(_Tp) == 8)
return __to_masktype(_mm256_cmp_pd(__xi, __yi, _CMP_LE_OQ));
else if constexpr (sizeof(__xi) == 16 && sizeof(_Tp) == 4)
return __auto_bitcast(_mm_cmp_ps(__xi, __yi, _CMP_LE_OQ));
else if constexpr (sizeof(__xi) == 16 && sizeof(_Tp) == 8)
return __to_masktype(_mm_cmp_pd(__xi, __yi, _CMP_LE_OQ));
else
__assert_unreachable<_Tp>();
}
else if constexpr (__have_sse2 && sizeof(__xi) == 16 && sizeof(_Tp) == 4)
{
const auto __xn = __vector_bitcast<int>(__xi);
const auto __yn = __vector_bitcast<int>(__yi);
const auto __xp = __xn < 0 ? -(__xn & 0x7fff'ffff) : __xn;
const auto __yp = __yn < 0 ? -(__yn & 0x7fff'ffff) : __yn;
return __auto_bitcast(
__and(__to_masktype(_mm_cmpord_ps(__xi, __yi)), __xp <= __yp));
}
else if constexpr (__have_sse2 && sizeof(__xi) == 16 && sizeof(_Tp) == 8)
return __vector_type_t<__int_with_sizeof_t<8>, 2>{
-_mm_ucomige_sd(__yi, __xi),
-_mm_ucomige_sd(_mm_unpackhi_pd(__yi, __yi),
_mm_unpackhi_pd(__xi, __xi))};
else
return _Base::_S_islessequal(__x, __y);
}
template <typename _Tp, size_t _Np>
static constexpr _MaskMember<_Tp> _S_islessgreater(_SimdWrapper<_Tp, _Np> __x,
_SimdWrapper<_Tp, _Np> __y)
{
const auto __xi = __to_intrin(__x);
const auto __yi = __to_intrin(__y);
if constexpr (__is_avx512_abi<_Abi>())
{
const auto __k1 = _Abi::template _S_implicit_mask_intrin<_Tp>();
if constexpr (sizeof(__xi) == 64 && sizeof(_Tp) == 4)
return _mm512_mask_cmp_ps_mask(__k1, __xi, __yi, _CMP_NEQ_OQ);
else if constexpr (sizeof(__xi) == 64 && sizeof(_Tp) == 8)
return _mm512_mask_cmp_pd_mask(__k1, __xi, __yi, _CMP_NEQ_OQ);
else if constexpr (sizeof(__xi) == 32 && sizeof(_Tp) == 4)
return _mm256_mask_cmp_ps_mask(__k1, __xi, __yi, _CMP_NEQ_OQ);
else if constexpr (sizeof(__xi) == 32 && sizeof(_Tp) == 8)
return _mm256_mask_cmp_pd_mask(__k1, __xi, __yi, _CMP_NEQ_OQ);
else if constexpr (sizeof(__xi) == 16 && sizeof(_Tp) == 4)
return _mm_mask_cmp_ps_mask(__k1, __xi, __yi, _CMP_NEQ_OQ);
else if constexpr (sizeof(__xi) == 16 && sizeof(_Tp) == 8)
return _mm_mask_cmp_pd_mask(__k1, __xi, __yi, _CMP_NEQ_OQ);
else
__assert_unreachable<_Tp>();
}
else if constexpr (__have_avx)
{
if constexpr (sizeof(__xi) == 32 && sizeof(_Tp) == 4)
return __to_masktype(_mm256_cmp_ps(__xi, __yi, _CMP_NEQ_OQ));
else if constexpr (sizeof(__xi) == 32 && sizeof(_Tp) == 8)
return __to_masktype(_mm256_cmp_pd(__xi, __yi, _CMP_NEQ_OQ));
else if constexpr (sizeof(__xi) == 16 && sizeof(_Tp) == 4)
return __auto_bitcast(_mm_cmp_ps(__xi, __yi, _CMP_NEQ_OQ));
else if constexpr (sizeof(__xi) == 16 && sizeof(_Tp) == 8)
return __to_masktype(_mm_cmp_pd(__xi, __yi, _CMP_NEQ_OQ));
else
__assert_unreachable<_Tp>();
}
else if constexpr (sizeof(__xi) == 16 && sizeof(_Tp) == 4)
return __auto_bitcast(
__and(_mm_cmpord_ps(__xi, __yi), _mm_cmpneq_ps(__xi, __yi)));
else if constexpr (sizeof(__xi) == 16 && sizeof(_Tp) == 8)
return __to_masktype(
__and(_mm_cmpord_pd(__xi, __yi), _mm_cmpneq_pd(__xi, __yi)));
else
__assert_unreachable<_Tp>();
}
};
struct _MaskImplX86Mixin
{
template <typename _Tp> using _TypeTag = _Tp*;
using _Base = _MaskImplBuiltinMixin;
template <typename _Up, size_t _ToN = 1, typename _Tp>
_GLIBCXX_SIMD_INTRINSIC static constexpr enable_if_t<is_same_v<_Tp, bool>,
_SimdWrapper<_Up, _ToN>>
_S_to_maskvector(_Tp __x)
{
static_assert(std::is_same_v<_Up, __int_for_sizeof_t<_Up>>);
return __x ? __vector_type_t<_Up, _ToN>{~_Up()}
: __vector_type_t<_Up, _ToN>();
}
template <typename _Up, size_t _UpN = 0, size_t _Np,
size_t _ToN = _UpN == 0 ? _Np : _UpN>
_GLIBCXX_SIMD_INTRINSIC static constexpr _SimdWrapper<_Up, _ToN>
_S_to_maskvector(_SanitizedBitMask<_Np> __x)
{
static_assert(std::is_same_v<_Up, __int_for_sizeof_t<_Up>>);
using _UV = __vector_type_t<_Up, _ToN>;
using _UI = __intrinsic_type_t<_Up, _ToN>;
[[maybe_unused]] const auto __k = __x._M_to_bits();
if constexpr (_Np == 1)
return _S_to_maskvector<_Up, _ToN>(__k);
else if (__x._M_is_constprop() || __builtin_is_constant_evaluated())
return __generate_from_n_evaluations<std::min(_ToN, _Np), _UV>(
[&](auto __i) -> _Up { return -__x[__i.value]; });
else if constexpr (sizeof(_Up) == 1)
{
if constexpr (sizeof(_UI) == 16)
{
if constexpr (__have_avx512bw_vl)
return __intrin_bitcast<_UV>(_mm_movm_epi8(__k));
else if constexpr (__have_avx512bw)
return __intrin_bitcast<_UV>(__lo128(_mm512_movm_epi8(__k)));
else if constexpr (__have_avx512f)
{
auto __as32bits = _mm512_maskz_mov_epi32(__k, ~__m512i());
auto __as16bits = __xzyw(
_mm256_packs_epi32(__lo256(__as32bits), __hi256(__as32bits)));
return __intrin_bitcast<_UV>(
_mm_packs_epi16(__lo128(__as16bits), __hi128(__as16bits)));
}
else if constexpr (__have_ssse3)
{
const auto __bitmask = __to_intrin(
__make_vector<_UChar>(1, 2, 4, 8, 16, 32, 64, 128, 1, 2, 4, 8,
16, 32, 64, 128));
return __intrin_bitcast<_UV>(
__vector_bitcast<_Up>(
_mm_shuffle_epi8(__to_intrin(
__vector_type_t<_ULLong, 2>{__k}),
_mm_setr_epi8(0, 0, 0, 0, 0, 0, 0, 0, 1, 1,
1, 1, 1, 1, 1, 1))
& __bitmask)
!= 0);
}
}
else if constexpr (sizeof(_UI) == 32)
{
if constexpr (__have_avx512bw_vl)
return __vector_bitcast<_Up>(_mm256_movm_epi8(__k));
else if constexpr (__have_avx512bw)
return __vector_bitcast<_Up>(__lo256(_mm512_movm_epi8(__k)));
else if constexpr (__have_avx512f)
{
auto __as16bits =
_mm512_srli_epi32(_mm512_maskz_mov_epi32(__k, ~__m512i()), 16)
| _mm512_slli_epi32(_mm512_maskz_mov_epi32(__k >> 16,
~__m512i()),
16);
auto __0_16_1_17 = __xzyw(_mm256_packs_epi16(
__lo256(__as16bits),
__hi256(__as16bits))
);
return __vector_bitcast<_Up>(__xzyw(_mm256_shuffle_epi8(
__0_16_1_17,
_mm256_setr_epi8(0, 2, 4, 6, 8, 10, 12, 14, 1, 3, 5, 7, 9, 11,
13, 15, 0, 2, 4, 6, 8, 10, 12, 14, 1, 3, 5,
7, 9, 11, 13,
15))));
}
else if constexpr (__have_avx2)
{
const auto __bitmask = _mm256_broadcastsi128_si256(__to_intrin(
__make_vector<_UChar>(1, 2, 4, 8, 16, 32, 64, 128, 1, 2, 4, 8,
16, 32, 64, 128)));
return __vector_bitcast<_Up>(
__vector_bitcast<_Up>(
_mm256_shuffle_epi8(
_mm256_broadcastsi128_si256(
__to_intrin(__vector_type_t<_ULLong, 2>{__k})),
_mm256_setr_epi8(0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1,
1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3,
3, 3, 3, 3))
& __bitmask)
!= 0);
}
}
else if constexpr (sizeof(_UI) == 64)
return reinterpret_cast<_UV>(_mm512_movm_epi8(__k));
if constexpr (std::min(_ToN, _Np) <= 4)
{
if constexpr (_Np > 7)
__x &= _SanitizedBitMask<_Np>(0x0f);
const _UInt __char_mask
= ((_UInt(__x.to_ulong()) * 0x00204081U) & 0x01010101ULL) * 0xff;
_UV __r = {};
__builtin_memcpy(&__r, &__char_mask,
std::min(sizeof(__r), sizeof(__char_mask)));
return __r;
}
else if constexpr (std::min(_ToN, _Np) <= 7)
{
if constexpr (_Np > 7)
__x &= _SanitizedBitMask<_Np>(0x7f);
const _ULLong __char_mask
= ((__x.to_ulong() * 0x40810204081ULL) & 0x0101010101010101ULL)
* 0xff;
_UV __r = {};
__builtin_memcpy(&__r, &__char_mask,
std::min(sizeof(__r), sizeof(__char_mask)));
return __r;
}
}
else if constexpr (sizeof(_Up) == 2)
{
if constexpr (sizeof(_UI) == 16)
{
if constexpr (__have_avx512bw_vl)
return __intrin_bitcast<_UV>(_mm_movm_epi16(__k));
else if constexpr (__have_avx512bw)
return __intrin_bitcast<_UV>(__lo128(_mm512_movm_epi16(__k)));
else if constexpr (__have_avx512f)
{
__m256i __as32bits = {};
if constexpr (__have_avx512vl)
__as32bits = _mm256_maskz_mov_epi32(__k, ~__m256i());
else
__as32bits = __lo256(_mm512_maskz_mov_epi32(__k, ~__m512i()));
return __intrin_bitcast<_UV>(
_mm_packs_epi32(__lo128(__as32bits), __hi128(__as32bits)));
}
}
else if constexpr (sizeof(_UI) == 32)
{
if constexpr (__have_avx512bw_vl)
return __vector_bitcast<_Up>(_mm256_movm_epi16(__k));
else if constexpr (__have_avx512bw)
return __vector_bitcast<_Up>(__lo256(_mm512_movm_epi16(__k)));
else if constexpr (__have_avx512f)
{
auto __as32bits = _mm512_maskz_mov_epi32(__k, ~__m512i());
return __vector_bitcast<_Up>(
__xzyw(_mm256_packs_epi32(__lo256(__as32bits),
__hi256(__as32bits))));
}
}
else if constexpr (sizeof(_UI) == 64)
return __vector_bitcast<_Up>(_mm512_movm_epi16(__k));
}
else if constexpr (sizeof(_Up) == 4)
{
if constexpr (sizeof(_UI) == 16)
{
if constexpr (__have_avx512dq_vl)
return __intrin_bitcast<_UV>(_mm_movm_epi32(__k));
else if constexpr (__have_avx512dq)
return __intrin_bitcast<_UV>(__lo128(_mm512_movm_epi32(__k)));
else if constexpr (__have_avx512vl)
return __intrin_bitcast<_UV>(
_mm_maskz_mov_epi32(__k, ~__m128i()));
else if constexpr (__have_avx512f)
return __intrin_bitcast<_UV>(
__lo128(_mm512_maskz_mov_epi32(__k, ~__m512i())));
}
else if constexpr (sizeof(_UI) == 32)
{
if constexpr (__have_avx512dq_vl)
return __vector_bitcast<_Up>(_mm256_movm_epi32(__k));
else if constexpr (__have_avx512dq)
return __vector_bitcast<_Up>(__lo256(_mm512_movm_epi32(__k)));
else if constexpr (__have_avx512vl)
return __vector_bitcast<_Up>(
_mm256_maskz_mov_epi32(__k, ~__m256i()));
else if constexpr (__have_avx512f)
return __vector_bitcast<_Up>(
__lo256(_mm512_maskz_mov_epi32(__k, ~__m512i())));
}
else if constexpr (sizeof(_UI) == 64)
return __vector_bitcast<_Up>(
__have_avx512dq ? _mm512_movm_epi32(__k)
: _mm512_maskz_mov_epi32(__k, ~__m512i()));
}
else if constexpr (sizeof(_Up) == 8)
{
if constexpr (sizeof(_UI) == 16)
{
if constexpr (__have_avx512dq_vl)
return __vector_bitcast<_Up>(_mm_movm_epi64(__k));
else if constexpr (__have_avx512dq)
return __vector_bitcast<_Up>(__lo128(_mm512_movm_epi64(__k)));
else if constexpr (__have_avx512vl)
return __vector_bitcast<_Up>(
_mm_maskz_mov_epi64(__k, ~__m128i()));
else if constexpr (__have_avx512f)
return __vector_bitcast<_Up>(
__lo128(_mm512_maskz_mov_epi64(__k, ~__m512i())));
}
else if constexpr (sizeof(_UI) == 32)
{
if constexpr (__have_avx512dq_vl)
return __vector_bitcast<_Up>(_mm256_movm_epi64(__k));
else if constexpr (__have_avx512dq)
return __vector_bitcast<_Up>(__lo256(_mm512_movm_epi64(__k)));
else if constexpr (__have_avx512vl)
return __vector_bitcast<_Up>(
_mm256_maskz_mov_epi64(__k, ~__m256i()));
else if constexpr (__have_avx512f)
return __vector_bitcast<_Up>(
__lo256(_mm512_maskz_mov_epi64(__k, ~__m512i())));
}
else if constexpr (sizeof(_UI) == 64)
return __vector_bitcast<_Up>(
__have_avx512dq ? _mm512_movm_epi64(__k)
: _mm512_maskz_mov_epi64(__k, ~__m512i()));
}
using _UpUInt = std::make_unsigned_t<_Up>;
using _V = __vector_type_t<_UpUInt, _ToN>;
constexpr size_t __bits_per_element = sizeof(_Up) * __CHAR_BIT__;
if constexpr (_ToN == 2)
{
return __vector_bitcast<_Up>(_V{_UpUInt(-__x[0]), _UpUInt(-__x[1])});
}
else if constexpr (!__have_avx2 && __have_avx && sizeof(_V) == 32)
{
if constexpr (sizeof(_Up) == 4)
return __vector_bitcast<_Up>(_mm256_cmp_ps(
_mm256_and_ps(_mm256_castsi256_ps(_mm256_set1_epi32(__k)),
_mm256_castsi256_ps(_mm256_setr_epi32(
0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80))),
_mm256_setzero_ps(), _CMP_NEQ_UQ));
else if constexpr (sizeof(_Up) == 8)
return __vector_bitcast<_Up>(_mm256_cmp_pd(
_mm256_and_pd(_mm256_castsi256_pd(_mm256_set1_epi64x(__k)),
_mm256_castsi256_pd(
_mm256_setr_epi64x(0x01, 0x02, 0x04, 0x08))),
_mm256_setzero_pd(), _CMP_NEQ_UQ));
else
__assert_unreachable<_Up>();
}
else if constexpr (__bits_per_element >= _ToN)
{
constexpr auto __bitmask
= __generate_vector<_V>(
[](auto __i) constexpr->_UpUInt {
return __i < _ToN ? 1ull << __i : 0;
});
const auto __bits = __vector_broadcast<_ToN, _UpUInt>(__k) & __bitmask;
if constexpr (__bits_per_element > _ToN)
return __vector_bitcast<_Up>(__bits) > 0;
else
return __vector_bitcast<_Up>(__bits != 0);
}
else
{
const _V __tmp
= __generate_vector<_V>([&](auto __i) constexpr {
return static_cast<_UpUInt>(
__k >> (__bits_per_element * (__i / __bits_per_element)));
})
& __generate_vector<_V>([](auto __i) constexpr {
return static_cast<_UpUInt>(1ull << (__i % __bits_per_element));
});
return __intrin_bitcast<_UV>(__tmp != _V());
}
}
template <typename _Up, size_t _UpN = 0, typename _Tp, size_t _Np,
size_t _ToN = _UpN == 0 ? _Np : _UpN>
_GLIBCXX_SIMD_INTRINSIC static constexpr _SimdWrapper<_Up, _ToN>
_S_to_maskvector(_SimdWrapper<_Tp, _Np> __x)
{
static_assert(std::is_same_v<_Up, __int_for_sizeof_t<_Up>>);
using _TW = _SimdWrapper<_Tp, _Np>;
using _UW = _SimdWrapper<_Up, _ToN>;
using _UI = __intrinsic_type_t<_Up, _ToN>;
if constexpr (is_same_v<_Tp, bool>)
return _S_to_maskvector<_Up, _ToN>(
_BitMask<_Np>(__x._M_data)._M_sanitized());
else if constexpr (sizeof(_Up) == sizeof(_Tp) && sizeof(_TW) == sizeof(_UW))
return __wrapper_bitcast<_Up, _ToN>(
_ToN <= _Np ? __x
: simd_abi::_VecBuiltin<sizeof(_Tp) * _Np>::_S_masked(__x));
else
{
if (__x._M_is_constprop() || __builtin_is_constant_evaluated())
{
const auto __y = __vector_bitcast<__int_for_sizeof_t<_Tp>>(__x);
return __generate_from_n_evaluations<std::min(_ToN, _Np),
__vector_type_t<_Up, _ToN>>(
[&](auto __i) -> _Up { return __y[__i.value]; });
}
using _To = __vector_type_t<_Up, _ToN>;
[[maybe_unused]] constexpr size_t _FromN = _Np;
constexpr int _FromBytes = sizeof(_Tp);
constexpr int _ToBytes = sizeof(_Up);
const auto __k = __x._M_data;
if constexpr (_FromBytes == _ToBytes)
return __intrin_bitcast<_To>(__k);
else if constexpr (sizeof(_UI) == 16 && sizeof(__k) == 16)
{
if constexpr (_FromBytes == 4 && _ToBytes == 8)
return __intrin_bitcast<_To>(__interleave128_lo(__k, __k));
else if constexpr (_FromBytes == 2 && _ToBytes == 8)
{
const auto __y
= __vector_bitcast<int>(__interleave128_lo(__k, __k));
return __intrin_bitcast<_To>(__interleave128_lo(__y, __y));
}
else if constexpr (_FromBytes == 1 && _ToBytes == 8)
{
auto __y
= __vector_bitcast<short>(__interleave128_lo(__k, __k));
auto __z = __vector_bitcast<int>(__interleave128_lo(__y, __y));
return __intrin_bitcast<_To>(__interleave128_lo(__z, __z));
}
else if constexpr (_FromBytes == 8 && _ToBytes == 4 && __have_sse2)
return __intrin_bitcast<_To>(
_mm_packs_epi32(__vector_bitcast<_LLong>(__k), __m128i()));
else if constexpr (_FromBytes == 8 && _ToBytes == 4)
return __vector_shuffle<1, 3, 6, 7>(__vector_bitcast<_Up>(__k),
_UI());
else if constexpr (_FromBytes == 2 && _ToBytes == 4)
return __intrin_bitcast<_To>(__interleave128_lo(__k, __k));
else if constexpr (_FromBytes == 1 && _ToBytes == 4)
{
const auto __y
= __vector_bitcast<short>(__interleave128_lo(__k, __k));
return __intrin_bitcast<_To>(__interleave128_lo(__y, __y));
}
else if constexpr (_FromBytes == 8 && _ToBytes == 2)
{
if constexpr (__have_sse2 && !__have_ssse3)
return __intrin_bitcast<_To>(_mm_packs_epi32(
_mm_packs_epi32(__vector_bitcast<_LLong>(__k), __m128i()),
__m128i()));
else
return __intrin_bitcast<_To>(
__vector_permute<3, 7, -1, -1, -1, -1, -1, -1>(
__vector_bitcast<_Up>(__k)));
}
else if constexpr (_FromBytes == 4 && _ToBytes == 2)
return __intrin_bitcast<_To>(
_mm_packs_epi32(__vector_bitcast<_LLong>(__k), __m128i()));
else if constexpr (_FromBytes == 1 && _ToBytes == 2)
return __intrin_bitcast<_To>(__interleave128_lo(__k, __k));
else if constexpr (_FromBytes == 8 && _ToBytes == 1 && __have_ssse3)
return __intrin_bitcast<_To>(
_mm_shuffle_epi8(__vector_bitcast<_LLong>(__k),
_mm_setr_epi8(7, 15, -1, -1, -1, -1, -1, -1,
-1, -1, -1, -1, -1, -1, -1,
-1)));
else if constexpr (_FromBytes == 8 && _ToBytes == 1)
{
auto __y
= _mm_packs_epi32(__vector_bitcast<_LLong>(__k), __m128i());
__y = _mm_packs_epi32(__y, __m128i());
return __intrin_bitcast<_To>(_mm_packs_epi16(__y, __m128i()));
}
else if constexpr (_FromBytes == 4 && _ToBytes == 1 && __have_ssse3)
return __intrin_bitcast<_To>(
_mm_shuffle_epi8(__vector_bitcast<_LLong>(__k),
_mm_setr_epi8(3, 7, 11, 15, -1, -1, -1, -1, -1,
-1, -1, -1, -1, -1, -1, -1)));
else if constexpr (_FromBytes == 4 && _ToBytes == 1)
{
const auto __y
= _mm_packs_epi32(__vector_bitcast<_LLong>(__k), __m128i());
return __intrin_bitcast<_To>(_mm_packs_epi16(__y, __m128i()));
}
else if constexpr (_FromBytes == 2 && _ToBytes == 1)
return __intrin_bitcast<_To>(
_mm_packs_epi16(__vector_bitcast<_LLong>(__k), __m128i()));
else
__assert_unreachable<_Tp>();
}
else if constexpr (sizeof(_UI) == 32 && sizeof(__k) == 32)
{
if constexpr (_FromBytes == _ToBytes)
__assert_unreachable<_Tp>();
else if constexpr (_FromBytes == _ToBytes * 2)
{
const auto __y = __vector_bitcast<_LLong>(__k);
return __intrin_bitcast<_To>(_mm256_castsi128_si256(
_mm_packs_epi16(__lo128(__y), __hi128(__y))));
}
else if constexpr (_FromBytes == _ToBytes * 4)
{
const auto __y = __vector_bitcast<_LLong>(__k);
return __intrin_bitcast<_To>(_mm256_castsi128_si256(
_mm_packs_epi16(_mm_packs_epi16(__lo128(__y), __hi128(__y)),
__m128i())));
}
else if constexpr (_FromBytes == _ToBytes * 8)
{
const auto __y = __vector_bitcast<_LLong>(__k);
return __intrin_bitcast<_To>(_mm256_castsi128_si256(
_mm_shuffle_epi8(_mm_packs_epi16(__lo128(__y), __hi128(__y)),
_mm_setr_epi8(3, 7, 11, 15, -1, -1, -1, -1,
-1, -1, -1, -1, -1, -1, -1,
-1))));
}
else if constexpr (_FromBytes * 2 == _ToBytes)
{
auto __y = __xzyw(__to_intrin(__k));
if constexpr (std::is_floating_point_v<_Tp>
|| (!__have_avx2 && _FromBytes == 4))
{
const auto __yy = __vector_bitcast<float>(__y);
return __intrin_bitcast<_To>(
_mm256_unpacklo_ps(__yy, __yy));
}
else
return __intrin_bitcast<_To>(_mm256_unpacklo_epi8(__y, __y));
}
else if constexpr (_FromBytes * 4 == _ToBytes)
{
auto __y
= _mm_unpacklo_epi8(__lo128(__vector_bitcast<_LLong>(__k)),
__lo128(__vector_bitcast<_LLong>(
__k)));
return __intrin_bitcast<_To>(
__concat(_mm_unpacklo_epi16(__y, __y),
_mm_unpackhi_epi16(__y, __y)));
}
else if constexpr (_FromBytes == 1 && _ToBytes == 8)
{
auto __y
= _mm_unpacklo_epi8(__lo128(__vector_bitcast<_LLong>(__k)),
__lo128(__vector_bitcast<_LLong>(
__k)));
__y = _mm_unpacklo_epi16(__y,
__y);
return __intrin_bitcast<_To>(
__concat(_mm_unpacklo_epi32(__y, __y),
_mm_unpackhi_epi32(__y, __y)));
}
else
__assert_unreachable<_Tp>();
}
else if constexpr (sizeof(_UI) == 32 && sizeof(__k) == 16)
{
if constexpr (_FromBytes == _ToBytes)
return __intrin_bitcast<_To>(
__intrinsic_type_t<_Tp, 32 / sizeof(_Tp)>(
__zero_extend(__to_intrin(__k))));
else if constexpr (_FromBytes * 2 == _ToBytes)
{
return __intrin_bitcast<_To>(
__concat(_mm_unpacklo_epi8(__vector_bitcast<_LLong>(__k),
__vector_bitcast<_LLong>(__k)),
_mm_unpackhi_epi8(__vector_bitcast<_LLong>(__k),
__vector_bitcast<_LLong>(__k))));
}
else if constexpr (_FromBytes * 4 == _ToBytes)
{
if constexpr (__have_avx2)
{
return __intrin_bitcast<_To>(_mm256_shuffle_epi8(
__concat(__vector_bitcast<_LLong>(__k),
__vector_bitcast<_LLong>(__k)),
_mm256_setr_epi8(0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3,
3, 3, 4, 4, 4, 4, 5, 5, 5, 5, 6, 6, 6, 6,
7, 7, 7, 7)));
}
else
{
return __intrin_bitcast<_To>(__concat(
_mm_shuffle_epi8(__vector_bitcast<_LLong>(__k),
_mm_setr_epi8(0, 0, 0, 0, 1, 1, 1, 1, 2,
2, 2, 2, 3, 3, 3, 3)),
_mm_shuffle_epi8(__vector_bitcast<_LLong>(__k),
_mm_setr_epi8(4, 4, 4, 4, 5, 5, 5, 5, 6,
6, 6, 6, 7, 7, 7, 7))));
}
}
else if constexpr (_FromBytes * 8 == _ToBytes)
{
if constexpr (__have_avx2)
{
return __intrin_bitcast<_To>(_mm256_shuffle_epi8(
__concat(__vector_bitcast<_LLong>(__k),
__vector_bitcast<_LLong>(__k)),
_mm256_setr_epi8(0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1,
1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3,
3, 3, 3, 3)));
}
else
{
return __intrin_bitcast<_To>(__concat(
_mm_shuffle_epi8(__vector_bitcast<_LLong>(__k),
_mm_setr_epi8(0, 0, 0, 0, 0, 0, 0, 0, 1,
1, 1, 1, 1, 1, 1, 1)),
_mm_shuffle_epi8(__vector_bitcast<_LLong>(__k),
_mm_setr_epi8(2, 2, 2, 2, 2, 2, 2, 2, 3,
3, 3, 3, 3, 3, 3, 3))));
}
}
else if constexpr (_FromBytes == _ToBytes * 2)
return __intrin_bitcast<_To>(__m256i(__zero_extend(
_mm_packs_epi16(__vector_bitcast<_LLong>(__k), __m128i()))));
else if constexpr (_FromBytes == 8 && _ToBytes == 2)
{
return __intrin_bitcast<_To>(__m256i(__zero_extend(
_mm_shuffle_epi8(__vector_bitcast<_LLong>(__k),
_mm_setr_epi8(6, 7, 14, 15, -1, -1, -1, -1,
-1, -1, -1, -1, -1, -1, -1,
-1)))));
}
else if constexpr (_FromBytes == 4 && _ToBytes == 1)
{
return __intrin_bitcast<_To>(__m256i(__zero_extend(
_mm_shuffle_epi8(__vector_bitcast<_LLong>(__k),
_mm_setr_epi8(3, 7, 11, 15, -1, -1, -1, -1,
-1, -1, -1, -1, -1, -1, -1,
-1)))));
}
else if constexpr (_FromBytes == 8 && _ToBytes == 1)
{
return __intrin_bitcast<_To>(__m256i(__zero_extend(
_mm_shuffle_epi8(__vector_bitcast<_LLong>(__k),
_mm_setr_epi8(7, 15, -1, -1, -1, -1, -1, -1,
-1, -1, -1, -1, -1, -1, -1,
-1)))));
}
else
static_assert(!std::is_same_v<_Tp, _Tp>, "should be unreachable");
}
else if constexpr (sizeof(_UI) == 16 && sizeof(__k) == 32)
{
if constexpr (_FromBytes == _ToBytes)
{
return __intrin_bitcast<_To>(__lo128(__k));
}
else if constexpr (_FromBytes == _ToBytes * 2)
{
auto __y = __vector_bitcast<_LLong>(__k);
return __intrin_bitcast<_To>(
_mm_packs_epi16(__lo128(__y), __hi128(__y)));
}
else if constexpr (_FromBytes == _ToBytes * 4)
{
auto __y = __vector_bitcast<_LLong>(__k);
return __intrin_bitcast<_To>(
_mm_packs_epi16(_mm_packs_epi16(__lo128(__y), __hi128(__y)),
__m128i()));
}
else if constexpr (_FromBytes == 8 && _ToBytes == 1)
{
auto __y = __vector_bitcast<_LLong>(__k);
return __intrin_bitcast<_To>(
_mm_shuffle_epi8(_mm_packs_epi16(__lo128(__y), __hi128(__y)),
_mm_setr_epi8(3, 7, 11, 15, -1, -1, -1, -1,
-1, -1, -1, -1, -1, -1, -1,
-1)));
}
else if constexpr (_FromBytes * 2 == _ToBytes)
{
auto __y = __lo128(__vector_bitcast<_LLong>(__k));
return __intrin_bitcast<_To>(_mm_unpacklo_epi8(__y, __y));
}
else if constexpr (_FromBytes * 4 == _ToBytes)
{
auto __y = __lo128(__vector_bitcast<_LLong>(__k));
__y = _mm_unpacklo_epi8(__y, __y);
return __intrin_bitcast<_To>(_mm_unpacklo_epi8(__y, __y));
}
else if constexpr (_FromBytes * 8 == _ToBytes)
{
auto __y = __lo128(__vector_bitcast<_LLong>(__k));
__y = _mm_unpacklo_epi8(__y, __y);
__y = _mm_unpacklo_epi8(__y, __y);
return __intrin_bitcast<_To>(_mm_unpacklo_epi8(__y, __y));
}
else
static_assert(!std::is_same_v<_Tp, _Tp>, "should be unreachable");
}
else
return _Base::template _S_to_maskvector<_Up, _ToN>(__x);
}
}
template <typename _Tp, size_t _Np>
_GLIBCXX_SIMD_INTRINSIC static constexpr _SanitizedBitMask<_Np>
_S_to_bits(_SimdWrapper<_Tp, _Np> __x)
{
if constexpr (is_same_v<_Tp, bool>)
return _BitMask<_Np>(__x._M_data)._M_sanitized();
else
{
static_assert(std::is_same_v<_Tp, __int_for_sizeof_t<_Tp>>);
if (__builtin_is_constant_evaluated()
|| __builtin_constant_p(__x._M_data))
{
const auto __bools = -__x._M_data;
const _ULLong __k = __call_with_n_evaluations<_Np>(
[](auto... __bits) { return (__bits | ...); },
[&](auto __i) { return _ULLong(__bools[+__i]) << __i; });
if (__builtin_is_constant_evaluated() || __builtin_constant_p(__k))
return __k;
}
const auto __xi = __to_intrin(__x);
if constexpr (sizeof(_Tp) == 1)
if constexpr (sizeof(__xi) == 16)
if constexpr (__have_avx512bw_vl)
return _BitMask<_Np>(_mm_movepi8_mask(__xi));
else
return _BitMask<_Np>(_mm_movemask_epi8(__xi));
else if constexpr (sizeof(__xi) == 32)
if constexpr (__have_avx512bw_vl)
return _BitMask<_Np>(_mm256_movepi8_mask(__xi));
else
return _BitMask<_Np>(_mm256_movemask_epi8(__xi));
else
return _BitMask<_Np>(_mm512_movepi8_mask(__xi));
else if constexpr (sizeof(_Tp) == 2)
if constexpr (sizeof(__xi) == 16)
if constexpr (__have_avx512bw_vl)
return _BitMask<_Np>(_mm_movepi16_mask(__xi));
else if constexpr (__have_avx512bw)
return _BitMask<_Np>(_mm512_movepi16_mask(__zero_extend(__xi)));
else
return _BitMask<_Np>(
_mm_movemask_epi8(_mm_packs_epi16(__xi, __m128i())));
else if constexpr (sizeof(__xi) == 32)
if constexpr (__have_avx512bw_vl)
return _BitMask<_Np>(_mm256_movepi16_mask(__xi));
else if constexpr (__have_avx512bw)
return _BitMask<_Np>(_mm512_movepi16_mask(__zero_extend(__xi)));
else
return _BitMask<_Np>(_mm_movemask_epi8(
_mm_packs_epi16(__lo128(__xi), __hi128(__xi))));
else
return _BitMask<_Np>(_mm512_movepi16_mask(__xi));
else if constexpr (sizeof(_Tp) == 4)
if constexpr (sizeof(__xi) == 16)
if constexpr (__have_avx512dq_vl)
return _BitMask<_Np>(_mm_movepi32_mask(__xi));
else if constexpr (__have_avx512vl)
return _BitMask<_Np>(_mm_cmplt_epi32_mask(__xi, __m128i()));
else if constexpr (__have_avx512dq)
return _BitMask<_Np>(_mm512_movepi32_mask(__zero_extend(__xi)));
else if constexpr (__have_avx512f)
return _BitMask<_Np>(
_mm512_cmplt_epi32_mask(__zero_extend(__xi), __m512i()));
else
return _BitMask<_Np>(
_mm_movemask_ps(reinterpret_cast<__m128>(__xi)));
else if constexpr (sizeof(__xi) == 32)
if constexpr (__have_avx512dq_vl)
return _BitMask<_Np>(_mm256_movepi32_mask(__xi));
else if constexpr (__have_avx512dq)
return _BitMask<_Np>(_mm512_movepi32_mask(__zero_extend(__xi)));
else if constexpr (__have_avx512vl)
return _BitMask<_Np>(_mm256_cmplt_epi32_mask(__xi, __m256i()));
else if constexpr (__have_avx512f)
return _BitMask<_Np>(
_mm512_cmplt_epi32_mask(__zero_extend(__xi), __m512i()));
else
return _BitMask<_Np>(
_mm256_movemask_ps(reinterpret_cast<__m256>(__xi)));
else
if constexpr (__have_avx512dq)
return _BitMask<_Np>(_mm512_movepi32_mask(__xi));
else
return _BitMask<_Np>(_mm512_cmplt_epi32_mask(__xi, __m512i()));
else if constexpr (sizeof(_Tp) == 8)
if constexpr (sizeof(__xi) == 16)
if constexpr (__have_avx512dq_vl)
return _BitMask<_Np>(_mm_movepi64_mask(__xi));
else if constexpr (__have_avx512dq)
return _BitMask<_Np>(_mm512_movepi64_mask(__zero_extend(__xi)));
else if constexpr (__have_avx512vl)
return _BitMask<_Np>(_mm_cmplt_epi64_mask(__xi, __m128i()));
else if constexpr (__have_avx512f)
return _BitMask<_Np>(
_mm512_cmplt_epi64_mask(__zero_extend(__xi), __m512i()));
else
return _BitMask<_Np>(
_mm_movemask_pd(reinterpret_cast<__m128d>(__xi)));
else if constexpr (sizeof(__xi) == 32)
if constexpr (__have_avx512dq_vl)
return _BitMask<_Np>(_mm256_movepi64_mask(__xi));
else if constexpr (__have_avx512dq)
return _BitMask<_Np>(_mm512_movepi64_mask(__zero_extend(__xi)));
else if constexpr (__have_avx512vl)
return _BitMask<_Np>(_mm256_cmplt_epi64_mask(__xi, __m256i()));
else if constexpr (__have_avx512f)
return _BitMask<_Np>(
_mm512_cmplt_epi64_mask(__zero_extend(__xi), __m512i()));
else
return _BitMask<_Np>(
_mm256_movemask_pd(reinterpret_cast<__m256d>(__xi)));
else
if constexpr (__have_avx512dq)
return _BitMask<_Np>(_mm512_movepi64_mask(__xi));
else
return _BitMask<_Np>(_mm512_cmplt_epi64_mask(__xi, __m512i()));
else
__assert_unreachable<_Tp>();
}
}
};
template <typename _Abi>
struct _MaskImplX86 : _MaskImplX86Mixin, _MaskImplBuiltin<_Abi>
{
using _MaskImplX86Mixin::_S_to_bits;
using _MaskImplX86Mixin::_S_to_maskvector;
using _MaskImplBuiltin<_Abi>::_S_convert;
template <typename _Tp>
using _SimdMember = typename _Abi::template __traits<_Tp>::_SimdMember;
template <typename _Tp>
using _MaskMember = typename _Abi::template _MaskMember<_Tp>;
template <typename _Tp>
static constexpr size_t _S_size = simd_size_v<_Tp, _Abi>;
using _Base = _MaskImplBuiltin<_Abi>;
template <typename _Tp>
_GLIBCXX_SIMD_INTRINSIC static constexpr _MaskMember<_Tp>
_S_broadcast(bool __x)
{
if constexpr (__is_avx512_abi<_Abi>())
return __x ? _Abi::_S_masked(_MaskMember<_Tp>(-1)) : _MaskMember<_Tp>();
else
return _Base::template _S_broadcast<_Tp>(__x);
}
template <typename _Tp>
_GLIBCXX_SIMD_INTRINSIC static constexpr _MaskMember<_Tp>
_S_load(const bool* __mem)
{
static_assert(std::is_same_v<_Tp, __int_for_sizeof_t<_Tp>>);
if constexpr (__have_avx512bw)
{
const auto __to_vec_or_bits = [](auto __bits) -> decltype(auto) {
if constexpr (__is_avx512_abi<_Abi>())
return __bits;
else
return _S_to_maskvector<_Tp>(
_BitMask<_S_size<_Tp>>(__bits)._M_sanitized());
};
if constexpr (_S_size<_Tp> <= 16 && __have_avx512vl)
{
__m128i __a = {};
__builtin_memcpy(&__a, __mem, _S_size<_Tp>);
return __to_vec_or_bits(_mm_test_epi8_mask(__a, __a));
}
else if constexpr (_S_size<_Tp> <= 32 && __have_avx512vl)
{
__m256i __a = {};
__builtin_memcpy(&__a, __mem, _S_size<_Tp>);
return __to_vec_or_bits(_mm256_test_epi8_mask(__a, __a));
}
else if constexpr (_S_size<_Tp> <= 64)
{
__m512i __a = {};
__builtin_memcpy(&__a, __mem, _S_size<_Tp>);
return __to_vec_or_bits(_mm512_test_epi8_mask(__a, __a));
}
}
else if constexpr (__is_avx512_abi<_Abi>())
{
if constexpr (_S_size<_Tp> <= 8)
{
__m128i __a = {};
__builtin_memcpy(&__a, __mem, _S_size<_Tp>);
const auto __b = _mm512_cvtepi8_epi64(__a);
return _mm512_test_epi64_mask(__b, __b);
}
else if constexpr (_S_size<_Tp> <= 16)
{
__m128i __a = {};
__builtin_memcpy(&__a, __mem, _S_size<_Tp>);
const auto __b = _mm512_cvtepi8_epi32(__a);
return _mm512_test_epi32_mask(__b, __b);
}
else if constexpr (_S_size<_Tp> <= 32)
{
__m128i __a = {};
__builtin_memcpy(&__a, __mem, 16);
const auto __b = _mm512_cvtepi8_epi32(__a);
__builtin_memcpy(&__a, __mem + 16, _S_size<_Tp> - 16);
const auto __c = _mm512_cvtepi8_epi32(__a);
return _mm512_test_epi32_mask(__b, __b)
| (_mm512_test_epi32_mask(__c, __c) << 16);
}
else if constexpr (_S_size<_Tp> <= 64)
{
__m128i __a = {};
__builtin_memcpy(&__a, __mem, 16);
const auto __b = _mm512_cvtepi8_epi32(__a);
__builtin_memcpy(&__a, __mem + 16, 16);
const auto __c = _mm512_cvtepi8_epi32(__a);
if constexpr (_S_size<_Tp> <= 48)
{
__builtin_memcpy(&__a, __mem + 32, _S_size<_Tp> - 32);
const auto __d = _mm512_cvtepi8_epi32(__a);
return _mm512_test_epi32_mask(__b, __b)
| (_mm512_test_epi32_mask(__c, __c) << 16)
| (_ULLong(_mm512_test_epi32_mask(__d, __d)) << 32);
}
else
{
__builtin_memcpy(&__a, __mem + 16, 16);
const auto __d = _mm512_cvtepi8_epi32(__a);
__builtin_memcpy(&__a, __mem + 32, _S_size<_Tp> - 48);
const auto __e = _mm512_cvtepi8_epi32(__a);
return _mm512_test_epi32_mask(__b, __b)
| (_mm512_test_epi32_mask(__c, __c) << 16)
| (_ULLong(_mm512_test_epi32_mask(__d, __d)) << 32)
| (_ULLong(_mm512_test_epi32_mask(__e, __e)) << 48);
}
}
else
__assert_unreachable<_Tp>();
}
else if constexpr (sizeof(_Tp) == 8 && _S_size<_Tp> == 2)
return __vector_bitcast<_Tp>(
__vector_type16_t<int>{-int(__mem[0]), -int(__mem[0]), -int(__mem[1]),
-int(__mem[1])});
else if constexpr (sizeof(_Tp) == 8 && _S_size<_Tp> <= 4 && __have_avx)
{
int __bool4 = 0;
__builtin_memcpy(&__bool4, __mem, _S_size<_Tp>);
const auto __k = __to_intrin(
(__vector_broadcast<4>(__bool4)
& __make_vector<int>(0x1, 0x100, 0x10000,
_S_size<_Tp> == 4 ? 0x1000000 : 0))
!= 0);
return __vector_bitcast<_Tp>(
__concat(_mm_unpacklo_epi32(__k, __k), _mm_unpackhi_epi32(__k, __k)));
}
else if constexpr (sizeof(_Tp) == 4 && _S_size<_Tp> <= 4)
{
int __bools = 0;
__builtin_memcpy(&__bools, __mem, _S_size<_Tp>);
if constexpr (__have_sse2)
{
__m128i __k = _mm_cvtsi32_si128(__bools);
__k = _mm_cmpgt_epi16(_mm_unpacklo_epi8(__k, __k), __m128i());
return __vector_bitcast<_Tp, _S_size<_Tp>>(
_mm_unpacklo_epi16(__k, __k));
}
else
{
__m128 __k = _mm_cvtpi8_ps(_mm_cvtsi32_si64(__bools));
_mm_empty();
return __vector_bitcast<_Tp, _S_size<_Tp>>(
_mm_cmpgt_ps(__k, __m128()));
}
}
else if constexpr (sizeof(_Tp) == 4 && _S_size<_Tp> <= 8)
{
__m128i __k = {};
__builtin_memcpy(&__k, __mem, _S_size<_Tp>);
__k = _mm_cmpgt_epi16(_mm_unpacklo_epi8(__k, __k), __m128i());
return __vector_bitcast<_Tp>(
__concat(_mm_unpacklo_epi16(__k, __k), _mm_unpackhi_epi16(__k, __k)));
}
else if constexpr (sizeof(_Tp) == 2 && _S_size<_Tp> <= 16)
{
__m128i __k = {};
__builtin_memcpy(&__k, __mem, _S_size<_Tp>);
__k = _mm_cmpgt_epi8(__k, __m128i());
if constexpr (_S_size<_Tp> <= 8)
return __vector_bitcast<_Tp, _S_size<_Tp>>(
_mm_unpacklo_epi8(__k, __k));
else
return __concat(_mm_unpacklo_epi8(__k, __k),
_mm_unpackhi_epi8(__k, __k));
}
else
return _Base::template _S_load<_Tp>(__mem);
}
template <size_t _Np, typename _Tp>
_GLIBCXX_SIMD_INTRINSIC static _MaskMember<_Tp>
_S_from_bitmask(_SanitizedBitMask<_Np> __bits, _TypeTag<_Tp>)
{
static_assert(std::is_same_v<_Tp, __int_for_sizeof_t<_Tp>>);
if constexpr (__is_avx512_abi<_Abi>())
return __bits._M_to_bits();
else
return _S_to_maskvector<_Tp, _S_size<_Tp>>(__bits);
}
template <typename _Tp, size_t _Np>
static inline _SimdWrapper<_Tp, _Np>
_S_masked_load(_SimdWrapper<_Tp, _Np> __merge, _SimdWrapper<_Tp, _Np> __mask,
const bool* __mem) noexcept
{
if constexpr (__is_avx512_abi<_Abi>())
{
if constexpr (__have_avx512bw_vl)
{
if constexpr (_Np <= 16)
{
const auto __a = _mm_mask_loadu_epi8(__m128i(), __mask, __mem);
return (__merge & ~__mask) | _mm_test_epi8_mask(__a, __a);
}
else if constexpr (_Np <= 32)
{
const auto __a
= _mm256_mask_loadu_epi8(__m256i(), __mask, __mem);
return (__merge & ~__mask) | _mm256_test_epi8_mask(__a, __a);
}
else if constexpr (_Np <= 64)
{
const auto __a
= _mm512_mask_loadu_epi8(__m512i(), __mask, __mem);
return (__merge & ~__mask) | _mm512_test_epi8_mask(__a, __a);
}
else
__assert_unreachable<_Tp>();
}
else
{
_BitOps::_S_bit_iteration(__mask, [&](auto __i) {
__merge._M_set(__i, __mem[__i]);
});
return __merge;
}
}
else if constexpr (__have_avx512bw_vl && _Np == 32 && sizeof(_Tp) == 1)
{
const auto __k = _S_to_bits(__mask)._M_to_bits();
__merge
= _mm256_mask_sub_epi8(__to_intrin(__merge), __k, __m256i(),
_mm256_mask_loadu_epi8(__m256i(), __k, __mem));
}
else if constexpr (__have_avx512bw_vl && _Np == 16 && sizeof(_Tp) == 1)
{
const auto __k = _S_to_bits(__mask)._M_to_bits();
__merge
= _mm_mask_sub_epi8(__vector_bitcast<_LLong>(__merge), __k, __m128i(),
_mm_mask_loadu_epi8(__m128i(), __k, __mem));
}
else if constexpr (__have_avx512bw_vl && _Np == 16 && sizeof(_Tp) == 2)
{
const auto __k = _S_to_bits(__mask)._M_to_bits();
__merge = _mm256_mask_sub_epi16(
__vector_bitcast<_LLong>(__merge), __k, __m256i(),
_mm256_cvtepi8_epi16(_mm_mask_loadu_epi8(__m128i(), __k, __mem)));
}
else if constexpr (__have_avx512bw_vl && _Np == 8 && sizeof(_Tp) == 2)
{
const auto __k = _S_to_bits(__mask)._M_to_bits();
__merge = _mm_mask_sub_epi16(
__vector_bitcast<_LLong>(__merge), __k, __m128i(),
_mm_cvtepi8_epi16(_mm_mask_loadu_epi8(__m128i(), __k, __mem)));
}
else if constexpr (__have_avx512bw_vl && _Np == 8 && sizeof(_Tp) == 4)
{
const auto __k = _S_to_bits(__mask)._M_to_bits();
__merge = __vector_bitcast<_Tp>(_mm256_mask_sub_epi32(
__vector_bitcast<_LLong>(__merge), __k, __m256i(),
_mm256_cvtepi8_epi32(_mm_mask_loadu_epi8(__m128i(), __k, __mem))));
}
else if constexpr (__have_avx512bw_vl && _Np == 4 && sizeof(_Tp) == 4)
{
const auto __k = _S_to_bits(__mask)._M_to_bits();
__merge = __vector_bitcast<_Tp>(_mm_mask_sub_epi32(
__vector_bitcast<_LLong>(__merge), __k, __m128i(),
_mm_cvtepi8_epi32(_mm_mask_loadu_epi8(__m128i(), __k, __mem))));
}
else if constexpr (__have_avx512bw_vl && _Np == 4 && sizeof(_Tp) == 8)
{
const auto __k = _S_to_bits(__mask)._M_to_bits();
__merge = __vector_bitcast<_Tp>(_mm256_mask_sub_epi64(
__vector_bitcast<_LLong>(__merge), __k, __m256i(),
_mm256_cvtepi8_epi64(_mm_mask_loadu_epi8(__m128i(), __k, __mem))));
}
else if constexpr (__have_avx512bw_vl && _Np == 2 && sizeof(_Tp) == 8)
{
const auto __k = _S_to_bits(__mask)._M_to_bits();
__merge = __vector_bitcast<_Tp>(_mm_mask_sub_epi64(
__vector_bitcast<_LLong>(__merge), __k, __m128i(),
_mm_cvtepi8_epi64(_mm_mask_loadu_epi8(__m128i(), __k, __mem))));
}
else
return _Base::_S_masked_load(__merge, __mask, __mem);
return __merge;
}
template <typename _Tp, size_t _Np>
_GLIBCXX_SIMD_INTRINSIC static void _S_store(_SimdWrapper<_Tp, _Np> __v,
bool* __mem) noexcept
{
if constexpr (__is_avx512_abi<_Abi>())
{
if constexpr (__have_avx512bw_vl)
_CommonImplX86::_S_store<_Np>(
__vector_bitcast<char>([](auto __data) {
if constexpr (_Np <= 16)
return _mm_maskz_set1_epi8(__data, 1);
else if constexpr (_Np <= 32)
return _mm256_maskz_set1_epi8(__data, 1);
else
return _mm512_maskz_set1_epi8(__data, 1);
}(__v._M_data)),
__mem);
else if constexpr (_Np <= 8)
_CommonImplX86::_S_store<_Np>(
__vector_bitcast<char>(
#if defined __x86_64__
__make_wrapper<_ULLong>(
_pdep_u64(__v._M_data, 0x0101010101010101ULL), 0ull)
#else
__make_wrapper<_UInt>(_pdep_u32(__v._M_data, 0x01010101U),
_pdep_u32(__v._M_data >> 4, 0x01010101U))
#endif
),
__mem);
else if constexpr (_Np <= 16)
_mm512_mask_cvtepi32_storeu_epi8(__mem, 0xffffu >> (16 - _Np),
_mm512_maskz_set1_epi32(__v._M_data,
1));
else
__assert_unreachable<_Tp>();
}
else if constexpr (__is_sse_abi<_Abi>())
{
if constexpr (_Np == 2 && sizeof(_Tp) == 8)
{
const auto __k = __vector_bitcast<int>(__v);
__mem[0] = -__k[1];
__mem[1] = -__k[3];
}
else if constexpr (_Np <= 4 && sizeof(_Tp) == 4)
{
if constexpr (__have_sse2)
{
const unsigned __bool4
= __vector_bitcast<_UInt>(
_mm_packs_epi16(_mm_packs_epi32(__intrin_bitcast<__m128i>(
__to_intrin(__v)),
__m128i()),
__m128i()))[0]
& 0x01010101u;
__builtin_memcpy(__mem, &__bool4, _Np);
}
else if constexpr (__have_mmx)
{
const __m64 __k
= _mm_cvtps_pi8(__and(__to_intrin(__v), _mm_set1_ps(1.f)));
__builtin_memcpy(__mem, &__k, _Np);
_mm_empty();
}
else
return _Base::_S_store(__v, __mem);
}
else if constexpr (_Np <= 8 && sizeof(_Tp) == 2)
{
_CommonImplX86::_S_store<_Np>(
__vector_bitcast<char>(_mm_packs_epi16(
__to_intrin(__vector_bitcast<_UShort>(__v) >> 15), __m128i())),
__mem);
}
else if constexpr (_Np <= 16 && sizeof(_Tp) == 1)
_CommonImplX86::_S_store<_Np>(__v._M_data & 1, __mem);
else
__assert_unreachable<_Tp>();
}
else if constexpr (__is_avx_abi<_Abi>())
{
if constexpr (_Np <= 4 && sizeof(_Tp) == 8)
{
auto __k = __intrin_bitcast<__m256i>(__to_intrin(__v));
int __bool4;
if constexpr (__have_avx2)
__bool4 = _mm256_movemask_epi8(__k);
else
__bool4 = (_mm_movemask_epi8(__lo128(__k))
| (_mm_movemask_epi8(__hi128(__k)) << 16));
__bool4 &= 0x01010101;
__builtin_memcpy(__mem, &__bool4, _Np);
}
else if constexpr (_Np <= 8 && sizeof(_Tp) == 4)
{
const auto __k = __intrin_bitcast<__m256i>(__to_intrin(__v));
const auto __k2
= _mm_srli_epi16(_mm_packs_epi16(__lo128(__k), __hi128(__k)), 15);
const auto __k3
= __vector_bitcast<char>(_mm_packs_epi16(__k2, __m128i()));
_CommonImplX86::_S_store<_Np>(__k3, __mem);
}
else if constexpr (_Np <= 16 && sizeof(_Tp) == 2)
{
if constexpr (__have_avx2)
{
const auto __x = _mm256_srli_epi16(__to_intrin(__v), 15);
const auto __bools = __vector_bitcast<char>(
_mm_packs_epi16(__lo128(__x), __hi128(__x)));
_CommonImplX86::_S_store<_Np>(__bools, __mem);
}
else
{
const auto __bools
= 1
& __vector_bitcast<_UChar>(
_mm_packs_epi16(__lo128(__to_intrin(__v)),
__hi128(__to_intrin(__v))));
_CommonImplX86::_S_store<_Np>(__bools, __mem);
}
}
else if constexpr (_Np <= 32 && sizeof(_Tp) == 1)
_CommonImplX86::_S_store<_Np>(1 & __v._M_data, __mem);
else
__assert_unreachable<_Tp>();
}
else
__assert_unreachable<_Tp>();
}
template <typename _Tp, size_t _Np>
static inline void _S_masked_store(const _SimdWrapper<_Tp, _Np> __v,
bool* __mem,
const _SimdWrapper<_Tp, _Np> __k) noexcept
{
if constexpr (__is_avx512_abi<_Abi>())
{
static_assert(is_same_v<_Tp, bool>);
if constexpr (_Np <= 16 && __have_avx512bw_vl)
_mm_mask_storeu_epi8(__mem, __k, _mm_maskz_set1_epi8(__v, 1));
else if constexpr (_Np <= 16)
_mm512_mask_cvtepi32_storeu_epi8(__mem, __k,
_mm512_maskz_set1_epi32(__v, 1));
else if constexpr (_Np <= 32 && __have_avx512bw_vl)
_mm256_mask_storeu_epi8(__mem, __k, _mm256_maskz_set1_epi8(__v, 1));
else if constexpr (_Np <= 32 && __have_avx512bw)
_mm256_mask_storeu_epi8(__mem, __k,
__lo256(_mm512_maskz_set1_epi8(__v, 1)));
else if constexpr (_Np <= 64 && __have_avx512bw)
_mm512_mask_storeu_epi8(__mem, __k, _mm512_maskz_set1_epi8(__v, 1));
else
__assert_unreachable<_Tp>();
}
else
_Base::_S_masked_store(__v, __mem, __k);
}
template <typename _Tp, size_t _Np>
_GLIBCXX_SIMD_INTRINSIC static constexpr _SimdWrapper<_Tp, _Np>
_S_logical_and(const _SimdWrapper<_Tp, _Np>& __x,
const _SimdWrapper<_Tp, _Np>& __y)
{
if constexpr (std::is_same_v<_Tp, bool>)
{
if constexpr (__have_avx512dq && _Np <= 8)
return _kand_mask8(__x._M_data, __y._M_data);
else if constexpr (_Np <= 16)
return _kand_mask16(__x._M_data, __y._M_data);
else if constexpr (__have_avx512bw && _Np <= 32)
return _kand_mask32(__x._M_data, __y._M_data);
else if constexpr (__have_avx512bw && _Np <= 64)
return _kand_mask64(__x._M_data, __y._M_data);
else
__assert_unreachable<_Tp>();
}
else
return _Base::_S_logical_and(__x, __y);
}
template <typename _Tp, size_t _Np>
_GLIBCXX_SIMD_INTRINSIC static constexpr _SimdWrapper<_Tp, _Np>
_S_logical_or(const _SimdWrapper<_Tp, _Np>& __x,
const _SimdWrapper<_Tp, _Np>& __y)
{
if constexpr (std::is_same_v<_Tp, bool>)
{
if constexpr (__have_avx512dq && _Np <= 8)
return _kor_mask8(__x._M_data, __y._M_data);
else if constexpr (_Np <= 16)
return _kor_mask16(__x._M_data, __y._M_data);
else if constexpr (__have_avx512bw && _Np <= 32)
return _kor_mask32(__x._M_data, __y._M_data);
else if constexpr (__have_avx512bw && _Np <= 64)
return _kor_mask64(__x._M_data, __y._M_data);
else
__assert_unreachable<_Tp>();
}
else
return _Base::_S_logical_or(__x, __y);
}
template <typename _Tp, size_t _Np>
_GLIBCXX_SIMD_INTRINSIC static constexpr _SimdWrapper<_Tp, _Np>
_S_bit_not(const _SimdWrapper<_Tp, _Np>& __x)
{
if constexpr (std::is_same_v<_Tp, bool>)
{
if constexpr (__have_avx512dq && _Np <= 8)
return _kandn_mask8(__x._M_data,
_Abi::template __implicit_mask_n<_Np>());
else if constexpr (_Np <= 16)
return _kandn_mask16(__x._M_data,
_Abi::template __implicit_mask_n<_Np>());
else if constexpr (__have_avx512bw && _Np <= 32)
return _kandn_mask32(__x._M_data,
_Abi::template __implicit_mask_n<_Np>());
else if constexpr (__have_avx512bw && _Np <= 64)
return _kandn_mask64(__x._M_data,
_Abi::template __implicit_mask_n<_Np>());
else
__assert_unreachable<_Tp>();
}
else
return _Base::_S_bit_not(__x);
}
template <typename _Tp, size_t _Np>
_GLIBCXX_SIMD_INTRINSIC static constexpr _SimdWrapper<_Tp, _Np>
_S_bit_and(const _SimdWrapper<_Tp, _Np>& __x,
const _SimdWrapper<_Tp, _Np>& __y)
{
if constexpr (std::is_same_v<_Tp, bool>)
{
if constexpr (__have_avx512dq && _Np <= 8)
return _kand_mask8(__x._M_data, __y._M_data);
else if constexpr (_Np <= 16)
return _kand_mask16(__x._M_data, __y._M_data);
else if constexpr (__have_avx512bw && _Np <= 32)
return _kand_mask32(__x._M_data, __y._M_data);
else if constexpr (__have_avx512bw && _Np <= 64)
return _kand_mask64(__x._M_data, __y._M_data);
else
__assert_unreachable<_Tp>();
}
else
return _Base::_S_bit_and(__x, __y);
}
template <typename _Tp, size_t _Np>
_GLIBCXX_SIMD_INTRINSIC static constexpr _SimdWrapper<_Tp, _Np>
_S_bit_or(const _SimdWrapper<_Tp, _Np>& __x, const _SimdWrapper<_Tp, _Np>& __y)
{
if constexpr (std::is_same_v<_Tp, bool>)
{
if constexpr (__have_avx512dq && _Np <= 8)
return _kor_mask8(__x._M_data, __y._M_data);
else if constexpr (_Np <= 16)
return _kor_mask16(__x._M_data, __y._M_data);
else if constexpr (__have_avx512bw && _Np <= 32)
return _kor_mask32(__x._M_data, __y._M_data);
else if constexpr (__have_avx512bw && _Np <= 64)
return _kor_mask64(__x._M_data, __y._M_data);
else
__assert_unreachable<_Tp>();
}
else
return _Base::_S_bit_or(__x, __y);
}
template <typename _Tp, size_t _Np>
_GLIBCXX_SIMD_INTRINSIC static constexpr _SimdWrapper<_Tp, _Np>
_S_bit_xor(const _SimdWrapper<_Tp, _Np>& __x,
const _SimdWrapper<_Tp, _Np>& __y)
{
if constexpr (std::is_same_v<_Tp, bool>)
{
if constexpr (__have_avx512dq && _Np <= 8)
return _kxor_mask8(__x._M_data, __y._M_data);
else if constexpr (_Np <= 16)
return _kxor_mask16(__x._M_data, __y._M_data);
else if constexpr (__have_avx512bw && _Np <= 32)
return _kxor_mask32(__x._M_data, __y._M_data);
else if constexpr (__have_avx512bw && _Np <= 64)
return _kxor_mask64(__x._M_data, __y._M_data);
else
__assert_unreachable<_Tp>();
}
else
return _Base::_S_bit_xor(__x, __y);
}
template <size_t _Np>
_GLIBCXX_SIMD_INTRINSIC static void
_S_masked_assign(_SimdWrapper<bool, _Np> __k, _SimdWrapper<bool, _Np>& __lhs,
_SimdWrapper<bool, _Np> __rhs)
{
__lhs._M_data
= (~__k._M_data & __lhs._M_data) | (__k._M_data & __rhs._M_data);
}
template <size_t _Np>
_GLIBCXX_SIMD_INTRINSIC static void
_S_masked_assign(_SimdWrapper<bool, _Np> __k, _SimdWrapper<bool, _Np>& __lhs,
bool __rhs)
{
if (__rhs)
__lhs._M_data = __k._M_data | __lhs._M_data;
else
__lhs._M_data = ~__k._M_data & __lhs._M_data;
}
using _MaskImplBuiltin<_Abi>::_S_masked_assign;
template <typename _Tp>
_GLIBCXX_SIMD_INTRINSIC static bool _S_all_of(simd_mask<_Tp, _Abi> __k)
{
if constexpr (__is_sse_abi<_Abi>() || __is_avx_abi<_Abi>())
{
constexpr size_t _Np = simd_size_v<_Tp, _Abi>;
using _TI = __intrinsic_type_t<_Tp, _Np>;
const _TI __a = reinterpret_cast<_TI>(__to_intrin(__data(__k)));
if constexpr (__have_sse4_1)
{
_GLIBCXX_SIMD_USE_CONSTEXPR _TI __b
= _Abi::template _S_implicit_mask_intrin<_Tp>();
return 0 != __testc(__a, __b);
}
else if constexpr (std::is_same_v<_Tp, float>)
return (_mm_movemask_ps(__a) & ((1 << _Np) - 1)) == (1 << _Np) - 1;
else if constexpr (std::is_same_v<_Tp, double>)
return (_mm_movemask_pd(__a) & ((1 << _Np) - 1)) == (1 << _Np) - 1;
else
return (_mm_movemask_epi8(__a) & ((1 << (_Np * sizeof(_Tp))) - 1))
== (1 << (_Np * sizeof(_Tp))) - 1;
}
else if constexpr (__is_avx512_abi<_Abi>())
{
constexpr auto _Mask = _Abi::template _S_implicit_mask<_Tp>();
const auto __kk = __k._M_data._M_data;
if constexpr (sizeof(__kk) == 1)
{
if constexpr (__have_avx512dq)
return _kortestc_mask8_u8(__kk, _Mask == 0xff ? __kk
: __mmask8(~_Mask));
else
return _kortestc_mask16_u8(__kk, __mmask16(~_Mask));
}
else if constexpr (sizeof(__kk) == 2)
return _kortestc_mask16_u8(__kk, _Mask == 0xffff ? __kk
: __mmask16(~_Mask));
else if constexpr (sizeof(__kk) == 4 && __have_avx512bw)
return _kortestc_mask32_u8(__kk, _Mask == 0xffffffffU
? __kk
: __mmask32(~_Mask));
else if constexpr (sizeof(__kk) == 8 && __have_avx512bw)
return _kortestc_mask64_u8(__kk, _Mask == 0xffffffffffffffffULL
? __kk
: __mmask64(~_Mask));
else
__assert_unreachable<_Tp>();
}
}
template <typename _Tp>
_GLIBCXX_SIMD_INTRINSIC static bool _S_any_of(simd_mask<_Tp, _Abi> __k)
{
if constexpr (__is_sse_abi<_Abi>() || __is_avx_abi<_Abi>())
{
constexpr size_t _Np = simd_size_v<_Tp, _Abi>;
using _TI = __intrinsic_type_t<_Tp, _Np>;
const _TI __a = reinterpret_cast<_TI>(__to_intrin(__data(__k)));
if constexpr (__have_sse4_1)
{
if constexpr (_Abi::template _S_is_partial<_Tp> || sizeof(__k) < 16)
{
_GLIBCXX_SIMD_USE_CONSTEXPR _TI __b
= _Abi::template _S_implicit_mask_intrin<_Tp>();
return 0 == __testz(__a, __b);
}
else
return 0 == __testz(__a, __a);
}
else if constexpr (std::is_same_v<_Tp, float>)
return (_mm_movemask_ps(__a) & ((1 << _Np) - 1)) != 0;
else if constexpr (std::is_same_v<_Tp, double>)
return (_mm_movemask_pd(__a) & ((1 << _Np) - 1)) != 0;
else
return (_mm_movemask_epi8(__a) & ((1 << (_Np * sizeof(_Tp))) - 1))
!= 0;
}
else if constexpr (__is_avx512_abi<_Abi>())
return (__k._M_data._M_data & _Abi::template _S_implicit_mask<_Tp>()) != 0;
}
template <typename _Tp>
_GLIBCXX_SIMD_INTRINSIC static bool _S_none_of(simd_mask<_Tp, _Abi> __k)
{
if constexpr (__is_sse_abi<_Abi>() || __is_avx_abi<_Abi>())
{
constexpr size_t _Np = simd_size_v<_Tp, _Abi>;
using _TI = __intrinsic_type_t<_Tp, _Np>;
const _TI __a = reinterpret_cast<_TI>(__to_intrin(__data(__k)));
if constexpr (__have_sse4_1)
{
if constexpr (_Abi::template _S_is_partial<_Tp> || sizeof(__k) < 16)
{
_GLIBCXX_SIMD_USE_CONSTEXPR _TI __b
= _Abi::template _S_implicit_mask_intrin<_Tp>();
return 0 != __testz(__a, __b);
}
else
return 0 != __testz(__a, __a);
}
else if constexpr (std::is_same_v<_Tp, float>)
return (__movemask(__a) & ((1 << _Np) - 1)) == 0;
else if constexpr (std::is_same_v<_Tp, double>)
return (__movemask(__a) & ((1 << _Np) - 1)) == 0;
else
return (__movemask(__a) & int((1ull << (_Np * sizeof(_Tp))) - 1))
== 0;
}
else if constexpr (__is_avx512_abi<_Abi>())
return (__k._M_data._M_data & _Abi::template _S_implicit_mask<_Tp>()) == 0;
}
template <typename _Tp>
_GLIBCXX_SIMD_INTRINSIC static bool _S_some_of(simd_mask<_Tp, _Abi> __k)
{
if constexpr (__is_sse_abi<_Abi>() || __is_avx_abi<_Abi>())
{
constexpr size_t _Np = simd_size_v<_Tp, _Abi>;
using _TI = __intrinsic_type_t<_Tp, _Np>;
const _TI __a = reinterpret_cast<_TI>(__to_intrin(__data(__k)));
if constexpr (__have_sse4_1)
{
_GLIBCXX_SIMD_USE_CONSTEXPR _TI __b
= _Abi::template _S_implicit_mask_intrin<_Tp>();
return 0 != __testnzc(__a, __b);
}
else if constexpr (std::is_same_v<_Tp, float>)
{
constexpr int __allbits = (1 << _Np) - 1;
const auto __tmp = _mm_movemask_ps(__a) & __allbits;
return __tmp > 0 && __tmp < __allbits;
}
else if constexpr (std::is_same_v<_Tp, double>)
{
constexpr int __allbits = (1 << _Np) - 1;
const auto __tmp = _mm_movemask_pd(__a) & __allbits;
return __tmp > 0 && __tmp < __allbits;
}
else
{
constexpr int __allbits = (1 << (_Np * sizeof(_Tp))) - 1;
const auto __tmp = _mm_movemask_epi8(__a) & __allbits;
return __tmp > 0 && __tmp < __allbits;
}
}
else if constexpr (__is_avx512_abi<_Abi>())
return _S_any_of(__k) && !_S_all_of(__k);
else
__assert_unreachable<_Tp>();
}
template <typename _Tp>
_GLIBCXX_SIMD_INTRINSIC static int _S_popcount(simd_mask<_Tp, _Abi> __k)
{
constexpr size_t _Np = simd_size_v<_Tp, _Abi>;
const auto __kk = _Abi::_S_masked(__k._M_data)._M_data;
if constexpr (__is_avx512_abi<_Abi>())
{
if constexpr (_Np > 32)
return __builtin_popcountll(__kk);
else
return __builtin_popcount(__kk);
}
else
{
if constexpr (__have_popcnt)
{
int __bits = __movemask(__to_intrin(__vector_bitcast<_Tp>(__kk)));
const int __count = __builtin_popcount(__bits);
return std::is_integral_v<_Tp> ? __count / sizeof(_Tp) : __count;
}
else if constexpr (_Np == 2 && sizeof(_Tp) == 8)
{
const int mask = _mm_movemask_pd(__auto_bitcast(__kk));
return mask - (mask >> 1);
}
else if constexpr (_Np <= 4 && sizeof(_Tp) == 8)
{
auto __x = -(__lo128(__kk) + __hi128(__kk));
return __x[0] + __x[1];
}
else if constexpr (_Np <= 4 && sizeof(_Tp) == 4)
{
if constexpr (__have_sse2)
{
__m128i __x = __intrin_bitcast<__m128i>(__to_intrin(__kk));
__x = _mm_add_epi32(__x,
_mm_shuffle_epi32(__x,
_MM_SHUFFLE(0, 1, 2, 3)));
__x = _mm_add_epi32(
__x, _mm_shufflelo_epi16(__x, _MM_SHUFFLE(1, 0, 3, 2)));
return -_mm_cvtsi128_si32(__x);
}
else
return __builtin_popcount(_mm_movemask_ps(__auto_bitcast(__kk)));
}
else if constexpr (_Np <= 8 && sizeof(_Tp) == 2)
{
auto __x = __to_intrin(__kk);
__x
= _mm_add_epi16(__x,
_mm_shuffle_epi32(__x, _MM_SHUFFLE(0, 1, 2, 3)));
__x = _mm_add_epi16(__x,
_mm_shufflelo_epi16(__x,
_MM_SHUFFLE(0, 1, 2, 3)));
__x = _mm_add_epi16(__x,
_mm_shufflelo_epi16(__x,
_MM_SHUFFLE(2, 3, 0, 1)));
return -short(_mm_extract_epi16(__x, 0));
}
else if constexpr (_Np <= 16 && sizeof(_Tp) == 1)
{
auto __x = __to_intrin(__kk);
__x = _mm_add_epi8(__x,
_mm_shuffle_epi32(__x, _MM_SHUFFLE(0, 1, 2, 3)));
__x
= _mm_add_epi8(__x,
_mm_shufflelo_epi16(__x, _MM_SHUFFLE(0, 1, 2, 3)));
__x
= _mm_add_epi8(__x,
_mm_shufflelo_epi16(__x, _MM_SHUFFLE(2, 3, 0, 1)));
auto __y = -__vector_bitcast<_UChar>(__x);
if constexpr (__have_sse4_1)
return __y[0] + __y[1];
else
{
unsigned __z = _mm_extract_epi16(__to_intrin(__y), 0);
return (__z & 0xff) + (__z >> 8);
}
}
else if constexpr (sizeof(__kk) == 32)
{
using _I = __int_for_sizeof_t<_Tp>;
const auto __as_int = __vector_bitcast<_I>(__kk);
_MaskImplX86<simd_abi::__sse>::_S_popcount(
simd_mask<_I, simd_abi::__sse>(__private_init,
__lo128(__as_int)
+ __hi128(__as_int)));
}
else
__assert_unreachable<_Tp>();
}
}
template <typename _Tp>
_GLIBCXX_SIMD_INTRINSIC static int _S_find_first_set(simd_mask<_Tp, _Abi> __k)
{
if constexpr (__is_avx512_abi<_Abi>())
if constexpr (_S_size<_Tp> <= 32)
return _tzcnt_u32(__k._M_data._M_data);
else
return _BitOps::_S_firstbit(__k._M_data._M_data);
else
return _Base::_S_find_first_set(__k);
}
template <typename _Tp>
_GLIBCXX_SIMD_INTRINSIC static int _S_find_last_set(simd_mask<_Tp, _Abi> __k)
{
if constexpr (__is_avx512_abi<_Abi>())
if constexpr (_S_size<_Tp> <= 32)
return 31 - _lzcnt_u32(__k._M_data._M_data);
else
return _BitOps::_S_lastbit(__k._M_data._M_data);
else
return _Base::_S_find_last_set(__k);
}
};
_GLIBCXX_SIMD_END_NAMESPACE
#endif
#endif
#elif _GLIBCXX_SIMD_HAVE_NEON
#ifndef _GLIBCXX_EXPERIMENTAL_SIMD_NEON_H_
#define _GLIBCXX_EXPERIMENTAL_SIMD_NEON_H_ 
#if __cplusplus >= 201703L
#if !_GLIBCXX_SIMD_HAVE_NEON
#error "simd_neon.h may only be included when NEON on ARM is available"
#endif
_GLIBCXX_SIMD_BEGIN_NAMESPACE
struct _CommonImplNeon : _CommonImplBuiltin
{
using _CommonImplBuiltin::_S_store;
};
template <typename _Abi> struct _SimdImplNeon : _SimdImplBuiltin<_Abi>
{
using _Base = _SimdImplBuiltin<_Abi>;
template <typename _Tp>
using _MaskMember = typename _Base::template _MaskMember<_Tp>;
template <typename _Tp> static constexpr size_t _S_max_store_size = 16;
template <typename _Tp, size_t _Np, typename _Up>
static inline _SimdWrapper<_Tp, _Np>
_S_masked_load(_SimdWrapper<_Tp, _Np> __merge, _MaskMember<_Tp> __k,
const _Up* __mem) noexcept
{
__execute_n_times<_Np>([&](auto __i) {
if (__k[__i] != 0)
__merge._M_set(__i, static_cast<_Tp>(__mem[__i]));
});
return __merge;
}
template <typename _Tp, std::size_t _Np>
_GLIBCXX_SIMD_INTRINSIC static void
_S_masked_store_nocvt(_SimdWrapper<_Tp, _Np> __v, _Tp* __mem,
_MaskMember<_Tp> __k)
{
__execute_n_times<_Np>([&](auto __i) {
if (__k[__i] != 0)
__mem[__i] = __v[__i];
});
}
template <typename _Tp, typename _BinaryOperation>
_GLIBCXX_SIMD_INTRINSIC static _Tp _S_reduce(simd<_Tp, _Abi> __x,
_BinaryOperation&& __binary_op)
{
constexpr size_t _Np = __x.size();
if constexpr (sizeof(__x) == 16 && _Np >= 4
&& !_Abi::template _S_is_partial<_Tp>)
{
const auto __halves = split<simd<_Tp, simd_abi::_Neon<8>>>(__x);
const auto __y = __binary_op(__halves[0], __halves[1]);
return _SimdImplNeon<simd_abi::_Neon<8>>::_S_reduce(
__y, static_cast<_BinaryOperation&&>(__binary_op));
}
else if constexpr (_Np == 8)
{
__x = __binary_op(__x, _Base::template _M_make_simd<_Tp, _Np>(
__vector_permute<1, 0, 3, 2, 5, 4, 7, 6>(
__x._M_data)));
__x = __binary_op(__x, _Base::template _M_make_simd<_Tp, _Np>(
__vector_permute<3, 2, 1, 0, 7, 6, 5, 4>(
__x._M_data)));
__x = __binary_op(__x, _Base::template _M_make_simd<_Tp, _Np>(
__vector_permute<7, 6, 5, 4, 3, 2, 1, 0>(
__x._M_data)));
return __x[0];
}
else if constexpr (_Np == 4)
{
__x = __binary_op(__x, _Base::template _M_make_simd<_Tp, _Np>(
__vector_permute<1, 0, 3, 2>(__x._M_data)));
__x = __binary_op(__x, _Base::template _M_make_simd<_Tp, _Np>(
__vector_permute<3, 2, 1, 0>(__x._M_data)));
return __x[0];
}
else if constexpr (_Np == 2)
{
__x = __binary_op(__x, _Base::template _M_make_simd<_Tp, _Np>(
__vector_permute<1, 0>(__x._M_data)));
return __x[0];
}
else
return _Base::_S_reduce(__x,
static_cast<_BinaryOperation&&>(__binary_op));
}
template <typename _Tp, typename _TVT = _VectorTraits<_Tp>>
_GLIBCXX_SIMD_INTRINSIC static _Tp _S_sqrt(_Tp __x)
{
if constexpr (__have_neon_a64)
{
const auto __intrin = __to_intrin(__x);
if constexpr (_TVT::template _S_is<float, 2>)
return vsqrt_f32(__intrin);
else if constexpr (_TVT::template _S_is<float, 4>)
return vsqrtq_f32(__intrin);
else if constexpr (_TVT::template _S_is<double, 1>)
return vsqrt_f64(__intrin);
else if constexpr (_TVT::template _S_is<double, 2>)
return vsqrtq_f64(__intrin);
else
__assert_unreachable<_Tp>();
}
else
return _Base::_S_sqrt(__x);
}
template <typename _TW, typename _TVT = _VectorTraits<_TW>>
_GLIBCXX_SIMD_INTRINSIC static _TW _S_trunc(_TW __x)
{
using _Tp = typename _TVT::value_type;
if constexpr (__have_neon_a32)
{
const auto __intrin = __to_intrin(__x);
if constexpr (_TVT::template _S_is<float, 2>)
return vrnd_f32(__intrin);
else if constexpr (_TVT::template _S_is<float, 4>)
return vrndq_f32(__intrin);
else if constexpr (_TVT::template _S_is<double, 1>)
return vrnd_f64(__intrin);
else if constexpr (_TVT::template _S_is<double, 2>)
return vrndq_f64(__intrin);
else
__assert_unreachable<_Tp>();
}
else if constexpr (is_same_v<_Tp, float>)
{
auto __intrin = __to_intrin(__x);
if constexpr (sizeof(__x) == 16)
__intrin = vcvtq_f32_s32(vcvtq_s32_f32(__intrin));
else
__intrin = vcvt_f32_s32(vcvt_s32_f32(__intrin));
return _Base::_S_abs(__x)._M_data < 0x1p23f
? __vector_bitcast<float>(__intrin)
: __x._M_data;
}
else
return _Base::_S_trunc(__x);
}
template <typename _Tp, size_t _Np>
_GLIBCXX_SIMD_INTRINSIC static _SimdWrapper<_Tp, _Np>
_S_round(_SimdWrapper<_Tp, _Np> __x)
{
if constexpr (__have_neon_a32)
{
const auto __intrin = __to_intrin(__x);
if constexpr (sizeof(_Tp) == 4 && sizeof(__x) == 8)
return vrnda_f32(__intrin);
else if constexpr (sizeof(_Tp) == 4 && sizeof(__x) == 16)
return vrndaq_f32(__intrin);
else if constexpr (sizeof(_Tp) == 8 && sizeof(__x) == 8)
return vrnda_f64(__intrin);
else if constexpr (sizeof(_Tp) == 8 && sizeof(__x) == 16)
return vrndaq_f64(__intrin);
else
__assert_unreachable<_Tp>();
}
else
return _Base::_S_round(__x);
}
template <typename _Tp, typename _TVT = _VectorTraits<_Tp>>
_GLIBCXX_SIMD_INTRINSIC static _Tp _S_floor(_Tp __x)
{
if constexpr (__have_neon_a32)
{
const auto __intrin = __to_intrin(__x);
if constexpr (_TVT::template _S_is<float, 2>)
return vrndm_f32(__intrin);
else if constexpr (_TVT::template _S_is<float, 4>)
return vrndmq_f32(__intrin);
else if constexpr (_TVT::template _S_is<double, 1>)
return vrndm_f64(__intrin);
else if constexpr (_TVT::template _S_is<double, 2>)
return vrndmq_f64(__intrin);
else
__assert_unreachable<_Tp>();
}
else
return _Base::_S_floor(__x);
}
template <typename _Tp, typename _TVT = _VectorTraits<_Tp>>
_GLIBCXX_SIMD_INTRINSIC static _Tp _S_ceil(_Tp __x)
{
if constexpr (__have_neon_a32)
{
const auto __intrin = __to_intrin(__x);
if constexpr (_TVT::template _S_is<float, 2>)
return vrndp_f32(__intrin);
else if constexpr (_TVT::template _S_is<float, 4>)
return vrndpq_f32(__intrin);
else if constexpr (_TVT::template _S_is<double, 1>)
return vrndp_f64(__intrin);
else if constexpr (_TVT::template _S_is<double, 2>)
return vrndpq_f64(__intrin);
else
__assert_unreachable<_Tp>();
}
else
return _Base::_S_ceil(__x);
}
};
struct _MaskImplNeonMixin
{
using _Base = _MaskImplBuiltinMixin;
template <typename _Tp, size_t _Np>
_GLIBCXX_SIMD_INTRINSIC static constexpr _SanitizedBitMask<_Np>
_S_to_bits(_SimdWrapper<_Tp, _Np> __x)
{
if (__builtin_is_constant_evaluated())
return _Base::_S_to_bits(__x);
using _I = __int_for_sizeof_t<_Tp>;
if constexpr (sizeof(__x) == 16)
{
auto __asint = __vector_bitcast<_I>(__x);
#ifdef __aarch64__
[[maybe_unused]] constexpr auto __zero = decltype(__asint)();
#else
[[maybe_unused]] constexpr auto __zero = decltype(__lo64(__asint))();
#endif
if constexpr (sizeof(_Tp) == 1)
{
constexpr auto __bitsel
= __generate_from_n_evaluations<16, __vector_type_t<_I, 16>>(
[&](auto __i) {
return static_cast<_I>(
__i < _Np ? (__i < 8 ? 1 << __i : 1 << (__i - 8)) : 0);
});
__asint &= __bitsel;
#ifdef __aarch64__
return __vector_bitcast<_UShort>(
vpaddq_s8(vpaddq_s8(vpaddq_s8(__asint, __zero), __zero),
__zero))[0];
#else
return __vector_bitcast<_UShort>(
vpadd_s8(vpadd_s8(vpadd_s8(__lo64(__asint), __hi64(__asint)),
__zero),
__zero))[0];
#endif
}
else if constexpr (sizeof(_Tp) == 2)
{
constexpr auto __bitsel
= __generate_from_n_evaluations<8, __vector_type_t<_I, 8>>(
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
constexpr auto __bitsel
= __generate_from_n_evaluations<4, __vector_type_t<_I, 4>>(
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
return (__asint[0] & 1) | (__asint[1] & 2);
else
__assert_unreachable<_Tp>();
}
else if constexpr (sizeof(__x) == 8)
{
auto __asint = __vector_bitcast<_I>(__x);
[[maybe_unused]] constexpr auto __zero = decltype(__asint)();
if constexpr (sizeof(_Tp) == 1)
{
constexpr auto __bitsel
= __generate_from_n_evaluations<8, __vector_type_t<_I, 8>>(
[&](auto __i) {
return static_cast<_I>(__i < _Np ? 1 << __i : 0);
});
__asint &= __bitsel;
return vpadd_s8(vpadd_s8(vpadd_s8(__asint, __zero), __zero),
__zero)[0];
}
else if constexpr (sizeof(_Tp) == 2)
{
constexpr auto __bitsel
= __generate_from_n_evaluations<4, __vector_type_t<_I, 4>>(
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
return _Base::_S_to_bits(__x);
}
};
template <typename _Abi>
struct _MaskImplNeon : _MaskImplNeonMixin, _MaskImplBuiltin<_Abi>
{
using _MaskImplBuiltinMixin::_S_to_maskvector;
using _MaskImplNeonMixin::_S_to_bits;
using _Base = _MaskImplBuiltin<_Abi>;
using _Base::_S_convert;
template <typename _Tp>
_GLIBCXX_SIMD_INTRINSIC static bool _S_all_of(simd_mask<_Tp, _Abi> __k)
{
const auto __kk
= __vector_bitcast<char>(__k._M_data)
| ~__vector_bitcast<char>(_Abi::template _S_implicit_mask<_Tp>());
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
template <typename _Tp>
_GLIBCXX_SIMD_INTRINSIC static bool _S_any_of(simd_mask<_Tp, _Abi> __k)
{
const auto __kk
= __vector_bitcast<char>(__k._M_data)
| ~__vector_bitcast<char>(_Abi::template _S_implicit_mask<_Tp>());
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
template <typename _Tp>
_GLIBCXX_SIMD_INTRINSIC static bool _S_none_of(simd_mask<_Tp, _Abi> __k)
{
const auto __kk = _Abi::_S_masked(__k._M_data);
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
template <typename _Tp>
_GLIBCXX_SIMD_INTRINSIC static bool _S_some_of(simd_mask<_Tp, _Abi> __k)
{
if constexpr (sizeof(__k) <= 8)
{
const auto __kk
= __vector_bitcast<char>(__k._M_data)
| ~__vector_bitcast<char>(_Abi::template _S_implicit_mask<_Tp>());
using _Up = std::make_unsigned_t<__int_for_sizeof_t<decltype(__kk)>>;
return __bit_cast<_Up>(__kk) + 1 > 1;
}
else
return _Base::_S_some_of(__k);
}
template <typename _Tp>
_GLIBCXX_SIMD_INTRINSIC static int _S_popcount(simd_mask<_Tp, _Abi> __k)
{
if constexpr (sizeof(_Tp) == 1)
{
const auto __s8 = __vector_bitcast<_SChar>(__k._M_data);
int8x8_t __tmp = __lo64(__s8) + __hi64z(__s8);
return -vpadd_s8(vpadd_s8(vpadd_s8(__tmp, int8x8_t()), int8x8_t()),
int8x8_t())[0];
}
else if constexpr (sizeof(_Tp) == 2)
{
const auto __s16 = __vector_bitcast<short>(__k._M_data);
int16x4_t __tmp = __lo64(__s16) + __hi64z(__s16);
return -vpadd_s16(vpadd_s16(__tmp, int16x4_t()), int16x4_t())[0];
}
else if constexpr (sizeof(_Tp) == 4)
{
const auto __s32 = __vector_bitcast<int>(__k._M_data);
int32x2_t __tmp = __lo64(__s32) + __hi64z(__s32);
return -vpadd_s32(__tmp, int32x2_t())[0];
}
else if constexpr (sizeof(_Tp) == 8)
{
static_assert(sizeof(__k) == 16);
const auto __s64 = __vector_bitcast<long>(__k._M_data);
return -(__s64[0] + __s64[1]);
}
}
template <typename _Tp>
_GLIBCXX_SIMD_INTRINSIC static int _S_find_first_set(simd_mask<_Tp, _Abi> __k)
{
return _Base::_S_find_first_set(__k);
}
template <typename _Tp>
_GLIBCXX_SIMD_INTRINSIC static int _S_find_last_set(simd_mask<_Tp, _Abi> __k)
{
return _Base::_S_find_last_set(__k);
}
};
_GLIBCXX_SIMD_END_NAMESPACE
#endif
#endif
#elif __ALTIVEC__
#ifndef _GLIBCXX_EXPERIMENTAL_SIMD_PPC_H_
#define _GLIBCXX_EXPERIMENTAL_SIMD_PPC_H_ 
#if __cplusplus >= 201703L
#ifndef __ALTIVEC__
#error "simd_ppc.h may only be included when AltiVec/VMX is available"
#endif
_GLIBCXX_SIMD_BEGIN_NAMESPACE
template <typename _Abi> struct _SimdImplPpc : _SimdImplBuiltin<_Abi>
{
using _Base = _SimdImplBuiltin<_Abi>;
template <typename _Tp, size_t _Np>
_GLIBCXX_SIMD_INTRINSIC static constexpr _SimdWrapper<_Tp, _Np>
_S_bit_shift_left(_SimdWrapper<_Tp, _Np> __x, _SimdWrapper<_Tp, _Np> __y)
{
__x = _Base::_S_bit_shift_left(__x, __y);
if constexpr (sizeof(_Tp) < sizeof(int))
__x._M_data = (__y._M_data < sizeof(_Tp) * __CHAR_BIT__) & __x._M_data;
return __x;
}
template <typename _Tp, size_t _Np>
_GLIBCXX_SIMD_INTRINSIC static constexpr _SimdWrapper<_Tp, _Np>
_S_bit_shift_left(_SimdWrapper<_Tp, _Np> __x, int __y)
{
__x = _Base::_S_bit_shift_left(__x, __y);
if constexpr (sizeof(_Tp) < sizeof(int))
{
if (__y >= sizeof(_Tp) * __CHAR_BIT__)
return {};
}
return __x;
}
template <typename _Tp, size_t _Np>
_GLIBCXX_SIMD_INTRINSIC static constexpr _SimdWrapper<_Tp, _Np>
_S_bit_shift_right(_SimdWrapper<_Tp, _Np> __x, _SimdWrapper<_Tp, _Np> __y)
{
if constexpr (sizeof(_Tp) < sizeof(int))
{
constexpr int __nbits = sizeof(_Tp) * __CHAR_BIT__;
if constexpr (std::is_unsigned_v<_Tp>)
return (__y._M_data < __nbits)
& _Base::_S_bit_shift_right(__x, __y)._M_data;
else
{
_Base::_S_masked_assign(_SimdWrapper<_Tp, _Np>(__y._M_data
>= __nbits),
__y, __nbits - 1);
return _Base::_S_bit_shift_right(__x, __y);
}
}
else
return _Base::_S_bit_shift_right(__x, __y);
}
template <typename _Tp, size_t _Np>
_GLIBCXX_SIMD_INTRINSIC static constexpr _SimdWrapper<_Tp, _Np>
_S_bit_shift_right(_SimdWrapper<_Tp, _Np> __x, int __y)
{
if constexpr (sizeof(_Tp) < sizeof(int))
{
constexpr int __nbits = sizeof(_Tp) * __CHAR_BIT__;
if (__y >= __nbits)
{
if constexpr (std::is_unsigned_v<_Tp>)
return {};
else
return _Base::_S_bit_shift_right(__x, __nbits - 1);
}
}
return _Base::_S_bit_shift_right(__x, __y);
}
};
_GLIBCXX_SIMD_END_NAMESPACE
#endif
#endif
#endif
#ifndef _GLIBCXX_EXPERIMENTAL_SIMD_MATH_H_
#define _GLIBCXX_EXPERIMENTAL_SIMD_MATH_H_ 
#if __cplusplus >= 201703L
#include <utility>
#include <iomanip>
_GLIBCXX_SIMD_BEGIN_NAMESPACE
template <typename _Tp, typename _V>
using __samesize = fixed_size_simd<_Tp, _V::size()>;
template <typename _DoubleR, typename _Tp, typename _Abi>
struct __math_return_type;
template <typename _DoubleR, typename _Tp, typename _Abi>
using __math_return_type_t =
typename __math_return_type<_DoubleR, _Tp, _Abi>::type;
template <typename _Tp, typename _Abi>
struct __math_return_type<double, _Tp, _Abi>
{
using type = std::experimental::simd<_Tp, _Abi>;
};
template <typename _Tp, typename _Abi>
struct __math_return_type<bool, _Tp, _Abi>
{
using type = std::experimental::simd_mask<_Tp, _Abi>;
};
template <typename _DoubleR, typename _Tp, typename _Abi>
struct __math_return_type
{
using type
= std::experimental::fixed_size_simd<_DoubleR, simd_size_v<_Tp, _Abi>>;
};
#define _GLIBCXX_SIMD_MATH_CALL_(__name) \
template <typename _Tp, typename _Abi, typename..., \
typename _R = std::experimental::__math_return_type_t< \
decltype(std::__name(std::declval<double>())), _Tp, _Abi>> \
enable_if_t<std::is_floating_point_v<_Tp>, _R> __name( \
std::experimental::simd<_Tp, _Abi> __x) \
{ \
return {std::experimental::__private_init, \
_Abi::_SimdImpl::_S_##__name(std::experimental::__data(__x))}; \
}
template <typename _Up, typename _Tp, typename _Abi>
struct __extra_argument_type;
template <typename _Tp, typename _Abi>
struct __extra_argument_type<_Tp*, _Tp, _Abi>
{
using type = std::experimental::simd<_Tp, _Abi>*;
static constexpr double* declval();
_GLIBCXX_SIMD_INTRINSIC static constexpr auto __data(type __x)
{
return &std::experimental::__data(*__x);
}
static constexpr bool __needs_temporary_scalar = true;
};
template <typename _Up, typename _Tp, typename _Abi>
struct __extra_argument_type<_Up*, _Tp, _Abi>
{
static_assert(std::is_integral_v<_Up>);
using type = std::experimental::fixed_size_simd<
_Up, std::experimental::simd_size_v<_Tp, _Abi>>*;
static constexpr _Up* declval();
_GLIBCXX_SIMD_INTRINSIC static constexpr auto __data(type __x)
{
return &std::experimental::__data(*__x);
}
static constexpr bool __needs_temporary_scalar = true;
};
template <typename _Tp, typename _Abi>
struct __extra_argument_type<_Tp, _Tp, _Abi>
{
using type = std::experimental::simd<_Tp, _Abi>;
static constexpr double declval();
_GLIBCXX_SIMD_INTRINSIC static constexpr decltype(auto)
__data(const type& __x)
{
return std::experimental::__data(__x);
}
static constexpr bool __needs_temporary_scalar = false;
};
template <typename _Up, typename _Tp, typename _Abi>
struct __extra_argument_type
{
static_assert(std::is_integral_v<_Up>);
using type = std::experimental::fixed_size_simd<
_Up, std::experimental::simd_size_v<_Tp, _Abi>>;
static constexpr _Up declval();
_GLIBCXX_SIMD_INTRINSIC static constexpr decltype(auto)
__data(const type& __x)
{
return std::experimental::__data(__x);
}
static constexpr bool __needs_temporary_scalar = false;
};
#define _GLIBCXX_SIMD_MATH_CALL2_(__name,arg2_) \
template <typename _Tp, typename _Abi, typename..., \
typename _Arg2 \
= std::experimental::__extra_argument_type<arg2_, _Tp, _Abi>, \
typename _R = std::experimental::__math_return_type_t< \
decltype(std::__name(std::declval<double>(), _Arg2::declval())), \
_Tp, _Abi>> \
enable_if_t<std::is_floating_point_v<_Tp>, _R> __name( \
const std::experimental::simd<_Tp, _Abi>& __x, \
const typename _Arg2::type& __y) \
{ \
return {std::experimental::__private_init, \
_Abi::_SimdImpl::_S_##__name(std::experimental::__data(__x), \
_Arg2::__data(__y))}; \
} \
template <typename _Up, typename _Tp, typename _Abi> \
_GLIBCXX_SIMD_INTRINSIC std::experimental::__math_return_type_t< \
decltype(std::__name( \
std::declval<double>(), \
std::declval<enable_if_t< \
std::conjunction_v< \
std::is_same<arg2_, _Tp>, \
std::negation<std::is_same<__remove_cvref_t<_Up>, \
std::experimental::simd<_Tp, _Abi>>>, \
std::is_convertible<_Up, std::experimental::simd<_Tp, _Abi>>, \
std::is_floating_point<_Tp>>, \
double>>())), \
_Tp, _Abi> \
__name(_Up&& __xx, const std::experimental::simd<_Tp, _Abi>& __yy) \
{ \
return std::experimental::__name(std::experimental::simd<_Tp, _Abi>( \
static_cast<_Up&&>(__xx)), \
__yy); \
}
#define _GLIBCXX_SIMD_MATH_CALL3_(__name,arg2_,arg3_) \
template <typename _Tp, typename _Abi, typename..., \
typename _Arg2 \
= std::experimental::__extra_argument_type<arg2_, _Tp, _Abi>, \
typename _Arg3 \
= std::experimental::__extra_argument_type<arg3_, _Tp, _Abi>, \
typename _R = std::experimental::__math_return_type_t< \
decltype(std::__name(std::declval<double>(), _Arg2::declval(), \
_Arg3::declval())), \
_Tp, _Abi>> \
enable_if_t<std::is_floating_point_v<_Tp>, _R> __name( \
std::experimental::simd<_Tp, _Abi> __x, typename _Arg2::type __y, \
typename _Arg3::type __z) \
{ \
return {std::experimental::__private_init, \
_Abi::_SimdImpl::_S_##__name(std::experimental::__data(__x), \
_Arg2::__data(__y), \
_Arg3::__data(__z))}; \
} \
template <typename _Tp, typename _Up, typename _V, typename..., \
typename _TT = __remove_cvref_t<_Tp>, \
typename _UU = __remove_cvref_t<_Up>, \
typename _VV = __remove_cvref_t<_V>, \
typename _Simd \
= std::conditional_t<std::experimental::is_simd_v<_UU>, _UU, _VV>> \
_GLIBCXX_SIMD_INTRINSIC decltype( \
std::experimental::__name(_Simd(std::declval<_Tp>()), \
_Simd(std::declval<_Up>()), \
_Simd(std::declval<_V>()))) \
__name(_Tp&& __xx, _Up&& __yy, _V&& __zz) \
{ \
return std::experimental::__name(_Simd(static_cast<_Tp&&>(__xx)), \
_Simd(static_cast<_Up&&>(__yy)), \
_Simd(static_cast<_V&&>(__zz))); \
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
_GLIBCXX_SIMD_INTRINSIC simd<_Tp, _Abi>
__zero_low_bits(simd<_Tp, _Abi> __x)
{
const simd<_Tp, _Abi> __bitmask = __bit_cast<_Tp>(
~std::make_unsigned_t<__int_for_sizeof_t<_Tp>>() << _Bits);
return {__private_init,
_Abi::_SimdImpl::_S_bit_and(__data(__x), __data(__bitmask))};
}
template <typename _Tp, typename _Abi> struct __folded
{
simd<_Tp, _Abi> _M_x;
rebind_simd_t<int, simd<_Tp, _Abi>> _M_quadrant;
};
namespace __math_float {
inline constexpr float __pi_over_4 = 0x1.921FB6p-1f;
inline constexpr float __2_over_pi = 0x1.45F306p-1f;
inline constexpr float __pi_2_5bits0
= 0x1.921fc0p0f;
inline constexpr float __pi_2_5bits0_rem
= -0x1.5777a6p-21f;
}
namespace __math_double {
inline constexpr double __pi_over_4 = 0x1.921fb54442d18p-1;
inline constexpr double __2_over_pi = 0x1.45F306DC9C883p-1;
inline constexpr double __pi_2 = 0x1.921fb54442d18p0;
}
template <typename _Abi>
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
__r._M_quadrant = 0;
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
if (_GLIBCXX_SIMD_IS_UNLIKELY(all_of(__r._M_x < __pi_over_4)))
{
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
__r._M_x = __r._M_x - __y_hi * __pi_2_1
- max(__y_hi * __pi_2_2, __y_lo * __pi_2_1)
- min(__y_hi * __pi_2_2, __y_lo * __pi_2_1)
- max(__y_hi * __pi_2_3, __y_lo * __pi_2_2)
- min(__y_hi * __pi_2_3, __y_lo * __pi_2_2)
- max(__y * __pi_2_4, __y_lo * __pi_2_3)
- min(__y * __pi_2_4, __y_lo * __pi_2_3);
}
return __r;
}
template <typename _Tp, typename _Abi>
rebind_simd_t<int, simd<_Tp, _Abi>>
__extract_exponent_as_int(const simd<_Tp, _Abi>& __v)
{
using _Vp = simd<_Tp, _Abi>;
using _Up = make_unsigned_t<__int_for_sizeof_t<_Tp>>;
using namespace std::experimental::__float_bitwise_operators;
const _Vp __exponent_mask
= __infinity_v<_Tp>;
return static_simd_cast<rebind_simd_t<int, _Vp>>(
__bit_cast<rebind_simd_t<_Up, _Vp>>(__v & __exponent_mask)
>> (__digits_v<_Tp> - 1));
}
template <typename ImplFun, typename FallbackFun, typename... _Args>
_GLIBCXX_SIMD_INTRINSIC auto
__impl_or_fallback_dispatch(int, ImplFun&& __impl_fun, FallbackFun&&,
_Args&&... __args)
-> decltype(__impl_fun(static_cast<_Args&&>(__args)...))
{
return __impl_fun(static_cast<_Args&&>(__args)...);
}
template <typename ImplFun, typename FallbackFun, typename... _Args>
inline auto
__impl_or_fallback_dispatch(float, ImplFun&&, FallbackFun&& __fallback_fun,
_Args&&... __args)
-> decltype(__fallback_fun(static_cast<_Args&&>(__args)...))
{
return __fallback_fun(static_cast<_Args&&>(__args)...);
}
template <typename... _Args>
_GLIBCXX_SIMD_INTRINSIC auto
__impl_or_fallback(_Args&&... __args)
{
return __impl_or_fallback_dispatch(int(), static_cast<_Args&&>(__args)...);
}
_GLIBCXX_SIMD_MATH_CALL_(acos)
_GLIBCXX_SIMD_MATH_CALL_(asin)
_GLIBCXX_SIMD_MATH_CALL_(atan)
_GLIBCXX_SIMD_MATH_CALL2_(atan2, _Tp)
template <typename _Tp, typename _Abi>
enable_if_t<std::is_floating_point_v<_Tp>, simd<_Tp, _Abi>>
cos(const simd<_Tp, _Abi>& __x)
{
using _V = simd<_Tp, _Abi>;
if constexpr (__is_scalar_abi<_Abi>() || __is_fixed_size_abi_v<_Abi>)
return {__private_init, _Abi::_SimdImpl::_S_cos(__data(__x))};
else
{
if constexpr (is_same_v<_Tp, float>)
if (_GLIBCXX_SIMD_IS_UNLIKELY(any_of(abs(__x) >= 393382)))
return static_simd_cast<_V>(
cos(static_simd_cast<rebind_simd_t<double, _V>>(__x)));
const auto __f = __fold_input(__x);
using namespace std::experimental::__float_bitwise_operators;
const _V __sign_flip
= _V(-0.f) & static_simd_cast<_V>((1 + __f._M_quadrant) << 30);
const auto __need_cos = (__f._M_quadrant & 1) == 0;
if (_GLIBCXX_SIMD_IS_UNLIKELY(all_of(__need_cos)))
return __sign_flip ^ __cosSeries(__f._M_x);
else if (_GLIBCXX_SIMD_IS_UNLIKELY(none_of(__need_cos)))
return __sign_flip ^ __sinSeries(__f._M_x);
else
{
_V __r = __sinSeries(__f._M_x);
where(__need_cos.__cvt(), __r) = __cosSeries(__f._M_x);
return __r ^ __sign_flip;
}
}
}
template <typename _Tp>
_GLIBCXX_SIMD_ALWAYS_INLINE
enable_if_t<std::is_floating_point<_Tp>::value, simd<_Tp, simd_abi::scalar>>
cos(simd<_Tp, simd_abi::scalar> __x)
{
return std::cos(__data(__x));
}
template <typename _Tp, typename _Abi>
enable_if_t<std::is_floating_point_v<_Tp>, simd<_Tp, _Abi>>
sin(const simd<_Tp, _Abi>& __x)
{
using _V = simd<_Tp, _Abi>;
if constexpr (__is_scalar_abi<_Abi>() || __is_fixed_size_abi_v<_Abi>)
return {__private_init, _Abi::_SimdImpl::_S_sin(__data(__x))};
else
{
if constexpr (is_same_v<_Tp, float>)
if (_GLIBCXX_SIMD_IS_UNLIKELY(any_of(abs(__x) >= 527449)))
return static_simd_cast<_V>(
sin(static_simd_cast<rebind_simd_t<double, _V>>(__x)));
const auto __f = __fold_input(__x);
using namespace std::experimental::__float_bitwise_operators;
const auto __sign_flip
= (__x ^ static_simd_cast<_V>(1 - __f._M_quadrant)) & _V(_Tp(-0.));
const auto __need_sin = (__f._M_quadrant & 1) == 0;
if (_GLIBCXX_SIMD_IS_UNLIKELY(all_of(__need_sin)))
return __sign_flip ^ __sinSeries(__f._M_x);
else if (_GLIBCXX_SIMD_IS_UNLIKELY(none_of(__need_sin)))
return __sign_flip ^ __cosSeries(__f._M_x);
else
{
_V __r = __cosSeries(__f._M_x);
where(__need_sin.__cvt(), __r) = __sinSeries(__f._M_x);
return __sign_flip ^ __r;
}
}
}
template <typename _Tp>
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
#if _GLIBCXX_SIMD_X86INTRIN
template <typename _Tp, size_t _Np>
_SimdWrapper<_Tp, _Np>
__getexp(_SimdWrapper<_Tp, _Np> __x)
{
if constexpr (__have_avx512vl && __is_sse_ps<_Tp, _Np>())
return __auto_bitcast(_mm_getexp_ps(__to_intrin(__x)));
else if constexpr (__have_avx512f && __is_sse_ps<_Tp, _Np>())
return __auto_bitcast(_mm512_getexp_ps(__auto_bitcast(__to_intrin(__x))));
else if constexpr (__have_avx512vl && __is_sse_pd<_Tp, _Np>())
return _mm_getexp_pd(__x);
else if constexpr (__have_avx512f && __is_sse_pd<_Tp, _Np>())
return __lo128(_mm512_getexp_pd(__auto_bitcast(__x)));
else if constexpr (__have_avx512vl && __is_avx_ps<_Tp, _Np>())
return _mm256_getexp_ps(__x);
else if constexpr (__have_avx512f && __is_avx_ps<_Tp, _Np>())
return __lo256(_mm512_getexp_ps(__auto_bitcast(__x)));
else if constexpr (__have_avx512vl && __is_avx_pd<_Tp, _Np>())
return _mm256_getexp_pd(__x);
else if constexpr (__have_avx512f && __is_avx_pd<_Tp, _Np>())
return __lo256(_mm512_getexp_pd(__auto_bitcast(__x)));
else if constexpr (__is_avx512_ps<_Tp, _Np>())
return _mm512_getexp_ps(__x);
else if constexpr (__is_avx512_pd<_Tp, _Np>())
return _mm512_getexp_pd(__x);
else
__assert_unreachable<_Tp>();
}
template <typename _Tp, size_t _Np>
_SimdWrapper<_Tp, _Np>
__getmant_avx512(_SimdWrapper<_Tp, _Np> __x)
{
if constexpr (__have_avx512vl && __is_sse_ps<_Tp, _Np>())
return __auto_bitcast(
_mm_getmant_ps(__to_intrin(__x), _MM_MANT_NORM_p5_1, _MM_MANT_SIGN_src));
else if constexpr (__have_avx512f && __is_sse_ps<_Tp, _Np>())
return __auto_bitcast(_mm512_getmant_ps(__auto_bitcast(__to_intrin(__x)),
_MM_MANT_NORM_p5_1,
_MM_MANT_SIGN_src));
else if constexpr (__have_avx512vl && __is_sse_pd<_Tp, _Np>())
return _mm_getmant_pd(__x, _MM_MANT_NORM_p5_1, _MM_MANT_SIGN_src);
else if constexpr (__have_avx512f && __is_sse_pd<_Tp, _Np>())
return __lo128(_mm512_getmant_pd(__auto_bitcast(__x), _MM_MANT_NORM_p5_1,
_MM_MANT_SIGN_src));
else if constexpr (__have_avx512vl && __is_avx_ps<_Tp, _Np>())
return _mm256_getmant_ps(__x, _MM_MANT_NORM_p5_1, _MM_MANT_SIGN_src);
else if constexpr (__have_avx512f && __is_avx_ps<_Tp, _Np>())
return __lo256(_mm512_getmant_ps(__auto_bitcast(__x), _MM_MANT_NORM_p5_1,
_MM_MANT_SIGN_src));
else if constexpr (__have_avx512vl && __is_avx_pd<_Tp, _Np>())
return _mm256_getmant_pd(__x, _MM_MANT_NORM_p5_1, _MM_MANT_SIGN_src);
else if constexpr (__have_avx512f && __is_avx_pd<_Tp, _Np>())
return __lo256(_mm512_getmant_pd(__auto_bitcast(__x), _MM_MANT_NORM_p5_1,
_MM_MANT_SIGN_src));
else if constexpr (__is_avx512_ps<_Tp, _Np>())
return _mm512_getmant_ps(__x, _MM_MANT_NORM_p5_1, _MM_MANT_SIGN_src);
else if constexpr (__is_avx512_pd<_Tp, _Np>())
return _mm512_getmant_pd(__x, _MM_MANT_NORM_p5_1, _MM_MANT_SIGN_src);
else
__assert_unreachable<_Tp>();
}
#endif
template <typename _Tp, typename _Abi>
enable_if_t<std::is_floating_point_v<_Tp>, simd<_Tp, _Abi>>
frexp(const simd<_Tp, _Abi>& __x, __samesize<int, simd<_Tp, _Abi>>* __exp)
{
if constexpr (simd_size_v<_Tp, _Abi> == 1)
{
int __tmp;
const auto __r = std::frexp(__x[0], &__tmp);
(*__exp)[0] = __tmp;
return __r;
}
else if constexpr (__is_fixed_size_abi_v<_Abi>)
{
return {__private_init,
_Abi::_SimdImpl::_S_frexp(__data(__x), __data(*__exp))};
#if _GLIBCXX_SIMD_X86INTRIN
}
else if constexpr (__have_avx512f)
{
constexpr size_t _Np = simd_size_v<_Tp, _Abi>;
constexpr size_t _NI = _Np < 4 ? 4 : _Np;
const auto __v = __data(__x);
const auto __isnonzero
= _Abi::_SimdImpl::_S_isnonzerovalue_mask(__v._M_data);
const _SimdWrapper<int, _NI> __exp_plus1
= 1 + __convert<_SimdWrapper<int, _NI>>(__getexp(__v))._M_data;
const _SimdWrapper<int, _Np> __e = __wrapper_bitcast<int, _Np>(
_Abi::_CommonImpl::_S_blend(_SimdWrapper<bool, _NI>(__isnonzero),
_SimdWrapper<int, _NI>(), __exp_plus1));
simd_abi::deduce_t<int, _Np>::_CommonImpl::_S_store(__e, __exp);
return {__private_init,
_Abi::_CommonImpl::_S_blend(_SimdWrapper<bool, _Np>(__isnonzero),
__v, __getmant_avx512(__v))};
#endif
}
else
{
static_assert(sizeof(_Tp) == 4 || sizeof(_Tp) == 8);
using _V = simd<_Tp, _Abi>;
using _IV = rebind_simd_t<int, _V>;
using namespace std::experimental::__proposed;
using namespace std::experimental::__float_bitwise_operators;
constexpr int __exp_adjust = sizeof(_Tp) == 4 ? 0x7e : 0x3fe;
constexpr int __exp_offset = sizeof(_Tp) == 4 ? 0x70 : 0x200;
constexpr _Tp __subnorm_scale = sizeof(_Tp) == 4 ? 0x1p112 : 0x1p512;
_GLIBCXX_SIMD_USE_CONSTEXPR_API _V __exponent_mask
= __infinity_v<_Tp>;
_GLIBCXX_SIMD_USE_CONSTEXPR_API _V __p5_1_exponent
= -(2 - __epsilon_v<_Tp>) / 2;
_V __mant = __p5_1_exponent & (__exponent_mask | __x);
const _IV __exponent_bits = __extract_exponent_as_int(__x);
if (_GLIBCXX_SIMD_IS_LIKELY(all_of(isnormal(__x))))
{
*__exp
= simd_cast<__samesize<int, _V>>(__exponent_bits - __exp_adjust);
return __mant;
}
#if __FINITE_MATH_ONLY__
const auto __iszero_inf_nan = __x == 0;
#else
const auto __as_int
= __bit_cast<rebind_simd_t<__int_for_sizeof_t<_Tp>, _V>>(abs(__x));
const auto __inf = __bit_cast<rebind_simd_t<__int_for_sizeof_t<_Tp>, _V>>(
_V(__infinity_v<_Tp>));
const auto __iszero_inf_nan = static_simd_cast<typename _V::mask_type>(
__as_int == 0 || __as_int >= __inf);
#endif
const _V __scaled_subnormal = __x * __subnorm_scale;
const _V __mant_subnormal
= __p5_1_exponent & (__exponent_mask | __scaled_subnormal);
where(!isnormal(__x), __mant) = __mant_subnormal;
where(__iszero_inf_nan, __mant) = __x;
_IV __e = __extract_exponent_as_int(__scaled_subnormal);
using _MaskType = typename std::conditional_t<
sizeof(typename _V::value_type) == sizeof(int), _V, _IV>::mask_type;
const _MaskType __value_isnormal = isnormal(__x).__cvt();
where(__value_isnormal.__cvt(), __e) = __exponent_bits;
static_assert(sizeof(_IV) == sizeof(__value_isnormal));
const _IV __offset
= (__bit_cast<_IV>(__value_isnormal) & _IV(__exp_adjust))
| (__bit_cast<_IV>(static_simd_cast<_MaskType>(__exponent_bits == 0)
& static_simd_cast<_MaskType>(__x != 0))
& _IV(__exp_adjust + __exp_offset));
*__exp = simd_cast<__samesize<int, _V>>(__e - __offset);
return __mant;
}
}
_GLIBCXX_SIMD_MATH_CALL2_(ldexp, int)
_GLIBCXX_SIMD_MATH_CALL_(ilogb)
_GLIBCXX_SIMD_MATH_CALL_(log)
_GLIBCXX_SIMD_MATH_CALL_(log10)
_GLIBCXX_SIMD_MATH_CALL_(log1p)
_GLIBCXX_SIMD_MATH_CALL_(log2)
template <typename _Tp, typename _Abi>
enable_if_t<std::is_floating_point<_Tp>::value, simd<_Tp, _Abi>>
logb(const simd<_Tp, _Abi>& __x)
{
constexpr size_t _Np = simd_size_v<_Tp, _Abi>;
if constexpr (_Np == 1)
return std::logb(__x[0]);
else if constexpr (__is_fixed_size_abi_v<_Abi>)
{
return {__private_init,
__data(__x)._M_apply_per_chunk([](auto __impl, auto __xx) {
using _V = typename decltype(__impl)::simd_type;
return __data(
std::experimental::logb(_V(__private_init, __xx)));
})};
}
#if _GLIBCXX_SIMD_X86INTRIN
else if constexpr (__have_avx512vl && __is_sse_ps<_Tp, _Np>())
return {__private_init,
__auto_bitcast(_mm_getexp_ps(__to_intrin(__as_vector(__x))))};
else if constexpr (__have_avx512vl && __is_sse_pd<_Tp, _Np>())
return {__private_init, _mm_getexp_pd(__data(__x))};
else if constexpr (__have_avx512vl && __is_avx_ps<_Tp, _Np>())
return {__private_init, _mm256_getexp_ps(__data(__x))};
else if constexpr (__have_avx512vl && __is_avx_pd<_Tp, _Np>())
return {__private_init, _mm256_getexp_pd(__data(__x))};
else if constexpr (__have_avx512f && __is_avx_ps<_Tp, _Np>())
return {__private_init,
__lo256(_mm512_getexp_ps(__auto_bitcast(__data(__x))))};
else if constexpr (__have_avx512f && __is_avx_pd<_Tp, _Np>())
return {__private_init,
__lo256(_mm512_getexp_pd(__auto_bitcast(__data(__x))))};
else if constexpr (__is_avx512_ps<_Tp, _Np>())
return {__private_init, _mm512_getexp_ps(__data(__x))};
else if constexpr (__is_avx512_pd<_Tp, _Np>())
return {__private_init, _mm512_getexp_pd(__data(__x))};
#endif
else
{
using _V = simd<_Tp, _Abi>;
using namespace std::experimental::__proposed;
auto __is_normal = isnormal(__x);
const _V abs_x = abs(__x);
auto&& __exponent = [](const _V& __v) {
using namespace std::experimental::__proposed;
using _IV = rebind_simd_t<
std::conditional_t<sizeof(_Tp) == sizeof(_LLong), _LLong, int>, _V>;
return (__bit_cast<_IV>(__v) >> (__digits_v<_Tp> - 1))
- (__max_exponent_v<_Tp> - 1);
};
_V __r = static_simd_cast<_V>(__exponent(abs_x));
if (_GLIBCXX_SIMD_IS_LIKELY(all_of(__is_normal)))
return __r;
const auto __is_zero = __x == 0;
const auto __is_nan = isnan(__x);
const auto __is_inf = isinf(__x);
where(__is_zero, __r) = -__infinity_v<_Tp>;
where(__is_nan, __r) = __x;
where(__is_inf, __r) = __infinity_v<_Tp>;
__is_normal |= __is_zero || __is_nan || __is_inf;
if (all_of(__is_normal))
return __r;
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
if constexpr (__is_scalar_abi<_Abi>()
|| (__is_fixed_size_abi_v<_Abi> && simd_size_v<_Tp, _Abi> == 1))
{
_Tp __tmp;
_Tp __r = std::modf(__x[0], &__tmp);
__iptr[0] = __tmp;
return __r;
}
else
{
const auto __integral = trunc(__x);
*__iptr = __integral;
auto __r = __x - __integral;
#if !__FINITE_MATH_ONLY__
where(isinf(__x), __r) = _Tp();
#endif
return copysign(__r, __x);
}
}
_GLIBCXX_SIMD_MATH_CALL2_(scalbn, int)
_GLIBCXX_SIMD_MATH_CALL2_(scalbln, long)
_GLIBCXX_SIMD_MATH_CALL_(cbrt)
_GLIBCXX_SIMD_MATH_CALL_(abs)
_GLIBCXX_SIMD_MATH_CALL_(fabs)
template <typename _Tp, typename _Abi>
enable_if_t<!std::is_floating_point_v<_Tp> && std::is_signed_v<_Tp>,
simd<_Tp, _Abi>>
abs(const simd<_Tp, _Abi>& __x)
{
return {__private_init, _Abi::_SimdImpl::_S_abs(__data(__x))};
}
template <typename _Tp, typename _Abi>
enable_if_t<!std::is_floating_point_v<_Tp> && std::is_signed_v<_Tp>,
simd<_Tp, _Abi>>
fabs(const simd<_Tp, _Abi>& __x)
{
return {__private_init, _Abi::_SimdImpl::_S_abs(__data(__x))};
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
_GLIBCXX_SIMD_INTRINSIC _R
__fixed_size_apply(_ToApply&& __apply, const _Tp& __arg0, const _Tps&... __args)
{
return {__private_init,
__data(__arg0)._M_apply_per_chunk(
[&](auto __impl, const auto&... __inner) {
using _V = typename decltype(__impl)::simd_type;
return __data(__apply(_V(__private_init, __inner)...));
},
__data(__args)...)};
}
template <typename _VV>
__remove_cvref_t<_VV>
__hypot(_VV __x, _VV __y)
{
using _V = __remove_cvref_t<_VV>;
using _Tp = typename _V::value_type;
if constexpr (_V::size() == 1)
return std::hypot(_Tp(__x[0]), _Tp(__y[0]));
else if constexpr (__is_fixed_size_abi_v<typename _V::abi_type>)
{
return __fixed_size_apply<_V>([](auto __a,
auto __b) { return hypot(__a, __b); },
__x, __y);
}
else
{
using namespace __float_bitwise_operators;
_V __absx = abs(__x);
_V __absy = abs(__y);
_V __hi = max(__absx, __absy);
_V __lo = min(__absy, __absx);
_GLIBCXX_SIMD_USE_CONSTEXPR_API _V __inf(__infinity_v<_Tp>);
#ifndef __FAST_MATH__
if constexpr (__have_neon && !__have_neon_a32)
{
const _V __hi_exp = __hi & __inf;
_V __scale_back = __hi_exp;
where(__hi_exp > 1, __scale_back) = __hi_exp * _Tp(0.125);
const _V __scale = (__scale_back ^ __inf) * _Tp(.5);
const _V __h1 = __hi * __scale;
const _V __l1 = __lo * __scale;
_V __r = __scale_back * sqrt(__h1 * __h1 + __l1 * __l1);
where(__hi == 0, __r) = 0;
return __r;
}
#endif
#ifdef __FAST_MATH__
if constexpr (true)
#else
if (_GLIBCXX_SIMD_IS_LIKELY(all_of(isnormal(__x))
&& all_of(isnormal(__y))))
#endif
{
const _V __hi_exp = __hi & __inf;
#ifdef __FAST_MATH__
using _Ip = __int_for_sizeof_t<_Tp>;
using _IV = rebind_simd_t<_Ip, _V>;
const auto __as_int = __bit_cast<_IV>(__hi_exp);
const _V __scale = __bit_cast<_V>(2 * __bit_cast<_Ip>(_Tp(1)) - __as_int);
#else
const _V __scale = (__hi_exp ^ __inf) * _Tp(.5);
#endif
_GLIBCXX_SIMD_USE_CONSTEXPR_API _V __mant_mask
= __norm_min_v<_Tp> - __denorm_min_v<_Tp>;
const _V __h1 = (__hi & __mant_mask) | _V(1);
const _V __l1 = __lo * __scale;
return __hi_exp * sqrt(__h1 * __h1 + __l1 * __l1);
}
else
{
_V __scale = _V(1 / __norm_min_v<_Tp>);
where(__hi >= __norm_min_v<_Tp>, __scale)
= ((__hi & __inf) ^ __inf) * _Tp(.5);
_V __hi_exp = __norm_min_v<_Tp>;
where(__hi >= __norm_min_v<_Tp>, __hi_exp)
= __hi & __inf;
_V __h1 = __hi * __scale;
_V __l1 = __lo * __scale;
_V __r = __hi_exp * sqrt(__h1 * __h1 + __l1 * __l1);
#ifdef __STDC_IEC_559__
_V __fixup = __hi;
where(isunordered(__x, __y), __fixup) = __quiet_NaN_v<_Tp>;
where(isinf(__absx) || isinf(__absy), __fixup) = __inf;
where(!(__lo == 0 || isunordered(__x, __y)
|| (isinf(__absx) || isinf(__absy))),
__fixup)
= __r;
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
template <typename _VV>
__remove_cvref_t<_VV>
__hypot(_VV __x, _VV __y, _VV __z)
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
using namespace __float_bitwise_operators;
const _V __absx = abs(__x);
const _V __absy = abs(__y);
const _V __absz = abs(__z);
_V __hi = max(max(__absx, __absy), __absz);
_V __l0 = min(__absz, max(__absx, __absy));
_V __l1 = min(__absy, __absx);
if constexpr (__digits_v<_Tp> == 64 && __max_exponent_v<_Tp> == 0x4000
&& __min_exponent_v<_Tp> == -0x3FFD && _V::size() == 1)
{
#ifdef __STDC_IEC_559__
if (isinf(__absx[0]) || isinf(__absy[0]) || isinf(__absz[0]))
return __infinity_v<_Tp>;
else if (isunordered(__absx[0], __absy[0] + __absz[0]))
return __quiet_NaN_v<_Tp>;
else if (__l0[0] == 0 && __l1[0] == 0)
return __hi;
#endif
_V __hi_exp = __hi;
const _ULLong __tmp = 0x8000'0000'0000'0000ull;
__builtin_memcpy(&__hi_exp, &__tmp, 8);
const _V __scale = 1 / __hi_exp;
__hi *= __scale;
__l0 *= __scale;
__l1 *= __scale;
return __hi_exp * sqrt((__l0 * __l0 + __l1 * __l1) + __hi * __hi);
}
else
{
_GLIBCXX_SIMD_USE_CONSTEXPR_API _V __inf(__infinity_v<_Tp>);
#ifndef __FAST_MATH__
if constexpr (_V::size() > 1 && __have_neon && !__have_neon_a32)
{
const _V __hi_exp = __hi & __inf;
_V __scale_back = __hi_exp;
where(__hi_exp > 1, __scale_back) = __hi_exp * _Tp(0.125);
const _V __scale = (__scale_back ^ __inf) * _Tp(.5);
const _V __h1 = __hi * __scale;
__l0 *= __scale;
__l1 *= __scale;
_V __lo
= __l0 * __l0 + __l1 * __l1;
asm("":"+m"(__lo));
_V __r = __scale_back * sqrt(__h1 * __h1 + __lo);
where(__hi == 0, __r) = 0;
return __r;
}
#endif
#ifdef __FAST_MATH__
if constexpr (true)
#else
if (_GLIBCXX_SIMD_IS_LIKELY(all_of(isnormal(__x))
&& all_of(isnormal(__y))
&& all_of(isnormal(__z))))
#endif
{
const _V __hi_exp = __hi & __inf;
#ifdef __FAST_MATH__
using _Ip = __int_for_sizeof_t<_Tp>;
using _IV = rebind_simd_t<_Ip, _V>;
const auto __as_int = __bit_cast<_IV>(__hi_exp);
const _V __scale
= __bit_cast<_V>(2 * __bit_cast<_Ip>(_Tp(1)) - __as_int);
#else
const _V __scale = (__hi_exp ^ __inf) * _Tp(.5);
#endif
constexpr _Tp __mant_mask
= __norm_min_v<_Tp> - __denorm_min_v<_Tp>;
const _V __h1 = (__hi & _V(__mant_mask)) | _V(1);
__l0 *= __scale;
__l1 *= __scale;
const _V __lo
= __l0 * __l0 + __l1 * __l1;
return __hi_exp * sqrt(__lo + __h1 * __h1);
}
else
{
_V __scale = _V(1 / __norm_min_v<_Tp>);
where(__hi >= __norm_min_v<_Tp>, __scale)
= ((__hi & __inf) ^ __inf) * _Tp(.5);
_V __hi_exp = __norm_min_v<_Tp>;
where(__hi >= __norm_min_v<_Tp>, __hi_exp)
= __hi & __inf;
_V __h1 = __hi * __scale;
__l0 *= __scale;
__l1 *= __scale;
_V __lo
= __l0 * __l0 + __l1 * __l1;
_V __r = __hi_exp * sqrt(__lo + __h1 * __h1);
#ifdef __STDC_IEC_559__
_V __fixup = __hi;
where(isunordered(__x, __y + __z), __fixup)
= __quiet_NaN_v<_Tp>;
where(isinf(__absx) || isinf(__absy) || isinf(__absz), __fixup)
= __inf;
where(!(__lo == 0 || isunordered(__x, __y + __z) || isinf(__absx)
|| isinf(__absy) || isinf(__absz)),
__fixup)
= __r;
__r = __fixup;
#endif
return __r;
}
}
}
}
template <typename _Tp, typename _Abi>
_GLIBCXX_SIMD_INTRINSIC simd<_Tp, _Abi>
hypot(const simd<_Tp, _Abi>& __x, const simd<_Tp, _Abi>& __y,
const simd<_Tp, _Abi>& __z)
{
return __hypot<conditional_t<__is_fixed_size_abi_v<_Abi>,
const simd<_Tp, _Abi>&, simd<_Tp, _Abi>>>(__x,
__y,
__z);
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
_GLIBCXX_SIMD_MATH_CALL3_(remquo, _Tp, int*)
template <typename _Tp, typename _Abi>
enable_if_t<std::is_floating_point_v<_Tp>, simd<_Tp, _Abi>>
copysign(const simd<_Tp, _Abi>& __x, const simd<_Tp, _Abi>& __y)
{
if constexpr (simd_size_v<_Tp, _Abi> == 1)
return std::copysign(__x[0], __y[0]);
else if constexpr (std::is_same_v<_Tp, long double> && sizeof(_Tp) == 12)
return simd<_Tp, _Abi>(
[&](auto __i) { return std::copysign(__x[__i], __y[__i]); });
else
{
using _V = simd<_Tp, _Abi>;
using namespace std::experimental::__float_bitwise_operators;
_GLIBCXX_SIMD_USE_CONSTEXPR_API auto __signmask = _V(1) ^ _V(-1);
return (__x & (__x ^ __signmask)) | (__y & __signmask);
}
}
_GLIBCXX_SIMD_MATH_CALL2_(nextafter, _Tp)
_GLIBCXX_SIMD_MATH_CALL2_(fdim, _Tp)
_GLIBCXX_SIMD_MATH_CALL2_(fmax, _Tp)
_GLIBCXX_SIMD_MATH_CALL2_(fmin, _Tp)
_GLIBCXX_SIMD_MATH_CALL3_(fma, _Tp, _Tp)
_GLIBCXX_SIMD_MATH_CALL_(fpclassify)
_GLIBCXX_SIMD_MATH_CALL_(isfinite)
template <typename _Tp, typename _Abi, typename...,
typename _R
= std::experimental::__math_return_type_t<bool, _Tp, _Abi>>
enable_if_t<std::is_floating_point_v<_Tp>, _R>
isinf(std::experimental::simd<_Tp, _Abi> __x)
{
return {std::experimental::__private_init,
_Abi::_SimdImpl::_S_isinf(std::experimental::__data(__x))};
}
template <typename _Tp, typename _Abi, typename...,
typename _R
= std::experimental::__math_return_type_t<bool, _Tp, _Abi>>
enable_if_t<std::is_floating_point_v<_Tp>, _R>
isnan(std::experimental::simd<_Tp, _Abi> __x)
{
return {std::experimental::__private_init,
_Abi::_SimdImpl::_S_isnan(std::experimental::__data(__x))};
}
_GLIBCXX_SIMD_MATH_CALL_(isnormal)
template <typename..., typename _Tp, typename _Abi>
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
_Abi::_SimdImpl::_S_signbit(std::experimental::__data(__x))};
}
_GLIBCXX_SIMD_MATH_CALL2_(isgreater, _Tp)
_GLIBCXX_SIMD_MATH_CALL2_(isgreaterequal, _Tp)
_GLIBCXX_SIMD_MATH_CALL2_(isless, _Tp)
_GLIBCXX_SIMD_MATH_CALL2_(islessequal, _Tp)
_GLIBCXX_SIMD_MATH_CALL2_(islessgreater, _Tp)
_GLIBCXX_SIMD_MATH_CALL2_(isunordered, _Tp)
template <typename _Tp, typename _Abi>
enable_if_t<std::is_floating_point_v<_Tp>, simd<_Tp, _Abi>>
assoc_laguerre(const std::experimental::fixed_size_simd<
unsigned, std::experimental::simd_size_v<_Tp, _Abi>>& __n,
const std::experimental::fixed_size_simd<
unsigned, std::experimental::simd_size_v<_Tp, _Abi>>& __m,
const std::experimental::simd<_Tp, _Abi>& __x)
{
return std::experimental::simd<_Tp, _Abi>([&](auto __i) {
return std::assoc_laguerre(__n[__i], __m[__i], __x[__i]);
});
}
template <typename _Tp, typename _Abi>
enable_if_t<std::is_floating_point_v<_Tp>, simd<_Tp, _Abi>>
assoc_legendre(const std::experimental::fixed_size_simd<
unsigned, std::experimental::simd_size_v<_Tp, _Abi>>& __n,
const std::experimental::fixed_size_simd<
unsigned, std::experimental::simd_size_v<_Tp, _Abi>>& __m,
const std::experimental::simd<_Tp, _Abi>& __x)
{
return std::experimental::simd<_Tp, _Abi>([&](auto __i) {
return std::assoc_legendre(__n[__i], __m[__i], __x[__i]);
});
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
template <typename _Tp, typename _Abi>
enable_if_t<std::is_floating_point_v<_Tp>, simd<_Tp, _Abi>>
hermite(const std::experimental::fixed_size_simd<
unsigned, std::experimental::simd_size_v<_Tp, _Abi>>& __n,
const std::experimental::simd<_Tp, _Abi>& __x)
{
return std::experimental::simd<_Tp, _Abi>(
[&](auto __i) { return std::hermite(__n[__i], __x[__i]); });
}
template <typename _Tp, typename _Abi>
enable_if_t<std::is_floating_point_v<_Tp>, simd<_Tp, _Abi>>
laguerre(const std::experimental::fixed_size_simd<
unsigned, std::experimental::simd_size_v<_Tp, _Abi>>& __n,
const std::experimental::simd<_Tp, _Abi>& __x)
{
return std::experimental::simd<_Tp, _Abi>(
[&](auto __i) { return std::laguerre(__n[__i], __x[__i]); });
}
template <typename _Tp, typename _Abi>
enable_if_t<std::is_floating_point_v<_Tp>, simd<_Tp, _Abi>>
legendre(const std::experimental::fixed_size_simd<
unsigned, std::experimental::simd_size_v<_Tp, _Abi>>& __n,
const std::experimental::simd<_Tp, _Abi>& __x)
{
return std::experimental::simd<_Tp, _Abi>(
[&](auto __i) { return std::legendre(__n[__i], __x[__i]); });
}
_GLIBCXX_SIMD_MATH_CALL_(riemann_zeta)
template <typename _Tp, typename _Abi>
enable_if_t<std::is_floating_point_v<_Tp>, simd<_Tp, _Abi>>
sph_bessel(const std::experimental::fixed_size_simd<
unsigned, std::experimental::simd_size_v<_Tp, _Abi>>& __n,
const std::experimental::simd<_Tp, _Abi>& __x)
{
return std::experimental::simd<_Tp, _Abi>(
[&](auto __i) { return std::sph_bessel(__n[__i], __x[__i]); });
}
template <typename _Tp, typename _Abi>
enable_if_t<std::is_floating_point_v<_Tp>, simd<_Tp, _Abi>>
sph_legendre(const std::experimental::fixed_size_simd<
unsigned, std::experimental::simd_size_v<_Tp, _Abi>>& __l,
const std::experimental::fixed_size_simd<
unsigned, std::experimental::simd_size_v<_Tp, _Abi>>& __m,
const std::experimental::simd<_Tp, _Abi>& theta)
{
return std::experimental::simd<_Tp, _Abi>([&](auto __i) {
return std::assoc_legendre(__l[__i], __m[__i], theta[__i]);
});
}
template <typename _Tp, typename _Abi>
enable_if_t<std::is_floating_point_v<_Tp>, simd<_Tp, _Abi>>
sph_neumann(const std::experimental::fixed_size_simd<
unsigned, std::experimental::simd_size_v<_Tp, _Abi>>& __n,
const std::experimental::simd<_Tp, _Abi>& __x)
{
return std::experimental::simd<_Tp, _Abi>(
[&](auto __i) { return std::sph_neumann(__n[__i], __x[__i]); });
}
#undef _GLIBCXX_SIMD_MATH_CALL_
#undef _GLIBCXX_SIMD_MATH_CALL2_
#undef _GLIBCXX_SIMD_MATH_CALL3_
_GLIBCXX_SIMD_END_NAMESPACE
#endif
#endif
#pragma GCC diagnostic pop
#endif
