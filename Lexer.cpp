//
// Created by unrelated on 2021/9/28.
//

#include <iostream>
#include "Lexer.h"
#include "MyException.h"
#include "MyDefination.h"

//Lexer::Lexer(std::ifstream ifs) {
//    this->ifs = ifs;
//    ifs >> now_line;
//    now_char_p = now_line.begin();
//}

Lexer::Lexer(std::string str) {
    this->ifs.open(str, std::ios::in);
    getline(ifs, now_line), ++line_count;
    now_char_p = now_line.begin();
}

Lexer::~Lexer() {
    this->ifs.close();
}

//bool Lexer::isWhitespace(typeof(std::string::iterator) ite) {
//    if (*ite != 32 && *ite != 33 && (*ite < 40 || *ite > 126))return true;
//    return false;
//}
bool Lexer::isal_num(int ch) {
    return std::isalnum(ch) || ch == '_';
}

bool Lexer::jumpSpace() {
    while (now_char_p == now_line.end() || std::isspace(*now_char_p)) {
        if (now_char_p == now_line.end()) {
            if (std::getline(ifs, now_line) && ++line_count) {
                now_char_p = now_line.begin();
            } else {
                end = true;
                return false;
            }
        } else {
            ++now_char_p;
        }
    }
    return true;
}

bool Lexer::jumpComment(int type) {
    now_char_p += 2;
    if (type) {
        while (true) {
            if (!jumpSpace()) {
                return false;
            }
            if (*now_char_p == '*' && now_char_p + 1 != now_line.end() && *(now_char_p + 1) == '/') {
                now_char_p += 2;
                return true;
            }
            now_char_p++;
        }
    } else {
        if (getline(ifs, now_line) && ++line_count)now_char_p = now_line.begin();
        else {
            end = true;
            return false;
        }
    }
    return false;
}

