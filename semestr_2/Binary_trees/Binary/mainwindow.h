#pragma once
#include <QMainWindow>
#include <QTextEdit>
#include <QLineEdit>
#include "BST.h"
#include "TreeWidget.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow() override;

private slots:
    void onInsert();
    void onRemove();
    void onSearch();
    void onPreOrder();
    void onInOrder();
    void onPostOrder();
    void onBalance();
    void onPrintH();
    void onPrintV();
    void onCountChar();
    void onClearTree();
    void onLoadDemo();

private:
    BST         tree_;
    TreeWidget* treeView_  = nullptr;
    QTextEdit*  logEdit_   = nullptr;
    QLineEdit*  inputEdit_ = nullptr;
    QLineEdit*  charEdit_  = nullptr;

    void log(const QString& msg);
    void refreshTree();
};
