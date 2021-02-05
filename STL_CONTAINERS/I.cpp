#include <iostream>
#include <map>
#include <string>
#include <algorithm>
#include <functional>
#include <set>

struct Default{
    int i = 0;
    Default& operator ++(){
        ++i;
    }
    friend std::ostream& operator<<(std::ostream& os, Default& def);
};

std::ostream& operator<<(std::ostream &os, Default &def) {
    std::cout << def.i;
    return os;
}

int main(){
    std::map<std::string, Default> myMap;
    std::string str;
    while((std::cin >> str)){
        //if(str == "0"){
        //    break;
        //}
        if(str == "\n"){
            continue;
        }
        ++myMap[str] ;
    }

    typedef std::function<bool(std::pair<std::string, Default>, std::pair<std::string, Default>)> Comparator;

    Comparator compFunctor = [](std::pair<std::string,Default>  a, std::pair<std::string,Default> b ){
        return (a.second.i > b.second.i) ||(a.second.i == b.second.i && a.first < b.first);
    };
    std::set<std::pair<std::string, Default>, Comparator> setOfWords( myMap.begin(), myMap.end(), compFunctor);

    for(auto it = setOfWords.begin(); it != setOfWords.end(); ++it){
        std:: cout  << it->first << '\n';
    }
    return 0;
}
