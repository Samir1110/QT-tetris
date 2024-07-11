#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <QWidget>

namespace Ui {
class backGround;
}

class backGround : public QWidget
{
    Q_OBJECT

public:
    explicit backGround(QWidget *parent = nullptr);
    ~backGround();
    QString FileName;

private slots:
    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::backGround *ui;
};

#endif // BACKGROUND_H
