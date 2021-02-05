#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <numeric>

template<class T>
class SUM {
public:
    T operator()(const T &lhs, const T &rhs) const {
        return lhs + rhs;
    }
};

const long long neutralElement = 0;

template<class T, class Function, T neutralElement>
class SegmentTree {
    long long treeSize;
    long long arraySize;
    std::vector<T> tree;
    Function function;

    long long getParent(const long long &index) {
        return (index - 1) / 2;
    }

    long long getLeftChild(const long long &index) {
        return 2 * index + 1;
    }

    long long getRightChild(const long long &index) {
        return 2 * index + 2;
    }

public:
    SegmentTree(const long long &n) {
        arraySize = pow(2, std::ceil(log2(n)));
        treeSize = 2 * arraySize - 1;
        tree.resize(treeSize, neutralElement);
    }

    void Build(std::vector<T> &elements) {
        for (long long i = arraySize - 1; i < arraySize - 1 + elements.size(); ++i) {
            tree[i] = elements[i - arraySize + 1];
        }
        for (long long i = arraySize - 2; i >= 0; --i) {
            tree[i] = function(tree[getLeftChild(i)], tree[getRightChild(i)]);
        }
    }
    void printTree() {
        for (long long i = 0; i < treeSize; ++i) {
            std::cout << tree[i] << " ";
        }
    }

    T Query(long long left, long long right) {
        left += arraySize - 1;
        right += arraySize - 1;
        T leftResult = neutralElement;
        T rightResult = neutralElement;
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

    void Update(long long position, const long long &newElement) {
        position += arraySize - 1;
        tree[position] = newElement;
        do {
            position = getParent(position);
            tree[position] = function(tree[getLeftChild(position)], tree[getRightChild(position)]);
        } while (position != 0);
    }

};

int main() {
    long long numberOfSoldiers = 0, numberOfRequests = 0;
    std::cin >> numberOfSoldiers;
    std::vector<long long> awards(numberOfSoldiers, 0);
    for (auto &element: awards) {
        std::cin >> element;
    }

    SegmentTree<long long, SUM<long long>, neutralElement> tree(numberOfSoldiers);
    tree.Build(awards);

    std::cin >> numberOfRequests;
    std::string request;
    long long left = 0, right = 0;
    for (long long i = 0; i < numberOfRequests; ++i) {
        std::cin >> request;
        if (request == "s") {
            std::cin >> left >> right;
            std::cout << tree.Query(left - 1, right - 1) << ' ';
        } else {
            long long position, newElement;
            std::cin >> position >> newElement;
            tree.Update(position - 1, newElement);
        }
    }
}