#!/bin/bash
otherrepo=$1

from_gcc() {
  sed -e 's,libstdc++-v3/include/experimental/bits/,experimental/bits/,g' \
      -e 's,libstdc++-v3/include/experimental/simd,experimental/simd\>,g' \
      -e 's,libstdc++-v3/testsuite/experimental/simd/tests/\(abs\|math_.arg\|fpclassify\|frexp\|hypot3_fma\|ldexp_scalbn_scalbln_modf\|logarithm\|remqo\|sincos\|trigonometric\|trunc_ceil_floor\).h,tests/math.cpp,g' \
      -e 's,libstdc++-v3/testsuite/experimental/simd/tests/mask_.*.h,tests/mask.cpp,g' \
      -e 's,libstdc++-v3/testsuite/experimental/simd/tests/\(broadcast\|generator\|operator_cvt\|reductions\|algorithms\).h,tests/simd.cpp,g' \
      -e 's,libstdc++-v3/testsuite/experimental/simd/tests/\(casts\|splits\|split_concat\).h,tests/casts.cpp,g' \
      -e 's,libstdc++-v3/testsuite/experimental/simd/tests/\([a-z_]*\).h,tests/\1.cpp,g'
}

to_gcc() {
  sed -e 's,experimental/bits/,libstdc++-v3/include/experimental/bits/,g' \
      -e 's,experimental/simd\>,libstdc++-v3/include/experimental/simd,g' \
      -e 's,tests/math.cpp,libstdc++-v3/testsuite/experimental/simd/tests/*.h,g' \
      -e 's,tests/mask.cpp,libstdc++-v3/testsuite/experimental/simd/tests/*.h,g' \
      -e 's,tests/simd.cpp,libstdc++-v3/testsuite/experimental/simd/tests/*.h,g' \
      -e 's,tests/casts.cpp,libstdc++-v3/testsuite/experimental/simd/tests/casts.h,g' \
      -e 's,tests/\([a-z_]*\).cpp,libstdc++-v3/testsuite/experimental/simd/tests/\1.h,g'
}

if [[ -d $otherrepo/gcc ]]; then
  fix_patch_paths=from_gcc
else
  fix_patch_paths=to_gcc
fi

yes_no() {
  while true; do
    read -s -n 1 yesno
    [[ $yesno == "y" || $yesno == "Y" ]] && echo && return 0
    [[ $yesno == "n" || $yesno == "N" ]] && echo && return 1
  done
}

process_revision() {
  rev=$1
  git -C $otherrepo show $rev | $fix_patch_paths > "$rev".diff
  git apply --index "$rev".diff
  while (($? != 0)); do
    echo "Try again with manual diff edit? [y/n] "
    yes_no || return 1
    vim "$rev".diff
    git apply --index "$rev".diff
  done
  rm "$rev".diff
  git commit -e -m "$(git -C $otherrepo show --format='%s%n%n%b' -s $rev)"
}

if (( $2 > 0 && $2 < 100 )); then
  for ((i = $2; i >= 0; i--)); do
    rev="HEAD~$i"
    git -C $otherrepo show $rev
    echo -n "Apply? [y/n] "
    yes_no && process_revision "$rev"
  done
else
  process_revision $2
fi
