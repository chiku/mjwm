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

#include <string>
#include <vector>

#include "stringx.h"
#include "filex.h"
#include "icon_search/icon_search_interface.h"
#include "icon_search/mirror_search.h"
#include "xdg/desktop_entry.h"
#include "subcategory.h"
#include "representation/menu_start.h"
#include "representation/menu_end.h"
#include "representation/subcategory_start.h"
#include "representation/subcategory_end.h"
#include "representation/program.h"

namespace amm {

Menu::Menu() : icon_searcher_(new icon_search::MirrorSearch), unclassified_subcategory_(Subcategory("Others", "applications-others", "Others"))
{
    CreateDefaultCategories();
}

Menu::~Menu()
{
    delete icon_searcher_;
}

void Menu::RegisterIconService(icon_search::IconSearchInterface &icon_searcher)
{
    delete icon_searcher_;
    icon_searcher_ = &icon_searcher;
}

void Menu::CreateDefaultCategories()
{
    subcategories_.clear();

    subcategories_.push_back(Subcategory("Settings",    "gnome-settings",           "Settings"   ));
    subcategories_.push_back(Subcategory("Accessories", "applications-accessories", "Utility"    ));
    subcategories_.push_back(Subcategory("Development", "applications-development", "Development"));
    subcategories_.push_back(Subcategory("Education",   "applications-science",     "Education"  ));
    subcategories_.push_back(Subcategory("Games",       "applications-games",       "Game"       ));
    subcategories_.push_back(Subcategory("Graphics",    "applications-graphics",    "Graphics"   ));
    subcategories_.push_back(Subcategory("Internet",    "applications-internet",    "Network"    ));
    subcategories_.push_back(Subcategory("Multimedia",  "applications-multimedia",  "AudioVideo" ));
    subcategories_.push_back(Subcategory("Office",      "applications-office",      "Office"     ));
    subcategories_.push_back(Subcategory("Science",     "applications-science",     "Science"    ));
    subcategories_.push_back(Subcategory("System",      "applications-system",      "System"     ));
}

void Menu::LoadCustomCategories(std::vector<std::string> lines)
{
    subcategories_.clear();

    for (std::vector<std::string>::const_iterator line = lines.begin(); line != lines.end(); ++line) {
        if ((*line)[0] != '#') {
            std::vector<std::string> tokens = StringX(StringX(*line).Trim()).Split(":");
            if (tokens.size() >= 3 && tokens[0] != "" && tokens[1] != "") {
                std::vector<std::string> classification_names;
                for (std::vector<std::string>::const_iterator token = tokens.begin()+2; token != tokens.end(); ++token) {
                    if (*token != "") {
                        classification_names.push_back(*token);
                    }
                }
                if (classification_names.size() > 0) {
                    subcategories_.push_back(Subcategory(tokens[0], tokens[1], classification_names));
                }
            }
        }
    }
}

void Menu::Populate(std::vector<std::string> entry_names)
{
    for (std::vector<std::string>::const_iterator name = entry_names.begin(); name != entry_names.end(); ++name) {
        AddDesktopEntry(*name);
    }

    subcategories_.push_back(unclassified_subcategory_);
}

void Menu::AddDesktopEntry(std::string entry_name)
{
    std::vector<std::string> lines;
    if (!FileX(entry_name).Load(&lines)) {
        summary_.AddUnparsedFile(entry_name);
        return;
    }
    xdg::DesktopEntry entry(lines);

    if (!entry.Display()) {
        summary_.AddSuppressedFile(entry_name);
        return;
    }

    if (!entry.IsValid()) {
        summary_.AddUnparsedFile(entry_name);
        return;
    }

    bool classified = Classify(entry);
    if (classified) {
        summary_.AddClassifiedFile(entry_name);
    } else {
        unclassified_subcategory_.AddDesktopEntry(entry);
        summary_.AddUnclassifiedFile(entry_name);
        summary_.AddUnhandledClassifications(entry.Categories());
    }
}

bool Menu::Classify(xdg::DesktopEntry entry)
{
    bool classified = false;

    std::vector<Subcategory>::iterator subcategory;
    for (subcategory = subcategories_.begin(); subcategory != subcategories_.end(); ++subcategory) {
        if (entry.IsAnyOf(subcategory->ClassificationNames())) {
            classified = true;
            subcategory->AddDesktopEntry(entry);
        }
    }

    return classified;
}

void Menu::Sort()
{
    std::vector<Subcategory>::iterator group;
    for (group = subcategories_.begin(); group != subcategories_.end(); ++group) {
        group->SortDesktopEntries();
    }
}

std::vector<RepresentationInterface*> Menu::Representations() const
{
    std::vector<RepresentationInterface*> representations;
    representation::MenuStart *menu_start = new representation::MenuStart;
    representations.push_back(menu_start);

    std::vector<Subcategory>::const_iterator subcategory;
    for (subcategory = subcategories_.begin(); subcategory != subcategories_.end(); ++subcategory) {
        if (subcategory->HasEntries()) {
            std::string icon_name = icon_searcher_->resolvedName(subcategory->IconName());
            representation::SubcategoryStart *start = new representation::SubcategoryStart(subcategory->DisplayName(), icon_name);
            representations.push_back(start);

            std::vector<xdg::DesktopEntry> entries = subcategory->DesktopEntries();
            for (std::vector<xdg::DesktopEntry>::const_iterator entry = entries.begin(); entry != entries.end(); ++entry) {
                std::string icon_name = icon_searcher_->resolvedName(entry->Icon());
                representation::Program *program = new representation::Program(entry->Name(), icon_name, entry->Executable(), entry->Comment());
                representations.push_back(program);
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
