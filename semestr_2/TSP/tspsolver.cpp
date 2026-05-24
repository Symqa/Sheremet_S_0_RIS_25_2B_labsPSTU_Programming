#include "tspsolver.h"
#include <algorithm>
#include <queue>

// ---- Helpers ----

QVector<QVector<int>> TSPSolver::copyMatrix(const QVector<QVector<int>> &m) {
    return m;
}

int TSPSolver::rowReduce(QVector<QVector<int>> &m, int n) {
    int reduction = 0;
    for (int i = 0; i < n; i++) {
        int minVal = BNB_INF;
        for (int j = 0; j < n; j++)
            if (m[i][j] < minVal) minVal = m[i][j];
        if (minVal == BNB_INF || minVal == 0) continue;
        reduction += minVal;
        for (int j = 0; j < n; j++)
            if (m[i][j] != BNB_INF) m[i][j] -= minVal;
    }
    return reduction;
}

int TSPSolver::colReduce(QVector<QVector<int>> &m, int n) {
    int reduction = 0;
    for (int j = 0; j < n; j++) {
        int minVal = BNB_INF;
        for (int i = 0; i < n; i++)
            if (m[i][j] < minVal) minVal = m[i][j];
        if (minVal == BNB_INF || minVal == 0) continue;
        reduction += minVal;
        for (int i = 0; i < n; i++)
            if (m[i][j] != BNB_INF) m[i][j] -= minVal;
    }
    return reduction;
}

int TSPSolver::reduceMatrix(QVector<QVector<int>> &m, int n) {
    return rowReduce(m, n) + colReduce(m, n);
}

QVector<QVector<int>> TSPSolver::getChildMatrix(const QVector<QVector<int>> &parent,
                                                  int i, int j, int n) {
    auto m = copyMatrix(parent);
    // Set entire row i and col j to INF
    for (int k = 0; k < n; k++) {
        m[i][k] = BNB_INF;
        m[k][j] = BNB_INF;
    }
    return m;
}

bool TSPSolver::isVisited(const QVector<int> &path, int v) {
    return path.contains(v);
}

// ---- Main Solver ----

TSPResult TSPSolver::solve(const QVector<QVector<int>> &dist, const QStringList &names) {
    TSPResult result;
    int n = dist.size();
    if (n < 2) { result.steps << "Нужно минимум 2 вершины."; return result; }

    // Check connectivity: every row and col must have at least one finite value (off diagonal)
    for (int i = 0; i < n; i++) {
        bool hasOut = false, hasIn = false;
        for (int j = 0; j < n; j++) {
            if (i != j && dist[i][j] < BNB_INF) hasOut = true;
            if (i != j && dist[j][i] < BNB_INF) hasIn = true;
        }
        if (!hasOut || !hasIn) {
            result.steps << QString("Граф не имеет решения: вершина %1 изолирована.").arg(names[i]);
            return result;
        }
    }

    result.steps << "=== Метод ветвей и границ (TSP) ===";
    result.steps << QString("Вершин: %1").arg(n);

    // Priority queue: min-heap by cost
    struct CmpNode {
        bool operator()(const TSPSolver::Node &a, const TSPSolver::Node &b) {
            return a.cost > b.cost; // min-heap
        }
    };
    std::priority_queue<Node, std::vector<Node>, CmpNode> pq;

    // Root node
    Node root;
    root.reducedMatrix = dist;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (i == j) root.reducedMatrix[i][j] = BNB_INF;

    root.cost = reduceMatrix(root.reducedMatrix, n);
    root.vertex = 0;
    root.level = 0;
    root.path = {0};

    result.steps << QString("Начальная нижняя граница (редукция): %1").arg(root.cost);

    pq.push(root);
    int bestCost = BNB_INF;
    QVector<int> bestPath;
    int iterations = 0;
    const int MAX_ITER = 100000;

    while (!pq.empty() && iterations < MAX_ITER) {
        iterations++;
        Node curr = pq.top(); pq.pop();

        if (curr.cost >= bestCost) continue;

        if (curr.level == n - 1) {
            // Complete tour: try to return to start
            if (curr.reducedMatrix[curr.vertex][0] != BNB_INF) {
                int totalCost = curr.cost + curr.reducedMatrix[curr.vertex][0];
                if (totalCost < bestCost) {
                    bestCost = totalCost;
                    bestPath = curr.path;
                    bestPath.append(0);
                    result.steps << QString("Найден маршрут: стоимость %1").arg(bestCost);
                    QString pathStr = "  Путь: ";
                    for (int v : bestPath) pathStr += names[v] + " → ";
                    pathStr.chop(3);
                    result.steps << pathStr;
                }
            }
            continue;
        }

        // Expand children
        for (int j = 0; j < n; j++) {
            if (isVisited(curr.path, j)) continue;
            if (curr.reducedMatrix[curr.vertex][j] == BNB_INF) continue;

            Node child;
            child.level = curr.level + 1;
            child.vertex = j;
            child.path = curr.path;
            child.path.append(j);

            child.reducedMatrix = getChildMatrix(curr.reducedMatrix, curr.vertex, j, n);

            // Block sub-tour: for each edge (path[k], path[k+1]), block reverse
            // More robust sub-tour prevention
            for (int k = 0; k + 1 < child.path.size(); k++) {
                int a = child.path[k+1], b = child.path[k];
                if (a < n && b < n) child.reducedMatrix[a][b] = BNB_INF;
            }

            // Prevent premature cycle closure: forbid return to start until the last step
            if (child.level < n - 1) {
                child.reducedMatrix[j][0] = BNB_INF;
            }

            child.cost = curr.cost + curr.reducedMatrix[curr.vertex][j];
            child.cost += reduceMatrix(child.reducedMatrix, n);

            if (child.cost < bestCost) {
                pq.push(child);
            }
        }
    }

    if (bestCost < BNB_INF) {
        result.solvable = true;
        result.cost = bestCost;
        result.tour = bestPath;
        result.steps << "--- Итог ---";
        result.steps << QString("Оптимальная стоимость маршрута: %1").arg(bestCost);
        QString finalPath = "Маршрут: ";
        for (int v : bestPath) finalPath += names[v] + " → ";
        finalPath.chop(3);
        result.steps << finalPath;
    } else {
        result.steps << "Решение не найдено (граф не является гамильтоновым).";
    }

    return result;
}
