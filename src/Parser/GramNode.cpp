//
// Created by unrelated on 2021/10/17.
//

#include "GramNode.h"

#include <utility>

int GramNode::nowLine = 0;
std::shared_ptr<SymTable>GramNode::nowTable_p = std::make_shared<SymTable>(nullptr);

GramNode::GramNode() = default;

void GramNode::setGramName(std::string gramName) {
    this->gramName = std::move(gramName);
}

void GramNode::setSons(std::vector<std::shared_ptr<GramNode>> sons) {
    this->sons = std::move(sons);
}

void GramNode::myOutput() {
    for (auto &i: sons) {
        i->myOutput();
    }
    std::ostream *os = getOs();
    (*os) << '<' << gramName << '>' << std::endl;
}

std::vector<std::shared_ptr<GramNode>> GramNode::getSons() {
    return this->sons;
}

std::shared_ptr<GramNode> GramNode::getSonByIndex(int index) {
    if (index < this->sons.size()) {
        return this->sons[index];
    }
    return nullptr;
}

std::string &GramNode::getGramName() {
    return this->gramName;
}

std::shared_ptr<SymTable> GramNode::getNowTable() {
    return GramNode::nowTable_p;
}

void GramNode::updateLineNumber() {
    this->sons.back()->updateLineNumber();
}

