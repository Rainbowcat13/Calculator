#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <set>
#include <QKeyEvent>
#include <QTextEdit>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    QVector<QString> getVariables();
    void keyPressEvent(QKeyEvent* event);

public slots:
    void calculate();
    void processInput();


private:
    QWidget* mCentralWidget;
    QFont mainFont;
    QLineEdit *inputExpressionEdit, *inversedNotationField, *answerField, *errorWindow;
    QString inversedNotation, answer;
    QPushButton* calcButton;
    QWidget* varWindow;
    std::set<QString> consts;
    QVector<QString> variables;
    QVector<QLineEdit*> varEdits;

};

#endif // MAINWINDOW_H
