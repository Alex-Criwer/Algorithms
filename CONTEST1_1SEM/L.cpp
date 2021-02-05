#include <iostream>
using namespace std;

int main()
{
    int n, m;
    cin >> n >> m;
    long** array = new long*[
    long** new_array = new long*[n];
    for (int i = 0; i < n; ++i) {
        array[i] = new long[m];
    }
    for (int i = 0; i < n; ++i) {
        new_array[i] = new long[m];
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> array[i][j];
            new_array[i][j] = array[i][j];
        }
    }
    for (int i = 1; i < m; ++i) {
        new_array[0][i] += new_array[0][i - 1];
    }
    for (int i = 1; i < n; ++i) {
        new_array[i][0] += new_array[i - 1][0];
    }
    for (int i = 1; i < n; ++i) {
        for (int j = 1; j < m; ++j) {
            new_array[i][j] = new_array[i][j] + new_array[i][j - 1] + new_array[i - 1][j] - new_array[i - 1][j - 1];
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cout << new_array[i][j] << " ";
        }
        cout << endl;
    }
    for (int i = 0; i < n; ++i) {
        delete[] new_array[i];
    }
    for (int i = 0; i < n; ++i) {
        delete[] array[i];
    }
    delete[] new_array;
    delete[] array;
    return 0;
}
