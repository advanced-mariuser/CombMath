#include "CGraph.h"
#include <iostream>
#include <stack>
#include <algorithm>
#include <unordered_set>
#include <queue>

CGraph::CGraph(int vertexCount)
{
    InitializeVertices(vertexCount);
}

void CGraph::InitializeVertices(int vertexCount)
{
    for (int i = 0; i < vertexCount; ++i)
    {
        m_vertices.emplace_back(i);
    }
}

void CGraph::AddEdge(int v1, int v2)
{
    CEdge edge(m_vertices[v1], m_vertices[v2]);
    // Check if the edge already exists in m_Edges
    if (std::find(m_edges.begin(), m_edges.end(), edge) == m_edges.end())
    {
        m_edges.push_back(edge);
        // Update faces after adding the edge
        UpdateFaces();
    }
}

void CGraph::AddEdgesFromAdjacencyMatrix(const std::vector<std::vector<int>> &adjacencyMatrix)
{
    for (int i = 0; i < adjacencyMatrix.size(); ++i)
    {
        for (int j = 0; j < adjacencyMatrix[i].size(); ++j)
        {
            if (adjacencyMatrix[i][j] == 1)
            {
                AddEdge(i, j);
            }
        }
    }
}

bool CGraph::IsConnected()
{
    std::vector<bool> visited(m_vertices.size(), false);
    DFSUtil(0, visited);
    for (bool v: visited)
    {
        if (!v) return false;
    }
    return true;
}

void CGraph::DFSUtil(int v, std::vector<bool> &visited)
{
    visited[v] = true;
    for (const CEdge &edge: m_edges)
    {
        int neighbor = (edge.m_v1.m_id == v) ? edge.m_v2.m_id : edge.m_v1.m_id;
        if (!visited[neighbor])
        {
            DFSUtil(neighbor, visited);
        }
    }
}

bool CGraph::HasCycle()
{
    std::vector<bool> visited(m_vertices.size(), false);
    for (const CVertex &vertex: m_vertices)
    {
        if (!visited[vertex.m_id])
        {
            if (IsCyclicUtil(vertex.m_id, visited, -1))
            {
                return true;
            }
        }
    }
    return false;
}

bool CGraph::IsCyclicUtil(int v, std::vector<bool> &visited, int parent)
{
    visited[v] = true;
    for (const CEdge &edge: m_edges)
    {
        int neighbor = (edge.m_v1.m_id == v) ? edge.m_v2.m_id : edge.m_v1.m_id;
        if (!visited[neighbor])
        {
            if (IsCyclicUtil(neighbor, visited, v))
            {
                return true;
            }
        } else if (neighbor != parent)
        {
            return true;
        }
    }
    return false;
}

bool CGraph::HasNoBridges()
{
    int V = m_vertices.size();
    std::vector<bool> visited(V, false);
    std::vector<int> disc(V, -1);
    std::vector<int> low(V, -1);
    std::vector<int> parent(V, -1);

    for (int i = 0; i < V; ++i)
    {
        if (!visited[i])
        {
            if (IsBridgeUtil(i, visited, disc, low, parent))
            {
                return false;
            }
        }
    }
    return true;
}

bool CGraph::IsBridgeUtil(int u, std::vector<bool> &visited, std::vector<int> &disc, std::vector<int> &low,
                          std::vector<int> &parent)
{
    static int time = 0;
    visited[u] = true;
    disc[u] = low[u] = ++time;

    for (const CEdge &edge: m_edges)
    {
        int v = (edge.m_v1.m_id == u) ? edge.m_v2.m_id : edge.m_v1.m_id;

        if (!visited[v])
        {
            parent[v] = u;
            if (IsBridgeUtil(v, visited, disc, low, parent))
            {
                return true;
            }
            low[u] = std::min(low[u], low[v]);

            if (low[v] > disc[u])
            {
                return true;
            }
        } else if (v != parent[u])
        {
            low[u] = std::min(low[u], disc[v]);
        }
    }
    return false;
}

std::vector<int> CGraph::FindCycle() {
    std::vector<bool> visited(m_vertices.size(), false);
    std::vector<int> parent(m_vertices.size(), -1);
    std::vector<int> cycle;

    for (int i = 0; i < m_vertices.size(); ++i) {
        if (!visited[i]) {
            if (FindCycleUtil(i, visited, parent, cycle)) {
                // Cycle found, stop searching
                break;
            }
        }
    }

    return cycle;
}

