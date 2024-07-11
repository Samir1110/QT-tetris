#include "mainwindow.h"
#include "ui_mainwindow.h"

#include<QResource>
#include<QDir>
#include<QFileDialog>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
    setFixedSize(1500, 1080);
    setWindowTitle("俄罗斯方块");

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
	//widgetGameArea 和 widgetNextArea 已在界面设计器内由普通QWidget分别提升成GameArea和NextArea
	//GameArea: 左侧游戏区域，自绘widget
	//NextArea: 右侧显示下个item的widget，也是自绘widget
	//游戏主运行逻辑在GameArea内，不过按键消息因为是MainWindow接受，通过ui->widgetGameArea->KeyPressed()函数调用传递下去
	//GameArea通过信号sigUpdateScore、sigUpdateLevel 通知MainWindow更新界面的得分和关卡
    //GameArea通过信号sigUpdateNextItem 通知 NextArea 刷新下一个元素
    connect(ui->gameArea, &GameArea::sigUpdateScore, this, &MainWindow::slotUpdateScore);
    connect(ui->gameArea, &GameArea::sigUpdateLevel, this, &MainWindow::slotUpdateLevel);
    connect(ui->gameArea, &GameArea::sigUpdateNextItem, ui->widgetNextArea, &NextArea::slotUpdateNextItem);
    //ui->gameArea->updateMyname("susu");
    // 连接信号和槽
    player->setMedia(QUrl::fromLocalFile("D:\\C++\\qt1\\Tetris\\music\\1.mp3"));
    player->setVolume(50);
    //        player->setPlaylist(playlist);
    // 播放音乐文件
    player->play();

}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *e)
{
    ui->gameArea->KeyPressed(e->key());
    QMainWindow::keyPressEvent(e);
}


void MainWindow::slotUpdateScore(int nScore)
{
	ui->labelScore->setText(QString::number(nScore));
}

void MainWindow::slotUpdateLevel(int nSpeed)
{
	ui->labelSpeed->setText(QString::number(nSpeed));
}
//connect(startButton, &QPushButton::clicked, board, &GameArea::start);

void MainWindow::on_pushButton_clicked()
{
    if(!ui->gameArea->m_gameStarted)
    {
        ui->gameArea->m_gameStarted = true;
        ui->gameArea->NewGame();
    }

}

void MainWindow::on_pushButton_3_clicked()
{
    ui->gameArea->loadGame();
}


void MainWindow::on_pushButton_2_clicked()
{
    ui->gameArea->saveOneUser(ui->gameArea->lastGame);
}
//在游戏画面一出现时就自动更新游戏
void MainWindow::setGameBefore()
{
    ui->gameArea->setGame();
    QString temp = ui->gameArea->name;
    QString labelText = QString("欢迎你：%1").arg(temp);
    ui->label_5->setText(labelText);
}

void MainWindow::on_pushButton_4_clicked()
{
    ui->gameArea->saveUserGameHistory();
}

void MainWindow::on_playButton__clicked()
{
    ui->gameArea->setPause();
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
void MainWindow::on_pushButton_5_clicked()
{
    this->close();
    last->show();
}


void MainWindow::on_pauseButton__clicked()
{
    player->pause();
}

