//
// Created by unrelated on 2021/10/18.
//
#include "../TokenNode.h"
#include "../ErrorNode.h"
#include "Stmt.h"
#include "Cond.h"
#include "Exp.h"
#include "Block.h"
#include "../../Lexer/Token/STRCON.h"
#include "../../Lexer/Token/BREAKTK.h"
#include "../../Lexer/Token/CONTINUETK.h"
#include "../../Lexer/Token/RETURNTK.h"
#include "../../Lexer/Token/PRINTFTK.h"
#include "../../Lexer/Token/COMMA.h"
#include "../../Exception/MyException/IllegalCharException.h"
#include "../../Exception/MyException/MismatchPlaceholderCountException.h"
#include "../../Exception/MyException/ConBreakInNonLoopException.h"
#include "../../Exception/MyException/AssignToConstException.h"
#include "../../Exception/MyException/MismatchReturnForVoidException.h"
#include "../../VM/PCode/STO.h"
#include "../../VM/PCode/PSTR.h"
#include "../../VM/PCode/PINT.h"
#include "../../VM/PCode/BRT.h"
#include "../../VM/PCode/BRF.h"
#include "../../VM/PCode/J.h"
#include "../../VM/PCode/RET.h"

Stmt::Stmt(std::vector<std::shared_ptr<GramNode>> sons, bool isLoop, bool isVoid)
        : GramNode(), isLoop(isLoop), isVoid(isVoid) {
    setGramName("Stmt");
    setSons(std::move(sons));
}

/**
 * Stmt -> 'if' '(' Cond ')' Stmt [ 'else' Stmt ] |
 *         'while' '(' Cond ')' Stmt |
 *         'break' ';' | 'continue' ';'|
 *         'return' [Exp] ';' |
 *         'printf' '(' FormatString{',' Exp} ')' ';'
 *         Block |
 *         LVal '=' Exp ';' |
 *         [Exp] ';' |
 *         LVal '=' 'getint' '(' ')' ';' |
 *
 * @param toAdd
 * @param ite_p
 * @return
 */
