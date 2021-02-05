#include <iostream>
#include <vector>
#include <deque>
#include <optional>
#include <limits>

const int INTMAX = std::numeric_limits<int>::max();

class Graph {

    struct Edge {
        size_t index;
        size_t weight;

        explicit Edge(const size_t &index, const size_t &weight) : index(index), weight(weight) {}
    };

    size_t vertexSize;
    std::vector<std::vector<Edge>> adjacencyList;
    std::vector<int> distances;

public:

    explicit Graph(const size_t &vertexSize) : vertexSize(vertexSize),
                                               adjacencyList(vertexSize, std::vector<Edge>()),
                                               distances(vertexSize, INTMAX) {}

    void Reset() {
        distances.assign(vertexSize, INTMAX);
    }

    void AddEdge(const int &from, const int &to) {
        adjacencyList[from].push_back(Edge(to, 0));
        adjacencyList[to].push_back(Edge(from, 1));
    }

    std::vector<int> Bfs(const int &start) {
        Reset();
        distances[start] = 0;
        std::deque<size_t> bfsQueue;
        bfsQueue.push_back(start);

        while (!bfsQueue.empty()) {
            size_t vertex = bfsQueue.front();
            bfsQueue.pop_front();

            for (const auto &neighbour: adjacencyList[vertex]) {
                if (distances[neighbour.index] > distances[vertex] + neighbour.weight) {
                    distances[neighbour.index] = distances[vertex] + neighbour.weight;
                    if(neighbour.weight == 0) {
                        bfsQueue.push_front(neighbour.index);
                    }  else {
                        bfsQueue.push_back(neighbour.index);
                    }
                }
            }

        }
        return distances;
    }


};


int main() {
    size_t vertexSize = 0;
    size_t edgeSize = 0;
    size_t start = 0;
    size_t end = 0;
    size_t numberOfQuestions = 0;
    std::cin >> vertexSize >> edgeSize;
    Graph graph(vertexSize);
    for (int i = 0; i < edgeSize; ++i) {
        int from, to;
        std::cin >> from >> to;
        graph.AddEdge(from - 1, to - 1);
    }
    std::cin >> numberOfQuestions;
    for (int i = 0; i < numberOfQuestions; ++i) {
        std::cin >> start >> end;
        std::vector<int> result = graph.Bfs(start - 1);
        if (result[end - 1] == INTMAX) {
            std::cout << -1 << '\n';
        } else {
            std::cout << result[end - 1] << '\n';
        }
    }

    return 0;
}