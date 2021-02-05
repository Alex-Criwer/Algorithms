#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>


enum program {
    FIRST_OPERATION = 1,
    SECOND_OPERATION = 2,
    THIRD_OPERATION = 3
};


class BIT {
    std::vector<std::vector<std::vector<int>>> valuesForFenwick;
    int size;
public:
    BIT(const int &size) : valuesForFenwick(size, std::vector<std::vector<int>>(size, std::vector<int>(size, 0))),
                           size(size) {}

    int Query(const int &x, const int &y, const int &z) {
        int result = 0;
        for (int i = x; i >= 0; i = ((i & (i + 1)) - 1)) {
            for (int j = y; j >= 0; j = ((j & (j + 1)) - 1)) {
                for (int k = z; k >= 0; k = ((k & (k + 1)) - 1)) {
                    result += valuesForFenwick[i][j][k];
                }
            }
        }
        return result;
    }

    int Query(const int &x1, const int &y1, const int &z1, const int &x2, const int &y2, const int &z2) {
        return Query(x2, y2, z2) - Query(x1 - 1, y2, z2) - Query(x2, y1 - 1, z2)
               - Query(x2, y2, z1 - 1) + Query(x1 - 1, y1 - 1, z2)
               + Query(x1 - 1, y2, z1 - 1) + Query(x2, y1 - 1, z1 - 1)
               - Query(x1 - 1, y1 - 1, z1 - 1);
    }

    void Update(const int &x, const int &y, const int &z, const int &delta) {
        for (int i = x; i < size; i = (i | (i + 1))) {
            for (int j = y; j < size; j = (j | (j + 1))) {
                for (int k = z; k < size; k = (k | (k + 1))) {
                    valuesForFenwick[i][j][k] += delta;
                }
            }
        }
    }

};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    int size = 0;
    std::cin >> size;
    BIT FenwickTree(size);
    int operation;
    while (true) {
        std::cin >> operation;
        if (FIRST_OPERATION == operation) {
            int x, y, z, delta;
            std::cin >> x >> y >> z >> delta;
            FenwickTree.Update(x, y, z, delta);

        } else if (SECOND_OPERATION == operation) {
            int x1, y1, z1, x2, y2, z2;
            std::cin >> x1 >> y1 >> z1 >> x2 >> y2 >> z2;
            std::cout << FenwickTree.Query(x1, y1, z1, x2, y2, z2) << '\n';
        } else if (THIRD_OPERATION == operation) {
            break;
        }
    }
    return 0;
}
