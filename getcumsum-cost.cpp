#include <RcppArmadillo.h>
using namespace Rcpp; // to be able to export Cost module

// [[Rcpp::depends(RcppArmadillo)]]

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

class Cost {
private:
  arma::mat X; 
  arma::mat cumsum_X;
  arma::mat cumsum_X_squared;
public:
  
  // Constructor
  Cost(const arma::mat& Xin) {
    X = Xin;
    
    // Pre-compute at creation time
    cumsum_X = cumulative_sum(Xin);
    cumsum_X_squared = cumulative_sum(arma::pow(Xin, 2));
  }
  
  double eval(int start, int end) {
    int nr = end - start;
    
    // Isoltate the sub-matrix
    arma::mat sub = X.rows(start, end-1);
    
    arma::rowvec meanX = arma::mean(sub, 0);
    
    double res = 0;
    for (int i=0; i<nr; i++) {
      res += std::pow(arma::norm(sub.row(i) - meanX, 2), 2);
    }
    
    return res;
  }
  
  double eval_efficient(int start, int end) {
    
    // We can slice precomputed cumsum_X and cumsum_X_squared
    
    double error_sum_X_squared = arma::sum(cumsum_X_squared.row(end) - cumsum_X_squared.row(start));
    double squared_error_sum_X = std::pow(arma::norm(cumsum_X.row(end) - cumsum_X.row(start), 2), 2);
    
    return error_sum_X_squared - squared_error_sum_X/(end-start);
  }
  
};
  
RCPP_MODULE(mod_Cost) {  
  class_<Cost>( "Cost")
  .constructor<arma::mat>()
  .method( "eval", &Cost::eval)
  .method( "eval_efficient", &Cost::eval_efficient)
  ;
}