bool
Stmt::create(std::vector<std::shared_ptr<GramNode>> &toAdd, std::vector<TokenBase *>::iterator &ite_p, bool isLoop,
             bool isVoid) {
    auto ite = ite_p;
    std::vector<std::shared_ptr<GramNode>> son_ps;
    if (TokenNode::create(son_ps, ite, TokenBase::IFTK)) {
        if (!TokenNode::create(son_ps, ite, TokenBase::LPARENT)) {
            return false;
        }
        if (!Cond::create(son_ps, ite)) {
            return false;
        }
        if (!TokenNode::create(son_ps, ite, TokenBase::RPARENT)) {
            ErrorNode::create(son_ps, ErrorNode::ErrorType::RIGHT_PARENTHESIS);
        }
        if (!Stmt::create(son_ps, ite, isLoop, isVoid)) {
            return false;
        }
        if (TokenNode::create(son_ps, ite, TokenBase::ELSETK)) {
            if (!Stmt::create(son_ps, ite, isLoop, isVoid)) {
                return false;
            }
        }
        ite_p = ite;
        std::shared_ptr<Stmt> tmp_p;
        tmp_p.reset(new Stmt(son_ps, isLoop, isVoid));
        toAdd.push_back(tmp_p);
        return true;
    } else if (TokenNode::create(son_ps, ite, TokenBase::WHILETK)) {
        if (!TokenNode::create(son_ps, ite, TokenBase::LPARENT)) {
            return false;
        }
        if (!Cond::create(son_ps, ite)) {
            return false;
        }
        if (!TokenNode::create(son_ps, ite, TokenBase::RPARENT)) {
            ErrorNode::create(son_ps, ErrorNode::ErrorType::RIGHT_PARENTHESIS);
        }
        if (!Stmt::create(son_ps, ite, true, isVoid)) {
            return false;
        }
        ite_p = ite;
        std::shared_ptr<Stmt> tmp_p;
        tmp_p.reset(new Stmt(son_ps, isLoop, isVoid));
        toAdd.push_back(tmp_p);
        return true;
    } else if (TokenNode::create(son_ps, ite, TokenBase::BREAKTK) ||
               TokenNode::create(son_ps, ite, TokenBase::CONTINUETK)) {
        if (!TokenNode::create(son_ps, ite, TokenBase::SEMICN)) {
            ErrorNode::create(son_ps, ErrorNode::ErrorType::SEMICOLON);
        }
        ite_p = ite;
        std::shared_ptr<Stmt> tmp_p;
        tmp_p.reset(new Stmt(son_ps, isLoop, isVoid));
        toAdd.push_back(tmp_p);
        return true;
    } else if (TokenNode::create(son_ps, ite, TokenBase::RETURNTK)) {
        if (!TokenBase::isTypeOf(ite, TokenBase::SEMICN))
//            if (!Exp::create(son_ps, ite))
//                return false;
            Exp::create(son_ps, ite);
        if (!TokenNode::create(son_ps, ite, TokenBase::SEMICN)) {
            ErrorNode::create(son_ps, ErrorNode::ErrorType::SEMICOLON);
        }
        ite_p = ite;
        std::shared_ptr<Stmt> tmp_p;
        tmp_p.reset(new Stmt(son_ps, isLoop, isVoid));
        toAdd.push_back(tmp_p);
        return true;
    } else if (TokenNode::create(son_ps, ite, TokenBase::PRINTFTK)) {
        if (!TokenNode::create(son_ps, ite, TokenBase::LPARENT)) {
            return false;
        }
        if (!TokenNode::create(son_ps, ite, TokenBase::STRCON)) {
            return false;
        }
        for (; TokenNode::create(son_ps, ite, TokenBase::COMMA);) {
            if (!Exp::create(son_ps, ite)) {
                return false;
            }
        }
        if (!TokenNode::create(son_ps, ite, TokenBase::RPARENT)) {
            ErrorNode::create(son_ps, ErrorNode::ErrorType::RIGHT_PARENTHESIS);
        }
        if (!TokenNode::create(son_ps, ite, TokenBase::SEMICN)) {
            ErrorNode::create(son_ps, ErrorNode::ErrorType::SEMICOLON);
        }
        ite_p = ite;
        std::shared_ptr<Stmt> tmp_p;
        tmp_p.reset(new Stmt(son_ps, isLoop, isVoid));
        toAdd.push_back(tmp_p);
        return true;
    } else if (TokenBase::isTypeOf(ite, TokenBase::LBRACE)) {
        if (!Block::create(son_ps, ite, isLoop, isVoid)) {
            return false;
        }
        ite_p = ite;
        std::shared_ptr<Stmt> tmp_p;
        tmp_p.reset(new Stmt(son_ps, isLoop, isVoid));
        toAdd.push_back(tmp_p);
        return true;
    } else if (TokenBase::isTypeOf(ite, TokenBase::IDENFR) &&
               !TokenBase::isTypeOf(ite + 1, TokenBase::LPARENT)) {
        if (!Exp::create(son_ps, ite))
            return false;
        auto exp_p = std::dynamic_pointer_cast<Exp>(son_ps.back());
        if (TokenBase::isTypeOf(ite, TokenBase::ASSIGN)) {
            son_ps.pop_back();
            std::shared_ptr<GramNode> gramNode_p;
            if (!exp_p->getLVal(gramNode_p))
                return false;
            auto lval_p = std::dynamic_pointer_cast<LVal>(gramNode_p);
            if (!lval_p)
                return false;
            son_ps.push_back(lval_p);
            TokenNode::create(son_ps, ite, TokenBase::ASSIGN);
            if (TokenNode::create(son_ps, ite, TokenBase::GETINTTK)) {
                if (!TokenNode::create(son_ps, ite, TokenBase::LPARENT)) {
                    return false;
                }
                if (!TokenNode::create(son_ps, ite, TokenBase::RPARENT)) {
                    ErrorNode::create(son_ps, ErrorNode::ErrorType::RIGHT_PARENTHESIS);
                }
                if (!TokenNode::create(son_ps, ite, TokenBase::SEMICN)) {
                    ErrorNode::create(son_ps, ErrorNode::ErrorType::SEMICOLON);
                }
                ite_p = ite;
                std::shared_ptr<Stmt> tmp_p;
                tmp_p.reset(new Stmt(son_ps, isLoop, isVoid));
                toAdd.push_back(tmp_p);
                return true;
            } else {
                Exp::create(son_ps, ite);
                if (TokenBase::isTypeOf(ite, TokenBase::SEMICN)) {
                    TokenNode::create(son_ps, ite, TokenBase::SEMICN);
                } else {
                    ErrorNode::create(son_ps, ErrorNode::ErrorType::SEMICOLON);
                }
                ite_p = ite;
                std::shared_ptr<Stmt> tmp_p;
                tmp_p.reset(new Stmt(son_ps, isLoop, isVoid));
                toAdd.push_back(tmp_p);
                return true;
            }
        } else {
            if (!TokenNode::create(son_ps, ite, TokenBase::SEMICN)) {
                ErrorNode::create(son_ps, ErrorNode::ErrorType::SEMICOLON);
            }
            ite_p = ite;
            std::shared_ptr<Stmt> tmp_p;
            tmp_p.reset(new Stmt(son_ps, isLoop, isVoid));
            toAdd.push_back(tmp_p);
            return true;
        }
    } else {
        if (!TokenBase::isTypeOf(ite, TokenBase::SEMICN))
            if (!Exp::create(son_ps, ite))
                return false;
        if (!TokenNode::create(son_ps, ite, TokenBase::SEMICN)) {
            ErrorNode::create(son_ps, ErrorNode::ErrorType::SEMICOLON);
        }
        ite_p = ite;
        std::shared_ptr<Stmt> tmp_p;
        tmp_p.reset(new Stmt(son_ps, isLoop, isVoid));
        toAdd.push_back(tmp_p);
        return true;
    }
}

