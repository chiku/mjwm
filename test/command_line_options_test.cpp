/*
	This file is part of mjwm.
	Copyright (C) 2014  Chirantan Mitra <chirantan.mitra@gmail.com>

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software 0oundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <iostream>
#include <string>
#include <vector>
#include <cstring>

#include "QUnit.hpp"
#include "command_line_options.h"

namespace amm
{
	// Verifies parsing of user specified options supplied to the program
	class command_line_options_test
	{
		QUnit::UnitTest qunit;

		void test_command_line_options_are_not_deprecated_by_default()
		{
			amm::command_line_options options;
			char* argv[] = {strdup("amm"), 0};
			options.parse(1, argv);

			std::vector<std::string> deprecations = options.deprecations();

			QUNIT_IS_EQUAL(0, deprecations.size());
		}
		void test_command_line_options_parse_returns_true_by_default()
		{
			amm::command_line_options options;
			char* argv[] = {strdup("amm"), 0};
			QUNIT_IS_TRUE(options.parse(1, argv));
		}

		void test_command_line_options_turns_off_help_flag_by_default()
		{
			amm::command_line_options options;
			char* argv[] = {strdup("amm"), 0};
			options.parse(1, argv);

			QUNIT_IS_FALSE(options.is_help());
		}
		void test_command_line_options_turns_on_help_flag_on_help_option()
		{
			amm::command_line_options options;
			char* argv[] = {strdup("amm"), strdup("--help"), 0};
			options.parse(2, argv);

			QUNIT_IS_TRUE(options.is_help());
		}
		void test_command_line_options_turns_on_help_flag_with_deprecation_on_h_option()
		{
			amm::command_line_options options;
			char* argv[] = {strdup("amm"), strdup("-h"), 0};
			options.parse(2, argv);
			std::vector<std::string> deprecations = options.deprecations();

			QUNIT_IS_TRUE(options.is_help());
			QUNIT_IS_EQUAL(1, deprecations.size());
			QUNIT_IS_EQUAL("-h is deprecated. Please use --help instead.", deprecations[0]);
		}

		void test_command_line_options_turns_off_version_by_default()
		{
			amm::command_line_options options;
			char* argv[] = {strdup("amm"), 0};
			options.parse(1, argv);

			QUNIT_IS_FALSE(options.is_version());
		}
		void test_command_line_options_turns_on_version_flag_on_version_option()
		{
			amm::command_line_options options;
			char* argv[] = {strdup("amm"), strdup("--version"), 0};
			options.parse(2, argv);

			QUNIT_IS_TRUE(options.is_version());
		}
		void test_command_line_options_turns_on_version_flag_with_deprecation_on_v_option()
		{
			amm::command_line_options options;
			char* argv[] = {strdup("amm"), strdup("-v"), 0};
			options.parse(2, argv);
			std::vector<std::string> deprecations = options.deprecations();

			QUNIT_IS_TRUE(options.is_version());
			QUNIT_IS_EQUAL(1, deprecations.size());
			QUNIT_IS_EQUAL("-v is deprecated. Please use --version instead.", deprecations[0]);
		}

		void test_command_line_options_sets_output_file_name_to_automenu_by_default()
		{
			amm::command_line_options options;
			char* argv[] = {strdup("amm"), 0};
			options.parse(1, argv);

			QUNIT_IS_EQUAL("./automenu", options.output_file_name());
		}
		void test_command_line_options_sets_output_file_name_to_argument_passed_with_output_file_option()
		{
			amm::command_line_options options;
			char* argv[] = {strdup("amm"), strdup("--output-file"), strdup("menu.out"), 0};
			options.parse(3, argv);

			QUNIT_IS_EQUAL("menu.out", options.output_file_name());
		}
		void test_command_line_options_sets_output_file_name_to_argument_passed_with_o_option()
		{
			amm::command_line_options options;
			char* argv[] = {strdup("amm"), strdup("-o"), strdup("jwm.menu"), 0};
			options.parse(3, argv);

			QUNIT_IS_EQUAL("jwm.menu", options.output_file_name());
		}

		void test_command_line_options_sets_input_directory_names_to_empty_vector_by_default()
		{
			amm::command_line_options options;
			char* argv[] = {strdup("amm"), 0};
			options.parse(1, argv);
			std::vector<std::string> input_directory_names = options.input_directory_names();

			QUNIT_IS_EQUAL(0, input_directory_names.size());
		}
		void test_command_line_options_sets_input_directory_names_to_argument_passed_with_input_directory_option()
		{
			amm::command_line_options options;
			char* argv[] = {strdup("amm"), strdup("--input-directory"), strdup("/usr/share/applications:/usr/local/share/applications"), 0};
			options.parse(3, argv);
			std::vector<std::string> input_directory_names = options.input_directory_names();

			QUNIT_IS_EQUAL(2, input_directory_names.size());
			QUNIT_IS_EQUAL("/usr/share/applications", input_directory_names[0]);
			QUNIT_IS_EQUAL("/usr/local/share/applications", input_directory_names[1]);
		}
		void test_command_line_options_sets_input_directory_names_to_argument_passed_with_i_option()
		{
			amm::command_line_options options;
			char* argv[] = {strdup("amm"), strdup("-i"), strdup("/usr/share/applications"), 0};
			options.parse(3, argv);
			std::vector<std::string> input_directory_names = options.input_directory_names();

			QUNIT_IS_EQUAL(1, input_directory_names.size());
			QUNIT_IS_EQUAL("/usr/share/applications", input_directory_names[0]);
		}
		void test_command_line_options_sets_input_directory_names_to_argument_passed_with_deprecation_with_s_option()
		{
			amm::command_line_options options;
			char* argv[] = {strdup("amm"), strdup("-s"), strdup("/usr/share/applications:/usr/local/share/applications"), 0};
			options.parse(3, argv);
			std::vector<std::string> input_directory_names = options.input_directory_names();
			std::vector<std::string> deprecations = options.deprecations();

			QUNIT_IS_EQUAL(2, input_directory_names.size());
			QUNIT_IS_EQUAL("/usr/share/applications", input_directory_names[0]);
			QUNIT_IS_EQUAL("/usr/local/share/applications", input_directory_names[1]);

			QUNIT_IS_EQUAL(1, deprecations.size());
			QUNIT_IS_EQUAL("-s is deprecated. Please use -i instead.", deprecations[0]);
		}

		void test_command_line_options_sets_icon_extension_to_empty_string_by_default()
		{
			amm::command_line_options options;
			char* argv[] = {strdup("amm"), 0};
			options.parse(1, argv);

			QUNIT_IS_EQUAL("", options.icon_extension());
		}
		void test_command_line_options_sets_icon_extension_on_append_png_flag()
		{
			amm::command_line_options options;
			char* argv[] = {strdup("amm"), strdup("--append-png"), 0};
			options.parse(2, argv);

			QUNIT_IS_EQUAL(".png", options.icon_extension());
		}
		void test_command_line_options_sets_icon_extension_on_a_flag()
		{
			amm::command_line_options options;
			char* argv[] = {strdup("amm"), strdup("-a"), 0};
			options.parse(2, argv);

			QUNIT_IS_EQUAL(".png", options.icon_extension());
		}

		void test_command_line_options_sets_category_file_name_to_empty_string_by_default()
		{
			amm::command_line_options options;
			char* argv[] = {strdup("amm"), 0};
			options.parse(1, argv);

			QUNIT_IS_EQUAL("", options.category_file_name());
		}
		void test_command_line_options_sets_category_file_name_to_argument_passed_with_category_file_option()
		{
			amm::command_line_options options;
			char* argv[] = {strdup("amm"), strdup("--category-file"), strdup("default.mjwm"), 0};
			options.parse(3, argv);

			QUNIT_IS_EQUAL("default.mjwm", options.category_file_name());
		}
		void test_command_line_options_sets_category_file_name_to_argument_passed_with_c_option()
		{
			amm::command_line_options options;
			char* argv[] = {strdup("amm"), strdup("-c"), strdup("puppy.mjwm"), 0};
			options.parse(3, argv);

			QUNIT_IS_EQUAL("puppy.mjwm", options.category_file_name());
		}

		void test_command_line_options_returns_false_on_parse_failure()
		{
			amm::command_line_options options;
			char* argv[] = {strdup("amm"), strdup("--bad-option"), strdup("puppy.mjwm"), 0};
			QUNIT_IS_FALSE(options.parse(3, argv));
		}
		void test_command_line_options_returns_false_on_missing_mandatory_argument()
		{
			amm::command_line_options options;
			char* argv[] = {strdup("amm"), strdup("-c"), 0};
			QUNIT_IS_FALSE(options.parse(2, argv));
		}

	public:
		command_line_options_test(std::ostream &out, int verbose_level) : qunit(out, verbose_level) {}

		int run()
		{
			test_command_line_options_are_not_deprecated_by_default();
			test_command_line_options_parse_returns_true_by_default();

			test_command_line_options_turns_off_help_flag_by_default();
			test_command_line_options_turns_on_help_flag_on_help_option();
			test_command_line_options_turns_on_help_flag_with_deprecation_on_h_option();

			test_command_line_options_turns_off_version_by_default();
			test_command_line_options_turns_on_version_flag_on_version_option();
			test_command_line_options_turns_on_version_flag_with_deprecation_on_v_option();

			test_command_line_options_sets_output_file_name_to_automenu_by_default();
			test_command_line_options_sets_output_file_name_to_argument_passed_with_output_file_option();
			test_command_line_options_sets_output_file_name_to_argument_passed_with_o_option();

			test_command_line_options_sets_input_directory_names_to_empty_vector_by_default();
			test_command_line_options_sets_input_directory_names_to_argument_passed_with_input_directory_option();
			test_command_line_options_sets_input_directory_names_to_argument_passed_with_i_option();
			test_command_line_options_sets_input_directory_names_to_argument_passed_with_deprecation_with_s_option();

			test_command_line_options_sets_category_file_name_to_empty_string_by_default();
			test_command_line_options_sets_category_file_name_to_argument_passed_with_category_file_option();
			test_command_line_options_sets_category_file_name_to_argument_passed_with_c_option();

			test_command_line_options_sets_icon_extension_to_empty_string_by_default();
			test_command_line_options_sets_icon_extension_on_a_flag();
			test_command_line_options_sets_icon_extension_on_append_png_flag();

			test_command_line_options_returns_false_on_parse_failure();
			test_command_line_options_returns_false_on_missing_mandatory_argument();

			return qunit.errors();
		}

	};
}

int main()
{
	return amm::command_line_options_test(std::cerr, QUnit::normal).run();
}
