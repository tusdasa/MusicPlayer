#include "musicplayer.h"

MusicPlayer::MusicPlayer(QWidget *parent)
    : QMainWindow(parent)
{
    //窗体
    this->setWindowIcon(QIcon(":/img/ico.png"));
    //禁用右键
    this->setContextMenuPolicy(Qt::NoContextMenu);
    //窗体大小
    this->setFixedSize(750,600);

    //控制UI组件
    cui = new ControlUI();
    tui = new CenterUI();
    player = new QMediaPlayer(this);
    this->setCentralWidget(tui);

    createMenuBar();
    createToolBar();
    createStatusBar();

    //播放队列数据模型
    mo = new QStringListModel();

    //打开文件
    connect(cui->openOneFile,SIGNAL(triggered(bool)),this,SLOT(openOneFileFunction()));
    //打开文件夹
    connect(cui->openOneFolder,SIGNAL(triggered(bool)),this,SLOT(openOneFolderFunction()));
    //播放
    connect(cui->play,SIGNAL(clicked(bool)),this,SLOT(playMusic()));
    //暂停
    connect(cui->pause,SIGNAL(clicked(bool)),this,SLOT(puseMusic()));
    //停止
    connect(cui->stop,SIGNAL(clicked(bool)),this,SLOT(stopMusic()));
    //下一首
    connect(cui->next,SIGNAL(clicked(bool)),this,SLOT(nextMusic()));
    //上一首
    connect(cui->before,SIGNAL(clicked(bool)),this,SLOT(beforeMusic()));
    //改变音量大小
    connect(cui->volume,SIGNAL(valueChanged(int)),this,SLOT(changeVolume()));
    //设置进度条
    connect(player,SIGNAL(durationChanged(qint64)),this,SLOT(setLoadMaxValue()));
    //进度条移动通知
    connect(player,SIGNAL(positionChanged(qint64)),this,SLOT(changeLoad()));
    //快进
    connect(cui->load,SIGNAL(sliderReleased()),this,SLOT(setMusicPosition()));
    //删除文件
    //connect(cui->delOneFile,SIGNAL(triggered(bool)),this,SLOT());
    //清理播放列表
    connect(cui->clearPlayList,SIGNAL(triggered(bool)),this,SLOT(clearMusicList()));
    //错误处理
    connect(player,SIGNAL(error(QMediaPlayer::Error)),this,SLOT(handleMusicPlayError()));
    //动画
    connect(player,SIGNAL(positionChanged(qint64)),tui,SLOT(chengeImageView()));
    //
    connect(player,SIGNAL(positionChanged(qint64)),this,SLOT(playNextOneMusic(qint64)));
    //关于
    connect(cui->about,SIGNAL(triggered(bool)),this,SLOT(about()));
}

