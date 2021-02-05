#include <iostream>
#include <vector>
#include <queue>
#include <optional>
#include <limits>
#include <map>

const int INTMAX = std::numeric_limits<int>::max();
std::vector<int> possibleMovesX{2, 2, -2, -2, 1, 1, -1, -1};
std::vector<int> possibleMovesY{-1, 1, 1, -1, 2, -2, 2, -2};
const size_t SIZE = 8;

class Graph {
public:
    struct Vertex {
        int x;
        int y;

        Vertex () = default;

        Vertex (const int &x, const int &y) : x(x), y(y) {}

        bool isSafe(int n) {
            return !(x < 0 || y < 0 || x >= n || y >= n);
        }

        bool operator<(const Vertex  &other) const {
            return x < other.x || (x == other.x && y < other.y);
        }
    };

    struct Edge {

        Vertex to;

        Edge(const int &x, const int &y) : to(x, y) {}
    };

private:
    size_t vertexSize;
    std::map<Vertex, std::vector<Edge>> adjacencyList;
    std::map<Vertex, Vertex> parents;
    std::map<Vertex, bool> used;
    std::map<Vertex, int> distances;

public:

    explicit Graph(const size_t &vertexSize) : vertexSize(vertexSize) {}

    void Reset() {
        used.clear();
        parents.clear();
        distances.clear();
    }

    void AddEdge(const Vertex &from, const Vertex &to) {
        adjacencyList[from].push_back(Edge(to.x, to.y));
        adjacencyList[to].push_back(Edge(from.x, from.y));
    }

    std::map<Vertex, int> Bfs(const Vertex &start, const Vertex &end) {
        Reset();
        used[start] = true;
        Vertex temp(-1, -1);
        parents[start] = temp;
        distances[start] = 0;
        std::queue<Vertex> bfsQueue;
        bfsQueue.push(start);
        while (!bfsQueue.empty()) {
            Vertex vertex = bfsQueue.front();
            bfsQueue.pop();

            for (int i = 0; i < SIZE; ++i) {
                Edge neighbour(vertex.x + possibleMovesX[i], vertex.y + possibleMovesY[i]);
                if (!used[neighbour.to] && neighbour.to.isSafe(vertexSize)) {
                    parents[neighbour.to] = vertex;
                    distances[neighbour.to] = distances[vertex] + 1;
                    used[neighbour.to] = true;
                    bfsQueue.push(neighbour.to);
                }
            }
        }
        return distances;
    }

    void PrintPath(const Vertex &vertex) {
        std::cout << distances[vertex] << '\n';
        std::vector<Vertex> result;
        Vertex current = vertex;
        while (parents[current].x != -1 && parents[current].y != -1) {
            result.push_back(current);
            current = parents[current];
        }
        result.push_back(current);
        for (auto it = result.rbegin(); it != result.rend(); it = std::next(it)) {
            std::cout << it->x + 1 << " " << it->y + 1 << '\n';
        }
    }

};


int main() {
    size_t numberOfVertex;
    size_t fromX, toX, fromY, toY;
    std::cin >> numberOfVertex >> fromX >> fromY >> toX >> toY;
    Graph graph(numberOfVertex);
    graph.Bfs(Graph::Vertex(fromX - 1, fromY - 1), Graph::Vertex(toX - 1, toY - 1));
    graph.PrintPath(Graph::Vertex(toX - 1, toY - 1));
    return 0;
}
