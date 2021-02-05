#include <iostream>
#include <vector>

constexpr int BEGIN_ARRAY_INDEX = 0;

using int_t = long long;

class StaticRSQ {
    std::vector<int_t> cumulativeSum;

public:
    StaticRSQ(const std::vector<int_t> &numbers) {
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

};

int main() {
    int_t vectorSize = 0, element = 0, numberOfRequest = 0;
    int_t leftIndex = 0, rightIndex = 0;
    std::cin >> vectorSize;
    std::vector<int_t> numbers;
    std::vector<int_t> answer;
    numbers.reserve(vectorSize);

    for (int_t i = 0; i < vectorSize; ++i) {
        std::cin >> element;
        numbers.push_back(element);
    }

    StaticRSQ rsq(numbers);

    std::cin >> numberOfRequest;
    for (int_t i = 0; i < numberOfRequest; ++i) {
        std::cin >> leftIndex >> rightIndex;
        answer.push_back(rsq.getSumSection(leftIndex - 1, rightIndex - 1));
    }

    for (const auto &element : answer) {
        std::cout << element << " ";
    }
    return 0;
}

//5
//1 2 3 4 5
//1