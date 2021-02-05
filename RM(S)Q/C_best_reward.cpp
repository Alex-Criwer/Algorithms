#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#pragma GCC optimize("-fgcse")
#pragma GCC optimize("-fgcse-lm")
#pragma GCC optimize("-fipa-sra")
#pragma GCC optimize("no-stack-protecbr")
#pragma GCC optimize("unroll-loops")

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <numeric>

constexpr uint32_t BEGIN_ARRAY_INDEX = 0;

enum Bracket {
    CLOSED_BRACKET = -1,
    OPENED_BRACKET = 1,
    NO_BRACKET = 0
};

class StaticRSQ {
    uint32_t *cumulativeSum ;
public:
    StaticRSQ(uint32_t* elementsOpen, uint32_t*elementsClosed, char* openedBrackets, char* closedBrackets, const unsigned int& size) {
        cumulativeSum = new uint32_t[size];
        unsigned int prevValue = 0;
        if (OPENED_BRACKET == openedBrackets[0]) {
            prevValue += elementsOpen[0];
        }
        cumulativeSum[0] = prevValue;
        for (int i = 1; i < size; ++i) {
            if (OPENED_BRACKET == openedBrackets[i]) {
                prevValue += elementsOpen[i];
            }
            cumulativeSum[i] = cumulativeSum[i - 1] + prevValue;
            if (CLOSED_BRACKET == closedBrackets[i]) {
                prevValue -= elementsClosed[i];
            }
        }
    }

    unsigned int getSumSection(const int &leftIndex, const int &rightIndex) {
        if (BEGIN_ARRAY_INDEX == leftIndex) {
            return cumulativeSum[rightIndex];
        }
        return cumulativeSum[rightIndex] - cumulativeSum[leftIndex - 1];
    }
    ~StaticRSQ() {
        delete[] cumulativeSum;
    }
};

class Generator {
    unsigned int a = 0, b = 0;
    unsigned int cur = 0;
    unsigned int nextRand() {
        cur = cur * a + b;
        return cur >> 8;
    }

public:
    Generator(const unsigned int &a, const unsigned int &b) : a(a), b(b) {}

    void AddReward(uint32_t* elementsOpen, uint32_t*elementsClosed, char* openedBrackets, char* closedBrackets) {
        unsigned int add = nextRand();
        unsigned int left = nextRand();
        unsigned int right = nextRand();
        if (left > right) {
            std::swap(left, right);
        }
        elementsOpen[left] += add;
        elementsClosed[right] += add;
        openedBrackets[left] = OPENED_BRACKET;
        closedBrackets[right] = CLOSED_BRACKET;
    }

    unsigned int Answer(StaticRSQ& rsq) {
        unsigned int left = nextRand();
        unsigned int right = nextRand();
        if (left > right) {
            std::swap(left, right);
        }
        return rsq.getSumSection(left, right);
    }
};


int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    const unsigned int numberOfSoldiers = 1 << 24;
    int numberOfAwards = 0, numberOfRequests = 0;
    std::cin >> numberOfAwards >> numberOfRequests;
    int a = 0, b = 0;
    std::cin >> a >> b;
    Generator generator(a, b);
    uint32_t* elementsOpen = new u_int32_t [numberOfSoldiers];
    uint32_t* elementsClosed = new u_int32_t [numberOfSoldiers];
    char* openedBrackets = new char[numberOfSoldiers];
    char* closedBrackets = new char[numberOfSoldiers];
    for (int i = 0; i < numberOfSoldiers; ++i) {
        elementsClosed[i] = elementsOpen[i] = 0;
        closedBrackets[i] = openedBrackets[i] = NO_BRACKET;
    }

    for (int i = 0; i < numberOfAwards; ++i) {
        generator.AddReward(elementsOpen, elementsClosed, openedBrackets, closedBrackets);
    }
    StaticRSQ rsq(elementsOpen, elementsClosed, openedBrackets, closedBrackets, numberOfSoldiers);

    unsigned int sum = 0;
    for (int i = 0; i < numberOfRequests; ++i) {
        sum += generator.Answer(rsq);
    }
    std::cout << sum << '\n';
    delete[] elementsOpen;
    delete[] elementsClosed;
    delete[] openedBrackets;
    delete[] closedBrackets;
    return 0;
}

