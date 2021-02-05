#include <iostream>
#include <map>
#include <vector>
#include <string>

int main(){
    std::map<std::string, std::map<std::string, long long>> shop;
    std::string person, thing;
    long long number;
    while(std::cin >> person){
        //if(person == "/"){
        //   break;
        //}
        std::cin.ignore(32767, ' ');
        std::cin >> thing;
        std::cin >> number;
        if(shop.find(person) == shop.end()){
            shop[person][thing] = 0;
        }
        shop[person][thing] += number;
    }

    for (auto it = shop.begin(); it != shop.end(); ++it) {
        std::cout << it->first << ":" << "\n";
        for (auto element: it->second) {
            std::cout << element.first << " " << element.second << "\n";
        }
    }
    return 0;
}
