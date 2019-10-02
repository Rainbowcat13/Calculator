#include "mainwindow.h"
#include <QLineEdit>
#include <QGridLayout>
#include <QDebug>
#include <QLabel>
#include <QPushButton>
#include <QString>
#include <QVector>
#include "expression.h"
#include "Tokenizer.h"
#include "Number.h"
#include <stdexcept>
#include "Queue.h"
#include <QKeyEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // initialized constants
    consts = {"pi", "e", ""};

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
    connect(calcButton, SIGNAL(clicked()), this, SLOT(processInput()));

    // Created window for errors
    errorWindow = new QLineEdit;
    errorWindow->setFont(mainFont);
    errorWindow->setText("Everything is OK");
    errorWindow->setStyleSheet("color: green");
    errorWindow->setAlignment(Qt::AlignCenter);
    errorWindow->setReadOnly(1);

    // Created field for answer
    answerField = new QLineEdit;
    answerField->setFont(mainFont);
    answerField->setText(answer);
    answerField->setAlignment(Qt::AlignCenter);
    answerField->setReadOnly(1);

    // Configured layout and added all widgets
    QGridLayout* mainLayout = new QGridLayout;
    mainLayout->addWidget(errorWindow, 0, 0, 5, 20);
    mainLayout->addWidget(inputExpressionEdit, 5, 0, 10, 10);
    mainLayout->addWidget(inversedNotationField, 15, 0, 10, 10);
    mainLayout->addWidget(calcButton, 5, 10, 10, 10);
    mainLayout->addWidget(answerField, 15, 10, 10, 10);
    mCentralWidget->setLayout(mainLayout);
    setCentralWidget(mCentralWidget);
}

void MainWindow::calculate() {
    auto expressionString = inputExpressionEdit->text().toStdString();
    Number preAnswer;
    Tokenizer t = Tokenizer(expressionString);
    Expression mainExpression = Expression({});
    try {
        auto tt = t.getAllTokens();
        mainExpression = Expression(tt);
        if (!variables.empty()) {
            for (int i = 0; i < variables.size(); i++) {
                auto var = variables[i].toStdString();
                Number num = Number(Number::parseNumber(varEdits[i]->text().toStdString()));
                mainExpression.setVariable(var, num);
            }
            varWindow->hide();
        }
        preAnswer = mainExpression.evaluate();
    }
    catch (std::invalid_argument s) {
        errorWindow->setText(QString::fromStdString(s.what()));
        errorWindow->setStyleSheet("color: red");
        if (!variables.empty()) {
            varWindow->hide();
        }
        return;
    }
    errorWindow->setText("Everything is OK");
    errorWindow->setStyleSheet("color: green");
    answer = QString::number(static_cast<double>(preAnswer));
    answerField->setText(answer);

    auto postfix = mainExpression.getPostfix();
    QString in = "";
    while (!postfix.isEmpty()) {
        auto token = postfix.front();
        postfix.pop();
        in += QString::fromStdString(token) + " ";
    }
    inversedNotation = in;
    inversedNotationField->setText(inversedNotation);
}

void MainWindow::keyPressEvent(QKeyEvent *event){
    if(event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return) {
       processInput();
    }
}

QVector<QString> MainWindow::getVariables() {
    QVector<QString> ans;
    int it = 0;
    auto s = inputExpressionEdit->text();
    int n = s.size();
    while (it < n) {
        while (it < n && !s[it].isLetter()) it++;
        QString curs = "";
        while (it < n && s[it].isLetter()) {
            curs.push_back(s[it]);
            it++;
        }
        if (it < n && s[it] == "(") {
            continue;
        }
        else {
            if (consts.find(curs) == consts.end())
                ans.push_back(curs);
        }
    }
    return ans;
}

void MainWindow::processInput() {
    // Created new window for entering variables
    varWindow = new QWidget;
    varWindow->setFixedSize(500, 500);
    QGridLayout* varLayout = new QGridLayout;
    variables = getVariables();
    if (variables.empty()) {
        calculate();
        return;
    }
    int cnt = 0;
    for (auto s: variables) {
        QLabel* currentVariable = new QLabel;
        currentVariable->setText("Enter " + s + " :");
        currentVariable->setFont(mainFont);
        currentVariable->setAlignment(Qt::AlignLeft);


        QLineEdit* currentEdit = new QLineEdit;
        currentEdit->setFont(mainFont);

        varLayout->addWidget(currentVariable, cnt, 0, 1, 1);
        varLayout->addWidget(currentEdit, cnt++, 1, 1, 3);
        varEdits.push_back(currentEdit);
    }

    QPushButton* countButton = new QPushButton;
    countButton->setFont(mainFont);
    countButton->setText("Count!");
    countButton->setStyleSheet("color: green");
    varLayout->addWidget(countButton, cnt, 1, 1, 2);
    connect(countButton, SIGNAL(clicked()), this, SLOT(calculate()));

    varWindow->setLayout(varLayout);
    varWindow->show();
}
