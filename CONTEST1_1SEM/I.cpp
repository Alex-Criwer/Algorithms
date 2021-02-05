#include <iostream>
using namespace std;
int main()
{
    int size;
    cin >> size;
    int* array_of_ages = new int[1001];
    int* array = new int[size];
    for (int i = 0; i < size; ++i) {
        cin >> array[i];
        ++array_of_ages[array[i]];
    }
    int max = 0;
    int index;
    for (int i = 0; i < 1001; ++i) {
        if (array_of_ages[i] > max)
        {
            max = array_of_ages[i];
            index = i;
        }
    }
    cout << index;
    delete[] array_of_ages;
    delete[] array;
    return 0;
}