#include <iostream>
#include <vector>
#include <algorithm>

using int_t = long long;

constexpr int_t BEGIN_ARRAY_INDEX = 0;

constexpr int_t ZERO = 0;

struct maxSumSection {
    int_t leftIndex = 0;
    int_t rightIndex = 0;
    int_t maxSum = 0;
};

class StaticRSQ {
    std::vector<int_t> cumulativeSum;
    std::vector<int_t> numbers;
public:
    StaticRSQ(const std::vector<int_t> &numbers) : numbers(numbers) {
        cumulativeSum.resize(numbers.size(), 0);

        for (int_t i = 0; i < cumulativeSum.size(); ++i) {
            if (BEGIN_ARRAY_INDEX == i) {
                cumulativeSum[i] = numbers[i];
            } else {
                cumulativeSum[i] = cumulativeSum[i - 1] + numbers[i];
            }
        }
    }

    int_t getSumSection(const int_t &leftIndex, const int_t &rightIndex) {
        if (BEGIN_ARRAY_INDEX == leftIndex) {
            return cumulativeSum[rightIndex];
        }
        return cumulativeSum[rightIndex] - cumulativeSum[leftIndex - 1];
    }

    void maxSumSection(maxSumSection &maxSection) {
        maxSection.maxSum = numbers[0];
        int_t currentSum = 0;
        int_t minusPosition = -1;
        for (int_t rightPosition = 0; rightPosition < cumulativeSum.size(); ++rightPosition) {
            currentSum += numbers[rightPosition];
            if (currentSum > maxSection.maxSum) {
                maxSection.maxSum = currentSum;
                maxSection.leftIndex = minusPosition + 1;
                maxSection.rightIndex = rightPosition;
            }

            if (currentSum < 0) {
                currentSum = 0;
                minusPosition = rightPosition;
            }
        }
    }

};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);
    int_t vectorSize = 0, element = 0;
    std::cin >> vectorSize;
    std::vector<int_t> numbers;

    numbers.reserve(vectorSize);

    for (int_t i = 0; i < vectorSize; ++i) {
        std::cin >> element;
        numbers.push_back(element);
    }

    StaticRSQ rsq(numbers);

    maxSumSection maxSection;
    rsq.maxSumSection(maxSection);
    std::cout << maxSection.leftIndex + 1 << " " << maxSection.rightIndex + 1 << " ";
    std::cout << rsq.getSumSection(maxSection.leftIndex, maxSection.rightIndex);

    return 0;
}
