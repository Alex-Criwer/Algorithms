#include <iostream>
#include <queue>
#include <algorithm>
#include <vector>


int main(){
    int size, number;
    double sum = 0;
    std::cin >> size;
    std::priority_queue<int,std::vector<int>,std::greater<int>> calculator;
    for (int i = 0; i < size; ++i) {
        std::cin >> number;
        calculator.push(number);
    }
   while(calculator.size() >=  2){
       int el1,el2;
       el1 = calculator.top();
       calculator.pop();
       el2 = calculator.top();
       calculator.pop();
       sum += (el1 + el2) * 0.05;
       calculator.push(el1+el2);
   }
   std:: cout << sum;

    return 0;
}

