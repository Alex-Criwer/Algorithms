#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

double value(int A, int B, int C, int D, double arg)
{
    return A * pow(arg, 3) + B * pow(arg, 2) + C * arg + D;
}
double result(int A, int B, int C, int D)
{
    double left_border = -1000, right_border = 1000;
    double x;
    double length = right_border - left_border;
    x = (left_border + right_border) / 2.0;
    while (length >= 0.0000001) {
        if (value(A, B, C, D, x) == 0) {
            return x;
        }
        else if (value(A, B, C, D, x) * value(A, B, C, D, left_border) < 0) {
            right_border = x;
        }
        else {
            left_border = x;
        }
        length = right_border - left_border;
        x = (left_border + right_border) / 2.0;
    }
    return x;
}

int main()
{
    int A, B, C, D;
    cin >> A >> B >> C >> D;
    cout << setprecision(10) << result(A, B, C, D);
    return 0;
}


