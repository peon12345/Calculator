#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <math.h>

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  m_numbers.addButton(ui->pushButton_0,0);
  m_numbers.addButton(ui->pushButton_1,1);
  m_numbers.addButton(ui->pushButton_2,2);
  m_numbers.addButton(ui->pushButton_3,3);
  m_numbers.addButton(ui->pushButton_4,4);
  m_numbers.addButton(ui->pushButton_5,5);
  m_numbers.addButton(ui->pushButton_6,6);
  m_numbers.addButton(ui->pushButton_7,7);
  m_numbers.addButton(ui->pushButton_8,8);
  m_numbers.addButton(ui->pushButton_9,9);
  m_numbers.addButton(ui->pushButton_decimal,DECIMAL_ID_BUTTON);

  m_clearButtons.addButton(ui->pushButton_delete,static_cast<int>(CleaningType::LAST_CHARACTER));
  m_clearButtons.addButton(ui->pushButton_clear_current,static_cast<int>(CleaningType::CURRENT_LINE));
  m_clearButtons.addButton(ui->pushButton_clear,static_cast<int>(CleaningType::ALL));

  m_operatorAddButtons.addButton(ui->pushButton_division,static_cast<int>(Operator::DIVISION));
  m_operatorAddButtons.addButton(ui->pushButton_mult,static_cast<int>(Operator::MULT));
  m_operatorAddButtons.addButton(ui->pushButton_plus,static_cast<int>(Operator::PLUS));
  m_operatorAddButtons.addButton(ui->pushButton_sub,static_cast<int>(Operator::SUB));
  m_operatorAddButtons.addButton(ui->pushButton_procent,static_cast<int>(Operator::PROCENT));

  m_operatorAddButtons.addButton(ui->pushButton_pow,static_cast<int>(Operator::POW));
  m_operatorAddButtons.addButton(ui->pushButton_root,static_cast<int>(Operator::ONE_DIVISON));
  m_operatorAddButtons.addButton(ui->pushButton_sign,static_cast<int>(Operator::SIGN));
  m_operatorAddButtons.addButton(ui->pushButton_sqrt,static_cast<int>(Operator::SQRT));

  QObject::connect(&m_numbers , &QButtonGroup::idClicked ,this, [&lineEdit = ui->lineEdit , &expressionAction = m_expressionAction , &mOperator = m_operator ]  (int id)  {

      if(expressionAction == ExpressionAction::CLEAR_VALUE){
          lineEdit->setText("0");
        }else if(expressionAction == ExpressionAction::CLEAR_VLAUE_AND_OPERATOR){
          lineEdit->setText("0");
          mOperator = Operator::NONE;
        }

      expressionAction =  ExpressionAction::NONE;

      if(id == DECIMAL_ID_BUTTON){

          if(! lineEdit->text().contains(".")){
              lineEdit->insert(".");
            }
        }else{
          if( (lineEdit->text() == "0")){
              lineEdit->clear();
            }
          lineEdit->insert(QString::number(id));
        }



    } );

  QObject::connect(&m_clearButtons , &QButtonGroup::idClicked , this , [this] (int id) {
      clear(static_cast<CleaningType> (id));
    });

  QObject::connect(&m_operatorAddButtons,&QButtonGroup::idClicked,this,[this] (int id) {
      addOperator(static_cast<Operator> (id));
    });


}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::addOperator(Operator operatorId)
{
  if(Operator::SIGN != operatorId){
      m_prevOperand = ui->lineEdit->text().toDouble();
      m_expressionAction = ExpressionAction::CLEAR_VALUE;
      m_operator = operatorId;

      if(operatorId == Operator::POW ||
         operatorId == Operator::ONE_DIVISON ||
         operatorId == Operator::SQRT){

          on_pushButton_eq_clicked();
        }
    }else{
      QString temp = ui->lineEdit->text();
      temp.push_front("-");
      ui->lineEdit->setText(temp);
    }

}

void MainWindow::clear(CleaningType c)
{
  switch(c){

    case CleaningType::LAST_CHARACTER:{
        QString temp = ui->lineEdit->text();
        temp.chop(1);

        if(temp.isEmpty() ) {
            temp = "0";
          }
        ui->lineEdit->setText(temp);
        break;
      }


    case CleaningType::CURRENT_LINE:{
        ui->lineEdit->setText("0");
        break;
      }

    case CleaningType::ALL:{
        ui->lineEdit->setText("0");
        m_prevOperand = 0;
        break;
      }
    }
}


void MainWindow::on_pushButton_eq_clicked()
{
  switch (m_operator) {
    case Operator::DIVISION:{
        ui->lineEdit->setText(QString::number(m_prevOperand / ui->lineEdit->text().toDouble()));
        break;
      }
    case Operator::MULT:{
        ui->lineEdit->setText(QString::number(m_prevOperand * ui->lineEdit->text().toDouble()));
        break;
      }
    case Operator::PLUS:{
        ui->lineEdit->setText(QString::number(m_prevOperand + ui->lineEdit->text().toDouble()));
        break;
      }
    case Operator::SUB:{
        ui->lineEdit->setText(QString::number(m_prevOperand - ui->lineEdit->text().toDouble()));
        break;
      }
    case Operator::PROCENT:{
        ui->lineEdit->setText(QString::number( (m_prevOperand/100) * ui->lineEdit->text().toDouble() ));
        break;
      }
    case Operator::POW:{
        ui->lineEdit->setText(QString::number(std::pow(m_prevOperand,2)));
        break;
      }
    case Operator::ONE_DIVISON:{
        ui->lineEdit->setText(QString::number(1/m_prevOperand));
        break;
      }
    case Operator::SQRT:{
        ui->lineEdit->setText(QString::number(std::sqrt(m_prevOperand)));
        break;
      }
    default:
      return void();
    }
  m_expressionAction = ExpressionAction::CLEAR_VLAUE_AND_OPERATOR;
}





























