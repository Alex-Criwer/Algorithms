#include <iostream>

using namespace std;

void quantityOfSubsequence(int *&array, int *&arrOfQuantity, int size) {
    int quantity;
    for (int i = 0; i < size; ++i) {
        quantity = 0;
        for (int j = 0; j < i; ++j) {
            if (array[i] > array[j]) {
                quantity += arrOfQuantity[j] % 1000000;
            }
        }
        arrOfQuantity[i] = quantity + 1;
    }
}

int main() {
    int size;
    cin >> size;
    int numberOfSequences;
    int *array = new int[size];
    int *arrOfQuantity = new int[size];
    for (int i = 0; i < size; ++i) {
        cin >> array[i];
        arrOfQuantity[i] = 1;
    }
    quantityOfSubsequence(array, arrOfQuantity, size);
    for (int i = 0; i < size; ++i) {
        numberOfSequences += arrOfQuantity[i];
    }
    cout << (numberOfSequences % 1000000);
    delete[] arrOfQuantity;
    delete[] array;
    return 0;
}