bool Lexer::getSymbol(std::string *const ans, int *const type) {
    switch (*now_char_p) {
        case '!': {
            (*ans).push_back('!');
            *type = NOT;
            ++now_char_p;
            if (now_char_p != now_line.end() && *now_char_p == '=') {
                (*ans).push_back('=');
                *type = NEQ;
                ++now_char_p;
            }
            return true;
        }
        case '%': {
            (*ans).push_back('%');
            *type = MOD;
            ++now_char_p;
            return true;
        }
        case '&': {
            if (now_char_p + 1 != now_line.end() && *(now_char_p + 1) == '&') {
                (*ans).append("&&");
                now_char_p += 2;
                *type = AND;
            } else {
                throw MyException();
            }
            return true;
        }
        case '(': {
            (*ans).push_back('(');
            *type = LPARENT;
            ++now_char_p;
            return true;
        }
        case ')': {
            (*ans).push_back(')');
            *type = RPARENT;
            ++now_char_p;
            return true;
        }
        case '*': {
            (*ans).push_back('*');
            *type = MULT;
            ++now_char_p;
            return true;
        }
        case '+': {
            (*ans).push_back('+');
            *type = PLUS;
            ++now_char_p;
            return true;
        }
        case ',': {
            (*ans).push_back(',');
            *type = COMMA;
            ++now_char_p;
            return true;
        }
        case '-': {
            (*ans).push_back('-');
            *type = MINU;
            ++now_char_p;
            return true;
        }
        case '/': {
            if (now_char_p + 1 != now_line.end()) {
                if (*(now_char_p + 1) == '/') {
                    jumpComment(0);
                    *type = COMMENT;
                    return true;
                } else if (*(now_char_p + 1) == '*') {
                    jumpComment(1);
                    *type = COMMENT;
                    return true;
                }
            }
            (*ans).push_back('/');
            *type = DIV;
            ++now_char_p;
            return true;
        }
        case ';': {
            (*ans).push_back(';');
            *type = SEMICN;
            ++now_char_p;
            return true;
        }
        case '<': {
            (*ans).push_back('<');
            *type = LSS;
            ++now_char_p;
            if (now_char_p != now_line.end() && *now_char_p == '=') {
                (*ans).push_back('=');
                *type = LEQ;
                ++now_char_p;
            }
            return true;
        }
        case '=': {
            (*ans).push_back('=');
            *type = ASSIGN;
            ++now_char_p;
            if (now_char_p != now_line.end() && *now_char_p == '=') {
                (*ans).push_back('=');
                *type = EQL;
                ++now_char_p;
            }
            return true;
        }
        case '>': {
            (*ans).push_back('>');
            *type = GRE;
            ++now_char_p;
            if (now_char_p != now_line.end() && *now_char_p == '=') {
                (*ans).push_back('=');
                *type = GEQ;
                ++now_char_p;
            }
            return true;
        }
        case '[': {
            (*ans).push_back('[');
            *type = LBRACK;
            ++now_char_p;
            return true;
        }
        case ']': {
            (*ans).push_back(']');
            *type = RBRACK;
            ++now_char_p;
            return true;
        }
        case 'b': {
            if (now_char_p + 1 == now_line.end() || *(now_char_p + 1) != 'r') {
                *type = OTHER;
                break;
            }
            if (now_char_p + 2 == now_line.end() || *(now_char_p + 2) != 'e') {
                *type = OTHER;
                break;
            }
            if (now_char_p + 3 == now_line.end() || *(now_char_p + 3) != 'a') {
                *type = OTHER;
                break;
            }
            if (now_char_p + 4 == now_line.end() || *(now_char_p + 4) != 'k') {
                *type = OTHER;
                break;
            }
            if (now_char_p + 5 != now_line.end() && Lexer::isal_num(*(now_char_p + 5))) {
                *type = OTHER;
                break;
            }
            (*ans).append("break");
            *type = BREAKTK;
            now_char_p += 5;
            return true;
        }
        case 'c': {
            if (now_char_p + 1 == now_line.end() || *(now_char_p + 1) != 'o') {
                *type = OTHER;
                break;
            }
            if (now_char_p + 2 == now_line.end() || *(now_char_p + 2) != 'n') {
                *type = OTHER;
                break;
            }
            if (now_char_p + 3 != now_line.end()) {
                switch (*(now_char_p + 3)) {
                    case 's': {
                        if (now_char_p + 4 == now_line.end() || *(now_char_p + 4) != 't') {
                            *type = OTHER;
                            break;
                        }
                        if (now_char_p + 5 != now_line.end() && Lexer::isal_num(*(now_char_p + 5))) {
                            *type = OTHER;
                            break;
                        }
                        (*ans).append("const");
                        *type = CONSTTK;
                        now_char_p += 5;
                        return true;
                    }
                    case 't': {
                        if (now_char_p + 4 == now_line.end() || *(now_char_p + 4) != 'i') {
                            *type = OTHER;
                            break;
                        }
                        if (now_char_p + 5 == now_line.end() || *(now_char_p + 5) != 'n') {
                            *type = OTHER;
                            break;
                        }
                        if (now_char_p + 6 == now_line.end() || *(now_char_p + 6) != 'u') {
                            *type = OTHER;
                            break;
                        }
                        if (now_char_p + 7 == now_line.end() || *(now_char_p + 7) != 'e') {
                            *type = OTHER;
                            break;
                        }
                        if (now_char_p + 8 != now_line.end() && Lexer::isal_num(*(now_char_p + 8))) {
                            *type = OTHER;
                            break;
                        }
                        (*ans).append("continue");
                        *type = CONTINUETK;
                        now_char_p += 8;
                        return true;
                    }
                    default:
                        *type = OTHER;
                }
            } else {
                *type = OTHER;
                break;
            }
        }
        case 'e': {
            if (now_char_p + 1 == now_line.end() || *(now_char_p + 1) != 'l') {
                *type = OTHER;
                break;
            }
            if (now_char_p + 2 == now_line.end() || *(now_char_p + 2) != 's') {
                *type = OTHER;
                break;
            }
            if (now_char_p + 3 == now_line.end() || *(now_char_p + 3) != 'e') {
                *type = OTHER;
                break;
            }
            if (now_char_p + 4 != now_line.end() && Lexer::isal_num(*(now_char_p + 4))) {
                *type = OTHER;
                break;
            }
            (*ans).append("else");
            *type = ELSETK;
            now_char_p += 4;
            return true;
        }
        case 'g': {
            if (now_char_p + 1 == now_line.end() || *(now_char_p + 1) != 'e') {
                *type = OTHER;
                break;
            }
            if (now_char_p + 2 == now_line.end() || *(now_char_p + 2) != 't') {
                *type = OTHER;
                break;
            }
            if (now_char_p + 3 == now_line.end() || *(now_char_p + 3) != 'i') {
                *type = OTHER;
                break;
            }
            if (now_char_p + 4 == now_line.end() || *(now_char_p + 4) != 'n') {
                *type = OTHER;
                break;
            }
            if (now_char_p + 5 == now_line.end() || *(now_char_p + 5) != 't') {
                *type = OTHER;
                break;
            }
            if (now_char_p + 6 != now_line.end() && Lexer::isal_num(*(now_char_p + 6))) {
                *type = OTHER;
                break;
            }
            (*ans).append("getint");
            *type = GETINTTK;
            now_char_p += 6;
            return true;
        }
        case 'i': {
            if (now_char_p + 1 != now_line.end()) {
                switch (*(now_char_p + 1)) {
                    case 'f': {
                        if (now_char_p + 2 != now_line.end() && Lexer::isal_num(*(now_char_p + 2))) {
                            *type = OTHER;
                            break;
                        }
                        (*ans).append("if");
                        *type = IFTK;
                        now_char_p += 2;
                        return true;
                    }
                    case 'n': {
                        if (now_char_p + 2 == now_line.end() || *(now_char_p + 2) != 't') {
                            *type = OTHER;
                            break;
                        }
                        if (now_char_p + 3 != now_line.end() && Lexer::isal_num(*(now_char_p + 3))) {
                            *type = OTHER;
                            break;
                        }
                        (*ans).append("int");
                        *type = INTTK;
                        now_char_p += 3;
                        return true;
                    }
                }
            } else {
                *type = OTHER;
                break;
            }
        }
        case 'm': {
            if (now_char_p + 1 == now_line.end() || *(now_char_p + 1) != 'a') {
                *type = OTHER;
                break;
            }
            if (now_char_p + 2 == now_line.end() || *(now_char_p + 2) != 'i') {
                *type = OTHER;
                break;
            }
            if (now_char_p + 3 == now_line.end() || *(now_char_p + 3) != 'n') {
                *type = OTHER;
                break;
            }
            if (now_char_p + 4 != now_line.end() && Lexer::isal_num(*(now_char_p + 4))) {
                *type = OTHER;
                break;
            }
            (*ans).append("main");
            *type = MAINTK;
            now_char_p += 4;
            return true;
        }
        case 'p': {
            if (now_char_p + 1 == now_line.end() || *(now_char_p + 1) != 'r') {
                *type = OTHER;
                break;
            }
            if (now_char_p + 2 == now_line.end() || *(now_char_p + 2) != 'i') {
                *type = OTHER;
                break;
            }
            if (now_char_p + 3 == now_line.end() || *(now_char_p + 3) != 'n') {
                *type = OTHER;
                break;
            }
            if (now_char_p + 4 == now_line.end() || *(now_char_p + 4) != 't') {
                *type = OTHER;
                break;
            }
            if (now_char_p + 5 == now_line.end() || *(now_char_p + 5) != 'f') {
                *type = OTHER;
                break;
            }
            if (now_char_p + 6 != now_line.end() && Lexer::isal_num(*(now_char_p + 6))) {
                *type = OTHER;
                break;
            }
            (*ans).append("printf");
            *type = PRINTFTK;
            now_char_p += 6;
            return true;
        }
        case 'r': {
            if (now_char_p + 1 == now_line.end() || *(now_char_p + 1) != 'e') {
                *type = OTHER;
                break;
            }
            if (now_char_p + 2 == now_line.end() || *(now_char_p + 2) != 't') {
                *type = OTHER;
                break;
            }
            if (now_char_p + 3 == now_line.end() || *(now_char_p + 3) != 'u') {
                *type = OTHER;
                break;
            }
            if (now_char_p + 4 == now_line.end() || *(now_char_p + 4) != 'r') {
                *type = OTHER;
                break;
            }
            if (now_char_p + 5 == now_line.end() || *(now_char_p + 5) != 'n') {
                *type = OTHER;
                break;
            }
            if (now_char_p + 6 != now_line.end() && Lexer::isal_num(*(now_char_p + 6))) {
                *type = OTHER;
                break;
            }
            (*ans).append("return");
            *type = RETURNTK;
            now_char_p += 6;
            return true;
        }
        case 'v': {
            if (now_char_p + 1 == now_line.end() || *(now_char_p + 1) != 'o') {
                *type = OTHER;
                break;
            }
            if (now_char_p + 2 == now_line.end() || *(now_char_p + 2) != 'i') {
                *type = OTHER;
                break;
            }
            if (now_char_p + 3 == now_line.end() || *(now_char_p + 3) != 'd') {
                *type = OTHER;
                break;
            }
            if (now_char_p + 4 != now_line.end() && Lexer::isal_num(*(now_char_p + 4))) {
                *type = OTHER;
                break;
            }
            (*ans).append("void");
            *type = VOIDTK;
            now_char_p += 4;
            return true;
        }
        case 'w': {
            if (now_char_p + 1 == now_line.end() || *(now_char_p + 1) != 'h') {
                *type = OTHER;
                break;
            }
            if (now_char_p + 2 == now_line.end() || *(now_char_p + 2) != 'i') {
                *type = OTHER;
                break;
            }
            if (now_char_p + 3 == now_line.end() || *(now_char_p + 3) != 'l') {
                *type = OTHER;
                break;
            }
            if (now_char_p + 4 == now_line.end() || *(now_char_p + 4) != 'e') {
                *type = OTHER;
                break;
            }
            if (now_char_p + 5 != now_line.end() && Lexer::isal_num(*(now_char_p + 5))) {
                *type = OTHER;
                break;
            }
            (*ans).append("while");
            *type = WHILETK;
            now_char_p += 5;
            return true;
        }
        case '{': {
            (*ans).push_back('{');
            *type = LBRACE;
            now_char_p++;
            return true;
        }
        case '|': {
            if (now_char_p + 1 != now_line.end() && *(now_char_p + 1) == '|') {
                (*ans).append("||");
                now_char_p += 2;
                *type = OR;
            } else {
                throw MyException();
            }
            return true;
        }
        case '}': {
            (*ans).push_back('}');
            *type = RBRACE;
            now_char_p++;
            return true;
        }
        case '\"': {
            Lexer::getStr(ans, type);
            return true;
        }
        case '_': {
            *type = IDENFR;
            break;
        }
        default:
            *type = OTHER;
    }
    return false;
}

