#ifndef HISTORY_H
#define HISTORY_H

#include <QWidget>

namespace Ui {
class history;
}

class history : public QWidget
{
    Q_OBJECT

public:
    explicit history(QWidget *parent = nullptr);
    ~history();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::history *ui;
};

#endif // HISTORY_H
