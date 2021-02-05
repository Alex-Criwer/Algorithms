#include <iostream>
#include <vector>
#include <limits>
#include <deque>
#include <set>

typedef long long int_t;

typedef int_t Vertex;

constexpr int_t INF = 1e18;

class Cmp {
public:
    bool operator()(const std::pair<int_t, int_t> &lhs, const std::pair<int_t, int_t> &rhs) const {
        if (lhs.first != rhs.first) {
            return lhs.first < rhs.first;
        }
        return lhs.second < rhs.second;
    }
};

class Graph {

    struct Edge {
        Vertex to;
        int_t weight;

        explicit Edge(const int_t &index, const int_t &weight) : to(index), weight(weight) {}
    };

    int_t vertexSize = 0;
    std::vector<std::vector<Edge>> adjacencyList;

public:

    explicit Graph(const int_t &vertexSize) : vertexSize(vertexSize),
                                            adjacencyList(vertexSize, std::vector<Edge>()) {}

    void AddEdge(const int_t &from, const int_t &to, const int_t &weight) {
        adjacencyList[from].push_back(Edge(to, weight));
        adjacencyList[to].push_back(Edge(from, weight));
    }

    std::vector<int_t> Dijkstra(const Vertex &start) {
        std::vector<int_t> distances(vertexSize, INF);
        std::vector<bool> used(vertexSize, false);
        std::vector<Vertex> parents(vertexSize, -1);
        std::set<std::pair<int_t, int_t>, Cmp> queueDijkstra;
        distances[start] = 0;
        queueDijkstra.insert({distances[start], start});
        for (int_t i = 0; i < vertexSize && !queueDijkstra.empty(); ++i) {
            auto pair = *queueDijkstra.begin();
            queueDijkstra.erase(pair);
            Vertex minVertex = pair.second;
            while (used[minVertex] && !queueDijkstra.empty()) {
                auto pair = *queueDijkstra.begin();
                queueDijkstra.erase(pair);
                minVertex = pair.second;
            }
            used[minVertex] = true;
            for (const auto &neighbour : adjacencyList[minVertex]) {
                if (!used[neighbour.to] && distances[neighbour.to] > distances[minVertex] + neighbour.weight) {
                    distances[neighbour.to] = distances[minVertex] + neighbour.weight;
                    parents[neighbour.to] = minVertex;
                    queueDijkstra.insert({distances[neighbour.to], neighbour.to});
                }
            }
        }
        return distances;
    }

};


int main() {
    int_t numberOfCountries = 0,
            numberOfLines = 0,
            numberOfInfectedCountries = 0;
    std::cin >> numberOfCountries >> numberOfLines >> numberOfInfectedCountries;
    Graph graph(numberOfCountries);
    std::vector<Vertex> infectedCountries;
    int_t indexOfInfectedCountry;
    for (int_t i = 0; i < numberOfInfectedCountries; ++i) {
        std::cin >> indexOfInfectedCountry;
        infectedCountries.push_back(indexOfInfectedCountry - 1);
    }
    Vertex from, to;
    int_t weight;
    for (int_t i = 0; i < numberOfLines; ++i) {
        std::cin >> from >> to >> weight;
        graph.AddEdge(from - 1, to - 1, weight);
    }
    Vertex start, end;
    std::cin >> start >> end;
    --start;
    --end;
    std::vector<int_t> distances = graph.Dijkstra(end);

    int_t minAmongTheInfected = INF;
    for (const auto &infected : infectedCountries) {
        if (distances[infected] < minAmongTheInfected) {
            minAmongTheInfected = distances[infected];
        }
    }

    if (minAmongTheInfected <= distances[start] || distances[start] == INF) {
        std::cout << -1 << '\n';
        return 0;
    } else {
        std::cout << distances[start] << '\n';
    }


    return 0;
}






