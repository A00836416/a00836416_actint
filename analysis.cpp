
/*
 * Copyright (C) 2025 Tec de Monterrey
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

/**
 * @file analysis.cpp
 * @brief Implementación de funciones para análisis de texto como búsqueda de patrones, palíndromos y substrings comunes.
 */

#include "analysis.h"
#include <fstream>
#include <iostream>
#include <algorithm>

using namespace std;

string read_file_content(const string &filename)
{
    ifstream file(filename);
    if (!file)
    {
        cerr << "Error al abrir el archivo: " << filename << endl;
        exit(1);
    }
    return string((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
}

pair<bool, size_t> contains_pattern(const string &text, const string &pattern)
{
    size_t pos = text.find(pattern);
    return (pos != string::npos) ? make_pair(true, pos + 1) : make_pair(false, static_cast<size_t>(0));
}

pair<int, int> expand_center(const string &text, int left, int right)
{
    while (left >= 0 && right < text.size() && text[left] == text[right])
    {
        --left;
        ++right;
    }
    return {left + 1, right - 1};
}

pair<int, int> longest_palindrome(const string &text)
{
    if (text.empty())
        return {1, 1};

    int start = 0, end = 0;
    for (int i = 0; i < text.size(); ++i)
    {
        auto [l1, r1] = expand_center(text, i, i);
        auto [l2, r2] = expand_center(text, i, i + 1);

        if (r1 - l1 > end - start)
        {
            start = l1;
            end = r1;
        }
        if (r2 - l2 > end - start)
        {
            start = l2;
            end = r2;
        }
    }
    return {start + 1, end + 1};
}

pair<int, int> longest_common_substring(const string &text1, const string &text2)
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