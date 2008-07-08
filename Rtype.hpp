#ifndef RTYPE_HPP
#define RTYPE_HPP

#include <string>
#include <Rinternals.h>

using std::string;

template<SEXPTYPE T>
class Rtype;

template<>
class Rtype<REALSXP> {
public:
  typedef double ValueType;
  static double scalar(SEXP x) {
    return REAL(x)[0];
  }
};

template<>
class Rtype<INTSXP> {
public:
  typedef int ValueType;
  static int scalar(SEXP x) {
    return INTEGER(x)[0];
  }
};

template<>
class Rtype<LGLSXP> {
public:
  typedef int ValueType;
  static int scalar(SEXP x) {
    return INTEGER(x)[0];
  }
};

template<>
class Rtype<STRSXP> {
public:
  typedef string ValueType;
  static string scalar(SEXP x) {
    string ans(CHAR(STRING_ELT(x, 0)));
    return ans;
  }
};



#endif // RTYPE_HPP
