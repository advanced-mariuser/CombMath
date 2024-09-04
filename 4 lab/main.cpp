#include <iostream>
#include <vector>
#include "src/Graph.h"

int main() {
    Matrix adjMatrix = {
            {0, 1, 0, 0},
            {1, 0, 1, 1},
            {0, 1, 0, 1},
            {0, 1, 1, 0}
    };

    Graph graph(adjMatrix);
    int countSpanningTrees = graph.CountSpanningTrees();
    std::cout << "Count of spanning trees: " << countSpanningTrees << std::endl;

    return 0;
}
