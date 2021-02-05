/*Найдите точки сочленения в неориентированном графе.*/
#include <iostream>
#include <set>
#include <vector>

const size_t minNumberOfChildren = 2;

enum Colors {
    WHITE,
    GRAY,
    BLACK
};

class Graph {
    struct Vertex {
        int index;

        Vertex() = default;

        explicit Vertex(const int &index) : index(index) {}

        bool operator==(const Vertex &other) const {
            return index == other.index;
        }
    };

    struct Edge {
        Vertex to;

        explicit Edge(const int &index) : to(index) {}
    };

    int vertexSize = 0;
    std::vector<std::vector<Edge>> adjacencyList;

public:

    explicit Graph(const int &vertexSize) : vertexSize(vertexSize),
                                            adjacencyList(vertexSize, std::vector<Edge>()) {}

    void AddEdge(const int &from, const int &to) {
        adjacencyList[from].push_back(Edge(to));
        adjacencyList[to].push_back(Edge(from));
    }

    std::set<int> CutVertexes() {
        std::vector<Colors> colors(vertexSize, Colors::WHITE);
        std::vector<int> tIn(vertexSize);
        std::vector<int> fUp(vertexSize);
        size_t time = 0;
        std::set<int> cutVertexes;
        for (int i = 0; i < vertexSize; ++i) {
            if (colors[i] == Colors::WHITE) {
                DfsVisit(Vertex(i), Vertex(-1), time, colors, tIn, fUp, cutVertexes);
            }
        }
        return cutVertexes;
    }

    void DfsVisit(Vertex start, Vertex parent, size_t &time, std::vector<Colors> &colors,
                  std::vector<int> &tIn, std::vector<int> &fUp, std::set<int> &cutVertexes) {
        ++time;
        tIn[start.index] = time;
        fUp[start.index] = time;
        colors[start.index] = Colors::GRAY;
        int counterOfChildren = 0;
        for (auto &neighbour : adjacencyList[start.index]) {
            if (neighbour.to == parent) {
                continue;
            }
            if (colors[neighbour.to.index] == Colors::WHITE) {
                DfsVisit(neighbour.to, start, time, colors, tIn, fUp, cutVertexes);
                fUp[start.index] = std::min(fUp[start.index], fUp[neighbour.to.index]);
                if (parent.index != -1 && fUp[neighbour.to.index] >= tIn[start.index]) {
                    cutVertexes.insert(start.index);
                }
                ++counterOfChildren;
            }
            if (colors[neighbour.to.index] == Colors::GRAY) {
                fUp[start.index] = std::min(fUp[start.index], tIn[neighbour.to.index]);
            }
        }
        if (parent.index == -1) {
            if (counterOfChildren >= minNumberOfChildren) {
                cutVertexes.insert(start.index);
            }
        }
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    size_t vertexSize = 0;
    size_t edgeSize = 0;
    std::cin >> vertexSize >> edgeSize;
    Graph graph(vertexSize);
    for (int i = 0; i < edgeSize; ++i) {
        int from, to;
        std::cin >> from >> to;
        graph.AddEdge(from - 1, to - 1);
    }
    std::set<int> cutVertexes = graph.CutVertexes();
    std::cout << cutVertexes.size() << '\n';
    for (const auto &vertex : cutVertexes) {
        std::cout << vertex + 1 << '\n';
    }
    return 0;
}
