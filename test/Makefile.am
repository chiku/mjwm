## Process this file with automake to produce Makefile.in
AUTOMAKE_OPTIONS = subdir-objects

check_PROGRAMS = mjwm_categories_test mjwm_menu_entry_test mjwm_menu_group_test

mjwm_categories_test_SOURCES = ../src/categories.cpp categories_test.cpp
mjwm_menu_entry_test_SOURCES = ../src/categories.cpp ../src/menu_entry.cpp menu_entry_test.cpp
mjwm_menu_group_test_SOURCES = ../src/categories.cpp ../src/menu_entry.cpp ../src/menu_group.cpp menu_group_test.cpp

TESTS = $(check_PROGRAMS)

AM_CPPFLAGS=-Wall -Wextra
