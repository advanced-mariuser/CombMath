#ifndef CFACE_H
#define CFACE_H

#include <vector>
#include "../Edge/CEdge.h"

class CFace {
public:
    std::vector<CEdge> m_edges;

    CFace(const std::vector<CEdge>& edges);
};

#endif // CFACE_H
