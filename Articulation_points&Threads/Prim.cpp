/*Требуется найти в связном графе остовное дерево минимального веса. Задачу решайте с помощью алгоритма Прима
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include <set>

const int INF = std::numeric_limits<int>::max();

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
        size_t weight;

        explicit Edge(const int &index, const size_t &weight) : to(index), weight(weight) {}

        bool operator==(const Edge &other) const {
            return to == other.to && weight == other.weight;
        }
    };

    int vertexSize = 0;
    std::vector<std::vector<Edge>> adjacencyList;

public:

    explicit Graph(const int &vertexSize) : vertexSize(vertexSize),
                                            adjacencyList(vertexSize, std::vector<Edge>()) {}


    void AddEdge(const int &from, const int &to, const size_t &weight) {
        adjacencyList[from].push_back(Edge(to, weight));
        adjacencyList[to].push_back(Edge(from, weight));
    }

    int PrimsMST() {
        int sumOfMST = 0;
        std::vector<bool> used(vertexSize, false);
        std::vector<int> parents(vertexSize, -1);
        std::vector<int> distances(vertexSize, INF);
        std::vector<std::pair<int, int>> MST;
        std::set<std::pair<int, int>> heap;
        distances[0] = 0;
        heap.insert(std::make_pair(0, 0));
        for (int i = 0; i < vertexSize; ++i) {
            int minVertex = heap.begin()->second;
            used[minVertex] = true;
            heap.erase(heap.begin());
            if (parents[minVertex] != -1) {
                MST.emplace_back(parents[minVertex], minVertex);
            }
            for (auto &neighbour : adjacencyList[minVertex]) {
                if (!used[neighbour.to.index] && distances[neighbour.to.index] > neighbour.weight) {
                    heap.erase(std::make_pair(distances[neighbour.to.index], neighbour.to.index));
                    distances[neighbour.to.index] = neighbour.weight;
                    parents[neighbour.to.index] = minVertex;
                    heap.insert(std::make_pair(neighbour.weight, neighbour.to.index));
                }
            }
        }

        for (int i = 0; i < distances.size(); ++i) {
            if (distances[i] != INF) {
                sumOfMST += distances[i];
            }
        }
        return sumOfMST;
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
    int from, to;
    size_t weight = 0;
    for (int i = 0; i < edgeSize; ++i) {
        std::cin >> from >> to >> weight;
        graph.AddEdge(from - 1, to - 1, weight);
    }
    std::cout << graph.PrimsMST();
    return 0;
}