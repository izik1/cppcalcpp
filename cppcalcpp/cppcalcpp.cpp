// cppcalcpp.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include "lexer.h"
#include "token.h"
#include "parser.h"
#include "evaluator.h"

void printTree(std::shared_ptr<exprtree> tree, size_t indent) {
    std::cout << std::string(indent, ' ') << (isOp(tree->m_type) ? typeStringMap[tree->m_type] :
        tree->m_type == type::identifier ? tree->m_strval : std::to_string(tree->m_intval)) << std::endl;
    for each (auto sub in tree->subtrees) printTree(sub, indent + 1);
}

int main() {
    evaluator eval{};
    while(true) {
        std::string str;
        std::getline(std::cin, str);
        std::vector<token> tokens = lexer::lex(str);
        auto tree = parser::parse(tokens.begin());
        std::cout << "Output: " << eval.evaluate(tree) << std::endl;
    }

    return 0;
}
