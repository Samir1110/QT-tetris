#include "keyboard.h"
#include "ui_keyboard.h"
#include <QFile>
#include <QInputDialog>
#include <QTextStream>
#include  <QMessageBox>
keyBoard::keyBoard(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::keyBoard)
{
    ui->setupUi(this);
    setWindowTitle("自定义快捷键");
    QString filePath = "D:\\C++\\qt1\\Tetris\\key.txt"; // 文件路径
    QFile file(filePath); // 创建 QFile 对象

    if (!file.open(QIODevice::ReadWrite | QIODevice::Text )) {
        qWarning("Failed to open file.");
    }

    QTextStream in(&file); // 创建 QTextStream 对象
    QString line = in.readLine(); // 读取一行数据

    // 根据逗号分隔字符串，获取需要修改的值
    QStringList dataList = line.split(",");
    ui->left->setText(dataList[0]);
    ui->right->setText(dataList[1]);
    ui->changeD->setText(dataList[2]);
    ui->fallOne->setText(dataList[3]);
    ui->fallFull->setText(dataList[4]);
    ui->start->setText(dataList[5]);
    ui->pause->setText(dataList[6]);
    ui->end->setText(dataList[7]);
}

keyBoard::~keyBoard()
{
    delete ui;
}

//修改左移键
void keyBoard::on_pushButton_clicked()
{
    bool ok;
    QString text = QInputDialog::getText(this, tr("修改左移键"),
                                         tr("请输入A~Z或0~9"), QLineEdit::Normal,
                                         "", &ok);
    if (ok && !text.isEmpty()) {
        // 判断用户输入是否符合预期
        QRegExp rx("[A-Za-z0-9]+");
        if (!rx.exactMatch(text)) {
            // 如果输入不符合预期，弹出一个 QMessageBox 提示用户
            QMessageBox::critical(this, tr("错误"), tr("请输入 A~Z 或 0~9！"));
            return;
        }

        QString filePath = "D:\\C++\\qt1\\Tetris\\key.txt"; // 文件路径
        QFile file(filePath); // 创建 QFile 对象

        if (!file.open(QIODevice::ReadWrite | QIODevice::Text )) {
            qWarning("Failed to open file.");
        }

        QTextStream in(&file); // 创建 QTextStream 对象
        QString line = in.readLine(); // 读取一行数据

        // 根据逗号分隔字符串，获取需要修改的值
        QStringList dataList = line.split(",");
        if (dataList.size() >= 8) {
            dataList[0] = text;
            line = dataList.join(",");
            file.resize(0);
            QTextStream out(&file);
            out << line; // 追加修改后的数据到文件中
        }
        ui->left->setText(text);
        file.close();
    }

}


void keyBoard::on_pushButton_2_clicked()
{
    bool ok;
    QString text = QInputDialog::getText(this, tr("修改右移键"),
                                         tr("请输入A~Z或0~9"), QLineEdit::Normal,
                                         "", &ok);
    if (ok && !text.isEmpty()) {
        // 判断用户输入是否符合预期
        QRegExp rx("[A-Za-z0-9]+");
        if (!rx.exactMatch(text)) {
            // 如果输入不符合预期，弹出一个 QMessageBox 提示用户
            QMessageBox::critical(this, tr("错误"), tr("请输入 A~Z 或 0~9！"));
            return;
        }

        QString filePath = "D:\\C++\\qt1\\Tetris\\key.txt"; // 文件路径
        QFile file(filePath); // 创建 QFile 对象

        if (!file.open(QIODevice::ReadWrite | QIODevice::Text )) {
            qWarning("Failed to open file.");
        }

        QTextStream in(&file); // 创建 QTextStream 对象
        QString line = in.readLine(); // 读取一行数据

        // 根据逗号分隔字符串，获取需要修改的值
        QStringList dataList = line.split(",");
        if (dataList.size() >= 8) {
            dataList[1] = text;
            line = dataList.join(",");
            file.resize(0);
            QTextStream out(&file);
            out << line; // 追加修改后的数据到文件中
        }
        ui->right->setText(text);
        file.close();
    }
}


