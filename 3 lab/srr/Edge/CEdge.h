#ifndef CEDGE_H
#define CEDGE_H

#include "../Vertex/CVertex.h"

class CEdge {
public:
    CVertex m_v1;
    CVertex m_v2;

    CEdge(CVertex v1, CVertex v2);

    bool operator<(const CEdge& other) const {
        if (m_v1.m_id != other.m_v1.m_id) {
            return m_v1.m_id < other.m_v1.m_id;
        }
        return m_v2.m_id < other.m_v2.m_id;
    }

    bool operator==(const CEdge& other) const;
};

#endif // CEDGE_H