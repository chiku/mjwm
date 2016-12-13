/*
  This file is part of mjwm.
  Copyright (C) 2014-2016  Chirantan Mitra <chirantan.mitra@gmail.com>

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

#define DO_QUOTE(X)       #X
#define QUOTE(X)          DO_QUOTE(X)

#include "filex.h"

#include <cstdlib>
#include <cstdio>
#include <string>
#include <vector>

#include "doctest.h"

namespace amm {

SCENARIO("FileX") {
    std::string fixture_dir = QUOTE(FIXTUREDIR);

    GIVEN("A filex") {
        WHEN("pointing to a file that exists") {
            FileX filex(fixture_dir + "applications/vlc.desktop");

            THEN("it exists") {
                CHECK(filex.exists());
            }

            THEN("it isn't a directory") {
                CHECK_FALSE(filex.existsAsDirectory());
            }

            THEN("it succeeds in reading its contents") {
                std::vector<std::string> lines;
                CHECK(filex.readLines(&lines));
            }

            THEN("it reads the content of the file") {
                std::vector<std::string> lines;
                filex.readLines(&lines);
                REQUIRE(lines.size() == 11);
                CHECK(lines[0] == "[Desktop Entry]");
                CHECK(lines[1] == "Version=1.0");
                CHECK(lines[2] == "Name=VLC media player");
                CHECK(lines[3] == "GenericName=Media player");
                CHECK(lines[4] == "Comment=Read, capture, broadcast your multimedia streams");
                CHECK(lines[5] == "Exec=/usr/bin/vlc --started-from-file %U");
                CHECK(lines[6] == "TryExec=/usr/bin/vlc");
                CHECK(lines[7] == "Icon=vlc");
                CHECK(lines[8] == "Terminal=false");
                CHECK(lines[9] == "Type=Application");
                CHECK(lines[10] == "Categories=AudioVideo;Player;Recorder;");
            }

            THEN("it over-writes the older content") {
                std::vector<std::string> lines;
                filex.readLines(&lines);
                filex.readLines(&lines);
                CHECK(lines.size() == 11);
            }

            THEN("it doesn't write lines to the file") {
                std::vector<std::string> lines;
                lines.push_back("first");
                lines.push_back("second");
                CHECK_FALSE(filex.writeLines(lines));
            }

            THEN("it can move the file to an existing directory") {
                std::string file_name = fixture_dir + "new-file";
                std::string renamed_file_name = fixture_dir + "renamed-file";

                remove(file_name.c_str());
                remove(renamed_file_name.c_str());

                std::vector<std::string> lines;
                lines.push_back("first");
                lines.push_back("second");
                CHECK(FileX(file_name).writeLines(lines));

                CHECK(FileX(file_name).moveTo(renamed_file_name));

                CHECK_FALSE(FileX(file_name).exists());

                std::vector<std::string> read_lines;
                CHECK(FileX(renamed_file_name).readLines(&read_lines));
                REQUIRE(read_lines.size() == 2);
                CHECK(read_lines[0] == "first");
                CHECK(read_lines[1] == "second");

                remove(file_name.c_str());
                remove(renamed_file_name.c_str());
            }

            THEN("it can't move the file to a non-existing directory") {
                std::string file_name = fixture_dir + "new-file";
                std::string renamed_file_name = "test/does-not-exist-fixtures/renamed-file";

                remove(file_name.c_str());
                remove(renamed_file_name.c_str());

                std::vector<std::string> lines;
                lines.push_back("first");
                lines.push_back("second");
                CHECK(FileX(file_name).writeLines(lines));

                CHECK_FALSE(FileX(file_name).moveTo(renamed_file_name));

                CHECK(FileX(file_name).exists());
                CHECK_FALSE(FileX(renamed_file_name).exists());

                remove(file_name.c_str());
                remove(renamed_file_name.c_str());
            }

            THEN("it can delete the file") {
                std::string file_name = fixture_dir + "new-file";

                remove(file_name.c_str());

                std::vector<std::string> lines;
                lines.push_back("first");
                lines.push_back("second");
                CHECK(FileX(file_name).writeLines(lines));

                CHECK(FileX(file_name).purge());

                CHECK_FALSE(FileX(file_name).exists());

                remove(file_name.c_str());
            }
        }

        WHEN("pointing to a directory that exists") {
            FileX dirx(fixture_dir + "applications");

            THEN("it exists") {
                CHECK(dirx.exists());
            }

            THEN("it is a directory") {
                CHECK(dirx.existsAsDirectory());
            }
        }

        WHEN("pointing to a file that doesn't exist") {
            std::string file_name = fixture_dir + "applications/does-not-exist.desktop";
            FileX filex(file_name);
            remove(file_name.c_str());
            remove((file_name + ".backup_extension").c_str());

            THEN("it doesn't exist") {
                CHECK_FALSE(filex.exists());
            }

            THEN("it isn't a directory") {
                CHECK_FALSE(filex.existsAsDirectory());
            }

            THEN("it fails to read its contents") {
                std::vector<std::string> lines;
                CHECK_FALSE(filex.readLines(&lines));
            }

            THEN("its lines are empty") {
                std::vector<std::string> lines;
                filex.readLines(&lines);
                CHECK(lines.empty());
            }

            THEN("it doesn't over-write the older contents") {
                std::vector<std::string> lines;
                lines.push_back("existing line");
                filex.readLines(&lines);
                REQUIRE(lines.size() == 1);
                CHECK(lines[0] == "existing line");
            }

            THEN("it writes lines to the file") {
                std::vector<std::string> lines;
                lines.push_back("first");
                lines.push_back("second");
                CHECK(filex.writeLines(lines));

                FileX read_file(file_name);
                std::vector<std::string> read_lines;
                CHECK(read_file.readLines(&read_lines));
                REQUIRE(read_lines.size() == 2);
                CHECK(read_lines[0] == "first");
                CHECK(read_lines[1] == "second");
                remove(file_name.c_str());
            }

            THEN("it can't delete the file") {
                std::string file_name = fixture_dir + "new-file";
                remove(file_name.c_str());

                CHECK_FALSE(FileX(file_name).purge());

                CHECK_FALSE(FileX(file_name).exists());
                remove(file_name.c_str());
            }
        }
    }
}

} // namespace amm
