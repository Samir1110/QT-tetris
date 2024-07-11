#include "GameArea2.h"
#include <QTimerEvent>
#include <QMessageBox>
#include <QKeyEvent>
#include <QTime>
#include<QApplication>
#include<QFile>
#include<QDebug>
#include<QTextStream>
//默认游戏区域为15*20的单元格，每个单元格尺寸40*40像素
constexpr int mAX_COLUMN = 22;
constexpr int mAX_ROW = 22;
constexpr int rECT_WIDTH = 45;
constexpr int rECT_HEIGHT = 45;
int MAX_COLUME = mAX_COLUMN;
int MAX_ROW	= mAX_ROW;
int pattern;
int keyPlace;
int RECT_WIDTH;
int RECT_HEIGHT;
//默认出生点水平中心处
int  DEFAULT_X_POS = (MAX_COLUME / 2 - 1);

GameArea2::GameArea2(QWidget *parent) : QWidget(parent)
{
    mScore = 0;
    mLevel = 1;
    mPaused = false;
    m_gameStarted = false;
    LoadGame = false;
    setMinimumSize(MAX_COLUME*RECT_WIDTH, MAX_ROW*RECT_HEIGHT);
}

// 在 GameArea2 的实现文件源文件中更新 myString 变量的值
void GameArea2::updateMyname(QString _name) {
    name = _name;
}

bool GameArea2::IsGameStarted() const
{
    return m_gameStarted;
}

void GameArea2::NewGame()
{
    mFixItems.ClearPoints();

    //mCurItem 和 mNextItem 使用不同随机因子，避免初始一样
    mCurItem.New(QTime::currentTime().msec());
    mCurItem.MoveTo(DEFAULT_X_POS, 1);//直接将方块移动到画面中央开始游戏

    mNextItem.New(QTime::currentTime().second());
    emit sigUpdateNextItem(mNextItem.Type(), mNextItem.Direction());//发送信号绘制下一个方块

    if(m_gameStarted == true)
    {
        mTimerID = startTimer(GetLevelTime(mLevel));
    }
    qDebug() << name;

}

void GameArea2::KeyPressed(int key)
{
    int x = 0;
    int y = 0;

    //	switch (key)
    //    {
    if(keyPlace == 1)
    {
        switch (key)
        {
        case Qt::Key_Left:
        {
            x = -1;
            break;
        }
        case Qt::Key_Up:
        {
            mCurItem.ChangeDirection(1);

            if (HitSide() || HitBottom())
            {
                mCurItem.ChangeDirection(-1);
            }
            return;
        }
        case Qt::Key_Right:
        {
            x = 1;
            break;
        }
        case Qt::Key_Down:
        {
            y = 1;
            break;
        }
        }
    }
    else
    {
        switch (key)
        {
        case Qt::Key_A:
        {
            x = -1;
            break;
        }
        case Qt::Key_W:
        {
            mCurItem.ChangeDirection(1);

            if (HitSide() || HitBottom())
            {
                mCurItem.ChangeDirection(-1);
            }
            return;
        }
        case Qt::Key_D:
        {
            x = 1;
            break;
        }
        case Qt::Key_S:
        {
            y = 1;
            break;
        }
        }
    }
    switch (key)
    {
    case Qt::Key_Space:
    {
        //空格键直接移到底部
        while (1)
        {
            mCurItem.Move(0, 1);
            if (HitSide() || HitBottom())
            {
                mCurItem.Move(0, -1);
                break;
            }
        }
        return;
    }
    case Qt::Key_J:
    {
        if(!m_gameStarted)
        {
            m_gameStarted = true;
            NewGame();
            break;
        }

    }
    case Qt::Key_P:
    {

        //暂停
        mPaused = !mPaused;
        break;
    }
    case Qt::Key_Escape:
        // 弹出消息框
        QMessageBox::StandardButton btn = QMessageBox::question(
            this, tr("确认退出"), tr("确认要退出游戏吗？"),
            QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);

        if (btn == QMessageBox::Yes) {
            qApp->quit(); // 关闭整个应用程序
        }
        else if (btn == QMessageBox::No) {
            // 设置焦点回到游戏窗口
            setFocus();
            mPaused = !mPaused;

        }
        break;
    }
    mCurItem.Move(x, y);

    if (HitSide() || HitBottom())
    {
        mCurItem.Move(-x, -y);
    }
}

void GameArea2::paintEvent(QPaintEvent *)
{
    //绘制左侧游戏区域
    DrawBKRects();
    DrawFixedRects();
    DrawCurItem();

    //如果暂停了，游戏区中间显示"暂停"大字
    if(mPaused)
    {
        QFont font;
        font.setPixelSize(100);

        QPainter painter(this);
        painter.setFont(font);
        painter.setBrush(Qt::NoBrush);
        painter.setPen(QPen(QColor("#FF3333"), 1));
        painter.drawText(rect(), Qt::AlignCenter, "暂停");
    }

    update();
}

