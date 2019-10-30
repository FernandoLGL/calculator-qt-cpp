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


private:
    Ui::Calculator *ui;
    void numberClicked(const QString &number);
    void operationClicked(const QString &operation);
};
#endif // CALCULATOR_H
