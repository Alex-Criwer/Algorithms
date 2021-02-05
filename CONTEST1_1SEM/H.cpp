#include <iostream>
#include <cmath>
using namespace std;

long long phi(int n)
{
    if (n == 1 || n == 2) {
        return 1;
    }
    long long fib_sum = 0;
    long long fib1 = 1;
    long long fib2 = 1;

    while (n != 2) {
        fib_sum = (fib1 + fib2) % 1000;
        fib1 = fib2;
        fib2 = fib_sum;
        --n;
    }
    return (fib_sum % 1000);
}

int main()
{
    int n;
    cin >> n;
    long long temp = phi(n) % 1000;
    if (n < 17) {
        cout << temp;
    }
    else if (n >= 17) {
        if (temp < 100 && temp >= 10) {
            cout << "0" << temp;
        }
        else if (temp >= 0 && temp < 10) {
            cout << "00" << temp;
        }
        else {
            cout << temp;
        }
    }
    return 0;
}