#include <iostream>
#include <cmath>
using namespace std;

int main()
{
    int size;
    cin >> size;
    int** array = new int*[size];
    for (int i = 0; i < size; ++i) {
        array[i] = new int[size];
    }
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            array[i][j] = 0;
        }
    }
    int num = 2;
    array[0][0] = 1;
    for (int j = 1; j < size; ++j) {
        if (j % 2 == 0) {
            int temp1 = j;
            int temp2 = 1;
            while (temp1 >= 0) {
                array[j][j - temp1] = num;
                ++num;
                --temp1;
            }
            while (temp2 <= j) {
                array[j - temp2][j] = num;
                ++num;
                ++temp2;
            }
        }
        else {
            int temp1 = j - 1;
            int temp2 = 0;
            while (temp2 <= j) {
                array[temp2][j] = num;
                ++num;
                ++temp2;
            }
            while (temp1 >= 0) {
                array[j][temp1] = num;
                ++num;
                --temp1;
            }
        }
    }
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            cout << array[i][j] << " ";
        }
        cout << endl;
    }
    for (int i = 0; i < size; ++i) {
        delete[] array[i];
    }
    delete[] array;
    return 0;
}


