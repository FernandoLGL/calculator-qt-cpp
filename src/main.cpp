#include <QApplication>

#include "Calculator.h"

int main(int argc, char* argv[])
{
    //QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication a(argc, argv);
    Calculator w;
    w.show();
    return a.exec();
}
