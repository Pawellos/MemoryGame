#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>

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
    void set_default_cards();
    void setIconOnButton(QPushButton *button, clubButton club);
    QVector<clubButton> randomGenerateButtonConfiguration(QVector<clubButton> clubs);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButtonClear_clicked();

    void on_pushButton_2_clicked(bool clicked);

    void on_pushButton_3_clicked(bool clicked);

    void on_pushButton_4_clicked(bool clicked);

    void on_pushButton_5_clicked(bool clicked);

    void on_pushButton_7_clicked(bool clicked);

    void on_pushButton_8_clicked(bool clicked);

    void on_pushButton_9_clicked(bool clicked);

    void on_pushButton_10_clicked(bool clicked);

    void on_pushButton_6_clicked(bool checked);

    void on_pushButton_11_clicked(bool checked);

protected:
    Ui::MainWindow *ui;
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
