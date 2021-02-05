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
    Vertex cycleStart, cycleEnd;
    size_t countCycle = 0;

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
                ++countCycle;
                parents[neighbour.to.index] = start;
                cycleStart = neighbour.to;
                cycleEnd = start;

                std::vector<Vertex> result;
                while (cycleEnd.index != cycleStart.index) {
                    result.push_back(cycleEnd);
                    cycleEnd = parents[cycleEnd.index];
                }
                result.push_back(cycleStart);

                for (auto &element: result) {
                    colors[element.index] = "BLACK";
                }
            }
        }

        colors[start.index] = "BLACK";
    }

    void numberOfCycles() {
        std::cout << countCycle << '\n';
    }

};


int main() {
    size_t vertexSize = 0;
    std::cin >> vertexSize;
    Graph graph(vertexSize);
    for (int i = 0; i < vertexSize; ++i) {
        int to;
        std::cin >> to;
        graph.AddEdge(i, to - 1);
    }
    graph.Dfs();
    graph.numberOfCycles();
    return 0;
}

