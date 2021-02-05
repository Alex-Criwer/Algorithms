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

template<class T>
class MIN {
public:
    T operator()(const T &lhs, const T &rhs) {
        return std::min(lhs, rhs);
    }
};

const int neutralElement = std::numeric_limits<int>::max();

template<class T, class Function, T neutralElement>
class MultiSegmentTree {
    int arraySizeX;
    int arraySizeY;
    std::vector<std::vector<T>> tree;
    Function function;
    std::vector<T> xEast;
    std::vector<T> xWest;
    std::vector<T> yNorth;
    std::vector<T> ySouth;

    int getParent(const int &index) {
        return (index - 1) / 2;
    }

    int getLeftChild(const int &index) {
        return 2 * index + 1;
    }

    int getRightChild(const int &index) {
        return 2 * index + 2;
    }

public:
    MultiSegmentTree(const int &height, const int& width) {
        arraySizeX = pow(2, std::ceil(log2(height)));
        arraySizeY = pow(2, std::ceil(log2(width)));
        tree.resize(arraySizeX * 2 - 1);
        for(auto& str : tree) {
            str.resize(arraySizeY * 2 - 1, neutralElement);
        }
    }

    void Build(std::vector<std::vector<T>> &elements) {
        Fill( arraySizeX,xEast, xWest);
        Fill(arraySizeY, yNorth, ySouth);

        for (int i = 0; i < elements.size(); ++i) {
            for (int j = 0; j < elements[i].size(); ++j) {
                *(begin(tree[i + arraySizeX - 1]) + arraySizeY - 1 + j) = elements[i][j];
            }
        }

        for (int i = 2 * arraySizeX - 2; i >= arraySizeX - 1; --i) {
            for (int j = arraySizeY - 2; j >= 0 ; --j) {
                tree[i][j] = function(tree[i][getLeftChild(j)], tree[i][getRightChild(j)]);
            }
        }

        for (int i = arraySizeX - 2; i >= 0; --i) {
            for (int j = 0; j < 2 * arraySizeY - 1; ++j) {
                tree[i][j] = function(tree[getLeftChild(i)][j], tree[getRightChild(i)][j]);
            }
        }
    }

    void Fill (const int& size, std::vector<T>& lhs, std::vector<T>& rhs) {
        lhs.resize(size * 2 - 1);
        rhs.resize(size * 2 - 1);
        for (int i = size - 1; i < 2 * size - 1; ++i) {
            lhs[i] = rhs[i] = i - (size - 1);
        }
        for (int i = size - 2; i >= 0; --i) {
            rhs[i] = rhs[getRightChild(i)];
            lhs[i] = lhs[getLeftChild(i)];
        }
    }

    T MinInSquere(const int& root, const int& x1, const int& y1, const int& x2, const int& y2) {
        if (x1 > xWest[root] || x2 < xEast[root]) {
            return neutralElement;
        } else if (xWest[root] == xEast[root] || (x1 <= xEast[root] && x2 >= xWest[root])) {
            return MinInLine(y1 ,y2, root, 0);
        } else {
            return function(MinInSquere(getLeftChild(root), x1, y1, x2, y2), MinInSquere(getRightChild(root), x1, y1, x2, y2));
        }
    }

    T MinInLine(const int& start, const int& end, const int&i, const int& j) {
        if (start > ySouth[j] || end < yNorth[j]) {
            return neutralElement;
        } else if (ySouth[j] == yNorth[j] || (start <= yNorth[j] && end >= ySouth[j])) {
            return tree[i][j];
        } else {
            return function(MinInLine(start, end, i, getLeftChild(j)), MinInLine(start, end, i, getRightChild(j)));
        }
    }

};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    int height = 0, width = 0;
    int numberOfRequest = 0;
    std::cin >> height >> width;
    std::vector<std::vector<int>> violations(height + 1, std::vector<int>(width + 1, 0));
    for (int i = 1; i < height + 1; ++i) {
        for (int j = 1; j < width + 1; ++j) {
            std::cin >> violations[i][j];
        }
    }

    MultiSegmentTree<int, MIN<int>, neutralElement> tree(height + 1, width + 1);
    tree.Build(violations);

    std::cin >> numberOfRequest;
    int x1, y1, x2, y2;
    int root = 0;
    for (int i = 0; i < numberOfRequest; ++i) {
        std::cin >> x1 >> y1 >> x2 >> y2;
        std::cout << tree.MinInSquere(root, x1, y1, x2, y2) << '\n';
    }
    return 0;
}

