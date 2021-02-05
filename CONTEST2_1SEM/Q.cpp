#include<iostream>

using namespace std;

int minimumForThree(int num1, int num2, int num3) {
    int min = num1;
    if (min > num2) {
        min = num2;
    }
    if (min > num3) {
        min = num3;
    }
    return min;
}

int minimumForTwo(int num1, int num2) {
    if (num1 < num2) {
        return num1;
    }
    return num2;
}

int main() {
    unsigned int number;
    cin >> number;
    int *array = new int[number + 1];
    array[0] = 0;
    array[1] = 0;
    array[2] = 1;
    array[3] = 1;
    for (int i = 4; i < number + 1; ++i) {
        if (i % 2 == 0 && i % 3 == 0) {
            array[i] = minimumForThree(array[i - 1], array[i / 2], array[i / 3]) + 1;
        } else if (i % 2 == 0) {
            array[i] = minimumForTwo(array[i - 1], array[i / 2]) + 1;
        } else if (i % 3 == 0) {
            array[i] = minimumForTwo(array[i - 1], array[i / 3]) + 1;
        } else {
            array[i] = array[i - 1] + 1;
        }
    }
    cout << array[number] << endl;
    delete[] array;
    return 0;
}