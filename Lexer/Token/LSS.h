//
// Created by unrelated on 2021/10/17.
//

#ifndef PARSER_LSS_H
#define PARSER_LSS_H


class LSS : public Token {
private:
    const std::string value;
public:
    LSS() : Token(24), value("<") {}

public:
    virtual void myOutput() override {
        std::ofstream ofs = getOfs();
        ofs << getTokenName() << ' ' << value << std::endl;
    }
};

#endif //PARSER_LSS_H
