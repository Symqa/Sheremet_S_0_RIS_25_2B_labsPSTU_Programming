#pragma once
#include <QVector>
#include <QString>
#include <QStringList>
#include <limits>

static const int BNB_INF = std::numeric_limits<int>::max() / 2;

struct TSPResult {
    QVector<int> tour;    // 0-based node indices, includes return to start
    int cost = BNB_INF;
    bool solvable = false;
    QStringList steps;    // step-by-step log
};

class TSPSolver {
public:
    // Branch and Bound
    static TSPResult solve(const QVector<QVector<int>> &dist, const QStringList &names);

private:
    struct Node {
        QVector<QVector<int>> reducedMatrix;
        QVector<int>  path;
        int           cost;
        int           vertex;
        int           level;
    };

    static QVector<QVector<int>> copyMatrix(const QVector<QVector<int>> &m);
    static int rowReduce(QVector<QVector<int>> &m, int n);
    static int colReduce(QVector<QVector<int>> &m, int n);
    static int reduceMatrix(QVector<QVector<int>> &m, int n);
    static QVector<QVector<int>> getChildMatrix(const QVector<QVector<int>> &parent,
                                                 int i, int j, int n);
    static bool isVisited(const QVector<int> &path, int v);
};
