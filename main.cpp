#include <iostream>
#include <map>
#include "Lexer/Lexer.h"
#include "Parser/Parser.h"

int main() {
    std::ifstream ifs;
    ifs.open("testfile.txt", std::ios::in);
    std::ofstream ofs;
    ofs.open("output.txt", std::ios::out | std::ios::trunc);
    MyOutput::setOutput(&std::cout);
    Lexer lexer{std::move(ifs)};
    Parser parser{lexer.getList()};
    parser.print();
    return 0;
}
