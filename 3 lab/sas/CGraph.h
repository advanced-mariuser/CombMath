#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <set>
#include <map>
#include <utility>

struct Vertex {
    int id;
    Vertex(int id) : id(id) {}
    bool operator<(const Vertex& other) const { return id < other.id; }
};

struct Edge {
    Vertex start;
    Vertex end;
    Edge(Vertex start, Vertex end) : start(start), end(end) {}
};

struct Segment {
    std::vector<Edge> edges;
    std::set<Vertex> contactVertices;
    Segment(std::vector<Edge> edges, std::set<Vertex> contactVertices)
            : edges(edges), contactVertices(contactVertices) {}
};

class CGraph {
private:
    std::map<int, Vertex> vertices;
    std::vector<Edge> edges;
    std::set<int> laidOutVertices;
    std::set<size_t> laidOutEdges;

    Vertex& getOrCreateVertex(int id);
    std::vector<Segment> findSegments();
    bool isConnected();
    bool hasCycle();
    bool hasBridge();
    int calculateGamma(const Segment& segment);
    void layOutSegment(const Segment& segment);

public:
    void addEdgesFromAdjacencyMatrix(const std::vector<std::vector<int>>& adjacencyMatrix);
    bool isPlanar();
    void printLaidOutGraph();

    bool findCycle(int v, std::vector<bool> &visited, std::vector<int> &parent, std::vector<Edge> &cycleEdges);
};

#endif // GRAPH_H
