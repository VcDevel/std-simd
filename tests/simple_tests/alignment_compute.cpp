#include<experimental/simd>

#include<array>
#include<vector>
#include<cstdint>
#include<cstdlib>
#include<type_traits>

#include<experimental/simd>
namespace stdx = std::experimental;


using uint8v_t = stdx::native_simd<uint8_t>;
using uint8v_mask_t = stdx::native_simd_mask<uint8_t>;
//using mask_cpu_t = min_uint_t<stdx::native_simd_mask<uint8_t>::size()>;



int main()
{
	std::array<uint8_t,128> data;
	uint8v_t hi(&data[0],stdx::__proposed::aligned<3>);

	std::array<float,128> dataf;
	stdx::native_simd<float> vf(&dataf[0],stdx::__proposed::aligned<3>);
	return 0;
}

