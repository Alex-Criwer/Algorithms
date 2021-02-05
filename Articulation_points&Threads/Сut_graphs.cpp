#include <iostream>
#include <vector>
#include <algorithm>
/*Дан неориентированный граф. Над ним в заданном порядке производят операции следующих двух типов:

cut — разрезать граф, то есть удалить из него ребро;

ask — проверить, лежат ли две вершины графа в одной компоненте связности.

Известно, что после выполнения всех операций типа cut рёбер в графе не осталось. Найдите результат выполнения каждой из операций типа ask.*/

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

        explicit Edge(const int &index) : to(index) {}

        explicit Edge(const int &from, const int &to) : from(from), to(to) {}

        bool operator<(const Edge &other) const {
            return std::pair<int, int>(from.index, to.index) < std::pair<int, int>(other.from.index, other.to.index);
        }
    };

    int vertexSize = 0;
    std::vector<std::vector<Edge>> adjacencyList;
    size_t counter = 0;

public:

    explicit Graph(const int &vertexSize) : vertexSize(vertexSize),
                                            adjacencyList(vertexSize, std::vector<Edge>()) {}

    void AddEdge(const int &from, const int &to) {
        adjacencyList[from].push_back(Edge(to));
        adjacencyList[to].push_back(Edge(from));
    }
};

struct Operation {
    std::string operation;
    size_t firstElement;
    size_t secondElement;
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    size_t vertexSize = 0;
    size_t edgeSize = 0;
    size_t numberOfOperations;
    std::cin >> vertexSize >> edgeSize >> numberOfOperations;
    Graph graph(vertexSize);
    for (int i = 0; i < edgeSize; ++i) {
        int from, to;
        std::cin >> from >> to;
        graph.AddEdge(from - 1, to - 1);
    }
    std::vector<Operation> operations;
    std::vector<std::string> answer;
    std::string str;
    size_t firstElement, secondElement;
    for (int i = 0; i < numberOfOperations; ++i) {
        std::cin >> str >> firstElement >> secondElement;
        operations.push_back({str, firstElement - 1, secondElement - 1});
    }
    DSU dsu(vertexSize);
    for (int i = numberOfOperations - 1; i >= 0; --i) {
        firstElement = operations[i].firstElement;
        secondElement = operations[i].secondElement;
        str = operations[i].operation;
        if (str == "ask") {
            if (dsu.FindSet(firstElement) == dsu.FindSet(secondElement)) {
                answer.emplace_back("YES");
            } else {
                answer.emplace_back("NO");
            }
        } else if (str == "cut") {
            dsu.UnionSets(firstElement, secondElement);
        }
    }

    for (int i = answer.size() - 1; i >= 0; --i) {
        std::cout << answer[i] << '\n';
    }
    return 0;
}