#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QTimer>
#include <QTime>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

struct clubButton{
    QString clubName;
    int sizeX;
    int sizeY;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    //void set_default_cards();
   // void setIconOnButton(QPushButton *button, clubButton club);
    QVector<clubButton> randomGenerateButtonConfiguration(QVector<clubButton> clubs);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButtonRestart_clicked();

    void checkButtonClicked();
    void startGame();
    void gameOver();
    void updateTime();

    void setDefaultCards(QPushButton *button);
    void setIconOnButton(QPushButton *button, clubButton club);
    void setIconOnButtonWithRandomTeam();
    void findingPairs();
private:
    int pairs = 0;
    int counter = 0;
    int clickCounter = 1;
    QVector<int> pushedButtons;

    QTimer *timer=new QTimer();
    QTimer * t = new QTimer();
    QTime time;

    Ui::MainWindow *ui;
    MainWindow *nWin;
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
#endif // MAINWINDOW_H
