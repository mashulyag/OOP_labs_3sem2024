#include <gtest/gtest.h>
#include "octagon.h"
#include "figures.h"
#include <math.h>


TEST(Oct_test, square_of_empty){
    Octagon<double> o;
    ASSERT_EQ(o.square(), 0.0);
}

TEST(Oct_test, square){
    Point<double> p1(0, 0);
    Point<double> p2(1, 0);
    Point<double> p3(1.5, sqrt(2));
    Point<double> p4(1, sqrt(2) + 1);
    Point<double> p5(0, sqrt(2) + 1);
    Point<double> p6(-0.5, sqrt(2));
    Point<double> p7(-1, 0);
    Point<double> p8(-0.5, -sqrt(2));

    Octagon<double> oct(p1, p2, p3, p4, p5, p6, p7, p8);
    ASSERT_NEAR(oct.square(), 2.38018, 0.00001);
    
}

TEST(Oct_test, center_of_empty){
    Octagon<double> o1;
    Point<double> p1;
    ASSERT_EQ(o1.center(), p1);
}

TEST(Oct_test, center) {
    Point<double> p1(0, 0);
    Point<double> p2(1, 0);
    Point<double> p3(1.5, sqrt(2));
    Point<double> p4(1, sqrt(2) + 1);
    Point<double> p5(0, sqrt(2) + 1);
    Point<double> p6(-0.5, sqrt(2));
    Point<double> p7(-1, 0);
    Point<double> p8(-0.5, -sqrt(2));

    Octagon oct(p1, p2, p3, p4, p5, p6, p7, p8);
    Point<double> center{0.1875, 0.78033};
    
    ASSERT_NEAR(oct.center()._x, center._x, 0.00001);
    ASSERT_NEAR(oct.center()._y, center._y, 0.00001);
}

TEST(Oct_test, equality_1){
    Point<double> p1(0, 0);
    Point<double> p2(1, 0);
    Point<double> p3(1.5, sqrt(2));
    Point<double> p4(1, sqrt(2) + 1);
    Point<double> p5(0, sqrt(2) + 1);
    Point<double> p6(-0.5, sqrt(2));
    Point<double> p7(-1, 0);
    Point<double> p8(-0.5, -sqrt(2));

    Octagon<double> o1{p1,p2,p3,p4,p5,p6,p7,p8};
    Octagon<double> o2{p1,p2,p3,p4,p5,p6,p7,p8};
    ASSERT_TRUE(o1 == o2);
}

TEST(Oct_test, equality_2){
    Point<double> p1(0, 0);
    Point<double> p2(1, 0);
    Point<double> p3(1.5, sqrt(2));
    Point<double> p4(1, sqrt(2) + 1);
    Point<double> p5(0, sqrt(2) + 1);
    Point<double> p6(-0.5, sqrt(2));
    Point<double> p7(-1, 0);
    Point<double> p8(-0.5, -sqrt(2));
    Point<double> p9(5, 1);

    Octagon<double> o1{p1,p3,p2,p4,p5,p6,p7,p8};
    Octagon<double> o2{p2,p1,p3,p8,p4,p5,p6,p9};
    ASSERT_FALSE(o1 == o2);
}


TEST(Oct_test, assignment){
    Point<double> p1(0, 0);
    Point<double> p2(1, 0);
    Point<double> p3(1.5, sqrt(2));
    Point<double> p4(1, sqrt(2) + 1);
    Point<double> p5(0, sqrt(2) + 1);
    Point<double> p6(-0.5, sqrt(2));
    Point<double> p7(-1, 0);
    Point<double> p8(-0.5, -sqrt(2));
    
    Octagon<double> o1;
    Octagon<double> o2{p2,p1,p3,p8,p4,p5,p6,p7};
    o1 = o2;
    ASSERT_TRUE(o1 == o2);
}


