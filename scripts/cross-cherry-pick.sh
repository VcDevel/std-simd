#!/bin/bash
stdsimdrepo=$1
rev=$2
gccrepo=$(pwd)
{ cd $stdsimdrepo && git show $rev; } \
  | sed -e 's,experimental/bits/,libstdc++-v3/include/experimental/bits/,g' \
        -e 's,tests/math.cpp,libstdc++-v3/testsuite/experimental/simd/tests/*.h,g' \
        -e 's,tests/mask.cpp,libstdc++-v3/testsuite/experimental/simd/tests/*.h,g' \
        -e 's,tests/simd.cpp,libstdc++-v3/testsuite/experimental/simd/tests/*.h,g' \
        -e 's,tests/casts.cpp,libstdc++-v3/testsuite/experimental/simd/tests/casts.h,g' \
        -e 's,tests/\([a-z_]*\).cpp,libstdc++-v3/testsuite/experimental/simd/tests/\1.h,g' \
  > "$rev".diff
git apply --index "$rev".diff
while (($? != 0)); do
  echo "Try again with manual diff edit? (or Ctrl-C)"
  read || exit
  vim "$rev".diff
  git apply --index "$rev".diff
done
rm "$rev".diff
git commit -e -m "$(cd $stdsimdrepo && git show --format='%s%n%n%b' -s $rev)"
