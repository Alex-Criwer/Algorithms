#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <string>

int main(){
    int numberOfOperations, operation,sum;
    std::string name;
    std::cin >> numberOfOperations;
    std::unordered_map<std::string, int> bank;
    for (int i = 0; i < numberOfOperations; ++i) {
        std::cin >> operation;
        if(operation == 1){
            std::cin >> name;
            std::cin >> sum;
            if(bank.find(name) == bank.end()){
                bank[name] = 0;
            }
            bank[name] += sum;
        } else if(operation == 2){
            std::cin >> name;
            if(bank.find(name) == bank.end()){
                std::cout << "ERROR" << '\n';
                continue;
            } else{
                std::cout << bank[name] << '\n';
            }
        }
    }

    return 0;
}
