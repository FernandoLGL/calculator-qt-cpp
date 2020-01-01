#include "Calculator.h"

#include "exprtk.hpp"
#include "ui_Calculator.h"
//#include <QDebug>
#include <QKeyEvent>
#include <QMessageBox>

Calculator::Calculator(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::Calculator),
      m_state(INIT),
      m_lastExpression(),
      m_lastResult() {
        ui->setupUi(this);

        // Connecting the appropriate functions to the appropriate objects so
        // that I can use my own functions
        connect(ui->pushButton_1, &QPushButton::clicked, this,
                &Calculator::oneClicked);
        connect(ui->pushButton_2, &QPushButton::clicked, this,
                &Calculator::twoClicked);
        connect(ui->pushButton_3, &QPushButton::clicked, this,
                &Calculator::threeClicked);
        connect(ui->pushButton_4, &QPushButton::clicked, this,
                &Calculator::fourClicked);
        connect(ui->pushButton_5, &QPushButton::clicked, this,
                &Calculator::fiveClicked);
        connect(ui->pushButton_6, &QPushButton::clicked, this,
                &Calculator::sixClicked);
        connect(ui->pushButton_7, &QPushButton::clicked, this,
                &Calculator::sevenClicked);
        connect(ui->pushButton_8, &QPushButton::clicked, this,
                &Calculator::eightClicked);
        connect(ui->pushButton_9, &QPushButton::clicked, this,
                &Calculator::nineClicked);
        connect(ui->pushButton_0, &QPushButton::clicked, this,
                &Calculator::zeroClicked);
        connect(ui->pushButton_adicao, &QPushButton::clicked, this,
                &Calculator::addClicked);
        connect(ui->pushButton_divisao, &QPushButton::clicked, this,
                &Calculator::divClicked);
        connect(ui->pushButton_subtracao, &QPushButton::clicked, this,
                &Calculator::subClicked);
        connect(ui->pushButton_multiplicacao, &QPushButton::clicked, this,
                &Calculator::multClicked);
        connect(ui->pushButton_igual, &QPushButton::clicked, this,
                &Calculator::evaluate);
        connect(ui->pushButton_Clear, &QPushButton::clicked, this,
                &Calculator::clearResult);
        connect(ui->pushButton_dot, &QPushButton::clicked, this,
                &Calculator::dotClicked);
        connect(ui->pushButton_ans, &QPushButton::clicked, this,
                &Calculator::ansClicked);
        connect(ui->pushButton_hist, &QPushButton::clicked, this,
                &Calculator::histClicked);
        connect(ui->pushButton_erase, &QPushButton::clicked, this,
                &Calculator::eraseClicked);
        connect(ui->pushButton_openParen, &QPushButton::clicked, this,
                &Calculator::openParenClicked);
        connect(ui->pushButton_closeParen, &QPushButton::clicked, this,
                &Calculator::closeParenClicked);
        connect(ui->pushButton_power, &QPushButton::clicked, this,
                &Calculator::powerClicked);
        connect(ui->pushButton_sqrt, &QPushButton::clicked, this,
                &Calculator::sqrtClicked);
        connect(ui->pushButton_help, &QPushButton::clicked, this,
                &Calculator::helpClicked);
}

Calculator::~Calculator() { delete ui; }

// Clearing basically means that we have to reset the text and the calculator to
// their initial states.
void Calculator::clearResult() {
        ui->resultado->setText("0.0");
        m_state = INIT;
}

// When the user asks for their last expression and result, we have to show it
// to them and set the state to HISTORY
void Calculator::histClicked() {
        ui->resultado->setText("H: " + m_lastExpression + " = " + m_lastResult);
        m_state = HISTORY;
}

QString parseExpression(QString expression) {
        // Because we deal with the whole string on the input, we have to
        // replace 'x' with '*' and (sqrt) with ^(1/2) so that Exprtk
        // understands it properly.
        expression.replace('x', '*');
        expression.replace("(sqrt)", "^(1/2)");
        return expression;
}

