#include "MainWindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

//    DbController Dbcon;
    QThread      db_thread;

    DbController::instance().moveToThread(&db_thread);
    db_thread.start();

    MainWindow window(0, &DbController::instance(), &db_thread);
    window.show();

    return app.exec();
}