bool CGraph::FindCycleUtil(int v, std::vector<bool>& visited, std::vector<int>& parent, std::vector<int>& cycle) {
    visited[v] = true;

    for (const CEdge& edge : m_edges) {
        int v1 = edge.m_v1.m_id;
        int v2 = edge.m_v2.m_id;
        int neighbor = (v1 == v) ? v2 : v1;

        if (!visited[neighbor]) {
            parent[neighbor] = v;
            if (FindCycleUtil(neighbor, visited, parent, cycle)) {
                return true;
            }
        } else if (neighbor != parent[v]) {
            // Cycle found
            cycle.push_back(neighbor);
            int current = v;
            while (current != neighbor) {
                cycle.push_back(current);
                current = parent[current];
            }
            cycle.push_back(neighbor);
            return true;
        }
    }

    return false;
}

std::vector<std::pair<int, int>> CGraph::GetEdges() const
{
    std::vector<std::pair<int, int>> edgeList;
    edgeList.reserve(m_edges.size());
    for (const CEdge &edge: m_edges)
    {
        edgeList.emplace_back(edge.m_v1.m_id, edge.m_v2.m_id);
    }
    return edgeList;
}

bool CGraph::IsEdgePresent(int v1, int v2) const
{
    // Проходим по всем ребрам и проверяем, существует ли ребро между v1 и v2
    for (const CEdge& edge : m_edges)
    {
        if ((edge.m_v1.m_id == v1 && edge.m_v2.m_id == v2) ||
            (edge.m_v1.m_id == v2 && edge.m_v2.m_id == v1))
        {
            return true;
        }
    }
    return false;
}

std::unordered_map<int, std::vector<int>> CGraph::GetAdjacencyList() const
{
    std::unordered_map<int, std::vector<int>> adjacencyList;

    for (const CEdge& edge : m_edges)
    {
        adjacencyList[edge.m_v1.m_id].push_back(edge.m_v2.m_id);
        adjacencyList[edge.m_v2.m_id].push_back(edge.m_v1.m_id);
    }

    return adjacencyList;
}

std::vector<CVertex> CGraph::FloodFill(int start, int end) const
{
    std::vector<CVertex> connectedComponent;
    std::vector<bool> visited(m_vertices.size(), false);
    std::queue<int> queue;

    std::unordered_map<int, std::vector<int>> adjacencyList = GetAdjacencyList();

    visited[start] = true;
    queue.push(start);

    while (!queue.empty())
    {
        int currentVertex = queue.front();
        queue.pop();

        connectedComponent.push_back(m_vertices[currentVertex]);

        for (int adjacentVertex : adjacencyList[currentVertex])
        {
            if (!visited[adjacentVertex])
            {
                visited[adjacentVertex] = true;
                queue.push(adjacentVertex);
            }
        }
    }

    return connectedComponent;
}


// This method updates the faces of the graph
void CGraph::UpdateFaces() {
    m_faces.clear();
    std::unordered_set<std::pair<int, int>, PairHash> visitedEdges;

    for (int v = 0; v < m_vertices.size(); ++v) {
        std::vector<CEdge> faceEdges;
        DFS(v, visitedEdges, faceEdges, -1, -1);
        if (!faceEdges.empty()) {
            m_faces.emplace_back(faceEdges);
        }
    }
}

void CGraph::DFS(int v, std::unordered_set<std::pair<int, int>, PairHash>& visitedEdges, std::vector<CEdge>& faceEdges, int parent, int startVertex) {
    std::unordered_map<int, std::vector<int>> adjacencyList = GetAdjacencyList();

    for (int neighbor : adjacencyList[v]) {
        std::pair<int, int> edge(std::min(v, neighbor), std::max(v, neighbor));
        if (visitedEdges.find(edge) == visitedEdges.end()) {
            visitedEdges.insert(edge);
            faceEdges.emplace_back(CEdge(m_vertices[v], m_vertices[neighbor]));
            DFS(neighbor, visitedEdges, faceEdges, v, (startVertex == -1) ? neighbor : startVertex);
        } else if (neighbor == parent) {
            continue;
        } else if (neighbor != startVertex) {
            faceEdges.emplace_back(CEdge(m_vertices[v], m_vertices[neighbor]));
        }
    }
}






