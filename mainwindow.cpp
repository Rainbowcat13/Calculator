#include "mainwindow.h"
#include <QLineEdit>
#include <QGridLayout>
#include <QDebug>
#include <QLabel>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // Set main window design
    setFixedSize(1366, 768);
    setWindowTitle(QString("Calculator"));

    // Created main and default widgets
    mCentralWidget = new QWidget;
    mainFont = QFont("Arial", 12, QFont::Bold);
    QString defaultExpression = "2*2";
    inversedNotation = "2 2 *";
    answer = "4";

    // Created and configured window for user expression input and connected it with signal
    inputExpressionEdit = new QLineEdit(this);
    inputExpressionEdit->setFont(mainFont);
    inputExpressionEdit->setText(defaultExpression);
    inputExpressionEdit->setAlignment(Qt::AlignCenter);
    inputExpressionEdit->setStyleSheet("color: green");
    connect(inputExpressionEdit, SIGNAL(textChanged(const QString &)),
            this, SLOT(inputChanged(const QString &)));

    // Created field for inversed notation
    inversedNotationField = new QLineEdit;
    inversedNotationField->setFont(mainFont);
    inversedNotationField->setText(inversedNotation);
    inversedNotationField->setAlignment(Qt::AlignCenter);
    inversedNotationField->setStyleSheet("color: black");
    inversedNotationField->setReadOnly(1);

    // Created button for calculating and connected it with signal
    calcButton = new QPushButton;
    calcButton->setFont(mainFont);
    calcButton->setText("Calculate");
    calcButton->setStyleSheet("background-color: blue;color: white");
    connect(calcButton, SIGNAL(clicked()), this, SLOT(calculate()));

    // Created field for answer
    answerField = new QLineEdit;
    answerField->setFont(mainFont);
    answerField->setText(answer);
    answerField->setAlignment(Qt::AlignCenter);
    answerField->setReadOnly(1);

    // Configured layout and added all widgets
    QGridLayout* mainLayout = new QGridLayout;
    mainLayout->addWidget(inputExpressionEdit, 0, 0, 10, 10);
    mainLayout->addWidget(inversedNotationField, 10, 0, 10, 10);
    mainLayout->addWidget(calcButton, 0, 10, 10, 10);
    mainLayout->addWidget(answerField, 10, 10, 10, 10);
    mCentralWidget->setLayout(mainLayout);
    setCentralWidget(mCentralWidget);
}


void MainWindow::inputChanged(const QString &s) {
    qDebug() << "PIZDA";
}

void MainWindow::calculate() {
    enterVariables();
    qDebug() << "aaaa";
}



void MainWindow::enterVariables() {
    // Created new window for entering variables
    varWindow = new QWidget;


    varWindow->show();
}
