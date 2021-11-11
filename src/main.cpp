#include <iostream>
#include <map>
#include "Lexer/Lexer.h"
#include "Parser/Parser.h"

int main() {
    std::ifstream ifs;
    ifs.open("testfile.txt", std::ios::in);
    std::ofstream ofs;
    ofs.open("output.txt", std::ios::out | std::ios::trunc);
    MyOutput::setOutput(&ofs);
    std::ofstream eofs;
    eofs.open("error.txt", std::ios::out | std::ios::trunc);
    MyOutput::setErrorOutput(&std::cout);
    Lexer lexer{std::move(ifs)};
    Parser parser{lexer.getList()};
    parser.getRoot()->checkValid();
    return 0;
}
