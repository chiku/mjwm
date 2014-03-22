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

run() {
	printf "%s: " $1
	./$1
}

run mjwm_desktop_file_categories_test
run mjwm_desktop_file_test
run mjwm_menu_entry_jwm_test
run mjwm_transform_jwm_test
run mjwm_subcategory_test
run mjwm_menu_test

cd ..
