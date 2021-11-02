//
// Created by unrelated on 2021/10/18.
//

#include "BType.h"


BType::BType(std::vector<std::shared_ptr<GramNode>> sons) : GramNode() {
    setGramName("BType");
    setSons(std::move(sons));
}

/**
 * BType -> 'int'
 * @param toAdd
 * @param ite_p
 * @return
 */
bool BType::create(std::vector<std::shared_ptr<GramNode>> &toAdd, std::vector<TokenBase *>::iterator &ite_p) {
    auto ite = ite_p;
    std::vector<std::shared_ptr<GramNode>> son_ps;
    if (!TokenNode::create(son_ps, ite, TokenBase::INTTK))
        return false;
    ite_p = ite;
    std::shared_ptr<BType> tmp_p;
    tmp_p.reset(new BType(son_ps));
    toAdd.push_back(tmp_p);
    return true;
}

void BType::myOutput() {
    for (auto &i: sons) {
        i->myOutput();
    }
}