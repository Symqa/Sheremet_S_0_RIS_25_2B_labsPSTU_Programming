#include "mainwindow.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPainter>
#include <QGroupBox>
#include <QSplitter>
#include <QHeaderView>
#include <QMessageBox>
#include <QQueue>
#include <QStack>
#include <QPen>
#include <QBrush>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsLineItem>
#include <QGraphicsEllipseItem>
#include <QGraphicsTextItem>
#include <QInputDialog>
#include <cmath>
#include <algorithm>


class GraphScene : public QGraphicsScene {
public:
    GraphScene(QObject *p = nullptr) : QGraphicsScene(p) {}
};

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), numVertices(0), matrixChanging(false)
{
    setWindowTitle("Graph Algorithms - Qt");
    setupUI();
    loadDefaultGraph();
}

void MainWindow::setupUI() {
    QWidget *central = new QWidget(this);
    setCentralWidget(central);
    QHBoxLayout *mainLayout = new QHBoxLayout(central);


    QVBoxLayout *leftLayout = new QVBoxLayout();
    scene = new GraphScene(this);
    scene->setSceneRect(0, 0, 600, 500);
    view = new QGraphicsView(scene);
    view->setMinimumSize(600, 500);
    view->setRenderHint(QPainter::Antialiasing);
    leftLayout->addWidget(new QLabel("<b>Визуализация графа</b>"));
    leftLayout->addWidget(view);

    QVBoxLayout *rightLayout = new QVBoxLayout();
    rightLayout->setSpacing(6);


    QGroupBox *matGroup = new QGroupBox("Матрица смежности");
    QVBoxLayout *matLayout = new QVBoxLayout(matGroup);
    matrixTable = new QTableWidget();
    matrixTable->setMinimumHeight(180);
    matLayout->addWidget(matrixTable);
    QPushButton *applyMatBtn = new QPushButton("Применить матрицу");
    matLayout->addWidget(applyMatBtn);
    connect(applyMatBtn, &QPushButton::clicked, this, &MainWindow::updateGraphFromMatrix);
    rightLayout->addWidget(matGroup);


    QGroupBox *editGroup = new QGroupBox("Редактирование графа");
    QVBoxLayout *editLayout = new QVBoxLayout(editGroup);


    QHBoxLayout *addVRow = new QHBoxLayout();
    QPushButton *addVBtn = new QPushButton("Добавить вершину");
    addVRow->addWidget(addVBtn);
    connect(addVBtn, &QPushButton::clicked, this, &MainWindow::addVertex);


    removeSpin = new QSpinBox(); removeSpin->setMinimum(1); removeSpin->setPrefix("Вершина ");
    QPushButton *remVBtn = new QPushButton("Удалить вершину");
    addVRow->addWidget(removeSpin);
    addVRow->addWidget(remVBtn);
    connect(remVBtn, &QPushButton::clicked, this, &MainWindow::removeVertex);
    editLayout->addLayout(addVRow);

    QHBoxLayout *edgeRow = new QHBoxLayout();
    edgeRow->addWidget(new QLabel("Из:"));
    fromSpin = new QSpinBox(); fromSpin->setMinimum(1); fromSpin->setMaximum(99);
    edgeRow->addWidget(fromSpin);
    edgeRow->addWidget(new QLabel("В:"));
    toSpin = new QSpinBox(); toSpin->setMinimum(1); toSpin->setMaximum(99);
    edgeRow->addWidget(toSpin);
    edgeRow->addWidget(new QLabel("Вес:"));
    weightSpin = new QSpinBox(); weightSpin->setMinimum(1); weightSpin->setMaximum(9999); weightSpin->setValue(1);
    edgeRow->addWidget(weightSpin);
    editLayout->addLayout(edgeRow);

    QHBoxLayout *edgeBtns = new QHBoxLayout();
    QPushButton *addEdgeBtn = new QPushButton("Добавить ребро");
    QPushButton *remEdgeBtn = new QPushButton("Удалить ребро");
    edgeBtns->addWidget(addEdgeBtn);
    edgeBtns->addWidget(remEdgeBtn);
    connect(addEdgeBtn, &QPushButton::clicked, this, &MainWindow::addEdge);
    connect(remEdgeBtn, &QPushButton::clicked, this, &MainWindow::removeEdge);
    editLayout->addLayout(edgeBtns);

    QPushButton *loadDefaultBtn = new QPushButton("Загрузить граф из задания");
    editLayout->addWidget(loadDefaultBtn);
    connect(loadDefaultBtn, &QPushButton::clicked, this, &MainWindow::loadDefaultGraph);

    rightLayout->addWidget(editGroup);


    QGroupBox *algGroup = new QGroupBox("Алгоритмы");
    QVBoxLayout *algLayout = new QVBoxLayout(algGroup);

    QHBoxLayout *startRow = new QHBoxLayout();
    startRow->addWidget(new QLabel("Старт:"));
    startCombo = new QComboBox(); startCombo->setMinimumWidth(60);
    startRow->addWidget(startCombo);
    startRow->addWidget(new QLabel("Конец (Дейкстра):"));
    endCombo = new QComboBox(); endCombo->setMinimumWidth(60);
    startRow->addWidget(endCombo);
    algLayout->addLayout(startRow);

    QHBoxLayout *algBtns = new QHBoxLayout();
    QPushButton *bfsBtn = new QPushButton("BFS (обход в ширину)");
    QPushButton *dfsBtn = new QPushButton("DFS (обход в глубину)");
    algBtns->addWidget(bfsBtn);
    algBtns->addWidget(dfsBtn);
    connect(bfsBtn, &QPushButton::clicked, this, &MainWindow::runBFS);
    connect(dfsBtn, &QPushButton::clicked, this, &MainWindow::runDFS);
    algLayout->addLayout(algBtns);

    QHBoxLayout *algBtns2 = new QHBoxLayout();
    QPushButton *dijkBtn = new QPushButton("Дейкстра (кратч. путь)");
    QPushButton *floydBtn = new QPushButton("Флойд (все пути)");
    algBtns2->addWidget(dijkBtn);
    algBtns2->addWidget(floydBtn);
    connect(dijkBtn, &QPushButton::clicked, this, &MainWindow::runDijkstra);
    connect(floydBtn, &QPushButton::clicked, this, &MainWindow::runFloyd);
    algLayout->addLayout(algBtns2);

    rightLayout->addWidget(algGroup);


    QGroupBox *logGroup = new QGroupBox("Результаты");
    QVBoxLayout *logLayout = new QVBoxLayout(logGroup);
    logEdit = new QTextEdit();
    logEdit->setReadOnly(true);
    logEdit->setMinimumHeight(180);
    logLayout->addWidget(logEdit);
    rightLayout->addWidget(logGroup);

    mainLayout->addLayout(leftLayout, 3);
    mainLayout->addLayout(rightLayout, 2);

    resize(1200, 700);
}

