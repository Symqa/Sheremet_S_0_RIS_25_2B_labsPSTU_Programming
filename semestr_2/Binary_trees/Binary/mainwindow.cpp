#include "MainWindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QGroupBox>
#include <QSplitter>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QMenuBar>
#include <QStatusBar>
#include <QApplication>
#include <sstream>
#include <iostream>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent)
{
    setWindowTitle("Бинарное дерево поиска");
    resize(1000, 600);

    // Центральный виджет
    auto* central = new QWidget;
    setCentralWidget(central);
    auto* mainLayout = new QHBoxLayout(central);

    // ── Левая панель управления ──────────────────────────────────────
    auto* leftPanel = new QWidget;
    leftPanel->setFixedWidth(200);
    auto* leftLayout = new QVBoxLayout(leftPanel);

    // Ввод строки
    leftLayout->addWidget(new QLabel("Строка:"));
    inputEdit_ = new QLineEdit;
    leftLayout->addWidget(inputEdit_);

    auto* btnInsert = new QPushButton("Вставить");
    auto* btnRemove = new QPushButton("Удалить");
    auto* btnSearch = new QPushButton("Найти");
    leftLayout->addWidget(btnInsert);
    leftLayout->addWidget(btnRemove);
    leftLayout->addWidget(btnSearch);

    leftLayout->addSpacing(10);
    leftLayout->addWidget(new QLabel("Обходы:"));
    auto* btnPre  = new QPushButton("Прямой");
    auto* btnIn   = new QPushButton("Симметричный");
    auto* btnPost = new QPushButton("Обратный");
    leftLayout->addWidget(btnPre);
    leftLayout->addWidget(btnIn);
    leftLayout->addWidget(btnPost);

    leftLayout->addSpacing(10);
    leftLayout->addWidget(new QLabel("Печать:"));
    auto* btnPH = new QPushButton("Горизонтальная");
    auto* btnPV = new QPushButton("Вертикальная");
    leftLayout->addWidget(btnPH);
    leftLayout->addWidget(btnPV);

    leftLayout->addSpacing(10);
    auto* btnBalance = new QPushButton("Балансировка");
    auto* btnDemo    = new QPushButton("Демо-данные");
    auto* btnClear   = new QPushButton("Очистить");
    leftLayout->addWidget(btnBalance);
    leftLayout->addWidget(btnDemo);
    leftLayout->addWidget(btnClear);

    leftLayout->addSpacing(10);
    leftLayout->addWidget(new QLabel("Подсчёт по символу:"));
    charEdit_ = new QLineEdit;
    charEdit_->setMaxLength(1);
    auto* btnCount = new QPushButton("Подсчитать");
    leftLayout->addWidget(charEdit_);
    leftLayout->addWidget(btnCount);

    leftLayout->addStretch();
    mainLayout->addWidget(leftPanel);

    // ── Правая часть: дерево + лог ──────────────────────────────────
    auto* rightSplit = new QSplitter(Qt::Vertical);

    treeView_ = new TreeWidget;
    logEdit_  = new QTextEdit;
    logEdit_->setReadOnly(true);
    logEdit_->setMaximumHeight(150);

    rightSplit->addWidget(treeView_);
    rightSplit->addWidget(logEdit_);
    rightSplit->setStretchFactor(0, 3);
    rightSplit->setStretchFactor(1, 1);
    mainLayout->addWidget(rightSplit, 1);

    // ── Сигналы ─────────────────────────────────────────────────────
    connect(btnInsert,  &QPushButton::clicked, this, &MainWindow::onInsert);
    connect(btnRemove,  &QPushButton::clicked, this, &MainWindow::onRemove);
    connect(btnSearch,  &QPushButton::clicked, this, &MainWindow::onSearch);
    connect(btnPre,     &QPushButton::clicked, this, &MainWindow::onPreOrder);
    connect(btnIn,      &QPushButton::clicked, this, &MainWindow::onInOrder);
    connect(btnPost,    &QPushButton::clicked, this, &MainWindow::onPostOrder);
    connect(btnPH,      &QPushButton::clicked, this, &MainWindow::onPrintH);
    connect(btnPV,      &QPushButton::clicked, this, &MainWindow::onPrintV);
    connect(btnBalance, &QPushButton::clicked, this, &MainWindow::onBalance);
    connect(btnDemo,    &QPushButton::clicked, this, &MainWindow::onLoadDemo);
    connect(btnClear,   &QPushButton::clicked, this, &MainWindow::onClearTree);
    connect(btnCount,   &QPushButton::clicked, this, &MainWindow::onCountChar);
    connect(inputEdit_, &QLineEdit::returnPressed, this, &MainWindow::onInsert);

    onLoadDemo();
}

