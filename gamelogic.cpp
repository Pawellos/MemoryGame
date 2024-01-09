#include "gamelogic.h"
#include "mainwindow.h"

#include <QDebug>
#include <QtWidgets>
#include <QString>
#include <QProcess>
#include <algorithm>

GameLogic::GameLogic()
{

}


QVector<clubButton> GameLogic::randomGenerateButtonConfiguration(QVector<clubButton> clubs)
{

 QVector<clubButton> clubTeams;
 for(clubButton & x : clubs)
    clubTeams.push_back(x);

 auto rd = std::random_device {};
 auto rng = std::default_random_engine { rd() };
 std::shuffle(std::begin(clubTeams), std::end(clubTeams), rng);

 return clubTeams;
}
