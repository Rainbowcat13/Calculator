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
#include <string>
#include <QKeyEvent>
#include <QIcon>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // initialized constants
    consts = {"pi", "e", ""};

    // Set main window design
    setFixedSize(1366, 768);
    setWindowTitle(QString("Calculator"));
    setWindowIcon(QIcon("X:\\Calculator\\images\\icon.png"));
    setStyleSheet("MainWindow{background-color: rgb(176, 224, 230)};");

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
    inputExpressionEdit->setStyleSheet("QLineEdit{"
                                       "background-color: rgb(192, 192, 192);"
                                       "color: black;"
                                       "border-style: inset;"
                                       "border-width: 4px;"
                                       "border-radius: 12px;"
                                       "border-color: black;"
                                       "min-width: 10em;"
                                       "padding: 6px;"
                                       "selection-background-color: rgb(0, 191, 255);"
                                       "selection-color: black;}"
                                       "QLineEdit:hover{"
                                       "background-color: rgb(255, 255, 240);"
                                       "color: black;"
                                       "border-style: inset;"
                                       "border-width: 4px;"
                                       "border-radius: 12px;"
                                       "border-color: black;"
                                       "min-width: 10em;"
                                       "padding: 6px;"
                                       "selection-background-color: rgb(0, 191, 255);"
                                       "selection-color: black;}");

    // Created field for inversed notation
    inversedNotationField = new QLineEdit;
    inversedNotationField->setFont(mainFont);
    inversedNotationField->setText(inversedNotation);
    inversedNotationField->setAlignment(Qt::AlignCenter);
    inversedNotationField->setStyleSheet("color: black");
    inversedNotationField->setReadOnly(1);
    inversedNotationField->setStyleSheet("QLineEdit{"
                                         "background-color: rgb(192, 192, 192);"
                                         "color: black;"
                                         "border-style: inset;"
                                         "border-width: 4px;"
                                         "border-radius: 12px;"
                                         "border-color: black;"
                                         "min-width: 10em;"
                                         "padding: 6px;"
                                         "selection-background-color: rgb(0, 191, 255);"
                                         "selection-color: black;}");

    // Created button for calculating and connected it with signal
    calcButton = new QPushButton;
    calcButton->setFont(mainFont);
    calcButton->setText("Calculate");
    //calcButton->setFixedSize(30, 60);
    calcButton->setStyleSheet("QPushButton{"
                              "background-color: rgb(248, 248, 255);"
                              "color: black;"
                              "border-style: inset;"
                              "border-width: 2px;"
                              "border-radius: 8px;"
                              "border-color: black;"
                              "min-width: 10em;"
                              "padding: 6px;}"
                              "QPushButton:pressed{"
                              "background-color: rgb(248, 248, 255);"
                              "color: black;"
                              "border-width: 4px;"
                              "border-radius: 12px;"
                              "border-color: black;"
                              "min-width: 10em;"
                              "padding: 6px;}");
    connect(calcButton, SIGNAL(clicked()), this, SLOT(processInput()));

    // Created window for errors
    errorWindow = new QLineEdit;
    errorWindow->setFont(mainFont);
    errorWindow->setText("Everything is OK");
    errorWindow->setStyleSheet("color: green");
    errorWindow->setAlignment(Qt::AlignCenter);
    errorWindow->setReadOnly(1);
    errorWindow->setStyleSheet("QLineEdit{"
                               "background-color: rgb(176, 224, 230);"
                               "color: rgb(34, 139, 34);"
                               "border-style: solid;"
                               "border-width: 4px;"
                               "border-radius: 12px;"
                               "border-color: red;"
                               "min-width: 10em;"
                               "padding: 6px;}");

    // Created field for answer
    answerField = new QLineEdit;
    answerField->setFont(mainFont);
    answerField->setText(answer);
    answerField->setAlignment(Qt::AlignCenter);
    answerField->setReadOnly(1);
    answerField->setStyleSheet("QLineEdit{"
                               "background-color: rgb(192, 192, 192);"
                               "color: black;"
                               "border-style: inset;"
                               "border-width: 4px;"
                               "border-radius: 12px;"
                               "border-color: black;"
                               "min-width: 10em;"
                               "padding: 6px;"
                               "selection-background-color: rgb(0, 191, 255);"
                               "selection-color: black;}");

    QLabel* errorLabel = new QLabel;
    errorLabel->setText("Errors in expression");
    errorLabel->setFont(mainFont);

    QLabel* expressionLabel = new QLabel;
    expressionLabel->setText("Enter your expression here");
    expressionLabel->setFont(mainFont);

    QLabel* inversedNotationLabel = new QLabel;
    inversedNotationLabel->setText("Inversed notation of expression");
    inversedNotationLabel->setFont(mainFont);

    QLabel* answerLabel = new QLabel;
    answerLabel->setText("Answer");
    answerLabel->setFont(mainFont);

    // Configured layout and added all widgets
    QGridLayout* mainLayout = new QGridLayout;
    mainLayout->addWidget(errorLabel, 0, 80, 5, 60);
    mainLayout->addWidget(inversedNotationLabel, 30, 75, 5, 60);
    mainLayout->addWidget(expressionLabel, 15, 78, 5, 60);
    mainLayout->addWidget(answerLabel, 45, 90, 5, 20);
    mainLayout->addWidget(errorWindow, 5, 0, 10, 200);
    mainLayout->addWidget(inputExpressionEdit, 20, 0, 10, 200);
    mainLayout->addWidget(inversedNotationField, 35, 0, 10, 200);
    mainLayout->addWidget(answerField, 50, 0, 10, 200);
    mainLayout->addWidget(calcButton, 60, 80, 10, 40);
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
        errorWindow->setStyleSheet("QLineEdit{"
                                   "background-color: rgb(176, 224, 230);"
                                   "color: red;"
                                   "border-style: solid;"
                                   "border-width: 4px;"
                                   "border-radius: 12px;"
                                   "border-color: red;"
                                   "min-width: 10em;"
                                   "padding: 6px;}");
        if (!variables.empty()) {
            varWindow->hide();
        }
        return;
    }
    errorWindow->setText("Everything is OK");
    errorWindow->setStyleSheet("QLineEdit{"
                               "background-color: rgb(176, 224, 230);"
                               "color: rgb(34, 139, 34);"
                               "border-style: solid;"
                               "border-width: 4px;"
                               "border-radius: 12px;"
                               "border-color: red;"
                               "min-width: 10em;"
                               "padding: 6px;}");

    auto aaa = std::to_string(static_cast<double>(preAnswer));
    answer = QString::fromStdString(aaa);
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
    std::set<QString> ans;
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
                ans.insert(curs);
        }
    }
    QVector<QString> aans;
    for (auto elem: ans) {
        aans.push_back(elem);
    }
    return aans;
}

