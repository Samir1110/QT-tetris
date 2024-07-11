#include "NextArea.h"

NextArea::NextArea(QWidget *parent) : QWidget(parent)
{
}

void NextArea::paintEvent(QPaintEvent *)
{
	QPainter painter(this);
    //painter.setBrush(QColor("#FFDEAD"));
	painter.setPen(QPen(QColor(Qt::black), 1));
    QColor fillColor;
	int xStart = 80;    //为了绘制在显示下一个方块区域的中部
	int yStart = 10;
    int w = 20;//小方块的像素20*20
	int h = 20;
	for(QPoint pt : mItem.Points())
	{
        int x = xStart + pt.x() * w;
        int y = yStart + pt.y() * h;

        switch (mItem.Type()) {
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
        painter.drawRect(x, y, w, h);

	}

	update();
}

void NextArea::slotUpdateNextItem(ItemType type, ItemDirection direction)
{
	mItem.InitPoints(type, direction);
}
