#!/bin/zsh
stdsimdrepo="${0%/scripts/*}/tests"
for filepath in ../../../../testsuite/experimental/simd/tests/*.h; do
  name="${${filepath##*/}%.h}"
  case "$name" in
    abs|fpclassify|frexp|hypot3_fma|ldexp_scalbn_scalbln_modf|logarithm|math_1arg|math_2arg|remqo|sincos|trigonometric|trunc_ceil_floor)
      vimdiff "$filepath" "$stdsimdrepo/math.cpp"
      ;;
    mask_broadcast|mask_implicit_cvt|mask_loadstore|mask_operator_cvt|mask_operators|mask_reductions)
      vimdiff "$filepath" "$stdsimdrepo/mask.cpp"
      ;;
    algorithms|broadcast|reductions|generator|operator_cvt)
      vimdiff "$filepath" "$stdsimdrepo/simd.cpp"
      ;;
    split_concat|splits|casts)
      vimdiff "$filepath" "$stdsimdrepo/casts.cpp"
      ;;
    *)
      vimdiff "$filepath" "$stdsimdrepo/${name}.cpp"
      ;;
  esac
done