bool Stmt::checkValid() {
    bool toReturn = true;
    auto ite = sons.begin();
    std::shared_ptr<TokenNode> tokenNode_p;
    tokenNode_p = std::dynamic_pointer_cast<TokenNode>(*ite);
    try {
        if (isConBreak() && !isLoop) {
            auto token_p = tokenNode_p->getToken_p();
            throw ConBreakInNonLoopException(token_p->getLineNumber());
        }
    } catch (ConBreakInNonLoopException &e) {
        e.myOutput();
        return false;
    }
    if (tokenNode_p && std::dynamic_pointer_cast<PRINTFTK>(tokenNode_p->getToken_p())) {
        auto printfTk_p = std::dynamic_pointer_cast<PRINTFTK>(tokenNode_p->getToken_p());
        ite += 2;
        tokenNode_p = std::dynamic_pointer_cast<TokenNode>(*ite);
        auto formatString_p = std::dynamic_pointer_cast<STRCON>(tokenNode_p->getToken_p());
        bool isValid = formatString_p->checkValid();
        ++ite;
        int count = 0;
        std::shared_ptr<Exp> exp_p;
        for (; (tokenNode_p = std::dynamic_pointer_cast<TokenNode>(*ite));) {
            if (!std::dynamic_pointer_cast<COMMA>(tokenNode_p->getToken_p()))
                break;
            count++;
            ite++;
            if (!(exp_p = std::dynamic_pointer_cast<Exp>(*ite)))
                return false;
            if (!exp_p->checkValid())
                return false;
            ite++;
        }
        try {
            if (count != formatString_p->getCount())
                throw MismatchPlaceholderCountException(printfTk_p->getLineNumber());
        } catch (MyException &e) {
            e.myOutput();
//            return false;
        }
        try {
            if (!isValid)
                throw IllegalCharException(formatString_p->getLineNumber());
        } catch (MyException &e) {
            e.myOutput();
            return false;
        }
    } else if (tokenNode_p && std::dynamic_pointer_cast<RETURNTK>(tokenNode_p->getToken_p())) {
        auto returnTk_p = std::dynamic_pointer_cast<RETURNTK>(tokenNode_p->getToken_p());
        try {
            if (isVoid && sons.size() > 2)
                throw MismatchReturnForVoidException(returnTk_p->getLineNumber());
        } catch (MyException &e) {
            e.myOutput();
            return false;
        }
        ++ite;
    }
    auto block_p = std::dynamic_pointer_cast<Block>(*ite);
    if (block_p) {
        GramNode::setNowTable(std::make_shared<SymTable>(GramNode::getNowTable()));
        if (!block_p->checkValid())
            return false;
        for (++ite; ite != sons.end(); ++ite)
            toReturn &= (*ite)->checkValid();
        return toReturn;
    }
    auto lval = std::dynamic_pointer_cast<LVal>(*ite);
    if (lval) {
        if (!lval->checkValid()) {
            toReturn = false;
        } else {
            std::shared_ptr<IdentInfo> identType;
            lval->getType(identType);
            try {
                if (identType->checkConst()) {
                    lval->updateLineNumber();
                    throw AssignToConstException(GramNode::nowLine);
                }
            } catch (MyException &e) {
                e.myOutput();
                return false;
            }//todo: check right parenthesis
        }
        ++ite;
    }
    for (; ite != sons.end(); ++ite) {
        toReturn &= (*ite)->checkValid();
    }
    return toReturn;
}

