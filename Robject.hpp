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

  template<typename RTYPE>
  class RObject {
  private:
    Rbackend<RTYPE>* handle_;
  public:
    ~RObject();
    RObject();
    RObject(const R_len_t len);
    RObject(const SEXP x);

    const R_len_t length();
  };

  ~RObject<RTYPE>::RObject() {
    handle_->detach();
  }

  RObject<RTYPE>::RObject() {
    handle_ = Rbackend<RTYPE>::init();
  }

  RObject<RTYPE>::RObject(const R_len_t len) {
    handle_ = Rbackend<RTYPE>::init(len);
  }

  RObject<RTYPE>::RObject(const SEXP x) {
    handle_ = Rbackend<RTYPE>::init(x);
  }
} // namespace RAbstraction

#endif //ROBJECT_HPP