#include <iostream>
using namespace std;
int main()
{
    int number;
    int k;
    cin >> number >> k;
    int position = 1;
    if(number == 1){
        return 1;
    }
    else {
        for (int i = 2; i <= number; ++i) {
            position = (position + k - 1) % i + 1;
        }
        cout << position;
    }

    return 0;
}