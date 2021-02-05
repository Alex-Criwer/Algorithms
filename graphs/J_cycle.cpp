#include <iostream>
#include <vector>
#include <optional>
#include <string>

class Graph {

    struct Vertex {
        size_t index;
        std::string color = "WHITE";

        Vertex() = default;

        explicit Vertex(const size_t &index) : index(index) {}

        explicit Vertex(const size_t &index, const std::string &str) : index(index), color(str) {}

    };

    struct Edge {
        Vertex to;

        Edge() = default;

        explicit Edge(const size_t &index) : to(index) {}

        explicit Edge(const size_t &index, const std::string &str) : to(index, str) {}
    };

    size_t vertexSize;
    std::vector<std::vector<Edge>> adjacencyList;
    std::vector<Vertex> parents;
    std::vector<std::string> colors;
    bool isCycle = false;
    Vertex cycleStart;

public:

    explicit Graph(const size_t &vertexSize) : vertexSize(vertexSize),
                                               adjacencyList(vertexSize, std::vector<Edge>()),
                                               parents(vertexSize, Vertex(-1)),
                                               colors(vertexSize, "WHITE") {}


    void AddEdge(const int &from, const int &to) {
        size_t count = 0;
        for (auto &element : adjacencyList[from]) {
            if (element.to.index == to) {
                ++count;
            }
        }
        if (count == 0) {
            adjacencyList[from].push_back(Edge(to));
        }
    }

    void Dfs() {
        for (int i = 0; i < vertexSize; ++i) {
            if (colors[i] == "WHITE") {
                DfsVisit(Vertex(i));
            }
        }
    }

    void DfsVisit(Vertex start) {

        colors[start.index] = "GRAY";

        for (auto &neighbour : adjacencyList[start.index]) {
            if (colors[neighbour.to.index] == "WHITE") {
                parents[neighbour.to.index] = start;
                DfsVisit(neighbour.to);
            } else if (colors[neighbour.to.index] == "GRAY") {
                isCycle = true;
                parents[neighbour.to.index] = start;
                cycleStart = neighbour.to;
            }
        }
        colors[start.index] = "BLACK";
    }

    void PrintCycle() {
        if (isCycle) {
            std::cout << "YES" << '\n';
            std::vector<Vertex> result;

            Vertex current = parents[cycleStart.index];
            while (current.index != cycleStart.index) {

                result.push_back(current);
                current = parents[current.index];
            }
            result.push_back(cycleStart);
            for (auto it = result.rbegin(); it != result.rend(); ++it) {
                std::cout << it->index + 1 << " ";
            }

        } else {
            std::cout << "NO" << '\n';
        }
    }

};


int main() {
    size_t vertexSize = 0;
    size_t edgeSize = 0;
    std::cin >> vertexSize >> edgeSize;
    Graph graph(vertexSize);
    for (int i = 0; i < edgeSize; ++i) {
        int from, to;
        std::cin >> from >> to;
        graph.AddEdge(from - 1, to - 1);
    }
    graph.Dfs();
    graph.PrintCycle();

    return 0;
}

