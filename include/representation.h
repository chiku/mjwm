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

class RepresentationInterface {
public:
  virtual std::string name() const = 0;
  virtual std::string visit(TransformerInterface &transformer) const = 0;
  virtual ~RepresentationInterface() {}
};

namespace representation {
class MenuStart : public RepresentationInterface {
 public:
  virtual std::string name() const { return "Menu start"; }
  virtual std::string visit(TransformerInterface &transformer) const {
    return transformer.Transform(*this);
  }
  virtual ~MenuStart() {}
};

class MenuEnd : public RepresentationInterface {
 public:
  virtual std::string name() const { return "Menu end"; }
  virtual std::string visit(TransformerInterface &transformer) const {
    return transformer.Transform(*this);
  }
  virtual ~MenuEnd() {}
};


class SubcategoryStart : public RepresentationInterface {
 public:
  SubcategoryStart(std::string name, std::string icon) {
    name_ = name;
    icon_ = icon;
  }
  virtual std::string name() const { return name_; }
  virtual std::string icon() const { return icon_; }
  virtual std::string visit(TransformerInterface &transformer) const {
    return transformer.Transform(*this);
  }
  virtual ~SubcategoryStart() {}
 private:
  std::string name_;
  std::string icon_;
};

class SubcategoryEnd : public RepresentationInterface {
 public:
  SubcategoryEnd(std::string name) {
    name_ = name;
  }
  virtual std::string name() const { return name_ + " end"; }
  virtual std::string visit(TransformerInterface &transformer) const {
    return transformer.Transform(*this);
  }
  virtual ~SubcategoryEnd() {}
 private:
  std::string name_;
};


class Program : public RepresentationInterface {
 public:
  Program(std::string name, std::string icon, std::string executable) {
    name_ = name;
    icon_ = icon;
    executable_ = executable;
  }
  virtual std::string name() const { return name_; }
  virtual std::string icon() const { return icon_; }
  virtual std::string executable() const { return executable_; }
  virtual std::string visit(TransformerInterface &transformer) const {
    return transformer.Transform(*this);
  }
  virtual ~Program() {}
 private:
  std::string name_;
  std::string icon_;
  std::string executable_;
};
} // namespace representation
} // namespace amm

#endif // AMM_REPRESENTATION_H_
