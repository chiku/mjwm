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

#include "xdg/icon_theme.h"

#include <vector>
#include <string>

#include "../catch.hpp"

namespace amm {
namespace xdg {

std::vector<std::string> BirchIconThemeLines() {
  std::vector<std::string> lines;
  lines.push_back("[Icon Theme]");
  lines.push_back("Name=Birch");
  lines.push_back("Name[sv]=Björk");
  lines.push_back("Comment=Icon theme with a wooden look");
  lines.push_back("Comment[sv]=Träinspirerat ikontema");
  lines.push_back("Inherits=wood,default");
  lines.push_back("Directories=48x48/apps,48x48/mimetypes,32x32/apps,scalable/apps,scalable/mimetypes");
  return lines;
}

std::vector<std::string> SubdirectoryLinesForScalableApps() {
  std::vector<std::string> lines;
  lines.push_back("[scalable/apps]");
  lines.push_back("Size=48");
  lines.push_back("Type=Scalable");
  lines.push_back("MinSize=1");
  lines.push_back("MaxSize=256");
  lines.push_back("Threshold=208");
  lines.push_back("Context=Applications");
  lines.push_back("");
  return lines;
}

std::vector<std::string> Join(std::vector<std::string> first, std::vector<std::string> second) {
  first.insert(first.end(), second.begin(), second.end());
  return first;
}

SCENARIO("xdg::IconTheme", "[icontheme]") {
  GIVEN("An Icon Theme") {
    WHEN("created") {
      IconTheme icon_theme(BirchIconThemeLines());

      THEN("it has a name") {
        REQUIRE(icon_theme.Name() == "Birch");
      }

      THEN("it has a list of parents") {
        std::vector<std::string> parents = icon_theme.Parents();
        REQUIRE(parents.size() == 2);
        REQUIRE(parents[0] == "wood");
        REQUIRE(parents[1] == "default");
      }

      THEN("it has a list of directories") {
        std::vector<IconSubdirectory> directories = icon_theme.Directories();
        REQUIRE(directories.size() == 5);
        REQUIRE(directories[0].Name() == "48x48/apps");
        REQUIRE(directories[1].Name() == "48x48/mimetypes");
        REQUIRE(directories[2].Name() == "32x32/apps");
        REQUIRE(directories[3].Name() == "scalable/apps");
        REQUIRE(directories[4].Name() == "scalable/mimetypes");
      }
    }
  }

  GIVEN("An Icon Theme with sub-directories") {
    IconTheme icon_theme(Join(BirchIconThemeLines(), SubdirectoryLinesForScalableApps()));
    std::vector<IconSubdirectory> directories = icon_theme.Directories();

    WHEN("the sub-directory has all properties") {
      IconSubdirectory scalable_apps = directories[3];

      THEN("the sub-directory has a size") {
        REQUIRE(scalable_apps.Size() == 48);
      }

      THEN("the sub-directory has a type") {
        REQUIRE(scalable_apps.Type() == "Scalable");
      }

      THEN("the sub-directory has a maximum size") {
        REQUIRE(scalable_apps.MaxSize() == 256);
      }

      THEN("the sub-directory has a threshold") {
        REQUIRE(scalable_apps.Threshold() == 208);
      }
    }
  }
}

} // namespace xdg
} // namespace amm
