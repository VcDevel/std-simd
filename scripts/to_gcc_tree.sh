#!/bin/sh

cd "`dirname "$0"`/.."
SRCDIR="$PWD"
GCCDIR=~/src/gcc-simd
if test "$1" != "-f"; then
  cd $GCCDIR
  if test -n "$(git status -s -uno)"; then
    echo "The target directory $GCCDIR is not ready:"
    git status -uno
    exit 1
  fi
fi

cd "$SRCDIR"
cp experimental/simd $GCCDIR/libstdc++-v3/include/experimental/
cp experimental/bits/simd*.h $GCCDIR/libstdc++-v3/include/experimental/bits/

cd $GCCDIR/libstdc++-v3/include/experimental
rm bits/simd_debug.h

for i in simd bits/simd*.h; do
  {
    sed '/\/\/ Copyright/Q' $i
    cat <<EOF
// Copyright (C) 2020 Free Software Foundation, Inc.
//
// This file is part of the GNU ISO C++ Library.  This library is free
// software; you can redistribute it and/or modify it under the
// terms of the GNU General Public License as published by the
// Free Software Foundation; either version 3, or (at your option)
// any later version.

// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// Under Section 7 of GPL version 3, you are granted additional
// permissions described in the GCC Runtime Library Exception, version
// 3.1, as published by the Free Software Foundation.

// You should have received a copy of the GNU General Public License and
// a copy of the GCC Runtime Library Exception along with this program;
// see the files COPYING3 and COPYING.RUNTIME respectively.  If not, see
// <http://www.gnu.org/licenses/>.
EOF
    sed '1,/POSSIBILITY OF SUCH DAMAGE/d' $i
  } > $i.tmp
  mv $i.tmp $i
  sed -i '/Vir_/d' $i
done

git add simd bits/simd*.h
git diff --cached
