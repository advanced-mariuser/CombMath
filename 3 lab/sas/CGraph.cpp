#include "CGraph.h"
#include <queue>
#include <algorithm>
#include <climits>
#include <iostream>

// Функция добавления рёбер из матрицы смежности
void CGraph::addEdgesFromAdjacencyMatrix(const std::vector<std::vector<int>> &adjacencyMatrix)
{
    int n = adjacencyMatrix.size();
    for (int i = 0; i < n; ++i)
    {
        for (int j = i + 1; j < n; ++j)
        {
            if (adjacencyMatrix[i][j] == 1)
            {
                Vertex &start = getOrCreateVertex(i);
                Vertex &end = getOrCreateVertex(j);
                edges.emplace_back(start, end);
            }
        }
    }
}

// Функция для получения или создания вершины
Vertex &CGraph::getOrCreateVertex(int id)
{
    auto it = vertices.find(id);
    if (it == vertices.end())
    {
        auto result = vertices.emplace(id, Vertex(id));
        return result.first->second;
    }
    return it->second;
}

// Поиск цикла в графе с помощью DFS
bool CGraph::findCycle(int v, std::vector<bool> &visited, std::vector<int> &parent, std::vector<Edge> &cycleEdges)
{
    visited[v] = true;
    for (const auto &edge : edges)
    {
        int u = -1;
        if (edge.start.id == v)
            u = edge.end.id;
        else if (edge.end.id == v)
            u = edge.start.id;

        if (u != -1)
        {
            if (!visited[u])
            {
                parent[u] = v;
                if (findCycle(u, visited, parent, cycleEdges))
                {
                    cycleEdges.push_back(edge);
                    return true;
                }
            }
            else if (parent[v] != u)
            {
                // Найден цикл
                cycleEdges.push_back(edge);
                return true;
            }
        }
    }
    return false;
}

// Поиск сегментов в графе, включая первый цикл
std::vector<Segment> CGraph::findSegments()
{
    std::vector<Segment> segments;
    for (size_t i = 1; i < edges.size(); ++i)
    {
        const auto &edge = edges[i];
        // Проверяем, оба ли конца ребра принадлежат уже уложенному графу G', но само ребро не принадлежит G'
        if (laidOutVertices.find(edge.start.id) != laidOutVertices.end() &&
            laidOutVertices.find(edge.end.id) != laidOutVertices.end() &&
            laidOutEdges.find(i) == laidOutEdges.end())
        {
            // Создаём сегмент с этим ребром
            std::vector<Edge> segmentEdges = {edge};
            std::set<Vertex> contactVertices = {edge.start, edge.end};
            segments.emplace_back(segmentEdges, contactVertices);
        }
    }

    // Отладочный вывод для проверки найденных сегментов
    std::cout << "Found segments:" << std::endl;
    for (const auto &segment : segments) {
        std::cout << "Segment with edges: ";
        for (const auto &edge : segment.edges) {
            std::cout << "(" << edge.start.id << ", " << edge.end.id << ") ";
        }
        std::cout << "and contact vertices: ";
        for (const auto &vertex : segment.contactVertices) {
            std::cout << vertex.id << " ";
        }
        std::cout << std::endl;
    }
    return segments;
}

