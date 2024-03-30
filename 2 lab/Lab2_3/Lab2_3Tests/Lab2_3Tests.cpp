#include <vector>
#define CATCH_CONFIG_MAIN
#include "../../../1 lab/catch2/catch.hpp"
#include "../Lab2_3/FindTheHamiltonianCycle.h"

TEST_CASE("Hamiltonian cycle search in directed graph")
{
	SECTION("Test for 5x5 matrix oriented")
	{
		std::vector<std::vector<int>> graph = {
			{ INT_MAX, 1, 0, 1, 1 },
			{ 1, INT_MAX, 1, 1, 0 },
			{ 1, 1, INT_MAX, 0, 1 },
			{ 1, 0, 1, INT_MAX, 1 },
			{ 0, 1, 1, 1, INT_MAX },
		};
		int min_length = INT_MAX;
		std::vector<std::pair<int, int>> minEdges;
		std::vector<std::pair<int, int>> edges;
		BranchAndBound(graph, edges, 0, min_length, minEdges);
		std::cout << edges.size() << std::endl;
		for (auto& edge : minEdges)
		{
			std::cout << "first: " << edge.first << " second: " << edge.second << std::endl;
		}
		REQUIRE(min_length != INT_MAX);
		int length = GetLength(graph, minEdges);
		std::vector<std::pair<int, int>> expectedPath = {
			{ 0, 2 },
			{ 1, 4 },
			{ 2, 3 },
			{ 3, 1 },
			{ 4, 0 }
		};
		int expectedLength = 0;
		REQUIRE(minEdges == expectedPath);
		REQUIRE(length == expectedLength);
	}

	SECTION("Test for 4x4 matrix oriented")
	{
		std::vector<std::vector<int>> graph = {
			{ INT_MAX, 5, 11, 9 },
			{ 10, INT_MAX, 8, 7 },
			{ 7, 14, INT_MAX, 8 },
			{ 12, 6, 15, INT_MAX }
		};
		int min_length = INT_MAX;
		std::vector<std::pair<int, int>> minEdges;
		std::vector<std::pair<int, int>> edges;
		BranchAndBound(graph, edges, 0, min_length, minEdges);
		std::cout << edges.size() << std::endl;
		for (auto& edge : minEdges)
		{
			std::cout << "first: " << edge.first + 1 << " second: " << edge.second + 1 << std::endl;
		}
		REQUIRE(min_length != INT_MAX);
		int length = GetLength(graph, minEdges);
		std::vector<std::pair<int, int>> expectedPath = {
			{1, 2},
			{0, 3},
			{2, 0},
			{3, 1}
		};
		int expectedLength = 30;
		REQUIRE(minEdges == expectedPath);
		REQUIRE(length == expectedLength);
	}

	SECTION("Test for 6x6 matrix oriented")
	{
		std::vector<std::vector<int>> graph = {
			{ INT_MAX, 5, 7, 6, 8, 3 },
			{ 1, INT_MAX, 8, 4, 6, 2 },
			{ 3, 9, INT_MAX, 6, 5, 3 },
			{ 7, 8, 4, INT_MAX, 4, 2 },
			{ 2, 7, 5, 6, INT_MAX, 6 },
			{ 5, 2, 6, 4, 5, INT_MAX }
		};
		int min_length = INT_MAX;
		std::vector<std::pair<int, int>> minEdges;
		std::vector<std::pair<int, int>> edges;
		BranchAndBound(graph, edges, 0, min_length, minEdges);
		std::cout << edges.size() << std::endl;
		for (auto& edge : minEdges)
		{
			std::cout << "first: " << edge.first + 1 << " second: " << edge.second + 1 << std::endl;
		}
		REQUIRE(min_length != INT_MAX);
		int length = GetLength(graph, minEdges);
		std::vector<std::pair<int, int>> expectedPath = {
			{2, 4},
			{0, 5},
			{1, 3},
			{3, 2},
			{4, 0},
			{5, 1}
		};
		int expectedLength = 20;
		REQUIRE(minEdges == expectedPath);
		REQUIRE(length == expectedLength);
	}
}