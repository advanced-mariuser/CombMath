#include "catch2/catch_test_macros.hpp"
#include "../src/HungarianAlgorithm.h"
#include "../src/Vector.h"

Vector getGeneratedVertexList(int size) {
    Vector vertices;
    for (int i = 0; i < size; ++i) {
        vertices.push_back(Vertex(-1));
    }
    return vertices;
}

bool compareVertexVectors(const Vector& a, const Vector& b) {
    if (a.size() != b.size()) return false;
    for (size_t i = 0; i < a.size(); ++i) {
        if (a[i].index() != b[i].index()) return false;
    }
    return true;
}

Vector getAlgorithmResult(int rows, int cols, const std::vector<std::vector<double>>& costsMatrix) {
    Vector workers;
    Vector jobs;

    for (int i = 0; i < rows; ++i) {
        workers.push_back(Vertex(i));
    }
    for (int i = 0; i < cols; ++i) {
        jobs.push_back(Vertex(i));
    }

    auto costFunction = [&costsMatrix](const Vertex& worker, const Vertex& job) {
        return costsMatrix[worker.index()][job.index()];
    };

    HungarianAlgorithm algorithm(workers, jobs, costFunction);

    std::vector<int> result = algorithm.getOptimalAssignment();
    Vector vertexResult;
    for (int i : result) {
        vertexResult.push_back(Vertex(i));
    }

    return vertexResult;
}

TEST_CASE("HungarianAlgorithmAggregator") {

    SECTION("test matrix 3x3 (1)") {
        std::vector<std::vector<double>> costsMatrix = {{0, 1, 2}, {3, 0, 6}, {9, 2, 10}};
        Vector expectedResult = getGeneratedVertexList(3);
        expectedResult[0] = Vertex(2);
        expectedResult[1] = Vertex(0);
        expectedResult[2] = Vertex(1);
        Vector result = getAlgorithmResult(3, 3, costsMatrix);
        REQUIRE(compareVertexVectors(result, expectedResult));
    }

    SECTION("test matrix 3x3 (2)") {
        std::vector<std::vector<double>> costsMatrix = {{5, 10, 3}, {1, 5, 10}, {2, 4, 5}};
        Vector expectedResult = getGeneratedVertexList(3);
        expectedResult[0] = Vertex(2);
        expectedResult[1] = Vertex(0);
        expectedResult[2] = Vertex(1);
        Vector result = getAlgorithmResult(3, 3, costsMatrix);
        REQUIRE(compareVertexVectors(result, expectedResult));
    }

    SECTION("test matrix 3x3 (3)") {
        std::vector<std::vector<double>> costsMatrix = {{1, 2, 8}, {1, 3, 10}, {4, 5, 6}};
        Vector expectedResult = getGeneratedVertexList(3);
        expectedResult[0] = Vertex(1);
        expectedResult[1] = Vertex(0);
        expectedResult[2] = Vertex(2);
        Vector result = getAlgorithmResult(3, 3, costsMatrix);
        REQUIRE(compareVertexVectors(result, expectedResult));
    }

    SECTION("test matrix 3x4") {
        std::vector<std::vector<double>> costsMatrix = {{0, 1, 2, 3}, {3, 0, 6, 7}, {9, 2, 10, 12}};
        Vector expectedResult = getGeneratedVertexList(3);
        expectedResult[0] = Vertex(2);
        expectedResult[1] = Vertex(0);
        expectedResult[2] = Vertex(1);
        Vector result = getAlgorithmResult(3, 4, costsMatrix);
        REQUIRE(compareVertexVectors(result, expectedResult));
    }

    SECTION("test matrix 3x7") {
        std::vector<std::vector<double>> costsMatrix = {{0, 1, 2, 3, 5, 4, 5}, {3, 0, 6, 7, 3, 8, 9}, {9, 2, 10, 12, 4, 0, 10}};
        Vector expectedResult = getGeneratedVertexList(3);
        expectedResult[0] = Vertex(0);
        expectedResult[1] = Vertex(1);
        expectedResult[2] = Vertex(5);
        Vector result = getAlgorithmResult(3, 7, costsMatrix);
        REQUIRE(compareVertexVectors(result, expectedResult));
    }

    SECTION("test matrix 4x3") {
        std::vector<std::vector<double>> costsMatrix = {{0, 1, 2}, {3, 0, 6}, {9, 2, 10}, {4, 3, 3}};
        Vector expectedResult = getGeneratedVertexList(4);
        expectedResult[0] = Vertex(0);
        expectedResult[1] = Vertex(1);
        expectedResult[2] = Vertex(-1);
        expectedResult[3] = Vertex(2);
        Vector result = getAlgorithmResult(4, 3, costsMatrix);
        REQUIRE(compareVertexVectors(result, expectedResult));
    }

    SECTION("test same transitions") {
        std::vector<std::vector<double>> costsMatrix = {{1, 2, 3, 4}, {1, 2, 3, 4}, {5, 4, 7, 4}, {8, 9, 12, 10}};
        Vector expectedResult = getGeneratedVertexList(4);
        expectedResult[0] = Vertex(0);
        expectedResult[1] = Vertex(2);
        expectedResult[2] = Vertex(3);
        expectedResult[3] = Vertex(1);
        Vector result = getAlgorithmResult(4, 4, costsMatrix);
        REQUIRE(compareVertexVectors(result, expectedResult));
    }
}
