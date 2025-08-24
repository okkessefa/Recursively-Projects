#include <iostream>
#include <string>   // for std::string
#include "fibonacci.h"



// Memoized Fibonacci (top-down DP) with logging.
std::int64_t fib_memo(int n, std::vector<std::int64_t> &memo, int depth = 0){
    // intentation for visual hierarchy
    std::string intent(depth * 2, ' ');
    std::cout<< intent <<"Enter F(" << n << ")\n";

    if(n < 0){
        std::cout << intent << "Invalid input F(" << n << "), returning 0\n";
        return 0;
    }
    
    if(n<= 1){
        std::cout<<"Reuse base F("<< n << ") = " << n <<'\n';
        return n;
    }
    if(memo[n] != -1){
        std::cout<<"Reuse F("<< n << ") = " << memo[n] <<'\n';
        return memo[n];
    }

    std::int64_t left = fib_memo(n - 1, memo, depth + 1); // deeper recursion
    std::int64_t right = fib_memo(n - 2, memo, depth + 1); // deeper recursion

    memo[n] = left + right;

    std::cout<< intent << "Computed F(" << n << ") = " << memo[n] << "\n";
    return memo[n];
}


std::int64_t fib(int n){
    std::vector<std::int64_t> memo(n+1, -1);
    return fib_memo(n, memo);
}


// simplified version
/*
int fib_memo(integer_value, memo){
    // base case
    if(n<= 1) return n;
    if(memo[n] != -1) return memo[n];
    
    // do somwthing to shtink the sub-problem 
    memo[n] = fib_memo(n - 1, memo) + fib_memo(n - 2, memo);

    // Recursive part 
    return memo[n];
}
//wrapper function
int fib(integer_value){
    memo(n+1, -1);
    return fib_memo(n, memo);
}
 */