#include <gtest/gtest.h>
#include <math.h>
#include "figures.h"
#include "triangle.h"
#include "square.h"
#include "octagon.h"
#include "array.h"

TEST(triangle_test, square_of_empty){
    Triangle tr;
    ASSERT_EQ(tr.square(), 0.0);
}

TEST(triangle_test, square){
    Point p1(-2, 0);
    Point p2(2, 0);
    Point p3(0, 3);

    Triangle tr(p1,p2,p3);
    ASSERT_EQ(tr.square(), 6.0);
}

TEST(triangle_test, center_of_empty){
    Triangle tr1;
    Point p1;
    ASSERT_EQ(tr1.center(), p1);
}

TEST(triangle_test, center){
    Point p1(-2, 0);
    Point p2(2, 0);
    Point p3(0, 3);

    Triangle tr(p1,p2,p3);
    Point prez{0,1};
    ASSERT_EQ(tr.center(), prez );
}

TEST(triangle_test, equality_empty){
    Triangle tr1;
    Triangle tr2;
    ASSERT_TRUE(tr1 == tr2);
}

TEST(triangle_test, equality_1){
    Point p1(-2, 0);
    Point p2(2, 0);
    Point p3(0, 3);

    Triangle tr1(p1,p2,p3);
    Triangle tr2(p2,p1,p3);
    ASSERT_TRUE(tr1 == tr2);
}

TEST(triangle_test, equality_2){
    Point p1(-2, 0);
    Point p2(2, 0);
    Point p3(0, 3);
    Point p4(5, 1);

    Triangle tr1(p1,p3,p2);
    Triangle tr2(p1,p3,p4);
    ASSERT_FALSE(tr1 == tr2);
}

TEST(triangle_test, assignment_empty){
    Triangle tr1;
    Triangle tr2;
    tr1 = tr2;
    ASSERT_TRUE(tr1 == tr2);
}

TEST(triangle_test, assignment){
    Point p1(1, 3);
    Point p2(2, 2);
    Point p3(3, 1);
    
    Triangle tr1;
    Triangle tr2(p1,p2,p3);
    tr1 = tr2;
    ASSERT_TRUE(tr1 == tr2);
}

TEST(triangle_test, assignment1){
    Point p1(1, 3);
    Point p2(2, 2);
    Point p3(3, 1);
    Point p4(1, 1);
    
    Triangle tr1(p1,p3,p4);
    Triangle tr2(p1,p2,p3);
    ASSERT_FALSE(tr1 == tr2);
}

TEST(triangle_test, assignment_move_empty){
    Triangle tr1;
    Triangle tr2;
    tr1 = std::move(tr2);
    ASSERT_TRUE(tr1 == tr2);
}

TEST(triangle_test, assignment_move){
    Point p1(1, 3);
    Point p2(2, 2);
    Point p3(3, 1);
    
    Triangle tr1;
    Triangle tr2(p1,p2,p3);
    tr1 = std::move(tr2);
    ASSERT_TRUE(tr1 == tr2);
}

TEST(triangle_test, operator_double) {
    Point p1(1, 3);
    Point p2(2, 2);
    Point p3(3, 1);
    
    Triangle tr1(p1,p2,p3);
    ASSERT_DOUBLE_EQ(static_cast<double>(tr1), tr1.square());
}

TEST(triangle_test, input_error) {
    std::stringstream input("1 3\n2 2\n3 1");

    Triangle tr1;
    ASSERT_THROW(input >> tr1, std::logic_error);
}

TEST(triangle_test, input1) {
    Point p1(1, 3);
    Point p2(2, 2);
    Point p3(3, 1);
    Triangle tr1(p1,p2,p3);
    std::stringstream input("1 3\n3 1\n-1 0");

    Triangle tr2;
    input >> tr2;
    ASSERT_FALSE(tr1 == tr2);
}

TEST(triangle_test, input_excp) {
    std::stringstream input("1 3\n3 1\n e 0");

    Triangle tr2;
    ASSERT_THROW(input >> tr2, std::invalid_argument);
}

