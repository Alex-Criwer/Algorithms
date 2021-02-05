#include <iostream>
#include <vector>
#include <limits>

typedef int Vertex;

const int INF = 1e8;

constexpr int ERROR = -1;

class Graph {

    struct Edge {
        Vertex from;
        Vertex to;
        int weight;

        explicit Edge(const int &index, const int &weight) : to(index), weight(weight) {}

        explicit Edge(const int &from, const int &to, const int &weight) : from(from), to(to), weight(weight) {}
    };

    int vertexSize = 0;
    int edgeSize = 0;
    std::vector<Edge> edges;

public:

    explicit Graph(const int &vertexSize) : vertexSize(vertexSize) {}

    void AddEdge(const int &from, const int &to, const int &weight) {
        edges.emplace_back(from, to, weight);
        ++edgeSize;
    }

    int Bellman_Ford(const Vertex &start, const Vertex &end, const int &numberOfMoves) {
        std::vector<std::pair<int, int>> result(vertexSize, {INF, INF});

        result[end] = {0, numberOfMoves};
        for (int i = 0; i < vertexSize - 1; i++)
            for (int j = 0; j < edgeSize; j++)
                if (result[edges[j].from].second > 0) {
                    if (result[edges[j].to].first > result[edges[j].from].first + edges[j].weight)
                        result[edges[j].to] = {result[edges[j].from].first + edges[j].weight,
                                               result[edges[j].from].second - 1};
                }

        if (result[start].second == INF) {
            return ERROR;
        }
        return result[start].first;
    }

};


int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    int numberOfTowns = 0,
            numberOfFlights = 0,
            numberOfNights = 0,
            startTown = 0,
            endTown = 0;
    std::cin >> numberOfTowns >> numberOfFlights >> numberOfNights >> startTown >> endTown;
    int start = 0, end = 0, cost = 0;
    Graph flights(numberOfTowns);
    for (int i = 0; i < numberOfFlights; ++i) {
        std::cin >> start >> end >> cost;
        flights.AddEdge(end - 1, start - 1, cost);
    }
    std::cout << flights.Bellman_Ford(startTown - 1, endTown - 1, numberOfNights) << '\n';
    return 0;
}
