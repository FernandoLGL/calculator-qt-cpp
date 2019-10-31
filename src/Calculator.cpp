#include "Calculator.h"
#include "ui_Calculator.h"
#include "exprtk.hpp"
#include <QDebug>

Calculator::Calculator(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Calculator)
    , m_state(INIT)
    , m_lastExpression()
    , m_lastResult()
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
    connect(ui->pushButton_ans, &QPushButton::clicked, this, &Calculator::ansClicked);
    connect(ui->pushButton_hist, &QPushButton::clicked, this, &Calculator::histClicked);
    connect(ui->pushButton_erase, &QPushButton::clicked, this, &Calculator::eraseClicked);
    connect(ui->pushButton_openParen, &QPushButton::clicked, this, &Calculator::openParenClicked);
    connect(ui->pushButton_closeParen, &QPushButton::clicked, this, &Calculator::closeParenClicked);
}

Calculator::~Calculator()
{
    delete ui;
}

void Calculator::clearResult(){
    ui->resultado->setText("0.0");
    m_state = INIT;
}

void Calculator::histClicked(){
    ui->resultado->setText("Last result: " + m_lastExpression + " = " + m_lastResult);
    m_state = INIT;
}

QString parseExpression(QString expression){
    expression.replace('X','*');
    return expression;
}

void Calculator::evaluate(){
    using expression_t = exprtk::expression<double>;
    using parser_t = exprtk::parser<double>;

    m_lastExpression = ui->resultado->text();
    std::string expression_string = parseExpression(ui->resultado->text()).toStdString();

    expression_t expression;

    parser_t parser;

    if (parser.compile(expression_string,expression))
    {
        double result = expression.value();

        ui->resultado->setText(QString::number(result));
        m_lastResult = QString::number(result);
    }
    else{
        ui->resultado->setText("ERROR");
        m_state = ERROR;
        return;
    }

    m_state = RESULT;
}

void Calculator::buttonClicked(const QString &textOnButton){
    QString previous = ui->resultado->text();
    if(m_state == INIT || m_state == RESULT || m_state == ERROR){
        ui->resultado->setText(textOnButton);
        m_state = INPUTTING;
        return;
    }
    m_state = INPUTTING;
    ui->resultado->setText(previous+=textOnButton);
}

void Calculator::ansClicked(){
    ui->resultado->setText(m_lastResult);
    m_state = ANS;
}

void Calculator::dotClicked(){
    buttonClicked(".");
}

void Calculator::oneClicked(){
    buttonClicked("1");
}

void Calculator::twoClicked(){
    buttonClicked("2");
}
void Calculator::threeClicked(){
    buttonClicked("3");
}
void Calculator::fourClicked(){
    buttonClicked("4");
}
void Calculator::fiveClicked(){
    buttonClicked("5");
}
void Calculator::sixClicked(){
    buttonClicked("6");
}
void Calculator::sevenClicked(){
    buttonClicked("7");
}
void Calculator::eightClicked(){
    buttonClicked("8");
}
void Calculator::nineClicked(){
    buttonClicked("9");
}
void Calculator::zeroClicked(){
    buttonClicked("0");
}
void Calculator::openParenClicked(){
    buttonClicked("(");
}
void Calculator::closeParenClicked(){
    buttonClicked(")");
}
void Calculator::addClicked(){
    if(lastIsOperator()) return;
    // Operations can't be the first character
    if(ui->resultado->text().isEmpty() || m_state == INIT || m_state == RESULT) return;
    buttonClicked("+");
}
void Calculator::subClicked(){
    if(lastIsOperator()) return;
    // Operations can't be the first character
    if(ui->resultado->text().isEmpty() || m_state == INIT || m_state == RESULT) return;
    buttonClicked("-");
}
void Calculator::divClicked(){
    if(lastIsOperator()) return;
    // Operations can't be the first character
    if(ui->resultado->text().isEmpty() || m_state == INIT || m_state == RESULT) return;
    buttonClicked("/");
}
void Calculator::multClicked(){
    if(lastIsOperator()) return;
    // Operations can't be the first character
    if(ui->resultado->text().isEmpty() || m_state == INIT || m_state == RESULT) return;
    buttonClicked("X");
}
bool Calculator::lastIsOperator(){
    // Regex of the operators
    QRegExp rx("[X+/-]");
    // right(1) is the same as returning the last character (QChar) as a QString
    if(rx.exactMatch(ui->resultado->text().right(1)))
        return true;
    return false;
}
void Calculator::eraseClicked(){
    // if we don't specify what happens when it's empty, the program crashes.
    if(ui->resultado->text().isEmpty()) return;
    QString previous = ui->resultado->text();
    ui->resultado->setText(previous.chopped(1));
}
