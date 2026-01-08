#include <QApplication>
#include <QLoggingCategory>
#include "main_window.h"

int main(int argc, char *argv[]) {
#ifdef QT_DEBUG
    QLoggingCategory::defaultCategory()->setEnabled(QtDebugMsg, true);
#endif

    QApplication app(argc, argv);
    MainWindow mainWindow;
    
    mainWindow.show();

    return app.exec();
}