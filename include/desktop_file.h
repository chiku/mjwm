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

#ifndef AMM_DESKTOP_FILE_H_
#define AMM_DESKTOP_FILE_H_

#include <string>
#include <vector>

namespace amm {
// Understands the representation of a FreeDesktop .desktop file
class DesktopFile {
 public:
  DesktopFile();

  std::string Name() const { return name_; }
  std::string Icon() const { return icon_; }
  std::string Executable() const { return executable_; }
  std::vector<std::string> Categories() const { return categories_; }
  bool Display() const { return display_; }

  bool operator < (const DesktopFile &other) const;
  bool operator > (const DesktopFile &other) const;
  bool operator == (const DesktopFile &other) const;
  bool operator != (const DesktopFile &other) const;

  bool IsValid() const;
  bool IsA(std::string type) const;
  bool IsAnyOf(std::vector<std::string> types) const;
  void Populate(std::string line);

 private:
  std::string name_;
  std::string executable_;
  std::string icon_;
  std::vector<std::string> categories_;
  bool display_;
};
} // namespace amm

#endif // AMM_DESKTOP_FILE_H_
