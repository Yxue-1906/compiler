#include <iostream>
#include <map>
#include "Lexer/Lexer.h"
#include "MyDefination.h"

int main() {
//    std::ifstream ifs;
//    ifs.open("testfile.txt", std::ios::in);
    std::ofstream ofs;
    ofs.open("output.txt", std::ios::out | std::ios::trunc);
    Lexer lexer("testfile.txt");
    std::string **strpp = (std::string **) malloc(sizeof(std::string *));
    int *type = (int *) malloc(sizeof(int));
    while (lexer.getWord(strpp, type)) {
        delete *strpp;
    }
    delete strpp;
    delete type;
    return 0;
}
