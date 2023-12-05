library(ggplot2)

A = 3
B = -5
C = 10



x <- seq(from = -abs(B/A) - abs(C/A), to = abs(B/A) + abs(C/A), length.out = 1000);
plot(x, A*x^2 - B*x + C)

zero_1 <- 