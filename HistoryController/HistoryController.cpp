#include "HistoryController.h"

std::array<QString, HISTORY_SIZE> HistoryController::m_historyText;
int HistoryController::m_historyCounter = 0;
QString HistoryController::m_lastResult;
QString HistoryController::m_lastExpression;

void HistoryController::addToHistory()
{
  QString lastExpressionAndResult(m_lastExpression + " = " + m_lastResult + "\n");
  if (isFull())
  {
    shiftUp();
    m_historyText[m_historyText.max_size() - 1] = lastExpressionAndResult;
    return;
  }
  m_historyText[(m_historyCounter++) % m_historyText.max_size()] = lastExpressionAndResult;
}

void HistoryController::shiftUp()
{
  for (int i = 0; i < static_cast<int>(m_historyText.max_size() - 1); ++i)
  {
    m_historyText[i] = m_historyText[i + 1];
  }
}

bool HistoryController::isFull()
{
  if (m_historyCounter < static_cast<int>(m_historyText.max_size())) return false;
  return true;
}
