#include "CGraph.h"

CGraph::CGraph(int vertexCount) : vertexCount(vertexCount) {
    adjacencyList.resize(vertexCount);
}

void CGraph::AddEdge(int v1, int v2) {
    adjacencyList[v1].push_back(v2);
    adjacencyList[v2].push_back(v1);
}

void CGraph::AddEdgesFromAdjacencyMatrix(const std::vector<std::vector<int>>& adjacencyMatrix) {
    for (int i = 0; i < adjacencyMatrix.size(); ++i) {
        for (int j = 0; j < adjacencyMatrix[i].size(); ++j) {
            if (adjacencyMatrix[i][j] == 1) {
                AddEdge(i, j);
            }
        }
    }
}

void CGraph::DFSUtil(int v, std::vector<bool>& visited) {
    visited[v] = true;
    for (int neighbor : adjacencyList[v]) {
        if (!visited[neighbor]) {
            DFSUtil(neighbor, visited);
        }
    }
}

bool CGraph::IsConnected() {
    std::vector<bool> visited(vertexCount, false);
    DFSUtil(0, visited);
    for (bool v : visited) {
        if (!v) return false;
    }
    return true;
}

bool CGraph::IsCyclicUtil(int v, std::vector<bool>& visited, int parent) {
    visited[v] = true;
    for (int neighbor : adjacencyList[v]) {
        if (!visited[neighbor]) {
            if (IsCyclicUtil(neighbor, visited, v)) {
                return true;
            }
        } else if (neighbor != parent) {
            return true;
        }
    }
    return false;
}

bool CGraph::HasCycle() {
    std::vector<bool> visited(vertexCount, false);
    for (int i = 0; i < vertexCount; ++i) {
        if (!visited[i]) {
            if (IsCyclicUtil(i, visited, -1)) {
                return true;
            }
        }
    }
    return false;
}

bool CGraph::IsBridgeUtil(int u, std::vector<bool>& visited, std::vector<int>& disc, std::vector<int>& low, std::vector<int>& parent) {
    static int time = 0;
    visited[u] = true;
    disc[u] = low[u] = ++time;

    for (int v : adjacencyList[u]) {
        if (!visited[v]) {
            parent[v] = u;
            if (IsBridgeUtil(v, visited, disc, low, parent)) {
                return true;
            }
            low[u] = std::min(low[u], low[v]);
            if (low[v] > disc[u]) {
                return true;
            }
        } else if (v != parent[u]) {
            low[u] = std::min(low[u], disc[v]);
        }
    }
    return false;
}

bool CGraph::HasNoBridges() {
    std::vector<bool> visited(vertexCount, false);
    std::vector<int> disc(vertexCount, -1);
    std::vector<int> low(vertexCount, -1);
    std::vector<int> parent(vertexCount, -1);

    for (int i = 0; i < vertexCount; ++i) {
        if (!visited[i]) {
            if (IsBridgeUtil(i, visited, disc, low, parent)) {
                return false;
            }
        }
    }
    return true;
}

void CGraph::FindCycleUtil(int v, std::vector<bool>& visited, std::vector<int>& parent, std::vector<int>& cycle, bool& found) {
    if (found) return;
    visited[v] = true;
    for (int neighbor : adjacencyList[v]) {
        if (!visited[neighbor]) {
            parent[neighbor] = v;
            FindCycleUtil(neighbor, visited, parent, cycle, found);
        } else if (parent[v] != neighbor && !found) {
            int cur = v;
            cycle.push_back(v);
            while (cur != neighbor) {
                cycle.push_back(parent[cur]);
                cur = parent[cur];
            }
            cycle.push_back(neighbor);
            found = true;
            return;
        }
    }
}

std::vector<int> CGraph::FindCycle() {
    std::vector<bool> visited(vertexCount, false);
    std::vector<int> parent(vertexCount, -1);
    std::vector<int> cycle;
    bool found = false;

    for (int i = 0; i < vertexCount; ++i) {
        if (!visited[i] && !found) {
            FindCycleUtil(i, visited, parent, cycle, found);
        }
    }
    return cycle;
}

int CGraph::GetVertexCount() const {
    return vertexCount;
}

const std::vector<std::vector<int>>& CGraph::GetAdjacencyList() const {
    return adjacencyList;
}
