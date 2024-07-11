#include "GameArea.h"
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
int MAX_COLUME = mAX_COLUMN;//列
int MAX_ROW	= mAX_ROW;//行
int pattern;//游戏模式
int keyPlace;//键盘模式
int keyboard[8];//8个键盘信号
int blockPattern;//方块模式
int RECT_WIDTH;//方块宽
int RECT_HEIGHT;//方块高
//默认出生点水平中心处
int  DEFAULT_X_POS = ((MAX_COLUME-2) / 2 -1);

void GameArea::setGame()
{
    QFile file("D:\\C++\\qt1\\Tetris\\setGame.txt");
    QTextStream in(&file);

    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "设置文件无法打开";
        return;
    }
    else
    {
        //文件顺序：玩家姓名，游戏界面列，游戏界面行，游戏模式，方块下落速度，键盘设置
        //pattern:1,自定义速度，2，普通、3，双人 4、隐形
        QString data = in.readAll();
        MyInput input(data);
        QString _name;
        _name = input.GetInput(0);
        updateMyname(_name);
        qDebug()<<name;
        MAX_COLUME = input.GetInput(1).toInt();
        MAX_ROW = input.GetInput(2).toInt();
        pattern = input.GetInput(3).toInt();
        keyPlace = input.GetInput(5).toInt();
        blockPattern = input.GetInput(6).toInt();
        if(pattern == 3)
        {
            RECT_WIDTH = 700/MAX_COLUME;
            RECT_HEIGHT = 700/mAX_ROW;
        }
        else
        {
            RECT_WIDTH = 800/MAX_COLUME;
            RECT_HEIGHT = 800/MAX_COLUME;
        }

        mScore  = 0;
        if(pattern  == 1)
        {
            mLevel = input.GetInput(4).toInt();
        }
        else
        {
            mLevel = 1;
        }
    }
    file.close();
    setKey();
    emit sigUpdateScore(mScore);    //更新MainWindow界面得分
    emit sigUpdateLevel(mLevel);    //更新MainWindow界面关卡

}
void GameArea::setKey()
{
    //键盘事件
    QString filePath = "D:\\C++\\qt1\\Tetris\\key.txt"; // 文件路径
    QFile file2(filePath); // 创建 QFile 对象
    if (!file2.open(QIODevice::ReadOnly | QIODevice::Text )) {
        qWarning("Failed to open file.");
    }
    QTextStream in2(&file2); // 创建 QTextStream 对象
    QString line = in2.readLine(); // 读取一行数据

    // 根据逗号分隔字符串，获取需要修改的值
    QStringList dataList = line.split(",");
    for (int i = 0; i < dataList.size(); ++i) {
        if (!dataList[i].trimmed().isEmpty()) {
            keyboard[i] = dataList[i].at(0).unicode();

        }
        qDebug()<<dataList[i];
        qDebug()<<keyboard[i];
    }
    file2.close();
}
GameArea::GameArea(QWidget *parent) : QWidget(parent)
{
//    this->setStyleSheet("background-color: transparent;");
//    this->setAttribute(Qt::WA_TranslucentBackground);
    mScore = 0;
    mLevel = 1;
    mPaused = false;
    m_gameStarted = false;
    LoadGame = false;
	setMinimumSize(MAX_COLUME*RECT_WIDTH, MAX_ROW*RECT_HEIGHT);
}

// 在 gameArea 的实现文件源文件中更新 myString 变量的值
void GameArea::updateMyname(QString _name) {
    name = _name;
}

bool GameArea::IsGameStarted() const
{
    return m_gameStarted;
}

