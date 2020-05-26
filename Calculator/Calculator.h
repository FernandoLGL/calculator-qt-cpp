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

  void on_pushButton_dot_clicked();

  void on_pushButton_1_clicked();

  void on_pushButton_2_clicked();

  void on_pushButton_3_clicked();

  void on_pushButton_4_clicked();

  void on_pushButton_5_clicked();

  void on_pushButton_6_clicked();

  void on_pushButton_7_clicked();

  void on_pushButton_8_clicked();

  void on_pushButton_9_clicked();

  void on_pushButton_add_clicked();

  void on_pushButton_ans_clicked();

  void on_pushButton_clear_clicked();

  void on_pushButton_closeParen_clicked();

  void on_pushButton_div_clicked();

  void on_pushButton_equals_clicked();

  void on_pushButton_erase_clicked();

  void on_pushButton_help_clicked();

  void on_pushButton_hist_clicked();

  void on_pushButton_mult_clicked();

  void on_pushButton_openParen_clicked();

  void on_pushButton_power_clicked();

  void on_pushButton_sqrt_clicked();

  void on_pushButton_sub_clicked();

  private:
  Ui::Calculator *ui;

  private:
  /**
   * Overriden function to handle key presses
   */
  void keyPressEvent(QKeyEvent *event);
};
#endif  // CALCULATOR_H
