#include"startwinodw.h"
#include "mainwindow.h"
#include <QApplication>
//#include<QMediaPlaylist>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
    startwinodw window1;
    window1.show();
	return a.exec();
}
