#include <iostream>
#include <set>
#include <math.h>

using std::set;

/*O(N*2^N)
 * */
void allPowerSets(const std::set<int> &s) {
    const unsigned int setSize = s.size();
    const unsigned long int nSubsets = pow(2, setSize);
    std::cout << "{ " << std::flush;
    for (unsigned long int currentSet = 0; currentSet < nSubsets; ++currentSet) {
        std::cout << "{" << std::flush;
        std::set<int>::iterator setIt = s.begin();

        for (unsigned int n = 0; n < setSize; ++n, ++setIt) {
            if (1 << n & currentSet) {
                std::cout << *setIt << " " << std::flush;
            }
        }

        std::cout << "}" << std::flush;
    }

    std::cout << "}" << std::flush;
}

int main() {
    std::set<int> testSet{1, 2, 3};
    allPowerSets(testSet);
    return 0;
}