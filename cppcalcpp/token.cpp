#include "stdafx.h"
#include "token.h"

token::token(const type p_type, const int32_t p_value) {
    m_type = p_type;
    m_value = p_value;
}

token::~token() {}
