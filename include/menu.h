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

#ifndef AMM_MENU_H_
#define AMM_MENU_H_

#include <string>
#include <vector>

#include "stats.h"
#include "subcategory.h"
#include "icon_search/icon_search_interface.h"
#include "representation/representation_interface.h"

namespace amm {
// Understands a collection of desktop files divided in subcategories
// TODO : Split amm::Menu
class Menu
{
public:
    Menu();
    ~Menu();

    void registerIconService(icon_search::IconSearchInterface &icon_searcher);
    void registerLanguage(const std::string &language) { language_ = language; }
    std::vector<Subcategory> subcategories() const { return subcategories_; }
    Stats summary() const { return summary_; }

    void loadCustomCategories(const std::vector<std::string> &lines);
    void populate(const std::vector<std::string> &desktop_file_names);
    void sort();
    std::vector<representation::RepresentationInterface*> representations() const;

private:
    void addDesktopEntry(const std::string &desktop_entry_name);
    bool classify(const xdg::DesktopEntry &entry);
    void createDefaultCategories();

    std::string language_;
    icon_search::IconSearchInterface *icon_searcher_;
    Subcategory unclassified_subcategory_;
    std::vector<Subcategory> subcategories_;
    std::vector<std::string> desktop_file_names_;
    Stats summary_;
};
} // namespace amm

#endif // AMM_MENU_H_
