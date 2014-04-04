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

// TODO : rename base to interface
// TODO : inline this implementation file
amm::representation::base::~base() {}

std::string
amm::representation::MenuStart::name()
{
  return "Menu start";
}
std::string
amm::representation::MenuStart::visit(amm::TransformerInterface &transformer)
{
  return transformer.Transform(this);
}
amm::representation::MenuStart::~MenuStart() {}


std::string
amm::representation::MenuEnd::name()
{
  return "Menu end";
}
std::string
amm::representation::MenuEnd::visit(amm::TransformerInterface &transformer)
{
  return transformer.Transform(this);
}
amm::representation::MenuEnd::~MenuEnd() {}


amm::representation::SubcategoryStart::SubcategoryStart(std::string name, std::string icon)
{
  name_ = name;
  icon_ = icon;
}
std::string
amm::representation::SubcategoryStart::name()
{
  return name_;
}
std::string
amm::representation::SubcategoryStart::icon()
{
  return icon_;
}
std::string
amm::representation::SubcategoryStart::visit(amm::TransformerInterface &transformer)
{
  return transformer.Transform(this);
}
amm::representation::SubcategoryStart::~SubcategoryStart() {}


amm::representation::SubcategoryEnd::SubcategoryEnd(std::string name)
{
  name_ = name;
}

std::string
amm::representation::SubcategoryEnd::name()
{
  return name_ + " end";
}
std::string
amm::representation::SubcategoryEnd::visit(amm::TransformerInterface &transformer)
{
  return transformer.Transform(this);
}
amm::representation::SubcategoryEnd::~SubcategoryEnd() {}


amm::representation::Program::Program(std::string name, std::string icon, std::string executable)
{
  name_ = name;
  icon_ = icon;
  executable_ = executable;
}
std::string
amm::representation::Program::name()
{
  return name_;
}
std::string
amm::representation::Program::icon()
{
  return icon_;
}
std::string
amm::representation::Program::executable()
{
  return executable_;
}
std::string
amm::representation::Program::visit(amm::TransformerInterface &transformer)
{
  return transformer.Transform(this);
}
amm::representation::Program::~Program() {}
