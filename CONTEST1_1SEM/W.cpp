#include <iostream>
#include <cmath>
using namespace std;
int hanoi_tower(int n, int stick_from, int stick_to, int stick_additional)
{
    if (n == 0) {
        return 0;
    }
    hanoi_tower(n - 1, stick_from, stick_additional, stick_to);
    cout << stick_from << " " << stick_to << endl;
    hanoi_tower(n - 1, stick_additional, stick_to, stick_from);
    return 0;
}

int main()
{
    int n = 0;
    cin >> n;
    hanoi_tower(n, 1, 2, 3);
    return 0;
}

