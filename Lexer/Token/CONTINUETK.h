//
// Created by unrelated on 2021/10/17.
//

#ifndef PARSER_CONTINUETK_H
#define PARSER_CONTINUETK_H


class CONTINUETK : public Token{
private:
public:
    CONTINUETK() : Token(Token::CONTINUETK){
        setValue_p(new std::string("continue"));
    }

public:
};


#endif //PARSER_CONTINUETK_H
