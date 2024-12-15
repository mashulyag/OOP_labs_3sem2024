#include <gtest/gtest.h>
#include "figures.h"
#include "triangle.h"

TEST(triangle_test, square){
    Triangle<double> t;
    ASSERT_EQ(t.square(), 0.0);
}

TEST(triangle_test, square1){
    Point<double> p1(-2, 0);
    Point<double> p2(2, 0);
    Point<double> p3(0, 3);
    Triangle<double> t(p1,p2,p3);

    ASSERT_EQ(t.square(), 6.0);
}

TEST(triangle_test, center){
    Triangle<double> tr1;
    Point<double> p1;
    ASSERT_EQ(tr1.center(), p1);
}

TEST(triangle_test, center1){
    Point<double> p1(-2, 0);
    Point<double> p2(2, 0);
    Point<double> p3(0, 3);

    Triangle<double> tr(p1,p2,p3);
    Point<double> center{0,1};
    ASSERT_EQ(tr.center(), center);
}

TEST(triangle_test, equality_empty){
    Triangle<double> tr1;
    Triangle<double> tr2;
    ASSERT_TRUE(tr1 == tr2);
}

TEST(triangle_test, equality_1){
    Point<double> p1(-2, 0);
    Point<double> p2(2, 0);
    Point<double> p3(0, 3);

    Triangle<double> tr1{p1,p3,p2};
    Triangle<double> tr2{p1,p3,p2};
    ASSERT_TRUE(tr1 == tr2);
}

TEST(triangle_test, equality_2){
    Point<double> p1(-2, 0);
    Point<double> p2(2, 0);
    Point<double> p3(0, 3);
    Point<double> p4(5, 1);

    Triangle<double> tr1{p1,p3,p2};
    Triangle<double> tr2{p1,p3,p4};
    ASSERT_FALSE(tr1 == tr2);
}

TEST(triangle_test, assignment1){
    Point<double> p1(1, 3);
    Point<double> p2(2, 2);
    Point<double> p3(3, 1);
    
    Triangle<double> tr1;
    Triangle<double> tr2{p1,p2,p3};
    tr1 = tr2;
    ASSERT_TRUE(tr1 == tr2);
}

TEST(triangle_test,assignment2){
    Point<double> p1(1, 3);
    Point<double> p2(2, 2);
    Point<double> p3(3, 1);
    Point<double> p4(1, 1);
    
    Triangle<double> tr1{p1,p3,p4};
    Triangle<double> tr2{p1,p2,p3};
    ASSERT_FALSE(tr1 == tr2);
}

TEST(triangle_test, assignment_move){
    Point<double> p1(1, 3);
    Point<double> p2(2, 2);
    Point<double> p3(3, 1);
    
    Triangle<double> tr1;
    Triangle<double> tr2{p1,p2,p3};
    tr1 = std::move(tr2);
    ASSERT_TRUE(tr1 == tr2);
}

TEST(triangle_test, op_double){
    Point<double> p1(1, 3);
    Point<double> p2(2, 2);
    Point<double> p3(3, 1);
    
    Triangle<double> tr1{p1,p2,p3};
    ASSERT_DOUBLE_EQ(static_cast<double>(tr1), tr1.square());
}

TEST(triangle_test, input){
    Point<double> p1(0, 0);
    Point<double> p2(2, 2);
    Point<double> p3(2, 0);
    Triangle<double> tr1{p1,p2,p3};

    std::stringstream input("0 0\n2 2\n2 0");

    Triangle<double> tr2;
    input >> tr2;
    ASSERT_TRUE(tr1 == tr2);
}

TEST(triangle_test, input_error1) {
    std::stringstream input("1 3\n3 1\n e 0");

    Triangle<double> tr2;
    ASSERT_THROW(input >> tr2, std::invalid_argument);
}

TEST(triangle_test, input_error2) {
    std::stringstream input("1 3\n3 1\n 3 1");

    Triangle<double> tr2;
    ASSERT_THROW(input >> tr2, std::logic_error);
}

TEST(triangle_test, output) {
    Point<double> p1(1, 3);
    Point<double> p2(2, 2);
    Point<double> p3(3, 1);
    Triangle<double> tr1{p1, p2, p3};

    std::ostringstream os;
    os << tr1;
    std::string output = "Triangle's coordinates:\n"
                         "(x: 1; y: 3)\n"
                         "(x: 2; y: 2)\n"
                         "(x: 3; y: 1)\n";
    ASSERT_EQ(os.str(), output);
}
