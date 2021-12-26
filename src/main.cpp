#include <iostream>
#include <map>
#include "Lexer/Lexer.h"
#include "Parser/Parser.h"
#include "VM/Interpreter.h"

int main() {
    std::ifstream ifs;
    ifs.open("testfile.txt", std::ios::in);
    std::ofstream ofs;
    ofs.open("output.txt", std::ios::out | std::ios::trunc);
    MyOutput::setOutput(&ofs);
    std::ofstream eofs;
    eofs.open("error.txt", std::ios::out | std::ios::trunc);
#ifdef DEBUG
    MyOutput::setErrorOutput(&eofs);
#else
    MyOutput::setErrorOutput(&eofs);
#endif
    Lexer lexer{std::move(ifs)};
    Parser parser{lexer.getList()};
//    parser.getRoot()->myOutput();
    auto root = parser.getRoot();
    if (root->checkValid())
        root->toMidCode();
    INTERPRETER::Interpreter interpreter{GramNode::MidCodeSequence, GramNode::labels};
    interpreter.setOs(std::make_shared<std::ostream>(std::cout.rdbuf()));
    interpreter.run();
    return 0;
}
