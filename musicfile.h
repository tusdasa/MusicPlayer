#ifndef MUSICFILE_H
#define MUSICFILE_H
#include <QString>
#include <QPixmap>
#include <QImage>
#include <QMediaContent>
#include <QUrl>
class MusicFile
{
public:
    MusicFile();
    void setFilenumber(int filenumber);
    int getFilenumber();
    void setFilename(QString filename);
    QString getFilename();
    void setFilepath(QString filepath);
    QString getFilepath();
    void setPixs(QImage img);
    QPixmap getPixs();
    QMediaContent getMediaContent();
private:
    int filenumber;
    QString filename;
    QString filepath;
    QPixmap pixs;




};

#endif // MUSICFILE_H
