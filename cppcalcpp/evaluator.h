#pragma once
#include <cstdint>
#include "exprtree.h"
namespace evaluator {
    int64_t evaluate(const exprtree* tree);
}
