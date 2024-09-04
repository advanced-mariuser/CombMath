#include "CEdge.h"

CEdge::CEdge(CVertex v1, CVertex v2) : m_v1(v1), m_v2(v2) {}

bool CEdge::operator==(const CEdge& other) const {
    return (m_v1.m_id == other.m_v1.m_id && m_v2.m_id == other.m_v2.m_id) ||
           (m_v1.m_id == other.m_v2.m_id && m_v2.m_id == other.m_v1.m_id);
}
