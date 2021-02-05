#include <iostream>
#include <vector>
#include <queue>
#include <optional>
#include <limits>

const int INTMAX = std::numeric_limits<int>::max();

class Graph {

    struct Vertex {
        int index;

        Vertex() = default;

        Vertex(const int &index) : index(index) {}
    };

    struct Edge {
        Vertex to;

        explicit Edge(const int &index) : to(index) {}
    };

    size_t vertexSize;
    std::vector<std::vector<Edge>> adjacencyList;
    std::vector<Vertex> parents;
    std::vector<bool> used;
    std::vector<int> distances;

public:

    explicit Graph(const size_t &vertexSize) : vertexSize(vertexSize),
                                               adjacencyList(vertexSize, std::vector<Edge>()),
                                               parents(vertexSize, Vertex(-1)),
                                               distances(vertexSize, INTMAX),
                                               used(vertexSize, false) {}

    void Reset() {
        used.assign(vertexSize, false);
        parents.assign(vertexSize, Vertex(-1));
        distances.assign(vertexSize, INTMAX);
    }

    void AddEdge(const int &from, const int &to) {
        adjacencyList[from].push_back(Edge(to));
        adjacencyList[to].push_back(Edge(from));
    }

    std::vector<int> Bfs(const int &start) {
        Reset();
        used[start] = true;
        parents[start] = Vertex(-1);
        distances[start] = 0;
        std::queue<size_t> bfsQueue;
        bfsQueue.push(start);
        while (!bfsQueue.empty()) {
            size_t vertex = bfsQueue.front();
            bfsQueue.pop();
            for (const auto &neighbour: adjacencyList[vertex]) {
                if (!used[neighbour.to.index]) {
                    parents[neighbour.to.index] = Vertex(vertex);
                    distances[neighbour.to.index] = distances[vertex] + 1;
                    used[neighbour.to.index] = true;
                    bfsQueue.push(neighbour.to.index);
                }
            }
        }
        return distances;
    }

    void PrintPath(const size_t &vertex) {
        std::cout << distances[vertex] << '\n';
        std::vector<int> result;
        size_t current = vertex;
        while (parents[current].index != -1) {
            result.push_back(current);
            current = parents[current].index;
        }
        result.push_back(current);
        for (auto it = result.rbegin(); it != result.rend(); it = std::next(it)) {
            std::cout << *it + 1 << " ";
        }
        std::cout << '\n';
    }

};


int main() {
    size_t vertexSize = 0;
    size_t edgeSize = 0;
    size_t start = 0;
    size_t end = 0;
    std::cin >> vertexSize >> edgeSize;
    std::cin >> start >> end;
    Graph graph(vertexSize);
    for (int i = 0; i < edgeSize; ++i) {
        int from, to;
        std::cin >> from >> to;
        graph.AddEdge(from - 1, to - 1);
    }
    std::vector<int> result = graph.Bfs(start - 1);
    if (result[end - 1] == INTMAX) {
        std::cout << -1 << '\n';
    } else {
        graph.PrintPath(end - 1);
    }
    return 0;
}
