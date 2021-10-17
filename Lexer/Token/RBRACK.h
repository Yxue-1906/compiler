//
// Created by unrelated on 2021/10/17.
//

#ifndef PARSER_RBRACK_H
#define PARSER_RBRACK_H


class RBRACK : public Token {
private:
    const std::string value;
public:
    RBRACK() : Token(36), value("]") {}

public:
    virtual void myOutput() override {
        std::ofstream &ofs = getOfs();
        ofs << getTokenName() << ' ' << value << std::endl;
    }
};


#endif //PARSER_RBRACK_H
