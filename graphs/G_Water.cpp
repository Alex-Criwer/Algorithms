#include <iostream>
#include <vector>
#include <queue>
#include <optional>
#include <map>
#include <cassert>

const int MAX_NUMBER_OF_NEIGHBOURS = 4;
std::vector<int> possibleMovesX{0, 0, 1, -1};
std::vector<int> possibleMovesY{1, -1, 0, 0};

class Graph {
public:
    struct Vertex {
        int x;
        int y;
        int levelOfWater;

        Vertex() = default;

        Vertex(const int &x, const int &y) : x(x), y(y) {}

        Vertex(const int &x, const int &y, const int &levelOfWater) : x(x), y(y), levelOfWater(levelOfWater) {}

        bool isSafe(const int &n, const int &m) {
            return !(x < 0 || y < 0 || x >= m || y >= n);
        }

        bool operator<(const Vertex &other) const {
            return x < other.x || (x == other.x && y < other.y);
        }

    };

    struct Edge {
        Vertex to;

        Edge() = default;

        Edge(const int &x, const int &y, const int &levelOfWater) : to(x, y, levelOfWater) {}

    };

private:
    size_t vertexSize;
    size_t n, m;
    std::map<Vertex, std::vector<Edge>> adjacencyList;
    std::map<Vertex, bool> used;
    std::map<Vertex, int> distances;
    std::vector<std::vector<int>> water;
    std::vector<bool> gutters;

public:

    std::vector<Edge>
    neighboursOfCell(const int &x, const int &y, const int &levelOfWater, const int &n, const int &m) {
        std::vector<Edge> result;
        for (int i = 0; i < MAX_NUMBER_OF_NEIGHBOURS; ++i) {
            Vertex neighbour(x + possibleMovesX[i], y + possibleMovesY[i]);
            if (neighbour.isSafe(n, m)) {
                result.push_back(Edge(neighbour.x, neighbour.y, water[neighbour.y][neighbour.x]));
            }
        }
        return result;
    }


    explicit Graph(const size_t &n, const size_t &m, std::vector<std::vector<int>> &water) : n(n), m(m),
                                                                                             vertexSize(n * m),
                                                                                             gutters(n * m, true),
                                                                                             water(water) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                Vertex vertex(j, i, water[i][j]);
                adjacencyList[vertex] = neighboursOfCell(j, i, water[i][j], n, m);
                used[vertex] = false;
            }
        }
    }

    void Reset() {
        used.clear();
        distances.clear();
    }

    void Hollow(const Vertex &vertex, size_t &counter) {
        if (used[vertex]) {
            return;
        }
        used[vertex] = true;
        for (const auto &neighbour : adjacencyList[vertex]) {
            if (water[vertex.y][vertex.x] == neighbour.to.levelOfWater) {
                Hollow(neighbour.to, counter);
            } else if (water[vertex.y][vertex.x] > neighbour.to.levelOfWater) {
                gutters[counter] = false;
            }

        }
    }

    size_t Answer() {
        size_t counter = 0;
        size_t answer = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                Vertex current(j, i, water[i][j]);
                if (!used[current]) {
                    Hollow(current, counter);
                    ++counter;
                }
            }
        }
        for (int i = 0; i < counter; ++i) {
            if (gutters[i]) {
                ++answer;
            }
        }
        return answer;
    }

};


int main() {
    int n, m;
    std::cin >> n >> m;
    std::vector<std::vector<int>> water(n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            int element;
            std::cin >> element;
            water[i].push_back(element);
        }
    }
    Graph graph(n, m, water);
    std::cout << graph.Answer() << '\n';
    return 0;
}
