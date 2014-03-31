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
#include <string>
#include <sstream>

#include "QUnit.hpp"

#include "menu.h"
#include "representation.h"
#include "transformer.h"

namespace amm
{
  namespace transformer
  {
    class test : public base
    {
      std::string transform(amm::representation::menu_start *entry)
      {
        std::stringstream stream;
        stream << "Menu start--> name: " << entry->name();
        return stream.str();
      }

      std::string transform(amm::representation::menu_end *entry)
      {
        std::stringstream stream;
        stream << "Menu end--> name: " << entry->name();
        return stream.str();
      }

      std::string transform(amm::representation::subcategory_start *entry)
      {
        std::stringstream stream;
        stream << "Subsection start--> name: " << entry->name() << " icon: " << entry->icon();
        return stream.str();
      }

      std::string transform(amm::representation::subcategory_end *entry)
      {
        std::stringstream stream;
        stream << "Subsection end--> name: " << entry->name();
        return stream.str();
      }

      std::string transform(amm::representation::menu_entry *entry)
      {
        std::stringstream stream;
        stream << "Program--> name: " << entry->name() << " icon: " << entry->icon() << " executable: " << entry->executable();
        return stream.str();
      }
    };
  }

  const std::string fixtures_directory = "test/fixtures/";

  // Verifies a collection of desktop files divided in subcategories
  class menu_test
  {
    QUnit::UnitTest qunit;

    void test_menu_loads_categories_from_colon_separated_lines()
    {
      std::vector<std::string> lines;
      lines.push_back("Accessories:accessories:Utility");
      lines.push_back("Games:games:Game");
      menu menu;

      menu.load_custom_categories(lines);
      std::vector<amm::subcategory> subcategories = menu.subcategories();

      QUNIT_IS_EQUAL(2, subcategories.size());
      QUNIT_IS_EQUAL("Accessories", subcategories[0].display_name());
      QUNIT_IS_EQUAL("Games", subcategories[1].display_name());
    }

    void test_menu_associates_multiple_categories_with_same_display_name_when_more_than_three_tokens_are_present()
    {
      std::vector<std::string> lines;
      lines.push_back("Games:games:Game:Fun");
      menu menu;

      menu.load_custom_categories(lines);
      std::vector<amm::subcategory> subcategories = menu.subcategories();

      QUNIT_IS_EQUAL(1, subcategories.size());

      std::vector<std::string> classification_names = subcategories[0].classification_names();
      QUNIT_IS_EQUAL(2, classification_names.size());
      QUNIT_IS_EQUAL("Game", classification_names[0]);
      QUNIT_IS_EQUAL("Fun", classification_names[1]);
    }

    void test_menu_loads_categories_ignores_comments()
    {
      std::vector<std::string> lines;
      lines.push_back("# Comments");
      lines.push_back("Games:Game:games");
      lines.push_back("#More:comment:here");
      menu menu;

      menu.load_custom_categories(lines);
      std::vector<amm::subcategory> subcategories = menu.subcategories();

      QUNIT_IS_EQUAL(1, subcategories.size());
      QUNIT_IS_EQUAL("Games", subcategories[0].display_name());
    }

    void test_menu_loads_categories_ignores_entries_without_three_tokens()
    {
      std::vector<std::string> lines;
      lines.push_back("Accessories::Accessories");
      lines.push_back("Game:Games");
      menu menu;

      menu.load_custom_categories(lines);
      std::vector<amm::subcategory> subcategories = menu.subcategories();

      QUNIT_IS_EQUAL(0, subcategories.size());
    }

    void test_menu_load_categories_skips_missing_classification_names()
    {
      std::vector<std::string> lines;
      lines.push_back("Games:games:Game::Fun::Frolic");
      menu menu;

      menu.load_custom_categories(lines);
      std::vector<amm::subcategory> subcategories = menu.subcategories();

      QUNIT_IS_EQUAL(1, subcategories.size());

      std::vector<std::string> classification_names = subcategories[0].classification_names();
      QUNIT_IS_EQUAL(3, classification_names.size());
      QUNIT_IS_EQUAL("Game", classification_names[0]);
      QUNIT_IS_EQUAL("Fun", classification_names[1]);
      QUNIT_IS_EQUAL("Frolic", classification_names[2]);
    }

