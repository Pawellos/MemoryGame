#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QtWidgets>
#include <QString>
#include <algorithm>

int counter = 0;
QVector<int> pushedButtons;

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
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    qDebug() << "Pushed the button";
    ui->textBrowser->setText("Hello world");
    QMessageBox::information(this, "Tittle","Heey world");
}


void MainWindow::on_pushButtonClear_clicked()
{
    qDebug() << "clear all";
    ui->textBrowser->setText("");
}


void MainWindow::setDefaultCards(QPushButton *button){
      setIconOnButton(button, Champions);
      button->setCheckable(true);
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
    ui->textBrowser->setText(buttonNameText);
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
    //std::for_each(buttonNameText.begin(), buttonNameText.end(), [&onlyDigit](auto x){ onlyDigit.push_back(x.isNumber());});
   // ui->textBrowser->setText(onlyDigit);
    button->setIcon(QIcon(teams[buttonNumber-1].clubName));
    button->setIconSize(QSize(teams[buttonNumber-1].sizeX,teams[buttonNumber-1].sizeY));
    pushedButtons.push_back(buttonNumber);
    counter++;
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
        }
        else{
            setIconOnButton(prevButton, teams[previous-1]);
            setIconOnButton(nextButton, teams[next-1]);
            QMessageBox::information(this, "Congrats","Sorry, not pair. Try again!");
            prevButton->setEnabled(true);
            nextButton->setEnabled(true);
            setIconOnButton(prevButton, Champions);
            setIconOnButton(nextButton, Champions);
        }
        counter = 0;
        pushedButtons.clear();
    //    if(counter == 0){
    //    setDefaultCards(prevButton);
    //    setDefaultCards(nextButton);}
    }
}


