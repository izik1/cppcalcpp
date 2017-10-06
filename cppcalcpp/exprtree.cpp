#include "stdafx.h"
#include "exprtree.h"

exprtree::exprtree() {
    subtrees = std::vector<exprtree*>();
}

exprtree::~exprtree() {
    for each (auto tree in subtrees) delete tree;
}