TEST(triangle_test, input_excp1) {
    std::stringstream input("1 3\n3 1\n 3 1");

    Triangle tr2;
    ASSERT_THROW(input >> tr2, std::logic_error);
}

TEST(triangle_test, output) {
    Point p1(1, 3);
    Point p2(2, 2);
    Point p3(3, 1);
    Triangle tr1(p1, p2, p3);

    std::ostringstream os;
    os << tr1;
    std::string output = "Triangle's coordinates:\n"
                         "(x: 1; y: 3)\n"
                         "(x: 2; y: 2)\n"
                         "(x: 3; y: 1)\n";
    ASSERT_EQ(os.str(), output);
}

TEST(triangle_test, output1) {
    Triangle tr1;

    std::ostringstream os;
    os << tr1;
    std::string output = "Triangle's coordinates:\n"
                         "(x: 0; y: 0)\n"
                         "(x: 0; y: 0)\n"
                         "(x: 0; y: 0)\n";
    ASSERT_EQ(os.str(), output);
}

//--------------------------------

TEST(octagon_test, square_of_empty){
    Octagon tr;
    ASSERT_EQ(tr.square(), 0.0);
}

TEST(octagon_test, square){
    Point p1(0, 0);
    Point p2(1, 0);
    Point p3(1.5, sqrt(2));
    Point p4(1, sqrt(2) + 1);
    Point p5(0, sqrt(2) + 1);
    Point p6(-0.5, sqrt(2));
    Point p7(-1, 0);
    Point p8(-0.5, -sqrt(2));

    Octagon oct(p1, p2, p3, p4, p5, p6, p7, p8);
    ASSERT_NEAR(oct.square(), 2.38018, 0.00001);
}

TEST(octagon_test, center_of_empty){
    Octagon tr1;
    Point p1;
    ASSERT_EQ(tr1.center(), p1);
}

TEST(octagon_test, center) {
    Point p1(0, 0);
    Point p2(1, 0);
    Point p3(1.5, sqrt(2));
    Point p4(1, sqrt(2) + 1);
    Point p5(0, sqrt(2) + 1);
    Point p6(-0.5, sqrt(2));
    Point p7(-1, 0);
    Point p8(-0.5, -sqrt(2));

    Octagon oct(p1, p2, p3, p4, p5, p6, p7, p8);
    Point prez{0.1875, 0.78033};
    
    ASSERT_NEAR(oct.center().m_x, prez.m_x, 0.00001);
    ASSERT_NEAR(oct.center().m_y, prez.m_y, 0.00001);
}

TEST(octagon_test, equality_empty){
    Octagon tr1;
    Octagon tr2;
    ASSERT_TRUE(tr1 == tr2);
}

TEST(octagon_test, equality_1){
    Point p1(0, 0);
    Point p2(1, 0);
    Point p3(1.5, sqrt(2));
    Point p4(1, sqrt(2) + 1);
    Point p5(0, sqrt(2) + 1);
    Point p6(-0.5, sqrt(2));
    Point p7(-1, 0);
    Point p8(-0.5, -sqrt(2));
    Point p9(5, 1);

    Octagon tr1(p1,p3,p2,p4,p5,p6,p7,p8);
    Octagon tr2(p2,p1,p3,p8,p4,p5,p6,p9);
    ASSERT_FALSE(tr1 == tr2);
}

TEST(octagon_test, assignment_empty){
    Octagon tr1;
    Octagon tr2;
    tr1 = tr2;
    ASSERT_TRUE(tr1 == tr2);
}

TEST(octagon_test, assignment){
    Point p1(0, 0);
    Point p2(1, 0);
    Point p3(1.5, sqrt(2));
    Point p4(1, sqrt(2) + 1);
    Point p5(0, sqrt(2) + 1);
    Point p6(-0.5, sqrt(2));
    Point p7(-1, 0);
    Point p8(-0.5, -sqrt(2));
    
    Octagon tr1;
    Octagon tr2(p2,p1,p3,p8,p4,p5,p6,p7);
    tr1 = tr2;
    ASSERT_TRUE(tr1 == tr2);
}


