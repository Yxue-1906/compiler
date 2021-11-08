//
// Created by unrelated on 2021/11/7.
//

#include "ErrorNode.h"

ErrorNode::ErrorNode(ErrorNode::ErrorType errorType) : errorType(errorType), lineNumber(GramNode::nowLine) {}

bool ErrorNode::checkValid() {
    return true;
}

void ErrorNode::updateLineNumber() {}

bool ErrorNode::create(std::vector<std::shared_ptr<GramNode>> son_ps, ErrorNode::ErrorType errorType) {
    switch (errorType) {
        case ErrorType::RIGHT_BRACKET:
            son_ps.push_back(std::make_shared<ErrorNode>(ErrorType::RIGHT_BRACKET));
            return true;
        case ErrorType::RIGHT_PARENTHESIS:
            son_ps.push_back(std::make_shared<ErrorNode>(ErrorType::RIGHT_PARENTHESIS));
            return true;
        default:
            //unreachable
            return false;
    }
}
