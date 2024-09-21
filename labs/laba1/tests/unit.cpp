#include <string>
#include "gtest/gtest.h"
#include "../include/solution.h"

TEST(CountVowelsTest, EmptyString) {
    EXPECT_EQ(countVowels(""), 0);
}

TEST(CountVowelsTest, NoVowels) {
    EXPECT_EQ(countVowels("bcd fgh jkl mnp qrs tuv wxz"), 0);
}

TEST(CountVowelsTest, AllVowels) {
    EXPECT_EQ(countVowels("i am mariya"), 6);
}

TEST(CountVowelsTest, MixedString) {
    EXPECT_EQ(countVowels("oop is good"), 5);
}

TEST(CountVowelsTest, SpacesOnly) {
    EXPECT_EQ(countVowels("     "), 0);
}

int main(int argc, char **argv) {
   ::testing::InitGoogleTest(&argc, argv);
   return RUN_ALL_TESTS();
}
