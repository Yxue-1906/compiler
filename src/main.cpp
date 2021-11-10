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
    MyOutput::setErrorOutput(&std::cout);
    Lexer lexer{std::move(ifs)};
//    for (auto &i: lexer.getList()) {
//        std::cout << i->getLineNumber() << ":";
//        i->myOutput();
//    }
    Parser parser{lexer.getList()};
//    parser.print();
    parser.getRoot()->checkValid();
    return 0;
}