void GameArea::NewGame()
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
void GameArea::keyPressed1(int key)
{
    int x = 0;
    int y = 0;
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
void GameArea::KeyPressed2(int key)
{
    int x = 0;
    int y = 0;
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
    case Qt::Key_Shift:
    {
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
    case Qt::Key_0:
    {
            //暂停
            mPaused = !mPaused;
            break;
    }
    }
    mCurItem.Move(x, y);

    if (HitSide() || HitBottom())
    {
            mCurItem.Move(-x, -y);
    }
}
void GameArea::KeyPressed(int key)
{
	int x = 0;
    int y = 0;

    Qt::Key key0 = static_cast<Qt::Key>(keyboard[0]);
    Qt::Key key1 = static_cast<Qt::Key>(keyboard[1]);
    Qt::Key key2 = static_cast<Qt::Key>(keyboard[2]);
    Qt::Key key3 = static_cast<Qt::Key>(keyboard[3]);
    Qt::Key key4 = static_cast<Qt::Key>(keyboard[4]);
    Qt::Key key5 = static_cast<Qt::Key>(keyboard[5]);
    Qt::Key key6 = static_cast<Qt::Key>(keyboard[6]);
    Qt::Key key7 = static_cast<Qt::Key>(keyboard[7]);

    if(key == key0 || key == Qt::Key_Left)
    {
        x = -1;
    }
    else if(key == key1 || key == Qt::Key_Right)
    {
        x = 1;

    }
    else if(key == key2 || key == Qt:: Key_Up)
    {
        if(ChangeDirection())
        {
            mCurItem.ChangeDirection(1);
        }
        if(HitSide() || HitBottom())
        {
            mCurItem.ChangeDirection(-1);
        }
    }
    else if(key == key3 || key == Qt::Key_Down)
    {
        y = 1;
    }
    else if(key == key4 || key == Qt::Key_Space)
    {
        while (1)
        {
            mCurItem.Move(0, 1);
            if (HitSide() || HitBottom())
            {
                mCurItem.Move(0, -1);
                break;
            }
        }
    }
    else if(key == key5)
    {
        if(!m_gameStarted)
        {
            m_gameStarted = true;
            NewGame();

        }
    }
    else if(key == key6 || key == Qt::Key_Escape)
    {
        //暂停
        mPaused = !mPaused;
    }
    else if(key == key7)
    {
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
    }

	mCurItem.Move(x, y);

	if (HitSide() || HitBottom())
	{
		mCurItem.Move(-x, -y);
	}
}

void GameArea::paintEvent(QPaintEvent *)
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

void GameArea::DrawBKRects()
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

void GameArea::DrawFixedRects()
{
	QPainter painter(this);
	painter.setBrush(QColor("#D3D3D3"));
	painter.setPen(QPen(QColor(Qt::black), 1));
    if(pattern != 4)
    {
        mFixItems.Draw(painter, 0, 0, RECT_WIDTH, RECT_HEIGHT);
    }
}


void GameArea::DrawCurItem()
{
    QPainter painter(this);
    QRect rect(0, 0, RECT_WIDTH, RECT_HEIGHT);

    // 根据方块类型设置不同的颜色
    QColor fillColor;
    if(blockPattern == 1)
    {
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
    }
    else if(blockPattern == 2)
    {
        fillColor = QColor(Qt::red);
    }
    else if(blockPattern == 3)
    {
        fillColor = QColor("#FFD700");

    }
    painter.setBrush(fillColor);

    painter.setPen(QPen(QColor(Qt::black), 1));
    mCurItem.Draw(painter, rect.x(), rect.y(), rect.width(), rect.height());
}

void GameArea::timerEvent(QTimerEvent* e)
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
                if(pattern == 4)
                {
                    killTimer(mTimerID);
                    mPaused = true;
                }
                else
                {
                    killTimer(mTimerID);
                    QMessageBox::information(NULL, "GAME OVER", "GAME OVER", QMessageBox::Yes, QMessageBox::Yes);
                    saveRank();
                    NewGame();
                    mPaused = true;
                    return;
                }

            }

			mCurItem = mNextItem;
			mCurItem.MoveTo(DEFAULT_X_POS, 1);

			mNextItem.New(QTime::currentTime().msec());
			emit sigUpdateNextItem(mNextItem.Type(), mNextItem.Direction());
		}
	}
}

bool GameArea::HitSide()
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

