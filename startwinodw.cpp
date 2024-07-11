#include "startwinodw.h"
#include "ui_startwinodw.h"
#include"choosegame.h"
#include"setting.h"
#include"history.h"
#include <QFileDialog>
#include <QDesktopServices>

startwinodw::startwinodw(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::startwinodw)
{
    ui->setupUi(this);
    setWindowTitle("欢迎来到俄罗斯方块");
}

startwinodw::~startwinodw()
{
    delete ui;
}

void startwinodw::on_StartButton_clicked()
{
    this->hide();
    ChooseGame *choose = new ChooseGame;
    choose->sw = this;
    choose->setAttribute(Qt::WA_DeleteOnClose);
    choose->show();
}


void startwinodw::on_HistoryButton_clicked()
{   
    history *historyWindow = new history;
    historyWindow->setAttribute(Qt::WA_DeleteOnClose);
    historyWindow->show();
}

void startwinodw::on_SetButton_clicked()
{
    setting *set = new setting;
    set->setAttribute(Qt::WA_DeleteOnClose);
    set->show();

}


void startwinodw::on_pushButton_clicked()
{
    QString mdFilePath = "D:\\C++\\qt1\\Tetris\\游戏说明.md";
    QDesktopServices::openUrl(QUrl::fromLocalFile(mdFilePath));
}

