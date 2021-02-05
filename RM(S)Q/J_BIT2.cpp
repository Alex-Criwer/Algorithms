#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>


enum program {
    FIRST_OPERATION = 1,
    SECOND_OPERATION = 2
};

class BIT {
    std::vector<std::vector<int>> valuesForFenwick;
    int height, width;
public:
    BIT(const int &height, const int &width) : valuesForFenwick(height, std::vector<int>(width, 0)),
                                               height(height), width(width) {}

    int Query(const int &x, const int &y) {
        int result = 0;
        for (int i = x; i >= 0; i = ((i & (i + 1)) - 1)) {
            for (int j = y; j >= 0; j = ((j & (j + 1)) - 1)) {
                result += valuesForFenwick[i][j];
            }
        }
        return result;
    }

    int Query(const int &x1, const int &y1, const int &x2, const int &y2) {
        int temp1 = Query(x2, y2);
        int temp2 = Query(x1 - 1, y1 - 1);
        int temp3 = Query(x2, y1 - 1);
        int temp4 = Query(x1 - 1, y2);
        return temp1 + temp2 - temp3 - temp4;
    }

    void Update(const int &x, const int &y, const int &delta) {
        for (int i = x; i < height; i = (i | (i + 1))) {
            for (int j = y; j < width; j = (j | (j + 1))) {
                valuesForFenwick[i][j] += delta;
            }
        }
    }

};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    int height = 0, width = 0, numberOfActions;
    std::cin >> height >> width >> numberOfActions;
    BIT FenwickTree(height, width);
    int operation;
    for (int i = 0; i < numberOfActions; ++i) {
        std::cin >> operation;
        if (FIRST_OPERATION == operation) {
            int x, y, delta;
            std::cin >> x >> y >> delta;
            FenwickTree.Update(x - 1, y - 1, delta);
        } else if (SECOND_OPERATION == operation) {
            int x1, y1, x2, y2;
            std::cin >> x1 >> y1 >> x2 >> y2;
            std::cout << FenwickTree.Query(x1 - 1, y1 - 1, x2 - 1, y2 - 1) << '\n';
        }
    }
    return 0;
}