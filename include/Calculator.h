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

    enum Operation{
        ADD,
        SUBTRACT,
        MULTIPLY,
        DIVIDE,
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
    //clicking the "=" button
    void evaluate();
    void clearResult();


private:
    Ui::Calculator *ui;
    //these 3 will be gone once the calculator can deal with full expressions
    bool m_inputDone;
    bool m_resultShown;
    double m_firstOperand;
    double m_secondOperand;
    bool m_ans;
    bool m_hist;
    QString m_lastOperationsBeforeClear;
    void numberClicked(const QString &number);
    void operationClicked(const QString &operation);
};
#endif // CALCULATOR_H
