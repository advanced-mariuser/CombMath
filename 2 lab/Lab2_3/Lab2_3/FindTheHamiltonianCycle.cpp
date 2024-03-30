#include "../Lab2_3/FindTheHamiltonianCycle.h"
#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;

void PrintMatrix(vector<vector<int>> matrix)
{
	for (int i = 0; i < matrix.size(); i++)
	{
		for (int j = 0; j < matrix.size(); j++)
		{
			if (matrix[i][j] < 10)
			{
				cout << " ";
			}
			if (matrix[i][j] == INT_MAX)
			{
				cout << " i|";
			}
			else
			{
				cout << matrix[i][j] << "|";
			}
		}
		cout << endl;
		cout << "------------" << endl;
	}
}

pair<int, int> ReduceMatrix(vector<vector<int>>& matrix, int& lowerBound)
{
	int n = matrix.size();
	vector<int> rowPenalty;
	vector<int> columnPenalty;

	for (int i = 0; i < n; ++i)
	{
		int minValue = INT_MAX;
		for (int j = 0; j < n; ++j)
		{
			if (matrix[i][j] < minValue)
			{
				minValue = matrix[i][j];
			}
		}
		if (minValue != INT_MAX && minValue >= 0)
		{
			rowPenalty.push_back(minValue);
			lowerBound += minValue;
			for (int j = 0; j < n; ++j)
			{
				if (matrix[i][j] != INT_MAX)
				{
					matrix[i][j] -= minValue;
				}
			}
		}
		else
		{
			rowPenalty.push_back(0);
		}
	}

	cout << "Row: " << endl;
	for (auto row : rowPenalty)
	{
		cout << row << " ";
	}
	cout << endl;

	cout << "After row:" << endl;
	PrintMatrix(matrix);

	for (int j = 0; j < n; ++j)
	{
		int minValue = INT_MAX;
		for (int i = 0; i < n; ++i)
		{
			if (matrix[i][j] < minValue)
			{
				minValue = matrix[i][j];
			}
		}
		if (minValue != INT_MAX && minValue >= 0)
		{
			columnPenalty.push_back(minValue);
			lowerBound += minValue;
			for (int i = 0; i < n; ++i)
			{
				if (matrix[i][j] != INT_MAX)
				{
					matrix[i][j] -= minValue;
				}
			}
		}
		else
		{
			columnPenalty.push_back(0);
		}
	}
	cout << "Column: " << endl;
	for (auto col : columnPenalty)
	{
		cout << col << " ";
	}
	cout << endl;

	cout << "After column:" << endl;
	PrintMatrix(matrix);

	int maxPenalty = INT_MIN;
	pair<int, int> maxPenaltyPoint;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (matrix[i][j] == 0)
			{
				if (rowPenalty[i] + columnPenalty[j] > maxPenalty)
				{
					maxPenaltyPoint = { i, j };
					maxPenalty = rowPenalty[i] + columnPenalty[j];
				}
			}
		}
	}
	return maxPenaltyPoint;
}

void EdgeRemoval(vector<vector<int>>& matrix, pair<int, int> indexes)
{
	int n = matrix.size();
	for (int i = 0; i < n; ++i)
	{
		matrix[indexes.first][i] = INT_MAX;
		matrix[i][indexes.second] = INT_MAX;
	}
}


int GetLength(vector<vector<int>> graph, vector<pair<int, int>> edges)
{
	int path = 0;
	for (auto edge : edges)
	{
		path += graph[edge.first][edge.second];
	}
	return path;
}


void BranchAndBound(vector<vector<int>>& matrix, vector<pair<int, int>>& edges, int length, int& minLength, vector<pair<int, int>>& minEdges)
{
	cout << "--------------------------------------------------" << endl;
	cout << "               START" << endl;
	cout << "--------------------------------------------------" << endl;
	if (edges.size() == matrix.size())
	{
		// Если достигнут конец пути, вычисляем его длину и проверяем на минимальность
		if (length < minLength)
		{
			minLength = length;
			minEdges = edges;
		}
		cout << "--------------------------------------------------" << endl;
		cout << "               RETURN" << endl;
		cout << "--------------------------------------------------" << endl;
		return;
	}

	int lowerBound = length;
	vector<pair<int, int>> copyEdges = edges;
	vector<vector<int>> copyMatrix = matrix;
	
	PrintMatrix(copyMatrix);
	
	pair<int, int> indexes = ReduceMatrix(copyMatrix, lowerBound);
	if (matrix[indexes.first][indexes.second] == INT_MAX)
	{
		return;
	}
	
	copyEdges.push_back(indexes);
	cout << "EDGES: " << endl;
	for (auto edge : copyEdges)
	{
		cout << "first: " << edge.first + 1 << " second: " << edge.second + 1 << endl;
	}
	cout << endl;
	
	vector<vector<int>> matrixWithEdge = copyMatrix;
	EdgeRemoval(matrixWithEdge, indexes);
	vector<pair<int, int>> newEdges = edges;
	
	cout << "+++ CHOOSE +++" << endl;
	cout << "+++ BOUND +++" << lowerBound << endl;
	BranchAndBound(matrixWithEdge, copyEdges, lowerBound + matrix[indexes.first][indexes.second], minLength, minEdges);
	
	vector<vector<int>> matrixWithoutEdge = copyMatrix;
	matrixWithoutEdge[indexes.first][indexes.second] = INT_MAX;
	
	cout << "--- NOT CHOOSE ---" << endl;
	BranchAndBound(matrixWithoutEdge, newEdges, lowerBound + matrix[indexes.first][indexes.second], minLength, minEdges);
	
	cout << "--------------------------------------------------" << endl;
	cout << "               END" << endl;
	cout << "--------------------------------------------------" << endl;
}