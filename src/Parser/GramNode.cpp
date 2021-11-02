//
// Created by unrelated on 2021/10/17.
//

#include "GramNode.h"

#include <utility>

GramNode::GramNode() = default;

void GramNode::setGramName(std::string gramName) {
    this->GramName = std::move(gramName);
}

void GramNode::setSons(std::vector<std::shared_ptr<GramNode>> sons) {
    this->sons = std::move(sons);
}

void GramNode::myOutput() {
    for (auto &i: sons) {
        i->myOutput();
    }
    std::ostream *os = getOs();
    (*os) << '<' << GramName << '>' << std::endl;
}

