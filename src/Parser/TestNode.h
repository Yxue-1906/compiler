//
// Created by unrelated on 2021/12/22.
//

#ifndef SRC_PARSER_TESTNODE_H
#define SRC_PARSER_TESTNODE_H

#include "GramNode.h"
#include "GramNode/ConstDecl.h"

class TestNode : public GramNode {
private:
    TestNode(std::vector<std::shared_ptr<GramNode>> sons) {
        setGramName("TestNode");
        setSons(std::move(sons));
    }

public:
    static bool create(std::vector<std::shared_ptr<GramNode>> &toAdd, std::vector<TokenBase *>::iterator &ite_p) {
        auto ite = ite_p;
        std::vector<std::shared_ptr<GramNode>> son_ps;
        ConstDecl::create(son_ps, ite);
        ConstDecl::create(son_ps, ite);
        std::shared_ptr<TestNode> tmp_p;
        tmp_p.reset(new TestNode(son_ps));
        toAdd.push_back(tmp_p);
        return true;
    }

    virtual std::string toMidCode() override {
        for (auto node: this->sons) {
            node->toMidCode();
        }
        return "";//todo:
    }


};


#endif //SRC_PARSER_TESTNODE_H
