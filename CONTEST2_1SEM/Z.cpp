#include <iostream>

using namespace std;

int check(int j, int i, int size) {
    char *str1 = new char[size];
    char *str2 = new char[size];
    for (int k = 0; k < size; ++k) {
        str1[k] = j % 2;
        str2[k] = i % 2;
        j /= 2;
        i /= 2;
    }
    for (int k = 1; k < size; ++k) {
        if (str1[k - 1] == str2[k - 1] && str1[k] == str2[k] && str1[k] == str1[k - 1]) {
            return 0;
        }
    }
    return 1;
}

int main() {
    int n, m;
    cin >> n >> m;
    if (n > m) {
        swap(n, m);
    }
    int size = 1 << n;
    int **array = new int *[m];
    for (int i = 0; i < m; ++i) {
        array[i] = new int[size];
    }
    for (int i = 0; i < size; ++i) {
        array[0][i] = 1;
    }
    for (int k = 1; k < m; ++k) {
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                array[k][i] = array[k][i] + array[k - 1][j] * check(j, i, n);
            }
        }
    }
    int result = 0;
    for (int i = 0; i < size; ++i) {
        result += array[m - 1][i];
    }
    cout << result << endl;
    for (int i = 0; i < m; ++i) {
        delete[] array[i];
    }
    delete[] array;
    return 0;
}
