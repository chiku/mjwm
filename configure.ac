#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.12])
AC_INIT([mjwm], [2.2.0], [chirantan.mitra@gmail.com])
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

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([iostream fstream string vector algorithm cstdio dirent.h getopt.h])
AC_HEADER_STDC

# Checks for typedefs, structures, and compiler characteristics.
AC_C_CONST

# Checks for library functions.
AC_FUNC_MALLOC
AC_CHECK_FUNCS([mjwm])
AC_CONFIG_FILES([Makefile])

AC_OUTPUT
