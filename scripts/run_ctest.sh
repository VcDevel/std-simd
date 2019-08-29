#!/bin/bash

case "$1" in
   Experimental|Nightly|Continuous)
      export dashboard_model=$1
      case "$2" in
        None|Debug|Release|RelWithDebug|RelWithDebInfo|MinSizeRel)
        export build_type=$2
        ;;
      esac
      ;;
   *)
      echo "Usage: $0 <model> [<build type>]"
      echo
      echo "Possible arguments for model are Nightly, Continuous, or Experimental."
      echo "Build type may be one of: None Debug Release RelWithDebug RelWithDebInfo MinSizeRel."
      echo
      exit 1
      ;;
esac

if [[ -x "$CXX" -a "${$(readlink $CXX)##*/}" = "icecc" ]]; then
  export number_of_processors=80
fi

ctest -S "`dirname $0`/test.cmake"
