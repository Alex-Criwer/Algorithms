#include <iostream>
#include <cstring>

using namespace std;

struct Element {
    int value;
    int positionInMax;
    int positionInMin;
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

void siftUpMax(Element **heap, int index) {
    int target = index;
    while (target > 0 && heap[target]->value > heap[parent(target)]->value) {
        swap(heap[target], heap[parent(target)]);
        heap[target]->positionInMax = target;
        heap[parent(target)]->positionInMax = parent(target);
        target = parent(target);
    }
}

void siftUpMin(Element **heap, int index) {
    int target = index;
    while (target > 0 && heap[target]->value < heap[parent(target)]->value) {
        swap(heap[target], heap[parent(target)]);
        heap[target]->positionInMin = target;
        heap[parent(target)]->positionInMin = parent(target);
        target = parent(target);
    }
}

void siftDownMax(Element **heap, int index, int heapSize) {
    int left = leftChild(index);
    int right = rightChild(index);
    int maxIndex = index;
    if (left < heapSize && heap[maxIndex]->value < heap[left]->value) {
        maxIndex = left;
    }
    if (right < heapSize && heap[maxIndex]->value < heap[right]->value) {
        maxIndex = right;
    }
    if (maxIndex != index) {
        swap(heap[maxIndex], heap[index]);
        heap[index]->positionInMax = index;
        heap[maxIndex]->positionInMax = maxIndex;
        siftDownMax(heap, maxIndex, heapSize);
    }

}

void siftDownMin(Element **heap, int index, int heapSize) {
    int left = leftChild(index);
    int right = rightChild(index);
    int minIndex = index;
    if (left < heapSize && heap[minIndex]->value > heap[left]->value) {
        minIndex = left;
    }
    if (right < heapSize && heap[minIndex]->value > heap[right]->value) {
        minIndex = right;
    }
    if (minIndex != index) {
        swap(heap[minIndex], heap[index]);
        heap[index]->positionInMin = index;
        heap[minIndex]->positionInMin = minIndex;
        siftDownMin(heap, minIndex, heapSize);
    }
}

void insert(Element **heapMax, Element **heapMin, int value, int heapSize) {
    Element *pv = new Element;
    pv->value = value;
    pv->positionInMax = heapSize - 1;
    pv->positionInMin = heapSize - 1;
    heapMax[heapSize - 1] = pv;
    heapMin[heapSize - 1] = pv;
    siftUpMax(heapMax, heapSize - 1);
    siftUpMin(heapMin, heapSize - 1);

}

int getMin(Element **heapMin) {
    return heapMin[0]->value;
}

int getMax(Element **heapMax) {
    return heapMax[0]->value;
}

void deleteElementInMax(Element **heapMax, Element **heapMin, int &heapSize) {

    int indexInHeapMin = (heapMax[0]->positionInMin);
    swap(heapMax[0], heapMax[heapSize - 1]);
    heapMax[0]->positionInMax = 0;
    heapMax[heapSize - 1]->positionInMax = heapSize - 1;
    swap(heapMin[indexInHeapMin], heapMin[heapSize - 1]);
    heapMin[indexInHeapMin]->positionInMin = indexInHeapMin;
    heapMin[heapSize - 1]->positionInMin = heapSize - 1;
    delete heapMax[heapSize - 1];
    heapMax[heapSize - 1] = nullptr;
    heapMin[heapSize - 1] = nullptr;
    --heapSize;
    siftDownMax(heapMax, 0, heapSize);
    if (indexInHeapMin < heapSize) {
        siftDownMin(heapMin, indexInHeapMin, heapSize);
        siftUpMin(heapMin, indexInHeapMin);
    }
}

void deleteElementInMin(Element **heapMin, Element **heapMax, int &heapSize) {

    int indexInHeapMax = (heapMin[0]->positionInMax);
    swap(heapMin[0], heapMin[heapSize - 1]);
    heapMin[0]->positionInMin = 0;
    heapMin[heapSize - 1]->positionInMin = heapSize - 1;
    swap(heapMax[indexInHeapMax], heapMax[heapSize - 1]);
    heapMax[indexInHeapMax]->positionInMax = indexInHeapMax;
    heapMax[heapSize - 1]->positionInMax = heapSize - 1;
    delete heapMin[heapSize - 1];
    heapMin[heapSize - 1] = nullptr;
    heapMax[heapSize - 1] = nullptr;
    --heapSize;
    siftDownMin(heapMin, 0, heapSize);
    if (indexInHeapMax < heapSize) {
        siftDownMax(heapMax, indexInHeapMax, heapSize);
        siftUpMax(heapMax, indexInHeapMax);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int numberOfCommand;
    cin >> numberOfCommand;
    int MAX_SIZE = 200000;
    Element **heapMax = new Element *[MAX_SIZE];
    Element **heapMin = new Element *[MAX_SIZE];
    for (int i = 0; i < MAX_SIZE; ++i) {
        heapMax[i] = nullptr;
        heapMin[i] = nullptr;
    }
    int size = 0;
    char *command = new char[50];
    for (int i = 0; i < numberOfCommand; ++i) {
        cin >> command;
        if (strcmp(command, "insert") == 0) {
            int number;
            cin >> number;
            ++size;
            insert(heapMax, heapMin, number, size);
            cout << "ok" << "\n";
        }

        if (strcmp(command, "extract_max") == 0) {
            if (size > 0) {
                cout << getMax(heapMax) << "\n";
                deleteElementInMax(heapMax, heapMin, size);
            } else {
                cout << "error" << "\n";
            }
        }

        if (strcmp(command, "extract_min") == 0) {
            if (size > 0) {
                cout << getMin(heapMin) << "\n";
                deleteElementInMin(heapMin, heapMax, size);
            } else {
                cout << "error" << "\n";
            }

        }

        if (strcmp(command, "get_max") == 0) {
            if (size > 0) {
                cout << getMax(heapMax) << "\n";
            } else {
                cout << "error" << "\n";
            }
        }

        if (strcmp(command, "get_min") == 0) {
            if (size > 0) {
                cout << getMin(heapMin) << "\n";
            } else {
                cout << "error" << "\n";
            }
        }

        if (strcmp(command, "size") == 0) {
            cout << size << "\n";
        }

        if (strcmp(command, "clear") == 0) {
            for (int i = 0; i < size; ++i) {
                delete heapMax[i];
                heapMax[i] = nullptr;
                heapMin[i] = nullptr;
            }
            size = 0;
            cout << "ok" << "\n";
        }
    }
    delete[] command;


    for (int i = 0; i < size; ++i) {
        delete heapMax[i];
    }
    delete[] heapMin;
    delete[] heapMax;
    return 0;
}