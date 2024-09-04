#include "HungarianAlgorithm.h"
#include <algorithm>
#include <limits>

const int HungarianAlgorithm::UNASSIGNED = 0;
const int HungarianAlgorithm::STAR = 1;
const int HungarianAlgorithm::PRIME = 2;

HungarianAlgorithm::HungarianAlgorithm(const Vector& workers, const Vector& jobs, std::function<double(const Vertex&, const Vertex&)> costFunc)
        : _workers(workers), _jobs(jobs), _n(std::max(workers.size(), jobs.size())) {

    _costsMatrix.resize(_n, std::vector<double>(_n, 0.0));
    for (const auto& worker : workers) {
        for (const auto& job : jobs) {
            _costsMatrix[worker.index()][job.index()] = costFunc(worker, job);
        }
    }

    _mask.resize(_n, std::vector<int>(_n, UNASSIGNED));
    _rowCover.resize(_n, 0);
    _colCover.resize(_n, 0);
}

void HungarianAlgorithm::reduceRows() {
    for (int i = 0; i < _n; ++i) {
        double minVal = *std::min_element(_costsMatrix[i].begin(), _costsMatrix[i].end());
        for (int j = 0; j < _n; ++j) {
            _costsMatrix[i][j] -= minVal;
        }
    }
}

void HungarianAlgorithm::reduceColumns() {
    for (int j = 0; j < _n; ++j) {
        double minVal = std::numeric_limits<double>::max();
        for (int i = 0; i < _n; ++i) {
            if (_costsMatrix[i][j] < minVal) {
                minVal = _costsMatrix[i][j];
            }
        }
        for (int i = 0; i < _n; ++i) {
            _costsMatrix[i][j] -= minVal;
        }
    }
}

void HungarianAlgorithm::coverZeros() {
    for (int i = 0; i < _n; ++i) {
        for (int j = 0; j < _n; ++j) {
            if (_costsMatrix[i][j] == 0 && _rowCover[i] == 0 && _colCover[j] == 0) {
                _mask[i][j] = STAR;
                _rowCover[i] = 1;
                _colCover[j] = 1;
            }
        }
    }
    std::fill(_rowCover.begin(), _rowCover.end(), 0);
    std::fill(_colCover.begin(), _colCover.end(), 0);
}

bool HungarianAlgorithm::step4() {
    int row = -1, col = -1;
    bool done = false;
    while (!done) {
        if (!findZero(row, col)) {
            done = true;
            return false;
        } else {
            _mask[row][col] = PRIME;
            int starCol = std::find(_mask[row].begin(), _mask[row].end(), STAR) - _mask[row].begin();
            if (starCol < _n) {
                _rowCover[row] = 1;
                _colCover[starCol] = 0;
            } else {
                return true;
            }
        }
    }
    return false;
}

bool HungarianAlgorithm::findZero(int& row, int& col) {
    for (row = 0; row < _n; ++row) {
        for (col = 0; col < _n; ++col) {
            if (_costsMatrix[row][col] == 0 && !_rowCover[row] && !_colCover[col]) {
                return true;
            }
        }
    }
    return false;
}

void HungarianAlgorithm::step5() {
    bool done = false;
    std::vector<std::pair<int, int>> path;
    int row = -1, col = -1;
    for (int r = 0; r < _n; ++r) {
        col = std::find(_mask[r].begin(), _mask[r].end(), PRIME) - _mask[r].begin();
        if (col < _n) {
            row = r;
            break;
        }
    }
    path.emplace_back(row, col);

    bool found = false;
    while (!found) {
        int starRow = -1;
        for (int r = 0; r < _n; ++r) {
            if (_mask[r][col] == STAR) {
                starRow = r;
                break;
            }
        }
        if (starRow == -1) {
            found = true;
        } else {
            path.emplace_back(starRow, col);
            row = starRow;
            col = std::find(_mask[row].begin(), _mask[row].end(), PRIME) - _mask[row].begin();
            path.emplace_back(row, col);
        }
    }

    for (const auto& p : path) {
        if (_mask[p.first][p.second] == STAR) {
            _mask[p.first][p.second] = UNASSIGNED;
        } else {
            _mask[p.first][p.second] = STAR;
        }
    }
    std::fill(_rowCover.begin(), _rowCover.end(), 0);
    std::fill(_colCover.begin(), _colCover.end(), 0);
    for (auto& row : _mask) {
        std::replace(row.begin(), row.end(), PRIME, UNASSIGNED);
    }
}

void HungarianAlgorithm::findSmallestUncoveredValue() {
    double minVal = std::numeric_limits<double>::max();
    for (int i = 0; i < _n; ++i) {
        if (_rowCover[i] == 0) {
            for (int j = 0; j < _n; ++j) {
                if (_colCover[j] == 0 && _costsMatrix[i][j] < minVal) {
                    minVal = _costsMatrix[i][j];
                }
            }
        }
    }
    for (int i = 0; i < _n; ++i) {
        if (_rowCover[i] == 1) {
            for (int j = 0; j < _n; ++j) {
                _costsMatrix[i][j] += minVal;
            }
        }
    }
    for (int j = 0; j < _n; ++j) {
        if (_colCover[j] == 0) {
            for (int i = 0; i < _n; ++i) {
                _costsMatrix[i][j] -= minVal;
            }
        }
    }
}

bool HungarianAlgorithm::isOptimal() {
    int count = 0;
    for (int i = 0; i < _n; ++i) {
        for (int j = 0; j < _n; ++j) {
            if (_mask[i][j] == STAR) {
                ++count;
            }
        }
    }
    return count >= _n;
}

std::vector<int> HungarianAlgorithm::getOptimalAssignment() {
    reduceRows();
    reduceColumns();
    coverZeros();
    while (!isOptimal()) {
        if (step4()) {
            step5();
        } else {
            findSmallestUncoveredValue();
        }
    }
    std::vector<int> assignment(_n, -1);
    for (int i = 0; i < _n; ++i) {
        for (int j = 0; j < _n; ++j) {
            if (_mask[i][j] == STAR) {
                assignment[i] = j;
                break;
            }
        }
    }
    return assignment;
}
