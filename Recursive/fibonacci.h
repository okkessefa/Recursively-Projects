#ifndef FIBONACCI_H
#define FIBONACCI_H
#include <cstdint> // for std::int64_t
#include <vector>

// Function prototype
std::int64_t fib(int n);
std::int64_t fib_memo(int n, std::vector<std::int64_t> &memo, int depth);

#endif
