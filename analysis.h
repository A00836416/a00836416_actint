#ifndef ANALYSIS_H
#define ANALYSIS_H

#include <string>
#include <vector>
#include <utility>

std::string readFileContent(const std::string &filename);
std::pair<bool, size_t> containsPattern(const std::string &text, const std::string &pattern);
std::pair<int, int> longestPalindrome(const std::string &text);
std::pair<int, int> longestCommonSubstring(const std::string &text1, const std::string &text2);

#endif
