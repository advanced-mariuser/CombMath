#include <algorithm>
#include <iostream>
#include <vector>
#define BOOST_TIMER_ENABLE_DEPRECATED
#include <boost/timer.hpp>
#include <string>
#include "CalculateOptimalRoute.h"

void Forecast(long double duration)
{
	for (int i = 11; i <= 15; i++)
	{
		duration *= i;
	}
	duration /= 3600;
	std::cout << "N = 15: " << duration << " hours" << std::endl;

	for (int i = 16; i <= 20; i++)
	{
		duration *= i;
	}
	duration /= 24;

	std::cout << "N = 20: " << duration << " days" << std::endl;

	for (int i = 21; i <= 50; i++)
	{
		duration *= i;
	}
	duration /= 365;
	std::cout << "N = 50: " << duration << " years" << std::endl;
}

int main()
{
	boost::timer t;
	t.restart();

	std::vector<std::vector<int>> weightMatrix = {
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
	std::vector<int> minV = CalculateOptimalRoute(weightMatrix);
	
	copy(minV.begin(), minV.end(), std::ostream_iterator<int>(std::cout, " "));
	
	double duration = t.elapsed();
	std::cout << duration << std::endl;

	Forecast(duration);
}