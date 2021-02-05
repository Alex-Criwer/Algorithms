#include<iostream>

using namespace std;

int maxForTwo(int a, int b) {
    if (a > b) {
        return a;
    }
    return b;
}

int main() {
    int numberOfStuff, maxWeight;
    cin >> numberOfStuff >> maxWeight;
    int *resultArray = new int[numberOfStuff];
    int **arrayMassCost = new int *[numberOfStuff + 1];
    int **array = new int *[numberOfStuff + 1];
    for (int i = 0; i < numberOfStuff + 1; ++i) {
        arrayMassCost[i] = new int[2];
        array[i] = new int[maxWeight + 1];
    }
    arrayMassCost[0][0] = 0;
    arrayMassCost[0][1] = 0;
    for (int i = 1; i < numberOfStuff + 1; ++i) {
        cin >> arrayMassCost[i][1]; // ввод масс
        array[i][0] = 0;
    }
    for (int i = 1; i < numberOfStuff + 1; ++i) {
        cin >> arrayMassCost[i][0]; //ввод стоимости
    }
    for (int i = 0; i < maxWeight + 1; ++i) {
        array[0][i] = 0;
    }

    for (int i = 1; i < numberOfStuff + 1; ++i) {
        for (int j = 1; j < maxWeight + 1; ++j) {
            if (j >= arrayMassCost[i][1]) {
                array[i][j] = maxForTwo(array[i - 1][j], arrayMassCost[i][0] + array[i - 1][j - arrayMassCost[i][1]]);
            } else {
                array[i][j] = array[i - 1][j];
            }
        }
    }

    int temp = 0;
    int i = numberOfStuff, j = maxWeight;
    while (true) {
        if (array[i][j] == 0) {
            break;
        }
        if (array[i - 1][j] == array[i][j]) {
            --i;
            continue;
        } else if (i != 0) {
            resultArray[temp++] = i;
            j = j - arrayMassCost[i][1];
            --i;
            continue;
        }
    }

    for (int i = 0; i < (temp + 1) / 2; ++i) {
        swap(resultArray[i], resultArray[temp - i - 1]);
    }
    for (int i = 0; i < temp; ++i) {
        cout << resultArray[i] << endl;
    }
    for (int i = 0; i < numberOfStuff + 1; ++i) {
        delete[] arrayMassCost[i];
        delete[] array[i];
    }
    delete[] resultArray;
    delete[] arrayMassCost;
    delete[] array;
    return 0;
}

