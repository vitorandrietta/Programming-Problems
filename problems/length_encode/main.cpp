#include <iostream>
#include <list>
#include <string>
#include <stdlib.h>
using std::string;




string lengthEncode(string s){
    unsigned int currentPos = 0;
    unsigned int strSize = s.size();
    string result;
    while( currentPos < strSize){
        char current;
        unsigned int occurrences = 0;
        for(current = s[currentPos]; currentPos < strSize && current == s[currentPos]; ++currentPos, ++occurrences);
        result.push_back(current);
        result.append(std::to_string(occurrences));
    }

    return result;
}


int main() {
    string plainString = "AAAABBBCCDAA";
    string encodedString = lengthEncode(plainString);
    for(auto&str : encodedString){
        std::cout << str ;
    }

    std::cout << std::endl;
    return 0;
}