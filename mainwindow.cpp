#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QtWidgets>
#include <QString>
#include <QProcess>
#include <algorithm>

static unsigned int countTime = 60;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    connect(userInterface, &UserInterface::resetCardsSignal, this, &MainWindow::resetCardsSlot);
    connect(userInterface, &UserInterface::notPairFoundSignal, this, &MainWindow::notPairFoundSlot);
    connect(userInterface, &UserInterface::PairFoundSignal, this, &MainWindow::PairFoundSlot);
    connect(userInterface, &UserInterface::endWinGameSignal, this, &MainWindow::endWinGameSlot);
    connect(timer, &QTimer::timeout, this, &MainWindow::gameOver);
    connect(t, &QTimer::timeout, this, &MainWindow::updateTime);

    ui->setupUi(this);
    startGame();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::startGame()
{
    userInterface->setTeams(game->randomGenerateButtonConfiguration(userInterface->getClubs()));
    // Cycle through locating the buttons
    for(int i = 1; i <= 10; ++i){
        QString butName = "Button" + QString::number(i);

        // Get the buttons by name and add to array
        QPushButton *cardButton = MainWindow::findChild<QPushButton *>(butName);
        cardButtons.push_back(cardButton);
        userInterface->setDefaultCards(cardButton);
        // When the button is released call num_pressed()
        connect(cardButton, SIGNAL(clicked()), this, SLOT(checkButtonClicked()));
        connect(cardButton, &QPushButton::clicked, [=]() {
            userInterface->setIconOnButtonWithRandomTeam(cardButton); });
      }
    t->start(1000);

    timer->setSingleShot(true);
    timer->start(62000); // 10000 ms to 10 sekund, można zmienić na 60000 dla 60 sekund
}

void MainWindow::checkButtonClicked()
{
    QPushButton* buttonSender = (QPushButton *)sender(); // retrieve the button you have clicked
    QString buttonNameText = buttonSender->objectName(); // retrive the text from the button clicked
    qDebug() << buttonNameText;
    ui->textBrowser->setText("clicked: " + QString::number(userInterface->getClickCounter()));
    buttonSender->setEnabled(false);

    if (userInterface->isCheckingPairs) {
        return;
    }

    userInterface->isCheckingPairs = true;

        QTimer::singleShot(800, [this]() {
            userInterface->findingPairs(timer, t);
            userInterface->isCheckingPairs = false;
        });
}

void MainWindow::gameOver()
{
    QPushButton *cardButtonToClear;
    // Cycle through locating the buttons
    t->stop();
    for(int i = 1; i <= 10; ++i){
        QString butName = "Button" + QString::number(i);
        cardButtonToClear = MainWindow::findChild<QPushButton *>(butName);
        cardButtonToClear->setEnabled(false);
    }
    ui->textBrowser->setText("Timeout !");
    QMessageBox::information(this, "Tittle","Game over");
}

void MainWindow::updateTime()
{
    ui->textBrowserTimer->setText("Time left:  " + QString::number(countTime--));
}

void MainWindow::on_pushButtonRestart_clicked()
{
    qDebug() << "clear all";
    ui->textBrowser->setText("");
    userInterface->setDefaultValues();
    userInterface->setTeams(game->randomGenerateButtonConfiguration(userInterface->getClubs()));
    // Cycle through locating the buttons
    for(int i = 1; i <= 10; ++i){
        QString butName = "Button" + QString::number(i);
        QPushButton *cardButton = MainWindow::findChild<QPushButton *>(butName);
        cardButtons.push_back(cardButton);

        userInterface->setDefaultCards(cardButton);
    }
    if (timer->isActive()) {
        timer->stop();
        delete timer;
        timer = nullptr;
    }
    countTime = 60;
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::gameOver);
    timer->setSingleShot(true);
    timer->start(62000);
    t->start();
}

void MainWindow::resetCardsSlot(const QString& butNamePrev, const QString& butNameNext) {
    QPushButton *prevButton = this->findChild<QPushButton *>(butNamePrev);
    QPushButton *nextButton = this->findChild<QPushButton *>(butNameNext);

   // QTimer::singleShot(100, [this, prevButton, nextButton]() { // 1000 ms opóźnienia

    userInterface->setIconOnButton(prevButton, {"/Users/pawellos/memoryGame/pics/CL1.jpeg", 165, 95});
    userInterface->setIconOnButton(nextButton, {"/Users/pawellos/memoryGame/pics/CL1.jpeg", 165, 95});

    prevButton->setEnabled(true);
    nextButton->setEnabled(true);
   //  });
}

void MainWindow::notPairFoundSlot(){
    QMessageBox::information(this, "Congrats","Sorry, not a pair. Try again!");
}

void MainWindow::PairFoundSlot(){
    QMessageBox::information(this, "Congrats","Woow great, You find pair !");
}

void MainWindow::endWinGameSlot(int clicks){
      QMessageBox::information(this, "Congrats","Congrats !!! You win. You needed to win " + QString::number(clicks-1) + " clicks");

}

