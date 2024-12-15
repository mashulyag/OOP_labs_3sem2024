#include <gtest/gtest.h>
#include "square.h"
#include "figures.h"

TEST(Square_test, square){
    Square<double> s;
    ASSERT_EQ(s.square(), 0.0);
}

TEST(Square_test, square1){
    Point<double> p1(0, 0);
    Point<double> p2(0, 2);
    Point<double> p3(2, 2);
    Point<double> p4(2, 0);
    Square<double> s(p1,p2,p3,p4);

    ASSERT_EQ(s.square(), 4.0);
}

TEST(Square_test, center){
    Square<double> s1;
    Point<double> p1;
    ASSERT_EQ(s1.center(), p1);
}

TEST(Square_test, center1){
    Point<double> p1(0, 0);
    Point<double> p2(0, 2);
    Point<double> p3(2, 2);
    Point<double> p4(2, 0);

    Square<double> s(p1,p2,p3,p4);
    Point<double> center{1,1};
    ASSERT_EQ(s.center(), center);
}

TEST(Square_test, equality_empty){
    Square<double> s1;
    Square<double> s2;
    ASSERT_TRUE(s1 == s2);
}

TEST(Square_test, equality_1){
    Point<double> p1(0, 0);
    Point<double> p2(0, 2);
    Point<double> p3(2, 2);
    Point<double> p4(2, 0);

    Square<double> s1{p1,p2,p3,p4};
    Square<double> s2{p1,p2,p3,p4};
    ASSERT_TRUE(s1 == s2);
}

TEST(Square_test, assignment1){
    Point<double> p1(0, 0);
    Point<double> p2(0, 2);
    Point<double> p3(2, 2);
    Point<double> p4(2, 0);
    
    Square<double> s1;
    Square<double> s2{p1,p2,p3,p4};
    s1 = s2;
    ASSERT_TRUE(s1 == s2);
}

TEST(Square_test, assignment_move){
    Point<double> p1(0, 0);
    Point<double> p2(0, 2);
    Point<double> p3(2, 2);
    Point<double> p4(2, 0);
    
    Square<double> s1;
    Square<double> s2{p1,p2,p3,p4};
    s1 = std::move(s2);
    ASSERT_TRUE(s1 == s2);
}

TEST(Square_test, op_double){
    Point<double> p1(0, 0);
    Point<double> p2(0, 2);
    Point<double> p3(2, 2);
    Point<double> p4(2, 0);
    
    Square<double> s1{p1,p2,p3,p4};
    ASSERT_DOUBLE_EQ(static_cast<double>(s1), s1.square());
}

TEST(Square_test, input){
    Point<double> p1(0, 0);
    Point<double> p2(0, 2);
    Point<double> p3(2, 2);
    Point<double> p4(2, 0);
    Square<double> s1{p1,p2,p3,p4};

    std::stringstream input("0 0\n0 2\n2 2\n2 0");

    Square<double> s2;
    input >> s2;
    ASSERT_TRUE(s1 == s2);
}

TEST(Square_test, input_error1) {
    std::stringstream input("1 3\n3 1\n e 0\n2 0");

    Square<double> s2;
    ASSERT_THROW(input >> s2, std::invalid_argument);
}

TEST(Square_test, input_error2) {
    std::stringstream input("1 3\n3 1\n 3 1\n1 2");

    Square<double> s2;
    ASSERT_THROW(input >> s2, std::logic_error);
}

TEST(Square_test, output) {
    Point<double> p1(0, 0);
    Point<double> p2(0, 2);
    Point<double> p3(2, 2);
    Point<double> p4(2, 0);
    Square<double> s1{p1, p2, p3, p4};

    std::ostringstream os;
    os << s1;
    std::string output = "Square's coordinates:\n"
                         "(x: 0; y: 0)\n"
                         "(x: 0; y: 2)\n"
                         "(x: 2; y: 2)\n"
                         "(x: 2; y: 0)\n";
    ASSERT_EQ(os.str(), output);
}
