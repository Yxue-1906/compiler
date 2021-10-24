//
// Created by unrelated on 2021/10/18.
//

#include "Stmt.h"
#include "../TokenNode.h"
#include "Cond.h"
#include "Exp.h"
#include "Block.h"
#include "LVal.h"

Stmt::Stmt(std::vector<GramNode *> sons) : GramNode() {
    setGramName("Stmt");
    setSons(std::move(sons));
}

/**
 * Stmt -> 'if' '(' Cond ')' Stmt [ 'else' Stmt ] |
 *         'while' '(' Cond ')' Stmt |
 *         'break' ';' | 'continue' ';'|
 *         'return' [Exp] ';' |
 *         'printf' '(' FormatString{',' Exp} ')' ';'
 *         Block |
 *         LVal '=' Exp ';' |
 *         [Exp] ';' |
 *         LVal '=' 'getint' '(' ')' ';' |
 *
 * @param toAdd
 * @param ite_p
 * @return
 */
bool Stmt::create(std::vector<GramNode *> &toAdd, std::vector<Token *>::iterator &ite_p) {
    auto ite = ite_p;
    std::vector<GramNode *> son_ps;
    auto detectExp = [&ite]() -> bool {
        if (!Token::isTypeOf(ite, Token::IDENFR))
            return true;
        int index = 1;
        for (int leftLBrackets = 0; leftLBrackets != 0 || Token::isTypeOf(ite + index, Token::LBRACK);) {
            if (Token::isTypeOf(ite + index, Token::RBRACK))
                leftLBrackets--;
            else if (Token::isTypeOf(ite + index, Token::LBRACK))
                leftLBrackets++;
            index++;
        }
        if (Token::isTypeOf(ite + index, Token::ASSIGN))
            return false;
        return true;
    };
    if (TokenNode::create(son_ps, ite, Token::IFTK)) {
        if (!TokenNode::create(son_ps, ite, Token::LPARENT)) {
            return false;
        }
        if (!Cond::create(son_ps, ite)) {
            return false;
        }
        if (!TokenNode::create(son_ps, ite, Token::RPARENT)) {
            return false;
        }
        if (!Stmt::create(son_ps, ite)) {
            return false;
        }
        if (TokenNode::create(son_ps, ite, Token::ELSETK)) {
            if (!Stmt::create(son_ps, ite)) {
                return false;
            }
        }
        ite_p = ite;
        toAdd.push_back(new Stmt(son_ps));
        return true;
    } else if (TokenNode::create(son_ps, ite, Token::WHILETK)) {
        if (!TokenNode::create(son_ps, ite, Token::LPARENT)) {
            return false;
        }
        if (!Cond::create(son_ps, ite)) {
            return false;
        }
        if (!TokenNode::create(son_ps, ite, Token::RPARENT)) {
            return false;
        }
        if (!Stmt::create(son_ps, ite)) {
            return false;
        }
        ite_p = ite;
        toAdd.push_back(new Stmt(son_ps));
        return true;
    } else if (TokenNode::create(son_ps, ite, Token::BREAKTK) || TokenNode::create(son_ps, ite, Token::CONTINUETK)) {
        if (!TokenNode::create(son_ps, ite, Token::SEMICN)) {
            return false;
        }
        ite_p = ite;
        toAdd.push_back(new Stmt(son_ps));
        return true;
    } else if (TokenNode::create(son_ps, ite, Token::RETURNTK)) {
        if (!Token::isTypeOf(ite, Token::SEMICN))
            if (!Exp::create(son_ps, ite))
                return false;
        if (!TokenNode::create(son_ps, ite, Token::SEMICN)) {
            return false;
        }
        ite_p = ite;
        toAdd.push_back(new Stmt(son_ps));
        return true;
    } else if (TokenNode::create(son_ps, ite, Token::PRINTFTK)) {
        if (!TokenNode::create(son_ps, ite, Token::LPARENT)) {
            return false;
        }
        if (!TokenNode::create(son_ps, ite, Token::STRCON)) {
            return false;
        }
        for (; TokenNode::create(son_ps, ite, Token::COMMA);) {
            if (!Exp::create(son_ps, ite)) {
                return false;
            }
        }
        if (!TokenNode::create(son_ps, ite, Token::RPARENT)) {
            return false;
        }
        if (!TokenNode::create(son_ps, ite, Token::SEMICN)) {
            return false;
        }
        ite_p = ite;
        toAdd.push_back(new Stmt(son_ps));
        return true;
    } else if (Token::isTypeOf(ite, Token::LBRACE)) {
        if (!Block::create(son_ps, ite)) {
            return false;
        }
        ite_p = ite;
        toAdd.push_back(new Stmt(son_ps));
        return true;
    } else if (Token::isTypeOf(ite, Token::IDENFR) &&
               !Token::isTypeOf(ite + 1, Token::LPARENT)) {
        if (detectExp()) {
            if (!Exp::create(son_ps, ite))
                return false;
            if (!TokenNode::create(son_ps, ite, Token::SEMICN))
                return false;
            ite_p = ite;
            toAdd.push_back(new Stmt(son_ps));
            return true;
        } else {
            if (!LVal::create(son_ps, ite))
                return false;
            if (!TokenNode::create(son_ps, ite, Token::ASSIGN))
                return false;
            if (TokenNode::create(son_ps, ite, Token::GETINTTK)) {
                if (!TokenNode::create(son_ps, ite, Token::LPARENT)) {
                    return false;
                }
                if (!TokenNode::create(son_ps, ite, Token::RPARENT)) {
                    return false;
                }
                if (!TokenNode::create(son_ps, ite, Token::SEMICN)) {
                    return false;
                }
                ite_p = ite;
                toAdd.push_back(new Stmt(son_ps));
                return true;
            } else {
                Exp::create(son_ps, ite);
                if (Token::isTypeOf(ite, Token::SEMICN)) {
                    TokenNode::create(son_ps, ite, Token::SEMICN);
                    ite_p = ite;
                    toAdd.push_back(new Stmt(son_ps));
                    return true;
                }
                return false;
            }
        }
    } else {
        if (!Token::isTypeOf(ite, Token::SEMICN))
            if (!Exp::create(son_ps, ite))
                return false;
        if (!TokenNode::create(son_ps, ite, Token::SEMICN)) {
            return false;
        }
        ite_p = ite;
        toAdd.push_back(new Stmt(son_ps));
        return true;
    }
}
