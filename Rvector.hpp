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
#include <R.backend.hpp>
#include <Robject.hpp>
#include <Rutilities.hpp>

namespace RAbstraction {

  template<SEXPTYPE RTYPE>
  class RVector : public Robject<RTYPE> {
    using RObject<RTYPE>::handle_;
    using RObject<RTYPE>::ValueType;
  public:
    typedef typename Rtype<RTYPE>::ValueType ValueType;
    ~RVector();
    RVector();
    RVector(const R_len_t length);
    RVector(const SEXP x);

    const R_len_t length();

    template<typename T>
    void setNames(T beg, T end);

    template<typename T>
    void getNames(T insert_iter);

    ValueType operator()(const R_len_t i);
  };

  template<SEXPTYPE RTYPE>
  ~RVector<RTYPE>::RVector() {}
  // now handled by Robject -- handle_->detach();

  template<SEXPTYPE RTYPE>
  RVector<RTYPE>::RVector() : Robject() {}

  template<SEXPTYPE RTYPE>
  RVector<RTYPE>::RVector(R_len_t length) : Robject(length) {}

  template<SEXPTYPE RTYPE>
  RVector<RTYPE>::RVector(const SEXP x) : Robject(x) {}

  template<SEXPTYPE RTYPE>
  const R_len_t length() {
    return length(handle_->getRobject());
  }

  template<SEXPTYPE RTYPE>
  template<typename T>
  void setNames(T beg, T end) {
    SEXP r_object, r_object_names, new_names;
    int unprotect = 0;

    r_object = handle_->getRobject();

    const int new_names_size = static_cast<const int>(std::distance(beg,end));

    if(new_names_size!=length(r_object)) {
      return;
    }

    PROTECT(new_names = string2sexp(beg,end));
    ++unprotect;

    setAttrib(r_object, R_NamesSymbol, new_names);
    UNPROTECT(unprotect);
  }


  template<SEXPTYPE RTYPE>
  template<typename T>
  void getNames(T insert_iter) {
    SEXP r_object, r_object_names, cnames;

    r_object = handle_->getRobject();
    r_object_names = getAttrib(x, R_NamesSymbol);

    if(r_object_names==R_NilValue) {
      return;
    }
    sexp2string(r_object_names,insert_iter);
  }


  template<SEXPTYPE RTYPE>
  ValueType& operator()(const R_len_t i, const R_len_t j) {
    SEXP r_object;
    ValueType hat;
    r_object = handle_->getRobject();
    Rprintf("not implemented yet.\n");
    return *hat;
  }

} // namespace RAbstraction

#endif //RVECTOR_HPP
