#ifndef HUNGARIAN_ALGORITHM_H
#define HUNGARIAN_ALGORITHM_H

#include <vector>
#include <functional>
#include <limits>
#include "Vector.h"

class HungarianAlgorithm {
public:
    HungarianAlgorithm(const Vector& workers, const Vector& jobs, std::function<double(const Vertex&, const Vertex&)> costFunc);
    std::vector<int> getOptimalAssignment();

    static const int UNASSIGNED;
private:
    void reduceRows();
    void reduceColumns();
    void coverZeros();
    bool step4();
    bool findZero(int& row, int& col);
    void step5();
    bool isOptimal();
    void findSmallestUncoveredValue();

    Vector _workers;
    Vector _jobs;
    std::vector<std::vector<double>> _costsMatrix;
    std::vector<int> _rowCover;
    std::vector<int> _colCover;
    std::vector<std::vector<int>> _mask;
    int _n;

    static const int STAR;
    static const int PRIME;
};

#endif // HUNGARIAN_ALGORITHM_H
