#pragma once
#include <vector>
#include <string>
#include "token.h"
class exprtree {
public:
    int64_t m_intval;
    type m_type;
    std::vector<exprtree*> subtrees;
    exprtree();
    ~exprtree();
};
