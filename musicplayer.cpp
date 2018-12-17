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

    //打开文件
    connect(cui->openOneFile,SIGNAL(triggered(bool)),this,SLOT(openOneFileFunction()));
    //打开文件夹
    connect(cui->openOneFolder,SIGNAL(triggered(bool)),this,SLOT(openOneFolderFunction()));
    //播放
    connect(cui->play,SIGNAL(clicked(bool)),this,SLOT(playMusic()));
    //
    connect(cui->pause,SIGNAL(clicked(bool)),this,SLOT(puseMusic()));
    //
    connect(cui->stop,SIGNAL(clicked(bool)),this,SLOT(stopMusic()));
    //
    connect(cui->next,SIGNAL(clicked(bool)),this,SLOT(nextMusic()));
    //
    connect(cui->before,SIGNAL(clicked(bool)),this,SLOT(beforeMusic()));
    //
    connect(cui->volume,SIGNAL(valueChanged(int)),this,SLOT(changeVolume()));
    //
    connect(player,SIGNAL(audioAvailableChanged(bool)),this,SLOT(setLoadMaxValue()));
    //
    connect(player,SIGNAL(positionChanged(qint64)),this,SLOT(changeLoad()));
    //
    connect(cui->load,SIGNAL(sliderReleased()),this,SLOT(setMusicPosition()));
}

MusicPlayer::~MusicPlayer()
{

}

void MusicPlayer::createMenuBar(){
     file = this->menuBar()->addMenu(tr("&File"));
     edit = this->menuBar()->addMenu(tr("&Edit"));
     view = this->menuBar()->addMenu(tr("&View"));
     help =  this->menuBar()->addMenu(tr("&Help"));

     file->addAction(cui->openOneFile);
     file->addAction(cui->openOneFolder);
}

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

void MusicPlayer::createStatusBar(){
    this->setStatusBar(cui->status);
}

void MusicPlayer::openOneFileFunction(){
    QString fileName = QFileDialog::getOpenFileName(this,QString("open a file"),"/","*.mp3");
    player->setMedia(QUrl::fromLocalFile(fileName));
    player->setVolume(80);
}
void MusicPlayer::openOneFolderFunction(){

}
void MusicPlayer::puseMusic(){
    player->pause();
}
void MusicPlayer::playMusic(){
    player->play();
}
void MusicPlayer::stopMusic(){
    player->stop();
    cui->load->setValue(0);
}
void MusicPlayer::nextMusic(){
    cui->load->setValue(0);
}
void MusicPlayer::beforeMusic(){
    cui->load->setValue(0);

}
void MusicPlayer::changeVolume(){
    player->setVolume(cui->volume->value());
}
void MusicPlayer::changeLoad(){
    qDebug() << "position" << player->position();
    cui->load->setValue(player->position());
    qDebug() << "value" <<cui->load->value();
    qDebug() << "duration" << player->duration();
    if(cui->load->value()==player->duration()){
        cui->load->setValue(0);
    }
}

void MusicPlayer::setLoadMaxValue(){
    cui->load->setMaximum(player->duration());
}

void MusicPlayer::setMusicPosition(){
    player->setPosition(cui->load->value());
}

