#include "centerui.h"

#include <QDebug>
CenterUI::CenterUI(QWidget *parent) : QWidget(parent)
{
    songname = new QLabel;
    songimage = new QLabel;
    list = new QListView;

    QVBoxLayout *root = new QVBoxLayout(this);

    QHBoxLayout *v1 = new QHBoxLayout();
    QHBoxLayout *v2 = new QHBoxLayout();


    pix.load(":/img/fm.png");
    songimage->setPixmap(pix);
    songimage->setFixedSize(354,354);
    songimage->setAlignment(Qt::AlignCenter);


    songname->setText("Waiting you ..");
    songname->setFixedSize(700,30);
    songname->setFont(QFont("微软雅黑",15,1));
    songname->setAlignment(Qt::AlignHCenter);

    list->setFixedSize(300,400);

    v1->addWidget(songname);
    v2->addWidget(songimage);
    v2->addWidget(list);

    root->addLayout(v1);
    root->addLayout(v2);


}

void CenterUI::chengeImageView(){
    QMatrix le ;
    le.rotate(pox);
    pix.load(":/img/cp.png");
    QPixmap pix2 = pix.transformed(le,Qt::SmoothTransformation);
    songimage->setPixmap(pix2);
    update();
    pox+=35;
}

void CenterUI::resetImageView(){

    QPixmap pix1;
    pix1.load(":/img/fm.png");
    songimage->setPixmap(pix1);
    update();
}
