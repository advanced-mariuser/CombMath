#include <sstream>
#include "catch2/catch_test_macros.hpp"
#include "../src/CGraph.h"
#include "../src/CGammaAlgorithm.h"

bool checkGraphPlanarity(CGraph &graph, bool notPlanar = false)
{
    std::ostringstream oss;
    CGammaAlgorithm gammaAlgorithm(graph);
    gammaAlgorithm.Run();

    std::string output = oss.str();
    if(notPlanar)
    {
        return output.find("No cycle found in the graph during initialization.") == std::string::npos;
    }
    return output.find("Graph successfully processed using Gamma Algorithm.") == std::string::npos;
}

TEST_CASE("Graph Planarity Test", "[graph]")
{
    SECTION("Graph is planar")
    {
        CGraph graph(4);

        std::vector<std::vector<int>> adjacencyMatrix = {
                {0, 1, 1, 0},
                {1, 0, 1, 1},
                {1, 1, 0, 1},
                {0, 1, 1, 0}
        };
        graph.AddEdgesFromAdjacencyMatrix(adjacencyMatrix);

        REQUIRE(checkGraphPlanarity(graph) == true);
    }

    SECTION("Graph is not planar - K5")
    {
        CGraph graph(5);
        std::vector<std::vector<int>> adjacencyMatrix = {
                {0, 1, 1, 1, 1},
                {1, 0, 1, 1, 1},
                {1, 1, 0, 1, 1},
                {1, 1, 1, 0, 1},
                {1, 1, 1, 1, 0}
        };
        graph.AddEdgesFromAdjacencyMatrix(adjacencyMatrix);

        REQUIRE(checkGraphPlanarity(graph, true) == true);
    }

    SECTION("Graph is not planar - K3,3")
    {
        CGraph graph(6);
        std::vector<std::vector<int>> adjacencyMatrix = {
                {0, 1, 1, 0, 0, 0},
                {1, 0, 1, 0, 0, 0},
                {1, 1, 0, 0, 0, 0},
                {0, 0, 0, 0, 1, 1},
                {0, 0, 0, 1, 0, 1},
                {0, 0, 0, 1, 1, 0}
        };
        graph.AddEdgesFromAdjacencyMatrix(adjacencyMatrix);

        REQUIRE(checkGraphPlanarity(graph, true) == true);
    }

    SECTION("Graph is planar 5")
    {
        CGraph graph(5);

        std::vector<std::vector<int>> adjacencyMatrix = {
                {0, 1, 1, 0, 1},
                {1, 0, 1, 1, 0},
                {1, 1, 0, 1, 0},
                {0, 1, 1, 0, 1},
                {1, 0, 0, 1, 0}
        };
        graph.AddEdgesFromAdjacencyMatrix(adjacencyMatrix);

        REQUIRE(checkGraphPlanarity(graph) == true);
    }

    SECTION("Graph P is not planar")
    {
        CGraph graph(10);

        std::vector<std::vector<int>> adjacencyMatrix = {
                {0, 0, 1, 0, 0, 0, 1, 0, 0, 1},
                {0, 0, 0, 0, 1, 1, 1, 0, 0, 0},
                {1, 0, 0, 1, 0, 1, 0, 0, 0, 0},
                {0, 0, 1, 0, 1, 0, 0, 1, 0, 0},
                {0, 1, 0, 1, 0, 0, 0, 0, 0, 1},
                {0, 1, 1, 0, 0, 0, 0, 0, 1, 0},
                {1, 1, 0, 0, 0, 0, 0, 1, 0, 0},
                {0, 0, 0, 1, 0, 0, 1, 0, 1, 0},
                {0, 0, 0, 0, 0, 1, 0, 1, 0, 1},
                {1, 0, 0, 0, 1, 0, 0, 0, 1, 0}
        };
        graph.AddEdgesFromAdjacencyMatrix(adjacencyMatrix);

        REQUIRE(checkGraphPlanarity(graph, true) == true);
    }

    SECTION("Empty graph")
    {
        CGraph graph(0);
        std::vector<std::vector<int>> adjacencyMatrix = {};
        graph.AddEdgesFromAdjacencyMatrix(adjacencyMatrix);

        REQUIRE(checkGraphPlanarity(graph) == true);
    }

    SECTION("Single vertex with no edges")
    {
        CGraph graph(1);
        std::vector<std::vector<int>> adjacencyMatrix = {
                {0}
        };
        graph.AddEdgesFromAdjacencyMatrix(adjacencyMatrix);

        REQUIRE(checkGraphPlanarity(graph) == true);
    }

    SECTION("Single edge")
    {
        CGraph graph(2);
        std::vector<std::vector<int>> adjacencyMatrix = {
                {0, 1},
                {1, 0}
        };
        graph.AddEdgesFromAdjacencyMatrix(adjacencyMatrix);

        REQUIRE(checkGraphPlanarity(graph) == true);
    }

    SECTION("Graph with a bridge")
    {
        CGraph graph(4);
        std::vector<std::vector<int>> adjacencyMatrix = {
                {0, 1, 0, 0},
                {1, 0, 1, 1},
                {0, 1, 0, 0},
                {0, 1, 0, 0}
        };
        graph.AddEdgesFromAdjacencyMatrix(adjacencyMatrix);

        REQUIRE(checkGraphPlanarity(graph) == true);
    }

    SECTION("Graph with cycles but no bridges")
    {
        CGraph graph(4);
        std::vector<std::vector<int>> adjacencyMatrix = {
                {0, 1, 1, 0},
                {1, 0, 1, 1},
                {1, 1, 0, 1},
                {0, 1, 1, 0}
        };
        graph.AddEdgesFromAdjacencyMatrix(adjacencyMatrix);

        REQUIRE(checkGraphPlanarity(graph) == true);
    }
}
