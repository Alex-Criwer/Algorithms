/*Шел 2100-й год. Физтех стал огромным ВУЗом, состоящим из большого множества корпусов
 * и гипертонеллей в качестве переходов между ними. Отныне до Тимирязевской (как и от
 * любого другого корпуса) можно добраться за 5 минут от общежития (или любого другого
 * здания университета) с помощью гиперлупов (напрямую или с пересадочными станциями в каждом корпусе).
К сожалению, иногда переходы могут быть обесточены во время проведения ремонтных работ, а значит
 перемещаться по ним нельзя. Нужно выяснить, сколько гипертоннелей для гиперлупов надо построить,
 чтобы при неисправности любого из переходов физтех оставался связным.
Учитывая то, что систему разрабатывали самые лучшие ученые страны, в ней нет бессмысленных кратных ребер и петель.*/

#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
#include <unordered_set>

typedef int Vertex;

enum Colors {
    WHITE,
    GRAY,
    BLACK
};

class Graph {
public:
    struct Edge {
        Vertex from;
        Vertex to;

        explicit Edge(const int &index) : to(index) {}

        explicit Edge(const int &from, const int &to) : from(from), to(to) {}

        bool operator<(const Edge &other) const {
            return std::pair<int, int>(from, to) < std::pair<int, int>(other.from, other.to);
        }

        bool operator==(const Edge &other) const {
            return from == other.from && to == other.to;
        }
    };

    class Hash {
        const int kPrimeNumber = 2000000011;
        const int kPrime = 131;
    public:
        int operator()(const Edge &edge) const {
            return (kPrime * edge.from + edge.to) % kPrimeNumber;
        }
    };


private:
    int vertexSize = 0;
    std::vector<std::vector<Edge>> adjacencyList;

public:

    explicit Graph(const int &vertexSize) : vertexSize(vertexSize),
                                            adjacencyList(vertexSize, std::vector<Edge>()) {}

    void AddEdge(const int &from, const int &to) {
        adjacencyList[from].push_back(Edge(to));
        adjacencyList[to].push_back(Edge(from));
    }

    size_t getDegree(const int &vertex) {
        return adjacencyList[vertex].size();
    }

    std::unordered_set<Edge, Hash> getBridges() {
        std::vector<Colors> colors(vertexSize, Colors::WHITE);
        std::vector<int> tIn(vertexSize);
        std::vector<int> fUp(vertexSize);
        std::vector<int> answer;
        std::unordered_set<Edge, Hash> bridges;
        size_t time = 0;
        for (int i = 0; i < vertexSize; ++i) {
            if (colors[i] == Colors::WHITE) {
                DfsVisit(Vertex(i), Vertex(-1), time, colors, tIn, fUp, bridges);
            }
        }
        return bridges;
    }

    void DfsVisit(Vertex start, Vertex parent, size_t &time, std::vector<Colors> &colors,
                  std::vector<int> &tIn, std::vector<int> &fUp, std::unordered_set<Edge, Hash> &bridges) {
        ++time;
        tIn[start] = time;
        fUp[start] = time;
        colors[start] = Colors::GRAY;
        for (auto &neighbour : adjacencyList[start]) {
            if (neighbour.to == parent) {
                continue;
            }
            if (colors[neighbour.to] == Colors::WHITE) {
                DfsVisit(neighbour.to, start, time, colors, tIn, fUp, bridges);
                fUp[start] = std::min(fUp[start], fUp[neighbour.to]);
                if (fUp[neighbour.to] > tIn[start]) {
                    bridges.insert(Edge(start, neighbour.to));
                }
            }
            if (colors[neighbour.to] == Colors::GRAY) {
                fUp[start] = std::min(fUp[start], tIn[neighbour.to]);
            }
        }
        colors[start] = Colors::BLACK;
    }

    void DfsVisitComponent(Vertex start, const size_t &numberOfDisconnectedComponents,
                           std::vector<Colors> &colors, const std::unordered_set<Edge, Hash> &bridges,
                           std::vector<std::unordered_set<Vertex>> &components) {
        colors[start] = Colors::GRAY;
        components[numberOfDisconnectedComponents].insert(start);
        for (const auto &neighbour : adjacencyList[start]) {
            if (colors[neighbour.to] == Colors::WHITE) {
                if (bridges.find(Edge(start, neighbour.to)) == bridges.end() &&
                    bridges.find(Edge(neighbour.to, start)) == bridges.end()) {
                    DfsVisitComponent(neighbour.to, numberOfDisconnectedComponents, colors, bridges, components);
                } else {
                    components.emplace_back();
                    DfsVisitComponent(neighbour.to, components.size() - 1, colors, bridges, components);
                }
            }
            colors[start] = Colors::BLACK;
        }
    }

    std::vector<std::unordered_set<Vertex>> getComponents(const std::unordered_set<Edge, Hash> &bridges) {
        size_t numberOfDisconnectedComponents = 0;
        std::vector<std::unordered_set<Vertex>> components;
        std::vector<Colors> colors(vertexSize, Colors::WHITE);
        for (int i = 0; i < vertexSize; ++i) {
            if (colors[i] == Colors::WHITE) {
                numberOfDisconnectedComponents = components.size();
                components.emplace_back();
                DfsVisitComponent(Vertex(i), numberOfDisconnectedComponents, colors, bridges, components);
            }
        }
        return components;
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    size_t vertexSize = 0;
    size_t edgeSize = 0;
    size_t numberOfLists = 0;
    std::cin >> vertexSize >> edgeSize;
    Graph graph(vertexSize);
    for (int i = 0; i < edgeSize; ++i) {
        int from, to;
        std::cin >> from >> to;
        graph.AddEdge(from - 1, to - 1);
    }
    std::unordered_set<Graph::Edge, Graph::Hash> bridges = graph.getBridges();
    std::vector<std::unordered_set<Vertex>> components = graph.getComponents(bridges);
    Graph connected(components.size());
    Vertex beginComponent, endComponent;
    for (const auto &bridge : bridges) {
        for (int i = 0; i < components.size(); ++i) {
            if (components[i].find(bridge.from) != components[i].end()) {
                beginComponent = i;
            } else if (components[i].find(bridge.to) != components[i].end()) {
                endComponent = i;
            }
        }
        connected.AddEdge(beginComponent, endComponent);
    }

    for (int i = 0; i < components.size(); ++i) {
        if (connected.getDegree(i) == 1) {
            ++numberOfLists;
        }
    }

    std::cout << (numberOfLists + 1) / 2 << '\n';
    return 0;
}
