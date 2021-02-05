#include <iostream>
using namespace std;
int main() {
    int number = 0;
    long size;
    cin >> size;
    int* array = new int[size];
    for (int i = 0; i < size; ++i) {
        cin >> array[i];
    }
    bool check;
    for (int i = 0; i < size - 1; ++i) {
        check = true;
        for (int j = 0; j < size - 1 - i; ++j) {
            if (array[j] > array [j+1])
            {
                swap(array[j], array[j+1]);
                check = false;
                ++number;
            }
        }
        if (check)
        {
            break;
        }
    }
    cout << number;
    delete[] array;
    return 0;
}

