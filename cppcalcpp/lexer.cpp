#include "stdafx.h"
#include "lexer.h"
#include "token.h"

std::vector<std::string> ops{ "+", "*", "-", "/" };

inline std::string substr(const std::string p_str, const size_t p_start, const size_t p_end) {
    return p_str.substr(p_start, p_end - p_start);
}

inline bool contains(const std::string p_str, const std::string p_substr) {
    return p_str.find(p_substr) != std::string::npos;
}

inline bool isOp(const std::string p_in) {
    for each (std::string op in ops) {
        if (op == p_in) {
            return true;
        }
    }

    return false;
}

std::vector<token> lexer::lex(std::string str) {
    std::vector<token> vec = std::vector<token>();
    int start = 0;
    int len = 0;
    for (size_t i = 0; i < str.size(); i++)
    {
        if (isOp(str.substr(i, 1)))
        {
            vec.push_back(token(token::num, str.substr(start, len)));
            vec.push_back(token(token::type::op, str.substr(i, 1)));
            len = 0;
            start = i + 1;
        }
        else
        {
            len++;
        }
    }

    if (len > 0)
    {
        vec.push_back(token(token::num, str.substr(start, len)));
    }

    vec.push_back(token(token::empty, ""));
    return vec;
}
