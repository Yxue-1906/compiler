//
// Created by unrelated on 2021/12/22.
//

#ifndef SRC_PARSER_TESTNODE_H
#define SRC_PARSER_TESTNODE_H

#include "GramNode.h"

class TestNode : public GramNode {
private:
    TestNode(std::vector<std::shared_ptr<GramNode>> sons) {
        setGramName("TestNode");
        setSons(std::move(sons));
    }

public:
    static bool create(std::vector<std::shared_ptr<GramNode>> &sons, std::vector<TokenBase *>::iterator &) {
        //todo:
        return true;
    }

    virtual std::string toMidCode() override {
        return "";//todo:
    }


};


#endif //SRC_PARSER_TESTNODE_H
