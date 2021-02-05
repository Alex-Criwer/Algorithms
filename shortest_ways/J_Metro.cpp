#include <iostream>
#include <vector>
#include <limits>
#include <deque>
#include <set>
#include <algorithm>

typedef long long Vertex;

constexpr long long INF = 1e18;

constexpr long long NO_PATH = -1;

constexpr long long NO_PARENT = -1;

struct Pair {
    long long distance;
    Vertex vertex;
    long long timeFromStart;
};

struct PairForParents {
    Vertex index;
    long long timeOfEdge;
};

class Cmp {
public:
    bool operator()(const Pair &lhs, const Pair &rhs) const {
        if (lhs.distance != rhs.distance) {
            return lhs.distance < rhs.distance;
        }
        if (lhs.vertex != rhs.vertex) {
            return lhs.vertex < rhs.vertex;
        }
        return lhs.timeFromStart < rhs.timeFromStart;
    }
};

class Graph {

    struct Edge {
        Vertex to;
        Vertex from;
        long long weight;
        long long time;

        explicit Edge(const long long &from, const long long &to, const long long &weight, const long long &time) : from(from), to(to),
                                                                                            weight(weight),
                                                                                            time(time) {}
    };

    long long vertexSize = 0;
    std::vector<std::vector<Edge>> adjacencyList;

public:

    explicit Graph(const long long &vertexSize) : vertexSize(vertexSize),
                                            adjacencyList(vertexSize, std::vector<Edge>()) {}

    void AddEdge(const long long &from, const long long &to, const long long &weight, const long long &time) {
        adjacencyList[from].push_back(Edge(from, to, weight, time));
        adjacencyList[to].push_back(Edge(to, from, weight, time));
    }

    void Dijkstra(const Vertex &start, const long long &maxTime) {
        std::vector<std::vector<long long>> distances(vertexSize, std::vector<long long>(maxTime + 1, INF));
        std::vector<std::vector<bool>> used(vertexSize, std::vector<bool>(maxTime + 1, false));
        std::vector<std::vector<PairForParents>> parents(vertexSize,
                                                         std::vector<PairForParents>(maxTime + 1, {-1, -1}));
        std::set<Pair, Cmp> queueDijkstra;
        distances[start][0] = 0;
        queueDijkstra.insert({distances[start][0], start, 0});

        while (!queueDijkstra.empty()) {
            auto pair = *queueDijkstra.begin();
            queueDijkstra.erase(pair);
            Vertex minVertex = pair.vertex;
            Vertex currentTime = pair.timeFromStart;
            while (used[minVertex][currentTime] && !queueDijkstra.empty()) {
                auto pair = *queueDijkstra.begin();
                queueDijkstra.erase(pair);
                minVertex = pair.vertex;
            }
            used[minVertex][currentTime] = true;
            for (const auto &neighbour : adjacencyList[minVertex]) {
                if (!used[neighbour.to][currentTime] && distances[neighbour.to][currentTime + neighbour.time] >
                                                        distances[minVertex][currentTime] + neighbour.weight &&
                    currentTime + neighbour.time <= maxTime) {
                    distances[neighbour.to][currentTime + neighbour.time] =
                            distances[minVertex][pair.timeFromStart] + neighbour.weight;
                    parents[neighbour.to][currentTime + neighbour.time] = {minVertex, currentTime};
                    queueDijkstra.insert({distances[neighbour.to][currentTime + neighbour.time], neighbour.to,
                                          currentTime + neighbour.time});
                }
            }
        }

        long long minDistance = INF;
        long long indexOfMin = -1;
        for (long long i = 0; i < maxTime + 1; ++i) {
            if (distances[vertexSize - 1][i] < minDistance) {
                minDistance = distances[vertexSize - 1][i];
                indexOfMin = i;
            }
        }

        if (indexOfMin == NO_PATH) {
            std::cout << NO_PATH;
            return;
        }

        std::cout << minDistance << '\n';
        std::vector<Vertex> pathOfParents;
        PairForParents current{vertexSize - 1, indexOfMin};
        while (current.index != -1) {
            pathOfParents.push_back(current.index);
            current = parents[current.index][current.timeOfEdge];
        }
        std::cout << pathOfParents.size() << '\n';
        std::reverse(pathOfParents.begin(), pathOfParents.end());
        for (long long i = 0; i < pathOfParents.size(); ++i) {
            std::cout << pathOfParents[i] + 1 << ' ';
        }

    }

};


int main() {
    long long vertexSize = 0, edgeSize = 0;
    long long maxTime = 0;
    std::cin >> vertexSize >> edgeSize >> maxTime;
    Graph graph(vertexSize);
    long long from, to, weight, time;
    for (long long i = 0; i < edgeSize; ++i) {
        std::cin >> from >> to >> weight >> time;
        graph.AddEdge(from - 1, to - 1, weight, time);
    }
    Vertex start = 0;
    graph.Dijkstra(start, maxTime);
    return 0;
}




