#include <iostream>

using namespace std;

int maxForTwo(int a, int b) {
    if (a > b) {
        return a;
    }
    return b;
}

int main() {
    int temp = 0;
    int lengthTheFirst, lengthTheSecond;
    cin >> lengthTheFirst;
    int *arrayTheFirst = new int[lengthTheFirst];
    for (int i = 0; i < lengthTheFirst; ++i) {
        cin >> arrayTheFirst[i];
    }
    cin >> lengthTheSecond;
    int *arrayTheSecond = new int[lengthTheSecond];
    for (int i = 0; i < lengthTheSecond; ++i) {
        cin >> arrayTheSecond[i];
    }
    int **resultArray = new int *[lengthTheFirst + 1];
    for (int i = 0; i < lengthTheFirst + 1; ++i) {
        resultArray[i] = new int[lengthTheSecond + 1];
    }
    for (int i = 0; i < lengthTheFirst + 1; ++i) {
        for (int j = 0; j < lengthTheSecond + 1; ++j) {
            resultArray[i][j] = 0;
        }
    }
    //заполняем массив результатов
    for (int i = 1; i < lengthTheFirst + 1; ++i) {
        for (int j = 1; j < lengthTheSecond + 1; ++j) {
            if (arrayTheFirst[i - 1] == arrayTheSecond[j - 1]) {
                resultArray[i][j] = resultArray[i - 1][j - 1] + 1;
            } else {
                resultArray[i][j] = maxForTwo(resultArray[i - 1][j], resultArray[i][j - 1]);
            }
        }
    }
    int length = resultArray[lengthTheFirst][lengthTheSecond];
    int *renewWay = new int[length];
    int tempI = lengthTheFirst;
    int tempJ = lengthTheSecond;
    while (tempI > 0 && tempJ > 0) {
        if (arrayTheFirst[tempI - 1] == arrayTheSecond[tempJ - 1]) {
            renewWay[temp++] = arrayTheFirst[tempI - 1];
            --tempI;
            --tempJ;
        } else if (resultArray[tempI - 1][tempJ] == resultArray[tempI][tempJ]) {
            --tempI;
        } else {
            --tempJ;
        }
    }

    for (int i = temp - 1; i >= 0; --i) {
        cout << renewWay[i] << " ";
    }
    for (int i = 0; i < lengthTheFirst + 1; ++i) {
        delete[] resultArray[i];
    }
    delete[] renewWay;
    delete[] resultArray;
    delete[] arrayTheSecond;
    delete[] arrayTheFirst;
    return 0;
}