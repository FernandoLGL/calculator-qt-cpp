#include "Calculator.h"

#include <QKeyEvent>
#include <QMessageBox>

#include "ClickHandler/ClickHandler.h"
#include "KeypressHandler/KeypressHandler.h"
#include "ui_Calculator.h"

Calculator::Calculator(QWidget *parent) : QMainWindow(parent), ui(new Ui::Calculator) { ui->setupUi(this); }

Calculator::~Calculator() { delete ui; }

void Calculator::keyPressEvent(QKeyEvent *event) { KeypressHandler::keyPress(event->key(), ui, this); }

void Calculator::on_pushButton_0_clicked() { ClickHandler::zeroButtonPress(ui); }

void Calculator::on_pushButton_1_clicked() { ClickHandler::oneButtonPress(ui); }

void Calculator::on_pushButton_2_clicked() { ClickHandler::twoButtonPress(ui); }

void Calculator::on_pushButton_3_clicked() { ClickHandler::threeButtonPress(ui); }

void Calculator::on_pushButton_4_clicked() { ClickHandler::fourButtonPress(ui); }

void Calculator::on_pushButton_5_clicked() { ClickHandler::fiveButtonPress(ui); }

void Calculator::on_pushButton_6_clicked() { ClickHandler::sixButtonPress(ui); }

void Calculator::on_pushButton_7_clicked() { ClickHandler::sevenButtonPress(ui); }

void Calculator::on_pushButton_8_clicked() { ClickHandler::eightButtonPress(ui); }

void Calculator::on_pushButton_9_clicked() { ClickHandler::nineButtonPress(ui); }

void Calculator::on_pushButton_add_clicked() { ClickHandler::addButtonPress(ui); }

void Calculator::on_pushButton_ans_clicked() { ClickHandler::ansButtonPress(ui); }

void Calculator::on_pushButton_clear_clicked() { ClickHandler::clearResultButtonPress(ui); }

void Calculator::on_pushButton_closeParen_clicked() { ClickHandler::closeParenButtonPress(ui); }

void Calculator::on_pushButton_div_clicked() { ClickHandler::divButtonPress(ui); }

void Calculator::on_pushButton_dot_clicked() { ClickHandler::dotButtonPress(ui); }

void Calculator::on_pushButton_equals_clicked() { ClickHandler::evaluateButtonPress(ui); }

void Calculator::on_pushButton_erase_clicked() { ClickHandler::eraseButtonPress(ui); }

void Calculator::on_pushButton_help_clicked() { ClickHandler::helpButtonPress(this); }

void Calculator::on_pushButton_hist_clicked() { ClickHandler::histButtonPress(this); }

void Calculator::on_pushButton_mult_clicked() { ClickHandler::multButtonPress(ui); }

void Calculator::on_pushButton_openParen_clicked() { ClickHandler::openParenButtonPress(ui); }

void Calculator::on_pushButton_power_clicked() { ClickHandler::powerButtonPress(ui); }

void Calculator::on_pushButton_sqrt_clicked() { ClickHandler::sqrtButtonPress(ui); }

void Calculator::on_pushButton_sub_clicked() { ClickHandler::subButtonPress(ui); }
