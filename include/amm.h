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

#ifndef AMM_AMM_H_
#define AMM_AMM_H_

#include <string>
#include <vector>

#include "amm_options.h"
#include "system_environment.h"
#include "menu.h"
#include "icon_search/icon_search_interface.h"

namespace amm {
class Amm
{
public:
    Amm();
    ~Amm();
    void validateEnvironment() const;
    void loadCommandLineOption(int argc, char **argv);
    void registerIconService();
    void readCategories();
    void readDesktopEntryFiles();
    void populate();
    void writeOutputFile();
    void printSummary() const;

private:
    SystemEnvironment environment_;
    AmmOptions options_;
    Menu menu_;
    std::vector<std::string> desktop_entry_file_names_;
    icon_search::IconSearchInterface *actual_searcher_;
};
} // namespace amm

#endif // AMM_AMM_H_
