#include "stdafx.h"
#include "lexer.h"
#include "token.h"
#include <map>
std::map<std::string, type> operators{
    {"+", type::plus},
    {"-", type::minus},
    {"*", type::astrisk},
    {"/", type::slash},
};

inline bool isOp(const std::string p_in) {
    return operators.find(p_in) != operators.end();
}

std::vector<token> lexer::lex(std::string str) {
    std::vector<token> vec = std::vector<token>();
    int start = 0;
    int len = 0;
    for (size_t i = 0; i < str.size(); i++) {
        if (isOp(str.substr(i, 1))) {
            vec.push_back(token(num, std::stoi(str.substr(start, len))));
            vec.push_back(token(operators[str.substr(i, 1)], 0));
            len = 0;
            start = i + 1;
        }
        else
        {
            len++;
        }
    }

    if (len > 0) {
        vec.push_back(token(num, std::stoi(str.substr(start, len))));
    }

    vec.push_back(token(end, 0));
    return vec;
}
