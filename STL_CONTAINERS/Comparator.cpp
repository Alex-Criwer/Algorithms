#include <iostream>
#include <algorithm>
#include <vector>

struct Pair {
    int numberOfComplitedTasks;
    int timePenalty;
    int numberCommand;

    Pair() : numberOfComplitedTasks(0), timePenalty(0) {}

    Pair(int numnerOfTasks, int time) : numberOfComplitedTasks(numnerOfTasks), timePenalty(time) {}

    friend std::istream &operator>>(std::istream &is, Pair &pair);
};


int main() {
    int size;
    std::cin >> size;
    std::vector<Pair> myVector;
    Pair pair;
    myVector.reserve(size);
    for (int i = 0; i < size; ++i) {
        std::cin >> pair;
        myVector.push_back(pair);
        myVector.back().numberCommand = i + 1;
    }
    std::sort(myVector.begin(), myVector.end(), [](Pair a, Pair b) {
        return (a.numberOfComplitedTasks > b.numberOfComplitedTasks) ||
               (a.numberOfComplitedTasks == b.numberOfComplitedTasks && a.timePenalty < b.timePenalty) ||
               (a.numberOfComplitedTasks == b.numberOfComplitedTasks && a.timePenalty == b.timePenalty &&
                a.numberCommand < b.numberCommand);

    });

    for (int i = 0; i < size; ++i) {
        std::cout << myVector[i].numberCommand << '\n';
    }

    return 0;
}

std::istream &operator>>(std::istream &is, Pair &pair) {
    is >> pair.numberOfComplitedTasks >> pair.timePenalty;
    return is;
}