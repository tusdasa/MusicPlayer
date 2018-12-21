#include "controlui.h"

ControlUI::ControlUI(QWidget *parent) : QWidget(parent)
{

    // 播放控制
        //播放按钮
        play = new QToolButton;
        //暂停
        pause = new QToolButton;
        //停止
        stop = new QToolButton;
        //下一曲
        next = new QToolButton;
        //上一曲
        before =  new QToolButton;

    // 其他控制
        //进度条
        load = new QSlider;

        //音量控制
        volume = new QDial;

        //按钮风格
        play->setIcon(QIcon(":/img/play.png"));
        pause->setIcon(QIcon(":/img/pause.png"));
        stop->setIcon(QIcon(":/img/stop.png"));
        next->setIcon(QIcon(":/img/next.png"));
        before->setIcon(QIcon(":/img/before.png"));
        //大小
        play->setFixedSize(50,50);
        pause->setFixedSize(50,50);
        stop->setFixedSize(50,50);
        next->setFixedSize(50,50);
        before->setFixedSize(50,50);

        //提示
        play->setStatusTip("Play");
        pause->setStatusTip("Pause");
        stop->setStatusTip("Stop");
        next->setStatusTip("Next");
        before->setStatusTip("Previous");

        //定大小
        volume->setMaximum(100);
        volume->setMinimum(0);
        volume->setFixedSize(50,50);

        //提示
        volume->setStatusTip("Volume");

        //初始化音量
        volume->setValue(80);

        //水平进度条
        load->setOrientation(Qt::Horizontal);
        load->setFixedHeight(20);
        load->setMinimum(0);

        //提示
        load->setStatusTip("Load");

        //打开一个文件
        openOneFile = new QAction();
        openOneFile->setText("opne File");
        openOneFile->setShortcut(QKeySequence::Open);

        //打开一个文件夹
        openOneFolder = new QAction();
        openOneFolder->setText("open Folder");

        //删除一个文件
        delOneFile = new QAction();
        delOneFile->setText("Delete");

        //清理播放列表
        clearPlayList = new QAction();
        clearPlayList->setText("ClearList");

        //关于
        about = new QAction();
        about->setIcon(QIcon(":/img/bix.png"));
        about->setText("about");

        //状态栏
        status = new QStatusBar;
        status->setStatusTip("Ready..");
        status->showMessage("Ready");
        status->activateWindow();
}