bool GameArea::ChangeDirection()
{
    Item temp = mCurItem;
    temp.ChangeDirection(1);
    for (QPoint p : temp.Points())
    {
        if (p.x() <= 0 || p.x() >= MAX_COLUME - 1)
        {
            return false;
        }
    }
    return true;
}
bool GameArea::HitBottom()
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

bool GameArea::HitTop()
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

void GameArea::AddToFixedRects()
{
	PointList points = mCurItem.Points();
    mFixItems.AddPoints(points);
}

void GameArea::DeleteFullRows()
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

int GameArea::GetLevelTime(int level)
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
void GameArea::setPause()
{
    mPaused = !mPaused;
}
void GameArea::saveRank()
{
    QFile file("D:\\C++\\qt1\\Tetris\\ranking.txt");
    QTextStream out(&file);
    if(!file.open(QIODevice::Append | QIODevice::Text))
    {
        qDebug() << "Can't create file";
        return;
    }
    else
    {
        qDebug()<<"Success!";
        out<< name <<",";
        out<< mScore<<",";
        out << mLevel << ",";
        QDateTime current = QDateTime::currentDateTime();
        QString formatted = current.toString("M/d h:mm");
        out<< formatted<< Qt::endl;
    }
}

void GameArea::saveUserGameHistory()
{
    int count = 1;
    QFile file("D:\\C++\\qt1\\Tetris\\UserGameHistory.txt");

    if (!file.open(QIODevice::ReadWrite | QIODevice::Text)) {
        qDebug() << "没有打开存档文件";
    }
    QTextStream in(&file);
    in.setCodec("UTF-8"); // 指定字符编码为 UTF-8

    while (!in.atEnd()) {
        QString line = in.readLine();
        MyInput input(line);
        if(input.GetInput(0) == name)
        {
            count++;
        }
        qDebug() << line;
    }
    QTextStream out(&file); // 创建一个 QTextStream 用于写入数据
    out.seek(file.size()); // 将文件指针移动到文件末尾
    out << name << "," ; // 向文件中写入数据
    QString result1 = QString("%1%2").arg(name).arg(count);
    out << result1 <<",";
    out << mScore << ",";
    out << mLevel << ",";
    QDateTime current = QDateTime::currentDateTime();
    QString formatted = current.toString("M/d h:mm");
    out<< formatted<< Qt::endl;

    file.close();


    QString fileName = result1;
    QString extension = ".txt";

    fileName.append(extension); // 将扩展名添加到文件名后面

    //创建新文件在用户存档库中
    QString dirPath = "D:\\C++\\qt1\\Tetris\\userGameHistory";
    dirPath.append("\\");
    dirPath.append(fileName);
    qDebug()<<dirPath;

    saveOneUser(dirPath);

}

