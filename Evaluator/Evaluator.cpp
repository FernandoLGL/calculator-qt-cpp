#include "Evaluator.h"

#include <QMessageBox>

#include "../extlib/exprtk.hpp"
#include "HistoryController/HistoryController.h"
#include "ui_Calculator.h"

void Evaluator::oneButtonPress(Ui::Calculator *ui) { buttonPressed("1", ui); }

void Evaluator::twoButtonPress(Ui::Calculator *ui) { buttonPressed("2", ui); }

void Evaluator::threeButtonPress(Ui::Calculator *ui) { buttonPressed("3", ui); }

void Evaluator::fourButtonPress(Ui::Calculator *ui) { buttonPressed("4", ui); }

void Evaluator::fiveButtonPress(Ui::Calculator *ui) { buttonPressed("5", ui); }

void Evaluator::sixButtonPress(Ui::Calculator *ui) { buttonPressed("6", ui); }

void Evaluator::sevenButtonPress(Ui::Calculator *ui) { buttonPressed("7", ui); }

void Evaluator::eightButtonPress(Ui::Calculator *ui) { buttonPressed("8", ui); }

void Evaluator::nineButtonPress(Ui::Calculator *ui) { buttonPressed("9", ui); }

void Evaluator::zeroButtonPress(Ui::Calculator *ui) { buttonPressed("0", ui); }

void Evaluator::addButtonPress(Ui::Calculator *ui) { buttonPressed("+", ui); }

void Evaluator::subButtonPress(Ui::Calculator *ui) { buttonPressed("-", ui); }

void Evaluator::divButtonPress(Ui::Calculator *ui) { buttonPressed("/", ui); }

void Evaluator::multButtonPress(Ui::Calculator *ui) { buttonPressed("x", ui); }

void Evaluator::dotButtonPress(Ui::Calculator *ui) { buttonPressed(".", ui); }

void Evaluator::openParenButtonPress(Ui::Calculator *ui) { buttonPressed("(", ui); }

void Evaluator::closeParenButtonPress(Ui::Calculator *ui) { buttonPressed(")", ui); }

void Evaluator::powerButtonPress(Ui::Calculator *ui) { buttonPressed("^", ui); }

void Evaluator::sqrtButtonPress(Ui::Calculator *ui) { buttonPressed("^(1/2)", ui); }

void Evaluator::ansButtonPress(Ui::Calculator *ui)
{
  /*
   * Expected behavior:
   * If what is displayed is the "cleared" state (0.0), we can just replace it by "ANS" so it can be parsed later.
   * If the last character is a binary operator, we may just append "ANS" so that it can be included in the
   * calculations.
   * Otherwise, we will append a multiplication by "ANS", which replicates the behavior of most calculators out there.
   * e.g.: if ANS is 2, "45ANS" means "45 x ANS" which is evaluated to "90".
   */
  QString previous = ui->display->text();
  if (previous == "0.0")
  {
    ui->display->setText("ANS");
    return;
  }
  else if (lastIsBinaryOperator(ui))
  {
    ui->display->setText(previous += "ANS");
    return;
  }
  ui->display->setText(previous += "xANS");
}

void Evaluator::histButtonPress(QWidget *calculator)
{
  QString history = HistoryController::getHistory();
  QMessageBox::about(calculator, "History", history);
}

void Evaluator::eraseButtonPress(Ui::Calculator *ui)
{
  /*
   * Expected behavior:
   * If the display is 1 char long when this is called, we reset it to the initial state (0.0).
   * else if the display ends with "ANS", we have to erase the entire "ANS" text
   * Otherwise, we erase the last char.
   */
  QString previous = ui->display->text();
  if (previous == "0.0")
    return;
  else if (ui->display->text().length() == 1)
    ui->display->setText("0.0");
  else if (ui->display->text().endsWith("ANS"))
  {
    // 3 is the length of "ANS"
    ui->display->setText(previous.chopped(3));
  }
  else
    ui->display->setText(previous.chopped(1));
}

void Evaluator::helpButtonPress(QWidget *calculator)
{
  QMessageBox::about(calculator,
                     "DON'T PANIC!",
                     "Shortcuts: \n\nS - Sqrt(Square Root)\nA - ANS (last answer)\nC - "
                     "Clear\nH - History\n(P)anic - This Help Window\n");
}

void Evaluator::evaluateButtonPress(Ui::Calculator *ui)
{
  using expression_t = exprtk::expression<double>;
  using parser_t     = exprtk::parser<double>;

  QString previous = ui->display->text();

  if (expressionIsANumber(previous))
    // in these cases we don't have to do anything since the result is already displayed on the screen (for example, 81
    // = 81). And we don't want to add it to history either.
    return;
  else if (expressionIsTheSame(previous))
  {
    // if the expression is the same as the one that was evaluated before; we still want to show the result to the user,
    // but we don't want to unnecessarily evaluate it and put it in the history.
    ui->display->setText(HistoryController::getLastResult());
    return;
  }

  ui->display->setText(previous.replace("ANS", HistoryController::getLastResult()));
  parseExpression(previous);

  std::string expression_string = previous.toStdString();

  expression_t expression;

  // Because we want to keep track of the typed expression so we can add it to history later on
  QString lastExpression = ui->display->text();

  parser_t parser;

  double result{};

  // if the expression was evaluated successfully
  if (parser.compile(expression_string, expression))
  {
    result = expression.value();

    ui->display->setText(QString::number(result));
  }
  else
  {
    ui->display->setText("Syntax ERROR");
    return;
  }

  HistoryController::setLastExpression(lastExpression);
  HistoryController::setLastResult(QString::number(result));

  HistoryController::addToHistory();
}

void Evaluator::clearResultButtonPress(Ui::Calculator *ui)
{
  /*
   * Expected behavior:
   * Reset to 0.0
   */
  ui->display->setText("0.0");
}

void Evaluator::buttonPressed(const QString &text, Ui::Calculator *ui)
{
  QString previous = ui->display->text();
  if (previous == "0.0")
  {
    ui->display->setText(text);
    return;
  }
  // Look for ANS and replace with last result so it looks nicer
  ui->display->setText(previous.replace("ANS", HistoryController::getLastResult()));
  ui->display->setText(previous += text);
}

bool Evaluator::lastIsBinaryOperator(Ui::Calculator *ui)
{
  // Regex of the binary operators
  QRegExp rx("[\\^x+/-]");
  // right(1) is the same as returning the last character (QChar) as a QString
  if (rx.exactMatch(ui->display->text().right(1))) return true;
  return false;
}

void Evaluator::parseExpression(QString &expression) { expression.replace('x', '*'); }

bool Evaluator::expressionIsANumber(QString &expression)
{
  // If there are no operators, then the expression must be a number
  QRegExp rx("[\\^x+/-]");

  foreach (const auto &c, expression)
  {
    if (rx.exactMatch(c)) return false;
  }
  return true;
}

bool Evaluator::expressionIsTheSame(QString &expression)
{
  if (HistoryController::getLastExpression() == expression) return true;
  return false;
}
