#include <iostream>
#include <cmath>
using namespace std;

int gcd(int x, int y)
{
    int z;
    while (y != 0) {
        z = x % y;
        x = y;
        y = z;
    }
    return x;
}
int main()
{
    int a, b, c;
    cin >> a >> b >> c;
    int gcd_div = gcd(a, b);
    if (c % gcd_div != 0) {
        cout << "Impossible";
        return 0;
    }
    a /= gcd_div;
    b /= gcd_div;
    c /= gcd_div;
    for (int i = 0;; ++i) {
        if ((c - i * a) % b == 0) {
            cout << i << " " << (c - i * a) / b;
            return 0;
        }
    }
}


