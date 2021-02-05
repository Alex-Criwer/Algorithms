#include <iostream>
#include <cstring>

using namespace std;

int minForThree(int **array, char *str1, char *str2, int i, int j) {
    int a;
    if (str1[i - 1] == str2[j - 1]) {
        a = array[i - 1][j - 1];
    } else {
        a = array[i - 1][j - 1] + 1;
    }
    int b = array[i - 1][j] + 1;
    int c = array[i][j - 1] + 1;
    int min = a;
    if (min > b) {
        min = b;
    }
    if (min > c) {
        min = c;
    }
    return min;
}

int main() {
    char *str1 = new char[1001];
    char *str2 = new char[1001];
    cin.getline(str1, 1001);
    cin.getline(str2, 1001);
    int lengthStr1 = strlen(str1);
    int lengthStr2 = strlen(str2);
    int **resultArray = new int *[lengthStr1 + 1];
    for (int i = 0; i < lengthStr1 + 1; ++i) {
        resultArray[i] = new int[lengthStr2 + 1];
    }
    for (int i = 0; i < lengthStr1 + 1; ++i) {
        resultArray[i][0] = i;
    }
    for (int j = 0; j < lengthStr2 + 1; ++j) {
        resultArray[0][j] = j;
    }
    for (int i = 1; i < lengthStr1 + 1; ++i) {
        for (int j = 1; j < lengthStr2 + 1; ++j) {
            resultArray[i][j] = minForThree(resultArray, str1, str2, i, j);
        }
    }
    cout << resultArray[lengthStr1][lengthStr2];
    for (int i = 0; i < lengthStr1 + 1; ++i) {
        delete[] resultArray[i];
    }
    delete[] resultArray;
    delete[] str1;
    delete[] str2;
    return 0;
}
