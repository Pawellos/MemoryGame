#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QTimer>
#include <QTime>

#include "gamelogic.h"
#include "userinterface.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE



class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButtonRestart_clicked();
    void resetCardsSlot(const QString& butNamePrev, const QString& butNameNext);
    void notPairFoundSlot();
    void PairFoundSlot();
    void endWinGameSlot(int clicks);


    void startGame();
    void checkButtonClicked();
    void gameOver();
    void updateTime();



private:


    QVector<QPushButton*> cardButtons;

    GameLogic *game = new GameLogic();
    UserInterface *userInterface = new UserInterface();

    QTimer *timer=new QTimer();
    QTimer * t = new QTimer();
    QTime time;


    Ui::MainWindow *ui;

};
#endif // MAINWINDOW_H
