set(CTEST_PROJECT_NAME "std-simd")
set(CTEST_NIGHTLY_START_TIME "01:00:00 UTC")

set(CTEST_DROP_METHOD "http")
set(CTEST_DROP_SITE "lxwww53.gsi.de")
set(CTEST_DROP_LOCATION "/submit.php?project=std-simd")

set(CTEST_DROP_SITE_CDASH TRUE)

set(CTEST_UPDATE_TYPE "git")

find_program(GITCOMMAND git)
set(CTEST_UPDATE_COMMAND "${GITCOMMAND}")

mark_as_advanced(GITCOMMAND)
