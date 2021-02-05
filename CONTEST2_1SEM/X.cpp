#include <iostream>
#include<cstring>

using namespace std;

bool isLetter(char a) {
    if (a != '?' && a != '*') {
        return true;
    }
    return false;
}

int minForTwo(int a, int b) {
    if (a < b) {
        return a;
    }
    return b;
}

int main() {
    char *str1 = new char[81];
    char *str2 = new char[81];
    cin.getline(str1, 81);
    cin.getline(str2, 81);
    char *resultStr = new char[81];
    int length1 = strlen(str1);
    int length2 = strlen(str2);
    int **arrayOfResults = new int *[length1 + 1];
    for (int i = 0; i < length1 + 1; ++i) {
        arrayOfResults[i] = new int[length2 + 1];
    }

    arrayOfResults[0][0] = 0; // начальное заполнение
    for (int i = 1; i < length1 + 1; ++i) {
        if (str1[i - 1] == '*') {
            arrayOfResults[i][0] = arrayOfResults[i - 1][0];
        } else {
            arrayOfResults[i][0] = -1;
        }
    }
    for (int i = 1; i < length2 + 1; ++i) {
        if (str2[i - 1] == '*') {
            arrayOfResults[0][i] = arrayOfResults[0][i - 1];
        } else {
            arrayOfResults[0][i] = -1;
        }
    }

    for (int i = 1; i < length1 + 1; ++i) {
        for (int j = 1; j < length2 + 1; ++j) {

            if (isLetter(str1[i - 1]) && isLetter(str2[j - 1]) && str1[i - 1] == str2[j - 1]) {
                arrayOfResults[i][j] = arrayOfResults[i - 1][j - 1] + 1;
            }
            if (isLetter(str1[i - 1]) && isLetter(str2[j - 1]) && str1[i - 1] != str2[j - 1]) {
                arrayOfResults[i][j] = -1;
            }
            if (isLetter(str1[i - 1]) && str2[j - 1] == '?') {
                arrayOfResults[i][j] = arrayOfResults[i - 1][j - 1] + 1;
            }
            if (isLetter(str2[j - 1]) && str1[i - 1] == '?') {
                arrayOfResults[i][j] = arrayOfResults[i - 1][j - 1] + 1;
            }
            if (str1[i - 1] == '?' && str2[j - 1] == '?') {
                arrayOfResults[i][j] = arrayOfResults[i - 1][j - 1] + 1;
            }


            if (str1[i - 1] == '*' && (isLetter(str2[j - 1]) || str2[j - 1] == '?')) {
                if (arrayOfResults[i - 1][j] == -1 && arrayOfResults[i][j - 1] != -1) {
                    arrayOfResults[i][j] = arrayOfResults[i][j - 1] + 1;
                    continue;
                }
                if (arrayOfResults[i][j - 1] == -1 && arrayOfResults[i - 1][j] != -1) {
                    arrayOfResults[i][j] = arrayOfResults[i - 1][j];
                    continue;
                }
                if (arrayOfResults[i][j - 1] == -1 && arrayOfResults[i - 1][j] == -1) {
                    arrayOfResults[i][j] = -1;
                    continue;
                }
                arrayOfResults[i][j] = minForTwo(arrayOfResults[i - 1][j], arrayOfResults[i][j - 1] + 1);
            }

            if (str2[j - 1] == '*' && (isLetter(str1[i - 1]) || str1[i - 1] == '?')) {
                if(arrayOfResults[i][j - 1] == -1 && arrayOfResults[i - 1][j] != -1){
                    arrayOfResults[i][j] = arrayOfResults [i - 1][j] + 1;
                    continue;
                }
                if(arrayOfResults[i - 1][j] == -1 && arrayOfResults[i][ j - 1] != -1){
                    arrayOfResults[i][j] = arrayOfResults[i][ j - 1];
                    continue;
                }
                if(arrayOfResults[i - 1][j] == -1 && arrayOfResults[i][ j - 1] == -1){
                    arrayOfResults[i][j] = -1;
                    continue;
                }
                arrayOfResults[i][j] = minForTwo(arrayOfResults[i][j - 1], arrayOfResults[i - 1][j] + 1);
            }


            if (str1[i - 1] == '*' && str2[j - 1] == '*') {
                if(arrayOfResults[i - 1][j] == -1 && arrayOfResults[i][j - 1] != -1 ){
                    arrayOfResults[i][j] = arrayOfResults[i][j - 1];
                    continue;
                }
                if(arrayOfResults[i][j - 1] == -1 && arrayOfResults[i - 1][j] != - 1){
                    arrayOfResults[i][j] = arrayOfResults[i - 1][j];
                    continue;
                }
                if(arrayOfResults[i][j - 1] == -1 && arrayOfResults[i - 1][j] == - 1){
                    arrayOfResults[i][j] = -1;
                    continue;
                }
                arrayOfResults[i][j] = minForTwo(arrayOfResults[i - 1][j], arrayOfResults[i][j - 1]);
            }
        }
    }

    cout << "____________" << arrayOfResults[length1][length2] << "_____________" << endl;


    for (int i = 0; i < length1 + 1; ++i) {
        for (int j = 0; j < length2 + 1; ++j) {
            cout << arrayOfResults[i][j] << " ";
        }
        cout << endl;
    }

    for (int i = 0; i < length1 + 1; ++i) {
        delete[] arrayOfResults[i];
    }
    delete[] resultStr;
    delete[] arrayOfResults;
    delete[] str1;
    delete[] str2;
    return 0;
}
