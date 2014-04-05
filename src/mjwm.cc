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
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>

#include "vectorx.h"
#include "messages.h"
#include "command_line_options.h"
#include "icon_service.h"
#include "file_search_service.h"
#include "representation.h"
#include "stats.h"
#include "menu.h"
#include "transformer/jwm.h"

namespace amm {

class Main {
 public:
  void LoadCommandLineOption(int argc, char **argv);
  void RegisterIconService();
  void ReadCategories();
  void ReadDesktopFiles();
  void Populate();
  void WriteOutputFile();
  void PrintSummary();

 private:
  CommandLineOptions command_line_options_;
  Menu menu_;
  std::vector<std::string> desktop_file_names_;
};

void Main::LoadCommandLineOption(int argc, char **argv) {
  command_line_options_ = CommandLineOptions();
  if (!command_line_options_.Parse(argc, argv)) {
    std::cerr << messages::OptionError();
    exit(2);
  }
  std::vector<std::string> deprecations = command_line_options_.Deprecations();
  if (deprecations.size() > 0) {
    std::cerr << VectorX(deprecations).Join("\n") << std::endl << "Proceeding..." << std::endl;
  }
  if (command_line_options_.IsHelp()) {
    std::cout << messages::Help();
    exit(0);
  }
  if (command_line_options_.IsVersion()) {
    std::cout << messages::Version();
    exit(0);
  }
}

void Main::ReadCategories() {
  std::string category_file_name = command_line_options_.CategoryFileName();
  std::vector<std::string> category_lines;

  if (category_file_name != "") {
    std::ifstream category_file(category_file_name.c_str());
    if (category_file.good()) {
      std::string line;
      while (std::getline(category_file, line)) {
        category_lines.push_back(line);
      }
      menu_.LoadCustomCategories(category_lines);
      category_file.close();
    } else {
      std::cerr << messages::BadCategoryFile(category_file_name) << std::endl;
      exit(1);
    }
  }
}

void Main::RegisterIconService() {
  IconService icon_service;
  icon_service.RegisterExtension(command_line_options_.IconExtension());
  menu_.RegisterIconService(icon_service);
}

void Main::ReadDesktopFiles() {
  std::vector<std::string> input_directory_names = command_line_options_.InputDirectoryNames();

  FileSearchService service;
  service.RegisterDirectoriesWithFallback(input_directory_names);
  service.Resolve();

  std::vector<std::string> bad_paths = service.BadPaths();
  if (bad_paths.size() > 0) {
    std::cerr << "These paths couldn't be opened: " << VectorX(bad_paths).Join(", ");
    std::cerr << std::endl << "Proceeding..." << std::endl;
  }
  desktop_file_names_ = service.DesktopFileNames();
}

void Main::Populate() {
  menu_.Populate(desktop_file_names_);
  if (menu_.Summary().TotalParsedFiles() == 0) {
    std::cerr << messages::NoValidDesktopFiles() << std::endl;
    exit(1);
  }
  menu_.Sort();
}

void Main::WriteOutputFile() {
  std::string output_file_name = command_line_options_.OutputFileName();
  std::ofstream output_file(output_file_name.c_str());
  if (!output_file.good()) {
    std::cerr << messages::BadOutputFile(output_file_name) << std::endl;
    exit(1);
  }

  transformer::Jwm jwm_transformer;
  std::vector<RepresentationInterface*> representations = menu_.Representations();

  output_file << messages::AutogeneratedByAmm();

  for (std::vector<RepresentationInterface*>::const_iterator representation = representations.begin(); representation != representations.end(); ++representation) {
    output_file << (*representation)->visit(jwm_transformer) << std::endl;
  }

  for (std::vector<RepresentationInterface*>::iterator representation = representations.begin(); representation != representations.end(); ++representation) {
    delete *representation;
  }

  output_file.close();
}

void Main::PrintSummary() {
  std::cout << menu_.Summary().NormalSummary();
}

} // namespace amm


int main(int argc, char *argv[]) {
  amm::Main operation;
  operation.LoadCommandLineOption(argc, argv);
  operation.RegisterIconService();
  operation.ReadCategories();
  operation.ReadDesktopFiles();
  operation.Populate();
  operation.WriteOutputFile();
  operation.PrintSummary();
}
