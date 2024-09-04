#include "Graph.h"

#include <utility>

Graph::Graph(Matrix  adjacencyMatrix) : adjMatrix(std::move(adjacencyMatrix)) {}

Matrix Graph::GetKirchhoffMatrix() const {
    int size  = adjMatrix.size();
    Matrix laplacian(size , std::vector<int>(size , 0));

    for (int i = 0; i < size ; ++i) {
        int degree = 0; // Степень вершины i
        for (int j = 0; j < size ; ++j) {
            if (adjMatrix[i][j] != 0) {
                degree++;
                laplacian[i][j] = -adjMatrix[i][j]; // Устанавливаем отрицательное значение в матрице Кирхгофа
            }
        }
        laplacian[i][i] = degree; // Диагональный элемент - степень вершины i
    }

    return laplacian;
}

int Graph::Determinant(Matrix matrix, int size) {
    int determinant = 1;

    // Приведение матрицы к треугольному виду
    for (size_t i = 0; i < size; i++) {
        for (size_t j = i + 1; j < size; j++) {
            while (matrix[j][i] != 0) {
                int multiplier = matrix[i][i] / matrix[j][i]; // Коэффициент для приведения
                for (size_t k = i; k < size; k++) {
                    matrix[i][k] -= multiplier * matrix[j][k];
                }
                for (size_t k = i; k < size; k++) {
                    std::swap(matrix[i][k], matrix[j][k]); // Меняем строки местами
                }
                determinant = -determinant; // Меняем знак определителя при смене строк
            }
        }
        determinant *= matrix[i][i]; // Умножаем определитель на диагональный элемент
    }

    return determinant;
}

int Graph::CountSpanningTrees() const {
    int n = adjMatrix.size();
    Matrix kirchhoff = GetKirchhoffMatrix();

    Matrix submatrix(n - 1, std::vector<int>(n - 1));
    for (int i = 1; i < n; i++) {
        for (int j = 1; j < n; j++) {
            submatrix[i - 1][j - 1] = kirchhoff[i][j];
        }
    }

    return Determinant(submatrix, n - 1);
}
