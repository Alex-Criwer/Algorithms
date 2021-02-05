#include <iostream>
#include <cmath>
using namespace std;

int main()
{
    int* array_of_numbers = new int[10];
    int A, B;
    cin >> A >> B;
    int temp;
    while (A <= B) {
        temp = A;
        do {
            int temp1 = temp % 10;
            ++array_of_numbers[temp1];
            temp /= 10;

        } while (temp > 0);
        ++A;
    }
    for (int i = 0; i < 10; ++i) {
        cout << array_of_numbers[i] << " ";
    }
    return 0;
}

