//
// Created by unrelated on 2021/11/7.
//

#include "ErrorNode.h"
#include "../Exception/MyException/MissingRightParenthesisException.h"
#include "../Exception/MyException/MissingRightBracketException.h"
#include "../Exception/MyException/MissingSemicolonException.h"

ErrorNode::ErrorNode(ErrorNode::ErrorType errorType)
        : errorType(errorType), lineNumber(GramNode::nowLine) {}

bool ErrorNode::checkValid() {
    try {
        switch (this->errorType) {
            case ErrorType::RIGHT_PARENTHESIS:
                throw MissingRightParenthesisException(this->lineNumber);
            case ErrorType::RIGHT_BRACKET:
                throw MissingRightBracketException(this->lineNumber);
            case ErrorType::SEMICOLON:
                throw MissingSemicolonException(this->lineNumber);
        }
    } catch (MyException &e) {
        e.myOutput();
        return false;
    }
}

void ErrorNode::updateLineNumber() {
    GramNode::nowLine = this->lineNumber;
}

bool ErrorNode::create(std::vector<std::shared_ptr<GramNode>> &son_ps, ErrorNode::ErrorType errorType) {
    switch (errorType) {
        case ErrorType::RIGHT_BRACKET:
            son_ps.push_back(std::make_shared<ErrorNode>(ErrorType::RIGHT_BRACKET));
            return true;
        case ErrorType::RIGHT_PARENTHESIS:
            son_ps.push_back(std::make_shared<ErrorNode>(ErrorType::RIGHT_PARENTHESIS));
            return true;
        case ErrorType::SEMICOLON:
            son_ps.push_back(std::make_shared<ErrorNode>(ErrorType::SEMICOLON));
        default:
            //unreachable
            return false;
    }
}

int ErrorNode::getLineNumber() const {
    return this->lineNumber;
}

ErrorNode::ErrorType ErrorNode::getErrorType() const {
    return this->errorType;
}
