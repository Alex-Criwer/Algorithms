#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include <set>

typedef size_t Vertex;

int INF = std::numeric_limits<int>::max();

constexpr int NO_EDGE = -1;

class Cmp {
public:
    bool operator()(const std::pair<int, int> &lhs, const std::pair<int, int> &rhs) const {
        if (lhs.first != rhs.first) {
            return lhs.first < rhs.first;
        }
        return lhs.second < rhs.second;
    }
};

bool Relax(const Vertex &from, const Vertex &to, const size_t &weight, std::vector<int> &distances) {
    if (distances[to] > distances[from] + weight) {
        distances[to] = distances[from] + weight;
        return true;
    }
    return false;
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
    std::vector<std::vector<Edge>> adjacencyList;

public:

    explicit Graph(const int &vertexSize) : vertexSize(vertexSize), adjacencyList(vertexSize, std::vector<Edge>()) {}

    void AddEdge(const size_t &from, const size_t &to, const int &weight) {
        edges.push_back(Edge(from, to, weight));
        adjacencyList[from].emplace_back(from, to, weight);
        ++edgeSize;
    }

    std::vector<int> Dijkstra(const Vertex &start) {
        std::vector<int> distances(vertexSize, INF);
        std::vector<bool> used(vertexSize, false);
        std::vector<Vertex> parents(vertexSize, -1);
        std::set<std::pair<int, int>, Cmp> queueDijkstra;
        distances[start] = 0;
        queueDijkstra.insert({distances[start], start});
        for (int i = 0; i < vertexSize && !queueDijkstra.empty(); ++i) {
            auto pair = *queueDijkstra.begin();
            queueDijkstra.erase(pair);
            Vertex minVertex = pair.second;
            while (used[minVertex] && !queueDijkstra.empty()) {
                auto pair = *queueDijkstra.begin();
                queueDijkstra.erase(pair);
                minVertex = pair.second;
            }
            used[minVertex] = true;
            for (const auto &neighbour : adjacencyList[minVertex]) {
                if (!used[neighbour.to] && (distances[neighbour.to] > distances[minVertex] + neighbour.weight ||
                                            distances[neighbour.to] == INF)) {
                    distances[neighbour.to] = distances[minVertex] + neighbour.weight;
                    parents[neighbour.to] = minVertex;
                    queueDijkstra.insert({distances[neighbour.to], neighbour.to});
                }
            }
        }
        return distances;
    }

    std::pair<bool, std::vector<int>> Bellman_Ford() {
        std::vector<int> distances(vertexSize, 0);
        bool contains = false;
        for (int i = 0; i < vertexSize - 1; ++i) {
            for (const Edge &edge : edges) {
                Relax(edge.from, edge.to, edge.weight, distances);
            }
        }
        for (Edge &edge : edges) {
            if (Relax(edge.from, edge.to, edge.weight, distances)) {
                contains = true;
            }
        }
        return {contains, distances};
    }


    std::vector<std::vector<int>> Johnson() {
        std::pair<bool, std::vector<int>> answer = Bellman_Ford();
        bool isNegativeCycle = answer.first;
        std::vector<int> potentials = answer.second;
        if (isNegativeCycle) {
            return {};
        }

        for (auto &edgeList : adjacencyList) {
            for (auto &edge : edgeList) {
                edge.weight += potentials[edge.from] - potentials[edge.to];
            }
        }
        std::vector<std::vector<int>> distances(vertexSize);
        for (int i = 0; i < vertexSize; ++i) {
            distances[i] = Dijkstra(i);
        }
        return distances;
    }


};


int main() {
    size_t vertexSize = 0;
    std::cin >> vertexSize;
    Graph graph(vertexSize);
    int weight = 0;
    for (int i = 0; i < vertexSize; ++i) {
        for (int j = 0; j < vertexSize; ++j) {
            std::cin >> weight;
            if (weight != NO_EDGE && i != j) {
                graph.AddEdge(i, j, weight);
            }
        }
    }
    std::vector<std::vector<int>> distances = graph.Johnson();
    int maxDistance = 0;
    for (int i = 0; i < vertexSize; ++i) {
        for (int j = 0; j < vertexSize; ++j) {
            if (distances[i][j] != INF) {
                maxDistance = std::max(maxDistance, distances[i][j]);
            }
        }
    }
    std::cout << maxDistance << '\n';
    return 0;
}