#include <iostream>
#include <vector>
#include <string>
#include "../Lab1_2/SelectItemsWithMaxCost.h"

using namespace std;

bool NextSet(vector<size_t>& indexes, size_t totalElements, size_t subsetSize)
{
	for (int i = subsetSize - 1; i >= 0; i--)
	{
		if (indexes[i] < totalElements - subsetSize + i + 1)
		{
			++indexes[i];
			for (size_t j = i + 1; j < subsetSize; j++)
			{
				indexes[j] = indexes[j - 1] + 1;
			}
			return true;
		}
	}
	return false;
}

vector<size_t> SelectItemsWithMaxCost(const vector<vector<size_t>>& itemsCostMatrix, size_t weightLimit)
{
	if (itemsCostMatrix.size() < 1u)
	{
		throw invalid_argument("There are no items");
	};

	for (size_t i = 0; i < itemsCostMatrix.size(); i++)
	{
		if (itemsCostMatrix[i].size() < 3u)
		{
			throw invalid_argument("Not enough info about " + to_string(i) + " item");
		};

		if (itemsCostMatrix[i].size() > 3u)
		{
			throw invalid_argument("Overflow of information about the " + to_string(i) + " item");
		};
	}

	vector<size_t> itemOrder = {};

	for (size_t i = 0; i < itemsCostMatrix.size(); i++)
	{
		itemOrder.push_back(itemsCostMatrix[i][0]);
	};

	size_t numItems = itemOrder.size();
	size_t maxCost = 0;
	vector<size_t> selectedItems = {};
	size_t selectedItemsSize = 0;

	for (size_t m = 1; m <= numItems; m++)
	{
		vector<size_t> copyItemOrder = itemOrder;

		do
		{

			size_t totalWeight = 0;
			size_t totalCost = 0;

			for (size_t i = 0; i < m; i++)
			{
				totalWeight += itemsCostMatrix[copyItemOrder[i] - 1][1];
				totalCost += itemsCostMatrix[copyItemOrder[i] - 1][2];
			}

			if ((totalWeight <= weightLimit) && (maxCost < totalCost))
			{
				maxCost = totalCost;
				selectedItems = copyItemOrder;
				selectedItemsSize = m;
			}

		} while (NextSet(copyItemOrder, numItems, m));
	}

	vector<size_t> answer = {};

	for (size_t i = 0; i < selectedItemsSize; i++)
	{
		answer.push_back(selectedItems[i]);
	}

	return answer;
}