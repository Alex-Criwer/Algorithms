#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

class SparseTable {
    std::vector<std::vector<int>> sparseTable;
public:
    SparseTable(int size, int firstElement) : sparseTable(floor(log2(size)) + 1,
                                                          std::vector<int>(size, std::numeric_limits<int>::max())) {
        sparseTable[0][0] = firstElement;
        for (int i = 1; i < size; ++i) {
            sparseTable[0][i] = (23 * sparseTable[0][i - 1] + 21563) % 16714589;  // заполнили первый слой
        }
        for (int k = 1; (1 << k) <= size; ++k) {
            for (int i = 0; i + (1 << k) <= size; ++i) {
                sparseTable[k][i] = std::min(sparseTable[k - 1][i], sparseTable[k - 1][i + (1 << k - 1)]);
            }
        }
    }

    int Query(int left, int right) {
        if (left > right) {
            std::swap(left, right);
        }
        int k = floor(log2(right - left + 1));
        return std::min(sparseTable[k][left], sparseTable[k][right - (1 << k) + 1]);
    }

};

int main() {
    int numberOfSoldiers = 0;
    int numberOfRequests = 0;
    int heightOfFirstSoldier = 0;
    int left = 0, right = 0;
    std::cin >> numberOfSoldiers >> numberOfRequests >> heightOfFirstSoldier;
    std::cin >> left >> right;

    SparseTable sparseTable(numberOfSoldiers, heightOfFirstSoldier);

    int answer = sparseTable.Query(left - 1, right - 1);
    for (int i = 1; i < numberOfRequests; ++i) {
        left = (17 * left + 751 + answer + 2 * i) % numberOfSoldiers + 1;
        right = (13 * right + 593 + answer + 5 * i) % numberOfSoldiers + 1;
        answer = sparseTable.Query(left - 1, right - 1);
    }

    std::cout << left << " " << right << " " << answer << '\n';
    return 0;
}
