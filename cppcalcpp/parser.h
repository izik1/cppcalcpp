#pragma once
#include <vector>
#include "exprtree.h"
#include <deque>
class token;
class parser {
public:
    parser(std::vector<token>::iterator iterator);
    static exprtree* parse(std::vector<token>::iterator iterator);
    exprtree* parse();
private:
    std::vector<token>::iterator m_iterator;
    token peek();
    token advance();
    token current();
    exprtree* parseExpression1(exprtree* lhs, size_t minPrecidence);
    exprtree* parsePrimary();
};
