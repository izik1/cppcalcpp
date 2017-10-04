#include "stdafx.h"
#include "token.h"

token::token(const type p_type, const int64_t p_value, const std::string p_strval) {
    m_type = p_type;
    m_value = p_value;
    m_strval = p_strval;
}

token::~token() {}