void GameArea::saveOneUser(QString text)
{
    // 创建文件对象
    QFile fileNew(text);

    // 打开文件
    if (fileNew.open(QIODevice::WriteOnly | QIODevice::Text)) {
        // 打开成功
        qDebug() << "用户存档打开成功";
        QTextStream out(&fileNew); // 创建一个 QTextStream 用于写入数据
        out << mScore << ",";
        out << mLevel << ",";
        //out << mPaused << Qt::endl;

        // 保存已落下、固定住了的方块们
        QString strFormat;
        for (int row = 0; row < mAX_ROW; row++)
        {
            for (int col = 0; col < mAX_COLUMN; col++)
            {
                bool hasItem = false;
                for (QPoint p : mFixItems.Points())
                {
                    if (p.x() == row && p.y() == col)
                    {
                        hasItem = true;
                        break;
                    }
                }
                if (hasItem)
                {
                    strFormat += "1 ";
                }
                else
                {
                    strFormat += "0 ";
                }

            }
            strFormat += "/";		//每行末尾加上一个斜杠
            //qDebug()<<"行增加了,这是行"<<row;
        }
        out<<strFormat<<",";

        // 保存当前移动中的方块
        out<<mCurItem.Type()<<"," <<mCurItem.Direction()<< ","<< mCurItem.GetPointPostionText(mCurItem.Type(), mCurItem.Direction())<<",";


        // 保存下一个方块
        out<<mNextItem.Type()<<"," <<mNextItem.Direction()<< ","<< mNextItem.GetPointPostionText(mNextItem.Type(), mNextItem.Direction())<<",";
        out<<name<<",";
        out<<MAX_COLUME<<",";
        out<<MAX_ROW<<",";
        out<<pattern<<",";
        out<<keyPlace<<",";
        out<<blockPattern<<",";


    }
    else {
        qDebug()<<"存档无法打开";
    }
    fileNew.close();
}
void GameArea::loadGame()
{
    QFile file("D:\\C++\\qt1\\Tetris\\lastGame.txt");
    QTextStream in(&file);

    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Can't open file";
        return;
    }
    else
    {
        qDebug()<<"Success!";
        QString data = in.readAll();
        MyInput input(data);
        // 读取分数、等级、暂停状态
        int score, level;

        score = (input.GetInput(0)).toInt();
        level = (input.GetInput(1)).toInt();
        name = input.GetInput(9);
        MAX_COLUME = input.GetInput(10).toInt();
        MAX_ROW = input.GetInput(11).toInt();
        pattern = input.GetInput(12).toInt();
        keyPlace = input.GetInput(13).toInt();
        blockPattern = input.GetInput(14).toInt();

        mScore = score;
        mLevel = level;
        mPaused = true;
        emit sigUpdateScore(mScore);    //更新MainWindow界面得分
        emit sigUpdateLevel(mLevel);    //更新MainWindow界面关卡

        mFixItems.ClearPoints();
        //读取固定的方块
        QString strFormat;
        strFormat = input.GetInput(2);
        QStringList rows = strFormat.split('/');
        PointList lastGameList;
        for (int row = 0; row < rows.size() && row < mAX_ROW; row++)
        {
            QStringList cols = rows[row].split(' ');
            for (int col = 0; col < cols.size() && col < mAX_COLUMN; col++)
            {
                if (cols[col] == "1")
                {
                    QPoint point(row, col);
                    lastGameList.append(point);
                }
            }
        }
        if (!lastGameList.isEmpty())
        {
            mFixItems.AddPoints(lastGameList);
        }

        // 读取当前移动中的方块
        QString curItemType, curItemDirection, curItemPointPos;
        curItemType = input.GetInput(3);
        curItemDirection = input.GetInput(4);
        curItemPointPos = input.GetInput(5);
        //in >> curItemType >> curItemDirection >> curItemPointPos;
        int curItemType1 = curItemType.toInt();
        ItemType itemType = static_cast<ItemType>(curItemType1);

        int curItemDirection1 =  curItemDirection.toInt();
        ItemDirection itemDirection = static_cast<ItemDirection>(curItemDirection1);

        mCurItem.Load(itemType,itemDirection,curItemPointPos);
        mCurItem.MoveTo(DEFAULT_X_POS, 1);

        // 读取下一个方块
        QString nextItemType, nextItemDirection, nextItemPointPos;
        nextItemType = input.GetInput(6);
        nextItemDirection = input.GetInput(7);
        nextItemPointPos = input.GetInput(8);
        //in >> nextItemType >> nextItemDirection >> nextItemPointPos;
        int nextItemType1 = nextItemType.toInt();
        ItemType itemType2 = static_cast<ItemType>(nextItemType1);

        int nextItemDirection1 =  nextItemDirection.toInt();
        ItemDirection nextDirection = static_cast<ItemDirection>(nextItemDirection1);

        mNextItem.Load(itemType2,nextDirection,nextItemPointPos);

        file.close();

        // 清空屏幕上所有方块，重新添加已落下的方块、当前移动中的方块和下一个方块
        emit sigUpdateNextItem(mNextItem.Type(), mNextItem.Direction());
        mTimerID = startTimer(GetLevelTime(mLevel));
    }
}

