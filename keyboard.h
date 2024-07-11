#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <QWidget>

namespace Ui {
class keyBoard;
}

class keyBoard : public QWidget
{
    Q_OBJECT

public:
    explicit keyBoard(QWidget *parent = nullptr);
    ~keyBoard();

private slots:


    void on_pushButton_clicked();//修改左移

    void on_pushButton_2_clicked();//修改右移

    void on_pushButton_3_clicked();//修改旋转

    void on_pushButton_4_clicked();//修改下落一行

    void on_pushButton_5_clicked();//修改下落到底部

    void on_pushButton_6_clicked();//修改开始

    void on_pushButton_7_clicked();//修改暂停

    void on_pushButton_8_clicked();//修改退出

    void on_pushButton_10_clicked();//默认配置

private:
    Ui::keyBoard *ui;
};

#endif // KEYBOARD_H
