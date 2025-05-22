#include <gtest/gtest.h>
#include <fstream>
#include "analysis.h"

TEST(PatternTest, Found)
{
    std::string text = "abcdef";
    std::string pattern = "cde";
    auto result = contains_pattern(text, pattern);
    EXPECT_TRUE(result.first);
    EXPECT_EQ(result.second, 3);
}

TEST(PatternTest, NotFound)
{
    std::string text = "abcdef";
    std::string pattern = "xyz";
    auto result = contains_pattern(text, pattern);
    EXPECT_FALSE(result.first);
    EXPECT_EQ(result.second, 0);
}

TEST(PalindromeTest, BasicOdd)
{
    std::string text = "racecar";
    auto result = longest_palindrome(text);
    EXPECT_EQ(result.first, 1);
    EXPECT_EQ(result.second, 7);
}

TEST(PalindromeTest, BasicEven)
{
    std::string text = "abccba";
    auto result = longest_palindrome(text);
    EXPECT_EQ(result.first, 1);
    EXPECT_EQ(result.second, 6);
}

TEST(CommonSubstringTest, HasCommon)
{
    std::string a = "abcde";
    std::string b = "cdefg";
    auto result = longest_common_substring(a, b);
    EXPECT_EQ(result.first, 3);
    EXPECT_EQ(result.second, 5);
}

TEST(FileReaderTest, ReadsCorrectContent)
{
    const std::string filename = "test_file.txt";
    const std::string expected_content = "Hola mundo\nEsta es una prueba.";
    std::ofstream test_file(filename);
    ASSERT_TRUE(test_file.is_open());
    test_file << expected_content;
    test_file.close();
    std::string result = read_file_content(filename);
    EXPECT_EQ(result, expected_content);
    std::remove(filename.c_str());
}

TEST(FileReaderTest, ThrowsIfFileNotFound)
{
    try
    {
        read_file_content("nope.txt");
        FAIL();
    }
    catch (const std::runtime_error &)
    {
        SUCCEED();
    }
}

TEST(PalindromeTest, EmptyString)
{
    std::string text = "";
    auto result = longest_palindrome(text);
    EXPECT_EQ(result.first, 1);
    EXPECT_EQ(result.second, 1);
}

TEST(CommonSubstringTest, FullMatch)
{
    std::string a = "abcdef";
    std::string b = "abcdef";
    auto result = longest_common_substring(a, b);
    EXPECT_EQ(result.first, 1);
    EXPECT_EQ(result.second, 6);
}

TEST(CommonSubstringTest, UnequalLength)
{
    std::string a = "abc";
    std::string b = "abcdefg";
    auto result = longest_common_substring(a, b);
    EXPECT_EQ(result.first, 1);
    EXPECT_EQ(result.second, 3);
}
