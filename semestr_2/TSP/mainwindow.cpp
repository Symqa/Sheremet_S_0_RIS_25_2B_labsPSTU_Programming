#include "mainwindow.h"
#include "tspsolver.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QHeaderView>
#include <QMessageBox>
#include <QPainter>
#include <QFont>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    setWindowTitle("Задача Коммивояжёра — Метод Ветвей и Границ");
    setupUI();
    onLoadDemo();
}

void MainWindow::setupUI() {
    QWidget *central = new QWidget(this);
    setCentralWidget(central);
    QHBoxLayout *mainLayout = new QHBoxLayout(central);

    // ---- Left: scene + toolbar ----
    QVBoxLayout *leftLayout = new QVBoxLayout();

    // Toolbar
    QGroupBox *toolBox = new QGroupBox("Инструменты редактора");
    QHBoxLayout *toolLayout = new QHBoxLayout(toolBox);

    btnAddNode  = new QPushButton("Добавить узел");
    btnAddEdge  = new QPushButton("Добавить ребро");
    btnMove     = new QPushButton("Перемещение");
    btnDelNode  = new QPushButton("Удалить узел");
    btnDelEdge  = new QPushButton("Удалить ребро");
    btnDemo     = new QPushButton("Демо-граф");
    btnClear    = new QPushButton("Очистить");

    for (auto *btn : {btnAddNode, btnAddEdge, btnMove, btnDelNode, btnDelEdge, btnDemo, btnClear}) {
        btn->setCheckable(true);
        toolLayout->addWidget(btn);
    }
    btnDemo->setCheckable(false);
    btnClear->setCheckable(false);

    leftLayout->addWidget(toolBox);

    // Scene
    scene = new TSPScene(this);
    view  = new QGraphicsView(scene);
    view->setMinimumSize(700, 520);
    view->setRenderHint(QPainter::Antialiasing);
    view->setDragMode(QGraphicsView::NoDrag);
    leftLayout->addWidget(view);

    statusLbl = new QLabel("Режим: Добавить узел  |  Нажмите на сцену");
    leftLayout->addWidget(statusLbl);

    mainLayout->addLayout(leftLayout, 3);

    // ---- Right panel ----
    QVBoxLayout *rightLayout = new QVBoxLayout();

    // Matrix
    QGroupBox *matGroup = new QGroupBox("Матрица расстояний (0 = нет ребра)");
    QVBoxLayout *matLayout = new QVBoxLayout(matGroup);
    matrixTable = new QTableWidget();
    matrixTable->setMinimumHeight(210);
    matLayout->addWidget(matrixTable);
    btnApplyMatrix = new QPushButton("Применить матрицу к графу");
    matLayout->addWidget(btnApplyMatrix);
    rightLayout->addWidget(matGroup);

    // Solve
    QGroupBox *solveGroup = new QGroupBox("Алгоритм");
    QVBoxLayout *solveLayout = new QVBoxLayout(solveGroup);
    btnSolve = new QPushButton("Решить задачу коммивояжёра");
    btnSolve->setMinimumHeight(40);
    btnSolve->setCheckable(false);
    solveLayout->addWidget(btnSolve);
    rightLayout->addWidget(solveGroup);

    // Log
    QGroupBox *logGroup = new QGroupBox("Результаты / Пошаговый разбор");
    QVBoxLayout *logLayout = new QVBoxLayout(logGroup);
    logEdit = new QTextEdit();
    logEdit->setReadOnly(true);
    logEdit->setMinimumHeight(280);
    logLayout->addWidget(logEdit);
    rightLayout->addWidget(logGroup, 1);

    mainLayout->addLayout(rightLayout, 2);

    resize(1280, 720);

    // Connect signals
    connect(btnAddNode,  &QPushButton::clicked, this, &MainWindow::onModeAddNode);
    connect(btnAddEdge,  &QPushButton::clicked, this, &MainWindow::onModeAddEdge);
    connect(btnMove,     &QPushButton::clicked, this, &MainWindow::onModeMoveNode);
    connect(btnDelNode,  &QPushButton::clicked, this, &MainWindow::onModeDeleteNode);
    connect(btnDelEdge,  &QPushButton::clicked, this, &MainWindow::onModeDeleteEdge);
    connect(btnDemo,     &QPushButton::clicked, this, &MainWindow::onLoadDemo);
    connect(btnClear,    &QPushButton::clicked, this, &MainWindow::onClearGraph);
    connect(btnSolve,    &QPushButton::clicked, this, &MainWindow::onSolve);
    connect(btnApplyMatrix, &QPushButton::clicked, this, &MainWindow::onMatrixApply);
    connect(scene, &TSPScene::graphChanged, this, &MainWindow::onGraphChanged);
    connect(matrixTable, &QTableWidget::cellChanged, this, &MainWindow::onEdgeWeightChanged);

    setActiveModeButton(btnAddNode);
}

