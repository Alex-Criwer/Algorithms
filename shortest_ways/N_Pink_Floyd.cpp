#include <iostream>
#include <vector>
#include <limits>
#include <deque>
#include <set>
#include <queue>

typedef int Vertex;

constexpr int INF = std::numeric_limits<int>::max();

constexpr int NO_PARENT = -1;

constexpr int THERE_IS_NO_EDGE = -1;

struct Pair {
    int weight;
    int numberOfEdge;
};

class Graph {

    struct Edge {
        Vertex to;
        int weight;

        explicit Edge(const int &index, const int &weight) : to(index), weight(weight) {}
    };

    size_t vertexSize = 0;
    std::vector<std::vector<int>> weights;
public:

    explicit Graph(const int &vertexSize) : vertexSize(vertexSize),
                                            weights(vertexSize, std::vector<int>(vertexSize, INF)) {}

    void AddEdge(const int &from, const int &to, const int &weight) {
        weights[from][to] = weight;
    }

    std::vector<std::vector<int>>
    Floyd_Warshall(std::vector<std::vector<Pair>> &matrix, std::vector<std::vector<Vertex>> &parents) {

        std::vector<std::vector<int>> minLength(vertexSize, std::vector<int>(vertexSize, INF));

        for (int i = 0; i < vertexSize; ++i) {
            for (int j = 0; j < vertexSize; ++j) {
                minLength[i][j] = matrix[i][j].weight;
            }
        }

        for (int k = 0; k < vertexSize; ++k) {
            for (int i = 0; i < vertexSize; ++i) {
                for (int j = 0; j < vertexSize; ++j) {
                    if (minLength[i][k] != INF && minLength[k][j] != INF) {
                        if (minLength[i][j] > minLength[i][k] + minLength[k][j]) {
                            minLength[i][j] = minLength[i][k] + minLength[k][j];
                            parents[i][j] = k;
                        }
                    }
                }
            }
        }

        for (int k = 0; k < vertexSize; ++k) {
            for (int i = 0; i < vertexSize; ++i) {
                for (int j = 0; j < vertexSize; ++j) {
                    if (minLength[i][k] != INF && minLength[k][j] != INF && minLength[k][k] < 0) {
                        minLength[i][j] = -INF;
                    }
                }
            }
        }
        return minLength;
    }

    void
    getPath(std::vector<std::vector<Pair>> &matrix, std::vector<std::vector<Vertex>> &parents, std::vector<int> &path,
            const Vertex &from, const Vertex &to) {
        if (parents[from][to] == NO_PARENT) {
            path.push_back(matrix[from][to].numberOfEdge);
            return;
        }
        getPath(matrix, parents, path, from, parents[from][to]);
        getPath(matrix, parents, path, parents[from][to], to);
    }

};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    size_t numberOfCities = 0, numberOfRays = 0, numberOfConcerts = 0;
    std::cin >> numberOfCities >> numberOfRays >> numberOfConcerts;
    Graph graph(numberOfCities);
    Vertex from, to;
    int weight = 0;
    std::vector<std::vector<Pair>> matrix(numberOfCities, std::vector<Pair>(numberOfCities, {INF, 0}));
    std::vector<std::vector<int>> parents(numberOfCities, std::vector<int>(numberOfCities, NO_PARENT));
    for (int i = 0; i < numberOfRays; ++i) {
        std::cin >> from >> to >> weight;
        if (matrix[from - 1][to - 1].weight > -weight) {
            matrix[from - 1][to - 1].weight = -weight;
            if (to == from && weight > 0) {
                matrix[from - 1][to - 1].weight = -INF;
            }
            matrix[from - 1][to - 1].numberOfEdge = i + 1;
        }
    }

    std::vector<std::vector<int>> minDistances = graph.Floyd_Warshall(matrix, parents);

    bool isNegativeCycle = false;
    Vertex currentCity, nextCity;
    std::vector<int> path;
    std::cin >> currentCity;
    for (int i = 0; i < numberOfConcerts - 1; ++i) {
        std::cin >> nextCity;
        if (minDistances[currentCity - 1][nextCity - 1] == -INF) {
            isNegativeCycle = true;
            break;
        }
        graph.getPath(matrix, parents, path, currentCity - 1, nextCity - 1);
        currentCity = nextCity;
    }

    if (isNegativeCycle) {
        std::cout << "infinitely kind";
        return 0;
    }
    std::cout << path.size() << '\n';
    for (int i = 0; i < path.size(); ++i) {
        std::cout << path[i] << ' ';
    }

    return 0;
}





