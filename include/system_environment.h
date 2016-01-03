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

#ifndef AMM_SYSTEM_ENVIRONMENT_H_
#define AMM_SYSTEM_ENVIRONMENT_H_

#include <string>
#include <vector>

namespace amm {
// Understands environment variables
class SystemEnvironment
{
public:
    SystemEnvironment();
    bool isValid() const { return home() != ""; }
    std::string home() const { return home_; }
    std::string xdgDataHome() const { return xdg_data_home_; }
    std::vector<std::string> xdgDataDirectories() const;
    std::string language() const { return language_; }
    std::vector<std::string> applicationDirectories() const;
    std::vector<std::string> iconThemeDirectories() const;

private:
    std::string home_;
    std::string xdg_data_home_;
    std::string xdg_data_dirs_;
    std::string language_;

    std::string getLanguageWith(const char *raw);
};
} // namespace amm

#endif // AMM_SYSTEM_ENVIRONMENT_H_
