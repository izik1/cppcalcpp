#pragma once
#include <cstdint>
#include "exprtree.h"
class evaluator {
public:
    evaluator();
    int64_t evaluate(const std::shared_ptr<exprtree> tree);
private:
    int64_t evaluateInternal(const std::shared_ptr<exprtree> tree);
    std::unordered_map<std::string, int64_t> ids;
    int64_t evaluateOp(const std::shared_ptr<exprtree> lhs, int64_t rhs, type op);
};
