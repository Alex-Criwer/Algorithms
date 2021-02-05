#include <iostream>
#include <cmath>
using namespace std;

long long main() {
    long long previous = 0, next = 0, current = 0;
    long long number = 0;
    cin >> previous >> current >> next;
    while (next != 0)
    {
        if (current > previous && current > next)
        {
            ++number;
        }
        previous = current;
        current = next;
        cin >> next;
    }
    cout << number;

    return 0;
}
