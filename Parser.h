//
// Created by unrelated on 2021/10/8.
//

#ifndef PARSER_PARSER_H
#define PARSER_PARSER_H

#include "Lexer.h"
#include "MyException.h"

class Parser {
public:
    // public attributes

private:
    // private attributes

public:
    // public methods
    Parser(Lexer);

private:
    // private methods
//    bool CompUnit() {
//        Decl();
//        FuncDef();
//        if (!MainFuncDef()) {
//            throw MyException();
//        }
//        return true;
//    }
//
//    bool Decl() {
//        if (!ConstDecl() && !VarDecl()) {
//            throw MyException();
//        }
//        return true;
//    }
};


#endif //PARSER_PARSER_H
