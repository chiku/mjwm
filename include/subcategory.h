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

#ifndef AMM_SUBCATEGORY_H_
#define AMM_SUBCATEGORY_H_

#include <string>
#include <vector>

#include "xdg/desktop_entry.h"

namespace amm {
// Understands a collection of desktop files belonging to the same category
class Subcategory
{
public:
    Subcategory() {}
    Subcategory(const std::string &display_name, const std::string &icon_name, const std::string &classification_name);
    Subcategory(const std::string &display_name, const std::string &icon_name, const std::vector<std::string> &classification_names);

    std::string displayName() const { return display_name_; }
    std::string iconName() const { return icon_name_; }
    std::vector<std::string> classificationNames() const { return classification_names_; }
    std::vector<xdg::DesktopEntry> desktopEntries() const { return desktop_entries_; }

    bool hasEntries() const;
    void addDesktopEntry(const xdg::DesktopEntry &desktop_file);
    void sortDesktopEntries();

    static Subcategory Others()      { return Subcategory("Others",      "applications-others",      "Others"     ); }
    static Subcategory Settings()    { return Subcategory("Settings",    "gnome-settings",           "Settings"   ); }
    static Subcategory Accessories() { return Subcategory("Accessories", "applications-accessories", "Utility"    ); }
    static Subcategory Development() { return Subcategory("Development", "applications-development", "Development"); }
    static Subcategory Education()   { return Subcategory("Education",   "applications-science",     "Education"  ); }
    static Subcategory Games()       { return Subcategory("Games",       "applications-games",       "Game"       ); }
    static Subcategory Graphics()    { return Subcategory("Graphics",    "applications-graphics",    "Graphics"   ); }
    static Subcategory Internet()    { return Subcategory("Internet",    "applications-internet",    "Network"    ); }
    static Subcategory Multimedia()  { return Subcategory("Multimedia",  "applications-multimedia",  "AudioVideo" ); }
    static Subcategory Office()      { return Subcategory("Office",      "applications-office",      "Office"     ); }
    static Subcategory Science()     { return Subcategory("Science",     "applications-science",     "Science"    ); }
    static Subcategory System()      { return Subcategory("System",      "applications-system",      "System"     ); }

private:
    std::string display_name_;
    std::string icon_name_;
    std::vector<std::string> classification_names_;
    std::vector<xdg::DesktopEntry> desktop_entries_;
};
} // namespace amm

#endif // AMM_SUBCATEGORY_H_
