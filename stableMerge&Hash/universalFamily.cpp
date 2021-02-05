#include <iostream>
#include <vector>
#include <unordered_set>

const int primeNUmber = 6679881;

class Hash {
    int a;
    int b;
public:
    Hash() {
        a = std::rand();
        b = std::rand();
    }

    int operator()(const int &value) const {
        return (a * value + b) % primeNUmber;
    }
};


template<class T, class Hash>
class universalFamilyHash {

    std::unordered_set<T, Hash> universalFamily;

public:

    void Operation(const char &request, const T &number);
};

template<class T, class Hash>
void universalFamilyHash<T, Hash>::Operation(const char &request, const T &number) {

    if (request == '+' && universalFamily.find(number) == universalFamily.end()) {
        universalFamily.insert(number);
    } else if (request == '-' && universalFamily.find(number) != universalFamily.end()) {
        universalFamily.erase(number);
    } else if (request == '?') {
        if (universalFamily.find(number) != universalFamily.end()) {
            std::cout << "YES" << '\n';
        } else {
            std::cout << "NO" << '\n';
        }
    }
}

int main() {
    size_t numberOfRequest = 0;
    universalFamilyHash<int, Hash> myFamily;
    char request;
    int number = 0;
    std::cin >> numberOfRequest;
    for (int i = 0; i < numberOfRequest; ++i) {
        std::cin >> request >> number;
        myFamily.Operation(request, number);

    }
    return 0;
}