#ifndef KEYPRESSHANDLER_H
#define KEYPRESSHANDLER_H

#include <QKeyEvent>

namespace Ui
{
class Calculator;
}

class QWidget;

class KeypressHandler
{
  public:
  KeypressHandler() = delete;

  static void keyPress(int key, Ui::Calculator* ui, QWidget* calculator);
};

#endif  // KEYPRESSHANDLER_H
