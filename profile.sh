#!/bin/bash

# This file is part of mjwm.
# Copyright (C) 2014-2016  Chirantan Mitra <chirantan.mitra@gmail.com>

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

valgrind --tool=callgrind --cache-sim=yes --branch-sim=yes --callgrind-out-file=callgrind.out ./mjwm --iconize=Faenza
gprof2dot --format=callgrind callgrind.out | dot -Tsvg -o output.svg
