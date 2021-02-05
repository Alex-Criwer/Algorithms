#include <iostream>
#include <cstring>

using namespace std;

struct Element {
    int value;
    int indexHeapMax = -1;
    int indexHeapMin = -1;
    int indexHeapHalfMax = -1;
    int indexHeapHalfMin = -1;
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
        heap[target]->indexHeapMax = target;
        heap[parent(target)]->indexHeapMax = parent(target);
        target = parent(target);
    }
}

void siftUpMin(Element **heap, int index) {
    int target = index;
    while (target > 0 && heap[target]->value < heap[parent(target)]->value) {
        swap(heap[target], heap[parent(target)]);
        heap[target]->indexHeapMin = target;
        heap[parent(target)]->indexHeapMin = parent(target);
        target = parent(target);
    }
}

void siftUpHalfMax(Element **heap, int index) {
    int target = index;
    while (target > 0 && heap[target]->value > heap[parent(target)]->value) {
        swap(heap[target], heap[parent(target)]);
        heap[target]->indexHeapHalfMax = target;
        heap[parent(target)]->indexHeapHalfMax = parent(target);
        target = parent(target);
    }
}

void siftUpHalfMin(Element **heap, int index) {
    int target = index;
    while (target > 0 && heap[target]->value < heap[parent(target)]->value) {
        swap(heap[target], heap[parent(target)]);
        heap[target]->indexHeapHalfMin = target;
        heap[parent(target)]->indexHeapHalfMin = parent(target);
        target = parent(target);
    }
}

void siftDownMax(Element **heap, int index, int size) {
    int maxIndex = index;
    int left = leftChild(index);
    int right = rightChild(index);
    if (left < size && heap[left]->value > heap[maxIndex]->value) {
        maxIndex = left;
    }
    if (right < size && heap[right]->value > heap[maxIndex]->value) {
        maxIndex = right;
    }
    if (maxIndex != index) {
        swap(heap[maxIndex], heap[index]);
        heap[index]->indexHeapMax = index;
        heap[maxIndex]->indexHeapMax = maxIndex;
        siftDownMax(heap, maxIndex, size);
    }
}

void siftDownHalfMax(Element **heap, int index, int size) {
    int maxIndex = index;
    int left = leftChild(index);
    int right = rightChild(index);
    if (left < size && heap[left]->value > heap[maxIndex]->value) {
        maxIndex = left;
    }
    if (right < size && heap[right]->value > heap[maxIndex]->value) {
        maxIndex = right;
    }
    if (maxIndex != index) {
        swap(heap[maxIndex], heap[index]);
        heap[index]->indexHeapHalfMax = index;
        heap[maxIndex]->indexHeapHalfMax = maxIndex;
        siftDownHalfMax(heap, maxIndex, size);
    }
}

void siftDownMin(Element **heap, int index, int size) {
    int minIndex = index;
    int left = leftChild(index);
    int right = rightChild(index);
    if (left < size && heap[left]->value < heap[minIndex]->value) {
        minIndex = left;
    }
    if (right < size && heap[right]->value < heap[minIndex]->value) {
        minIndex = right;
    }
    if (minIndex != index) {
        swap(heap[minIndex], heap[index]);
        heap[index]->indexHeapMin = index;
        heap[minIndex]->indexHeapMin = minIndex;
        siftDownMin(heap, minIndex, size);
    }
}

void siftDownHalfMin(Element **heap, int index, int size) {
    int minIndex = index;
    int left = leftChild(index);
    int right = rightChild(index);
    if (left < size && heap[left]->value < heap[minIndex]->value) {
        minIndex = left;
    }
    if (right < size && heap[right]->value < heap[minIndex]->value) {
        minIndex = right;
    }
    if (minIndex != index) {
        swap(heap[minIndex], heap[index]);
        heap[index]->indexHeapHalfMin = index;
        heap[minIndex]->indexHeapHalfMin = minIndex;
        siftDownHalfMin(heap, minIndex, size);
    }
}


void addHalfMin(Element **heapMax, Element **heapMin, Element **heapHalfMin, int value, int &sizeHalfMin, int &size) {
    Element *newElement = new Element;
    newElement->indexHeapMax = size;
    newElement->indexHeapMin = size;
    newElement->indexHeapHalfMin = sizeHalfMin;
    newElement->value = value;
    heapHalfMin[sizeHalfMin] = newElement;
    heapMax[size] = newElement;
    heapMin[size] = newElement;
    ++size;
    ++sizeHalfMin;
    siftUpMax(heapMax, size - 1);
    siftUpMin(heapMin, size - 1);
    siftUpHalfMin(heapHalfMin, sizeHalfMin - 1);
}

