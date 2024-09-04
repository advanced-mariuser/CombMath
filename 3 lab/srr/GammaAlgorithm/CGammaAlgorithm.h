#ifndef CGAMMAALGORITHM_H
#define CGAMMAALGORITHM_H

#include "../Vertex/CVertex.h"
#include "../Graph/CGraph.h"
#include "../Segment/CSegment.h"
#include "../Face/CFace.h"
#include <vector>

class CGammaAlgorithm {
public:
    explicit CGammaAlgorithm(CGraph &graph);
    void Run();

private:
    CGraph& m_graph;
    CGraph m_graphFilled;
    std::vector<CSegment> m_segments;

    void Initialize();
    void GeneralStep();
    static void Completion();

    std::vector<CSegment> FindSegments() const;
};

#endif // CGAMMAALGORITHM_H