void Calculator::evaluate() {
        // It doesn't make sense to evaluate at the beginning (or after history
        // or any modes that change the state to INIT)
        if (m_state == INIT || m_state == HISTORY) return;
        using expression_t = exprtk::expression<double>;
        using parser_t = exprtk::parser<double>;

        // Because "ANS" can be at the end (still in ANS state) and that should
        // not give an error.
        if (m_state == ANS)
                ui->resultado->setText(
                    ui->resultado->text().replace("ANS", m_lastResult));

        // The expression string we pass to Exprtk should be the parsed screen
        // text
        std::string expression_string =
            parseExpression(ui->resultado->text()).toStdString();

        // qDebug() << "Expressao passada: " <<
        // QString::fromStdString(expression_string);
        expression_t expression;

        // Because we want to keep track of the typed expression
        QString tmp = ui->resultado->text();

        parser_t parser;

        double result{};
        if (parser.compile(expression_string, expression)) {
                result = expression.value();

                ui->resultado->setText(QString::number(result));
        } else {
                ui->resultado->setText("ERROR");
                m_state = ERROR;
                return;
        }

        m_lastExpression = tmp;
        m_lastResult = QString::number(result);
        m_state = RESULT;
}

void Calculator::buttonClicked(const QString &textOnButton) {
        QString previous = ui->resultado->text();
        // Replace ANS with the last result when the user presses another button
        // right after asking for ANS, so that it looks nicer.
        if (m_state == ANS)
                ui->resultado->setText(previous.replace("ANS", m_lastResult));
        // Because whenever we are in an end or init state, we should overwrite
        // whatever is already on the screen with the button text
        if (m_state == INIT || m_state == RESULT || m_state == ERROR ||
            m_state == HISTORY) {
                ui->resultado->setText(textOnButton);
                m_state = INPUTTING;
                // because when doing this we don't want to append the button
                // text to the previous text
                return;
        }
        m_state = INPUTTING;
        ui->resultado->setText(previous += textOnButton);
}

void Calculator::ansClicked() {
        QString previous = ui->resultado->text();
        // It doesn't make sense to ask for ANS when facing an ERROR or when
        // the last result is unknown
        if (m_state == ERROR || m_lastResult.isEmpty()) return;
        // It doesn't make sense here to add the last result if we're
        // concatenating to a number. But this only applies for INPUTTING state.
        if (!lastIsOperator() && m_state == INPUTTING) return;
        // it doesn't make sense to concatenate ANS to ANS itself.
        if (previous.endsWith("ANS")) return;
        if (m_state == RESULT || m_state == HISTORY || m_state == INIT)
                ui->resultado->setText("ANS");
        else
                ui->resultado->setText(previous + "ANS");
        m_state = ANS;
}

void Calculator::dotClicked() {
        // There can't be two dots next to each other
        if (ui->resultado->text().back() == '.') return;
        buttonClicked(".");
}

void Calculator::oneClicked() {
        // Because you can't have something like ANS1, ANS2...
        if (m_state == ANS) return;
        buttonClicked("1");
}

void Calculator::twoClicked() {
        if (m_state == ANS) return;
        buttonClicked("2");
}
void Calculator::threeClicked() {
        if (m_state == ANS) return;
        buttonClicked("3");
}
void Calculator::fourClicked() {
        if (m_state == ANS) return;
        buttonClicked("4");
}
void Calculator::fiveClicked() {
        if (m_state == ANS) return;
        buttonClicked("5");
}
void Calculator::sixClicked() {
        if (m_state == ANS) return;
        buttonClicked("6");
}
void Calculator::sevenClicked() {
        if (m_state == ANS) return;
        buttonClicked("7");
}
void Calculator::eightClicked() {
        if (m_state == ANS) return;
        buttonClicked("8");
}
void Calculator::nineClicked() {
        if (m_state == ANS) return;
        buttonClicked("9");
}
void Calculator::zeroClicked() {
        if (m_state == ANS) return;
        QString previous = ui->resultado->text();
        // it doesn't make sense to start your calculations with 00
        if (previous == "0") return;
        buttonClicked("0");
}
void Calculator::openParenClicked() { buttonClicked("("); }
void Calculator::closeParenClicked() { buttonClicked(")"); }

