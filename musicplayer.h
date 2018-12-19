#ifndef MUSICPLAYER_H
#define MUSICPLAYER_H

#include <QMainWindow>
#include <QMenuBar>
#include <QToolBar>
#include <QMenu>
#include <QMediaPlayer>
#include <QFileDialog>
#include <QList>
#include <musicfile.h>
#include <QStringListModel>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QMouseEvent>
#include <QMediaMetaData>
#include <QMessageBox>
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

    int count=0;

    //播放列表

    QList<MusicFile> playlist;

    //视图
    QStringListModel * mo;

    //数据
    QStringList sl;

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
    //删除
    void delMusicFile();
    //清理播放列表
    void clearMusicList();
    //出错处理
    void handleMusicPlayError();
    //当前播放完毕播放下一首
    void playNextOneMusic(qint64 pox);

protected :
    //void mousePressEvent(QMouseEvent *event);
signals:
    updateImage();
};

#endif // MUSICPLAYER_H
