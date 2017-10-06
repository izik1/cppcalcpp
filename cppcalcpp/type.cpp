#include "stdafx.h"
#include "type.h"

std::unordered_map<type, std::string> typeStringMap{
    {type::num,          "num"},
    {type::eof,          "eof"},
    {type::plus,         "plus"},
    {type::minus,        "minus"},
    {type::slash,        "slash"},
    {type::astrisk,      "astrisk"},
    {type::paren_open,   "paren_open"},
    {type::paren_close,  "paren_close"},
    {type::carrot,       "carrot"},
    {type::identifier,   "identifier"},
    {type::equals,       "equals"},
};

std::unordered_map<std::string, type> lexerSymbolMap{
    {"+", type::plus},
    {"-", type::minus},
    {"*", type::astrisk},
    {"/", type::slash},
    {"(", type::paren_open},
    {")", type::paren_close},
    {"^", type::carrot},
    {"=", type::equals},
};
