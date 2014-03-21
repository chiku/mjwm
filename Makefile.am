## Process this file with automake to produce Makefile.in
AUTOMAKE_OPTIONS = subdir-objects

AM_CPPFLAGS=-Wall -Wextra

bin_PROGRAMS = mjwm
mjwm_SOURCES = src/desktop_file_categories.cpp src/desktop_file.cpp src/menu_entry/jwm.cpp src/transform/jwm.cpp src/menu_group.cpp src/desktop_file_search.cpp src/mjwm.cpp

check_PROGRAMS = mjwm_desktop_file_categories_test mjwm_desktop_file_test mjwm_menu_entry_jwm_test mjwm_transform_jwm_test mjwm_menu_group_test

mjwm_desktop_file_categories_test_SOURCES = src/desktop_file_categories.cpp test/desktop_file_categories_test.cpp
mjwm_desktop_file_test_SOURCES = src/desktop_file_categories.cpp src/desktop_file.cpp test/desktop_file_test.cpp
mjwm_menu_entry_jwm_test_SOURCES = src/menu_entry/jwm.cpp test/menu_entry/jwm_test.cpp
mjwm_transform_jwm_test_SOURCES = src/desktop_file_categories.cpp src/desktop_file.cpp src/menu_entry/jwm.cpp src/transform/jwm.cpp test/transform/jwm_test.cpp
mjwm_menu_group_test_SOURCES = src/desktop_file_categories.cpp src/desktop_file.cpp src/menu_entry/jwm.cpp src/transform/jwm.cpp src/menu_group.cpp test/menu_group_test.cpp

TESTS = $(check_PROGRAMS)
