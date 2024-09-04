#ifndef CGRAPH_H
#define CGRAPH_H

#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <stack>
#include "../Edge/CEdge.h"
#include "../Face/CFace.h"

struct PairHash {
    template<typename T1, typename T2>
    std::size_t operator () (const std::pair<T1,T2> &pair) const {
        auto h1 = std::hash<T1>{}(pair.first);
        auto h2 = std::hash<T2>{}(pair.second);
        return h1 ^ h2;
    }
};

class CGraph {
public:
    std::vector<CVertex> m_vertices;
    std::vector<CEdge> m_edges;
    std::vector<CFace> m_faces;

    explicit CGraph(int vertexCount);
    void AddEdgesFromAdjacencyMatrix(const std::vector<std::vector<int>>& adjacencyMatrix);
    bool IsConnected();
    bool HasCycle();
    bool HasNoBridges();
    std::vector<int> FindCycle();
    std::vector<std::pair<int, int>> GetEdges() const;
    std::vector<CVertex> FloodFill(int start, int end) const;
    bool IsEdgePresent(int v1, int v2) const;

    void AddEdge(int v1, int v2);

private:
    void InitializeVertices(int vertexCount);
    bool IsCyclicUtil(int v, std::vector<bool>& visited, int parent);
    void DFSUtil(int v, std::vector<bool>& visited);

    void BridgeUtil(int u, std::vector<bool> visited, std::vector<int> tin, std::vector<int> low, int &time, int parent);

    bool IsBridgeUtil(int u, std::vector<bool> &visited, std::vector<int> &disc, std::vector<int> &low,
                      std::vector<int> &parent);

    bool isEdgeValid(int v1, int v2, const std::vector<int> &cycle);

    bool FindCycleUtil(int v, std::vector<bool> &visited, std::vector<int> &parent, std::vector<int> &cycle);

    std::unordered_map<int, std::vector<int>> GetAdjacencyList() const;

    void UpdateFaces();

    void
    DFS(int v, std::unordered_set<std::pair<int, int>, PairHash> &visitedEdges, std::vector<CEdge> &faceEdges,
        int parent,
        int startVertex);
};

#endif // CGRAPH_H
