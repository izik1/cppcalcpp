#pragma once
#include <unordered_map>

enum type {
    plus,
    minus,
    astrisk,
    slash,
    num,
    end,
};

extern std::unordered_map<type, std::string> typeToString;

inline bool isOp(type t) {
    switch (t) {
    case plus:
    case minus:
    case astrisk:
    case slash:
        return true;
    default: return false;
    }
}