void MainWindow::log(const QString &msg) {
    logEdit->append(msg);
}

void MainWindow::loadDefaultGraph() {

    numVertices = 6;
    adjList.assign(numVertices, {});
    adjMatrix.assign(numVertices, QVector<int>(numVertices, 0));

    auto addE = [&](int from, int to, int w) {
        // 1-based to 0-based
        int f = from-1, t = to-1;
        adjList[f].append({t, w});
        adjMatrix[f][t] = w;
    };

    addE(1,2,10);
    addE(1,4,28);
    addE(2,3,14);
    addE(3,4,18);
    addE(3,5,15);
    addE(4,5,20);
    addE(5,6,30);
    addE(6,1,19);


    nodePositions = {
        {300, 30},   // 1
        {150, 160},  // 2
        {150, 350},  // 3
        {400, 350},  // 4
        {420, 210},  // 5
        {530, 80},   // 6
    };

    updateMatrixFromGraph();
    rebuildScene();
    updateCombos();
    log("Загружен граф из задания (6 вершин).");
}

void MainWindow::updateCombos() {
    startCombo->clear();
    endCombo->clear();
    for (int i = 0; i < numVertices; i++) {
        startCombo->addItem(QString::number(i+1));
        endCombo->addItem(QString::number(i+1));
    }
    if (numVertices > 1) endCombo->setCurrentIndex(numVertices-1);

    fromSpin->setMaximum(numVertices);
    toSpin->setMaximum(numVertices);
    removeSpin->setMaximum(numVertices);
}

