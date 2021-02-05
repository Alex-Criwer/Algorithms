#include <iostream>
#include <vector>
#include <queue>
#include <optional>
#include <limits>
#include <map>


const int INTMAX = std::numeric_limits<int>::max();
const int MAX_WEIGHT = 10;

struct Pair {
    int from, to;

    Pair() = default;

    explicit Pair(const int &from, const int &to) : from(from), to(to) {}

    bool operator<(const Pair &other) const {
        return std::pair<int, int>(from, to) < std::pair<int, int>(other.from, other.to);
    }
};

class Graph {
    struct Edge {
        size_t index;

        Edge() = default;

        Edge(const size_t &index) : index(index) {}
    };

    size_t vertexSize = 0;
    size_t max = 0;
    std::vector<bool> used;
    std::vector<std::vector<Edge>> adjList;
    std::vector<int> distances;
    std::map<Pair, int> weights;
public:

    Graph(const size_t &vertexSize) : vertexSize(vertexSize),
                                      max(MAX_WEIGHT * (vertexSize - 1) + 1),
                                      used(vertexSize, false),
                                      adjList(vertexSize, std::vector<Edge>()),
                                      distances(vertexSize, INTMAX) {}

    void AddEdge(const int &from, const int &to, const int &weight) {
        adjList[from - 1].push_back(Edge(to - 1));
        weights[Pair(from - 1, to - 1)] = weight;
    }

    void Reset() {
        used.assign(vertexSize, false);
        distances.assign(vertexSize, INTMAX);
    }

    void Bfs(const size_t &index) {
        size_t start = index - 1;
        Reset();
        used[start] = true;
        distances[start] = 0;
        std::vector<std::queue<int>> pathToLength;
        pathToLength.resize(max);
        pathToLength[0].push(start);
        for (int i = 0; i < max; ++i) {
            while (!pathToLength[i].empty()) {
                int vertex = pathToLength[i].front();
                pathToLength[i].pop();
                if (distances[vertex] != i) {
                    continue;
                }
                for (auto neighbour : adjList[vertex]) {
                    if (distances[neighbour.index] > i + weights[Pair(vertex, neighbour.index)]) {
                        distances[neighbour.index] = i + weights[Pair(vertex, neighbour.index)];
                        pathToLength[i + weights[Pair(vertex, neighbour.index)]].push(neighbour.index);
                    }
                }
            }
        }
    }

    void PrintAnswer(const int &end) {
        if (distances[end - 1] == INTMAX) {
            std::cout << -1 << '\n';
            return;
        }
        std::cout << distances[end - 1] << '\n';
    }

    void print() {
        for (auto element : weights) {
            std::cout << "from " << element.first.from + 1 << " to " << element.first.to + 1 << " weight "
                      << element.second << '\n';
        }
    }


};


int main() {
    std::cin.tie(0);
    std::ios_base::sync_with_stdio(false);
    size_t vertexSize = 0;
    size_t edgeSize = 0;
    size_t start = 0;
    size_t end = 0;
    std::cin >> vertexSize >> edgeSize;
    std::cin >> start >> end;
    Graph graph(vertexSize);
    for (int i = 0; i < edgeSize; ++i) {
        int from, to, weight;
        std::cin >> from >> to >> weight;
        graph.AddEdge(from, to, weight);
    }
    graph.Bfs(start);
    graph.PrintAnswer(end);
    return 0;
}