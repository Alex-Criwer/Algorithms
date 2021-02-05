#include<iostream>
#include <unordered_map>
#include <string>

int main() {
    int size;
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::string firstWord, secondWord, findWord;
    std::cin >> size;
    std::unordered_map<std::string, std::string> dictionary1, dictionary2;
    for (int i = 0; i < size; ++i) {
        std::cin >> firstWord >> secondWord;
        dictionary1[firstWord] = secondWord;
        dictionary2[secondWord] = firstWord;
    }
    int temp;
    std::cin >> temp;
    for (int i = 0; i < temp; ++i) {
        std::cin >> findWord;
        if (dictionary1.find(findWord) != dictionary1.end()) {
            std::cout << dictionary1[findWord] << "\n";
            continue;
        }
        if (dictionary2.find(findWord) != dictionary2.end()) {
            std::cout << dictionary2[findWord] << "\n";
            continue;
        }
    }
    return 0;
}
