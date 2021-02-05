#include <iostream>
#include <cmath>
#include <cstring>
#include "string.h"
using namespace std;

long long digital_root(long long elem)
{
    long long sum = 0;

    do {
        while (elem > 0) {
            sum += elem % 10;
            elem /= 10;
        }
        elem = sum;
        sum = 0;

    } while (elem > 9);
    return elem;
}

int main()
{
    int size;
    cin >> size;
    char** array = new char*[size];
    int* sqrts = new int[size];
    for (int i = 0; i < size; ++i) {
        array[i] = new char[1000];
        sqrts[i] = 0;
        cin >> array[i];
    }

    for (int i = 0; i < size; ++i) {
        for (int j = 0; array[i][j] != '\0'; ++j) {
            sqrts[i] += (int)(array[i][j] - '0');
            sqrts[i] = digital_root(sqrts[i]);
        }
    }

    int j;
    for (int i = 1; i < size; ++i) {
        j = i - 1;
        while (j >= 0 && (sqrts[j]) >= sqrts[j + 1]) {
            if ((sqrts[j] == sqrts[j + 1])) {
                if ((strlen(array[j]) > strlen(array[j + 1])) || (strlen(array[j]) == strlen(array[j + 1]) && strcmp(array[j], array[j + 1]) > 0)) {
                    swap(array[j], array[j + 1]);
                    swap(sqrts[j], sqrts[j + 1]);
                }
            }
            else {
                swap(array[j], array[j + 1]);
                swap(sqrts[j], sqrts[j + 1]);
            }
            --j;
        }
    }

    for (int i = 0; i < size; ++i) {
        cout << array[i] << endl;
    }
    for (int i = 0; i < size; ++i) {
        delete[] array[i];
    }
    delete[] sqrts;
    delete[] array;
    return 0;
}