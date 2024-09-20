#include <gtest/gtest.h>
#include "exchanger.h"

TEST(test_01, basic_test_set)
{
    std::string input = "abbaba";
    std::string output = "baabab";
    std::string result = exchanger(input);
    ASSERT_TRUE(result == output);
}

TEST(test_02, basic_test_set)
{
    std::string input = "bbcabaca";
    std::string output = "aacbabcb";
    std::string result = exchanger(input);
    ASSERT_TRUE(result == output);
}

TEST(test_03, basic_test_set)
{
    std::string input = "aabcdab";
    std::string output = "\nОшибка: строка содержит недопустимый символ. Используйте только a, b и c.";
    std::string result = exchanger(input);
    ASSERT_TRUE(result == output);
}

TEST(test_04, basic_test_set)
{
    std::string input = "";
    std::string output = "\nОшибка: Введена пустая строка.";
    std::string result = exchanger(input);
    ASSERT_TRUE(result == output);
}

TEST(test_05, basic_test_set)
{
    std::string input = "aBBcACbAA";
    std::string output = "bAAcBCaBB";
    std::string result = exchanger(input);
    ASSERT_TRUE(result == output);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}