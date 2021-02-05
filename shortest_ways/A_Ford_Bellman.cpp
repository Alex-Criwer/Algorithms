#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

typedef size_t Vertex;

size_t INF = std::numeric_limits<size_t>::max();

size_t MAX_DISTANCE = 30000;

void Relax(const Vertex &from, const Vertex &to, const size_t &weight, std::vector<int> &distances) {
    if (distances[to] > distances[from] + weight && distances[from] != INF) {
        distances[to] = distances[from] + weight;
    }
}

class Graph {

    struct Edge {
        Vertex from;
        Vertex to;
        int weight;

        explicit Edge(const size_t &index, const int &weight) : to(index), weight(weight) {}

        explicit Edge(const size_t &from, const size_t &to, const int &weight) : from(from), to(to), weight(weight) {}
    };

    size_t vertexSize = 0;
    size_t edgeSize = 0;
    std::vector<Edge> edges;

public:

    explicit Graph(const int &vertexSize) : vertexSize(vertexSize) {}

    void AddEdge(const size_t &from, const size_t &to, const int &weight) {
        edges.push_back(Edge(from, to, weight));
        ++edgeSize;
    }

    std::vector<int> Bellman_Ford(const Vertex &start) {
        std::vector<int> distances(vertexSize, INF);
        distances[start] = 0;
        for (int i = 0; i < vertexSize - 1; ++i) {
            for (const Edge &edge : edges) {
                Relax(edge.from, edge.to, edge.weight, distances);
            }
        }
        for (auto &elem : distances) {
            if (elem == INF) {
                elem = MAX_DISTANCE;
            }
        }
        return distances;
    }


};


int main() {
    size_t vertexSize = 0, edgeSize = 0;
    std::cin >> vertexSize >> edgeSize;
    Graph graph(vertexSize);
    Vertex from = 0, to = 0;
    int weight = 0;
    for (int i = 0; i < edgeSize; ++i) {
        std::cin >> from >> to >> weight;
        graph.AddEdge(from - 1, to - 1, weight);
    }
    Vertex start = 3;
    std::vector<int> distances = graph.Bellman_Ford(start);
    for (const auto &distance : distances) {
        std::cout << distance << " ";
    }
    return 0;
}

/*4 7
1 2 7
2 3 -2
3 2 1
1 3 3
4 1 0
4 2 0
4 3 0*/