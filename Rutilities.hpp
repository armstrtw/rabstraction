#ifndef RUTILTIES_HPP
#define RUTILTIES_HPP

#include <Rinternals.h>

template<typename T>
SEXP string2sexp(T first, T last) {
  SEXP ans;
  const int ans_size = static_cast<const int>(std::distance(first,last));

  PROTECT(ans = allocVector(STRSXP,ans_size));

  int i = 0;
  while(first != last) {
    SET_STRING_ELT(ans, i, mkChar(first->c_str()));
    ++first; ++i;
  }
  UNPROTECT(1);
  return ans;
}

template<typename T>
void sexp2string(const SEXP str_sexp, T insert_iter) {

  if(str_sexp==R_NilValue)
    return;

  for(int i=0; i < length(str_sexp); i++) {
    //insert_iter->assign(CHAR(STRING_ELT(str_sexp,i)));
    *insert_iter = std::string(CHAR(STRING_ELT(str_sexp,i)));
    ++insert_iter;
  }
}

template<typename T>
void setColnamesMatrix(const SEXP x, T first, T last) {

  SEXP dimnames, cnames;

  const int cn_size = static_cast<const int>(std::distance(first,last));

  if(cn_size!=ncols(x))
    return;

  PROTECT(cnames = string2sexp(first,last));
  PROTECT(dimnames = allocVector(VECSXP, 2));
  SET_VECTOR_ELT(dimnames, 0, R_NilValue);
  SET_VECTOR_ELT(dimnames, 1, cnames);
  setAttrib(x, R_DimNamesSymbol, dimnames);
  UNPROTECT(2);
}

template<typename T>
void getColnamesMatrix(const SEXP x, T insert_iter) {

  SEXP dimnames, cnames;

  PROTECT(dimnames = getAttrib(x, R_DimNamesSymbol));

  if(dimnames==R_NilValue) {
    UNPROTECT(1);  // dimnames
    return;
  }

  PROTECT(cnames = VECTOR_ELT(dimnames, 1));

  if(cnames==R_NilValue) {
    UNPROTECT(2); // dimnames and cnames
    return;
  }

  sexp2string(cnames,insert_iter);
  UNPROTECT(2); // dimnames and cnames
}


#endif // RUTILTIES_HPP
