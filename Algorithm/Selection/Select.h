#pragma once

#include <cassert>
#include <vector>
#include <cmath>
#include <algorithm>

namespace Selection
{
    int SelectKthNum(std::vector<int>& v, const int k);
    int SelectLinear(std::vector<int>& v, const int k);
}