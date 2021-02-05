#include <iostream>
#include <vector>
#include <deque>

using Vertex = int;

enum Colors {
    WHITE,
    GRAY,
    BLACK
};

class AbstractVisitor {
public:
    virtual void startVertex() = 0;

    virtual void discoverVertex(const Vertex &vertex) = 0;

    virtual std::deque<Vertex> getOrderOfVertex() = 0;

    virtual void finishVertex(const Vertex &vertex) = 0;
};

class TimeSortVisitor : public AbstractVisitor {
    int vertexSize = 0;
    std::deque<Vertex> &vertexesSortedByTimeOut;
public:
    TimeSortVisitor(const int &vertexSize, std::deque<Vertex> &array) : vertexSize(vertexSize),
                                                                        vertexesSortedByTimeOut(array) {}

    void startVertex() override {}

    void discoverVertex(const Vertex &vertex) {}

    std::deque<Vertex> getOrderOfVertex() {
        std::deque<Vertex> withoutOrder(vertexSize);
        for (int i = 0; i < vertexSize; ++i) {
            withoutOrder[i] = Vertex(i);
        }
        return withoutOrder;
    }

    void finishVertex(const Vertex &vertex) {
        vertexesSortedByTimeOut.push_front(vertex);
    }
};

class SCCFindVisitor : public AbstractVisitor {
    std::deque<Vertex> &vertexesSortedByTimeOut;
    int &counter;
    std::vector<int> &strongComponents;
public:
    SCCFindVisitor(std::deque<Vertex> &vertexesSortedByTimeOut, int &counter,
                   std::vector<int> &strongComponents) :
            vertexesSortedByTimeOut(vertexesSortedByTimeOut),
            counter(counter), strongComponents(strongComponents) {}

    void startVertex() override {
        counter++;
    }

    void discoverVertex(const Vertex &vertex) {
        strongComponents[vertex] = counter;
    }

    std::deque<Vertex> getOrderOfVertex() override {
        return vertexesSortedByTimeOut;
    }

    virtual void finishVertex(const Vertex &vertex) {}
};

class Graph {
public:
    struct Edge {
        Vertex to;

        Edge() = default;

        explicit Edge(const int &index) : to(index) {}
    };

private:
    int vertexSize = 0;
    std::vector<std::vector<Edge>> adjacencyList;

    Graph Transposed() const {
        Graph transportedGraph(vertexSize);
        for (int i = 0; i < vertexSize; ++i) {
            for (const auto &edge : adjacencyList[i]) {
                transportedGraph.AddEdge(edge.to, i);
            }
        }
        return transportedGraph;
    }

    void Dfs(AbstractVisitor *visitor) {
        std::vector<int> colors(vertexSize, Colors::WHITE);
        for (auto &vertex : visitor->getOrderOfVertex()) {
            if (colors[vertex] == Colors::WHITE) {
                visitor->startVertex();
                DfsVisit(vertex, visitor, colors);
            }
        }
    }

    void DfsVisit(const Vertex &start, AbstractVisitor *visitor, std::vector<int> &colors) {
        colors[start] = Colors::GRAY;
        visitor->discoverVertex(start);
        for (const auto neighbour : adjacencyList[start]) {
            if (colors[neighbour.to] == Colors::WHITE) {
                DfsVisit(neighbour.to, visitor, colors);
            }
        }
        colors[start] = Colors::BLACK;
        visitor->finishVertex(start);
    }

public:
    struct StrongComponents {
        int numberOfComponents;
        std::vector<int> SCC;
    };

    Graph(const int &vertexSize) : vertexSize(vertexSize), adjacencyList(vertexSize, std::vector<Edge>()) {}

    void AddEdge(const int &from, const int &to) {
        adjacencyList[from].push_back(Edge(to));
    }

    StrongComponents findStrongComponents() {
        std::vector<int> strongComponents(vertexSize, -1);
        int counter = 0;
        std::deque<Vertex> toSort;
        AbstractVisitor *timeVisitor = new TimeSortVisitor(vertexSize, toSort);
        Dfs(timeVisitor);
        AbstractVisitor *sccVisitor = new SCCFindVisitor(toSort, counter, strongComponents);
        Graph transported = this->Transposed();
        transported.Dfs(sccVisitor);
        delete timeVisitor;
        delete sccVisitor;
        return {counter, strongComponents};
    }

};

int main() {
    size_t vertexSize = 0;
    size_t edgeSize = 0;
    std::cin >> vertexSize >> edgeSize;
    Graph graph(vertexSize);
    for (int i = 0; i < edgeSize; ++i) {
        int from, to;
        std::cin >> from >> to;
        graph.AddEdge(from - 1, to - 1);
    }
    Graph::StrongComponents strongComponents = graph.findStrongComponents();
    std::cout << strongComponents.numberOfComponents << '\n';
    for (const auto &element : strongComponents.SCC) {
        std::cout << element << ' ';
    }
    return 0;
}
