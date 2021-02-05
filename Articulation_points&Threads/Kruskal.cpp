/*Дан связный неориентированный граф, в котором надо найти остовое дерево минимального веса с помощью алгоритма Крускала. Гарантируется, что ребра будут отсортированы по весу по неубыванию.
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <algorithm>

class DSU {
    using element = int;
    mutable std::vector<element> parents;
    std::vector<size_t> rank;

public:
    DSU() = default;

    DSU(const size_t &numberOfElements) : rank(numberOfElements, 0), parents(numberOfElements) {
        for (int i = 0; i < numberOfElements; ++i) {
            parents[i] = i;
        }
    }

    element MakeSet() {
        parents.push_back(parents.size());
        rank.push_back(0);
        return parents[parents.size() - 1];
    }

    element FindSet(const element &elem) const {
        if (elem == parents[elem]) {
            return elem;
        }
        return parents[elem] = FindSet(parents[elem]);
    }

    void UnionSets(const element &first, const element &second) {
        element firstRoot = FindSet(first);
        element secondRoot = FindSet(second);
        if (firstRoot == secondRoot) {
            return;
        }
        if (rank[firstRoot] < rank[secondRoot]) {
            parents[firstRoot] = secondRoot;
        } else if (rank[firstRoot] > rank[secondRoot]) {
            parents[secondRoot] = firstRoot;
        } else {
            parents[firstRoot] = secondRoot;
            ++rank[secondRoot];
        }
    }

    ~DSU() = default;
};

template<class T>
struct Cmp {
    bool operator()(const T &first, const T &second) {
        return first.weight < second.weight;
    }
};

class Graph {
    struct Vertex {
        int index;

        Vertex() = default;

        explicit Vertex(const int &index) : index(index) {}

        bool operator==(const Vertex &other) const {
            return index == other.index;
        }
    };

    struct Edge {
        Vertex from;
        Vertex to;
        size_t weight;

        explicit Edge(const int &index, const size_t &weight) : to(index), weight(weight) {}

        explicit Edge(const int &from, const int &to, const size_t &weight) : from(from), to(to), weight(weight) {}

    };

    int vertexSize = 0;
    std::vector<std::vector<Edge>> adjacencyList;
    std::vector<Edge> edges;

public:

    explicit Graph(const int &vertexSize) : vertexSize(vertexSize),
                                            adjacencyList(vertexSize, std::vector<Edge>()) {}

    void AddEdge(const int &from, const int &to, const size_t &weight) {
        adjacencyList[from].push_back(Edge(to, weight));
        adjacencyList[to].push_back(Edge(from, weight));
        edges.emplace_back(from, to, weight);
    }

    int KruskalMST() {
        int weightMST = 0;
        DSU dsu(vertexSize);
        Cmp<Edge> cmp;
        std::sort(edges.begin(), edges.end(), cmp);
        for (int i = 0; i < edges.size(); ++i) {
            int firstSetElement = dsu.FindSet(edges[i].from.index);
            int secondSetElement = dsu.FindSet(edges[i].to.index);
            if (firstSetElement != secondSetElement) {
                weightMST += edges[i].weight;
                dsu.UnionSets(firstSetElement, secondSetElement);
            }
        }
        return weightMST;
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    size_t vertexSize = 0;
    size_t edgeSize = 0;
    std::cin >> vertexSize >> edgeSize;
    Graph graph(vertexSize);
    int from, to;
    size_t weight = 0;
    for (int i = 0; i < edgeSize; ++i) {
        std::cin >> from >> to >> weight;
        graph.AddEdge(from - 1, to - 1, weight);
    }
    std::cout << graph.KruskalMST() << '\n';
    return 0;
}