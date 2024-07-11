#ifndef MAINWINDOW2_H
#define MAINWINDOW2_H
#include <QMediaPlayer>
#include <QMainWindow>
#include "choosegame.h"
namespace Ui {
class MainWindow2;
}

class MainWindow2 : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow2(QWidget *parent = nullptr);
    ~MainWindow2();
    void SetGameBefore();
    ChooseGame *last;
    QMediaPlayer* player = new QMediaPlayer(this);

private slots:
    void slotUpdateScore1(int nScore);
    void slotUpdateLevel1(int nSpeed);

    void slotUpdateScore2(int nScore);
    void slotUpdateLevel2(int nSpeed);

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

protected:
    void keyPressEvent(QKeyEvent *event) override;

private:

    Ui::MainWindow2 *ui;
};

#endif // MAINWINDOW2_H
