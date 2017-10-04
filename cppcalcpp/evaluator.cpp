#include "stdafx.h"
#include "evaluator.h"
#include <cassert>

int32_t evaluateOp(int32_t lhs, int32_t rhs, type op) {
    switch(op) {
    case plus:
        return lhs + rhs;
    case minus:
        return lhs - rhs;
    case astrisk:
        return lhs * rhs;
    case slash:
        return lhs / rhs;
    case num:
    case eof:
    default:
        throw std::logic_error("unexpected op");
    }
}

int32_t evaluator::evaluate(const exprtree* tree) {
    if(isOp(tree->m_type)) {
        assert(tree->subtrees.size() == 2);
        return evaluateOp(evaluate(tree->subtrees[0]), evaluate(tree->subtrees[1]), tree->m_type);
    }

    if(tree->m_type == num) return tree->m_intval;
    throw std::logic_error("Unexpected type in evaluation.");
}
