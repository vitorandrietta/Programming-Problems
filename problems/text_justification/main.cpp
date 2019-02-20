#include <iostream>
#include <list>
#include <string>
#include <vector>
#include <sstream>
#include <iterator>

using std::list;
using std::string;
using std::vector;

/*by aggregate analysis you can see that this solution runs in O(n+k), being n the number of
  * words in the parameter and k the charsPerLine, we avoid going through the list every time by saving the iterator*/
list<string> justifyText(list<string> &words, unsigned int charsPerLine) {
    const string empty_space = " ";
    unsigned int const nWords = words.size();
    vector<list<string>::iterator> spaceIterators(charsPerLine);
    list<string> result;
    list<string>::iterator wordBeingInserted = words.begin();
    for (unsigned int wordCount = 0; wordCount < nWords;) {
        unsigned int wordsInLine = 0, charsInLine = 0;
        list<string> currentLine;
        while (charsInLine < charsPerLine && wordCount < nWords) {


            int additionalSpace = charsInLine > 0 ? 1 : 0;
            string currentWord = (*wordBeingInserted);
            if (charsInLine + additionalSpace + currentWord.size() <= charsPerLine) {

                if (charsInLine != 0) {
                    currentLine.emplace_back(empty_space);
                    spaceIterators[wordsInLine - 1] = currentLine.end();
                    --spaceIterators[wordsInLine - 1];
                }
                currentLine.emplace_back(currentWord);
                charsInLine += additionalSpace + currentWord.size();

                ++wordBeingInserted;
                ++wordCount;
                ++wordsInLine;
            } else {
                break;
            }
        }

        if (wordsInLine == 1) {
            spaceIterators[0] = currentLine.end();
            spaceIterators[0]--;
        }
        while (charsInLine < charsPerLine) {
            for (unsigned spacePos = 0; spacePos < wordsInLine-1 && charsInLine < charsPerLine; ++spacePos) {
                currentLine.insert(spaceIterators[spacePos], empty_space);
                ++charsInLine;
            }
        }

        std::ostringstream stream;
        std::copy(currentLine.begin(), currentLine.end(), std::ostream_iterator<string>(stream));
        result.emplace_back(stream.str());
    }

    return result;
}

int main() {
    list<string> text{"the", "quick", "brown", "fox", "jumps", "over", "the", "lazy", "dog"};
    list<string> result = justifyText(text, 16u);
    for (auto &str:result) {
        std::cout << str << std::endl;
    }
    return 0;
}