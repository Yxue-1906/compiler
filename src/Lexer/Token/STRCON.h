#include <utility>

//
// Created by unrelated on 2021/10/17.
//

#ifndef PARSER_STRCON_H
#define PARSER_STRCON_H


class STRCON : public Token<std::string> {
private:
    int count = -1;
public:
    STRCON(const std::string &value)
            : Token(TokenBase::STRCON, std::make_shared<std::string>(value)) {}

public:
    bool checkValid() {
        bool toReturn = true;
        this->count = 0;
        auto ite = this->value_p->begin();
        ite++;
        for (; ite != this->value_p->end(); ++ite) {
            if (*ite == '\\') {
                if (ite + 1 != this->value_p->end() && *(ite + 1) == 'n')
                    ite++;
                else
                    toReturn = false;
            } else if (*ite == '%') {
                if (ite + 1 != this->value_p->end() && *(ite + 1) == 'd')
                    this->count++, ite++;
                else
                    toReturn = false;
            }
        }
        return toReturn;
    }

    int getCount() {
        if (count == -1) {
            checkValid();
        }
        return count;
    }
};


#endif //PARSER_STRCON_H
