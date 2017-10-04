#include "stdafx.h"
#include "parser.h"
#include "token.h"
#include <unordered_map>
#include <iterator>
#include <cassert>

// larger number = higher precedence.
std::unordered_map<type, size_t> precedence = {
    {plus, 1},
    {minus, 1},
    {slash, 2},
    {carrot, 3},
    {astrisk, 2},
    {equals, 0},
};
std::unordered_map<type, bool> isRightAssositve = {
    {plus, false},
    {minus, false},
    {slash, false},
    {carrot, true},
    {equals, true},
    {astrisk, false},
};

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

exprtree* parser::parseExpression1(exprtree* lhs, size_t minPrecidence) {
    auto lookahead = peek();
    while(isOp(lookahead.m_type) && precedence[lookahead.m_type] >= minPrecidence) {
        auto op = lookahead;
        advance();
        auto rhs = parsePrimary();
        lookahead = peek();
        while(isOp(lookahead.m_type) && precidenceCompare(lookahead, op)) {
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

exprtree* parser::parsePrimary() {
    auto tok = advance();
    switch(tok.m_type) {
    case type::num:
    {
        auto tree = new exprtree();
        tree->m_intval = tok.m_value;
        tree->m_type = type::num;
        return tree;
    }
    case type::paren_open:
    {
        exprtree* tree = parseExpression1(parsePrimary(), 0);
        tok = advance();
        if(tok.m_type != type::paren_close) throw std::logic_error("Invalid operation (missing closing parens)");
        return tree;
    }
    case type::minus:
    {
        tok = advance();
        assert(tok.m_type == type::num);
        auto tree = new exprtree();
        tree->m_intval = -tok.m_value;
        tree->m_type = type::num;
        return tree;
    }

    case type::identifier:
    {
        auto tree = new exprtree();
        tree->m_strval = tok.m_strval;
        tree->m_type = type::identifier;
        return tree;
    }

    default:
        throw std::logic_error("Invalid operation");
    }
}

parser::parser(std::vector<token>::iterator iterator) {
    m_iterator = iterator;
}

exprtree* parser::parse() {
    return parseExpression1(parsePrimary(), 0);
}
