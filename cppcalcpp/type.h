#pragma once
#include <unordered_map>

enum type {
    plus,
    minus,
    astrisk,
    slash,
    num,
    eof,
    carrot,
    paren_open,
    paren_close,
    identifier,
    equals,
};

extern std::unordered_map<type, std::string> typeStringMap;
extern std::unordered_map<std::string, type> lexerSymbolMap;
inline bool isOp(type t) {
    switch(t) {
    case plus:
    case minus:
    case astrisk:
    case carrot:
    case slash:
    case equals:
        return true;
    default: return false;
    }
}
