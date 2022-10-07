#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
{
  ui->setupUi(this);
}

MainWindow::~MainWindow()
{
  delete ui;
}


void MainWindow::on_pushButton_plus_clicked()
{
   double first_number = ui->first_number_lineEdit->text().toDouble();
   double second_number = ui->second_number_lineEdit->text().toDouble();
   double result = first_number + second_number;
   changeResultLabel(result);
}


void MainWindow::on_pushButton_substraction_clicked()
{
  double first_number = ui->first_number_lineEdit->text().toDouble();
  double second_number = ui->second_number_lineEdit->text().toDouble();
  double result = first_number - second_number;
  changeResultLabel(result);
}


void MainWindow::on_pushButton_mult_clicked()
{
  double first_number = ui->first_number_lineEdit->text().toDouble();
  double second_number = ui->second_number_lineEdit->text().toDouble();
  double result = first_number * second_number;
  changeResultLabel(result);
}


void MainWindow::on_pushButton_division_clicked()
{
  double first_number = ui->first_number_lineEdit->text().toDouble();
  double second_number = ui->second_number_lineEdit->text().toDouble();
  double result = first_number / second_number;
  changeResultLabel(result);
}

void MainWindow::changeResultLabel(int newResult)
{
 static const QString textResult = "Результат:";

 ui->label_3->setText(textResult + QString::number(newResult));
}

