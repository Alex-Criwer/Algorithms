#include <iostream>
#include <algorithm>
#include <vector>

int main() {
    int size, numberOfOperations, operation, u, v;
    std::cin >> size >> numberOfOperations;
    std::vector<std::vector<int>> graph;
    graph.resize(size);
    for (int i = 0; i < numberOfOperations; ++i) {
        std::cin >> operation;
        if (operation == 1) {
            std::cin >> u >> v;
            graph[u-1].push_back(v);
            graph[v-1].push_back(u);
        } else if (operation == 2) {
            std::cin >> u;
            for (const auto &element : graph[u-1]) {
                std::cout << element << ' ';
            }
            std::cout << '\n';
        }

    }
    return 0;
}

