//
// Created by unrelated on 2021/10/18.
//

#include "UnaryOp.h"
#include "../TokenNode.h"

UnaryOp::UnaryOp(std::vector<std::shared_ptr<GramNode>> sons) : GramNode() {
    setGramName("UnaryOp");
    setSons(std::move(sons));
}

bool UnaryOp::create(std::vector<std::shared_ptr<GramNode>> &toAdd, std::vector<TokenBase *>::iterator &ite_p) {
    auto ite = ite_p;
    std::vector<std::shared_ptr<GramNode>> son_ps;
    std::shared_ptr<UnaryOp> tmp_p;
    if (TokenNode::create(son_ps, ite, TokenBase::PLUS)) {
        tmp_p.reset(new UnaryOp(son_ps));
        tmp_p->type = UnaryOp::Type::PLUS;
    } else if (TokenNode::create(son_ps, ite, TokenBase::MINU)) {
        tmp_p.reset(new UnaryOp(son_ps));
        tmp_p->type = UnaryOp::Type::MINUS;
    } else if (TokenNode::create(son_ps, ite, TokenBase::NOT)) {
        tmp_p.reset(new UnaryOp(son_ps));
        tmp_p->type = UnaryOp::Type::NOT;
    }
    if (!son_ps.empty()) {
        toAdd.push_back(tmp_p);
        ite_p = ite;
        return true;
    } else {
        return false;
    }
}

UnaryOp::Type UnaryOp::getType() {
    return this->type;
}
