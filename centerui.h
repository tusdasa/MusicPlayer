#ifndef CENTERUI_H
#define CENTERUI_H

#include <QWidget>
#include <QLabel>
#include <QPicture>
#include <QVBoxLayout>
#include <QImage>
#include <QPixmap>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QListView>
#include <QMatrix>

class CenterUI : public QWidget
{
    Q_OBJECT
public:
    explicit CenterUI(QWidget *parent = nullptr);
    QLabel *songname;
    QLabel *songimage;
    QPixmap pix;
    QListView *list;
    int pox=0;
signals:

public slots:
    void chengeImageView();
    void resetImageView();
};

#endif // CENTERUI_H
