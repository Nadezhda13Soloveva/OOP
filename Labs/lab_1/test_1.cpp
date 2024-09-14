#include <gtest/gtest.h>
#include "exchanger.h"

TEST(test_01, basic_test_set)
{
    ASSERT_TRUE(exchanger("abbaba")=="baabab");
}

TEST(test_02, basic_test_set)
{
    ASSERT_TRUE(exchanger("bbcabaca")=="aacbabcb");
}

TEST(test_03, basic_test_set)
{
    ASSERT_TRUE(exchanger("aabcdab")=="\nОшибка: строка содержит недопустимый символ. Используйте только a, b и c.");
}

TEST(test_04, basic_test_set)
{
    ASSERT_TRUE(exchanger("")=="\nОшибка: Введена пустая строка.");
}

TEST(test_05, basic_test_set)
{
    ASSERT_TRUE(exchanger("aBBcACbAA")=="bAAcBCaBB");
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}