void keyBoard::on_pushButton_3_clicked()
{
    bool ok;
    QString text = QInputDialog::getText(this, tr("修改变形键"),
                                         tr("请输入A~Z或0~9"), QLineEdit::Normal,
                                         "", &ok);
    if (ok && !text.isEmpty()) {
        // 判断用户输入是否符合预期
        QRegExp rx("[A-Za-z0-9]+");
        if (!rx.exactMatch(text)) {
            // 如果输入不符合预期，弹出一个 QMessageBox 提示用户
            QMessageBox::critical(this, tr("错误"), tr("请输入 A~Z 或 0~9！"));
            return;
        }

        QString filePath = "D:\\C++\\qt1\\Tetris\\key.txt"; // 文件路径
        QFile file(filePath); // 创建 QFile 对象

        if (!file.open(QIODevice::ReadWrite | QIODevice::Text )) {
            qWarning("Failed to open file.");
        }

        QTextStream in(&file); // 创建 QTextStream 对象
        QString line = in.readLine(); // 读取一行数据

        // 根据逗号分隔字符串，获取需要修改的值
        QStringList dataList = line.split(",");
        if (dataList.size() >= 8) {
            dataList[2] = text;
            line = dataList.join(",");
            file.resize(0);
            QTextStream out(&file);
            out << line; // 追加修改后的数据到文件中
        }
        ui->changeD->setText(text);
        file.close();
    }
}


void keyBoard::on_pushButton_4_clicked()
{
    bool ok;
    QString text = QInputDialog::getText(this, tr("修改下落一格键"),
                                         tr("请输入A~Z或0~9"), QLineEdit::Normal,
                                         "", &ok);
    if (ok && !text.isEmpty()) {
        // 判断用户输入是否符合预期
        QRegExp rx("[A-Za-z0-9]+");
        if (!rx.exactMatch(text)) {
            // 如果输入不符合预期，弹出一个 QMessageBox 提示用户
            QMessageBox::critical(this, tr("错误"), tr("请输入 A~Z 或 0~9！"));
            return;
        }

        QString filePath = "D:\\C++\\qt1\\Tetris\\key.txt"; // 文件路径
        QFile file(filePath); // 创建 QFile 对象

        if (!file.open(QIODevice::ReadWrite | QIODevice::Text )) {
            qWarning("Failed to open file.");
        }

        QTextStream in(&file); // 创建 QTextStream 对象
        QString line = in.readLine(); // 读取一行数据

        // 根据逗号分隔字符串，获取需要修改的值
        QStringList dataList = line.split(",");
        if (dataList.size() >= 8) {
            dataList[3] = text;
            line = dataList.join(",");
            file.resize(0);
            QTextStream out(&file);
            out << line; // 追加修改后的数据到文件中
        }
        ui->fallOne->setText(text);
        file.close();
    }
}


void keyBoard::on_pushButton_5_clicked()
{
    bool ok;
    QString text = QInputDialog::getText(this, tr("修改下落到底键"),
                                         tr("请输入A~Z或0~9"), QLineEdit::Normal,
                                         "", &ok);
    if (ok && !text.isEmpty()) {
        // 判断用户输入是否符合预期
        QRegExp rx("[A-Za-z0-9]+");
        if (!rx.exactMatch(text)) {
            // 如果输入不符合预期，弹出一个 QMessageBox 提示用户
            QMessageBox::critical(this, tr("错误"), tr("请输入 A~Z 或 0~9！"));
            return;
        }

        QString filePath = "D:\\C++\\qt1\\Tetris\\key.txt"; // 文件路径
        QFile file(filePath); // 创建 QFile 对象

        if (!file.open(QIODevice::ReadWrite | QIODevice::Text )) {
            qWarning("Failed to open file.");
        }

        QTextStream in(&file); // 创建 QTextStream 对象
        QString line = in.readLine(); // 读取一行数据

        // 根据逗号分隔字符串，获取需要修改的值
        QStringList dataList = line.split(",");
        if (dataList.size() >= 8) {
            dataList[4] = text;
            line = dataList.join(",");
            file.resize(0);
            QTextStream out(&file);
            out << line; // 追加修改后的数据到文件中
        }
        ui->fallFull->setText(text);
        file.close();
    }
}



void keyBoard::on_pushButton_6_clicked()
{
    bool ok;
    QString text = QInputDialog::getText(this, tr("修改开始键"),
                                         tr("请输入A~Z或0~9"), QLineEdit::Normal,
                                         "", &ok);
    if (ok && !text.isEmpty()) {
        // 判断用户输入是否符合预期
        QRegExp rx("[A-Za-z0-9]+");
        if (!rx.exactMatch(text)) {
            // 如果输入不符合预期，弹出一个 QMessageBox 提示用户
            QMessageBox::critical(this, tr("错误"), tr("请输入 A~Z 或 0~9！"));
            return;
        }

        QString filePath = "D:\\C++\\qt1\\Tetris\\key.txt"; // 文件路径
        QFile file(filePath); // 创建 QFile 对象

        if (!file.open(QIODevice::ReadWrite | QIODevice::Text )) {
            qWarning("Failed to open file.");
        }

        QTextStream in(&file); // 创建 QTextStream 对象
        QString line = in.readLine(); // 读取一行数据

        // 根据逗号分隔字符串，获取需要修改的值
        QStringList dataList = line.split(",");
        if (dataList.size() >= 8) {
            dataList[5] = text;
            line = dataList.join(",");
            file.resize(0);
            QTextStream out(&file);
            out << line; // 追加修改后的数据到文件中
        }
        ui->start->setText(text);
        file.close();
    }
}


