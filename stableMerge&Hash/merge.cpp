/* Вам даны два отсортированных массива. Нужно слить их за линейное время в один большой отсортированный.
*/

#include <iostream>
#include <vector>

void enterTheArray(std::vector<int> &array) {
    size_t size = 0;
    std::cin >> size;
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

int main() {
    std::vector<int> firstArray, secondArray, merged;
    enterTheArray(firstArray);
    enterTheArray(secondArray);
    printTheArray(merge(firstArray, secondArray));
    return 0;
}


