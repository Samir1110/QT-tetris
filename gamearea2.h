#ifndef GameArea2_H
#define GameArea2_H

#include "Item.h"
#include <QWidget>
#include<iterator>
class GameArea2 : public QWidget
{
    Q_OBJECT
public:
    explicit GameArea2(QWidget *parent = nullptr);

    void DrawBKRects();         //用作背景的方块
    void DrawFixedRects();      //下落后已固定不动的方块
    void DrawCurItem();         //当前下落中的方块

    bool IsGameStarted() const;
    void NewGame();
    void KeyPressed(int key);

    bool HitSide();             //判断当前下落方块是否超左右边界
    bool HitBottom();           //判断当前下落方块是否达到底部
    bool HitTop();              //判断当前下落方块是否达到顶部
    void AddToFixedRects();     //把当前方块加入到 固定方块
    void DeleteFullRows();      //删除完整的行
    int GetLevelTime(int level);   //获取不同等级关卡对应的定时器时间，关卡越高，时间越快(短)。比如1关=1s,2关=900ms,3关=800ms
    bool m_gameStarted;
    bool LoadGame;

    //获取信息
    QString name;
    void updateMyname(QString _name);
    QString lastGame = "D:\\C++\\qt1\\Tetris\\lastGame.txt";
signals:
    void sigUpdateNextItem(ItemType type, ItemDirection direction);
    void sigUpdateScore(int nScore);
    void sigUpdateLevel(int nSpeed);
    void sigPause(bool bPaused);

protected:

    void paintEvent(QPaintEvent *) override;
    void timerEvent(QTimerEvent*) override;

private:
    Item mFixItems;     //已落下、固定住了的方块们
    Item mCurItem;      //当前移动中的方块
    Item mNextItem;     //下一个方块

    int mTimerID;       //定时器ID
    int mScore;         //得分
    int mLevel;         //关卡
    bool mPaused;       //是否暂停
};

#endif
