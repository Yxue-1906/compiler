//
// Created by unrelated on 2021/9/28.
//

#include <iostream>
#include "Lexer.h"
#include "../Exception/MyException.h"


Lexer::Lexer(std::ifstream ifs) {
    this->ifs = std::move(ifs);
    ifs >> now_line;
    now_char_p = now_line.begin();
    this->init();
}

//Lexer::Lexer(std::string str) {
//    this->ifs.open(str, std::ios::in);
//    getline(ifs, now_line), ++line_count;
//    now_char_p = now_line.begin();
//    now_look_forward_p = now_line.begin();
//}

Lexer::~Lexer() {
    this->ifs.close();
}

std::vector<Token *> &Lexer::getList() {
    if (inited)return this->tokenList;
    else {
        std::cout << "lexer has not inited!" << std::endl;
        throw new MyException();
    }
}

/**
 * take in a string for pre-read, an optional tailJudge to judge if tail meets requirement
 * @param chs a string to match
 * @param tailJudge must return ture if tail meets requirement; false if not
 * @return ture if pre-read successful and move ite forward; false if pre-read fail
 */
bool Lexer::safeLookAhead(const std::string &chs, const std::function<bool(std::string::iterator)> &tailJudge = {}) {
    if (now_look_forward_p != now_char_p)now_look_forward_p = now_char_p;
    for (auto ite = chs.begin(); ite != chs.end(); ++ite) {
        if (now_look_forward_p != now_line.end() && *now_look_forward_p == *ite) {
            ++now_look_forward_p;
        } else {
            now_look_forward_p = now_char_p;
            return false;
        }
    }
    if (tailJudge) {
        if (!tailJudge(now_look_forward_p)) {
            now_look_forward_p = now_char_p;
            return false;
        }
    }
    now_char_p = now_look_forward_p;
    return true;
}

bool Lexer::isAlNum(int ch) {
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
    if (type) {
        while (true) {
            if (!jumpSpace()) {
                return false;
            }
            if (*now_char_p == '*' && now_char_p + 1 != now_line.end()
                && *(now_char_p + 1) == '/') {
                now_char_p += 2;
                return true;
            }
            now_char_p++;
        }
    } else {
        if (getline(ifs, now_line) && ++line_count)
            now_char_p = now_line.begin();
        else {
            end = true;
            return false;
        }
    }
    return false;
}

Token *Lexer::getSymbol() {
    auto generalTailJudge = [this](std::string::iterator ite) {
        if (ite == now_line.end() || !isAlNum(*ite))return true;
        return false;
    };
    if (safeLookAhead("!=")) {
        return new NEQ();
    } else if (safeLookAhead("!")) {
        return new NOT();
    } else if (safeLookAhead("%")) {
        return new MOD();
    } else if (safeLookAhead("&&")) {
        return new AND();
    } else if (safeLookAhead("(")) {
        return new LPARENT();
    } else if (safeLookAhead(")")) {
        return new RPARENT();
    } else if (safeLookAhead("*")) {
        return new MULT();
    } else if (safeLookAhead("+")) {
        return new PLUS();
    } else if (safeLookAhead(",")) {
        return new COMMA();
    } else if (safeLookAhead("-")) {
        return new MINU();
    } else if (safeLookAhead("//")) {
        jumpComment(LINE_COMMENT);
        jumpSpace();
        return getSymbol();
    } else if (safeLookAhead("/*")) {
        jumpComment(BLOCK_COMMENT);
        jumpSpace();
        return getSymbol();
    } else if (safeLookAhead("/")) {
        return new DIV();
    } else if (safeLookAhead(";")) {
        return new SEMICN();
    } else if (safeLookAhead("<=")) {
        return new LEQ();
    } else if (safeLookAhead("<")) {
        return new LSS();
    } else if (safeLookAhead("==")) {
        return new EQL();
    } else if (safeLookAhead("=")) {
        return new ASSIGN();
    } else if (safeLookAhead(">=")) {
        return new GEQ();
    } else if (safeLookAhead(">")) {
        return new GRE();
    } else if (safeLookAhead("[")) {
        return new LBRACK();
    } else if (safeLookAhead("]")) {
        return new RBRACK();
    } else if (safeLookAhead("break", generalTailJudge)) {
        return new BREAKTK();
    } else if (safeLookAhead("const", generalTailJudge)) {
        return new CONSTTK();
    } else if (safeLookAhead("continue", generalTailJudge)) {
        return new CONTINUETK();
    } else if (safeLookAhead("else", generalTailJudge)) {
        return new ELSETK();
    } else if (safeLookAhead("getint", generalTailJudge)) {
        return new GETINTTK();
    } else if (safeLookAhead("if", generalTailJudge)) {
        return new IFTK();
    } else if (safeLookAhead("int", generalTailJudge)) {
        return new INTTK();
    } else if (safeLookAhead("main", generalTailJudge)) {
        return new MAINTK();
    } else if (safeLookAhead("printf", generalTailJudge)) {
        return new PRINTFTK();
    } else if (safeLookAhead("return", generalTailJudge)) {
        return new RETURNTK();
    } else if (safeLookAhead("void", generalTailJudge)) {
        return new VOIDTK();
    } else if (safeLookAhead("while", generalTailJudge)) {
        return new WHILETK();
    } else if (safeLookAhead("{")) {
        return new LBRACE();
    } else if (safeLookAhead("||")) {
        return new OR();
    } else if (safeLookAhead("}")) {
        return new RBRACE();
    } else {
        return nullptr;
    }
}

IDENFR *Lexer::getIdent() {
    std::string ident;
    if (now_char_p == now_line.end() || (!std::isalpha(*now_char_p) && *now_char_p != '_')) {
        return nullptr;
    }
    while (now_char_p != now_line.end() && isAlNum(*now_char_p)) {
        ident.push_back(*now_char_p);
        ++now_char_p;
    }
    return new IDENFR(ident);
}

INTCON *Lexer::getConst() {
    int num = 0;
    if (now_char_p == now_line.end() || !std::isdigit(*now_char_p)) {
        return nullptr;
    }
    while (now_char_p != now_line.end() && std::isdigit(*now_char_p)) {
        num *= 10;
        num += *now_char_p - '0';
        ++now_char_p;
    }
    return new INTCON(num);
}

STRCON *Lexer::getStr() {
    std::string str;
    if (now_char_p == now_line.end() || *now_char_p != '"') {
        return nullptr;
    }
    while (now_char_p != now_line.end()) {
        str.push_back(*now_char_p);
        ++now_char_p;
        if (*now_char_p == '"') {
            str.push_back('"');
            ++now_char_p;
            break;
        }
        if (now_char_p == now_line.end())throw MyException();
    }
    return new STRCON(str);
}


void Lexer::init() {
    while (true) {
        if (!Lexer::jumpSpace())break;
        try {
            Token *nextSym = nullptr;
            if ((nextSym = getSymbol()) || (nextSym = getIdent()) ||
                (nextSym = getConst()) || (nextSym = getStr())) {
                this->tokenList.push_back(nextSym);
                nextSym->setLineNumber(line_count);
                nextSym->myOutput();
            } else break;
        } catch (MyException e) {
            //e.printStack();
            std::cout << "error!" << std::endl;
        }
    }
    inited = true;
    Token::setEnd(this->tokenList.end());
}