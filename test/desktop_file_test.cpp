/*
  This file is part of mjwm.
  Copyright (C) 2014  Chirantan Mitra <chirantan.mitra@gmail.com>

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <iostream>
#include <vector>
#include <string>

#include "QUnit.hpp"

#include "desktop_file.h"

namespace amm
{
  // Verifies the representation of a FreeDesktop .desktop file
  class desktop_file_test
  {
    QUnit::UnitTest qunit;

    void test_desktop_file_parses_name()
    {
      DesktopFile entry;
      entry.Populate("Name=Mousepad\n");
      QUNIT_IS_EQUAL("Mousepad", entry.name());
    }

    void test_desktop_file_parses_icon()
    {
      DesktopFile entry;
      entry.Populate("Icon=accessories-text-editor\n");
      QUNIT_IS_EQUAL("accessories-text-editor", entry.icon());
    }

    void test_desktop_file_parses_executable()
    {
      DesktopFile entry;
      entry.Populate("Exec=mousepad %F\n");
      QUNIT_IS_EQUAL("mousepad %F", entry.executable());
    }

    void test_desktop_file_parses_categories()
    {
      DesktopFile entry;
      entry.Populate("Categories=Application;Utility;TextEditor;GTK;\n");
      std::vector<std::string> categories = entry.categories();
      QUNIT_IS_EQUAL(4, categories.size());
      QUNIT_IS_EQUAL("Application", categories[0]);
      QUNIT_IS_EQUAL("GTK", categories[1]);
      QUNIT_IS_EQUAL("TextEditor", categories[2]);
      QUNIT_IS_EQUAL("Utility", categories[3]);
    }

    void test_desktop_file_parses_no_display()
    {
      DesktopFile entry;
      entry.Populate("NoDisplay=true\n");
      QUNIT_IS_FALSE(entry.display());
    }

    void test_desktop_file_treats_1_as_true_for_no_display()
    {
      DesktopFile entry;
      entry.Populate("NoDisplay=1\n");
      QUNIT_IS_FALSE(entry.display());
    }

    void test_desktop_file_display_is_true_by_default()
    {
      DesktopFile entry;
      QUNIT_IS_TRUE(entry.display());
    }

    void test_desktop_file_parse_doesnt_fail_when_entry_is_missing()
    {
      DesktopFile entry;
      entry.Populate("Categories=");
      QUNIT_IS_EQUAL("", entry.executable());
    }

    void test_desktop_file_parse_doesnt_fail_when_line_is_missing()
    {
      DesktopFile entry;
      entry.Populate("");
      QUNIT_IS_EQUAL("", entry.name());
    }

    void test_desktop_file_is_lesser_than_a_desktop_file_with_alphabetically_greater_name()
    {
      DesktopFile entry, greater_entry;
      entry.Populate("Name=Mousepad\n");
      greater_entry.Populate("Name=VLC\n");
      QUNIT_IS_TRUE(entry < greater_entry);
      QUNIT_IS_FALSE(greater_entry < entry);
    }

    void test_desktop_file_is_greater_than_a_desktop_file_with_alphabetically_lesser_name()
    {
      DesktopFile entry, lesser_entry;
      entry.Populate("Name=VLC\n");
      lesser_entry.Populate("Name=Mousepad\n");
      QUNIT_IS_TRUE(entry > lesser_entry);
      QUNIT_IS_FALSE(lesser_entry > entry);
    }

    void test_desktop_file_is_equal_to_desktop_file_with_same_name()
    {
      DesktopFile entry, same_entry, different_entry;
      entry.Populate("Name=Mousepad\n");
      same_entry.Populate("Name=Mousepad\n");
      different_entry.Populate("Name=VLC\n");
      QUNIT_IS_TRUE(entry == same_entry);
      QUNIT_IS_FALSE(entry == different_entry);
    }

    void test_desktop_file_is_not_equal_to_desktop_file_with_different_name()
    {
      DesktopFile entry, same_entry, different_entry;
      entry.Populate("Name=Mousepad\n");
      same_entry.Populate("Name=Mousepad\n");
      different_entry.Populate("Name=VLC\n");
      QUNIT_IS_TRUE(entry != different_entry);
      QUNIT_IS_FALSE(entry != same_entry);
    }

    void test_desktop_file_is_valid_when_it_has_name_and_icon_and_executable()
    {
      DesktopFile valid_entry;
      valid_entry.Populate("Name=Mousepad\n");
      valid_entry.Populate("Icon=accessories-text-editor\n");
      valid_entry.Populate("Exec=mousepad %F\n");
      QUNIT_IS_TRUE(valid_entry.IsValid());
    }

    void test_desktop_file_is_not_valid_without_name()
    {
      DesktopFile missing_name_entry;
      missing_name_entry.Populate("Icon=accessories-text-editor\n");
      missing_name_entry.Populate("Exec=mousepad %F\n");
      QUNIT_IS_FALSE(missing_name_entry.IsValid());
    }

    void test_desktop_file_is_not_valid_without_icon()
    {
      DesktopFile missing_icon_entry;
      missing_icon_entry.Populate("Name=Mousepad\n");
      missing_icon_entry.Populate("Exec=mousepad %F\n");
      QUNIT_IS_FALSE(missing_icon_entry.IsValid());
    }

    void test_desktop_file_is_not_valid_without_executable()
    {
      DesktopFile missing_executable_entry;
      missing_executable_entry.Populate("Name=Mousepad\n");
      missing_executable_entry.Populate("Icon=accessories-text-editor\n");
      QUNIT_IS_FALSE(missing_executable_entry.IsValid());
    }

    void test_desktop_file_is_a_audiovideo_if_tag_includes_AudioVideo()
    {
      DesktopFile entry;
      entry.Populate("Categories=AudioVideo;Audio;Player;GTK;\n");
      QUNIT_IS_TRUE(entry.IsA("AudioVideo"));
    }

    void test_desktop_file_is_not_a_audiovideo_if_tag_excludes_AudioVideo()
    {
      DesktopFile entry;
      entry.Populate("Categories=Audio;Video;Player;GTK;\n");
      QUNIT_IS_FALSE(entry.IsA("AudioVideo"));
    }

    void test_desktop_file_is_a_audiovideo_if_tag_includes_AudioVideo_without_trailing_semicolon()
    {
      DesktopFile entry;
      entry.Populate("Categories=AudioVideo\n");
      QUNIT_IS_TRUE(entry.IsA("AudioVideo"));
    }

    void test_desktop_file_is_not_a_audiovideo_if_empty()
    {
      DesktopFile entry;
      entry.Populate("Categories=\n");
      QUNIT_IS_FALSE(entry.IsA("AudioVideo"));
    }

    void test_desktop_file_is_any_of_audiovideo_and_multimedia_if_tag_includes_AudioVideo()
    {
      DesktopFile entry;
      entry.Populate("Categories=AudioVideo;Audio;Player;GTK;\n");
      std::vector<std::string> classifications;
      classifications.push_back("AudioVideo");
      classifications.push_back("Multimedia");
      QUNIT_IS_TRUE(entry.IsAnyOf(classifications));
    }

    void test_desktop_file_is_not_any_of_audiovideo_or_mutlimedia_if_tag_excludes_AudioVideo_and_multimedia()
    {
      DesktopFile entry;
      entry.Populate("Categories=Audio;Video;Player;GTK;\n");
      std::vector<std::string> classifications;
      classifications.push_back("AudioVideo");
      classifications.push_back("Multimedia");
      QUNIT_IS_FALSE(entry.IsAnyOf(classifications));
    }

  public:
    desktop_file_test(std::ostream &out, int verbose_level) : qunit(out, verbose_level) {}

    int run()
    {
      test_desktop_file_parses_name();
      test_desktop_file_parses_icon();
      test_desktop_file_parses_executable();
      test_desktop_file_parses_categories();
      test_desktop_file_parses_no_display();
      test_desktop_file_treats_1_as_true_for_no_display();
      test_desktop_file_display_is_true_by_default();

      test_desktop_file_parse_doesnt_fail_when_entry_is_missing();
      test_desktop_file_parse_doesnt_fail_when_line_is_missing();

      test_desktop_file_is_lesser_than_a_desktop_file_with_alphabetically_greater_name();
      test_desktop_file_is_greater_than_a_desktop_file_with_alphabetically_lesser_name();
      test_desktop_file_is_equal_to_desktop_file_with_same_name();
      test_desktop_file_is_not_equal_to_desktop_file_with_different_name();

      test_desktop_file_is_valid_when_it_has_name_and_icon_and_executable();
      test_desktop_file_is_not_valid_without_name();
      test_desktop_file_is_not_valid_without_icon();
      test_desktop_file_is_not_valid_without_executable();

      test_desktop_file_is_a_audiovideo_if_tag_includes_AudioVideo();
      test_desktop_file_is_not_a_audiovideo_if_tag_excludes_AudioVideo();
      test_desktop_file_is_a_audiovideo_if_tag_includes_AudioVideo_without_trailing_semicolon();
      test_desktop_file_is_not_a_audiovideo_if_empty();

      test_desktop_file_is_any_of_audiovideo_and_multimedia_if_tag_includes_AudioVideo();
      test_desktop_file_is_not_any_of_audiovideo_or_mutlimedia_if_tag_excludes_AudioVideo_and_multimedia();
      return qunit.errors();
    }

  };
}

int main()
{
  return amm::desktop_file_test(std::cerr, QUnit::normal).run();
}
