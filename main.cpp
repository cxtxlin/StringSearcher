#include <iostream>
#include <fstream>
#include <vector>
#include <regex>
#include <string>
#include "bi_istream_iterator.h"

int main() {

    std::fstream myFile ("vasile.txt", std::ios::in);

    std::regex theRegExpression("ase");
    std::match_results<bi_istream_iterator<char>> matchResults;
    bi_istream_iterator<char> startIter(myFile, 0);

    while (std::regex_search(
            startIter
            , bi_istream_iterator<char>(myFile)
            , matchResults
            , theRegExpression
        )
    ) {
        for (const auto &item: matchResults)
            std::cout << item << ' ';
        std::cout << std::endl;

        startIter = matchResults.suffix().first;
    }

    return 0;
}
