#include "CSegment.h"

CSegment::CSegment(const std::vector<CVertex>& vertices, const std::set<CEdge>& edges)
        : m_vertices(vertices), m_edges(edges) {}

std::set<int> CSegment::GetContactVertices(const std::vector<CVertex>& graphVertices) {
    std::set<int> contactVertices;
    for (const CVertex& v : m_vertices) {
        for (const CEdge& edge : m_edges) {
            int neighborId = (edge.m_v1.m_id == v.m_id) ? edge.m_v2.m_id : edge.m_v1.m_id;
            if (graphVertices[neighborId].m_id != -1) { // Check if it's a contact vertex
                contactVertices.insert(neighborId);
            }
        }
    }
    return contactVertices;
}

std::set<CEdge> CSegment::GetEdges() const {
    return m_edges;
}

void CSegment::UpdateSegment(CGraph& graphFilled) {
    // Add the edges from the segment to the filled graph
    for (const CEdge& edge : m_edges) {
        graphFilled.AddEdge(edge.m_v1.m_id, edge.m_v2.m_id);
    }
}