#include "background.h"
#include "ui_background.h"
#include <QPixmap>
#include<QDebug>
#include<QFile>
#include <QTextStream>

backGround::backGround(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::backGround)
{
    ui->setupUi(this);
    setWindowTitle("选择样式");
    QPixmap pixmap1("D:\\C++\\qt1\\Tetris\\BKPicture\\01.jpeg"); // 加载图片
    ui->Bk1->setPixmap(pixmap1.scaled(ui->Bk1->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation)); // 设置 QLabel 的图片，并自动适应大小
    ui->Bk1->setScaledContents(true); // 设置 QLabel 的 scaledContents 属性为 true

    QPixmap pixmap2("D:\\C++\\qt1\\Tetris\\BKPicture\\02.jpg"); // 加载图片
    ui->Bk2->setPixmap(pixmap2.scaled(ui->Bk2->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation)); // 设置 QLabel 的图片，并自动适应大小
    ui->Bk2->setScaledContents(true); // 设置 QLabel 的 scaledContents 属性为 true

    QPixmap pixmap3("D:\\C++\\qt1\\Tetris\\BKPicture\\03.jpg"); // 加载图片
    ui->Bk3->setPixmap(pixmap3.scaled(ui->Bk3->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation)); // 设置 QLabel 的图片，并自动适应大小
    ui->Bk3->setScaledContents(true); // 设置 QLabel 的 scaledContents 属性为 true

    QPixmap pixmap4("D:\\C++\\qt1\\Tetris\\BKPicture\\04.jpg"); // 加载图片
    ui->Bk4->setPixmap(pixmap4.scaled(ui->Bk4->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation)); // 设置 QLabel 的图片，并自动适应大小
    ui->Bk4->setScaledContents(true); // 设置 QLabel 的 scaledContents 属性为 true

    QPixmap pixmap5("D:\\C++\\qt1\\Tetris\\BKPicture\\05.jpg"); // 加载图片
    ui->Bk5->setPixmap(pixmap5.scaled(ui->Bk5->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation)); // 设置 QLabel 的图片，并自动适应大小
    ui->Bk5->setScaledContents(true); // 设置 QLabel 的 scaledContents 属性为 true

    QPixmap pixmap6("D:\\C++\\qt1\\Tetris\\BKPicture\\06.jpg"); // 加载图片
    ui->Bk6->setPixmap(pixmap6.scaled(ui->Bk6->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation)); // 设置 QLabel 的图片，并自动适应大小
    ui->Bk6->setScaledContents(true); // 设置 QLabel 的 scaledContents 属性为 true
}

backGround::~backGround()
{
    delete ui;
}

void backGround::on_pushButton_4_clicked()
{
    FileName = "D:\\C++\\qt1\\Tetris\\BKPicture\\01.jpeg";
    QFile file("D:\\C++\\qt1\\Tetris\\backGround.txt"); // 创建 QFile 对象
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) { // 打开文件
        qDebug() << "Failed to open file:" ;
        return;
    }
    QTextStream out(&file); // 创建 QTextStream 对象
    out << FileName ;
    file.close(); // 关闭文件
}


void backGround::on_pushButton_5_clicked()
{
    FileName = "D:\\C++\\qt1\\Tetris\\BKPicture\\02.jpg";
    QFile file("D:\\C++\\qt1\\Tetris\\backGround.txt"); // 创建 QFile 对象
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) { // 打开文件
        qDebug() << "Failed to open file:" ;
        return;
    }
    QTextStream out(&file); // 创建 QTextStream 对象
    out << FileName ;
    file.close(); // 关闭文件
}


void backGround::on_pushButton_6_clicked()
{
    FileName = "D:\\C++\\qt1\\Tetris\\BKPicture\\03.jpg";
    QFile file("D:\\C++\\qt1\\Tetris\\backGround.txt"); // 创建 QFile 对象
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) { // 打开文件
        qDebug() << "Failed to open file:" ;
        return;
    }
    QTextStream out(&file); // 创建 QTextStream 对象
    out << FileName ;
    file.close(); // 关闭文件
}


void backGround::on_pushButton_7_clicked()
{
    FileName = "D:\\C++\\qt1\\Tetris\\BKPicture\\04.jpg";
    QFile file("D:\\C++\\qt1\\Tetris\\backGround.txt"); // 创建 QFile 对象
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) { // 打开文件
        qDebug() << "Failed to open file:" ;
        return;
    }
    QTextStream out(&file); // 创建 QTextStream 对象
    out << FileName ;
    file.close(); // 关闭文件
}


void backGround::on_pushButton_8_clicked()
{
    FileName = "D:\\C++\\qt1\\Tetris\\BKPicture\\05.jpg";
    QFile file("D:\\C++\\qt1\\Tetris\\backGround.txt"); // 创建 QFile 对象
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) { // 打开文件
        qDebug() << "Failed to open file:" ;
        return;
    }
    QTextStream out(&file); // 创建 QTextStream 对象
    out << FileName ;
    file.close(); // 关闭文件
}


void backGround::on_pushButton_9_clicked()
{
    FileName = "D:\\C++\\qt1\\Tetris\\BKPicture\\06.jpg";
    QFile file("D:\\C++\\qt1\\Tetris\\backGround.txt"); // 创建 QFile 对象
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) { // 打开文件
        qDebug() << "Failed to open file:" ;
        return;
    }
    QTextStream out(&file); // 创建 QTextStream 对象
    out << FileName ;
    file.close(); // 关闭文件
}


void backGround::on_pushButton_clicked()
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
    if (dataList.size() >= 7) {
        dataList[6] = "1";
        line = dataList.join(",");
        file.resize(0);
        QTextStream out(&file);
        out << line; // 追加修改后的数据到文件中
    }
    file.close();
}



void backGround::on_pushButton_2_clicked()
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
    if (dataList.size() >= 7) {
        dataList[6] = "2";
        line = dataList.join(",");
        file.resize(0);
        QTextStream out(&file);
        out << line; // 追加修改后的数据到文件中
    }
    file.close();
}


void backGround::on_pushButton_3_clicked()
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
    if (dataList.size() >= 7) {
        dataList[6] = "3";
        line = dataList.join(",");
        file.resize(0);
        QTextStream out(&file);
        out << line; // 追加修改后的数据到文件中
    }
    file.close();
}

