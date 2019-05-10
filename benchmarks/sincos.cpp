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

#include "bench.h"

struct Sine {
    static constexpr char name[] = "Sine";
};
struct Cosine {
    static constexpr char name[] = "Cosine";
};

MAKE_VECTORMATH_OVERLOAD(sin)
MAKE_VECTORMATH_OVERLOAD(cos)

template <bool Latency, class T, class What> double benchmark()
{
    T a = T() + 2;
    return time_mean<5'000'000>([&]() {
        fake_modify(a);
        using ::sin;
        using ::cos;
        using std::sin;
        using std::cos;
        T r = std::is_same_v<What, Sine> ? sin(a) : cos(a);
        if constexpr (Latency)
            a = r;
        else
            fake_read(r);
    });
}

int main()
{
    bench_all<float, Sine>();
    bench_all<float, Cosine>();
    bench_all<double, Sine>();
    bench_all<double, Cosine>();
}
