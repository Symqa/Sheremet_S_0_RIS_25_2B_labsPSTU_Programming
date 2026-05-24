#include "mainwindow.h"
#include "tspsolver.h"
#include <QGraphicsSceneMouseEvent>
#include <QInputDialog>
#include <QMessageBox>
#include <QPen>
#include <QBrush>
#include <QFont>
#include <cmath>

const double TSPScene::NODE_R = 24.0;
int TSPScene::nodeCounter = 0;

TSPScene::TSPScene(QObject *parent) : QGraphicsScene(parent) {
    setSceneRect(0, 0, 700, 520);
    setBackgroundBrush(Qt::white);
}

void TSPScene::clearGraph() {
    clear();
    nodes.clear();
    edges.clear();
    nodeNames.clear();
    nodeCounter = 0;
    highlightItems.clear();
    emit graphChanged();
}

void TSPScene::addNode(QPointF pos) {
    nodeCounter++;
    QString name = QString("V%1").arg(nodeCounter);

    NodeData nd;
    nd.pos = pos;

    nd.ellipse = addEllipse(pos.x()-NODE_R, pos.y()-NODE_R, 2*NODE_R, 2*NODE_R,
                             QPen(Qt::black, 2),
                             QBrush(Qt::lightGray));
    nd.ellipse->setZValue(2);

    nd.label = addText(name);
    nd.label->setFont(QFont("Arial", 10, QFont::Bold));
    nd.label->setDefaultTextColor(Qt::black);
    nd.label->setPos(pos.x() - nd.label->boundingRect().width()/2,
                     pos.y() - nd.label->boundingRect().height()/2);
    nd.label->setZValue(3);

    nodes.append(nd);
    nodeNames.append(name);
    emit graphChanged();
}

void TSPScene::deleteNode(int idx) {
    if (idx < 0 || idx >= nodes.size()) return;

    removeItem(nodes[idx].ellipse);
    removeItem(nodes[idx].label);
    delete nodes[idx].ellipse;
    delete nodes[idx].label;

    for (int i = edges.size()-1; i >= 0; i--) {
        if (edges[i].from == idx || edges[i].to == idx) {
            deleteEdge(i);
        }
    }
    nodes.remove(idx);
    nodeNames.remove(idx);

    for (auto &e : edges) {
        if (e.from > idx) e.from--;
        if (e.to   > idx) e.to--;
    }
    emit graphChanged();
}

void TSPScene::deleteEdge(int idx) {
    if (idx < 0 || idx >= edges.size()) return;
    auto &e = edges[idx];
    auto safeRemove = [&](QGraphicsItem *item) {
        if (item) { removeItem(item); delete item; }
    };
    safeRemove(e.line); safeRemove(e.arrowL); safeRemove(e.arrowR);
    safeRemove(e.weightLabel);
    safeRemove(e.lineRev); safeRemove(e.arrowLR); safeRemove(e.arrowRR);
    safeRemove(e.weightLabelRev);
    edges.remove(idx);
    emit graphChanged();
}

QPointF TSPScene::arrowEnd(QPointF from, QPointF to, double r) const {
    double dx = to.x()-from.x(), dy = to.y()-from.y();
    double len = sqrt(dx*dx+dy*dy);
    if (len < 1) return to;
    return {to.x() - dx/len*r, to.y() - dy/len*r};
}

void TSPScene::drawArrow(QGraphicsLineItem *&aL, QGraphicsLineItem *&aR,
                          QPointF start, QPointF end, QPen pen) {
    double dx = end.x()-start.x(), dy = end.y()-start.y();
    double angle = atan2(dy, dx);
    double sz = 11;
    QPointF a1 = {end.x()-sz*cos(angle-M_PI/6), end.y()-sz*sin(angle-M_PI/6)};
    QPointF a2 = {end.x()-sz*cos(angle+M_PI/6), end.y()-sz*sin(angle+M_PI/6)};
    if (aL) { removeItem(aL); delete aL; }
    if (aR) { removeItem(aR); delete aR; }
    aL = addLine(end.x(), end.y(), a1.x(), a1.y(), pen);
    aR = addLine(end.x(), end.y(), a2.x(), a2.y(), pen);
    aL->setZValue(1); aR->setZValue(1);
}

