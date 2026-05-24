#pragma once
#include <QWidget>
#include <QVector>
#include <QString>
#include "BST.h"

// =====================================================================
//  TreeWidget — виджет для графического отображения бинарного дерева.
//  Поддерживает масштабирование (колесо мыши) и перетаскивание (ЛКМ).
//  Подсвечивает узел, переданный через highlight().
// =====================================================================

struct DrawNode {
    Node*  bst    = nullptr;
    float  x      = 0.f;
    float  y      = 0.f;
};

class TreeWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TreeWidget(QWidget* parent = nullptr);

    void setTree(BST* tree);
    void highlight(const QString& key);   // подсветить найденный узел
    void clearHighlight();

protected:
    void paintEvent(QPaintEvent* event)       override;
    void wheelEvent(QWheelEvent* event)       override;
    void mousePressEvent(QMouseEvent* event)  override;
    void mouseMoveEvent(QMouseEvent* event)   override;
    void mouseReleaseEvent(QMouseEvent* event)override;
    void resizeEvent(QResizeEvent* event)     override;

private:
    BST*    tree_      = nullptr;
    QString highlighted_;

    // Сцена
    QVector<DrawNode> nodes_;
    float   scale_     = 1.0f;
    QPointF offset_;          // смещение центра сцены
    QPoint  lastMouse_;
    bool    dragging_  = false;

    // Параметры отрисовки
    static constexpr float NODE_R  = 28.f;
    static constexpr float H_GAP   = 52.f;
    static constexpr float V_GAP   = 76.f;

    void   buildLayout();
    float  layoutRec(Node* node, float& xCur, int depth);
    DrawNode* findDN(Node* bst);

    QPointF world2screen(float x, float y) const;
};
