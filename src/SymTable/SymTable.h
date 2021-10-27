//
// Created by unrelated on 2021/10/26.
//

#ifndef PARSER_SYMTABLE_H
#define PARSER_SYMTABLE_H


#include <string>
#include <map>
#include <memory>
#include <iostream>
#include <vector>

class Info;

class Ident {
public:
    Ident(int type) : type(type);

public:
    static int INDENT;
    static int FUNC;
private:
    const int type;
    std::shared_ptr<Info *> info_p;
};

class Info {
private:
    virtual void do_init() = 0;
};

class IdentInfo : public Info {
private:
    virtual void do_init() override {}

public:
    IdentInfo(std::string name, bool const isArray, int const *value, const int count)
            : name(name), isArray(isArray), value(value), count(count) {}

    const std::string &queryName() {
        return this->name;
    }

    int queryValue(int index) {
        if (isArray && index < count)return value[index];
        else if (index > count) {
            std::cerr << "maybe out of bounds" << std::endl;
            return value[index];
        }
    }

    int queryCount() {
        return this->count;
    }

private:
    std::string name;
    int const *value;
    const int count;

public:
    const bool isArray;
};

class FuncInfo : public Info {
private:
    void do_init() override {}

public:
    FuncInfo(int type, int count) : type(type), count(count) {}

public:
    static int VOID_F;
    static int INT_F;
private:
    const int type;
    const int count;
};

class SymTable {
private:
    std::map<std::string, Ident> symTable;
    std::shared_ptr<SymTable> former = nullptr;

public:
    bool  queryIdent(std::string name);
};


#endif //PARSER_SYMTABLE_H
