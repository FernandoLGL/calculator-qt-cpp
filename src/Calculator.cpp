#include "Calculator.h"
#include "ui_Calculator.h"

/*
 * Warning: This is the most atrocious code I have ever written and I'll never touch this again, this was just to get used to Qt Creator.
 * I'll do a better calculator in the future.
 */

Calculator::Calculator(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Calculator)
    , m_inputDone(false)
    , m_resultShown(false)
    , m_firstOperand(0.0)
    , m_secondOperand(0.0)
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
    connect(ui->pushButton_adicao, &QPushButton::clicked, this, &Calculator::addClicked);
    connect(ui->pushButton_divisao, &QPushButton::clicked, this, &Calculator::divClicked);
    connect(ui->pushButton_subtracao, &QPushButton::clicked, this, &Calculator::subClicked);
    connect(ui->pushButton_multiplicacao, &QPushButton::clicked, this, &Calculator::multClicked);
    connect(ui->pushButton_igual, &QPushButton::clicked, this, &Calculator::evaluate);
    connect(ui->pushButton_Clear, &QPushButton::clicked, this, &Calculator::clearResult);
    connect(ui->pushButton_dot, &QPushButton::clicked, this, &Calculator::dotClicked);
}

Calculator::~Calculator()
{
    delete ui;
}

void Calculator::clearResult(){
    ui->resultado->setText("0.0");
    ui->displayOperacao->setText("");
}

void Calculator::evaluate(){
    //can't end with "."
    if(ui->resultado->text().back() == '.') return;

    QString result;
    m_secondOperand = ui->resultado->text().toDouble();
    QChar op = ui->displayOperacao->text().front();
    switch(op.unicode()){
    case '+':
        result = QString::number(m_firstOperand + m_secondOperand);
        ui->resultado->setText(result);
        break;
    case '-':
        result = QString::number(m_firstOperand - m_secondOperand);
        ui->resultado->setText(result);
        break;
    case 'X':
        result = QString::number(m_firstOperand * m_secondOperand);
        ui->resultado->setText(result);
        break;
    case '/':
        result = QString::number(m_firstOperand / m_secondOperand);
        ui->resultado->setText(result);
        break;
    }
    m_inputDone=false;
    m_resultShown=true;
    return;
}

void Calculator::numberClicked(const QString &number){
    QString previousResult(ui->resultado->text());

    if(m_inputDone){
        m_firstOperand = previousResult.toDouble();
        ui->resultado->setText(number);
        m_inputDone=false;
        return;
    }

    // previousResult = 0 in case the user pressed 0 first
    // this second "if" condition will be a problem now that the dot has been added to the calculator
    if(m_resultShown || previousResult == "0.0" || previousResult == "0"){
        ui->resultado->setText(number);
        m_resultShown=false;
        return;
    }

    ui->resultado->setText(previousResult += number);
}

void Calculator::dotClicked(){
    //there can't be more than 1 dot
    if(ui->resultado->text().contains('.')) return;
    QString previousResult(ui->resultado->text());
    ui->resultado->setText(previousResult += ".");
}

void Calculator::operationClicked(const QString &operation){
    m_inputDone = true;
    ui->displayOperacao->setText(operation);
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

void Calculator::addClicked(){
    operationClicked("+");
}
void Calculator::subClicked(){
    operationClicked("-");
}
void Calculator::divClicked(){
    operationClicked("/");
}
void Calculator::multClicked(){
    operationClicked("X");
}