TEST(Oct_test, assignment_move){
    Point<double> p1(0, 0);
    Point<double> p2(1, 0);
    Point<double> p3(1.5, 2);
    Point<double> p4(1, 1.2 + 1);
    Point<double> p5(0, 1.2 + 1);
    Point<double> p6(-0.5, 1.2);
    Point<double> p7(-1, 0);
    Point<double> p8(-0.5, -1.2);
    
    Octagon<double> o1;
    Octagon<double> o2{p2,p1,p3,p8,p4,p5,p6,p7};
    o1 = std::move(o2);
    ASSERT_TRUE(o1 == o2);
}

TEST(Oct_test, operator_double) {
    Point<double> p1(0, 0);
    Point<double> p2(1, 0);
    Point<double> p3(1.5, sqrt(2));
    Point<double> p4(1, sqrt(2) + 1);
    Point<double> p5(0, sqrt(2) + 1);
    Point<double> p6(-0.5, sqrt(2));
    Point<double> p7(-1, 0);
    Point<double> p8(-0.5, -sqrt(2));

    Octagon<double> oct(p1, p2, p3, p4, p5, p6, p7, p8);
    ASSERT_NEAR(static_cast<double>(oct), oct.square(), 0.00001);
}

TEST(Oct_test, input) {
    Point<double> p1(1, 8);
    Point<double> p2(2, 7);
    Point<double> p3(3, 6);
    Point<double> p4(4, 5);
    Point<double> p5(5, 4);
    Point<double> p6(6, 3);
    Point<double> p7(7, 2);
    Point<double> p8(8, 1);

    Octagon<double> o1{p1,p2,p3,p4,p5,p6,p7,p8};

    std::stringstream input("1 8\n8 1\n2 7\n"
                            "7 2\n3 6\n6 3\n"
                            "4 5\n5 4\n");

    Octagon<double> o2;
    input >> o2;
    ASSERT_FALSE(o1 == o2);
}

TEST(Oct_test, input_excp) {
    std::stringstream input("1 8\n8 1\n2 7\n"
                            "7 2\n3 6\n6 3\n"
                            "4 5\n5 e\n");

    Octagon<double> o2;
    ASSERT_THROW(input >> o2, std::invalid_argument);
}

TEST(Oct_test, input_excp1) {
    std::stringstream input("1 8\n8 1\n2 7\n"
                            "7 2\n3 6\n6 3\n"
                            "4 5\n4 5\n");

    Octagon<double> o2;
    ASSERT_THROW(input >> o2, std::logic_error);
}

TEST(Oct_test, output) {
    Point<double> p1(0, 0);
    Point<double> p2(1, 0);
    Point<double> p3(1.5, sqrt(2));
    Point<double> p4(1, sqrt(2) + 1);
    Point<double> p5(0, sqrt(2) + 1);
    Point<double> p6(-0.5, sqrt(2));
    Point<double> p7(-1, 0);
    Point<double> p8(-0.5, -sqrt(2));
    Octagon<double> o1{p1,p2,p3,p4,p5,p6,p7,p8};

    std::ostringstream os;
    os << o1;
    std::string output = "Octagon's coordinates:\n"
                         "(x: 0; y: 0)\n"
                         "(x: 1; y: 0)\n"
                         "(x: 1.5; y: 1.41421)\n"
                         "(x: 1; y: 2.41421)\n"
                         "(x: 0; y: 2.41421)\n"
                         "(x: -0.5; y: 1.41421)\n"
                         "(x: -1; y: 0)\n"
                         "(x: -0.5; y: -1.41421)\n";
    ASSERT_EQ(os.str(), output);
}

TEST(Oct_test, output1) {
    Octagon<double> o1;

    std::ostringstream os;
    os << o1;
    std::string output = "Octagon's coordinates:\n"
                         "(x: 0; y: 0)\n"
                         "(x: 0; y: 0)\n"
                         "(x: 0; y: 0)\n"
                         "(x: 0; y: 0)\n"
                         "(x: 0; y: 0)\n"
                         "(x: 0; y: 0)\n"
                         "(x: 0; y: 0)\n"
                         "(x: 0; y: 0)\n";
    ASSERT_EQ(os.str(), output);
}