void addHalfMax(Element **heapMax, Element **heapMin, Element **heapHalfMax, int value, int &sizeHalfMax, int &size) {
    Element *newElement = new Element;
    newElement->indexHeapMax = size;
    newElement->indexHeapMin = size;
    newElement->indexHeapHalfMax = sizeHalfMax;
    newElement->value = value;
    heapHalfMax[sizeHalfMax] = newElement;
    heapMax[size] = newElement;
    heapMin[size] = newElement;
    ++size;
    ++sizeHalfMax;
    siftUpMax(heapMax, size - 1);
    siftUpMin(heapMin, size - 1);
    siftUpHalfMax(heapHalfMax, sizeHalfMax - 1);
}

void add(Element **heapMax, Element **heapMin, Element **heapHalfMax, Element **heapHalfMin,
         int value, int &size, int &sizeHalfMin, int &sizeHalfMax) {
    if (sizeHalfMax == 0 && sizeHalfMin == 0) {
        addHalfMax(heapMax, heapMin, heapHalfMax, value, sizeHalfMax, size);
    } else if (sizeHalfMin > sizeHalfMax && value < heapHalfMin[0]->value) {
        addHalfMax(heapMax, heapMin, heapHalfMax, value, sizeHalfMax, size);
    } else if (sizeHalfMax == 0 && sizeHalfMin > 0 && value > heapHalfMin[0]->value) {
        heapHalfMax[0] = heapHalfMin[0];
        heapHalfMax[0]->indexHeapHalfMax = 0;
        heapHalfMax[0]->indexHeapHalfMin = -1;
        sizeHalfMax++;
        sizeHalfMin--;
        addHalfMin(heapMax, heapMin, heapHalfMin, value, sizeHalfMin, size);
    } else if (sizeHalfMin < sizeHalfMax && value > heapHalfMax[0]->value) {
        addHalfMin(heapMax, heapMin, heapHalfMin, value, sizeHalfMin, size);
    } else if (sizeHalfMin == 0 && sizeHalfMax > 0 && value < heapHalfMax[0]->value) {
        heapHalfMin[0] = heapHalfMax[0];
        heapHalfMin[0]->indexHeapHalfMin = 0;
        heapHalfMin[0]->indexHeapHalfMax = -1;
        sizeHalfMin++;
        sizeHalfMax--;
        addHalfMax(heapMax, heapMin, heapHalfMax, value, sizeHalfMax, size);
    } else if (value <= heapHalfMax[0]->value && sizeHalfMax <= sizeHalfMin) {
        addHalfMax(heapMax, heapMin, heapHalfMax, value, sizeHalfMax, size);
    } else if (value >= heapHalfMin[0]->value && sizeHalfMin <= sizeHalfMax) {
        addHalfMin(heapMax, heapMin, heapHalfMin, value, sizeHalfMin, size);
    } else if (value >= heapHalfMax[0]->value && value <= heapHalfMin[0]->value) {
        if (sizeHalfMax > sizeHalfMin) {
            addHalfMin(heapMax, heapMin, heapHalfMin, value, sizeHalfMin, size);
        } else {
            addHalfMax(heapMax, heapMin, heapHalfMax, value, sizeHalfMax, size);
        }
    } else if (value < heapHalfMax[0]->value && sizeHalfMax > sizeHalfMin) {
        heapHalfMin[sizeHalfMin] = heapHalfMax[0];
        heapHalfMin[sizeHalfMin]->indexHeapHalfMin = sizeHalfMin;
        siftUpHalfMin(heapHalfMin, sizeHalfMin);
        swap(heapHalfMax[0], heapHalfMax[sizeHalfMax - 1]);
        heapHalfMax[0]->indexHeapHalfMax = 0;
        heapHalfMax[sizeHalfMax - 1]->indexHeapHalfMax = -1;
        sizeHalfMax--;
        sizeHalfMin++;
        siftDownHalfMax(heapHalfMax, 0, sizeHalfMax);
        addHalfMax(heapMax, heapMin, heapHalfMax, value, sizeHalfMax, size);
    } else if (value > heapHalfMin[0]->value && sizeHalfMin > sizeHalfMax) {
        heapHalfMax[sizeHalfMax] = heapHalfMin[0];
        heapHalfMax[sizeHalfMax]->indexHeapHalfMax = sizeHalfMax;
        siftUpHalfMax(heapHalfMax, sizeHalfMax);
        swap(heapHalfMin[0], heapHalfMin[sizeHalfMin - 1]);
        heapHalfMin[0]->indexHeapHalfMin = 0;
        heapHalfMin[sizeHalfMin - 1]->indexHeapHalfMin = -1;
        sizeHalfMin--;
        sizeHalfMax++;
        siftDownHalfMin(heapHalfMin, 0, sizeHalfMin);
        addHalfMin(heapMax, heapMin, heapHalfMin, value, sizeHalfMin, size);
    }
}

