#include <iostream>
using namespace std;
typedef unsigned long long ull;

ull** multiplication(ull** array1, ull** array2, ull size)
{
    ull** mul_array = new ull*[size];
    for (int i = 0; i < size; ++i) {
        mul_array[i] = new ull[size];
    }
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            mul_array[i][j] = 0;
            for (int k = 0; k < size; ++k) {
                mul_array[i][j] += array1[i][k] * array2[k][j];
            }
        }
    }
    return mul_array;
}

ull** power(ull degree, ull size, ull** array)
{
    if (degree == 1) {
        return array;
    }
    ull** new_array = new ull*[size];
    for (int i = 0; i < size; ++i) {
        new_array[i] = new ull[size];
    }

    new_array = power(degree / 2, size, array);
    new_array = multiplication(new_array, new_array, size);
    if (degree % 2 != 0) {
        new_array = multiplication(new_array, array, size);
    }
    return new_array;
}

int main()
{
    ull size;
    ull degree;
    cin >> size;
    cin >> degree;
    ull** array = new ull*[size];
    ull** new_array = new ull*[size];
    for (int i = 0; i < size; ++i) {
        array[i] = new ull[size];
    }
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            cin >> array[i][j];
        }
    }

    new_array = power(degree, size, array);
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            cout << new_array[i][j] << " ";
        }
        cout << endl;
    }

    for (int i = 0; i < size; ++i) {
        delete[] array[i];
        delete[] new_array[i];
    }
    delete[] array;
    delete[] new_array;
    return 0;
}