    void test_menu_load_categories_skips_categories_without_one_category_name()
    {
      std::vector<std::string> lines;
      lines.push_back("Games:games:::");
      menu menu;

      menu.load_custom_categories(lines);
      std::vector<amm::subcategory> subcategories = menu.subcategories();

      QUNIT_IS_EQUAL(0, subcategories.size());
    }

    void test_menu_stats_successfully_parsed_desktop_files()
    {
      std::vector<std::string> files;
      files.push_back(fixtures_directory + "vlc.desktop");
      files.push_back(fixtures_directory + "mousepad.desktop");
      menu menu;

      menu.populate(files);
      amm::stats stats = menu.stats();

      QUNIT_IS_EQUAL(2, stats.total_parsed_files());
    }

    void test_menu_stats_successfully_parsed_unclassified_desktop_files()
    {
      std::vector<std::string> files;
      files.push_back(fixtures_directory + "unclassified.desktop");
      files.push_back(fixtures_directory + "mousepad.desktop");
      menu menu;

      menu.populate(files);
      amm::stats stats = menu.stats();

      QUNIT_IS_EQUAL(1, stats.total_unclassified_files());
    }

    void test_menu_stats_suppressed_desktop_files()
    {
      std::vector<std::string> files;
      files.push_back(fixtures_directory + "mousepad.desktop");
      files.push_back(fixtures_directory + "suppressed.desktop");
      menu menu;

      menu.populate(files);
      amm::stats stats = menu.stats();

      QUNIT_IS_EQUAL(1, stats.total_suppressed_files());
    }

    void test_menu_stats_unparsed_desktop_files()
    {
      std::vector<std::string> files;
      files.push_back(fixtures_directory + "vlc.desktop");
      files.push_back(fixtures_directory + "missing.desktop");
      menu menu;

      menu.populate(files);
      amm::stats stats = menu.stats();
      std::vector<std::string> unparsed_files = stats.unparsed_files();

      QUNIT_IS_EQUAL(1, unparsed_files.size());
      QUNIT_IS_EQUAL(fixtures_directory + "missing.desktop", unparsed_files[0]);
    }

    void test_menu_stats_unparsed_desktop_files_exclude_suppressed_files()
    {
      std::vector<std::string> files;
      files.push_back(fixtures_directory + "suppressed.desktop");
      files.push_back(fixtures_directory + "suppressedinvalid.desktop");
      files.push_back(fixtures_directory + "missing.desktop");
      menu menu;

      menu.populate(files);
      amm::stats stats = menu.stats();
      std::vector<std::string> unparsed_files = stats.unparsed_files();

      QUNIT_IS_EQUAL(1, unparsed_files.size());
      QUNIT_IS_EQUAL(fixtures_directory + "missing.desktop", unparsed_files[0]);
    }

    void test_menu_stats_the_catagories_that_werent_handled()
    {
      std::vector<std::string> files;
      files.push_back(fixtures_directory + "unclassified.desktop");
      files.push_back(fixtures_directory + "mousepad.desktop");
      menu menu;

      menu.populate(files);
      amm::stats stats = menu.stats();
      std::vector<std::string> unhandled_classifications = stats.unhandled_classifications();

      QUNIT_IS_EQUAL(1, unhandled_classifications.size());
      QUNIT_IS_EQUAL("GTK", unhandled_classifications[0]);
    }

