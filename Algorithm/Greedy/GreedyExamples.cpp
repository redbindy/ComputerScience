#include "GreedyExamples.h"

int MaximizeSumGreedy(const int binaryTree[], const int n)
{
    assert(binaryTree != nullptr);
    assert(n > 0);

    int sum = 0;

    int nodeIndex = 1;
    while (nodeIndex <= n)
    {
        sum += binaryTree[nodeIndex];

        const int leftIndex = nodeIndex * 2;
        const int rightIndex = nodeIndex * 2 + 1;

        if (leftIndex > n && rightIndex > n)
        {
            break;
        }

        int leftWeight = INT32_MIN;
        if (leftIndex <= n)
        {
            leftWeight = binaryTree[leftIndex];
        }

        int rightWeight = INT32_MIN;
        if (rightIndex <= n)
        {
            rightWeight = binaryTree[rightIndex];
        }

        if (leftWeight == INT32_MIN && rightWeight == INT32_MIN)
        {
            break;
        }

        if (leftWeight > rightWeight)
        {
            nodeIndex = leftIndex;
        }
        else
        {
            nodeIndex = rightIndex;
        }
    }

    return sum;
}

int MinimizeCoinCountGreedy(const int total, std::vector<int>& coinAmounts)
{
    assert(total >= 0);

    int curr = total;
    int coinCount = 0;

    std::vector<int> copiedAmounts = coinAmounts;
    std::sort(copiedAmounts.begin(), copiedAmounts.end(), std::greater<int>());

    for (const int amount : copiedAmounts)
    {
        coinCount += curr / amount;
        curr %= amount;
    }

    return coinCount;
}

std::vector<MeetingPlan> ScheduleMeetingRoomGreedy(const std::vector<MeetingPlan>& plans)
{
#if (DEBUG || _DEBUG)
    for (const MeetingPlan& plan : plans)
    {
        assert(plan.start <= plan.end);
    }
#endif

    std::vector<MeetingPlan> copiedPlans = plans;

    std::sort(copiedPlans.begin(), copiedPlans.end(), [](const MeetingPlan& a, const MeetingPlan& b) -> bool
    {
        return a.end < b.end;
    });

    std::vector<MeetingPlan> result;
    result.reserve(plans.size());

    result.push_back(copiedPlans[0]);
    for (int i = 1; i < copiedPlans.size(); ++i)
    {
        const MeetingPlan& prevPlan = result.back();

        const MeetingPlan& plan = copiedPlans[i];

        if (plan.start < prevPlan.end)
        {
            continue;
        }

        result.push_back(plan);
    }

    return result;
}
