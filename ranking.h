#ifndef RANKING_H
#define RANKING_H

#include <QWidget>
#include <QTableWidgetItem>
namespace Ui {
class ranking;
}

class ranking : public QWidget
{
    Q_OBJECT

public:
    explicit ranking(QWidget *parent = nullptr);
    ~ranking();
    void loadRank();
    void setNumberSort(int column);


private:
    Ui::ranking *ui;
};

// 自定义 QTableWidgetItem 子类
class NumberTableWidgetItem : public QTableWidgetItem {
public:
    bool operator<(const QTableWidgetItem &other) const override {
        // 如果比较对象是一个数字，则按照数字大小进行比较
        if (other.type() == QTableWidgetItem::UserType) {
            return data(Qt::UserRole).toInt() < other.data(Qt::UserRole).toInt();
        }
        // 否则按照字符串排序规则进行比较
        return QTableWidgetItem::operator<(other);
    }
};
#endif // RANKING_H
