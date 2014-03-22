
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

#include <iostream>

#include "messages.h"

void
amm::messages::display_help()
{
	std::cout << "mjwm version " << AMM_VERSION <<  ", Copyright (C) 2014 Chirantan Mitra <chirantan.mitra@gmail.com>" << std::endl;
	std::cout << "mjwm comes with ABSOLUTELY NO WARRANTY; for details refer COPYING." << std::endl;
	std::cout << "This is free software, and you are welcome to redistribute it" << std::endl;
	std::cout << "under certain conditions; Refer COPYING for details." << std::endl;

	std::cout << "mjwm creates jwm's menu from (freedesktop) desktop files" << std::endl;
	std::cout << "  -o, --output-file [FILE]           Outfile file [Default: ./automenu]" << std::endl;
	std::cout << "  -s, --input-directory [DIRECTORY]  Directory to scan for '.desktop' files [Default: /usr/share/applications/]" << std::endl;
	std::cout << "  -a, --append-png                   Add '.png' to icon filenames" << std::endl;
	std::cout << "  -v, --version                      Show version" << std::endl << std::endl;
	std::cout << "  -h, --help                         Show this help" << std::endl << std::endl;

	std::cout << "Include the generated file in the rootmenu section of your ~/.jwmrc" << std::endl;
	std::cout << "More information at http://github.com/chiku/mjwm" << std::endl;
}

void
amm::messages::display_version()
{
	std::cout << "mjwm " << AMM_VERSION << std::endl;
}

void
amm::messages::display_option_error()
{
	std::cerr << "Please run mjwm -h to see options" << std::endl;
}
