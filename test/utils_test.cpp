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
#include <string>
#include <vector>

#include "QUnit.hpp"

#include "utils.h"

namespace amm
{
  class utils_test
  {
    QUnit::UnitTest qunit;

    void test_stringx_ends_with_a_given_string_if_it_is_present_in_the_end()
    {
      QUNIT_IS_TRUE(amm::stringx("vlc.desktop").ends_with(".desktop"));
      QUNIT_IS_TRUE(amm::stringx(".desktop").ends_with(".desktop"));
    }

    void test_stringx_doesnt_end_with_a_string_if_it_is_not_present_in_the_end()
    {
      QUNIT_IS_FALSE(amm::stringx("vlc.desktopfile").ends_with(".desktop"));
      QUNIT_IS_FALSE(amm::stringx("desktop").ends_with(".desktop"));
    }

    void test_stringx_terminate_with_adds_missing_ending_string()
    {
      QUNIT_IS_EQUAL("AudioVideo;GTK;", amm::stringx("AudioVideo;GTK").terminate_with(";"));
    }

    void test_stringx_terminate_with_doesnt_duplicate_existing_ending_string()
    {
      QUNIT_IS_EQUAL("AudioVideo;", amm::stringx("AudioVideo").terminate_with(";"));
    }

    void test_stringx_terminate_with_handles_cases_when_string_length_is_lesser_than_end_length()
    {
      QUNIT_IS_EQUAL(";", amm::stringx("").terminate_with(";"));
    }

    void test_stringx_encode_XML_escapes_characters()
    {
      QUNIT_IS_EQUAL("Icon=&lt;&apos;foo&apos; &amp; &quot;bar&quot;&gt;", amm::stringx("Icon=<\'foo\' & \"bar\">").encode());
    }

    void test_stringx_trim_removes_whitespaces_from_begenning_and_end()
    {
      QUNIT_IS_EQUAL("accessories-text-editor", amm::stringx(" \taccessories-text-editor \t\n").trim());
    }

    void test_stringx_split_divides_a_string_with_a_given_delimiter()
    {
      std::vector<std::string> result = amm::stringx("AudioVideo;Video;Player;").split(";");
      QUNIT_IS_EQUAL(3, result.size());
      QUNIT_IS_EQUAL("AudioVideo", result[0]);
      QUNIT_IS_EQUAL("Video", result[1]);
      QUNIT_IS_EQUAL("Player", result[2]);
    }

    void test_stringx_split_doesnt_leave_out_last_element_if_final_delimeter_is_missing()
    {
      std::vector<std::string> result = amm::stringx("AudioVideo;Video;Player").split(";");
      QUNIT_IS_EQUAL(3, result.size());
      QUNIT_IS_EQUAL("AudioVideo", result[0]);
      QUNIT_IS_EQUAL("Video", result[1]);
      QUNIT_IS_EQUAL("Player", result[2]);
    }


    void test_vectorx_joins_into_a_string_with_a_delimiter()
    {
      std::vector<std::string> vector;
      vector.push_back("foo");
      vector.push_back("bar");
      vector.push_back("baz");
      QUNIT_IS_EQUAL("foo; bar; baz", amm::vectorx(vector).join("; "));
    }

    void test_vectorx_joins_into_vector_with_one_entry()
    {
      std::vector<std::string> vector;
      vector.push_back("foo");
      QUNIT_IS_EQUAL("foo", amm::vectorx(vector).join("; "));
    }

    void test_vectorx_joins_into_vector_with_no_entries()
    {
      std::vector<std::string> vector;
      QUNIT_IS_EQUAL("", amm::vectorx(vector).join("; "));
    }

    void test_vectorx_terminated_with_an_end_is_applied_to_all_elements()
    {
      std::vector<std::string> vector;
      vector.push_back("foo/");
      vector.push_back("bar");
      vector.push_back("baz/");

      std::vector<std::string> terminated_vector = amm::vectorx(vector).terminate_with("/");
      QUNIT_IS_EQUAL(3, terminated_vector.size());
      QUNIT_IS_EQUAL("foo/", terminated_vector[0]);
      QUNIT_IS_EQUAL("bar/", terminated_vector[1]);
      QUNIT_IS_EQUAL("baz/", terminated_vector[2]);
    }

    void test_vectorx_unique_removes_duplicates()
    {
      std::vector<std::string> vector;
      vector.push_back("foo");
      vector.push_back("bar");
      vector.push_back("foo");
      vector.push_back("bar");
      vector.push_back("bar");

      std::vector<std::string> unique_vector = amm::vectorx(vector).unique();
      QUNIT_IS_EQUAL(2, unique_vector.size());
      QUNIT_IS_EQUAL("bar", unique_vector[0]);
      QUNIT_IS_EQUAL("foo", unique_vector[1]);
    }

  public:
    utils_test(std::ostream &out, int verbose_level) : qunit(out, verbose_level) {}

    int run()
    {
      test_stringx_ends_with_a_given_string_if_it_is_present_in_the_end();
      test_stringx_doesnt_end_with_a_string_if_it_is_not_present_in_the_end();
      test_stringx_terminate_with_adds_missing_ending_string();
      test_stringx_terminate_with_doesnt_duplicate_existing_ending_string();
      test_stringx_terminate_with_handles_cases_when_string_length_is_lesser_than_end_length();
      test_stringx_encode_XML_escapes_characters();
      test_stringx_trim_removes_whitespaces_from_begenning_and_end();
      test_stringx_split_divides_a_string_with_a_given_delimiter();
      test_stringx_split_doesnt_leave_out_last_element_if_final_delimeter_is_missing();

      test_vectorx_joins_into_a_string_with_a_delimiter();
      test_vectorx_joins_into_vector_with_one_entry();
      test_vectorx_joins_into_vector_with_no_entries();
      test_vectorx_terminated_with_an_end_is_applied_to_all_elements();
      test_vectorx_unique_removes_duplicates();
      return qunit.errors();
    }
  };
}


int main()
{
  return amm::utils_test(std::cerr, QUnit::normal).run();
}
