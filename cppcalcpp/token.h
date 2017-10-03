#pragma once
#include <cassert>
#include <cstdint>
enum type {
    plus,
    minus,
    astrisk,
    slash,
    num,
    end,
};

class token
{
public:
    type m_type;

    int32_t m_value;
    token(const type p_type, const int32_t p_value);
    ~token();
};

inline bool isOp(type t) {
    switch (t)
    {
    case plus:
    case minus:
    case astrisk:
    case slash:
        return true;
    case num:
    case end:
        return false;
    default:
        assert(0);
        return false;
    }
}
