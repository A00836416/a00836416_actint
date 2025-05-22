#include <gtest/gtest.h>
#include "analysis.h"

TEST(PatternTest, Found)
{
    std::string text = "abcdef";
    std::string pattern = "cde";
    auto result = containsPattern(text, pattern);
    EXPECT_TRUE(result.first);
    EXPECT_EQ(result.second, 3);
}

TEST(PatternTest, NotFound)
{
    std::string text = "abcdef";
    std::string pattern = "xyz";
    auto result = containsPattern(text, pattern);
    EXPECT_FALSE(result.first);
    EXPECT_EQ(result.second, 0);
}

TEST(PalindromeTest, BasicOdd)
{
    std::string text = "racecar";
    auto result = longestPalindrome(text);
    EXPECT_EQ(result.first, 1);
    EXPECT_EQ(result.second, 7);
}

TEST(PalindromeTest, BasicEven)
{
    std::string text = "abccba";
    auto result = longestPalindrome(text);
    EXPECT_EQ(result.first, 1);
    EXPECT_EQ(result.second, 6);
}

TEST(CommonSubstringTest, HasCommon)
{
    std::string a = "abcde";
    std::string b = "cdefg";
    auto result = longestCommonSubstring(a, b);
    EXPECT_EQ(result.first, 3);
    EXPECT_EQ(result.second, 5);
}
