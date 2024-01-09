#include "userinterface.h"

#include <QDebug>
#include <QtWidgets>
#include <QString>
#include <QProcess>
#include <algorithm>

UserInterface::UserInterface()
{

}

void UserInterface::findingPairs(QTimer *timer, QTimer *t){
    if(counter == 2){
        int previous = pushedButtons[0];
        int next = pushedButtons[1];
        qDebug() <<"prev =" << previous;
        qDebug() <<"next =" << next;
        QString butNamePrev = "Button" + QString::number(previous);
        qDebug() <<"butNamePrev =" << butNamePrev;
        QString butNameNext = "Button" + QString::number(next);
        qDebug() <<"butNameNext =" << butNameNext;

        if(teams[previous-1].clubName == teams[next-1].clubName){
             pairs++;
             emit PairFoundSignal();
        }

        else{
            emit resetCardsSignal(butNamePrev, butNameNext);
            emit notPairFoundSignal();
        }
        counter = 0;
        pushedButtons.clear();
        qDebug() << pairs;

        if(pairs == teams.size()/2){
            timer->stop();
            t->stop();
            emit endWinGameSignal(clickCounter);
        }
    }
}


void UserInterface::setDefaultCards(QPushButton *button){
      setIconOnButton(button, Champions);
      button->setEnabled(true);

}

void UserInterface::setIconOnButton(QPushButton *button, clubButton club){
    button->setIcon(QIcon(club.clubName));
    button->setIconSize(QSize(club.sizeX,club.sizeY));
}


void UserInterface::setIconOnButtonWithRandomTeam(QPushButton *button){
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



void UserInterface::setTeams(QVector<clubButton> teamsToSet)
{
    teams = teamsToSet;
}

QVector<clubButton> UserInterface::getClubs()
{
    return clubs;
}

int UserInterface::getClickCounter()
{
    return clickCounter;
}


void UserInterface::setDefaultValues()
{
    pairs = 0;
    counter = 0;
    clickCounter = 1;
    pushedButtons.clear();
}

