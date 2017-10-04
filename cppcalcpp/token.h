#pragma once
#include <cassert>
#include <cstdint>
#include "type.h"
class token {
public:
    type m_type;
    int64_t m_value;
    token(const type p_type, const int64_t p_value);
    ~token();
};
