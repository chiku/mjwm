## Process this file with automake to produce Makefile.in
AUTOMAKE_OPTIONS = subdir-objects

# AM_CPPFLAGS=-I$(top_builddir)/include -I$(top_srcdir)/include -Wall -Wextra -fno-exceptions -fno-rtti -fno-threadsafe-statics -ffast-math -flto
AM_CPPFLAGS=-I$(top_builddir)/include -I$(top_srcdir)/include -Wall -Wextra

bin_PROGRAMS = mjwm
mjwm_SOURCES = src/stringx.cc \
               src/vectorx.cc \
               src/filex.cc \
               src/directoryx.cc \
               src/xdg/entry_line.cc \
               src/xdg/entry.cc \
               src/xdg/desktop_entry.cc \
               src/xdg/icon_theme.cc \
               src/xdg/icon_subdirectory.cc \
               src/subcategory.cc \
               src/stats.cc \
               src/menu.cc \
               src/transformer/jwm.cc \
               src/system_environment.cc \
               src/qualified_icon_theme.cc \
               src/icon_search/xdg_search.cc \
               src/desktop_entry_file_search.cc \
               src/messages.cc \
               src/amm_options.cc \
               src/command_line_options_parser.cc \
               src/amm.cc \
               src/main.cc

check_PROGRAMS = mjwm_stringx_test \
                 mjwm_vectorx_test \
                 mjwm_filex_test \
                 mjwm_directoryx_test \
                 mjwm_xdg_entry_line_test \
                 mjwm_xdg_entry_test \
                 mjwm_xdg_desktop_entry_test \
                 mjwm_xdg_icon_theme_test \
                 mjwm_xdg_icon_subdirectory_test \
                 mjwm_subcategory_test \
                 mjwm_stats_test \
                 mjwm_menu_test \
                 mjwm_desktop_entry_file_search_test \
                 mjwm_transformer_jwm_test \
                 mjwm_service_system_environment_test \
                 mjwm_command_line_options_parser_test \
                 mjwm_icon_search_caching_search_test

mjwmdir=$(datadir)/mjwm
mjwm_DATA = data/default.mjwm data/puppy.mjwm
man1_MANS = doc/mjwm.1

TESTS = $(check_PROGRAMS)

mjwm_stringx_test_SOURCES = src/stringx.cc \
                            test/stringx_test.cc

mjwm_vectorx_test_SOURCES = src/stringx.cc \
                            src/vectorx.cc \
                            test/vectorx_test.cc

mjwm_filex_test_SOURCES = src/filex.cc \
                          test/filex_test.cc

mjwm_directoryx_test_SOURCES = src/directoryx.cc \
                               test/directoryx_test.cc

mjwm_xdg_entry_line_test_SOURCES = src/stringx.cc \
                                   src/xdg/entry_line.cc \
                                   test/xdg/entry_line_test.cc

mjwm_xdg_entry_test_SOURCES = src/stringx.cc \
                              src/xdg/entry_line.cc \
                              src/xdg/entry.cc \
                              test/xdg/entry_test.cc

mjwm_xdg_desktop_entry_test_SOURCES = src/stringx.cc \
                                      src/xdg/entry_line.cc \
                                      src/xdg/entry.cc \
                                      src/xdg/desktop_entry.cc \
                                      test/xdg/desktop_entry_test.cc

mjwm_xdg_icon_theme_test_SOURCES = src/stringx.cc \
                                   src/xdg/entry_line.cc \
                                   src/xdg/entry.cc \
                                   src/xdg/icon_subdirectory.cc \
                                   src/xdg/icon_theme.cc \
                                   test/xdg/icon_theme_test.cc

mjwm_xdg_icon_subdirectory_test_SOURCES = src/xdg/icon_subdirectory.cc \
                                          test/xdg/icon_subdirectory_test.cc

mjwm_subcategory_test_SOURCES = src/stringx.cc \
                                src/xdg/entry_line.cc \
                                src/xdg/entry.cc \
                                src/xdg/desktop_entry.cc \
                                src/subcategory.cc \
                                test/subcategory_test.cc

mjwm_stats_test_SOURCES = src/stringx.cc \
                          src/vectorx.cc \
                          src/stats.cc \
                          test/stats_test.cc

mjwm_menu_test_SOURCES = src/stringx.cc \
                         src/vectorx.cc \
                         src/filex.cc \
                         src/xdg/entry_line.cc \
                         src/xdg/entry.cc \
                         src/xdg/desktop_entry.cc \
                         src/subcategory.cc \
                         src/stats.cc \
                         src/menu.cc \
                         test/menu_test.cc

mjwm_transformer_jwm_test_SOURCES = src/stringx.cc \
                                    src/vectorx.cc \
                                    src/transformer/jwm.cc \
                                    test/transformer/jwm_test.cc


mjwm_desktop_entry_file_search_test_SOURCES = src/stringx.cc \
                                              src/vectorx.cc \
                                              src/system_environment.cc \
                                              src/desktop_entry_file_search.cc \
                                              test/desktop_entry_file_search_test.cc

mjwm_service_system_environment_test_SOURCES = src/stringx.cc \
                                               src/system_environment.cc \
                                               test/system_environment_test.cc

mjwm_command_line_options_parser_test_SOURCES = src/stringx.cc \
                                                src/amm_options.cc \
                                                src/command_line_options_parser.cc \
                                                test/command_line_options_parser_test.cc

mjwm_icon_search_caching_search_test_SOURCES = test/icon_search/caching_search_test.cc
