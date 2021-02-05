/*Задан ориентированный граф, каждое ребро которого обладает целочисленной
 * пропускной способностью. Найдите максимальный поток из вершины с номером
 * 1 в вершину с номером n.
В этой задаче необходимо реализовать алгоритм Форда-Фалкерсона.*/
#include <iostream>
#include <vector>
#include <algorithm>

#define DEBUG

#ifdef DEBUG
#define _debug (exrp) expr
#else
#define _debug (expr)
#endif

typedef int Vertex;

class Graph {

    struct Edge {
        Vertex from;
        Vertex to;
        int capacity;
        int flow;

        explicit Edge(const int &index) : to(index) {}

        explicit Edge(const int &from, const int &to, const int &capacity, const int &flow) : from(from), to(to),
                                                                                              capacity(capacity),
                                                                                              flow(flow) {}
    };

    int vertexSize = 0;
    std::vector<std::vector<int>> adjacencyList;
    std::vector<Edge> edges;
    static constexpr int MAX_CAPACITY = 100000;

public:

    explicit Graph(const int &vertexSize) : vertexSize(vertexSize),
                                            adjacencyList(vertexSize, std::vector<int>()) {}

    void AddEdge(const int &from, const int &to, const int &i, const int &capacity) {
        adjacencyList[from].push_back(i);
        adjacencyList[to].push_back(i ^ 1);
        edges.emplace_back(from, to, capacity, 0);
        edges.emplace_back(to, from, 0, 0);
    }

    int maxFlow(const int &from, const int &to) {
        int myMaxFlow = 0;
        std::vector<bool> used(vertexSize, false);
        while (true) {
            used.assign(vertexSize, false);
            if (fordFulkerson(from, to, MAX_CAPACITY, used) == 0) {
                break;
            }
        }
        for (const auto &numberOfEdge : adjacencyList[0]) {
            myMaxFlow += edges[numberOfEdge].flow;
        }
        return myMaxFlow;
    }

    int fordFulkerson(const int &currentVertex, const int &endVertex, const int &flow, std::vector<bool> &used) {
        if (currentVertex == endVertex) {
            return flow;
        }
        used[currentVertex] = true;
        for (const auto &neighbour : adjacencyList[currentVertex]) {
            auto &currEdge = edges[neighbour];
            if (!used[currEdge.to] && currEdge.flow < currEdge.capacity) {
                int delta = fordFulkerson(currEdge.to, endVertex, std::min(flow, currEdge.capacity - currEdge.flow),
                                          used);
                if (delta > 0) {
                    currEdge.flow += delta;
                    edges[neighbour ^ 1].flow -= delta;
                    return delta;
                }
            }
        }
        return 0;
    }
};


int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    size_t vertexSize = 0;
    size_t edgeSize = 0;
    size_t from = 0, to = 0, capacity = 0;
    std::cin >> vertexSize >> edgeSize;
    Graph graph(vertexSize);
    for (int i = 0; i < 2 * edgeSize; i += 2) {
        std::cin >> from >> to >> capacity;
        graph.AddEdge(from - 1, to - 1, i, capacity);
    }
    std::cout << graph.maxFlow(0, vertexSize - 1) << '\n';
    return 0;
}