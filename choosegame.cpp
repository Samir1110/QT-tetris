#include "choosegame.h"
#include "ui_choosegame.h"
#include"mainwindow.h"
#include"mainwindow2.h"
#include<QTextStream>
ChooseGame::ChooseGame(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChooseGame)
{
    ui->setupUi(this);
    setWindowTitle("选择游戏模式");
}

ChooseGame::~ChooseGame()
{
    delete ui;
}

void ChooseGame::on_pushButton_2_clicked()
{
    QString filePath = "D:\\C++\\qt1\\Tetris\\setGame.txt"; // 文件路径
    QFile file(filePath); // 创建 QFile 对象

    if (!file.open(QIODevice::ReadWrite | QIODevice::Text )) {
        qWarning("Failed to open file.");
    }

    QTextStream in(&file); // 创建 QTextStream 对象
    QString line = in.readLine(); // 读取一行数据

    // 根据逗号分隔字符串，获取需要修改的值
    QStringList dataList = line.split(",");
    if (dataList.size() >= 4) {
        dataList[3] = "2"; // 修改第三个逗号后面的值为 1
        line = dataList.join(",");
        file.resize(0);
        QTextStream out(&file);
        out << line; // 追加修改后的数据到文件中
    }
    file.close();
    this->hide();
    MainWindow *tetrixWindow1 = new MainWindow;
    tetrixWindow1->last = this;
    tetrixWindow1-> setAttribute(Qt::WA_DeleteOnClose);
    tetrixWindow1->setGameBefore();
    tetrixWindow1->show();
}


void ChooseGame::on_pushButton_clicked()
{
    QString filePath = "D:\\C++\\qt1\\Tetris\\setGame.txt"; // 文件路径
    QFile file(filePath); // 创建 QFile 对象

    if (!file.open(QIODevice::ReadWrite | QIODevice::Text )) {
        qWarning("Failed to open file.");
    }

    QTextStream in(&file); // 创建 QTextStream 对象
    QString line = in.readLine(); // 读取一行数据

    // 根据逗号分隔字符串，获取需要修改的值
    QStringList dataList = line.split(",");
    if (dataList.size() >= 4) {
        dataList[3] = "1"; // 修改第三个逗号后面的值为 1
        line = dataList.join(",");
        file.resize(0);
        QTextStream out(&file);
        out << line; // 追加修改后的数据到文件中
    }
    file.close();
    this->hide();
    MainWindow *tetrixWindow1 = new MainWindow;
    tetrixWindow1->last = this;
    tetrixWindow1-> setAttribute(Qt::WA_DeleteOnClose);
    tetrixWindow1->setGameBefore();
    tetrixWindow1->show();
}

void ChooseGame::on_pushButton_4_clicked()
{
    QString filePath = "D:\\C++\\qt1\\Tetris\\setGame.txt"; // 文件路径
    QFile file(filePath); // 创建 QFile 对象

    if (!file.open(QIODevice::ReadWrite | QIODevice::Text )) {
        qWarning("Failed to open file.");
    }

    QTextStream in(&file); // 创建 QTextStream 对象
    QString line = in.readLine(); // 读取一行数据

    // 根据逗号分隔字符串，获取需要修改的值
    QStringList dataList = line.split(",");
    if (dataList.size() >= 4) {
        dataList[3] = "4"; // 修改第三个逗号后面的值为 1
        line = dataList.join(",");
        file.resize(0);
        QTextStream out(&file);
        out << line; // 追加修改后的数据到文件中
    }
    file.close();
    this->hide();
    MainWindow *tetrixWindow1 = new MainWindow;
    tetrixWindow1->last = this;
    tetrixWindow1-> setAttribute(Qt::WA_DeleteOnClose);
    tetrixWindow1->setGameBefore();
    tetrixWindow1->show();
}


void ChooseGame::on_pushButton_3_clicked()
{
    QString filePath = "D:\\C++\\qt1\\Tetris\\setGame.txt"; // 文件路径
    QFile file(filePath); // 创建 QFile 对象

    if (!file.open(QIODevice::ReadWrite | QIODevice::Text )) {
        qWarning("Failed to open file.");
    }

    QTextStream in(&file); // 创建 QTextStream 对象
    QString line = in.readLine(); // 读取一行数据

    // 根据逗号分隔字符串，获取需要修改的值
    QStringList dataList = line.split(",");
    if (dataList.size() >= 4) {
        dataList[3] = "3"; // 修改第三个逗号后面的值为 1
        line = dataList.join(",");
        file.resize(0);
        QTextStream out(&file);
        out << line; // 追加修改后的数据到文件中
    }
    file.close();
    this->hide();
    MainWindow2 *tetrixWindow2 = new MainWindow2;
    tetrixWindow2->last = this;
    tetrixWindow2-> setAttribute(Qt::WA_DeleteOnClose);
    tetrixWindow2->SetGameBefore();
    tetrixWindow2->show();
}


void ChooseGame::on_pushButton_5_clicked()
{
    this->close();
    sw->show();
}

