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
