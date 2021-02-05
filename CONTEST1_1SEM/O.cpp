#include <iostream>
using namespace std;
long long main()
{
    long size;
    cin >> size;
    long long* array = new long long[size];
    for (long long i = 0; i < size; ++i) {
        cin >> array[i];
    }
    long long j;
    for (long long i = 1; i < size; ++i) {
        j = i - 1;
        while (j >= 0 && array[j] > array[j + 1]) {
            swap(array[j], array[j + 1]);
            --j;
        }
    }
    for (long long i = 0; i < size; ++i) {
        cout << array[i] << " ";
    }
    delete[] array;
    return 0;
}