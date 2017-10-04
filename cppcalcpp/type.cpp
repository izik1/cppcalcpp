#include "stdafx.h"
#include "type.h"

std::unordered_map<type, std::string> typeToString{
    {num,          "num"},
    {eof,          "eof"},
    {plus,         "plus"},
    {minus,        "minus"},
    {slash,        "slash"},
    {astrisk,      "astrisk"},
    {paren_open,   "paren_open"},
    {paren_close,  "paren_close"},
};

std::unordered_map<std::string, type> lexerSymbolMap{
    {"+", type::plus},
    {"-", type::minus},
    {"*", type::astrisk},
    {"/", type::slash},
    {"(", type::paren_open},
    {")", type::paren_close},
};
