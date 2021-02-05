#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include <queue>
#include <unordered_set>

typedef size_t Vertex;

size_t INF = std::numeric_limits<size_t>::max();

size_t MAX_DISTANCE = 30000;

bool Relax(const Vertex &from, const Vertex &to, const size_t &weight, std::vector<int> &distances) {
    if (distances[to] > distances[from] + weight && distances[from] != INF) {
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
    std::vector<std::vector<Edge>> adjacencyList;

public:

    explicit Graph(const int &vertexSize) : vertexSize(vertexSize), adjacencyList(vertexSize, std::vector<Edge>()) {}

    void AddEdge(const size_t &from, const size_t &to, const int &weight) {
        adjacencyList[from].emplace_back(from, to, weight);
        ++edgeSize;
    }

    std::vector<int> Bellman_Ford(const Vertex &start) {
        std::vector<int> distances(vertexSize, INF);
        std::unordered_set<int> myQueue;
        distances[start] = 0;
        myQueue.insert(start);
        Vertex current;
        while (!myQueue.empty()) {
            current = *myQueue.begin();
            myQueue.erase(current);
            for (const auto &neighbour : adjacencyList[current]) {
                if (Relax(neighbour.from, neighbour.to, neighbour.weight, distances)) {
                    if (myQueue.find(neighbour.to) == myQueue.end()) {
                        myQueue.insert(neighbour.to);
                    }
                }
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
    Vertex start = 0;
    std::vector<int> distances = graph.Bellman_Ford(start);
    for (const auto &distance : distances) {
        std::cout << distance << " ";
    }
    return 0;
}


