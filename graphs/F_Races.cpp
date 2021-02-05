#include <iostream>
#include <vector>
#include <queue>
#include <optional>
#include <limits>
#include <map>

const int MAX_NUMBER_OF_NEIGHBOURS = 4;

enum Turns {
    LEFT,
    RIGHT,
    UP,
    DOWN
};

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

        bool operator==(const Vertex &other) const {
            return x == other.x && y == other.y;
        }

        bool operator!=(const Vertex &other) const {
            return !(*this == other);
        }

    };

    struct Edge {
        Vertex to;

        Edge() = default;

        Edge(const int &x, const int &y) : to(x, y) {}

    };

private:
    size_t vertexSize;
    int n, m;
    std::map<Vertex, std::vector<Edge>> adjacencyList;
    std::map<Vertex, bool> used;
    std::map<Vertex, int> distances;
    std::vector<std::vector<char>> board;

public:

    std::vector<Edge> neighboursOfCell(const int &x, const int &y, const int &n, const int &m) {
        std::vector<Edge> result;
        for (int i = 0; i < MAX_NUMBER_OF_NEIGHBOURS; ++i) {
            Vertex neighbour = findNeighbour(x, y, n, m, i);
            if (neighbour.isSafe(n, m) && neighbour != Vertex{x, y} && !used[neighbour]) {
                result.push_back(Edge(neighbour.x, neighbour.y));
            }
        }
        return result;
    }

    Vertex findNeighbour(const int &x, const int &y, const int &n, const int &m, const int &i) {
        int moveX = 0;
        int moveY = 0;
        switch (i) {
            case Turns::LEFT:
                while (x - moveX > 0 && board[y][x - moveX - 1] != '#') {
                    ++moveX;
                }
                return Vertex(x - (moveX + 1) / 2, y);

            case Turns::RIGHT:
                moveX = 0;
                while (x + moveX < m - 1 && board[y][x + moveX + 1] != '#') {
                    ++moveX;
                }
                return Vertex(x + (moveX + 1) / 2, y);

            case Turns::UP:
                moveY = 0;
                while (y - moveY > 0 && board[y - moveY - 1][x] != '#') {
                    ++moveY;
                }
                return Vertex(x, y - (moveY + 1) / 2);

            case Turns::DOWN:
                moveY = 0;
                while (y + moveY < n - 1 && board[y + moveY + 1][x] != '#') {
                    ++moveY;
                }
                return Vertex(x, y + (moveY + 1) / 2);

        }

    }


    explicit Graph(const int &n, const int &m, std::vector<std::vector<char>> &board) : n(n), m(m),
                                                                                        vertexSize(n * m),
                                                                                        board(board) {}

    void Reset() {
        used.clear();
        distances.clear();
    }

    int Bfs(const int x, const int y) {
        Vertex start(x, y);
        Reset();
        bool stop = false;
        int answer = -1;
        distances[start] = 0;
        used[start] = true;
        std::queue<Vertex> bfsQueue;
        bfsQueue.push(start);
        while (!bfsQueue.empty() && !stop) {
            Vertex vertex = bfsQueue.front();
            bfsQueue.pop();
            std::vector neighbours = neighboursOfCell(vertex.x, vertex.y, n, m);

            for (auto neighbour : neighbours) {
                if (!used[neighbour.to]) {
                    distances[neighbour.to] = distances[vertex] + 1;
                    used[neighbour.to] = true;
                    bfsQueue.push(neighbour.to);
                    if (board[neighbour.to.y][neighbour.to.x] == 'T') {
                        answer = distances[neighbour.to];
                        stop = true;
                        break;
                    }
                }
            }
        }
        return answer;
    }

};


int main() {
    int n, m;
    std::cin >> n >> m;
    std::vector<std::vector<char>> board(n);
    int startX = 0;
    int startY = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            char element;
            std::cin >> element;
            board[i].push_back(element);
            if (element == 'S') {
                startX = j;
                startY = i;
            }
        }
    }
    Graph graph(n, m, board);
    std::cout << graph.Bfs(startX, startY) << '\n';
    return 0;
}

