#include "sethistory.h"
#include "ui_sethistory.h"
#include<QFile>
#include<QDebug>
setHistory::setHistory(QString text, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::setHistory)
{
    ui->setupUi(this);
    setWindowTitle("玩家历史记录");
    m_text = text; // 保存 text 的值
}

setHistory::~setHistory()
{
    delete ui;
}

void setHistory::on_pushButton_3_clicked()
{
    QString fileName = m_text;
    QString extension = ".txt";

    fileName.append(extension); // 将扩展名添加到文件名后面

    //创建新文件在用户存档库中
    QString dirPath = "D:\\C++\\qt1\\Tetris\\userGameHistory";
    dirPath.append("\\");
    dirPath.append(fileName);
    qDebug()<<dirPath;

    QFile file(dirPath);
    if (file.exists()) {
        if (file.remove()) {
            qDebug() << "Successfully deleted file" << fileName;
        } else {
            qDebug() << "Failed to delete file" << fileName << file.errorString();
        }
    } else {
        qDebug() << "File does not exist:" << fileName;
    }

}

void setHistory::on_pushButton_clicked()
{
    QString fileName = m_text;
    QString extension = ".txt";

    fileName.append(extension); // 将扩展名添加到文件名后面

    //创建新文件在用户存档库中
    QString dirPath = "D:\\C++\\qt1\\Tetris\\userGameHistory";
    dirPath.append("\\");
    dirPath.append(fileName);
    qDebug()<<dirPath;
    QFile sourceFile(dirPath);
    QFile targetFile("D:\\C++\\qt1\\Tetris\\lastGame.txt");

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
    QString _name;
    QStringList dataList;
    sourceFile.seek(0);
    while (!sourceFile.atEnd()) {
        QString line = sourceFile.readLine().trimmed();
        if (!line.isEmpty()) {
            dataList = line.split(",");
            break; // 在这种情况下，我们只需要读取一行数据，所以可以直接退出循环
        }
    }
    sourceFile.close();

    if (dataList.size() >= 12) {
        _name = dataList.value(9); // 获取列表中索引为 9 的元素（第10个数据）
    }


    qDebug()<<_name;
    targetFile.close();
    sourceFile.close();


    QString filePath = "D:\\C++\\qt1\\Tetris\\setGame.txt"; // 文件路径
    QFile file(filePath); // 创建 QFile 对象

    if (!file.open(QIODevice::ReadWrite | QIODevice::Text )) {
        qWarning("Failed to open file.");
    }

    QTextStream in1(&file); // 创建 QTextStream 对象
    QString line1 = in1.readLine(); // 读取一行数据

    // 根据逗号分隔字符串，获取需要修改的值
    QStringList dataList1 = line1.split(",");
    if (dataList1.size() >= 6) {
        dataList1[0] = _name;
        line1 = dataList1.join(",");
        file.resize(0);
        QTextStream out(&file);
        out << line1; // 追加修改后的数据到文件中
    }
    file.close();
}



void setHistory::on_pushButton_2_clicked()
{
    QString fileName = m_text;
    QString extension = ".txt";

    fileName.append(extension); // 将扩展名添加到文件名后面

    //创建新文件在用户存档库中
    QString dirPath = "D:\\C++\\qt1\\Tetris\\userGameHistory";
    dirPath.append("\\");
    dirPath.append(fileName);
    qDebug()<<dirPath;
    QFile sourceFile(dirPath);

    QString fileNameNew = m_text;
    QString extensionNew = "_Copy.txt";

    fileNameNew.append(extensionNew); // 将扩展名添加到文件名后面

    //创建新文件在用户存档库中
    QString dirPathNew = "D:\\C++\\qt1\\Tetris\\userGameHistory";
    dirPathNew.append("\\");
    dirPathNew.append(fileNameNew);
    qDebug()<<dirPathNew;
    QFile targetFile(dirPathNew);

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

