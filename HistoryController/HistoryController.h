#ifndef HISTORYCONTROLLER_H
#define HISTORYCONTROLLER_H

#include <QString>
#include <array>

#include "Constants/Constants.h"

class HistoryController
{
  // Each array index is a line of the history
  static std::array<QString, HISTORY_SIZE> m_historyText;
  static int m_historyCounter;

  static QString m_lastResult;
  static QString m_lastExpression;

  public:
  HistoryController() = delete;

  public:
  static void addToHistory();
  static QString getHistory()
  {
    QString history;
    for (const auto& historyLine : m_historyText)
    {
      history += historyLine;
    }
    return history;
  }

  static QString getLastResult() { return m_lastResult; }
  static void setLastResult(const QString& lastResult) { m_lastResult = lastResult; }
  static QString getLastExpression() { return m_lastExpression; }
  static void setLastExpression(const QString& lastExpression) { m_lastExpression = lastExpression; }

  private:
  /**
   * @brief shiftUp once the history is at full capacity, shifts every line up, discarding the first, so that the last
   * expression and its result can be displayed at the bottom
   */
  static void shiftUp();
  /**
   * @brief isFull checks if the history is at full capacity
   * @return  true if the history is at full capacity; false otherwise.
   */
  static bool isFull();
};

#endif  // HISTORYCONTROLLER_H
