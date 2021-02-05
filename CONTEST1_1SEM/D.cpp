#include <iostream>
#include <cmath>
using namespace std;

long long gcd (long long x, long long y)
{
    while (y != 0) {
        long long c = x % y;
        x = y;
        y = c;
    }
    return x;
}
long long scf (long long x, long long y)
{
    return (x * y) / gcd(x, y);
}

int main() {
    long long  x, y;
    cin >> x >> y;
    cout << gcd(x, y) << " " << scf(x, y);
    return 0;
}

