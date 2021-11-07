//
// Created by unrelated on 2021/10/18.
//

#include "Stmt.h"
#include "../TokenNode.h"
#include "Cond.h"
#include "Exp.h"
#include "Block.h"
#include "LVal.h"
#include "../../Lexer/Token/STRCON.h"
#include "../../Exception/MyException/IllegalCharException.h"
#include "../../Exception/MyException/MismatchPlaceholderCountException.h"
#include "../../Lexer/Token/BREAKTK.h"
#include "../../Lexer/Token/CONTINUETK.h"
#include "../../Exception/MyException/ConBreakInNonLoopException.h"
#include "../../Exception/MyException/MissingSemicolonException.h"
#include "../../Lexer/Token/RETURNTK.h"

Stmt::Stmt(std::vector<std::shared_ptr<GramNode>> sons) : GramNode() {
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
bool
Stmt::create(std::vector<std::shared_ptr<GramNode>> &toAdd, std::vector<TokenBase *>::iterator &ite_p, bool isLoop) {
    auto ite = ite_p;
    std::vector<std::shared_ptr<GramNode>> son_ps;
    auto detectExp = [ite]() -> bool {
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
        if (!Stmt::create(son_ps, ite, isLoop)) {
            return false;
        }
        if (TokenNode::create(son_ps, ite, TokenBase::ELSETK)) {
            if (!Stmt::create(son_ps, ite, isLoop)) {
                return false;
            }
        }
        ite_p = ite;
        std::shared_ptr<Stmt> tmp_p;
        tmp_p.reset(new Stmt(son_ps));
        toAdd.push_back(tmp_p);
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
        if (!Stmt::create(son_ps, ite, true)) {
            return false;
        }
        ite_p = ite;
        std::shared_ptr<Stmt> tmp_p;
        tmp_p.reset(new Stmt(son_ps));
        toAdd.push_back(tmp_p);
        return true;
    } else if (TokenNode::create(son_ps, ite, TokenBase::BREAKTK) ||
               TokenNode::create(son_ps, ite, TokenBase::CONTINUETK)) {
        if (!TokenNode::create(son_ps, ite, TokenBase::SEMICN)) {
            return false;
        }
        ite_p = ite;
        std::shared_ptr<Stmt> tmp_p;
        tmp_p.reset(new Stmt(son_ps));
        toAdd.push_back(tmp_p);
        return true;
    } else if (TokenNode::create(son_ps, ite, TokenBase::RETURNTK)) {
        if (!TokenBase::isTypeOf(ite, TokenBase::SEMICN))
            if (!Exp::create(son_ps, ite))
                return false;
        if (!TokenNode::create(son_ps, ite, TokenBase::SEMICN)) {
            return false;
        }
        ite_p = ite;
        std::shared_ptr<Stmt> tmp_p;
        tmp_p.reset(new Stmt(son_ps));
        toAdd.push_back(tmp_p);
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
        std::shared_ptr<Stmt> tmp_p;
        tmp_p.reset(new Stmt(son_ps));
        toAdd.push_back(tmp_p);
        return true;
    } else if (TokenBase::isTypeOf(ite, TokenBase::LBRACE)) {
        if (!Block::create(son_ps, ite, isLoop, true)) {
            return false;
        }
        ite_p = ite;
        std::shared_ptr<Stmt> tmp_p;
        tmp_p.reset(new Stmt(son_ps));
        toAdd.push_back(tmp_p);
        return true;
    } else if (TokenBase::isTypeOf(ite, TokenBase::IDENFR) &&
               !TokenBase::isTypeOf(ite + 1, TokenBase::LPARENT)) {
        if (detectExp()) {
            if (!Exp::create(son_ps, ite))
                return false;
            if (!TokenNode::create(son_ps, ite, TokenBase::SEMICN)) {
                return false;
            }
            ite_p = ite;
            std::shared_ptr<Stmt> tmp_p;
            tmp_p.reset(new Stmt(son_ps));
            toAdd.push_back(tmp_p);
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
                std::shared_ptr<Stmt> tmp_p;
                tmp_p.reset(new Stmt(son_ps));
                toAdd.push_back(tmp_p);
                return true;
            } else {
                Exp::create(son_ps, ite);
                if (TokenBase::isTypeOf(ite, TokenBase::SEMICN)) {
                    TokenNode::create(son_ps, ite, TokenBase::SEMICN);
                    ite_p = ite;
                    std::shared_ptr<Stmt> tmp_p;
                    tmp_p.reset(new Stmt(son_ps));
                    toAdd.push_back(tmp_p);
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
        std::shared_ptr<Stmt> tmp_p;
        tmp_p.reset(new Stmt(son_ps));
        toAdd.push_back(tmp_p);
        return true;
    }
}

/**
 * get return type
 * @param toReturn return value here
 * @return false on fail, true on succeed
 */
bool Stmt::getReturnType(std::shared_ptr<IdentInfo> &toReturn) {
    auto firstTokenNode = std::dynamic_pointer_cast<TokenNode>(this->sons[0]);
    if (!firstTokenNode)
        return false;
    auto returnTk_p = std::dynamic_pointer_cast<RETURNTK>(firstTokenNode->getToken_p());
    if (!returnTk_p)
        return false;
    if (this->sons.size() > 1) {
        auto exp_p = std::dynamic_pointer_cast<Exp>(this->sons[1]);
        if (!exp_p)
            return false;
        return exp_p->getType(toReturn);
    }
    return false;
}
