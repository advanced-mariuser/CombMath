#include "CGammaAlgorithm.h"

CGammaAlgorithm::CGammaAlgorithm(CGraph& graph) : m_graph(graph), m_graphFilled(graph.GetVertexCount()) {}

void CGammaAlgorithm::Run() {
    Initialize();
    GeneralStep();
    Completion();
}

//Находит цикл в исходном графе m_graph и добавляет этот цикл в m_graphFilled.
void CGammaAlgorithm::Initialize() {
    m_cycle = m_graph.FindCycle();  // Поиск цикла в m_graph.
    if (m_cycle.empty()) {  // Если цикл не найден, вывод сообщения об ошибке и выход из функции.
        std::cerr << "No cycle found in the graph during initialization." << std::endl;
        return;
    }
    // Добавление ребер цикла в m_graphFilled.
    for (size_t i = 0; i < m_cycle.size() - 1; ++i) {
        m_graphFilled.AddEdge(m_cycle[i], m_cycle[i + 1]);
    }
    // Добавление ребра для замыкания цикла, соединяя последнюю вершину с первой.
    m_graphFilled.AddEdge(m_cycle.back(), m_cycle.front());
}

//Добавляет ребра из исходного графа m_graph в m_graphFilled, пока не останется больше ребер, которые можно добавить, не нарушая планарность.
void CGammaAlgorithm::GeneralStep() {
    while (true) {
        bool added = false;  // Флаг для отслеживания, было ли добавлено ребро в текущей итерации.
        // Итерация по всем вершинам m_graphFilled.
        for (int v = 0; v < m_graphFilled.GetVertexCount(); ++v) {
            // Итерация по списку смежности исходного графа m_graph.
            for (int u : m_graph.GetAdjacencyList()[v]) {
                // Если у вершины v есть список смежности и ребро (v, u) отсутствует в m_graphFilled, добавить его.
                if (!m_graphFilled.GetAdjacencyList()[v].empty() &&
                    std::find(m_graphFilled.GetAdjacencyList()[v].begin(), m_graphFilled.GetAdjacencyList()[v].end(), u) == m_graphFilled.GetAdjacencyList()[v].end()) {
                    m_graphFilled.AddEdge(v, u);  // Добавить ребро (v, u) в m_graphFilled.
                    added = true;  // Установить флаг в true, указывая на добавление ребра.
                }
            }
        }
        if (!added) break;  // Если в текущей итерации не было добавлено ни одного ребра, выйти из цикла.
    }
}

void CGammaAlgorithm::Completion() {
    std::cout << "Graph successfully processed using Gamma Algorithm." << std::endl;
}