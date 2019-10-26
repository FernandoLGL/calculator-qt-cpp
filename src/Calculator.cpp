#include "Calculator.h"
#include "ui_Calculator.h"

Calculator::Calculator(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Calculator)
{
    ui->setupUi(this);
    connect(ui->resultado, &QLineEdit::returnPressed, this, &Calculator::returnPressed);
}

Calculator::~Calculator()
{
    delete ui;
}


void Calculator::returnPressed()
{
    double resultadoParcial {ui->resultado->text().toDouble()};
    ui->resultado->setText(QString::number(resultadoParcial));
}
