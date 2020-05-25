#ifndef KEYPRESSHANDLER_H
#define KEYPRESSHANDLER_H

#include <QKeyEvent>

namespace Ui
{
class Calculator;
}

class KeypressHandler
{
  public:
  KeypressHandler() = delete;

  static void keyPress(int key, Ui::Calculator* ui);
};

#endif  // KEYPRESSHANDLER_H
