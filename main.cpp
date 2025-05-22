#include <iostream>
#include <vector>
#include <algorithm>
#include "analysis.h"

using namespace std;

int main()
{
    string transmission1 = readFileContent("a00836416_actint/mcode1.txt");
    string transmission2 = readFileContent("a00836416_actint/mcode2.txt");
    vector<string> mcodes = {
        readFileContent("a00836416_actint/mcode1.txt"),
        readFileContent("a00836416_actint/mcode2.txt"),
        readFileContent("a00836416_actint/mcode3.txt")};

    cout << "Parte 1:" << endl;
    for (int i = 0; i < 3; i++)
    {
        auto result1 = containsPattern(transmission1, mcodes[i]);
        cout << (result1.first ? "true " + to_string(result1.second) : "false") << endl;
    }
    for (int i = 0; i < 3; i++)
    {
        auto result2 = containsPattern(transmission2, mcodes[i]);
        cout << (result2.first ? "true " + to_string(result2.second) : "false") << endl;
    }

    cout << "Parte 2:" << endl;
    auto palindrome1 = longestPalindrome(transmission1);
    auto palindrome2 = longestPalindrome(transmission2);

    string palindrome1_text = transmission1.substr(palindrome1.first - 1, palindrome1.second - palindrome1.first + 1);
    palindrome1_text.erase(remove(palindrome1_text.begin(), palindrome1_text.end(), '\n'), palindrome1_text.end());
    cout << palindrome1.first << " " << palindrome1.second << " " << palindrome1_text << endl;

    string palindrome2_text = transmission2.substr(palindrome2.first - 1, palindrome2.second - palindrome2.first + 1);
    palindrome2_text.erase(remove(palindrome2_text.begin(), palindrome2_text.end(), '\n'), palindrome2_text.end());
    cout << palindrome2.first << " " << palindrome2.second << " " << palindrome2_text << endl;

    cout << "Parte 3:" << endl;
    auto commonSubstring = longestCommonSubstring(transmission1, transmission2);

    string common_text = transmission1.substr(commonSubstring.first - 1, commonSubstring.second - commonSubstring.first + 1);
    common_text.erase(remove(common_text.begin(), common_text.end(), '\n'), common_text.end());
    cout << commonSubstring.first << " " << commonSubstring.second << " " << common_text << endl;

    return 0;
}
