#pragma once

#include <cassert>
#include <cstdint>
#include <vector>
#include <algorithm>

int MaximizeSumGreedy(const int binaryTree[], const int n);

int MinimizeCoinCountGreedy(const int total, std::vector<int>& coinAmounts);

struct MeetingPlan
{
    int start;
    int end;
};

std::vector<MeetingPlan> ScheduleMeetingRoomGreedy(const std::vector<MeetingPlan>& plans);