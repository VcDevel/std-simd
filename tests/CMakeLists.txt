cmake_minimum_required(VERSION 3.0)
cmake_policy(SET CMP0054 NEW)

if(CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR)
   message(FATAL_ERROR "You don't want to configure in the source directory!")
endif()

project("std::simd tests" CXX)
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
set(CMAKE_REQUIRED_INCLUDES "${CMAKE_CURRENT_SOURCE_DIR}/..")

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang" AND "${CMAKE_CXX_COMPILER_VERSION}" VERSION_GREATER "9.99")
   message(WARNING "Compiling with Clang is not officially supported.")
elseif(NOT "${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" OR "${CMAKE_CXX_COMPILER_VERSION}" VERSION_LESS "10.0")
   message(FATAL_ERROR "This std::experimental::simd implementation requires GCC 10 or higher. ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}")
endif()

execute_process(COMMAND "${CMAKE_CXX_COMPILER}" -dumpmachine
   OUTPUT_VARIABLE dumpmachine
   OUTPUT_STRIP_TRAILING_WHITESPACE)
string(REPLACE "-" ";" dumpmachine "${dumpmachine}")
list(GET dumpmachine 0 target_arch)
if (NOT target_arch STREQUAL CMAKE_SYSTEM_PROCESSOR)
   message(STATUS "Compiling for ${target_arch} (cmake thinks ${CMAKE_SYSTEM_PROCESSOR})")
endif()

include (AddTargetProperty)
include (AddCompilerFlag)
include (CMakeParseArguments)

set(Vc_X86 FALSE)
set(Vc_ARM FALSE)
set(Vc_AARCH64 FALSE)
if("${target_arch}" MATCHES "(x86|AMD64|amd64)")
   set(Vc_X86 TRUE)

   execute_process(
      COMMAND ${CMAKE_CXX_COMPILER} -dM -march=native -E -o- -x c++ /dev/null
      OUTPUT_VARIABLE predefined
      )
   macro(check_predefined_macro name)
      string(FIND "${predefined}" "define __${name}__ 1" HAVE_${name})
      if(HAVE_${name} EQUAL -1)
         message(STATUS "Checking host system for ${name}: No.")
         set(HAVE_${name} FALSE)
      else()
         message(STATUS "Checking host system for ${name}: Yes.")
         set(HAVE_${name} TRUE)
      endif()
   endmacro()
   check_predefined_macro(SSE)
   check_predefined_macro(SSE2)
   check_predefined_macro(SSE3)
   check_predefined_macro(SSSE3)
   check_predefined_macro(SSE4_1)
   check_predefined_macro(SSE4_2)
   check_predefined_macro(SSE4A)
   check_predefined_macro(AVX)
   check_predefined_macro(AVX2)
   check_predefined_macro(AVX512F)
   check_predefined_macro(AVX512BW)
   check_predefined_macro(AVX512VL)
   check_predefined_macro(AVX512CD)
   check_predefined_macro(AVX512DQ)
   check_predefined_macro(AVX512ER)
   check_predefined_macro(AVX512PF)
   check_predefined_macro(FMA)
   check_predefined_macro(FMA4)
   if (HAVE_AVX512F AND HAVE_AVX512PF AND HAVE_AVX512ER)
      set(HAVE_KNL TRUE)
   else()
      set(HAVE_KNL FALSE)
   endif()
   if (HAVE_AVX512F AND HAVE_AVX512VL AND HAVE_AVX512BW AND HAVE_AVX512DQ AND HAVE_AVX512CD)
      set(HAVE_AVX512 TRUE)
   else()
      set(HAVE_AVX512 FALSE)
   endif()
elseif("${target_arch}" MATCHES "arm")
   set(Vc_ARM TRUE)
elseif("${target_arch}" STREQUAL "aarch64")
   set(Vc_AARCH64 TRUE)
   if (CMAKE_CROSSCOMPILING)
     find_program(QEMU "qemu-aarch64")
     if (QEMU)
       set(CMAKE_CROSSCOMPILING_EMULATOR "${QEMU}")
     endif()
   endif()
else()
   message(WARNING "No optimized implementation of the Vc types available for ${target_arch}")