void Calculator::sqrtClicked() {
        // We can't write ^^, ++, --...
        if (lastIsOperator()) return;
        // This operation can't be the first character
        if (ui->resultado->text().isEmpty() || m_state == INIT)
                return;
        if(m_state == RESULT || m_state == HISTORY){
            ansClicked();
        }
        buttonClicked("(sqrt)");
}

void Calculator::helpClicked() {
        QMessageBox::about(
            this, "DON'T PANIC!",
            "Shortcuts: \n\nS - Sqrt(Square Root)\nA - ANS (last answer)\nC - "
            "Clear\nH - History\n(P)anic - This Help Window\n");
}

void Calculator::powerClicked() {
        if (lastIsOperator()) return;
        // This operation can't be the first character
        if (ui->resultado->text().isEmpty() || m_state == INIT)
                return;
        if(m_state == RESULT || m_state == HISTORY){
            ansClicked();
        }
        buttonClicked("^");
}
void Calculator::addClicked() {
        if (lastIsOperator()) return;
        if(m_state == RESULT || m_state == HISTORY){
            ansClicked();
        }
        buttonClicked("+");
}
void Calculator::subClicked() {
        if (lastIsOperator()) return;
        if(m_state == RESULT || m_state == HISTORY){
            ansClicked();
        }
        buttonClicked("-");
}
void Calculator::divClicked() {
        if (lastIsOperator()) return;
        // This operation can't be the first character
        if (ui->resultado->text().isEmpty() || m_state == INIT)
                return;
        if(m_state == RESULT || m_state == HISTORY){
            ansClicked();
        }
        buttonClicked("/");
}
void Calculator::multClicked() {
        if (lastIsOperator()) return;
        // This operation can't be the first character
        if (ui->resultado->text().isEmpty() || m_state == INIT)
            return;
        if(m_state == RESULT || m_state == HISTORY){
            ansClicked();
        }
        buttonClicked("x");
}
bool Calculator::lastIsOperator() {
        // Regex of the operators
        QRegExp rx("[\\(sqrt\\)\\^x+/-]");
        // right(1) is the same as returning the last character (QChar) as a
        // QString
        if (rx.exactMatch(ui->resultado->text().right(1))) return true;
        return false;
}
void Calculator::eraseClicked() {
        // if we don't specify what happens when it's empty, the program
        // crashes.
        if (ui->resultado->text().isEmpty()) return;
        // We can't erase the error message nor does it make sense to erase the
        // history or the initial 0.0
        if (m_state == INIT || m_state == ERROR || m_state == HISTORY) return;
        QString previous = ui->resultado->text();
        // If the next in line to be erased is (sqrt), we have to remove it
        // entirely, not just the closing parentheses.
        if (previous.endsWith("(sqrt)"))
                // 6 is the length of (sqrt)
                ui->resultado->setText(previous.chopped(6));
        else
                ui->resultado->setText(previous.chopped(1));
        // we have to update our variable
        previous = ui->resultado->text();
        // If we erase the only remaining number, we are back to square one.
        if (previous.isEmpty()) {
                ui->resultado->setText("0.0");
                m_state = INIT;
                return;
        }
        m_state = INPUTTING;
}

void Calculator::keyPressEvent(QKeyEvent *event) {
        // qDebug() << event->key();
        // Long list of what to do when facing a key press
        switch (event->key()) {
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
                //since there is no comma, when the user presses it, it's assumed s/he meant  "."
                case Qt::Key_Comma:
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
