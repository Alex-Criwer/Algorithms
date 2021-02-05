#include <iostream>
#include <vector>
#include <limits>
#include <deque>
#include <set>
#include <queue>

typedef int Vertex;

constexpr int INF = std::numeric_limits<int>::max();

constexpr int ERROR = -1;


class Graph {

    struct Edge {
        Vertex to;
        int weight;

        explicit Edge(const int &index, const int &weight) : to(index), weight(weight) {}
    };

    size_t vertexSize = 0;
    std::vector<std::vector<Edge>> adjacencyList;
    std::vector<std::vector<int>> weights;
public:

    explicit Graph(const int &vertexSize) : vertexSize(vertexSize),
                                            adjacencyList(vertexSize, std::vector<Edge>()),
                                            weights(vertexSize, std::vector<int>(vertexSize, INF)) {}

    void AddEdge(const int &from, const int &to, const int &weight) {
        adjacencyList[from].push_back(Edge(to, weight));
        weights[from][to] = weight;
    }

    int Dijkstra(const Vertex &start, const Vertex &end) {
        std::vector<int> distances(vertexSize, INF);
        std::vector<bool> used(vertexSize, false);
        for (int i = 0; i < vertexSize; ++i) {
            distances[i] = weights[start][i];
        }
        distances[start] = 0;
        int index = 0;
        Vertex vertex = 0;
        for (int i = 0; i < vertexSize; ++i) {
            index = 0;
            int min = INF;
            for (int j = 0; j < vertexSize; ++j) {
                if (!used[j] && distances[j] < min) {
                    min = distances[j];
                    index = j;
                }
            }
            vertex = index;
            used[vertex] = true;
            for (const auto &neighbour : adjacencyList[vertex]) {
                if (!used[neighbour.to] && distances[vertex] != INF &&
                    distances[neighbour.to] > neighbour.weight + distances[vertex]) {
                    distances[neighbour.to] = neighbour.weight + distances[vertex];
                }
            }

        }
        if (distances[end] == INF) {
            return ERROR;
        }
        return distances[end];
    }

};


int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    size_t vertexSize = 0, start, end;
    std::cin >> vertexSize >> start >> end;
    Graph graph(vertexSize);
    int weight = 0;
    for (int i = 0; i < vertexSize; ++i) {
        for (int j = 0; j < vertexSize; ++j) {
            std::cin >> weight;
            if (weight != ERROR && i != j) {
                graph.AddEdge(i, j, weight);
            }
        }
    }
    int distance = graph.Dijkstra(start - 1, end - 1);
    std::cout << distance << '\n';
    return 0;
}





