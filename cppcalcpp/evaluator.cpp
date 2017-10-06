#include "stdafx.h"
#include "evaluator.h"
#include <cassert>

inline int64_t ipow(int64_t num, int64_t pow) {
    int64_t res = 1;
    for(int64_t i = 0; i < pow; i++) {
        res *= num;
    }

    return res;
}

int64_t evaluator::evaluateOp(const std::shared_ptr<exprtree> lhs, int64_t rhs, type op) {
    switch(op) {
    case plus:
        return evaluate(lhs) + rhs;
    case minus:
        return evaluate(lhs) - rhs;
    case astrisk:
        return evaluate(lhs) * rhs;
    case slash:
        return evaluate(lhs) / rhs;
    case carrot:
        return ipow(evaluate(lhs), rhs);
    case equals:
        ids.insert_or_assign(lhs->m_strval, rhs);
        return ids[lhs->m_strval];
    case num:
    case eof:
    default:
        throw std::logic_error("unexpected op");
    }
}

int64_t evaluator::evaluate(const std::shared_ptr<exprtree> tree) {
    if(isOp(tree->m_type)) {
        assert(tree->subtrees.size() == 2);
        return evaluateOp(tree->subtrees[0], evaluate(tree->subtrees[1]), tree->m_type);
    }

    if(tree->m_type == identifier) {
        if(ids.find(tree->m_strval) != ids.end()) return ids[tree->m_strval];
        else throw std::logic_error("Undefined identifier: " + tree->m_strval);
    }
    if(tree->m_type == num) return tree->m_intval;
    throw std::logic_error("Unexpected type in evaluation.");
}

evaluator::evaluator() { ids = {}; }
