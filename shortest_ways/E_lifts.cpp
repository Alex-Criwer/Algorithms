#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#pragma GCC optimize("-fgcse")
#pragma GCC optimize("-fgcse-lm")
#pragma GCC optimize("-fipa-sra")
#pragma GCC optimize("no-stack-protecbr")
#pragma GCC optimize("unroll-loops")

#include <iostream>
#include <vector>
#include <limits>
#include <deque>
#include <set>

typedef int Vertex;

constexpr int INF = std::numeric_limits<int>::max();

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
    }

    void AddVertex(const int &diff) {
        vertexSize += diff;
        adjacencyList.resize(vertexSize);
    }

    size_t getNUmberOfVertexes() {
        return vertexSize;
    }

    int Dijkstra(const Vertex &start, const Vertex &end) {
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
        return distances[end];
    }

};


int main() {
    int numberOfFloors, upCost, downCost, toPutCost, toOutCost, numberOfLifts;
    std::cin >> numberOfFloors >> upCost >> downCost >> toPutCost >> toOutCost >> numberOfLifts;

    Graph graph(numberOfLifts + numberOfFloors);

    size_t number;
    int floor = 0;
    int difference = 0;
    int maxNumberOfFloors = numberOfFloors;
    for (int index = 0; index < numberOfLifts; ++index) {
        std::cin >> number;
        for (int i = 0; i < number; ++i) {
            std::cin >> floor;
            if (floor > maxNumberOfFloors) {
                difference = floor - maxNumberOfFloors;
                graph.AddVertex(difference);
                maxNumberOfFloors += difference;
            }
            graph.AddEdge(floor + numberOfLifts - 1, index, toPutCost);
            graph.AddEdge(index, floor + numberOfLifts - 1, toOutCost);
        }
    }

    for (int i = numberOfLifts; i < graph.getNUmberOfVertexes() - 1; ++i) {
        graph.AddEdge(i, i + 1, upCost);
        graph.AddEdge(i + 1, i, downCost);
    }

    Vertex start = numberOfLifts, end = numberOfFloors + numberOfLifts - 1;
    std::cout << graph.Dijkstra(start, end) << '\n';
    return 0;
}




