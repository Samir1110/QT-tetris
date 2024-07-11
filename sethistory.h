#ifndef SETHISTORY_H
#define SETHISTORY_H

#include <QWidget>

namespace Ui {
class setHistory;
}

class setHistory : public QWidget
{
    Q_OBJECT

public:
    explicit setHistory(QString text, QWidget *parent = nullptr);
    ~setHistory();

private slots:
    void on_pushButton_3_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::setHistory *ui;
    QString m_text; // 保存 text 的成员变量
};
class MyInput
{
private:
    QString data[30];

public:
    MyInput(QString in)  // 把输入的字符串按逗号分成单独的字符串
    {
        int j=0;
        QString temp="";
        for(int i=0;i < in.size();i++)
        {
            if( in[i] == ',' )
            {
                data[j++] = temp;
                temp = "";
            }
            else
                temp = temp + in[i];
        }
        data[j] = temp;
    }
    QString GetInput(int index)
    {
        return data[index];
    }
};
#endif // SETHISTORY_H
