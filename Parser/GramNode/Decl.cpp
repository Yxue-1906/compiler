//
// Created by unrelated on 2021/10/18.
//

#include "Decl.h"
#include "ConstDecl.h"

Decl::Decl(std::vector<GramNode *> sons) {
    setGramName("Decl");
    setSons(std::move(sons));
}

bool Decl::create(std::vector<GramNode *> &toAdd, std::vector<Token *>::iterator &ite_p) {
    auto ite = ite_p;
    std::vector<GramNode *> son_ps;
    if ((**ite).isTypeOf(Token::CONSTTK)) {
        if (!ConstDecl::create(son_ps, ite)) {
            return false;
        }
        toAdd.push_back(new Decl(son_ps));
    } else {
        if (!VarDecl::create(son_ps, ite))
    }

}