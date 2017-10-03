#pragma once
#include <string>
class token
{
public:
    enum type {
        num,
        op,
        empty,
    };
    type m_type;
    std::string m_value;
    token(const token::type p_type, const std::string p_value);
    ~token();
};
