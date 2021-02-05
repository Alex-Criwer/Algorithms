#include <iostream>

using namespace std;

struct Participant {
    int number;
    int coins;
};

bool compare(Participant a, Participant b) {
    if (a.coins > b.coins) {
        return true;
    }
    if (a.coins < b.coins) {
        return false;
    }
    if (a.number < b.number) {
        return true;
    }
    return false;
}

void siftDown(Participant *array, int index, int size) {
    int maxIndex = index;
    int left = index * 2 + 1;
    int right = index * 2 + 2;
    if (left < size && compare(array[left], array[maxIndex])) {
        maxIndex = left;
    }
    if (right < size && compare(array[right], array[maxIndex])) {
        maxIndex = right;
    }
    if (maxIndex != index) {
        swap(array[index], array[maxIndex]);
        siftDown(array, maxIndex, size);
    }
}

void buildTheHeap(Participant *array, int size) {
    for (int i = size / 2; i >= 0; --i) {
        siftDown(array, i, size);
    }
}

void heapSort(Participant *array, int size) {
    int currSize = size;
    for (int i = 0; i < size; ++i) {
        swap(array[0], array[currSize - 1]);
        --currSize;
        siftDown(array, 0, currSize);
    }
}

int main() {
    int size;
    cin >> size;
    Participant *array = new Participant[size];
    for (int i = 0; i < size; ++i) {
        cin >> array[i].number >> array[i].coins;
    }
    buildTheHeap(array, size);
    heapSort(array, size);
    for (int i = size - 1; i >= 0; --i) {
        cout << array[i].number << " " << array[i].coins << endl;
    }
    delete[] array;
    return 0;
}