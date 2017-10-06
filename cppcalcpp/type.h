#pragma once
#include <unordered_map>

enum class type {
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
    case type::plus:
    case type::minus:
    case type::astrisk:
    case type::carrot:
    case type::slash:
    case type::equals:
        return true;
    default: return false;
    }
}
