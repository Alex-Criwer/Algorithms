/*Реализуйте статическую хеш-таблицу на известном фиксированном наборе ключей с константным поиском в худшем случае.
*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>
#define DEBUG
#include <random>

#ifdef DEBUG
#define ON_DEBUG(expr) expr
#else
#define ON_DEBUG(expr)
#endif

#define BIG_CONSTANT(x) (x)

const size_t maxOptimalCoefficient = 4;
const int kPrimeNumber = 2000000011;
std::mt19937 generator;

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

struct hashFunction {
    size_t seed;

    hashFunction() {
        std::uniform_int_distribution<size_t> distributions(1, kPrimeNumber - 1);
        seed = distributions(generator);
    }

    int operator()(const std::string &value) const {
        return MurmurHash64A(value.c_str(), value.size(), seed);
    }
};


template<class T, class HashFunction>
std::vector<size_t> countDistribution(size_t size, const std::vector<T> &strings, const HashFunction &hash);

bool checkIfThereAreCollisions(const std::vector<size_t> &distribution);

bool fixedSetDistributionIsOptimal(const std::vector<size_t> &distribution);

template<class T, class HashFunction>
class HashTable {
    std::vector<T> buckets_;
    HashFunction hash;
public:
    HashTable() = default;

    std::vector<T> returnBuckets() const {
        return buckets_;
    }

    void initializeHashFunction(const std::vector<T> &strings);

    bool contains(const T &element) const;
};


template<class T, class HashFunction>
class FixedSet {
    std::vector<HashTable<T, HashFunction>> upBusckets;
    HashFunction upHash;
public:
    FixedSet() = default;

    void create(const std::vector<T> &strings);

    bool contains(const T &element) const;
};


int main() {
    std::cin.tie(NULL);
    std::ios_base::sync_with_stdio(false);
    size_t n, k;
    std::vector<std::string> strings;
    std::cin >> n;
    for (int i = 0; i < n; ++i) {
        std::string element;
        std::cin >> element;
        strings.push_back(element);
    }
    FixedSet<std::string, hashFunction> fixedSet;
    fixedSet.create(strings);

    std::cin >> k;
    for (int i = 0; i < k; ++i) {
        std::string element;
        std::cin >> element;
        if (fixedSet.contains(element)) {
            std::cout << "YES\n";
        } else {
            std::cout << "NO\n";
        }
    }

    return 0;
}


bool checkIfThereAreCollisions(const std::vector<size_t> &distribution) {
    for (const auto &element : distribution) {
        if (element > 1) {
            return true;
        }
    }
    return false;
}

template<class T, class HashFunction>
std::vector<size_t> countDistribution(size_t size, const std::vector<T> &strings, const HashFunction &hash) {
    std::vector<size_t> distribution;
    distribution.assign(size, 0);
    for (auto &element : strings) {
        ++distribution[hash(element) % size];
    }
    return distribution;
}


template<class T, class HashFunction>
void HashTable<T, HashFunction>::initializeHashFunction(const std::vector<T> &strings) {
    buckets_.resize(strings.size() * strings.size());
    do {
        hash = hashFunction();
    } while (checkIfThereAreCollisions(countDistribution(buckets_.size(), strings, hash)));

    for (const auto &string: strings) {
        buckets_[hash(string) % buckets_.size()] = string;
    }
}

template<class T, class HashFunction>
bool HashTable<T, HashFunction>::contains(const T &element) const {
    if (buckets_[hash(element) % buckets_.size()] == element) {
        return true;
    }
    return false;
}

template<class T, class HashFunction>
void FixedSet<T, HashFunction>::create(const std::vector<T> &strings) {
    upBusckets.resize(strings.size());

    do {
        upHash = hashFunction();
    } while (!fixedSetDistributionIsOptimal(countDistribution(strings.size(), strings, upHash)));

    std::vector<std::vector<T>> buckets(strings.size());
    for (auto &element: strings) {
        buckets[upHash(element) % strings.size()].push_back(element);
    }

    for (int i = 0; i < strings.size(); ++i) {
        upBusckets[i].initializeHashFunction(buckets[i]);
    }

}

template<class T, class HashFunction>
bool FixedSet<T, HashFunction>::contains(const T &element) const {
    size_t buckets_number = upHash(element) % upBusckets.size();
    if (!upBusckets[buckets_number].returnBuckets().empty()) {
        return upBusckets[buckets_number].contains(element);
    }
    return false;
}

bool fixedSetDistributionIsOptimal(const std::vector<size_t> &distribution) {
    size_t sumOfSqueres = 0;
    for (auto element : distribution) {
        sumOfSqueres += element * element;
    }
    return sumOfSqueres <= maxOptimalCoefficient * distribution.size();
}


