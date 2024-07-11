#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QKeyEvent>
#include <QMainWindow>
#include <QMediaPlayer>
#include<QPushButton>
#include<QMediaPlaylist>
#include "choosegame.h"
#include "background.h"
namespace Ui {
	class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();
    //GameArea* gameArea;
    void setGameBefore();
    QMediaPlayer* player = new QMediaPlayer(this);
    backGround *bg;
    ChooseGame *last;

protected:
    void keyPressEvent(QKeyEvent *event) override;

private slots:
	void slotUpdateScore(int nScore);
	void slotUpdateLevel(int nSpeed);
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();


    void on_pushButton_4_clicked();

    //void on_pushButton_5_clicked();


    void on_playButton__clicked();

    void on_pushButton_5_clicked();

    void on_pauseButton__clicked();

private:
    Ui::MainWindow *ui;

};

#endif
