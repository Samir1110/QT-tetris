#include "userhistory.h"
#include "ui_userhistory.h"
#include<QDir>
#include<QFile>
#include<QDateTime>
#include<QVBoxLayout>
userHistory::userHistory(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::userHistory)
{
    ui->setupUi(this);
    setWindowTitle("多玩家游戏记录");
    setObjectName("userHistory");
    // 创建一个 QVBoxLayout 布局，将其设置为 QWidget 的 layout
    QVBoxLayout *layout = new QVBoxLayout(this);
    setLayout(layout);

    // 创建 QTableWidget 控件并添加到布局中
    QTableWidget *tableWidget = new QTableWidget(this);
    layout->addWidget(tableWidget);

    // 设置表头和列数
    tableWidget->setColumnCount(2);
    QStringList headers = QStringList() << "存档号" << "存档时间";
    tableWidget->setHorizontalHeaderLabels(headers);

    // 读取文件夹中的文件信息并添加到表格中
    QString folderPath = "D:\\C++\\qt1\\Tetris\\userGameHistory";
    QDir folder(folderPath);
    QFileInfoList fileList = folder.entryInfoList(QDir::NoDotAndDotDot | QDir::Files);

    tableWidget->setRowCount(fileList.size());

    for (int i = 0; i < fileList.size(); ++i) {
        QFileInfo fileInfo = fileList.at(i);

        QTableWidgetItem *fileNameItem = new QTableWidgetItem(fileInfo.fileName());
        QTableWidgetItem *fileTimeItem = new QTableWidgetItem(fileInfo.birthTime().toString("M/d hh:mm"));

        tableWidget->setItem(i, 0, fileNameItem);
        tableWidget->setItem(i, 1, fileTimeItem);
    }

    // 自适应表格大小
    tableWidget->resizeColumnsToContents();
    tableWidget->resizeRowsToContents();

    }



userHistory::~userHistory()
{
    delete ui;
}
