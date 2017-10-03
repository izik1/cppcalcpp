// cppcalcpp.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include "lexer.h"
#include "token.h"
#include "parser.h"
#include "evaluator.h"
void printTree(exprtree* tree, size_t indent) {
    std::cout << std::string(indent, ' ') <<
        (tree->m_type == exprtree::op ? tree->m_strval : std::to_string(tree->m_intval)) << std::endl;
    for each (auto sub in tree->subtrees)
    {
        printTree(sub, indent + 1);
    }
}

int main()
{
    std::string str;
    std::cin >> str;
    std::cin.ignore();
    std::vector<token> tokens = lexer::lex(str);
    auto tree = parser(tokens.begin()).parse();
    std::cout << "Output: " << evaluator::evaluate(tree) << std::endl;
    return 0;
}
