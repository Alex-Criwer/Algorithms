#include <iostream>
#include <vector>
#include <algorithm>

typedef int Vertex;

constexpr int INF = 100000;

bool Relax(const Vertex &from, const Vertex &to, const int &weight,
           std::vector<int> &distances, std::vector<Vertex> &parents) {
    if (distances[to] > distances[from] + weight) {
        distances[to] = distances[from] + weight;
        parents[to] = from;
        return true;
    }
    return false;
}

class Graph {

    struct Edge {
        Vertex from;
        Vertex to;
        int weight;

        explicit Edge(const int &index, const int &weight) : to(index), weight(weight) {}

        explicit Edge(const int &from, const int &to, const int &weight) : from(from), to(to), weight(weight) {}
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

    std::pair<bool, std::vector<Vertex>> Bellman_Ford() {
        std::vector<int> distances(vertexSize, INF);
        std::vector<Vertex> parents(vertexSize, -1);
        std::vector<Vertex> cycle;
        bool contains = false;
        for (int i = 0; i < vertexSize - 1; ++i) {
            for (const Edge &edge : edges) {
                Relax(edge.from, edge.to, edge.weight, distances, parents);
            }
        }
        for (Edge &edge : edges) {
            if (Relax(edge.from, edge.to, edge.weight, distances, parents)) {
                contains = true;
                std::vector<bool> used(vertexSize, false);
                int start = edge.to;
                while (!used[start]) {
                    used[start] = true;
                    start = parents[start];
                }
                cycle.push_back(start);
                Vertex end = parents[start];
                while (end != start) {
                    cycle.push_back(end);
                    end = parents[end];
                }
                cycle.push_back(start);
                std::reverse(cycle.begin(), cycle.end());
                return {contains, cycle};
            }
        }
        return {contains, cycle};
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
            if (weight != INF) {
                graph.AddEdge(i, j, weight);
            }
        }
    }

    std::pair<bool, std::vector<Vertex>> answer = graph.Bellman_Ford();
    if (!answer.first) {
        std::cout << "NO" << '\n';
    } else {
        std::cout << "YES" << '\n';
        std::cout << answer.second.size() << '\n';
        for (const auto &element : answer.second) {
            std::cout << element + 1 << ' ';
        }

    }
    return 0;
}