void min(Element **heapMin, Element **heapMax, Element **heapHalfMax, Element **heapHalfMin, int &size, int &sizeHalfMax,
            int &sizeHalfMin) {
    if (sizeHalfMax == 0) {
        int halfMinIndex = heapMin[0]->indexHeapHalfMin;
        swap(heapHalfMin[halfMinIndex], heapHalfMin[sizeHalfMin - 1]);
        heapHalfMin[halfMinIndex]->indexHeapHalfMin = halfMinIndex;
        sizeHalfMin--;
        if (halfMinIndex < sizeHalfMin) {
            siftUpHalfMin(heapHalfMin, halfMinIndex);
            siftDownHalfMin(heapHalfMin, halfMinIndex, sizeHalfMin);
        }
    } else {
        int halfMaxIndex = heapMin[0]->indexHeapHalfMax;
        swap(heapHalfMax[halfMaxIndex], heapHalfMax[sizeHalfMax - 1]);
        heapHalfMax[halfMaxIndex]->indexHeapHalfMax = halfMaxIndex;
        sizeHalfMax--;
        if (halfMaxIndex < sizeHalfMax) {
            siftUpHalfMax(heapHalfMax, halfMaxIndex);
            siftDownHalfMax(heapHalfMax, halfMaxIndex, sizeHalfMax);
        }
        if (sizeHalfMin - sizeHalfMax > 1) {
            heapHalfMax[sizeHalfMax] = heapHalfMin[0];
            heapHalfMax[sizeHalfMax]->indexHeapHalfMax = sizeHalfMax;
            siftUpHalfMax(heapHalfMax, sizeHalfMax);
            swap(heapHalfMin[0], heapHalfMin[sizeHalfMin - 1]);
            heapHalfMin[0]->indexHeapHalfMin = 0;
            heapHalfMin[sizeHalfMin - 1]->indexHeapHalfMin = -1;
            sizeHalfMin--;
            sizeHalfMax++;
            siftDownHalfMin(heapHalfMin, 0, sizeHalfMin);
        }
    }
    int maxIndex = heapMin[0]->indexHeapMax;
    swap(heapMax[maxIndex], heapMax[size - 1]);
    heapMax[maxIndex]->indexHeapMax = maxIndex;
    swap(heapMin[0], heapMin[size - 1]);
    heapMin[0]->indexHeapMin = 0;
    size--;
    delete heapMin[size];
    siftDownMin(heapMin, 0, size);
    if (maxIndex < size) {
        siftUpMax(heapMax, maxIndex);
        siftDownMax(heapMax, maxIndex, size);
    }
}

void max(Element **heapMax, Element **heapMin, Element **heapHalfMin, Element **heapHalfMax, int &size, int &sizeHalfMin,
            int &sizeHalfMax) {
    if (sizeHalfMin == 0) {
        int halfMaxIndex = heapMax[0]->indexHeapHalfMax;
        swap(heapHalfMax[halfMaxIndex], heapHalfMax[sizeHalfMax - 1]);
        heapHalfMax[halfMaxIndex]->indexHeapHalfMax = halfMaxIndex;
        sizeHalfMax--;
        if (halfMaxIndex < sizeHalfMax) {
            siftUpHalfMax(heapHalfMax, halfMaxIndex);
            siftDownHalfMax(heapHalfMax, halfMaxIndex, sizeHalfMax);
        }
    } else {
        int halfMinIndex = heapMax[0]->indexHeapHalfMin;
        swap(heapHalfMin[halfMinIndex], heapHalfMin[sizeHalfMin - 1]);
        heapHalfMin[halfMinIndex]->indexHeapHalfMin = halfMinIndex;
        sizeHalfMin--;
        if (halfMinIndex < sizeHalfMin) {
            siftUpHalfMin(heapHalfMin, halfMinIndex);
            siftDownHalfMin(heapHalfMin, halfMinIndex, sizeHalfMin);
        }
        if (sizeHalfMax - sizeHalfMin > 1) {
            heapHalfMin[sizeHalfMin] = heapHalfMax[0];
            heapHalfMin[sizeHalfMin]->indexHeapHalfMin = sizeHalfMin;
            siftUpHalfMin(heapHalfMin, sizeHalfMin);
            swap(heapHalfMax[0], heapHalfMax[sizeHalfMax - 1]);
            heapHalfMax[0]->indexHeapHalfMax = 0;
            heapHalfMax[sizeHalfMax - 1]->indexHeapHalfMax = -1;
            sizeHalfMax--;
            sizeHalfMin++;
            siftDownHalfMax(heapHalfMax, 0, sizeHalfMax);
        }
    }
    int minIndex = heapMax[0]->indexHeapMin;
    swap(heapMin[minIndex], heapMin[size - 1]);
    heapMin[minIndex]->indexHeapMin = minIndex;
    swap(heapMax[0], heapMax[size - 1]);
    heapMax[0]->indexHeapMax = 0;
    size--;
    delete heapMax[size];
    siftDownMax(heapMax, 0, size);
    if (minIndex < size) {
        siftUpMin(heapMin, minIndex);
        siftDownMin(heapMin, minIndex, size);
    }
}

