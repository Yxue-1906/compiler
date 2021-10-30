//
// Created by unrelated on 2021/10/17.
//

#ifndef PARSER_LSS_H
#define PARSER_LSS_H


class LSS : public Token<std::string> {
private:
public:
    LSS() : Token(TokenBase::LSS,
                  std::make_shared<std::string>("<")) {}

public:
};

#endif //PARSER_LSS_H
