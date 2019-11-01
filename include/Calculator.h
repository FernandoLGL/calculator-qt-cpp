#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class Calculator; }
QT_END_NAMESPACE

class Calculator : public QMainWindow
{
    Q_OBJECT

public:
    Calculator(QWidget *parent = nullptr);
    ~Calculator();

    enum State{
        INIT,
        INPUTTING,
        RESULT,
        ANS,
        ERROR,
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
    //clicking the "=" button
    void evaluate();
    void clearResult();

private:
    Ui::Calculator *ui;
    QString m_lastOperationsBeforeClear;
    State m_state;
    QString m_lastExpression;
    QString m_lastResult;

private:
    void buttonClicked(const QString &number);
    bool lastIsOperator();
    void keyPressEvent(QKeyEvent *event);
};
#endif // CALCULATOR_H
