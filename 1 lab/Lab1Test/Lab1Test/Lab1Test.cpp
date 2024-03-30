#include <iostream>
#include <sstream>
#include <vector>
#include <boost/timer.hpp>
#define CATCH_CONFIG_MAIN
#include "../../catch2/catch.hpp"
#include "../../Lab1/Lab 1/CalculateOptimalRoute.h"

using namespace std;

TEST_CASE("Test calc with N = 10")
{
	boost::timer t;
	t.restart();
	vector<vector<int>> roads = {
		{ 0, 12, 13, 14, 15, 16, 17, 18, 19, 110 },
		{ 12, 0, 23, 24, 25, 26, 27, 28, 29, 210 },
		{ 13, 23, 0, 34, 35, 36, 37, 38, 39, 310 },
		{ 14, 24, 34, 0, 45, 46, 47, 48, 49, 410 },
		{ 15, 25, 35, 45, 0, 56, 57, 58, 59, 510 },
		{ 16, 26, 36, 46, 56, 0, 67, 68, 69, 610 },
		{ 17, 27, 37, 47, 57, 67, 0, 78, 79, 710 },
		{ 18, 28, 38, 48, 58, 68, 78, 0, 89, 810 },
		{ 19, 29, 39, 49, 59, 69, 79, 89, 0, 910 },
		{ 110, 210, 310, 410, 510, 610, 710, 810, 910, 0 }
	};

	vector<int> optimalPermutation = CalculateOptimalRoute(roads);
	vector<int> expectedPermutation = { 1, 6, 3, 7, 4, 8, 5, 9, 2, 10 };
	double duration = t.elapsed();
	std::cout << duration << std::endl;
	REQUIRE(optimalPermutation == expectedPermutation);
}

TEST_CASE("Empty graph")
{
	boost::timer t;
	t.restart();
	vector<vector<int>> roads = {
		{ 0, 2, 2, 0 },
		{ 2, 0, 0, 2 },
		{ 2, 0, 0, 2 },
		{ 0, 2, 2, 0 }
	};

	vector<int> optimalPermutation = CalculateOptimalRoute(roads);
	vector<int> expectedPermutation = { 1, 2, 3, 4 };
	double duration = t.elapsed();
	std::cout << duration << std::endl;
	REQUIRE(optimalPermutation == expectedPermutation);
}

TEST_CASE("Average graph")
{
	boost::timer t;
	t.restart();
	vector<vector<int>> roads = {
   {0, 12, 7, 3},
   {12, 0, 5, 1},
   {7, 5, 0, 4},
   {3, 1, 4, 0}
	};
	vector<int> optimalPermutation = CalculateOptimalRoute(roads);
	vector<int> expectedPermutation = { 1, 3, 2, 4 };
	double duration = t.elapsed();
	std::cout << duration << std::endl;
	REQUIRE(optimalPermutation == expectedPermutation);
}
