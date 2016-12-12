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

#include "amm_options.h"

#include <string>
#include "stringx.h"

namespace amm {
AmmOptions AmmOptions::Default(const std::string &home, const std::string &language)
{
    AmmOptions amm_options;
    amm_options.is_parsed = false;
    amm_options.is_help = false;
    amm_options.is_version = false;
    amm_options.is_iconize = false;
    amm_options.is_backup = true;
    amm_options.override_default_directories = false;
    amm_options.summary_type = "normal";
    amm_options.output_file_name = StringX(home).terminateWith("/") + (".jwmrc-mjwm");
    amm_options.icon_theme_name = "hicolor";
    amm_options.language = language;
    return amm_options;
}
} // namespace amm
