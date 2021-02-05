#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <numeric>

template<class T>
class MAX {
public:
    std::pair<T, int> operator()(const std::pair<T, int> &lhs, const std::pair<T, int> &rhs) {
        if ( lhs.first > rhs.first){
            return lhs;
        } else {
            return rhs;
        }
    }
};

template<class T, class Function, T neutralElement>
class SegmentTree {
    int treeSize;
    int arraySize;
    std::vector<std::pair<T, int>> tree;
    Function function;

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
    SegmentTree(const int &n) {
        arraySize = pow(2, std::ceil(log2(n)));
        treeSize = 2 * arraySize - 1;
        tree.resize(treeSize, std::make_pair(neutralElement, 1));
    }

    void Build(std::vector<T> &elements) {
        for (int i = arraySize - 1; i < arraySize - 1 + elements.size(); ++i) {
            tree[i] = std::make_pair(elements[i - arraySize + 1], 1);
        }
        for (int i = arraySize - 2; i >= 0; --i) {
            int numberOfIn = 1; // количество вхождений
            if (tree[getLeftChild(i)].first == tree[getRightChild(i)].first) {
                numberOfIn = tree[getLeftChild(i)].second + tree[getRightChild(i)].second;
            } else {
                numberOfIn = std::max(tree[getLeftChild(i)].second, tree[getRightChild(i)].second);
            }
            tree[i] = std::make_pair(function(tree[getLeftChild(i)], tree[getRightChild(i)]).first, numberOfIn);
        }
    }

    void printTree() {
        for (int i = 0; i < treeSize; ++i) {
            std::cout << tree[i] << " ";
        }
    }

    std::pair<T, int> Query(int left, int right, int& numberOfMax) {
        left += arraySize - 1;
        right += arraySize - 1;
        std::pair<T, int> leftResult = {neutralElement, 0};  // todo или пустое
        std::pair<T, int> rightResult = {neutralElement, 0}; // todo или пустое
        int numberOfMaxLeft = 0;
        int numberOfMaxRight = 0;
        while (left < right) {
            if (left == getRightChild(getParent(left))) {
                leftResult = function(leftResult, tree[left]);
            }
            left = getParent(left + 1);

            if (right == getLeftChild(getParent(right))) {
                rightResult = function(rightResult, tree[right]);
            }
            right = getParent(right - 1);
        }
        if (left == right) {
            leftResult = function(leftResult, tree[left]);
        }
        return function(leftResult, rightResult);
    }
};

const int neutralElement = 0;

int main() {
    int numberOfSoldiers = 0, numberOfRequests = 0;
    std::cin >> numberOfSoldiers;
    std::vector<int> awards(numberOfSoldiers);
    for (auto &element: awards) {
        std::cin >> element;
    }

    SegmentTree<int, MAX<int>, neutralElement> tree(numberOfSoldiers);
    tree.Build(awards);

    std::cin >> numberOfRequests;
    int left = 0, right = 0;
    for (int i = 0; i < numberOfRequests; ++i) {
        std::cin >> left >> right;
        int numberOfMax = 0;
        std::cout << tree.Query(left - 1, right - 1, numberOfMax).first << " " << numberOfMax << '\n';
    }
}

