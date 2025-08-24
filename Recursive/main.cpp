#include <iostream>
#include "fibonacci.h"

int main() {
    int n;
    std::cout << "Enter a number for Fibonacci: ";
    std::cin >> n;

    std::cout << "\nTracing recursive calls:\n";
    
    std::cout << "F(" << n << ") = " << fib(n) << "\n";
    return 0;
}
