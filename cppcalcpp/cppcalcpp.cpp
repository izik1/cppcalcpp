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
        (isOp(tree->m_type) ? typeToString[tree->m_type] : std::to_string(tree->m_intval)) << std::endl;
    for each (auto sub in tree->subtrees) {
        printTree(sub, indent + 1);
    }
}

int main() {
    evaluator eval{};
    while(true) {
        std::string str;
        std::getline(std::cin, str);
        std::vector<token> tokens = lexer::lex(str);
        auto tree = parser(tokens.begin()).parse();

        //printTree(tree, 0);
        std::cout << "Output: " << eval.evaluate(tree) << std::endl;
    }

    return 0;
}
