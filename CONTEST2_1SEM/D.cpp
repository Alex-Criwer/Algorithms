#include <iostream>
#include<cstring>
using namespace std;

struct element{
    int value;
    int numberOfInsert;
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

void siftUp(element* heap, int index, element** arrPtr){
    while(index > 0 && heap[index].value < heap[parent(index)].value) {
        swap(heap[index], heap[parent(index)]);
        swap(arrPtr[heap[index].numberOfInsert], arrPtr[heap[parent(index)].numberOfInsert]);
        index = parent(index);
    }
}
void siftDown(element* heap, int index, int heapSize, element** arrPtr) {
    int left = leftChild(index);
    int right = rightChild(index);
    int maxIndex = index;
    if(left < heapSize && heap[left].value < heap[maxIndex].value) {
        maxIndex = left;
    }
    if(right < heapSize && heap[right].value < heap[maxIndex].value) {
        maxIndex = right;
    }
    if(maxIndex != index){
        swap(heap[index], heap[maxIndex]);
        swap(arrPtr[heap[index].numberOfInsert], arrPtr[heap[maxIndex].numberOfInsert]);
        siftDown(heap, maxIndex, heapSize, arrPtr);
    }
}

void insert(element* heap, int value, int heapSize, int index, element** arrPtr) {
    heap[heapSize - 1].value = value;
    heap[heapSize - 1].numberOfInsert = index;
    arrPtr[index] = heap + (heapSize - 1);
    siftUp(heap, heapSize - 1, arrPtr);
}

int getMin(element* heap) {
    return heap[0].value;
}

bool find(element** arrPtr, int index) {
    return arrPtr[index] != nullptr;
}
int findTheIndex(element* heap, int x, element** arrPtr) {
    return arrPtr[x] - heap;
}

void deleteElement(element* heap, int index, int& heapSize, element** arrPtr) {
    swap(heap[index], heap[heapSize - 1]);
    swap(arrPtr[heap[index].numberOfInsert], arrPtr[heap[heapSize - 1].numberOfInsert]);
    arrPtr[heap[heapSize - 1].numberOfInsert] = nullptr;
    --heapSize;
    if (index < heapSize) {
        siftDown(heap, index, heapSize, arrPtr);
        siftUp(heap, index, arrPtr);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int numberOfCommands;
    cin >> numberOfCommands;
    int index = 0;
    int size = 0;

    int MAX_SIZE = 200000;
    element* heap = new element[MAX_SIZE];
    element** arrPtr = new element*[MAX_SIZE];
    for (int i = 0; i < MAX_SIZE; ++i){
        arrPtr[i] = nullptr;
    }

    char* command = new char[50];
    for (int i = 0; i < numberOfCommands; ++i) {
        cin >> command;

        if (strcmp(command, "insert") == 0) {
            int number;
            cin >> number;
            insert(heap,number,++size,index++, arrPtr);
            cout << "ok" << endl;
        }

        if(strcmp(command, "extract_min") == 0) {
            if (size > 0) {
                cout << getMin(heap) << endl;
                deleteElement(heap, 0, size, arrPtr);
            }
            else {
                cout << "error" << endl;
            }
        }

        if(strcmp(command, "delete") == 0) {
            int x;
            cin >> x;
            --x;
            if(find(arrPtr, x)) {
                int indexInHeap = findTheIndex(heap, x, arrPtr);
                deleteElement(heap, indexInHeap, size, arrPtr);
                cout << "ok" << endl;
            }
            else{
                cout << "error" << endl;
            }
        }

        if(strcmp(command, "change") == 0) {
            int x, numToChange;
            cin >> x >> numToChange;
            --x;
            if(find(arrPtr, x)) {
                int indexInHeap = findTheIndex(heap, x, arrPtr);
                heap[indexInHeap].value = numToChange;
                siftDown(heap,indexInHeap, size, arrPtr);
                siftUp(heap,indexInHeap, arrPtr);
                cout << "ok" << endl;
            }
            else {
                cout << "error" << endl;
            }
        }

        if(strcmp(command, "get_min") == 0) {
            if(size > 0) {
                cout << getMin(heap) << endl;
            }
            else {
                cout << "error" << endl;
            }
        }

        if(strcmp(command,"size") == 0) {
            cout << size << endl;
        }

        if(strcmp(command,"clear") == 0) {
            size = 0;
            for (int c = 0; c < MAX_SIZE; ++c){
                arrPtr[c] = nullptr;
            }
            cout << "ok" << endl;
        }
    }

    delete[] arrPtr;
    delete[] command;
    delete[] heap;
    return 0;
}