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
#include <Robject.hpp>
#include <Rutilities.hpp>

namespace RAbstraction {

  template<SEXPTYPE RTYPE>
  class RVector : public RObject<RTYPE> {
    using RObject<RTYPE>::handle_;
    using RObject<RTYPE>::ValueType;
  public:
    ~RVector();
    RVector();
    RVector(const R_len_t len);
    RVector(const SEXP x);
    RVector(const RVector& x);

    const R_len_t len() const;

    template<typename T>
    void setNames(T beg, T end);

    template<typename T>
    void getNames(T insert_iter) const;

    typename RObject<RTYPE>::ValueType operator[](const R_len_t i) const;
    typename RObject<RTYPE>::ValueType& operator[](const R_len_t i);
    typename RObject<RTYPE>::ValueType operator()(const R_len_t i) const;
    typename RObject<RTYPE>::ValueType& operator()(const R_len_t i);
  };

  template<SEXPTYPE RTYPE>
  RVector<RTYPE>::~RVector() {}

  template<SEXPTYPE RTYPE>
  RVector<RTYPE>::RVector() : RObject<RTYPE>() {}

  template<SEXPTYPE RTYPE>
  RVector<RTYPE>::RVector(R_len_t len) : RObject<RTYPE>(len) {}

  template<SEXPTYPE RTYPE>
  RVector<RTYPE>::RVector(const SEXP x) : RObject<RTYPE>(x) {}

  template<SEXPTYPE RTYPE>
  RVector<RTYPE>::RVector(const RVector& x) : RObject<RTYPE>(x) {}

  template<SEXPTYPE RTYPE>
  const R_len_t RVector<RTYPE>::len() const {
    SEXP r_object = handle_->getRObject();
    return length(r_object);
  }

  template<SEXPTYPE RTYPE>
  template<typename T>
  void RVector<RTYPE>::setNames(T beg, T end) {
    SEXP r_object, new_names;

    r_object = handle_->getRObject();

    const int new_names_size = static_cast<const int>(std::distance(beg,end));

    if(new_names_size!=length(r_object)) {
      return;
    }

    PROTECT(new_names = string2sexp(beg,end));
    setAttrib(r_object, R_NamesSymbol, new_names);
    UNPROTECT(1);
  }


  template<SEXPTYPE RTYPE>
  template<typename T>
  void RVector<RTYPE>::getNames(T insert_iter) const {
    SEXP r_object, r_object_names, cnames;

    r_object = handle_->getRObject();
    r_object_names = getAttrib(r_object, R_NamesSymbol);

    if(r_object_names==R_NilValue) {
      return;
    }
    sexp2string(r_object_names,insert_iter);
  }

  template<SEXPTYPE RTYPE>
  inline
  typename RObject<RTYPE>::ValueType RVector<RTYPE>::operator[](const R_len_t i) const {
    SEXP r_object = handle_->getRObject();
    return Rtype<RTYPE>::index(r_object, i);
  }

  template<SEXPTYPE RTYPE>
  inline
  typename RObject<RTYPE>::ValueType& RVector<RTYPE>::operator[](const R_len_t i) {
    SEXP r_object = handle_->getRObject();
    return Rtype<RTYPE>::index(r_object, i);
  }

  // same as operator[], but implements auto wrapping index (ie index = i % len)
  template<SEXPTYPE RTYPE>
  inline
  typename RObject<RTYPE>::ValueType RVector<RTYPE>::operator()(const R_len_t i) const {
    SEXP r_object = handle_->getRObject();
    return Rtype<RTYPE>::index(r_object, i % len());
  }

  // same as operator[], but implements auto wrapping index (ie index = i % len)
  template<SEXPTYPE RTYPE>
  inline
  typename RObject<RTYPE>::ValueType& RVector<RTYPE>::operator()(const R_len_t i) {
    SEXP r_object = handle_->getRObject();
    return Rtype<RTYPE>::index(r_object, i % len());
  }
} // namespace RAbstraction

#endif //RVECTOR_HPP
