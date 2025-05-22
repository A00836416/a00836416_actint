#include "analysis.h"
#include <fstream>
#include <iostream>
#include <algorithm>

using namespace std;

string readFileContent(const string &filename)
{
    ifstream file(filename);
    if (!file)
    {
        cerr << "Error al abrir el archivo: " << filename << endl;
        exit(1);
    }
    return string((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
}

pair<bool, size_t> containsPattern(const string &text, const string &pattern)
{
    size_t pos = text.find(pattern);
    return (pos != string::npos) ? make_pair(true, pos + 1) : make_pair(false, static_cast<size_t>(0));
}

pair<int, int> longestPalindrome(const string &text)
{
    int n = text.size();
    if (n == 0)
        return {1, 1};

    int maxLen = 1, start = 0;
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; (i - j >= 0) && (i + j < n) && (text[i - j] == text[i + j]); ++j)
        {
            if (2 * j + 1 > maxLen)
            {
                maxLen = 2 * j + 1;
                start = i - j;
            }
        }
        for (int j = 0; (i - j >= 0) && (i + j + 1 < n) && (text[i - j] == text[i + j + 1]); ++j)
        {
            if (2 * j + 2 > maxLen)
            {
                maxLen = 2 * j + 2;
                start = i - j;
            }
        }
    }
    return {start + 1, start + maxLen};
}

pair<int, int> longestCommonSubstring(const string &text1, const string &text2)
{
    int m = text1.size(), n = text2.size();
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
    int maxLen = 0, endIdx = 0;

    for (int i = 1; i <= m; ++i)
    {
        for (int j = 1; j <= n; ++j)
        {
            if (text1[i - 1] == text2[j - 1])
            {
                dp[i][j] = dp[i - 1][j - 1] + 1;
                if (dp[i][j] > maxLen)
                {
                    maxLen = dp[i][j];
                    endIdx = i;
                }
            }
        }
    }
    return {endIdx - maxLen + 1, endIdx};
}
