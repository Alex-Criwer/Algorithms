#include <iostream>
using namespace std;

int main(){
    int n, k;
    cin >> n >> k;
    bool** array = new bool*[2];
    for (int i = 0; i < 2; ++i) {
        array[i] = new bool[n];
    }
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < n; ++j) {
            array[i][j] = true;
        }
    }
    int x, y;
    for (int i = 0; i < k; ++i) {
        cin >> x >> y;
        --x;
        --y;
        array[y][x] = 0;
    }
    int* arrayA = new int[n + 1];
    int* arrayB = new int[n + 1];
    int* arrayC = new int[n + 1];
    arrayA[0] = arrayB[1] = arrayC[1] = 1;
    arrayA[1] = 2;

    for (int i = 2; i < n + 1; ++i) {
        arrayA[i] = arrayA[i - 1] * 2 + arrayB[i - 1] + arrayC[i - 1] + arrayA[i - 2];
        arrayB[i] = arrayA[i - 1] + arrayC[i - 1];
        arrayC[i] = arrayA[i - 1] + arrayB[i - 1];
    }






    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << array[i][j] << " ";
        }
        cout << endl;
    }
    for (int i = 0; i < 2; ++i) {
        delete[] array[i];
    }
    delete[] arrayA;
    delete[] arrayB;
    delete[] arrayC;
    delete[] array;
    return 0;
}

