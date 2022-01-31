#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QtWidgets>
#include <QString>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    set_default_cards();
    teams = randomGenerateButtonConfiguration(clubs);

    //   this->centralWidget()->setStyleSheet("background-image:url(\"/Users/pawellos/memoryGame/pics/UEFA-Champions-League.jpeg\"); background-position: center;" );
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


void MainWindow::on_pushButton_2_clicked(bool clicked)
{
    if(clicked){
         setIconOnButton(ui->pushButton_2, teams[0]);

    }
    else{
        setIconOnButton(ui->pushButton_2, Champions);
        //  ui->pushButton_2->setEnabled(false);
    }
}

void MainWindow::on_pushButton_3_clicked(bool clicked)
{
    if(clicked){
        setIconOnButton(ui->pushButton_3, teams[1]);
    }
    else{
        setIconOnButton(ui->pushButton_3, Champions);
    }
}

void MainWindow::on_pushButton_4_clicked(bool clicked)
{
    if(clicked){
        setIconOnButton(ui->pushButton_4, teams[2]);
    }
    else{
        setIconOnButton(ui->pushButton_4, Champions);
    }
}

void MainWindow::on_pushButton_5_clicked(bool clicked)
{
    if(clicked){
        setIconOnButton(ui->pushButton_5, teams[3]);
    }
    else{
        setIconOnButton(ui->pushButton_5, Champions);
    }
}

void MainWindow::on_pushButton_6_clicked(bool clicked)
{
    if(clicked){
        setIconOnButton(ui->pushButton_6, teams[4]);
    }
    else{
        setIconOnButton(ui->pushButton_6, Champions);
    }
}

void MainWindow::on_pushButton_7_clicked(bool clicked)
{
    if(clicked){
        setIconOnButton(ui->pushButton_7, teams[5]);
    }
    else{
        setIconOnButton(ui->pushButton_7, Champions);
    }
}


void MainWindow::on_pushButton_8_clicked(bool clicked)
{
    if(clicked){
        setIconOnButton(ui->pushButton_8, teams[6]);
    }
    else{
        setIconOnButton(ui->pushButton_8, Champions);
    }
}


void MainWindow::on_pushButton_9_clicked(bool clicked)
{
    if(clicked){
        setIconOnButton(ui->pushButton_9, teams[7]);
    }
    else{
        setIconOnButton(ui->pushButton_9, Champions);
    }
}


void MainWindow::on_pushButton_10_clicked(bool clicked)
{
    if(clicked){
        setIconOnButton(ui->pushButton_10, teams[8]);
    }
    else{
        setIconOnButton(ui->pushButton_10, Champions);
    }
}

void MainWindow::on_pushButton_11_clicked(bool clicked)
{
    if(clicked){
        setIconOnButton(ui->pushButton_11, teams[9]);
    }
    else{
        setIconOnButton(ui->pushButton_11, Champions);
    }
}

void MainWindow::set_default_cards(){
     //ui->pushButton_2->setIcon(QIcon("/Users/pawellos/memoryGame/pics/CL1.jpeg"));
    // ui->pushButton_2->setIconSize(QSize(165,95));
     ui->pushButton_2->setCheckable(true);
     setIconOnButton(ui->pushButton_2, Champions);
     ui->pushButton_3->setCheckable(true);
     setIconOnButton(ui->pushButton_3, Champions);
     ui->pushButton_4->setCheckable(true);
     setIconOnButton(ui->pushButton_4, Champions);
     ui->pushButton_5->setCheckable(true);
     setIconOnButton(ui->pushButton_5, Champions);
     ui->pushButton_6->setCheckable(true);
     setIconOnButton(ui->pushButton_6, Champions);
     ui->pushButton_7->setCheckable(true);
     setIconOnButton(ui->pushButton_7, Champions);
     ui->pushButton_8->setCheckable(true);
     setIconOnButton(ui->pushButton_8, Champions);
     ui->pushButton_9->setCheckable(true);
     setIconOnButton(ui->pushButton_9, Champions);
     ui->pushButton_10->setCheckable(true);
     setIconOnButton(ui->pushButton_10, Champions);
     ui->pushButton_11->setCheckable(true);
     setIconOnButton(ui->pushButton_11, Champions);

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







