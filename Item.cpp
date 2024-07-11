#include "Item.h"
#include <QTime>
#include <QtCore/QRandomGenerator>
Item::Item(ItemType type, ItemDirection directon)//方块类的构造函数
{
    mPosition = QPoint(0, 0);//初始位置为（0，0）
	InitPoints(type, directon);
}

Item::~Item()
{
}

ItemType Item::Type()
{
	return mType;
}

ItemDirection Item::Direction()
{
	return mDirection;
}

PointList Item::Points()
{
	return mPoints;
}

void Item::New(int nRandomFactor)
{
    // 使用 QRandomGenerator 生成随机数
    QRandomGenerator random = QRandomGenerator::securelySeeded();

    // 随机初始化元素类型、方向
    ItemType type = (ItemType)(random.bounded(ItemType_MAX));
    ItemDirection direction = (ItemDirection)(random.bounded(ItemDirection_MAX));
    InitPoints(type, direction);

}

void Item::Load(ItemType type1, ItemDirection direction1, QString text1)
{
    ItemType type = type1;
    ItemDirection direction = direction1;
    InitPoints1(type,direction,text1);
}

void Item::InitPoints1(ItemType type, ItemDirection direction, QString text)
{
    PointList points = TextToPointList(text);
    mPoints.clear();
    for (QPoint pt : points)
    {
        //真实坐标需要加上起始位置mPos
        mPoints.append(mPosition + pt);
    }
    mType = type;
    mDirection = direction;
}
void Item::InitPoints(ItemType type, ItemDirection direction)
{
    //根据元素的类型、方向，初始化对应形状的4个坐标点（在4*4的矩阵中）
    //这里先以4行文本描述坐标点位置，然后再翻译成QPoint列表
    QString text = GetPointPostionText(type, direction);
    PointList points = TextToPointList(text);

	mPoints.clear();
	for (QPoint pt : points)
	{
        //真实坐标需要加上起始位置mPos
        mPoints.append(mPosition + pt);
	}
    mType = type;
    mDirection = direction;
}

QString Item::GetPointPostionText(ItemType type, ItemDirection direction)
{
    QString text;
    switch (type)
    {
    case ItemType_Line:
    {
        if (direction == ItemDirection_Up || direction == ItemDirection_Down)
        {
            //直线型元素第1、3种方向（横向）的坐标点位如下：
            text =
                QString("0 0 0 0/") +
                QString("0 0 0 0/") +
                QString("1 1 1 1/") +
                QString("0 0 0 0/");
        }
        else if (direction == ItemDirection_Left || direction == ItemDirection_Right)
        {
            //直线型元素第2、4种方向（竖向）的坐标点位如下：
            text =
                QString("0 0 1 0/") +
                QString("0 0 1 0/") +
                QString("0 0 1 0/") +
                QString("0 0 1 0/");
        }
        break;
    }
    case ItemType_T:
    {
        if (direction == ItemDirection_Up)
        {
            //T型元素第1种方向的坐标点位如下：
            text =
                QString("0 1 0 0/") +
                QString("1 1 1 0/") +
                QString("0 0 0 0/") +
                QString("0 0 0 0/");
        }
        else if (direction == ItemDirection_Right)
        {
            //T型元素第2种方向的坐标点位如下：
            text =
                QString("0 1 0 0/") +
                QString("0 1 1 0/") +
                QString("0 1 0 0/") +
                QString("0 0 0 0/");
        }
        else if (direction == ItemDirection_Down)
        {
            //T型元素第3种方向的坐标点位如下：
            text =
                QString("0 0 0 0/") +
                QString("1 1 1 0/") +
                QString("0 1 0 0/") +
                QString("0 0 0 0/");
        }
        else if (direction == ItemDirection_Left)
        {
            //T型元素第4种方向的坐标点位如下：
            text =
                QString("0 1 0 0/") +
                QString("1 1 0 0/") +
                QString("0 1 0 0/") +
                QString("0 0 0 0/");
        }
        break;
    }
    case ItemType_L1:
    {
        if (direction == ItemDirection_Up)
        {
            //L1型元素第1种方向的坐标点位如下：
            text =
                QString("0 1 0 0/") +
                QString("0 1 0 0/") +
                QString("0 1 1 0/") +
                QString("0 0 0 0/");
        }
        else if (direction == ItemDirection_Right)
        {
            //L1型元素第2种方向的坐标点位如下：
            text =
                QString("0 0 0 0/") +
                QString("0 1 1 1/") +
                QString("0 1 0 0/") +
                QString("0 0 0 0/");
        }
        else if (direction == ItemDirection_Down)
        {
            //L1型元素第3种方向的坐标点位如下：
            text =
                QString("0 0 0 0/") +
                QString("0 1 1 0/") +
                QString("0 0 1 0/") +
                QString("0 0 1 0/");
        }
        else if (direction == ItemDirection_Left)
        {
            //L1型元素第4种方向的坐标点位如下：
            text =
                QString("0 0 0 0/") +
                QString("0 0 1 0/") +
                QString("1 1 1 0/") +
                QString("0 0 0 0/");
        }
        break;
    }
    case ItemType_L2:
    {
        if (direction == ItemDirection_Up)
        {
            //L2型元素第1种方向的坐标点位如下：
            text =
                QString("0 0 1 0/") +
                QString("0 0 1 0/") +
                QString("0 1 1 0/") +
                QString("0 0 0 0/");
        }
        else if (direction == ItemDirection_Right)
        {
            //L2型元素第2种方向的坐标点位如下：
            text =
                QString("0 0 0 0/") +
                QString("0 1 0 0/") +
                QString("0 1 1 1/") +
                QString("0 0 0 0/");
        }
        else if (direction == ItemDirection_Down)
        {
            //L2型元素第3种方向的坐标点位如下：
            text =
                QString("0 0 0 0/") +
                QString("0 1 1 0/") +
                QString("0 1 0 0/") +
                QString("0 1 0 0/");
        }
        else if (direction == ItemDirection_Left)
        {
            //L2型元素第4种方向的坐标点位如下：
            text =
                QString("0 0 0 0/") +
                QString("1 1 1 0/") +
                QString("0 0 1 0/") +
                QString("0 0 0 0/");
        }
        break;
    }
    case ItemType_Square:
    {
        //田字型元素只有一种坐标：
        text =
            QString("1 1 0 0/") +
            QString("1 1 0 0/") +
            QString("0 0 0 0/") +
            QString("0 0 0 0/");
        break;
    }
    case ItemType_Z:
    {
        if (direction == ItemDirection_Up)
        {
            //Z型元素第1种方向的坐标点位如下：
            text =
                QString("0 1 0 0/") +
                QString("0 1 1 0/") +
                QString("0 0 1 0/") +
                QString("0 0 0 0/");
        }
        else if (direction == ItemDirection_Right)
        {
            //Z型元素第2种方向的坐标点位如下：
            text =
                QString("0 0 0 0/") +
                QString("0 1 1 0/") +
                QString("1 1 0 0/") +
                QString("0 0 0 0/");
        }
        else if (direction == ItemDirection_Down)
        {
            //Z型元素第3种方向的坐标点位如下：
            text =
                QString("0 0 1 0/") +
                QString("0 1 1 0/") +
                QString("0 1 0 0/") +
                QString("0 0 0 0/");
        }
        else if (direction == ItemDirection_Left)
        {
            //Z型元素第4种方向的坐标点位如下：
            text =
                QString("0 0 0 0/") +
                QString("1 1 0 0/") +
                QString("0 1 1 0/") +
                QString("0 0 0 0/");
        }
        break;
    }
    default:
        break;
    }
    return text;
}

