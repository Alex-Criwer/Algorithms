#include<iostream>

using namespace std;

int parent(int index) {
    return (index - 1) / 2;
}

int leftChild(int index) {
    return index * 2 + 1;
}

int rightChild(int index) {
    return index * 2 + 2;
}

int quickSort(int *arrivalTime, int *processingTime, int left, int right) {
    int i = left;
    int j = right;
    int x = arrivalTime[(left + right) / 2];
    do {
        while (arrivalTime[i] < x) {
            ++i;
        }
        while (arrivalTime[j] > x) {
            --j;
        }
        if (i <= j) {
            swap(arrivalTime[i], arrivalTime[j]);
            swap(processingTime[i], processingTime[j]);
            ++i;
            --j;
        }
    } while (i <= j);
    if (i < right) {
        quickSort(arrivalTime, processingTime, i, right);
    }
    if (left < j) {
        quickSort(arrivalTime, processingTime, left, j);
    }
}

void siftUp(int *heap, int index) {
    while (index > 0 && heap[index] < heap[parent(index)]) {
        swap(heap[index], heap[parent(index)]);
        index = parent(index);
    }
}

void siftDown(int *heap, int index, int heapSize) {
    int left = leftChild(index);
    int right = rightChild(index);
    int max = index;
    if (left < heapSize && heap[max] > heap[left]) {
        max = left;
    }
    if (right < heapSize && heap[max] > heap[right]) {
        max = right;
    }
    if (max != index) {
        swap(heap[index], heap[max]);
        siftDown(heap, max, heapSize);
    }
}

void addElement(int *heap, int value, int &heapSize) {
    heap[heapSize] = value;
    ++heapSize;
    siftUp(heap, heapSize - 1);
}

void extractMin(int *heap, int &heapSize) {
    swap(heap[0], heap[heapSize - 1]);
    --heapSize;
    siftDown(heap, 0, heapSize);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int size;
    int numberOfAdds = 0;
    int maxNumberOfMachines = 0;
    cin >> size;
    int *arrivalTime = new int[size];
    int *processingTime = new int[size];
    int *heap = new int[size];
    for (int i = 0; i < size; ++i) {
        cin >> arrivalTime[i] >> processingTime[i];
    }
    quickSort(arrivalTime, processingTime, 0, size - 1);
    for (int i = 0; i < size; ++i) {
        while (numberOfAdds > 0 && heap[0] <= arrivalTime[i]) {
            extractMin(heap, numberOfAdds);
        }
        addElement(heap, arrivalTime[i] + processingTime[i], numberOfAdds);
        if (numberOfAdds > maxNumberOfMachines) {
            maxNumberOfMachines = numberOfAdds;
        }
    }

    cout << maxNumberOfMachines << endl;
    delete[] heap;
    delete[] arrivalTime;
    delete[] processingTime;
    return 0;
}