void MainWindow::setActiveModeButton(QPushButton *btn) {
    for (auto *b : {btnAddNode, btnAddEdge, btnMove, btnDelNode, btnDelEdge})
        b->setChecked(false);
    if (btn) btn->setChecked(true);
}

void MainWindow::onModeAddNode()   { scene->setMode(TSPScene::Mode::AddNode);   setActiveModeButton(btnAddNode);  statusLbl->setText("Режим: Добавить узел  |  Кликните по сцене"); }
void MainWindow::onModeAddEdge()   { scene->setMode(TSPScene::Mode::AddEdge);   setActiveModeButton(btnAddEdge);  statusLbl->setText("Режим: Добавить ребро  |  Кликните первый узел, затем второй"); }
void MainWindow::onModeMoveNode()  { scene->setMode(TSPScene::Mode::MoveNode);  setActiveModeButton(btnMove);     statusLbl->setText("Режим: Перемещение  |  Тащите узел мышкой"); }
void MainWindow::onModeDeleteNode(){ scene->setMode(TSPScene::Mode::DeleteNode);setActiveModeButton(btnDelNode);  statusLbl->setText("Режим: Удалить узел  |  Кликните на узел"); }
void MainWindow::onModeDeleteEdge(){ scene->setMode(TSPScene::Mode::DeleteEdge);setActiveModeButton(btnDelEdge);  statusLbl->setText("Режим: Удалить ребро  |  Кликните на ребро"); }

void MainWindow::onLoadDemo() {
    scene->loadDemoGraph();
    log("Загружен демо-граф: 6 локаций настольной игры.");
    log("Замок, Лес, Гора, Болото, Деревня, Руины — полный граф.");
}

void MainWindow::onClearGraph() {
    scene->clearGraph();
    matrixTable->clear();
    matrixTable->setRowCount(0);
    matrixTable->setColumnCount(0);
    logEdit->clear();
}

void MainWindow::onGraphChanged() {
    syncMatrixFromScene();
}

void MainWindow::syncMatrixFromScene() {
    matrixSyncing = true;
    matrixTable->blockSignals(true);

    int n = scene->nodeCount();
    auto mat = scene->getMatrix();
    auto names = scene->getNodeNames();

    matrixTable->setRowCount(n);
    matrixTable->setColumnCount(n);
    matrixTable->setHorizontalHeaderLabels(names);
    matrixTable->setVerticalHeaderLabels(names);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int val = mat[i][j];
            QString txt = (val == 0 || val == TSP_INF) ? "0" : QString::number(val);
            auto *item = new QTableWidgetItem(txt);
            item->setTextAlignment(Qt::AlignCenter);
            matrixTable->setItem(i, j, item);
        }
    }
    matrixTable->resizeColumnsToContents();
    matrixTable->blockSignals(false);
    matrixSyncing = false;
}

void MainWindow::onEdgeWeightChanged(int row, int col) {
    if (matrixSyncing) return;
}

void MainWindow::onMatrixApply() {
    int n = matrixTable->rowCount();
    QStringList names;
    QVector<QVector<int>> mat(n, QVector<int>(n, TSP_INF));
    for (int i = 0; i < n; i++) {
        names << matrixTable->horizontalHeaderItem(i)->text();
        for (int j = 0; j < n; j++) {
            if (!matrixTable->item(i,j)) continue;
            bool ok;
            int v = matrixTable->item(i,j)->text().toInt(&ok);
            if (!ok || v <= 0) mat[i][j] = (i==j ? 0 : TSP_INF);
            else mat[i][j] = (i==j ? 0 : v);
        }
    }
    scene->setMatrix(mat, names);
    log("Граф обновлён из матрицы.");
}

void MainWindow::onSolve() {
    scene->clearHighlight();
    int n = scene->nodeCount();
    if (n < 2) { log("Добавьте хотя бы 2 вершины."); return; }

    auto mat = scene->getMatrix();
    auto names = scene->getNodeNames();

    logEdit->clear();
    log("Запуск алгоритма Ветвей и Границ...");

    TSPResult res = TSPSolver::solve(mat, names);

    for (auto &s : res.steps) log(s);

    if (res.solvable) {
        scene->highlightTour(res.tour);
        log(QString("\nОптимальный маршрут найден! Стоимость: %1").arg(res.cost));
    } else {
        log("Гамильтонов цикл не найден для данного графа.");
    }
}

void MainWindow::log(const QString &msg) {
    logEdit->append(msg);
}
