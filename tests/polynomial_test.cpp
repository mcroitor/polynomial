#include <stdlib.h>
#include <iostream>
#include "polynomial.h"

/*
 * Simple C++ Test Suite
 */

void polynomial_init() {
    std::cout << "polynomial initialization test" << std::endl;
    mc::polynomial<double> p = {1, 0, 2, 5, 0};
    std::cout << p << std::endl;
    if (p.degree() > 3) {
        std::cout << "%TEST_FAILED% time=0 testname=initialization test (polynomial_test) message=incorrect polynomial degree" << std::endl;
        return;
    }

    if (p[0] != 1 || p[1] != 0 || p[2] != 2 || p[3] != 5) {
        std::cout << "%TEST_FAILED% time=0 testname=initialization test (polynomial_test) message=incorrect coefficients" << std::endl;
        return;
    }
}

void polynomial_sum() {
    std::cout << "polynomial sum test" << std::endl;
    mc::polynomial<double> p = {1, 1, -2, 1},
    g = {0, 1, 2, -1}, result = p + g;
    mc::polynomial<double> test = {1, 2};
    std::cout << p << " + " << g << " = " << result << std::endl;
    if (!(test == result)) {
        std::cout << "%TEST_FAILED% time=0 testname=sum test (polynomial_test) message=incorrect sum" << std::endl;
        return;
    }
}

void polynomial_multiplication() {
    std::cout << "polynomial multiplication test" << std::endl;
    mc::polynomial<double> p = {1, 1, 0},
    g = {-1, 1, -1, 1}, result = p*g;
    mc::polynomial<double> test = {-1, 0, 0, 0, 1};
    std::cout << p << " * " << g << " = " << result << std::endl;
    if (!(test == result)) {
        std::cout << "%TEST_FAILED% time=0 testname=multiplication test (polynomial_test) message=incorrect product sum" << std::endl;
        return;
    }
}

void polynomial_division() {
    std::cout << "polynomial division test" << std::endl;
    mc::polynomial<double> p = {0, 0, 0, 1},
    g = {-1, 1}, result = p / g;
    mc::polynomial<double> test = {1, 1, 1};
    std::cout << p << " / " << g << " = " << result << std::endl;
    if (!(test == result)) {
        std::cout << "%TEST_FAILED% time=0 testname=division test (polynomial_test) message=incorrect division result" << std::endl;
        return;
    }
}

void polynomial_mod() {
    std::cout << "polynomial mod test" << std::endl;
    mc::polynomial<double> p = {0, 0, 0, 1},
    g = {-1, 1}, result = p % g;
    mc::polynomial<double> test = {1};
    std::cout << p << " / " << g << " = " << result << std::endl;
    if (!(test == result)) {
        std::cout << "%TEST_FAILED% time=0 testname=mod test (polynomial_test) message=incorrect mod result" << std::endl;
        return;
    }
}

void polynomial_big_int() {
    std::cout << "polynomial big integer test" << std::endl;
    mc::polynomial<std::int64_t> p = {0, 0, 0, 1},
    g = {-1, 1}, result = p % g;
    mc::polynomial<std::int64_t> test = {1};
    std::cout << p << " / " << g << " = " << result << std::endl;
    if (!(test == result)) {
        std::cout << "%TEST_FAILED% time=0 testname=big integer test (polynomial_test) message=incorrect big int result" << std::endl;
        return;
    }
}

void polynomial_spec() {
    std::cout << "polynomial spec test" << std::endl;
    mc::polynomial<std::int64_t> result(1);
    mc::polynomial<std::int64_t> p1 = mc::polynomial<std::int64_t>(1, 1) + mc::polynomial<std::int64_t>(-1);
    mc::polynomial<std::int64_t> p2 = mc::polynomial<std::int64_t>(1, 1) + mc::polynomial<std::int64_t>(1);

    result *= p1;
    result *= p2;
    mc::polynomial<std::int64_t> test = {-1, 0, 1};
    std::cout << test << " = " << result << std::endl;
    if (!(test == result)) {
        std::cout << "%TEST_FAILED% time=0 testname=spec test (polynomial_test) message=incorrect spec result" << std::endl;
        return;
    }
}

int main(int argc, char** argv) {
    std::cout << "%SUITE_STARTING% newsimpletest2" << std::endl;
    std::cout << "%SUITE_STARTED%" << std::endl;

    std::cout << "%TEST_STARTED% test1 (polynomial init)" << std::endl;
    polynomial_init();
    std::cout << "%TEST_FINISHED% time=0 test1 (polynomial init)" << std::endl;

    std::cout << "%TEST_STARTED% test2 (polynomial sum)" << std::endl;
    polynomial_sum();
    std::cout << "%TEST_FINISHED% time=0 test2 (polynomial sum)" << std::endl;

    std::cout << "%TEST_STARTED% test3 (polynomial multiplication)" << std::endl;
    polynomial_multiplication();
    std::cout << "%TEST_FINISHED% time=0 test3 (polynomial multiplication)" << std::endl;

    std::cout << "%TEST_STARTED% test4 (polynomial division)" << std::endl;
    polynomial_division();
    std::cout << "%TEST_FINISHED% time=0 test4 (polynomial division)" << std::endl;

    std::cout << "%TEST_STARTED% test5 (polynomial mod)" << std::endl;
    polynomial_mod();
    std::cout << "%TEST_FINISHED% time=0 test5 (polynomial mod)" << std::endl;

//    std::cout << "%TEST_STARTED% test6 (polynomial big integer)" << std::endl;
//    polynomial_big_int();
//    std::cout << "%TEST_FINISHED% time=0 test5 (polynomial big integer)" << std::endl;

    std::cout << "%TEST_STARTED% test6 (polynomial spec)" << std::endl;
    polynomial_spec();
    std::cout << "%TEST_FINISHED% time=0 test7 (polynomial spec)" << std::endl;

    std::cout << "%SUITE_FINISHED% time=0" << std::endl;

    return (EXIT_SUCCESS);
}

