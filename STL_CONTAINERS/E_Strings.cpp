#include <iostream>
#include <unordered_set>
#include <string>

int main(){
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::unordered_set <std::string> mySet;
    char operation;
    std::string word;
    while(true){
        std::cin >> operation;
        if(operation == '#')
            break;

        if(operation == '+'){
            std::cin >> word;
            mySet.insert(word);
        }
        else if(operation == '-'){
            std::cin >> word;
            if(mySet.find(word) != mySet.end()){
                mySet.erase(word);
            }
        }
        else if (operation == '?'){
            std::cin >> word;
            if(mySet.find(word) != mySet.end()){
                std::cout << "YES" << '\n';
            } else{
                std::cout << "NO" << '\n';
            }
        }

    }
    return 0;
}