//
// Created by unrelated on 2021/10/18.
//

#include "Stmt.h"
#include "../TokenNode.h"
#include "Cond.h"

Stmt::Stmt(std::vector<GramNode *> sons) {
    setGramName("Stmt");
    setSons(std::move(sons));
}

bool Stmt::create(GramNode *&toReturn, std::vector<Token *>::iterator &ite_p) {
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
        toReturn = new Stmt(son_ps);
        return true;
    } else if ((**ite).isTypeOf(Token::WHILETK)) {
        son_ps.push_back(new TokenNode(**ite));
        ++ite;
        if(!)
    }

}
