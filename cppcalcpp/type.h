#pragma once
#include <unordered_map>

enum type {
    plus,
    minus,
    astrisk,
    slash,
    num,
    eof,
    paren_open,
    paren_close,
};

extern std::unordered_map<type, std::string> typeToString;
extern std::unordered_map<std::string, type> operators;

inline bool isOp(type t) {
    switch(t) {
    case plus:
    case minus:
    case astrisk:
    case slash:
        return true;
    default: return false;
    }
}
