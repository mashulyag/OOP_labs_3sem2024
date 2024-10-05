#include "../include/solution.h"
#include "gtest/gtest.h"
#include <iostream>

// Тест конструктора по умолчанию
TEST(FourTest, DefaultConstructor) {
    Four four;
    ASSERT_EQ(four.getSize(), 1);
    ASSERT_EQ(four.toString(), "0");
}

// Тест конструктора с параметрами (size_t, unsigned char)
TEST(FourTest, SizeTConstructor) {
    Four four(5, 2);
    ASSERT_EQ(four.getSize(), 5);
    ASSERT_EQ(four.toString(), "22222");
}

// Тест конструктора с initializer_list
TEST(FourTest, InitializerListConstructor) {
    Four four({1, 2, 3});
    ASSERT_EQ(four.getSize(), 3);
    ASSERT_EQ(four.toString(), "321");
}

// Тест конструктора с std::string
TEST(FourTest, StringConstructor) {
    Four four("123");
    ASSERT_EQ(four.getSize(), 3);
    ASSERT_EQ(four.toString(), "321");
}

// Тест оператора копирования
TEST(FourTest, CopyConstructor) {
    Four four1("123");
    Four four2(four1);
    ASSERT_EQ(four2.getSize(), 3);
    ASSERT_EQ(four2.toString(), "321");
}

// Тест оператора присваивания копированием
TEST(FourTest, CopyAssignment) {
    Four four1("123");
    Four four2;
    four2 = four1;
    ASSERT_EQ(four2.getSize(), 3);
    ASSERT_EQ(four2.toString(), "321");
}

// Тест оператора сложения
TEST(FourTest, Addition) {
    Four four1("23");
    Four four2("03");
    Four result = four1 + four2;
    ASSERT_EQ(result.toString(), "26");
}

// Тест оператора вычитания
TEST(FourTest, Subtraction) {
    Four four1("23");
    Four four2("03");
    Four result = four1 - four2;
    ASSERT_EQ(result.toString(), "20");
}

// Тест оператора сравнения равенства
TEST(FourTest, Equality) {
    Four four1("123");
    Four four2("123");
    ASSERT_TRUE(four1 == four2);
}

// Тест оператора сравнения неравенства
TEST(FourTest, Inequality) {
    Four four1("123");
    Four four2("03");
    ASSERT_TRUE(four1 != four2);
}

// Тест оператора сравнения меньше
TEST(FourTest, LessThan) {
    Four four1("123");
    Four four2("124");
    ASSERT_TRUE(four1 < four2);
}

// Тест оператора сравнения больше
TEST(FourTest, GreaterThan) {
    Four four1("124");
    Four four2("123");
    ASSERT_TRUE(four1 > four2);
}

// Тест оператора сравнения меньше или равно
TEST(FourTest, LessThanOrEqual) {
    Four four1("123");
    Four four2("123");
    ASSERT_TRUE(four1 <= four2);
}

// Тест оператора сравнения больше или равно
TEST(FourTest, GreaterThanOrEqual) {
    Four four1("123");
    Four four2("123");
    ASSERT_TRUE(four1 >= four2);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
