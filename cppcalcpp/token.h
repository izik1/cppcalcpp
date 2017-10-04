#pragma once
#include <cassert>
#include <cstdint>
#include "type.h"
class token {
public:
    type m_type;
    int64_t m_value;
    std::string m_strval;
    token(const type p_type, const int64_t p_value, const std::string p_strval);
    ~token();
};
