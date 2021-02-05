#include <iostream>
#include <cmath>
using namespace std;
long long main() {
    long long x, y, p;
    cin >> x >> y >> p;
   x = x % p;
   long long result = 1;
   while (y > 0)
   {
       if (y % 2 == 1)
       {
           result = (result * x) % p;
       }
       y = (y >> 1);
       x = (x * x) % p;

   }
    cout << result;
    return 0;
}

