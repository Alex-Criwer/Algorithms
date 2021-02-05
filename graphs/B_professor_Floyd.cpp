#include <iostream>
#include <vector>
#include <optional>
#include <string>

size_t CONSTANT_TO_CHANGE_COLOR = 3;
size_t FIRST_INDICATOR = 1;

class Graph {

    struct Vertex {
        size_t index;
        size_t color;

        Vertex() = default;

        explicit Vertex(const size_t &index) : index(index) {}

        explicit Vertex(const size_t &index, const size_t &str) : index(index), color(str) {}

    };

    struct Edge {
        Vertex to;

        Edge() = default;

        explicit Edge(const size_t &index) : to(index) {}

        explicit Edge(const size_t &index, const size_t &str) : to(index, str) {}
    };

    size_t vertexSize;
    std::vector<std::vector<Edge>> adjacencyList;
    std::vector<Vertex> graphVertexes;
    std::vector<bool> used;
    bool isNotTwoColors = false;

public:

    explicit Graph(const size_t &vertexSize) : vertexSize(vertexSize),
                                               adjacencyList(vertexSize, std::vector<Edge>()),
                                               graphVertexes(vertexSize, Vertex()),
                                               used(vertexSize, false) {}


    void AddEdge(const int &from, const int &to) {
        adjacencyList[from].push_back(Edge(to));
        adjacencyList[to].push_back(Edge(from));
        graphVertexes[from] = Vertex(from);
        graphVertexes[to] = Vertex(to);

    }

    void Dfs() {
        for (auto &vertex : graphVertexes) {
            if (!used[vertex.index]) {
                DfsVisit(vertex, FIRST_INDICATOR);
            }
        }
    }

    void DfsVisit(Vertex &start, int indicatorOfColor) {

        if (isNotTwoColors) {
            return;
        }
        start.color = indicatorOfColor;
        graphVertexes[start.index].color = indicatorOfColor;
        used[start.index] = true;

        for (auto &neighbour : adjacencyList[start.index]) {
            if (!used[neighbour.to.index]) {
                used[neighbour.to.index] = true;
                DfsVisit(neighbour.to, CONSTANT_TO_CHANGE_COLOR - indicatorOfColor);
            } else if (used[neighbour.to.index] == used[start.index] &&
                       graphVertexes[neighbour.to.index].color == graphVertexes[start.index].color) {
                isNotTwoColors = true;
            }
        }
    }

    void professorFloydAnswer() {
        if (isNotTwoColors) {
            std::cout << "NO" << '\n';
        } else {
            std::cout << "YES" << '\n';
        }
    };

};


int main() {
    size_t vertexSize = 0;
    size_t numberOfPairs = 0;
    std::cin >> vertexSize >> numberOfPairs;
    Graph graph(vertexSize);
    for (int i = 0; i < numberOfPairs; ++i) {
        int from, to;
        std::cin >> from >> to;
        graph.AddEdge(from - 1, to - 1);
    }
    graph.Dfs();
    graph.professorFloydAnswer();
    return 0;
}

