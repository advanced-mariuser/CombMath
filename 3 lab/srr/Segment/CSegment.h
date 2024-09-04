#ifndef CSEGMENT_H
#define CSEGMENT_H

#include <vector>
#include <set>
#include "../Vertex/CVertex.h"
#include "../Edge/CEdge.h"
#include "../Graph/CGraph.h"

class CSegment {
public:
    CSegment(const std::vector<CVertex>& vertices, const std::set<CEdge>& edges);
    std::set<int> GetContactVertices(const std::vector<CVertex>& graphVertices);
    std::set<CEdge> GetEdges() const;
    void UpdateSegment(CGraph& graphFilled);

private:
    std::vector<CVertex> m_vertices;
    std::set<CEdge> m_edges;
};

#endif // CSEGMENT_H
