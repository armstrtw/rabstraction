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

#ifndef RVECTOR_HPP
#define RVECTOR_HPP

#include <Rinternals.h>


template<SEXPTYPE T>
class RVector;

template<>
class RVector<REALSXP> {
public:
  typedef double ValueType;
  static ValueType scalar(SEXP x) {
    return REAL(x)[0];
  }
};

template<>
class RVector<INTSXP> {
public:
  typedef int ValueType;
  static ValueType scalar(SEXP x) {
    return INTEGER(x)[0];
  }
};

template<>
class RVector<LGLSXP> {
public:
  typedef int ValueType;
  static ValueType scalar(SEXP x) {
    return INTEGER(x)[0];
  }
};



#endif // RVECTOR_HPP
