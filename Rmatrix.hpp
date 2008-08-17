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

namespace RAbstraction {

  template<typename RTYPE>
  class RMatrix {
  private:
    Rbackend<RTYPE>* handle_;
  public:
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

    T operator()(const R_len_t m, const R_len_t n);
  };

  ~RMatrix<RTYPE>::RMatrix() {
    handle_->detach();
  }

  RMatrix<RTYPE>::RMatrix() {
    handle_ = Rbackend<RTYPE>::init();
  }

  RMatrix<RTYPE>::RMatrix(R_len_t rows, R_len_t cols) {
    SEXP dim_attribute;

    // check for dimensions too big
    if(static_cast<double>(rows) * static_cast<double>(cols) > INT_MAX) {
      handle_ = Rbackend<RTYPE>::init();
      Rprintf("matrix dimensions too big.\n");
    } else {
      handle_ = Rbackend<RTYPE>::init(rows*cols);
    }

    // add dimensions
    PROTECT(dims = allocVector(INTSXP, 2));
    INTEGER(dims)[0] = rows;
    INTEGER(dims)[1] = cols;
    setAttrib(handle_, R_DimSymbol, dims);
    UNPROTECT(1); // dims
  }

  RMatrix<RTYPE>::RMatrix(const SEXP x) {
    handle_ =

} // namespace RAbstraction

#endif //RMATRIX_HPP
