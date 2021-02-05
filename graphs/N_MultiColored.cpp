#include <iostream>
#include <vector>
#include <optional>
#include <string>

enum Colors {
    WHITE,
    GRAY,
    BLACK
};

class Graph {

    struct Vertex {
        int index;
        int color = Colors::WHITE;

        Vertex() = default;

        Vertex(const int &index) : index(index) {}

        Vertex(const int &index, const int &color) : index(index), color(color) {}
    };

    struct Edge {
        Vertex to;

        Edge() = default;

        Edge(const int &index) : to(index) {}

        Edge(const int &index, const int &color) : to(index, color) {}
    };

    size_t vertexSize;
    std::vector<std::vector<Edge>> adjacencyList;
    std::vector<int> colors;
    bool isCycle = false;
    bool stop = false;

public:

    Graph(const size_t &vertexSize) : vertexSize(vertexSize),
                                      adjacencyList(vertexSize, std::vector<Edge>()),
                                      colors(vertexSize, Colors::WHITE) {}

    void AddEdge(const int &index, const std::string &colorsToNeighbours) {
        for (int i = 0; i < colorsToNeighbours.size(); ++i) {
            if (colorsToNeighbours[i] == 'R') {
                adjacencyList[index].push_back(Edge(index + i + 1));
            } else {
                adjacencyList[index + i + 1].push_back(Edge(index));
            }
        }
    }

    void Dfs() {
        for (int i = 0; i < vertexSize; ++i) {
            if (colors[i] == Colors::WHITE && !stop) {
                DfsVisit(Vertex(i));
            }
        }
    }

    void DfsVisit(const Vertex &start) {
        colors[start.index] = Colors::GRAY;

        for (const auto &neighbour: adjacencyList[start.index]) {
            if (colors[neighbour.to.index] == Colors::WHITE) {
                DfsVisit(neighbour.to);
            } else if (colors[neighbour.to.index] == Colors::GRAY) {
                stop = true;
                isCycle = true;
            }
        }
        if (stop) {
            return;
        }
        colors[start.index] = Colors::BLACK;
    }

    void Answer() {
        if (isCycle) {
            std::cout << "NO" << '\n';
        } else {
            std::cout << "YES" << '\n';
        }
    }

};


int main() {
    std::cin.tie(0);
    std::ios_base::sync_with_stdio(false);
    size_t numberOfVertexes = 0;
    std::cin >> numberOfVertexes;
    Graph graph(numberOfVertexes);
    for (int i = 0; i < numberOfVertexes - 1; ++i) {
        std::string str;
        std::cin >> str;
        graph.AddEdge(i, str);
    }
    graph.Dfs();
    graph.Answer();
    return 0;
}