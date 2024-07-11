#ifndef CHOOSEGAME_H
#define CHOOSEGAME_H

#include <QWidget>
#include "startwinodw.h"
namespace Ui {
class ChooseGame;
}

class ChooseGame : public QWidget
{
    Q_OBJECT

public:
    explicit ChooseGame(QWidget *parent = nullptr);
    ~ChooseGame();
    startwinodw * sw;

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_5_clicked();

private:
    Ui::ChooseGame *ui;
};

#endif // CHOOSEGAME_H