bool Stmt::isConBreak() {
    auto tokenNode = std::dynamic_pointer_cast<TokenNode>(sons[0]);
    if (!tokenNode)
        return false;
    auto continueTk = std::dynamic_pointer_cast<CONTINUETK>(tokenNode->getToken_p());
    if (continueTk)
        return true;
    auto breakTk = std::dynamic_pointer_cast<BREAKTK>(tokenNode->getToken_p());
    if (breakTk)
        return true;
    return false;
}

/**
 * get return type
 * @param toReturn return value here
 * @return false on fail, true on succeed
 */
bool Stmt::hasReturn() {
    auto ite = sons.begin();
    auto tokenNode_p = std::dynamic_pointer_cast<TokenNode>(*ite);
    if (tokenNode_p && std::dynamic_pointer_cast<RETURNTK>(tokenNode_p->getToken_p()))
        return true;
    else
        return false;
}

std::vector<std::shared_ptr<std::string>> Stmt::toMidCode() {
    std::vector<std::shared_ptr<std::string>> toReturn;
    auto ite = sons.begin();
    auto tokenNode_p = std::dynamic_pointer_cast<TokenNode>(*ite);
    if (tokenNode_p) {
        if (tokenNode_p->getToken_p()->getTokenType() == TokenBase::SEMICN) {
            return toReturn;
        }
        if (tokenNode_p->getToken_p()->getTokenType() == TokenBase::IFTK) {
            //todo: maybe finished
            ite += 2;
            auto cond_p = std::dynamic_pointer_cast<Cond>(*ite);
            auto formerOrLabels = orLabels;
            orLabels = std::make_shared<std::vector<int>>();
            auto tmpVars_p = cond_p->toMidCode();
            auto nowLabel = "$" + std::to_string(nowLabelCount++);
            for (int i: *orLabels) {
                auto brt_p = std::dynamic_pointer_cast<INTERPRETER::BRT>(MidCodeSequence[i]);
                if (brt_p) {
                    brt_p->setLabel(nowLabel);
                } else {
                    //should not run to here!
                    int tmp;
                    std::cout << "error!" << std::endl;
                    std::cin >> tmp;
                }
            }
            orLabels = formerOrLabels;
            labels.emplace(nowLabel, MidCodeSequence.size() + 1);
            nowLabel = "$" + std::to_string(nowLabelCount++);
            MidCodeSequence.push_back(std::make_shared<INTERPRETER::BRF>(*tmpVars_p[0], nowLabel));
            ite += 2;
            auto stmt_p = std::dynamic_pointer_cast<Stmt>(*ite);
            stmt_p->toMidCode();
            ite += 2;
            if (ite < sons.end()) {
                labels.emplace(nowLabel, MidCodeSequence.size() + 1);
                nowLabel = "$" + std::to_string(nowLabelCount++);
                MidCodeSequence.push_back(std::make_shared<INTERPRETER::J>(nowLabel));
                stmt_p = std::dynamic_pointer_cast<Stmt>(*ite);
                stmt_p->toMidCode();
                labels.emplace(nowLabel, MidCodeSequence.size());
            } else {
                labels.emplace(nowLabel, MidCodeSequence.size());
            }
            return toReturn;
        }
        if (tokenNode_p->getToken_p()->getTokenType() == TokenBase::WHILETK) {
            //todo: while (cond) block
            ite += 2;
            auto cond_p = std::dynamic_pointer_cast<Cond>(*ite);
            auto beforeCondLabel = "$" + std::to_string(nowLabelCount++);
            labels.emplace(beforeCondLabel, MidCodeSequence.size());
            auto formerOrLabels = orLabels;
            orLabels = std::make_shared<std::vector<int>>();
            auto tmpVars_p = cond_p->toMidCode();
            auto fromOrLabel = "$" + std::to_string(nowLabelCount++);
            for (int i: *orLabels) {
                auto brt_p = std::dynamic_pointer_cast<INTERPRETER::BRT>(MidCodeSequence[i]);
                if (brt_p) {
                    brt_p->setLabel(fromOrLabel);
                } else {
                    //should not run to here!
                    int tmp;
                    std::cout << "error!" << std::endl;
                    std::cin >> tmp;
                }
            }
            orLabels = formerOrLabels;
            labels.emplace(fromOrLabel, MidCodeSequence.size() + 1);
            ite += 2;
            auto afterBlockLabel = "$" + std::to_string(nowLabelCount++);
            MidCodeSequence.push_back(std::make_shared<INTERPRETER::BRF>(*tmpVars_p[0], afterBlockLabel));
            auto formerBreakLabels = breakLabels;
            auto formerContinueLabels = continueLabels;
            breakLabels = std::make_shared<std::vector<int>>();
            continueLabels = std::make_shared<std::vector<int>>();
            auto stmt_p = std::dynamic_pointer_cast<Stmt>(*ite);
            stmt_p->toMidCode();
            for (int i: *breakLabels) {
                auto j_p = std::dynamic_pointer_cast<INTERPRETER::J>(MidCodeSequence[i]);
                if (j_p) {
                    j_p->setLabel(afterBlockLabel);
                } else {
                    //should not run to here!
                    int tmp;
                    std::cout << "error!" << std::endl;
                    std::cin >> tmp;
                }
            }
            for (int i: *continueLabels) {
                auto j_p = std::dynamic_pointer_cast<INTERPRETER::J>(MidCodeSequence[i]);
                if (j_p) {
                    j_p->setLabel(beforeCondLabel);
                } else {
                    //should not run to here!
                    int tmp;
                    std::cout << "error!" << std::endl;
                    std::cin >> tmp;
                }
            }
            breakLabels = formerBreakLabels;
            continueLabels = formerContinueLabels;
            MidCodeSequence.push_back(std::make_shared<INTERPRETER::J>(beforeCondLabel));
            labels.emplace(afterBlockLabel, MidCodeSequence.size());
            return toReturn;
        }
        if (tokenNode_p->getToken_p()->getTokenType() == TokenBase::BREAKTK) {
            breakLabels->push_back(MidCodeSequence.size());
            MidCodeSequence.push_back(std::make_shared<INTERPRETER::J>());
            return toReturn;
        }
        if (tokenNode_p->getToken_p()->getTokenType() == TokenBase::CONTINUETK) {
            continueLabels->push_back(MidCodeSequence.size());
            MidCodeSequence.push_back(std::make_shared<INTERPRETER::J>());
            return toReturn;
        }
        if (tokenNode_p->getToken_p()->getTokenType() == TokenBase::RETURNTK) {
            if (sons.size() > 1) {
                auto exp_p = std::dynamic_pointer_cast<Exp>(sons[1]);
                auto tmpVars_p = exp_p->toMidCode();
                MidCodeSequence.push_back(std::make_shared<INTERPRETER::STO>(*tmpVars_p[0], "%ret", "0"));
            }
            MidCodeSequence.push_back(std::make_shared<INTERPRETER::RET>());
            return toReturn;
        }
        if (tokenNode_p->getToken_p()->getTokenType() == TokenBase::PRINTFTK) {
            ite += 2;
            tokenNode_p = std::dynamic_pointer_cast<TokenNode>(*ite);
            auto formatString_p = std::dynamic_pointer_cast<STRCON>(tokenNode_p->getToken_p())->getValue_p();
            auto formatString = std::string{formatString_p->substr(1, formatString_p->size() - 2)};
            ite += 2;
            for (int i = 0; i < formatString.size();) {
                if (formatString[i] == '%' && i + 1 < formatString.size() && formatString[i + 1] == 'd') {
                    auto exp_p = std::dynamic_pointer_cast<Exp>(*ite);
                    auto tmpVars_p = exp_p->toMidCode();
                    auto tmpVar = *tmpVars_p[0];
                    MidCodeSequence.push_back(std::make_shared<INTERPRETER::PINT>(tmpVar));
                    i += 2;
                    ite += 2;
                    continue;
                }
                if (formatString[i] == '\\' && i + 1 < formatString.size() && formatString[i + 1] == 'n') {
                    MidCodeSequence.push_back(std::make_shared<INTERPRETER::PSTR>("\n"));
                    i += 2;
                    continue;
                }
                MidCodeSequence.push_back(std::make_shared<INTERPRETER::PSTR>(std::string{formatString[i]}));
                ++i;
            }
            return toReturn;
        }
        //should not run to here
    } else {
        auto exp_p = std::dynamic_pointer_cast<Exp>(*ite);
        if (exp_p) {
            exp_p->toMidCode();
            return toReturn;
        }
        auto lval_p = std::dynamic_pointer_cast<LVal>(*ite);
        if (lval_p) {
            ite += 2;
            auto lvalBaseOffset = lval_p->getAddr();
            exp_p = std::dynamic_pointer_cast<Exp>(*ite);
            if (exp_p) {
                auto tmpVars = exp_p->toMidCode();
                auto tmpVar_p = tmpVars[0];
                MidCodeSequence.push_back(std::make_shared<INTERPRETER::STO>(
                        *tmpVar_p,
                        *lvalBaseOffset.first,
                        *lvalBaseOffset.second));
                return toReturn;
            }
            tokenNode_p = std::dynamic_pointer_cast<TokenNode>(*ite);
            if (tokenNode_p && tokenNode_p->getToken_p()->getTokenType() == TokenBase::GETINTTK) {
                int value;
                std::cin >> value;
                MidCodeSequence.push_back(std::make_shared<INTERPRETER::STO>(
                        std::to_string(value),
                        *lvalBaseOffset.first,
                        *lvalBaseOffset.second));
                return toReturn;
            }
            //should not run to here!
            int tmp;
            std::cout << "error occurred when run to stmt->lval" << std::endl;
            std::cin >> tmp;
        }
        auto block_p = std::dynamic_pointer_cast<Block>(*ite);
        if (block_p) {
            symTableGenCode.newStack();
            block_p->toMidCode();
            symTableGenCode.deleteStack();
            return toReturn;
        }
        //should not run to here?
    }
    //should not run to here
    int tmp;
    std::cout << "error occurred in stmt" << std::endl;
    std::cin >> tmp;
}



