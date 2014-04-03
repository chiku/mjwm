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

#include <string>

#include "representation.h"

amm::representation::base::~base() {}

std::string
amm::representation::menu_start::name()
{
  return "Menu start";
}
std::string
amm::representation::menu_start::visit(amm::TransformerInterface &transformer)
{
  return transformer.transform(this);
}
amm::representation::menu_start::~menu_start() {}


std::string
amm::representation::menu_end::name()
{
  return "Menu end";
}
std::string
amm::representation::menu_end::visit(amm::TransformerInterface &transformer)
{
  return transformer.transform(this);
}
amm::representation::menu_end::~menu_end() {}


amm::representation::subcategory_start::subcategory_start(std::string name, std::string icon)
{
  name_ = name;
  icon_ = icon;
}
std::string
amm::representation::subcategory_start::name()
{
  return name_;
}
std::string
amm::representation::subcategory_start::icon()
{
  return icon_;
}
std::string
amm::representation::subcategory_start::visit(amm::TransformerInterface &transformer)
{
  return transformer.transform(this);
}
amm::representation::subcategory_start::~subcategory_start() {}


amm::representation::subcategory_end::subcategory_end(std::string name)
{
  name_ = name;
}

std::string
amm::representation::subcategory_end::name()
{
  return name_ + " end";
}
std::string
amm::representation::subcategory_end::visit(amm::TransformerInterface &transformer)
{
  return transformer.transform(this);
}
amm::representation::subcategory_end::~subcategory_end() {}


amm::representation::menu_entry::menu_entry(std::string name, std::string icon, std::string executable)
{
  name_ = name;
  icon_ = icon;
  executable_ = executable;
}
std::string
amm::representation::menu_entry::name()
{
  return name_;
}
std::string
amm::representation::menu_entry::icon()
{
  return icon_;
}
std::string
amm::representation::menu_entry::executable()
{
  return executable_;
}
std::string
amm::representation::menu_entry::visit(amm::TransformerInterface &transformer)
{
  return transformer.transform(this);
}
amm::representation::menu_entry::~menu_entry() {}
