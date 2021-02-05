#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <algorithm>
#include <unordered_set>
#include <cstring>

#define BIG_CONSTANT(x) (x)

uint64_t MurmurHash64A(const char *key, int len, uint64_t seed) {
    const uint64_t m = BIG_CONSTANT(0xc6a4a7935bd1e995);
    const int r = 47;

    uint64_t h = seed ^(len * m);

    const uint64_t *data = (const uint64_t *) key;
    const uint64_t *end = data + (len / 8);

    while (data != end) {
        uint64_t k = *data++;

        k *= m;
        k ^= k >> r;
        k *= m;

        h ^= k;
        h *= m;
    }

    const unsigned char *data2 = (const unsigned char *) data;

    switch (len & 7) {
        case 7:
            h ^= uint64_t(data2[6]) << 48;
        case 6:
            h ^= uint64_t(data2[5]) << 40;
        case 5:
            h ^= uint64_t(data2[4]) << 32;
        case 4:
            h ^= uint64_t(data2[3]) << 24;
        case 3:
            h ^= uint64_t(data2[2]) << 16;
        case 2:
            h ^= uint64_t(data2[1]) << 8;
        case 1:
            h ^= uint64_t(data2[0]);
            h *= m;
    };

    h ^= h >> r;
    h *= m;
    h ^= h >> r;

    return h;
}

template<uint64_t seed>
struct HashFunction {
    uint64_t operator()(const std::string &str) const {
        return MurmurHash64A(str.c_str(), str.size(), seed);
    }
};

template<class T, class Hash>
class universalStringHash {

    std::unordered_set<T, Hash> universalFamily;

public:

    void operation(const char &request, const T &str);
};

template<class T, class Hash>
void universalStringHash<T, Hash>::operation(const char &request, const T &str) {
    if (request == '+' && universalFamily.find(str) == universalFamily.end()) {
        universalFamily.insert(str);
    } else if (request == '-' && universalFamily.find(str) != universalFamily.end()) {
        universalFamily.erase(str);
    } else if (request == '?') {
        if (universalFamily.find(str) != universalFamily.end()) {
            std::cout << "YES" << '\n';
        } else {
            std::cout << "NO" << '\n';
        }
    }
}

int main() {
    universalStringHash<std::string, HashFunction<5>> hashTable;
    char request;
    std::string str = "";
    while ((request = getchar()) != '#') {
        std::cin >> str;
        hashTable.operation(request, str);
        std::cin.get();
    }
    return 0;
}