#include "dialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // load qss
    QFile qssFile(":/style");
    if (qssFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        a.setStyleSheet(qssFile.readAll());
        qssFile.close();
    }

    Dialog w;
    w.show();

    return a.exec();
}