void TSPScene::redrawEdge(int idx) {
    auto &e = edges[idx];
    if (e.from >= nodes.size() || e.to >= nodes.size()) return;

    QPointF pf = nodes[e.from].pos;
    QPointF pt = nodes[e.to].pos;

    double dx = pt.x()-pf.x(), dy = pt.y()-pf.y();
    double len = sqrt(dx*dx+dy*dy);
    double ox = 0, oy = 0;
    if (len > 1) { ox = -dy/len*4; oy = dx/len*4; }

    QPointF pfO = {pf.x()+ox, pf.y()+oy};
    QPointF ptO = {pt.x()+ox, pt.y()+oy};

    QPointF startFwd = {pfO.x() + (pt.x()-pf.x())/len*NODE_R + ox,
                        pfO.y() + (pt.y()-pf.y())/len*NODE_R + oy};
    QPointF endFwd   = arrowEnd(pfO, ptO, NODE_R);

    QPen fwdPen(Qt::blue, 2);

    if (!e.line) e.line = addLine(0,0,0,0, fwdPen);
    e.line->setLine(startFwd.x(), startFwd.y(), endFwd.x(), endFwd.y());
    e.line->setPen(fwdPen);
    e.line->setZValue(1);
    drawArrow(e.arrowL, e.arrowR, startFwd, endFwd, fwdPen);

    QPointF mid = {(startFwd.x()+endFwd.x())/2 - 12 + ox*2,
                   (startFwd.y()+endFwd.y())/2 - 14 + oy*2};
    if (!e.weightLabel) {
        e.weightLabel = addText("");
        e.weightLabel->setFont(QFont("Arial", 9, QFont::Bold));
        e.weightLabel->setDefaultTextColor(Qt::darkGreen);
        e.weightLabel->setZValue(3);
    }
    e.weightLabel->setPlainText(QString::number(e.weight));
    e.weightLabel->setPos(mid);

    // Reverse direction
    QPointF pfR = {pf.x()-ox, pf.y()-oy};
    QPointF ptR = {pt.x()-ox, pt.y()-oy};
    QPointF startRev = {ptR.x() + (pf.x()-pt.x())/len*NODE_R - ox,
                        ptR.y() + (pf.y()-pt.y())/len*NODE_R - oy};
    QPointF endRev   = arrowEnd(ptR, pfR, NODE_R);

    QPen revPen(Qt::darkCyan, 2);

    if (!e.lineRev) e.lineRev = addLine(0,0,0,0, revPen);
    e.lineRev->setLine(startRev.x(), startRev.y(), endRev.x(), endRev.y());
    e.lineRev->setPen(revPen);
    e.lineRev->setZValue(1);
    drawArrow(e.arrowLR, e.arrowRR, startRev, endRev, revPen);

    QPointF midR = {(startRev.x()+endRev.x())/2 + 4 - ox*2,
                    (startRev.y()+endRev.y())/2 - 14 - oy*2};
    if (!e.weightLabelRev) {
        e.weightLabelRev = addText("");
        e.weightLabelRev->setFont(QFont("Arial", 9, QFont::Bold));
        e.weightLabelRev->setDefaultTextColor(Qt::darkGreen);
        e.weightLabelRev->setZValue(3);
    }
    e.weightLabelRev->setPlainText(QString::number(e.weight));
    e.weightLabelRev->setPos(midR);
}

void TSPScene::redrawAllEdges() {
    for (int i = 0; i < edges.size(); i++) redrawEdge(i);
}

void TSPScene::redrawNode(int idx) {
    auto &nd = nodes[idx];
    nd.ellipse->setRect(nd.pos.x()-NODE_R, nd.pos.y()-NODE_R, 2*NODE_R, 2*NODE_R);
    nd.label->setPos(nd.pos.x()-nd.label->boundingRect().width()/2,
                     nd.pos.y()-nd.label->boundingRect().height()/2);
}

void TSPScene::addEdge(int from, int to, int weight) {
    for (auto &e : edges) if (e.from == from && e.to == to) return;

    EdgeData ed;
    ed.from = from; ed.to = to; ed.weight = weight;
    ed.line = ed.arrowL = ed.arrowR = nullptr;
    ed.weightLabel = nullptr;
    ed.lineRev = ed.arrowLR = ed.arrowRR = nullptr;
    ed.weightLabelRev = nullptr;
    edges.append(ed);
    redrawEdge(edges.size()-1);
    emit graphChanged();
}

int TSPScene::hitNode(QPointF pos) const {
    for (int i = 0; i < nodes.size(); i++) {
        double dx = pos.x()-nodes[i].pos.x(), dy = pos.y()-nodes[i].pos.y();
        if (dx*dx+dy*dy <= NODE_R*NODE_R*1.5) return i;
    }
    return -1;
}

int TSPScene::hitEdge(QPointF pos) const {
    for (int i = 0; i < edges.size(); i++) {
        if (edges[i].line && edges[i].line->boundingRect().contains(pos)) return i;
        if (edges[i].lineRev && edges[i].lineRev->boundingRect().contains(pos)) return i;
    }
    return -1;
}

void TSPScene::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    QPointF pos = event->scenePos();

    if (event->button() == Qt::LeftButton) {
        switch (mode) {
        case Mode::AddNode:
            addNode(pos);
            break;

        case Mode::AddEdge: {
            int hit = hitNode(pos);
            if (hit < 0) break;
            if (currentEdgeFrom < 0) {
                currentEdgeFrom = hit;
                nodes[hit].ellipse->setPen(QPen(Qt::red, 3));
            } else {
                if (hit != currentEdgeFrom) {
                    bool ok;
                    int w = QInputDialog::getInt(nullptr, "Вес ребра",
                        QString("Вес ребра %1 — %2:").arg(nodeNames[currentEdgeFrom]).arg(nodeNames[hit]),
                        1, 1, 9999, 1, &ok);
                    if (ok) addEdge(currentEdgeFrom, hit, w);
                }
                nodes[currentEdgeFrom].ellipse->setPen(QPen(Qt::black, 2));
                currentEdgeFrom = -1;
            }
            break;
        }

        case Mode::MoveNode:
            draggingNode = hitNode(pos);
            if (draggingNode >= 0)
                dragOffset = pos - nodes[draggingNode].pos;
            break;

        case Mode::DeleteNode: {
            int hit = hitNode(pos);
            if (hit >= 0) deleteNode(hit);
            break;
        }

        case Mode::DeleteEdge: {
            int hit = hitEdge(pos);
            if (hit >= 0) deleteEdge(hit);
            break;
        }
        }
    }
    QGraphicsScene::mousePressEvent(event);
}

void TSPScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    if (mode == Mode::MoveNode && draggingNode >= 0) {
        nodes[draggingNode].pos = event->scenePos() - dragOffset;
        redrawNode(draggingNode);
        redrawAllEdges();
    }
    QGraphicsScene::mouseMoveEvent(event);
}

void TSPScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    if (mode == Mode::MoveNode && draggingNode >= 0) {
        draggingNode = -1;
        emit graphChanged();
    }
    QGraphicsScene::mouseReleaseEvent(event);
}

QVector<QVector<int>> TSPScene::getMatrix() const {
    int n = nodes.size();
    QVector<QVector<int>> m(n, QVector<int>(n, TSP_INF));
    for (int i = 0; i < n; i++) m[i][i] = 0;
    for (auto &e : edges) {
        m[e.from][e.to] = e.weight;
        m[e.to][e.from] = e.weight;
    }
    return m;
}

void TSPScene::setMatrix(const QVector<QVector<int>> &mat, const QStringList &labels) {
    clearGraph();
    int n = mat.size();
    nodeCounter = n;
    for (int i = 0; i < n; i++) {
        nodeNames.append(labels[i]);
        double angle = 2*M_PI*i/n;
        QPointF pos = {350 + 200*cos(angle - M_PI/2), 260 + 200*sin(angle - M_PI/2)};
        NodeData nd;
        nd.pos = pos;
        nd.ellipse = addEllipse(pos.x()-NODE_R, pos.y()-NODE_R, 2*NODE_R, 2*NODE_R,
                                 QPen(Qt::black, 2), QBrush(Qt::lightGray));
        nd.ellipse->setZValue(2);
        nd.label = addText(labels[i]);
        nd.label->setFont(QFont("Arial", 10, QFont::Bold));
        nd.label->setDefaultTextColor(Qt::black);
        nd.label->setPos(pos.x()-nd.label->boundingRect().width()/2,
                         pos.y()-nd.label->boundingRect().height()/2);
        nd.label->setZValue(3);
        nodes.append(nd);
    }
    for (int i = 0; i < n; i++)
        for (int j = i+1; j < n; j++)
            if (mat[i][j] < TSP_INF && mat[i][j] != 0)
                addEdge(i, j, mat[i][j]);
    emit graphChanged();
}

void TSPScene::loadDemoGraph() {
    QStringList names = {"Замок","Лес","Гора","Болото","Деревня","Руины"};
    QVector<QVector<int>> mat = {
        {  0, 12, 20, 15, 25, 18},
        { 12,  0, 14, 22, 10, 30},
        { 20, 14,  0, 17, 28, 12},
        { 15, 22, 17,  0, 20, 24},
        { 25, 10, 28, 20,  0, 16},
        { 18, 30, 12, 24, 16,  0},
    };
    setMatrix(mat, names);
}

void TSPScene::highlightTour(const QVector<int> &tour) {
    clearHighlight();
    if (tour.size() < 2) return;

    QPen hlPen(Qt::red, 4);
    for (int k = 0; k+1 < tour.size(); k++) {
        int u = tour[k], v = tour[k+1];
        QPointF pu = nodes[u].pos, pv = nodes[v].pos;
        double dx = pv.x()-pu.x(), dy = pv.y()-pu.y();
        double len = sqrt(dx*dx+dy*dy);
        if (len < 1) continue;
        QPointF start = {pu.x()+dx/len*NODE_R, pu.y()+dy/len*NODE_R};
        QPointF end   = {pv.x()-dx/len*NODE_R, pv.y()-dy/len*NODE_R};
        auto *line = addLine(start.x(), start.y(), end.x(), end.y(), hlPen);
        line->setZValue(1.5);
        highlightItems.append(line);
    }
    for (int k = 0; k < tour.size(); k++) {
        int u = tour[k];
        if (u >= nodes.size()) continue;
        nodes[u].ellipse->setBrush(QBrush(Qt::yellow));
        nodes[u].ellipse->setPen(QPen(Qt::red, 3));
        highlightItems.append(nodes[u].ellipse);
    }
}

void TSPScene::clearHighlight() {
    for (auto *item : highlightItems) {
        if (auto *el = qgraphicsitem_cast<QGraphicsEllipseItem*>(item)) {
            el->setBrush(QBrush(Qt::lightGray));
            el->setPen(QPen(Qt::black, 2));
        } else {
            removeItem(item);
            delete item;
        }
    }
    highlightItems.clear();
}
