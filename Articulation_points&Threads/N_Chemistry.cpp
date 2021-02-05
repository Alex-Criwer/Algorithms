/* Вася и Сережа играют в следующую игру. В некоторых клетках клетчатого листка Сережа рисует один из символов H, O, N или C, после чего Вася должен провести между некоторыми находящимися в соседних клетках символами линии так, чтобы получилось корректное изображение химической молекулы. К сожалению, Сережа любит рисовать много символов, и Вася не может сразу определить, возможно ли вообще нарисовать линии нужным способом. Помогите ему написать программу, которая даст ответ на этот вопрос.

В этой задаче проведенные между символами химических элементов линии будем считать корректным изображением молекулы, если они удовлетворяют следующим условиям:

каждая линия соединяет символы, нарисованные в соседних (по стороне) клетках;
между каждой парой символов проведено не более одной линии;
от каждого элемента отходит ровно столько линий, какова валентность этого элемента (1 для H, 2 для O, 3 для N, 4 для C);
пустые клетки ни с чем не соединены;
хотя бы в одной клетке нарисован какой-то символ.
*/

#include <iostream>
#include <vector>
#include <algorithm>

#define DEBUG

#ifdef DEBUG
#define _debug (exrp) expr
#else
#define _debug (expr)
#endif

typedef int Vertex;

class Graph {

    struct Edge {
        Vertex from;
        Vertex to;
        int capacity;
        int flow;

        explicit Edge(const int &index) : to(index) {}

        explicit Edge(const int &from, const int &to, const int &capacity, const int &flow) : from(from), to(to),
                                                                                              capacity(capacity),
                                                                                              flow(flow) {}
    };

    int vertexSize = 0;
    int edgeSize = 0;
    std::vector<std::vector<int>> adjacencyList;
    std::vector<Edge> edges;
    static constexpr int MAX_CAPACITY = 100000000;

public:

    explicit Graph(const int &vertexSize) : vertexSize(vertexSize),
                                            adjacencyList(vertexSize, std::vector<int>()) {}

    void AddEdge(const int &from, const int &to, const int &capacity) {
        adjacencyList[from].push_back(edgeSize);
        adjacencyList[to].push_back(edgeSize ^ 1);
        edgeSize += 2;
        edges.emplace_back(from, to, capacity, 0);
        edges.emplace_back(to, from, 0, 0);
    }

    int maxFlow(const int &from, const int &to) {
        int myMaxFlow = 0;
        std::vector<bool> used(vertexSize, false);
        while (true) {
            used.assign(vertexSize, false);
            if (fordFulkerson(from, to, MAX_CAPACITY, used) == 0) {
                break;
            }
        }
        for (const auto &numberOfEdge : adjacencyList[0]) {
            myMaxFlow += edges[numberOfEdge].flow;
        }
        return myMaxFlow;
    }

    int fordFulkerson(const int &currentVertex, const int &endVertex, const int &flow, std::vector<bool> &used) {
        if (currentVertex == endVertex) {
            return flow;
        }
        used[currentVertex] = true;
        for (const auto &neighbour : adjacencyList[currentVertex]) {
            auto &currEdge = edges[neighbour];
            if (!used[currEdge.to] && currEdge.flow < currEdge.capacity) {
                int delta = fordFulkerson(currEdge.to, endVertex, std::min(flow, currEdge.capacity - currEdge.flow),
                                          used);
                if (delta > 0) {
                    currEdge.flow += delta;
                    edges[neighbour ^ 1].flow -= delta;
                    return delta;
                }
            }
        }
        return 0;
    }
};

int elementValence(const char& element) {
    if (element == 'H') {
        return 1;
    } else if (element == 'O') {
        return 2;
    } else if (element == 'N') {
        return 3;
    } else if (element == 'C') {
        return 4;
    }
    return 0;
}


int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    int width = 0, height = 0;
    std::cin >> height >> width;
    std::vector<std::vector<char>> table(height, std::vector<char>(width));
    char element;
    bool empty = true;
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            std::cin >> element;
            table[i][j] = element;
            if (element != '.') {
                empty = false;
            }
        }
    }
    if (empty) {
        std::cout << "Invalid" << '\n';
        return 0;
    }
    int flowOut = 0, flowIn = 0;
    int vertexSize = width * height + 2;
    Graph graph(vertexSize);
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
           int currentVertex = i * width + j + 1;
           if((i % 2 == 1 && j % 2 == 1) || ((i % 2 == 0 && j % 2 == 0))) {
               flowOut += elementValence(table[i][j]);
               graph.AddEdge(0, currentVertex, elementValence(table[i][j]));
               if (i > 0) {
                   graph.AddEdge(currentVertex, width * (i - 1) + j + 1, 1);
               }
               if (i < height - 1) {
                   graph.AddEdge(currentVertex, width * (i + 1) + j + 1, 1);
               }
               if (j > 0) {
                   graph.AddEdge(currentVertex, width * i + (j - 1) + 1, 1);
               }
               if (j < width - 1) {
                   graph.AddEdge(currentVertex, width * i + (j + 1) + 1, 1);
               }

           } else {
               flowIn += elementValence(table[i][j]);
               graph.AddEdge(currentVertex, vertexSize - 1, elementValence(table[i][j]));
           }
        }
    }
    int maxFlow = graph.maxFlow(0, vertexSize - 1);
    if (flowOut == maxFlow && flowIn == maxFlow) {
        std::cout << "Valid" << '\n';
    } else {
        std::cout << "Invalid" << '\n';
    }

    return 0;
}
