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

#include "menu.h"

#include <fstream>
#include <string>
#include <vector>

#include "util.h"
#include "icon_service.h"
#include "desktop_file.h"
#include "subcategory.h"

namespace amm {

Menu::Menu() {
  unclassified_subcategory_ = Subcategory("Others", "others", "Others");

  CreateDefaultCategories();
}

void Menu::CreateDefaultCategories() {
  subcategories_.clear();

  subcategories_.push_back(Subcategory("Settings",    "settings",    "Settings"   ));
  subcategories_.push_back(Subcategory("Accessories", "accessories", "Utility"    ));
  subcategories_.push_back(Subcategory("Development", "development", "Development"));
  subcategories_.push_back(Subcategory("Education",   "education",   "Education"  ));
  subcategories_.push_back(Subcategory("Games",       "games",       "Game"       ));
  subcategories_.push_back(Subcategory("Graphics",    "graphics",    "Graphics"   ));
  subcategories_.push_back(Subcategory("Internet",    "internet",    "Network"    ));
  subcategories_.push_back(Subcategory("Multimedia",  "multimedia",  "AudioVideo" ));
  subcategories_.push_back(Subcategory("Office",      "office",      "Office"     ));
  subcategories_.push_back(Subcategory("Science",     "science",     "Science"    ));
  subcategories_.push_back(Subcategory("System",      "system",      "System"     ));
}

void Menu::LoadCustomCategories(std::vector<std::string> lines) {
  subcategories_.clear();

  for (std::vector<std::string>::const_iterator line = lines.begin(); line != lines.end(); ++line) {
    if ((*line)[0] != '#') {
      std::vector<std::string> tokens = StringX(*line).Split(":");
      if (tokens.size() >= 3 && tokens[0] != "" && tokens[1] != "") {
        std::vector<std::string> classification_names;
        for (size_t i = 2; i < tokens.size(); ++i) {
          if (tokens[i] != "") {
            classification_names.push_back(tokens[i]);
          }
        }
        if (classification_names.size() > 0) {
          Subcategory subcategory(tokens[0], tokens[1], classification_names);
          subcategories_.push_back(subcategory);
        }
      }
    }
  }
}

void Menu::Populate(std::vector<std::string> desktop_file_names) {
  std::vector<std::string>::const_iterator name;
  for (name = desktop_file_names.begin(); name != desktop_file_names.end(); ++name) {
    std::string line;
    DesktopFile desktop_file;
    std::ifstream file(name->c_str());

    if (file.good()) {
      while (std::getline(file, line)) {
        desktop_file.Populate(line);
      }
      if (!desktop_file.Display()) {
        summary_.AddSuppressedFile(*name);
      } else if (desktop_file.IsValid()) {
        Classify(desktop_file, *name);
      } else {
        summary_.AddUnparsedFile(*name);
      }

      file.close();
    }
  }

  subcategories_.push_back(unclassified_subcategory_);
}

// TODO : desktop file should store which file it was created from
void Menu::Classify(DesktopFile desktop_file, std::string desktop_file_name) {
  bool classified = false;

  std::vector<Subcategory>::iterator subcategory;
  for (subcategory = subcategories_.begin(); subcategory != subcategories_.end(); ++subcategory) {
    if (desktop_file.IsAnyOf(subcategory->ClassificationNames())) {
      classified = true;
      subcategory->AddDesktopFile(desktop_file);
    }
  }

  if (classified) {
    summary_.AddClassifiedFile(desktop_file_name);
  } else {
    unclassified_subcategory_.AddDesktopFile(desktop_file);
    summary_.AddUnclassifiedFile(desktop_file_name);
    summary_.AddUnhandledClassifications(desktop_file.Categories());
  }
}

void Menu::Sort() {
  std::vector<Subcategory>::iterator group;
  for (group = subcategories_.begin(); group != subcategories_.end(); ++group) {
    group->SortDesktopFiles();
  }
}

std::vector<representation::base*> Menu::Representations() const {
  std::vector<representation::base*> representations;
  representation::MenuStart *menu_start = new representation::MenuStart;
  representations.push_back(menu_start);

  std::vector<Subcategory>::const_iterator subcategory;
  for (subcategory = subcategories_.begin(); subcategory != subcategories_.end(); ++subcategory) {
    if (subcategory->HasEntries()) {
      representation::SubcategoryStart *start = new representation::SubcategoryStart(subcategory->DisplayName(), icon_service_.ResolvedName(subcategory->IconName()));
      representations.push_back(start);

      std::vector<DesktopFile> desktop_files = subcategory->DesktopFiles();
      std::vector<DesktopFile>::const_iterator desktop_file;
      for (desktop_file = desktop_files.begin(); desktop_file != desktop_files.end(); ++desktop_file) {
        representation::Program *entry = new representation::Program(desktop_file->Name(), icon_service_.ResolvedName(desktop_file->Icon()), desktop_file->Executable());
        representations.push_back(entry);
      }

      representation::SubcategoryEnd *end = new representation::SubcategoryEnd(subcategory->DisplayName());
      representations.push_back(end);
    }
  }

  representation::MenuEnd *menu_end = new representation::MenuEnd;
  representations.push_back(menu_end);
  return representations;
}

} // namespace amm
