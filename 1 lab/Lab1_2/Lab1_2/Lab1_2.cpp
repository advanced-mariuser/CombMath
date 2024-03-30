#include <algorithm>
#include <iostream>
#include <vector>
#include "../Lab1_2/SelectItemsWithMaxCost.h"

using namespace std;

// {index, weight, cost}

int main()
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
	try
	{
		vector<size_t>inBag = SelectItemsWithMaxCost(objects, 6404180);

		copy(inBag.begin(), inBag.end(), ostream_iterator<size_t>(cout, " "));
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}