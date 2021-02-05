#include <iostream>
#include <vector>

std::vector<int> merge(std::vector<int> &lhs, std::vector<int> &rhs);

void enterTheArray(const size_t &size, std::vector<int> &array);

void printTheArray(const std::vector<int> &array);

void enterHugeArray(const size_t &size, std::vector<std::vector<int>> &hugeArray);

std::vector<int> mergeArrays(std::vector<std::vector<int>> &hugeArray);

int main() {
    size_t numberOfArrays = 0;
    std::cin >> numberOfArrays;
    std::vector<std::vector<int>> hugeArray;
    enterHugeArray(numberOfArrays, hugeArray);
    printTheArray(mergeArrays(hugeArray));
    return 0;
}

std::vector<int> merge(std::vector<int> &lhs, std::vector<int> &rhs) {
    size_t indexA = 0, indexB = 0, indexC = 0;
    std::vector<int> result(lhs.size() + rhs.size());
    while (indexA < lhs.size() && indexB < rhs.size()) {
        if (lhs[indexA] <= rhs[indexB]) {
            result[indexC++] = lhs[indexA++];
        } else {
            result[indexC++] = rhs[indexB++];
        }
    }
    while (indexA < lhs.size()) {
        result[indexC++] = lhs[indexA++];
    }
    while (indexB < rhs.size()) {
        result[indexC++] = rhs[indexB++];
    }
    return result;
}

void enterTheArray(const size_t &size, std::vector<int> &array) {
    array.reserve(size);
    for (int i = 0; i < size; ++i) {
        int element;
        std::cin >> element;
        array.push_back(element);
    }
}

void printTheArray(const std::vector<int> &array) {
    for (auto &element: array) {
        std::cout << element << " ";
    }
}

void enterHugeArray(const size_t &size, std::vector<std::vector<int>> &hugeArray) {
    hugeArray.reserve(size);
    for (int i = 0; i < size; ++i) {
        size_t sizeOfSmallArray = 0;
        std::cin >> sizeOfSmallArray;
        std::vector<int> tempBuffer;
        enterTheArray(sizeOfSmallArray, tempBuffer);
        hugeArray.push_back(tempBuffer);
    }
}

std::vector<int> mergeArrays(std::vector<std::vector<int>> &hugeArray) {
    std::vector<std::vector<int>> tempArray;
    while (hugeArray.size() != 1) {
        tempArray.clear();
        for (int i = 0; i < hugeArray.size(); i += 2) {
            if (i == hugeArray.size() - 1) {
                tempArray.push_back(hugeArray.back());
            } else {
                tempArray.push_back(merge(hugeArray[i], hugeArray[i + 1]));
            }
        }
        hugeArray = tempArray;
    }
    return hugeArray.front();
}