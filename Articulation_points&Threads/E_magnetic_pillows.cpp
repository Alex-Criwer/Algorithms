/* Город будущего застроен небоскребами, для передвижения между которыми и
 * парковки транспорта многие тройки небоскребов соединены треугольной подушкой
 * из однополярных магнитов. Каждая подушка соединяет ровно 3 небоскреба и вид
 * сверху на нее представляет собой треугольник, с вершинами в небоскребах.
 * Это позволяет беспрепятственно передвигаться между соответствующими небоскребами.
 * Подушки можно делать на разных уровнях, поэтому один небоскреб может быть
 * соединен различными подушками с парами других, причем два небоскреба могут
 * соединять несколько подушек (как с разными третьими небоскребами, так и с одинаковым).
 * Например, возможны две подушки на разных уровнях между небоскребами 1, 2 и 3, и,
 * кроме того, магнитная подушка между 1, 2, 5.
Система магнитных подушек организована так, что с их помощью можно добираться от одного
 небоскреба, до любого другого в этом городе (с одной подушки на другую можно
 перемещаться внутри небоскреба), но поддержание каждой из них требует больших затрат энергии.
Требуется написать программу, которая определит, какие из магнитных подушек нельзя удалять
 из подушечной системы города, так как удаление даже только этой подушки может привести
 к тому, что найдутся небоскребы из которых теперь нельзя добраться до некоторых других
 небоскребов, и жителям станет очень грустно.
*/

#include <iostream>
#include <set>
#include <vector>
#include <algorithm>

const size_t minNumberOfChildren = 2;

enum Colors {
    WHITE,
    GRAY,
    BLACK
};

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
    };

    int vertexSize = 0;
    std::vector<std::vector<Edge>> adjacencyList;

public:

    explicit Graph(const int &vertexSize) : vertexSize(vertexSize),
                                            adjacencyList(vertexSize, std::vector<Edge>()) {}

    void AddEdge(const int &from, const int &to) {
        adjacencyList[from].push_back(Edge(to));
        adjacencyList[to].push_back(Edge(from));
    }

    std::set<int> CutVertexes() {
        std::vector<Colors> colors(vertexSize, Colors::WHITE);
        std::vector<int> tIn(vertexSize);
        std::vector<int> fUp(vertexSize);
        size_t time = 0;
        std::set<int> cutVertexes;
        for (int i = 0; i < vertexSize; ++i) {
            if (colors[i] == Colors::WHITE) {
                DfsVisit(Vertex(i), Vertex(-1), time, colors, tIn, fUp, cutVertexes);
            }
        }
        return cutVertexes;
    }

    void DfsVisit(Vertex start, Vertex parent, size_t &time, std::vector<Colors> &colors,
                  std::vector<int> &tIn, std::vector<int> &fUp, std::set<int> &cutVertexes) {
        ++time;
        tIn[start.index] = time;
        fUp[start.index] = time;
        colors[start.index] = Colors::GRAY;
        int counterOfChildren = 0;
        for (auto &neighbour : adjacencyList[start.index]) {
            if (neighbour.to == parent) {
                continue;
            }
            if (colors[neighbour.to.index] == Colors::WHITE) {
                DfsVisit(neighbour.to, start, time, colors, tIn, fUp, cutVertexes);
                fUp[start.index] = std::min(fUp[start.index], fUp[neighbour.to.index]);
                if (parent.index != -1 && fUp[neighbour.to.index] >= tIn[start.index]) {
                    cutVertexes.insert(start.index);
                }
                ++counterOfChildren;
            }
            if (colors[neighbour.to.index] == Colors::GRAY) {
                fUp[start.index] = std::min(fUp[start.index], tIn[neighbour.to.index]);
            }
        }
        if (parent.index == -1) {
            if (counterOfChildren >= minNumberOfChildren) {
                cutVertexes.insert(start.index);
            }
        }
        colors[start.index] = Colors::BLACK;
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    size_t numberOfSkyscrapers = 0;
    size_t numberOfMagneticPillows = 0;
    std::cin >> numberOfSkyscrapers >> numberOfMagneticPillows;
    Graph graph(numberOfSkyscrapers + numberOfMagneticPillows);
    for (int i = 0; i < numberOfMagneticPillows; ++i) {
        int firstScraper, secondScraper, thirdScraper;
        std::cin >> firstScraper >> secondScraper >> thirdScraper;
        graph.AddEdge(i, firstScraper - 1 + numberOfMagneticPillows);
        graph.AddEdge(i, secondScraper - 1 + numberOfMagneticPillows);
        graph.AddEdge(i, thirdScraper - 1 + numberOfMagneticPillows);
    }
    std::set<int> cutVertexes = graph.CutVertexes();
    cutVertexes.erase(std::upper_bound(std::begin(cutVertexes), std::end(cutVertexes), numberOfMagneticPillows - 1),
                           std::end(cutVertexes));
    std::cout << cutVertexes.size() << '\n';
    for (const auto &vertex : cutVertexes) {
        std::cout << vertex + 1 << '\n';
    }
    return 0;
}
