//
// Created by unrelated on 2021/10/18.
//

#include "ConstDecl.h"
#include "../../Lexer/Token/CONSTTK.h"


ConstDecl::ConstDecl(std::vector<GramNode> sons) {
    setGramName("ConstDecl");
    setSons(std::move(sons));
}

bool ConstDecl::create(GramNode &toReturn, std::vector<Token *>::iterator &ite_p) {
    auto ite = ite_p;
    std::vector<GramNode *> sons;
    if (Token::type2Name.at(Token::getTokenType(**ite)) != "CONSTTK")
        throw new MyException();
    sons.push_back(static_cast<GramNode *const>(new TokenNode(**ite)));

}