endif()

# set up ccache#{{{
##################################################################
option(USE_CCACHE "If enabled, ccache will be used (if it exists on the system) to speed up recompiles." OFF)
if(USE_CCACHE)
   find_program(CCACHE_COMMAND ccache)
   if(CCACHE_COMMAND)
      mark_as_advanced(CCACHE_COMMAND)
      set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "${CCACHE_COMMAND}")
   endif()
endif()#}}}

# Set default CMAKE_BUILD_TYPE to Release#{{{
##################################################################
if(NOT CMAKE_BUILD_TYPE)
   set(CMAKE_BUILD_TYPE Release CACHE STRING
      "Choose the type of build, options are: None Debug Release RelWithDebug RelWithDebInfo MinSizeRel."
      FORCE)
endif(NOT CMAKE_BUILD_TYPE)

if(CMAKE_BUILD_TYPE STREQUAL "" AND NOT CMAKE_CXX_FLAGS MATCHES "-O[123]")
   message(STATUS "WARNING! It seems you are compiling without optimization. Please set CMAKE_BUILD_TYPE.")
endif(CMAKE_BUILD_TYPE STREQUAL "" AND NOT CMAKE_CXX_FLAGS MATCHES "-O[123]")#}}}

# Set default C(XX)FLAGS and includes#{{{
##################################################################
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
   set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++2a -W -Wall -Wextra -Wpedantic -Wcast-align -Wshadow -Wundef -Wold-style-cast -ffp-contract=fast -ftemplate-depth=512")
else()
   set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++2a -W -Wall -Wextra -Wpedantic -Wcast-align -Wshadow -Wundef -Wold-style-cast -fabi-version=0 -fabi-compat-version=0 -ffp-contract=fast -ftemplate-depth=512 -fmax-errors=10")
endif()
if(Vc_X86)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mfpmath=sse")
endif()

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/.. ${CMAKE_CURRENT_SOURCE_DIR}/virtest)
#}}}

