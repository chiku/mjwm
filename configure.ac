# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.12])
AC_INIT([mjwm], [2.4.0], [https://github.com/chiku/mjwm/issues])
AC_LANG(C++)

# Silent by default
AM_SILENT_RULES([yes])

AC_CONFIG_SRCDIR([src/mjwm.cpp])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_AUX_DIR([build-aux])
AM_INIT_AUTOMAKE([parallel-tests color-tests])

# Checks for programs.
AC_PROG_CXX
AC_PROG_INSTALL

# Checks for header files.
AC_CHECK_HEADERS([iostream fstream string sstream vector algorithm cstdlib cstring ctime dirent.h getopt.h])

# Checks for library functions.
AC_CHECK_FUNCS([mjwm])
AC_CONFIG_FILES([Makefile])

AC_OUTPUT