MainWindow::~MainWindow() = default;

void MainWindow::log(const QString& msg) {
    logEdit_->append(msg);
}

void MainWindow::refreshTree() {
    treeView_->setTree(&tree_);
}

void MainWindow::onInsert() {
    QString s = inputEdit_->text().trimmed();
    if (s.isEmpty()) return;
    tree_.insert(s.toUtf8().constData());
    log("Вставлено: " + s);
    refreshTree();
    treeView_->clearHighlight();
    inputEdit_->clear();
}

void MainWindow::onRemove() {
    QString s = inputEdit_->text().trimmed();
    if (s.isEmpty()) return;
    if (tree_.remove(s.toUtf8().constData()))
        log("Удалено: " + s);
    else
        log("Не найдено: " + s);
    refreshTree();
    treeView_->clearHighlight();
    inputEdit_->clear();
}

void MainWindow::onSearch() {
    QString s = inputEdit_->text().trimmed();
    if (s.isEmpty()) return;
    Node* found = tree_.search(s.toUtf8().constData());
    if (found) { log("Найдено: " + s); treeView_->highlight(s); }
    else        { log("Не найдено: " + s); treeView_->clearHighlight(); }
}

void MainWindow::onPreOrder() {
    std::ostringstream oss;
    auto* old = std::cout.rdbuf(oss.rdbuf());
    tree_.preOrder(tree_.getRoot());
    std::cout.rdbuf(old);
    log("Прямой: " + QString::fromStdString(oss.str()));
}

void MainWindow::onInOrder() {
    std::ostringstream oss;
    auto* old = std::cout.rdbuf(oss.rdbuf());
    tree_.inOrder(tree_.getRoot());
    std::cout.rdbuf(old);
    log("Симметричный: " + QString::fromStdString(oss.str()));
}

void MainWindow::onPostOrder() {
    std::ostringstream oss;
    auto* old = std::cout.rdbuf(oss.rdbuf());
    tree_.postOrder(tree_.getRoot());
    std::cout.rdbuf(old);
    log("Обратный: " + QString::fromStdString(oss.str()));
}

void MainWindow::onBalance() {
    tree_.balance();
    log("Дерево сбалансировано.");
    refreshTree();
    treeView_->clearHighlight();
}

void MainWindow::onPrintH() {
    std::ostringstream oss;
    auto* old = std::cout.rdbuf(oss.rdbuf());
    tree_.printHorizontal();
    std::cout.rdbuf(old);
    log(QString::fromStdString(oss.str()));
}

void MainWindow::onPrintV() {
    std::ostringstream oss;
    auto* old = std::cout.rdbuf(oss.rdbuf());
    tree_.printVertical();
    std::cout.rdbuf(old);
    log(QString::fromStdString(oss.str()));
}

void MainWindow::onCountChar() {
    QString s = charEdit_->text().trimmed();
    if (s.isEmpty()) return;
    char c = s[0].toLatin1();
    int cnt = tree_.countStartingWith(c);
    log(QString("Начинаются с '%1': %2").arg(c).arg(cnt));
}

void MainWindow::onClearTree() {
    tree_.clear();
    log("Дерево очищено.");
    refreshTree();
    treeView_->clearHighlight();
}

void MainWindow::onLoadDemo() {
    tree_.clear();
    const char* words[] = {
        "apple", "banana", "cherry", "apricot", "avocado",
        "blueberry", "date", "elderberry", "fig", "grape",
        "almond", "blackberry", "coconut", nullptr
    };
    for (int i = 0; words[i]; ++i)
        tree_.insert(words[i]);
    log("Демо-данные загружены.");
    refreshTree();
    treeView_->clearHighlight();
}