void Item::ClearPoints()
{
	mPoints.clear();
}

void Item::ChangeDirection(int nDirection)
{
    ItemDirection newDirection = (ItemDirection)((mDirection + nDirection) % ItemDirection_MAX);
    //当前方向+1，并保证不超出方向总大小
    InitPoints(mType, newDirection);//初始化方块
}

void Item::Draw(QPainter& painter, int nStartX, int nStartY, int nWidth, int nHeight)
{
	for (int i = 0; i < mPoints.size(); i++)
	{
		QPoint pt = mPoints[i];
		painter.drawRect(QRect(nStartX + pt.x() * nWidth, nStartY + pt.y() * nHeight, nWidth, nHeight));
    }
}
//对于每个坐标点，如果它不在元素的坐标点列表中，就添加到mPoints的底部
//就是把当前方块添加到固定方块上
void Item::AddPoints(const PointList& points)
{
	for (int i = 0; i < points.size(); i++)
	{
		if (!mPoints.contains(points[i]))
		{
			mPoints.append(points[i]);
		}
	}
}
//判断指定的点是否在元素的坐标点列表中。
bool Item::Contains(QPoint& point)
{
	return mPoints.contains(point);
}

bool Item::Contains(int x, int y)
{
	QPoint point(x, y);
	return mPoints.contains(point);
}

void Item::Move(int x, int y)
{
	for (int i = 0; i < mPoints.size(); i++)
	{
		int x1 = mPoints[i].x() + x;
		int y1 = mPoints[i].y() + y;
		mPoints[i].setX(x1);
		mPoints[i].setY(y1);
	}
	mPosition += QPoint(x, y);
}

void Item::MoveTo(int x, int y)
{
	for (int i = 0; i < mPoints.size(); i++)
	{
		int x1 = mPoints[i].x() - mPosition.x() + x;
		int y1 = mPoints[i].y() - mPosition.y() + y;
		mPoints[i].setX(x1);
		mPoints[i].setY(y1);
	}
	mPosition = QPoint(x, y);
}

void Item::DeleteRow(int y)
{
	PointList newPoints;
	for (int i = 0; i < mPoints.size(); i++)
	{
		if (mPoints[i].y() != y)
		{
			newPoints.append(mPoints[i]);
		}
	}
	mPoints = newPoints;
}

PointList Item::TextToPointList(QString strFormat)
{
	PointList points;
	QStringList rows = strFormat.split('/');			//先以斜杠拆分为4行
	for (int i = 0; i < rows.size(); i++)
	{
		QString strRowText = rows.at(i);
		QStringList columns = strRowText.split(' ');  //每行内容又以空格拆分为4列
		for (int j = 0; j < columns.size(); j++)
		{
			if (columns.at(j) == "1")
			{
				points.append(QPoint(i, j));
			}
		}
	}
	return points;
}

void Item::MoveDown(int nRow, int y)
{
	for (int i = 0; i < mPoints.size(); i++)
	{
		if (mPoints[i].y() < nRow)
		{
			mPoints[i].setY(mPoints[i].y() + y);
		}
	}
}

void Item::AddNew()
{

}

void Item::setmType(ItemType type)
{
    mType = type;
}