MusicPlayer::~MusicPlayer()
{

}
//创建菜单栏
void MusicPlayer::createMenuBar(){
     file = this->menuBar()->addMenu(tr("&File"));
     edit = this->menuBar()->addMenu(tr("&Edit"));
     view = this->menuBar()->addMenu(tr("&View"));
     help =  this->menuBar()->addMenu(tr("&Help"));
     //打开文件
     file->addAction(cui->openOneFile);
     //打开一个文件夹
     file->addAction(cui->openOneFolder);

     //删除一个文件
     edit->addAction(cui->delOneFile);
     //清理播放列表
     edit->addAction(cui->clearPlayList);

     //关于
     help->addAction(cui->about);
}
//创建工具栏
void MusicPlayer::createToolBar(){
       QToolBar * playctrl = new QToolBar(this);
       playctrl->addWidget(cui->play);
       playctrl->addWidget(cui->pause);
       playctrl->addWidget(cui->stop);
       playctrl->addWidget(cui->next);
       playctrl->addWidget(cui->before);
       this->addToolBar(Qt::TopToolBarArea,playctrl);


       QToolBar * volumectrl = new QToolBar(this);
       volumectrl->addWidget(cui->volume);
       this->addToolBar(Qt::TopToolBarArea,volumectrl);

       QToolBar * loadctrl = new QToolBar(this);
       loadctrl->addWidget(cui->load);
       this->addToolBar(Qt::TopToolBarArea,loadctrl);
}
//创建状态栏
void MusicPlayer::createStatusBar(){
    this->setStatusBar(cui->status);
}
//打开单个文件
void MusicPlayer::openOneFileFunction(){
    QString fileName = QFileDialog::getOpenFileName(this,QString("open a file"),"/","*.mp3");

    if(fileName!=NULL){
        MusicFile mf;
        QFileInfo file(fileName);
        mf.setFilename(file.fileName());
        mf.setFilenumber(1);
        mf.setFilepath(file.absoluteFilePath());
        playlist << mf;
        player->setMedia(QUrl::fromLocalFile(mf.getFilepath()));
        sl.clear();
        for(int i=0;i<playlist.length();i++){
            MusicFile mf1 = playlist.at(i);
            sl << mf1.getFilename();
            qDebug() << "mf1 << " << mf1.getFilename();
        }
        mo->setStringList(sl);
        tui->list->setModel(mo);
        tui->songname->setText(mf.getFilename());
        qDebug() << player->metaData("Title");

        player->play();
        qDebug() << player->currentMedia().canonicalResource().mimeType();
        player->setVolume(80);
    }

    qDebug() << fileName;

}
//打开多个文件
void MusicPlayer::openOneFolderFunction(){
    //拓展名控制
    QStringList ext ;
    ext << "mp3";
    QString folderName = QFileDialog::getExistingDirectory(this,"open a dir","/");
    if(folderName!=NULL){
        QDir dir(folderName);
        qDebug() << dir.absolutePath();
        int j=1;
        foreach (QFileInfo info, dir.entryInfoList()) {
            if(info.isFile()){
                for(int i=0;i<ext.length();i++){
                    //拓展名控制
                    if(info.suffix()==ext[i]){
                            MusicFile mf;
                            mf.setFilenumber(j);
                            qDebug() << j;
                            mf.setFilepath(info.absoluteFilePath());
                            qDebug() << info.absoluteFilePath();
                            mf.setFilename(info.fileName());
                            qDebug() << info.fileName();
                            playlist << mf;
                            j++;
                    }
                }
            }
        }


        for(int i=0;i<playlist.length();i++){
            MusicFile mf1 = playlist.at(i);
            sl << mf1.getFilename();
            qDebug() << "mf1 << " <<mf1.getFilename();
        }
        mo->setStringList(sl);
        tui->list->setModel(mo);
        MusicFile mf1 = playlist.at(0);
        if(mf1.getMediaContent()!=NULL){
            player->setMedia(mf1.getMediaContent());
            tui->songname->setText(mf1.getFilename());
            player->play();
        }


    }
}
//暂停播放
void MusicPlayer::puseMusic(){
    if(player->state()==QMediaPlayer::PausedState){
        player->play();
    }else{
        player->pause();
    }

    qDebug() << "state:" <<player->state();


}
//播放音乐
void MusicPlayer::playMusic(){
    if(player->state()==QMediaPlayer::PlayingState){
        player->pause();
    }else {
        player->play();
    }

}
//暂停播放
void MusicPlayer::stopMusic(){
    player->stop();
    cui->load->setValue(0);
    tui->resetImageView();
    update();
    update();
}
//下一曲
void MusicPlayer::nextMusic(){

    if(playlist.length()==0){
        tui->songname->setText("Nothing");
    }
    if(playlist.length()>=count+1){
        count+=1;
        MusicFile mf = playlist.at(count);
        player->stop();
        player->setMedia(mf.getMediaContent());
        tui->songname->setText(mf.getFilename());
        player->play();
        cui->load->setValue(0);
    }
    qDebug() << "nextMusic()" << "playlistLength" << playlist.length();


}
//上一曲
void MusicPlayer::beforeMusic(){

    if(playlist.length()==0){
        tui->songname->setText("Nothing");
    }
    qDebug() << "beforeMusic1" <<count;
    if(count>0){
        count-=1;
    qDebug() << "beforeMusic2" <<count;
        if(playlist.length()>=count){
    qDebug() << "beforeMusic3" <<count;
            player->stop();
            MusicFile mf = playlist.at(count);
            player->setMedia(mf.getMediaContent());
            tui->songname->setText(mf.getFilename());
            player->play();
            cui->load->setValue(0);
        }
    }

    if(count==0){
        if(playlist.length()>count){
            player->stop();
            MusicFile mf = playlist.at(count);
            player->setMedia(mf.getMediaContent());
            tui->songname->setText(mf.getFilename());
            player->play();
            cui->load->setValue(0);
        }
    }
    qDebug() << "beforeMusic()" << "playlistLength" << playlist.length();

}
//改变音量
void MusicPlayer::changeVolume(){
    player->setVolume(cui->volume->value());
}
//改变进度条位置
void MusicPlayer::changeLoad(){
    long l = player->position()/1000;
    int temp = (int) l;
    qDebug() << "position" << temp;
    cui->load->setValue(temp);
    qDebug() << "value" << cui->load->value();
    if(cui->load->value()==((int)(player->duration()/1000))){
        cui->load->setValue(0);
    }
    qDebug() << "duration" << ((int)(player->duration()/1000));
}
//设置总进度
void MusicPlayer::setLoadMaxValue(){
    if(player->isAudioAvailable()){
        long a = player->duration()/1000;
        int tmep = (int) a;
        cui->load->setMaximum(tmep);
    }

}
//设置音乐播放进度
void MusicPlayer::setMusicPosition(){
    if(player->isAudioAvailable()){
        qint64 temp = (long)(cui->load->value())*1000;
       player->setPosition(temp);
    }
}
//清理播放列表
void MusicPlayer::clearMusicList(){
    player->stop();
    //player->deleteLater();
    playlist.clear();
    tui->songname->setText("Waiting you..");
    sl.clear();
    mo->setStringList(sl);
    //tui->resetImageView();
    tui->resetImageView();
    update();
    update();
}
//删除文件
void MusicPlayer::delMusicFile(){
    //TODO
}
//错误处理
void MusicPlayer::handleMusicPlayError(){
    this->stopMusic();
    tui->songname->setText("Error occurred");
    if(player->error()==QMediaPlayer::ResourceError){
        QMessageBox::warning(this,"ERROR","ResourceError",QMessageBox::Ok);
    }
    if(player->error()==QMediaPlayer::FormatError){
        QMessageBox::warning(this,"ERROR","FormatError",QMessageBox::Ok);
    }
    if(player->error()==QMediaPlayer::AccessDeniedError){
        QMessageBox::warning(this,"ERROR","AccessDeniedError",QMessageBox::Ok);
    }
    if(player->error()==QMediaPlayer::ServiceMissingError){
        QMessageBox::warning(this,"ERROR","ServiceMissingError",QMessageBox::Ok);
    }
    if(player->error()==QMediaPlayer::NetworkError){
        QMessageBox::warning(this,"ERROR","NetworkError",QMessageBox::Ok);
    }
}
//自动下一曲
void MusicPlayer::playNextOneMusic(qint64 pox){
     //qDebug() << " playNextOneMusic " << pox;
     //qDebug() << " playNextOneMusic " << player->duration();
    if(pox>0 && player->duration()>0){
        if(pox==player->duration()){
                if(playlist.length()>count+1){
                    count++;
                    MusicFile mf = playlist.at(count);
                    player->setMedia(mf.getMediaContent());
                    tui->songname->setText(mf.getFilename());
                    player->play();
                }
    }
   }
}
//关于
void MusicPlayer::about(){
    QMessageBox::about(this,"About","This software is based on Qt, thanks to Qt's open source spirit. Has been carefully guided by the teacher. And the enthusiastic help of classmates.");
}