void MainWindow::processInput() {
    // Created new window for entering variables
    varWindow = new QWidget;
    varWindow->setFixedSize(500, 500);
    varWindow->setWindowIcon(QIcon("X:\\Calculator\\images\\icon.png"));
    varWindow->setStyleSheet("background-color: rgb(176, 224, 230);");
    QGridLayout* varLayout = new QGridLayout;
    variables = getVariables();
    if (variables.empty()) {
        calculate();
        return;
    }
    int cnt = 0;
    varEdits.clear();
    for (auto s: variables) {
        QLabel* currentVariable = new QLabel;
        currentVariable->setText("Enter " + s + " :");
        currentVariable->setFont(mainFont);
        currentVariable->setAlignment(Qt::AlignLeft);


        QLineEdit* currentEdit = new QLineEdit;
        currentEdit->setFont(mainFont);
        currentEdit->setStyleSheet("QLineEdit{"
                                   "background-color: rgb(192, 192, 192);"
                                   "color: black;"
                                   "border-style: inset;"
                                   "border-width: 4px;"
                                   "border-radius: 12px;"
                                   "border-color: black;"
                                   "min-width: 10em;"
                                   "padding: 6px;"
                                   "selection-background-color: rgb(0, 191, 255);"
                                   "selection-color: black;}"
                                   "QLineEdit:hover{"
                                   "background-color: rgb(255, 255, 240);"
                                   "color: black;"
                                   "border-style: inset;"
                                   "border-width: 4px;"
                                   "border-radius: 12px;"
                                   "border-color: black;"
                                   "min-width: 10em;"
                                   "padding: 6px;"
                                   "selection-background-color: rgb(0, 191, 255);"
                                   "selection-color: black;}");

        varLayout->addWidget(currentVariable, cnt, 0, 1, 1);
        varLayout->addWidget(currentEdit, cnt++, 1, 1, 3);
        varEdits.push_back(currentEdit);
    }

    QPushButton* countButton = new QPushButton;
    countButton->setFont(mainFont);
    countButton->setText("Count!");
    countButton->setStyleSheet("QPushButton{"
                               "background-color: rgb(248, 248, 255);"
                               "color: black;"
                               "border-style: inset;"
                               "border-width: 2px;"
                               "border-radius: 8px;"
                               "border-color: black;"
                               "min-width: 10em;"
                               "padding: 6px;}"
                               "QPushButton:pressed{"
                               "background-color: rgb(248, 248, 255);"
                               "color: black;"
                               "border-width: 4px;"
                               "border-radius: 12px;"
                               "border-color: black;"
                               "min-width: 10em;"
                               "padding: 6px;}");
    varLayout->addWidget(countButton, cnt, 1, 1, 2);
    connect(countButton, SIGNAL(clicked()), this, SLOT(calculate()));

    varWindow->setLayout(varLayout);
    varWindow->show();
}
