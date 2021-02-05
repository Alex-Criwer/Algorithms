#include <iostream>
#include <set>

struct Set{
    std::set<int> mySet;
    void add(int number);
    int next(int number);

};

void Set::add(int number) {
    mySet.insert(number);
}

int Set::next(int number) {

    if(mySet.find(*mySet.lower_bound(number)) != mySet.end()){
        return *mySet.lower_bound(number);
    } else{
        return (-1);
    }

}

int main(){
    Set myWorkingSet;
    char operation, prevOperation = '!' ;
    int number, prevNumber = 0;
    int numberOfOperations;
    std::cin >> numberOfOperations;
    for (int i = 0; i < numberOfOperations; ++i) {
        std::cin >> operation ;
        std:: cin >> number;
        if(operation == '+' && prevOperation != '?'){
            myWorkingSet.add(number);
        } else if (operation == '?'){
           prevNumber =  myWorkingSet.next(number);
           std::cout << prevNumber << '\n';
        } else if (operation == '+' && prevOperation == '?'){
            myWorkingSet.add((number + prevNumber) % 1000000000);
        }

        prevOperation = operation;
    }
    return 0;
}
