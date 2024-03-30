#include "CalculateOptimalRoute.h"
#include <algorithm>
#include <vector>
#include <iostream>

int CountSum(std::vector<int>& permutations, std::vector<std::vector<int>>& weightMatrix)
{
	int sum = 0;
	for (int i = 0; i < permutations.size(); i++)
	{
		int currentIndex = permutations[i]-1;
		int nextIndex = permutations[(i + 1) % permutations.size()]-1;

		sum += weightMatrix[currentIndex][nextIndex];
	}
    
    return sum;
}

std::vector<int> CalculateOptimalRoute(std::vector<std::vector<int>>& weightMatrix)
{
	std::vector<int> routs;
	
	for (size_t i = 1; i <= weightMatrix.size(); i++)
	{
		routs.push_back(i);
	}
	
	std::vector<int> optimalRouts = routs;

	int minSum = CountSum(routs, weightMatrix);;
	bool isFirstIter = true;
	do
	{
		int sum = CountSum(routs, weightMatrix);

		if (minSum > sum)
		{
			minSum = sum;
			optimalRouts = routs;
		}
	} while (std::next_permutation(routs.begin(), routs.end()));
	
	return optimalRouts;
}