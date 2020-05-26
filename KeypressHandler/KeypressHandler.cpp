#include "KeypressHandler.h"

#include "Calculator/Calculator.h"
#include "Evaluator/Evaluator.h"

void KeypressHandler::keyPress(int key, Ui::Calculator* ui, QWidget* calculator)
{
  switch (key)
  {
    case Qt::Key_0: Evaluator::zeroButtonPress(ui); break;
    case Qt::Key_1: Evaluator::oneButtonPress(ui); break;
    case Qt::Key_2: Evaluator::twoButtonPress(ui); break;
    case Qt::Key_3: Evaluator::threeButtonPress(ui); break;
    case Qt::Key_4: Evaluator::fourButtonPress(ui); break;
    case Qt::Key_5: Evaluator::fiveButtonPress(ui); break;
    case Qt::Key_6: Evaluator::sixButtonPress(ui); break;
    case Qt::Key_7: Evaluator::sevenButtonPress(ui); break;
    case Qt::Key_8: Evaluator::eightButtonPress(ui); break;
    case Qt::Key_9: Evaluator::nineButtonPress(ui); break;
    case Qt::Key_ParenLeft: Evaluator::openParenButtonPress(ui); break;
    case Qt::Key_ParenRight: Evaluator::closeParenButtonPress(ui); break;
    case Qt::Key_Asterisk: Evaluator::multButtonPress(ui); break;
    case Qt::Key_Slash: Evaluator::divButtonPress(ui); break;
    case Qt::Key_Minus: Evaluator::subButtonPress(ui); break;
    case Qt::Key_Equal:
    case Qt::Key_Enter:
    case Qt::Key_Return: Evaluator::evaluateButtonPress(ui); break;
    case Qt::Key_Plus: Evaluator::addButtonPress(ui); break;
    case Qt::Key_Backspace: Evaluator::eraseButtonPress(ui); break;
    case Qt::Key_Period:
    case Qt::Key_periodcentered:
    // since there is no comma, when the user presses it, it's assumed s/he meant  "."
    case Qt::Key_Comma: Evaluator::dotButtonPress(ui); break;
    case Qt::Key_H: Evaluator::histButtonPress(calculator); break;
    case Qt::Key_A: Evaluator::ansButtonPress(ui); break;
    case Qt::Key_C: Evaluator::clearResultButtonPress(ui); break;
    case Qt::Key_Dead_Circumflex: Evaluator::powerButtonPress(ui); break;
    case Qt::Key_S: Evaluator::sqrtButtonPress(ui); break;
    case Qt::Key_P: Evaluator::helpButtonPress(calculator); break;
  }
}