void CGraph::printLaidOutGraph() {
    std::cout << "Current laid out graph (G') adjacency matrix:" << std::endl;
    int n = vertices.size();
    std::vector<std::vector<int>> adjacencyMatrix(n, std::vector<int>(n, 0));

    for (const auto &edge : edges) {
        if (laidOutEdges.find(&edge - &edges[0]) != laidOutEdges.end()) {
            adjacencyMatrix[edge.start.id][edge.end.id] = 1;
            adjacencyMatrix[edge.end.id][edge.start.id] = 1;
        }
    }

    for (const auto &row : adjacencyMatrix) {
        for (int val : row) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}


// Основная функция проверки планарности графа
bool CGraph::isPlanar()
{
    // Проверка на связность графа
    if (!isConnected())
    {
        return false;
    }

    // Графы с количеством вершин <= 4 всегда планарны
    if (vertices.size() <= 4)
    {
        return true;
    }

    // Проверка на наличие циклов и мостов
    if (hasCycle() && hasBridge())
    {
        return false;
    }

    // Проверка условий теоремы Эйлера для графов с >= 5 вершинами
    if (vertices.size() >= 5)
    {
        int edgesCount = edges.size();
        int verticesCount = vertices.size();
        if (edgesCount > 3 * verticesCount - 6)
        {
            return false; // Применение теоремы Эйлера для проверки планарности
        }
    }

    // Поиск первого цикла в графе
    std::vector<bool> visited(vertices.size(), false);
    std::vector<int> parent(vertices.size(), -1);
    std::vector<Edge> cycleEdges;

    bool cycleFound = false;
    for (const auto &vertex : vertices)
    {
        if (!visited[vertex.first])
        {
            cycleFound = findCycle(vertex.first, visited, parent, cycleEdges);
            if (cycleFound)
                break;
        }
    }

    if (cycleFound)
    {
        std::set<Vertex> contactVertices;
        int i = 0;
        for (const auto &edge : cycleEdges)
        {
            laidOutVertices.insert(edge.start.id);
            laidOutVertices.insert(edge.end.id);
            laidOutEdges.insert(i);
            i++;
        }
    }
    else
    {
        // Если цикл не найден, граф не планарен
        return false;
    }

    while (true)
    {
        std::vector<Segment> segments = findSegments();
        if (segments.empty()) break;

        const Segment *chosenSegment = nullptr;
        int minGamma = INT_MAX;

        // Поиск сегмента с минимальным числом |Γ(S)|
        for (const auto &segment: segments)
        {
            int gamma = calculateGamma(segment);
            // Если гамма сегмента равна 0, граф не планарен
            if (gamma == 0) return false;
            // Выбираем сегмент с минимальной гаммой
            if (gamma < minGamma)
            {
                minGamma = gamma;
                chosenSegment = &segment;
            }
        }

        // Если найден сегмент с минимальной гаммой, укладываем его в граф G'
        if (chosenSegment != nullptr)
        {
            layOutSegment(*chosenSegment);
            printLaidOutGraph();
        } else
        {
            break;
        }
    }
    return true;
}

// Проверка связности графа
bool CGraph::isConnected()
{
    if (vertices.empty()) return true;

    std::set<int> visited;
    std::queue<int> toVisit;
    int start = vertices.begin()->first;

    toVisit.push(start);
    while (!toVisit.empty())
    {
        int currentId = toVisit.front();
        toVisit.pop();

        if (visited.find(currentId) == visited.end())
        {
            visited.insert(currentId);
            for (const auto &edge: edges)
            {
                if (edge.start.id == currentId && visited.find(edge.end.id) == visited.end())
                {
                    toVisit.push(edge.end.id);
                }
                if (edge.end.id == currentId && visited.find(edge.start.id) == visited.end())
                {
                    toVisit.push(edge.start.id);
                }
            }
        }
    }

    return visited.size() == vertices.size();
}

// Проверка наличия циклов в графе
bool CGraph::hasCycle()
{
    std::set<int> visited;  // Множество для отслеживания посещённых вершин
    std::map<int, int> parent;  // Словарь для хранения родительской вершины каждой вершины
    std::queue<int> toVisit;  // Очередь для обхода графа

    // Обходим все вершины графа, чтобы гарантировать проверку всех компонент связности
    for (const auto &pair: vertices)
    {
        int start = pair.first;  // Начальная вершина для текущего обхода
        if (visited.find(start) == visited.end())
        {  // Если вершина ещё не была посещена
            toVisit.push(start);
            parent[start] = -1;  // Устанавливаем родителя начальной вершины как -1 (нет родителя)

            while (!toVisit.empty())
            {  // Пока есть вершины для посещения
                int current = toVisit.front();  // Текущая вершина
                toVisit.pop();

                if (visited.find(current) == visited.end())
                {  // Если текущая вершина ещё не посещена
                    visited.insert(current);  // Помечаем её как посещённую
                    // Проверяем все рёбра, исходящие из текущей вершины
                    for (const auto &edge: edges)
                    {
                        int neighbor = -1;
                        // Определяем соседнюю вершину по ребру
                        if (edge.start.id == current)
                        {
                            neighbor = edge.end.id;
                        } else if (edge.end.id == current)
                        {
                            neighbor = edge.start.id;
                        }
                        // Если найдена соседняя вершина, и это не родительская вершина текущей вершины
                        if (neighbor != -1 && neighbor != parent[current])
                        {
                            // Если соседняя вершина уже посещена, значит, найден цикл
                            if (visited.find(neighbor) != visited.end())
                            {
                                return true;  // Граф содержит цикл
                            }
                            // Иначе добавляем соседнюю вершину в очередь для дальнейшего обхода
                            toVisit.push(neighbor);
                            // Устанавливаем текущую вершину как родительскую для соседней вершины
                            parent[neighbor] = current;
                        }
                    }
                }
            }
        }
    }

    return false;  // Если обход завершился без нахождения цикла, граф не содержит циклов
}


// Рекурсивная функция для поиска мостов
void bridgeDFS(int u, const std::vector<std::vector<int>> &adj, std::vector<bool> &visited, std::vector<int> &disc,
               std::vector<int> &low, std::vector<int> &parent, bool &hasBridge, int &time)
{
    // Помечаем вершину u как посещенную
    visited[u] = true;
    // Устанавливаем время входа в вершину и минимальное время достижения
    disc[u] = low[u] = ++time;

    // Проходим по всем вершинам, смежным с u
    for (int v: adj[u])
    {
        // Если вершина v не посещена, выполняем рекурсивный вызов для v
        if (!visited[v])
        {
            // Устанавливаем u как родителя для v
            parent[v] = u;

            // Рекурсивный вызов для вершины v
            bridgeDFS(v, adj, visited, disc, low, parent, hasBridge, time);

            // После возвращения из рекурсии, обновляем low[u] с минимальным значением low[v]
            low[u] = std::min(low[u], low[v]);

            // Если low[v] больше disc[u], это означает, что нет обратного пути к u через v, и ребро (u, v) является мостом
            if (low[v] > disc[u])
            {
                hasBridge = true;
            }
        }
            // Если v уже посещена и не является родителем u, обновляем low[u] с disc[v]
        else if (v != parent[u])
        {
            low[u] = std::min(low[u], disc[v]);
        }
    }
}


// Проверка наличия мостов в графе
bool CGraph::hasBridge()
{
    int V = vertices.size();
    std::vector<std::vector<int>> adj(V);
    for (const auto &edge: edges)
    {
        adj[edge.start.id].push_back(edge.end.id);
        adj[edge.end.id].push_back(edge.start.id);
    }

    std::vector<bool> visited(V, false);
    std::vector<int> disc(V);
    std::vector<int> low(V);
    std::vector<int> parent(V, -1);
    bool hasBridge = false;
    int time = 0;

    for (int i = 0; i < V; ++i)
    {
        if (!visited[i])
        {
            bridgeDFS(i, adj, visited, disc, low, parent, hasBridge, time);
        }
    }

    return hasBridge;
}

// Вычисление гамма для сегмента
int CGraph::calculateGamma(const Segment &segment)
{
    // Инициализация переменной gammaCount с максимальным значением int
    int gammaCount = INT_MAX;
    // Перебираем все контактные вершины сегмента
    for (const auto &vertex: segment.contactVertices)
    {
        // Инициализация счетчика количества граней, вмещающих текущую контактную вершину
        int faceCount = 0;
        // Перебираем все ребра графа
        for (const auto &edge: edges)
        {
            // Проверяем, принадлежит ли текущая контактная вершина ребру
            // И ребро не уложено в предыдущих шагах
            if ((edge.start.id == vertex.id || edge.end.id == vertex.id) &&
                laidOutEdges.find(&edge - &edges[0]) == laidOutEdges.end())
            {
                faceCount++;
            }
        }
        // Обновляем значение gammaCount, выбирая минимальное значение между текущим значением и количеством граней, вмещающих текущую контактную вершину
        gammaCount = std::min(gammaCount, faceCount);
    }
    return gammaCount;
}


// Обработка сегмента и его добавление к результату
void CGraph::layOutSegment(const Segment &segment)
{
    for (const auto &edge: segment.edges)
    {
        laidOutEdges.insert(&edge - &edges[0]);
    }
    for (const auto &vertex: segment.contactVertices)
    {
        laidOutVertices.insert(vertex.id);
    }
}
