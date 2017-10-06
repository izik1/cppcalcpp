#pragma once
#include <cstdint>
#include "exprtree.h"
class evaluator {
public:
    std::unordered_map<std::string, int64_t> ids;
    evaluator();
    int64_t evaluate(const std::shared_ptr<exprtree> tree);
    int64_t evaluateOp(const std::shared_ptr<exprtree> lhs, int64_t rhs, type op);
};