void MainWindow::updateMatrixFromGraph() {
    matrixChanging = true;
    matrixTable->blockSignals(true);
    matrixTable->setRowCount(numVertices);
    matrixTable->setColumnCount(numVertices);
    QStringList headers;
    for (int i = 0; i < numVertices; i++) headers << QString::number(i+1);
    matrixTable->setHorizontalHeaderLabels(headers);
    matrixTable->setVerticalHeaderLabels(headers);

    for (int i = 0; i < numVertices; i++) {
        for (int j = 0; j < numVertices; j++) {
            auto *item = new QTableWidgetItem(adjMatrix[i][j] == 0 ? "0" : QString::number(adjMatrix[i][j]));
            item->setTextAlignment(Qt::AlignCenter);
            if (adjMatrix[i][j] != 0) {
                item->setBackground(QBrush(QColor(200, 230, 255)));
            }
            matrixTable->setItem(i, j, item);
        }
    }
    matrixTable->resizeColumnsToContents();
    matrixTable->blockSignals(false);
    matrixChanging = false;
    connect(matrixTable, &QTableWidget::cellChanged, this, &MainWindow::onMatrixCellChanged);
}

void MainWindow::onMatrixCellChanged(int row, int col) {
    if (matrixChanging) return;

    if (!matrixTable->item(row, col)) return;
    bool ok;
    int val = matrixTable->item(row, col)->text().toInt(&ok);
    if (!ok || val < 0) { val = 0; }
    adjMatrix[row][col] = val;
    // Rebuild adj list
    adjList.assign(numVertices, {});
    for (int i = 0; i < numVertices; i++)
        for (int j = 0; j < numVertices; j++)
            if (adjMatrix[i][j] != 0)
                adjList[i].append({j, adjMatrix[i][j]});
    rebuildScene();
}

void MainWindow::updateGraphFromMatrix() {

    for (int i = 0; i < numVertices; i++) {
        for (int j = 0; j < numVertices; j++) {
            if (!matrixTable->item(i,j)) continue;
            bool ok;
            int v = matrixTable->item(i,j)->text().toInt(&ok);
            adjMatrix[i][j] = (ok && v > 0) ? v : 0;
        }
    }
    adjList.assign(numVertices, {});
    for (int i = 0; i < numVertices; i++)
        for (int j = 0; j < numVertices; j++)
            if (adjMatrix[i][j] != 0)
                adjList[i].append({j, adjMatrix[i][j]});
    rebuildScene();
    log("Граф обновлён из матрицы.");
}

void MainWindow::rebuildScene() {
    scene->clear();
    nodeItems.clear();
    nodeLabelItems.clear();


    while ((int)nodePositions.size() < numVertices) {
        double angle = 2*M_PI*(nodePositions.size()) / (numVertices > 0 ? numVertices : 1);
        nodePositions.append({300 + 200*cos(angle), 250 + 200*sin(angle)});
    }

    double r = 22;


    for (int i = 0; i < numVertices; i++) {
        for (auto &e : adjList[i]) {
            int j = e.to;
            QPointF p1 = nodePositions[i];
            QPointF p2 = nodePositions[j];

            double dx = p2.x() - p1.x();
            double dy = p2.y() - p1.y();
            double len = sqrt(dx*dx + dy*dy);
            if (len < 1) continue;
            double nx = dx/len, ny = dy/len;

            QPointF start = {p1.x() + nx*r, p1.y() + ny*r};
            QPointF end   = {p2.x() - nx*r, p2.y() - ny*r};


            QGraphicsLineItem *line = scene->addLine(start.x(), start.y(), end.x(), end.y(),
                                                      QPen(Qt::black, 2));
            Q_UNUSED(line);


            double angle = atan2(ny, nx);
            double arrowSize = 10;
            QPointF a1 = {end.x() - arrowSize*cos(angle - M_PI/6),
                          end.y() - arrowSize*sin(angle - M_PI/6)};
            QPointF a2 = {end.x() - arrowSize*cos(angle + M_PI/6),
                          end.y() - arrowSize*sin(angle + M_PI/6)};
            scene->addLine(end.x(), end.y(), a1.x(), a1.y(), QPen(Qt::black, 2));
            scene->addLine(end.x(), end.y(), a2.x(), a2.y(), QPen(Qt::black, 2));

            QPointF mid = {(start.x()+end.x())/2 - 10, (start.y()+end.y())/2 - 12};
            QGraphicsTextItem *wt = scene->addText(QString::number(e.weight));
            wt->setPos(mid);
            wt->setDefaultTextColor(Qt::darkBlue);
            wt->setFont(QFont("Arial", 8));
        }
    }

    for (int i = 0; i < numVertices; i++) {
        QPointF pos = nodePositions[i];
        QGraphicsEllipseItem *el = scene->addEllipse(pos.x()-r, pos.y()-r, 2*r, 2*r,
                                                      QPen(Qt::black, 2), QBrush(QColor(240,240,100)));
        nodeItems.append(el);

        QGraphicsTextItem *lbl = scene->addText(QString::number(i+1));
        lbl->setFont(QFont("Arial", 11, QFont::Bold));
        lbl->setPos(pos.x() - 7, pos.y() - 10);
        nodeLabelItems.append(lbl);
    }
}

