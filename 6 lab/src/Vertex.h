#ifndef VERTEX_H
#define VERTEX_H

class Vertex {
public:
    Vertex(int idx) : _index(idx) {}
    int index() const { return _index; }

private:
    int _index;
};

#endif // VERTEX_H
