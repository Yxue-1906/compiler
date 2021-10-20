//
// Created by unrelated on 2021/10/18.
//

#include "BType.h"


BType::BType(std::vector<GramNode *> sons) {
    setGramName("BType");
    setSons(std::move(sons));
}
/**
 * BType -> 'int'
 * @param toAdd
 * @param ite_p
 * @return
 */
bool BType::create(std::vector<GramNode *> &toAdd, std::vector<Token *>::iterator &ite_p) {
    auto ite = ite_p;
    std::vector<GramNode *> son_ps;
    if (!TokenNode::create(son_ps, ite, Token::INTTK))
        return false;
    ite_p = ite;
    toAdd .push_back(new BType(son_ps));
    return true;
}