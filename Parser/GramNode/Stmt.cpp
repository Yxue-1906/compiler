//
// Created by unrelated on 2021/10/18.
//

#include "Stmt.h"
#include "../TokenNode.h"
#include "Cond.h"
#include "Exp.h"
#include "Block.h"
#include "LVal.h"

Stmt::Stmt(std::vector<GramNode *> sons) {
    setGramName("Stmt");
    setSons(std::move(sons));
}

bool Stmt::create(std::vector<GramNode *> &toAdd, std::vector<Token *>::iterator &ite_p) {
    auto ite = ite_p;
    std::vector<GramNode *> son_ps;
    GramNode *nexNode;
    if ((**ite).isTypeOf(Token::IFTK)) {
        son_ps.push_back(new TokenNode(**ite));
        ++ite;
        if (!(**ite).isTypeOf(Token::LPARENT)) {
            return false;
        }
        son_ps.push_back(new TokenNode(**ite));
        ++ite;
        if (!Cond::create(nexNode, ite)) {
            return false;
        }
        if (!(**ite).isTypeOf(Token::RPARENT)) {
            return false;
        }
        son_ps.push_back(new TokenNode(**ite));
        ++ite;
        if (!Stmt::create(nexNode, ite)) {
            return false;
        }
        son_ps.push_back(nexNode);
        if ((**ite).isTypeOf(Token::ELSETK)) {
            son_ps.push_back(new TokenNode(**ite));
            ++ite;
            if (!Stmt::create(nexNode, ite)) {
                return false;
            }
            son_ps.push_back(nexNode);
        }
        ite_p = ite;
        toAdd = new Stmt(son_ps);
        return true;
    } else if ((**ite).isTypeOf(Token::WHILETK)) {
        son_ps.push_back(new TokenNode(**ite));
        ++ite;
        if (!(**ite).isTypeOf(Token::LPARENT)) {
            return false;
        }
        son_ps.push_back(new TokenNode(**ite));
        ++ite;
        if (!Cond::create(nexNode, ite)) {
            return false;
        }
        son_ps.push_back(nexNode);
        if (!Stmt::create(nexNode, ite)) {
            return false;
        }
        son_ps.push_back(nexNode);
        ite_p = ite;
        toAdd = new Stmt(son_ps);
        return true;
    } else if ((**ite).isTypeOf(Token::BREAKTK) || (**ite).isTypeOf(Token::CONTINUETK)) {
        son_ps.push_back(new TokenNode(**ite));
        ++ite;
        if (!(**ite).isTypeOf(Token::SEMICN)) {
            return false;
        }
        son_ps.push_back(new TokenNode(**ite));
        ++ite;
        ite_p = ite;
        toAdd = new Stmt(son_ps);
        return true;
    } else if ((**ite).isTypeOf(Token::RETURNTK)) {
        son_ps.push_back(new TokenNode(**ite));
        ++ite;
        if (Exp::create(nexNode, ite)) {
            son_ps.push_back(nexNode);
        }
        if (!(**ite).isTypeOf(Token::SEMICN)) {
            return false;
        }
        son_ps.push_back(new TokenNode(**ite));
        ++ite;
        ite_p = ite;
        toAdd = new Stmt(son_ps);
        return true;
    } else if ((**ite).isTypeOf(Token::PRINTFTK)) {
        son_ps.push_back(new TokenNode(**ite));
        ++ite;
        if (!(**ite).isTypeOf(Token::LPARENT)) {
            return false;
        }
        son_ps.push_back(new TokenNode(**ite));
        ++ite;
        if (!(**ite).isTypeOf(Token::STRCON)) {
            return false;
        }
        son_ps.push_back(new TokenNode(**ite));
        ++ite;
        for (; (**ite).isTypeOf(Token::COMMA);) {
            son_ps.push_back(new TokenNode(**ite));
            ++ite;
            if (!Exp::create(nexNode, ite)) {
                return false;
            }
            son_ps.push_back(nexNode);
        }
        if (!(**ite).isTypeOf(Token::RPARENT)) {
            return false;
        }
        son_ps.push_back(new TokenNode(**ite));
        ++ite;
        if (!(**ite).isTypeOf(Token::SEMICN)) {
            return false;
        }
        son_ps.push_back(new TokenNode(**ite));
        ++ite;
        ite_p = ite;
        toAdd = new Stmt(son_ps);
        return true;
    } else if ((**ite).isTypeOf(Token::LBRACE)) {
        if (!Block::create(nexNode, ite)) {
            return false;
        }
        son_ps.push_back(nexNode);
        ite_p = ite;
        toAdd = new Stmt(son_ps);
        return true;
    } else if (LVal::create(nexNode, ite)) {
        son_ps.push_back(nexNode);
        if (!TokenNode::create(nexNode, ite, Token::EQL)) {
            return false;
        }
        son_ps.push_back(nexNode);
        if (TokenNode::create(nexNode, ite, Token::GETINTTK)) {
            son_ps.push_back(nexNode);
            if (!TokenNode::create(nexNode, ite, Token::LPARENT)) {
                return false;
            }
            son_ps.push_back(nexNode);
            if (!TokenNode::create(nexNode, ite, Token::RPARENT)) {
                return false;
            }
            son_ps.push_back(nexNode);
            if
        }
    }


}
