/*
  This file is part of mjwm.
  Copyright (C) 2014-2022  Chirantan Mitra <chirantan.mitra@gmail.com>

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

#include "messages.h"

#include <string>
#include <sstream>

#include "../config.h"
#include "timex.h"

namespace amm {
namespace messages {

std::string help()
{
    std::stringstream stream;

    stream << PACKAGE_STRING <<  ", Copyright (C) 2014-2016 Chirantan Mitra <chirantan.mitra@gmail.com>" << std::endl;
    stream << PACKAGE << " comes with ABSOLUTELY NO WARRANTY; for details refer COPYING." << std::endl;
    stream << "This is free software, and you are welcome to redistribute it" << std::endl;
    stream << "under certain conditions; Refer COPYING for details." << std::endl;
    stream << std::endl;

    stream << PACKAGE << " creates JWM's menu from (freedesktop) desktop files" << std::endl;
    stream << std::endl;

    stream << "Optional arguments:" << std::endl;
    stream << "  -c, --category-file=[FILE]  Use an external category file. This overrides the" << std::endl;
    stream << "                                built in categories. Please look at" << std::endl;
    stream << "                                default.mjwm to write your own category files." << std::endl;
    stream << "      --help                  Show this help." << std::endl;
    stream << "      --iconize=[THEME]       Search for icon files by name in $HOME," << std::endl;
    stream << "                                $XDG_DATA_DIRS/icons, and /usr/share/pixmaps." << std::endl;
    stream << "                                Icon file names would be absolute paths to" << std::endl;
    stream << "                                icons in the specified directories. Hicolor" << std::endl;
    stream << "                                icon theme is used if no theme name is given." << std::endl;
    stream << "  -o, --output-file=[FILE]    Outfile file [Default: $HOME/.jwmrc-mjwm]" << std::endl;
    stream << "  -i, --input-directory=[DIRECTORY]" << std::endl;
    stream << "                              Directory to scan for '.desktop' files. Multiple" << std::endl;
    stream << "                                directories, if provided, must be separated by" << std::endl;
    stream << "                                colons. [Default: application directories" << std::endl;
    stream << "                                under $XDG_DATA_HOME & $XDG_DATA_DIRS]" << std::endl;
    stream << "      --language=[NAME]       The language for which the menu would be build." << std::endl;
    stream << "                                Defaults to the system default." << std::endl;
    stream << "      --no-backup             Do not create any backup files." << std::endl;
    stream << "  -v  --verbose               Verbose output." << std::endl;
    stream << "      --version               Show version information." << std::endl;
    stream << std::endl;
    stream << "Deprecated options. (Would be removed a in future release)" << std::endl;
    stream << "      --summary=[TYPE]        The summary of the run. Acceptable values are" << std::endl;
    stream << "                                normal and long. Defaults to normal." << std::endl;
    stream << std::endl;

    stream << "Include the generated file in the rootmenu section of your ~/.jwmrc" << std::endl;
    stream << "More information at http://github.com/chiku/mjwm";

    return stream.str();
}

std::string version()
{
    return PACKAGE_STRING;
}

std::string homeNotSet()
{
    return "$HOME is not set. Please set $HOME to a proper value and rerun.";
}

std::string optionError()
{
    std::stringstream stream;
    stream << "Please run "<< PACKAGE << " --help to see options";
    return stream.str();
}

std::string badSummaryType(const std::string &actual)
{
    std::stringstream stream;
    stream << actual << " is not a valid summary type" << std::endl << optionError();
    return stream.str();
}

std::string badInputPaths(const std::string &bad_paths)
{
    std::stringstream stream;
    stream << "These paths couldn't be opened: " << bad_paths;
    return stream.str();
}

std::string autogeneratedByAmm()
{
    std::stringstream stream;
    stream << "<!-- Autogenerated by " << PACKAGE_STRING << " (" << timex::currentTimeAsReadble() << ") -->";
    return stream.str();
}

std::string noValidDesktopEntryFiles()
{
    return "No valid desktop files were found in any search directories.";
}

std::string badCategoryFile(const std::string &file_name)
{
    std::stringstream stream;
    stream << "Couldn't open category file: " << file_name;
    return stream.str();
}

std::string outputPathBlockedByDirectory(const std::string &file_name)
{
    std::stringstream stream;
    stream << "A directory with the same name as the output file exists: " << file_name;
    return stream.str();
}

std::string badOutputFile(const std::string &file_name)
{
    std::stringstream stream;
    stream << "Couldn't open output file: " << file_name;
    return stream.str();
}

std::string backupFile(const std::string &file_name, const std::string &backup_file_name)
{
    std::stringstream stream;
    stream << "Backed " << file_name << " to " << backup_file_name;
    return stream.str();
}

} // namespace messages
} // namespace amm
