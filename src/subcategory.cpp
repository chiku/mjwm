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

#include <string>
#include <vector>
#include <algorithm>

#include "desktop_file.h"
#include "subcategory.h"

amm::subcategory::subcategory()
{
}

// TODO : one of these constructors should not be used / re-implemented in terms of the other
amm::subcategory::subcategory(std::string display_name, std::string icon_name, std::string classification_name)
{
  display_name_ = display_name;
  icon_name_ = icon_name;
  classification_names_.push_back(classification_name);
}

amm::subcategory::subcategory(std::string display_name, std::string icon_name, std::vector<std::string> classification_names)
{
  display_name_ = display_name;
  icon_name_ = icon_name;
  classification_names_ = classification_names;
}

std::string
amm::subcategory::display_name() const
{
  return display_name_;
}

std::vector<std::string>
amm::subcategory::classification_names() const
{
  return classification_names_;
}

std::string
amm::subcategory::icon_name() const
{
  return icon_name_;
}

std::vector<amm::DesktopFile>
amm::subcategory::desktop_files() const
{
  return desktop_files_;
}

bool
amm::subcategory::has_entries() const
{
  return desktop_files().size() > 0;
}

void
amm::subcategory::add_desktop_file(amm::DesktopFile desktop_file)
{
  desktop_files_.push_back(desktop_file);
}

void
amm::subcategory::sort_desktop_files()
{
  std::sort(desktop_files_.begin(), desktop_files_.end());
}
