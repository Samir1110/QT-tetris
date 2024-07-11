#include "mainwindow2.h"
#include "ui_mainwindow2.h"
#include<QKeyEvent>
#include <QFileDialog>
MainWindow2::MainWindow2(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow2)
{
    ui->setupUi(this);
    setWindowTitle("双人模式");
    connect(ui->GameArea1, &GameArea::sigUpdateScore, this, &MainWindow2::slotUpdateScore1);
    connect(ui->GameArea1, &GameArea::sigUpdateLevel, this, &MainWindow2::slotUpdateLevel1);
    connect(ui->GameArea1, &GameArea::sigUpdateNextItem, ui->NextArea1, &NextArea::slotUpdateNextItem);

    connect(ui->GameArea2, &GameArea::sigUpdateScore, this, &MainWindow2::slotUpdateScore2);
    connect(ui->GameArea2, &GameArea::sigUpdateLevel, this, &MainWindow2::slotUpdateLevel2);
    connect(ui->GameArea2, &GameArea::sigUpdateNextItem, ui->NextArea2, &NextArea::slotUpdateNextItem);
    // 连接信号和槽

    QFile file("D:\\C++\\qt1\\Tetris\\backGround.txt"); // 创建 QFile 对象
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) { // 打开文件
        qDebug() << "Failed to open file:" ;

    }
    QTextStream in(&file); // 创建 QTextStream 对象
    QString content = in.readAll(); // 读取所有文本内容
    file.close();
    qDebug()<<content;

    QPixmap pixmap(content); // 加载图片
    QPalette palette;
    palette.setBrush(this->backgroundRole(), QBrush(pixmap.scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation))); // 将背景图片设为QWidget的background
    this->setPalette(palette);
    player->setMedia(QUrl::fromLocalFile("D:\\C++\\qt1\\Tetris\\music\\1.mp3"));
    player->setVolume(50);
    //        player->setPlaylist(playlist);
    // 播放音乐文件
    player->play();
}


void MainWindow2::slotUpdateScore1(int nScore)
{
    ui->labelScore1->setText(QString::number(nScore));
}

void MainWindow2::slotUpdateLevel1(int nSpeed)
{
    ui->labelLevel1->setText(QString::number(nSpeed));
}

void MainWindow2::slotUpdateScore2(int nScore)
{
    ui->labelScore2->setText(QString::number(nScore));
}

void MainWindow2::slotUpdateLevel2(int nSpeed)
{
    ui->labelLevel2->setText(QString::number(nSpeed));
}
//在游戏画面一出现时就自动更新游戏
void MainWindow2::SetGameBefore()
{
    ui->GameArea1->setGame();
    ui->GameArea2->setGame();

}

MainWindow2::~MainWindow2()
{
    delete ui;
}


void MainWindow2::keyPressEvent(QKeyEvent *e)
{
    ui->GameArea1->keyPressed1(e->key());
    QMainWindow::keyPressEvent(e);
    ui->GameArea2->KeyPressed2(e->key());
    QMainWindow::keyPressEvent(e);

}

void MainWindow2::on_pushButton_clicked()
{
    if(!ui->GameArea1->m_gameStarted)
    {
        ui->GameArea1->m_gameStarted = true;
        ui->GameArea1->NewGame();
    }

    if(!ui->GameArea2->m_gameStarted)
    {
        ui->GameArea2->m_gameStarted = true;
        ui->GameArea2->NewGame();
    }

}


void MainWindow2::on_pushButton_2_clicked()
{
    ui->GameArea1->setPause();
    ui->GameArea2->setPause();
}


void MainWindow2::on_pushButton_3_clicked()
{
    this->close();
    last->show();
}


void MainWindow2::on_pushButton_4_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Music File"), "D:\\C++\\qt1\\Tetris\\music\\Savannah Sgro - Moody.mp3", tr("Music Files (*.mp3 *.wav)"));

    if (!fileName.isEmpty()) {

        // 将播放列表设置为媒体播放器的播放列表
        player->setMedia(QUrl::fromLocalFile(fileName));
        player->setVolume(50);
        //        player->setPlaylist(playlist);

        // 播放音乐文件
        player->play();
    }
}


void MainWindow2::on_pushButton_5_clicked()
{
    player->pause();
}

