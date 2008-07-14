///////////////////////////////////////////////////////////////////////////
// Copyright (C) 2008  Whit Armstrong                                    //
//                                                                       //
// This program is free software: you can redistribute it and/or modify  //
// it under the terms of the GNU General Public License as published by  //
// the Free Software Foundation, either version 3 of the License, or     //
// (at your option) any later version.                                   //
//                                                                       //
// This program is distributed in the hope that it will be useful,       //
// but WITHOUT ANY WARRANTY; without even the implied warranty of        //
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         //
// GNU General Public License for more details.                          //
//                                                                       //
// You should have received a copy of the GNU General Public License     //
// along with this program.  If not, see <http://www.gnu.org/licenses/>. //
///////////////////////////////////////////////////////////////////////////

#ifndef RTYPE_HPP
#define RTYPE_HPP

#include <string>
#include <Rinternals.h>

using std::string;

template<SEXPTYPE T>
class Rtype;

template<>
class Rtype<REALSXP> {
public:
  typedef double ValueType;
  static double scalar(SEXP x) {
    return REAL(x)[0];
  }
};

template<>
class Rtype<INTSXP> {
public:
  typedef int ValueType;
  static int scalar(SEXP x) {
    return INTEGER(x)[0];
  }
};

template<>
class Rtype<LGLSXP> {
public:
  typedef int ValueType;
  static int scalar(SEXP x) {
    return INTEGER(x)[0];
  }
};

template<>
class Rtype<STRSXP> {
public:
  typedef string ValueType;
  static string scalar(SEXP x) {
    string ans(CHAR(STRING_ELT(x, 0)));
    return ans;
  }
};



#endif // RTYPE_HPP
