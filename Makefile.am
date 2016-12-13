## Process this file with automake to produce Makefile.in

AUTOMAKE_OPTIONS = subdir-objects
ACLOCAL_AMFLAGS = -I m4 --install

bin_PROGRAMS = mjwm
check_PROGRAMS = mjwm_test

# mjwm_CXXFLAGS = -I$(top_builddir)/include -I$(top_srcdir)/include -Wall -Wextra -fno-exceptions -fno-rtti -fno-threadsafe-statics -ffast-math -flto
mjwm_CXXFLAGS = -I$(top_builddir)/include -I$(top_srcdir)/include -Wall -Wextra
mjwm_test_CXXFLAGS = -I$(top_builddir)/include -I$(top_srcdir)/include -Wall -Wextra -DFIXTUREDIR=$(top_srcdir)/test/fixtures/

header_files = include/system_environment.h \
               include/timex.h \
               include/desktop_entry_file_search.h \
               include/menu.h \
               include/qualified_icon_theme.h \
               include/command_line_options_parser.h \
               include/amm_options.h \
               include/amm.h \
               include/directoryx.h \
               include/transformer/transformer_interface.h \
               include/transformer/jwm.h \
               include/stats.h \
               include/stringx.h \
               include/xdg/entry_line.h \
               include/xdg/entry.h \
               include/xdg/icon_theme.h \
               include/xdg/icon_subdirectory.h \
               include/xdg/desktop_entry.h \
               include/messages.h \
               include/icon_search/caching_search.h \
               include/icon_search/xdg_search.h \
               include/icon_search/icon_search_interface.h \
               include/icon_search/mirror_search.h \
               include/filex.h \
               include/vectorx.h \
               include/representation/program.h \
               include/representation/menu_end.h \
               include/representation/menu_start.h \
               include/representation/representation_interface.h \
               include/representation/subcategory_end.h \
               include/representation/subcategory_start.h \
               include/subcategory.h

implementation_files = src/stringx.cc \
                       src/vectorx.cc \
                       src/filex.cc \
                       src/directoryx.cc \
                       src/xdg/entry_line.cc \
                       src/xdg/entry.cc \
                       src/xdg/desktop_entry.cc \
                       src/xdg/icon_subdirectory.cc \
                       src/xdg/icon_theme.cc \
                       src/subcategory.cc \
                       src/stats.cc \
                       src/menu.cc \
                       src/transformer/jwm.cc \
                       src/system_environment.cc \
                       src/desktop_entry_file_search.cc \
                       src/amm_options.cc \
                       src/command_line_options_parser.cc

test_files = test/doctest.h \
             test/stringx_test.cc \
             test/vectorx_test.cc \
             test/filex_test.cc \
             test/directoryx_test.cc \
             test/xdg/entry_line_test.cc \
             test/xdg/entry_test.cc \
             test/xdg/desktop_entry_test.cc \
             test/xdg/icon_subdirectory_test.cc \
             test/xdg/icon_theme_test.cc \
             test/subcategory_test.cc \
             test/stats_test.cc \
             test/menu_test.cc \
             test/transformer/jwm_test.cc \
             test/system_environment_test.cc \
             test/desktop_entry_file_search_test.cc \
             test/amm_options_test.cc \
             test/command_line_options_parser_test.cc \
             test/icon_search/caching_search_test.cc

fixture_files = test/fixtures/applications/nested/deepnested/whaawmp.desktop \
                test/fixtures/applications/nested/xfburn.desktop \
                test/fixtures/applications/desktop.vlc \
                test/fixtures/applications/missing.desktop \
                test/fixtures/applications/mousepad.desktop \
                test/fixtures/applications/suppressed.desktop \
                test/fixtures/applications/suppressedinvalid.desktop \
                test/fixtures/applications/unclassified.desktop \
                test/fixtures/applications/vlc.desktop

EXTRA_DIST = m4/NOTES $(fixture_files)

mjwm_SOURCES = $(implementation_files) src/timex.cc src/messages.cc src/amm.cc src/qualified_icon_theme.cc src/icon_search/xdg_search.cc src/main.cc $(header_files)
mjwm_test_SOURCES = $(implementation_files) $(test_files) test/test_runner.cc $(header_files)

mjwmdir=$(datadir)/mjwm
dist_mjwm_DATA = data/default.mjwm data/puppy.mjwm
dist_man1_MANS = doc/mjwm.1

TESTS = $(check_PROGRAMS)
