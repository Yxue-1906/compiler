//
// Created by unrelated on 2021/10/18.
//

#include "MainFuncDef.h"
#include "../TokenNode.h"
#include "Block.h"
#include "../ErrorNode.h"
#include "../../Exception/MyException/MissingRightParenthesisException.h"
#include "../../Lexer/Token/MAINTK.h"
#include "../../Exception/MyException/MismatchReturnForNonVoidException.h"

MainFuncDef::MainFuncDef(std::vector<std::shared_ptr<GramNode>> sons) : GramNode() {
    setGramName("MainFuncDef");
    setSons(std::move(sons));
}

/**
 * MainFuncDef -> 'int' 'main' '(' ')' Block
 * @param toAdd
 * @param ite_p
 * @return
 */
bool MainFuncDef::create(std::vector<std::shared_ptr<GramNode>> &toAdd, std::vector<TokenBase *>::iterator &ite_p) {
    auto ite = ite_p;
    std::vector<std::shared_ptr<GramNode>> son_ps;
    GramNode *nexNode;
    if (!TokenNode::create(son_ps, ite, TokenBase::INTTK)) {
        return false;
    }
    if (!TokenNode::create(son_ps, ite, TokenBase::MAINTK)) {
        return false;
    }
    if (!TokenNode::create(son_ps, ite, TokenBase::LPARENT)) {
        return false;
    }
    if (!TokenNode::create(son_ps, ite, TokenBase::RPARENT)) {
        ErrorNode::create(son_ps, ErrorNode::ErrorType::RIGHT_PARENTHESIS);
    }
    if (!Block::create(son_ps, ite, false, false)) {
        return false;
    }
    ite_p = ite;
    std::shared_ptr<MainFuncDef> tmp_p;
    tmp_p.reset(new MainFuncDef(son_ps));
    toAdd.push_back(tmp_p);
    return true;
}

bool MainFuncDef::checkValid() {
    bool toReturn = true;
    //get main token, prepare to get line number
    auto tokenNode = std::dynamic_pointer_cast<TokenNode>(sons[1]);
    auto mainTk = std::dynamic_pointer_cast<MAINTK>(tokenNode->getToken_p());

    //check if mis right parenthesis
    GramNode::setNowTable(std::make_shared<SymTable>(GramNode::getNowTable()));
    for (auto &i: sons) {
        i->checkValid();
    }

    //check return type
    auto block_p = std::dynamic_pointer_cast<Block>(sons.back());
    std::shared_ptr<IdentInfo> returnType;
    toReturn &= block_p->checkReturn(false);
    return toReturn;
}

std::string MainFuncDef::toMidCode() {
    labels.emplace("main", MidCodeSequence.size());
    auto block_p = std::dynamic_pointer_cast<Block>(this->sons[4]);
    if (!block_p) {
        block_p->toMidCode();
    }
    return "";
}
