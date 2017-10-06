#pragma once
#include <vector>
#include <string>
#include "token.h"
#include <memory>
class exprtree {
public:
    int64_t m_intval;
    std::string m_strval;
    type m_type;
    std::vector<std::shared_ptr<exprtree>> subtrees;
    exprtree();
    ~exprtree();
};
