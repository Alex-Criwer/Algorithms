#include<iostream>

using namespace std;

int minimumForTwo(int num1, int num2) {
    if (num1 < num2) {
        return num1;
    }
    return num2;
}

int main() {
    int size;
    cin >> size;
    int *array = new int[size];
    int *arrOfMinLength = new int[size + 1];
    for (int i = 0; i < size; ++i) {
        cin >> array[i];
    }
    for (int i = 1; i < size; ++i) {
        int j = i - 1;
        while (j >= 0 && array[j] > array[j + 1]) {
            swap(array[j], array[j + 1]);
            --j;
        }
    }
    arrOfMinLength[0] = 0;
    arrOfMinLength[1] = 0;
    arrOfMinLength[2] = array[1] - array[0];
    if (size > 2) {
        arrOfMinLength[3] = array[2] - array[0];
    }
    for (int i = 4; i < size + 1; ++i) {
        arrOfMinLength[i] = minimumForTwo(arrOfMinLength[i - 1], arrOfMinLength[i - 2]) + array[i - 1] - array[i - 2];
    }
    cout << arrOfMinLength[size] << endl;
    delete[] arrOfMinLength;
    delete[] array;
    return 0;
}

