#ifndef GRAPH_H
#define GRAPH_H

#include <vector>

typedef std::vector<std::vector<int>> Matrix;

class Graph {
public:
    explicit Graph(Matrix  adjacencyMatrix);
    Matrix GetKirchhoffMatrix() const;
    int CountSpanningTrees() const;

private:
    Matrix adjMatrix;
    static int Determinant(Matrix matrix, int n);
};

#endif // GRAPH_H
