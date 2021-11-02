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
bool Stmt::create(std::vector<std::shared_ptr<GramNode>> &toAdd, std::vector<TokenBase *>::iterator &ite_p) {
    auto ite = ite_p;
    std::vector<std::shared_ptr<GramNode>> son_ps;
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
        if (!Stmt::create(son_ps, ite)) {
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
        try {
            auto tokenNode = std::dynamic_pointer_cast<TokenNode>(son_ps.back());
            auto strcon = std::dynamic_pointer_cast<STRCON>(tokenNode->getToken_p());//todo:check nullptr
            if (!strcon->checkValid()) {
                auto printfNode = std::dynamic_pointer_cast<TokenNode>(son_ps[0]);
                int lineNumber = printfNode->getToken_p()->getLineNumber();
                throw IllegalCharException(lineNumber);
            }
        } catch (IllegalCharException &e) {//todo
            e.myOutput();
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
        if (!Block::create(son_ps, ite)) {
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
            if (!TokenNode::create(son_ps, ite, TokenBase::SEMICN))
                return false;
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
