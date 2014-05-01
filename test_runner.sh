#!/bin/sh

# This file is part of mjwm.
# Copyright (C) 2014  Chirantan Mitra <chirantan.mitra@gmail.com>

# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.

# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

set -e

cd `dirname $0`

suites=0

run() {
	suites=$((suites+1))
	printf "%s: " $1
	./$1
}

run mjwm_stringx_test
run mjwm_vectorx_test
run mjwm_xdg_entry_test
run mjwm_xdg_entry_line_test
run mjwm_xdg_desktop_entry_test
run mjwm_xdg_icon_theme_test
run mjwm_subcategory_test
run mjwm_stats_test
run mjwm_menu_test
run mjwm_service_file_search_test
run mjwm_transformer_jwm_test
run mjwm_command_line_options_parser_test
run mjwm_service_environment_variable_test

echo "Suites run: $suites"

cd ..
