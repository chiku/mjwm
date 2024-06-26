/*
  This file is part of mjwm.
  Copyright (C) 2014-2024  Chirantan Mitra <chirantan.mitra@gmail.com>

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

#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

#include "amm.h"
#include "vectorx.h"
#include "filex.h"
#include "timex.h"
#include "messages.h"
#include "amm_options.h"
#include "system_environment.h"
#include "command_line_options_parser.h"
#include "representation/representation_interface.h"
#include "icon_search/icon_search_interface.h"
#include "icon_search/xdg_search.h"
#include "icon_search/caching_search.h"
#include "qualified_icon_theme.h"
#include "desktop_entry_file_search.h"
#include "stats.h"
#include "menu.h"
#include "transformer/jwm.h"

namespace amm {

static inline void displayToSTDOUT(std::string message)
{
    std::cout << message << std::endl;
}

static inline void displayToSTDERR(std::string message)
{
    std::cerr << message << std::endl;
}

Amm::Amm()
{
    actual_searcher_ = NULL;
}

Amm::~Amm()
{
    if (actual_searcher_ != NULL) {
        delete actual_searcher_;
        actual_searcher_ = NULL;
    }
}

void Amm::validateEnvironment() const
{
    if (!environment_.isValid()) {
        displayToSTDERR(messages::homeNotSet());
        exit(2);
    }
}

void Amm::loadCommandLineOption(int argc, char **argv)
{
    options_ = CommandLineOptionsParser(environment_.home(), environment_.language()).parse(argc, argv);
    std::vector<std::string> deprecations = options_.deprecations;
    if (!deprecations.empty()) {
        displayToSTDERR(vectorx::join(deprecations, "\n"));
    }
    if (!options_.is_parsed) {
        displayToSTDERR(messages::optionError());
        exit(2);
    }
    if (options_.is_help) {
        displayToSTDOUT(messages::help());
        exit(0);
    }
    if (options_.is_version) {
        displayToSTDOUT(messages::version());
        exit(0);
    }
}

void Amm::readCategories()
{
    std::string category_file_name = options_.category_file_name;
    std::vector<std::string> category_lines;

    if (category_file_name != "") {
        if (filex::readLines(category_file_name, &category_lines)) {
            menu_.loadCustomCategories(category_lines);
        } else {
            displayToSTDERR(messages::badCategoryFile(category_file_name));
            exit(1);
        }
    }
}

void Amm::registerIconService()
{
    if (options_.is_iconize) {
        QualifiedIconTheme theme(environment_, options_.icon_theme_name);
        actual_searcher_ = new icon_search::XdgSearch(48, theme);
        icon_search::IconSearchInterface *icon_searcher = new icon_search::CachingSearch(*actual_searcher_);
        menu_.registerIconService(*icon_searcher);
    }
}

void Amm::readDesktopEntryFiles()
{
    std::vector<std::string> input_directory_names = options_.input_directory_names;

    DesktopEntryFileSearch service;
    if (options_.override_default_directories) {
        service.registerDirectories(input_directory_names);
    } else {
        service.registerDefaultDirectories();
    }
    service.resolve();

    std::vector<std::string> bad_paths = service.badPaths();
    if (!bad_paths.empty()) {
        displayToSTDERR(messages::badInputPaths(vectorx::join(bad_paths, ", ")));
    }
    desktop_entry_file_names_ = service.desktopEntryFileNames();
}

void Amm::populate()
{
    menu_.registerLanguage(options_.language);
    menu_.populate(desktop_entry_file_names_);
    if (menu_.summary().totalParsedFiles() == 0) {
        displayToSTDERR(messages::noValidDesktopEntryFiles());
        exit(1);
    }
    menu_.sort();
}

void Amm::writeOutputFile()
{
    transformer::Jwm jwm_transformer;
    std::vector<representation::RepresentationInterface*> representations = menu_.representations();
    std::vector<std::string> output;

    output.push_back(messages::autogeneratedByAmm());

    for (std::vector<representation::RepresentationInterface*>::const_iterator representation = representations.begin(); representation != representations.end(); ++representation) {
        output.push_back((*representation)->visit(jwm_transformer));
        delete *representation;
    }

    std::string output_file_name = options_.output_file_name;
    if (filex::existsAsDirectory(output_file_name)) {
        displayToSTDERR(messages::outputPathBlockedByDirectory(output_file_name));
        exit(1);
    }
    if (filex::exists(output_file_name)) {
        if (options_.is_backup) {
            std::string backup_file_name = output_file_name + "." + timex::currentTimeAsTimestamp() + ".bak";
            filex::moveTo(output_file_name, backup_file_name);
            displayToSTDOUT(messages::backupFile(output_file_name, backup_file_name));
        } else {
            filex::purge(output_file_name);
        }
    }
    if (!filex::writeLines(output_file_name, output)) {
        displayToSTDERR(messages::badOutputFile(options_.output_file_name));
        exit(1);
    }
}

void Amm::printSummary() const
{
    displayToSTDOUT(menu_.summary().details(options_.summary_type, options_.output_file_name)); // extra line
}

} // namespace amm
