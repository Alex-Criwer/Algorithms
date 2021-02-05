#include <iostream>
#include <vector>
#include <optional>
#include <string>

class Graph {

    struct Vertex {
        size_t index;

        Vertex() = default;

        explicit Vertex(const size_t &index) : index(index) {}

    };

    struct Edge {
        Vertex to;

        explicit Edge(const size_t &index) : to(index) {}
    };

    size_t vertexSize;
    std::vector<std::vector<Edge>> adjacencyList;
    std::vector<std::string> colors;
    std::vector<Vertex> components;
    std::vector<std::vector<Vertex>> answer;

public:

    explicit Graph(const size_t &vertexSize) : vertexSize(vertexSize),
                                               adjacencyList(vertexSize, std::vector<Edge>()),
                                               colors(vertexSize, "WHITE") {}

    void AddEdge(const int &from, const int &to) {
        adjacencyList[from].push_back(Edge(to));
        adjacencyList[to].push_back(Edge(from));
    }

    void FindComponents() {
        for (int i = 0; i < vertexSize; ++i) {
            if (colors[i] == "WHITE") {
                components.clear();
                DfsVisit(Vertex(i));
                answer.push_back(components);
            }
        }
        std::cout << answer.size() << '\n';
        for (int i = 0; i < answer.size(); ++i) {
            std::cout << answer[i].size() << '\n';
            for (const auto &element: answer[i]) {
                std::cout << element.index + 1 << " ";
            }
            std::cout << '\n';
        }
    }


    void DfsVisit(const Vertex &start) {
        colors[start.index] = "GRAY";
        components.push_back(start);
        for (auto &neighbour: adjacencyList[start.index]) {
            if (colors[neighbour.to.index] == "WHITE") {
                DfsVisit(neighbour.to);
            }
        }
        colors[start.index] = "BLACK";
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
    graph.FindComponents();
    return 0;
};
