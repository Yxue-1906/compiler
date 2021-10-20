//
// Created by unrelated on 2021/10/18.
//

#include "ValDecl.h"
#include "BType.h"

ValDecl::ValDecl(std::vector<GramNode *> sons) {
    setGramName("ValDecl");
    setSons(std::move(sons));
}

bool ValDecl::create(std::vector<GramNode *> &toAdd, std::vector<Token *>::iterator &ite_p) {
    auto ite = ite_p;
    std::vector<GramNode *> son_ps;
    if (!BType::create(son_ps, ite)) {
        return false;
    }

}