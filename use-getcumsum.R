library(Rcpp)
sourceCpp("getcumsum.cpp")

X <- matrix(1:9, nrow = 3, byrow = TRUE)
Y <- cumulative_sum(X)

print(Y)
