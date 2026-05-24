#pragma once
#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTableWidget>
#include <QTextEdit>
#include <QComboBox>
#include <QSpinBox>
#include <QPushButton>
#include <QLabel>
#include <QVector>
#include <QMap>
#include <QGraphicsEllipseItem>
#include <QGraphicsLineItem>
#include <QGraphicsTextItem>
#include <limits>

static const int INF = std::numeric_limits<int>::max() / 2;

struct Edge {
    int to;
    int weight;
};

class GraphScene;

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

private slots:
    void runBFS();
    void runDFS();
    void runDijkstra();
    void runFloyd();
    void addVertex();
    void removeVertex();
    void addEdge();
    void removeEdge();
    void loadDefaultGraph();
    void updateMatrixFromGraph();
    void updateGraphFromMatrix();
    void onMatrixCellChanged(int row, int col);
    void updateCombos();

private:
    void setupUI();
    void setupDefaultGraph();
    void rebuildScene();
    void log(const QString &msg);
    void highlightPath(const QVector<int> &path);
    void clearHighlight();


    int numVertices;
    QVector<QVector<Edge>> adjList;
    QVector<QVector<int>> adjMatrix;


    GraphScene *scene;
    QGraphicsView *view;
    QTableWidget *matrixTable;
    QTextEdit *logEdit;
    QComboBox *startCombo, *endCombo;
    QSpinBox *fromSpin, *toSpin, *weightSpin;
    QSpinBox *removeSpin;
    QSpinBox *removeFromSpin, *removeToSpin;


    QVector<QGraphicsEllipseItem*> nodeItems;
    QVector<QGraphicsTextItem*> nodeLabelItems;
    QVector<QPointF> nodePositions;

    bool matrixChanging;
};
