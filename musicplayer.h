#ifndef MUSICPLAYER_H
#define MUSICPLAYER_H

#include <QMainWindow>
#include <QMenuBar>
#include <QToolBar>
#include <QMenu>
#include <QMediaPlayer>
#include <QFileDialog>
#include "controlui.h"
#include "centerui.h"
class MusicPlayer : public QMainWindow
{
    Q_OBJECT

public:
    MusicPlayer(QWidget *parent = 0);
    ~MusicPlayer();
    void createToolBar();
    void createMenuBar();
    void createStatusBar();
    //UI
    ControlUI * cui;

    //中心组件
    CenterUI * tui;

    //菜单
    QMenu *file;
    QMenu *edit;
    QMenu *view;
    QMenu *help;

    //播放器
    QMediaPlayer *player;

public slots:
    //打开文件夹
    void openOneFileFunction();
    //打开文件夹
    void openOneFolderFunction();
    //播放
    void playMusic();
    //暂停
    void puseMusic();
    //停止
    void stopMusic();
    //下一曲
    void nextMusic();
    //上一曲
    void beforeMusic();
    //改变音量
    void changeVolume();
    //改变进度条
    void changeLoad();
    //设置进度条的最大值
    void setLoadMaxValue();
    //设置音乐位置
    void setMusicPosition();
};

#endif // MUSICPLAYER_H
