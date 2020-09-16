/*{{{
Copyright © 2017-2020 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH
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
#include "unittest.h"
#include "metahelpers.h"

template <class... Ts> using base_template = std::experimental::simd<Ts...>;
#include "testtypes.h"

namespace stdx = std::experimental;
namespace simd_abi = stdx::simd_abi;

template <class From, class To>
concept castable_to = requires(From(f)(), void(g)(const To&))
{
  g(static_cast<To>(f()));
};

template <typename T> struct Convertible// {{{
{
  T data;
  operator T&() & { return data; }
  operator const T &() const & { return data; }
  operator T &&() && { return static_cast<T&&>(data); }
};
// }}}
enum Enum// {{{
{
  EnumA,
  EnumB = 0xffff
};

template <>
class std::numeric_limits<Enum>
  : public std::numeric_limits<stdx::__enum_evaluation_type_t<Enum>>
{
public:
  static inline constexpr bool is_integer = false;
  static inline constexpr int digits = 16;
  static inline constexpr int min() { return int(Enum::EnumA); }
  static inline constexpr int max() { return int(Enum::EnumB); }
};

// }}}
enum EnumS : signed char// {{{
{
};

template <>
class std::numeric_limits<EnumS> : public std::numeric_limits<signed char>
{
public:
  static inline constexpr bool is_integer = false;
};

// }}}
enum class EnumClass// {{{
{
  A,
  B
};

template <>
class std::numeric_limits<EnumClass>
  : public std::numeric_limits<std::underlying_type_t<EnumClass>>
{
public:
  static inline constexpr bool is_integer = false;
};

// }}}
// operator<< for enums{{{
template <typename T>
requires(std::is_enum_v<T>)
std::ostream&
operator<<(std::ostream& s, T x)
{
  return s << static_cast<stdx::__enum_evaluation_type_t<T>>(x);
}
// }}}
// all_*_types type lists {{{
template <typename T>
struct invalid_simd : std::negation<std::is_destructible<T>>
{
};

using abi_list =
#if !defined ABITYPES || ABITYPES == 0
  all_native_abis;
#else
  fixed_size_abi_list;
#endif
template <typename T>
using all_valid_simd_types = typename vir::filter_list<
  vir::filter_predicate<invalid_simd>,
  vir::expand_one<vir::Template<stdx::simd>,
		  vir::outer_product<vir::Typelist<T>, abi_list>>>::type;

using all_unscoped_enum_types
  = vir::concat<all_valid_simd_types<Enum>, all_valid_simd_types<EnumS>>;
using all_scoped_enum_types = all_valid_simd_types<EnumClass>;
using all_enum_types = vir::concat<all_unscoped_enum_types, all_scoped_enum_types>;
// }}}
TEST(sanity) //{{{1
{
  [[maybe_unused]] stdx::simd<Enum, simd_abi::scalar> x{};
  VERIFY(vir::list_size<all_unscoped_enum_types>::value > 0);
  VERIFY(vir::list_size<all_scoped_enum_types>::value > 0);
}

TEST_TYPES(V, broadcast, all_enum_types)  //{{{1
{
  using T = typename V::value_type;
  using U = stdx::__enum_evaluation_type_t<T>;

  // implicit conversion to enum never works
  static_assert(!std::convertible_to<U, T>);
  // static_cast to enum always works
  static_assert(castable_to<U, T>);
  // construction (direct-initialization) requires implicit conversion
  // => doesn't work
  static_assert(!std::constructible_from<T, U>);

  VERIFY(std::is_enum_v<T>);
  VERIFY(std::experimental::is_simd_v<V>);
  VERIFY(std::experimental::is_abi_tag_v<typename V::abi_type>);
  VERIFY((std::convertible_to<T, V>) );
  VERIFY((!std::convertible_to<U, V>));
  COMPARE((std::convertible_to<float, V>), (std::convertible_to<float, T>) );
  COMPARE((std::convertible_to<Convertible<V>&, V>),
	  (std::convertible_to<Convertible<T>&, T>) );
  VERIFY((castable_to<T, V>) );
  COMPARE((castable_to<U, V>), (castable_to<U, T>) );
  COMPARE((castable_to<float, V>), (castable_to<float, T>) );
  COMPARE((castable_to<Convertible<U>&, V>), (castable_to<Convertible<U>&, T>))
    .on_failure("\nU = ", typeid(U));
  COMPARE((castable_to<Convertible<T>&, V>),
	  (castable_to<Convertible<T>&, T>) );

  V x; // not initialized
  x = V{};
  COMPARE(x, V(T{}));
  COMPARE(x, V());
  COMPARE(x, V{});
  x = V();
  COMPARE(x, V(T{}));
  COMPARE(x, V());
  COMPARE(x, V{});
  x = T();
  COMPARE(x, V(T()));
  COMPARE(x, V());
  COMPARE(x, V{});

  for (std::size_t i = 0; i < V::size(); ++i)
    {
      COMPARE(T(x[i]), T()) << "i = " << i;
      COMPARE(x[i], T()) << "i = " << i;
    }

  constexpr U u1 = 1;
  x = V(u1);
  V y = T();
  for (std::size_t i = 0; i < V::size(); ++i)
    {
      COMPARE(x[i], T(1)) << "i = " << i;
      COMPARE(y[i], T()) << "i = " << i;
    }
  y = T(1);
  COMPARE(x, y);

  enum unscoped_enum {};
  enum class scoped_enum {};
  VERIFY((is_substitution_failure<V &, unscoped_enum, assignment>));
  VERIFY((is_substitution_failure<V &, scoped_enum, assignment>));
  VERIFY((is_substitution_failure<V &, int, assignment>));
  VERIFY((is_substitution_failure<V &, unsigned, assignment>));
  VERIFY((is_substitution_failure<V &, float, assignment>));
}

TEST_TYPES(V, cvt_ctor, all_enum_types)  //{{{1
{
  using T = typename V::value_type;

  auto tests =
    [](auto foo) {
      using U = decltype(foo);
      if constexpr (V::size() <= stdx::simd_abi::max_fixed_size<U>)
	{
	  using UV = stdx::rebind_simd_t<U, V>;
	  COMPARE((std::constructible_from<V, UV>), (castable_to<U, T>) )
	    .on_failure("\nT = ", typeid(T), "\nU = ", typeid(U),
			"\nUV = ", typeid(UV));
	  COMPARE((std::constructible_from<V, Convertible<UV>>),
		  (castable_to<Convertible<U>, T>) );

	  COMPARE((std::convertible_to<UV, V>), (std::convertible_to<U, T>) );

	  COMPARE((castable_to<UV, V>), (castable_to<U, T>) );
	  COMPARE((castable_to<Convertible<UV>, V>),
		  (castable_to<Convertible<U>, T>) );
	}
    };
  tests(stdx::__enum_evaluation_type_t<T>());
  tests(short());
  tests(llong());

  using U = stdx::__enum_evaluation_type_t<T>;
  using UV = stdx::simd<U, typename V::abi_type>;
  UV x([](int i) { return i; });
  COMPARE(V(x), V([](int i) { return T(i); }));
}

TEST_TYPES(V, cvt_operator, all_enum_types)  //{{{1
{
  using T = typename V::value_type;
  using U = stdx::__enum_evaluation_type_t<T>;
  using UV = stdx::simd<U, typename V::abi_type>;

  VERIFY((std::constructible_from<UV, V>));
  COMPARE((std::convertible_to<V, UV>), (std::convertible_to<T, U>) );

  V x([](int i) { return T(i); });
  COMPARE(UV(x), UV([](int i) { return i; }));
}

template <class V> struct call_generator {  // {{{1
    template <class F> auto operator()(const F &f) -> decltype(V(f));
};

TEST_TYPES(V, generators, all_enum_types) //{{{1
{
  using T = typename V::value_type;
  V x([](int) { return T(1); });
  COMPARE(x, V(1));
  x = V([](auto i) { return T(i.value); });
  COMPARE(x, V([](int i) { return T(i); }));

  VERIFY(!sfinae_is_callable<int (&)(int)>(call_generator<V>()));
  VERIFY(!sfinae_is_callable<signed char (&)(int)>(call_generator<V>()));
  VERIFY(!sfinae_is_callable<unsigned char (&)(int)>(call_generator<V>()));
  VERIFY(!sfinae_is_callable<float (&)(int)>(call_generator<V>()));
}

TEST_TYPES(V, loads_and_stores, all_enum_types) //{{{1
{
  using T = typename V::value_type;
  using U = std::conditional_t<std::is_same_v<T, Enum>, int,
			       stdx::__enum_evaluation_type_t<T>>;

  VERIFY((std::constructible_from<V, T*>));
  VERIFY((std::constructible_from<V, const T*>));
  VERIFY((std::constructible_from<V, U*>));
  VERIFY((std::constructible_from<V, const U*>));
  VERIFY((!std::convertible_to<T*, V>));
  VERIFY((!std::convertible_to<const T*, V>));
  VERIFY((!std::convertible_to<U*, V>));
  VERIFY((!std::convertible_to<const U*, V>));

  constexpr std::size_t mem_size = 2 * V::size() + 32;
  alignas(stdx::memory_alignment_v<V>) T mem0[mem_size] = {};
  alignas(stdx::memory_alignment_v<V, U>) U mem1[mem_size] = {};

  V vseq([](int i) { return T(i); });
  vseq.copy_to(mem0);
  vseq.copy_to(mem1);
  for (std::size_t i = 0; i < V::size(); ++i)
    {
      COMPARE(mem0[i], T(i));
      COMPARE(mem1[i], U(i));
    }
  for (std::size_t i = V::size(); i < mem_size; ++i)
    {
      COMPARE(mem0[i], T());
      COMPARE(mem1[i], U());
    }
  COMPARE(V(mem0, stdx::vector_aligned), vseq);
  COMPARE(V(mem1, stdx::vector_aligned), vseq);
  COMPARE(V(mem0 + 1),
	  V([](auto i) { return T(i + 1 < V::size() ? i + 1 : 0); }));
  COMPARE(V(mem1 + 1),
	  V([](auto i) { return T(i + 1 < V::size() ? i + 1 : 0); }));

  V tmp;
  tmp.copy_from(mem0, stdx::vector_aligned);
  COMPARE(tmp, vseq);
  tmp.copy_from(mem1, stdx::vector_aligned);
  COMPARE(tmp, vseq);
  tmp.copy_from(mem0 + 1);
  COMPARE(tmp, V([](auto i) { return T(i + 1 < V::size() ? i + 1 : 0); }));
  tmp.copy_from(mem1 + 1);
  COMPARE(tmp, V([](auto i) { return T(i + 1 < V::size() ? i + 1 : 0); }));
}

template <class A, class B, class Expected = A> void binary_op_return_type()  //{{{1
{
    using namespace vir::test;
    using AC = std::add_const_t<A>;
    using BC = std::add_const_t<B>;
    const auto name = vir::typeToString<A>() + " + " + vir::typeToString<B>();
    COMPARE_TYPES(decltype(A() + B()), Expected).on_failure('\n', name);
    COMPARE_TYPES(decltype(B() + A()), Expected).on_failure('\n', name);
    COMPARE_TYPES(decltype(AC() + BC()), Expected).on_failure('\n', name);
    COMPARE_TYPES(decltype(BC() + AC()), Expected).on_failure('\n', name);
    ADD_PASS() << name;
}

TEST_TYPES(V, operator_conversions, all_unscoped_enum_types)  //{{{1
{
  using T = typename V::value_type;
  using U = stdx::__enum_evaluation_type_t<T>;
  using VU = stdx::simd<U, typename V::abi_type>;
  binary_op_return_type<V, V, VU>();
  binary_op_return_type<V, T, VU>();
  binary_op_return_type<V, int, VU>();
  binary_op_return_type<V, U, VU>();
}

TEST_TYPES(V, no_operators, all_scoped_enum_types)  //{{{1
{
  using T = typename V::value_type;
  using U = stdx::__enum_evaluation_type_t<T>;
  COMPARE(requires(V a, V b) { a + b; }, false);
  COMPARE(requires(V a, T b) { a + b; }, false);
  COMPARE(requires(T a, V b) { a + b; }, false);
  COMPARE(requires(V a, U b) { a + b; }, false);
  COMPARE(requires(U a, V b) { a + b; }, false);
}

TEST_TYPES(V, reductions, all_enum_types)  //{{{1
{
  using T = typename V::value_type;
  using U = stdx::__enum_evaluation_type_t<T>;
  V x{};
  COMPARE(reduce(x,
		 [](auto a, auto b) {
		   return stdx::static_simd_cast<decltype(a)>(
		     stdx::static_simd_cast<U>(a)
		     | stdx::static_simd_cast<U>(b));
		 }),
	  T{});
}

TEST_TYPES(V, algorithms, all_unscoped_enum_types)  //{{{1
{
    using T = typename V::value_type;
    V a{[](auto i) { return T(i & 1u); }};
    V b{[](auto i) { return T((i + 1u) & 1u); }};
    COMPARE(min(a, b), V{});
    COMPARE(max(a, b), V{T(1)});
}

TEST_TYPES(V, deduce_from_list, all_enum_types) // {{{1
{
  using T = typename V::value_type;
  using A = typename V::abi_type;
  VERIFY((sfinae_is_callable<T>(
    [](auto a) -> stdx::simd_abi::deduce_t<decltype(a), 1> { return {}; })));
  VERIFY((sfinae_is_callable<T>(
    [](auto a) -> stdx::simd_abi::deduce_t<decltype(a), 2> { return {}; })));
  VERIFY((sfinae_is_callable<T>(
    [](auto a) -> stdx::simd_abi::deduce_t<decltype(a), 4> { return {}; })));
  VERIFY((sfinae_is_callable<T>(
    [](auto a) -> stdx::simd_abi::deduce_t<decltype(a), 8> { return {}; })));
  using W = stdx::simd_abi::deduce_t<T, V::size(), A>;
  VERIFY(
    (sfinae_is_callable<W>([](auto a) -> stdx::simd<T, W> { return {}; })));
  if constexpr (stdx::__is_fixed_size_abi_v<A>)
    {
      if constexpr (stdx::__is_fixed_size_abi_v<W>)
	COMPARE_TYPES(W, A);
      else
	COMPARE_TYPES(W, typename std::decay_t<decltype(
			   __data(std::declval<V&>()))>::_FirstAbi);
    }
  else if constexpr (V::size() == 1)
    COMPARE_TYPES(W, std::experimental::simd_abi::scalar);
  else if constexpr (stdx::__have_avx512f)
    {
      COMPARE(V::size(), (std::experimental::simd_size_v<T, W>) )
	<< vir::typeToString<W>();
      COMPARE_TYPES(W, stdx::simd_abi::_VecBltnBtmsk<sizeof(T) * V::size()>);
    }
  else
    COMPARE_TYPES(W, A);
}

TEST_TYPES(V, compare, all_enum_types) //{{{1
{
  using M = typename V::mask_type;
  using T = typename V::value_type;
  using U = stdx::__enum_evaluation_type_t<T>;

  VERIFY(requires(V a, V b) { {a == b} -> std::same_as<M>; });
  VERIFY(requires(V a, T b) { {a == b} -> std::same_as<M>; });
  VERIFY(requires(T a, V b) { {a == b} -> std::same_as<M>; });
  if constexpr(stdx::__unscoped_enum<T>)
    {
      VERIFY(requires(V a, U b) { {a == b} -> std::same_as<M>; });
      VERIFY(requires(U a, V b) { {a == b} -> std::same_as<M>; });
    }
  else
    {
      VERIFY(!requires(V a, U b) { {a == b}; });
      VERIFY(!requires(U a, V b) { {a == b}; });
    }

  constexpr U min = std::numeric_limits<U>::min();
  constexpr U max = std::numeric_limits<U>::max();
  const V v0{};
  const V v1(T(1));
  const V v2(T(2));
  const V v01([](int i) { return T(i % 2); });
  const V v012([](int i) { return T(i % 3); });
  const auto& make_mask = [](auto... in) {
    const bool arr[] = {static_cast<bool>(in)...};
    return M(stdx::__private_init,
	     [&arr](auto i) { return arr[i % sizeof...(in)]; });
  };
  COMPARE(v0 == v01, make_mask(1, 0));
  COMPARE(v0 == v012, make_mask(1, 0, 0));
  COMPARE(v1 == v012, make_mask(0, 1, 0));
  COMPARE(v2 == v012, make_mask(0, 0, 1));
  COMPARE(v0 < v012, make_mask(0, 1, 1));
  COMPARE(v0 <= v012, M(true));
  COMPARE(v2 <= v012, make_mask(0, 0, 1));

  constexpr U half
    = std::numeric_limits<U>::max() >> (std::numeric_limits<U>::digits / 2);
  for (T lo_ : {T(min), T(min + 1), T(-1), T(0), T(1), T(half - 1), T(half),
		T(half + 1), T(max - 1)})
    {
      for (T hi_ : {T(min + 1), T(-1), T(0), T(1), T(half - 1), T(half),
		    T(half + 1), T(max - 1), T(max)})
	{
	  if (hi_ <= lo_)
	    continue;
	  for (std::size_t pos = 0; pos < V::size(); ++pos)
	    {
	      V lo = lo_;
	      V hi = hi_;
	      lo[pos] = T(0); // have a different value in the vector in case
	      hi[pos] = T(1); // this affects neighbors
	      COMPARE(hi, hi);
	      VERIFY(all_of(hi != lo)) << "hi: " << hi << ", lo: " << lo;
	      VERIFY(all_of(lo != hi)) << "hi: " << hi << ", lo: " << lo;
	      VERIFY(none_of(hi != hi)) << "hi: " << hi << ", lo: " << lo;
	      VERIFY(none_of(hi == lo)) << "hi: " << hi << ", lo: " << lo;
	      VERIFY(none_of(lo == hi)) << "hi: " << hi << ", lo: " << lo;
	      VERIFY(all_of(lo < hi))
		<< "hi: " << hi << ", lo: " << lo << ", lo < hi: " << (lo < hi);
	      VERIFY(none_of(hi < lo)) << "hi: " << hi << ", lo: " << lo;
	      VERIFY(none_of(hi <= lo)) << "hi: " << hi << ", lo: " << lo;
	      VERIFY(all_of(hi <= hi)) << "hi: " << hi << ", lo: " << lo;
	      VERIFY(all_of(hi > lo)) << "hi: " << hi << ", lo: " << lo;
	      VERIFY(none_of(lo > hi)) << "hi: " << hi << ", lo: " << lo;
	      VERIFY(all_of(hi >= lo)) << "hi: " << hi << ", lo: " << lo;
	      VERIFY(all_of(hi >= hi)) << "hi: " << hi << ", lo: " << lo;
	    }
	}
    }
}

TEST_TYPES(V, subscripting, all_enum_types) //{{{1
{
  using T = typename V::value_type;
  using U = stdx::__enum_evaluation_type_t<T>;
  using UV = stdx::simd<U, typename V::abi_type>;
  using std::swap;

  V x = T(~U());
  for (std::size_t i = 0; i < V::size(); ++i)
    {
      COMPARE(x[i], T(~U()));
      x[i] = T();
    }
  COMPARE(x, V());
  for (std::size_t i = 0; i < V::size(); ++i)
    {
      COMPARE(x[i], T());
      x[i] = T(~U());
    }
  COMPARE(x, V(T(~U())));

  if constexpr (requires(T a) { a* a; })
    {
      COMPARE_TYPES(decltype(x[0] * x[0]), decltype(T() * T()));
      COMPARE_TYPES(decltype(x[0] * T()), decltype(T() * T()));
      COMPARE_TYPES(decltype(T() * x[0]), decltype(T() * T()));
      COMPARE_TYPES(decltype(x * x[0]), UV);
      COMPARE_TYPES(decltype(x[0] * x), UV);
    }

  x = V([](auto i) { return T(i.value); });
  for (std::size_t i = 0; i < V::size(); ++i)
      COMPARE(x[i], T(i));
  for (std::size_t i = 0; i + 1 < V::size(); i += 2)
      swap(x[i], x[i + 1]);
  for (std::size_t i = 0; i + 1 < V::size(); i += 2)
    {
      COMPARE(x[i], T(i + 1)) << x;
      COMPARE(x[i + 1], T(i)) << x;
    }
  x = T(1);
  V y = T();
  COMPARE(x[0], T(1));
  x[0] = y[0]; // make sure non-const smart_reference assignment works
  COMPARE(x[0], T(0));
  x = T(1);
  x[0] = x[0]; // self-assignment on smart_reference
  COMPARE(x[0], T(1));

  stdx::simd<typename V::value_type, stdx::simd_abi::scalar> z = T(2);
  x[0] = z[0];
  COMPARE(x[0], T(2));
  x = T(3);
  z[0] = x[0];
  COMPARE(z[0], T(3));
}

TEST_TYPES(V, operators, all_unscoped_enum_types) //{{{1
{
  using M = typename V::mask_type;
  using T = typename V::value_type;

  const V v0{};
  const V v1(1);
  const V v2(2);
  const auto& make_vec = [](auto... values) {
    const T arr[] = {static_cast<T>(values)...};
    return V([&arr](auto i) { return arr[i % sizeof...(values)]; });
  };
  const V v1234567 = make_vec(1, 2, 3, 4, 5, 6, 7);

  // not{{{2
  COMPARE(!v0, M(true));
  COMPARE(!v1, M(false));

  // unary minus{{{2
  {
    using U = stdx::__enum_evaluation_type_t<T>;
    using UV = stdx::simd<U, typename V::abi_type>;
    COMPARE(-v0, UV());
    COMPARE(-v1, -UV(1));
  }

  { // plus{{{2
    V x = v0;
    V y = v0;
    COMPARE(x + y, x);
    VERIFY(std::is_integral_v<typename decltype(x + y)::value_type>);
    COMPARE(x = V(x + T(1)), v1);
    COMPARE(x + x, v2);
    y = v1234567;
    COMPARE(x = V(x + y), make_vec(2, 3, 4, 5, 6, 7, 8));
    COMPARE(x = V(x + -y), v1);
    COMPARE(x, v1);
  }

  { // minus{{{2
    V x = v1;
    V y = v0;
    COMPARE(x - y, x);
    COMPARE(x - T(1), y);
    COMPARE(y, x - T(1));
    COMPARE(x - x, y);
    y = v1234567;
    COMPARE(x = V(y - x), make_vec(0, 1, 2, 3, 4, 5, 6));
    COMPARE(x = V(y - x), v1);
    COMPARE(x, v1);
  }

  { // multiplies{{{2
    V x(1);
    V y(0);
    COMPARE(x * y, y);
    COMPARE(x = V(x * T(2)), V(2));
    COMPARE(x * x, V(4));
    y = v1234567;
    COMPARE(x = V(x * y), make_vec(2, 4, 6, 8, 10, 12, 14));
    y = T(2);
    for (T n : {T(std::numeric_limits<T>::max() - 1),
		T(std::numeric_limits<T>::min())})
      {
	x = T(n / 2);
	COMPARE(x * y, V(n));
      }
    x = T(2);
    COMPARE(x = V(x * make_vec(1, 2, 3)), make_vec(2, 4, 6));
    COMPARE(x, make_vec(2, 4, 6));
  }

  { // divides{{{2
    V x = T(2);
    COMPARE(x / x, V(1));
    COMPARE(T(3) / x, V(T(3) / T(2)));
    COMPARE(x / T(3), V(T(2) / T(3)));
    V y = v1234567;
    COMPARE(y / x, make_vec(0, 1, 1, 2, 2, 3, 3));

    y = make_vec(std::numeric_limits<T>::max(), std::numeric_limits<T>::min());
    V ref = make_vec(std::numeric_limits<T>::max() / 2,
		     std::numeric_limits<T>::min() / 2);
    COMPARE(y / x, ref);

    y = make_vec(std::numeric_limits<T>::min(), std::numeric_limits<T>::max());
    ref = make_vec(std::numeric_limits<T>::min() / 2,
		   std::numeric_limits<T>::max() / 2);
    COMPARE(y / x, ref);

    y = make_vec(std::numeric_limits<T>::max(),
		 std::numeric_limits<T>::min() + 1);
    COMPARE(y / y, V(1));

    ref = make_vec(2 / std::numeric_limits<T>::max(),
		   2 / (std::numeric_limits<T>::min() + 1));
    COMPARE(x / y, ref);
    COMPARE(x = V(x / y), ref);
    COMPARE(x, ref);
  } // }}}2
}

// }}}
// vim: foldmethod=marker
