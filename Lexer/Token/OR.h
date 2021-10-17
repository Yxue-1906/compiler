//
// Created by unrelated on 2021/10/17.
//

#ifndef PARSER_OR_H
#define PARSER_OR_H


class OR: public Token {
private:
    const std::string value;
public:
    OR() : Token(13), value("||") {}

public:
    virtual void myOutput() override {
        std::ofstream ofs = getOfs();
        ofs << getTokenName() << ' ' << value << std::endl;
    }
};


#endif //PARSER_OR_H
