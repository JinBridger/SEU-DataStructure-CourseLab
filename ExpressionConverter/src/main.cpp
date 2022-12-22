#include "ExpressionConverter.h"

#include <iostream>
#include <string>

// infix2prefix: Time Complexity:  O(n)
//               Space Complexity: O(n)
// prefix2infix: Time Complexity:  O(n^2)
//               Space Complexity: O(n)

int main() {
    std::string infix1 = "A*B/C";
    std::string infix2 = "A/B-C+D*E-A*C";
    std::string infix3 = "A*(B+C)/D-G";

    std::string prefix1 = "/*ABC";
    std::string prefix2 = "-+-/ABC*DE*AC";
    std::string prefix3 = "-/*A+BCDG";

    ExpressionConverter cvt;

    std::cout << cvt.infix2prefix(infix1) << std::endl;
    std::cout << cvt.infix2prefix(infix2) << std::endl;
    std::cout << cvt.infix2prefix(infix3) << std::endl;

    std::cout << std::endl;

    std::cout << cvt.prefix2infix(prefix1) << std::endl;
    std::cout << cvt.prefix2infix(prefix2) << std::endl;
    std::cout << cvt.prefix2infix(prefix3) << std::endl;
}