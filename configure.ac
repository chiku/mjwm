#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.66])
AC_INIT([mjwm], [1.0], [chirantan.mitra@gmail.com])
AC_LANG(C++)

AC_CONFIG_SRCDIR([src/menu_entry.cpp])
AC_CONFIG_SRCDIR([src/menu_group.cpp])
AC_CONFIG_SRCDIR([src/mjwm.cpp])
AC_CONFIG_HEADERS([config.h])
AM_INIT_AUTOMAKE

# Checks for programs.
AC_PROG_CXX
AC_PROG_INSTALL

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([iostream fstream string vector algorithm dirent.h string.h getopt.h])
AC_HEADER_STDC

# Checks for typedefs, structures, and compiler characteristics.
AC_C_CONST

# Checks for library functions.
AC_FUNC_MALLOC
AC_CHECK_FUNCS([mjwm])
AC_CONFIG_FILES([Makefile src/Makefile test/Makefile])

AC_OUTPUT
