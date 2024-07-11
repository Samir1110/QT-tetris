#include "setting.h"
#include "ui_setting.h"

#include "background.h"
#include "keyboard.h"
#include<QFile>
#include<QTextStream>
#include <QFileDialog>
#include <QDesktopServices>
#include<QDebug>
#include<QInputDialog>
setting::setting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::setting)

{
    ui->setupUi(this);
    setWindowTitle("游戏设置");
    //connect(ui->lineEdit, SIGNAL(editingFinished()), this, SLOT(on_lineEdit_editingFinished()));
    QFile file("D:\\C++\\qt1\\Tetris\\setGame.txt");
    QTextStream in(&file);

    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "设置文件无法打开";
        return;
    }
    else
    {
        QString data = in.readAll();
        MyInput input(data);
        ui->nameLabel->setText(input.GetInput(0));
        file.close();
    }
}

setting::~setting()
{
    delete ui;
}

//修改名字
void setting::on_pushButton_2_clicked()
{
    bool ok;
    QString text = QInputDialog::getText(this, tr("新玩家名"),
                                         tr("请输入文本:"), QLineEdit::Normal,
                                         "", &ok);
    if (ok && !text.isEmpty()) {
    // 用户点击了“确定”按钮并且输入非空文本时执行此处代码
        QString filePath = "D:\\C++\\qt1\\Tetris\\setGame.txt"; // 文件路径
        QFile file(filePath); // 创建 QFile 对象

        if (!file.open(QIODevice::ReadWrite | QIODevice::Text )) {
            qWarning("Failed to open file.");
        }

        QTextStream in(&file); // 创建 QTextStream 对象
        QString line = in.readLine(); // 读取一行数据

        // 根据逗号分隔字符串，获取需要修改的值
        QStringList dataList = line.split(",");
        if (dataList.size() >= 6) {
            dataList[0] = text; // 修改第三个逗号后面的值为 1
            line = dataList.join(",");
            file.resize(0);
            QTextStream out(&file);
            out << line; // 追加修改后的数据到文件中
        }

        ui->nameLabel->setText(text);
        file.close();
        }

}


//修改速度
void setting::on_pushButton_3_clicked()
{
        bool ok;
        QString text = QInputDialog::getText(this, tr("修改速度"),
                                             tr("请输入文本:"), QLineEdit::Normal,
                                             "", &ok);
        if (ok && !text.isEmpty()) {
        // 用户点击了“确定”按钮并且输入非空文本时执行此处代码
        QString filePath = "D:\\C++\\qt1\\Tetris\\setGame.txt"; // 文件路径
        QFile file(filePath); // 创建 QFile 对象

        if (!file.open(QIODevice::ReadWrite | QIODevice::Text )) {
            qWarning("Failed to open file.");
        }

        QTextStream in(&file); // 创建 QTextStream 对象
        QString line = in.readLine(); // 读取一行数据

        // 根据逗号分隔字符串，获取需要修改的值
        QStringList dataList = line.split(",");
        if (dataList.size() >= 6) {
            dataList[4] = text;
            line = dataList.join(",");
            file.resize(0);
            QTextStream out(&file);
            out << line; // 追加修改后的数据到文件中
        }
        file.close();
        }
}

//自定义列数
void setting::on_pushButton_4_clicked()
{
        bool ok;
        QString text = QInputDialog::getText(this, tr("自定义列数"),
                                             tr("请输入文本:"), QLineEdit::Normal,
                                             "", &ok);
        if (ok && !text.isEmpty()) {
        // 用户点击了“确定”按钮并且输入非空文本时执行此处代码
        QString filePath = "D:\\C++\\qt1\\Tetris\\setGame.txt"; // 文件路径
        QFile file(filePath); // 创建 QFile 对象

        if (!file.open(QIODevice::ReadWrite | QIODevice::Text )) {
            qWarning("Failed to open file.");
        }

        QTextStream in(&file); // 创建 QTextStream 对象
        QString line = in.readLine(); // 读取一行数据

        // 根据逗号分隔字符串，获取需要修改的值
        QStringList dataList = line.split(",");
        if (dataList.size() >= 6) {
            dataList[1] = text;
            line = dataList.join(",");
            file.resize(0);
            QTextStream out(&file);
            out << line; // 追加修改后的数据到文件中
        }
        file.close();
        }
}

//行数
void setting::on_pushButton_5_clicked()
{
        bool ok;
        QString text = QInputDialog::getText(this, tr("自定义行数"),
                                             tr("请输入文本:"), QLineEdit::Normal,
                                             "", &ok);
        if (ok && !text.isEmpty()) {
        // 用户点击了“确定”按钮并且输入非空文本时执行此处代码
        QString filePath = "D:\\C++\\qt1\\Tetris\\setGame.txt"; // 文件路径
        QFile file(filePath); // 创建 QFile 对象

        if (!file.open(QIODevice::ReadWrite | QIODevice::Text )) {
            qWarning("Failed to open file.");
        }

        QTextStream in(&file); // 创建 QTextStream 对象
        QString line = in.readLine(); // 读取一行数据

        // 根据逗号分隔字符串，获取需要修改的值
        QStringList dataList = line.split(",");
        if (dataList.size() >= 6) {
            dataList[5] = text;
            line = dataList.join(",");
            file.resize(0);
            QTextStream out(&file);
            out << line; // 追加修改后的数据到文件中
        }
        file.close();
        }
}

//键盘模式选择
void setting::on_pushButton_6_clicked()
{
    keyBoard *kb = new keyBoard;
    kb->setAttribute(Qt::WA_DeleteOnClose);
    kb->show();

}

//恢复默认配置
void setting::on_pushButton_7_clicked()
{
        QFile sourceFile("D:\\C++\\qt1\\Tetris\\default.txt");
        QFile targetFile("D:\\C++\\qt1\\Tetris\\setGame.txt");

        if (!sourceFile.open(QIODevice::ReadOnly)) {
        qDebug() << "Failed to open source file.";
        return;
        }

        if (!targetFile.open(QIODevice::ReadWrite | QIODevice::Truncate)) {
        qDebug() << "Failed to open target file.";
        sourceFile.close();
        return;
        }

        while (!sourceFile.atEnd()) {
        QByteArray line = sourceFile.readLine();
        targetFile.write(line);
        }
}



void setting::on_pushButton_9_clicked()
{
    backGround *bg = new backGround;
    bg->setAttribute(Qt::WA_DeleteOnClose);
    bg->show();
}


void setting::on_pushButton_clicked()
{
    QString mdFilePath = "D:\\C++\\qt1\\Tetris\\修改说明.md"; // 替换为你的md文件路径
    QDesktopServices::openUrl(QUrl::fromLocalFile(mdFilePath));
}