void midMin(Element **heapMax, Element **heapMin, Element **heapHalfMin, int &size, int &sizeHalfMin) {
    int minIndex = heapHalfMin[0]->indexHeapMin;
    swap(heapMin[minIndex], heapMin[size - 1]);
    heapMin[minIndex]->indexHeapMin = minIndex;
    size--;
    if (minIndex < size) {
        siftUpMin(heapMin, minIndex);
        siftDownMin(heapMin, minIndex, size);
    }
    int maxIndex = heapHalfMin[0]->indexHeapMax;
    swap(heapMax[maxIndex], heapMax[size]);
    heapMax[maxIndex]->indexHeapMax = maxIndex;
    if (maxIndex < size) {
        siftUpMax(heapMax, maxIndex);
        siftDownMax(heapMax, maxIndex, size);
    }
    swap(heapHalfMin[0], heapHalfMin[sizeHalfMin - 1]);
    heapHalfMin[0]->indexHeapHalfMin = 0;
    sizeHalfMin--;
    delete heapHalfMin[sizeHalfMin];
    siftDownHalfMin(heapHalfMin, 0, sizeHalfMin);
}

void midMax(Element **heapMax, Element **heapMin, Element **heapHalfMax, int &size, int &sizeHalfMax) {
    int maxIndex = heapHalfMax[0]->indexHeapMax;
    swap(heapMax[maxIndex], heapMax[size - 1]);
    heapMax[maxIndex]->indexHeapMax = maxIndex;
    size--;
    if (maxIndex < size) {
        siftUpMax(heapMax, maxIndex);
        siftDownMax(heapMax, maxIndex, size);
    }
    int minIndex = heapHalfMax[0]->indexHeapMin;
    swap(heapMin[minIndex], heapMin[size]);
    heapMin[minIndex]->indexHeapMin = minIndex;
    if (minIndex < size) {
        siftUpMin(heapMin, minIndex);
        siftDownMin(heapMin, minIndex, size);
    }
    swap(heapHalfMax[0], heapHalfMax[sizeHalfMax - 1]);
    heapHalfMax[0]->indexHeapHalfMax = 0;
    sizeHalfMax--;
    delete heapHalfMax[sizeHalfMax];
    siftDownHalfMax(heapHalfMax, 0, sizeHalfMax);
}


int main() {
    const int MAX_SIZE = 200000;
    int size = 0, sizeHalfMax = 0, sizeHalfMin = 0;
    int numberOfCommands;
    cin >> numberOfCommands;
    Element **heapMax = new Element *[MAX_SIZE];
    Element **heapMin = new Element *[MAX_SIZE];
    Element **heapHalfMax = new Element *[MAX_SIZE];
    Element **heapHalfMin = new Element *[MAX_SIZE];
    char *command = new char[10];
    for (int i = 0; i < numberOfCommands; ++i) {
        cin >> command;
        if (strcmp(command, "add") == 0) {
            int number;
            cin >> number;
            add(heapMax, heapMin, heapHalfMax, heapHalfMin, number, size, sizeHalfMin, sizeHalfMax);
        }
        if (strcmp(command, "min") == 0 && size != 0) {
            cout << heapMin[0]->value << endl;
            min(heapMin, heapMax, heapHalfMax, heapHalfMin, size, sizeHalfMax, sizeHalfMin);
        }
        if (strcmp(command, "max") == 0 && size != 0) {
            cout << heapMax[0]->value << endl;
            max(heapMax, heapMin, heapHalfMin, heapHalfMax, size, sizeHalfMin, sizeHalfMax);
        }
        if (strcmp(command, "mid") == 0 && size != 0) {
            if (sizeHalfMax < sizeHalfMin) {
                cout << heapHalfMin[0]->value << endl;
                midMin(heapMax, heapMin, heapHalfMin, size, sizeHalfMin);
            } else {
                cout << heapHalfMax[0]->value << endl;
                midMax(heapMax, heapMin, heapHalfMax, size, sizeHalfMax);
            }
        }
    }
    delete[] command;
    delete[] heapHalfMax;
    delete[] heapHalfMin;
    delete[] heapMax;
    delete[] heapMin;
    return 0;
}