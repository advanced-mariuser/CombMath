#ifndef VECTOR_H
#define VECTOR_H

#include <vector>
#include "Vertex.h"

class Vector : public std::vector<Vertex> {
public:
    size_t size() const {
        return std::vector<Vertex>::size();
    }

    void push_back(const Vertex& vertex) {
        std::vector<Vertex>::push_back(vertex);
    }
};

#endif // VECTOR_H
