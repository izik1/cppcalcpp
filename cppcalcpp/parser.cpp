#include "stdafx.h"
#include "parser.h"
#include "token.h"
#include <map>
#include <iterator>
#include <cassert>

// larger number = higher precedence.
std::map<type, size_t> precedence = { {plus, 0 },{ minus, 0 },{ astrisk, 1 },{ slash , 1 } };
std::map<type, bool> isRightAssositve{ { plus, false },{ minus, false } , { astrisk, false },{ slash, false } };
token parser::peek() {
    return *(m_iterator);
}

token parser::current() {
    return *m_iterator;
}

token parser::advance() {
    return (*m_iterator++);
}

bool precidenceCompare(token a, token b) {
    return precedence[a.m_type] > precedence[b.m_type] ||
        (precedence[a.m_type] == precedence[b.m_type] && isRightAssositve[a.m_type]);
}

exprtree* parser::parseExpression1(exprtree* lhs, size_t minPrecidence)
{
    auto lookahead = peek();
    while (isOp(lookahead.m_type) && precedence[lookahead.m_type] >= minPrecidence)
    {
        auto op = lookahead;
        advance();
        auto rhs = parsePrimary();
        lookahead = peek();
        while (isOp(lookahead.m_type) && precidenceCompare(lookahead, op))
        {
            rhs = parseExpression1(rhs, precedence[lookahead.m_type]);
            lookahead = peek();
        }

        auto tree = new exprtree();
        tree->subtrees.push_back(lhs);
        tree->subtrees.push_back(rhs);
        tree->m_type = op.m_type;
        lhs = tree;
    }

    return lhs;
}

exprtree* parser::parsePrimary()
{
    auto token = advance();
    assert(token.m_type == type::num);
    auto tree = new exprtree();
    tree->m_intval = token.m_value;
    tree->m_type = type::num;
    return tree;
}

parser::parser(std::vector<token>::iterator iterator) {
    m_iterator = iterator;
}

exprtree* parser::parse() {
    return parseExpression1(parsePrimary(), 0);
}
