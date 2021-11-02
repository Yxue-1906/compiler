//
// Created by unrelated on 2021/10/18.
//

#include "Exp.h"
#include "AddExp.h"

Exp::Exp(std::vector<std::shared_ptr<GramNode>> sons) : GramNode() {
    setGramName("Exp");
    setSons(std::move(sons));
}

/**
 * Exp -> AddExp
 * @param toAdd
 * @param ite_p
 * @return
 */
bool Exp::create(std::vector<std::shared_ptr<GramNode>> &toAdd, std::vector<TokenBase *>::iterator &ite_p) {
    auto ite = ite_p;
    std::vector<std::shared_ptr<GramNode>> son_ps;
    if (!AddExp::create(son_ps, ite)) {
        return false;
    }
    ite_p = ite;
    std::shared_ptr<Exp> tmp_p;
    tmp_p.reset(new Exp(son_ps));
    toAdd.push_back(tmp_p);
    return true;
}

//bool Exp::create(std::vector<std::shared_ptr<GramNode>> &toAdd, std::vector<TokenBase *>::iterator &ite_p, LVal *lval) {
//    auto ite = ite_p;
//    std::vector<std::shared_ptr<GramNode>> son_ps;
//    son_ps.push_back(lval);
//    ite_p = ite;
//    std::shared_ptr<Exp> tmp_p;
//    tmp_p.reset(new Exp(son_ps));
//    toAdd.push_back(tmp_p);
//    return true;
//}