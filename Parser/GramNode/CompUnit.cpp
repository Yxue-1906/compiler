//
// Created by unrelated on 2021/10/17.
//

#include "CompUnit.h"

CompUnit::CompUnit(std::vector<Token> sons) {
    setGramName("CompUnit");
    setSons(sons);
}