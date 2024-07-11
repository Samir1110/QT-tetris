#ifndef STARTWINODW_H
#define STARTWINODW_H

#include <QDialog>

namespace Ui {
class startwinodw;
}

class startwinodw : public QDialog
{
    Q_OBJECT

public:
    explicit startwinodw(QWidget *parent = nullptr);
    ~startwinodw();

private slots:
    void on_StartButton_clicked();

    void on_HistoryButton_clicked();

    void on_SetButton_clicked();

    void on_pushButton_clicked();

private:
    Ui::startwinodw *ui;
};

#endif // STARTWINODW_H
