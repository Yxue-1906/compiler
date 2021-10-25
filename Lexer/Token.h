//
// Created by unrelated on 2021/10/17.
//

#ifndef LEXER_TOKEN_H
#define LEXER_TOKEN_H


#include <map>
#include <vector>
#include "../Output/MyOutput.h"

class Token : public MyOutput {
private:
    const std::string tokenName;
    const int tokenType;

    static std::vector<Token *>::iterator end;
    static bool endSet;

    int lineNumber = -1;
    bool lineNumberSet = false;

protected:
    void *value_p;
    bool valueType;
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
protected:
    template<class T>
    void setValue_p(T *value_p) {
        if (!this->value_p) {
            valueType = std::is_same<T, int>::value;
            this->value_p = value_p;
        }
    }

public:
    Token(int);

    std::string &getTokenName();

    int getTokenType();

    static void setEnd(std::vector<Token *>::iterator);

    static bool isTypeOf(std::vector<Token *>::iterator &ite, int type);

    static bool isTypeOf(std::vector<Token *>::iterator &&ite, int type);

    int setLineNumber(int lineNumber);

    virtual void myOutput() override;

    int getLineNumber();

private:


};


#endif //LEXER_TOKEN_H