TEST(octagon_test, assignment_move_empty){
    Octagon tr1;
    Octagon tr2;
    tr1 = std::move(tr2);
    ASSERT_TRUE(tr1 == tr2);
}

TEST(octagon_test, assignment_move){
    Point p1(0, 0);
    Point p2(1, 0);
    Point p3(1.5, 2);
    Point p4(1, 1.2 + 1);
    Point p5(0, 1.2 + 1);
    Point p6(-0.5, 1.2);
    Point p7(-1, 0);
    Point p8(-0.5, -1.2);
    
    Octagon tr1;
    Octagon tr2(p2,p1,p3,p8,p4,p5,p6,p7);
    tr1 = std::move(tr2);
    ASSERT_TRUE(tr1 == tr2);
}

TEST(octagon_test, operator_double) {
    Point p1(0, 0);
    Point p2(1, 0);
    Point p3(1.5, sqrt(2));
    Point p4(1, sqrt(2) + 1);
    Point p5(0, sqrt(2) + 1);
    Point p6(-0.5, sqrt(2));
    Point p7(-1, 0);
    Point p8(-0.5, -sqrt(2));

    Octagon oct(p1, p2, p3, p4, p5, p6, p7, p8);
    ASSERT_NEAR(static_cast<double>(oct), oct.square(), 0.00001);
}

TEST(octagon_test, input) {
    Point p1(1, 8);
    Point p2(2, 7);
    Point p3(3, 6);
    Point p4(4, 5);
    Point p5(5, 4);
    Point p6(6, 3);
    Point p7(7, 2);
    Point p8(8, 1);

    Octagon tr1(p1,p2,p3,p4,p5,p6,p7,p8);

    std::stringstream input("1 8\n2 7\n3 6\n4 5\n"
                            "5 4\n6 3\n7 2\n8 1");

    Octagon tr2;
    input >> tr2;
    ASSERT_TRUE(tr1 == tr2);
}

TEST(octagon_test, input1) {
    Point p1(1, 8);
    Point p2(2, 7);
    Point p3(3, 6);
    Point p4(4, 5);
    Point p5(5, 4);
    Point p6(6, 3);
    Point p7(7, 2);
    Point p8(8, 1);

    Octagon tr1(p1,p2,p3,p4,p5,p6,p7,p8);

    std::stringstream input("1 8\n8 1\n2 7\n"
                            "7 2\n3 6\n6 3\n"
                            "4 5\n5 0\n");

    Octagon tr2;
    input >> tr2;
    ASSERT_FALSE(tr1 == tr2);
}

TEST(octagon_test, input_excp) {
    std::stringstream input("1 8\n8 1\n2 7\n"
                            "7 2\n3 6\n6 3\n"
                            "4 5\n5 e\n");

    Octagon tr2;
    ASSERT_THROW(input >> tr2, std::invalid_argument);
}

TEST(octagon_test, input_excp1) {
    std::stringstream input("1 8\n8 1\n2 7\n"
                            "7 2\n3 6\n6 3\n"
                            "4 5\n4 5\n");

    Octagon tr2;
    ASSERT_THROW(input >> tr2, std::logic_error);
}

