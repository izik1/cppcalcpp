#include "stdafx.h"
#include "evaluator.h"
#include <cassert>

inline int64_t ipow(int64_t num, int64_t pow) {
    int64_t res = 1;
    for(int64_t i = 0; i < pow; i++) res *= num;
    return res;
}

int64_t evaluator::evaluateOp(const std::shared_ptr<exprtree> lhs, int64_t rhs, type op) {
    switch(op) {
    case type::plus: return evaluateInternal(lhs) + rhs;
    case type::minus: return evaluateInternal(lhs) - rhs;
    case type::astrisk: return evaluateInternal(lhs) * rhs;
    case type::slash: return evaluateInternal(lhs) / rhs;
    case type::carrot: return ipow(evaluateInternal(lhs), rhs);
    case type::equals:
        if(lhs.get()->m_strval[0] == '_') {
            throw std::logic_error("identifiers starting with underscores are reserved, "
                "and cannot be used on the left hand side of an assignment.");
        }
        ids.insert_or_assign(lhs->m_strval, rhs);
        return ids[lhs->m_strval];
    default: throw std::logic_error("unexpected op");
    }
}

int64_t evaluator::evaluate(const std::shared_ptr<exprtree> tree) {
    auto val = evaluateInternal(tree);
    for(int i = 10; i > 1; i--) {
        if(ids.find("_" + std::to_string(i - 1)) != ids.end()) {
            ids.insert_or_assign("_" + std::to_string(i), ids["_" + std::to_string(i - 1)]);
        }
    }

    ids.insert_or_assign("_", val);
    ids.insert_or_assign("_1", val);

    return val;
}

int64_t evaluator::evaluateInternal(const std::shared_ptr<exprtree> tree) {
    if(isOp(tree->m_type)) {
        assert(tree->subtrees.size() == 2);
        return evaluateOp(tree->subtrees[0], evaluate(tree->subtrees[1]), tree->m_type);
    }

    if(tree->m_type == type::identifier) {
        if(ids.find(tree->m_strval) != ids.end()) return ids[tree->m_strval];
        else throw std::logic_error("Undefined identifier: " + tree->m_strval);
    }
    if(tree->m_type == type::num) return tree->m_intval;
    throw std::logic_error("Unexpected type in evaluation.");
}

evaluator::evaluator() { ids = {}; }
