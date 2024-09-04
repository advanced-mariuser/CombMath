#ifndef CGAMMAALGORITHM_H
#define CGAMMAALGORITHM_H

#include "CGraph.h"
#include <iostream>
#include <algorithm>

class CGammaAlgorithm {
public:
    CGammaAlgorithm(CGraph& graph);
    void Run();

private:
    void Initialize();
    void GeneralStep();
    void Completion();
    CGraph& m_graph;
    CGraph m_graphFilled;
    std::vector<int> m_cycle;
};

#endif // CGAMMAALGORITHM_H
