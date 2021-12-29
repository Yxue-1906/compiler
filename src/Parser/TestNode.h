//
// Created by unrelated on 2021/12/22.
//

#ifndef SRC_PARSER_TESTNODE_H
#define SRC_PARSER_TESTNODE_H

#include "GramNode.h"
#include "GramNode/ConstDecl.h"
#include "GramNode/VarDecl.h"
#include "../VM/PCode/PINT.h"
#include "GramNode/MainFuncDef.h"
#include "GramNode/FuncDef.h"
#include "../VM/PCode/J.h"
#include "../VM/PCode/LOD.h"

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
        //test begin
        FuncDef::create(son_ps, ite);
        MainFuncDef::create(son_ps, ite);

        //test end
        std::shared_ptr<TestNode> tmp_p;
        tmp_p.reset(new TestNode(son_ps));
        toAdd.push_back(tmp_p);
        return true;
    }

    virtual std::vector<std::shared_ptr<std::string>> toMidCode() override {
        labels.emplace("$init", MidCodeSequence.size());
        MidCodeSequence.push_back(std::make_shared<INTERPRETER::J>("$main"));
        for (auto node: this->sons) {
            node->toMidCode();
        }
        labels.emplace("$end", MidCodeSequence.size());
        return std::vector<std::shared_ptr<std::string>>{};
    }


};


#endif //SRC_PARSER_TESTNODE_H
