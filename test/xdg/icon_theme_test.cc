/*
  This file is part of mjwm.
  Copyright (C) 2014-2016  Chirantan Mitra <chirantan.mitra@gmail.com>

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

#include "xdg/icon_theme.h"

#include <vector>
#include <string>

#include "../doctest.h"

namespace amm {
namespace xdg {

std::vector<std::string> hicolorThemeLines()
{
    std::vector<std::string> lines;
    lines.push_back("[Icon Theme]");
    lines.push_back("Name=Hicolor");
    lines.push_back("Directories=48x48/apps,48x48/mimetypes,32x32/apps,scalable/apps,scalable/mimetypes");
    return lines;
}

std::vector<std::string> birchIconThemeLinesWithoutParent()
{
    std::vector<std::string> lines;
    lines.push_back("[Icon Theme]");
    lines.push_back("Name=Birch");
    lines.push_back("Name[sv]=Björk");
    lines.push_back("Comment=Icon theme with a wooden look");
    lines.push_back("Comment[sv]=Träinspirerat ikontema");
    lines.push_back("Directories=48x48/apps,48x48/mimetypes,32x32/apps,scalable/apps,scalable/mimetypes");
    return lines;
}

std::vector<std::string> birchIconThemeLines()
{
    std::vector<std::string> lines = birchIconThemeLinesWithoutParent();
    lines.push_back("Inherits=wood,default");
    return lines;
}

std::vector<std::string> subdirectoryLinesForScalableApps()
{
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

std::vector<std::string> joinLists(std::vector<std::string> first, std::vector<std::string> second)
{
    first.insert(first.end(), second.begin(), second.end());
    return first;
}

SCENARIO("xdg::IconTheme") {
    GIVEN("An Icon Theme") {
        WHEN("created") {
            IconTheme icon_theme(birchIconThemeLines());

            THEN("it has a name") {
                CHECK(icon_theme.name() == "Birch");
            }

            THEN("it has a list of parents") {
                std::vector<std::string> parents = icon_theme.parents();
                REQUIRE(parents.size() == 2);
                CHECK(parents[0] == "wood");
                CHECK(parents[1] == "default");
            }

            THEN("it has a list of directories") {
                std::vector<IconSubdirectory> directories = icon_theme.directories();
                REQUIRE(directories.size() == 5);
                CHECK(directories[0].name() == "48x48/apps");
                CHECK(directories[1].name() == "48x48/mimetypes");
                CHECK(directories[2].name() == "32x32/apps");
                CHECK(directories[3].name() == "scalable/apps");
                CHECK(directories[4].name() == "scalable/mimetypes");
            }
        }

        WHEN("registered with its internal name") {
            IconTheme icon_theme(birchIconThemeLines());
            icon_theme.internalNameIs("birch");

            THEN("it can be referred to by its internal name") {
                CHECK(icon_theme.isNamed("birch"));
            }

            THEN("it can be referred to by its display name") {
                CHECK(icon_theme.isNamed("Birch"));
            }

            THEN("it can't be referred to other names") {
                CHECK(!icon_theme.isNamed("Wood"));
            }
        }

        WHEN("without explicit parents") {
            IconTheme icon_theme(birchIconThemeLinesWithoutParent());

            THEN("its parent is Hicolor") {
                std::vector<std::string> parents = icon_theme.parents();
                REQUIRE(parents.size() == 1);
                CHECK(parents[0] == "Hicolor");
            }
        }

        WHEN("Hicolor") {
            IconTheme icon_theme(hicolorThemeLines());

            THEN("it has no parents") {
                std::vector<std::string> parents = icon_theme.parents();
                CHECK(parents.empty());
            }
        }
    }

    GIVEN("An Icon Theme with sub-directories") {
        IconTheme icon_theme(joinLists(birchIconThemeLines(), subdirectoryLinesForScalableApps()));
        std::vector<IconSubdirectory> directories = icon_theme.directories();

        WHEN("the sub-directory has all properties") {
            IconSubdirectory scalable_apps = directories[3];

            THEN("the sub-directory has a size") {
                CHECK(scalable_apps.size() == 48);
            }

            THEN("the sub-directory has a type") {
                CHECK(scalable_apps.type() == SCALABLE);
            }

            THEN("the sub-directory has a maximum size") {
                CHECK(scalable_apps.maxSize() == 256);
            }

            THEN("the sub-directory has a threshold") {
                CHECK(scalable_apps.threshold() == 208);
            }
        }
    }
}

} // namespace xdg
} // namespace amm
