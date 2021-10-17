//
// Created by unrelated on 2021/9/28.
//

#include <iostream>
#include "Lexer.h"
#include "../Exception/MyException.h"
#include "../MyDefination.h"

//Lexer::Lexer(std::ifstream ifs) {
//    this->ifs = ifs;
//    ifs >> now_line;
//    now_char_p = now_line.begin();
//}

Lexer::Lexer(std::string str) {
    this->ifs.open(str, std::ios::in);
    getline(ifs, now_line), ++line_count;
    now_char_p = now_line.begin();
    now_look_forward_p = now_line.begin();
}

Lexer::~Lexer() {
    this->ifs.close();
}

/**
 * take in a string for pre-read, an optional tailJudge to judge if tail meets requirement
 * @param chs a string to match
 * @param tailJudge must return ture if tail meets requirement; false if not
 * @return ture if pre-read successful and move ite forward; false if pre-read fail
 */
bool Lexer::safeLookAhead(const std::string chs, std::function<bool(std::string::iterator)> tailJudge = {}) {
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
        } else {
            ++now_look_forward_p;
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
    auto generalTailJudge = [this](std::string::iterator ite) {
        if (ite == now_line.end() || !isAlNum(*ite))return true;
        return false;
    };
    if (safeLookAhead("!=")) {
        ans->append("!=");
        *type = NEQ;
        return true;
    } else if (safeLookAhead("!")) {
        ans->push_back('!');
        *type = NOT;
        return true;
    } else if (safeLookAhead("%")) {
        ans->push_back('%');
        *type = MOD;
        return true;
    } else if (safeLookAhead("&&")) {
        ans->append("&&");
        *type = AND;
        return true;
    } else if (safeLookAhead("(")) {
        ans->push_back('(');
        *type = LPARENT;
        return true;
    } else if (safeLookAhead(")")) {
        ans->push_back(')');
        *type = RPARENT;
        return true;
    } else if (safeLookAhead("*")) {
        ans->push_back('*');
        *type = MULT;
        return true;
    } else if (safeLookAhead("+")) {
        ans->push_back('+');
        *type = PLUS;
        return true;
    } else if (safeLookAhead(",")) {
        ans->push_back(',');
        *type = COMMA;
        return true;
    } else if (safeLookAhead("-")) {
        ans->push_back('-');
        *type = MINU;
        return true;
    } else if (safeLookAhead("//")) {
        jumpComment(LINE_COMMENT);
        *type = OTHER;
        return getSymbol(ans, type);
    } else if (safeLookAhead("/*")) {
        jumpComment(BLOCK_COMMENT);
        *type = OTHER;
        return getSymbol(ans, type);
    } else if (safeLookAhead("/")) {
        ans->push_back('/');
        *type = DIV;
        return true;
    } else if (safeLookAhead(";")) {
        ans->push_back(';');
        *type = SEMICN;
        return true;
    } else if (safeLookAhead("<=")) {
        ans->append("<=");
        *type = LEQ;
        return true;
    } else if (safeLookAhead("<")) {
        ans->push_back('<');
        *type = LSS;
        return true;
    } else if (safeLookAhead("==")) {
        ans->append("==");
        *type = EQL;
        return true;
    } else if (safeLookAhead("=")) {
        ans->push_back('=');
        *type = EQL;
        return true;
    } else if (safeLookAhead(">=")) {
        ans->append(">=");
        *type = GEQ;
        return true;
    } else if (safeLookAhead(">")) {
        ans->push_back('>');
        *type = GRE;
        return true;
    } else if (safeLookAhead("[")) {
        ans->push_back('[');
        *type = LBRACK;
        return true;
    } else if (safeLookAhead("]")) {
        ans->push_back(']');
        *type = RBRACK;
        return true;
    } else if (safeLookAhead("break", generalTailJudge)) {
        ans->append("break");
        *type = BREAKTK;
        return true;
    } else if (safeLookAhead("const", generalTailJudge)) {
        ans->append("const");
        *type = CONSTTK;
        return true;
    } else if (safeLookAhead("continues", generalTailJudge)) {
        ans->append("continues");
        *type = CONTINUETK;
        return true;
    } else if (safeLookAhead("else", generalTailJudge)) {
        ans->append("else");
        *type = ELSETK;
        return true;
    } else if (safeLookAhead("getint", generalTailJudge)) {
        ans->append("getint");
        *type = GETINTTK;
        return true;
    } else if (safeLookAhead("if", generalTailJudge)) {
        ans->append("if");
        *type = IFTK;
        return true;
    } else if (safeLookAhead("int", generalTailJudge)) {
        ans->append("int");
        *type = INTCON;
        return true;
    } else if (safeLookAhead("main", generalTailJudge)) {
        ans->append("main");
        *type = MAINTK;
        return true;
    } else if (safeLookAhead("printf", generalTailJudge)) {
        ans->append("printf");
        *type = PRINTFTK;
        return true;
    } else if (safeLookAhead("return", generalTailJudge)) {
        ans->append("return");
        *type = RETURNTK;
        return true;
    } else if (safeLookAhead("void", generalTailJudge)) {
        ans->append("void");
        *type = VOIDTK;
        return true;
    } else if (safeLookAhead("while", generalTailJudge)) {
        ans->append("while");
        *type = WHILETK;
        return true;
    } else if (safeLookAhead("{")) {
        ans->push_back('{');
        *type = LBRACE;
        return true;
    } else if (safeLookAhead("||")) {
        ans->append("||");
        *type = OR;
        return true;
    } else if (safeLookAhead("}")) {
        ans->push_back('}');
        *type = RBRACE;
        return true;
    } else {
        *type = OTHER;
        return false;
    }
}

bool Lexer::getIdent(std::string *const ans, int *const type) {
    if (now_char_p == now_line.end() || (!std::isalpha(*now_char_p) && *now_char_p != '_')) {
        *type = OTHER;
        return false;
    }
    while (now_char_p != now_line.end() && isAlNum(*now_char_p)) {
        ans->push_back(*now_char_p);
        ++now_char_p;
    }
    *type = IDENFR;
    return true;
}

bool Lexer::getConst(std::string *const ans, int *const type) {
    if (now_char_p == now_line.end() || !std::isdigit(*now_char_p)) {
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
    if (now_char_p == now_line.end() || *now_char_p != '"') {
        *type = OTHER;
        return false;
    }
    ++now_char_p;
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
        if (getSymbol(*ans, type) || getIdent(*ans, type) || getConst(*ans, type) || getStr(*ans, type)) {
            return true;
        } else return false;
    } catch (MyException e) {
        //e.printStack();
        std::cout << "error!" << std::endl;
    }
    return false;
}