/* В Байтландии есть целых n городов, но нет ни одной дороги.
 * Король страны, Вальдемар де Беар, решил исправить эту ситуацию и соединить некоторые города дорогами так,
 * чтобы по этим дорогам можно было добраться от любого города до любого другого. Когда строительство будет завершено,
 * король планирует отпраздновать День Объединения.
 * К сожалению, казна Байтландии почти пуста, поэтому король требует сэкономить деньги,
 * минимизировав суммарную длину всех построенных дорог.
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include <math.h>

const int INF = std::numeric_limits<int>::max();

double distance(const int &firstX, const int &firstY, const int &secondX, const int &secondY) {
    return sqrt((secondX - firstX) * (secondX - firstX) + (secondY - firstY) * (secondY - firstY));
}

class Graph {
    struct Vertex {
        int index;

        Vertex() = default;

        explicit Vertex(const int &index) : index(index) {}

        bool operator==(const Vertex &other) const {
            return index == other.index;
        }
    };

    struct Edge {
        Vertex to;

        explicit Edge(const int &index) : to(index) {}

        bool operator==(const Edge &other) const {
            return to == other.to;
        }
    };

    int vertexSize = 0;
    std::vector<std::vector<Edge>> adjacencyList;

public:

    explicit Graph(const int &vertexSize) : vertexSize(vertexSize),
                                            adjacencyList(vertexSize, std::vector<Edge>()) {}


    void AddEdge(const int &from, const int &to, const size_t) {
        adjacencyList[from].push_back(Edge(to));
        adjacencyList[to].push_back(Edge(from));
    }

    double PrimsMST() {
        int x, y;
        std::vector<int> coordinatesX(vertexSize);
        std::vector<int> coordinatesY(vertexSize);
        for (int i = 0; i < vertexSize; ++i) {
            std::cin >> x >> y;
            coordinatesX[i] = x;
            coordinatesY[i] = y;
        }

        double minRoadLength = 0.0;
        std::vector<bool> used(vertexSize, false);
        std::vector<int> parents(vertexSize, -1);
        std::vector<double> distances(vertexSize, INF);
        distances[0] = 0;
        for (int i = 0; i < vertexSize; ++i) {
            int minVertex = -1;
            for (int j = 0; j < vertexSize; ++j) {
                if (!used[j] && (minVertex == -1 || distances[j] < distances[minVertex])) {
                    minVertex = j;
                }
            }
            used[minVertex] = true;
            if (parents[minVertex] != -1) {
                minRoadLength += distance(coordinatesX[minVertex], coordinatesY[minVertex],
                                          coordinatesX[parents[minVertex]], coordinatesY[parents[minVertex]]);
            }
            for (int neighbour = 0; neighbour < vertexSize; ++neighbour) {
                double weight = distance(coordinatesX[minVertex], coordinatesY[minVertex],
                                         coordinatesX[neighbour], coordinatesY[neighbour]);
                if (!used[neighbour] && weight < distances[neighbour]) {
                    distances[neighbour] = weight;
                    parents[neighbour] = minVertex;
                }
            }
        }

        return minRoadLength;
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    size_t vertexSize = 0;
    std::cin >> vertexSize;
    Graph graph(vertexSize);
    printf("%.7f", graph.PrimsMST());
    return 0;
}