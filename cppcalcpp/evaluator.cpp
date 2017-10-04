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

int64_t evaluateOp(int64_t lhs, int64_t rhs, type op) {
    switch(op) {
    case plus:
        return lhs + rhs;
    case minus:
        return lhs - rhs;
    case astrisk:
        return lhs * rhs;
    case slash:
        return lhs / rhs;
    case carrot:
        return ipow(lhs, rhs);
    case num:
    case eof:
    default:
        throw std::logic_error("unexpected op");
    }
}

int64_t evaluator::evaluate(const exprtree* tree) {
    if(isOp(tree->m_type)) {
        assert(tree->subtrees.size() == 2);
        return evaluateOp(evaluate(tree->subtrees[0]), evaluate(tree->subtrees[1]), tree->m_type);
    }

    if(tree->m_type == num) return tree->m_intval;
    throw std::logic_error("Unexpected type in evaluation.");
}
