//
// Created by unrelated on 2021/10/17.
//

#ifndef PARSER_NEQ_H
#define PARSER_NEQ_H


class NEQ : public Token {
private:
    const std::string value;
public:
    NEQ() : Token(29), value("!=") {}

public:
    virtual void myOutput() override {
        std::ofstream ofs =std::move(getOfs()) ;
        ofs << getTokenName() << ' ' << value << std::endl;
    }
};

#endif //PARSER_NEQ_H
