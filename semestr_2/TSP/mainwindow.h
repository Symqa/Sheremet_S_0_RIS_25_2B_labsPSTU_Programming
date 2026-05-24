#pragma once
#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsEllipseItem>
#include <QGraphicsLineItem>
#include <QGraphicsTextItem>
#include <QTableWidget>
#include <QTextEdit>
#include <QPushButton>
#include <QLabel>
#include <QSpinBox>
#include <QLineEdit>
#include <QVector>
#include <QString>
#include <QMouseEvent>
#include <QPointF>
#include <limits>

static const int TSP_INF = std::numeric_limits<int>::max() / 2;

// ---- Interactive Graph Scene ----
class TSPScene : public QGraphicsScene {
    Q_OBJECT
public:
    enum class Mode { AddNode, AddEdge, MoveNode, DeleteNode, DeleteEdge };

    explicit TSPScene(QObject *parent = nullptr);

    void setMode(Mode m) { mode = m; currentEdgeFrom = -1; }
    Mode getMode() const { return mode; }
    void clearGraph();
    void loadDemoGraph();

    int nodeCount() const { return nodes.size(); }
    QVector<QVector<int>> getMatrix() const;
    void setMatrix(const QVector<QVector<int>> &mat, const QStringList &labels);
    void highlightTour(const QVector<int> &tour);
    void clearHighlight();
    QStringList getNodeNames() const { return nodeNames; }

signals:
    void graphChanged();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

private:
    struct NodeData {
        QGraphicsEllipseItem *ellipse;
        QGraphicsTextItem    *label;
        QPointF               pos;
    };
    struct EdgeData {
        int from, to, weight;
        QGraphicsLineItem  *line;
        QGraphicsLineItem  *arrowL, *arrowR;
        QGraphicsTextItem  *weightLabel;
        // reverse
        QGraphicsLineItem  *lineRev;
        QGraphicsLineItem  *arrowLR, *arrowRR;
        QGraphicsTextItem  *weightLabelRev;
    };

    void addNode(QPointF pos);
    void addEdge(int from, int to, int weight);
    void deleteNode(int idx);
    void deleteEdge(int idx);
    int  hitNode(QPointF pos) const;
    int  hitEdge(QPointF pos) const;
    void redrawEdge(int idx);
    void redrawAllEdges();
    void redrawNode(int idx);
    QPointF arrowEnd(QPointF from, QPointF to, double r) const;
    void    drawArrow(QGraphicsLineItem *&aL, QGraphicsLineItem *&aR,
                      QPointF start, QPointF end, QPen pen);

    QVector<NodeData> nodes;
    QVector<EdgeData> edges;
    QStringList       nodeNames;

    Mode mode = Mode::AddNode;
    int  currentEdgeFrom = -1;
    int  draggingNode = -1;
    QPointF dragOffset;

    // highlight items
    QVector<QGraphicsItem*> highlightItems;

    static const double NODE_R;
    static int nodeCounter;
};

// ---- Main Window ----
class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

private slots:
    void onModeAddNode();
    void onModeAddEdge();
    void onModeMoveNode();
    void onModeDeleteNode();
    void onModeDeleteEdge();
    void onLoadDemo();
    void onClearGraph();
    void onSolve();
    void onMatrixApply();
    void onGraphChanged();
    void onEdgeWeightChanged(int row, int col);

private:
    void setupUI();
    void syncMatrixFromScene();
    void log(const QString &msg);
    void setActiveModeButton(QPushButton *btn);

    TSPScene    *scene;
    QGraphicsView *view;
    QTableWidget  *matrixTable;
    QTextEdit     *logEdit;
    QLabel        *statusLbl;

    QPushButton *btnAddNode, *btnAddEdge, *btnMove, *btnDelNode, *btnDelEdge;
    QPushButton *btnSolve, *btnDemo, *btnClear, *btnApplyMatrix;

    bool matrixSyncing = false;
};
