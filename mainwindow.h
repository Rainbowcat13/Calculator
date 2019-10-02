#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <set>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    QVector<QString> getVariables();

public slots:
    void calculate();
    void processInput();

private:
    QWidget* mCentralWidget;
    QFont mainFont;
    QLineEdit *inputExpressionEdit, *inversedNotationField, *answerField;
    QString inversedNotation, answer;
    QPushButton* calcButton;
    QWidget* varWindow;
    std::set<QString> consts;

    void enterVariables();
};

#endif // MAINWINDOW_H
