#include <QApplication>
#include "MainWindow.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    // Метаданные приложения
    QApplication::setApplicationName("BSTLab");
    QApplication::setApplicationDisplayName("Бинарное дерево поиска (char*)");
    QApplication::setApplicationVersion("1.0");
    QApplication::setOrganizationName("PNRPU");

    MainWindow window;
    window.show();

    return app.exec();
}
