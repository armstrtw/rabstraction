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
    RObject(const RObject& x);

    void setAttribute(const SEXP attrubuteSymbol, const SEXP attributeValue);
    void setAttribute(const char* attrubuteName, const SEXP attributeValue);
    const SEXP getAttribute(const char* attrubuteName);
    const SEXP getAttribute(const SEXP attrubuteSymbol);

    const R_len_t length();

    template<typename T>
    void setClass(T beg, T end);

    void setClass(const char* cls);

    template<typename T>
    void getClass(T cont);

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
  RObject<RTYPE>::RObject(const RObject& x) {
    handle_ = x.handle_;
    handle_->attach();
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
  const SEXP RObject<RTYPE>::getAttribute(const char* attrubuteName) {
    if(getSEXP()==R_NilValue) {
      Rprintf("could not get attribute on uninitialized R_Object.\n");
      return;
    }
    return getAttrib(getSEXP(),install(attrubuteName));
  }

  template<SEXPTYPE RTYPE>
  const SEXP RObject<RTYPE>::getAttribute(const SEXP attrubuteSymbol) {
    if(getSEXP()==R_NilValue) {
      Rprintf("could not get attribute on uninitialized R_Object.\n");
      return;
    }
    return getAttrib(getSEXP(), attrubuteSymbol);
  }

  template<SEXPTYPE RTYPE>
  template<typename T>
  void RObject<RTYPE>::setClass(T beg, T end) {
    SEXP classes;
    SEXP r_object = handle_->getRObject();

    PROTECT(classes = string2sexp(beg,end));
    classgets(r_object,classes);
    UNPROTECT(1);
  }

  template<SEXPTYPE RTYPE>
  void RObject<RTYPE>::setClass(const char* cls) {
    SEXP cls_sexp;
    SEXP r_object = handle_->getRObject();

    PROTECT(cls_sexp = allocVector(STRSXP,1));
    SET_STRING_ELT(cls_sexp, 0, mkChar(cls));

    classgets(r_object,cls_sexp);
    UNPROTECT(1);
  }

  template<SEXPTYPE RTYPE>
  template<typename T>
  void RObject<RTYPE>::getClass(T insert_iter) {
    SEXP klass = getAttrib(getSEXP(),R_ClassSymbol);
    sexp2string(klass, insert_iter);
  }

  template<SEXPTYPE RTYPE>
  const SEXP RObject<RTYPE>::getSEXP() {
    return handle_->getRObject();
  }
} // namespace RAbstraction

#endif //ROBJECT_HPP
