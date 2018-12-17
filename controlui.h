#ifndef CONTROLUI_H
#define CONTROLUI_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QToolButton>
#include <QSlider>
#include <QDial>
#include <QAction>
#include <QFileDialog>
#include <QUrl>
#include <QDir>
#include <QFile>
#include <QDebug>
#include <QFileInfo>
#include <QStatusBar>
class ControlUI : public QWidget
{
    Q_OBJECT
public:
    explicit ControlUI(QWidget *parent = nullptr);
    //播放按钮
       QToolButton *play;
       //暂停
       QToolButton *pause;
       //停止
       QToolButton *stop;
       //下一曲
       QToolButton *next;
       //上一曲
       QToolButton *before;

       //播放进度条
       QSlider *load;

       // 音量控制
       QDial *volume;

       //打开一个文件
       QAction *openOneFile;

       //打开一个文件夹
       QAction *openOneFolder;

       //状态栏
       QStatusBar *status;
signals:

public slots:
};

#endif // CONTROLUI_H
