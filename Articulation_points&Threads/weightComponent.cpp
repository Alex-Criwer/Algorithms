/*В неориентированный взвешанный граф добавляют ребра. Напишите программу, которая в некоторые моменты находит сумму весов ребер в компоненте связности.

*/
#include <iostream>
#include <vector>
#include <algorithm>

class DSU {
    using element = int;
    std::vector<element> parents;
    std::vector<size_t> rank;
    std::vector<size_t> weights;
public:
    DSU() = default;

    DSU(const int &numberOfElements) : rank(numberOfElements, 0),
                                       weights(numberOfElements, 0),
                                       parents(numberOfElements) {
        for (int i = 0; i < numberOfElements; ++i) {
            parents[i] = i;
        }
    }

    element MakeSet() {
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

    void UnionSets(const element &firstSetElement, const element &secondSetElement, const size_t &weight) {
        element firstRoot = FindSet(firstSetElement);
        element secondRoot = FindSet(secondSetElement);
        if (firstRoot != secondRoot) {
            if (rank[firstRoot] < rank[secondRoot]) {
                parents[firstRoot] = secondRoot;
                weights[secondRoot] += weight + weights[firstRoot];
            } else if (rank[firstRoot] > rank[secondRoot]) {
                parents[secondRoot] = firstRoot;
                weights[firstRoot] += weight + weights[secondRoot];
            } else {
                parents[firstRoot] = secondRoot;
                weights[secondRoot] += weight + weights[firstRoot];
                ++rank[secondRoot];
            }
        } else {
            weights[firstRoot] += weight;
        }
    }

    size_t knowWeight(const element &setElement) {
        element root = FindSet(setElement);
        return weights[root];
    }

    ~DSU() = default;
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    size_t vertexSize = 0;
    size_t numberOfOperations = 0;
    size_t operation, from, to, weight, element;
    std::cin >> vertexSize >> numberOfOperations;
    DSU dsu(vertexSize);
    for (int i = 0; i < numberOfOperations; ++i) {
        std::cin >> operation;
        if (operation == 1) {
            std::cin >> from >> to >> weight;
            dsu.UnionSets(from - 1, to - 1, weight);
        } else if (operation == 2) {
            std::cin >> element;
            std::cout << dsu.knowWeight(element - 1) << '\n';
        }
    }
    return 0;
}
