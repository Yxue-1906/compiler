//
// Created by unrelated on 2021/10/17.
//

#ifndef PARSER_CONSTTK_H
#define PARSER_CONSTTK_H


class CONSTTK : public Token {
private:
    const std::string value;
public:
    CONSTTK() : Token(5), value("const") {}

public:
    virtual void myOutput() override {
        std::ofstream &ofs = getOfs();
        ofs << getTokenName() << ' ' << value << std::endl;
    }
};


#endif //PARSER_CONSTTK_H
