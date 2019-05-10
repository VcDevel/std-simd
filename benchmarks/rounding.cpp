/*  This file is part of the Vc library. {{{
Copyright © 2019 Matthias Kretz <kretz@kde.org>

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

#include <random>
#include "bench.h"

struct Floor { static constexpr char name[] = "std::floor"; };
struct Ceil { static constexpr char name[] = "std::ceil"; };
struct Round { static constexpr char name[] = "std::round"; };
struct Rint { static constexpr char name[] = "std::rint"; };
struct Nearbyint { static constexpr char name[] = "std::nearbyint"; };

MAKE_VECTORMATH_OVERLOAD(floor)
MAKE_VECTORMATH_OVERLOAD(ceil)
MAKE_VECTORMATH_OVERLOAD(round)
MAKE_VECTORMATH_OVERLOAD(rint)
MAKE_VECTORMATH_OVERLOAD(nearbyint)

static std::mt19937 rnd_gen = std::mt19937(1);

template <class T> T random()
{
    if constexpr (std::is_floating_point_v<T>) {
        std::uniform_real_distribution<T> dis(-10.0, 20.0);
        return dis(rnd_gen);
    } else if constexpr (std::experimental::is_simd_v<T>) {
        return T([](int) { return random<typename T::value_type>(); });
    } else {
        T r = {};
        for (int i = 0; i < sizeof(T) / sizeof(r[0]); ++i) {
            r[i] = random<std::remove_reference_t<decltype(r[0])>>();
        }
        return r;
    }
}

template <bool Latency, class T, class What> double benchmark()
{
    std::vector<T> input;
    input.reserve(1024);
    for (int n = input.capacity(); n; --n) {
        input.push_back(random<T>());
    }
    T a = T();
    int i = 0;
    return time_mean<5'000'000>([&]() {
        a += input[i];
        i = (i + 1) % input.size();
        fake_modify(a);
        using ::floor;
        using ::ceil;
        using ::round;
        using ::rint;
        using ::nearbyint;
        using std::floor;
        using std::ceil;
        using std::round;
        using std::rint;
        using std::nearbyint;
        T r;
        if constexpr (std::is_same_v<What, Floor>)
            r = floor(a);
        else if constexpr (std::is_same_v<What, Ceil>)
            r = ceil(a);
        else if constexpr (std::is_same_v<What, Round>)
            r = round(a);
        else if constexpr (std::is_same_v<What, Rint>)
            r = rint(a);
        else if constexpr (std::is_same_v<What, Nearbyint>)
            r = nearbyint(a);
        if constexpr (Latency)
            a = r;
        else {
            a = T();
            fake_read(r);
        }
    });
}

int main()
{
    bench_all<float, Floor    >();
    bench_all<float, Ceil     >();
    bench_all<float, Round    >();
    bench_all<float, Rint     >();
    bench_all<float, Nearbyint>();
    bench_all<double, Floor    >();
    bench_all<double, Ceil     >();
    bench_all<double, Round    >();
    bench_all<double, Rint     >();
    bench_all<double, Nearbyint>();
}





