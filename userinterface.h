#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include <QMainWindow>
#include <QPushButton>

struct clubButton{
    QString clubName;
    int sizeX;
    int sizeY;
};

class UserInterface : public QObject
{
    Q_OBJECT

signals:
    void resetCardsSignal(const QString& butNamePrev, const QString& butNameNext);
    void updateButtonSignal(const QString& buttonName, const QString& iconName, int sizeX, int sizeY);
    void notPairFoundSignal();
    void PairFoundSignal();
    void endWinGameSignal(int clicks);



public:
    UserInterface();
    void findingPairs(QTimer *timer, QTimer *t);
    void setDefaultCards(QPushButton *button);
    void setIconOnButton(QPushButton *button, clubButton club);
    void setIconOnButtonWithRandomTeam(QPushButton *button);
    void setTeams(QVector<clubButton> teamsToSet);
    void setDefaultValues();
    QVector<clubButton> getClubs();
    int getClickCounter();
    bool isCheckingPairs = false;

private:
    int pairs = 0;
    int counter = 0;
    int clickCounter = 1;
    QVector<int> pushedButtons;

    QString championsBasic = "/Users/pawellos/memoryGame/pics/CL1.jpeg";
    QString inter = "/Users/pawellos/memoryGame/pics/inter.png";
    QString chelsea = "/Users/pawellos/memoryGame/pics/chelsea.png";
    QString real = "/Users/pawellos/memoryGame/pics/real.png";
    QString city = "/Users/pawellos/memoryGame/pics/city.png";
    QString milan = "/Users/pawellos/memoryGame/pics/milan2.png";
    clubButton Champions{championsBasic, 165, 95};
    clubButton Inter{inter, 90, 90};
    clubButton Chelsea{chelsea, 125, 130};
    clubButton Real{real, 90, 90};
    clubButton City{city, 90, 90};
    clubButton Milan{milan, 90, 90};

    QVector<clubButton> teams;
    QVector<clubButton> clubs {Inter, Chelsea, Real, City, Milan, Inter, Chelsea, Real, City, Milan};
};

#endif // USERINTERFACE_H
