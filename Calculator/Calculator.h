#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui
{
  class Calculator;
}
QT_END_NAMESPACE

class Calculator : public QMainWindow
{
  Q_OBJECT

  public:
  Calculator(QWidget *parent = nullptr);
  ~Calculator();

  // I should work to get rid of this or just make this better
  // To keep track of the state of the calculator
  enum State
  {
    INIT,
    INPUTTING,
    RESULT,
    ANS,
    ERROR,
    HISTORY,
  };

  private slots:
  void oneClicked();
  void twoClicked();
  void threeClicked();
  void fourClicked();
  void fiveClicked();
  void sixClicked();
  void sevenClicked();
  void eightClicked();
  void nineClicked();
  void zeroClicked();
  void addClicked();
  void subClicked();
  void divClicked();
  void multClicked();
  void dotClicked();
  void ansClicked();
  void histClicked();
  void eraseClicked();
  void openParenClicked();
  void closeParenClicked();
  void powerClicked();
  void sqrtClicked();
  void helpClicked();
  // clicking the "=" button
  void evaluate();
  void clearResult();

  private:
  Ui::Calculator *ui;
  State m_state;
  // Save the last expression (what the user typed) to show in History
  QString m_lastExpression;
  // Save the result of the last expression to show in History
  QString m_lastResult;

  private:
  /**
   * Generic function for what to do when a button is clicked.
   *
   * @param value The value associated with the button
   */
  void buttonClicked(const QString &value);
  /**
   * Checks if the last character inputted is an operator(or operation)
   * @return true if the last character is an operator or operation, false
   * otherwise.
   */
  bool lastIsOperator();
  /**
   * Overriden function to handle key presses
   */
  void keyPressEvent(QKeyEvent *event);
};
#endif  // CALCULATOR_H
