#include "catch2/catch_test_macros.hpp"
#include "../src/Graph.h"

TEST_CASE("Graph::CountSpanningTrees tests", "[Graph::CountSpanningTrees]")
{
	SECTION("Empty graph (isolated vertices)")
	{
		Matrix adjMatrix = {
			{0, 0, 0},
			{0, 0, 0},
			{0, 0, 0}
		};
        Graph graph(adjMatrix);
		REQUIRE(graph.CountSpanningTrees() == 0);
	}

    SECTION("Single vertex graph")
    {
        Matrix adjMatrix = {
                {0}
        };
        Graph graph(adjMatrix);
        REQUIRE(graph.CountSpanningTrees() == 1);
    }

	SECTION("Graph-tree (linear graph)")
	{
		Matrix adjMatrix = {
			{0, 1, 0},
			{1, 0, 1},
			{0, 1, 0}
		};
        Graph graph(adjMatrix);
		REQUIRE(graph.CountSpanningTrees() == 1);
	}

	SECTION("Complete graph on 3 vertices")
	{
		Matrix adjMatrix = {
			{0, 1, 1},
			{1, 0, 1},
			{1, 1, 0}
		};
        Graph graph(adjMatrix);
		REQUIRE(graph.CountSpanningTrees() == 3);
	}

	SECTION("Complete graph on 4 vertices")
	{
		Matrix adjMatrix = {
			{0, 1, 1, 1},
			{1, 0, 1, 1},
			{1, 1, 0, 1},
			{1, 1, 1, 0}
		};
        Graph graph(adjMatrix);
		REQUIRE(graph.CountSpanningTrees() == 16);
	}

	SECTION("Graph with two components of connectivity")
	{
		Matrix adjMatrix = {
			{0, 1, 0, 0},
			{1, 0, 0, 0},
			{0, 0, 0, 1},
			{0, 0, 1, 0}
		};
        Graph graph(adjMatrix);
		REQUIRE(graph.CountSpanningTrees() == 0);
	}

    SECTION("Graph with a cycle")
    {
        Matrix adjMatrix = {
                {0, 1, 1},
                {1, 0, 1},
                {1, 1, 0}
        };
        Graph graph(adjMatrix);
        REQUIRE(graph.CountSpanningTrees() == 3);
    }

    SECTION("Larger graph")
    {
        Matrix adjMatrix = {
                {0, 1, 1, 0, 0},
                {1, 0, 1, 1, 0},
                {1, 1, 0, 1, 1},
                {0, 1, 1, 0, 1},
                {0, 0, 1, 1, 0}
        };
        Graph graph(adjMatrix);
        REQUIRE(graph.CountSpanningTrees() == 21);
    }
}