#ifndef SETTING_H
#define SETTING_H

#include <QWidget>

namespace Ui {
class setting;
}

class setting : public QWidget
{
    Q_OBJECT

public:
    explicit setting(QWidget *parent = nullptr);
    ~setting();

private slots:
    //void on_lineEdit_editingFinished();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_clicked();

private:
    Ui::setting *ui;
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

#endif // SETTING_H
