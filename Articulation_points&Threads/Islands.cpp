#include <iostream>
#include <vector>
#include <algorithm>

/*Одно разбросанное на островах Океании государство решило создать
 * сеть автомобильных дорог (вернее, мостов). По каждому мосту можно
 * перемещаться в обе стороны. Был разработан план очередности
 * строительства мостов и известно, что после постройки всех мостов
 * можно будет проехать по ним с каждого острова на каждый
 * (возможно, через некоторые промежуточные острова).
Однако, этот момент может наступить до того, как будут построены все мосты.
 Ваша задача состоит такое минимальное количество мостов, после постройки
 которых (в порядке строительства по плану) можно будет попасть с любого острова на любой другой.*/

class DSU {
    using element = int;
    std::vector<element> parents;
    std::vector<size_t> rank;
    size_t numberOfDiffSets;
public:
    DSU() = default;

    DSU(const int &numberOfElements) : rank(numberOfElements, 0), parents(numberOfElements),
                                       numberOfDiffSets(numberOfElements) {
        for (int i = 0; i < numberOfElements; ++i) {
            parents[i] = i;
        }
    }

    element MakeSet() {
        ++numberOfDiffSets;
        parents.push_back(parents.size());
        rank.push_back(0);
        return parents[parents.size() - 1];
    }

    element FindSet(const element &elem) {
        if (elem == parents[elem]) {
            return elem;
        }
        return parents[elem] = FindSet(parents[elem]);
    }

    void UnionSets(const element &firstSetElement, const element &secondSetElement) {
        element firstRoot = FindSet(firstSetElement);
        element secondRoot = FindSet(secondSetElement);
        if (firstRoot != secondRoot) {
            if (rank[firstRoot] < rank[secondRoot]) {
                parents[firstRoot] = secondRoot;
            } else if (rank[firstRoot] > rank[secondRoot]) {
                parents[secondRoot] = firstRoot;
            } else {
                parents[firstRoot] = secondRoot;
                ++rank[secondRoot];
            }
            --numberOfDiffSets;
        }
    }

    size_t getNumberOfDifferentSets() const {
        return numberOfDiffSets;
    }

    ~DSU() = default;
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    size_t vertexSize = 0;
    size_t numberOfBridges = 0;
    size_t counter = 0;
    std::cin >> vertexSize >> numberOfBridges;
    DSU dsu(vertexSize);
    for (int i = 0; i < numberOfBridges; ++i) {
        int from, to;
        std::cin >> from >> to;
        if (dsu.getNumberOfDifferentSets() == 1) {
            break;
        }
        dsu.UnionSets(from, to);
        ++counter;
    }
    std::cout << counter;
    return 0;
}
