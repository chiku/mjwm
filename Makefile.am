## Process this file with automake to produce Makefile.in
AUTOMAKE_OPTIONS = subdir-objects

AM_CPPFLAGS=-Wall -Wextra

bin_PROGRAMS = mjwm
mjwm_SOURCES = src/desktop_file_categories.cpp \
               src/desktop_file.cpp \
               src/jwm/menu_entry.cpp \
               src/jwm/transform.cpp \
               src/jwm/subcategory.cpp \
               src/jwm/menu.cpp \
               src/application_directories.cpp \
               src/messages.cpp \
               src/mjwm.cpp

check_PROGRAMS = mjwm_desktop_file_categories_test \
                 mjwm_desktop_file_test \
                 mjwm_jwm_menu_entry_test \
                 mjwm_jwm_transform_test \
                 mjwm_jwm_subcategory_test \
                 mjwm_jwm_menu_test \
                 mjwm_messages_test \
                 mjwm_application_directories_test

mjwm_desktop_file_categories_test_SOURCES = src/desktop_file_categories.cpp \
                                            test/desktop_file_categories_test.cpp
mjwm_desktop_file_test_SOURCES = src/desktop_file_categories.cpp \
                                 src/desktop_file.cpp \
                                 test/desktop_file_test.cpp
mjwm_jwm_menu_entry_test_SOURCES = src/jwm/menu_entry.cpp \
                                   test/jwm/menu_entry_test.cpp
mjwm_jwm_transform_test_SOURCES = src/desktop_file_categories.cpp \
                                  src/desktop_file.cpp \
                                  src/jwm/menu_entry.cpp \
                                  src/jwm/transform.cpp \
                                  test/jwm/transform_test.cpp
mjwm_jwm_subcategory_test_SOURCES = src/desktop_file_categories.cpp \
                                    src/desktop_file.cpp \
                                    src/jwm/menu_entry.cpp \
                                    src/jwm/transform.cpp \
                                    src/jwm/subcategory.cpp \
                                    test/jwm/subcategory_test.cpp
mjwm_application_directories_test_SOURCES = src/application_directories.cpp \
                                            test/application_directories_test.cpp
mjwm_jwm_menu_test_SOURCES = src/desktop_file_categories.cpp \
                             src/desktop_file.cpp \
                             src/jwm/menu_entry.cpp \
                             src/jwm/transform.cpp \
                             src/jwm/subcategory.cpp \
                             src/jwm/menu.cpp \
                             test/jwm/menu_test.cpp
mjwm_messages_test_SOURCES = src/messages.cpp \
                             test/messages_test.cpp

TESTS = $(check_PROGRAMS)