# Look for the Intel SDE if we're running on x86 and Linux#{{{
##################################################################
if(Vc_X86 AND CMAKE_SYSTEM_NAME STREQUAL "Linux")
   find_program(RUN_ON_AVX512 run_on_avx512 DOC "Path to a script that runs the executable on a skylake-avx512 machine")

   macro(Vc_find_sde)
      find_program(INTEL_SDE sde64 ${ARGN} DOC "Path to the Intel Software Development Emulator")
      if(INTEL_SDE)
         execute_process(COMMAND ${INTEL_SDE} -help RESULT_VARIABLE _sde_usable OUTPUT_QUIET ERROR_QUIET)
         if(NOT _sde_usable LESS 2)
            unset(INTEL_SDE CACHE)
            find_program(INTEL_SDE sde ${ARGN} NO_DEFAULT_PATH DOC "Path to the Intel Software Development Emulator")
            if(INTEL_SDE)
               execute_process(COMMAND ${INTEL_SDE} -help RESULT_VARIABLE _sde_usable OUTPUT_QUIET ERROR_QUIET)
               if(NOT _sde_usable LESS 2)
                  set(INTEL_SDE FALSE)
               endif()
            endif()
         endif()
      endif()
   endmacro()

   file(GLOB SDE_DIRS /opt/intel/*)
   list(SORT SDE_DIRS)
   list(REVERSE SDE_DIRS)
   Vc_find_sde(${SDE_DIRS} "$ENV{HOME}/.cache/sde/")

   # if running a dashboard cycle and no installed SDE was found, download and use it automatically
   if(NOT "$ENV{DASHBOARD_TEST_FROM_CTEST}" STREQUAL "" AND NOT INTEL_SDE)
      find_program(_bin_sh sh)
      find_program(_wget wget)
      if(_bin_sh AND _wget AND DEFINED ENV{HOME})
         option(DOWNLOAD_INTEL_SDE "Download the Intel Software Development Emulator to execute tests on different ISAs" ON)
         if(DOWNLOAD_INTEL_SDE)
            message(STATUS "Downloading Intel SDE:")
            file(MAKE_DIRECTORY "$ENV{HOME}/.cache/sde")
            execute_process(COMMAND ${_bin_sh} "${CMAKE_SOURCE_DIR}/../scripts/download_intel_sde.sh"
               WORKING_DIRECTORY "$ENV{HOME}/.cache/sde"
               TIMEOUT 20
               RESULT_VARIABLE res)
            if(${res} EQUAL 0)
               Vc_find_sde("$ENV{HOME}/.cache/sde/" NO_DEFAULT_PATH)
            endif()
         endif()
      endif()
      mark_as_advanced(_bin_sh _wget)
   endif()

   if(INTEL_SDE)
      execute_process(COMMAND ${INTEL_SDE} -version OUTPUT_VARIABLE sde_version ERROR_QUIET)
      string(REGEX MATCH "Version: +[0-9.]+" sde_version "${sde_version}")
      message(STATUS "Intel SDE ${sde_version}")
   else()
      message(STATUS "Intel SDE not found.")
   endif()
endif()#}}}

# Set up make targets#{{{
##################################################################
add_custom_target(other VERBATIM)
add_custom_target(NoSIMD COMMENT "build non-SIMD code" VERBATIM)
if(Vc_X86)
   add_custom_target(SSE COMMENT "build SSE code" VERBATIM)
   add_custom_target(SSE1 COMMENT "build SSE1 code" VERBATIM)
   add_custom_target(SSE2 COMMENT "build SSE2 code" VERBATIM)
   add_custom_target(SSSE3 COMMENT "build SSSE3 code" VERBATIM)
   add_custom_target(SSE4_2 COMMENT "build SSE4.2 code" VERBATIM)
   add_dependencies(SSE SSE1 SSE2 SSSE3 SSE4_2)
   add_custom_target(AVX COMMENT "build AVX code" VERBATIM)
   add_custom_target(AVX2 COMMENT "build AVX2 code" VERBATIM)
   add_custom_target(KNL COMMENT "build KNL code" VERBATIM)
   add_custom_target(AVX512 COMMENT "build AVX512 code" VERBATIM)
elseif(Vc_ARM)
   add_custom_target(ARMV7 COMMENT "build ARMV7 code" VERBATIM)
   add_custom_target(ARMV8 COMMENT "build ARMV8 code" VERBATIM)
elseif(Vc_AARCH64)
   add_custom_target(NEON COMMENT "build NEON code" VERBATIM)
endif()#}}}

# Unit tests#{{{
##################################################################
include (CTest)
add_custom_target(test_random ${CMAKE_CTEST_COMMAND} --schedule-random
   USES_TERMINAL
   )
if(NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/virtest/vir/test.h")
   # first try to resolve the issue automatically
   message(STATUS "virtest missing: calling 'git submodule update --init'")
   execute_process(
      COMMAND git submodule update --init
      WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
      )
endif()
if(NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/virtest/vir/test.h")
   message(FATAL_ERROR "Unit tests enabled but virtest is missing. Call 'git submodule update' to clone the required unit test framework.")
endif()
add_custom_target(build_tests ALL VERBATIM)
#}}}

if(NOT "$ENV{TRAVIS_OS_NAME}" STREQUAL "")
   set(CMAKE_CXX_FLAGS_RELEASE "-O1 -DNDEBUG") # try to not time out, -O0 is faster
endif()

add_definitions(-DCOMPILE_FOR_UNIT_TESTS -D_GLIBCXX_SIMD_NO_OPTIMIZATION_WARNINGS)

option(ENABLE_UBSAN "Enable build of unit tests with undefined behavior sanitizer" OFF)
if(ENABLE_UBSAN)
   AddCompilerFlag("-fsanitize=undefined")
endif()

execute_process(COMMAND ${CMAKE_CXX_COMPILER} -print-prog-name=objcopy OUTPUT_VARIABLE OBJCOPY OUTPUT_STRIP_TRAILING_WHITESPACE)

function(vc_download_testdata)#{{{
   set(_deps)
   foreach(fun sincos asin acos atan ln log2 log10)
      foreach(type f d e)
         if("${type}" STREQUAL "f")
            set(filename "reference-${fun}-sp.dat")
         elseif("${type}" STREQUAL "d")
            set(filename "reference-${fun}-dp.dat")
         else()
            set(filename "reference-${fun}-ep.dat")
         endif()
         add_custom_command(OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/${filename}"
            COMMAND ${CMAKE_COMMAND} -Dfilename=${filename} -P ${CMAKE_CURRENT_SOURCE_DIR}/download.cmake
            DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/download.cmake
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
            COMMENT "Downloading Test Data: ${filename}"
            VERBATIM
            )
         if(OBJCOPY)
            string(REGEX REPLACE "[.-]" "_" toreplace "_binary_${filename}_")
            string(LENGTH "${fun}" fun_len)
            set(replacement "_ZN14reference_dataIN8function${fun_len}${fun}E${type}E")
            if (Vc_X86)
              set(objcopy_args "-O;elf64-x86-64;-B;i386")
            elseif(Vc_AARCH64)
              set(objcopy_args "-O;elf64-littleaarch64;-B;aarch64")
            elseif(Vc_ARM)
              set(objcopy_args "-O;elf32-littlearm;-B;arm")
            endif()
            add_custom_command(OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/${filename}.o"
               COMMAND ${OBJCOPY} -I binary ${objcopy_args}
               --redefine-sym ${toreplace}start=${replacement}6begin_E
               --redefine-sym ${toreplace}end=${replacement}4end_E
               --redefine-sym ${toreplace}size=${replacement}5size_E
               ${filename} ${filename}.o
               DEPENDS "${CMAKE_CURRENT_BINARY_DIR}/${filename}"
               WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
               COMMENT "Converting Test Data: ${filename}.o"
               VERBATIM
               )
            list(APPEND _deps "${CMAKE_CURRENT_BINARY_DIR}/${filename}.o")
         endif()
         list(APPEND _deps "${CMAKE_CURRENT_BINARY_DIR}/${filename}")
      endforeach()
   endforeach()
   add_custom_target(download-testdata ALL
      DEPENDS ${_deps}
      )

   add_dependencies(NoSIMD download-testdata)
   if(Vc_X86)
      add_dependencies(SSE2 download-testdata)
      add_dependencies(SSE4_2 download-testdata)
      add_dependencies(AVX download-testdata)
      add_dependencies(AVX2 download-testdata)
      add_dependencies(KNL download-testdata)
      add_dependencies(AVX512 download-testdata)
   elseif(Vc_ARM)
      add_dependencies(ARMV7 download-testdata)
      add_dependencies(ARMV8 download-testdata)
   elseif(Vc_AARCH64)
      add_dependencies(NEON download-testdata)
   endif()
endfunction()
vc_download_testdata()#}}}

# typeToString can use cxxabi for demangling
CHECK_CXX_SOURCE_COMPILES("#include <cxxabi.h>
int main() { return 0; }" cxx_abi_header_works)
if(cxx_abi_header_works)
   add_definitions(-DHAVE_CXX_ABI_H)
endif()

function(vc_target_setup name sde_cpuid flags)#{{{
   string(REPLACE "|" ";" flags "${flags}")
   set(result)
   AddCompilerFlag("${flags}" CXX_FLAGS result CXX_RESULT ok)
   if(ok)
      set(Vc_${name}_flags ${result} PARENT_SCOPE)
      message(STATUS "Building tests for ${name}: enabled")
      list(APPEND vc_all_target_variants ${name})
      set(vc_all_target_variants ${vc_all_target_variants} PARENT_SCOPE)
      if(sde_cpuid)
         set(sde_cpuid_${name} "-${sde_cpuid}" PARENT_SCOPE)
      endif()
   else()
      message(STATUS "Building tests for ${name}: disabled")
   endif()
endfunction()#}}}

# sets Vc_nosimd_flags, Vc_sse2_flags, ...
if(Vc_X86)
   vc_target_setup(nosimd mrm "-mno-sse")
   vc_target_setup(sse2 mrm "-march=nocona;-mno-sse3")
   vc_target_setup(ssse3 mrm "-march=core2")
   vc_target_setup(sse4_2 nhm "-march=nehalem")
   vc_target_setup(avx snb "-march=sandybridge")
   vc_target_setup(avx2 hsw "-march=haswell")
   #vc_target_setup(knl knl "-march=knl")
   vc_target_setup(avx512 skx "-march=skylake-avx512")
elseif(Vc_ARM)
   vc_target_setup(armv7 "" "-march=armv7-a+simd;-mfloat-abi=softfp")
   vc_target_setup(armv8 "" "-march=armv8-a+simd;-mfloat-abi=softfp")
   find_program(RUN_ON_ARM run_on_armel)
elseif(Vc_AARCH64)
   vc_target_setup(neon "" "-march=armv8-a")
   find_program(RUN_ON_AARCH64 run_on_aarch64)
endif()

macro(vc_add_run_target _target emulator run_target_list)#{{{
   if("${CMAKE_GENERATOR}" MATCHES "Visual Studio")
      # do nothing. This just clutters the solution explorer
   else()
      if(_ROUNDINGMODES)
         set(_test_args "--roundingmodes")
      else()
         set(_test_args "")
      endif()
      if(emulator)
         add_custom_target(run_${_target}
           ${emulator} $<TARGET_FILE:${_target}> "-v" ${_test_args}
            DEPENDS ${_target}
            COMMENT "Execute ${_target} test (via emulator)"
            VERBATIM
            )
      else()
         add_custom_target(run_${_target}
            ${_target} -v ${_test_args}
            DEPENDS ${_target}
            COMMENT "Execute ${_target} test"
            VERBATIM
            )
      endif()
      list(APPEND ${run_target_list} "run_${target}")
   endif()
endmacro()#}}}

function(vc_add_test name) #{{{
   if($ENV{VcSkipTests} MATCHES "${name}")
      return()
   endif()
   set(_only "$ENV{VcOnlyTests}")
   if(NOT ("${_only}" STREQUAL "" OR "${_only}" MATCHES "${name}"))
      return()
   endif()

   cmake_parse_arguments("" "ROUNDINGMODES;NO_TESTABIS;NO_TESTTYPES;SINGLE_TESTTYPE;EXCLUDE_FROM_ALL" "SOURCE" "DEFINITIONS" ${ARGN})

   if(_SOURCE)
      set(src "${_SOURCE}")
   else()
      set(src "${name}.cpp")
   endif()

   set(run_targets)
   foreach(impl ${vc_all_target_variants})
      set(_target "${name}_${impl}")
      set(flags "${Vc_COMPILE_FLAGS}")
      if(DEFINED Vc_${impl}_flags)
         list(APPEND flags "${Vc_${impl}_flags}")
      endif()
      if(_ROUNDINGMODES)
         list(APPEND flags "-frounding-math")
      endif()

      string(REPLACE ";" " " link_flags "${flags}")

      string(TOUPPER "${impl}" label)
      set(emulator FALSE)
      set(can_exec_test "${HAVE_${label}}")
      if(impl STREQUAL "nosimd")
         set(label NoSIMD)
         set(can_exec_test TRUE)
      elseif(NOT can_exec_test)
         if((impl STREQUAL "KNL" AND HAVE_AVX512PF AND HAVE_AVX512ER) OR
            (impl STREQUAL "AVX512" AND HAVE_AVX512DQ AND HAVE_AVX512VL AND HAVE_AVX512BW))
            set(can_exec_test TRUE)
         elseif(Vc_X86 AND RUN_ON_AVX512 AND "${impl}" STREQUAL "avx512")
            set(can_exec_test TRUE)
            set(emulator "${RUN_ON_AVX512}")
         elseif(Vc_X86 AND INTEL_SDE)
            set(can_exec_test TRUE)
            set(emulator "${INTEL_SDE};${sde_cpuid_${impl}};--")
         elseif(Vc_ARM AND RUN_ON_ARM)
            set(can_exec_test TRUE)
            set(emulator "${RUN_ON_ARM}")
         elseif(Vc_AARCH64 AND RUN_ON_AARCH64)
            set(can_exec_test TRUE)
            set(emulator "${RUN_ON_AARCH64}")
         else()
            set(can_exec_test FALSE)
         endif()
      endif()
      if(_NO_TESTTYPES)
         set(type_split " ")
      elseif(_SINGLE_TESTTYPE)
         set(type_split "ldouble" "float" "double" "uint" "llong" "long" "uchar" "int" "ushort" "short" "ulong" "schar" "ullong" "wchar" "char16" "char32" "char")
      else()
         set(type_split "ldouble,float,double,schar,uchar" "llong,long,ullong,ulong,char,wchar" "int,short,uint,ushort,char16,char32")
      endif()
      if(_NO_TESTABIS)
         set(abi_split " ")
      else()
         set(abi_split 0 1 2 3 4 5 6 7 8)
      endif()
      foreach(types ${type_split})
         foreach(abis ${abi_split})
            if(impl STREQUAL "nosimd")#{{{
               set(target ${_target})
            else()
               string(TOLOWER "${_target}" target)
            endif()#}}}
            if(NOT _NO_TESTTYPES)
               string(REPLACE "," "_" target "${target}_${types}")
            endif()
            if(NOT _NO_TESTABIS)
               set(target "${target}_${abis}")
            endif()

            if(OBJCOPY)
               list(APPEND _DEFINITIONS "_GLIBCXX_SIMD_LINK_TESTDATA")
               if("${name}" STREQUAL "math")
                  foreach(fun sincos asin acos atan)
                     foreach(filename reference-${fun}-sp.dat reference-${fun}-dp.dat reference-${fun}-ep.dat)
                        set(src ${src} ${CMAKE_CURRENT_BINARY_DIR}/${filename}.o)
                     endforeach()
                  endforeach()
               elseif("${name}" STREQUAL "logarithm")
                  foreach(fun ln log2 log10)
                     foreach(filename reference-${fun}-sp.dat reference-${fun}-dp.dat reference-${fun}-ep.dat)
                        set(src ${src} ${CMAKE_CURRENT_BINARY_DIR}/${filename}.o)
                     endforeach()
                  endforeach()
               endif()
            endif()

            add_executable(${target} EXCLUDE_FROM_ALL ${src})
            set_property(TARGET ${target} APPEND PROPERTY COMPILE_DEFINITIONS "${_DEFINITIONS}")
            set_property(TARGET ${target} APPEND PROPERTY COMPILE_OPTIONS "${flags}")
            set_property(TARGET ${target} APPEND PROPERTY LINK_FLAGS "${link_flags}")
            if(NOT _NO_TESTTYPES)
               set_property(TARGET ${target} APPEND PROPERTY COMPILE_DEFINITIONS "TESTTYPES=${types}")
            endif()
            if(NOT _NO_TESTABIS)
               set_property(TARGET ${target} APPEND PROPERTY COMPILE_DEFINITIONS "ABITYPES=${abis}")
            endif()
            if(NOT _EXCLUDE_FROM_ALL)
               add_target_property(${target} LABELS "${label}")
               add_dependencies(build_tests ${target})
               add_dependencies(${label} ${target})
            endif()
            if(${can_exec_test}) # add test and run target#{{{
               if(NOT _EXCLUDE_FROM_ALL)
                  if(_ROUNDINGMODES)
                     set(_test_args "--roundingmodes")
                  else()
                     set(_test_args "")
                  endif()
                  if(emulator)
                     add_test(NAME ${target}
                       COMMAND ${emulator} $<TARGET_FILE:${target}> ${_test_args}
                        )
                  else()
                     add_test(${target} "${CMAKE_CURRENT_BINARY_DIR}/${target}" ${_test_args})
                  endif()
                  set_property(TEST ${target} PROPERTY LABELS "${label}")
               endif()
               vc_add_run_target(${target} "${emulator}" run_targets)
            endif()#}}}
            if(impl STREQUAL "nosimd")
               break()
            endif()
         endforeach()
      endforeach()
   endforeach()
   if(run_targets)
      add_custom_target(run_${name}_all
         COMMENT "Execute all ${name} tests"
         VERBATIM
         )
      add_dependencies(run_${name}_all ${run_targets})
   endif()
endfunction() #}}}

vc_add_test(sfinae NO_TESTTYPES)
vc_add_test(loadstore SINGLE_TESTTYPE DEFINITIONS ONE_RANDOM_ARITHMETIC_TYPE)
vc_add_test(allcvt_loadstore SINGLE_TESTTYPE SOURCE loadstore.cpp SINGLE_TESTTYPE EXCLUDE_FROM_ALL)
vc_add_test(mask)
vc_add_test(mask_conversions SINGLE_TESTTYPE)
vc_add_test(simd)
vc_add_test(operators)
vc_add_test(integer_operators SINGLE_TESTTYPE) # without SINGLE_TESTTYPE GCC gets OOM killed
vc_add_test(casts DEFINITIONS ONE_RANDOM_ARITHMETIC_TYPE)
vc_add_test(allcvt_casts SOURCE casts.cpp EXCLUDE_FROM_ALL SINGLE_TESTTYPE)
vc_add_test(math ROUNDINGMODES)
vc_add_test(specialmath ROUNDINGMODES)
vc_add_test(where NO_TESTTYPES)
vc_add_test(bitset_conversions NO_TESTTYPES)
vc_add_test(proposed SINGLE_TESTTYPE)
vc_add_test(enum NO_TESTTYPES)# NO_TESTABIS)

# ABI tests#{{{
find_program(OBJDUMP objdump)
mark_as_advanced(OBJDUMP)
if(OBJDUMP AND NOT ENABLE_UBSAN) # ubsan changes codegen too much, just skip it
   set(alias_strategies2)
   list(APPEND alias_strategies2 MayAlias VectorBuiltin)

   set(run_targets)
   macro(test_uninitialized _impl)
      set(_target "uninit_${_impl}")
      set(_test test_${_target})
      add_executable(${_target} EXCLUDE_FROM_ALL uninit.cpp)
      set_property(TARGET ${_target} APPEND PROPERTY COMPILE_OPTIONS "${ARGN};-O2")
      add_target_property(${_target} LABELS "${_impl}")
      add_dependencies(${_impl} ${_target})
      add_dependencies(build_tests ${_target})
      add_test(NAME ${_test}
         WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
         COMMAND ${CMAKE_COMMAND} -DOBJDUMP=${OBJDUMP} -DBINARY=$<TARGET_FILE:${_target}> -DIMPL=${_impl}
         -DCOMPILER_IS_CLANG=${Vc_COMPILER_IS_CLANG} -DSYSTEM_NAME=${CMAKE_SYSTEM_NAME}
         -P ${CMAKE_CURRENT_SOURCE_DIR}/uninit.cmake
         )
      set_property(TEST ${_test} PROPERTY LABELS "${_impl}")
      add_custom_target(run_${_target}
         ${CMAKE_COMMAND} -DOBJDUMP=${OBJDUMP} -DBINARY=$<TARGET_FILE:${_target}> -DIMPL=${_impl}
         -DCOMPILER_IS_CLANG=${Vc_COMPILER_IS_CLANG} -DSYSTEM_NAME=${CMAKE_SYSTEM_NAME}
         -P ${CMAKE_CURRENT_SOURCE_DIR}/uninit.cmake
         WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
         DEPENDS ${_target}
         COMMENT "Execute ${_target} test"
         VERBATIM
         )
      list(APPEND run_targets "run_${_target}")
   endmacro()

   macro(test_abi target _impl abi)
      foreach(subtype native fixed_size)
         if("${subtype}" STREQUAL "fixed_size")
            set(suffix "_fixed_size")
         else()
            set(suffix "")
         endif()
         set(_target "${target}${suffix}")
         set(_test test_${_target})
         add_executable(${_target} EXCLUDE_FROM_ALL abi${suffix}.cpp)
         set_property(TARGET ${_target} APPEND PROPERTY COMPILE_DEFINITIONS "_GLIBCXX_SIMD_ABI=${abi}")
         set_property(TARGET ${_target} APPEND PROPERTY COMPILE_OPTIONS "${ARGN};-O2")
         add_target_property(${_target} LABELS "${_impl}")
         add_dependencies(${_impl} ${_target})
         add_dependencies(build_tests ${_target})

         add_test(NAME ${_test}
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
            COMMAND ${CMAKE_COMMAND} -DOBJDUMP=${OBJDUMP} -DBINARY=$<TARGET_FILE:${_target}> -DIMPL=${_impl}
            -DCOMPILER_IS_CLANG=${Vc_COMPILER_IS_CLANG} -DSYSTEM_NAME=${CMAKE_SYSTEM_NAME}
            -P ${CMAKE_CURRENT_SOURCE_DIR}/abi${suffix}.cmake
            )
         set_property(TEST ${_test} PROPERTY LABELS "${_impl}")
         add_custom_target(run_${_target}
            ${CMAKE_COMMAND} -DOBJDUMP=${OBJDUMP} -DBINARY=$<TARGET_FILE:${_target}> -DIMPL=${_impl}
            -DCOMPILER_IS_CLANG=${Vc_COMPILER_IS_CLANG} -DSYSTEM_NAME=${CMAKE_SYSTEM_NAME}
            -P ${CMAKE_CURRENT_SOURCE_DIR}/abi${suffix}.cmake
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
            DEPENDS ${_target}
            COMMENT "Execute ${_target} test"
            VERBATIM
            )
         list(APPEND run_targets "run_${_target}")
      endforeach()
   endmacro()

   if("${target_arch}" MATCHES "[x3-7]86")
      test_uninitialized(SSE ${Vc_sse2_flags})
      test_uninitialized(AVX ${Vc_avx_flags})
      test_uninitialized(KNL ${Vc_knl_flags})

      test_abi(abi_SSE     SSE __sse ${Vc_sse2_flags})
      test_abi(abi_SSE_AVX SSE __sse ${Vc_avx_flags})
      test_abi(abi_AVX     AVX __avx ${Vc_avx_flags})
      test_abi(abi_AVX2    AVX2 __avx ${Vc_avx2_flags})
      #test_abi(abi_AVX512  AVX512 __avx512 ${Vc_avx512_flags})
      #test_abi(abi_KNL     KNL __avx512 ${Vc_knl_flags})
   endif()

   if(run_targets)
      add_custom_target(run_abi_all
         COMMENT "Execute all ABI tests"
         VERBATIM
         )
      add_dependencies(run_abi_all ${run_targets})
   endif()
endif()#}}}

# compile and link test for targets that need to link lots of stuff together#{{{
add_library(linkTestLibDynamic1 SHARED EXCLUDE_FROM_ALL linkTestLib0.cpp linkTestLib1.cpp)
add_library(linkTestLibDynamic2 SHARED EXCLUDE_FROM_ALL linkTestLib0.cpp linkTestLib1.cpp)
add_library(linkTestLibStatic STATIC EXCLUDE_FROM_ALL linkTestLib2.cpp linkTestLib3.cpp)
add_executable(linkTest EXCLUDE_FROM_ALL linkTest0.cpp linkTest1.cpp)
add_dependencies(build_tests linkTest)
add_dependencies(other linkTest)
add_target_property(linkTestLibDynamic1 COMPILE_FLAGS "-DPOSTFIX=A")
add_target_property(linkTestLibDynamic2 COMPILE_FLAGS "-DPOSTFIX=B")
if (Vc_X86)
  set(link_march "-march=native")
elseif (Vc_ARM)
  set(link_march "-march=armv8-a+simd;-mfloat-abi=softfp")
elseif (Vc_AARCH64)
  set(link_march "-march=armv8-a")
endif()
set_property(TARGET linkTestLibDynamic1 APPEND PROPERTY COMPILE_OPTIONS "${link_march}")
set_property(TARGET linkTestLibDynamic2 APPEND PROPERTY COMPILE_OPTIONS "${link_march}")
set_property(TARGET linkTestLibStatic APPEND PROPERTY COMPILE_OPTIONS "${link_march}")
set_property(TARGET linkTest APPEND PROPERTY COMPILE_OPTIONS "${link_march}")
target_link_libraries(linkTest linkTestLibDynamic1 linkTestLibDynamic2 linkTestLibStatic)#}}}

# vim: foldmethod=marker commentstring=#%s
