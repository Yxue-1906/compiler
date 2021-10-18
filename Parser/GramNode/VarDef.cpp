//
// Created by unrelated on 2021/10/18.
//

#include "VarDef.h"
#include "../TokenNode.h"
#include "ConstExp.h"
#include "ConstInitVal.h"

VarDef::VarDef(std::vector<GramNode *> sons) {
    setGramName("VarDef");
    setSons(std::move(sons));
}

bool VarDef::create(GramNode *&toReturn, std::vector<Token *>::iterator &ite_p) {
    auto ite = ite_p;
    std::vector<GramNode *> son_ps;
    GramNode *nexNode;
    if (!(**ite).isTypeOf(Token::IDENFR)) {
        return false;
    }
    son_ps.push_back(new TokenNode(**ite));
    ++ite;
    if ((**ite).isTypeOf(Token::LBRACK)) {
        son_ps.push_back(new TokenNode(**ite));
        ++ite;
        if (!ConstExp::create(nexNode, ite)) {
            return false;
        }
        son_ps.push_back(nexNode);
        if (!(**ite).isTypeOf(Token::RBRACK)) {
            return false;
        }
        son_ps.push_back(new TokenNode(**ite));
        ++ite;
    }
    if ((**ite).isTypeOf(Token::EQL)) {
        son_ps.push_back(new TokenNode(**ite));
        ++ite;
        if (!ConstInitVal::create(nexNode, ite)) {
            return false;
        }
        son_ps.push_back(nexNode);
    }
    ite_p = ite;
    toReturn = new VarDef(son_ps);
    return true;
}