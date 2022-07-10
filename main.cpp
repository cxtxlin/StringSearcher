#include <iostream>
#include <fstream>
#include <vector>
#include <regex>
#include <string>
#include "bi_istream_iterator.h"

int main() {

    std::fstream myFile ("vasile.txt", std::ios::in);
//
//    myFile.seekg(0, std::ios_base::end);
//    std::streampos lastPos = myFile.tellg();
//
//    bi_istream_iterator<char> beg(myFile);
//    bi_istream_iterator<char> end;

//    fstream_bidir_iterator beg(myFile, 0);
//    fstream_bidir_iterator end(myFile, lastPos);

//    for (auto iter = beg; iter != end; ++iter)
//        std::cout << *iter << ' ';
//
//    std::cout << std::endl;

    std::regex theRegExpression("ase");
    std::match_results<bi_istream_iterator<char>> matchResults;

    bi_istream_iterator<char> startIter(myFile, 0);

    std::regex_search(
            startIter
            , bi_istream_iterator<char>(myFile)
            , matchResults
            , theRegExpression
        );
    for (const auto & item : matchResults)
        std::cout << item;
    std::cout << std::endl;
//        cee = matchResults.suffix().str();

    return 0;
}
