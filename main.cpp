#include <QApplication>

#include "Calculator/Calculator.h"

int main(int argc, char* argv[])
{
  // If I ever decide to make an Android build
  // QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
  QApplication a(argc, argv);
  Calculator w;
  w.show();
  return a.exec();
}
