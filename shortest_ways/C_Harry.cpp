#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

typedef long long Vertex;

long long INF = std::numeric_limits<long long>::max();


void Relax(const Vertex &from, const long long&timeFrom, const Vertex &to, const long long &timeTo, std::vector<long long> &distances) {
    if (distances[from] <=  timeFrom && distances[to] > timeTo) {
        distances[to] = timeTo;
    }
}

class Graph {

    struct Edge {
        Vertex from;
        Vertex to;
        long long timeFrom;
        long long timeTo;

        explicit Edge(const long long &from, const long long &timeFrom, const long long &to, const long long &timeTo) : from(from), to(to), timeTo(timeTo), timeFrom(timeFrom) {}
    };

    long long vertexSize = 0;
    long long edgeSize = 0;
    std::vector<Edge> edges;

public:

    explicit Graph(const long long &vertexSize) : vertexSize(vertexSize) {}

    void AddEdge(const long long &from,const long long& timeFrom, const long long &to, const long long &timeTo) {
        edges.push_back(Edge(from, timeFrom ,to, timeTo));
        ++edgeSize;
    }

    long long Bellman_Ford(const Vertex &start, const  Vertex &end) {
        std::vector<long long> distances(vertexSize, INF);
        distances[start] = 0;
        for (long long i = 0; i < edgeSize; ++i) {
            for (const Edge &edge : edges) {
                Relax(edge.from, edge.timeFrom, edge.to, edge.timeTo, distances);
            }
        }
        return distances[end];
    }
};


int main() {
    long long vertexSize, numberOfTeleports;
    std::cin >> vertexSize;
    Graph graph(vertexSize);
    Vertex start, end;
    std::cin >> start >> end;
    std::cin >> numberOfTeleports;
    Vertex from = 0, to = 0;
    long long timeFrom, timeTo;
    for (long long i = 0; i < numberOfTeleports; ++i) {
        std::cin >> from >> timeFrom >> to >> timeTo;
        graph.AddEdge(from - 1, timeFrom, to - 1, timeTo);
    }
    std::cout << graph.Bellman_Ford(start - 1, end - 1) << '\n';
    return 0;
}


