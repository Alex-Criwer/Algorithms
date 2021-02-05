#include<iostream>

using namespace std;

void pushBack(int *array, int value, int &size) {
    array[size] = value;
    ++size;
}

int popFront(int *array, int &size) {
    int temp = array[0];
    for (int i = 0; i < size; ++i) {
        array[i] = array[i + 1];
    }
    --size;
    return temp;
}

void pushInTheMiddle(int *array, int value, int &size) {
    if (size % 2 == 1) {
        for (int i = size; i > size / 2 + 1; --i) {
            array[i] = array[i - 1];
        }
        array[size / 2 + 1] = value;
    } else {
        for (int i = size; i > size / 2; --i) {
            array[i] = array[i - 1];
        }
        array[size / 2] = value;
    }
    ++size;
}

int main() {
    int numberOfOperations;
    char priority;
    int number, size = 0;
    cin >> numberOfOperations;
    int *arrayOfGoblins = new int[numberOfOperations];
    for (int i = 0; i < numberOfOperations; ++i) {
        cin >> priority;
        if (priority == '+') {
            cin >> number;
            pushBack(arrayOfGoblins, number, size);
        }
        if (priority == '*') {
            cin >> number;
            pushInTheMiddle(arrayOfGoblins, number, size);
        }
        if (priority == '-') {
            cout << popFront(arrayOfGoblins, size) << endl;
        }
    }
    delete[] arrayOfGoblins;
    return 0;
}
 