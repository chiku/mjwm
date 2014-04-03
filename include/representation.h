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

#ifndef AMM_REPRESENTATION_H_
#define AMM_REPRESENTATION_H_

#include <string>

#include "transformer.h"

namespace amm {
namespace representation {
class base {
public:
  virtual std::string name() = 0;
  virtual std::string visit(TransformerInterface &transformer) = 0;
  virtual ~base();
};

class menu_start : public base {
 public:
  virtual std::string name();
  virtual std::string visit(TransformerInterface &transformer);
  virtual ~menu_start();
};

class menu_end : public base {
 public:
  virtual std::string name();
  virtual std::string visit(TransformerInterface &transformer);
  virtual ~menu_end();
};


class subcategory_start : public base {
 public:
  subcategory_start(std::string name, std::string icon);
  virtual std::string name();
  virtual std::string icon();
  virtual std::string visit(TransformerInterface &transformer);
  virtual ~subcategory_start();
 private:
  std::string name_;
  std::string icon_;
};

class subcategory_end : public base {
 public:
  subcategory_end(std::string name);
  virtual std::string name();
  virtual std::string visit(TransformerInterface &transformer);
  virtual ~subcategory_end();
 private:
  std::string name_;
};


class menu_entry : public base {
 public:
  menu_entry(std::string name, std::string icon, std::string executable);
  virtual std::string name();
  virtual std::string icon();
  virtual std::string executable();
  virtual std::string visit(TransformerInterface &transformer);
  virtual ~menu_entry();
 private:
  std::string name_;
  std::string icon_;
  std::string executable_;
};
} // namespace representation
} // namespace amm

#endif // AMM_REPRESENTATION_H_
