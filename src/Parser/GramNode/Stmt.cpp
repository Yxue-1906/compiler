//
// Created by unrelated on 2021/10/18.
//

#include "Stmt.h"
#include "../TokenNode.h"
#include "Cond.h"
#include "Exp.h"
#include "Block.h"
#include "../../Lexer/Token/STRCON.h"
#include "../../Exception/MyException/IllegalCharException.h"
#include "../../Exception/MyException/MismatchPlaceholderCountException.h"
#include "../../Lexer/Token/BREAKTK.h"
#include "../../Lexer/Token/CONTINUETK.h"
#include "../../Exception/MyException/ConBreakInNonLoopException.h"
#include "../../Lexer/Token/RETURNTK.h"
#include "../../Lexer/Token/PRINTFTK.h"
#include "../../Lexer/Token/COMMA.h"
#include "../ErrorNode.h"
#include "../../Exception/MyException/AssignToConstException.h"

Stmt::Stmt(std::vector<std::shared_ptr<GramNode>> sons, bool isLoop)
        : GramNode(), isLoop(isLoop) {
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
Stmt::create(std::vector<std::shared_ptr<GramNode>> &toAdd, std::vector<TokenBase *>::iterator &ite_p, bool isLoop) {
    auto ite = ite_p;
    std::vector<std::shared_ptr<GramNode>> son_ps;
    auto detectExp = [ite]() -> bool {
        if (!TokenBase::isTypeOf(ite, TokenBase::IDENFR))
            return true;
        int index = 1;
        for (int leftLBrackets = 0; leftLBrackets != 0 || TokenBase::isTypeOf(ite + index, TokenBase::LBRACK);) {
            if (TokenBase::isTypeOf(ite + index, TokenBase::RBRACK))
                leftLBrackets--;
            else if (TokenBase::isTypeOf(ite + index, TokenBase::LBRACK))
                leftLBrackets++;
            index++;
        }
        if (TokenBase::isTypeOf(ite + index, TokenBase::ASSIGN))
            return false;
        return true;
    };
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
        if (!Stmt::create(son_ps, ite, isLoop)) {
            return false;
        }
        if (TokenNode::create(son_ps, ite, TokenBase::ELSETK)) {
            if (!Stmt::create(son_ps, ite, isLoop)) {
                return false;
            }
        }
        ite_p = ite;
        std::shared_ptr<Stmt> tmp_p;
        tmp_p.reset(new Stmt(son_ps, isLoop));
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
        if (!Stmt::create(son_ps, ite, true)) {
            return false;
        }
        ite_p = ite;
        std::shared_ptr<Stmt> tmp_p;
        tmp_p.reset(new Stmt(son_ps, isLoop));
        toAdd.push_back(tmp_p);
        return true;
    } else if (TokenNode::create(son_ps, ite, TokenBase::BREAKTK) ||
               TokenNode::create(son_ps, ite, TokenBase::CONTINUETK)) {
        if (!TokenNode::create(son_ps, ite, TokenBase::SEMICN)) {
            ErrorNode::create(son_ps, ErrorNode::ErrorType::SEMICOLON);
        }
        ite_p = ite;
        std::shared_ptr<Stmt> tmp_p;
        tmp_p.reset(new Stmt(son_ps, isLoop));
        toAdd.push_back(tmp_p);
        return true;
    } else if (TokenNode::create(son_ps, ite, TokenBase::RETURNTK)) {
        if (!TokenBase::isTypeOf(ite, TokenBase::SEMICN))
            if (!Exp::create(son_ps, ite))
                return false;
        if (!TokenNode::create(son_ps, ite, TokenBase::SEMICN)) {
            ErrorNode::create(son_ps, ErrorNode::ErrorType::SEMICOLON);
        }
        ite_p = ite;
        std::shared_ptr<Stmt> tmp_p;
        tmp_p.reset(new Stmt(son_ps, isLoop));
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
        tmp_p.reset(new Stmt(son_ps, isLoop));
        toAdd.push_back(tmp_p);
        return true;
    } else if (TokenBase::isTypeOf(ite, TokenBase::LBRACE)) {
        if (!Block::create(son_ps, ite, isLoop)) {
            return false;
        }
        ite_p = ite;
        std::shared_ptr<Stmt> tmp_p;
        tmp_p.reset(new Stmt(son_ps, isLoop));
        toAdd.push_back(tmp_p);
        return true;
    } else if (TokenBase::isTypeOf(ite, TokenBase::IDENFR) &&
               !TokenBase::isTypeOf(ite + 1, TokenBase::LPARENT)) {
        if (detectExp()) {
            if (!Exp::create(son_ps, ite))
                return false;
            if (!TokenNode::create(son_ps, ite, TokenBase::SEMICN)) {
                ErrorNode::create(son_ps, ErrorNode::ErrorType::SEMICOLON);
            }
            ite_p = ite;
            std::shared_ptr<Stmt> tmp_p;
            tmp_p.reset(new Stmt(son_ps, isLoop));
            toAdd.push_back(tmp_p);
            return true;
        } else {
            if (!LVal::create(son_ps, ite))
                return false;
            if (!TokenNode::create(son_ps, ite, TokenBase::ASSIGN))
                return false;
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
                tmp_p.reset(new Stmt(son_ps, isLoop));
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
                tmp_p.reset(new Stmt(son_ps, isLoop));
                toAdd.push_back(tmp_p);
                return true;
            }
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
        tmp_p.reset(new Stmt(son_ps, isLoop));
        toAdd.push_back(tmp_p);
        return true;
    }
}

