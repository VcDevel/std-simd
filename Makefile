CXX ?= c++
SHELL := /bin/bash -o pipefail
build_dir := $(shell which $(CXX))
tmp := "case $$(readlink -f $(build_dir)) in *icecc) which $${ICECC_CXX:-g++};; *) echo $(build_dir);; esac"
build_dir := $(shell sh -c $(tmp))
build_dir := $(realpath $(build_dir))
build_dir := build-$(subst /,-,$(build_dir:/%=%))
cols := $(shell sh -c '{ stty size 2>/dev/null || echo 0 80; }|cut -d" " -f2')
cores := $(shell sh -c 'grep -c processor /proc/cpuinfo')

NINJA ?= $(shell which ninja)
ifeq (,$(NINJA))
	GENERATOR :=
	HELP_TARGET := --target help
	BUILD_FLAGS := $(MAKEFLAGS)
else
	GENERATOR := -G Ninja
	HELP_TARGET := -- -t targets all
	BUILD_FLAGS := -j 100 -k $(cores)
endif

ifeq (,$(CMAKE_TOOLCHAIN_FILE))
	CMAKE_ARGS :=
else
	CMAKE_ARGS := -DCMAKE_TOOLCHAIN_FILE=$(CMAKE_TOOLCHAIN_FILE)
endif

CMAKE=cmake
BUILD_OUTPUT_TRANSFORMATION ?= -e 's/std::\(experimental::\([a-z_0-9]\+::\)\?\)\?/⠶/g'
FIX_OUTPUT=sed -u $(BUILD_OUTPUT_TRANSFORMATION)|stdbuf -oL fold -s -w $(cols)

test: $(build_dir)/CMakeCache.txt
	$(CMAKE) --build $(build_dir) --target all -- $(BUILD_FLAGS) | $(FIX_OUTPUT)
	$(CMAKE) --build $(build_dir) --target test_random -- $(BUILD_FLAGS) | $(FIX_OUTPUT)

help: $(build_dir)/CMakeCache.txt
	@echo "Compiler_Explorer_AVX512"
	@echo "Compiler_Explorer_Skylake"
	@echo "Compiler_Explorer_Nehalem"
	@$(CMAKE) --build $(build_dir) $(HELP_TARGET)

ccmake:
	@test -n "$(build_dir)"
	@mkdir -p "$(build_dir)"
	ccmake $(GENERATOR) $(CMAKE_ARGS) -Htests -B"$(build_dir)"

Compiler_Explorer_AVX512:
	$(CXX) -Wall -I. -S -std=c++17 -O2 -march=skylake-avx512 -masm=intel $(CXXFLAGS) -o - ce.cpp | \
		egrep -v -e '^\s+\.(weak|align|hidden|section|type|file|text|p2align|cfi|size|globl|ident)' -e '^.LF' > ce.tmp
	sed /\.intel_syntax/d ce.tmp | c++filt > ce.asm
	sed -n '/ret/q;p' ce.tmp | llvm-mca-10 --mcpu=skylake-avx512 > ce.mca
	@rm ce.tmp

Compiler_Explorer_Skylake:
	$(CXX) -Wall -I. -S -std=c++17 -O2 -march=skylake -masm=intel $(CXXFLAGS) -o - ce.cpp | \
		egrep -v -e '^\s+\.(weak|align|hidden|section|type|file|text|p2align|cfi|size|globl|ident)' -e '^.LF' > ce.tmp
	sed /\.intel_syntax/d ce.tmp | c++filt > ce.asm
	sed -n '/ret/q;p' ce.tmp | llvm-mca-10 --mcpu=skylake > ce.mca
	@rm ce.tmp

Compiler_Explorer_Nehalem:
	$(CXX) -Wall -I. -S -std=c++17 -O2 -march=nehalem -masm=intel $(CXXFLAGS) -o - ce.cpp | \
		egrep -v -e '^\s+\.(weak|align|hidden|section|type|file|text|p2align|cfi|size|globl|ident)' -e '^.LF' > ce.tmp
	sed /\.intel_syntax/d ce.tmp | c++filt > ce.asm
	sed -n '/ret/q;p' ce.tmp | llvm-mca-10 --mcpu=nehalem > ce.mca
	@rm ce.tmp

%:: $(build_dir)/CMakeCache.txt
	$(CMAKE) --build $(build_dir) --target $* -- $(BUILD_FLAGS) | $(FIX_OUTPUT)

$(build_dir)/CMakeCache.txt:
	@test -n "$(build_dir)"
	@mkdir -p "$(build_dir)"
	@test -e "$(build_dir)/CMakeCache.txt" || $(CMAKE) $(GENERATOR) $(CMAKE_ARGS) -Htests -B"$(build_dir)"

print_build_dir:
	@echo "$(PWD)/$(build_dir)"

clean_builddir:
	rm -rf "$(build_dir)"

# the following rule works around %:: grabbing the Makefile rule and thus stops it from running every time
Makefile:
	@true

install:
	./install.sh

benchmarks:
	cd benchmarks && for i in *.cpp; do ./run.sh $$i; done

benchmark-%:
	cd benchmarks && ./run.sh $*

.PHONY: print_build_dir clean_builddir install benchmarks
