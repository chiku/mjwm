## Process this file with automake to produce Makefile.in
AUTOMAKE_OPTIONS = subdir-objects

AM_CPPFLAGS=-I$(top_builddir)/include -I$(top_srcdir)/include -Wall -Wextra

bin_PROGRAMS = mjwm
mjwm_SOURCES = src/stringx.cpp \
               src/vectorx.cpp \
               src/desktop_file.cpp \
               src/subcategory.cpp \
               src/representation.cpp \
               src/menu.cpp \
               src/jwm/transformer.cpp \
               src/icon_service.cpp \
               src/desktop_file_names.cpp \
               src/messages.cpp \
               src/command_line_options.cpp \
               src/mjwm.cpp

mjwmdir=$(datadir)/mjwm
mjwm_DATA = data/default.mjwm
man1_MANS = doc/mjwm.1

check_PROGRAMS = mjwm_vectorx_test \
                 mjwm_stringx_test \
                 mjwm_desktop_file_test \
                 mjwm_subcategory_test \
                 mjwm_menu_test \
                 mjwm_desktop_file_names_test \
                 mjwm_jwm_transformer_test \
                 mjwm_messages_test \
                 mjwm_command_line_options_test

mjwm_stringx_test_SOURCES = src/stringx.cpp \
                            test/stringx_test.cpp
mjwm_vectorx_test_SOURCES = src/stringx.cpp \
                            src/vectorx.cpp \
                            test/vectorx_test.cpp
mjwm_desktop_file_test_SOURCES = src/stringx.cpp \
                                 src/vectorx.cpp \
                                 src/desktop_file.cpp \
                                 test/desktop_file_test.cpp
mjwm_desktop_file_names_test_SOURCES = src/vectorx.cpp \
                                       src/stringx.cpp \
                                       src/desktop_file_names.cpp \
                                       test/desktop_file_names_test.cpp
mjwm_subcategory_test_SOURCES = src/vectorx.cpp \
                                src/stringx.cpp \
                                src/desktop_file.cpp \
                                src/subcategory.cpp \
                                test/subcategory_test.cpp
mjwm_menu_test_SOURCES = src/vectorx.cpp \
                         src/stringx.cpp \
                         src/icon_service.cpp \
                         src/desktop_file.cpp \
                         src/subcategory.cpp \
                         src/representation.cpp \
                         src/jwm/transformer.cpp \
                         src/menu.cpp \
                         test/menu_test.cpp
mjwm_jwm_transformer_test_SOURCES = src/stringx.cpp \
                                    src/vectorx.cpp \
                                    src/representation.cpp \
                                    src/jwm/transformer.cpp \
                                    test/jwm/transformer_test.cpp
mjwm_messages_test_SOURCES = src/messages.cpp \
                             test/messages_test.cpp
mjwm_command_line_options_test_SOURCES = src/stringx.cpp \
                                         src/command_line_options.cpp \
                                         test/command_line_options_test.cpp
TESTS = $(check_PROGRAMS)
