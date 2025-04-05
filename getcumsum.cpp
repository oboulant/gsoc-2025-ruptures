// [[Rcpp::depends(RcppArmadillo)]]
#include <RcppArmadillo.h>

// [[Rcpp::export]]
arma::mat cumulative_sum(const arma::mat& X) {
  arma::uword T = X.n_rows;
  arma::uword D = X.n_cols;
  
  // initialize with zeros
  arma::mat Y(T + 1, D, arma::fill::zeros); 
  
  for (arma::uword t = 0; t < T; ++t) {
    Y.row(t + 1) = Y.row(t) + X.row(t);
  }
  
  return Y;
}