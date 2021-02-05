#include <iostream>
#include <vector>
#include <limits>
#include <deque>
#include <set>
#include <queue>

typedef int Vertex;

constexpr int INF = std::numeric_limits<int>::max();

constexpr int THERE_IS_EDGE = 1;

constexpr int THERE_IS_NO_EDGE = 0;

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

    void Floyd_Warshall( std::vector<std::vector<int>> &matrix) {
        for (int k = 0; k < vertexSize; ++k) {
            for (int i = 0; i < vertexSize; ++i) {
                for (int j = 0; j < vertexSize; ++j) {
                    if(matrix[i][k] != INF && matrix[k][j] != INF) {
                        matrix[i][j] = std::min(matrix[i][j], matrix[i][k] + matrix[k][j]);
                    }
                }
            }
        }
    }
};


int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    size_t vertexSize = 0;
    std::cin >> vertexSize;
    Graph graph(vertexSize);
    std::vector<std::vector<int>> matrix(vertexSize, std::vector<int>(vertexSize));
    int weight = 0;
    for (int i = 0; i < vertexSize; ++i) {
        for (int j = 0; j < vertexSize; ++j) {
            std::cin >> weight;
            if (weight == THERE_IS_EDGE) {
                matrix[i][j] = weight;        //initialisation of matrix
            } else {
                matrix[i][j] = INF;
            }
        }
    }

    graph.Floyd_Warshall(matrix);

    for (int i = 0; i < vertexSize; ++i) {
        for (int j = 0; j < vertexSize; ++j) {
            if (matrix[i][j] == INF) {
                std::cout << THERE_IS_NO_EDGE << " ";
            } else {
                std::cout << THERE_IS_EDGE << " ";
            }
        }
        std::cout << '\n';
    }

    return 0;
}





