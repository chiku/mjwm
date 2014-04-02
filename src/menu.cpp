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

#include <fstream>
#include <string>
#include <vector>

#include "util.h"
#include "icon_service.h"
#include "desktop_file.h"
#include "subcategory.h"
#include "menu.h"

amm::menu::menu()
{
  unclassified_subcategory_ = amm::subcategory("Others", "others", "Others");

  create_default_categories();
}

void
amm::menu::create_default_categories()
{
  subcategories_.clear();

  subcategories_.push_back(amm::subcategory("Settings",    "settings",    "Settings"   ));
  subcategories_.push_back(amm::subcategory("Accessories", "accessories", "Utility"    ));
  subcategories_.push_back(amm::subcategory("Development", "development", "Development"));
  subcategories_.push_back(amm::subcategory("Education",   "education",   "Education"  ));
  subcategories_.push_back(amm::subcategory("Games",       "games",       "Game"       ));
  subcategories_.push_back(amm::subcategory("Graphics",    "graphics",    "Graphics"   ));
  subcategories_.push_back(amm::subcategory("Internet",    "internet",    "Network"    ));
  subcategories_.push_back(amm::subcategory("Multimedia",  "multimedia",  "AudioVideo" ));
  subcategories_.push_back(amm::subcategory("Office",      "office",      "Office"     ));
  subcategories_.push_back(amm::subcategory("Science",     "science",     "Science"    ));
  subcategories_.push_back(amm::subcategory("System",      "system",      "System"     ));
}

void
amm::menu::load_custom_categories(std::vector<std::string> lines)
{
  subcategories_.clear();

  for (std::vector<std::string>::const_iterator line = lines.begin(); line != lines.end(); ++line) {
    if ((*line)[0] != '#') {
      std::vector<std::string> tokens = amm::StringX(*line).Split(":");
      if (tokens.size() >= 3 && tokens[0] != "" && tokens[1] != "") {
        std::vector<std::string> classification_names;
        for (size_t i = 2; i < tokens.size(); ++i) {
          if (tokens[i] != "") {
            classification_names.push_back(tokens[i]);
          }
        }
        if (classification_names.size() > 0) {
          amm::subcategory subcategory(tokens[0], tokens[1], classification_names);
          subcategories_.push_back(subcategory);
        }
      }
    }
  }
}

void
amm::menu::register_icon_service(amm::icon_service icon_service)
{
  icon_service_ = icon_service;
}

void
amm::menu::populate(std::vector<std::string> desktop_file_names)
{
  std::vector<std::string>::const_iterator name;
  for (name = desktop_file_names.begin(); name != desktop_file_names.end(); ++name) {
    std::string line;
    amm::DesktopFile desktop_file;
    std::ifstream file(name->c_str());

    if (file.good()) {
      while (std::getline(file, line)) {
        desktop_file.Populate(line);
      }
      if (!desktop_file.display()) {
        stats_.add_suppressed_file(*name);
      } else if (desktop_file.IsValid()) {
        classify(desktop_file, *name);
      } else {
        stats_.add_unparsed_file(*name);
      }

      file.close();
    }
  }

  subcategories_.push_back(unclassified_subcategory_);
}

// TODO : desktop file should store which file it was created from
void
amm::menu::classify(amm::DesktopFile desktop_file, std::string desktop_file_name)
{
  bool classified = false;

  std::vector<amm::subcategory>::iterator subcategory;
  for (subcategory = subcategories_.begin(); subcategory != subcategories_.end(); ++subcategory) {
    if (desktop_file.IsAnyOf(subcategory->classification_names())) {
      classified = true;
      subcategory->add_desktop_file(desktop_file);
    }
  }

  if (classified) {
    stats_.add_classified_file(desktop_file_name);
  } else {
    unclassified_subcategory_.add_desktop_file(desktop_file);
    stats_.add_unclassified_file(desktop_file_name);
    stats_.add_unhandled_classifications(desktop_file.categories());
  }
}

std::vector<amm::subcategory>
amm::menu::subcategories() const
{
  return subcategories_;
}

amm::stats
amm::menu::stats() const
{
  return stats_;
}

void
amm::menu::sort()
{
  std::vector<amm::subcategory>::iterator group;
  for (group = subcategories_.begin(); group != subcategories_.end(); ++group) {
    group->sort_desktop_files();
  }
}

std::vector<amm::representation::base*>
amm::menu::representations() const
{
  std::vector<amm::representation::base*> representations;
  amm::representation::menu_start *menu_start = new amm::representation::menu_start;
  representations.push_back(menu_start);

  std::vector<amm::subcategory>::const_iterator subcategory;
  for (subcategory = subcategories_.begin(); subcategory != subcategories_.end(); ++subcategory) {
    if (subcategory->has_entries()) {
      amm::representation::subcategory_start *start = new amm::representation::subcategory_start(subcategory->display_name(), icon_service_.resolved_name(subcategory->icon_name()));
      representations.push_back(start);

      std::vector<amm::DesktopFile> desktop_files = subcategory->desktop_files();
      std::vector<amm::DesktopFile>::const_iterator desktop_file;
      for (desktop_file = desktop_files.begin(); desktop_file != desktop_files.end(); ++desktop_file) {
        amm::representation::menu_entry *entry = new amm::representation::menu_entry(desktop_file->name(), icon_service_.resolved_name(desktop_file->icon()), desktop_file->executable());
        representations.push_back(entry);
      }

      amm::representation::subcategory_end *end = new amm::representation::subcategory_end(subcategory->display_name());
      representations.push_back(end);
    }
  }

  amm::representation::menu_end *menu_end = new amm::representation::menu_end;
  representations.push_back(menu_end);
  return representations;
}
