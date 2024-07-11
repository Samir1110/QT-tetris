#include "ranking.h"
#include "ui_ranking.h"
#include<QFile>
#include<QDebug>
#include <QStyledItemDelegate>

ranking::ranking(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ranking)
{
    ui->setupUi(this);
    setFixedSize(875, 1080);
    setWindowTitle("排行榜");

    // 访问QTableWidget控件
    QTableWidget *tableWidget = ui->tableWidget;
    tableWidget->setGeometry(25, 25, 825, 1000);
    //tableWidget->show();
    // 设置表格内容

    // 设置表头
    tableWidget->setColumnCount(5);
    tableWidget->setRowCount(20);
    tableWidget->setHorizontalHeaderLabels(QStringList()<<"玩家"<<"分数"<<"关卡"<<"游玩时间"<<"排名");



}



ranking::~ranking()
{
    delete ui;
}


void ranking::loadRank()
{
    int row = 0; // 从第一行开始添加数据
    QString fileName = "D:\\C++\\qt1\\Tetris\\ranking.txt";
    QFile file(fileName);

    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Failed to open file: " << fileName;
        return; // 如果文件无法打开，则返回
    }

    // 从文件中读取数据并进行处理
    while (!file.atEnd()) {
        QString line = file.readLine();
        QStringList fields = line.split(",");
        //qDebug()  << fields.size();
        // 使用循环为每个单元格创建一个QTableWidgetItem对象，并将其插入到表格中
        for (int column = 0; column < fields.size(); column++) {

            if (column == 1)
            {
                QTableWidgetItem *item = new QTableWidgetItem();
                item->setData(Qt::DisplayRole, fields[1].toInt());
                ui->tableWidget->setItem(row, 1, item);
            }
            else
            {
                QTableWidgetItem *item = new QTableWidgetItem(fields[column]);
                ui->tableWidget->setItem(row, column, item);
            }

        }

        row++; // 下一行
    }
    // 执行排序操作
    ui->tableWidget->sortItems(1,Qt::DescendingOrder);
    // 往表格中插入数据
    QTableWidget *tableWidget = ui->tableWidget;
    tableWidget->setItem(0, 4, new QTableWidgetItem("第一名"));
    tableWidget->setItem(1, 4, new QTableWidgetItem("第二名"));
    tableWidget->setItem(2, 4, new QTableWidgetItem("第三名"));
    tableWidget->setItem(3, 4, new QTableWidgetItem("第四名"));
    tableWidget->setItem(4, 4, new QTableWidgetItem("第五名"));
    tableWidget->setItem(5, 4, new QTableWidgetItem("第六名"));
    tableWidget->setItem(6, 4, new QTableWidgetItem("第七名"));
    tableWidget->setItem(7, 4, new QTableWidgetItem("第八名"));
    tableWidget->setItem(8, 4, new QTableWidgetItem("第九名"));
    tableWidget->setItem(9, 4, new QTableWidgetItem("第十名"));
    tableWidget->setItem(10, 4, new QTableWidgetItem("第十一名"));
    tableWidget->setItem(11, 4, new QTableWidgetItem("第十二名"));
    tableWidget->setItem(12, 4, new QTableWidgetItem("第十三名"));
    tableWidget->setItem(13, 4, new QTableWidgetItem("第十四名"));
    tableWidget->setItem(14, 4, new QTableWidgetItem("第十五名"));
    tableWidget->setItem(15, 4, new QTableWidgetItem("第十六名"));
    tableWidget->setItem(16, 4, new QTableWidgetItem("第十七名"));
    tableWidget->setItem(17, 4, new QTableWidgetItem("第十八名"));
    tableWidget->setItem(18, 4, new QTableWidgetItem("第十九名"));
    tableWidget->setItem(19, 4, new QTableWidgetItem("第二十名"));
    file.close(); // 用完后关闭文件

}

void ranking::setNumberSort(int column) {
    for (int row = 0; row < ui->tableWidget->rowCount(); ++row) {
        auto *item = new NumberTableWidgetItem();
        item->setData(Qt::UserRole, ui->tableWidget->item(row, column)->data(Qt::UserRole));
        ui->tableWidget->setItem(row, column, item);
    }
    ui->tableWidget->sortItems(column, Qt::DescendingOrder);
}
