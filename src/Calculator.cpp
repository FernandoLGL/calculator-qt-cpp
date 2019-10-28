#include "Calculator.h"
#include "ui_Calculator.h"

#include <QDebug>

Calculator::Calculator(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Calculator)
{
    ui->setupUi(this);
    connect(ui->pushButton_1, &QPushButton::clicked, this, &Calculator::oneClicked);
    connect(ui->pushButton_2, &QPushButton::clicked, this, &Calculator::twoClicked);
    connect(ui->pushButton_3, &QPushButton::clicked, this, &Calculator::threeClicked);
    connect(ui->pushButton_4, &QPushButton::clicked, this, &Calculator::fourClicked);
    connect(ui->pushButton_5, &QPushButton::clicked, this, &Calculator::fiveClicked);
    connect(ui->pushButton_6, &QPushButton::clicked, this, &Calculator::sixClicked);
    connect(ui->pushButton_7, &QPushButton::clicked, this, &Calculator::sevenClicked);
    connect(ui->pushButton_8, &QPushButton::clicked, this, &Calculator::eightClicked);
    connect(ui->pushButton_9, &QPushButton::clicked, this, &Calculator::nineClicked);
    connect(ui->pushButton_0, &QPushButton::clicked, this, &Calculator::zeroClicked);
}

Calculator::~Calculator()
{
    delete ui;
}

void Calculator::numberClicked(const QString &number){
    QString previousResult(ui->resultado->text());
    // previousResult = 0 in case the user pressed 0 first
    if(previousResult == "0.0" || previousResult == "0"){
        ui->resultado->setText(number);
        return;
    }
    ui->resultado->setText(previousResult += number);
}

void Calculator::oneClicked(){
    numberClicked("1");
}

void Calculator::twoClicked(){
    numberClicked("2");
}
void Calculator::threeClicked(){
    numberClicked("3");
}
void Calculator::fourClicked(){
    numberClicked("4");
}
void Calculator::fiveClicked(){
    numberClicked("5");
}
void Calculator::sixClicked(){
    numberClicked("6");
}
void Calculator::sevenClicked(){
    numberClicked("7");
}
void Calculator::eightClicked(){
    numberClicked("8");
}
void Calculator::nineClicked(){
    numberClicked("9");
}
void Calculator::zeroClicked(){
    numberClicked("0");
}
