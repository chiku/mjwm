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

#ifndef AMM_COMMAND_LINE_OPTIONS_H_
#define AMM_COMMAND_LINE_OPTIONS_H_

#include <string>
#include <vector>

namespace amm {
// Understands parsing of user specified options supplied to the program
class CommandLineOptions {
 public:
  CommandLineOptions();

  bool Parse(int agrc, char *const *argv);

  bool is_help() const { return is_help_; }
  bool is_version() const { return is_version_; }
  std::string output_file_name() const { return output_file_name_; }
  std::vector<std::string> input_directory_names() const { return input_directory_names_; }
  std::string category_file_name() const { return category_file_name_; }
  std::string icon_extension() const { return icon_extension_; }
  std::vector<std::string> deprecations() const { return deprecations_; }

 private:
  bool is_help_;
  bool is_version_;
  std::string output_file_name_;
  std::vector<std::string> input_directory_names_;
  std::string category_file_name_;
  std::string icon_extension_;
  std::vector<std::string> deprecations_;
};
} // namespace amm

#endif // AMM_COMMAND_LINE_OPTIONS_H_
