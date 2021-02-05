/* Для решения транспортной проблемы в некотором городе до недавнего времени использовались N автобусных маршрутов. Каждый маршрут начинался на одной из M площадей и там же заканчивался. В процессе проезда по маршруту автобус мог несколько раз проезжать одну и ту же площадь, и даже мог проезжать более одного раза по одной и той же улице в одном и том же направлении. В определенный момент местные власти решили сократить количество автобусных маршрутов в городе до одного. По их мнению, должен был остаться лишь один маршрут, который проходил бы по всем улицам, по которым раньше проходили автобусные маршруты, причем в том же направлении (но не обязательно в том же порядке). Если по каким-либо улицам автобусы ездили в обоих направлениях, то и новый маршрут должен проходить по этим улицам в обоих направлениях. По тем улицам и в тех направлениях, по которым раньше автобусы не ездили, новый маршрут проходить не должен. Однако так как контролеров увольнять нельзя, власти решили, что по каждой улице в каждом направлении новый маршрут должен проходить столько раз, сколько по ней проходили все старые маршруты, вместе взятые. Требуется написать программу, которая для заданных исходных данных определяет требуемый местным властям автобусный маршрут.
*/

#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
#include <unordered_map>

typedef int Vertex;

class Graph {

    struct Edge {
        Vertex to;

        explicit Edge(const int &to) : to(to) {}

        bool operator==(const Edge &other) const {
            return to == other.to;
        }
    };

    int vertexSize = 0;
    int edgeSize = 0;
    std::vector<std::unordered_map<Vertex, int>> adjacencyList; //numberOfEdgesBetweenThem

public:

    explicit Graph(const int &vertexSize) : vertexSize(vertexSize), adjacencyList(vertexSize) {}

    void AddEdge(const int &from, const int &to) {
        ++adjacencyList[from][to];
        ++edgeSize;
    }

    void EulerCycle(const Vertex &vertex, std::vector<Vertex> &answer) {
        const auto &neighbours = adjacencyList[vertex];
        for (auto iter = neighbours.begin(); iter != neighbours.end(); ++iter) {
            while (iter->second > 0) {
                deleteEdge(vertex, iter->first);
                EulerCycle(iter->first, answer);
            }
        }
        answer.push_back(vertex);
    }

    void deleteEdge(const Vertex &from, const Vertex &to) {
        auto iter = adjacencyList[from].find(to);
        if (iter != adjacencyList[from].end() && iter->second > 0) {
            --iter->second;
            --edgeSize;
        }
    }

    std::vector<Vertex> Cycle() {
        std::vector<Vertex> answer;
        size_t numberOfEdges = edgeSize;
        for (int vertex = 0; vertex < vertexSize; ++vertex) {
            EulerCycle(vertex, answer);
            if (answer.size() != 1) {
                break;
            } else {
                answer.clear();
            }
        }

        if (answer.size() != numberOfEdges + 1) {
            return {};
        }
        return answer;
    }


};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    size_t numberOfBusWays = 0;
    size_t numberOfSquares = 0;
    std::cin >> numberOfBusWays >> numberOfSquares;
    Graph graph(numberOfSquares);
    for (int i = 0; i < numberOfBusWays; ++i) {
        int numberOfElements;
        Vertex from, to;
        std::cin >> numberOfElements;
        std::cin >> from;
        for (int j = 0; j < numberOfElements; ++j) {
            std::cin >> to;
            graph.AddEdge(from - 1, to - 1);
            from = to;
        }
    }
    std::vector<Vertex> answer = graph.Cycle();
    if (answer.empty()) {
        std::cout << 0 << '\n';
    } else {
        std::cout << answer.size() << " ";
        for (auto iter = answer.rbegin(); iter != answer.rend(); ++iter) {
            std::cout << *iter + 1 << " ";
        }
    }
    return 0;
}

