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

#ifndef R_BACKEND_HPP
#define R_BACKEND_HPP

#include <Rinternals.h>
#include <Rsexp.allocator.templates.hpp>
#include <Rutilities.hpp>

namespace RAbstraction {

  template<typename RTYPE>
  class Rbackend {
  private:
    int refcount_;
    bool release_data_;
    SEXP R_object_;

    Rbackend();
    Rbackend(const R_len_t length);
    Rbackend(const SEXP x);

    // not allowed
    Rbackend(const Rbackend& t);
    Rbackend& operator=(const Rbackend& right);
  public:
    typedef ValueType Rtype<RTYPE>::ValueType;

    ~Rbackend();

    static Rbackend* init();
    static Rbackend* init(const R_len_t length);
    static Rbackend* init(const SEXP x);

    void attach();
    void detach();

    void setAttribute(const char* attrubuteName, const SEXP attributeValue);
    const SEXP fetchAttribute(const char* attrubuteName);

    const SEXP getRobject();
  };

  template<typename RTYPE>
  Rbackend<RTYPE>::~Rbackend() {
    if(release_data_) {
      if(R_object_!=R_NilValue) {
        UNPROTECT_PTR(R_object_);
      }
    }
  }

  template <typename RTYPE>
  Rbackend<RTYPE>::Rbackend() {
    refcount_ = 1;
    release_data_ = true;
    R_object_ = R_NilValue;
  }

  template <typename RTYPE>
  Rbackend<RTYPE>::Rbackend(const R_len_t length) {
    refcount_ = 1;
    release_data_ = true;

    // all R data objects are vectors
    // just add dim attribute if you need a matrix
    PROTECT(R_object_ = R_allocator<TYPE>::Vector(length));
  }

  template <typename RTYPE>
  Rbackend<RTYPE>::Rbackend(const SEXP x) {
    R_object_ = x;
    refcount_ = 1;

    // do not release data (presumably) already allocated in R session
    release_data_ = false;
  }

  template<typename RTYPE>
  Rbackend* Rbackend<RTYPE>::init() {
    return new Rbackend();
  }

  template<typename RTYPE>
  Rbackend* Rbackend<RTYPE>::init(const R_len_t length) {
    return new Rbackend(length);
  }

  template<typename RTYPE>
  Rbackend* Rbackend<RTYPE>::init(const SEXP x) {
    return new Rbackend(x);
  }

  template<typename RTYPE>
  void Rbackend<RTYPE>::attach() {
    ++refcount_;
  }

  template<typename RTYPE>
  void Rbackend<RTYPE>::detach() {
    if(--refcount_ == 0) {
      delete this;
    }
  }

  template<typename RTYPE>
  void Rbackend::setAttribute(const char* attrubuteName, const SEXP attributeValue) {
    if(R_object_==R_NilValue || attributeValue==R_NilValue) {
      Rprintf("could not set attribute.\n");
      return;
    }
    setAttrib(R_object_,install(attrubuteName),r_dates);
  }

  template<typename RTYPE>
  const SEXP Rbackend::fetchAttribute(const char* attrubuteName) {
    if(R_object_==R_NilValue) {
      Rprintf("could not fetch attribute on uninitialized R_Object.\n");
      return;
    }
    return getAttrib(R_object_,install(attrubuteName));
  }

  template<typename RTYPE>
  const SEXP getRobject() {
    return R_object_;
  }
} // namespace RAbstraction

#endif // R_BACKEND_HPP
