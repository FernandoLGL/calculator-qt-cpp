#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui
{
class Calculator;
}
QT_END_NAMESPACE

// Class responsible for the actual GUI
class Calculator : public QMainWindow
{
  Q_OBJECT

  public:
  Calculator(QWidget *parent = nullptr);
  ~Calculator();

  private slots:
  void on_pushButton_0_clicked();

  private:
  Ui::Calculator *ui;

  private:
  /**
   * Overriden function to handle key presses
   */
  void keyPressEvent(QKeyEvent *event);
};
#endif  // CALCULATOR_H
