#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

typedef size_t Vertex;

int INF = std::numeric_limits<int>::max();

void Relax(const Vertex &from, const Vertex &to, const size_t &weight, std::vector<int> &distances) {
    if (distances[to] > distances[from] + weight && distances[from] != INF) {
        distances[to] = distances[from] + weight;
    }
}

class Graph {

    struct Edge {
        Vertex from;
        Vertex to;
        int timeFrom;
        int timeTo;

        explicit Edge(const size_t &from, const int &timeFrom, const size_t &to, const int &timeTo) : from(from), to(to), timeFrom(timeFrom), timeTo(timeTo) {}
    };

    size_t vertexSize = 0;
    size_t edgeSize = 0;
    std::vector<Edge> edges;

public:

    explicit Graph(const int &vertexSize) : vertexSize(vertexSize) {}

    void AddEdge(const size_t &from, const int &timeFrom,const size_t &to, const int &timeTo) {
        edges.push_back(Edge(from, timeFrom, to, timeTo));
        ++edgeSize;
    }

    int Bellman_Ford(const Vertex &start, const Vertex &end) {
        std::vector<int> distances(vertexSize, INF);
        distances[start] = 0;
        for (int i = 0; i < vertexSize - 1; ++i) {
            for (const Edge &edge : edges) {
                Relax(edge.from, edge.to, edge.timeTo - edge.timeFrom, distances);
            }
        }
        return distances[end];
    }


};


int main() {
    size_t vertexSize = 0, edgeSize = 0;
    Vertex start, end;
    std::cin >> vertexSize;
    std::cin >> start >> end;
    std::cin >> edgeSize;
    Graph graph(vertexSize);
    Vertex from = 0, to = 0;
    int timeFrom = 0 , timeTo = 0;
    for (int i = 0; i < edgeSize; ++i) {
        std::cin >> from >> timeFrom >> to >> timeTo;
        graph.AddEdge(from - 1, timeFrom, to - 1, timeTo);

    }
    std::cout << graph.Bellman_Ford(start - 1, end - 1) << '\n';
    return 0;
}
