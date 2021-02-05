#include <iostream>
#include <cmath>

using namespace std;

void findTheMedian(int *array, int left, int right) {
    int median = (left + right) / 2;
    if ((array[left] < array[median] && array[left] > array[right]) ||
        (array[left] > array[median] && array[left] > array[right])) {
        swap(array[left], array[right]);
    } else if ((array[median] < array[left] && array[median] > array[right]) ||
               (array[median] > array[left] && array[median] > array[right])) {
        swap(array[median], array[right]);
    }
}

int partition(int *array, int left, int right) {
    findTheMedian(array, left, right);
    int x = array[right];
    int i = left - 1;
    for (int j = left; j < right; ++j) {
        if (array[j] <= x) {
            ++i;
            swap(array[i], array[j]);
        }
    }
    swap(array[i + 1], array[right]);
    return i + 1;
}

void quickSort(int *array, int left, int right) {
    if (left < right) {
        int pivot = partition(array, left, right);
        quickSort(array, left, pivot - 1);
        quickSort(array, pivot + 1, right);
    }
}

int kStatistics(int *array, int left, int right, int k) {
    int pivot = partition(array, left, right);
    if (k < pivot) {
        return kStatistics(array, left, pivot - 1, k);
    } else if (k > pivot) {
        return kStatistics(array, pivot + 1, right, k);
    } else {
        return array[k];
    }
}

int main() {
    int size;
    cin >> size;
    int k;
    cin >> k;
    --k;
    int *array = new int[size];
    cin >> array[0] >> array[1];
    for (int i = 2; i < size; ++i) {
        array[i] = (array[i - 1] * 123 + array[i - 2] * 45) % (10000000 + 4321);
    }
    cout << kStatistics(array, 0, size - 1, k);
    delete[] array;
    return 0;
}
