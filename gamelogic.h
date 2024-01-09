#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include "userinterface.h"

#include <QPushButton>
#include <QTimer>
#include <QTime>

class GameLogic
{
public:
    GameLogic();
    QVector<clubButton> randomGenerateButtonConfiguration(QVector<clubButton> clubs);


private:

};

#endif // GAMELOGIC_H
