#include <iostream>
#include<cmath>
#include<iomanip>
using namespace std;
int main() {
   double x_A, y_A, x_B, y_B;
   cin >> x_A >> y_A >> x_B >> y_B;
/*напишем функцию, как находить расстояние от произвольной точки до точек А и В
  возьмем производную и  приравняем к нулю, получим два уравнения, рассмотрим их*/
    double x0_1, x0_2;
    if (y_A == y_B)
    {
        cout << abs(x_A - x_B);
        return 0;
    }

    x0_1 = (y_A * x_B + y_B * x_A) / (y_A + y_B);
    x0_2 = (y_A * x_B - y_B * x_A) / (y_A - y_B);

    if (x0_1 > 0)
    {
        cout << setprecision(10) << x0_1;
    }
    else
    {
        cout << setprecision(10) << x0_2;
    }
    return 0;
}
