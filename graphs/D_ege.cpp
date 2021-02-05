#include <iostream>
#include <queue>
#include <vector>
#include <limits>
#include <map>

const int INTMAX = std::numeric_limits<int>::max();
const int firstNumberRank = 1000;
const int lastNumberRank = 10;

class Graph {

    struct Vertex {
        int index;

        Vertex() = default;

        explicit Vertex(const int &index) : index(index) {}

        Vertex(const Vertex &other) {
            this->index = other.index;
        }

        Vertex AddOne() {
            if (this->index / firstNumberRank != 9) {
                return Vertex(this->index + firstNumberRank);
            }
            return *this;
        }

        Vertex MinusOne() {
            if (this->index % lastNumberRank != 1) {
                return Vertex(this->index - 1);
            }
            return *this;
        }

        Vertex LeftMove() {
            return Vertex((this->index % firstNumberRank) * lastNumberRank + this->index / firstNumberRank);
        }

        Vertex RightMove() {
            return Vertex((this->index % lastNumberRank) * firstNumberRank + this->index / lastNumberRank);
        }

        std::vector<Vertex> allOperations() {
            return {AddOne(), MinusOne(), LeftMove(), RightMove()};
        }

        bool operator<(const Vertex &other) const {
            return this->index < other.index;
        }

    };


    struct Edge {
        Vertex to;

        Edge() = default;

        explicit Edge(const int &index) : to(index) {}

    };


    std::map<Vertex, bool> used;
    std::map<Vertex, Vertex> parents;
    std::map<Vertex, int> distances;

public:

    void Reset() {
        used.clear();
        parents.clear();
        distances.clear();
    }

    std::map<Vertex, int> Bfs(const int &first, const int &last) {
        Reset();
        bool stop = false;
        Vertex start(first), end(last);
        std::queue<Vertex> bfsQueue;
        parents[start] = Vertex{-1};
        used[start] = true;
        distances[start] = 1;
        bfsQueue.push(start);
        while (!bfsQueue.empty() && !stop) {
            Vertex vertex = bfsQueue.front();
            bfsQueue.pop();
            if (vertex.index == end.index) {
                break;
            }
            std::vector<Vertex> neighbours = vertex.allOperations();
            for (const auto &neighbour : neighbours) {
                if (!used[neighbour]) {
                    parents[neighbour] = vertex;
                    used[neighbour] = true;
                    distances[neighbour] = distances[vertex] + 1;
                    bfsQueue.push(neighbour);
                }
                if (neighbour.index == end.index) {
                    stop = true;
                    break;
                }
            }
        }
        return distances;
    }

    void PrintPath(const int &last) {
        Vertex end(last);
        std::cout << distances[end] << '\n';
        std::vector<Vertex> result;
        Vertex current = end;
        while (parents[current].index != -1) {
            result.push_back(current);
            current = parents[current];
        }
        result.push_back(current);
        for (auto it = result.rbegin(); it != result.rend(); it = std::next(it)) {
            std::cout << it->index << '\n';
        }
    }

};


int main() {
    int first = 0, last = 0;
    Graph graph;
    std::cin >> first >> last;
    graph.Bfs(first, last);
    graph.PrintPath(last);
    return 0;
}
