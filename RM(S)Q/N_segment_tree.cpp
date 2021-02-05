#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <numeric>

template<class T>
class MIN {
public:
    static const int neutralElement = std::numeric_limits<int>::max();

    T operator()(const T &lhs, const T &rhs) {
        return std::gcd(lhs, rhs);
    }
};

template<class T, class Function>
class SegmentTree {
    int treeSize;
    int arraySize;
    std::vector<T> tree;
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
        tree.resize(treeSize, Function::neutralElement);
    }

    void Build(std::vector<T> &elements) {
        for (int i = arraySize - 1; i < arraySize - 1 + elements.size(); ++i) {
            tree[i] = elements[i - arraySize + 1];
        }
        for (int i = arraySize - 2; i >= 0; --i) {
            tree[i] = function(tree[getLeftChild(i)], tree[getRightChild(i)]);
        }
    }

    void printTree() {
        for (int i = 0; i < treeSize; ++i) {
            std::cout << tree[i] << " ";
        }
    }

    T Query(int left, int right) {
        left += arraySize - 1;
        right += arraySize - 1;
        T leftResult = Function::neutralElement;
        T rightResult = Function::neutralElement;
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

int main() {
    int numberOfSoldiers = 0, numberOfRequests = 0;
    std::cin >> numberOfSoldiers;
    std::vector<int> awards(numberOfSoldiers);
    for (auto &element: awards) {
        std::cin >> element;
    }

    SegmentTree<int, MIN<int>> tree(numberOfSoldiers);
    tree.Build(awards);

    std::cin >> numberOfRequests;
    int left = 0, right = 0;
    for (int i = 0; i < numberOfRequests; ++i) {
        std::cin >> left >> right;
        std::cout << tree.Query(left - 1, right - 1) << '\n';
    }
}

