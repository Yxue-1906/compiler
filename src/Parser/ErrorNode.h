//
// Created by unrelated on 2021/11/7.
//

#ifndef SRC_PARSER_ERRORNODE_H
#define SRC_PARSER_ERRORNODE_H


#include "GramNode.h"

class ErrorNode : public GramNode {
public:
    enum ErrorType {
        SEMICOLON,
        RIGHT_BRACKET,
        RIGHT_PARENTHESIS
    };

    ErrorNode(ErrorType errorType);

    virtual bool checkValid() override;

    virtual void updateLineNumber() override;

    static bool create(std::vector<std::shared_ptr<GramNode>> &son_ps, ErrorType errorType);

    int getLineNumber() const;

    ErrorType getErrorType() const;

private:
    const ErrorType errorType;
    const int lineNumber;
};


#endif //SRC_PARSER_ERRORNODE_H
