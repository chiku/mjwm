## Process this file with automake to produce Makefile.in
AUTOMAKE_OPTIONS = subdir-objects

# AM_CPPFLAGS=-I$(top_builddir)/include -I$(top_srcdir)/include -Wall -Wextra -fno-exceptions -fno-rtti -fno-threadsafe-statics -ffast-math -flto
AM_CPPFLAGS=-I$(top_builddir)/include -I$(top_srcdir)/include -Wall -Wextra

bin_PROGRAMS = mjwm
mjwm_SOURCES = src/stringx.cc \
               src/vectorx.cc \
               src/xdg/entry_line.cc \
               src/xdg/entry.cc \
               src/desktop_file_line.cc \
               src/desktop_entry.cc \
               src/subcategory.cc \
               src/stats.cc \
               src/menu.cc \
               src/transformer/jwm.cc \
               src/service/environment_variable.cc \
               src/service/icon/scan.cc \
               src/service/file_search.cc \
               src/messages.cc \
               src/command_line_options_parser.cc \
               src/amm.cc \
               src/main.cc

check_PROGRAMS = mjwm_stringx_test \
                 mjwm_vectorx_test \
                 mjwm_xdg_entry_line_test \
                 mjwm_xdg_entry_test \
                 mjwm_desktop_file_line_test \
                 mjwm_desktop_entry_test \
                 mjwm_subcategory_test \
                 mjwm_stats_test \
                 mjwm_menu_test \
                 mjwm_service_file_search_test \
                 mjwm_transformer_jwm_test \
                 mjwm_service_environment_variable_test \
                 mjwm_command_line_options_parser_test

mjwmdir=$(datadir)/mjwm
mjwm_DATA = data/default.mjwm data/puppy.mjwm
man1_MANS = doc/mjwm.1

TESTS = $(check_PROGRAMS)

mjwm_stringx_test_SOURCES = src/stringx.cc \
                            test/stringx_test.cc

mjwm_vectorx_test_SOURCES = src/stringx.cc \
                            src/vectorx.cc \
                            test/vectorx_test.cc

mjwm_xdg_entry_line_test_SOURCES = src/stringx.cc \
                                   src/xdg/entry_line.cc \
                                   test/xdg/entry_line_test.cc

mjwm_xdg_entry_test_SOURCES = src/stringx.cc \
                              src/xdg/entry_line.cc \
                              src/xdg/entry.cc \
                              test/xdg/entry_test.cc

mjwm_desktop_file_line_test_SOURCES = src/stringx.cc \
                                      src/desktop_file_line.cc \
                                      test/desktop_file_line_test.cc

mjwm_desktop_entry_test_SOURCES = src/stringx.cc \
                                  src/desktop_file_line.cc \
                                  src/xdg/entry_line.cc \
                                  src/xdg/entry.cc \
                                  src/desktop_entry.cc \
                                  test/desktop_entry_test.cc

mjwm_subcategory_test_SOURCES = src/stringx.cc \
                                src/xdg/entry_line.cc \
                                src/xdg/entry.cc \
                                src/desktop_file_line.cc \
                                src/desktop_entry.cc \
                                src/subcategory.cc \
                                test/subcategory_test.cc

mjwm_stats_test_SOURCES = src/stringx.cc \
                          src/vectorx.cc \
                          src/stats.cc \
                          test/stats_test.cc

mjwm_menu_test_SOURCES = src/stringx.cc \
                         src/vectorx.cc \
                         src/xdg/entry_line.cc \
                         src/xdg/entry.cc \
                         src/desktop_file_line.cc \
                         src/desktop_entry.cc \
                         src/subcategory.cc \
                         src/stats.cc \
                         src/menu.cc \
                         test/menu_test.cc

mjwm_transformer_jwm_test_SOURCES = src/stringx.cc \
                                    src/vectorx.cc \
                                    src/transformer/jwm.cc \
                                    test/transformer/jwm_test.cc


mjwm_service_file_search_test_SOURCES = src/stringx.cc \
                                        src/vectorx.cc \
                                        src/service/environment_variable.cc \
                                        src/service/file_search.cc \
                                        test/service/file_search_test.cc

mjwm_service_environment_variable_test_SOURCES = src/stringx.cc \
                                                 src/service/environment_variable.cc \
                                                 test/service/environment_variable_test.cc

mjwm_command_line_options_parser_test_SOURCES = src/stringx.cc \
                                                src/command_line_options_parser.cc \
                                                test/command_line_options_parser_test.cc
