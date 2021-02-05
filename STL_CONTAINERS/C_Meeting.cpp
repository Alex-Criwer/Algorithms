#include <iostream>
#include <algorithm>
#include <vector>


int main(){
    int size, n, number, counter = 0;
    std::cin >> size;
    std::vector<int> myVector;
    myVector.reserve(size);
    for (int i = 0; i < size; ++i) {
        std::cin >> n;
        myVector.push_back(n);
    }
    std::cin >> number;
    for(auto element: myVector){
        if(element == number)
            ++counter;
    }
    std::cout << counter;
    return 0;
}