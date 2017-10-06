#include "stdafx.h"
#include "parser.h"
#include "token.h"
#include <unordered_map>
#include <iterator>
#include <cassert>

// larger number = higher precedence.
std::unordered_map<type, size_t> precedence = {
    {type::plus, 1},
    {type::minus, 1},
    {type::slash, 2},
    {type::carrot, 3},
    {type::astrisk, 2},
    {type::equals, 0},
};
std::unordered_map<type, bool> isRightAssositve = {
    {type::plus, false},
    {type::minus, false},
    {type::slash, false},
    {type::carrot, true},
    {type::equals, true},
    {type::astrisk, false},
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

std::shared_ptr<exprtree> parser::parseExpression1(std::shared_ptr<exprtree> lhs, size_t minPrecidence) {
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

        auto tree = std::make_shared<exprtree>(exprtree());
        tree->subtrees.push_back(lhs);
        tree->subtrees.push_back(rhs);
        tree->m_type = op.m_type;
        lhs = tree;
    }

    return lhs;
}

std::shared_ptr<exprtree> parser::parsePrimary() {
    auto tok = advance();
    switch(tok.m_type) {
    case type::num:
    {
        auto tree = std::make_shared<exprtree>(exprtree());
        tree->m_intval = tok.m_value;
        tree->m_type = type::num;
        return tree;
    }
    case type::paren_open:
    {
        auto tree = parseExpression1(parsePrimary(), 0);
        advance().expect(type::paren_close);
        return tree;
    }
    case type::minus:
    {
        tok = advance().expect(type::num);
        auto tree = std::make_shared<exprtree>(exprtree());
        tree->m_intval = -tok.m_value;
        tree->m_type = type::num;
        return tree;
    }

    case type::identifier:
    {
        auto tree = std::make_shared<exprtree>(exprtree());
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

std::shared_ptr<exprtree> parser::parse(std::vector<token>::iterator iterator) {
    return parser(iterator).parse();
}

std::shared_ptr<exprtree> parser::parse() {
    return parseExpression1(parsePrimary(), 0);
}
