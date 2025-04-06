library(Rcpp)
library("microbenchmark")

sourceCpp("getcumsum-cost.cpp")

X = matrix(rnorm(10000000), ncol = 100)
cost_obj = new(Cost, X)

# getcumsum
Y <- cumulative_sum(X)

# cost "unefficient"
res_uneffcient <- cost_obj$eval(0, 10000)

# cost "unefficient"
res_efficient <- cost_obj$eval_efficient(0, 10000)

# counterpart in native R
R_eval = function(X, start, end){ 
  subX = X[start+1:end, ] 
  cMeans = colMeans(subX)
  
  return(sum(sweep(subX, 2, cMeans, FUN = "-")^2)) 
}

res_r <- R_eval(X, 0, 10000)

# compare

## output values
all.equal(res_r, res_efficient, res_uneffcient)

## performance
microbenchmark::microbenchmark(R_eval(X, 0, 1000),
                               cost_obj$eval_efficient(0, 1000),
                               cost_obj$eval(0, 1000),
                               times = 10)
