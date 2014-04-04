## Process this file with automake to produce Makefile.in
AUTOMAKE_OPTIONS = subdir-objects

AM_CPPFLAGS=-I$(top_builddir)/include -I$(top_srcdir)/include -Wall -Wextra

bin_PROGRAMS = mjwm
mjwm_SOURCES = src/util.cpp \
               src/desktop_file.cpp \
               src/subcategory.cpp \
               src/representation.cpp \
               src/menu.cpp \
               src/transformer/jwm.cc \
               src/icon_service.cpp \
               src/file_search_service.cpp \
               src/messages.cpp \
               src/command_line_options.cpp \
               src/stats.cpp \
               src/mjwm.cpp

check_PROGRAMS = mjwm_util_test \
                 mjwm_desktop_file_test \
                 mjwm_subcategory_test \
                 mjwm_stats_test \
                 mjwm_menu_test \
                 mjwm_file_search_service_test \
                 mjwm_transformer_jwm_test \
                 mjwm_command_line_options_test

mjwmdir=$(datadir)/mjwm
mjwm_DATA = data/default.mjwm data/puppy.mjwm
man1_MANS = doc/mjwm.1

TESTS = $(check_PROGRAMS)

mjwm_util_test_SOURCES = src/util.cpp \
                         test/util_test.cpp
mjwm_desktop_file_test_SOURCES = src/util.cpp \
                                 src/desktop_file.cpp \
                                 test/desktop_file_test.cpp
mjwm_file_search_service_test_SOURCES = src/util.cpp \
                                        src/file_search_service.cpp \
                                        test/file_search_service_test.cpp
mjwm_subcategory_test_SOURCES = src/util.cpp \
                                src/desktop_file.cpp \
                                src/subcategory.cpp \
                                test/subcategory_test.cpp
mjwm_stats_test_SOURCES = src/util.cpp \
                          src/stats.cpp \
                          test/stats_test.cpp
mjwm_menu_test_SOURCES = src/util.cpp \
                         src/icon_service.cpp \
                         src/desktop_file.cpp \
                         src/subcategory.cpp \
                         src/representation.cpp \
                         src/transformer/jwm.cc \
                         src/stats.cpp \
                         src/menu.cpp \
                         test/menu_test.cpp
mjwm_transformer_jwm_test_SOURCES = src/util.cpp \
                                    src/representation.cpp \
                                    src/transformer/jwm.cc \
                                    test/transformer/jwm_test.cc
mjwm_command_line_options_test_SOURCES = src/util.cpp \
                                         src/command_line_options.cpp \
                                         test/command_line_options_test.cpp
