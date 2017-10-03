#include "stdafx.h"
#include "evaluator.h"
#include <cassert>

int32_t evaluateOp(int32_t lhs, int32_t rhs, std::string op) {
    if (op == "+")
    {
        return lhs + rhs;
    }
    if (op == "*")
    {
        return lhs * rhs;
    }
    if (op == "-")
    {
        return lhs - rhs;
    }
    if (op == "/")
    {
        return lhs / rhs;
    }
    assert(0);
    throw std::logic_error("unexpected op");
}

int32_t evaluator::evaluate(const exprtree* tree) {
    switch (tree->m_type) {
    case exprtree::op:
        assert(tree->subtrees.size() == 2);
        return evaluateOp(evaluate(tree->subtrees[0]), evaluate(tree->subtrees[1]), tree->m_strval);
    case exprtree::num: return tree->m_intval;
    default:
        assert(0);
        throw std::logic_error("Unexpected type in evaluation.");
    }
}
