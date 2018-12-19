#include "musicfile.h"

MusicFile::MusicFile()
{
    pixs.load(":/img/fm.png");

}

int MusicFile::getFilenumber(){

    return this->getFilenumber();

}
QString MusicFile::getFilepath(){
    return this->filepath;
}
QPixmap MusicFile::getPixs(){
    QPixmap pix1 = pixs.scaled(300,300,Qt::KeepAspectRatio);
    return pix1;
}
QString MusicFile::getFilename(){
    return this->filename;
}

void MusicFile::setFilename(QString filename){
    this->filename=filename;
}
void MusicFile::setFilepath(QString filepath){
    this->filepath = filepath;
}
void MusicFile::setPixs(QImage img){
    this->pixs=QPixmap::fromImage(img);
}
void MusicFile::setFilenumber(int filenumber){
    this->filenumber=filenumber;
}

QMediaContent MusicFile::getMediaContent(){
    if(this->filepath==NULL){
        return NULL;
    }else{
        QMediaContent media(QUrl::fromLocalFile(this->filepath));
        return media;
    }
}


