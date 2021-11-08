//
// Created by unrelated on 2021/11/7.
//

#include "ErrorNode.h"

ErrorNode::ErrorNode(ErrorNode::ErrorType errorType) : errorType(errorType), lineNumber(GramNode::nowLine) {}

bool ErrorNode::checkValid() {
    return true;
}

void ErrorNode::updateLineNumber() {
    GramNode::nowLine = lineNumber;
}
