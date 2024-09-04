#include "CGammaAlgorithm.h"
#include <iostream>
#include <algorithm>

CGammaAlgorithm::CGammaAlgorithm(CGraph &graph) : m_graph(graph), m_graphFilled(0) { }

void CGammaAlgorithm::Run()
{
    Initialize();
    while (!m_segments.empty())
    {
        GeneralStep();
    }
    Completion();
}

std::vector<CSegment> CGammaAlgorithm::FindSegments() const
{
    std::vector<CSegment> segments;

    // Iterate over all edges in the filled graph
    for (const CEdge& edge : m_graphFilled.m_edges)
    {
        // Check if the edge is not in the original graph but connects two vertices in the original graph
        if (!m_graph.IsEdgePresent(edge.m_v1.m_id, edge.m_v2.m_id))
        {
            // Find connected component excluding the filled graph
            std::vector<CVertex> connectedComponent = m_graph.FloodFill(edge.m_v1.m_id, edge.m_v2.m_id);

            // Construct the segment with the edge and connected component
            CSegment segment(connectedComponent, std::set<CEdge>{edge});

            // Add the segment to the list
            segments.push_back(segment);
        }
    }

    return segments;
}

void CGammaAlgorithm::Initialize()
{
    std::vector<int> cycle = m_graph.FindCycle();
    if (cycle.empty())
    {
        std::cerr << "No simple cycle found. The graph might not be suitable." << std::endl;
        return;
    }

    m_graphFilled = CGraph(cycle.size());

    // Represent cycle as an edge and initialize segments
    std::set<CEdge> initialCycleEdges;
    for (size_t i = 0; i < cycle.size(); ++i)
    {
        int next = (i + 1) % cycle.size();
        m_graphFilled.AddEdge(cycle[i], cycle[next]);
    }

    m_segments = FindSegments();
}

void CGammaAlgorithm::GeneralStep()
{
    for (CSegment &segment: m_segments)
    {
        std::set<CEdge> gammaS = segment.GetEdges();
        if (gammaS.empty())
        {
            std::cerr << "Graph is not planar." << std::endl;
            return;
        }
    }

    auto minSegmentIt = std::min_element(m_segments.begin(), m_segments.end(),
                                         [](const CSegment &s1, const CSegment &s2)
                                         {
                                             return s1.GetEdges().size() < s2.GetEdges().size();
                                         });

    if (minSegmentIt != m_segments.end())
    {
        minSegmentIt->UpdateSegment(m_graphFilled);
        m_segments = FindSegments(); // Update segments after stacking
    }
}

void CGammaAlgorithm::Completion()
{
    std::cout << "Planar stacking of the original graph constructed." << std::endl;
}
