#include <iostream>
#include <vector>
#include <math.h>

using std::vector;

/*we can use Bellman-Ford algorithm to solve this problem:
 * the answer is yes for the problem if we have a sequence of multiplication of currencies (path) with value
 * greater than 1, it means we can trade from and arrive at the same currency with a greater value
 * if we use BellmanFord using the -log of the value of the exchange rate, we will detect if our graph have a way to
 * obtain profit from a currency (because we know, log(a*b*c) = log(a)+log(b)+log(c)
 * because we will run bellman-ford parting fron each vertex, this will take  O(VEV) = O(N³) being N the number
 * of vertex = |V|
 * */
bool profitByCurrencyExchange(vector<vector<double>> currencyTable) {

    unsigned int numberOfCurrencies = currencyTable.size();
    vector<double> distances(numberOfCurrencies, INT32_MAX);

    /*note that there is no problem in altering currencyTable because it's passe by copy*/
    for (unsigned int l = 0; l < numberOfCurrencies; ++l) {
        for (unsigned int c = 0; c < numberOfCurrencies; ++c) {
            currencyTable[l][c] = -log(currencyTable[l][c]);
        }
    }

    distances[0] = 0;

    for (unsigned int i = 0; i < numberOfCurrencies - 1; ++i) {
        for (unsigned int u = 0; u < numberOfCurrencies ; ++u) {
            for(unsigned int v =0; v <numberOfCurrencies; ++v){
                double weight = currencyTable[u][v];
                if(distances[u] + weight < distances[v]){
                    distances[v] = distances[u] + weight;
                }
            }
        }
    }

    for (unsigned int u = 0; u < numberOfCurrencies ; ++u) {
        for(unsigned int v =0; v <numberOfCurrencies; ++v){
            double weight = currencyTable[u][v];
            if(distances[u] + weight < distances[v]){
                return true;
            }
        }
    }

    return false;

}

int main() {
    vector<vector<double>> currencyTable ;
    //initialize currency table here
    std::cout << "there is a way from obtain profit coming from and returning to a currency ? " << std::endl;
    std::cout << profitByCurrencyExchange(currencyTable) << std::endl;
    return 0;
}