## Process this file with automake to produce Makefile.in
AUTOMAKE_OPTIONS = subdir-objects

AM_CPPFLAGS=-Wall -Wextra

bin_PROGRAMS = mjwm
mjwm_SOURCES = src/stringx.cpp \
               src/vectorx.cpp \
               src/desktop_file_categories.cpp \
               src/desktop_file.cpp \
               src/jwm/menu_entry.cpp \
               src/jwm/transform.cpp \
               src/jwm/subcategory.cpp \
               src/jwm/menu.cpp \
               src/icon_service.cpp \
               src/application_directories.cpp \
               src/messages.cpp \
               src/mjwm.cpp

check_PROGRAMS = mjwm_vectorx_test \
                 mjwm_stringx_test \
                 mjwm_desktop_file_categories_test \
                 mjwm_desktop_file_test \
                 mjwm_jwm_menu_entry_test \
                 mjwm_jwm_transform_test \
                 mjwm_jwm_subcategory_test \
                 mjwm_jwm_menu_test \
                 mjwm_messages_test \
                 mjwm_application_directories_test

mjwm_stringx_test_SOURCES = src/stringx.cpp \
                            test/stringx_test.cpp
mjwm_vectorx_test_SOURCES = src/vectorx.cpp \
                            test/vectorx_test.cpp
mjwm_desktop_file_categories_test_SOURCES = src/stringx.cpp \
                                            src/vectorx.cpp \
                                            src/desktop_file_categories.cpp \
                                            test/desktop_file_categories_test.cpp
mjwm_desktop_file_test_SOURCES = src/stringx.cpp \
                                 src/vectorx.cpp \
                                 src/desktop_file_categories.cpp \
                                 src/desktop_file.cpp \
                                 test/desktop_file_test.cpp
mjwm_jwm_menu_entry_test_SOURCES = src/jwm/menu_entry.cpp \
                                   test/jwm/menu_entry_test.cpp
mjwm_jwm_transform_test_SOURCES = src/stringx.cpp \
                                  src/vectorx.cpp \
                                  src/desktop_file_categories.cpp \
                                  src/desktop_file.cpp \
                                  src/jwm/menu_entry.cpp \
                                  src/jwm/transform.cpp \
                                  src/icon_service.cpp \
                                  test/jwm/transform_test.cpp
mjwm_jwm_subcategory_test_SOURCES = src/stringx.cpp \
                                    src/vectorx.cpp \
                                    src/desktop_file_categories.cpp \
                                    src/desktop_file.cpp \
                                    src/jwm/menu_entry.cpp \
                                    src/jwm/transform.cpp \
                                    src/jwm/subcategory.cpp \
                                    src/icon_service.cpp \
                                    test/jwm/subcategory_test.cpp
mjwm_application_directories_test_SOURCES = src/stringx.cpp \
                                            src/application_directories.cpp \
                                            test/application_directories_test.cpp
mjwm_jwm_menu_test_SOURCES = src/stringx.cpp \
                             src/vectorx.cpp \
                             src/desktop_file_categories.cpp \
                             src/desktop_file.cpp \
                             src/jwm/menu_entry.cpp \
                             src/jwm/transform.cpp \
                             src/jwm/subcategory.cpp \
                             src/jwm/menu.cpp \
                             src/icon_service.cpp \
                             test/jwm/menu_test.cpp
mjwm_messages_test_SOURCES = src/messages.cpp \
                             test/messages_test.cpp

TESTS = $(check_PROGRAMS)
