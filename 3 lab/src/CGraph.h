#ifndef CGRAPH_H
#define CGRAPH_H

#include <vector>
#include <iostream>
#include <queue>
#include <set>

class CGraph {
public:
    CGraph(int vertexCount);
    void AddEdge(int v1, int v2);
    void AddEdgesFromAdjacencyMatrix(const std::vector<std::vector<int>>& adjacencyMatrix);
    bool IsConnected();
    bool HasCycle();
    bool HasNoBridges();
    std::vector<int> FindCycle();

    int GetVertexCount() const;
    const std::vector<std::vector<int>>& GetAdjacencyList() const;

private:
    int vertexCount;
    std::vector<std::vector<int>> adjacencyList;
    void DFSUtil(int v, std::vector<bool>& visited);
    bool IsCyclicUtil(int v, std::vector<bool>& visited, int parent);
    bool IsBridgeUtil(int u, std::vector<bool>& visited, std::vector<int>& disc, std::vector<int>& low, std::vector<int>& parent);
    void FindCycleUtil(int v, std::vector<bool>& visited, std::vector<int>& parent, std::vector<int>& cycle, bool& found);
};

#endif // CGRAPH_H
