#include "stdafx.h"
#include "lexer.h"
#include "token.h"
inline bool isOp(const std::string p_in) {
    return lexerSymbolMap.find(p_in) != lexerSymbolMap.end();
}

std::vector<token> lexer::lex(std::string str) {
    std::vector<token> vec = std::vector<token>();
    int start = 0;
    int len = 0;
    for(size_t i = 0; i < str.size(); i++) {
        if(isOp(str.substr(i, 1))) {
            if(len > 0) vec.push_back(token(num, std::stoi(str.substr(start, len))));
            vec.push_back(token(lexerSymbolMap[str.substr(i, 1)], 0));
            len = 0;
            start = i + 1;
        } else {
            len++;
        }
    }

    if(len > 0) vec.push_back(token(num, std::stoi(str.substr(start, len))));
    vec.push_back(token(eof, 0));
    return vec;
}
