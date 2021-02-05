#include <iostream>
using namespace std;

int main()
{
    std::ios_base::sync_with_stdio(false);
    int size;
    cin >> size;
    int* array = new int[size];
    for (int i = 0; i < size; ++i) {
        cin >> array[i];
    }
    int the_first_max = array[0];
    int the_second_max = array[1];
    int the_third_max = array[2];
    int the_first_min = array[0];
    int the_second_min = array[1];

    if (the_first_min > the_second_min) {
        swap(the_first_min, the_second_min);
    }
    if (the_first_max > the_second_max) {
        swap(the_first_max, the_second_max);
    }
    if (the_second_max > the_third_max) {
        swap(the_second_max, the_third_max);
    }
    if (the_first_max > the_second_max) {
        swap(the_first_max, the_second_max);
    }
    for (int i = 3; i < size; ++i) {
        if (array[i] > the_first_max) {
            the_first_max = array[i];
        }
        if (the_first_max > the_second_max) {
            swap(the_first_max, the_second_max);
        }
        if (the_second_max > the_third_max) {
            swap(the_second_max, the_third_max);
        }
    }
    for (int i = 2; i < size; ++i) {
        if (array[i] < the_second_min) {
            the_second_min = array[i];
        }
        if (the_second_min < the_first_min) {
            swap(the_second_min, the_first_min);
        }
    }
    if ((long long)the_first_min * the_second_min * the_third_max > (long long)the_first_max * the_second_max * the_third_max) {
        cout << the_first_min << " " << the_second_min << " " << the_third_max;
    }
    else {
        cout << the_first_max << " " << the_second_max << " " << the_third_max;
    }
    delete[] array;
    return 0;
}
