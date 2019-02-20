#include <iostream>
#include <string>
#include <vector>
#include <cstring>


using std::vector;

/*we can solve this problem with dynamic programming tool
 *
 * let s be the string which we want to turn into a palindrome word
 * let L be the number of characters in s
 * let I be the start of the sub-word being analyzed.
 * let M[I,L] be the minimum number of letters, which we need add for s[I..L] be palindrome
 *
 * we have 3 cases to cover:
 *
 * 1st - s[I] == s[L] , then M[I,L] = M[I+1,L-1]
 * 2nd - s[I] != s[L], then M[I,L] = min(M[I+1,L],M[I,L-1])+1
 * 3rd - I >= L then M[I,L] = 0
 *  *
 * */

/*O(N²), N = len(s)*/
std::string toPalindrome(const std::string s) {
    unsigned int wordLength = s.length();
    vector<vector<unsigned int>> topDownMatrix(wordLength, vector<unsigned int>(wordLength));
    for (unsigned int l = 0; l < wordLength; ++l) {
        for (unsigned int c = 0; c < wordLength; ++c) {
            topDownMatrix[l][c] = 0u;
        }
    }


    for (unsigned int diag = 1; diag < wordLength; ++diag) {
        for (unsigned int l = 0, c = diag; c < wordLength; ++l, ++c) {
            if (s[l] == s[c]) {
                topDownMatrix[l][c] = topDownMatrix[l + 1][c - 1];
            } else {
                topDownMatrix[l][c] = std::min(topDownMatrix[l + 1][c], topDownMatrix[l][c - 1]) + 1;
            }
        }
    }


    {
        std::string result;
        result = s;
        unsigned int l = 0, c = wordLength-1;
        while (c > l) {
            if (topDownMatrix[l][c] == topDownMatrix[l + 1][c - 1]) {
                --c;
                ++l;
            } else {
                if (topDownMatrix[l + 1][c] == topDownMatrix[l][c - 1]) {
                    if (s[l] > s[c]) {
                        result.insert(result.begin() + l, s[c]);
                        --c;
                    } else {
                        result.insert(result.end() - c, s[l]);
                        ++l;
                    }
                } else {
                    if (topDownMatrix[l + 1][c] < topDownMatrix[l][c - 1]) {
                        result.insert(result.end() - c, s[l]);
                        ++l;
                    } else {
                        result.insert(result.begin() + l, s[c]);
                        --c;
                    }
                }
            }

        }

        return result;
    }


}


int main() {
    const std::string testCase{"google"};
    std::string result = toPalindrome(testCase);
    std::cout << result << std::endl;
    return 0;
}