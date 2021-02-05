#include<iostream>
using namespace std;

template <typename T>
void siftDown(T* heap, int index, int heapSize) {
    int left = index * 2 + 1;
    int right = index * 2 + 2;
    int maxIndex = index;
    if(left < heapSize && heap[left] > heap[maxIndex]) {
        maxIndex = left;
    }
    if(right < heapSize && heap[right] > heap[maxIndex]) {
        maxIndex = right;
    }
    if(maxIndex != index) {
        swap(heap[index], heap[maxIndex]);
        siftDown(heap, maxIndex, heapSize);
    }
}
template <typename T>
void buildTheHeap (T* begin, T* end) {
    for (int i = (end - begin) / 2; i >= 0 ; --i) {
        siftDown(begin,i,end - begin);
    }
}

template <typename T>
void heapSort (T* begin, T* end) {
    int currSize = end - begin;
    for (int i = 0; i < end - begin ; ++i) {
        swap(*begin, *(begin + currSize - 1));
        --currSize;
        siftDown(begin, 0, currSize);
    }
}

int main() {
    int heapSize;
    cin >> heapSize;
    int* heap = new int[heapSize];
    for (int i = 0; i < heapSize; ++i) {
        cin >> heap[i];
    }
    buildTheHeap(heap, heap + heapSize);
    heapSort(heap, heap + heapSize);
    for (int i = 0; i < heapSize; ++i) {
        cout << heap[i] << " ";
    }
    delete[] heap;
    return 0;
}