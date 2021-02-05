#include <iostream>
#include <vector>
#include <limits>
#include <deque>
#include <set>

typedef int Vertex;

constexpr int INF = std::numeric_limits<int>::max();

constexpr int MAX_DISTANCE = 2009000999;

class Cmp {
public:
    bool operator()(const std::pair<int, int> &lhs, const std::pair<int, int> &rhs) const {
        if (lhs.first != rhs.first) {
            return lhs.first < rhs.first;
        }
        return lhs.second < rhs.second;
    }
};

class Graph {

    struct Edge {
        Vertex to;
        int weight;

        explicit Edge(const int &index, const int &weight) : to(index), weight(weight) {}
    };

    size_t vertexSize = 0;
    std::vector<std::vector<Edge>> adjacencyList;

public:

    explicit Graph(const int &vertexSize) : vertexSize(vertexSize),
                                            adjacencyList(vertexSize, std::vector<Edge>()) {}

    void AddEdge(const int &from, const int &to, const int &weight) {
        adjacencyList[from].push_back(Edge(to, weight));
        adjacencyList[to].push_back(Edge(from, weight));
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
                if (!used[neighbour.to] && distances[neighbour.to] > distances[minVertex] + neighbour.weight) {
                    distances[neighbour.to] = distances[minVertex] + neighbour.weight;
                    parents[neighbour.to] = minVertex;
                    queueDijkstra.insert({distances[neighbour.to], neighbour.to});
                }
            }
        }
        return distances;
    }

};


int main() {
    size_t numberOfBlocks = 0;
    std::cin >> numberOfBlocks;
    for (int index = 0; index < numberOfBlocks; ++index) {
        size_t vertexSize = 0, edgeSize = 0;
        std::cin >> vertexSize >> edgeSize;
        Graph graph(vertexSize);
        Vertex from = 0, to = 0;
        int weight = 0;
        for (int i = 0; i < edgeSize; ++i) {
            std::cin >> from >> to >> weight;
            graph.AddEdge(from, to, weight);
        }
        Vertex start;
        std::cin >> start;
        std::vector<int> distances = graph.Dijkstra(start);
        for (const auto &element : distances) {
            if (element == INF) {
                std::cout << MAX_DISTANCE << " ";
                continue;
            }
            std::cout << element << " ";
        }
        std::cout << '\n';
    }
    return 0;
}




