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

  template<typename T>
  class RMatrix {
  private:
    Rbackend handle_;
  public:
    ~RMatrix();
    RMatrix();
    RMatrix(const int rows, const int cols);
    RMatrix(const SEXP x);

    const int rows();
    const int cols();

    template<typename T>
    void setColnames(T beg, T end);

    template<typename T>
    void setRownames(T beg, T end);

    template<typename T>
    void getColnames(T insert_iter);

    template<typename T>
    void getRownames(T insert_iter);

    T operator()(const int m, const int n);
  };

  ~RMatrix<T>::RMatrix() {
    handle_->detach();
  }

} // namespace RAbstraction

#endif //RMATRIX_HPP
