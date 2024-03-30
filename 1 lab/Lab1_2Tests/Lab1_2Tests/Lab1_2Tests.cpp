#include <iostream>
#include <sstream>
#include <vector>
#define CATCH_CONFIG_MAIN
#include "../../catch2/catch.hpp"
#include "../../Lab1_2/Lab1_2/SelectItemsWithMaxCost.h"	

using namespace std;

TEST_CASE("Correct input values")
{
	SECTION("10 items")
	{
		vector<vector<size_t>> objects = {
		{1, 23, 92},
		{2, 31, 57},
		{3, 29, 49},
		{4, 44, 68},
		{5, 53, 60},
		{6, 38, 43},
		{7, 63, 67},
		{8, 85, 84},
		{9, 89, 87},
		{10, 82, 72}
		};

		vector<size_t> result = SelectItemsWithMaxCost(objects, 165);
		vector<size_t> expected = { 1, 2, 3, 4, 6 };

		REQUIRE(expected == result);
	}
	SECTION("10 items full")
	{
		vector<vector<size_t>> objects = {
		{1, 23, 92},
		{2, 31, 57},
		{3, 29, 49},
		{4, 44, 68},
		{5, 53, 60},
		{6, 38, 43},
		{7, 63, 67},
		{8, 85, 84},
		{9, 89, 87},
		{10, 82, 72}
		};

		vector<size_t> result = SelectItemsWithMaxCost(objects, 1000);
		vector<size_t> expected = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

		REQUIRE(expected == result);
	}
	SECTION("24 items")
	{
		vector<vector<size_t>> objects = {
		{1, 382745, 825594},
		{2, 799601, 1677009},
		{3, 909247, 1676628},
		{4, 729069, 1523970},
		{5, 467902, 943972},
		{6, 44328, 97426},
		{7, 34610, 69666},
		{8, 698150, 1296457},
		{9, 823460, 1679693},
		{10, 903959, 1902996},
		{11, 853665, 1844992},
		{12, 551830, 1049289},
		{13, 610856, 1252836},
		{14, 670702, 1319836},
		{15, 488960, 953277},
		{16, 951111, 2067538},
		{17, 323046, 675367},
		{18, 446298, 853655},
		{19, 931161, 1826027},
		{20, 31385, 65731},
		{21, 496951, 901489},
		{22, 264724, 577243},
		{23, 224916, 466257},
		{24, 169684, 369261}
		};

		vector<size_t> result = SelectItemsWithMaxCost(objects, 6404180);
		vector<size_t> expected = { 1, 2, 4, 5, 6, 10, 11, 13, 16, 22, 23, 24 };

		REQUIRE(expected == result);
	}
	SECTION("30 items")
	{
		vector<vector<size_t>> objects = {
	   {1, 8782, 6927},
	   {2, 6949, 5694},
	   {3, 4882, 5231},
	   {4, 1327, 4064},
	   {5, 2048, 6940},
	   {6, 2034, 6808},
	   {7, 3761, 9916},
	   {8, 3495, 946},
	   {9, 1150, 4433},
	   {10, 403, 4721},
	   {11, 5356, 4450},
	   {12, 321, 3774},
	   {13, 6504, 9961},
	   {14, 3596, 3904},
	   {15, 3244, 9287},
	   {16, 3064, 7043},
	   {17, 1491, 8975},
	   {18, 2196, 929},
	   {19, 4473, 1941},
	   {20, 663, 9994},
	   {21, 2052, 9289},
	   {22, 8873, 6741},
	   {23, 8461, 3405},
	   {24, 5243, 1288},
	   {25, 466, 4729},
	   {26, 1785, 9088},
	   {27, 8928, 1667},
	   {28, 9991, 3345},
	   {29, 830, 2209},
	   {30, 3599, 9590}
		};

		vector<size_t> result = SelectItemsWithMaxCost(objects, 5972);
		vector<size_t> expected = { 10, 12, 17, 20, 25, 26, 29 };
		REQUIRE(expected == result);
	}
}

TEST_CASE("Incorrect input")
{
	SECTION("Empty")
	{
		vector<vector<size_t>> objects;
		REQUIRE_THROWS_AS(SelectItemsWithMaxCost(objects, 5972), std::invalid_argument);
	}
	SECTION("Not full")
	{
		vector<vector<size_t>> objects = {
		{1, 23},
		{2, 31, 57},
		{3, 29, 49},
		{4, 44, 68},
		{5, 53, 60},
		{6, 38},
		{7, 63, 67},
		{8, 85, 84},
		{9, 89, 87},
		{10, 82, 72}
		};;
		REQUIRE_THROWS_AS(SelectItemsWithMaxCost(objects, 165), std::invalid_argument);
	}
	SECTION("More then full")
	{
		vector<vector<size_t>> objects = {
		{1, 23, 92},
		{2, 31, 57},
		{3, 29, 49},
		{4, 44, 68},
		{5, 53, 60, 14},
		{6, 38, 43},
		{7, 63, 67},
		{8, 85, 84},
		{9, 89, 87},
		{10, 82, 72}
		};;
		REQUIRE_THROWS_AS(SelectItemsWithMaxCost(objects, 165), std::invalid_argument);
	}
}