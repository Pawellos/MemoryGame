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
    ui->setupUi(this);
    teams = randomGenerateButtonConfiguration(clubs);

    QPushButton *cardButtons[10];
    // Cycle through locating the buttons
    for(int i = 1; i <= 10; ++i){
        QString butName = "Button" + QString::number(i);

        // Get the buttons by name and add to array
        cardButtons[i] = MainWindow::findChild<QPushButton *>(butName);
        setDefaultCards(cardButtons[i]);
        // When the button is released call num_pressed()
        connect(cardButtons[i], SIGNAL(clicked()), this, SLOT(checkButtonClicked()));
        connect(cardButtons[i], SIGNAL(clicked()), this, SLOT(setIconOnButtonWithRandomTeam()));
        connect(cardButtons[i], SIGNAL(clicked()), this, SLOT(findingPairs()));
      }
    t->start(1000);
    connect(t, &QTimer::timeout, this, &MainWindow::updateTime);
    //timer->singleShot(10000, this, &MainWindow::gameOver);
    connect(timer, &QTimer::timeout, this, &MainWindow::gameOver);
    timer->setSingleShot(true);
    timer->start(62000); // 10000 ms to 10 sekund, można zmienić na 60000 dla 60 sekund
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::startGame()
{
    //ui->setupUi(this);
    pairs = 0;
    counter = 0;
    clickCounter = 1;
    pushedButtons.clear();

    teams = randomGenerateButtonConfiguration(clubs);

    QPushButton *cardButtons[10];
    // Cycle through locating the buttons
    for(int i = 1; i <= 10; ++i){
        QString butName = "Button" + QString::number(i);

     // Get the buttons by name and add to array
        cardButtons[i] = MainWindow::findChild<QPushButton *>(butName);
        setDefaultCards(cardButtons[i]);
        // When the button is released call num_pressed()
        connect(cardButtons[i], SIGNAL(clicked()), this, SLOT(checkButtonClicked()));
        connect(cardButtons[i], SIGNAL(clicked()), this, SLOT(setIconOnButtonWithRandomTeam()));
        connect(cardButtons[i], SIGNAL(clicked()), this, SLOT(findingPairs()));
        }
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



void MainWindow::on_pushButton_clicked()
{
    qDebug() << "Pushed the button";
    ui->textBrowser->setText("Hello world");
    QMessageBox::information(this, "Tittle","Heey world");
}


void MainWindow::on_pushButtonRestart_clicked()
{
    qDebug() << "clear all";
    ui->textBrowser->setText("");
    pairs = 0;
    counter = 0;
    clickCounter = 1;
    pushedButtons.clear();
    teams = randomGenerateButtonConfiguration(clubs);
    QPushButton *cardButtonToClear;
    // Cycle through locating the buttons
    for(int i = 1; i <= 10; ++i){
        QString butName = "Button" + QString::number(i);
        cardButtonToClear = MainWindow::findChild<QPushButton *>(butName);
        setDefaultCards(cardButtonToClear);
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


void MainWindow::setDefaultCards(QPushButton *button){
      setIconOnButton(button, Champions);
      //button->setCheckable(true);
      button->setEnabled(true);

}

void MainWindow::setIconOnButton(QPushButton *button, clubButton club){
    button->setIcon(QIcon(club.clubName));
    button->setIconSize(QSize(club.sizeX,club.sizeY));
}

QVector<clubButton> MainWindow::randomGenerateButtonConfiguration(QVector<clubButton> clubs)
{

 QVector<clubButton> clubTeams;
 for(clubButton & x : clubs)
    clubTeams.push_back(x);

 auto rd = std::random_device {};
 auto rng = std::default_random_engine { rd() };
 std::shuffle(std::begin(clubTeams), std::end(clubTeams), rng);

 return clubTeams;
}

void MainWindow::checkButtonClicked()
{
    QPushButton* buttonSender = (QPushButton *)sender(); // retrieve the button you have clicked
    QString buttonNameText = buttonSender->objectName(); // retrive the text from the button clicked
    qDebug() << buttonNameText;
    ui->textBrowser->setText("clicked: " + QString::number(clickCounter));
    buttonSender->setEnabled(false);
}

void MainWindow::setIconOnButtonWithRandomTeam(){
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    QString buttonNameText = button->objectName();
    QString onlyDigit = "";
    for(const auto& c : buttonNameText){
        if(c.isNumber()){
         onlyDigit += c;
        }
    }
    int buttonNumber = onlyDigit.toInt();
    button->setIcon(QIcon(teams[buttonNumber-1].clubName));
    button->setIconSize(QSize(teams[buttonNumber-1].sizeX,teams[buttonNumber-1].sizeY));
    pushedButtons.push_back(buttonNumber);
    counter++;
    clickCounter++;
}

void MainWindow::findingPairs(){
    if(counter == 2){
        int previous = pushedButtons[0];
        int next = pushedButtons[1];
        qDebug() <<"prev =" << previous;
        qDebug() <<"next =" << next;
        QString butNamePrev = "Button" + QString::number(previous);
        qDebug() <<"butNamePrev =" << butNamePrev;
        QString butNameNext = "Button" + QString::number(next);
        qDebug() <<"butNameNext =" << butNameNext;
        QPushButton * prevButton = MainWindow::findChild<QPushButton *>(butNamePrev);
        QPushButton * nextButton = MainWindow::findChild<QPushButton *>(butNameNext);

        if(teams[previous-1].clubName == teams[next-1].clubName){
         QMessageBox::information(this, "Congrats","Woow great, You find pair !");
         pairs++;
        }
        else{
            setIconOnButton(prevButton, teams[previous-1]);
            setIconOnButton(nextButton, teams[next-1]);
            prevButton->setEnabled(true);
            nextButton->setEnabled(true);
            QMessageBox::information(this, "Congrats","Sorry, not pair. Try again!");
            setIconOnButton(prevButton, Champions);
            setIconOnButton(nextButton, Champions);
        }
        counter = 0;
        pushedButtons.clear();
        qDebug() << pairs;

        if(pairs == teams.size()/2){
            timer->stop();
            t->stop();
            QMessageBox::information(this, "Congrats","Congrats !!! You win. You needed to win " + QString::number(clickCounter-1) + " clicks");
        }
    }
}