TEST(octagon_test, output) {
    Point p1(0, 0);
    Point p2(1, 0);
    Point p3(1.5, sqrt(2));
    Point p4(1, sqrt(2) + 1);
    Point p5(0, sqrt(2) + 1);
    Point p6(-0.5, sqrt(2));
    Point p7(-1, 0);
    Point p8(-0.5, -sqrt(2));
    Octagon tr1(p1,p2,p3,p4,p5,p6,p7,p8);

    std::ostringstream os;
    os << tr1;
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

TEST(octagon_test, output1) {
    Octagon tr1;

    std::ostringstream os;
    os << tr1;
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

//----------------------------

TEST(square_test, area_of_empty){
    Square sq;
    ASSERT_EQ(sq.square(), 0.0);
}

TEST(square_test, area){
    Point p1(0,0);
    Point p2(0,2);
    Point p3(2,2);
    Point p4(2,0);

    Square sq(p1,p2,p3,p4);
    ASSERT_EQ(sq.square(), 4.0);
}

TEST(square_test, center_of_empty){
    Square sq;
    Point p;
    ASSERT_EQ(sq.center(), p);
}

TEST(square_test, center){
    Point p1(0,0);
    Point p2(0,2);
    Point p3(2,2);
    Point p4(2,0);

    Square sq(p1,p2,p3,p4);
    ASSERT_EQ(sq.center().m_x, 1.0);
    ASSERT_EQ(sq.center().m_y, 1.0);
}

TEST(square_test, equality_empty){
    Square sq1, sq2;
    ASSERT_TRUE(sq1 == sq2);
}

TEST(square_test, equality_1){
    Point p1(0,0);
    Point p2(0,2);
    Point p3(2,2);
    Point p4(2,0);

    Square sq1(p1,p2,p3,p4);
    Square sq2(p3,p4,p1,p2);
    ASSERT_TRUE(sq1 == sq2);
}

TEST(square_test, equality_2){
    Point p1(0,0);
    Point p2(0,2);
    Point p3(2,2);
    Point p4(2,0);

    Square sq1(p1,p2,p3,p4);
    Square sq2(p1,p3,p2,p4);
    ASSERT_FALSE(sq1 == sq2);
}

TEST(square_test, assignment_empty){
    Square sq1, sq2;
    sq2 = sq1;
    ASSERT_TRUE(sq1 == sq2);
}

TEST(square_test, assignment){
    Point p1(0,0);
    Point p2(0,2);
    Point p3(2,2);
    Point p4(2,0);
    Square sq1;
    Square sq2(p1,p2,p3,p4);
    sq1 = sq2;
    ASSERT_TRUE(sq1 == sq2);
}

TEST(square_test, assignment_move_empty){
    Square sq1, sq2;
    sq1 = std::move(sq2);
    ASSERT_TRUE(sq1 == sq2);

}

TEST(square_test, assignment_move){
    Point p1(0,0);
    Point p2(0,2);
    Point p3(2,2);
    Point p4(2,0);

    Square sq1;
    Square sq2(p1,p2,p3,p4);
    sq1 = std::move(sq2);
    ASSERT_TRUE(sq1 == sq2);
}

TEST(square_test, operator_double){
    Point p1(0,0);
    Point p2(0,2);
    Point p3(2,2);
    Point p4(2,0);

    Square sq1(p1,p2,p3,p4);
    ASSERT_EQ(static_cast<double>(sq1), sq1.square());
}

TEST(square_test, input){
    Point p1(0,0);
    Point p2(0,2);
    Point p3(2,2);
    Point p4(2,0);

    Square sq1(p1,p2,p3,p4);
    std::stringstream input("0 0\n0 2\n2 2\n2 0");
    Square sq2;
    input >> sq2;
    ASSERT_TRUE(sq1 == sq2);
}

TEST(square_test, input1){
    Point p1(0,0);
    Point p2(0,2);
    Point p3(2,2);
    Point p4(2,0);

    Square sq1(p1,p2,p3,p4);
    std::stringstream input("0 1\n1 1\n1 0\n0 0");
    Square sq2;
    input >> sq2;
    ASSERT_FALSE(sq1 == sq2);
}

TEST(square_test, input_error){
    std::stringstream input("0 2\n2 2\n2 0\n0 e");
    Square sq1;
    ASSERT_THROW(input >> sq1, std::invalid_argument);
}

TEST(square_test, input_error2){
    std::stringstream input("0 2\n2 2\n2 0\n0 6");
    Square sq1;
    ASSERT_THROW(input >> sq1, std::logic_error);
}

TEST(square_test, output){
    Point p1(0,0);
    Point p2(0,2);
    Point p3(2,2);
    Point p4(2,0);

    Square sq1(p1,p2,p3,p4);

    std::ostringstream os;
    os << sq1;
    std::string output = "Square's coordinates:\n"
                         "(x: 0; y: 0)\n"
                         "(x: 0; y: 2)\n"
                         "(x: 2; y: 2)\n"
                         "(x: 2; y: 0)\n";
    ASSERT_EQ(os.str(), output);
}
