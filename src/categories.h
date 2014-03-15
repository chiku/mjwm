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

#ifndef __mjwm_categories__
#define __mjwm_categories__

#include <string>
#include <vector>

namespace mjwm
{
	const std::string DELIM = ";";

	const std::string AUDIO_VIDEO = "AudioVideo";
	const std::string DEVELOPMENT = "Development";
	const std::string EDUCATION   = "Education";
	const std::string GAME        = "Game";
	const std::string GRAPHICS    = "Graphics";
	const std::string NETWORK     = "Network";
	const std::string OFFICE      = "Office";
	const std::string SCIENCE     = "Science";
	const std::string SETTINGS    = "Settings";
	const std::string SYSTEM      = "System";
	const std::string UTILITY     = "Utility";

	class categories;

	std::ostream& operator <<(std::ostream& stream, const mjwm::categories& categories);

	class categories
	{
	public:
		std::string _raw;
		std::vector<std::string> _categories;

		bool _audiovideo;
		bool _development;
		bool _education;
		bool _game;
		bool _graphics;
		bool _network;
		bool _office;
		bool _science;
		bool _settings;
		bool _system;
		bool _utility;

		void parse();
		void sort();
		void interpret();

	public:
		categories();
		categories(std::string raw);

		bool is_audiovideo() const;
		bool is_development() const;
		bool is_education() const;
		bool is_game() const;
		bool is_graphics() const;
		bool is_network() const;
		bool is_office() const;
		bool is_science() const;
		bool is_settings() const;
		bool is_system() const;
		bool is_utility() const;

		friend std::ostream& operator << (std::ostream& stream, const mjwm::categories& categories);
	};

}

#endif
