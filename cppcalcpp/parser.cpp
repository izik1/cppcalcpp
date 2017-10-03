#include "stdafx.h"
#include "parser.h"
#include "token.h"
#include <map>
#include <string>
#include <utility>
#include <iterator>
#include <iostream>
#include <cassert>

// larger number = higher precidence.
std::map<std::string, size_t> precidence = { {"+", 0 },{ "-", 0 },{ "*", 1 },{ "/", 1 } };
std::map<std::string, bool> isRightAssositve{ { "+", false },{ "-", false } , { "*", false },{ "/", false } };
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
    return precidence[a.m_value] > precidence[b.m_value] ||
        (precidence[a.m_value] == precidence[b.m_value] && isRightAssositve[a.m_value]);
}

exprtree* parser::parseExpression1(exprtree* lhs, size_t minPrecidence)
{
    auto lookahead = peek();
    while (lookahead.m_type == token::op && precidence[lookahead.m_value] >= minPrecidence)
    {
        auto op = lookahead;
        advance();
        auto rhs = parsePrimary();
        lookahead = peek();
        while (lookahead.m_type == token::op && precidenceCompare(lookahead, op))
        {
            rhs = parseExpression1(rhs, precidence[lookahead.m_value]);
            lookahead = peek();
        }

        auto tree = new exprtree();
        tree->subtrees.push_back(lhs);
        tree->subtrees.push_back(rhs);
        tree->m_type = exprtree::op;
        tree->m_strval = op.m_value;
        lhs = tree;
    }

    return lhs;
}

exprtree* parser::parsePrimary()
{
    auto token = advance();
    assert(token.m_type == token::num);
    auto tree = new exprtree();
    tree->m_intval = std::stoi(token.m_value);
    tree->m_type = exprtree::num;
    return tree;
}

parser::parser(std::vector<token>::iterator iterator) {
    m_iterator = iterator;
}

exprtree* parser::parse() {
    return parseExpression1(parsePrimary(), 0);
}
