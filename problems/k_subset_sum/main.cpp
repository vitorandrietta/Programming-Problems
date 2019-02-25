#include <iostream>
#include <vector>
#include <list>

using std::vector;
using std::list;

/*the recurrence relation describing this problem can be represented as follows:
 *
 * let S(n,k,A) Be the TRUE if there is a subset of numbers of A with indexes between 1 and n with sums k
 *
 * cases:
 * 1- S(n,k,A) :- n = 1, if A[1] == k then return TRUE
 * 2- S(n,k,A) = if S(n-1,k-A[n],A) is false then return S(n-1,k,A) else return S(n-1,K-A[n],A)

 * */


/*O(2^n) poor solution without memorization and with overlaping problems*/
bool topDownSubsetSumK(const vector<int> &numbers, int k, int n) {
    if (n == 0) {
        if (k == numbers[0]) {
            return true;
        }

        return false;
    }

    return topDownSubsetSumK(numbers, k - numbers[n], n - 1) || topDownSubsetSumK(numbers, k, n - 1);
}

/*Bottom Up Approach with memorization O(nk)*/
list<int> *bottomUpSubsetSumK(const vector<int> &numbers, int k, int n) {
    vector<vector<bool>> bottomUpMatrix(n+1, vector<bool>(k + 1));




    for (unsigned int i = 0; i <= n; ++i) {
        bottomUpMatrix[i][0] = true; //it's always possible to sum 0 (empty set)
    }

    for (unsigned int j = 1; j <= k; ++j) {
        bottomUpMatrix[0][j] = false;
    }

    for (unsigned int i = 1; i <= n; ++i) {
        for (unsigned int j = 1; j <= k; ++j) {
            if (j < numbers[i-1]) {
                bottomUpMatrix[i][j] = bottomUpMatrix[i - 1][j];
            } else {
                bottomUpMatrix[i][j] = bottomUpMatrix[i - 1][j - numbers[i-1]] || bottomUpMatrix[i - 1][j];
            }
        }
    }

    if (!bottomUpMatrix[n][k]) {
        return nullptr;
    }

    list<int> *result = new list<int>();
    for (int i = n , j = k; j >= 1 && i >= 1; --i) {
        if (!(numbers[i-1] > j) && bottomUpMatrix[i - 1][j - numbers[i-1]]) {
            j -= numbers[i-1];
            result->emplace_back(numbers[i-1]);
        }
    }

    return result;
}


int main() {
    vector<int> s{12, 1, 61, 5, 9, 2};
    list<int> *subset;
    subset = bottomUpSubsetSumK(s, 24, s.size());
    if (subset != nullptr) {
        std::cout << "{" << std::flush;
        for (auto item:*subset) {
            std::cout << item << "," << std::flush;
        }
        std::cout << "}" << std::flush;
        delete subset;
    } else {
        std::cout << "null" << std::flush;
    }

    return 0;
}
