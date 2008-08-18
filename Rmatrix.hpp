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

#ifndef RMATRIX_HPP
#define RMATRIX_HPP

#include <Rinternals.h>
#include <R.backend.hpp>
#include <Robject.hpp>
#include <Rutilities.hpp>

namespace RAbstraction {

  template<typename RTYPE>
  class RMatrix : public Robject<RTYPE> {
  public:
    typedef typename Rtype<RTYPE>::ValueType ValueType;
    ~RMatrix();
    RMatrix();
    RMatrix(const R_len_t rows, const R_len_t cols);
    RMatrix(const SEXP x);

    const R_len_t rows();
    const R_len_t cols();

    template<typename T>
    void setColnames(T beg, T end);

    template<typename T>
    void setRownames(T beg, T end);

    template<typename T>
    void getColnames(T insert_iter);

    template<typename T>
    void getRownames(T insert_iter);

    ValueType operator()(const R_len_t m, const R_len_t n);
  };

  template<typename RTYPE>
  ~RMatrix<RTYPE>::RMatrix() {}
  // now handled by Robject -- handle_->detach();

  template<typename RTYPE>
  RMatrix<RTYPE>::RMatrix() : Robject() {}

  template<typename RTYPE>
  RMatrix<RTYPE>::RMatrix(R_len_t rows, R_len_t cols) : Robject(rows*cols) {
    SEXP dim_attribute;

    // check overflow
    if(static_cast<double>(rows) * static_cast<double>(cols) > INT_MAX) {
      handle_->detach();
      handle_ = Rbackend<RTYPE>::init();
      Rprintf("matrix dimensions too big.\n");
  }

    // add dimensions
    PROTECT(dims = allocVector(INTSXP, 2));
    INTEGER(dims)[0] = rows;
    INTEGER(dims)[1] = cols;
    setAttrib(handle_, R_DimSymbol, dims);
    UNPROTECT(1); // dims
  }

  template<typename RTYPE>
  RMatrix<RTYPE>::RMatrix(const SEXP x) : Robject(x) {}

  template<typename RTYPE>
  const R_len_t rows() {
    return nrows(handle_->getRobject());
  }

  template<typename RTYPE>
  const R_len_t cols() {
    return nrows(handle_->getRobject());
  }

  template<typename RTYPE>
  template<typename T>
  void setColnames(T beg, T end) {
    SEXP r_object, dimnames, cnames;
    int unprotect = 0;

    r_object = handle_->getRobject();

    const int cn_size = static_cast<const int>(std::distance(beg,end));

    if(cn_size!=ncols(r_object)) {
      return;
    }

    PROTECT(cnames = string2sexp(beg,end));
    ++unprotect;

    // check if we have existing dimnames
    dimnames = getAttrib(r_object, R_DimNamesSymbol);
    if(dimnames == R_NilValue) {
      PROTECT(dimnames = allocVector(VECSXP, 2));
      ++unprotect;
      SET_VECTOR_ELT(dimnames, 0, R_NilValue);
    }
    SET_VECTOR_ELT(dimnames, 1, cnames);
    setAttrib(r_object, R_DimNamesSymbol, dimnames);
    UNPROTECT(unprotect);
  }

  template<typename RTYPE>
  template<typename T>
  void setRownames(T beg, T end) {
    SEXP r_object, dimnames, rnames;
    int unprotect = 0;

    r_object = handle_->getRobject();

    const int cn_size = static_cast<const int>(std::distance(beg,end));

    if(cn_size!=ncols(r_object)) {
      return;
    }

    PROTECT(rnames = string2sexp(beg,end));
    ++unprotect;

    // check if we have existing dimnames
    dimnames = getAttrib(r_object, R_DimNamesSymbol);
    if(dimnames == R_NilValue) {
      PROTECT(dimnames = allocVector(VECSXP, 2));
      ++unprotect;
      SET_VECTOR_ELT(dimnames, 1, R_NilValue);
    }
    SET_VECTOR_ELT(dimnames, 0, rnames);
    setAttrib(r_object, R_DimNamesSymbol, dimnames);
    UNPROTECT(unprotect);
  }

  template<typename RTYPE>
  template<typename T>
  void getColnames(T insert_iter) {
    SEXP r_object, dimnames, cnames;

    r_object = handle_->getRobject();

    dimnames = getAttrib(x, R_DimNamesSymbol);

    if(dimnames==R_NilValue) {
      return;
    }

    cnames = VECTOR_ELT(dimnames, 1);

    if(cnames==R_NilValue) {
      return;
    }

    sexp2string(cnames,insert_iter);
  }

  template<typename RTYPE>
  template<typename T>
  void getRownames(T insert_iter) {
    SEXP r_object, dimnames, rnames;

    r_object = handle_->getRobject();

    dimnames = getAttrib(x, R_DimNamesSymbol);

    if(dimnames==R_NilValue) {
      return;
    }

    rnames = VECTOR_ELT(dimnames, 0);

    if(rnames==R_NilValue) {
      return;
    }

    sexp2string(rnames,insert_iter);
  }


  template<typename RTYPE>
  ValueType& operator()(const R_len_t i, const R_len_t j) {
    SEXP r_object;
    ValueType hat;
    r_object = handle_->getRobject();
    Rprintf("not implemented yet.\n");
    return *hat;
  }

} // namespace RAbstraction

#endif //RMATRIX_HPP
