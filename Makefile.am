## Process this file with automake to produce Makefile.in
AUTOMAKE_OPTIONS = subdir-objects

AM_CPPFLAGS=-I$(top_builddir)/include -I$(top_srcdir)/include -Wall -Wextra

bin_PROGRAMS = mjwm
mjwm_SOURCES = src/util.cc \
               src/desktop_file.cc \
               src/subcategory.cc \
               src/menu.cc \
               src/transformer/jwm.cc \
               src/icon_service.cc \
               src/file_search_service.cc \
               src/messages.cc \
               src/command_line_options.cc \
               src/stats.cc \
               src/mjwm.cc

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

mjwm_util_test_SOURCES = src/util.cc \
                         test/util_test.cc
mjwm_desktop_file_test_SOURCES = src/util.cc \
                                 src/desktop_file.cc \
                                 test/desktop_file_test.cc
mjwm_file_search_service_test_SOURCES = src/util.cc \
                                        src/file_search_service.cc \
                                        test/file_search_service_test.cc
mjwm_subcategory_test_SOURCES = src/util.cc \
                                src/desktop_file.cc \
                                src/subcategory.cc \
                                test/subcategory_test.cc
mjwm_stats_test_SOURCES = src/util.cc \
                          src/stats.cc \
                          test/stats_test.cc
mjwm_menu_test_SOURCES = src/util.cc \
                         src/icon_service.cc \
                         src/desktop_file.cc \
                         src/subcategory.cc \
                         src/transformer/jwm.cc \
                         src/stats.cc \
                         src/menu.cc \
                         test/menu_test.cc
mjwm_transformer_jwm_test_SOURCES = src/util.cc \
                                    src/transformer/jwm.cc \
                                    test/transformer/jwm_test.cc
mjwm_command_line_options_test_SOURCES = src/util.cc \
                                         src/command_line_options.cc \
                                         test/command_line_options_test.cc