    void test_menu_is_transformed_to_a_collection_of_representations()
    {
      std::vector<std::string> files;
      files.push_back(fixtures_directory + "vlc.desktop");
      files.push_back(fixtures_directory + "mousepad.desktop");
      menu menu;

      menu.populate(files);
      std::vector<amm::representation::base*> representations = menu.representations();
      amm::transformer::test test_transformer;

      QUNIT_IS_EQUAL(8, representations.size());
      QUNIT_IS_EQUAL("Menu start--> name: Menu start", representations[0]->visit(test_transformer));
      QUNIT_IS_EQUAL("Subsection start--> name: Accessories icon: accessories", representations[1]->visit(test_transformer));
      QUNIT_IS_EQUAL("Program--> name: Mousepad icon: accessories-text-editor executable: mousepad %F", representations[2]->visit(test_transformer));
      QUNIT_IS_EQUAL("Subsection end--> name: Accessories end", representations[3]->visit(test_transformer));
      QUNIT_IS_EQUAL("Subsection start--> name: Multimedia icon: multimedia", representations[4]->visit(test_transformer));
      QUNIT_IS_EQUAL("Program--> name: VLC media player icon: vlc executable: /usr/bin/vlc --started-from-file %U", representations[5]->visit(test_transformer));
      QUNIT_IS_EQUAL("Subsection end--> name: Multimedia end", representations[6]->visit(test_transformer));
      QUNIT_IS_EQUAL("Menu end--> name: Menu end", representations[7]->visit(test_transformer));

      clear_memory(representations);
    }

    void test_menu_appends_icon_extension_when_available()
    {
      std::vector<std::string> files;
      files.push_back(fixtures_directory + "vlc.desktop");
      files.push_back(fixtures_directory + "mousepad.desktop");
      menu menu;
      amm::icon_service icon_service;
      icon_service.register_extension(".xpm");
      menu.register_icon_service(icon_service);

      menu.populate(files);
      std::vector<amm::representation::base*> representations = menu.representations();
      amm::transformer::test test_transformer;

      QUNIT_IS_EQUAL(8, representations.size());
      QUNIT_IS_EQUAL("Menu start--> name: Menu start", representations[0]->visit(test_transformer));
      QUNIT_IS_EQUAL("Subsection start--> name: Accessories icon: accessories.xpm", representations[1]->visit(test_transformer));
      QUNIT_IS_EQUAL("Program--> name: Mousepad icon: accessories-text-editor.xpm executable: mousepad %F", representations[2]->visit(test_transformer));
      QUNIT_IS_EQUAL("Subsection end--> name: Accessories end", representations[3]->visit(test_transformer));
      QUNIT_IS_EQUAL("Subsection start--> name: Multimedia icon: multimedia.xpm", representations[4]->visit(test_transformer));
      QUNIT_IS_EQUAL("Program--> name: VLC media player icon: vlc.xpm executable: /usr/bin/vlc --started-from-file %U", representations[5]->visit(test_transformer));
      QUNIT_IS_EQUAL("Subsection end--> name: Multimedia end", representations[6]->visit(test_transformer));
      QUNIT_IS_EQUAL("Menu end--> name: Menu end", representations[7]->visit(test_transformer));

      clear_memory(representations);
    }

    void clear_memory(std::vector<amm::representation::base*> representations)
    {
      for (std::vector<amm::representation::base*>::iterator iter = representations.begin(); iter != representations.end(); ++iter) {
        delete *iter;
      }
    }


  public:
    menu_test(std::ostream &out, int verbose_level) : qunit(out, verbose_level) {}

    int run()
    {
      test_menu_loads_categories_from_colon_separated_lines();
      test_menu_associates_multiple_categories_with_same_display_name_when_more_than_three_tokens_are_present();
      test_menu_loads_categories_ignores_comments();
      test_menu_loads_categories_ignores_entries_without_three_tokens();
      test_menu_load_categories_skips_missing_classification_names();
      test_menu_load_categories_skips_categories_without_one_category_name();

      test_menu_stats_successfully_parsed_desktop_files();
      test_menu_stats_successfully_parsed_unclassified_desktop_files();
      test_menu_stats_suppressed_desktop_files();
      test_menu_stats_unparsed_desktop_files();
      test_menu_stats_unparsed_desktop_files_exclude_suppressed_files();
      test_menu_stats_the_catagories_that_werent_handled();

      test_menu_is_transformed_to_a_collection_of_representations();
      test_menu_appends_icon_extension_when_available();
      return qunit.errors();
    }
  };
}


int main()
{
  return amm::menu_test(std::cerr, QUnit::normal).run();
}
