#include <iostream>
#include <algorithm>
#include <vector>

int main(){
    int size, color;
    std::cin >> size;
    std::vector <int> animals;
    animals.reserve(size);
    for (int i = 0; i < size; ++i) {
        std::cin >> color;
        animals.push_back(color);
    }
    int what;
    std::cin >> what;
    for (int i = 0; i < what; ++i) {
        std::cin >> color;
        std::cout << std::upper_bound(animals.begin(), animals.end(),color) - std::lower_bound(animals.begin(), animals.end(),color) << '\n';
    }
    return 0;
}