bool Lexer::getIdent(std::string *const ans, int *const type) {
    if (!std::isalpha(*now_char_p) && *now_char_p != '_') {
        *type = OTHER;
        return false;
    }
    while (now_char_p != now_line.end() && Lexer::isal_num(*now_char_p)) {
        ans->push_back(*now_char_p);
        ++now_char_p;
    }
    *type = IDENFR;
    return true;
}

bool Lexer::getConst(std::string *const ans, int *const type) {
    if (!std::isdigit(*now_char_p)) {
        *type = OTHER;
        return false;
    }
    while (now_char_p != now_line.end() && std::isdigit(*now_char_p)) {
        ans->push_back(*now_char_p);
        ++now_char_p;
    }
    *type = INTCON;
    return true;
}

bool Lexer::getStr(std::string *const ans, int *const type) {
    while (now_char_p != now_line.end()) {
        ans->push_back(*now_char_p);
        ++now_char_p;
        if (*now_char_p == '"') {
            ans->push_back('"');
            ++now_char_p;
            break;
        }
        if (now_char_p == now_line.end())throw MyException();
    }
    *type = STRCON;
    return true;
}

bool Lexer::getWord(std::string **const ans, int *type) {
    if (!Lexer::jumpSpace()) {
        *ans = nullptr;
        *type = 0;
    }
    *ans = new std::string();
    try {
        if (getSymbol(*ans, type)) {
            return true;
        } else if (getIdent(*ans, type)) {
            return true;
        } else if (getConst(*ans, type)) {
            return true;
        } else return false;
    } catch (MyException e) {
        //e.printStack();
        std::cout << "error!" << std::endl;
    }
    return false;
}