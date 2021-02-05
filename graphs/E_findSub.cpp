#include <iostream>
#include <vector>
#include <queue>
#include <optional>
#include <limits>
#include <map>

const int INTMAX = std::numeric_limits<int>::max();
const int MAX_NUMBER_OF_NEIGHBOURS = 4;
std::vector<int> possibleMovesX{0, 0, 1, -1};
std::vector<int> possibleMovesY{1, -1, 0, 0};

class Graph {
public:
    struct Vertex {
        int x;
        int y;

        Vertex() = default;

        Vertex(const int &x, const int &y) : x(x), y(y) {}

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

        Edge(const int &x, const int &y) : to(x, y) {}

    };

private:
    size_t vertexSize;
    size_t n, m;
    std::map<Vertex, std::vector<Edge>> adjacencyList;
    std::map<Vertex, bool> used;
    std::map<Vertex, int> distances;
    std::vector<std::vector<int>> city;

public:

    std::vector<Edge> neighboursOfCell(const int &x, const int &y, const int &n, const int &m) {
        std::vector<Edge> result;
        for (int i = 0; i < MAX_NUMBER_OF_NEIGHBOURS; ++i) {
            Vertex neighbour(x + possibleMovesX[i], y + possibleMovesY[i]);
            if (neighbour.isSafe(n, m)) {
                result.push_back(Edge(neighbour.x, neighbour.y));
            }
        }
        return result;
    }


    explicit Graph(const size_t &n, const size_t &m, std::vector<std::vector<int>> &city) : n(n), m(m),
                                                                                            vertexSize(n * m),
                                                                                            city(city) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                Vertex vertex(j, i);
                adjacencyList[vertex] = neighboursOfCell(j, i, n, m);
                used[vertex] = false;
            }
        }
    }

    void Reset() {
        used.clear();
        distances.clear();
    }

    int Bfs(const int x, const int y) {
        Vertex start(x, y);
        Reset();
        if (city[y][x] == 1) {
            return 0;
        }
        bool stop = false;
        int answer = 0;
        distances[start] = 0;
        used[start] = true;
        std::queue<Vertex> bfsQueue;
        bfsQueue.push(start);
        while (!bfsQueue.empty() && !stop) {
            Vertex vertex = bfsQueue.front();
            bfsQueue.pop();
            for (auto neighbour : adjacencyList[vertex]) {
                if (!used[neighbour.to]) {
                    distances[neighbour.to] = distances[vertex] + 1;
                    used[neighbour.to] = true;
                    bfsQueue.push(neighbour.to);
                    if (city[neighbour.to.y][neighbour.to.x] == 1) {
                        answer = distances[neighbour.to];
                        stop = true;
                        break;
                    }
                }
            }
        }
        return answer;
    }

    void minDistanceToSub() {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                std::cout << Bfs(j, i) << " ";
            }
            std::cout << '\n';
        }
    }

};


int main() {
    int n, m;
    std::cin >> n >> m;
    std::vector<std::vector<int>> city(n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            int element;
            std::cin >> element;
            city[i].push_back(element);
        }
    }
    Graph graph(n, m, city);
    graph.minDistanceToSub();
    return 0;
}
