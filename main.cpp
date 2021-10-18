#include <iostream>
#include <map>
#include "Lexer/Lexer.h"

int main() {
    std::ifstream ifs;
    ifs.open("testfile.txt", std::ios::in);
    std::ofstream ofs;
    ofs.open("output.txt", std::ios::out | std::ios::trunc);
    Lexer lexer{std::move(ifs)};
    MyOutput::setOutput(ofs);
    Parser parser{};
//    for (auto &i: lexer.getList()) {
//        (*i).myOutput();
//    }
    return 0;
}