void MainWindow::highlightPath(const QVector<int> &path) {

    for (int idx : path) {
        if (idx >= 0 && idx < nodeItems.size()) {
            nodeItems[idx]->setBrush(QBrush(QColor(100, 220, 100)));
        }
    }
}

void MainWindow::clearHighlight() {
    for (auto *item : nodeItems)
        item->setBrush(QBrush(QColor(240,240,100)));
}



void MainWindow::addVertex() {
    numVertices++;
    adjList.resize(numVertices);
    for (auto &row : adjMatrix) row.append(0);
    adjMatrix.append(QVector<int>(numVertices, 0));


    double angle = 2*M_PI*(numVertices-1) / numVertices;
    nodePositions.append({300 + 220*cos(angle), 250 + 220*sin(angle)});

    updateMatrixFromGraph();
    rebuildScene();
    updateCombos();
    log(QString("Добавлена вершина %1.").arg(numVertices));
}

void MainWindow::removeVertex() {
    int v = removeSpin->value() - 1;
    if (v < 0 || v >= numVertices) { log("Неверный номер вершины."); return; }

    numVertices--;
    adjList.remove(v);
    for (auto &row : adjList) {

        for (int i = row.size()-1; i >= 0; i--) {
            if (row[i].to == v) row.remove(i);
            else if (row[i].to > v) row[i].to--;
        }
    }
    adjMatrix.remove(v);
    for (auto &row : adjMatrix) row.remove(v);
    nodePositions.remove(v);

    updateMatrixFromGraph();
    rebuildScene();
    updateCombos();
    log(QString("Удалена вершина %1.").arg(v+1));
}

void MainWindow::addEdge() {
    int f = fromSpin->value()-1, t = toSpin->value()-1, w = weightSpin->value();
    if (f < 0 || f >= numVertices || t < 0 || t >= numVertices) {
        log("Неверные вершины для ребра."); return;
    }

    for (int i = adjList[f].size()-1; i >= 0; i--)
        if (adjList[f][i].to == t) adjList[f].remove(i);
    adjList[f].append({t, w});
    adjMatrix[f][t] = w;
    updateMatrixFromGraph();
    rebuildScene();
    log(QString("Добавлено ребро %1->%2 (вес %3).").arg(f+1).arg(t+1).arg(w));
}

void MainWindow::removeEdge() {
    int f = fromSpin->value()-1, t = toSpin->value()-1;
    if (f < 0 || f >= numVertices || t < 0 || t >= numVertices) {
        log("Неверные вершины для ребра."); return;
    }
    for (int i = adjList[f].size()-1; i >= 0; i--)
        if (adjList[f][i].to == t) adjList[f].remove(i);
    adjMatrix[f][t] = 0;
    updateMatrixFromGraph();
    rebuildScene();
    log(QString("Удалено ребро %1->%2.").arg(f+1).arg(t+1));
}



void MainWindow::runBFS() {
    if (numVertices == 0) return;
    clearHighlight();
    int start = startCombo->currentIndex();
    QVector<bool> visited(numVertices, false);
    QQueue<int> q;
    QVector<int> order;
    q.enqueue(start);
    visited[start] = true;
    while (!q.isEmpty()) {
        int v = q.dequeue();
        order.append(v);
        for (auto &e : adjList[v]) {
            if (!visited[e.to]) {
                visited[e.to] = true;
                q.enqueue(e.to);
            }
        }
    }
    QString res = "BFS от вершины " + QString::number(start+1) + ": ";
    for (int v : order) res += QString::number(v+1) + " ";
    log(res);
    highlightPath(order);
}

