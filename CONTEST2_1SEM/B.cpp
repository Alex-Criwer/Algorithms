#include <iostream>

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

void siftDown(int *heap, int &index, int heapSize) {
    int left = leftChild(index);
    int right = rightChild(index);
    int maxIndex = index;
    if (left < heapSize && heap[left] > heap[maxIndex]) {
        maxIndex = left;
    }
    if (right < heapSize && heap[right] > heap[maxIndex]) {
        maxIndex = right;
    }
    if (maxIndex != index) {
        swap(heap[index], heap[maxIndex]);
        index = maxIndex;
        siftDown(heap, index, heapSize);
    }
}

int siftUp(int *heap, int index) {
    while (index > 0 && heap[index] > heap[parent(index)]) {
        swap(heap[index], heap[parent(index)]);
        index = parent(index);
    }
    return index + 1;
}

void addElement(int *heap, int value, int heapSize) {
    heap[heapSize - 1] = value;
    cout << siftUp(heap, heapSize - 1) << endl;
}

void deleteElement(int *queue, int index, int &queueSize) {
    --index;
    int index2 = index;
    cout << queue[index] << endl;
    swap(queue[index], queue[queueSize - 1]);
    --queueSize;
    if (index < queueSize) {
        siftDown(queue, index, queueSize);
        siftUp(queue, index2);
    }
}

int main() {
    int queueSize;
    int numberOfAdds = 0;
    int numberOfOperations;
    cin >> queueSize >> numberOfOperations;
    int *queue = new int[queueSize];
    for (int i = 0; i < numberOfOperations; ++i) {
        int k;
        cin >> k;
        if (k == 1) {
            if (numberOfAdds == 0) {
                cout << "-1" << endl;
            } else if (numberOfAdds == 1) {
                cout << "0" << ' ' << queue[0] << endl;
                --numberOfAdds;
            } else if (numberOfAdds > 0) {
                int currMax = queue[0];
                swap(queue[0], queue[numberOfAdds - 1]);
                --numberOfAdds;
                int index = 0;
                siftDown(queue, index, numberOfAdds);
                cout << index + 1 << ' ' << currMax << endl;
            }
        } else if (k == 2) {
            int n;
            cin >> n;
            if (numberOfAdds == queueSize) {
                cout << "-1" << endl;
            } else {
                ++numberOfAdds;
                addElement(queue, n, numberOfAdds);
            }
        } else if (k == 3) {
            int index;
            cin >> index;
            if (index > numberOfAdds || index <= 0) {
                cout << "-1" << endl;
            } else {
                deleteElement(queue, index, numberOfAdds);
            }
        }
    }

    for (int i = 0; i < numberOfAdds; ++i) {
        cout << queue[i] << " ";
    }
    delete[] queue;
    return 0;
}
