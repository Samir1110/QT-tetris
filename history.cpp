#include "history.h"
#include "ui_history.h"
#include"ranking.h"
#include"sethistory.h"
#include"userhistory.h"
#include <QUrl>
#include <QDesktopServices>
#include<QInputDialog>
#include<QFile>
#include<QTextStream>
#include<QDebug>
#include<QMessageBox>
#include<QVBoxLayout>
history::history(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::history)
{
    ui->setupUi(this);
    setWindowTitle("游戏记录");
}

history::~history()
{
    delete ui;
}

void history::on_pushButton_clicked()
{
    ranking *rankingWindow = new ranking;
    rankingWindow->setAttribute(Qt::WA_DeleteOnClose);
    rankingWindow->loadRank();
    rankingWindow->show();
}


void history::on_pushButton_2_clicked()
{
    userHistory *uh = new userHistory;
    uh->setAttribute(Qt::WA_DeleteOnClose);
    uh->show();

}


void history::on_pushButton_3_clicked()
{
    bool ok;
    QString text = QInputDialog::getText(this, tr("存档操作"),
                                         tr("请输入存档号:"), QLineEdit::Normal,
                                         "", &ok);
    if (ok && !text.isEmpty()) {
        // 用户点击了“确定”按钮并且输入非空文本时执行此处代码
        QString fileName = text;
        fileName.append(".txt");
        QString dirPath = "D:\\C++\\qt1\\Tetris\\userGameHistory";
        dirPath.append("\\");
        dirPath.append(fileName);
        qDebug()<<dirPath;
        QFile sourceFile(dirPath);
        if (!sourceFile.exists()) {
            qWarning("File is not exists");
        }
        else
        {

                    this->close();
                    setHistory *set = new setHistory(text); // 将 text 传递给新窗口的构造函数中
                    set->setAttribute(Qt::WA_DeleteOnClose);
                    set->show();
                    set->show();                
        }
        }

}

