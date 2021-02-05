#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <numeric>

const uint64_t neutralElement = 0;

template<class T>
class SUM {
public:
    T operator()(const T &lhs, const T &rhs) {
        return lhs + rhs;
    }
};

template<class T, class Function, T neutralElement>
class SegmentTree {
    uint64_t treeSize;
    uint64_t arraySize;
    std::vector<T> tree;
    std::vector<T> adds;
    Function function;

    uint64_t getParent(const uint64_t &index) {
        return (index - 1) / 2;
    }

    uint64_t getLeftChild(const uint64_t &index) {
        return 2 * index + 1;
    }

    uint64_t getRightChild(const uint64_t &index) {
        return 2 * index + 2;
    }

public:
    SegmentTree(const uint64_t &n) {
        arraySize = pow(2, std::ceil(log2(n)));
        treeSize = 2 * arraySize - 1;
        tree.resize(treeSize, neutralElement);
        adds.resize(treeSize, neutralElement);
    }

    void Build(std::vector<T> &elements) {
        for (int i = arraySize - 1; i < arraySize - 1 + elements.size(); ++i) {
            tree[i] = elements[i - arraySize + 1];
        }
        for (int i = arraySize - 2; i >= 0; --i) {
            tree[i] = function(tree[getLeftChild(i)], tree[getRightChild(i)]);
        }
    }

    void pruint64_tTree() {
        for (int i = 0; i < treeSize; ++i) {
            std::cout << tree[i] << " ";
        }
    }

    T Query(uint64_t left, uint64_t right) {
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

    void Push(const uint64_t &index) {
        adds[getLeftChild(index)] += adds[index];
        adds[getRightChild(index)] += adds[index];
        adds[index] = neutralElement;
    }

    void UpdateInBorders(const uint64_t &left, const uint64_t &right, const T &value) {
        Update(0, 0, arraySize - 1, left, right, value);
    }

    T getValueInBorders(const uint64_t &index) {
        return getValue(0, 0, arraySize - 1, index);
    }

    T getValue(const uint64_t &start, const uint64_t &leftMaxBorder, const uint64_t &rightMaxBorder, const uint64_t &index) {
        uint64_t middle = (leftMaxBorder + rightMaxBorder) / 2;
        if (leftMaxBorder == rightMaxBorder) {
            return tree[start] + adds[start];
        } else if (index > middle) {
            return adds[start] + getValue(getRightChild(start), middle + 1, rightMaxBorder, index);
        } else {
            adds[start] + getValue(getLeftChild(start), leftMaxBorder, middle, index);
        }
    }

    void
    Update(const uint64_t &index, const uint64_t &leftMaxBorder, const uint64_t &rightMaxBorder, const uint64_t &left, const uint64_t &right,
           const T &value) {
        if (left > rightMaxBorder || right < leftMaxBorder) {
            return;
        }
        if (left <= leftMaxBorder && right >= rightMaxBorder) {
            adds[index] += value;
        } else {
            Push(index);
            uint64_t middle = (leftMaxBorder + rightMaxBorder) / 2;
            Update(getLeftChild(index), leftMaxBorder, middle, left, right, value);
            Update(getRightChild(index), middle + 1, rightMaxBorder, left, right, value);
        }
    }
};

int main() {
    uint64_t numberOfSoldiers = 0;
    uint64_t left = 0, right = 0;
    uint64_t index = 0;
    uint64_t value = 0;
    uint64_t numberOfRequest;
    char request;
    std::cin >> numberOfSoldiers;
    std::vector<uint64_t> elements(numberOfSoldiers);
    for (auto &element : elements) {
        std::cin >> element;
    }

    SegmentTree<uint64_t, SUM<uint64_t>, neutralElement> rsq(numberOfSoldiers);
    rsq.Build(elements);

    std::cin >> numberOfRequest;
    for (int i = 0; i < numberOfRequest; ++i) {
        std::cin >> request;
        if (request == 'a') {
            std::cin >> left >> right >> value;
            rsq.UpdateInBorders(left - 1, right - 1, value);
        } else if (request == 'g') {
            std::cin >> index;
            std::cout << rsq.getValueInBorders(index - 1) << '\n';
        }
    }
    return 0;
}


