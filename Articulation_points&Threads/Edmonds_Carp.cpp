#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

typedef int Vertex;

class Graph {

    struct Edge {
        Vertex from;
        Vertex to;
        int capacity;
        int flow;
        int backIndex = 0;

        explicit Edge(const int &index) : to(index) {}

        explicit Edge(const int &from, const int &to, const int &capacity, const int &flow) : from(from), to(to),
                                                                                              capacity(capacity),
                                                                                              flow(flow) {}
    };

    int vertexSize = 0;
    std::vector<std::vector<Edge>> adjacencyList;
    static constexpr int MAX_CAPACITY = 1000000000;
public:

    explicit Graph(const int &vertexSize) : vertexSize(vertexSize),
                                            adjacencyList(vertexSize, std::vector<Edge>()) {}

    void AddEdge(const int &from, const int &to, const int &capacity) {
        adjacencyList[from].push_back(Edge(from, to, capacity, 0));
        adjacencyList[to].push_back(Edge(to, from, 0, 0));
        adjacencyList[from].back().backIndex = adjacencyList[to].size() - 1;
        adjacencyList[to].back().backIndex = adjacencyList[from].size() - 1;
    }

    int maxFlow(const int &from, const int &to) {
        int maxFlow = 0;
        while (true) {
            std::vector<Vertex> parents(vertexSize, -1);
            std::vector<int> parentsEdgeNumber(vertexSize, -1);
            std::vector<bool> used(vertexSize, false);
            int flow = EdmondsCarp(from, to, parents, parentsEdgeNumber, used);
            if (flow == 0) {
                return maxFlow;
            }
            maxFlow += flow;
            int copyFrom = from, copyTo = to;
            while (copyFrom != copyTo) {
                Vertex prev = parents[copyTo];
                Edge &curEdge = adjacencyList[prev][parentsEdgeNumber[copyTo]];
                Edge &backEdge = adjacencyList[copyTo][curEdge.backIndex];
                curEdge.flow += flow;
                backEdge.flow -= flow;
                copyTo = prev;
            }

        }

    }


    int EdmondsCarp(const int &startVertex, const int &endVertex, std::vector<Vertex> &parents,
                    std::vector<int> &parentsEdgeNumber, std::vector<bool> &used) {
        std::queue<Vertex> bfsQueue;
        std::vector<int> flow(vertexSize, 0);
        bfsQueue.push(startVertex);
        flow[startVertex] = MAX_CAPACITY;
        while (!bfsQueue.empty()) {
            int vertex = bfsQueue.front();
            bfsQueue.pop();
            used[vertex] = true;
            int edgeNumber = 0;
            for (const auto &edge : adjacencyList[vertex]) {
                int edgeFlow = std::min(edge.capacity - edge.flow, flow[vertex]);
                if (flow[edge.to] < edgeFlow && !used[edge.to]) {
                    parents[edge.to] = vertex;
                    parentsEdgeNumber[edge.to] = edgeNumber;
                    flow[edge.to] = edgeFlow;
                    bfsQueue.push(edge.to);
                }
                ++edgeNumber;
            }
        }
        return flow[endVertex];
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
    for (int i = 0; i < edgeSize; ++i) {
        std::cin >> from >> to >> capacity;
        graph.AddEdge(from - 1, to - 1, capacity);
    }
    int maxFlow = graph.maxFlow(0, vertexSize - 1);
    std::cout << maxFlow << '\n';
    return 0;
}