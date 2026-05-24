#include "TreeWidget.h"
#include <QPainter>
#include <QWheelEvent>
#include <QMouseEvent>
#include <QFontMetricsF>

TreeWidget::TreeWidget(QWidget* parent) : QWidget(parent)
{
    setMinimumSize(400, 300);
    setMouseTracking(true);
    // Белый фон — стандартный Qt
    QPalette pal = palette();
    pal.setColor(QPalette::Window, Qt::white);
    setAutoFillBackground(true);
    setPalette(pal);
}

void TreeWidget::setTree(BST* tree) {
    tree_ = tree;
    buildLayout();
    update();
}

void TreeWidget::highlight(const QString& key) {
    highlighted_ = key;
    update();
}

void TreeWidget::clearHighlight() {
    highlighted_.clear();
    update();
}

void TreeWidget::buildLayout() {
    nodes_.clear();
    if (!tree_ || !tree_->getRoot()) return;
    float xCur = 0.f;
    layoutRec(tree_->getRoot(), xCur, 0);
}

float TreeWidget::layoutRec(Node* node, float& xCur, int depth) {
    if (!node) return 0.f;
    layoutRec(node->left, xCur, depth + 1);
    DrawNode dn;
    dn.bst = node;
    dn.x   = xCur + NODE_R;
    dn.y   = depth * (2 * NODE_R + V_GAP) + NODE_R + 20.f;
    nodes_.append(dn);
    xCur += 2 * NODE_R + H_GAP;
    layoutRec(node->right, xCur, depth + 1);
    return 0.f;
}

DrawNode* TreeWidget::findDN(Node* bst) {
    for (auto& dn : nodes_)
        if (dn.bst == bst) return &dn;
    return nullptr;
}

QPointF TreeWidget::world2screen(float x, float y) const {
    return { x * scale_ + offset_.x(), y * scale_ + offset_.y() };
}

void TreeWidget::paintEvent(QPaintEvent*) {
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);
    p.fillRect(rect(), Qt::white);

    if (nodes_.isEmpty()) {
        p.drawText(rect(), Qt::AlignCenter, "Дерево пустое");
        return;
    }

    // Рёбра — просто чёрные линии
    p.setPen(QPen(Qt::black, 1.5));
    for (auto& dn : nodes_) {
        auto draw = [&](Node* child) {
            DrawNode* c = findDN(child);
            if (c) p.drawLine(world2screen(dn.x, dn.y), world2screen(c->x, c->y));
        };
        if (dn.bst->left)  draw(dn.bst->left);
        if (dn.bst->right) draw(dn.bst->right);
    }

    // Узлы — круг + текст
    QFont font;
    font.setPointSize(int(9 * scale_));
    p.setFont(font);

    for (auto& dn : nodes_) {
        QPointF center = world2screen(dn.x, dn.y);
        float r = NODE_R * scale_;
        bool sel = (!highlighted_.isEmpty() && highlighted_ == QString(dn.bst->data));

        // Заливка: жёлтая если найден, иначе светло-голубая
        p.setBrush(sel ? QColor(255, 230, 100) : QColor(173, 216, 230));
        p.setPen(QPen(Qt::black, 1.5));
        p.drawEllipse(center, r, r);

        // Текст
        p.setPen(Qt::black);
        QString txt = QString(dn.bst->data);
        QFontMetricsF fm(font);
        if (fm.horizontalAdvance(txt) > r * 1.8f)
            txt = txt.left(4) + "..";
        p.drawText(QRectF(center.x()-r, center.y()-r, r*2, r*2), Qt::AlignCenter, txt);
    }
}

void TreeWidget::wheelEvent(QWheelEvent* event) {
    float factor = event->angleDelta().y() > 0 ? 1.12f : 0.89f;
    QPointF mouse = event->position();
    offset_ = mouse + (offset_ - mouse) * factor;
    scale_ = qBound(0.15f, scale_ * factor, 6.f);
    buildLayout();
    update();
}

void TreeWidget::mousePressEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton) {
        dragging_ = true;
        lastMouse_ = event->pos();
        setCursor(Qt::ClosedHandCursor);
    }
}

void TreeWidget::mouseMoveEvent(QMouseEvent* event) {
    if (dragging_) {
        QPoint delta = event->pos() - lastMouse_;
        offset_ += QPointF(delta);
        lastMouse_ = event->pos();
        update();
    }
}

void TreeWidget::mouseReleaseEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton) {
        dragging_ = false;
        setCursor(Qt::ArrowCursor);
    }
}

void TreeWidget::resizeEvent(QResizeEvent*) {
    if (offset_.isNull() && !nodes_.isEmpty())
        offset_ = { width() / 2.f - nodes_[0].x * scale_, 30.f };
}
