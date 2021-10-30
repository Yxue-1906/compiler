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
bool Stmt::create(std::vector<GramNode *> &toAdd, std::vector<TokenBase *>::iterator &ite_p) {
    auto ite = ite_p;
    std::vector<GramNode *> son_ps;
    auto detectExp = [&ite]() -> bool {
        if (!TokenBase::isTypeOf(ite, TokenBase::IDENFR))
            return true;
        int index = 1;
        for (int leftLBrackets = 0; leftLBrackets != 0 || TokenBase::isTypeOf(ite + index, TokenBase::LBRACK);) {
            if (TokenBase::isTypeOf(ite + index, TokenBase::RBRACK))
                leftLBrackets--;
            else if (TokenBase::isTypeOf(ite + index, TokenBase::LBRACK))
                leftLBrackets++;
            index++;
        }
        if (TokenBase::isTypeOf(ite + index, TokenBase::ASSIGN))
            return false;
        return true;
    };
    if (TokenNode::create(son_ps, ite, TokenBase::IFTK)) {
        if (!TokenNode::create(son_ps, ite, TokenBase::LPARENT)) {
            return false;
        }
        if (!Cond::create(son_ps, ite)) {
            return false;
        }
        if (!TokenNode::create(son_ps, ite, TokenBase::RPARENT)) {
            return false;
        }
        if (!Stmt::create(son_ps, ite)) {
            return false;
        }
        if (TokenNode::create(son_ps, ite, TokenBase::ELSETK)) {
            if (!Stmt::create(son_ps, ite)) {
                return false;
            }
        }
        ite_p = ite;
        toAdd.push_back(new Stmt(son_ps));
        return true;
    } else if (TokenNode::create(son_ps, ite, TokenBase::WHILETK)) {
        if (!TokenNode::create(son_ps, ite, TokenBase::LPARENT)) {
            return false;
        }
        if (!Cond::create(son_ps, ite)) {
            return false;
        }
        if (!TokenNode::create(son_ps, ite, TokenBase::RPARENT)) {
            return false;
        }
        if (!Stmt::create(son_ps, ite)) {
            return false;
        }
        ite_p = ite;
        toAdd.push_back(new Stmt(son_ps));
        return true;
    } else if (TokenNode::create(son_ps, ite, TokenBase::BREAKTK) ||
               TokenNode::create(son_ps, ite, TokenBase::CONTINUETK)) {
        if (!TokenNode::create(son_ps, ite, TokenBase::SEMICN)) {
            return false;
        }
        ite_p = ite;
        toAdd.push_back(new Stmt(son_ps));
        return true;
    } else if (TokenNode::create(son_ps, ite, TokenBase::RETURNTK)) {
        if (!TokenBase::isTypeOf(ite, TokenBase::SEMICN))
            if (!Exp::create(son_ps, ite))
                return false;
        if (!TokenNode::create(son_ps, ite, TokenBase::SEMICN)) {
            return false;
        }
        ite_p = ite;
        toAdd.push_back(new Stmt(son_ps));
        return true;
    } else if (TokenNode::create(son_ps, ite, TokenBase::PRINTFTK)) {
        if (!TokenNode::create(son_ps, ite, TokenBase::LPARENT)) {
            return false;
        }
        if (!TokenNode::create(son_ps, ite, TokenBase::STRCON)) {
            return false;
        }
        for (; TokenNode::create(son_ps, ite, TokenBase::COMMA);) {
            if (!Exp::create(son_ps, ite)) {
                return false;
            }
        }
        if (!TokenNode::create(son_ps, ite, TokenBase::RPARENT)) {
            return false;
        }
        if (!TokenNode::create(son_ps, ite, TokenBase::SEMICN)) {
            return false;
        }
        ite_p = ite;
        toAdd.push_back(new Stmt(son_ps));
        return true;
    } else if (TokenBase::isTypeOf(ite, TokenBase::LBRACE)) {
        if (!Block::create(son_ps, ite)) {
            return false;
        }
        ite_p = ite;
        toAdd.push_back(new Stmt(son_ps));
        return true;
    } else if (TokenBase::isTypeOf(ite, TokenBase::IDENFR) &&
               !TokenBase::isTypeOf(ite + 1, TokenBase::LPARENT)) {
        if (detectExp()) {
            if (!Exp::create(son_ps, ite))
                return false;
            if (!TokenNode::create(son_ps, ite, TokenBase::SEMICN))
                return false;
            ite_p = ite;
            toAdd.push_back(new Stmt(son_ps));
            return true;
        } else {
            if (!LVal::create(son_ps, ite))
                return false;
            if (!TokenNode::create(son_ps, ite, TokenBase::ASSIGN))
                return false;
            if (TokenNode::create(son_ps, ite, TokenBase::GETINTTK)) {
                if (!TokenNode::create(son_ps, ite, TokenBase::LPARENT)) {
                    return false;
                }
                if (!TokenNode::create(son_ps, ite, TokenBase::RPARENT)) {
                    return false;
                }
                if (!TokenNode::create(son_ps, ite, TokenBase::SEMICN)) {
                    return false;
                }
                ite_p = ite;
                toAdd.push_back(new Stmt(son_ps));
                return true;
            } else {
                Exp::create(son_ps, ite);
                if (TokenBase::isTypeOf(ite, TokenBase::SEMICN)) {
                    TokenNode::create(son_ps, ite, TokenBase::SEMICN);
                    ite_p = ite;
                    toAdd.push_back(new Stmt(son_ps));
                    return true;
                }
                return false;
            }
        }
    } else {
        if (!TokenBase::isTypeOf(ite, TokenBase::SEMICN))
            if (!Exp::create(son_ps, ite))
                return false;
        if (!TokenNode::create(son_ps, ite, TokenBase::SEMICN)) {
            return false;
        }
        ite_p = ite;
        toAdd.push_back(new Stmt(son_ps));
        return true;
    }
}
