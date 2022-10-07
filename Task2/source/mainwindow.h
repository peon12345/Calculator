#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QButtonGroup>
#include <queue>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

private:
  QButtonGroup m_numbers;
  QButtonGroup m_clearButtons;
  QButtonGroup m_operatorAddButtons;

  double m_prevOperand;

  Ui::MainWindow *ui;
  enum class CleaningType {
    LAST_CHARACTER ,
    CURRENT_LINE,
    ALL,
  };

  enum class ExpressionAction{
    NONE,
    CLEAR_VALUE,
    CLEAR_VLAUE_AND_OPERATOR
  } m_expressionAction = ExpressionAction::NONE;

  static constexpr int DECIMAL_ID_BUTTON = 10;

  enum class Operator {
    DIVISION,
    MULT,
    PLUS,
    SUB,
    PROCENT,
    POW,
    ONE_DIVISON,
    SIGN,
    SQRT,
    NONE
  } m_operator;

private slots:
  void addOperator(Operator operatorId);
  void clear(CleaningType c);
  void on_pushButton_eq_clicked();
};
#endif // MAINWINDOW_H
