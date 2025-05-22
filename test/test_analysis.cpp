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
    const std::string filename = "test_read_ok.txt";
    const std::string expected_content = "Contenido válido";
    std::ofstream test_file(filename);
    test_file << expected_content;
    test_file.close();
    std::string result = read_file_content(filename);
    EXPECT_EQ(result, expected_content);
    std::remove(filename.c_str());
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

TEST(CommonSubstringTest, OneEmptyString)
{
    std::string a = "abcde";
    std::string b = "";
    auto result = longest_common_substring(a, b);
    EXPECT_EQ(result.first, 1);
    EXPECT_EQ(result.second, 0);
}

TEST(CommonSubstringTest, BothEmptyStrings)
{
    std::string a = "";
    std::string b = "";
    auto result = longest_common_substring(a, b);
    EXPECT_EQ(result.first, 1);
    EXPECT_EQ(result.second, 0);
}

TEST(CommonSubstringTest, NoCommonSubstring)
{
    std::string a = "abc";
    std::string b = "xyz";
    auto result = longest_common_substring(a, b);
    EXPECT_EQ(result.first, 1);
    EXPECT_EQ(result.second, 0);
}

TEST(CommonSubstringTest, OneStringEmptyMatrixEdgeCase)
{
    std::string a = "abcde";
    std::string b = "";
    auto result = longest_common_substring(a, b);
    EXPECT_EQ(result.first, 1);
    EXPECT_EQ(result.second, 0);
}

TEST(CommonSubstringTest, NoUpdateMaxLen)
{
    std::string a = "abc";
    std::string b = "xyz";
    auto result = longest_common_substring(a, b);
    EXPECT_EQ(result.first, 1);
    EXPECT_EQ(result.second, 0);
}

TEST(CommonSubstringTest, MatchWithoutUpdatingMaxLen)
{
    std::string a = "aaa";
    std::string b = "aa";
    auto result = longest_common_substring(a, b);
    EXPECT_EQ(result.first, 1);
    EXPECT_EQ(result.second, 2);
}

TEST(CommonSubstringTest, EqualLengthNoUpdate)
{
    std::string a = "abcabc";
    std::string b = "abcxyz";
    auto result = longest_common_substring(a, b);
    EXPECT_EQ(result.first, 1);
    EXPECT_EQ(result.second, 3);
}

TEST(CommonSubstringTest, DiagonalDPMatrixUsage)
{
    std::string a = "abcde12345";
    std::string b = "xyz12345uvw";
    auto result = longest_common_substring(a, b);
    EXPECT_EQ(result.first, 6);
    EXPECT_EQ(result.second, 10);
}

TEST(CommonSubstringTest, DiagonalUnequalLength)
{
    std::string a = "abcdef123";
    std::string b = "123";
    auto result = longest_common_substring(a, b);
    EXPECT_EQ(result.first, 7);
    EXPECT_EQ(result.second, 9);
}

TEST(FileReaderTest, ThrowsIfFileNotFound)
{
    try
    {
        read_file_content("archivo_que_no_existe_123.txt");
        FAIL() << "Se esperaba std::runtime_error";
    }
    catch (const std::runtime_error &e)
    {
        std::string msg = e.what();
        EXPECT_NE(msg.find("No se pudo abrir el archivo"), std::string::npos);
    }
    catch (...)
    {
        FAIL() << "Excepción inesperada";
    }
}

TEST(CommonSubstringTest, MatchWithoutUpdatingMaxLenMultipleTimes)
{
    std::string a = "abcabc";
    std::string b = "abcabc";
    auto result = longest_common_substring(a, b);
    EXPECT_EQ(result.first, 1);
    EXPECT_EQ(result.second, 6);
}
