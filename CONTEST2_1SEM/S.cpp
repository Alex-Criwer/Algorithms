#include<iostream>

using namespace std;

void renewWay(int *array, int *arrOfQuantity, int index, int size, int *arrOfMaxSubsequence) {
    arrOfMaxSubsequence[0] = array[index];
    int temp = 1;
    for (int i = index; i >= 0; --i) {
        if (array[index] > array[i] && (arrOfQuantity[index] - arrOfQuantity[i]) == 1) {
            arrOfMaxSubsequence[temp] = array[i];
            index = i;
            ++temp;
        }
    }
}

int indexOfMaxSequenceLength(int *arrOfQuantity, int size) {
    int maxLength = 0;
    int index = 0;
    for (int i = 0; i < size; ++i) {
        if (arrOfQuantity[i] > maxLength) {
            maxLength = arrOfQuantity[i];
            index = i;
        }
    }
    return index;
}

int returnMaxLength(int *arrOfQuantity, int index) {
    return arrOfQuantity[index];
}

int findMaxSubsequence(int *array, int *arrOfQuantity, int *arrOfMaxSubsequence, int size) {
    for (int i = 0; i < size; ++i) {
        int maxLength = 0;
        for (int j = 0; j < i; ++j) {
            if (array[j] < array[i] && arrOfQuantity[j] > maxLength) {
                maxLength = arrOfQuantity[j];
            }
        }
        arrOfQuantity[i] = maxLength + 1;
    }
    int indexOfMaxSubsequenceLength = indexOfMaxSequenceLength(arrOfQuantity, size);
    renewWay(array, arrOfQuantity, indexOfMaxSubsequenceLength, size, arrOfMaxSubsequence);
    int maxSubsequenceLength = returnMaxLength(arrOfQuantity, indexOfMaxSubsequenceLength);
    return maxSubsequenceLength;
}

int main() {
    int size;
    cin >> size;
    int *array = new int[size];
    int *arrOfQuantity = new int[size];
    int *arrOfMaxSubsequence = new int[size];
    for (int i = 0; i < size; ++i) {
        cin >> array[i];
        arrOfQuantity[i] = 1;
    }
    int sizeOfMaxSubsequence = findMaxSubsequence(array, arrOfQuantity, arrOfMaxSubsequence, size);
    for (int i = sizeOfMaxSubsequence - 1; i >= 0; --i) {
        cout << arrOfMaxSubsequence[i] << " ";
    }
    delete[] array;
    delete[]arrOfMaxSubsequence;
    delete[] arrOfQuantity;
    return 0;
}
