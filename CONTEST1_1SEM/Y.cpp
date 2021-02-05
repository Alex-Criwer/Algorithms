#include <iostream>
using namespace std;

int sorting(int* array, int size)
{
    int j;
    for (int i = 1; i < size; ++i) {
        j = i - 1;
        while (j >= 0 && (array[j] > array[j + 1])) {
            swap(array[j], array[j + 1]);
            --j;
        }
    }
    return 0;
}

int main()
{
    int size;
    cin >> size;
    int sum;
    cin >> sum;
    int new_sum = 0;
    int* array = new int[size];
    for (int i = 0; i < size; ++i) {
        cin >> array[i];
    }
    sorting(array, size);

    for (int i = 0; i < size - 2; ++i) {
        int left = i + 1;
        int right = size - 1;
        while (left < right) {
            new_sum = array[i] + array[left] + array[right];
            if (new_sum == sum && i != left && i != right && right != left) {
                cout << "YES" << endl;
                cout << array[left] << " " << array[i] << " " << array[right];
                return 0;
            }
            else if (new_sum < sum) {
                ++left;
            }
            else if (new_sum > sum) {
                --right;
            }
        }
    }
    cout << "NO";
    delete[] array;
    return 0;
}
