#include <iostream>
#include <vector>
#include <string>
#include <deque>

class Graph {

    struct Vertex {
        int index;
        std::string color = "WHITE";

        Vertex() = default;

        explicit Vertex(const int &index) : index(index) {}

        explicit Vertex(const size_t &index, const std::string &str) : index(index), color(str) {}
    };

    struct Edge {
        Vertex to;

        Edge() = default;

        explicit Edge(const int &index) : to(index) {}

        explicit Edge(const size_t &index, const std::string &str) : to(index, str) {}
    };

    std::deque<int> result;
    size_t vertexSize;
    std::vector<std::vector<Edge>> adjacencyList;
    std::vector<std::string> colors;
    bool isCycle = false;

public:

    explicit Graph(const size_t &vertexSize) : vertexSize(vertexSize),
                                               adjacencyList(vertexSize, std::vector<Edge>()),
                                               colors(vertexSize, "WHITE") {}


    void AddEdge(const int &from, const int &to) {
        adjacencyList[from].push_back(Edge(to));
    }

    void TopSort() {
        for (int i = 0; i < adjacencyList.size(); ++i) {
            if (colors[i] == "WHITE") {
                DfsVisit(i);
            }
        }

        if (isCycle) {
            std::cout << -1;
        } else {
            for (auto element : result) {
                std::cout << element << " ";
            }
        }
    }

    void DfsVisit(int &start) {

        colors[start] = "GRAY";
        for (auto &neighbour : adjacencyList[start]) {
            if (colors[neighbour.to.index] == "WHITE") {
                DfsVisit(neighbour.to.index);
            } else if (colors[neighbour.to.index] == "GRAY") {
                isCycle = true;
            }
        }
        colors[start] = "BLACK";
        result.push_front(start + 1);
    }
};


int main() {
    size_t vertexSize = 0;
    size_t edgeSize = 0;
    std::deque<int> result;
    std::cin >> vertexSize >> edgeSize;
    Graph graph(vertexSize);
    for (int i = 0; i < edgeSize; ++i) {
        int from, to;
        std::cin >> from >> to;
        graph.AddEdge(from - 1, to - 1);
    }
    graph.TopSort();
    return 0;
}