bool Stmt::checkValid() {
    bool toReturn = true;
    auto ite = sons.begin();
    std::shared_ptr<TokenNode> tokenNode_p;
    tokenNode_p = std::dynamic_pointer_cast<TokenNode>(*ite);
    if (tokenNode_p) {
        try {
            if (isConBreak() && !isLoop) {
                auto token_p = tokenNode_p->getToken_p();
                throw ConBreakInNonLoopException(token_p->getLineNumber());
            }
        } catch (ConBreakInNonLoopException &e) {
            e.myOutput();
            return false;
        }
        auto printfTk_p = std::dynamic_pointer_cast<PRINTFTK>(tokenNode_p->getToken_p());
        if (printfTk_p) {
            try {
                ite += 2;
                tokenNode_p = std::dynamic_pointer_cast<TokenNode>(*ite);
                auto formatString_p = std::dynamic_pointer_cast<STRCON>(tokenNode_p->getToken_p());
                if (!formatString_p->checkValid())
                    throw IllegalCharException(formatString_p->getLineNumber());
                int count = 0;
                std::shared_ptr<Exp> exp_p;
                while (ite != sons.end()) {
                    tokenNode_p = std::dynamic_pointer_cast<TokenNode>(*ite);
                    if (tokenNode_p && std::dynamic_pointer_cast<COMMA>(tokenNode_p->getToken_p())) {
                        count++;
                    } else if ((exp_p = std::dynamic_pointer_cast<Exp>(*ite))) {
                        if (!exp_p->checkValid())
                            return false;
                    } else {
                        //be errorNode or right parenthesis
                        break;
                    }
                    ite++;
                }
                if (count != formatString_p->getCount())
                    throw MismatchPlaceholderCountException(printfTk_p->getLineNumber());
                for (; ite != sons.end(); ++ite) {
                    toReturn &= (*ite)->checkValid();
                }
            } catch (MyException &e) {
                e.myOutput();
                return false;
            }
            return true;
        }
        for (auto &i: sons) {
            toReturn &= i->checkValid();
        }
        return toReturn;
    }
    auto lval = std::dynamic_pointer_cast<LVal>(*ite);
    if (lval) {
        if (!lval->checkValid())
            return false;
        std::shared_ptr<IdentInfo> identType;
        if (!lval->getType(identType)) {
            std::cout << "unreachable" << std::endl;
        }
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
    for (auto &i: sons) {
        if (!i->checkValid())
            return false;
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
bool Stmt::isNonVoidReturn() {
    auto ite = sons.begin();
    auto tokenNode_p = std::dynamic_pointer_cast<TokenNode>(*ite);
    if (tokenNode_p && std::dynamic_pointer_cast<RETURNTK>(tokenNode_p->getToken_p())) {
        if (sons.size() > 2)
            return true;
    }
    return false;
}



