#pragma once
#include <vector>
#include <string>

class exprtree
{
public:
    enum type {
        op,
        num,
    };

    uint32_t m_intval;
    std::string m_strval;
    type m_type;
    std::vector<exprtree*> subtrees;
    exprtree();
    ~exprtree();
};