void keyBoard::on_pushButton_7_clicked()
{
    bool ok;
    QString text = QInputDialog::getText(this, tr("修改暂停键"),
                                         tr("请输入A~Z或0~9"), QLineEdit::Normal,
                                         "", &ok);
    if (ok && !text.isEmpty()) {
        // 判断用户输入是否符合预期
        QRegExp rx("[A-Za-z0-9]+");
        if (!rx.exactMatch(text)) {
            // 如果输入不符合预期，弹出一个 QMessageBox 提示用户
            QMessageBox::critical(this, tr("错误"), tr("请输入 A~Z 或 0~9！"));
            return;
        }

        QString filePath = "D:\\C++\\qt1\\Tetris\\key.txt"; // 文件路径
        QFile file(filePath); // 创建 QFile 对象

        if (!file.open(QIODevice::ReadWrite | QIODevice::Text )) {
            qWarning("Failed to open file.");
        }

        QTextStream in(&file); // 创建 QTextStream 对象
        QString line = in.readLine(); // 读取一行数据

        // 根据逗号分隔字符串，获取需要修改的值
        QStringList dataList = line.split(",");
        if (dataList.size() >= 8) {
            dataList[6] = text;
            line = dataList.join(",");
            file.resize(0);
            QTextStream out(&file);
            out << line; // 追加修改后的数据到文件中
        }
        ui->pause->setText(text);
        file.close();
    }
}



void keyBoard::on_pushButton_8_clicked()
{
    bool ok;
    QString text = QInputDialog::getText(this, tr("修改退出键"),
                                         tr("请输入A~Z或0~9"), QLineEdit::Normal,
                                         "", &ok);
    if (ok && !text.isEmpty()) {
        // 判断用户输入是否符合预期
        QRegExp rx("[A-Za-z0-9]+");
        if (!rx.exactMatch(text)) {
            // 如果输入不符合预期，弹出一个 QMessageBox 提示用户
            QMessageBox::critical(this, tr("错误"), tr("请输入 A~Z 或 0~9！"));
            return;
        }

        QString filePath = "D:\\C++\\qt1\\Tetris\\key.txt"; // 文件路径
        QFile file(filePath); // 创建 QFile 对象

        if (!file.open(QIODevice::ReadWrite | QIODevice::Text )) {
            qWarning("Failed to open file.");
        }

        QTextStream in(&file); // 创建 QTextStream 对象
        QString line = in.readLine(); // 读取一行数据

        // 根据逗号分隔字符串，获取需要修改的值
        QStringList dataList = line.split(",");
        if (dataList.size() >= 8) {
            dataList[7] = text;
            line = dataList.join(",");
            file.resize(0);
            QTextStream out(&file);
            out << line; // 追加修改后的数据到文件中
        }
        ui->end->setText(text);
        file.close();
    }
}


void keyBoard::on_pushButton_10_clicked()
{
    QFile sourceFile("D:\\C++\\qt1\\Tetris\\defaultkey.txt");
    QFile targetFile("D:\\C++\\qt1\\Tetris\\key.txt");

    if (!sourceFile.open(QIODevice::ReadOnly)) {
        qWarning("Failed to open source file.") ;
        return;
    }

    if (!targetFile.open(QIODevice::ReadWrite | QIODevice::Truncate)) {
        qWarning("Failed to open source file.") ;
        sourceFile.close();
        return;
    }

    while (!sourceFile.atEnd()) {
        QByteArray line = sourceFile.readLine();
        targetFile.write(line);
    }
    sourceFile.seek(0);
    QTextStream in(&sourceFile); // 创建 QTextStream 对象

    QString line = in.readLine(); // 读取一行数据
    // 根据逗号分隔字符串，获取需要修改的值
    QStringList dataList = line.split(",");
    ui->left->setText(dataList[0]);
    ui->right->setText(dataList[1]);
    ui->changeD->setText(dataList[2]);
    ui->fallOne->setText(dataList[3]);
    ui->fallFull->setText(dataList[4]);
    ui->start->setText(dataList[5]);
    ui->pause->setText(dataList[6]);
    ui->end->setText(dataList[7]);
}

