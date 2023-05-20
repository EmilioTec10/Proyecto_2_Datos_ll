#include <QPoint>
#include <valarray>
#include <iostream>
#include "BackTracking.h"

// Función auxiliar para calcular la distancia entre dos QPoints
double BackTracking:: distance(const QPoint& p1, const QPoint& p2) {
    int dx = p2.x() - p1.x();
    int dy = p2.y() - p1.y();
    return std::sqrt(dx * dx + dy * dy);
}

// Función de backtracking para determinar el siguiente paso a seguir
bool BackTracking:: backtrack(const QPoint& current, const QPoint& target, std::vector<QPoint>& moves, int maxDepth) {
    // Verificar si se llegó al punto objetivo
    if (current == target) {
        return true;
    }

    // Verificar si se alcanzó la profundidad máxima
    if (moves.size() >= maxDepth) {
        return false;
    }

    // Movimientos posibles (horizontal, vertical y diagonal)
    std::vector<QPoint> possibleMoves = {
            {current.x() + 1, current.y()},
            {current.x() - 1, current.y()},
            {current.x(), current.y() + 1},
            {current.x(), current.y() - 1},
            {current.x() + 1, current.y() + 1},
            {current.x() - 1, current.y() - 1},
            {current.x() + 1, current.y() - 1},
            {current.x() - 1, current.y() + 1}
    };

    // Calcular la distancia al objetivo para cada movimiento posible
    std::vector<double> distances;
    for (const auto& move : possibleMoves) {
        distances.push_back(distance(move, target));
    }

    // Ordenar los movimientos posibles en función de la distancia al objetivo
    std::sort(distances.begin(), distances.end());

    // Realizar el backtracking en función del orden de las distancias
    for (const auto& dist : distances) {
        for (const auto& move : possibleMoves) {
            if (distance(move, target) == dist) {
                // Realizar el movimiento
                moves.push_back(move);

                // Verificar si se alcanzó el nuevo objetivo
                if (backtrack(move, target, moves, maxDepth)) {
                    return true;
                }

                // Retroceder y deshacer el movimiento
                moves.pop_back();
            }
        }
    }

    return false; // No se encontró una solución válida
}

// Función para determinar el siguiente paso a seguir para llegar de un QPoint a otro
QPoint BackTracking:: determineNextMove(const QPoint& current, const QPoint& target, int maxDepth) {
    std::vector<QPoint> moves;
    moves.push_back(current);

    backtrack(current, target, moves, maxDepth);

    // Verificar si se encontró un movimiento válido
    if (!moves.empty() && moves.size() > 1) {
        std::cout << "(" << moves[1].x() << ", " << moves[1].y() << ")" << std::endl;
        return moves[1]; // El siguiente movimiento después del punto actual
    }

    return current; // Permanecer en el mismo punto si no se encontró un movimiento válido
}

