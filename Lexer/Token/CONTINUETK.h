//
// Created by unrelated on 2021/10/17.
//

#ifndef PARSER_CONTINUETK_H
#define PARSER_CONTINUETK_H


class CONTINUETK : public Token{
private:
    const std::string value;
public:
    CONTINUETK() : Token(8), value("continue") {}

public:
    virtual void myOutput() override {
        std::ofstream &ofs = getOfs();
        ofs << getTokenName() << ' ' << value << std::endl;
    }
};


#endif //PARSER_CONTINUETK_H
