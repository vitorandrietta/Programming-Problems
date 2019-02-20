#include <iostream>
#include <string>
#include <vector>

using std::string;
using std::min;
using std::vector;

/*recursive solution without memorization O(3)*/
unsigned int editDistance(string &from, string &to, unsigned int fromlstIdx, unsigned int toLstIdx) {

    //if the first string is over
    if (fromlstIdx == 0)
        //we need to add toLstIndx characters
        return toLstIdx + 1;
    //if the second string is over
    if (toLstIdx == 0)
        //we need to delete fromlstIdx characters
        return fromlstIdx + 1;
    //if the character is the same, we dont need to make a change
    unsigned int cost = 1;
    if (from[fromlstIdx] == to[toLstIdx]) {
        cost = 0;
    }

    unsigned int withReplace = editDistance(from, to, fromlstIdx - 1, toLstIdx - 1) + cost;
    unsigned int withAdd = editDistance(from, to, fromlstIdx, toLstIdx - 1) + 1;
    unsigned int withDelete = editDistance(from, to, fromlstIdx - 1, toLstIdx) + 1;


    return min(min(withReplace, withDelete), withAdd);

}

/*O(NM), N = len(from), M = len(to)*/
unsigned int topDownEditDistance(string &from, string &to) {
    /*we only need the previous line to compute the current*/
    unsigned int toSize = to.size(), fromSize = from.size();
    /*i know that with this initialization all my cells will be = 0*/
    vector<vector<unsigned int>> topDownTable(from.size(), vector<unsigned int>(to.size()));

    for (unsigned int i = 0; i < fromSize; ++i) {
        topDownTable[i][0] = i;
    }

    for (unsigned int j = 0; j < toSize; ++j) {
        topDownTable[0][j] = j;
    }

    for (unsigned int i = 1; i < fromSize; ++i) {
        for (unsigned int j = 1; j < toSize; ++j) {
            unsigned  int cost = 1;
            if (from[i - 1] == to[j - 1]){
                cost = 0;
            }

            unsigned int withReplace = topDownTable[i-1][j-1] + cost;
            unsigned int withAdd = topDownTable[i][j-1] + 1;
            unsigned int withDelete = topDownTable[i-1][j] + 1;

            topDownTable[i][j] = min(min(withAdd,withReplace),withDelete);
        }
    }

    return topDownTable[fromSize - 1][toSize -1];
}

int main() {
    string from = "kitten", to = "sitting";
    std::cout << "the number of necessary edits to turn '" << from << "' into '" << to << "' is:" << std::endl;
    std::cout << topDownEditDistance(from, to) << std::endl;
    return 0;
}