//
// Created by unrelated on 2021/10/18.
//

#include "ValDecl.h"
#include "BType.h"

ValDecl::ValDecl(std::vector<GramNode *> sons) {
    setGramName("ValDecl");
    setSons(std::move(sons));
}

bool ValDecl::create(GramNode *&toReturn, std::vector<Token *>::iterator &ite_p) {
    auto ite = ite_p;
    std::vector<GramNode *> son_ps;
    GramNode *nexNode;
    if (!BType::create(nexNode, ite)) {
        return false;
    }
    son_ps.push_back(nexNode);

}