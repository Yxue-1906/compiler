//
// Created by unrelated on 2021/10/17.
//

#ifndef LEXER_TOKEN_H
#define LEXER_TOKEN_H


#include <map>
#include <vector>
#include <memory>
#include <string>

#include "../Output/MyOutput.h"

class TokenBase : public MyOutput {
private:
    const std::string tokenName;
    const int tokenType;

    static std::vector<TokenBase *>::iterator end;
    static bool endSet;

    int lineNumber = -1;
    bool lineNumberSet = false;

public:
    static int IDENFR;
    static int INTCON;
    static int STRCON;
    static int MAINTK;
    static int CONSTTK;
    static int INTTK;
    static int BREAKTK;
    static int CONTINUETK;
    static int IFTK;
    static int ELSETK;
    static int NOT;
    static int AND;
    static int OR;
    static int WHILETK;
    static int GETINTTK;
    static int PRINTFTK;
    static int RETURNTK;
    static int PLUS;
    static int MINU;
    static int VOIDTK;
    static int MULT;
    static int DIV;
    static int MOD;
    static int LSS;
    static int LEQ;
    static int GRE;
    static int GEQ;
    static int EQL;
    static int NEQ;
    static int ASSIGN;
    static int SEMICN;
    static int COMMA;
    static int LPARENT;
    static int RPARENT;
    static int LBRACK;
    static int RBRACK;
    static int LBRACE;
    static int RBRACE;
    static int COMMENT;

    static const std::map<int, std::string> type2Name;

public:
    TokenBase(int);

    std::string &getTokenName();

    int getTokenType();

    static void setEnd(std::vector<TokenBase *>::iterator);

    static bool isTypeOf(std::vector<TokenBase *>::iterator &ite, int type);

    static bool isTypeOf(std::vector<TokenBase *>::iterator &&ite, int type);

    int setLineNumber(int lineNumber);

    int getLineNumber() const;
};

template<class T>
class Token : public TokenBase {
protected:
    std::shared_ptr<T> const value_p;

public:
    Token(int type, std::shared_ptr<T> value_p)
            : TokenBase(type), value_p(value_p) {}

    std::shared_ptr<T> getValue_p() const {
        return this->value_p;
    }

    virtual void myOutput() override {
        std::ostream *os = getOs();
        (*os) << getTokenName() << ' ' << *value_p << std::endl;
    }
};

#endif //LEXER_TOKEN_H
