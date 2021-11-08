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
    if (!Block::create(son_ps, ite, false, true)) {
        return false;
    }
    ite_p = ite;
    std::shared_ptr<MainFuncDef> tmp_p;
    tmp_p.reset(new MainFuncDef(son_ps));
    toAdd.push_back(tmp_p);
    return true;
}

bool MainFuncDef::checkValid() {
    //get main token, prepare to get line number
    auto tokenNode = std::dynamic_pointer_cast<TokenNode>(sons[1]);
    auto mainTk = std::dynamic_pointer_cast<MAINTK>(tokenNode->getToken_p());

    //check if mis right parenthesis
    for (auto &i: sons) {
        i->updateLineNumber();
        auto errorNode = std::dynamic_pointer_cast<ErrorNode>(i);
        try {
            if (errorNode) {
                switch (errorNode->errorType) {
                    case ErrorNode::ErrorType::RIGHT_PARENTHESIS:
                        throw MissingRightParenthesisException(GramNode::nowLine);
                    default:
                        //unreachable
                        std::cout << __FILE__ << ':' << __LINE__ << ':' << "Unreachable" << std::endl;
                        break;
                }
            }
        } catch (MissingRightParenthesisException &e) {
            e.myOutput();
            return false;
        }
    }

    //check block valid
    auto block_p = std::dynamic_pointer_cast<Block>(sons.back());
    if (!block_p) {
        //unreachable
        std::cout << __FILE__ << ':' << __LINE__ << ':' << "Unreachable" << std::endl;
    }
    block_p->checkValid();

    //check return type
    std::shared_ptr<IdentInfo> returnType;
    try {
        if (!returnType || returnType->getDimension() != 0)
            throw MismatchReturnForNonVoidException(mainTk->getLineNumber());
    } catch (MismatchReturnForNonVoidException &e) {
        e.myOutput();
        return false;
    }
    return true;
}
