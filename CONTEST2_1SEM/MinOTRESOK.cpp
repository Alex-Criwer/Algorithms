#include <iostream>
using namespace std;

struct element{
    int value;
    int index;
};

int parent(int index) {
    return (index - 1) / 2;
}
int leftChild(int index) {
    return index * 2 + 1;
}
int rightChild(int index) {
    return index * 2 + 2;
}

void siftUp(element* heap, int index, int* heapIndex) {
    int target = index;
    while (target > 0 && heap[target].value < heap[parent(target)].value) {
        swap(heap[target], heap[parent(target)]);
        swap(heapIndex[heap[target].index], heapIndex[heap[parent(target)].index]);
        target = parent(target);
    }
}
void siftDown(element* heap, int index, int heapSize,int* heapIndex) {
    int left = leftChild(index);
    int right = rightChild(index);
    int minIndex = index;
    if (left < heapSize && heap[left].value < heap[minIndex].value) {
        minIndex = left;
    }
    if (right < heapSize && heap[right].value < heap[minIndex].value) {
        minIndex = right;
    }
    if (minIndex != index) {
        swap(heap[index], heap[minIndex]);
        swap(heapIndex[heap[index].index], heapIndex[heap[minIndex].index]);
        siftDown(heap, minIndex,heapSize, heapIndex);
    }
}

void insert(element* heap, int* heapIndex, int value ,int index, int heapSize) {
    heap[heapSize].value = value;
    heap[heapSize].index = index;
    heapIndex[heap[heapSize].index] = heapSize;
    ++heapSize;
    siftUp(heap,heapSize - 1,heapIndex);
}

void deleteTheElement (element* heap, int* heapIndex, int indDel, int heapSize) {
    swap(heap[indDel], heap[heapSize - 1]);
    swap(heapIndex[heap[indDel].index], heapIndex[heap[heapSize - 1].index]);
    --heapSize;
    siftDown(heap,indDel,heapSize, heapIndex);
    siftUp(heap,indDel,heapIndex);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int sizeOfArray, k, size = 0 ,index = 0;
    int temp = 0;
    cin >> sizeOfArray >> k;
    int* arr = new int[sizeOfArray];
    int* heapIndex = new int[sizeOfArray];
    element* heap = new element[k + 1];
    heapIndex[0] = 0;
    for (int i = 0; i < sizeOfArray; ++i) {
        cin >> arr[i];
    }
    for (int i = 0; i < k; ++i) {
        insert(heap, heapIndex, arr[i],index,size);
        ++size;
        ++index;
    }
    for (int i = k; i < sizeOfArray; ++i) {
        cout << heap[0].value << endl;
        int indDel = heapIndex[temp];
        deleteTheElement(heap, heapIndex, indDel, size);
        --size;
        insert(heap,heapIndex, arr[i],index,size);
        ++size;
        ++temp;
        ++index;
    }
    cout << heap[0].value << endl;
    delete[] heap;
    delete[] heapIndex;
    delete[] arr;
    return 0;
}