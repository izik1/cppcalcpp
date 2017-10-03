#include "stdafx.h"
#include "token.h"

token::token(const token::type p_type, const std::string p_value)
{
    m_type = p_type;
    m_value = p_value;
}

token::~token()
{
}
