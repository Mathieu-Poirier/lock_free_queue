AC_INIT([lock_free_queue], [0.0.1])
AC_CONFIG_SRCDIR([src/main.cpp])
AM_INIT_AUTOMAKE([foreign parallel-tests])

AC_PROG_CXX
AC_PROG_RANLIB
AM_PROG_AR

PKG_PROG_PKG_CONFIG
PKG_CHECK_MODULES([GTEST], [gtest_main])

AC_CONFIG_FILES([
  Makefile
  src/Makefile
  tests/Makefile
])
AC_OUTPUT