void GameArea2::DrawBKRects()
{
    //画背景边框
    QPainter painter(this);
    painter.setBrush(QColor(Qt::white));
    painter.setPen(Qt::NoPen);

    // 画游戏区域格子边框（虚线）
    painter.setPen(QPen(QColor("#dcdcdc"), 2, Qt::DotLine));
    for (int i = 1; i < MAX_COLUME - 1; i++) {
        for (int j = 1; j < MAX_ROW - 1; j++) {
            painter.drawRect(i * RECT_WIDTH, j * RECT_HEIGHT, RECT_WIDTH, RECT_HEIGHT);
        }
    }
}

void GameArea2::DrawFixedRects()
{
    QPainter painter(this);
    painter.setBrush(QColor("#D3D3D3"));
    painter.setPen(QPen(QColor(Qt::black), 1));
    if(pattern != 4)
    {
        mFixItems.Draw(painter, 0, 0, RECT_WIDTH, RECT_HEIGHT);
    }
}


void GameArea2::DrawCurItem()
{
    QPainter painter(this);
    QRect rect(0, 0, RECT_WIDTH, RECT_HEIGHT);

    // 根据方块类型设置不同的颜色
    QColor fillColor;
    switch (mCurItem.Type()) {
    case 0:
        fillColor = QColor("#00FFFF"); // 青色
        break;
    case 1:
        fillColor = QColor("#0000FF"); // 蓝色
        break;
    case 2:
        fillColor = QColor("#FFA500"); // 橙色
        break;
    case 3:
        fillColor = QColor("#FFFF00"); // 黄色
        break;
    case 4:
        fillColor = QColor("#00FF00"); // 绿色
        break;
    case 5:
        fillColor = QColor("#800080"); // 紫色
        break;
    case 6:
        fillColor = QColor("#FF0000"); // 红色
        break;
    }
    painter.setBrush(fillColor);

    painter.setPen(QPen(QColor(Qt::black), 1));
    mCurItem.Draw(painter, rect.x(), rect.y(), rect.width(), rect.height());
}

void GameArea2::timerEvent(QTimerEvent* e)
{
    if(mPaused)
    {
        return;
    }
    if (e->timerId() == mTimerID)
    {
        mCurItem.Move(0, 1);
        if (HitBottom())
        {
            mCurItem.Move(0, -1);
            AddToFixedRects();
            DeleteFullRows();

            if (HitTop())
            {
                killTimer(mTimerID);
                QMessageBox::information(NULL, "GAME OVER", "GAME OVER", QMessageBox::Yes, QMessageBox::Yes);

                NewGame();
                mPaused = true;
                return;
            }

            mCurItem = mNextItem;
            mCurItem.MoveTo(DEFAULT_X_POS, 1);

            mNextItem.New(QTime::currentTime().msec());
            emit sigUpdateNextItem(mNextItem.Type(), mNextItem.Direction());
        }
    }
}

bool GameArea2::HitSide()
{
    for (QPoint p : mCurItem.Points())
    {
        if (p.x() <= 0 || p.x() >= MAX_COLUME - 1)
        {
            return true;
        }
    }
    return false;
}

bool GameArea2::HitBottom()
{
    for (QPoint p : mCurItem.Points())
    {
        if (p.y() >= MAX_ROW - 1)
        {
            return true;
        }
        if (mFixItems.Contains(p))
        {
            return true;
        }
    }
    return false;
}

bool GameArea2::HitTop()
{
    for (QPoint p : mFixItems.Points())
    {
        if (p.y() <= 1)
        {
            return true;
        }
    }
    return false;
}

void GameArea2::AddToFixedRects()
{
    PointList points = mCurItem.Points();
    mFixItems.AddPoints(points);
}

void GameArea2::DeleteFullRows()
{
    int nRowsDeleted = 0;
    for (int i = 1; i < MAX_ROW - 1; i++)
    {
        int nCount = 0;
        for (int j = 1; j < MAX_COLUME - 1; j++)
        {
            if (mFixItems.Contains(j, i))
            {
                nCount++;
            }
        }
        if (nCount >= MAX_COLUME - 2)
        {
            mFixItems.DeleteRow(i);
            mFixItems.MoveDown(i, 1);	//消除行之上的内容下移一个单位
            nRowsDeleted++;
        }
    }

    //一次元素落下，最多可能消4行
    //一次消除的越多，得分越多
    if (nRowsDeleted == 1)
    {
        mScore += 200;
    }
    else if (nRowsDeleted == 2)
    {
        mScore += 400;
    }
    else if (nRowsDeleted == 3)
    {
        mScore += 600;
        mScore *= 1.5;
    }
    else if (nRowsDeleted == 4)
    {
        mScore += 800;
        mScore *= 2;
    }
    emit sigUpdateScore(mScore);    //更新MainWindow界面得分

    //粗略使用每1000分一关
    if (mScore >= 1000 * mLevel)
    {
        mLevel++;
        if(pattern != 1)
        {
            //随关卡增加下落速度，即把定时器加快
            killTimer(mTimerID);
            mTimerID = startTimer(GetLevelTime(mLevel));
            emit sigUpdateLevel(mLevel);    //更新MainWindow界面关卡
        }


    }
}

int GameArea2::GetLevelTime(int level)
{
    //第1关=1000ms,第2关=900ms 越来越快 第8关=300ms 第10关=100ms
    //关卡>10后，速度不再增加，保持100ms
    if (level > 10)
    {
        return 100;
    }
    if (level > 0)
    {
        return (11 - level) * 100;
    }
}

