//
// Created by unrelated on 2021/10/17.
//

#ifndef PARSER_NOT_H
#define PARSER_NOT_H


class NOT : public Token {
private:
    const std::string value;
public:
    NOT() : Token(11), value("!") {}

public:
    virtual void myOutput() override {
        std::ofstream &ofs = getOfs();
        ofs << getTokenName() << ' ' << value << std::endl;
    }
};


#endif //PARSER_NOT_H
