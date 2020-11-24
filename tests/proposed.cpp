/*{
Copyright © 2010-2019 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH
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

}*/

//#define UNITTEST_ONLY_XTEST 1
#include "unittest.h"

template <class... Ts> using base_template = std::experimental::simd<Ts...>;
#include "testtypes.h"

using std::experimental::__proposed::resizing_simd_cast;

#ifdef __STRICT_ANSI__
#define CONSTEXPR_ const
#else
#define CONSTEXPR_ constexpr
#endif

TEST_TYPES(V, resizing_simd_cast, all_test_types)
  {
    using T = typename V::value_type;
    using M = typename V::mask_type;
    stdx::__execute_n_times<stdx::simd_abi::max_fixed_size<T>>([](auto ii) {
      CONSTEXPR_ V seq([](int i) { return i; });
      CONSTEXPR_ M kseq = V([](int i) { return i & 1; }) == 1;
      constexpr int N = ii + 1;
      using V0 = stdx::__deduced_simd<T, N>;
      using V1 = stdx::fixed_size_simd<T, N>;
      using M0 = typename V0::mask_type;
      using M1 = typename V1::mask_type;
      const auto v0 = resizing_simd_cast<V0>(seq);
      const auto v1 = resizing_simd_cast<V1>(seq);
      const auto m0 = resizing_simd_cast<M0>(kseq);
      const auto m1 = resizing_simd_cast<M1>(kseq);
      COMPARE(typeid(v0), typeid(V0));
      COMPARE(typeid(v1), typeid(V1));
      COMPARE(typeid(m0), typeid(M0));
      COMPARE(typeid(m1), typeid(M1));
      COMPARE(v0, V0([](int i) { return i < int(V::size()) ? i : 0; }));
      COMPARE(v1, V1([](int i) { return i < int(V::size()) ? i : 0; }));
      COMPARE(m0, V0([](int i) { return i < int(V::size()) ? i & 1 : 0; }) == 1);
      COMPARE(m1, V1([](int i) { return i < int(V::size()) ? i & 1 : 0; }) == 1);
    });
  }
