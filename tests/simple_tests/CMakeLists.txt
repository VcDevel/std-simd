cmake_minimum_required(VERSION 3.14)

add_executable(alignment_compute alignment_compute.cpp)
target_compile_options(alignment_compute PUBLIC 
	"$<$<CONFIG:Release>:-march=native>"
	"$<$<CONFIG:Debug>:-march=native>"
	"$<$<CONFIG:RelWithDebInfo>:-march=native>"
	"$<$<CONFIG:MinSizeRel>:-march=native>"
)
set_target_properties(alignment_compute PROPERTIES
            CXX_STANDARD 20
            CXX_STANDARD_REQUIRED ON)

		message(WARNING "${CMAKE_CURRENT_SOURCE_DIR}/../..")
target_include_directories(alignment_compute PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../..")
