#include "stdafx.h"
#include "exprtree.h"

exprtree::exprtree() {
    subtrees = std::vector<std::shared_ptr<exprtree>>();
}

exprtree::~exprtree() {}
