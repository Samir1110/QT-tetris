#ifndef USERHISTORY_H
#define USERHISTORY_H

#include <QWidget>

namespace Ui {
class userHistory;
}

class userHistory : public QWidget
{
    Q_OBJECT

public:
    explicit userHistory(QWidget *parent = nullptr);
    ~userHistory();

private:
    Ui::userHistory *ui;
};

#endif // USERHISTORY_H
