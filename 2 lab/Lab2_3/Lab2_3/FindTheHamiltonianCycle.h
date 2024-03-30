#pragma once
#include <vector>

using namespace std;

int GetLength(vector<vector<int>> graph, vector<pair<int, int>> edges);
void BranchAndBound(vector<vector<int>>& matrix, vector<pair<int, int>>& edges, int length, int& minLength, vector<pair<int, int>>& minEdges);