void MainWindow::runDFS() {
    if (numVertices == 0) return;
    clearHighlight();
    int start = startCombo->currentIndex();
    QVector<bool> visited(numVertices, false);
    QStack<int> st;
    QVector<int> order;
    st.push(start);
    while (!st.isEmpty()) {
        int v = st.pop();
        if (visited[v]) continue;
        visited[v] = true;
        order.append(v);

        for (int i = adjList[v].size()-1; i >= 0; i--)
            st.push(adjList[v][i].to);
    }
    QString res = "DFS от вершины " + QString::number(start+1) + ": ";
    for (int v : order) res += QString::number(v+1) + " ";
    log(res);
    highlightPath(order);
}

void MainWindow::runDijkstra() {
    if (numVertices == 0) return;
    clearHighlight();
    int start = startCombo->currentIndex();
    int end   = endCombo->currentIndex();

    QVector<int> dist(numVertices, INF);
    QVector<int> prev(numVertices, -1);
    QVector<bool> visited(numVertices, false);
    dist[start] = 0;

    for (int iter = 0; iter < numVertices; iter++) {

        int u = -1;
        for (int i = 0; i < numVertices; i++)
            if (!visited[i] && (u == -1 || dist[i] < dist[u])) u = i;
        if (u == -1 || dist[u] == INF) break;
        visited[u] = true;
        for (auto &e : adjList[u]) {
            if (dist[u] + e.weight < dist[e.to]) {
                dist[e.to] = dist[u] + e.weight;
                prev[e.to] = u;
            }
        }
    }

    log("=== Дейкстра от вершины " + QString::number(start+1) + " ===");
    QString distances = "Расстояния: ";
    for (int i = 0; i < numVertices; i++) {
        distances += QString("%1: %2  ").arg(i+1).arg(dist[i] == INF ? QString("∞") : QString::number(dist[i]));
    }
    log(distances);

    if (dist[end] == INF) {
        log(QString("Путь до вершины %1: недостижима.").arg(end+1));
    } else {
        QVector<int> path;
        for (int v = end; v != -1; v = prev[v]) path.prepend(v);
        QString pathStr = QString("Кратчайший путь %1->%2 (длина %3): ")
                          .arg(start+1).arg(end+1).arg(dist[end]);
        for (int v : path) pathStr += QString::number(v+1) + " ";
        log(pathStr);
        highlightPath(path);
    }
}

void MainWindow::runFloyd() {
    if (numVertices == 0) return;
    clearHighlight();
    log("=== Алгоритм Флойда ===");


    QVector<QVector<int>> D(numVertices, QVector<int>(numVertices, INF));
    QVector<QVector<int>> Next(numVertices, QVector<int>(numVertices, -1));

    for (int i = 0; i < numVertices; i++) {
        D[i][i] = 0;
        for (auto &e : adjList[i]) {
            D[i][e.to] = e.weight;
            Next[i][e.to] = e.to;
        }
    }

    for (int k = 0; k < numVertices; k++)
        for (int i = 0; i < numVertices; i++)
            for (int j = 0; j < numVertices; j++)
                if (D[i][k] != INF && D[k][j] != INF && D[i][k]+D[k][j] < D[i][j]) {
                    D[i][j] = D[i][k]+D[k][j];
                    Next[i][j] = Next[i][k];
                }


    QString header = "     ";
    for (int j = 0; j < numVertices; j++) header += QString("%1  ").arg(j+1, 4);
    log(header);
    for (int i = 0; i < numVertices; i++) {
        QString row = QString("%1:  ").arg(i+1, 3);
        for (int j = 0; j < numVertices; j++) {
            row += (D[i][j]==INF ? QString("  ∞ ") : QString("%1  ").arg(D[i][j], 4));
        }
        log(row);
    }

    int start = startCombo->currentIndex();
    log(QString("Пути от вершины %1:").arg(start+1));
    for (int j = 0; j < numVertices; j++) {
        if (j == start) continue;
        if (D[start][j] == INF) {
            log(QString("  -> %1: недостижима").arg(j+1));
        } else {

            QVector<int> path;
            int cur = start;
            while (cur != j && cur != -1) {
                path.append(cur);
                cur = Next[cur][j];
            }
            path.append(j);
            QString ps = QString("  -> %1 (dist=%2): ").arg(j+1).arg(D[start][j]);
            for (int v : path) ps += QString::number(v+1) + " ";
            log(ps);
        }
    }
}
