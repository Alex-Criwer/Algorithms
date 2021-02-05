/*Дан неориентированный граф. Требуется найти все мосты в нем.*/
#include <iostream>
#include <set>
#include <vector>
#include <map>
#include <algorithm>

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
        Vertex from;
        Vertex to;

        explicit Edge(const int &index) : to(index) {}

        explicit Edge(const int &from, const int &to) : from(from), to(to) {}

        bool operator<(const Edge &other) const {
            return std::pair<int, int>(from.index, to.index) < std::pair<int, int>(other.from.index, other.to.index);
        }
    };

    int vertexSize = 0;
    std::vector<std::vector<Edge>> adjacencyList;
    std::map<Edge, int> edgeNumber;
    std::map<Edge, bool> isPotentialBridge;
    size_t counter = 0;

public:

    explicit Graph(const int &vertexSize) : vertexSize(vertexSize),
                                            adjacencyList(vertexSize, std::vector<Edge>()) {}

    void AddEdge(const int &from, const int &to) {
        adjacencyList[from].push_back(Edge(to));
        adjacencyList[to].push_back(Edge(from));
        ++counter;
        Edge currentEdge(from, to);
        Edge currentReverseEdge(to, from);
        if (edgeNumber.find(currentEdge) == edgeNumber.end()) {
            edgeNumber[currentEdge] = counter;
            edgeNumber[currentReverseEdge] = counter;
            isPotentialBridge[currentEdge] = true;
            isPotentialBridge[currentReverseEdge] = true;
        } else {
            isPotentialBridge[currentEdge] = false;
            isPotentialBridge[currentReverseEdge] = false;
        }
    }

    void getBridgesIndex() {
        std::vector<Colors> colors(vertexSize, Colors::  WHITE);
        std::vector<int> tIn(vertexSize);
        std::vector<int> fUp(vertexSize);
        std::vector<int> answer;
        std::set<Edge> bridges;
        size_t time = 0;
        for (int i = 0; i < vertexSize; ++i) {
            if (colors[i] == Colors::WHITE) {
                DfsVisit(Vertex(i), Vertex(-1), time, colors, tIn, fUp, bridges);
            }
        }
        std::cout << bridges.size() << '\n';
        for (const auto &edge : bridges) {
            answer.push_back(edgeNumber[edge]);
        }
        std::sort(answer.begin(), answer.end());
        for (const auto el : answer) {
            std::cout << el << ' ';
        }
    }

    void DfsVisit(Vertex start, Vertex parent, size_t &time, std::vector<Colors> &colors,
                  std::vector<int> &tIn, std::vector<int> &fUp, std::set<Edge> &bridges) {
        ++time;
        tIn[start.index] = time;
        fUp[start.index] = time;
        colors[start.index] = Colors::GRAY;
        for (auto &neighbour : adjacencyList[start.index]) {
            if (neighbour.to == parent) {
                continue;
            }
            if (colors[neighbour.to.index] == Colors::WHITE) {
                DfsVisit(neighbour.to, start, time, colors, tIn, fUp, bridges);
                fUp[start.index] = std::min(fUp[start.index], fUp[neighbour.to.index]);
                if (fUp[neighbour.to.index] > tIn[start.index]) {
                    if (isPotentialBridge[Edge(start.index, neighbour.to.index)]) {
                        bridges.insert(Edge(start.index, neighbour.to.index));
                    }
                }
            }
            if (colors[neighbour.to.index] == Colors::GRAY) {
                fUp[start.index] = std::min(fUp[start.index], tIn[neighbour.to.index]);
            }
        }
        colors[start.index] = Colors::BLACK;
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
    graph.getBridgesIndex();
    return 0;
}
