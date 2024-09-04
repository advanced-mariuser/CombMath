#include <iostream>
#include <vector>
#include "src/HungarianAlgorithm.h"
#include "src/Vector.h"
#include "src/Vertex.h"

std::vector<std::vector<double>> costMatrix;
//  {9, 2, 7, 8},
//            {6, 4, 3, 7},
//            {5, 8, 1, 8},
//            {7, 6, 9, 4}
void initializeCostMatrix(int size) {
    costMatrix = {
            {0, 1, 2},
            {3, 0, 6},
            {9, 2, 10}
    };
}

double costFunction(const Vertex& worker, const Vertex& job) {
    return costMatrix[worker.index()][job.index()];
}

int main() {
    Vector workers;
    Vector jobs;

    for (int i = 0; i < 3; ++i) {
        workers.push_back(Vertex(i));
        jobs.push_back(Vertex(i));
    }

    initializeCostMatrix(workers.size());

    HungarianAlgorithm algorithm(workers, jobs, costFunction);

    std::vector<int> result = algorithm.getOptimalAssignment();

    std::cout << "Optimal assignment:" << std::endl;
    for (size_t i = 0; i < result.size(); ++i) {
        std::cout << "Worker " << i << " assigned to Job " << result[i] << " with cost " << costMatrix[i][result[i]] << std::endl;
    }

    return 0;
}
