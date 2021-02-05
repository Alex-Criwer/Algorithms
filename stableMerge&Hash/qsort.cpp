#include <iostream>
#include <vector>

int partition(std::vector<int> &array, const int &left, const int &right) {
    int pivot = array[(left + right) / 2];
    int i = left - 1;
    int j = right + 1;
    while (true) {
        do {
            ++i;
        } while (array[i] < pivot);
        do {
            --j;
        } while (array[j] > pivot);
        if (i >= j) {
            return j;
        }
        std::swap(array[i], array[j]);
    }
}

void qsort(std::vector<int> &array, int left, int right) {
    if (left < right) {
        int pivot = partition(array, left, right);
        qsort(array, left, pivot);
        qsort(array, pivot + 1, right);
    }
}

int main() {
    int size;
    std::cin >> size;
    std::vector<int> array;
    array.reserve(size);
    for (int i = 0; i < size; ++i) {
        int element;
        std::cin >> element;
        array.push_back(element);
    }
    qsort(array, 0, size - 1);
    for (auto &element: array) {
        std::cout << element << " ";
    }
    return 0;
}
