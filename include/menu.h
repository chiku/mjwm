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

#ifndef AMM_MENU_H_
#define AMM_MENU_H_

#include <string>
#include <vector>

#include "stats.h"
#include "subcategory.h"
#include "service/icon_service_interface.h"
#include "service/icon/mirror.h"
#include "representation_interface.h"

namespace amm {
// Understands a collection of desktop files divided in subcategories
// TODO : Split amm::Menu
class Menu {
 public:
  Menu();
  ~Menu();

  void RegisterIconService(service::IconServiceInterface &icon_service);
  std::vector<Subcategory> Subcategories() const { return subcategories_; }
  Stats Summary() const { return summary_; }

  void LoadCustomCategories(std::vector<std::string> lines);
  void Populate(std::vector<std::string> desktop_file_names);
  void Sort();
  std::vector<RepresentationInterface*> Representations() const;

 private:
  void AddDesktopEntry(std::string desktop_entry_name);
  bool Classify(xdg::DesktopEntry entry);
  void CreateDefaultCategories();

  service::IconServiceInterface *icon_service_;
  Subcategory unclassified_subcategory_;
  std::vector<Subcategory> subcategories_;
  std::vector<std::string> desktop_file_names_;
  Stats summary_;
};
} // namespace amm

#endif // AMM_MENU_H_
