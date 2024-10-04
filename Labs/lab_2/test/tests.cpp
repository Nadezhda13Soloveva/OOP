#include <gtest/gtest.h>
#include "five.h"
#include <sstream>

TEST(FiveTest, DefaultConstructor) {
    Five num;

    std::string output = num.toString();
    std::string result = "";

    ASSERT_TRUE(output == result);
}

TEST(FiveTest, SizeConstructor) {
    Five num(5, 3);

    std::string output = num.toString();
    std::string result = "33333";  

    ASSERT_TRUE(output == result);
}

TEST(FiveTest, InvalidSizeConstructor) {
    ASSERT_THROW(Five(5, 5), std::invalid_argument);
}

TEST(FiveTest, InitializerListConstructor) {
    Five num{1, 2, 3, 4};

    std::string output = num.toString();
    std::string result = "4321";  

    ASSERT_TRUE(output == result);
}

TEST(FiveTest, InvalidInitializerListConstructor) {
    ASSERT_THROW(Five({1, 5, 3}), std::invalid_argument);
}

TEST(FiveTest, StringConstructor) {
    Five num("4321");

    std::string output = num.toString();
    std::string result = "4321";  

    ASSERT_TRUE(output == result);
}

TEST(FiveTest, InvalidStringConstructor) {
    ASSERT_THROW(Five("5321"), std::invalid_argument);
}

TEST(FiveTest, CopyConstructor) {
    Five num1("4321");
    Five num2(num1);

    std::string output = num2.toString();
    std::string result = "4321";  

    ASSERT_TRUE(output == result);
}

TEST(FiveTest, MoveConstructor) {
    Five num1("4321");
    Five num2(std::move(num1));

    std::string output1 = num2.toString();
    std::string output2 = num1.toString();

    std::string result1 = "4321";
    std::string result2 = "";

    ASSERT_TRUE(output1 == result1 && output2 == result2);
}

TEST(FiveTest, AssignmentOperator) {
    Five num1("4321");
    Five num2;

    num2 = num1;
    std::string output = num2.toString();
    std::string result = num1.toString();

    ASSERT_TRUE(output == result);
}

TEST(FiveTest, MoveAssignmentOperator) {
    Five num1("4321");
    Five num2;

    num2 = std::move(num1);
    std::string output1 = num2.toString();
    std::string output2 = num1.toString();

    std::string result1 = "4321";
    std::string result2 = "";

    ASSERT_TRUE(output1 == result1 && output2 == result2);
}

TEST(FiveTest, AdditionOperator) {
    Five num1("4321");
    Five num2("1234");

    Five num3 = num1 + num2;
    std::string output = num3.toString();
    std::string result = "11110";  

    ASSERT_TRUE(output == result);
}

TEST(FiveTest, SubtractionOperator) {
    Five num1("4321");
    Five num2("1234");

    Five num3 = num1 - num2;
    std::string output = num3.toString();
    std::string result = "3032";  

    ASSERT_TRUE(output == result);
}

TEST(FiveTest, InvalidSubtractionOperator) {
    Five num1("1234");
    Five num2("4321");

    ASSERT_THROW(num1 - num2, std::invalid_argument);
}

TEST(FiveTest, ComparisonOperators) {
    Five num1("4321");
    Five num2("1234");
    Five num3("4321");

    bool output1 = (num1 > num2);
    bool output2 = !(num1 < num2);
    bool output3 = !(num1 == num2);
    bool output4 = (num1 == num3);

    ASSERT_TRUE(output1 && output2 && output3 && output4);
}

TEST(FiveTest, OutputStreamOperator) {
    Five num("4321");
    std::ostringstream oss;

    oss << num;
    std::string output = oss.str();
    std::string result = "4321";

    ASSERT_TRUE(output == result);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
