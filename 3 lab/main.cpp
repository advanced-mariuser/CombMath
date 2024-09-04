#include "../src/CGraph.h"
#include "../src/CGammaAlgorithm.h"
#include <vector>
#include <iostream>

int main() {
    CGraph graph(10);
    std::vector<std::vector<int>> adjacencyMatrix = {
            {0, 1, 1, 0, 0, 0, 1, 0, 0, 0},
            {1, 0, 0, 1, 0, 1, 0, 0, 0, 0},
            {1, 0, 0, 0, 1, 0, 0, 1, 0, 0},
            {0, 1, 0, 0, 1, 0, 0, 0, 1, 0},
            {0, 0, 1, 1, 0, 0, 0, 0, 0, 1},
            {0, 1, 0, 0, 0, 0, 0, 1, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 1, 1},
            {0, 0, 1, 0, 0, 1, 0, 0, 1, 0},
            {0, 0, 0, 1, 0, 0, 1, 1, 0, 0},
            {0, 0, 0, 0, 1, 1, 1, 0, 0, 0},
    };
    graph.AddEdgesFromAdjacencyMatrix(adjacencyMatrix);

    if (!graph.IsConnected() || !graph.HasCycle() || !graph.HasNoBridges()) {
        std::cerr << "Graph does not meet the required properties." << std::endl;
        return 1;
    }

    CGammaAlgorithm gammaAlgorithm(graph);
    gammaAlgorithm.Run();

    return 0;
}
