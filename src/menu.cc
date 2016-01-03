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

Menu::Menu() : icon_searcher_(new icon_search::MirrorSearch), unclassified_subcategory_(Subcategory::Others())
{
    createDefaultCategories();
}

Menu::~Menu()
{
    delete icon_searcher_;
}

void Menu::registerIconService(icon_search::IconSearchInterface &icon_searcher)
{
    delete icon_searcher_;
    icon_searcher_ = &icon_searcher;
}

void Menu::createDefaultCategories()
{
    subcategories_.clear();

    subcategories_.push_back(Subcategory::Settings());
    subcategories_.push_back(Subcategory::Accessories());
    subcategories_.push_back(Subcategory::Development());
    subcategories_.push_back(Subcategory::Education());
    subcategories_.push_back(Subcategory::Games());
    subcategories_.push_back(Subcategory::Graphics());
    subcategories_.push_back(Subcategory::Internet());
    subcategories_.push_back(Subcategory::Multimedia());
    subcategories_.push_back(Subcategory::Office());
    subcategories_.push_back(Subcategory::Science());
    subcategories_.push_back(Subcategory::System());
}

void Menu::loadCustomCategories(const std::vector<std::string> &lines)
{
    subcategories_.clear();

    for (std::vector<std::string>::const_iterator line = lines.begin(); line != lines.end(); ++line) {
        if ((*line)[0] != '#') {
            std::vector<std::string> tokens = StringX(StringX(*line).trim()).split(":");
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

void Menu::populate(const std::vector<std::string> &entry_names)
{
    for (std::vector<std::string>::const_iterator name = entry_names.begin(); name != entry_names.end(); ++name) {
        addDesktopEntry(*name);
    }

    subcategories_.push_back(unclassified_subcategory_);
}

void Menu::addDesktopEntry(const std::string &entry_name)
{
    std::vector<std::string> lines;
    if (!FileX(entry_name).readLines(&lines)) {
        summary_.addUnparsedFile(entry_name);
        return;
    }
    xdg::DesktopEntry entry;
    entry.hasLanguage(language_);
    entry.parse(lines);

    if (!entry.display()) {
        summary_.addSuppressedFile(entry_name);
        return;
    }

    if (!entry.isValid()) {
        summary_.addUnparsedFile(entry_name);
        return;
    }

    bool classified = classify(entry);
    if (classified) {
        summary_.addClassifiedFile(entry_name);
    } else {
        unclassified_subcategory_.addDesktopEntry(entry);
        summary_.addUnclassifiedFile(entry_name);
        summary_.addUnhandledClassifications(entry.categories());
    }
}

bool Menu::classify(const xdg::DesktopEntry &entry)
{
    bool classified = false;

    std::vector<Subcategory>::iterator subcategory;
    for (subcategory = subcategories_.begin(); subcategory != subcategories_.end(); ++subcategory) {
        if (entry.isAnyOf(subcategory->classificationNames())) {
            classified = true;
            subcategory->addDesktopEntry(entry);
        }
    }

    return classified;
}

void Menu::sort()
{
    std::vector<Subcategory>::iterator group;
    for (group = subcategories_.begin(); group != subcategories_.end(); ++group) {
        group->sortDesktopEntries();
    }
}

std::vector<representation::RepresentationInterface*> Menu::representations() const
{
    std::vector<representation::RepresentationInterface*> representations;
    representation::MenuStart *menu_start = new representation::MenuStart;
    representations.push_back(menu_start);

    std::vector<Subcategory>::const_iterator subcategory;
    for (subcategory = subcategories_.begin(); subcategory != subcategories_.end(); ++subcategory) {
        if (subcategory->hasEntries()) {
            std::string icon_name = icon_searcher_->resolvedName(subcategory->iconName());
            representation::SubcategoryStart *start = new representation::SubcategoryStart(subcategory->displayName(), icon_name);
            representations.push_back(start);

            std::vector<xdg::DesktopEntry> entries = subcategory->desktopEntries();
            for (std::vector<xdg::DesktopEntry>::const_iterator entry = entries.begin(); entry != entries.end(); ++entry) {
                std::string icon_name = icon_searcher_->resolvedName(entry->icon());
                representation::Program *program = new representation::Program(entry->name(), icon_name, entry->executable(), entry->comment());
                representations.push_back(program);
            }

            representation::SubcategoryEnd *end = new representation::SubcategoryEnd(subcategory->displayName());
            representations.push_back(end);
        }
    }

    representation::MenuEnd *menu_end = new representation::MenuEnd;
    representations.push_back(menu_end);
    return representations;
}

} // namespace amm
