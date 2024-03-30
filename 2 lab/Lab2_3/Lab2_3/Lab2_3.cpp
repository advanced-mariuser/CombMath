#include <../../FindTheHamiltonianCycle.h>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n = 6;

    vector<vector<int>> matrix = {
        { INT_MAX, 5, 7, 6, 8, 3 },
        { 1, INT_MAX, 8, 4, 6, 2 },
        { 3, 9, INT_MAX, 6, 5, 3 },
        { 7, 8, 4, INT_MAX, 4, 2 },
        { 2, 7, 5, 6, INT_MAX, 6 },
        { 5, 2, 6, 4, 5, INT_MAX }
    };

    int min_length = INT_MAX;
    vector<pair<int, int>> min_path;
    vector<pair<int, int>> path;
    BranchAndBound(matrix, path, 0, min_length, min_path);

    std::cout << "Min Path: ";
    for (auto edge : min_path)
    {
        std::cout << ++edge.first << " -> " << ++edge.second << std::endl;
    }
    int length = GetLength(matrix, min_path);
    std::cout << "Length: " << length << std::endl;

    return 0;
}
