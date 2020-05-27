#ifndef CLICKHANDLER_H
#define CLICKHANDLER_H

namespace Ui
{
class Calculator;
}

class QWidget;

// Class responsible for what happens when the user clicks a button
class ClickHandler
{
  public:
  ClickHandler() = delete;
  static void oneButtonPress(Ui::Calculator* ui);
  static void twoButtonPress(Ui::Calculator* ui);
  static void threeButtonPress(Ui::Calculator* ui);
  static void fourButtonPress(Ui::Calculator* ui);
  static void fiveButtonPress(Ui::Calculator* ui);
  static void sixButtonPress(Ui::Calculator* ui);
  static void sevenButtonPress(Ui::Calculator* ui);
  static void eightButtonPress(Ui::Calculator* ui);
  static void nineButtonPress(Ui::Calculator* ui);
  static void zeroButtonPress(Ui::Calculator* ui);
  static void addButtonPress(Ui::Calculator* ui);
  static void subButtonPress(Ui::Calculator* ui);
  static void divButtonPress(Ui::Calculator* ui);
  static void multButtonPress(Ui::Calculator* ui);
  static void dotButtonPress(Ui::Calculator* ui);
  static void ansButtonPress(Ui::Calculator* ui);
  static void histButtonPress(QWidget* calculator);
  static void eraseButtonPress(Ui::Calculator* ui);
  static void openParenButtonPress(Ui::Calculator* ui);
  static void closeParenButtonPress(Ui::Calculator* ui);
  static void powerButtonPress(Ui::Calculator* ui);
  static void sqrtButtonPress(Ui::Calculator* ui);
  static void helpButtonPress(QWidget* calculator);
  // clicking the "=" button
  static void evaluateButtonPress(Ui::Calculator* ui);
  static void clearResultButtonPress(Ui::Calculator* ui);
};

#endif  // CLICKHANDLER_H
