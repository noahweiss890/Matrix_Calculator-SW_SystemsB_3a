#include <iostream>
#include <stdexcept>
#include "doctest.h"
#include "Matrix.hpp"

using namespace zich;
using namespace std;


TEST_CASE("Illegal matrix") {
    vector<double> m1 = {1,0,0,0,1,0,0,0,1};
    CHECK_THROWS(zich::Matrix mat(m1, 4, 3));
    vector<double> m2 = {1};
    CHECK_THROWS(zich::Matrix mat(m2, 3, 3));
    vector<double> m3;
    CHECK_THROWS(zich::Matrix mat(m3, 2, 3));
}

TEST_CASE("Legal multiplication") {
    vector<double> m1 = {1,2,3,4,5,6};
    zich::Matrix mat1(m1, 2, 3);
    vector<double> m2 = {1,2,3,4,5,6,7,8,9,10,11,12};
    zich::Matrix mat2(m2, 3, 4);
    vector<double> m3 = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
    zich::Matrix mat3(m3, 4, 5);
    vector<double> m4 = {1,2,3,4,5,6,7,8,9,10};
    zich::Matrix mat4(m4, 5, 2);
    CHECK_NOTHROW(mat1 * mat2);
    CHECK_NOTHROW(mat2 * mat3);
    CHECK_NOTHROW(mat3 * mat4);
    CHECK_NOTHROW(mat4 * mat1);
    CHECK_NOTHROW(mat1 * mat2 * mat3 * mat4);
    CHECK((mat1 * mat2).getMat().size() == 8);
    CHECK((mat2 * mat3).getMat().size() == 15);
    CHECK((mat3 * mat4).getMat().size() == 8);
    CHECK((mat4 * mat1).getMat().size() == 15);
    CHECK((mat1 * mat2 * mat3 * mat4).getMat().size() == 4);
}

TEST_CASE("Illegal multiplication") {
    vector<double> m1 = {1,2,3,4,5,6};
    zich::Matrix mat1(m1, 2, 3);
    vector<double> m2 = {1,2,3,4,5,6,7,8,9,10,11,12};
    zich::Matrix mat2(m2, 4, 3);
    CHECK_THROWS(mat1 * mat1);
    CHECK_THROWS(mat1 * mat2);
}

TEST_CASE("Legal +/-") {
    vector<double> m1 = {1,2,3,4,5,6};
    zich::Matrix mat1(m1, 2, 3);
    vector<double> m2 = {6,5,4,3,2,1};
    zich::Matrix mat2(m2, 2, 3);
    vector<double> m3 = {7,7,7,7,7,7};
    zich::Matrix mat3(m3, 2, 3);
    vector<double> m4 = {1,2,3,4,5,6};
    zich::Matrix mat4(m4, 2, 3);
    vector<double> m5 = {-1,-2,-3,-4,-5,-6};
    zich::Matrix mat5(m5, 2, 3);
    vector<double> m6 = {0,0,0,0,0,0};
    zich::Matrix mat6(m6, 2, 3);
    CHECK_NOTHROW(mat1 + mat1);
    CHECK_NOTHROW(mat1 - mat1);
    CHECK_NOTHROW(mat1 + mat2);
    CHECK_NOTHROW(mat2 - mat1);
    mat1 += mat2;
    CHECK(mat1 == mat3);
    mat1 -= mat2;
    CHECK(mat1 == mat4);
    CHECK(-mat1 == mat5);
    CHECK(-mat6 == mat6);
    CHECK(+mat1 == mat1);
}

TEST_CASE("Illegal +/-") {
    vector<double> m1 = {1,2,3,4,5,6};
    zich::Matrix mat1(m1, 2, 3);
    vector<double> m2 = {6,5};
    zich::Matrix mat2(m2, 2, 1);
    CHECK_THROWS(mat1 + mat2);
    CHECK_THROWS(mat2 + mat1);
    CHECK_THROWS(mat1 - mat2);
    CHECK_THROWS(mat2 - mat1);
    CHECK_THROWS(mat1 += mat2);
    CHECK_THROWS(mat1 -= mat2);
}

TEST_CASE("Legal relational operators") {
    vector<double> m1 = {1,2,3,4,5,6};
    zich::Matrix mat1(m1, 2, 3);
    vector<double> m2 = {6,5,4,3,2,1};
    zich::Matrix mat2(m2, 2, 3);
    vector<double> m3 = {1,1,1,1};
    zich::Matrix mat3(m3, 1, 4);
    CHECK(mat1 == mat1);
    CHECK(mat1 != mat2);
    CHECK(mat3 < mat1);
    CHECK(mat1 > mat3);
    CHECK(mat1 <= mat2);
    CHECK(mat3 <= mat2);
    CHECK(mat2 >= mat1);
    CHECK(mat2 >= mat3);
}

TEST_CASE("Illegal relational operators") {
    vector<double> m1 = {1,2,3,4,5,6};
    zich::Matrix mat1(m1, 2, 3);
    vector<double> m2 = {1,2,3,4,5,6};
    zich::Matrix mat2(m2, 3, 2);
    bool bla;
    CHECK_THROWS(bla = mat1 == mat2);
    CHECK_THROWS(bla = mat1 != mat2);
}

TEST_CASE("scaler multiplication") {
    vector<double> m1 = {1,2,3,4,5,6};
    zich::Matrix mat1(m1, 2, 3);
    vector<double> m2 = {2,4,6,8,10,12};
    zich::Matrix mat2(m2, 2, 3);
    CHECK(mat1 * 1 == mat1);
    CHECK(1 * mat1 == mat1);
    CHECK(mat1 * 2 == mat2);
    CHECK(2 * mat1 == mat2);
}

TEST_CASE("Increment / Decrement") {
    vector<double> m1 = {1,2,3,4,5,6};
    zich::Matrix mat1(m1, 2, 3);
    vector<double> m2 = {2,3,4,5,6,7};
    zich::Matrix mat2(m2, 2, 3);
    vector<double> m3 = {1,2,3,4,5,6};
    zich::Matrix mat3(m3, 2, 3);
    vector<double> m4 = {1,2,3,4,5,6};
    zich::Matrix mat4(m4, 2, 3);
    vector<double> m5 = {2,3,4,5,6,7};
    zich::Matrix mat5(m5, 2, 3);
    CHECK(++mat1 == mat2);
    CHECK(--mat2 == mat3);
    CHECK(mat3++ == mat4);
    CHECK(mat5-- == mat1);
}