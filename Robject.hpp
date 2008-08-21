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

#ifndef ROBJECT_HPP
#define ROBJECT_HPP

#include <Rinternals.h>
#include <R.backend.hpp>

namespace RAbstraction {

  template<SEXPTYPE RTYPE>
  class RObject {
  public:
    typedef typename Rtype<RTYPE>::ValueType ValueType;
    Rbackend<RTYPE>* handle_;
    ~RObject();
    RObject();
    RObject(const R_len_t len);
    RObject(const SEXP x);

    void setAttribute(const SEXP attrubuteSymbol, const SEXP attributeValue);
    void setAttribute(const char* attrubuteName, const SEXP attributeValue);
    const SEXP fetchAttribute(const char* attrubuteName);
    const SEXP fetchAttribute(const SEXP attrubuteSymbol);

    const R_len_t length();
    const SEXP getSEXP();
  };

  template<SEXPTYPE RTYPE>
  RObject<RTYPE>::~RObject() {
    handle_->detach();
  }

  template<SEXPTYPE RTYPE>
  RObject<RTYPE>::RObject() {
    handle_ = Rbackend<RTYPE>::init();
  }

  template<SEXPTYPE RTYPE>
  RObject<RTYPE>::RObject(const R_len_t len) {
    handle_ = Rbackend<RTYPE>::init(len);
  }

  template<SEXPTYPE RTYPE>
  RObject<RTYPE>::RObject(const SEXP x) {
    handle_ = Rbackend<RTYPE>::init(x);
  }

  template<SEXPTYPE RTYPE>
  void RObject<RTYPE>::setAttribute(const char* attrubuteName, const SEXP attributeValue) {
    if(getSEXP()==R_NilValue) {
      Rprintf("could not set attribute on NULL object.\n");
      return;
    }
    setAttrib(getSEXP(),install(attrubuteName),attributeValue);
  }

  template<SEXPTYPE RTYPE>
  void RObject<RTYPE>::setAttribute(const SEXP attrubuteSymbol, const SEXP attributeValue) {
    if(getSEXP()==R_NilValue) {
      Rprintf("could not set attribute on NULL object.\n");
      return;
    }
    setAttrib(getSEXP(),attrubuteSymbol,attributeValue);
  }


  template<SEXPTYPE RTYPE>
  const SEXP RObject<RTYPE>::fetchAttribute(const char* attrubuteName) {
    if(getSEXP()==R_NilValue) {
      Rprintf("could not fetch attribute on uninitialized R_Object.\n");
      return;
    }
    return getAttrib(getSEXP(),install(attrubuteName));
  }

  template<SEXPTYPE RTYPE>
  const SEXP RObject<RTYPE>::fetchAttribute(const SEXP attrubuteSymbol) {
    if(getSEXP()==R_NilValue) {
      Rprintf("could not fetch attribute on uninitialized R_Object.\n");
      return;
    }
    return getAttrib(getSEXP(), attrubuteSymbol);
  }

  template<SEXPTYPE RTYPE>
  const SEXP RObject<RTYPE>::getSEXP() {
    return handle_->getRObject();
  }
} // namespace RAbstraction

#endif //ROBJECT_HPP
