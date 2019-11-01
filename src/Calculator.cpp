#include "Calculator.h"
#include "ui_Calculator.h"
#include "exprtk.hpp"
//#include <QDebug>
#include <QKeyEvent>
#include <QMessageBox>

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
    connect(ui->pushButton_power, &QPushButton::clicked, this, &Calculator::powerClicked);
    connect(ui->pushButton_sqrt, &QPushButton::clicked, this, &Calculator::sqrtClicked);
    connect(ui->pushButton_help, &QPushButton::clicked, this, &Calculator::helpClicked);
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
    expression.replace('x','*');
    expression.replace("(sqrt)", "^(1/2)");
    return expression;
}

void Calculator::evaluate(){
    if(m_state == INIT) return;
    using expression_t = exprtk::expression<double>;
    using parser_t = exprtk::parser<double>;

    if(m_state == ANS) ui->resultado->setText(ui->resultado->text().replace("ANS", m_lastResult));

    std::string expression_string = parseExpression(ui->resultado->text()).toStdString();

    //qDebug() << "Expressao passada: " << QString::fromStdString(expression_string);
    expression_t expression;

    QString tmp = ui->resultado->text();

    parser_t parser;

    double result{};
    if (parser.compile(expression_string,expression))
    {
        result = expression.value();

        ui->resultado->setText(QString::number(result));
    }
    else{
        ui->resultado->setText("ERROR");
        m_state = ERROR;
        return;
    }

    m_lastExpression = tmp;
    m_lastResult = QString::number(result);
    m_state = RESULT;
}

void Calculator::buttonClicked(const QString &textOnButton){
    QString previous = ui->resultado->text();
    if (m_state == ANS)
        ui->resultado->setText(previous.replace("ANS",m_lastResult));
    if(m_state == INIT || m_state == RESULT || m_state == ERROR){
        ui->resultado->setText(textOnButton);
        m_state = INPUTTING;
        return;
    }
    m_state = INPUTTING;
    ui->resultado->setText(previous+=textOnButton);
}

void Calculator::ansClicked(){
    QString previous = ui->resultado->text();
    if(m_state == ERROR || m_state == INIT) return;
    if (m_state == RESULT)
        ui->resultado->setText("ANS");
    else
        ui->resultado->setText(previous+"ANS");
    m_state = ANS;
}

void Calculator::dotClicked(){
    // There can't be two dots next to each other
    if(ui->resultado->text().back() == '.') return;
    buttonClicked(".");
}

void Calculator::oneClicked(){
    if (m_state == ANS) return;
    buttonClicked("1");
}

void Calculator::twoClicked(){
    if (m_state == ANS) return;
    buttonClicked("2");
}
void Calculator::threeClicked(){
    if (m_state == ANS) return;
    buttonClicked("3");
}
void Calculator::fourClicked(){
    if (m_state == ANS) return;
    buttonClicked("4");
}
void Calculator::fiveClicked(){
    if (m_state == ANS) return;
    buttonClicked("5");
}
void Calculator::sixClicked(){
    if (m_state == ANS) return;
    buttonClicked("6");
}
void Calculator::sevenClicked(){
    if (m_state == ANS) return;
    buttonClicked("7");
}
void Calculator::eightClicked(){
    if (m_state == ANS) return;
    buttonClicked("8");
}
void Calculator::nineClicked(){
    if (m_state == ANS) return;
    buttonClicked("9");
}
void Calculator::zeroClicked(){
    if (m_state == ANS) return;
    buttonClicked("0");
}
void Calculator::openParenClicked(){
    buttonClicked("(");
}
void Calculator::closeParenClicked(){
    buttonClicked(")");
}

void Calculator::sqrtClicked(){
    if(lastIsOperator()) return;
    // Operations can't be the first character
    if(ui->resultado->text().isEmpty() || m_state == INIT || m_state == RESULT) return;
    buttonClicked("(sqrt)");
}

void Calculator::helpClicked()
{
    QMessageBox::about(this, "DON'T PANIC!", "Shortcuts: \n\nS - Sqrt(Square Root)\nA - ANS (last answer)\nC - Clear\nH - History\nP - this help window (stands for Panic)");
}

void Calculator::powerClicked()
{
    if(lastIsOperator()) return;
    // Operations can't be the first character
    if(ui->resultado->text().isEmpty() || m_state == INIT || m_state == RESULT) return;
    buttonClicked("^");
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
    buttonClicked("x");
}
bool Calculator::lastIsOperator(){
    // Regex of the operators
    QRegExp rx("[\\(sqrt\\)\\^x+/-]");
    // right(1) is the same as returning the last character (QChar) as a QString
    if(rx.exactMatch(ui->resultado->text().right(1)))
        return true;
    return false;
}
void Calculator::eraseClicked(){
    // if we don't specify what happens when it's empty, the program crashes.
    if(ui->resultado->text().isEmpty()) return;
    if(m_state == INIT || m_state == ERROR) return;
    QString previous = ui->resultado->text();
    ui->resultado->setText(previous.chopped(1));
    if(ui->resultado->text().isEmpty()){
        ui->resultado->setText("0.0");
        m_state = INIT;
        return;
    }
    m_state = INPUTTING;
}

void Calculator::keyPressEvent(QKeyEvent *event){
    //qDebug() << event->key();
    switch(event->key()){
    case Qt::Key_0:
        zeroClicked();
        break;
    case Qt::Key_1:
        oneClicked();
        break;
    case Qt::Key_2:
        twoClicked();
        break;
    case Qt::Key_3:
        threeClicked();
        break;
    case Qt::Key_4:
        fourClicked();
        break;
    case Qt::Key_5:
        fiveClicked();
        break;
    case Qt::Key_6:
        sixClicked();
        break;
    case Qt::Key_7:
        sevenClicked();
        break;
    case Qt::Key_8:
        eightClicked();
        break;
    case Qt::Key_9:
        nineClicked();
        break;
    case Qt::Key_ParenLeft:
        openParenClicked();
        break;
    case Qt::Key_ParenRight:
        closeParenClicked();
        break;
    case Qt::Key_Asterisk:
        multClicked();
        break;
    case Qt::Key_Slash:
        divClicked();
        break;
    case Qt::Key_Minus:
        subClicked();
        break;
    case Qt::Key_Equal:
    case Qt::Key_Enter:
    case Qt::Key_Return:
        evaluate();
        break;
    case Qt::Key_Plus:
        addClicked();
        break;
    case Qt::Key_Backspace:
        eraseClicked();
        break;
    case Qt::Key_Period:
    case Qt::Key_periodcentered:
        dotClicked();
        break;
    case Qt::Key_H:
        histClicked();
        break;
    case Qt::Key_A:
        ansClicked();
        break;
    case Qt::Key_C:
        clearResult();
        break;
    case Qt::Key_Dead_Circumflex:
        powerClicked();
        break;
    case Qt::Key_S:
        sqrtClicked();
        break;
    case Qt::Key_P:
        helpClicked();
        break;
    }
}
