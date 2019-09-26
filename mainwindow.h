#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);

public slots:
    void inputChanged(const QString &);
    void calculate();

private:
    QWidget* mCentralWidget;
    QFont mainFont;
    QLineEdit *inputExpressionEdit, *inversedNotationField, *answerField;
    QString inversedNotation, answer;
    QPushButton* calcButton;
    QWidget* varWindow;

    void enterVariables();
};

#endif // MAINWINDOW_H
