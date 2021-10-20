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
        Exp::create(son_ps, ite);
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
    } else if (TokenNode::create(son_ps, ite, Token::LBRACE)) {
        if (!Block::create(son_ps, ite)) {
            return false;
        }
        ite_p = ite;
        toAdd.push_back(new Stmt(son_ps));
        return true;
    } else if (LVal::create(son_ps, ite)) {
        if (!TokenNode::create(son_ps, ite, Token::EQL)) {
            return false;
        }
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
        } else if (Exp::create(son_ps, ite)) {
            if (!TokenNode::create(son_ps, ite, Token::SEMICN)) {
                return false;
            }
            ite_p = ite;
            toAdd.push_back(new Stmt(son_ps));
            return true;
        }
        return false;
    }
}
