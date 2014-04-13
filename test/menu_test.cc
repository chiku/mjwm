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

#define CATCH_CONFIG_MAIN

#include "menu.h"

#include <string>
#include <vector>

#include "catch.hpp"
#include "representation.h"
#include "transformer_interface.h"
#include "service/icon_service_interface.h"

namespace amm {

static const std::string kapplicationFixturesDirectory = "test/fixtures/applications/";

class TestTransformer : public TransformerInterface {
 public:
  std::string Transform(const representation::MenuStart &entry) const {
    return "Menu start--> name: " + entry.name();
  }

  std::string Transform(const representation::MenuEnd &entry) const {
    return "Menu end--> name: " + entry.name();
  }

  std::string Transform(const representation::SubcategoryStart &entry) const {
    return "Subsection start--> name: " + entry.name() + " icon: " + entry.icon();
  }

  std::string Transform(const representation::SubcategoryEnd &entry) const {
    return "Subsection end--> name: " + entry.name();
  }

  std::string Transform(const representation::Program &entry) const {
    return "Program--> name: " + entry.name() + " icon: " + entry.icon() + " executable: " + entry.executable();
  }
};

class TestIconService : public service::IconServiceInterface {
 public:
  std::string ResolvedName(std::string name) const {
    return name + ".always";
  }
};

static void clear_memory(std::vector<RepresentationInterface*> representations) {
  for (std::vector<RepresentationInterface*>::iterator iter = representations.begin(); iter != representations.end(); ++iter) {
    delete *iter;
  }
}


SCENARIO("Menu custom categories", "[menu]") {
  GIVEN("A menu") {
    Menu menu;

    WHEN("loaded with custom categories") {
      std::vector<std::string> lines;
      lines.push_back("Accessories:accessories:Utility");
      lines.push_back("Games:games:Game");
      menu.LoadCustomCategories(lines);

      THEN("it stores them in its subcategories") {
        std::vector<Subcategory> subcategories = menu.Subcategories();

        REQUIRE(subcategories.size() == 2);
        REQUIRE(subcategories[0].DisplayName() == "Accessories");
        REQUIRE(subcategories[1].DisplayName() == "Games");
      }
    }

    WHEN("given a line beginning with '#'") {
      std::vector<std::string> lines;
      lines.push_back("# Comments");
      lines.push_back("#More:comment:here");
      menu.LoadCustomCategories(lines);

      THEN("it ignores it the lines begenning with '#'") {
        std::vector<Subcategory> subcategories = menu.Subcategories();

        REQUIRE(subcategories.size() == 0);
      }
    }

    WHEN("given a line with less than three tokens") {
      std::vector<std::string> lines;
      lines.push_back("Accessories::Accessories");
      lines.push_back("Game:Games");
      menu.LoadCustomCategories(lines);

      THEN("it ignores the lines") {
        std::vector<Subcategory> subcategories = menu.Subcategories();

        REQUIRE(subcategories.size() == 0);
      }
    }


    WHEN("loaded with custom categories with more than three tokens") {
      std::vector<std::string> lines;
      lines.push_back("Games:games:Game:Fun");
      menu.LoadCustomCategories(lines);

      THEN("it has multiple classifications in its subcategories") {
        std::vector<Subcategory> subcategories = menu.Subcategories();

        REQUIRE(subcategories.size() == 1);
        REQUIRE(subcategories[0].DisplayName() == "Games");

        std::vector<std::string> classification_names = subcategories[0].ClassificationNames();
        REQUIRE(classification_names.size() == 2);
        REQUIRE(classification_names[0] == "Game");
        REQUIRE(classification_names[1] == "Fun");
      }
    }

    WHEN("given a line with more than three tokens but with some classification names as empty") {
      std::vector<std::string> lines;
      lines.push_back("Games:games:Game::Fun::Frolic");
      menu.LoadCustomCategories(lines);

      THEN("it ignores the missing classification names") {
        std::vector<Subcategory> subcategories = menu.Subcategories();

        REQUIRE(subcategories.size() == 1);

        std::vector<std::string> classification_names = subcategories[0].ClassificationNames();
        REQUIRE(classification_names.size() == 3);
        REQUIRE(classification_names[0] == "Game");
        REQUIRE(classification_names[1] == "Fun");
        REQUIRE(classification_names[2] == "Frolic");
      }
    }

    WHEN("given a line without a single classification name") {
      std::vector<std::string> lines;
      lines.push_back("Games:games:::");
      menu.LoadCustomCategories(lines);

      THEN("it ignores the lines with missing classification names") {
        std::vector<Subcategory> subcategories = menu.Subcategories();

        REQUIRE(subcategories.size() == 0);
      }
    }
  }
}

SCENARIO("Menu statistics", "[menu]") {
  GIVEN("A menu") {
    Menu menu;

    WHEN("successfully parsed") {
      std::vector<std::string> files;
      files.push_back(kapplicationFixturesDirectory + "vlc.desktop");
      files.push_back(kapplicationFixturesDirectory + "mousepad.desktop");
      menu.Populate(files);
      Stats summary = menu.Summary();

      THEN("it holds the number of total files") {
        REQUIRE(summary.TotalParsedFiles() == 2);
      }
    }

    WHEN("parsing an unclassified desktop file") {
      std::vector<std::string> files;
      files.push_back(kapplicationFixturesDirectory + "unclassified.desktop");
      files.push_back(kapplicationFixturesDirectory + "mousepad.desktop");
      menu.Populate(files);
      Stats summary = menu.Summary();

      THEN("it holds the number of unclassified files") {
        REQUIRE(summary.TotalUnclassifiedFiles() == 1);
      }

      THEN("it holds the categories that weren't handled") {
        std::vector<std::string> unhandled_classifications = summary.UnhandledClassifications();

        REQUIRE(unhandled_classifications.size() == 1);
        REQUIRE(unhandled_classifications[0] == "GTK");
      }
    }

    WHEN("parsing a file suppressed with 'NoDisplay=true'") {
      std::vector<std::string> files;
      files.push_back(kapplicationFixturesDirectory + "mousepad.desktop");
      files.push_back(kapplicationFixturesDirectory + "suppressed.desktop");
      menu.Populate(files);
      Stats summary = menu.Summary();

      THEN("it holds the number of suppressed files") {
        REQUIRE(summary.TotalSuppressedFiles() == 1);
      }
    }

    WHEN("parsing a file with missing entries") {
      std::vector<std::string> files;
      files.push_back(kapplicationFixturesDirectory + "vlc.desktop");
      files.push_back(kapplicationFixturesDirectory + "missing.desktop");
      menu.Populate(files);
      Stats summary = menu.Summary();

      THEN("it holds the a list of unparsed files") {
        std::vector<std::string> unparsed_files = summary.UnparsedFiles();

        REQUIRE(unparsed_files.size() == 1);
        REQUIRE(unparsed_files[0] == kapplicationFixturesDirectory + "missing.desktop");
      }
    }

    WHEN("parsing a file with missing and suppressed entries") {
      std::vector<std::string> files;
      files.push_back(kapplicationFixturesDirectory + "suppressed.desktop");
      files.push_back(kapplicationFixturesDirectory + "suppressedinvalid.desktop");
      files.push_back(kapplicationFixturesDirectory + "missing.desktop");
      menu.Populate(files);
      Stats summary = menu.Summary();

      THEN("missing entries excludes suppressed files") {
        std::vector<std::string> unparsed_files = summary.UnparsedFiles();

        REQUIRE(unparsed_files.size() == 1);
        REQUIRE(unparsed_files[0] == kapplicationFixturesDirectory + "missing.desktop");
      }
    }
  }
}

SCENARIO("Menu sort", "[menu]") {
  GIVEN("A menu") {
    std::vector<std::string> lines;
    lines.push_back("Multimedia:multimedia:AudioVideo");
    lines.push_back("Utilities:utilities:Utility");

    std::vector<std::string> files;
    files.push_back(kapplicationFixturesDirectory + "vlc.desktop");
    files.push_back(kapplicationFixturesDirectory + "nested/xfburn.desktop");
    files.push_back(kapplicationFixturesDirectory + "nested/deepnested/whaawmp.desktop");
    files.push_back(kapplicationFixturesDirectory + "mousepad.desktop");

    Menu menu;
    menu.LoadCustomCategories(lines);
    menu.Populate(files);

    WHEN("sorted") {
      menu.Sort();

      THEN("it sorts the individual entries inside subcategories") {
        std::vector<Subcategory> subcategories = menu.Subcategories();
        REQUIRE(subcategories.size() == 3);

        REQUIRE(subcategories[0].DisplayName() == "Multimedia");
        std::vector<DesktopFile> multimedia_files = subcategories[0].DesktopFiles();
        REQUIRE(multimedia_files.size() == 3);
        REQUIRE(multimedia_files[0].Name() == "VLC media player");
        REQUIRE(multimedia_files[1].Name() == "Whaaw! Media Player");
        REQUIRE(multimedia_files[2].Name() == "Xfburn");

        REQUIRE(subcategories[1].DisplayName() == "Utilities");
        std::vector<DesktopFile> utility_files = subcategories[1].DesktopFiles();
        REQUIRE(utility_files.size() == 2);
        REQUIRE(utility_files[0].Name() == "Mousepad");
        REQUIRE(utility_files[1].Name() == "Xfburn");

        REQUIRE(subcategories[2].DisplayName() == "Others");
        std::vector<DesktopFile> other_files = subcategories[2].DesktopFiles();
        REQUIRE(other_files.size() == 0);
      }
    }
  }
}

SCENARIO("Menu representations", "[menu]") {
  GIVEN("A menu") {
    Menu menu;

    WHEN("transformed to a representations") {
      std::vector<std::string> files;
      files.push_back(kapplicationFixturesDirectory + "vlc.desktop");
      files.push_back(kapplicationFixturesDirectory + "mousepad.desktop");

      menu.Populate(files);
      std::vector<RepresentationInterface*> representations = menu.Representations();
      TestTransformer test_transformer;

      THEN("it stores menu start, subcategory start, menu entry, subcategory end and menu end") {
        REQUIRE(representations.size() == 8);
        REQUIRE(representations[0]->visit(test_transformer) == "Menu start--> name: Menu start");
        REQUIRE(representations[1]->visit(test_transformer) == "Subsection start--> name: Accessories icon: applications-accessories");
        REQUIRE(representations[2]->visit(test_transformer) == "Program--> name: Mousepad icon: accessories-text-editor executable: mousepad %F");
        REQUIRE(representations[3]->visit(test_transformer) == "Subsection end--> name: Accessories end");
        REQUIRE(representations[4]->visit(test_transformer) == "Subsection start--> name: Multimedia icon: applications-multimedia");
        REQUIRE(representations[5]->visit(test_transformer) == "Program--> name: VLC media player icon: vlc executable: /usr/bin/vlc --started-from-file %U");
        REQUIRE(representations[6]->visit(test_transformer) == "Subsection end--> name: Multimedia end");
        REQUIRE(representations[7]->visit(test_transformer) == "Menu end--> name: Menu end");

        clear_memory(representations);
      }
    }

    WHEN("transformed to a representations with icon service") {
      std::vector<std::string> files;
      files.push_back(kapplicationFixturesDirectory + "vlc.desktop");
      files.push_back(kapplicationFixturesDirectory + "mousepad.desktop");

      TestIconService *icon_service = new TestIconService;
      menu.RegisterIconService(*icon_service);

      menu.Populate(files);
      std::vector<RepresentationInterface*> representations = menu.Representations();
      TestTransformer test_transformer;

      THEN("it adds the icon name to icons for subcategory and menu-entry") {
        REQUIRE(representations.size() == 8);
        REQUIRE(representations[0]->visit(test_transformer) == "Menu start--> name: Menu start");
        REQUIRE(representations[1]->visit(test_transformer) == "Subsection start--> name: Accessories icon: applications-accessories.always");
        REQUIRE(representations[2]->visit(test_transformer) == "Program--> name: Mousepad icon: accessories-text-editor.always executable: mousepad %F");
        REQUIRE(representations[3]->visit(test_transformer) == "Subsection end--> name: Accessories end");
        REQUIRE(representations[4]->visit(test_transformer) == "Subsection start--> name: Multimedia icon: applications-multimedia.always");
        REQUIRE(representations[5]->visit(test_transformer) == "Program--> name: VLC media player icon: vlc.always executable: /usr/bin/vlc --started-from-file %U");
        REQUIRE(representations[6]->visit(test_transformer) == "Subsection end--> name: Multimedia end");
        REQUIRE(representations[7]->visit(test_transformer) == "Menu end--> name: Menu end");

        clear_memory(representations);
      }
    }
  }
}

} // namespace amm
