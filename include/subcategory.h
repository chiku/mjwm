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

#ifndef AMM_SUBCATEGORY_H_
#define AMM_SUBCATEGORY_H_

#include <string>
#include <vector>

#include "desktop_entry.h"

namespace amm {
// Understands a collection of desktop files belonging to the same category
class Subcategory {
 public:
  Subcategory() {}
  Subcategory(std::string display_name, std::string icon_name, std::string classification_name);
  Subcategory(std::string display_name, std::string icon_name, std::vector<std::string> classification_names);

  std::string DisplayName() const { return display_name_; }
  std::string IconName() const { return icon_name_; }
  std::vector<std::string> ClassificationNames() const { return classification_names_; }
  std::vector<DesktopEntry> DesktopEntries() const { return desktop_entries_; }

  bool HasEntries() const;
  void AddDesktopEntry(DesktopEntry desktop_file);
  void SortDesktopEntries();

 private:
  std::string display_name_;
  std::string icon_name_;
  std::vector<std::string> classification_names_;
  std::vector<DesktopEntry> desktop_entries_;
};
} // namespace amm

#endif // AMM_SUBCATEGORY_H_
